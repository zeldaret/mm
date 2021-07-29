from typing import Callable, Dict, List, Tuple
import re

from .perm import (
    Perm,
    CombinePerm,
    GeneralPerm,
    RandomizerPerm,
    TextPerm,
    TernaryPerm,
    TypecastPerm,
    VarPerm,
    CondNezPerm,
    LineSwapPerm,
    IntPerm,
)


def split_args(args: List[str]) -> List[Perm]:
    perm_args = [rec_perm_gen(arg) for arg in args]
    return perm_args


def split_args_newline(args: List[str]) -> List[Perm]:
    s = "\n".join(args)
    lines = [line for line in s.split("\n") if line and not line.isspace()]
    perm_args = [rec_perm_gen(line) for line in lines]
    return perm_args


def split_args_text(args: List[str]) -> List[str]:
    perm_list = split_args(args)
    res: List[str] = []
    for perm in perm_list:
        assert isinstance(perm, TextPerm)
        res.append(perm.text)
    return res


perm_create: Dict[str, Callable[[List[str]], Perm]] = {
    "PERM_GENERAL": lambda args: GeneralPerm(split_args(args)),
    "PERM_RANDOMIZE": lambda args: RandomizerPerm(split_args(args)[0]),
    "PERM_TERNARY": lambda args: TernaryPerm(*split_args(args)),
    "PERM_TYPECAST": lambda args: TypecastPerm(split_args(args)),
    "PERM_VAR": lambda args: VarPerm(split_args(args)),
    "PERM_CONDNEZ": lambda args: CondNezPerm(*split_args(args)),
    "PERM_LINESWAP": lambda args: LineSwapPerm(split_args_newline(args)),
    "PERM_INT": lambda args: IntPerm(*map(int, split_args_text(args))),
}


def get_parenthesis_args(s: str) -> Tuple[List[str], str]:
    level = 0
    current = ""
    remain = ""
    args = []
    for i, c in enumerate(s):
        # Find individual args
        if c == "," and level == 1:
            args.append(current)
            current = ""
        # Track parenthesis level
        else:
            if c == "(":
                level += 1
                if level == 1:  # Ignore first parenthesis
                    continue
            elif c == ")":
                level -= 1
                if level == 0:  # Last closing parenthesis; get remaining and finish
                    args.append(current)
                    if i + 1 < len(s):
                        remain = s[i + 1 :]
                    break
            current += c
    assert level == 0, "Error, no closing parenthesis found"
    return args, remain


def rec_perm_gen(input: str) -> Perm:
    remain = input
    macro_search = r"(PERM_.+?)\("

    perms: List[Perm] = []
    while len(remain) > 0:
        match = re.search(macro_search, remain)

        # No match found; return remaining
        if match is None:
            text_perm = TextPerm(remain)
            perms.append(text_perm)
            break

        # Get perm type and args
        perm_type = match.group(1)
        if not perm_type in perm_create:
            raise Exception("Could not evaluate expression:" + perm_type)
        between = remain[: match.start()]
        args, remain = get_parenthesis_args(remain[match.end() - 1 :])

        # Create text perm
        perms.append(TextPerm(between))

        # Create new perm
        perms.append(perm_create[perm_type](args))

    if len(perms) == 1:
        return perms[0]
    return CombinePerm(perms)


def perm_gen(input: str) -> Perm:
    ret = rec_perm_gen(input)
    if isinstance(ret, TextPerm):
        ret = RandomizerPerm(ret)
        print("No perm macros found. Defaulting to randomization")
    return ret
