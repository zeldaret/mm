def bits(p: int, s: int, n: int):
    return (p >> s) & ((1 << n) - 1)


def cbool(b: bool):
    return "true" if b else "false"


PARAMS_FMT = {}

INCLUDES = {}
