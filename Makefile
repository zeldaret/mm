# TODO think about how to split this up

MIPS_BINUTILS := mips-linux-gnu-

AS := $(MIPS_BINUTILS)as
LD := $(MIPS_BINUTILS)ld

QEMU_IRIX := ~/irixemu/mips-linux-user/qemu-mips
IRIX_ROOT := ./ido/
CC := $(QEMU_IRIX) -L $(IRIX_ROOT) $(IRIX_ROOT)/usr/bin/cc

CFLAGS := -G 0 -non_shared -Xfullwarn -Xcpluscomm

MIPS_VERSION := -mips2
OPTIMIZATION := -O2 -g3

build/src/libultra/os/%: OPTIMIZATION := -O1
build/src/libultra/io/%: OPTIMIZATION := -O2
build/src/libultra/libc/%: OPTIMIZATION := -O2
build/src/boot_O2_g3/%: OPTIMIZATION := -O2 -g3
test.txt: OPTIMIZATION := -O2 -g3
test.txt: MIPS_VERSION := -mips2

BASEROM_FILES := $(wildcard baserom/*)
BASEROM_O_FILES := $(BASEROM_FILES:baserom/%=build/baserom/%.o)
S_FILES := $(wildcard asm/*)
S_O_FILES = $(S_FILES:asm/%.asm=build/asm/%.o)
C_FILES := $(wildcard src/*) \
           $(wildcard src/libultra/*) \
           $(wildcard src/libultra/os/*) \
           $(wildcard src/libultra/io/*) \
           $(wildcard src/libultra/libc/*) \
           $(wildcard src/code/*) \
           $(wildcard src/boot_O2_g3/*)
C_O_FILES = $(C_FILES:src/%.c=build/src/%.o)
O_FILES := $(BASEROM_O_FILES) $(S_O_FILES)


ROM := rom.z64
ELF := build/rom.elf

# make build directories
$(shell mkdir -p build/asm)
$(shell mkdir -p build/baserom)
$(shell mkdir -p build/src)
$(shell mkdir -p build/src/libultra)
$(shell mkdir -p build/src/libultra/os)
$(shell mkdir -p build/src/libultra/io)
$(shell mkdir -p build/src/libultra/libc)
$(shell mkdir -p build/src/code)
$(shell mkdir -p build/src/boot_O2_g3)

check: $(ROM) code.bin boot.bin
	@md5sum -c checksum.md5

$(ROM): $(ELF)
	@python3 elf2rom.py

$(ELF): $(O_FILES) ldscript.txt
	$(LD) -T ldscript.txt --no-check-sections --accept-unknown-input-arch -o $@

boot.bin: code.elf
	$(MIPS_BINUTILS)objcopy --dump-section boot=$@ $<

code.bin: code.elf
	$(MIPS_BINUTILS)objcopy --dump-section code=$@ $<

code.elf: $(S_O_FILES) $(C_O_FILES) codescript.txt undef.txt
	$(LD) -T codescript.txt -T undef.txt --no-check-sections --accept-unknown-input-arch -o $@

test.txt: build/src/test.o
	$(MIPS_BINUTILS)objdump -d -z --adjust-vma=0x80080180 $< > test.txt

clean:
	rm $(ROM) $(ELF) code.elf code.bin boot.bin -r build

# Recipes

build/baserom/%.o: baserom/%
	$(MIPS_BINUTILS)objcopy -I binary -O elf32-big $< $@

build/asm/%.o: asm/%.asm
	$(AS) -march=vr4300 -32 $^ -o $@

build/src/%.o: src/%.c include/*
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTIMIZATION) -Iinclude $< -o $@

