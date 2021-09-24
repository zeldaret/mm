MAKEFLAGS += --no-builtin-rules

# Build options can either be changed by modifying the makefile, or by building with 'make SETTING=value'

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

PROJECT_DIR := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

MAKE = make
CPPFLAGS += -P

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

# Threads to compress and extract assets with, TODO improve later
ifeq ($(DETECTED_OS),linux)
  N_THREADS ?= $(shell nproc)
else
  N_THREADS ?= 1
endif

#### Tools ####
ifeq ($(shell command -v mips-linux-gnu-ld >/dev/null 2>&1; echo $$?), 0)
  MIPS_BINUTILS_PREFIX := mips-linux-gnu-
else
  $(error Please install or build mips-linux-gnu)
endif

CC       := tools/ido_recomp/$(DETECTED_OS)/7.1/cc
CC_OLD   := tools/ido_recomp/$(DETECTED_OS)/5.3/cc

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

AS         := $(MIPS_BINUTILS_PREFIX)as
LD         := $(MIPS_BINUTILS_PREFIX)ld
OBJCOPY    := $(MIPS_BINUTILS_PREFIX)objcopy
OBJDUMP    := $(MIPS_BINUTILS_PREFIX)objdump


# Check code syntax with host compiler

ifeq ($(shell command -v clang >/dev/null 2>&1; echo $$?),0)
  CC_CHECK_COMP := clang
else
  CC_CHECK_COMP := gcc
endif

CHECK_WARNINGS_ON  := -Wall -Wextra -Wstrict-prototypes -Wshadow
CHECK_WARNINGS_OFF := -Wno-format-security -Wno-unknown-pragmas -Wno-unused-parameter -Wno-unused-variable -Wno-missing-braces -Wno-int-conversion -Wno-unused-label

ifeq ($(CC_CHECK_COMP),clang)
CHECK_WARNINGS_ON  += -Wpedantic
CHECK_WARNINGS_OFF += -Wno-long-long -Wno-c11-extensions -Wno-c99-extensions -Wno-tautological-overlap-compare -Wno-four-char-constants
else
CHECK_WARNINGS_OFF += -Wno-unused-but-set-variable -Wno-multichar
endif

CHECK_WARNINGS := $(CHECK_WARNINGS_ON) $(CHECK_WARNINGS_OFF)
CC_CHECK := $(CC_CHECK_COMP) -fno-builtin -fsyntax-only -funsigned-char -std=gnu90 -D _LANGUAGE_C -D NON_MATCHING -Iinclude -Isrc -Iassets -Ibuild -include stdarg.h $(CHECK_WARNINGS)

CPP        := cpp
ELF2ROM    := tools/buildtools/elf2rom
MKLDSCRIPT := tools/buildtools/mkldscript
YAZ0       := tools/buildtools/yaz0
ZAPD       := tools/ZAPD/ZAPD.out

OPTFLAGS := -O2 -g3
ASFLAGS := -march=vr4300 -32 -Iinclude
MIPS_VERSION := -mips2

# we support Microsoft extensions such as anonymous structs, which the compiler does support but warns for their usage. Surpress the warnings with -woff.
CFLAGS += -G 0 -non_shared -Xfullwarn -Xcpluscomm -Iinclude -Isrc -Iassets -Ibuild -I. -Wab,-r4300_mul -woff 624,649,838,712

ifeq ($(shell getconf LONG_BIT), 32)
  # Work around memory allocation bug in QEMU
  export QEMU_GUEST_BASE := 1
else
  # Ensure that gcc treats the code as 32-bit
  CC_CHECK += -m32
endif

#### Files ####

# ROM image
ROMC := mm.us.rev1.rom.z64
ROM := $(ROMC:.rom.z64=.rom_uncompressed.z64)
ELF := $(ROM:.z64=.elf)
# description of ROM segments
SPEC := spec

# create asm directories
$(shell mkdir -p asm data)

SRC_DIRS := $(shell find src -type d)
ASM_DIRS := $(shell find asm -type d -not -path "asm/non_matchings*") $(shell find data -type d)
ASSET_BIN_DIRS := $(shell find assets/* -type d -not -path "assets/xml*")
BASEROM_DIRS := $(shell find baserom -type d 2>/dev/null)
ASSET_C_FILES := $(shell find assets/ -type f -name "*.c")
ASSET_FILES_BIN := $(foreach dir,$(ASSET_BIN_DIRS),$(wildcard $(dir)/*.bin))
ASSET_FILES_OUT := $(foreach f,$(ASSET_FILES_BIN:.bin=.bin.inc.c),build/$f)

## Assets binaries (PNGs, JPGs, etc)
TEXTURE_FILES_PNG := $(foreach dir,$(ASSET_BIN_DIRS),$(wildcard $(dir)/*.png))
TEXTURE_FILES_JPG := $(foreach dir,$(ASSET_BIN_DIRS),$(wildcard $(dir)/*.jpg))
TEXTURE_FILES_OUT := $(foreach f,$(TEXTURE_FILES_PNG:.png=.inc.c),build/$f) \
					 $(foreach f,$(TEXTURE_FILES_JPG:.jpg=.jpg.inc.c),build/$f) \

C_FILES       := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
S_FILES       := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))
O_FILES       := $(foreach f,$(S_FILES:.s=.o),build/$f) \
                 $(foreach f,$(wildcard baserom/*),build/$f.o) \
                 $(foreach f,$(C_FILES:.c=.o),build/$f) \
                 $(foreach f,$(ASSET_C_FILES:.c=.o),build/$f)

# Automatic dependency files
# (Only asm_processor dependencies are handled for now)
DEP_FILES := $(O_FILES:.o=.asmproc.d)

# create build directories
$(shell mkdir -p build/baserom $(foreach dir,$(SRC_DIRS) $(ASM_DIRS) $(ASSET_BIN_DIRS),build/$(dir)))

# directory flags
build/src/boot_O2/%.o: OPTFLAGS := -O2
build/src/boot_O2_g3/%.o: OPTFLAGS := -O2 -g3

build/src/libultra/os/%.o: OPTFLAGS := -O1
build/src/libultra/voice/%.o: OPTFLAGS := -O2
build/src/libultra/io/%.o: OPTFLAGS := -O2
build/src/libultra/libc/%.o: OPTFLAGS := -O2
build/src/libultra/gu/%.o: OPTFLAGS := -O2
build/src/libultra/rmon/%.o: OPTFLAGS := -O2

# file flags
build/src/boot_O2_g3/fault.o: CFLAGS += -trapuv
build/src/boot_O2_g3/fault_drawer.o: CFLAGS += -trapuv

build/src/libultra/libc/ll.o: OPTFLAGS := -O1
build/src/libultra/libc/ll.o: MIPS_VERSION := -mips3 -32
build/src/libultra/libc/llcvt.o: OPTFLAGS := -O1
build/src/libultra/libc/llcvt.o: MIPS_VERSION := -mips3 -32

# cc & asm-processor
build/src/boot_O2/%.o: CC := python3 tools/asm-processor/build.py $(CC) -- $(AS) $(ASFLAGS) --
build/src/boot_O2_g3/%.o: CC := python3 tools/asm-processor/build.py $(CC) -- $(AS) $(ASFLAGS) --

build/src/libultra/%.o: CC := python3 tools/asm-processor/build.py $(CC_OLD) -- $(AS) $(ASFLAGS) --

build/src/code/%.o: CC := python3 tools/asm-processor/build.py $(CC) -- $(AS) $(ASFLAGS) --

build/src/overlays/actors/%.o: CC := python3 tools/asm-processor/build.py $(CC) -- $(AS) $(ASFLAGS) --
build/src/overlays/effects/%.o: CC := python3 tools/asm-processor/build.py $(CC) -- $(AS) $(ASFLAGS) --
build/src/overlays/fbdemos/%.o: CC := python3 tools/asm-processor/build.py $(CC) -- $(AS) $(ASFLAGS) --
build/src/overlays/gamestates/%.o: CC := python3 tools/asm-processor/build.py $(CC) -- $(AS) $(ASFLAGS) --
build/src/overlays/kaleido_scope/%.o: CC := python3 tools/asm-processor/build.py $(CC) -- $(AS) $(ASFLAGS) --

#### Main Targets ###

uncompressed: $(ROM)
ifeq ($(COMPARE),1)
	@md5sum $(ROM)
	@md5sum -c checksum_uncompressed.md5
endif

compressed: $(ROMC)
ifeq ($(COMPARE),1)
	@md5sum $(ROMC)
	@md5sum -c checksum.md5
endif

.PHONY: all uncompressed compressed clean assetclean distclean disasm init setup
.DEFAULT_GOAL := uncompressed
all: compressed

$(ROM): $(ELF)
	$(ELF2ROM) -cic 6105 $< $@

$(ROMC): uncompressed
	python3 tools/z64compress_wrapper.py --mb 32 --matching --threads $(N_THREADS) $(ROM) $@ $(ELF) build/$(SPEC)

$(ELF): $(TEXTURE_FILES_OUT) $(OVERLAY_RELOC_FILES) $(O_FILES) build/ldscript.txt build/undefined_syms.txt
	$(LD) -T build/undefined_syms.txt -T build/ldscript.txt --no-check-sections --accept-unknown-input-arch --emit-relocs -Map build/mm.map -o $@


#### Main commands ####

## Cleaning ##
clean:
	$(RM) -rf $(ROMC) $(ROM) $(ELF) build

assetclean:
	$(RM) -rf $(ASSET_BIN_DIRS)
	$(RM) -rf build/assets
	$(RM) -rf .extracted-assets.json

distclean: assetclean clean
	$(RM) -rf asm baserom data
	$(MAKE) -C tools clean

## Extraction step
setup:
	$(MAKE) -C tools
	python3 tools/fixbaserom.py
	python3 tools/extract_baserom.py
	python3 extract_assets.py -t $(N_THREADS)

## Assembly generation
disasm:
	$(RM) -rf asm data
	python3 tools/disasm/disasm.py

diff-init: all
	$(RM) -rf expected/
	mkdir -p expected/
	cp -r build expected/build

init:
	$(MAKE) distclean
	$(MAKE) setup
	$(MAKE) disasm
	$(MAKE) all
	$(MAKE) diff-init

build/assets/%.o: assets/%.c
	$(CC) -I build/ -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<

#### Various Recipes ####

build/undefined_syms.txt: undefined_syms.txt
	$(CPP) $(CPPFLAGS) $< > build/undefined_syms.txt

build/ldscript.txt: $(SPEC)
	$(CPP) $(CPPFLAGS) $< > build/spec
	$(MKLDSCRIPT) build/spec $@

build/baserom/%.o: baserom/%
	$(OBJCOPY) -I binary -O elf32-big $< $@

build/asm/%.o: asm/%.s
	$(AS) $(ASFLAGS) $< -o $@

build/data/%.o: data/%.s
	iconv --from UTF-8 --to EUC-JP $< | $(AS) $(ASFLAGS) -o $@

build/src/overlays/%.o: src/overlays/%.c
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<
	$(CC_CHECK) $<
	@$(OBJDUMP) -d $@ > $(@:.o=.s)
# TODO: `() || true` is currently necessary to suppress `Error 1 (ignored)` make warnings caused by `test`, but this will go away if 
# 	the following is moved to a separate rule that is only run once when all the required objects have been compiled. 
	$(ZAPD) bovl -eh -i $@ -cfg $< --outputpath $(@D)/$(notdir $(@D))_reloc.s
	(test -f $(@D)/$(notdir $(@D))_reloc.s && $(AS) $(ASFLAGS) $(@D)/$(notdir $(@D))_reloc.s -o $(@D)/$(notdir $(@D))_reloc.o) || true

build/src/%.o: src/%.c
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<
	$(CC_CHECK) $<
	@$(OBJDUMP) -d $@ > $(@:.o=.s)

build/src/libultra/libc/ll.o: src/libultra/libc/ll.c
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<
	$(CC_CHECK) $<
	python3 tools/set_o32abi_bit.py $@
	@$(OBJDUMP) -d $@ > $(@:.o=.s)

build/src/libultra/libc/llcvt.o: src/libultra/libc/llcvt.c
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<
	$(CC_CHECK) $<
	python3 tools/set_o32abi_bit.py $@
	@$(OBJDUMP) -d $@ > $(@:.o=.s)

# Build C files from assets
build/%.inc.c: %.png
	$(ZAPD) btex -eh -tt $(lastword ,$(subst ., ,$(basename $<))) -i $< -o $@

build/assets/%.bin.inc.c: assets/%.bin
	$(ZAPD) bblb -eh -i $< -o $@

build/assets/%.jpg.inc.c: assets/%.jpg
	$(ZAPD) bren -eh -i $< -o $@

-include $(DEP_FILES)
