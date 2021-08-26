import bisect
import copy
from dataclasses import dataclass, field
from random import Random
import typing
from typing import (
    Any,
    Callable,
    Dict,
    List,
    Optional,
    Sequence,
    Set,
    Tuple,
    TypeVar,
    Union,
)

from pycparser import c_ast as ca

from . import ast_util
from .ast_util import Block, Indices, Statement, Expression
from .ast_types import (
    SimpleType,
    Type,
    TypeMap,
    allowed_basic_type,
    build_typemap,
    decayed_expr_type,
    get_decl_type,
    resolve_typedefs,
    same_type,
    set_decl_name,
    pointer_decay,
)

# Set to true to perform expression type detection eagerly. This can help when
# debugging crashes in the ast_types code.
DEBUG_EAGER_TYPES = False

# Randomize the type of introduced temporary variable with this probability
PROB_RANDOMIZE_TYPE = 0.3

# Reuse an existing var instead of introducing a new temporary one with this probability
PROB_REUSE_VAR = 0.5

# When wrapping statements in a new block, use a same-line `do { ... } while(0);`
# (as opposed to non-same-line `if (1) { ... }`) with this probability.
# This matches what macros often do.
PROB_INS_BLOCK_DOWHILE = 0.5

# Make a pointer to a temporary expression, rather than copy it by value, with
# this probability. (This always happens for expressions of struct type,
# regardless of this probability.)
PROB_TEMP_PTR = 0.05

# Instead of emitting an assignment statement, assign the temporary within the
# first expression it's used in with this probability.
PROB_TEMP_ASSIGN_AT_FIRST_USE = 0.1

# When creating a temporary for an expression, use the temporary for all equal
# expressions with this probability.
PROB_TEMP_REPLACE_ALL = 0.2

# When creating a temporary for an expression, use the temporary for an interval
# with maximal endpoint with this probability.
PROB_TEMP_REPLACE_MOST = 0.2

# When substituting a variable by its value, substitute all instances with this
# probability, rather than just a subrange or the complement of one.
PROB_EXPAND_REPLACE_ALL = 0.3

# When substituting a variable by its value, keep the variable assignment with
# this probability.
PROB_KEEP_REPLACED_VAR = 0.2

# Change the return type of an external function to void with this probability.
PROB_RET_VOID = 0.2

# Number larger than any node index. (If you're trying to compile a 1 GB large
# C file to matching asm, you have bigger problems than this limit.)
MAX_INDEX = 10 ** 9

T = TypeVar("T")


class RandomizationFailure(Exception):
    pass


def ensure(condition: Any) -> None:
    """Abort the randomization pass if 'condition' fails to hold, and try
    another pass instead. Don't call this after making any modifications to
    the AST."""
    if not condition:
        raise RandomizationFailure


@dataclass
class Region:
    start: int
    end: int
    indices: Optional[Indices] = field(compare=False)

    @staticmethod
    def unbounded() -> "Region":
        return Region(-1, MAX_INDEX, None)

    def is_unbounded(self) -> bool:
        return self.indices is None

    def contains_node(self, node: ca.Node) -> bool:
        """Check whether the region contains an entire node."""
        if self.indices is None:
            return True
        return (
            self.start < self.indices.starts[node]
            and self.indices.ends[node] < self.end
        )

    def contains_pre(self, node: ca.Node) -> bool:
        """Check whether the region contains a point just before a given node."""
        if self.indices is None:
            return True
        return self.start < self.indices.starts[node] < self.end

    def contains_pre_index(self, index: int) -> bool:
        """Check whether the region contains a point just before a given node,
        as specified by its index."""
        if self.indices is None:
            return True
        return self.start < index < self.end


def reverse_start_indices(indices: Indices) -> Dict[int, ca.Node]:
    ret = {}
    for k, v in indices.starts.items():
        ret[v] = k
    return ret


def get_randomization_region(
    top_node: ca.Node, indices: Indices, random: Random
) -> Region:
    ret: List[Region] = []
    cur_start: Optional[int] = None

    class Visitor(ca.NodeVisitor):
        def visit_Pragma(self, node: ca.Pragma) -> None:
            nonlocal cur_start
            if node.string == "_permuter randomizer start":
                if cur_start is not None:
                    raise Exception("nested PERM_RANDOMIZE not supported")
                cur_start = indices.ends[node]
            if node.string == "_permuter randomizer end":
                assert cur_start is not None, "randomizer end without start"
                ret.append(Region(cur_start + 1, indices.starts[node] - 1, indices))
                cur_start = None

    Visitor().visit(top_node)
    assert cur_start is None, "randomizer start without end"
    if not ret:
        return Region.unbounded()
    return random.choice(ret)


def get_block_expressions(block: Block, region: Region) -> List[Expression]:
    """Return a list of all expressions within a block that are also within a
    given region."""
    exprs: List[Expression] = []

    def visitor(expr: Expression) -> None:
        if region.contains_node(expr):
            exprs.append(expr)

    replace_subexprs(block, visitor)
    return exprs


def compute_write_locations(
    top_node: ca.Node, indices: Indices
) -> Dict[str, List[int]]:
    writes: Dict[str, List[int]] = {}

    def add_write(var_name: str, loc: int) -> None:
        if var_name not in writes:
            writes[var_name] = []
        else:
            assert (
                loc > writes[var_name][-1]
            ), "consistent traversal order should guarantee monotonicity here"
        writes[var_name].append(loc)

    class Visitor(ca.NodeVisitor):
        def visit_Decl(self, node: ca.Decl) -> None:
            if node.name:
                add_write(node.name, indices.starts[node])
            self.generic_visit(node)

        def visit_UnaryOp(self, node: ca.UnaryOp) -> None:
            if node.op in ["p++", "p--", "++", "--"] and isinstance(node.expr, ca.ID):
                add_write(node.expr.name, indices.starts[node])
            self.generic_visit(node)

        def visit_Assignment(self, node: ca.Assignment) -> None:
            if isinstance(node.lvalue, ca.ID):
                add_write(node.lvalue.name, indices.starts[node])
            self.generic_visit(node)

    Visitor().visit(top_node)
    return writes


def compute_read_locations(top_node: ca.Node, indices: Indices) -> Dict[str, List[int]]:
    reads: Dict[str, List[int]] = {}
    for node in find_var_reads(top_node):
        var_name = node.name
        loc = indices.starts[node]
        if var_name not in reads:
            reads[var_name] = []
        else:
            assert (
                loc > reads[var_name][-1]
            ), "consistent traversal order should guarantee monotonicity here"
        reads[var_name].append(loc)
    return reads


def find_var_reads(top_node: ca.Node) -> List[ca.ID]:
    ret = []

    class Visitor(ca.NodeVisitor):
        def visit_Decl(self, node: ca.Decl) -> None:
            if node.init:
                self.visit(node.init)

        def visit_ID(self, node: ca.ID) -> None:
            ret.append(node)

        def visit_UnaryOp(self, node: ca.UnaryOp) -> None:
            if node.op == "&" and isinstance(node.expr, ca.ID):
                return
            self.generic_visit(node)

        def visit_StructRef(self, node: ca.StructRef) -> None:
            self.visit(node.name)

        def visit_Assignment(self, node: ca.Assignment) -> None:
            if isinstance(node.lvalue, ca.ID):
                return
            self.generic_visit(node)

    Visitor().visit(top_node)
    return ret


def visit_replace(top_node: ca.Node, callback: Callable[[ca.Node, bool], Any]) -> None:
    def empty_statement_to_none(node: Any) -> Any:
        if isinstance(node, ca.EmptyStatement):
            return None
        return node

    def rec(orig_node: ca.Node, toplevel: bool = False, *, lvalue: bool = False) -> Any:
        node: "ca.AnyNode" = typing.cast("ca.AnyNode", orig_node)
        repl = callback(node, not toplevel and not lvalue)
        if repl:
            return repl
        if isinstance(node, ca.Assignment):
            node.lvalue = rec(node.lvalue, lvalue=True)
            node.rvalue = rec(node.rvalue)
        elif isinstance(node, ca.StructRef):
            node.name = rec(node.name, lvalue=(lvalue and node.type == "."))
        elif isinstance(node, ca.Cast):
            if node.expr:
                node.expr = rec(node.expr)
        elif isinstance(node, (ca.Constant, ca.ID)):
            pass
        elif isinstance(node, ca.UnaryOp):
            if node.op in ["p++", "p--", "++", "--", "&"]:
                node.expr = rec(node.expr, lvalue=True)
            elif node.op != "sizeof":
                node.expr = rec(node.expr)
        elif isinstance(node, ca.BinaryOp):
            node.left = rec(node.left)
            node.right = rec(node.right)
        elif isinstance(node, ca.FuncCall):
            # not worth replacing .name
            if node.args:
                rec(node.args, True)
        elif isinstance(node, ca.ExprList):
            for i in range(len(node.exprs)):
                if not isinstance(node.exprs[i], ca.Typename):
                    node.exprs[i] = rec(node.exprs[i])
        elif isinstance(node, ca.ArrayRef):
            node.name = rec(node.name, lvalue=lvalue)
            node.subscript = rec(node.subscript)
        elif isinstance(node, ca.TernaryOp):
            node.cond = rec(node.cond)
            node.iftrue = rec(node.iftrue, True)
            node.iffalse = rec(node.iffalse, True)
        elif isinstance(node, ca.Return):
            if node.expr:
                node.expr = rec(node.expr)
        elif isinstance(node, ca.Decl):
            if node.init:
                node.init = rec(node.init, isinstance(node.init, ca.InitList))
        elif isinstance(node, ca.For):
            if node.init:
                node.init = empty_statement_to_none(rec(node.init, True))
            if node.cond:
                node.cond = rec(node.cond)
            if node.next:
                node.next = empty_statement_to_none(rec(node.next, True))
            node.stmt = rec(node.stmt, True)
        elif isinstance(node, ca.Compound):
            if node.block_items:
                for i, sub in enumerate(node.block_items):
                    node.block_items[i] = rec(sub, True)
        elif isinstance(node, (ca.Case, ca.Default)):
            if node.stmts:
                for i, sub in enumerate(node.stmts):
                    node.stmts[i] = rec(sub, True)
        elif isinstance(node, ca.While):
            node.cond = rec(node.cond)
            node.stmt = rec(node.stmt, True)
        elif isinstance(node, ca.DoWhile):
            node.stmt = rec(node.stmt, True)
            node.cond = rec(node.cond)
        elif isinstance(node, ca.Switch):
            node.cond = rec(node.cond)
            node.stmt = rec(node.stmt, True)
        elif isinstance(node, ca.Label):
            node.stmt = rec(node.stmt, True)
        elif isinstance(node, ca.If):
            node.cond = rec(node.cond)
            node.iftrue = rec(node.iftrue, True)
            if node.iffalse:
                node.iffalse = rec(node.iffalse, True)
        elif isinstance(
            node,
            (
                ca.TypeDecl,
                ca.PtrDecl,
                ca.ArrayDecl,
                ca.Typename,
                ca.IdentifierType,
                ca.Struct,
                ca.Union,
                ca.Enum,
                ca.EmptyStatement,
                ca.Pragma,
                ca.Break,
                ca.Continue,
                ca.Goto,
                ca.CompoundLiteral,
                ca.Typedef,
                ca.FuncDecl,
                ca.FuncDef,
                ca.EllipsisParam,
                ca.Enumerator,
                ca.EnumeratorList,
                ca.FileAST,
                ca.InitList,
                ca.NamedInitializer,
                ca.ParamList,
            ),
        ):
            pass
        else:
            _: None = node
            assert False, f"Node with unknown type: {node}"
        return node

    rec(top_node, True)


def replace_subexprs(top_node: ca.Node, callback: Callable[[Expression], Any]) -> None:
    def expr_filter(node: ca.Node, is_expr: bool) -> Any:
        if not is_expr:
            return None
        return callback(typing.cast(Expression, node))

    visit_replace(top_node, expr_filter)


def replace_node(top_node: ca.Node, old: ca.Node, new: ca.Node) -> None:
    visit_replace(top_node, lambda node, _: new if node is old else None)


def random_bool(random: Random, prob: float) -> bool:
    return random.random() < prob


def random_weighted(random: Random, values: Sequence[Tuple[T, float]]) -> T:
    sumprob = 0.0
    for (val, prob) in values:
        assert prob >= 0, "Probabilities must be non-negative"
        sumprob += prob
    assert sumprob > 0, "Cannot pick randomly from empty set"
    targetprob = random.uniform(0, sumprob)
    sumprob = 0.0
    for (val, prob) in values:
        sumprob += prob
        if sumprob > targetprob:
            return val

    # Float imprecision
    for (val, prob) in values:
        if prob > 0:
            return val
    assert False, "unreachable"


def random_type(random: Random) -> SimpleType:
    new_names: List[str] = []
    if random_bool(random, 0.5):
        new_names.append("unsigned")
    new_names.extend(
        random_weighted(
            random,
            [
                (["char"], 1),
                (["short"], 1),
                (["int"], 2),
                (["long"], 0.5),
                (["long", "long"], 0.5),
            ],
        )
    )
    idtype = ca.IdentifierType(names=new_names)
    quals = []
    if random_bool(random, 0.5):
        quals = ["volatile"]
    return ca.TypeDecl(declname=None, quals=quals, type=idtype)


def randomize_type(
    type: SimpleType, typemap: TypeMap, random: Random, *, ensure_changed: bool = False
) -> SimpleType:
    if allowed_basic_type(
        type, typemap, ["int", "char", "long", "short", "signed", "unsigned"]
    ):
        return random_type(random)
    if ensure_changed:
        raise RandomizationFailure
    return type


def randomize_innermost_type(
    type: Type, typemap: TypeMap, random: Random, *, ensure_changed: bool = False
) -> Type:
    if isinstance(type, ca.TypeDecl):
        return randomize_type(type, typemap, random, ensure_changed=ensure_changed)
    new_type = copy.copy(type)
    new_type.type = randomize_innermost_type(
        type.type, typemap, random, ensure_changed=ensure_changed
    )
    return new_type


def get_insertion_points(
    fn: ca.FuncDef, region: Region, *, allow_within_decl: bool = False
) -> List[Tuple[Block, int, Optional[ca.Node]]]:
    cands: List[Tuple[Block, int, Optional[ca.Node]]] = []

    def rec(block: Block) -> None:
        stmts = ast_util.get_block_stmts(block, False)
        last_node: ca.Node = block
        for i, stmt in enumerate(stmts):
            if region.contains_pre(stmt):
                cands.append((block, i, stmt))
            ast_util.for_nested_blocks(stmt, rec)
            last_node = stmt
        if region.contains_node(last_node):
            cands.append((block, len(stmts), None))

    rec(fn.body)
    if not allow_within_decl:
        cands = [c for c in cands if not isinstance(c[2], ca.Decl)]
    return cands


def maybe_reuse_var(
    var: Optional[str],
    assign_before: ca.Node,
    orig_expr: Expression,
    type: SimpleType,
    reads: Dict[str, List[int]],
    writes: Dict[str, List[int]],
    indices: Indices,
    typemap: TypeMap,
    random: Random,
) -> Optional[str]:
    if not random_bool(random, PROB_REUSE_VAR) or var is None:
        return None
    var_type: SimpleType = decayed_expr_type(ca.ID(var), typemap)
    if not same_type(var_type, type, typemap, allow_similar=True):
        return None

    def find_next(list: List[int], value: int) -> Optional[int]:
        ind = bisect.bisect_left(list, value)
        if ind < len(list):
            return list[ind]
        return None

    assignment_ind = indices.starts[assign_before]
    expr_ind = indices.starts[orig_expr]
    write = find_next(writes.get(var, []), assignment_ind)
    read = find_next(reads.get(var, []), assignment_ind)
    # TODO: if write/read is within expr, search again from after it (since
    # we move expr, uses within it aren't relevant).
    if read is not None and (write is None or write >= read):
        # We don't want to overwrite a variable which we later read,
        # unless we write to it before that read
        return None
    if write is not None and write < expr_ind:
        # Our write will be overwritten before we manage to read from it.
        return None
    return var


def perm_temp_for_expr(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Create a temporary variable for a random expression. The variable will
    be assigned at another random point (nearer the expression being more
    likely), possibly reuse an existing variable, possibly be of a different
    size/signedness, and possibly be used for other identical expressions as
    well. Only expressions within the given region may be chosen for
    replacement, but the assignment and the affected identical expressions may
    be outside of it."""
    Place = Tuple[Block, int, Statement]
    einds: Dict[ca.Node, int] = {}
    writes: Dict[str, List[int]] = compute_write_locations(fn, indices)
    reads: Dict[str, List[int]] = compute_read_locations(fn, indices)
    typemap = build_typemap(ast)
    candidates: List[Tuple[Tuple[Place, Expression, Optional[str]], float]] = []

    # Step 0: decide whether to make a pointer to the chosen expression, or to
    # copy it by value.
    should_make_ptr = random_bool(random, PROB_TEMP_PTR)

    def surrounding_writes(expr: Expression, base: Expression) -> Tuple[int, int]:
        """Compute the previous and next write to a variable included in expr,
        starting from base. If none, default to -1 or MAX_INDEX respectively.
        If base itself writes to an included variable (e.g. if it is an
        increment expression), the \"next\" write will be defined as the node
        itself, while the \"previous\" will continue searching to the left."""
        sub_reads = find_var_reads(expr)
        prev_write = -1
        next_write = MAX_INDEX
        base_index = indices.starts[base]
        for sub_read in sub_reads:
            var_name = sub_read.name
            if var_name not in writes:
                continue
            # Find the first write that is strictly before indices[expr],
            # and the first write that is on or after.
            wr = writes[var_name]
            ind = bisect.bisect_left(wr, base_index)
            if ind > 0:
                prev_write = max(prev_write, wr[ind - 1])
            if ind < len(wr):
                next_write = min(next_write, wr[ind])
        return prev_write, next_write

    # Step 1: assign probabilities to each place/expression
    def rec(block: Block, reuse_cands: List[str]) -> None:
        stmts = ast_util.get_block_stmts(block, False)
        reuse_cands = reuse_cands[:]
        assignment_cands: List[Place] = []  # places to insert before
        past_decls = False
        for index, stmt in enumerate(stmts):
            if isinstance(stmt, ca.Decl):
                assert stmt.name, "Anonymous declarations cannot happen in functions"
                if not isinstance(stmt.type, ca.ArrayDecl):
                    reuse_cands.append(stmt.name)
                    if not isinstance(stmt.type, ca.PtrDecl):
                        # Make non-pointers more common
                        reuse_cands.append(stmt.name)
            elif not isinstance(stmt, ca.Pragma):
                past_decls = True
            if past_decls:
                assignment_cands.append((block, index, stmt))

            ast_util.for_nested_blocks(stmt, lambda b: rec(b, reuse_cands))

            def visitor(expr: Expression) -> None:
                if DEBUG_EAGER_TYPES:
                    decayed_expr_type(expr, typemap)

                if not region.contains_node(expr):
                    return

                orig_expr = expr
                if should_make_ptr:
                    if not ast_util.is_lvalue(expr):
                        return
                    expr = ca.UnaryOp("&", expr)

                eind = einds.get(expr, 0)
                prev_write, _ = surrounding_writes(expr, orig_expr)

                for place in assignment_cands[::-1]:
                    # If expr contains an ID which is written to within
                    # [place, expr), bail out; we're trying to move the
                    # assignment too high up.
                    # TODO: also fail on moving past function calls, or
                    # possibly-aliasing writes.
                    if indices.starts[place[2]] <= prev_write:
                        break

                    # Make far-away places less likely, and similarly for
                    # trivial expressions.
                    eind += 1
                    prob = 1 / eind
                    if isinstance(orig_expr, (ca.ID, ca.Constant)):
                        prob *= 0.15 if should_make_ptr else 0.5
                    reuse_cand = random.choice(reuse_cands) if reuse_cands else None
                    candidates.append(((place, expr, reuse_cand), prob))

                einds[expr] = eind

            replace_subexprs(stmt, visitor)

    rec(fn.body, [])

    # Step 2: decide on a place/expression
    ensure(candidates)
    place: Optional[Place]
    place, expr, reuse_cand = random_weighted(random, candidates)

    if random_bool(random, PROB_TEMP_ASSIGN_AT_FIRST_USE):
        # Don't emit a statement for the assignment, emit an assignment
        # expression at the first use instead.
        place = None

    type: SimpleType = decayed_expr_type(expr, typemap)

    # Always use pointers when replacing structs
    if (
        not should_make_ptr
        and isinstance(type, ca.TypeDecl)
        and isinstance(type.type, (ca.Struct, ca.Union))
        and ast_util.is_lvalue(expr)
    ):
        should_make_ptr = True
        expr = ca.UnaryOp("&", expr)
        type = decayed_expr_type(expr, typemap)

    if should_make_ptr:
        assert isinstance(expr, ca.UnaryOp)
        assert not isinstance(expr.expr, ca.Typename)
        orig_expr = expr.expr
    else:
        orig_expr = expr
    # print("replacing:", to_c(expr))

    # Step 3: decide on a variable to hold the expression
    if place is not None:
        assign_before = place[2]
    else:
        assign_before = orig_expr
    reused_var = maybe_reuse_var(
        reuse_cand,
        assign_before,
        orig_expr,
        type,
        reads,
        writes,
        indices,
        typemap,
        random,
    )
    if reused_var is not None:
        reused = True
        var = reused_var
    else:
        reused = False
        var = "new_var"
        counter = 1
        while var in writes:
            counter += 1
            var = f"new_var{counter}"

    # Step 4: possibly expand the replacement to include duplicate expressions.
    prev_write, next_write = surrounding_writes(expr, orig_expr)
    prev_write = max(prev_write, indices.starts[assign_before] - 1)
    replace_cands: List[Expression] = []

    def find_duplicates(e: Expression) -> None:
        if prev_write < indices.starts[e] <= next_write and ast_util.equal_ast(
            e, orig_expr
        ):
            replace_cands.append(e)

    if ast_util.is_effectful(expr):
        replace_cands = [orig_expr]
    else:
        replace_subexprs(fn.body, find_duplicates)

    assert orig_expr in replace_cands
    if random_bool(random, PROB_TEMP_REPLACE_ALL):
        lo_index = 0
        hi_index = len(replace_cands)
    else:
        index = replace_cands.index(orig_expr)
        lo_index = random.randint(0, index)
        hi_index = random.randint(index + 1, len(replace_cands))
        if random_bool(random, PROB_TEMP_REPLACE_MOST):
            if random_bool(random, 0.5):
                lo_index = 0
            else:
                hi_index = len(replace_cands)
    replace_cand_set = set(replace_cands[lo_index:hi_index])

    # Step 5: replace the chosen expression
    def replacer(e: Expression) -> Optional[Expression]:
        if e in replace_cand_set:
            ret: Expression = ca.ID(var)
            if place is None and e is orig_expr:
                ret = ca.Assignment("=", ret, expr)
            if should_make_ptr:
                ret = ca.UnaryOp("*", ret)
            return ret
        return None

    replace_subexprs(fn.body, replacer)

    # Step 6: insert the assignment and any new variable declaration
    if place is not None:
        block, index, _ = place
        assignment = ca.Assignment("=", ca.ID(var), expr)
        ast_util.insert_statement(block, index, assignment)
    if not reused:
        if random_bool(random, PROB_RANDOMIZE_TYPE):
            type = randomize_type(type, typemap, random)
        ast_util.insert_decl(fn, var, type, random)


def perm_expand_expr(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Replace a random variable by its contents."""
    all_writes: Dict[str, List[int]] = compute_write_locations(fn, indices)
    all_reads: Dict[str, List[int]] = compute_read_locations(fn, indices)

    # Step 1: pick out a variable to replace
    rev: Dict[int, str] = {}
    for var, locs in all_reads.items():
        for index in locs:
            if region.contains_pre_index(index):
                rev[index] = var
    ensure(rev)
    index = random.choice(list(rev.keys()))
    var = rev[index]

    # Step 2: find the assignment it uses
    reads = all_reads[var]
    writes = all_writes.get(var, [])
    i = bisect.bisect_left(writes, index)
    # if i == 0, there is no write to replace the read by.
    ensure(i > 0)
    before = writes[i - 1]
    after = MAX_INDEX if i == len(writes) else writes[i]
    rev_indices = reverse_start_indices(indices)
    write = rev_indices[before]
    if (
        isinstance(write, ca.Decl)
        and write.init
        and not isinstance(write.init, ca.InitList)
    ):
        repl_expr = write.init
    elif isinstance(write, ca.Assignment) and write.op == "=":
        repl_expr = write.rvalue
    else:
        raise RandomizationFailure

    # Step 3: pick of the range of variables to replace
    repl_cands = [
        i for i in reads if before < i < after and region.contains_pre_index(i)
    ]
    assert repl_cands, "index is always in repl_cands"
    myi = repl_cands.index(index)
    if not random_bool(random, PROB_EXPAND_REPLACE_ALL) and len(repl_cands) > 1:
        # Keep using the variable for a bit in the middle
        side = random.randrange(3)
        H = len(repl_cands)
        loi = 0 if side == 0 else random.randint(0, myi)
        hii = H if side == 1 else random.randint(myi + 1, H)
        if loi == 0 and hii == H:
            loi, hii = myi, myi + 1
        repl_cands[loi:hii] = []
        keep_var = True
    else:
        keep_var = random_bool(random, PROB_KEEP_REPLACED_VAR)
    repl_cands_set = set(repl_cands)

    # Don't duplicate effectful expressions.
    if ast_util.is_effectful(repl_expr):
        ensure(len(repl_cands) == 1 and not keep_var)

    # Step 4: do the replacement
    def callback(expr: ca.Node, is_expr: bool) -> Optional[ca.Node]:
        if indices.starts[expr] in repl_cands_set:
            return copy.deepcopy(repl_expr)
        if expr == write and isinstance(write, ca.Assignment) and not keep_var:
            if is_expr:
                return write.lvalue
            else:
                return ca.EmptyStatement()
        return None

    visit_replace(fn.body, callback)
    if not keep_var and isinstance(write, ca.Decl):
        write.init = None


def perm_randomize_internal_type(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Randomize types of pre-existing local variables. Function parameters
    are not included -- those are handled by perm_randomize_function_type.
    Only variables mentioned within the given region are affected."""
    names: Set[str] = set()

    class IdVisitor(ca.NodeVisitor):
        def visit_ID(self, node: ca.ID) -> None:
            if region.contains_node(node):
                names.add(node.name)

        def visit_StructRef(self, node: ca.StructRef) -> None:
            self.visit(node.name)

    IdVisitor().visit(fn)

    typemap = build_typemap(ast)
    decls: List[ca.Decl] = []

    class Visitor(ca.NodeVisitor):
        def visit_Decl(self, decl: ca.Decl) -> None:
            if isinstance(decl.type, ca.TypeDecl) and decl.name and decl.name in names:
                decls.append(decl)
            self.generic_visit(decl)

    Visitor().visit(fn)

    ensure(decls)
    decl = random.choice(decls)
    assert isinstance(decl.type, ca.TypeDecl), "checked above"
    decl.type = randomize_type(decl.type, typemap, random, ensure_changed=True)
    set_decl_name(decl)


def perm_randomize_external_type(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Randomize types of global variables. Only variables mentioned within the
    given region are affected."""
    names: Set[str] = set()

    class IdVisitor(ca.NodeVisitor):
        def visit_ID(self, node: ca.ID) -> None:
            if region.contains_node(node):
                names.add(node.name)

        def visit_StructRef(self, node: ca.StructRef) -> None:
            self.visit(node.name)

    IdVisitor().visit(fn)

    ensure(names)
    name = random.choice(list(names))
    decls: List[Tuple[ca.Decl, int]] = []

    for i in range(len(ast.ext)):
        item = ast.ext[i]
        if isinstance(item, ca.Decl) and item.name == name:
            new_decl = copy.copy(item)
            decls.append((new_decl, i))

    ensure(decls)
    decl = random.choice(decls)[0]
    decl_type = get_decl_type(decl)

    typemap = build_typemap(ast)
    new_type = randomize_innermost_type(decl_type, typemap, random, ensure_changed=True)

    for decl, i in decls:
        decl.type = copy.deepcopy(new_type)
        ast.ext[i] = decl
        set_decl_name(decl)


def perm_randomize_function_type(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Randomize types of function parameters and returns. Only functions
    called within the given region are affected, plus the current function."""
    assert fn.decl.name is not None, "function definitions have names"
    names: Set[str] = {fn.decl.name}

    class IdVisitor(ca.NodeVisitor):
        def visit_FuncCall(self, node: ca.FuncCall) -> None:
            if region.contains_node(node) and isinstance(node.name, ca.ID):
                names.add(node.name.name)
            self.generic_visit(node)

    IdVisitor().visit(fn)

    name = random.choice(list(names))

    # Find the declarations of function with the given name. For performance
    # reasons, the part of the AST they live in are shared between all
    # randomization runs, so if we mutated them in place bad things would
    # happen. Thus, we replace the AST parts we plan to change with mutable
    # copies.
    all_decls: List[Tuple[ca.Decl, int, "ca.ExternalDeclaration"]] = []
    main_decl: Optional[ca.Decl] = None
    for i in range(len(ast.ext)):
        item = ast.ext[i]
        if (
            isinstance(item, ca.Decl)
            and isinstance(item.type, ca.FuncDecl)
            and item.name == name
        ):
            new_decl = copy.copy(item)
            ast.ext[i] = new_decl
            all_decls.append((new_decl, i, new_decl))
        if isinstance(item, ca.FuncDef) and item.decl.name == name:
            assert isinstance(
                item.decl.type, ca.FuncDecl
            ), "function definitions have function types"
            new_fndef = copy.copy(item)
            new_decl = copy.copy(item.decl)
            new_fndef.decl = new_decl
            ast.ext[i] = new_fndef
            all_decls.append((new_decl, i, new_fndef))
            main_decl = new_decl

    # Change the type within the function definition if there is one (since we
    # need to keep names there), or else within an arbitrary of the (typically
    # just one) declarations. We later mirror the change to all declarations.
    ensure(all_decls)
    if not main_decl:
        main_decl = random.choice(all_decls)[0]

    typemap = build_typemap(ast)

    main_fndecl = copy.deepcopy(main_decl.type)
    assert isinstance(main_fndecl, ca.FuncDecl), "checked above"
    main_decl.type = main_fndecl

    if random_bool(random, 0.5):
        # Replace the return type, changing integer signedness/size as well as
        # switching to/from void (which we should perhaps avoid if the function
        # call result is used, but eh, it's annoying to tell).
        type = pointer_decay(main_fndecl.type, typemap)
        if allowed_basic_type(type, typemap, ["void"]):
            main_fndecl.type = random_type(random)
        elif random_bool(random, PROB_RET_VOID):
            idtype = ca.IdentifierType(names=["void"])
            main_fndecl.type = ca.TypeDecl(declname=None, quals=[], type=idtype)
        else:
            main_fndecl.type = randomize_type(
                type, typemap, random, ensure_changed=True
            )
        set_decl_name(main_decl)
    else:
        # Replace a parameter, changing integer signedness/size.
        if not main_fndecl.args:
            raise RandomizationFailure
        ensure(main_fndecl.args.params)
        ind = random.randrange(len(main_fndecl.args.params))
        arg = main_fndecl.args.params[ind]
        if isinstance(arg, (ca.ID, ca.EllipsisParam)):
            raise RandomizationFailure
        arg_type = arg.type if isinstance(arg, ca.Typename) else get_decl_type(arg)
        type = pointer_decay(arg_type, typemap)
        arg.type = randomize_type(type, typemap, random, ensure_changed=True)
        if isinstance(arg, ca.Decl):
            set_decl_name(arg)

    # Commit the changes by writing them back to the AST, for all declarations.
    for i in range(len(all_decls)):
        decl, ind, new_node = all_decls[i]
        ast.ext[ind] = new_node
        if decl is not main_decl:
            decl.type = copy.deepcopy(main_decl.type)


def perm_refer_to_var(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Add `if (variable) {}` or `if (struct.member) {}` in a random place.
    This will get optimized away but may affect regalloc."""
    # Find expression to insert, searching within the randomization region.
    cands: List[Expression] = [
        expr
        for expr in get_block_expressions(fn.body, region)
        if isinstance(expr, (ca.StructRef, ca.ID))
    ]
    ensure(cands)
    expr = random.choice(cands)
    ensure(not ast_util.is_effectful(expr))
    typemap = build_typemap(ast)
    type: Type = resolve_typedefs(decayed_expr_type(expr, typemap), typemap)
    if isinstance(type, ca.TypeDecl) and isinstance(type.type, (ca.Struct, ca.Union)):
        expr = ca.UnaryOp("&", expr)

    if random_bool(random, 0.5):
        expr = ca.UnaryOp("!", expr)

    # Insert it wherever -- possibly outside the randomization region, since regalloc
    # can act at a distance. (Except before a declaration.)
    ins_cands = get_insertion_points(fn, Region.unbounded())
    ensure(ins_cands)

    cond = copy.deepcopy(expr)
    stmt = ca.If(cond=cond, iftrue=ca.Compound(block_items=[]), iffalse=None)
    tob, toi, _ = random.choice(ins_cands)
    ast_util.insert_statement(tob, toi, stmt)


def perm_ins_block(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Wrap a random range of statements within `if (1) { ... }` or
    `do { ... } while(0)`. Control flow can have remote effects, so this
    mostly ignores the region restriction."""
    cands: List[Block] = []

    def rec(block: Block) -> None:
        cands.append(block)
        for stmt in ast_util.get_block_stmts(block, False):
            ast_util.for_nested_blocks(stmt, rec)

    rec(fn.body)
    block = random.choice(cands)
    stmts = ast_util.get_block_stmts(block, True)
    decl_count = 0
    for stmt in stmts:
        if isinstance(stmt, (ca.Decl, ca.Pragma)):
            decl_count += 1
        else:
            break
    lo = random.randrange(decl_count, len(stmts) + 1)
    hi = random.randrange(decl_count, len(stmts) + 1)
    if hi < lo:
        lo, hi = hi, lo
    new_block = ca.Compound(block_items=stmts[lo:hi])
    if random_bool(random, PROB_INS_BLOCK_DOWHILE) and all(
        region.contains_node(n) for n in stmts[lo:hi]
    ):
        cond = ca.Constant(type="int", value="0")
        stmts[lo:hi] = [
            ca.Pragma("_permuter sameline start"),
            ca.DoWhile(cond=cond, stmt=new_block),
            ca.Pragma("_permuter sameline end"),
        ]
    else:
        cond = ca.Constant(type="int", value="1")
        stmts[lo:hi] = [ca.If(cond=cond, iftrue=new_block, iffalse=None)]


def perm_empty_stmt(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Inserts a no-op statement, one of:
    - if (1) {} (sometimes multiple of them)
    - if (0) {}
    - label:
    - goto label; label:;
    - ;
    Control flow can have remote effects, so this
    ignores the region restriction."""

    # Insert the statement wherever, except before a declaration.
    cands = get_insertion_points(fn, Region.unbounded())
    ensure(cands)

    label_name = f"dummy_label_{random.randint(1, 10**6)}"

    stmts: List[Statement] = []

    kind = random.randrange(5)
    if kind == 0:  # if (1) or multiple if (1)
        count = random.choice([1, random.randint(2, 6)])
        for _ in range(count):
            cond = ca.Constant(type="int", value="1")
            stmts.append(ca.If(cond=cond, iftrue=ca.Compound([]), iffalse=None))
    elif kind == 1:  # if (0)
        cond = ca.Constant(type="int", value="0")
        stmts = [ca.If(cond=cond, iftrue=ca.Compound([]), iffalse=None)]
    elif kind == 2:  # label:
        stmts = [ca.Label(label_name, ca.EmptyStatement())]
        pass
    elif kind == 3:  # goto label; label:
        stmts = [
            ca.Goto(label_name),
            ca.Label(label_name, ca.EmptyStatement()),
        ]
    elif kind == 4:  # ;
        stmts = [ca.EmptyStatement()]

    tob, toi, _ = random.choice(cands)
    stmts.insert(0, ca.Pragma("_permuter sameline start"))
    stmts.append(ca.Pragma("_permuter sameline end"))
    for stmt in stmts[::-1]:
        ast_util.insert_statement(tob, toi, stmt)


def perm_sameline(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Put all statements within a random interval on the same line."""
    cands = get_insertion_points(fn, region)
    n = len(cands)
    ensure(n >= 3)
    # Generate a small random interval
    lef: float = n - 2
    for i in range(4):
        lef *= random.uniform(0, 1)
    le = int(lef) + 2
    i = random.randrange(n - le)
    j = i + le
    # Insert the second statement first, since inserting a statement may cause
    # later indices to move.
    ast_util.insert_statement(
        cands[j][0], cands[j][1], ca.Pragma("_permuter sameline end")
    )
    ast_util.insert_statement(
        cands[i][0], cands[i][1], ca.Pragma("_permuter sameline start")
    )


def perm_associative(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Change a+b into b+a, or similar for other commutative operations."""
    cands: List[ca.BinaryOp] = []
    commutative_ops = list("+*|&^<>") + ["<=", ">=", "==", "!="]

    class Visitor(ca.NodeVisitor):
        def visit_BinaryOp(self, node: ca.BinaryOp) -> None:
            if node.op in commutative_ops and region.contains_node(node):
                cands.append(node)
            self.generic_visit(node)

    Visitor().visit(fn.body)
    ensure(cands)
    node = random.choice(cands)
    node.left, node.right = node.right, node.left
    if node.op[0] == "<":
        node.op = ">" + node.op[1:]
    elif node.op[0] == ">":
        node.op = "<" + node.op[1:]


def perm_condition(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Change if(x) into if(x != 0), or vice versa. Also handles for/while/do-while."""
    cands: List[Union[ca.If, ca.While, ca.DoWhile, ca.For]] = []

    class Visitor(ca.NodeVisitor):
        def visit_If(self, node: ca.If) -> None:
            cands.append(node)
            self.generic_visit(node)

        def visit_While(self, node: ca.While) -> None:
            cands.append(node)
            self.generic_visit(node)

        def visit_DoWhile(self, node: ca.DoWhile) -> None:
            cands.append(node)
            self.generic_visit(node)

        def visit_For(self, node: ca.For) -> None:
            cands.append(node)
            self.generic_visit(node)

    Visitor().visit(fn.body)
    ensure(cands)
    node = random.choice(cands)
    if not node.cond:
        raise RandomizationFailure

    if (
        isinstance(node.cond, ca.BinaryOp)
        and node.cond.op in ["==", "!=", "<", ">", "<=", ">="]
        and random_bool(random, 0.9)
    ):
        ensure(node.cond.op in ["==", "!="])
        ensure(
            isinstance(node.cond.right, ca.Constant)
            and node.cond.right.value in ["0", "0U", "0.0", "0.0f"]
        )
        if node.cond.op == "==":
            node.cond = ca.UnaryOp("!", node.cond.left)
        else:
            node.cond = node.cond.left
    else:
        expr = node.cond
        op = "!="
        if isinstance(expr, ca.UnaryOp) and expr.op == "!" and random_bool(random, 0.9):
            assert not isinstance(expr.expr, ca.Typename)
            expr = expr.expr
            op = "=="
        zero = random_weighted(
            random,
            [
                (ca.Constant("int", "0"), 0.8),
                (ca.Constant("unsigned int", "0U"), 0.2),
                (ca.Constant("float", "0.0f"), 0.05),
            ],
        )
        node.cond = ca.BinaryOp(op, expr, zero)


def perm_add_self_assignment(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Introduce a "x = x;" somewhere."""
    cands = get_insertion_points(fn, region)
    vars: List[str] = []

    class Visitor(ca.NodeVisitor):
        def visit_Decl(self, decl: ca.Decl) -> None:
            if decl.name:
                vars.append(decl.name)
            self.generic_visit(decl)

    Visitor().visit(fn.body)
    ensure(vars)
    ensure(cands)
    var = random.choice(vars)
    where = random.choice(cands)
    assignment = ca.Assignment("=", ca.ID(var), ca.ID(var))
    ast_util.insert_statement(where[0], where[1], assignment)


def perm_dummy_comma_expr(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Change x into (0, x) for a random expression x."""
    cands = get_block_expressions(fn.body, region)
    ensure(cands)
    expr = random.choice(cands)
    new_expr = ca.ExprList([ca.Constant("int", "0"), expr])
    replace_node(fn.body, expr, new_expr)


def perm_reorder_stmts(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Move a statement to another random place."""
    cands = get_insertion_points(fn, region, allow_within_decl=True)

    # Figure out candidate statements to be moved. Don't move pragmas; it can
    # cause assertion failures. Don't move blocks; statements are generally not
    # reordered across basic blocks, and we don't want to risk moving a block
    # to inside itself.
    source_inds = []
    for i, c in enumerate(cands):
        stmt = c[2]
        if (
            stmt is not None
            and not isinstance(stmt, ca.Pragma)
            and not ast_util.has_nested_block(stmt)
        ):
            source_inds.append(i)

    ensure(source_inds)
    fromi = random.choice(source_inds)

    weighted_cands = []
    for i in range(len(cands)):
        dist = max(fromi - i, i - (fromi + 1))
        if dist == 0:
            continue
        # Move distance 1, 2, 3, ... with probabilities
        # 23%, 12%, 8%, 6%, 4%, 3%, 3%, 2%, 2%, 2%, ...
        prob = (dist + 1) ** -1.5
        weighted_cands.append((i, prob))
    ensure(weighted_cands)
    toi = random_weighted(random, weighted_cands)

    fromb, fromi, from_stmt = cands[fromi]
    tob, toi, to_stmt = cands[toi]

    if fromb == tob:
        ensure(toi != fromi and toi != fromi + 1)

    if isinstance(from_stmt, ca.Decl):
        # Moving a declaration is tricky, when also preserving C89 compatibility.
        # We can move it to after another declaration, or to the start of a block.
        # Alternatively, if the declaration includes an initializer, and we move
        # it forwards, we can split that out as an assignment.
        # We don't allow moving the declaration or assignment past the next
        # occurrence of the variable.
        ensure(from_stmt.name)
        var_name = from_stmt.name
        to_index = indices.starts[to_stmt] if to_stmt else indices.ends[fromb]
        uses = 0

        class Visitor(ca.NodeVisitor):
            def visit_ID(self, node: ca.ID) -> None:
                nonlocal uses
                if node.name == var_name and indices.starts[node] < to_index:
                    uses += 1

            def visit_TypeDecl(self, node: ca.TypeDecl) -> None:
                nonlocal uses
                if node.declname == var_name and indices.starts[node] < to_index:
                    uses += 1

        Visitor().visit(fn.body)
        ensure(uses <= 1)

        to_block_stmts = ast_util.get_block_stmts(tob, False)
        if toi == 0 or isinstance(to_block_stmts[toi - 1], ca.Decl):
            # Fine to move
            pass
        elif (
            from_stmt.name
            and from_stmt.init
            and not isinstance(from_stmt.init, ca.InitList)
            and uses > 0
        ):
            assignment = ca.Assignment("=", ca.ID(from_stmt.name), from_stmt.init)
            ast_util.insert_statement(tob, toi, assignment)
            from_stmt.init = None
            return
        else:
            raise RandomizationFailure
    else:
        # Don't put statements before declarations.
        ensure(not isinstance(to_stmt, ca.Decl))

    if fromb == tob and fromi < toi:
        toi -= 1

    stmt = ast_util.get_block_stmts(fromb, True).pop(fromi)
    ast_util.insert_statement(tob, toi, stmt)


def perm_compound_assignment(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Convert a statement of the form `x = x op y` to `x op= y`, or vice versa."""
    cands: List[ca.Assignment] = []
    operators = ["+", "-", "*", "/", "<<", ">>", "^", "|", "&"]

    class Visitor(ca.NodeVisitor):
        def visit_Assignment(self, node: ca.Assignment) -> None:
            if region.contains_node(node):
                if node.op != "=" or (
                    isinstance(node.rvalue, ca.BinaryOp)
                    and ast_util.equal_ast(node.lvalue, node.rvalue.left)
                    and node.rvalue.op in operators
                ):
                    cands.append(node)
            self.generic_visit(node)

    Visitor().visit(fn.body)
    ensure(cands)
    node = random.choice(cands)

    if node.op == "=":
        assert isinstance(node.rvalue, ca.BinaryOp)
        node.op = node.rvalue.op + node.op
        node.rvalue = node.rvalue.right
    else:
        operator = node.op[:-1]
        node.op = "="
        node.rvalue = ca.BinaryOp(operator, copy.deepcopy(node.lvalue), node.rvalue)


def perm_inequalities(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Adjusts inequalities to equivalent versions that sometimes produce different code.
    For example, a > b and a >= b + 1, a < b to a <= b - 1 (and vice versa)"""
    cands: List[ca.BinaryOp] = []
    inequalities = ["<", ">", "<=", ">="]

    class Visitor(ca.NodeVisitor):
        def visit_BinaryOp(self, node: ca.BinaryOp) -> None:
            if node.op in inequalities and region.contains_node(node):
                cands.append(node)
            self.generic_visit(node)

    Visitor().visit(fn.body)
    ensure(cands)

    node = random.choice(cands)

    # Does not simplify, 'a <= (b + 1)' becomes 'a < ((b + 1) + 1)'

    def plus1(node: ca.Node) -> ca.BinaryOp:
        return ca.BinaryOp("+", node, ca.Constant("int", "1"))

    def minus1(node: ca.Node) -> ca.BinaryOp:
        return ca.BinaryOp("-", node, ca.Constant("int", "1"))

    # Don't change the operator, change both operands (can produce fake matches sometimes)
    #   Ex: a > b -> a + 1 > b + 1
    if random.random() < 0.25:
        change = random.choice([plus1, minus1])
        node.left = change(node.left)
        node.right = change(node.right)

    else:
        if node.op in ["<", ">="]:
            node.op = {"<": "<=", ">=": ">"}[node.op]
            if random_bool(random, 0.5):
                node.left = plus1(node.left)
            else:
                node.right = minus1(node.right)
        else:
            node.op = {">": ">=", "<=": "<"}[node.op]
            if random_bool(random, 0.5):
                node.left = minus1(node.left)
            else:
                node.right = plus1(node.right)


def perm_add_mask(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Add a random amount of masks of 0xFF[FFFFFFFFFFFFFF] to a random expression of integer type.
    In some cases this mask is optimized out but affects regalloc.
    The regalloc change seems to cycle with slight differences every n masks."""
    typemap = build_typemap(ast)

    # Find expression to add the mask to
    cands: List[Expression] = get_block_expressions(fn.body, region)
    ensure(cands)

    expr = random.choice(cands)
    type: SimpleType = decayed_expr_type(expr, typemap)
    ensure(
        allowed_basic_type(
            type, typemap, ["int", "char", "long", "short", "signed", "unsigned"]
        )
    )

    # Mask as if restricting the value to 8, 16, 32, or 64-bit width.
    # Sometimes use an unsigned mask like '0xFFu'
    masks: List[str] = ["0xFF", "0xFFFF", "0xFFFFFFFF", "0xFFFFFFFFFFFFFFFF"]
    mask = random.choice(masks) + random.choice(["", "u"])

    new_expr = ca.BinaryOp("&", expr, ca.Constant("int", mask))
    if random_bool(random, 0.3):
        for _ in range(random.randrange(12)):
            new_expr = ca.BinaryOp("&", new_expr, ca.Constant("int", mask))

    replace_node(fn.body, expr, new_expr)


def perm_float_literal(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Converts a Float Literal"""
    cands: List[ca.Constant] = []

    class Visitor(ca.NodeVisitor):
        def visit_Constant(self, node: ca.Constant) -> None:
            if node.type == "float" and region.contains_node(node):
                cands.append(node)

    Visitor().visit(fn.body)
    ensure(cands)

    node = random.choice(cands)

    value: str = node.value.lower()
    choices: List[str] = [value[:-1]]
    if value.endswith(".0f"):
        choices.append(value[:-3] or "0")
    elif value.endswith(".f"):
        choices.append(value[:-2] or "0")
    if value.startswith("0."):
        choices.append("." + (value[2:] or "0"))
    elif value.startswith("."):
        choices.append("0" + value)
    if value.endswith(".0f"):
        choices.append((value[:-3] or "0") + ".f")
    else:
        choices.append(value[:-1] + "0f")

    ensure(choices)
    value = random.choice(choices)
    if value.endswith("f"):
        type = "float"
    elif "." in value:
        type = "double"
    else:
        type = "int"

    replace_node(fn.body, node, ca.Constant(type, value))


def perm_cast_simple(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Cast a random expression to a simple type (integral or floating point only)."""
    typemap = build_typemap(ast)

    # Find a random expression
    cands: List[Expression] = get_block_expressions(fn.body, region)
    ensure(cands)

    expr = random.choice(cands)
    type: SimpleType = decayed_expr_type(expr, typemap)
    ensure(
        allowed_basic_type(
            type,
            typemap,
            ["int", "char", "long", "short", "signed", "unsigned", "float", "double"],
        )
    )

    integral_type = [["int"], ["char"], ["long"], ["short"], ["long", "long"]]
    floating_type = [["float"], ["double"]]
    new_type: List[str]
    if random_bool(random, 0.5):
        # Cast to integral type, sometimes unsigned
        sign: List[str] = random.choice([[], ["unsigned"]])
        new_type = sign + random.choice(integral_type)
    else:
        # Cast to floating point type
        new_type = random.choice(floating_type)

    # Surround the original expression with a cast to the chosen type
    typedecl = ca.TypeDecl(None, [], ca.IdentifierType(new_type))
    new_expr = ca.Cast(ca.Typename(None, [], typedecl), expr)
    replace_node(fn.body, expr, new_expr)


# struct_ref          # type of a         # easiest conversion
################################################################
# (a + b).c;          # impossible        #
# (a + b)->c;         # s*                # a[b].c
# (*(a + b)).c;       # s*                # a[b].c
# (*(a + b))->c;      # s**               # (*(a[b]).c
# (&(a + b)).c;       # impossible        #
# (&(a + b))->c;      # impossible        #
# (*(&(a + b))).c;    # impossible        #
# (*(&(a + b)))->c;   # imp: a+b=rvalue   #
# (&(*(a + b))).c;    # impossible        #
# (&(*(a + b)))->c;   # s*                # a[b].c (-&* req.)
################################################################
# (a[b]).c;           # s*                # (a + b)->c
# (a[b])->c;          # s**               # (*(a + b))->c
# (*(a[b])).c;        # s**               # (*(a + b))->c
# (*(a[b]))->c;       # s***              # (*(*(a + b)))->c
# (&(a[b])).c;        # impossible        #
# (&(a[b]))->c;       # s*                # (&(*(a + b)))->c
# (*(&(a[b]))).c;     # s*                # (*(&(a + b)))->c
# (*(&(a[b])))->c;    # s**               # (*(&(*(a + b))))->c
# (&(*(a[b]))).c;     # impossible        #
# (&(*(a[b])))->c;    # s**               # (&(*(*(a + b))))->c
################################################################
# a.c                 # s                 # (&a)->c
# a->c                # s*                # (*a).c
# (*a).c              # s*                # a->c
# (*a)->c             # s**               # (*(*a)).c
# (&a).c              # impossible        #
# (&a)->c             # s                 # (*(&a)).c
def perm_struct_ref(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Permute struct references: (a + b)->c, and (*(a + b)).c, a[b].c, (&a[b])->c"""
    cands: List[ca.StructRef] = []

    class Visitor(ca.NodeVisitor):
        def visit_StructRef(self, node: ca.StructRef) -> None:
            if region.contains_node(node):
                cands.append(node)
            self.generic_visit(node)

    Visitor().visit(fn.body)
    ensure(cands)

    # TODO: Split into separate perm? Need a separate one for arrayrefs, (a + b)[1] to a[b + 1]
    def randomize_associative_binop(left: ca.Node, right: ca.BinaryOp) -> ca.BinaryOp:
        """Try moving parentheses to the left side sometimes (sadly, it seems to matter)"""
        if random_bool(random, 0.5) and right.op in ["+", "-"]:
            # ((a + b) - c)
            return ca.BinaryOp(
                right.op, ca.BinaryOp("+", left, right.left), right.right
            )
        else:
            # (a + (b - c))
            return ca.BinaryOp("+", left, right)

    # Conversions
    def to_array(node: ca.BinaryOp) -> ca.ArrayRef:
        """Change a BinaryOp, a + b, to an ArrayRef, a[b]
        The operator is expected to be + or -"""
        # TODO: Permute binops like to_binop() does
        if node.op == "-":
            # Convert to a[-b]
            node.right = ca.UnaryOp("-", node.right)
        return ca.ArrayRef(node.left, node.right)

    def to_binop(node: ca.ArrayRef) -> ca.BinaryOp:
        """Change an ArrayRef, a[b], to a BinaryOp, a + b
        If b is also BinaryOp, such as a[b - 1], sometimes change the order of operations,
        ie: a + (b - 1) vs (a + b) - 1"""
        if isinstance(node.subscript, ca.BinaryOp):
            return randomize_associative_binop(node.name, node.subscript)
        return ca.BinaryOp("+", node.name, node.subscript)

    def deref(node: Expression) -> Expression:
        """Surround the given node with a dereference operator"""
        if isinstance(node, ca.UnaryOp) and node.op == "&":
            assert not isinstance(node.expr, ca.Typename)
            return node.expr
        return ca.UnaryOp("*", node)

    def addr(node: Expression) -> Expression:
        """Surround the given node with an address-of operator"""
        if isinstance(node, ca.UnaryOp) and node.op == "*":
            assert not isinstance(node.expr, ca.Typename)
            return node.expr
        return ca.UnaryOp("&", node)

    def rec(node: ca.Node) -> Any:
        """Recurse down the StructRef tree, finding the parent of the leaf BinaryOp/ArrayRef.
        Throws RandomizationFailure when a UnaryOp other than * or & was encountered."""
        if isinstance(node, ca.UnaryOp):
            ensure(node.op in ["&", "*"])
            return rec(node.expr) or node
        if isinstance(node, ca.StructRef):
            return rec(node.name) or node
        return None

    # TODO
    def apply_child(  # type: ignore
        parent: Union[ca.StructRef, ca.UnaryOp], func
    ) -> None:
        if isinstance(parent, ca.StructRef):
            parent.name = func(parent.name)
        elif isinstance(parent, ca.UnaryOp):
            parent.expr = func(parent.expr)

    def get_child(parent: Union[ca.StructRef, ca.UnaryOp]) -> ca.Node:
        if isinstance(parent, ca.StructRef):
            return parent.name
        elif isinstance(parent, ca.UnaryOp):
            return parent.expr

    struct_ref = random.choice(cands)
    parent: Union[ca.StructRef, ca.UnaryOp]

    # Step 1: Find the parent of the leaf node
    parent = rec(struct_ref)

    changed = False

    # Step 2: Simplify (...)->c to (*(...)).c
    if struct_ref.type == "->":
        struct_ref.type = "."
        # check if deref would remove the parent node
        if (
            parent is struct_ref.name
            and isinstance(parent, ca.UnaryOp)
            and parent.op == "&"
        ):
            struct_ref.name = deref(struct_ref.name)
            parent = struct_ref
        else:
            struct_ref.name = deref(struct_ref.name)
            if parent is struct_ref and isinstance(
                struct_ref.name, ca.UnaryOp
            ):  # Check to make mypy happy
                parent = struct_ref.name
        changed = True

    # Simple StructRefs only need their type permuted
    if isinstance(get_child(parent), (ca.ArrayRef, ca.BinaryOp)):
        # For binops, a lhs like  &(a+b)->c is impossible, because a + b is an rvalue

        # Step 3: Simplify further by converting ArrayRef to BinaryOp
        if isinstance(get_child(parent), ca.ArrayRef):
            apply_child(parent, to_binop)
            apply_child(parent, deref)
            parent = typing.cast("Union[ca.StructRef, ca.UnaryOp]", get_child(parent))
            changed = True

        # Step 4: Convert back to ArrayRef
        if random_bool(random, 0.5):
            # Sanity check that there's at least one dereference
            if isinstance(parent, ca.UnaryOp) and parent.op == "*":
                apply_child(parent, to_array)
                apply_child(parent, addr)
                changed = True

    # Step 5: Convert the StructRef type back
    if random_bool(random, 0.5):
        struct_ref.name = addr(struct_ref.name)
        struct_ref.type = "->"
        changed = True

    ensure(changed)


def perm_split_assignment(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Split assignments of the form a = b . c . d ...; into a = b; a = a . c . d ...;, a = c . d ...; a = b . a;, etc."""
    cands = []
    # Look for assignments of the form 'var = binaryOp' (ignores op=)
    class Visitor(ca.NodeVisitor):
        def visit_Assignment(self, node: ca.Assignment) -> None:
            if (
                node.op == "="
                and isinstance(node.rvalue, ca.BinaryOp)
                and region.contains_node(node)
            ):
                cands.append(node)
            self.generic_visit(node)

    Visitor().visit(fn.body)
    ensure(cands)

    assign = random.choice(cands)
    var = assign.lvalue

    ins_cands = get_insertion_points(fn, region)

    for ins_block, ins_index, node in ins_cands:
        if node is assign:
            break
    else:
        raise RandomizationFailure

    binops = []

    def collect_binops(node: ca.BinaryOp) -> None:
        if isinstance(node.left, ca.BinaryOp):
            collect_binops(node.left)
        binops.append(node)
        if isinstance(node.right, ca.BinaryOp):
            collect_binops(node.right)

    collect_binops(typing.cast(ca.BinaryOp, assign.rvalue))

    split = random.choice(binops)

    typemap = build_typemap(ast)
    vartype = decayed_expr_type(var, typemap)

    # Choose which side to move to a new assignment
    if random_bool(random, 0.5):
        side = split.left
        sidetype = decayed_expr_type(side, typemap)
        ensure(same_type(vartype, sidetype, typemap, allow_similar=True))
        split.left = copy.deepcopy(var)
    else:
        side = split.right
        sidetype = decayed_expr_type(side, typemap)
        ensure(same_type(vartype, sidetype, typemap, allow_similar=True))
        split.right = copy.deepcopy(var)

    # The assignment is always inserted before the original
    new_assign = ca.Assignment("=", copy.deepcopy(var), side)
    ast_util.insert_statement(ins_block, ins_index, new_assign)


def perm_remove_ast(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Delete parts of the function that might be unnecessary (mistakes or unnecessary changes from an improved base.c)."""
    cands: List[Tuple[ca.Node, ca.Node]] = []

    class Visitor(ca.NodeVisitor):
        def visit_Cast(self, node: ca.Cast) -> None:
            if region.contains_node(node):
                cands.append((node, node.expr))
            self.generic_visit(node)

        # Replace (a & constant) with (a).
        def visit_BinaryOp(self, node: ca.BinaryOp) -> None:
            if region.contains_node(node) and node.op == "&":
                if isinstance(node.left, ca.Constant):
                    cands.append((node, node.right))
                if isinstance(node.right, ca.Constant):
                    cands.append((node, node.left))
            self.generic_visit(node)

        # Remove if statements that don't have an else
        def visit_If(self, node: ca.If) -> None:
            if not node.iffalse and region.contains_node(node):
                cands.append((node, node.iftrue))
            self.generic_visit(node)

        # Remove loops
        def visit_While(self, node: ca.While) -> None:
            if region.contains_node(node):
                cands.append((node, node.stmt))
            self.generic_visit(node)

        def visit_DoWhile(self, node: ca.DoWhile) -> None:
            if region.contains_node(node):
                cands.append((node, node.stmt))
            self.generic_visit(node)

    Visitor().visit(fn.body)
    ensure(cands)

    cand, expr = random.choice(cands)
    replace_node(fn.body, cand, expr)


def perm_duplicate_assignment(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Duplicate an assignment, sometimes forcing IDO to reuse a register."""
    cands = []

    class Visitor(ca.NodeVisitor):
        def visit_Assignment(self, node: ca.Assignment) -> None:
            if region.contains_node(node) and node.op == "=":
                cands.append(node)
            self.generic_visit(node)

    Visitor().visit(fn.body)
    ensure(cands)
    cand = random.choice(cands)

    ins_cands = get_insertion_points(fn, Region.unbounded())
    ensure(ins_cands)

    dup = copy.deepcopy(cand)
    tob, toi, _ = random.choice(ins_cands)
    ast_util.insert_statement(tob, toi, dup)


def perm_pad_var_decl(
    fn: ca.FuncDef, ast: ca.FileAST, indices: Indices, region: Region, random: Random
) -> None:
    """Inserts an unused variable to adjust stack offsets. Probably only useful with --stack-diffs enabled."""
    vars: List[str] = []

    class Visitor(ca.NodeVisitor):
        def visit_Decl(self, decl: ca.Decl) -> None:
            if decl.name:
                vars.append(decl.name)
            self.generic_visit(decl)

    Visitor().visit(fn.body)

    var = "pad"
    counter = 1
    while var in vars:
        counter += 1
        var = f"pad{counter}"

    type = random_type(random)
    ast_util.insert_decl(fn, var, type, random)


class Randomizer:
    def __init__(self, rng_seed: int) -> None:
        self.random = Random(rng_seed)

    def randomize(self, ast: ca.FileAST, fn_index: int) -> None:
        fn = ast.ext[fn_index]
        assert isinstance(fn, ca.FuncDef)
        indices = ast_util.compute_node_indices(fn)
        region = get_randomization_region(fn, indices, self.random)
        methods = [
            (perm_temp_for_expr, 100),
            (perm_expand_expr, 20),
            (perm_reorder_stmts, 20),
            (perm_add_mask, 15),
            (perm_cast_simple, 10),
            (perm_refer_to_var, 10),
            (perm_float_literal, 10),
            (perm_randomize_internal_type, 10),
            (perm_randomize_external_type, 5),
            (perm_randomize_function_type, 5),
            (perm_split_assignment, 10),
            (perm_sameline, 10),
            (perm_ins_block, 10),
            (perm_struct_ref, 10),
            (perm_empty_stmt, 10),
            (perm_condition, 10),
            (perm_dummy_comma_expr, 5),
            (perm_add_self_assignment, 5),
            (perm_associative, 5),
            (perm_inequalities, 5),
            (perm_compound_assignment, 5),
            (perm_remove_ast, 5),
            (perm_duplicate_assignment, 5),
            (perm_pad_var_decl, 1),
        ]
        while True:
            method = random_weighted(self.random, methods)
            try:
                method(fn, ast, indices, region, self.random)
                break
            except RandomizationFailure:
                pass
