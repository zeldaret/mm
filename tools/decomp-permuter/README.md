# Decomp permuter

Automatically permutes C files to better match a target binary. The permuter has two modes of operation:
- Random: purely at random, introduce temporary variables for values, change types, put statements on the same line...
- Manual: test all combinations of user-specified variations, using macros like `PERM_GENERAL(a = b ? c : d;, if (b) a = c; else a = d;)` to try both specified alternatives.

The modes can also be combined, by using the `PERM_RANDOMIZE` macro.

[<img src="https://asciinema.org/a/232846.svg" height="300">](https://asciinema.org/a/232846)

The main target for the tool is MIPS code compiled by old compilers (IDO, possibly GCC).
Getting it to work on other architectures shouldn't be too hard, however.
https://github.com/laqieer/decomp-permuter-arm has an ARM port.

## Usage

`./permuter.py directory/` runs the permuter; see below for the meaning of the directory.
Pass `-h` to see possible flags. `-j` is suggested (enables multi-threaded mode).

You'll first need to install a couple of prerequisites: `python3 -m pip install pycparser pynacl toml` (also `dataclasses` if on Python 3.6 or below)

The permuter expects as input one or more directory containing:
  - a .c file with a single function,
  - a .o file to match,
  - a .sh file that compiles the .c file.

For projects with a properly configured makefile, you should be able to set these up by running
```
./import.py <path/to/file.c> <path/to/file.s>
```
where file.c contains the function to be permuted, and file.s is its assembly in a self-contained file.
Otherwise, see USAGE.md for more details.

For projects using Ninja instead of Make, add a `permuter_settings.toml` in the root or `tools/` directory of the project:
```toml
build_system = "ninja"
```
Then `import.py` should work as expected if `build.ninja` is at the root of the project.

The .c file may be modified with any of the following macros which affect manual permutation:

- `PERM_GENERAL(a, b, ...)` expands to any of `a`, `b`, ...
- `PERM_VAR(a, b)` sets the meta-variable `a` to `b`, `PERM_VAR(a)` expands to the meta-variable `a`.
- `PERM_RANDOMIZE(code)` expands to `code`, but allows randomization within that region. Multiple regions may be specified.
- `PERM_LINESWAP(lines)` expands to a permutation of the ordered set of non-whitespace lines (split by `\n`). Each line must contain zero or more complete C statements. (For incomplete statements use `PERM_LINESWAP_TEXT`, which is slower because it has to repeatedly parse C code.)
- `PERM_INT(lo, hi)` expands to an integer between `lo` and `hi` (which must be constants).
- `PERM_IGNORE(code)` expands to `code`, without passing it through the C parser library (pycparser)/randomizer. This can be used to avoid parse errors for non-standard C, e.g. `asm` blocks.
- `PERM_PRETEND(code)` expands to `code` for the purpose of the C parser/randomizer, but gets removed afterwards. This can be used together with `PERM_IGNORE` to enable the permuter to deal with input it isn't designed for (e.g. inline functions, C++, non-code).
- `PERM_ONCE([key,] code)` expands to either `code` or to nothing, such that each unique key gets expanded exactly once. `key` defaults to `code`. For example, `PERM_ONCE(a;) b; PERM_ONCE(a;)` expands to either `a; b;` or `b; a;`.

Arguments are split by a commas, exluding commas inside parenthesis. `(,)` is a special escape sequence that resolves to `,`. 

Nested macros are allowed, so e.g.
```
PERM_VAR(delayed, )
PERM_GENERAL(stmt;, PERM_VAR(delayed, stmt;))
...
PERM_VAR(delayed)
```
is an alternative way of writing `PERM_ONCE`.

## permuter@home

The permuter supports a distributed mode, where people can donate processor power to your permuter runs to speed them up.
To use this, pass `-J` when running `permuter.py` and follow the instructions.
You will need to be granted access by someone who is already connected to a permuter network.

To allow others to use your computer for permuter runs, do the following:

- install Docker (used for sandboxing and to ensure a consistent environment)
- if on Linux, add yourself to the Docker group: `sudo usermod -aG docker $USER`
- install required packages: `python3 -m pip install docker`
- open a terminal, and run `./pah.py run-server` to start the server.
  There are a few required arguments (e.g. how many cores to use), see `--help` for more details.

Please be aware that being in the Docker group implies (password-less) sudo rights.
You can avoid that for your personal account by running the permuter under a separate user.
Unfortunately, there is currently no way to run a sandboxed permuter server without sudo rights. 😢

Anyone who is granted access to permuter@home can run a server.

To set up a new permuter network, see [src/net/controller/README.md](./src/net/controller/README.md).

## FAQ

**What do the scores mean?** The scores are computed by taking diffs of objdump'd .o
files, and giving different penalties for lines that are the same/use the same
instruction/are reordered/don't match at all. 0 means the function matches fully.
Stack positions are ignored unless --stack-diffs is passed (but beware that the
permuter is currently quite bad at resolving stack differences). For more details,
see scorer.py. It's far from a perfect system, and should probably be tweaked to
look at e.g. the register diff graph.

**What sort of non-matchings are the permuter good at?** It's generally best towards
the end, when mostly regalloc changes remain. If there are reorderings or functional
changes, it's often easy to resolve those by hand, and neither the scorer nor the
randomizer tends to play well with them.

**Should I use this instead of trying to match code by hand?** No, but it can be a good
complement. PERM macros can be used to quickly test lots of variations of a function at
once, in cases where there are interactions between several parts of a function.
The randomization mode often finds lots of nonsensical changes that improve regalloc
"by accident"; it's up to you to pick out the ones that look sensible. If none do,
it can still be useful to know which parts of the function need to be changed to get the
code nearer to matching. Having made one of the improvements, and the function can then be
permuted again, to find further possible improvements.

## Helping out

There's tons of room for helping out with the permuter!
Many more randomization passes could be added, the scoring function is far from optimal,
the permuter could be made easier to use, etc. etc. The GitHub Issues list has some ideas.

Ideally, `mypy permuter.py` and `./run-tests.sh` should succeed with no errors, and files
formatted with `black`. To setup a pre-commit hook for black, run:
```
pip install pre-commit black
pre-commit install
```
PRs that skip this are still welcome, however.
