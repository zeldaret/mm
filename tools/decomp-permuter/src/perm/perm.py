from base64 import b64encode
from collections import defaultdict
from dataclasses import dataclass, field
from typing import Dict, List, Tuple, TypeVar, Optional
import math

from pycparser import c_ast as ca

from ..ast_util import Statement

T = TypeVar("T")


@dataclass
class PreprocessState:
    once_options: Dict[str, List["Perm"]] = field(
        default_factory=lambda: defaultdict(list)
    )


@dataclass
class EvalState:
    vars: Dict[str, str] = field(default_factory=dict)
    once_choices: Dict[str, "Perm"] = field(default_factory=dict)
    ast_perms: List[Tuple["Perm", int]] = field(default_factory=list)

    def register_ast_perm(self, perm: "Perm", seed: int) -> int:
        ret = len(self.ast_perms)
        self.ast_perms.append((perm, seed))
        return ret

    def gen_ast_statement_perm(
        self, perm: "Perm", seed: int, *, statements: List[str]
    ) -> str:
        perm_id = self.register_ast_perm(perm, seed)
        lines = [
            "{",
            f"#pragma _permuter ast_perm {perm_id}",
            *["{" + stmt + "}" for stmt in statements],
            "}",
        ]
        return "\n".join(lines)


class Perm:
    """A Perm subclass generates different variations of a part of the source
    code. Its evaluate method will be called with a seed between 0 and
    perm_count-1, and it should return a unique string for each.

    A Perm is allowed to return different strings for the same seed, but if so,
    if should override is_random to return True. This will cause permutation
    to happen in an infinite loop, rather than stop after the last permutation
    has been tested."""

    perm_count: int
    children: List["Perm"]

    def evaluate(self, seed: int, state: EvalState) -> str:
        return ""

    def eval_statement_ast(self, args: List[Statement], seed: int) -> List[Statement]:
        raise NotImplementedError

    def preprocess(self, state: PreprocessState) -> None:
        for p in self.children:
            p.preprocess(state)

    def is_random(self) -> bool:
        return any(p.is_random() for p in self.children)


def _eval_all(seed: int, perms: List[Perm], state: EvalState) -> List[str]:
    ret = []
    for p in perms:
        seed, sub_seed = divmod(seed, p.perm_count)
        ret.append(p.evaluate(sub_seed, state))
    assert seed == 0, "seed must be in [0, prod(counts))"
    return ret


def _count_all(perms: List[Perm]) -> int:
    res = 1
    for p in perms:
        res *= p.perm_count
    return res


def _eval_either(seed: int, perms: List[Perm], state: EvalState) -> str:
    for p in perms:
        if seed < p.perm_count:
            return p.evaluate(seed, state)
        seed -= p.perm_count
    assert False, "seed must be in [0, sum(counts))"


def _count_either(perms: List[Perm]) -> int:
    return sum(p.perm_count for p in perms)


def _shuffle(items: List[T], seed: int) -> List[T]:
    items = items[:]
    output = []
    while items:
        ind = seed % len(items)
        seed //= len(items)
        output.append(items[ind])
        del items[ind]
    return output


class RootPerm(Perm):
    def __init__(self, inner: Perm) -> None:
        self.children = [inner]
        self.perm_count = inner.perm_count
        self.preprocess_state = PreprocessState()
        self.preprocess(self.preprocess_state)
        for key, options in self.preprocess_state.once_options.items():
            if len(options) == 1:
                raise Exception(f"PERM_ONCE({key}) occurs only once, possible error?")
            self.perm_count *= len(options)

    def evaluate(self, seed: int, state: EvalState) -> str:
        for key, options in self.preprocess_state.once_options.items():
            seed, choice = divmod(seed, len(options))
            state.once_choices[key] = options[choice]
        return self.children[0].evaluate(seed, state)


class TextPerm(Perm):
    def __init__(self, text: str) -> None:
        # Comma escape sequence
        text = text.replace("(,)", ",")
        self.text = text
        self.children = []
        self.perm_count = 1

    def evaluate(self, seed: int, state: EvalState) -> str:
        return self.text


class IgnorePerm(Perm):
    def __init__(self, inner: Perm) -> None:
        self.children = [inner]
        self.perm_count = inner.perm_count

    def evaluate(self, seed: int, state: EvalState) -> str:
        text = self.children[0].evaluate(seed, state)
        if not text:
            return ""
        encoded = b64encode(text.encode("utf-8")).decode("ascii")
        return "#pragma _permuter b64literal " + encoded


class PretendPerm(Perm):
    def __init__(self, inner: Perm) -> None:
        self.children = [inner]
        self.perm_count = inner.perm_count

    def evaluate(self, seed: int, state: EvalState) -> str:
        text = self.children[0].evaluate(seed, state)
        return "\n".join(
            [
                "",
                "#pragma _permuter latedefine start",
                text,
                "#pragma _permuter latedefine end",
                "",
            ]
        )


class CombinePerm(Perm):
    def __init__(self, parts: List[Perm]) -> None:
        self.children = parts
        self.perm_count = _count_all(parts)

    def evaluate(self, seed: int, state: EvalState) -> str:
        texts = _eval_all(seed, self.children, state)
        return "".join(texts)


class RandomizerPerm(Perm):
    def __init__(self, inner: Perm) -> None:
        self.children = [inner]
        self.perm_count = inner.perm_count

    def evaluate(self, seed: int, state: EvalState) -> str:
        text = self.children[0].evaluate(seed, state)
        return "\n".join(
            [
                "",
                "#pragma _permuter randomizer start",
                text,
                "#pragma _permuter randomizer end",
                "",
            ]
        )

    def is_random(self) -> bool:
        return True


class GeneralPerm(Perm):
    def __init__(self, candidates: List[Perm]) -> None:
        self.perm_count = _count_either(candidates)
        self.children = candidates

    def evaluate(self, seed: int, state: EvalState) -> str:
        return _eval_either(seed, self.children, state)


class OncePerm(Perm):
    def __init__(self, key: str, inner: Perm) -> None:
        self.key = key
        self.children = [inner]
        self.perm_count = inner.perm_count

    def preprocess(self, state: PreprocessState) -> None:
        state.once_options[self.key].append(self)
        super().preprocess(state)

    def evaluate(self, seed: int, state: EvalState) -> str:
        if state.once_choices[self.key] is self:
            return self.children[0].evaluate(seed, state)
        return ""


class VarPerm(Perm):
    def __init__(self, var_name: Perm, expansion: Optional[Perm]) -> None:
        if expansion:
            self.children = [var_name, expansion]
        else:
            self.children = [var_name]
        self.perm_count = _count_all(self.children)

    def evaluate(self, seed: int, state: EvalState) -> str:
        var_name_perm = self.children[0]
        seed, sub_seed = divmod(seed, var_name_perm.perm_count)
        var_name = var_name_perm.evaluate(sub_seed, state).strip()
        if len(self.children) > 1:
            ret = self.children[1].evaluate(seed, state)
            state.vars[var_name] = ret
            return ""
        else:
            if var_name not in state.vars:
                raise Exception(f"Tried to read undefined PERM_VAR {var_name}")
            return state.vars[var_name]


class LineSwapPerm(Perm):
    def __init__(self, lines: List[Perm]) -> None:
        self.children = lines
        self.own_count = math.factorial(len(lines))
        self.perm_count = self.own_count * _count_all(self.children)

    def evaluate(self, seed: int, state: EvalState) -> str:
        sub_seed, variation = divmod(seed, self.own_count)
        texts = _eval_all(sub_seed, self.children, state)
        return "\n".join(_shuffle(texts, variation))


class LineSwapAstPerm(Perm):
    def __init__(self, lines: List[Perm]) -> None:
        self.children = lines
        self.own_count = math.factorial(len(lines))
        self.perm_count = self.own_count * _count_all(self.children)

    def evaluate(self, seed: int, state: EvalState) -> str:
        sub_seed, variation = divmod(seed, self.own_count)
        texts = _eval_all(sub_seed, self.children, state)
        return state.gen_ast_statement_perm(self, variation, statements=texts)

    def eval_statement_ast(self, args: List[Statement], seed: int) -> List[Statement]:
        ret = []
        for item in _shuffle(args, seed):
            assert isinstance(item, ca.Compound)
            ret.extend(item.block_items or [])
        return ret


class IntPerm(Perm):
    def __init__(self, low: int, high: int) -> None:
        assert low <= high
        self.low = low
        self.children = []
        self.perm_count = high - low + 1

    def evaluate(self, seed: int, state: EvalState) -> str:
        return str(self.low + seed)
