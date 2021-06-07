import random
from typing import List, Iterable, Set, Tuple

from .perm import Perm, EvalState


def _gen_all_seeds(total_count: int) -> Iterable[int]:
    """Generate all numbers 0..total_count-1 in random order, in expected time
    O(1) per number."""
    seen: Set[int] = set()
    while len(seen) < total_count // 2:
        seed = random.randrange(total_count)
        if seed not in seen:
            seen.add(seed)
            yield seed

    remaining: List[int] = []
    for seed in range(total_count):
        if seed not in seen:
            remaining.append(seed)
    random.shuffle(remaining)
    for seed in remaining:
        yield seed


def perm_gen_all_seeds(perm: Perm) -> Iterable[int]:
    while True:
        for seed in _gen_all_seeds(perm.perm_count):
            yield seed
        if not perm.is_random():
            break


def perm_evaluate_one(perm: Perm) -> Tuple[str, EvalState]:
    eval_state = EvalState()
    return perm.evaluate(0, eval_state), eval_state
