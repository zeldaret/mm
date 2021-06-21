from typing import List
import subprocess


def preprocess(filename: str, cpp_args: List[str] = []) -> str:
    return subprocess.check_output(
        ["cpp"] + cpp_args + ["-P", "-nostdinc", filename],
        universal_newlines=True,
        encoding="utf-8",
    )
