from base64 import b64decode
from collections import defaultdict
import copy
from dataclasses import dataclass
from random import Random
import re
from typing import Any, Callable, Dict, List, Optional, Set, Tuple, TYPE_CHECKING, Union

from pycparser import CParser, c_ast as ca, c_generator
from pycparser.plyparser import ParseError

from .error import CandidateConstructionFailure
from .ast_types import SimpleType, set_decl_name


@dataclass
class Indices:
    starts: Dict[ca.Node, int]
    ends: Dict[ca.Node, int]


Block = Union[ca.Compound, ca.Case, ca.Default]
if TYPE_CHECKING:
    # ca.Expression and ca.Statement don't actually exist, they live only in
    # the stubs file.
    Expression = ca.Expression
    Statement = ca.Statement
else:
    Expression = Statement = None


def to_c_raw(node: ca.Node) -> str:
    source: str = c_generator.CGenerator().visit(node)
    return source


def to_c(node: ca.Node, *, from_import: bool = False) -> str:
    source = to_c_raw(node) if from_import else PatchedCGenerator().visit(node)
    if "#pragma" not in source:
        return source
    lines = source.split("\n")
    out: List[str] = []
    same_line = 0
    ignore = 0
    for line in lines:
        stripped = line.strip()
        if stripped.startswith("#pragma _permuter "):
            # Expand permuter pragmas to nothing, by default. Still, keep one
            # output line per input line to preserve line numbers for import.py
            # error messages.
            line = ""

            stripped = stripped[len("#pragma _permuter ") :]
            if stripped == "sameline start":
                same_line += 1
            elif stripped == "sameline end":
                same_line -= 1
            elif stripped == "latedefine start":
                ignore += 1
            elif stripped == "latedefine end":
                assert ignore > 0, "mismatched ignore pragmas"
                ignore -= 1
            elif stripped.startswith("define "):
                assert ignore > 0, "define pragma must be within latedefine block"
                line = "#" + stripped
            elif stripped.startswith("b64literal "):
                line = b64decode(stripped.split(" ", 1)[1]).decode("utf-8")
        elif ignore > 0:
            # Ignore non-pragma lines within latedefine section
            line = ""

        if not same_line:
            line += "\n"
        elif line and out and not out[-1].endswith("\n"):
            line = " " + line.lstrip()
        out.append(line)
    assert same_line == 0
    assert ignore == 0, "unbalanced ignore pragmas"
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


def parse_c(source: str, *, from_import: bool = False) -> ca.FileAST:
    try:
        parser = CParser()
        return parser.parse(source, "<source>")
    except ParseError as e:
        msg = str(e)
        position, msg = msg.split(": ", 1)
        parts = position.split(":")
        if len(parts) >= 2:
            lineno = int(parts[1])
            posstr = f" at approximately line {lineno}"
            if len(parts) >= 3:
                posstr += f", column {parts[2]}"
            if not from_import:
                posstr += " (after PERM expansion)"
            try:
                line = source.split("\n")[lineno - 1].rstrip()
                posstr += "\n\n" + line
            except IndexError:
                posstr += "(out of bounds?)"
        else:
            posstr = ""
        raise CandidateConstructionFailure(
            f"Syntax error in base.c.\n{msg}{posstr}"
        ) from None


def compute_node_indices(top_node: ca.Node) -> Indices:
    starts: Dict[ca.Node, int] = {}
    ends: Dict[ca.Node, int] = {}
    cur_index = 1

    class Visitor(ca.NodeVisitor):
        def generic_visit(self, node: ca.Node) -> None:
            nonlocal cur_index
            assert node not in starts, "nodes should only appear once in AST"
            starts[node] = cur_index
            cur_index += 2
            super().generic_visit(node)
            ends[node] = cur_index
            cur_index += 2

    Visitor().visit(top_node)
    return Indices(starts, ends)


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


def insert_decl(
    fn: ca.FuncDef, var: str, type: SimpleType, random: Optional[Random] = None
) -> None:
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

    if random:
        index = random.randint(0, index)
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


def prune_ast(fn: ca.FuncDef, ast: ca.FileAST) -> int:
    """Prune away unnecessary parts of the AST, to reduce overhead from serialization
    and from the compiler's C parser."""

    # Create a GC graph that maps names of declarations and enumerators to indices
    # in ast.ext, as well an initial list of GC roots, consisting of everything
    # that isn't a Decl and or Typedef.
    edges: Dict[str, List[int]] = defaultdict(list)
    gc_roots: List[int] = []
    can_fwd_declare_typedef: Set[str] = set()
    can_fwd_declare_tagged: Set[str] = set()

    def add_type_edges(
        tp: Union["ca.Type", ca.Struct, ca.Union, ca.Enum], i: int
    ) -> None:
        while isinstance(tp, (ca.PtrDecl, ca.ArrayDecl)):
            tp = tp.type
        if isinstance(tp, ca.FuncDecl):
            return
        inner_type = tp.type if isinstance(tp, ca.TypeDecl) else tp
        if isinstance(inner_type, ca.IdentifierType):
            return
        if inner_type.name:
            edges[inner_type.name].append(i)
        if isinstance(inner_type, ca.Enum) and inner_type.values:
            for value in inner_type.values.enumerators:
                edges[value.name].append(i)
        if isinstance(inner_type, (ca.Struct, ca.Union)) and inner_type.decls:
            for decl in inner_type.decls:
                if isinstance(decl, ca.Decl):
                    add_type_edges(decl.type, i)

    for i in range(len(ast.ext)):
        item = ast.ext[i]
        if isinstance(item, ca.Decl) and not item.init:
            # (Exclude declarations with initializers, since taking function
            # pointers can affect regalloc on IDO.)
            if item.name:
                edges[item.name].append(i)
            if isinstance(item.type, (ca.Struct, ca.Union, ca.Enum)) and item.type.name:
                can_fwd_declare_tagged.add(item.type.name)
            add_type_edges(item.type, i)
        elif isinstance(item, ca.Typedef):
            edges[item.name].append(i)
            if isinstance(item.type, ca.TypeDecl) and isinstance(
                item.type.type, (ca.Struct, ca.Union, ca.Enum)
            ):
                can_fwd_declare_typedef.add(item.name)
            add_type_edges(item.type, i)
        elif isinstance(item, ca.Pragma) and "GLOBAL_ASM" in item.string:
            pass
        else:
            gc_roots.append(i)

    mentioned_ids: Set[str] = set()

    class IdVisitor(ca.NodeVisitor):
        def visit_Pragma(self, node: ca.Pragma) -> None:
            for token in re.findall(r"[a-zA-Z0-9_$]+", node.string):
                mentioned_ids.add(token)

        def visit_ID(self, node: ca.ID) -> None:
            mentioned_ids.add(node.name)

    IdVisitor().visit(ast)

    # Do the GC as a DFS traversal of the graph. Visiting a node searches its
    # AST for all kinds of mentioned IDs, and adds more nodes to the stack
    # using the edges we found before.
    gc_todo: List[int] = gc_roots
    need_fwd_decl_typedef: List[str] = []
    need_fwd_decl_tagged: List[str] = []

    def add_name(name: str) -> None:
        if name in edges:
            gc_todo.extend(edges[name])
            del edges[name]

    class Visitor(ca.NodeVisitor):
        def visit_Pragma(self, node: ca.Pragma) -> None:
            for token in re.findall(r"[a-zA-Z0-9_$]+", node.string):
                add_name(token)

        def visit_ID(self, node: ca.ID) -> None:
            add_name(node.name)

        def visit_IdentifierType(self, node: ca.IdentifierType) -> None:
            for name in node.names:
                add_name(name)

        def visit_Enum(self, node: ca.Enum) -> None:
            if node.name and not node.values:
                add_name(node.name)
            self.generic_visit(node)

        def visit_Struct(self, node: ca.Struct) -> None:
            if node.name and not node.decls:
                add_name(node.name)
            self.generic_visit(node)

        def visit_Union(self, node: ca.Union) -> None:
            if node.name and not node.decls:
                add_name(node.name)
            self.generic_visit(node)

        def visit_PtrDecl(self, node: ca.PtrDecl) -> None:
            # For pointer declarations which haven't been accessed, forward
            # declarations suffice.
            if (
                isinstance(node.type, ca.TypeDecl)
                and node.type.declname
                and node.type.declname not in mentioned_ids
            ):
                tp = node.type.type
                if isinstance(tp, ca.IdentifierType):
                    if all(name in can_fwd_declare_typedef for name in tp.names):
                        need_fwd_decl_typedef.extend(tp.names)
                        return
                elif tp.name and tp.name in can_fwd_declare_tagged:
                    if not (tp.values if isinstance(tp, ca.Enum) else tp.decls):
                        need_fwd_decl_tagged.append(tp.name)
                        return
            self.generic_visit(node)

        def visit_TypeDecl(self, node: ca.TypeDecl) -> None:
            if node.declname:
                add_name(node.declname)
            self.generic_visit(node)

    keep_exts: Set[int] = set()
    while gc_todo:
        i = gc_todo.pop()
        if i not in keep_exts:
            keep_exts.add(i)
            Visitor().visit(ast.ext[i])

    temp_id = 0

    def fwd_declare(tp: Union[ca.Struct, ca.Union, ca.Enum]) -> None:
        nonlocal temp_id
        if not tp.name:
            temp_id += 1
            tp.name = f"_PermuterTemp{temp_id}"
        if isinstance(tp, (ca.Struct, ca.Union)):
            tp.decls = None
        elif isinstance(tp, ca.Enum):
            tp.values = None
        else:
            assert False

    new_ext = []

    for i, item in enumerate(ast.ext):
        if i in keep_exts:
            pass
        elif isinstance(item, ca.Typedef) and item.name in need_fwd_decl_typedef:
            assert item.name in can_fwd_declare_typedef
            assert isinstance(item.type, ca.TypeDecl)
            assert isinstance(item.type.type, (ca.Struct, ca.Union, ca.Enum))
            fwd_declare(item.type.type)
        elif (
            isinstance(item, ca.Decl)
            and isinstance(item.type, (ca.Struct, ca.Union, ca.Enum))
            and item.type.name
            and item.type.name in need_fwd_decl_tagged
        ):
            assert item.type.name in can_fwd_declare_tagged
            fwd_declare(item.type)
        else:
            continue
        new_ext.append(item)

    ast.ext = new_ext
    return ast.ext.index(fn)
