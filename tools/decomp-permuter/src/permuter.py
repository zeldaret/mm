from dataclasses import dataclass
import difflib
import itertools
import random
import re
import time
import traceback
from typing import (
    Any,
    List,
    Iterator,
    Optional,
    Tuple,
    Union,
)

from .candidate import Candidate, CandidateResult
from .compiler import Compiler
from .error import CandidateConstructionFailure
from .perm.perm import EvalState
from .perm.eval import perm_evaluate_one, perm_gen_all_seeds
from .perm.parse import perm_parse
from .profiler import Profiler
from .scorer import Scorer


@dataclass
class EvalError:
    exc_str: Optional[str]
    seed: Optional[Tuple[int, int]]


EvalResult = Union[CandidateResult, EvalError]


@dataclass
class Finished:
    reason: Optional[str] = None


@dataclass
class Message:
    text: str


class NeedMoreWork:
    pass


class _CompileFailure(Exception):
    pass


@dataclass
class WorkDone:
    perm_index: int
    result: EvalResult


Task = Union[Finished, Tuple[int, int]]
FeedbackItem = Union[Finished, Message, NeedMoreWork, WorkDone]
Feedback = Tuple[FeedbackItem, int, Optional[str]]


class Permuter:
    """
    Represents a single source from which permutation candidates can be generated,
    and which keeps track of good scores achieved so far.
    """

    def __init__(
        self,
        dir: str,
        fn_name: Optional[str],
        compiler: Compiler,
        scorer: Scorer,
        source_file: str,
        source: str,
        *,
        force_seed: Optional[int],
        force_rng_seed: Optional[int],
        keep_prob: float,
        need_profiler: bool,
        need_all_sources: bool,
        show_errors: bool,
        best_only: bool,
        better_only: bool,
    ) -> None:
        self.dir = dir
        self.compiler = compiler
        self.scorer = scorer
        self.source_file = source_file
        self.source = source

        if fn_name is None:
            # Semi-legacy codepath; all functions imported through import.py have a
            # function name. This would ideally be done on AST level instead of on the
            # pre-macro'ed source code, but we don't care enough to make that
            # refactoring.
            fns = _find_fns(source)
            if len(fns) == 0:
                raise Exception(f"{self.source_file} does not contain any function!")
            if len(fns) > 1:
                raise Exception(
                    f"{self.source_file} must contain only one function, "
                    "or have a function.txt next to it with a function name."
                )
            self.fn_name = fns[0]
        else:
            self.fn_name = fn_name
        self.unique_name = self.fn_name

        self._permutations = perm_parse(source)

        self._force_seed = force_seed
        self._force_rng_seed = force_rng_seed
        self._cur_seed: Optional[Tuple[int, int]] = None

        self.keep_prob = keep_prob
        self.need_profiler = need_profiler
        self._need_all_sources = need_all_sources
        self._show_errors = show_errors
        self._best_only = best_only
        self._better_only = better_only

        (
            self.base_score,
            self.base_hash,
            self.base_source,
        ) = self._create_and_score_base()
        self.best_score = self.base_score
        self.hashes = {self.base_hash}
        self._cur_cand: Optional[Candidate] = None
        self._last_score: Optional[int] = None

    def _create_and_score_base(self) -> Tuple[int, str, str]:
        base_source, eval_state = perm_evaluate_one(self._permutations)
        base_cand = Candidate.from_source(
            base_source, eval_state, self.fn_name, rng_seed=0
        )
        o_file = base_cand.compile(self.compiler, show_errors=True)
        if not o_file:
            raise CandidateConstructionFailure(f"Unable to compile {self.source_file}")
        base_result = base_cand.score(self.scorer, o_file)
        assert base_result.hash is not None
        return base_result.score, base_result.hash, base_cand.get_source()

    def _need_to_send_source(self, result: CandidateResult) -> bool:
        return self._need_all_sources or self.should_output(result)

    def _eval_candidate(self, seed: int) -> CandidateResult:
        t0 = time.time()

        # Determine if we should keep the last candidate.
        # Don't keep 0-score candidates; we'll only create new, worse, zeroes.
        keep = (
            self._permutations.is_random()
            and random.uniform(0, 1) < self.keep_prob
            and self._last_score != 0
            and self._last_score != self.scorer.PENALTY_INF
        ) or self._force_rng_seed

        self._last_score = None

        # Create a new candidate if we didn't keep the last one (or if the last one didn't exist)
        # N.B. if we decide to keep the previous candidate, we will skip over the provided seed.
        # This means we're not guaranteed to test all seeds, but it doesn't really matter since
        # we're randomizing anyway.
        if not self._cur_cand or not keep:
            eval_state = EvalState()
            cand_c = self._permutations.evaluate(seed, eval_state)
            rng_seed = self._force_rng_seed or random.randrange(1, 10 ** 20)
            self._cur_seed = (seed, rng_seed)
            self._cur_cand = Candidate.from_source(
                cand_c, eval_state, self.fn_name, rng_seed=rng_seed
            )

        # Randomize the candidate
        if self._permutations.is_random():
            self._cur_cand.randomize_ast()

        t1 = time.time()

        self._cur_cand.get_source()

        t2 = time.time()

        o_file = self._cur_cand.compile(self.compiler)
        if not o_file and self._show_errors:
            raise _CompileFailure()

        t3 = time.time()

        result = self._cur_cand.score(self.scorer, o_file)

        t4 = time.time()

        if self.need_profiler:
            profiler = Profiler()
            profiler.add_stat(Profiler.StatType.perm, t1 - t0)
            profiler.add_stat(Profiler.StatType.stringify, t2 - t1)
            profiler.add_stat(Profiler.StatType.compile, t3 - t2)
            profiler.add_stat(Profiler.StatType.score, t4 - t3)
            result.profiler = profiler

        self._last_score = result.score

        if not self._need_to_send_source(result):
            result.source = None
            result.hash = None

        return result

    def should_output(self, result: CandidateResult) -> bool:
        """Check whether a result should be outputted. This must be more liberal
        in child processes than in parent ones, or else sources will be missing."""
        return (
            result.score <= self.base_score
            and result.hash is not None
            and result.source is not None
            and not (result.score > self.best_score and self._best_only)
            and (
                result.score < self.base_score
                or (result.score == self.base_score and not self._better_only)
            )
            and result.hash not in self.hashes
        )

    def record_result(self, result: CandidateResult) -> None:
        """Record a new result, updating the best score and adding the hash to
        the set of hashes we have already seen. No hash is recorded for score
        0, since we are interested in all score 0's, not just the first."""
        self.best_score = min(self.best_score, result.score)
        if result.score != 0 and result.hash is not None:
            self.hashes.add(result.hash)

    def seed_iterator(self) -> Iterator[int]:
        """Create an iterator over all seeds for this permuter. The iterator
        will be infinite if we are randomizing."""
        if self._force_seed is None:
            return iter(perm_gen_all_seeds(self._permutations))
        if self._permutations.is_random():
            return itertools.repeat(self._force_seed)
        return iter([self._force_seed])

    def try_eval_candidate(self, seed: int) -> EvalResult:
        """Evaluate a seed for the permuter."""
        try:
            return self._eval_candidate(seed)
        except _CompileFailure:
            return EvalError(exc_str=None, seed=self._cur_seed)
        except Exception:
            return EvalError(exc_str=traceback.format_exc(), seed=self._cur_seed)

    def diff(self, other_source: str) -> str:
        """Compute a unified white-space-ignoring diff from the (pretty-printed)
        base source against another source generated from this permuter."""

        class Line(str):
            def __eq__(self, other: Any) -> bool:
                return isinstance(other, str) and self.strip() == other.strip()

            def __hash__(self) -> int:
                return hash(self.strip())

        a = list(map(Line, self.base_source.split("\n")))
        b = list(map(Line, other_source.split("\n")))
        return "\n".join(
            difflib.unified_diff(a, b, fromfile="before", tofile="after", lineterm="")
        )


def _find_fns(source: str) -> List[str]:
    fns = re.findall(r"(\w+)\([^()\n]*\)\s*?{", source)
    return [
        fn
        for fn in fns
        if not fn.startswith("PERM") and fn not in ["if", "for", "switch", "while"]
    ]
