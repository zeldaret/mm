import re
import argparse
from typing import Optional
from pathlib import Path


def _find_bracket_end(input: str, start_index: int) -> int:
    level = 1
    assert input[start_index] == "{"
    i = start_index + 1
    while i < len(input):
        if input[i] == "{":
            level += 1
        elif input[i] == "}":
            level -= 1
            if level == 0:
                break
        i += 1

    assert level == 0, "unbalanced {}"
    return i


def strip_other_fns(source: str, keep_fn_name: str) -> str:
    result = ""
    remain = source
    while True:
        fn_regex = re.compile(r"^.*\s+\**(\w+)\(.*\)\s*?{", re.M)
        fn = re.search(fn_regex, remain)
        if fn is None:
            result += remain
            remain = ""
            break

        fn_name = fn.group(1)
        bracket_end = _find_bracket_end(remain, fn.end() - 1)
        if fn_name.startswith("PERM"):
            result += remain[: bracket_end + 1]
        elif fn_name == keep_fn_name:
            result += "\n\n" + remain[: bracket_end + 1] + "\n\n"
        else:
            result += remain[: fn.end() - 1].rstrip() + ";"

        remain = remain[bracket_end + 1 :]

    return result


def strip_other_fns_and_write(
    source: str, fn_name: str, out_filename: Optional[str] = None
) -> None:
    stripped = strip_other_fns(source, fn_name)

    if out_filename is None:
        print(stripped)
    else:
        with open(out_filename, "w", encoding="utf-8") as f:
            f.write(stripped)


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Remove all but a single function definition from a file."
    )
    parser.add_argument("c_file", help="File containing the function.")
    parser.add_argument("fn_name", help="Function name.")
    args = parser.parse_args()

    source = Path(args.c_file).read_text()
    strip_other_fns_and_write(source, args.fn_name, args.c_file)


if __name__ == "__main__":
    main()
