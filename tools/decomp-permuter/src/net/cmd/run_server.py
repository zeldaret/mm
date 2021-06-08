from argparse import ArgumentParser, Namespace
import base64
from dataclasses import dataclass
from enum import Enum
from functools import partial
import json
import os
import platform
import queue
import random
import shutil
from subprocess import Popen, PIPE
import sys
import time
import threading
import traceback
from typing import Any, Callable, Dict, List, Optional, TYPE_CHECKING

from ...helpers import static_assert_unreachable
from ..core import CancelToken, ServerError, read_config
from ..server import (
    Client,
    Config,
    IoActivity,
    IoConnect,
    IoDisconnect,
    IoImmediateDisconnect,
    IoReconnect,
    IoServerFailed,
    IoShutdown,
    IoUserRemovePermuter,
    IoWorkDone,
    PermuterHandle,
    Server,
    ServerOptions,
)
from .base import Command
from .util import ask


class RunServerCommand(Command):
    command = "run-server"
    help = """Run a permuter server, allowing anyone with access to the central
        server to run sandboxed permuter jobs on your machine. Requires docker."""

    @staticmethod
    def add_arguments(parser: ArgumentParser) -> None:
        parser.add_argument(
            "--cores",
            dest="num_cores",
            metavar="CORES",
            type=float,
            required=True,
            help="Number of cores to use (float).",
        )
        parser.add_argument(
            "--memory",
            dest="max_memory_gb",
            metavar="MEMORY_GB",
            type=float,
            required=True,
            help="""Restrict the sandboxed process to the given amount of memory in
                gigabytes (float). If this limit is hit, the permuter will crash
                horribly, but at least your system won't lock up.""",
        )
        parser.add_argument(
            "--systray",
            dest="systray",
            action="store_true",
            help="""Make the server controllable through the system tray.""",
        )
        parser.add_argument(
            "--min-priority",
            dest="min_priority",
            metavar="PRIORITY",
            type=float,
            default=0.1,
            help="""Only accept jobs from clients who pass --priority with a number
                higher or equal to this value. (default: %(default)s)""",
        )

    @staticmethod
    def run(args: Namespace) -> None:
        options = ServerOptions(
            num_cores=args.num_cores,
            max_memory_gb=args.max_memory_gb,
            min_priority=args.min_priority,
        )

        server_main(options, args.systray)


class SystrayState:
    def server_reconnecting(self) -> None:
        pass

    def server_connected(self) -> None:
        pass

    def server_failed(self, graceful: bool, message: Optional[str] = None) -> None:
        pass

    def connect(self, handle: PermuterHandle, nickname: str, fn_name: str) -> None:
        pass

    def disconnect(self, handle: PermuterHandle) -> None:
        pass

    def work_done(self, handle: PermuterHandle, is_improvement: bool) -> None:
        pass

    def stop(self) -> None:
        pass


@dataclass
class Permuter:
    nickname: str
    fn_name: str
    iterations: int = 0
    improvements: int = 0
    last_systray_update: float = 0.0
    slot: "Optional[ClientSlot]" = None


@dataclass
class ClientSlot:
    menu_id: int
    iterations_id: int
    improvements_id: int
    stop_id: int
    permuter: Optional[PermuterHandle] = None


class SystrayStatus(Enum):
    CONNECTING = 0
    CONNECTED = 1
    FAILED = 2
    RECONNECTING = 3


class RealSystrayState(SystrayState):
    _CLIENT_SLOTS = 10
    _UPDATE_INTERVAL = 2.0
    _MENU_TOOLTIP = "permuter@home"
    _permuters: Dict[PermuterHandle, Permuter]
    _onclick: Dict[int, Callable[[], None]]
    _client_slots: List[ClientSlot]

    def __init__(
        self,
        config: Config,
        io_queue: "queue.Queue[IoActivity]",
    ) -> None:
        self._io_queue = io_queue
        self._permuters = {}
        self._onclick = {}
        self._status = SystrayStatus.CONNECTING
        self._fail_message: Optional[str] = None

        def load_icon(fname: str) -> str:
            path = os.path.join(os.path.dirname(__file__), "icons", fname)
            with open(path, "rb") as f:
                data = f.read()
            return base64.b64encode(data).decode("ascii")

        self._icons = {
            "working": load_icon("okthink.ico"),
            "passive": load_icon("ok.ico"),
            "fail": load_icon("notok.ico"),
        }
        self._current_icon = "working"

        next_id = 100

        def add_item(
            menu: List[dict],
            title: str,
            onclick: Optional[Callable[[], None]] = None,
            *,
            submenu: Optional[List[dict]] = None,
            hidden: bool = False,
        ) -> int:
            nonlocal next_id
            next_id += 1
            obj = {
                "title": title,
                "enabled": onclick is not None or submenu is not None,
                "hidden": hidden,
                "__id": next_id,
            }
            if onclick is not None:
                self._onclick[next_id] = onclick
            if submenu is not None:
                obj["items"] = submenu
            menu.append(obj)
            return next_id

        menu: List[dict] = []
        self._status_id = add_item(menu, "Connecting...")
        self._client_slots = []
        for i in range(self._CLIENT_SLOTS):
            submenu: List[dict] = []
            remove_cb = partial(self._remove_permuter, i)
            self._client_slots.append(
                ClientSlot(
                    iterations_id=add_item(submenu, ""),
                    improvements_id=add_item(submenu, ""),
                    stop_id=add_item(submenu, "Stop", remove_cb),
                    menu_id=add_item(menu, "", submenu=submenu, hidden=True),
                )
            )
        self._more_id = add_item(menu, "", hidden=True)
        add_item(menu, "Quit", self._quit)

        try:
            path = self._setup_helper()
            self._proc = Popen(
                [path],
                stdout=PIPE,
                stdin=PIPE,
                universal_newlines=True,
            )
            assert self._proc.stdout is not None
            self._proc_stdout = self._proc.stdout
            assert self._proc.stdin is not None
            self._proc_stdin = self._proc.stdin

            self._send(
                {
                    "icon": self._icons[self._current_icon],
                    "tooltip": self._MENU_TOOLTIP,
                    "items": menu,
                }
            )

            resp_str = self._proc_stdout.readline()
            assert resp_str
            resp = json.loads(resp_str)
            assert isinstance(resp, dict)
            assert resp.get("type") == "ready"
        except Exception:
            print("Failed to initialize systray!")
            print()
            print("See src/net/cmd/systray/README.md for details on how to set it up.")
            traceback.print_exc()
            sys.exit(1)

        self._read_thread = threading.Thread(target=self._read_loop, daemon=True)
        self._read_thread.start()

    @staticmethod
    def _setup_helper() -> str:
        fname = "permuter-systray"
        suffix = ""
        osname = sys.platform.replace("darwin", "macos")
        arch = platform.machine().replace("AMD64", "x86_64")
        if (
            osname in ("win32", "msys", "cygwin")
            or "microsoft" in platform.uname().release.lower()
        ):
            osname = "win"
            suffix = ".exe"

        dir = os.path.join(os.path.dirname(__file__), "systray")
        target_binary = os.path.join(dir, fname + suffix)
        if os.path.exists(target_binary):
            return target_binary

        prebuilt_file = f"{fname}-{osname}-{arch}{suffix}"
        prebuilt_file = os.path.join(dir, "prebuilt", prebuilt_file)

        print("An external helper binary is required for systray support.")
        print(
            "To build it from source (requires Go), see src/net/cmd/systray/README.md."
        )

        if os.path.exists(prebuilt_file):
            print("Alternatively, a pre-built binary can be used.")
            if ask("Use pre-built binary?", default=False):
                shutil.copy(prebuilt_file, target_binary)
                os.chmod(target_binary, 0o755)
                return target_binary

        print("Aborting.")
        sys.exit(1)

    def _send(self, msg: dict) -> None:
        data = json.dumps(msg)
        self._proc_stdin.write(data + "\n")
        self._proc_stdin.flush()

    def _update_item(
        self, id: int, title: str, *, hidden: bool = False, enabled: bool = False
    ) -> None:
        self._send(
            {
                "type": "update-item",
                "item": {
                    "title": title,
                    "enabled": enabled,
                    "hidden": hidden,
                    "__id": id,
                },
                "seq_id": -1,
            }
        )

    def _remove_permuter(self, slot_index: int) -> None:
        slot = self._client_slots[slot_index]
        if not slot.permuter:
            return
        handle = slot.permuter
        self._io_queue.put((None, (handle, IoUserRemovePermuter())))

    def _quit(self) -> None:
        self._io_queue.put((None, IoShutdown()))

    def _read_loop(self) -> None:
        while True:
            resp_str = self._proc_stdout.readline()
            if not resp_str:
                break
            try:
                resp = json.loads(resp_str)
            except Exception:
                raise Exception(f"Failed to parse systray JSON: {resp_str}") from None
            if resp["type"] == "clicked":
                id = resp["__id"]
                if id in self._onclick:
                    self._onclick[id]()

    def _permuter_slot(self, perm: Permuter) -> Optional[ClientSlot]:
        for slot in self._client_slots:
            if slot.permuter is not None and self._permuters[slot.permuter] is perm:
                return slot
        return None

    def _update_permuter(self, perm: Permuter, slot: ClientSlot) -> None:
        self._update_item(
            slot.iterations_id,
            f"Iterations: {perm.iterations}",
        )
        self._update_item(
            slot.improvements_id,
            f"Improvements found: {perm.improvements}",
        )

    def _update_status(self) -> None:
        if self._status == SystrayStatus.CONNECTING:
            status = "Reconnecting..."
            icon = "working"
        elif self._status == SystrayStatus.RECONNECTING:
            status = "Disconnected, will reconnect..."
            icon = "fail"
        elif self._status == SystrayStatus.CONNECTED:
            if self._permuters:
                status = "Currently permuting:"
                icon = "working"
            else:
                status = "Not running"
                icon = "passive"
        elif self._status == SystrayStatus.FAILED:
            if self._fail_message:
                status = f"Error: {self._fail_message}"
            else:
                status = "Error occurred"
            icon = "fail"
        else:
            assert False, f"bad status {self._status}"

        self._update_item(self._status_id, status)
        if self._current_icon != icon:
            self._current_icon = icon
            self._send(
                {
                    "type": "update-menu",
                    "menu": {
                        "tooltip": self._MENU_TOOLTIP,
                        "icon": self._icons[icon],
                    },
                }
            )

    def _fill_slots(self) -> None:
        has_more = False
        while True:
            key = next((k for k, p in self._permuters.items() if p.slot is None), None)
            if key is None:
                break
            chosen_slot: Optional[ClientSlot] = None
            for i in range(self._CLIENT_SLOTS - 1, -1, -1):
                slot = self._client_slots[i]
                if slot.permuter is None:
                    chosen_slot = slot
                elif chosen_slot is not None:
                    break
            if chosen_slot is None:
                has_more = True
                break
            perm = self._permuters[key]
            perm.slot = chosen_slot
            chosen_slot.permuter = key
            self._update_permuter(perm, chosen_slot)
            self._update_item(
                chosen_slot.menu_id, f"{perm.fn_name} ({perm.nickname})", enabled=True
            )
        self._update_item(self._more_id, "More...", hidden=not has_more)

    def _hide_slot(self, slot: ClientSlot) -> None:
        if slot.permuter is not None:
            self._update_item(slot.menu_id, "", hidden=True)
        slot.permuter = None

    def server_reconnecting(self) -> None:
        self._status = SystrayStatus.CONNECTING
        self._update_status()

    def server_connected(self) -> None:
        self._status = SystrayStatus.CONNECTED
        self._update_status()

    def server_failed(self, graceful: bool, message: Optional[str] = None) -> None:
        self._status = SystrayStatus.RECONNECTING if graceful else SystrayStatus.FAILED
        self._fail_message = message
        self._permuters = {}
        self._update_status()
        for slot in self._client_slots:
            self._hide_slot(slot)
        self._fill_slots()

    def connect(self, handle: PermuterHandle, nickname: str, fn_name: str) -> None:
        perm = Permuter(nickname, fn_name)
        self._permuters[handle] = perm
        self._fill_slots()
        self._update_status()

    def disconnect(self, handle: PermuterHandle) -> None:
        slot = self._permuters[handle].slot
        del self._permuters[handle]
        self._update_status()
        if slot:
            self._hide_slot(slot)
        self._fill_slots()

    def work_done(self, handle: PermuterHandle, is_improvement: bool) -> None:
        perm = self._permuters[handle]
        perm.iterations += 1
        if is_improvement:
            perm.improvements += 1
        if perm.slot and time.time() > perm.last_systray_update + self._UPDATE_INTERVAL:
            perm.last_systray_update = time.time()
            self._update_permuter(perm, perm.slot)

    def stop(self) -> None:
        try:
            self._send({"type": "exit"})
        except BrokenPipeError:
            # The systray process may have been killed by Ctrl+C.
            pass
        self._proc.wait()
        self._read_thread.join()


class Reconnector:
    _RESET_BACKOFF_AFTER_UPTIME: float = 60.0
    _RANDOM_ADDEND_MAX: float = 60.0
    _BACKOFF_MULTIPLIER: float = 2.0
    _INITIAL_DELAY: float = 5.0

    _io_queue: "queue.Queue[IoActivity]"
    _reconnect_token: CancelToken
    _reconnect_delay: float
    _reconnect_timer: Optional[threading.Timer]
    _start_time: float
    _stop_time: float

    def __init__(self, io_queue: "queue.Queue[IoActivity]") -> None:
        self._io_queue = io_queue
        self._reconnect_token = CancelToken()
        self._reconnect_delay = self._INITIAL_DELAY
        self._reconnect_timer = None
        self._start_time = self._stop_time = time.time()

    def mark_start(self) -> None:
        self._start_time = time.time()

    def mark_stop(self) -> None:
        self._stop_time = time.time()

    def stop(self) -> None:
        self._reconnect_token.cancelled = True
        if self._reconnect_timer is not None:
            self._reconnect_timer.cancel()
            self._reconnect_timer.join()
            self._reconnect_timer = None

    def reconnect_eventually(self) -> int:
        if self._stop_time - self._start_time > self._RESET_BACKOFF_AFTER_UPTIME:
            delay = self._reconnect_delay = self._INITIAL_DELAY
        else:
            delay = self._reconnect_delay
            self._reconnect_delay = (
                self._reconnect_delay * self._BACKOFF_MULTIPLIER
                + random.uniform(1.0, self._RANDOM_ADDEND_MAX)
            )
        token = CancelToken()
        self._reconnect_token = token
        self._reconnect_timer = threading.Timer(
            delay, lambda: self._io_queue.put((token, IoReconnect()))
        )
        self._reconnect_timer.daemon = True
        self._reconnect_timer.start()
        return int(delay)


def main_loop(
    io_queue: "queue.Queue[IoActivity]",
    server: Server,
    systray: SystrayState,
) -> None:
    reconnector = Reconnector(io_queue)
    handle_clients: Dict[PermuterHandle, Client] = {}
    while True:
        token, activity = io_queue.get()
        if token and token.cancelled:
            continue

        if not isinstance(activity, tuple):
            if isinstance(activity, IoShutdown):
                break

            elif isinstance(activity, IoReconnect):
                print("reconnecting...")
                try:
                    systray.server_reconnecting()
                    reconnector.mark_start()
                    server.start()
                    systray.server_connected()
                except EOFError:
                    delay = reconnector.reconnect_eventually()
                    print(f"failed again, reconnecting in {delay} seconds...")
                    systray.server_failed(True)
                except ServerError as e:
                    print("failed!", e.message)
                    systray.server_failed(False, e.message)
                except Exception:
                    print("failed!")
                    traceback.print_exc()
                    systray.server_failed(False)

            elif isinstance(activity, IoServerFailed):
                if activity.message:
                    print("Server error:", activity.message)
                print("disconnected from permuter@home")
                server.stop()
                reconnector.mark_stop()
                systray.server_failed(activity.graceful, activity.message)

                if activity.graceful:
                    delay = reconnector.reconnect_eventually()
                    print(f"will reconnect in {delay} seconds...")

            else:
                static_assert_unreachable(activity)

        else:
            handle, msg = activity

            if isinstance(msg, IoConnect):
                client = msg.client
                handle_clients[handle] = client
                systray.connect(handle, client.nickname, msg.fn_name)
                print(f"[{client.nickname}] connected ({msg.fn_name})")

            elif isinstance(msg, IoDisconnect):
                systray.disconnect(handle)
                nickname = handle_clients[handle].nickname
                del handle_clients[handle]
                print(f"[{nickname}] {msg.reason}")

            elif isinstance(msg, IoImmediateDisconnect):
                print(f"[{msg.client.nickname}] {msg.reason}")

            elif isinstance(msg, IoWorkDone):
                # TODO: statistics
                systray.work_done(handle, msg.is_improvement)

            elif isinstance(msg, IoUserRemovePermuter):
                server.remove_permuter(handle)

            else:
                static_assert_unreachable(msg)


def server_main(options: ServerOptions, use_systray: bool) -> None:
    io_queue: "queue.Queue[IoActivity]" = queue.Queue()
    config = read_config()

    systray: SystrayState
    if use_systray:
        systray = RealSystrayState(config, io_queue)
    else:
        systray = SystrayState()

    try:
        server = Server(options, config, io_queue)
        server.start()

        try:
            systray.server_connected()
            main_loop(io_queue, server, systray)
        finally:
            server.stop()
    finally:
        systray.stop()
