from typing import Optional
import tempfile
import subprocess

from .helpers import try_remove


class Compiler:
    def __init__(self, compile_cmd: str, show_errors: bool = False) -> None:
        self.compile_cmd = compile_cmd
        self.show_errors = show_errors

    def compile(self, source: str, show_errors: bool = False) -> Optional[str]:
        show_errors = show_errors or self.show_errors
        with tempfile.NamedTemporaryFile(
            prefix="permuter", suffix=".c", mode="w", delete=False
        ) as f:
            c_name = f.name
            f.write(source)

        with tempfile.NamedTemporaryFile(
            prefix="permuter", suffix=".o", delete=False
        ) as f2:
            o_name = f2.name

        try:
            stderr = None if show_errors else subprocess.DEVNULL
            subprocess.check_call(
                self.compile_cmd + " " + c_name + " -o " + o_name,
                shell=True,
                stderr=stderr,
            )
        except subprocess.CalledProcessError:
            if not show_errors:
                try_remove(c_name)
            try_remove(o_name)
            return None
        except KeyboardInterrupt:
            # If Ctrl+C happens during this call, make a best effort in
            # removing the .c and .o files. This is totally racy, but oh well...
            try_remove(c_name)
            try_remove(o_name)
            raise

        try_remove(c_name)
        return o_name
