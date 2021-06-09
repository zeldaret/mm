import os
from pathlib import Path
import re
import shutil
import tempfile
from typing import Any, Optional
import unittest

from src.compiler import Compiler
from src.preprocess import preprocess
from src import main


class TestPermMacros(unittest.TestCase):
    def go(
        self,
        intro: str,
        outro: str,
        base: str,
        target: str,
        *,
        fn_name: Optional[str] = None,
        **kwargs: Any
    ) -> int:
        base = intro + "\n" + base + "\n" + outro
        target = intro + "\n" + target + "\n" + outro
        compiler = Compiler("test/compile.sh", show_errors=True)

        # For debugging, to avoid the auto-deleted directory:
        # target_dir = tempfile.mkdtemp()
        with tempfile.TemporaryDirectory() as target_dir:
            with open(os.path.join(target_dir, "base.c"), "w") as f:
                f.write(base)

            target_o = compiler.compile(target, show_errors=True)
            assert target_o is not None
            shutil.move(target_o, os.path.join(target_dir, "target.o"))

            shutil.copy2("test/compile.sh", os.path.join(target_dir, "compile.sh"))

            if fn_name:
                with open(os.path.join(target_dir, "function.txt"), "w") as f:
                    f.write(fn_name)

            opts = main.Options(directories=[target_dir], stop_on_zero=True, **kwargs)
            return main.run(opts)[0]

    def test_general(self) -> None:
        score = self.go(
            "int test() {",
            "}",
            "return PERM_GENERAL(32,64);",
            "return 64;",
        )
        self.assertEqual(score, 0)

    def test_not_found(self) -> None:
        score = self.go(
            "int test() {",
            "}",
            "return PERM_GENERAL(32,64);",
            "return 92;",
        )
        self.assertNotEqual(score, 0)

    def test_multiple_functions(self) -> None:
        score = self.go(
            "",
            "",
            """
            int ignoreme() {}
            int foo() { return PERM_GENERAL(32,64); }
            int ignoreme2() {}
            """,
            "int foo() { return 64; }",
            fn_name="foo",
        )
        self.assertEqual(score, 0)

    def test_general_multiple(self) -> None:
        score = self.go(
            "int test() {",
            "}",
            "return PERM_GENERAL(1,2,3) + PERM_GENERAL(3,6,9);",
            "return 9;",
        )
        self.assertEqual(score, 0)

    def test_general_nested(self) -> None:
        score = self.go(
            "int test() {",
            "}",
            "return PERM_GENERAL(1,PERM_GENERAL(100,101),3) + PERM_GENERAL(3,6,9);",
            "return 110;",
        )
        self.assertEqual(score, 0)

    def test_cast(self) -> None:
        score = self.go(
            "int test(int a, int b) {",
            "}",
            "return a / PERM_GENERAL(,(unsigned int),(float)) b;",
            "return a / (float) b;",
        )
        self.assertEqual(score, 0)

    def test_cast_threaded(self) -> None:
        score = self.go(
            "int test(int a, int b) {",
            "}",
            "return a / PERM_GENERAL(,(unsigned int),(float)) b;",
            "return a / (float) b;",
            threads=2,
        )
        self.assertEqual(score, 0)

    def test_ignore(self) -> None:
        score = self.go(
            "int test(int a, int b) {",
            "}",
            "PERM_IGNORE( return a / PERM_GENERAL(a, b); )",
            "return a / b;",
        )
        self.assertEqual(score, 0)

    def test_pretend(self) -> None:
        score = self.go(
            "int global;",
            "",
            """
            PERM_IGNORE( inline void foo() { )
            PERM_PRETEND( void foo(); void bar() { )
                PERM_RANDOMIZE(
                    global = 1;
                )
            PERM_IGNORE( } void bar() { )
                PERM_RANDOMIZE(
                    global = 2; foo();
                )
            }
            """,
            """
            inline void foo() { global = 1; }
            void bar() { foo(); global = 2; }
            """,
            fn_name="bar",
        )
        self.assertEqual(score, 0)

    def test_once1(self) -> None:
        score = self.go(
            "volatile int A, B, C; void test() {",
            "}",
            """
                PERM_ONCE(B = 2;)
                A = 1;
                PERM_ONCE(B = 2;)
                C = 3;
                PERM_ONCE(B = 2;)
            """,
            "A = 1; B = 2; C = 3;",
        )
        self.assertEqual(score, 0)

    def test_once2(self) -> None:
        score = self.go(
            "volatile int A, B, C; void test() {",
            "}",
            """
                PERM_VAR(emit,)
                PERM_VAR(bademit,)
                PERM_ONCE(1, PERM_VAR(bademit, A = 7;) A = 2;)
                PERM_ONCE(1, PERM_VAR(emit, A = 1;))
                PERM_VAR(emit)
                PERM_VAR(bademit)
                PERM_ONCE(2, B = 2;)
                PERM_ONCE(2, B = 1;)
                PERM_ONCE(2,)
                PERM_ONCE(3, PERM_VAR(bademit, A = 9))
                PERM_ONCE(3, PERM_VAR(bademit, A = 9))
                C = 3;
            """,
            "A = 1; B = 2; C = 3;",
        )
        self.assertEqual(score, 0)

    def test_lineswap(self) -> None:
        score = self.go(
            "void a(); void b(); void c(); void test(void) {",
            "}",
            """
            PERM_LINESWAP(
                a();
                b();
                c();
            )
            """,
            "b(); a(); c();",
        )
        self.assertEqual(score, 0)

    def test_lineswap_text(self) -> None:
        score = self.go(
            "void a(); void b(); void c(); void test(void) {",
            "}",
            """
            PERM_LINESWAP_TEXT(
                a();
                b();
                c();
            )
            """,
            "b(); a(); c();",
        )
        self.assertEqual(score, 0)

    def test_randomizer(self) -> None:
        score = self.go(
            "void foo(); void bar(); void test(void) {",
            "}",
            "PERM_RANDOMIZE(bar(); foo();)",
            "foo(); bar();",
        )
        self.assertEqual(score, 0)

    def test_auto_randomizer(self) -> None:
        score = self.go(
            "void foo(); void bar(); void test(void) {",
            "}",
            "bar(); foo();",
            "foo(); bar();",
        )
        self.assertEqual(score, 0)

    def test_randomizer_threaded(self) -> None:
        score = self.go(
            "void foo(); void bar(); void test(void) {",
            "}",
            "PERM_RANDOMIZE(bar(); foo();)",
            "foo(); bar();",
            threads=2,
        )
        self.assertEqual(score, 0)


if __name__ == "__main__":
    unittest.main()
