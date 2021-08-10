import sys

from pycparser import parse_file, c_generator

if len(sys.argv) < 2:
    print(f"Usage: {sys.argv[0]} filename.c")
    exit()


# ast = c_parser.CParser().parse(src)
ast = parse_file(sys.argv[1], use_cpp=True)
# ast.show()
# print(c_generator.CGenerator().visit(ast))
print(ast)
