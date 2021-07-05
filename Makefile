MAKEFLAGS += --no-builtin-rules

# If COMPARE is 1, check the output md5sum after building
COMPARE ?= 1
# If NON_MATCHING is 1, define the NON_MATCHING C flag when building
NON_MATCHING ?= 0
# If ORIG_COMPILER is 1, compile with QEMU_IRIX and the original compiler
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

ZAPD := tools/ZAPD/ZAPD.out

OPTFLAGS := -O2 -g3
ASFLAGS := -march=vr4300 -32
MIPS_VERSION := -mips2

# we support Microsoft extensions such as anonymous structs, which the compiler does support but warns for their usage. Surpress the warnings with -woff.
CFLAGS += -G 0 -non_shared -Xfullwarn -Xcpluscomm -Iinclude -Isrc -Iassets -Ibuild -I./ -Isrc -Wab,-r4300_mul -woff 624,649,838,712

#### Files ####

# ROM image
MM_BASEROM ?= baserom.mm.us.rev1.z64
MM_ROM_NAME ?= mm.us.rev1.rom
ROM := $(MM_ROM_NAME).z64
UNCOMPRESSED_ROM := $(MM_ROM_NAME)_uncompressed.z64
ELF := $(MM_ROM_NAME).elf

SRC_DIRS := $(shell find src -type d)
ASSET_BIN_DIRS := $(shell find assets/* -type d -not -path "assets/xml*")
BASEROM_DIRS := $(shell find baserom -type d 2>/dev/null)
COMP_DIRS := $(BASEROM_DIRS:baserom%=comp%)
BINARY_DIRS := $(BASEROM_DIRS:baserom%=binary%)
ASSET_C_FILES := $(shell find assets/ -type f -name "*.c")
ASSET_FILES_BIN := $(foreach dir,$(ASSET_BIN_DIRS),$(wildcard $(dir)/*.bin))
ASSET_FILES_OUT := $(foreach f,$(ASSET_FILES_BIN:.bin=.bin.inc.c),build/$f)

# Because we may not have disassembled the code files yet, there might not be any assembly files.
# Instead, generate a list of assembly files based on what's listed in the linker script.
S_FILES := $(shell grep build/asm ./linker_scripts/code_script.txt | sed 's/\s*build\///g; s/\.o(\..*)/\.asm/g')
C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

C_O_FILES := $(C_FILES:%.c=build/%.o)
S_O_FILES := $(S_FILES:asm/%.asm=build/asm/%.o)
ASSET_O_FILES := $(ASSET_C_FILES:%.c=build/%.o)
O_FILES := $(C_O_FILES) $(S_O_FILES) $(ASSET_O_FILES)

## Assets binaries (PNGs, JPGs, etc)
TEXTURE_FILES_PNG := $(foreach dir,$(ASSET_BIN_DIRS),$(wildcard $(dir)/*.png))
TEXTURE_FILES_JPG := $(foreach dir,$(ASSET_BIN_DIRS),$(wildcard $(dir)/*.jpg))
TEXTURE_FILES_OUT := $(foreach f,$(TEXTURE_FILES_PNG:.png=.inc.c),build/$f) \
					 $(foreach f,$(TEXTURE_FILES_JPG:.jpg=.jpg.inc.c),build/$f) \

# create build directories
$(shell mkdir -p build/linker_scripts build/asm build/asm/boot build/asm/code build/asm/overlays $(foreach dir, $(COMP_DIRS) $(BINARY_DIRS) $(SRC_DIRS) $(ASSET_BIN_DIRS),$(shell mkdir -p build/$(dir))))

# This file defines `ROM_FILES`, `UNCOMPRESSED_ROM_FILES`, and rules for generating `.yaz0` files
ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), distclean)
$(shell tools/dmadata_dependencies.py \
	--dmadata-table=tables/dmadata_table.txt \
	--output-deps=build/rom_dependencies.d)
-include build/rom_dependencies.d
endif
endif

build/src/libultra/os/%: OPTFLAGS := -O1
build/src/libultra/voice/%: OPTFLAGS := -O2
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
build/src/libultra/voice/%: CC := ./tools/preprocess.py $(CC_OLD) -- $(AS) $(ASFLAGS) --

CC := ./tools/preprocess.py $(CC) -- $(AS) $(ASFLAGS) --

.PHONY: all clean setup diff-init init assetclean distclean assembly
# make will delete any generated assembly files that are not a prerequisite for anything, so keep it from doing so
.PRECIOUS: asm/%.asm
.DEFAULT_GOAL := $(UNCOMPRESSED_ROM)

# just using build/baserom still probably has some race condiction/dependency bug, but since
# it is first and should be completed relatively fast, it should not occur all that often.
$(UNCOMPRESSED_ROM): build/baserom $(TEXTURE_FILES_OUT) $(ASSET_FILES_OUT) $(UNCOMPRESSED_ROM_FILES)
	./tools/makerom.py ./tables/dmadata_table.txt $@
ifeq ($(COMPARE),1)
	@md5sum $(UNCOMPRESSED_ROM)
	@md5sum -c checksum_uncompressed.md5
endif

$(ROM): build/baserom $(ROM_FILES)
	./tools/makerom.py ./tables/dmadata_table.txt $@ -c
ifeq ($(COMPARE),1)
	@md5sum $(ROM)
	@md5sum -c checksum.md5
endif

all: $(UNCOMPRESSED_ROM) $(ROM) ;

build/code.elf: $(O_FILES) build/linker_scripts/code_script.ld undef.txt build/linker_scripts/object_script.ld build/dmadata_script.ld
	$(LD) -T build/linker_scripts/code_script.ld -T undef.txt -T build/linker_scripts/object_script.ld -T build/dmadata_script.ld --no-check-sections --accept-unknown-input-arch -Map build/mm.map -N -o $@

build/code_pre_dmadata.elf: $(O_FILES) build/linker_scripts/code_script.ld undef.txt build/linker_scripts/object_script.ld
	$(LD) -r -T build/linker_scripts/code_script.ld -T undef.txt -T build/linker_scripts/object_script.ld --no-check-sections --accept-unknown-input-arch -N -o $@

build/dmadata_script.txt: tables/dmadata_table.txt build/code_pre_dmadata.elf
	./tools/dmadata.py ./tables/dmadata_table.txt /dev/null -u -l $@ -e build/code_pre_dmadata.elf

build/dmadata: $(ROM_FILES:build/dmadata=)
	./tools/dmadata.py ./tables/dmadata_table.txt $@

build/uncompressed_dmadata: $(UNCOMPRESSED_ROM_FILES:build/uncompressed_dmadata=)
	./tools/dmadata.py ./tables/dmadata_table.txt $@ -u

build/binary/boot build/binary/code: build/code.elf
	@$(OBJCOPY) --dump-section $(notdir $@)=$@ $< /dev/null

build/binary/assets/scenes/%: build/code.elf
	@$(OBJCOPY) --dump-section $*=$@ $< /dev/null

build/binary/overlays/%: build/code.elf
	@$(OBJCOPY) --dump-section $*=$@ $< /dev/null


#### ASM rules ####

# Use an empty sentinel file (dep) to track the directory as a dependency, and
# emulate GNU Make's order-only dependency.
# The `touch $@; action || rm $@` pattern ensures that the `dep` file is older
# than the output files from `action`, and only exists if `action` succeeds.
asm/non_matchings/%/dep: asm/%.asm
	@mkdir -p $(dir $@)
	@touch $@
	./tools/split_asm.py $< asm/non_matchings/$* || rm $@

asm/%.asm: asm/disasm.dep ;

asm/disasm.dep: tables/files.txt tables/functions.txt tables/objects.txt tables/variables.txt tables/vrom_variables.txt
	@mkdir -p asm
	@touch $@
	./tools/disasm.py -d ./asm -l ./tables/files.txt -f ./tables/functions.txt -o ./tables/objects.txt -v ./tables/variables.txt -v ./tables/vrom_variables.txt || rm $@


#### Main commands ####

## Cleaning ##
clean:
	$(RM) -rf $(ROM) $(UNCOMPRESSED_ROM) build

assetclean:
	$(RM) -rf $(ASSET_BIN_DIRS)
	$(RM) -rf build/assets

distclean: assetclean clean
	$(RM) -rf baserom/ asm/ expected/
	$(MAKE) -C tools clean

## Extraction step
setup:
	$(MAKE) -C tools
	./tools/extract_rom.py $(MM_BASEROM)
	python3 extract_assets.py

## Assembly generation
assembly: $(S_FILES)
	@echo "Assembly generated."

diff-init: all
	$(RM) -rf expected/
	mkdir -p expected/
	cp -r build expected/build
	cp $(UNCOMPRESSED_ROM) expected/$(UNCOMPRESSED_ROM)
	cp $(ROM) expected/$(ROM)

init:
	$(MAKE) distclean
	$(MAKE) setup
	$(MAKE) assembly
	$(MAKE) all
	$(MAKE) diff-init

# Recipes

build/baserom:
	cp -r baserom/ build/baserom/

# FIXME: The process of splitting rodata changes the assembly files, so we must avoid making .o files for them until that is done.
# The simplest way to do that is to give them an order dependency on .c files' .o files
build/asm/%.o: asm/%.asm | $(C_O_FILES)
	iconv --from UTF-8 --to EUC-JP $^ | $(AS) $(ASFLAGS) -o $@

build/src/overlays/%.o: src/overlays/%.c
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<
	@./tools/overlay.py $@ build/src/overlays/$*_overlay.s
	@$(AS) $(ASFLAGS) build/src/overlays/$*_overlay.s -o build/src/overlays/$*_overlay.o

build/%.o: %.c
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<

build/assets/%.o: assets/%.c
	$(CC) -I build/ -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<

build/src/libultra/libc/ll.o: src/libultra/libc/ll.c
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<
	@./tools/set_o32abi_bit.py $@

build/src/libultra/libc/llcvt.o: src/libultra/libc/llcvt.c
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<
	@./tools/set_o32abi_bit.py $@

build/comp/%.yaz0: build/binary/%
	./tools/yaz0 $< $@

build/comp/assets/audio/%.yaz0: build/baserom/assets/audio/%
	./tools/yaz0 $< $@

build/comp/assets/misc/%.yaz0: build/baserom/assets/misc/%
	./tools/yaz0 $< $@

build/comp/assets/objects/%.yaz0: build/baserom/assets/objects/%
	./tools/yaz0 $< $@

build/comp/assets/textures/%.yaz0: build/baserom/assets/textures/%
	./tools/yaz0 $< $@

build/%.d: %.c
	@./tools/depend.py $< $@
	@$(GCC) $< -Iinclude -Isrc -I./ -MM -MT 'build/$*.o' >> $@

build/dmadata_script.ld: build/dmadata_script.txt
	@$(GCC) -E -CC -x c -Iinclude $< | grep -v '^#' > $@

build/linker_scripts/%.ld: linker_scripts/%.txt
	@$(GCC) -E -CC -x c -Iinclude $< | grep -v '^#' > $@

build/assets/%.d: assets/%.c
	@$(GCC) $< -Iinclude -I./ -MM -MT 'build/assets/$*.o' > $@

## Build C files from assets

build/%.inc.c: %.png
	$(ZAPD) btex -eh -tt $(lastword ,$(subst ., ,$(basename $<))) -i $< -o $@

build/assets/%.bin.inc.c: assets/%.bin
	$(ZAPD) bblb -eh -i $< -o $@

build/assets/%.jpg.inc.c: assets/%.jpg
	$(ZAPD) bren -eh -i $< -o $@

ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), distclean)
-include $(C_FILES:%.c=build/%.d)
endif
endif
