import sys


def ask(msg: str, *, default: bool) -> bool:
    if default:
        msg += " (Y/n)? "
    else:
        msg += " (y/N)? "
    res = input(msg).strip().lower()
    if not res:
        return default
    if res in ["y", "yes", "n", "no"]:
        return res[0] == "y"
    print("Bad response!")
    sys.exit(1)
