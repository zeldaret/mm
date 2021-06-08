#!/usr/bin/env python3
import sys

from pycparser import parse_file, c_generator

fname = "test.c" if len(sys.argv) < 2 else sys.argv[1]


# ast = c_parser.CParser().parse(src)
ast = parse_file(fname, use_cpp=True)
# ast.show()
# print(c_generator.CGenerator().visit(ast))
print(ast)
