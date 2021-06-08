from typing import Optional

from .permuter import Permuter

# Number of additional characters to replace with spaces, in addition to what
# is required based on the length of the previous progress line. This could be
# set to 0, but it's nice to have some margin to deal with e.g. zero-width
# control characters.
SAFETY_PAD = 10


class Printer:
    _last_progress: Optional[str] = None

    def progress(self, message: str) -> None:
        if self._last_progress is None:
            clear = ""
        else:
            pad = max(len(self._last_progress) - len(message) + SAFETY_PAD, 0)
            clear = "\b" * pad + " " * pad + "\r"
        print(clear + message, end="", flush=True)
        self._last_progress = message

    def print(
        self,
        message: str,
        permuter: Optional[Permuter],
        who: Optional[str],
        *,
        color: str = "",
        keep_progress: bool = False,
    ) -> None:
        if self._last_progress is not None:
            if keep_progress:
                print()
            else:
                pad = len(self._last_progress) + SAFETY_PAD
                print("\r" + " " * pad + "\r", end="")
        if permuter is not None:
            message = f"[{permuter.unique_name}] {message}"
        if who is not None:
            message = f"[{who}] {message}"
        if color:
            message = f"{color}{message}\u001b[0m"
        print(message)
        self._last_progress = None
