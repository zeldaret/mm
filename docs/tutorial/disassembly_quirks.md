# Disassembly quirks

As MM's disassembly is automatic, there are certain unique problems it has.

## Renaming functions and variables

A function must be renamed in `tools/disasm/functions.txt` in addition to the source code, for the disassembler to know what to call the symbol at that address when it sees it.

Variables must be renamed in `tools/disasm/variables.txt`. It may also be necessary to change their type, count or size to stop the disassembler misusing them.

You can avoid having to redisassemble every time by running `rename_global_asm.py`, which will rename the individual functions' assembly files in `asm/nonmatchings/` to the name of the function they contain.


## Fake and incorrect symbols

TODO


## Resplitting a file

The files `boot` and `code` are each divided up into dozens of separate files, that are all joined together into one text, data, rodata and bss section when building the ROM. As such, it has been necessary to guess where the file boundaries are, and not every file contains the correct functions or the correct data (rodata is mostly the exception since it is automatically split).

To change a split for a file, find its entry in `tools/disasm/files.txt`, and change or create entries to accurately reflect where the file(s) should start. For example, it was found that the last function in `z_nmi_buff.c` had nothing to do with the rest, so it should be split into its own file. Looking up the address of the last function, it was found to be at `0x8010C1B0`, so adding the line:

```diff
            0x8010C0C0 : "z_nmi_buff",
+++            0x8010C1B0 : "code_8010C1B0",
            0x8010C230 : "z_olib",
```

to the file will extract it correctly as a separate file. It also is necessary to make a new C file and move the `GLOBAL_ASM` declaration into it.

Unfortunately you essentially have to redisassemble after telling the disassembler to resplit a file.


## 
