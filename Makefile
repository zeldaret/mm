# If COMPARE is 1, check the output md5sum after building
COMPARE ?= 1
# If NON_MATCHING is 1, define the NON_MATCHING C flag when building
NON_MATCHING ?= 0
# If ORIG_COMPILER is 1, compile with QEMU_IRIX and the original compiler
# TODO we do not support static recomp, so force this to 1
ORIG_COMPILER ?= 0

ifeq ($(NON_MATCHING),1)
  CFLAGS := -DNON_MATCHING
  CPPFLAGS := -DNON_MATCHING
  COMPARE := 0
endif

ifeq ($(OS),Windows_NT)
    DETECTED_OS=windows
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        DETECTED_OS=linux
    endif
    ifeq ($(UNAME_S),Darwin)
        DETECTED_OS=macos
        MAKE=gmake
        CPPFLAGS += -xc++
    endif
endif

#### Tools ####
ifeq ($(shell type mips-linux-gnu-ld >/dev/null 2>/dev/null; echo $$?), 0)
  MIPS_BINUTILS_PREFIX := mips-linux-gnu-
else
  MIPS_BINUTILS_PREFIX := mips64-elf-
endif

CC       := tools/ido_recomp/$(DETECTED_OS)/7.1/cc
CC_OLD   := tools/ido_recomp/$(DETECTED_OS)/5.3/cc
GCC      := gcc
QEMU_IRIX ?= ./tools/qemu-mips

# if ORIG_COMPILER is 1, check that either QEMU_IRIX is set or qemu-irix package installed
ifeq ($(ORIG_COMPILER),1)
  ifndef QEMU_IRIX
    QEMU_IRIX := $(shell which qemu-irix)
    ifeq (, $(QEMU_IRIX))
      $(error Please install qemu-irix package or set QEMU_IRIX env var to the full qemu-irix binary path)
    endif
  endif
  CC        = $(QEMU_IRIX) -L tools/ido7.1_compiler tools/ido7.1_compiler/usr/bin/cc
  CC_OLD    = $(QEMU_IRIX) -L tools/ido5.3_compiler tools/ido5.3_compiler/usr/bin/cc
endif

AS      := $(MIPS_BINUTILS_PREFIX)as
LD      := $(MIPS_BINUTILS_PREFIX)ld
OBJCOPY := $(MIPS_BINUTILS_PREFIX)objcopy
OBJDUMP := $(MIPS_BINUTILS_PREFIX)objdump

OPTFLAGS := -O2 -g3
ASFLAGS := -march=vr4300 -32
MIPS_VERSION := -mips2

# we support Microsoft extensions such as anonymous structs, which the compiler does support but warns for their usage. Surpress the warnings with -woff.
CFLAGS += -G 0 -non_shared -Xfullwarn -Xcpluscomm -Iinclude -Isrc -Wab,-r4300_mul -woff 649,838

#### Files ####

# ROM image
MM_BASEROM ?= baserom.z64
MM_ROM_NAME ?= rom
ROM := $(MM_ROM_NAME).z64
UNCOMPRESSED_ROM := $(MM_ROM_NAME)_uncompressed.z64
ELF := $(MM_ROM_NAME).elf

BASEROM_FILES := $(wildcard baserom/*)
# Exclude dmadata, it will be generated right before packing the rom
BASEROM_FILES := $(subst baserom/dmadata ,,$(BASEROM_FILES))
BASEROM_BUILD_FILES := $(BASEROM_FILES:baserom/%=build/baserom/%)

BASE_DECOMP_FILES := $(wildcard decomp/*)
DECOMP_FILES := $(BASE_DECOMP_FILES:decomp/%=build/decomp/%)
COMP_FILES := $(DECOMP_FILES:build/decomp/%=build/comp/%.yaz0)

DMADATA_FILES := $(DECOMP_FILES) $(BASEROM_BUILD_FILES)
# Exclude code files, they will be extracted from the file instead
DMADATA_FILES := $(subst build/baserom/boot ,,$(DMADATA_FILES))
DMADATA_FILES := $(subst build/decomp/code ,,$(DMADATA_FILES))
DMADATA_FILES := $(DMADATA_FILES:build/decomp/ovl_%=)

SRC_DIRS := $(shell find src -type d)

# Because we may not have disassembled the code files yet, there might not be any assembly files.
# Instead, generate a list of assembly files based on what's listed in the linker script.
S_FILES := $(shell grep build/asm ./linker_scripts/code_script.txt | sed 's/\s*build\///g; s/\.o(\..*)/\.asm/g')
C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
C_O_FILES := $(C_FILES:src/%.c=build/src/%.o)
S_O_FILES := $(S_FILES:asm/%.asm=build/asm/%.o)
O_FILES := $(C_O_FILES) $(S_O_FILES)
ROM_FILES := $(shell cat ./tables/makerom_files.txt)
UNCOMPRESSED_ROM_FILES := $(shell cat ./tables/makerom_uncompressed_files.txt)

# create build directories
$(shell mkdir -p build/asm build/asm/boot build/asm/code build/asm/overlays build/baserom build/comp build/decomp $(foreach dir,$(SRC_DIRS),$(shell mkdir -p build/$(dir))))

build/src/libultra/os/%: OPTFLAGS := -O1
build/src/libultra/io/%: OPTFLAGS := -O2
build/src/libultra/libc/%: OPTFLAGS := -O2
build/src/libultra/libc/ll%: OPTFLAGS := -O1
build/src/libultra/libc/ll%: MIPS_VERSION := -mips3 -32
build/src/libultra/gu/%: OPTFLAGS := -O2
build/src/libultra/rmon/%: OPTFLAGS := -O2
build/src/boot_O1/%: OPTFLAGS := -O1
build/src/boot_O2/%: OPTFLAGS := -O2
build/src/boot_O2_g3/%: OPTFLAGS := -O2 -g3
build/src/boot_O2_g3_trapuv/%: OPTFLAGS := -O2 -g3
build/src/boot_O2_g3_trapuv/%: CFLAGS := $(CFLAGS) -trapuv

build/src/libultra/%: CC := $(CC_OLD)
build/src/libultra/io/%: CC := ./tools/preprocess.py $(CC_OLD) -- $(AS) $(ASFLAGS) --

CC := ./tools/preprocess.py $(CC) -- $(AS) $(ASFLAGS) --

.PHONY: all clean setup diff-init init
# disasm is not a file so we must tell make not to check it when evaluating timestamps
.INTERMEDIATE: disasm
# make will delete any generated assembly files that are not a prerequisite for anything, so keep it from doing so
.PRECIOUS: asm/%.asm

$(UNCOMPRESSED_ROM): $(UNCOMPRESSED_ROM_FILES)
	./tools/makerom.py ./tables/dmadata_table.txt $@
ifeq ($(COMPARE),1)
	@md5sum $(UNCOMPRESSED_ROM)
	@md5sum -c checksum_uncompressed.md5
endif

$(ROM): $(ROM_FILES)
	./tools/makerom.py ./tables/dmadata_table.txt $@ -c
ifeq ($(COMPARE),1)
	@md5sum $(ROM)
	@md5sum -c checksum.md5
endif

all:
	$(MAKE) $(UNCOMPRESSED_ROM)
	$(MAKE) $(ROM)

build/code.elf: $(O_FILES) linker_scripts/code_script.txt undef.txt linker_scripts/object_script.txt linker_scripts/dmadata_script.txt
	$(LD) -T linker_scripts/code_script.txt -T undef.txt -T linker_scripts/object_script.txt -T linker_scripts/dmadata_script.txt --no-check-sections --accept-unknown-input-arch -Map build/mm.map -N -o $@

build/code_pre_dmadata.elf: $(O_FILES) linker_scripts/code_script.txt undef.txt linker_scripts/object_script.txt
	$(LD) -r -T linker_scripts/code_script.txt -T undef.txt -T linker_scripts/object_script.txt --no-check-sections --accept-unknown-input-arch -N -o $@

linker_scripts/dmadata_script.txt: $(DMADATA_FILES) build/code_pre_dmadata.elf
	./tools/dmadata.py ./tables/dmadata_table.txt /dev/null -u -l linker_scripts/dmadata_script.txt -e build/code_pre_dmadata.elf

build/dmadata: $(COMP_FILES) $(DECOMP_FILES) $(BASEROM_BUILD_FILES)
	./tools/dmadata.py ./tables/dmadata_table.txt $@

build/uncompressed_dmadata: $(DECOMP_FILES) $(BASEROM_BUILD_FILES)
	./tools/dmadata.py ./tables/dmadata_table.txt $@ -u

build/baserom/boot: build/boot.bin
	cp $< $@

build/decomp/code: build/code.bin
	cp $< $@

build/decomp/ovl_%: build/code.elf
	@$(OBJCOPY) --dump-section ovl_$*=$@ $< /dev/null

asm/non_matchings/%: asm/%.asm
	@./tools/split_asm.py $< $@

asm/%.asm: disasm ;

disasm: tables/files.txt tables/functions.txt tables/objects.txt tables/variables.txt tables/vrom_variables.txt tables/pre_boot_variables.txt
	./tools/disasm.py -d ./asm -u . -l ./tables/files.txt -f ./tables/functions.txt -o ./tables/objects.txt -v ./tables/variables.txt -v ./tables/vrom_variables.txt -v ./tables/pre_boot_variables.txt

clean:
	rm -f $(ROM) $(UNCOMPRESSED_ROM) -r build asm

setup:
	git submodule update --init --recursive
	python3 -m pip install -r requirements.txt
	$(MAKE) -C tools
	./tools/extract_rom.py $(MM_BASEROM)

diff-init: all
	rm -rf expected/
	mkdir -p expected/
	cp -r build expected/build
	cp $(UNCOMPRESSED_ROM) expected/$(UNCOMPRESSED_ROM)
	cp $(ROM) expected/$(ROM)

init:
	$(MAKE) clean
	$(MAKE) setup
	$(MAKE) all
	$(MAKE) diff-init

# Recipes

build/%.bin: build/code.elf
	@$(OBJCOPY) --dump-section $*=$@ $< /dev/null

build/baserom/%: baserom/%
	@cp $< $@

# FIXME: The process of splitting rodata changes the assembly files, so we must avoid making .o files for them until that is done.
# The simplest way to do that is to give them an order dependency on .c files' .o files
build/asm/%.o: asm/%.asm | $(C_O_FILES)
	$(AS) $(ASFLAGS) $^ -o $@

build/asm/%.rodata.o: asm/%.rodata.asm
	iconv --from UTF-8 --to EUC-JP $^ | $(AS) $(ASFLAGS) -o $@

build/src/overlays/%.o: src/overlays/%.c
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<
	@./tools/overlay.py $@ build/src/overlays/$*_overlay.s
	@$(AS) $(ASFLAGS) build/src/overlays/$*_overlay.s -o build/src/overlays/$*_overlay.o

build/src/%.o: src/%.c
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<

build/src/libultra/libc/ll.o: src/libultra/libc/ll.c
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<
	@./tools/set_o32abi_bit.py $@

build/src/libultra/libc/llcvt.o: src/libultra/libc/llcvt.c
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<
	@./tools/set_o32abi_bit.py $@

build/decomp/%: decomp/%
	@cp $< $@

build/comp/%.yaz0: build/decomp/%
	./tools/yaz0 $< $@

build/src/%.d: src/%.c
	@./tools/depend.py $< $@
	@$(GCC) $< -Iinclude -MM -MT 'build/src/$*.o' >> $@

ifneq ($(MAKECMDGOALS), clean)
include $(C_FILES:src/%.c=build/src/%.d)
endif
