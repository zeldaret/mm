#!/usr/bin/env python3
# usage: ./import.py path/to/file.c path/to/asm.s [make flags]
import sys
import os
import re
import subprocess
import shutil
import argparse
import shlex
import toml
from typing import Callable, Dict, List, Match, Mapping, Optional, Pattern, Set, Tuple
from collections import defaultdict

from strip_other_fns import strip_other_fns_and_write


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

CPP: List[str] = ["cpp", "-P", "-undef"]

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


def find_makefile_dir(filename: str) -> str:
    old_dirname = None
    dirname = os.path.abspath(os.path.dirname(filename))
    while dirname and (not old_dirname or len(dirname) < len(old_dirname)):
        for fname in ["makefile", "Makefile"]:
            if os.path.isfile(os.path.join(dirname, fname)):
                return dirname
        old_dirname = dirname
        dirname = os.path.dirname(dirname)

    print(f"Missing makefile for file {filename}!", file=sys.stderr)
    sys.exit(1)


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
    c_file: str, make_flags: List[str]
) -> Tuple[List[str], List[str], str]:
    makefile_dir = find_makefile_dir(os.path.abspath(os.path.dirname(c_file)))
    rel_c_file = os.path.relpath(c_file, makefile_dir)
    make_cmd = ["make", "--always-make", "--dry-run", "--debug=j"] + make_flags
    debug_output = (
        subprocess.check_output(make_cmd, cwd=makefile_dir).decode("utf-8").split("\n")
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
            "Failed to find compile command from makefile output. "
            f"Please ensure 'make -Bn --debug=j {formatcmd(make_flags)}' "
            f"contains a line with the string '{rel_c_file}'.{close_extra}",
            file=sys.stderr,
        )
        sys.exit(1)

    if len(output) > 1:
        output_lines = "\n".join(map(formatcmd, output))
        print(
            f"Error: found multiple compile commands for {rel_c_file}:\n{output_lines}\n"
            "Please modify the makefile such that if PERMUTER = 1, "
            "only a single compile command is included.",
            file=sys.stderr,
        )
        sys.exit(1)

    return output[0], assembler, makefile_dir


PreserveMacros = Tuple[Pattern[str], Callable[[str], str]]


def build_preserve_macros(
    cwd: str, preserve_regex: Optional[str]
) -> Optional[PreserveMacros]:
    data: Mapping[str, object] = {}
    for filename in SETTINGS_FILES:
        filename = os.path.join(cwd, filename)
        if os.path.exists(filename):
            with open(filename) as f:
                data = toml.load(f)
            break

    subdata = data.get("preserve_macros", {})
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
    """Import C file, preserving function macros. Subroutine of import_c_file."""

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


def import_c_file(
    compiler: List[str],
    cwd: str,
    in_file: str,
    preserve_macros: Optional[PreserveMacros],
) -> Tuple[str, List[str]]:
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
            return (
                subprocess.check_output(
                    cpp_command + STUB_FN_MACROS, cwd=cwd, encoding="utf-8"
                ),
                [],
            )

        return preprocess_c_with_macros(cpp_command, cwd, preserve_macros)

    except subprocess.CalledProcessError as e:
        print(
            "Failed to preprocess input file, when running command:\n"
            + formatcmd(e.cmd),
            file=sys.stderr,
        )
        sys.exit(1)


def finalize_compile_command(cmdline: List[str]) -> str:
    quoted = [arg if arg == "|" else shlex.quote(arg) for arg in cmdline]
    ind = (quoted + ["|"]).index("|")
    return " ".join(quoted[:ind] + ['"$INPUT"'] + quoted[ind:] + ["-o", '"$OUTPUT"'])


def write_compile_command(compiler: List[str], cwd: str, out_file: str) -> None:
    with open(out_file, "w", encoding="utf-8") as f:
        f.write("#!/usr/bin/env bash\n")
        f.write('INPUT="$(readlink -f "$1")"\n')
        f.write('OUTPUT="$(readlink -f "$3")"\n')
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


def compile_base(compile_script: str, in_file: str, out_file: str) -> None:
    in_file = os.path.abspath(in_file)
    out_file = os.path.abspath(out_file)
    compile_cmd = [compile_script, in_file, "-o", out_file]
    try:
        subprocess.check_call(compile_cmd)
    except subprocess.CalledProcessError:
        print(
            "Warning: failed to compile .c file, you'll need to adjust it manually. "
            f"Command line:\n{formatcmd(compile_cmd)}"
        )


def write_to_file(cont: str, filename: str) -> None:
    with open(filename, "w", encoding="utf-8") as f:
        f.write(cont)


def try_strip_other_fns_and_write(
    source: str, func_name: str, base_c_file: str
) -> None:
    try:
        strip_other_fns_and_write(source, func_name, base_c_file)
    except Exception:
        import traceback

        traceback.print_exc()
        print(
            "Warning: failed to remove other functions. Edit {base_c_file} and remove them manually."
        )
        with open(base_c_file, "w", encoding="utf-8") as f:
            f.write(source)


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Import a function for use with the permuter. "
        "Will create a new directory nonmatchings/<funcname>-<id>/."
    )
    parser.add_argument(
        "c_file",
        help="File containing the function. "
        "Assumes that the file can be built with 'make' to create an .o file.",
    )
    parser.add_argument(
        "asm_file",
        help="File containing assembly for the function. "
        "Must start with 'glabel <function_name>' and contain no other functions.",
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
        help="Regex for which macros to preserve, or empty string for no macros. "
        f"By default, this is read from {settings_files} in the imported "
        "file's Makefile's directory. Type information is also read from this file.",
    )
    args = parser.parse_args()

    make_flags = args.make_flags + ["PERMUTER=1"]

    func_name, asm_cont = parse_asm(args.asm_file)
    print(f"Function name: {func_name}")

    compiler, assembler, cwd = find_build_command_line(args.c_file, make_flags)
    print(f"Compiler: {formatcmd(compiler)} {{input}} -o {{output}}")
    print(f"Assembler: {formatcmd(assembler)} {{input}} -o {{output}}")

    preserve_macros = build_preserve_macros(cwd, args.preserve_macros_regex)
    source, macros = import_c_file(compiler, cwd, args.c_file, preserve_macros)

    dirname = create_directory(func_name)
    base_c_file = f"{dirname}/base.c"
    base_o_file = f"{dirname}/base.o"
    target_s_file = f"{dirname}/target.s"
    target_o_file = f"{dirname}/target.o"
    compile_script = f"{dirname}/compile.sh"
    func_name_file = f"{dirname}/function.txt"

    try:
        # try_strip_other_fns_and_write(source, func_name, base_c_file)
        write_to_file(source, base_c_file)
        write_to_file(func_name, func_name_file)
        write_compile_command(compiler, cwd, compile_script)
        write_asm(asm_cont, target_s_file)
        compile_asm(assembler, cwd, target_s_file, target_o_file)
        compile_base(compile_script, base_c_file, base_o_file)
    except:
        if not args.keep:
            print(f"\nDeleting directory {dirname} (run with --keep to preserve it).")
            shutil.rmtree(dirname)
        raise

    if macros:
        macro_str = "macros: " + ", ".join(macros)
    else:
        macro_str = "no macros"
    print(f"Preserving {macro_str}. Use --preserve-macros='<regex>' to override.")
    print(f"\nDone. Imported into {dirname}")


if __name__ == "__main__":
    main()
