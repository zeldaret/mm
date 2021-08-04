from typing import Dict, Union, List, Tuple, Callable, Optional, Any, Set
import attr
import bisect
import copy
from random import Random
import sys
import time
import typing

from pycparser import c_ast as ca, c_parser, c_generator

from .error import CandidateConstructionFailure
from .ast_types import (
    SimpleType,
    TypeMap,
    build_typemap,
    decayed_expr_type,
    resolve_typedefs,
    set_decl_name,
)

Indices = Dict[ca.Node, int]
Block = Union[ca.Compound, ca.Case, ca.Default]
if typing.TYPE_CHECKING:
    # ca.Expression and ca.Statement don't actually exist, they live only in
    # the stubs file.
    Expression = ca.Expression
    Statement = ca.Statement
else:
    Expression = Statement = None


def to_c(node: ca.Node) -> str:
    source = PatchedCGenerator().visit(node)
    if "#pragma" not in source:
        return source
    lines = source.split("\n")
    out = []
    same_line = 0
    in_late_defines = False
    for line in lines:
        stripped = line.strip()
        if stripped.startswith("#pragma"):
            if stripped == "#pragma _permuter sameline start":
                same_line += 1
            elif stripped == "#pragma _permuter sameline end":
                same_line -= 1
                if same_line == 0:
                    out.append("\n")
            elif stripped == "#pragma _permuter latedefine start":
                assert not in_late_defines
                in_late_defines = True
            elif stripped == "#pragma _permuter latedefine end":
                assert in_late_defines
                in_late_defines = False
            elif stripped.startswith("#pragma _permuter define "):
                assert in_late_defines
                out.append("#" + stripped.split(" ", 2)[2] + "\n")

            # Ignore permuter pragmas, but leave actual pragmas in (like intrinsics)
            if stripped.startswith("#pragma _permuter"):
                continue
        if in_late_defines:
            continue
        if not same_line:
            line += "\n"
        elif out and not out[-1].endswith("\n"):
            line = " " + line.lstrip()
        out.append(line)
    assert same_line == 0
    return "".join(out).rstrip() + "\n"


class PatchedCGenerator(c_generator.CGenerator):
    """Like a CGenerator, except it keeps else if's prettier despite
    the terrible things we've done to them in normalize_ast."""

    def visit_If(self, n: ca.If) -> str:
        n2 = n
        if (
            n.iffalse
            and isinstance(n.iffalse, ca.Compound)
            and n.iffalse.block_items
            and len(n.iffalse.block_items) == 1
            and isinstance(n.iffalse.block_items[0], ca.If)
        ):
            n2 = ca.If(cond=n.cond, iftrue=n.iftrue, iffalse=n.iffalse.block_items[0])
        return super().visit_If(n2)  # type: ignore


def extract_fn(ast: ca.FileAST, fn_name: str) -> Tuple[ca.FuncDef, int]:
    ret = []
    for i, node in enumerate(ast.ext):
        if isinstance(node, ca.FuncDef):
            if node.decl.name == fn_name:
                ret.append((node, i))
            else:
                node = node.decl
                ast.ext[i] = node
        if isinstance(node, ca.Decl) and isinstance(node.type, ca.FuncDecl):
            node.funcspec = [spec for spec in node.funcspec if spec != "static"]
    if len(ret) == 0:
        raise CandidateConstructionFailure(f"Function {fn_name} not found in base.c.")
    if len(ret) > 1:
        raise CandidateConstructionFailure(
            f"Found multiple copies of function {fn_name} in base.c."
        )
    return ret[0]


def compute_node_indices(top_node: ca.Node) -> Indices:
    indices: Indices = {}
    cur_index = 0

    class Visitor(ca.NodeVisitor):
        def generic_visit(self, node: ca.Node) -> None:
            nonlocal cur_index
            assert node not in indices, "nodes should only appear once in AST"
            indices[node] = cur_index
            cur_index += 1
            super().generic_visit(node)

    Visitor().visit(top_node)
    return indices


def equal_ast(a: ca.Node, b: ca.Node) -> bool:
    def equal(a: Any, b: Any) -> bool:
        if type(a) != type(b):
            return False
        if a is None:
            return b is None
        if isinstance(a, list):
            assert isinstance(b, list)
            if len(a) != len(b):
                return False
            for i in range(len(a)):
                if not equal(a[i], b[i]):
                    return False
            return True
        if isinstance(a, (int, str)):
            return bool(a == b)
        assert isinstance(a, ca.Node)
        for name in a.__slots__[:-2]:  # type: ignore
            if not equal(getattr(a, name), getattr(b, name)):
                return False
        return True

    return equal(a, b)


def is_lvalue(expr: Expression) -> bool:
    if isinstance(expr, (ca.ID, ca.StructRef, ca.ArrayRef)):
        return True
    if isinstance(expr, ca.UnaryOp):
        return expr.op == "*"
    return False


def is_effectful(expr: Expression) -> bool:
    found = False

    class Visitor(ca.NodeVisitor):
        def visit_UnaryOp(self, node: ca.UnaryOp) -> None:
            nonlocal found
            if node.op in ["p++", "p--", "++", "--"]:
                found = True
            else:
                self.generic_visit(node.expr)

        def visit_FuncCall(self, _: ca.Node) -> None:
            nonlocal found
            found = True

        def visit_Assignment(self, _: ca.Node) -> None:
            nonlocal found
            found = True

    Visitor().visit(expr)
    return found


def get_block_stmts(block: Block, force: bool) -> List[Statement]:
    if isinstance(block, ca.Compound):
        ret = block.block_items or []
        if force and not block.block_items:
            block.block_items = ret
    else:
        ret = block.stmts or []
        if force and not block.stmts:
            block.stmts = ret
    return ret


def insert_decl(fn: ca.FuncDef, var: str, type: SimpleType) -> None:
    type = copy.deepcopy(type)
    decl = ca.Decl(
        name=var, quals=[], storage=[], funcspec=[], type=type, init=None, bitsize=None
    )
    set_decl_name(decl)
    assert fn.body.block_items, "Non-empty function"
    for index, stmt in enumerate(fn.body.block_items):
        if not isinstance(stmt, ca.Decl):
            break
    else:
        index = len(fn.body.block_items)
    fn.body.block_items[index:index] = [decl]


def insert_statement(block: Block, index: int, stmt: Statement) -> None:
    stmts = get_block_stmts(block, True)
    stmts[index:index] = [stmt]


def brace_nested_blocks(stmt: Statement) -> None:
    def brace(stmt: Statement) -> Block:
        if isinstance(stmt, (ca.Compound, ca.Case, ca.Default)):
            return stmt
        return ca.Compound([stmt])

    if isinstance(stmt, (ca.For, ca.While, ca.DoWhile)):
        stmt.stmt = brace(stmt.stmt)
    elif isinstance(stmt, ca.If):
        stmt.iftrue = brace(stmt.iftrue)
        if stmt.iffalse:
            stmt.iffalse = brace(stmt.iffalse)
    elif isinstance(stmt, ca.Switch):
        stmt.stmt = brace(stmt.stmt)
    elif isinstance(stmt, ca.Label):
        brace_nested_blocks(stmt.stmt)


def has_nested_block(node: ca.Node) -> bool:
    return isinstance(
        node,
        (
            ca.Compound,
            ca.For,
            ca.While,
            ca.DoWhile,
            ca.If,
            ca.Switch,
            ca.Case,
            ca.Default,
        ),
    )


def for_nested_blocks(stmt: Statement, callback: Callable[[Block], None]) -> None:
    def invoke(stmt: Statement) -> None:
        assert isinstance(
            stmt, (ca.Compound, ca.Case, ca.Default)
        ), "brace_nested_blocks should have turned nested statements into blocks"
        callback(stmt)

    if isinstance(stmt, ca.Compound):
        invoke(stmt)
    elif isinstance(stmt, (ca.For, ca.While, ca.DoWhile)):
        invoke(stmt.stmt)
    elif isinstance(stmt, ca.If):
        if stmt.iftrue:
            invoke(stmt.iftrue)
        if stmt.iffalse:
            invoke(stmt.iffalse)
    elif isinstance(stmt, ca.Switch):
        invoke(stmt.stmt)
    elif isinstance(stmt, (ca.Case, ca.Default)):
        invoke(stmt)
    elif isinstance(stmt, ca.Label):
        for_nested_blocks(stmt.stmt, callback)


def normalize_ast(fn: ca.FuncDef, ast: ca.FileAST) -> None:
    """Add braces to all ifs/fors/etc., to make it easier to insert statements."""

    def rec(block: Block) -> None:
        stmts = get_block_stmts(block, False)
        for stmt in stmts:
            brace_nested_blocks(stmt)
            for_nested_blocks(stmt, rec)

    rec(fn.body)
