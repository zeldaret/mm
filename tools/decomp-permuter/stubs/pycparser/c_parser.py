#------------------------------------------------------------------------------
# pycparser: c_parser.py
#
# CParser class: Parser and AST builder for the C language
#
# Eli Bendersky [https://eli.thegreenplace.net/]
# License: BSD
#------------------------------------------------------------------------------

from . import c_ast

class CParser:
    def __init__(self) -> None: ...
    def parse(self, text: str, filename: str='', debuglevel: int=0) -> c_ast.FileAST: ...

