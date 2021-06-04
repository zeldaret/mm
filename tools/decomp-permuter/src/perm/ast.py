from typing import List, Optional, Tuple

from .. import ast_util
from .perm import EvalState, Perm
from ..ast_util import Block, Statement
from ..error import CandidateConstructionFailure

from pycparser import c_ast as ca


class _Done(Exception):
    pass


def _apply_perm(fn: ca.FuncDef, perm_id: int, perm: Perm, seed: int) -> None:
    """Find and apply a single late perm macro in the AST."""
    # Currently we search for statement macros only.
    wanted_pragma = f"_permuter ast_perm {perm_id}"
    Loc = Tuple[List[Statement], int]

    def try_handle_block(block: ca.Node, where: Optional[Loc]) -> None:
        if not isinstance(block, ca.Compound) or not block.block_items:
            return
        pragma = block.block_items[0]
        if not isinstance(pragma, ca.Pragma) or pragma.string != wanted_pragma:
            return

        args: List[Statement] = block.block_items[1:]
        stmts = perm.eval_statement_ast(args, seed)

        if where:
            where[0][where[1] : where[1] + 1] = stmts
        else:
            block.block_items = stmts
        raise _Done

    def rec(block: Block) -> None:
        # if (x) { _Pragma(...); inputs } -> if (x) { outputs }
        try_handle_block(block, None)
        stmts = ast_util.get_block_stmts(block, False)
        for i, stmt in enumerate(stmts):
            # { ... { _Pragma(...); inputs } ... } -> { ... outputs ... }
            try_handle_block(stmt, (stmts, i))
            ast_util.for_nested_blocks(stmt, rec)

    try:
        rec(fn.body)
        raise CandidateConstructionFailure("Failed to find PERM macro in AST.")
    except _Done:
        pass


def apply_ast_perms(fn: ca.FuncDef, eval_state: EvalState) -> None:
    """Find all late perm macros in the AST and apply them."""
    # Nested perms will have smaller IDs, so apply the perms from lowest ID to
    # highest to ensure that all arguments to perms have already been evaluated.
    for perm_id, (perm, seed) in enumerate(eval_state.ast_perms):
        _apply_perm(fn, perm_id, perm, seed)
