from argparse import ArgumentParser, Namespace
import time

from ...helpers import plural
from ..core import connect, json_prop
from .base import Command


class PingCommand(Command):
    command = "ping"
    help = "Check server connectivity."

    @staticmethod
    def add_arguments(parser: ArgumentParser) -> None:
        pass

    @staticmethod
    def run(args: Namespace) -> None:
        run_ping()


def run_ping() -> None:
    port = connect()
    t0 = time.time()
    port.send_json({"method": "ping"})
    msg = port.receive_json()
    rtt = (time.time() - t0) * 1000
    print(f"Connected successfully! Round-trip time: {rtt:.1f} ms")
    servers_str = plural(json_prop(msg, "servers", int), "server")
    clients_str = plural(json_prop(msg, "clients", int), "client")
    cores_str = plural(int(json_prop(msg, "cores", float)), "core")
    print(f"{servers_str} online ({cores_str}, {clients_str})")
