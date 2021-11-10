"""Functions and classes for dealing with types in a C AST.

They make a number of simplifying assumptions:
 - const and volatile doesn't matter.
 - arithmetic promotes all int-like types to 'int'.
 - no two variables can have the same name, even across functions.

For the purposes of the randomizer these restrictions are acceptable."""

from dataclasses import dataclass, field
from typing import Union, Dict, Set, List

from pycparser import c_ast
from pycparser.c_ast import ArrayDecl, TypeDecl, PtrDecl, FuncDecl, IdentifierType

Type = Union[PtrDecl, ArrayDecl, TypeDecl, FuncDecl]
SimpleType = Union[PtrDecl, TypeDecl]

StructUnion = Union[c_ast.Struct, c_ast.Union]


@dataclass
class TypeMap:
    typedefs: Dict[str, Type] = field(default_factory=dict)
    fn_ret_types: Dict[str, Type] = field(default_factory=dict)
    var_types: Dict[str, Type] = field(default_factory=dict)
    struct_defs: Dict[str, StructUnion] = field(default_factory=dict)


def basic_type(name: Union[str, List[str]]) -> TypeDecl:
    names = [name] if isinstance(name, str) else name
    idtype = IdentifierType(names=names)
    return TypeDecl(declname=None, quals=[], align=[], type=idtype)


def pointer(type: Type) -> Type:
    return PtrDecl(quals=[], type=type)


def resolve_typedefs(type: Type, typemap: TypeMap) -> Type:
    while (
        isinstance(type, TypeDecl)
        and isinstance(type.type, IdentifierType)
        and len(type.type.names) == 1
        and type.type.names[0] in typemap.typedefs
    ):
        type = typemap.typedefs[type.type.names[0]]
    return type


def pointer_decay(type: Type, typemap: TypeMap) -> SimpleType:
    real_type = resolve_typedefs(type, typemap)
    if isinstance(real_type, ArrayDecl):
        return PtrDecl(quals=[], type=real_type.type)
    if isinstance(real_type, FuncDecl):
        return PtrDecl(quals=[], type=type)
    if isinstance(real_type, TypeDecl) and isinstance(real_type.type, c_ast.Enum):
        return basic_type("int")
    assert not isinstance(
        type, (ArrayDecl, FuncDecl)
    ), "resolve_typedefs can't hide arrays/functions"
    return type


def get_decl_type(decl: c_ast.Decl) -> Type:
    """For a Decl that declares a variable (and not just a struct/union/enum),
    return its type."""
    assert decl.name is not None
    assert isinstance(decl.type, (PtrDecl, ArrayDecl, FuncDecl, TypeDecl))
    return decl.type


def deref_type(type: Type, typemap: TypeMap) -> Type:
    type = resolve_typedefs(type, typemap)
    assert isinstance(type, (ArrayDecl, PtrDecl)), "dereferencing non-pointer"
    return type.type


def struct_member_type(struct: StructUnion, field_name: str, typemap: TypeMap) -> Type:
    if not struct.decls:
        assert (
            struct.name in typemap.struct_defs
        ), f"Accessing field {field_name} of undefined struct {struct.name}"
        struct = typemap.struct_defs[struct.name]
    assert struct.decls, "struct_defs never points to an incomplete type"
    for decl in struct.decls:
        if isinstance(decl, c_ast.Decl):
            if decl.name == field_name:
                return get_decl_type(decl)
            if decl.name == None and isinstance(decl.type, (c_ast.Struct, c_ast.Union)):
                try:
                    return struct_member_type(decl.type, field_name, typemap)
                except AssertionError:
                    pass

    assert False, f"No field {field_name} in struct {struct.name}"


def expr_type(node: c_ast.Node, typemap: TypeMap) -> Type:
    def rec(sub_expr: c_ast.Node) -> Type:
        return expr_type(sub_expr, typemap)

    if isinstance(node, c_ast.Assignment):
        return rec(node.lvalue)
    if isinstance(node, c_ast.StructRef):
        lhs_type = rec(node.name)
        if node.type == "->":
            lhs_type = deref_type(lhs_type, typemap)
        struct_type = resolve_typedefs(lhs_type, typemap)
        assert isinstance(struct_type, TypeDecl)
        assert isinstance(
            struct_type.type, (c_ast.Struct, c_ast.Union)
        ), f"struct deref of non-struct {struct_type.declname}"
        return struct_member_type(struct_type.type, node.field.name, typemap)
    if isinstance(node, c_ast.Cast):
        return node.to_type.type
    if isinstance(node, c_ast.Constant):
        if node.type == "string":
            return pointer(basic_type("char"))
        if node.type == "char":
            return basic_type("int")
        return basic_type(node.type.split(" "))
    if isinstance(node, c_ast.ID):
        return typemap.var_types[node.name]
    if isinstance(node, c_ast.UnaryOp):
        if node.op in ["p++", "p--", "++", "--"]:
            return rec(node.expr)
        if node.op == "&":
            return pointer(rec(node.expr))
        if node.op == "*":
            subtype = rec(node.expr)
            return deref_type(subtype, typemap)
        if node.op in ["-", "+"]:
            subtype = pointer_decay(rec(node.expr), typemap)
            if allowed_basic_type(subtype, typemap, ["double"]):
                return basic_type("double")
            if allowed_basic_type(subtype, typemap, ["float"]):
                return basic_type("float")
        if node.op in ["sizeof", "-", "+", "~", "!"]:
            return basic_type("int")
        assert False, f"unknown unary op {node.op}"
    if isinstance(node, c_ast.BinaryOp):
        lhs_type = pointer_decay(rec(node.left), typemap)
        rhs_type = pointer_decay(rec(node.right), typemap)
        if node.op in [">>", "<<"]:
            return lhs_type
        if node.op in ["<", "<=", ">", ">=", "==", "!=", "&&", "||"]:
            return basic_type("int")
        if node.op in "&|^%":
            return basic_type("int")
        real_lhs = resolve_typedefs(lhs_type, typemap)
        real_rhs = resolve_typedefs(rhs_type, typemap)
        if node.op in "+-":
            lptr = isinstance(real_lhs, PtrDecl)
            rptr = isinstance(real_rhs, PtrDecl)
            if lptr or rptr:
                if lptr and rptr:
                    assert node.op != "+", "pointer + pointer"
                    return basic_type("int")
                if lptr:
                    return lhs_type
                assert node.op == "+", "int - pointer"
                return rhs_type
        if node.op in "*/+-":
            assert isinstance(real_lhs, TypeDecl)
            assert isinstance(real_rhs, TypeDecl)
            assert isinstance(real_lhs.type, IdentifierType)
            assert isinstance(real_rhs.type, IdentifierType)
            if "double" in real_lhs.type.names + real_rhs.type.names:
                return basic_type("double")
            if "float" in real_lhs.type.names + real_rhs.type.names:
                return basic_type("float")
            return basic_type("int")
    if isinstance(node, c_ast.FuncCall):
        expr = node.name
        if isinstance(expr, c_ast.ID):
            if expr.name not in typemap.fn_ret_types:
                raise Exception(f"Called function {expr.name} is missing a prototype")
            return typemap.fn_ret_types[expr.name]
        else:
            fptr_type = resolve_typedefs(rec(expr), typemap)
            if isinstance(fptr_type, PtrDecl):
                fptr_type = fptr_type.type
            fptr_type = resolve_typedefs(fptr_type, typemap)
            assert isinstance(fptr_type, FuncDecl), "call to non-function"
            return fptr_type.type
    if isinstance(node, c_ast.ExprList):
        return rec(node.exprs[-1])
    if isinstance(node, c_ast.ArrayRef):
        subtype = rec(node.name)
        return deref_type(subtype, typemap)
    if isinstance(node, c_ast.TernaryOp):
        return rec(node.iftrue)
    assert False, f"Unknown expression node type: {node}"


def decayed_expr_type(expr: c_ast.Node, typemap: TypeMap) -> SimpleType:
    return pointer_decay(expr_type(expr, typemap), typemap)


def same_type(
    type1: Type, type2: Type, typemap: TypeMap, allow_similar: bool = False
) -> bool:
    while True:
        type1 = resolve_typedefs(type1, typemap)
        type2 = resolve_typedefs(type2, typemap)
        if isinstance(type1, ArrayDecl) and isinstance(type2, ArrayDecl):
            type1 = type1.type
            type2 = type2.type
            continue
        if isinstance(type1, PtrDecl) and isinstance(type2, PtrDecl):
            type1 = type1.type
            type2 = type2.type
            continue
        if isinstance(type1, TypeDecl) and isinstance(type2, TypeDecl):
            sub1 = type1.type
            sub2 = type2.type
            if isinstance(sub1, c_ast.Struct) and isinstance(sub2, c_ast.Struct):
                return sub1.name == sub2.name
            if isinstance(sub1, c_ast.Union) and isinstance(sub2, c_ast.Union):
                return sub1.name == sub2.name
            if (
                allow_similar
                and isinstance(sub1, (IdentifierType, c_ast.Enum))
                and isinstance(sub2, (IdentifierType, c_ast.Enum))
            ):
                # All int-ish types are similar (except void, but whatever)
                return True
            if isinstance(sub1, c_ast.Enum) and isinstance(sub2, c_ast.Enum):
                return sub1.name == sub2.name
            if isinstance(sub1, IdentifierType) and isinstance(sub2, IdentifierType):
                return sorted(sub1.names) == sorted(sub2.names)
        return False


def allowed_basic_type(
    type: SimpleType, typemap: TypeMap, allowed_types: List[str]
) -> bool:
    """Check if a type resolves to a basic type with one of the allowed_types
    keywords in it."""
    base_type = resolve_typedefs(type, typemap)
    if not isinstance(base_type, c_ast.TypeDecl):
        return False
    if not isinstance(base_type.type, c_ast.IdentifierType):
        return False
    if all(x not in base_type.type.names for x in allowed_types):
        return False
    return True


def build_typemap(ast: c_ast.FileAST) -> TypeMap:
    ret = TypeMap()
    for item in ast.ext:
        if isinstance(item, c_ast.Typedef):
            ret.typedefs[item.name] = item.type
        if isinstance(item, c_ast.FuncDef):
            assert item.decl.name is not None, "cannot define anonymous function"
            assert isinstance(item.decl.type, FuncDecl)
            ret.fn_ret_types[item.decl.name] = item.decl.type.type
        if isinstance(item, c_ast.Decl) and isinstance(item.type, FuncDecl):
            assert item.name is not None, "cannot define anonymous function"
            ret.fn_ret_types[item.name] = item.type.type
    defined_function_decls: Set[c_ast.Decl] = set()

    class Visitor(c_ast.NodeVisitor):
        def visit_Struct(self, struct: c_ast.Struct) -> None:
            if struct.decls and struct.name is not None:
                ret.struct_defs[struct.name] = struct
            # Do not visit decls of this struct

        def visit_Union(self, union: c_ast.Union) -> None:
            if union.decls and union.name is not None:
                ret.struct_defs[union.name] = union
            # Do not visit decls of this union

        def visit_Decl(self, decl: c_ast.Decl) -> None:
            if decl.name is not None:
                ret.var_types[decl.name] = get_decl_type(decl)
            if not isinstance(decl.type, FuncDecl) or decl in defined_function_decls:
                # Do not visit declarations in parameter lists of functions
                # other than our own.
                self.visit(decl.type)

        def visit_Enumerator(self, enumerator: c_ast.Enumerator) -> None:
            ret.var_types[enumerator.name] = basic_type("int")

        def visit_FuncDef(self, fn: c_ast.FuncDef) -> None:
            if fn.decl.name is not None:
                ret.var_types[fn.decl.name] = get_decl_type(fn.decl)
            defined_function_decls.add(fn.decl)
            self.generic_visit(fn)

    Visitor().visit(ast)
    return ret


def set_decl_name(decl: c_ast.Decl) -> None:
    name = decl.name
    assert name is not None
    type = get_decl_type(decl)
    while not isinstance(type, TypeDecl):
        type = type.type
    type.declname = name
