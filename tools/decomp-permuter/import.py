#!/usr/bin/env python3
# usage: ./import.py path/to/file.c path/to/asm.s [make flags]
import sys
import os
import platform
import re
import subprocess
import shutil
import argparse
import shlex
import toml
import json
from typing import Callable, Dict, List, Match, Mapping, Optional, Pattern, Set, Tuple
from collections import defaultdict

from src import ast_util
from src.compiler import Compiler
from src.error import CandidateConstructionFailure

is_macos = platform.system() == "Darwin"


def homebrew_gcc_cpp() -> str:
    lookup_path = "/usr/local/bin"
    try:
        return max(f for f in os.listdir(lookup_path) if f.startswith("cpp-"))
    except ValueError:
        print("Error while looking up in " + lookup_path + " for cpp- executable")
        sys.exit(1)


cpp_cmd = homebrew_gcc_cpp() if is_macos else "cpp"
make_cmd = "gmake" if is_macos else "make"

ASM_PRELUDE: str = """
.set noat
.set noreorder
.set gp=64
.macro glabel label
    .global \label
    .type \label, @function
    \label:
.endm
"""

DEFAULT_AS_CMDLINE: List[str] = ["mips-linux-gnu-as", "-march=vr4300", "-mabi=32"]

CPP: List[str] = [cpp_cmd, "-P", "-undef"]

STUB_FN_MACROS: List[str] = [
    "-D_Static_assert(x, y)=",
    "-D__attribute__(x)=",
    "-DGLOBAL_ASM(...)=",
]

SETTINGS_FILES = ["permuter_settings.toml", "tools/permuter_settings.toml"]


def formatcmd(cmdline: List[str]) -> str:
    return " ".join(shlex.quote(arg) for arg in cmdline)


def parse_asm(asm_file: str) -> Tuple[str, str]:
    func_name = None
    asm_lines = []
    try:
        with open(asm_file, encoding="utf-8") as f:
            cur_section = ".text"
            for line in f:
                if line.strip().startswith(".section"):
                    cur_section = line.split()[1]
                elif line.strip() in [
                    ".text",
                    ".rdata",
                    ".rodata",
                    ".late_rodata",
                    ".bss",
                    ".data",
                ]:
                    cur_section = line.strip()
                if cur_section == ".text":
                    if func_name is None and line.strip().startswith("glabel "):
                        func_name = line.split()[1]
                    asm_lines.append(line)
    except OSError as e:
        print("Could not open assembly file:", e, file=sys.stderr)
        sys.exit(1)

    if func_name is None:
        print(
            "Missing function name in assembly file! The file should start with 'glabel function_name'.",
            file=sys.stderr,
        )
        sys.exit(1)

    if not re.fullmatch(r"[a-zA-Z0-9_$]+", func_name):
        print(f"Bad function name: {func_name}", file=sys.stderr)
        sys.exit(1)

    return func_name, "".join(asm_lines)


def create_directory(func_name: str) -> str:
    os.makedirs(f"nonmatchings/", exist_ok=True)
    ctr = 0
    while True:
        ctr += 1
        dirname = f"{func_name}-{ctr}" if ctr > 1 else func_name
        dirname = f"nonmatchings/{dirname}"
        try:
            os.mkdir(dirname)
            return dirname
        except FileExistsError:
            pass


def find_root_dir(filename: str, pattern: List[str]) -> Optional[str]:
    old_dirname = None
    dirname = os.path.abspath(os.path.dirname(filename))

    while dirname and (not old_dirname or len(dirname) < len(old_dirname)):
        for fname in pattern:
            if os.path.isfile(os.path.join(dirname, fname)):
                return dirname
        old_dirname = dirname
        dirname = os.path.dirname(dirname)

    return None


def fixup_build_command(
    parts: List[str], ignore_part: str
) -> Tuple[List[str], Optional[List[str]]]:
    res = []
    skip_count = 0
    assembler = None
    for part in parts:
        if skip_count > 0:
            skip_count -= 1
            continue
        if part in ["-MF", "-o"]:
            skip_count = 1
            continue
        if part == ignore_part:
            continue
        res.append(part)

    try:
        ind0 = min(
            i
            for i, arg in enumerate(res)
            if any(
                cmd in arg
                for cmd in ["asm_processor", "asm-processor", "preprocess.py"]
            )
        )
        ind1 = res.index("--", ind0 + 1)
        ind2 = res.index("--", ind1 + 1)
        assembler = res[ind1 + 1 : ind2]
        res = res[ind0 + 1 : ind1] + res[ind2 + 1 :]
    except ValueError:
        pass

    return res, assembler


def find_build_command_line(
    root_dir: str, c_file: str, make_flags: List[str], build_system: str
) -> Tuple[List[str], List[str]]:
    if build_system == "make":
        build_invocation = [
            make_cmd,
            "--always-make",
            "--dry-run",
            "--debug=j",
            "PERMUTER=1",
        ] + make_flags
    elif build_system == "ninja":
        build_invocation = ["ninja", "-t", "commands"] + make_flags
    else:
        print("Unknown build system '" + build_system + "'.")
        sys.exit(1)

    rel_c_file = os.path.relpath(c_file, root_dir)
    debug_output = (
        subprocess.check_output(build_invocation, cwd=root_dir)
        .decode("utf-8")
        .split("\n")
    )

    output = []
    close_match = False

    assembler = DEFAULT_AS_CMDLINE
    for line in debug_output:
        while "//" in line:
            line = line.replace("//", "/")
        while "/./" in line:
            line = line.replace("/./", "/")
        if rel_c_file not in line:
            continue

        close_match = True
        parts = shlex.split(line)

        # extract actual command from 'bash -c "..."'
        if parts[0] == "bash" and "-c" in parts:
            for part in parts:
                if rel_c_file in part:
                    parts = shlex.split(part)
                    break

        if rel_c_file not in parts:
            continue
        if "-o" not in parts:
            continue
        if "-fsyntax-only" in parts:
            continue
        cmdline, asmproc_assembler = fixup_build_command(parts, rel_c_file)
        if asmproc_assembler:
            assembler = asmproc_assembler
        output.append(cmdline)

    if not output:
        close_extra = (
            "\n(Found one possible candidate, but didn't match due to "
            "either spaces in paths, having -fsyntax-only, or missing an -o flag.)"
            if close_match
            else ""
        )
        print(
            "Failed to find compile command from build script output. "
            f"Please ensure running '{' '.join(build_invocation)}' "
            f"contains a line with the string '{rel_c_file}'.{close_extra}",
            file=sys.stderr,
        )
        sys.exit(1)

    if len(output) > 1:
        output_lines = "\n".join(map(formatcmd, output))
        print(
            f"Error: found multiple compile commands for {rel_c_file}:\n{output_lines}\n"
            f"Please modify the build script such that '{' '.join(build_invocation)}' "
            "produces a single compile command.",
            file=sys.stderr,
        )
        sys.exit(1)

    return output[0], assembler


PreserveMacros = Tuple[Pattern[str], Callable[[str], str]]


def build_preserve_macros(
    cwd: str, preserve_regex: Optional[str], settings: Mapping[str, object]
) -> Optional[PreserveMacros]:

    subdata = settings.get("preserve_macros", {})
    assert isinstance(subdata, dict)
    regexes = []
    for regex, value in subdata.items():
        assert isinstance(value, str)
        regexes.append((re.compile(f"^(?:{regex})$"), value))

    if preserve_regex == "" or (preserve_regex is None and not regexes):
        return None

    if preserve_regex is None:
        global_regex_text = "(?:" + ")|(?:".join(subdata.keys()) + ")"
    else:
        global_regex_text = preserve_regex
    global_regex = re.compile(f"^(?:{global_regex_text})$")

    def type_fn(macro: str) -> str:
        for regex, value in regexes:
            if regex.match(macro):
                return value
        return "int"

    return global_regex, type_fn


def preprocess_c_with_macros(
    cpp_command: List[str], cwd: str, preserve_macros: PreserveMacros
) -> Tuple[str, List[str]]:
    """Import C file, preserving function macros. Subroutine of import_c_file.

    Returns the source code and a list of preserved macros."""

    preserve_regex, preserve_type_fn = preserve_macros

    # Start by running 'cpp' in a mode that just processes ifdefs and includes.
    source = subprocess.check_output(
        cpp_command + ["-dD", "-fdirectives-only"], cwd=cwd, encoding="utf-8"
    )

    # Modify function macros that match preserved names so the preprocessor
    # doesn't touch them, and at the same time normalize their syntax. Some
    # of these instances may be in comments, but that's fine.
    def repl(match: Match[str]) -> str:
        name = match.group(1)
        after = "(" if match.group(2) == "(" else " "
        if preserve_regex.match(name):
            return f"_permuter define {name}{after}"
        else:
            return f"#define {name}{after}"

    source = re.sub(
        r"^\s*#\s*define\s+([a-zA-Z0-9_]+)([ \t\(]|$)",
        repl,
        source,
        flags=re.MULTILINE,
    )

    # Get rid of auto-inserted macros which the second cpp invocation will
    # warn about.
    source = re.sub(r"^#define __STDC_.*\n", "", source, flags=re.MULTILINE)

    # Now, run the preprocessor again for real.
    source = subprocess.check_output(
        CPP + STUB_FN_MACROS, cwd=cwd, encoding="utf-8", input=source
    )

    # Finally, find all function-like defines that we hid (some might have
    # been comments, so we couldn't do this before), and construct fake
    # function declarations for them in a specially demarcated section of
    # the file. When the compiler runs, this section will be replaced by
    # the real defines and the preprocessor invoked once more.
    late_defines = []
    lines = []
    graph = defaultdict(set)
    reg_token = re.compile(r"[a-zA-Z0-9_]+")
    for line in source.splitlines():
        is_macro = line.startswith("_permuter define ")
        params = []
        if is_macro:
            ind1 = line.find("(")
            ind2 = line.find(" ", len("_permuter define "))
            ind = min(ind1, ind2)
            if ind == -1:
                ind = len(line) if ind1 == ind2 == -1 else max(ind1, ind2)
            before = line[:ind]
            after = line[ind:]
            name = before.split()[2]
            late_defines.append((name, after))
            if after.startswith("("):
                params = [w.strip() for w in after[1 : after.find(")")].split(",")]
        else:
            lines.append(line)
            name = ""
        for m in reg_token.finditer(line):
            name2 = m.group(0)
            has_wildcard = False
            if is_macro and name2 not in params:
                wcbefore = line[: m.start()].rstrip().endswith("##")
                wcafter = line[m.end() :].lstrip().startswith("##")
                if wcbefore or wcafter:
                    graph[name].add(name2 + "*")
                    has_wildcard = True
            if not has_wildcard:
                graph[name].add(name2)

    # Prune away (recursively) unused macros, for cleanliness.
    used_anywhere = set()
    used_by_nonmacro = graph[""]
    queue = [""]
    while queue:
        name = queue.pop()
        if name not in used_anywhere:
            used_anywhere.add(name)
            if name.endswith("*"):
                wildcard = name[:-1]
                for name2 in graph:
                    if wildcard in name2:
                        queue.extend(graph[name2])
            else:
                queue.extend(graph[name])

    def get_decl(name: str, after: str) -> str:
        typ = preserve_type_fn(name)
        if after.startswith("("):
            return f"{typ} {name}();"
        else:
            return f"extern {typ} {name};"

    used_macros = [name for (name, after) in late_defines if name in used_by_nonmacro]

    return (
        "\n".join(
            ["#pragma _permuter latedefine start"]
            + [
                f"#pragma _permuter define {name}{after}"
                for (name, after) in late_defines
                if name in used_anywhere
            ]
            + [
                get_decl(name, after)
                for (name, after) in late_defines
                if name in used_by_nonmacro
            ]
            + ["#pragma _permuter latedefine end"]
            + lines
            + [""]
        ),
        used_macros,
    )


def prune_source(source: str, func_name: str) -> str:
    """Reduce the source to a smaller version that includes only the
    imported function and functions/struct/variables that it uses."""


def import_c_file(
    compiler: List[str],
    cwd: str,
    in_file: str,
    preserve_macros: Optional[PreserveMacros],
    should_prune: bool,
    func_name: str,
) -> Tuple[str, Optional[str]]:
    """Preprocess a C file into permuter-usable source.

    Prints preserved macros as a side effect.

    Returns source for base.c and compilable (macro-expanded) source."""
    in_file = os.path.relpath(in_file, cwd)
    include_next = 0
    cpp_command = CPP + [in_file, "-D__sgi", "-D_LANGUAGE_C", "-DNON_MATCHING"]

    for arg in compiler:
        if include_next > 0:
            include_next -= 1
            cpp_command.append(arg)
            continue
        if arg in ["-D", "-U", "-I"]:
            cpp_command.append(arg)
            include_next = 1
            continue
        if (
            arg.startswith("-D")
            or arg.startswith("-U")
            or arg.startswith("-I")
            or arg in ["-nostdinc"]
        ):
            cpp_command.append(arg)

    try:
        if preserve_macros is None:
            # Simple codepath, should work even if the more complex one breaks.
            source = subprocess.check_output(
                cpp_command + STUB_FN_MACROS, cwd=cwd, encoding="utf-8"
            )
            macros: List[str] = []
        else:
            source, macros = preprocess_c_with_macros(cpp_command, cwd, preserve_macros)

    except subprocess.CalledProcessError as e:
        print(
            "Failed to preprocess input file, when running command:\n"
            + formatcmd(e.cmd),
            file=sys.stderr,
        )
        sys.exit(1)

    if macros:
        macro_str = "macros: " + ", ".join(macros)
    else:
        macro_str = "no macros"
    print(f"Preserving {macro_str}. Use --preserve-macros='<regex>' to override.")

    compilable_source: Optional[str] = None
    try:
        ast = ast_util.parse_c(source, from_import=True)
        orig_fn, _ = ast_util.extract_fn(ast, func_name)
        if should_prune:
            try:
                ast_util.prune_ast(orig_fn, ast)
                source = ast_util.to_c_raw(ast)
            except Exception:
                print(
                    "Source minimization failed! "
                    "You could try --no-prune as a workaround."
                )
                raise
        compilable_source = ast_util.to_c(ast, from_import=True)
    except CandidateConstructionFailure as e:
        print(e.message)
        if should_prune and "PERM_" in source:
            print(
                "Please put in PERM macros after import, otherwise source "
                "minimization does not work."
            )
        else:
            print("Proceeding anyway, but expect errors when permuting!")

    return source, compilable_source


def finalize_compile_command(cmdline: List[str]) -> str:
    quoted = [arg if arg == "|" else shlex.quote(arg) for arg in cmdline]
    ind = (quoted + ["|"]).index("|")
    return " ".join(quoted[:ind] + ['"$INPUT"'] + quoted[ind:] + ["-o", '"$OUTPUT"'])


def write_compile_command(compiler: List[str], cwd: str, out_file: str) -> None:

    with open(out_file, "w", encoding="utf-8") as f:
        f.write("#!/usr/bin/env bash\n")
        f.write('INPUT="$(realpath "$1")"\n')
        f.write('OUTPUT="$(realpath "$3")"\n')
        f.write(f"cd {shlex.quote(cwd)}\n")
        f.write(finalize_compile_command(compiler))
    os.chmod(out_file, 0o755)


def write_asm(asm_cont: str, out_file: str) -> None:
    with open(out_file, "w", encoding="utf-8") as f:
        f.write(ASM_PRELUDE)
        f.write(asm_cont)


def compile_asm(assembler: List[str], cwd: str, in_file: str, out_file: str) -> None:
    in_file = os.path.abspath(in_file)
    out_file = os.path.abspath(out_file)
    cmdline = assembler + [in_file, "-o", out_file]
    try:
        subprocess.check_call(cmdline, cwd=cwd)
    except subprocess.CalledProcessError:
        print(
            f"Failed to assemble .s file, command line:\n{formatcmd(cmdline)}",
            file=sys.stderr,
        )
        sys.exit(1)


def compile_base(compile_script: str, source: str, c_file: str, out_file: str) -> None:
    if "PERM_" in source:
        print(
            "Cannot test-compile imported code because it contains PERM macros. "
            "It is recommended to put in PERM macros after import."
        )
        return
    escaped_c_file = json.dumps(c_file)
    source = "#line 1 " + escaped_c_file + "\n" + source
    compiler = Compiler(compile_script, show_errors=True)
    o_file = compiler.compile(source)
    if o_file:
        shutil.move(o_file, out_file)
    else:
        print("Warning: failed to compile .c file.")


def write_to_file(cont: str, filename: str) -> None:
    with open(filename, "w", encoding="utf-8") as f:
        f.write(cont)


def main() -> None:
    parser = argparse.ArgumentParser(
        description="""Import a function for use with the permuter.
        Will create a new directory nonmatchings/<funcname>-<id>/."""
    )
    parser.add_argument(
        "c_file",
        help="""File containing the function.
        Assumes that the file can be built with 'make' to create an .o file.""",
    )
    parser.add_argument(
        "asm_file",
        help="""File containing assembly for the function.
        Must start with 'glabel <function_name>' and contain no other functions.""",
    )
    parser.add_argument(
        "make_flags",
        nargs="*",
        help="Arguments to pass to 'make'. PERMUTER=1 will always be passed.",
    )
    parser.add_argument(
        "--keep", action="store_true", help="Keep the directory on error."
    )
    settings_files = ", ".join(SETTINGS_FILES[:-1]) + " or " + SETTINGS_FILES[-1]
    parser.add_argument(
        "--preserve-macros",
        metavar="REGEX",
        dest="preserve_macros_regex",
        help=f"""Regex for which macros to preserve, or empty string for no macros.
        By default, this is read from {settings_files} in a parent directory of
        the imported file. Type information is also read from this file.""",
    )
    parser.add_argument(
        "--no-prune",
        dest="prune",
        action="store_false",
        help="""Don't minimize the source to keep only the imported function and
        functions/struct/variables that it uses. Normally this behavior is
        useful to make the permuter faster, but in cases where unrelated code
        affects the generated assembly asm it can be necessary to turn off.
        Note that regardless of this setting the permuter always removes all
        other functions by replacing them with declarations.""",
    )
    args = parser.parse_args()

    root_dir = find_root_dir(
        args.c_file, SETTINGS_FILES + ["Makefile", "makefile", "build.ninja"]
    )

    if not root_dir:
        print(f"Can't find root dir of project!", file=sys.stderr)
        sys.exit(1)

    settings: Mapping[str, object] = {}
    for filename in SETTINGS_FILES:
        filename = os.path.join(root_dir, filename)
        if os.path.exists(filename):
            with open(filename) as f:
                settings = toml.load(f)
            break

    build_system = settings.get("build_system", "make")
    compiler = settings.get("compiler_command")
    assembler = settings.get("assembler_command")
    make_flags = args.make_flags

    func_name, asm_cont = parse_asm(args.asm_file)
    print(f"Function name: {func_name}")

    if compiler or assembler:
        assert isinstance(compiler, str)
        assert isinstance(assembler, str)
        assert settings.get("build_system") is None

        compiler = shlex.split(compiler)
        assembler = shlex.split(assembler)
    else:
        assert isinstance(build_system, str)
        compiler, assembler = find_build_command_line(
            root_dir, args.c_file, make_flags, build_system
        )

    print(f"Compiler: {formatcmd(compiler)} {{input}} -o {{output}}")
    print(f"Assembler: {formatcmd(assembler)} {{input}} -o {{output}}")

    preserve_macros = build_preserve_macros(
        root_dir, args.preserve_macros_regex, settings
    )
    source, compilable_source = import_c_file(
        compiler, root_dir, args.c_file, preserve_macros, args.prune, func_name
    )

    dirname = create_directory(func_name)
    base_c_file = f"{dirname}/base.c"
    base_o_file = f"{dirname}/base.o"
    target_s_file = f"{dirname}/target.s"
    target_o_file = f"{dirname}/target.o"
    compile_script = f"{dirname}/compile.sh"
    func_name_file = f"{dirname}/function.txt"

    try:
        write_to_file(source, base_c_file)
        write_to_file(func_name, func_name_file)
        write_compile_command(compiler, root_dir, compile_script)
        write_asm(asm_cont, target_s_file)
        compile_asm(assembler, root_dir, target_s_file, target_o_file)
        if compilable_source is not None:
            compile_base(compile_script, compilable_source, base_c_file, base_o_file)
    except:
        if not args.keep:
            print(f"\nDeleting directory {dirname} (run with --keep to preserve it).")
            shutil.rmtree(dirname)
        raise

    print(f"\nDone. Imported into {dirname}")


if __name__ == "__main__":
    main()
