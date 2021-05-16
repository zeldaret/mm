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

#### Tools ####
ifeq ($(shell type mips-linux-gnu-ld >/dev/null 2>/dev/null; echo $$?), 0)
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
CHECK_WARNINGS := -Wall -Wextra -Wno-format-security -Wno-unknown-pragmas -Wno-unused-parameter -Wno-unused-variable -Wno-missing-braces -Wno-int-conversion
CC_CHECK   := gcc -fno-builtin -fsyntax-only -fsigned-char -std=gnu90 -D _LANGUAGE_C -D NON_MATCHING -Iinclude -Isrc -include stdarg.h $(CHECK_WARNINGS)

CPP        := cpp
ELF2ROM    := tools/buildtools/elf2rom
MKLDSCRIPT := tools/buildtools/mkldscript
YAZ0       := tools/buildtools/yaz0
ZAPD       := tools/ZAPD/ZAPD.out

OPTFLAGS := -O2 -g3
ASFLAGS := -march=vr4300 -32 -Iinclude
MIPS_VERSION := -mips2

# we support Microsoft extensions such as anonymous structs, which the compiler does support but warns for their usage. Surpress the warnings with -woff.
CFLAGS += -G 0 -non_shared -Xfullwarn -Xcpluscomm -Iinclude -Isrc -Wab,-r4300_mul -woff 649,838,712

ifeq ($(shell getconf LONG_BIT), 32)
  # Work around memory allocation bug in QEMU
  export QEMU_GUEST_BASE := 1
else
  # Ensure that gcc treats the code as 32-bit
  CC_CHECK += -m32
endif

#### Files ####

# ROM image
ROM := zelda_majora_us.z64
ROMC := $(ROM:.z64=.compressed.z64)
ELF := $(ROM:.z64=.elf)
# description of ROM segments
SPEC := spec

# create asm directories
$(shell mkdir -p asm data)

SRC_DIRS := $(shell find src -type d)
ASM_DIRS := $(shell find asm -type d -not -path "asm/non_matchings*") $(shell find data -type d)
BASEROM_DIRS := $(shell find baserom -type d 2>/dev/null)
ASSET_C_FILES := $(shell find assets/ -type f -name "*.c")

# Because we may not have disassembled the code files yet, there might not be any assembly files.
# Instead, generate a list of assembly files based on what's listed in the linker script.
S_FILES := $(shell grep build/asm ./linker_scripts/code_script.txt | sed 's/\s*build\///g; s/\.o(\..*)/\.asm/g')
C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
C_O_FILES := $(C_FILES:%.c=build/%.o)
S_O_FILES := $(S_FILES:asm/%.asm=build/asm/%.o)
ASSET_O_FILES := $(ASSET_C_FILES:%.c=build/%.o)
O_FILES := $(C_O_FILES) $(S_O_FILES) $(ASSET_O_FILES)

ASSET_BIN_DIRS := $(shell find assets/* -type d -not -path "assets/xml*")

TEXTURE_FILES_PNG := $(foreach dir,$(ASSET_BIN_DIRS),$(wildcard $(dir)/*.png))
TEXTURE_FILES_JPG := $(foreach dir,$(ASSET_BIN_DIRS),$(wildcard $(dir)/*.jpg))
TEXTURE_FILES_OUT := $(foreach f,$(TEXTURE_FILES_PNG:.png=.inc.c),build/$f) \
					 $(foreach f,$(TEXTURE_FILES_JPG:.jpg=.jpg.inc.c),build/$f) \

C_FILES       := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
S_FILES       := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))
O_FILES       := $(foreach f,$(S_FILES:.s=.o),build/$f) \
                 $(foreach f,$(C_FILES:.c=.o),build/$f) \
                 $(foreach f,$(wildcard baserom/*),build/$f.o)
# create build directories
$(shell mkdir -p build/baserom $(foreach dir,$(SRC_DIRS) $(ASM_DIRS),build/$(dir)))

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

CC := ./tools/preprocess.py $(CC) -- $(AS) $(ASFLAGS) --

#### Main Targets ###

uncompressed: $(ROM)
ifeq ($(COMPARE),1)
	@md5sum $(ROM)
	@md5sum -c checksum_uncompressed.md5
endif

compressed: $(ROMC)
ifeq ($(COMPARE),1)
	@md5sum $(ROMC)
	@md5sum -c checksum_compressed.md5
endif

.PHONY: all clean setup diff-init init assetclean distclean
# make will delete any generated assembly files that are not a prerequisite for anything, so keep it from doing so
.PRECIOUS: asm/%.asm
.DEFAULT_GOAL := $(UNCOMPRESSED_ROM)

all: uncompressed compressed

$(ROM): $(ELF)
	$(ELF2ROM) -cic 6105 $< $@

$(ROMC): $(ROM)
	python3 tools/z64compress_wrapper.py --mb 32 --matching --threads $(shell nproc) $< $@ $(ELF) build/$(SPEC)

$(ELF): $(TEXTURE_FILES_OUT) $(O_FILES) build/ldscript.txt build/undefined_syms.txt
	$(LD) -T build/undefined_syms.txt -T build/ldscript.txt --no-check-sections --accept-unknown-input-arch --emit-relocs -Map build/z64.map -o $@

clean:
	$(RM) -r $(ROM) $(ELF) build

distclean:
	$(RM) -r $(ROM) $(ROMC) $(ELF) build asm baserom data
	$(MAKE) -C tools clean

disasm:
	python3 tools/disasm/disasm.py

init:
	git submodule update --init --recursive
	python3 -m pip install -r requirements.txt
	$(MAKE) distclean
	$(MAKE) setup
	$(MAKE) disasm

setup:
	$(MAKE) -C tools
	python3 tools/fixbaserom.py
	python3 tools/extract_baserom.py

build/assets/%.o: assets/%.c
	$(CC) -I build/ -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $<

build/binary/assets/scenes/%: build/code.elf
	@$(OBJCOPY) --dump-section $*=$@ $< /dev/null

.PHONY: all uncompressed compressed clean distclean disasm init setup

#### Various Recipes ####

build/undefined_syms.txt: undefined_syms.txt
	$(CPP) $(CPPFLAGS) $< > build/undefined_syms.txt

build/ldscript.txt: $(SPEC)
	$(CPP) $(CPPFLAGS) $< > build/spec
	$(MKLDSCRIPT) build/spec $@

build/baserom/%.o: baserom/%
	$(OBJCOPY) -I binary -O elf32-big $< $@

build/asm/%.o: asm/%.s
	$(AS) $(ASFLAGS) $^ -o $@

build/data/%.o: data/%.s
	iconv --from UTF-8 --to EUC-JP $^ | $(AS) $(ASFLAGS) -o $@

# Build C files from assets
build/%.inc.c: %.png
	$(ZAPD) btex -eh -tt $(lastword ,$(subst ., ,$(basename $<))) -i $< -o $@

build/assets/%.jpg.inc.c: assets/%.jpg
	$(ZAPD) bren -eh -i $< -o $@

build/src/overlays/%.o: src/overlays/%.c
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $^
#	$(CC_CHECK) $^
	$(ZAPD) bovl -i $@ -cfg $^ --outputpath $(@D)/$(notdir $(@D))_reloc.s
	-test -f $(@D)/$(notdir $(@D))_reloc.s && $(AS) $(ASFLAGS) $(@D)/$(notdir $(@D))_reloc.s -o $(@D)/$(notdir $(@D))_reloc.o
	@$(OBJDUMP) -d $@ > $(@:.o=.s)

build/src/%.o: src/%.c
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTFLAGS) -o $@ $^
#	$(CC_CHECK) $^
	@$(OBJDUMP) -d $@ > $(@:.o=.s)
