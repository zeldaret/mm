#!/usr/bin/env python3
# Generate a .d file with Makefile variables from the dmadata_table.txt file

import os, struct, sys, ast, argparse


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--yaz0-path", required=False, help="path to `yaz0` tool")
    parser.add_argument(
        "--dmadata-table",
        type=argparse.FileType("r"),
        help="dmadata_table.txt input file",
    )
    parser.add_argument(
        "--output-deps", type=argparse.FileType("w"), help="romfiles.d output file"
    )
    args = parser.parse_args()

    dmadata_table = ast.literal_eval(args.dmadata_table.read())
    rom_files = []
    for base_file, comp_file, _, _ in dmadata_table:
        if base_file == "":
            assert comp_file == ""
            continue

        # TODO: Unsure if it's better to emit these rules here, or use a set of
        # prefix rules in the Makefile.
        if args.yaz0_path is not None and comp_file.endswith(".yaz0"):
            # Add a rule for generating the compressed `.yaz0` file
            # from the uncompressed file
            args.output_deps.write(f"{comp_file}: {base_file}\n")
            args.output_deps.write(f"\t{args.yaz0_path} $< $@\n")
            args.output_deps.write("\n")

        if comp_file == "":
            comp_file = base_file

        rom_files.append((base_file, comp_file))
    args.dmadata_table.close()

    # Define lists of files for using in other rules
    uncompressed_files, compressed_files = zip(*rom_files)
    for var_name, filenames in (
        ("UNCOMPRESSED_ROM_FILES", uncompressed_files),
        ("ROM_FILES", compressed_files),
    ):
        args.output_deps.write(f"{var_name} := \\\n")
        for filename in filenames:
            args.output_deps.write(f"    {filename} \\\n")
        args.output_deps.write("\n\n")
    args.output_deps.close()


if __name__ == "__main__":
    main()
