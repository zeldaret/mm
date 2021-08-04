import os


def try_remove(path: str) -> None:
    try:
        os.remove(path)
    except FileNotFoundError:
        pass
