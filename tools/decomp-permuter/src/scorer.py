from dataclasses import dataclass, field
import difflib
import hashlib
import re
from typing import Tuple, List, Optional
from collections import Counter


from .objdump import objdump, sp_offset


@dataclass(init=False, unsafe_hash=True)
class DiffAsmLine:
    line: str = field(compare=False)
    mnemonic: str

    def __init__(self, line: str) -> None:
        self.line = line
        self.mnemonic = line.split("\t")[0]


class Scorer:
    PENALTY_INF = 10 ** 9

    PENALTY_STACKDIFF = 1
    PENALTY_REGALLOC = 5
    PENALTY_REORDERING = 60
    PENALTY_INSERTION = 100
    PENALTY_DELETION = 100

    def __init__(self, target_o: str, *, stack_differences: bool):
        self.target_o = target_o
        self.stack_differences = stack_differences
        _, self.target_seq = self._objdump(target_o)
        self.differ: difflib.SequenceMatcher[DiffAsmLine] = difflib.SequenceMatcher(
            autojunk=False
        )
        self.differ.set_seq2(self.target_seq)

    def _objdump(self, o_file: str) -> Tuple[str, List[DiffAsmLine]]:
        ret = []
        lines = objdump(o_file, stack_differences=self.stack_differences)
        for line in lines:
            ret.append(DiffAsmLine(line))
        return "\n".join(lines), ret

    def score(self, cand_o: Optional[str]) -> Tuple[int, str]:
        if not cand_o:
            return Scorer.PENALTY_INF, ""

        objdump_output, cand_seq = self._objdump(cand_o)

        score = 0
        deletions = []
        insertions = []

        def lo_hi_match(old: str, new: str) -> bool:
            old_lo = old.find("%lo")
            old_hi = old.find("%hi")
            new_lo = new.find("%lo")
            new_hi = new.find("%hi")

            if old_lo != -1 and new_lo != -1:
                old_idx = old_lo
                new_idx = new_lo
            elif old_hi != -1 and new_hi != -1:
                old_idx = old_hi
                new_idx = new_hi
            else:
                return False

            if old[:old_idx] != new[:new_idx]:
                return False

            old_inner = old[old_idx + 4 : -1]
            new_inner = new[new_idx + 4 : -1]
            return old_inner.startswith(".") or new_inner.startswith(".")

        def diff_sameline(old: str, new: str) -> None:
            nonlocal score
            if old == new:
                return

            if lo_hi_match(old, new):
                return

            ignore_last_field = False
            if self.stack_differences:
                oldsp = re.search(sp_offset, old)
                newsp = re.search(sp_offset, new)
                if oldsp and newsp:
                    oldrel = int(oldsp.group(1) or "0", 0)
                    newrel = int(newsp.group(1) or "0", 0)
                    score += abs(oldrel - newrel) * self.PENALTY_STACKDIFF
                    ignore_last_field = True

            # Probably regalloc difference, or signed vs unsigned

            # Compare each field in order
            newfields, oldfields = new.split(","), old.split(",")
            if ignore_last_field:
                newfields = newfields[:-1]
                oldfields = oldfields[:-1]
            for nf, of in zip(newfields, oldfields):
                if nf != of:
                    score += self.PENALTY_REGALLOC
            # Penalize any extra fields
            score += abs(len(newfields) - len(oldfields)) * self.PENALTY_REGALLOC

        def diff_insert(line: str) -> None:
            # Reordering or totally different codegen.
            # Defer this until later when we can tell.
            insertions.append(line)

        def diff_delete(line: str) -> None:
            deletions.append(line)

        self.differ.set_seq1(cand_seq)
        for (tag, i1, i2, j1, j2) in self.differ.get_opcodes():
            if tag == "equal":
                for k in range(i2 - i1):
                    old = self.target_seq[j1 + k].line
                    new = cand_seq[i1 + k].line
                    diff_sameline(old, new)
            if tag == "replace" or tag == "delete":
                for k in range(i1, i2):
                    diff_insert(cand_seq[k].line)
            if tag == "replace" or tag == "insert":
                for k in range(j1, j2):
                    diff_delete(self.target_seq[k].line)

        insertions_co = Counter(insertions)
        deletions_co = Counter(deletions)
        for item in insertions_co + deletions_co:
            ins = insertions_co[item]
            dels = deletions_co[item]
            common = min(ins, dels)
            score += (
                (ins - common) * self.PENALTY_INSERTION
                + (dels - common) * self.PENALTY_DELETION
                + self.PENALTY_REORDERING * common
            )

        return (score, hashlib.sha256(objdump_output.encode()).hexdigest())
