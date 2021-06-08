# asm-differ

Nice differ for assembly code (MIPS and AArch64; should be easy to hack to support other instruction sets).

![](screenshot.png)

## Dependencies

- Python >= 3.6
- `python3 -m pip install --user colorama ansiwrap watchdog python-Levenshtein`

## Usage

Create a file `diff-settings.sh` in some directory (see the one in this repo for an example). Then from that directory, run

```
/path/to/diff.sh [flags] (function|rom addr)
```

Recommended flags are `-mwo` (automatically run `make` on source file changes, and include symbols in diff). See `--help` for more details.

### Tab completion

[argcomplete](https://kislyuk.github.io/argcomplete/) can be optionally installed (with `python3 -m pip install argcomplete`) to enable tab completion in a bash shell, completing options and symbol names using the linker map. It also requires a bit more setup:

If invoking the script **exactly** as `./diff.py`, the following should be added to the `.bashrc` according to argcomplete's instructions:

```sh
eval "$(register-python-argcomplete ./diff.py)"
```

If that doesn't work, run `register-python-argcomplete ./diff.py` in your terminal and copy the output to `.bashrc`.

If setup correctly (don't forget to restart the shell), `complete | grep ./diff.py` should output:

```
complete -o bashdefault -o default -o nospace -F _python_argcomplete ./diff.py
```

Note for developers or for general troubleshooting: run `export _ARC_DEBUG=` to enable debug output during tab-completion, it may show otherwise silenced errors. Use `unset _ARC_DEBUG` or restart the terminal to disable.
