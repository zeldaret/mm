import unittest
import os
import tempfile
import shutil
from pathlib import Path
import re

from strip_other_fns import strip_other_fns_and_write
from src.compiler import Compiler
from src.preprocess import preprocess
from src import main

c_files_list = [
    ['test_general.c', 'test_general'],
    ['test_general.c', 'test_general_3'],
    ['test_general.c', 'test_general_multiple'],
    ['test_ternary.c', 'test_ternary1'],
    ['test_ternary.c', 'test_ternary2'],
    ['test_type.c', 'test_type1'],
    ['test_type.c', 'test_type2'],
    ['test_type.c', 'test_type3'],
    ['test_randomizer.c', 'test_randomizer'],
]

class TestStringMethods(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = Compiler('test/compile.sh')
        cls.tmp_dirs = {}
        for test_c, test_fn in c_files_list:
            d = tempfile.TemporaryDirectory()
            file_test = os.path.join('test', test_c)
            file_actual = os.path.join(d.name, "actual.c")
            file_base = os.path.join(d.name, "base.c")
            file_target = os.path.join(d.name, "target.o")

            actual_preprocessed = preprocess(file_test, cpp_args=['-DACTUAL'])
            base_preprocessed = preprocess(file_test, cpp_args=['-UACTUAL'])

            strip_other_fns_and_write(actual_preprocessed, test_fn, file_actual)
            strip_other_fns_and_write(base_preprocessed, test_fn, file_base)

            actual_source = Path(file_actual).read_text()
            target_o = compiler.compile(actual_source, show_errors=True)
            assert target_o is not None
            shutil.copy2(target_o, file_target)
            os.remove(target_o)

            shutil.copy2("test/compile.sh", d.name)
            cls.tmp_dirs[(test_c, test_fn)] = d
            
    @classmethod
    def tearDownClass(cls):
        for d in cls.tmp_dirs.values():
            d.cleanup()

    def go(self, filename, fn_name, **kwargs) -> int:
        d = self.tmp_dirs[(filename, fn_name)].name
        score, = main.run(main.Options(directories=[d], stop_on_zero=True, **kwargs))
        return score

    def test_general(self):
        score = self.go('test_general.c', 'test_general')
        self.assertEqual(score, 0)

    def test_general_3(self):
        score = self.go('test_general.c', 'test_general_3')
        self.assertEqual(score, 0)

    def test_general_multiple(self):
        score = self.go('test_general.c', 'test_general_multiple')
        self.assertEqual(score, 0)

    def test_ternary1(self):
        score = self.go('test_ternary.c', 'test_ternary1')
        self.assertEqual(score, 0)

    def test_ternary2(self):
        score = self.go('test_ternary.c', 'test_ternary2')
        self.assertEqual(score, 0)

    def test_type1(self):
        score = self.go('test_type.c', 'test_type1')
        self.assertEqual(score, 0)

    def test_type2(self):
        score = self.go('test_type.c', 'test_type2')
        self.assertEqual(score, 0)

    def test_type3(self):
        score = self.go('test_type.c', 'test_type3')
        self.assertEqual(score, 0)

    def test_type3_threaded(self):
        score = self.go('test_type.c', 'test_type3', threads=2)
        self.assertEqual(score, 0)

    def test_randomizer(self):
        score = self.go('test_randomizer.c', 'test_randomizer')
        self.assertEqual(score, 0)

    def test_randomizer_threaded(self):
        score = self.go('test_randomizer.c', 'test_randomizer', threads=2)
        self.assertEqual(score, 0)


if __name__ == '__main__':
    unittest.main()
