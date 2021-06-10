# asm-processor

Pre-process .c files and post-process .o files to enable embedding MIPS assembly into IDO-compiled C.

## Usage

Let's say you have a file compiled with `-g` on the IDO compiler, that looks like this:
```c
float func4(void) {
    "func4";
    return 0.2f;
}
```

This script enables replacing it by:
```asm
GLOBAL_ASM(
.rdata
.word 0x66756e63 # func
.word 0x34000000 # 4\0\0\0

.late_rodata
glabel rv
.word 0x3e4ccccd # 0.2f

.text
glabel func4
lui     $at, %hi(rv)
jr      $ra
lwc1    $f0, %lo(rv)($at)
jr      $ra
nop
jr      $ra
nop
)
```

To compile the file, run `./compile.sh file.c`, or invoke the `asm_processor.py` script in a similar manner. (`compile.sh` is mostly just intended to describe example usage.)

Reading assembly from file is also supported, e.g. `GLOBAL_ASM("file.s")`.

### What is supported?

`.text`, `.data`, `.bss` and `.rodata` sections, `.word`/`.incbin`, `.ascii`/`.asciz`, and `-g`, `-g3`, `-O1`, `-O2` and `-framepointer` flags to the IDO compiler.

### What is not supported?

* complicated assembly (.ifdef, macro declarations/calls other than `glabel`, pseudo-instructions that expand to several real instructions)
* non-IDO compilers
* `-mips1` (`-mips3` may also not work fully)

C `#ifdef`s only work outside of `GLOBAL_ASM` calls, but is otherwise able to replace `.ifdef`.

### What's up with "late rodata"?

The IDO compiler emits rodata in two passes: first array/string contents, then large literals/switch jump tables.

Data declared within `.rdata`/`.section .rodata` will end up in the first half, and `.late_rodata`/`.section .late_rodata` in the second half.

### How does it work?

It's a bit of a hack!
The basic idea is replace `GLOBAL_ASM` blocks with dummy C functions/global vars of the same sections sizes as the assembly.
Then the C file gets compiled, and the dummy contents overwritten with the injected assembly.

To accomplish this, asm-processor has logic for guessing the size of assembly contents
(which assumes the assembly isn't too complicated, e.g. no macros),
and for emitting C code of exact sizes for a bunch of different IDO compiler flags.

The assembler code is padded with nops to line it up with its correct position in the C;
this allows C and asm ELF files to be merged easily without having to fix up e.g. symbol addresses.

The most difficulty part is `late_rodata`, which is hard to create programmatically.
asm-processor does that by emitting code that uses dummy float literals/double literals/jump tables,
assembles the late_rodata at another location of the .rodata section, then overwrites the dummy rodata.
This does require some movement of symbols and relocations, and quite a bit of care in what code to
emit and how to preserve .double alignment.

It's worth noting some alternative ways in which asm-processor would have been implemented:
- One idea to get rid of the C/asm size estimations is to emit arbitrary code, and then move code,
symbols and relocations to the correct place after the sizes are known.
Given the machinery for `late_rodata` this wouldn't have been too difficult, and it would have the upside of improved portability.
There is a big downside, however: using dummy code of incorrect size throws off alignment and can introduce unintended padding.
Fixing this would require running multiple passes of asm-processor, with one compile per `ASM_GLOBAL`.
- Another idea is to run the compiler with -S to emit assembly, modify the emitted assembly, then run the assembler
(which in IDO's case may perform additional instruction reordering etc.).
This option has not been investigated in much detail, and would perhaps be superior to the current implementation.
It does have a few unknowns to it, e.g. instruction encoding differences between GNU `as` and IDO's assembler,
how to avoid reordering the injected assembly, and how .rodata/.late_rodata are implemented.

### Testing

There are a few tests to ensure you don't break anything when hacking on asm-processor: `./run-tests.sh` should exit without output if they pass, or else output a diff from previous to new version.
