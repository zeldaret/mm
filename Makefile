# Build options can be changed by modifying the makefile or by building with 'make SETTING=value'.
# It is also possible to override the settings in Defaults in a file called .make_options as 'SETTING=value'.

-include .make_options

MAKEFLAGS += --no-builtin-rules

# Ensure the build fails if a piped command fails
SHELL = /bin/bash
.SHELLFLAGS = -o pipefail -c

# OS Detection
ifeq ($(OS),Windows_NT)
  DETECTED_OS = windows
  MAKE = make
  VENV_BIN_DIR = Scripts
else
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
    DETECTED_OS = linux
    MAKE = make
    VENV_BIN_DIR = bin
  endif
  ifeq ($(UNAME_S),Darwin)
    DETECTED_OS = macos
    MAKE = gmake
    VENV_BIN_DIR = bin
  endif
endif


#### Defaults ####

# Target game version. Currently only the following version is supported:
#   n64-us   N64 USA (default)
VERSION ?= n64-us
# If COMPARE is 1, check the output md5sum after building
COMPARE ?= 1
# If NON_MATCHING is 1, define the NON_MATCHING C flag when building
NON_MATCHING ?= 0
# If ORIG_COMPILER is 1, compile with QEMU_IRIX and the original compiler
ORIG_COMPILER ?= 0
# if WERROR is 1, pass -Werror to CC_CHECK, so warnings would be treated as errors
WERROR ?= 0
# Keep .mdebug section in build
KEEP_MDEBUG ?= 0
# Disassembles all asm from the ROM instead of skipping files which are entirely in C
FULL_DISASM ?= 0
# Check code syntax with host compiler
RUN_CC_CHECK ?= 1
CC_CHECK_COMP ?= gcc
# Dump build object files
OBJDUMP_BUILD ?= 0
# Force asm processor to run on every file
ASM_PROC_FORCE ?= 0
# Number of threads to disassmble, extract, and compress with
N_THREADS ?= $(shell nproc)
# MIPS toolchain prefix
MIPS_BINUTILS_PREFIX ?= mips-linux-gnu-
# Python virtual environment
VENV ?= .venv
# Python interpreter
PYTHON ?= $(VENV)/$(VENV_BIN_DIR)/python3
# Emulator w/ flags
N64_EMULATOR ?=


#### Setup ####

# Ensure the map file being created using English localization
export LANG := C

ifneq ($(NON_MATCHING),0)
  CFLAGS := -DNON_MATCHING
  CPPFLAGS := -DNON_MATCHING
  COMPARE := 0
endif

DISASM_FLAGS := --reg-names=o32
ifneq ($(FULL_DISASM), 0)
  DISASM_FLAGS += --all
endif

PROJECT_DIR   := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

BASEROM_DIR   := baseroms/$(VERSION)
BUILD_DIR     := build/$(VERSION)
EXTRACTED_DIR := extracted/$(VERSION)


#### Tools ####
ifneq ($(shell type $(MIPS_BINUTILS_PREFIX)ld >/dev/null 2>/dev/null; echo $$?), 0)
  $(error Unable to find $(MIPS_BINUTILS_PREFIX)ld. Please install or build MIPS binutils, commonly mips-linux-gnu. (or set MIPS_BINUTILS_PREFIX if your MIPS binutils install uses another prefix))
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

AS      := $(MIPS_BINUTILS_PREFIX)as
LD      := $(MIPS_BINUTILS_PREFIX)ld
NM      := $(MIPS_BINUTILS_PREFIX)nm
OBJCOPY := $(MIPS_BINUTILS_PREFIX)objcopy
OBJDUMP := $(MIPS_BINUTILS_PREFIX)objdump

IINC := -Iinclude -Iinclude/libc -Isrc -Iassets -I$(BUILD_DIR) -I.

ifeq ($(KEEP_MDEBUG),0)
  RM_MDEBUG = $(OBJCOPY) --remove-section .mdebug $@
else
  RM_MDEBUG = @:
endif

# Check code syntax with host compiler
CC_CHECK_WARNINGS := -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-parameter -Wno-unused-variable -Wno-missing-braces -Wno-unused-but-set-variable -Wno-unused-label -Wno-sign-compare -Wno-tautological-compare
# Have CC_CHECK pretend to be a MIPS compiler
MIPS_BUILTIN_DEFS := -DMIPSEB -D_MIPS_FPSET=16 -D_MIPS_ISA=2 -D_ABIO32=1 -D_MIPS_SIM=_ABIO32 -D_MIPS_SZINT=32 -D_MIPS_SZPTR=32
# The -MMD flags additionaly creates a .d file with the same name as the .o file.
CC_CHECK_FLAGS   := -MMD -MP -fno-builtin -fsyntax-only -funsigned-char -fdiagnostics-color -std=gnu89 -m32 -DNON_MATCHING -DAVOID_UB -DCC_CHECK=1

ifneq ($(WERROR), 0)
  CC_CHECK_WARNINGS += -Werror
endif

ifeq ($(RUN_CC_CHECK),0)
  CC_CHECK_COMP    := @:
endif

# The `cpp` command behaves differently on macOS (it behaves as if
# `-traditional-cpp` was passed) so we use `gcc -E` instead.
CPP           := gcc -E
CPPFLAGS      += -P -xc -fno-dollars-in-identifiers

MKLDSCRIPT    := tools/buildtools/mkldscript
MKDMADATA     := tools/buildtools/mkdmadata
ZAPD          := tools/ZAPD/ZAPD.out
FADO          := tools/fado/fado.elf
MAKEYAR       := $(PYTHON) tools/buildtools/makeyar.py
CHECKSUMMER   := $(PYTHON) tools/buildtools/checksummer.py
SHIFTJIS_CONV := $(PYTHON) tools/buildtools/shiftjis_conv.py

ASM_PROC       := $(PYTHON) tools/asm-processor/build.py
ASM_PROC_FLAGS := --input-enc=utf-8 --output-enc=euc-jp --convert-statics=global-with-filename --encode-cutscene-data-floats
ifneq ($(ASM_PROC_FORCE), 0)
  ASM_PROC_FLAGS += --force
endif

SCHC        := $(PYTHON) tools/buildtools/schc.py
SCHC_FLAGS  :=

# Command to replace path variables in the spec file. We can't use the C
# preprocessor for this because it won't substitute inside string literals.
SPEC_REPLACE_VARS := sed -e 's|$$(BUILD_DIR)|$(BUILD_DIR)|g'

CFLAGS           += -G 0 -non_shared -Xcpluscomm -nostdinc -Wab,-r4300_mul

WARNINGS         := -fullwarn -verbose -woff 624,649,838,712,516,513,596,564,594
ASFLAGS          := -march=vr4300 -32 -G0
COMMON_DEFINES   := -D_MIPS_SZLONG=32
AS_DEFINES       := $(COMMON_DEFINES) -DMIPSEB -D_LANGUAGE_ASSEMBLY -D_ULTRA64
C_DEFINES        := $(COMMON_DEFINES) -DLANGUAGE_C -D_LANGUAGE_C
ENDIAN           := -EB

OPTFLAGS := -O2 -g3
MIPS_VERSION := -mips2

# Use relocations and abi fpr names in the dump
OBJDUMP_FLAGS := --disassemble --reloc --disassemble-zeroes -Mreg-names=32

ifneq ($(OBJDUMP_BUILD), 0)
  OBJDUMP_CMD = $(OBJDUMP) $(OBJDUMP_FLAGS) $@ > $(@:.o=.s)
  OBJCOPY_BIN = $(OBJCOPY) -O binary $@ $@.bin
else
  OBJDUMP_CMD = @:
  OBJCOPY_BIN = @:
endif

ifeq ($(shell getconf LONG_BIT), 32)
  # Work around memory allocation bug in QEMU
  export QEMU_GUEST_BASE := 1
endif


#### Files ####

# ROM image
ROM      := $(BUILD_DIR)/mm-$(VERSION).z64
ROMC     := $(ROM:.z64=-compressed.z64)
ELF      := $(ROM:.z64=.elf)
MAP      := $(ROM:.z64=.map)
LDSCRIPT := $(ROM:.z64=.ld)
# description of ROM segments
SPEC := spec

# create asm directories
$(shell mkdir -p asm data extracted)

SRC_DIRS := $(shell find src -type d)
ASM_DIRS := $(shell find asm -type d -not -path "asm/non_matchings*") $(shell find data -type d)

## Assets binaries (PNGs, JPGs, etc)
ASSET_BIN_DIRS := $(shell find assets/* -type d -not -path "assets/xml*" -not -path "assets/c/*" -not -name "c" -not -path "assets/text")
# Prevents building C files that will be #include'd
ASSET_BIN_DIRS_C_FILES := $(shell find assets/* -type d -not -path "assets/xml*" -not -path "assets/code*" -not -path "assets/overlays*")


ASSET_FILES_BIN := $(foreach dir,$(ASSET_BIN_DIRS),$(wildcard $(dir)/*.bin))
ASSET_FILES_OUT := $(foreach f,$(ASSET_FILES_BIN:.bin=.bin.inc.c),$(BUILD_DIR)/$f)

TEXTURE_FILES_PNG := $(foreach dir,$(ASSET_BIN_DIRS),$(wildcard $(dir)/*.png))
TEXTURE_FILES_JPG := $(foreach dir,$(ASSET_BIN_DIRS),$(wildcard $(dir)/*.jpg))
TEXTURE_FILES_OUT := $(foreach f,$(TEXTURE_FILES_PNG:.png=.inc.c),$(BUILD_DIR)/$f) \
                     $(foreach f,$(TEXTURE_FILES_JPG:.jpg=.jpg.inc.c),$(BUILD_DIR)/$f) \

C_FILES        := $(foreach dir,$(SRC_DIRS) $(ASSET_BIN_DIRS_C_FILES),$(wildcard $(dir)/*.c))
S_FILES        := $(shell grep -F "\$$(BUILD_DIR)/asm" spec | sed 's/.*$$(BUILD_DIR)\/// ; s/\.o\".*/.s/') \
                  $(shell grep -F "\$$(BUILD_DIR)/data" spec | sed 's/.*$$(BUILD_DIR)\/// ; s/\.o\".*/.s/')
SCHEDULE_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.schl))
BASEROM_FILES  := $(shell grep -F "\$$(BUILD_DIR)/baserom" spec | sed 's/.*$$(BUILD_DIR)\/// ; s/\.o\".*//')
ARCHIVES_O     := $(shell grep -F ".yar.o" spec | sed 's/.*include "// ; s/.*$$(BUILD_DIR)\/// ; s/\.o\".*/.o/')
O_FILES        := $(foreach f,$(S_FILES:.s=.o),$(BUILD_DIR)/$f) \
                  $(foreach f,$(C_FILES:.c=.o),$(BUILD_DIR)/$f) \
                  $(foreach f,$(BASEROM_FILES),$(BUILD_DIR)/$f.o) \
                  $(foreach f,$(ARCHIVES_O),$(BUILD_DIR)/$f)

SHIFTJIS_C_FILES := src/libultra/voice/voicecheckword.c src/audio/voice_external.c src/code/z_message.c src/code/z_message_nes.c
SHIFTJIS_O_FILES := $(foreach f,$(SHIFTJIS_C_FILES:.c=.o),$(BUILD_DIR)/$f)

OVL_RELOC_FILES := $(shell $(CPP) $(CPPFLAGS) $(SPEC) | $(SPEC_REPLACE_VARS) | grep -o '[^"]*_reloc.o' )

SCHEDULE_INC_FILES := $(foreach f,$(SCHEDULE_FILES:.schl=.schl.inc),$(BUILD_DIR)/$f)

LD_FILES := $(foreach f,$(shell find linker_scripts/*.ld),$(BUILD_DIR)/$f)

# Automatic dependency files
# (Only asm_processor dependencies and reloc dependencies are handled for now)
DEP_FILES := $(O_FILES:.o=.asmproc.d) $(OVL_RELOC_FILES:.o=.d)

# Other directories that need to be created in the build directory
OTHER_DIRS := baserom dmadata linker_scripts

# create build directories
$(shell mkdir -p $(foreach dir,$(SRC_DIRS) $(ASM_DIRS) $(ASSET_BIN_DIRS) $(ASSET_BIN_DIRS_C_FILES) $(OTHER_DIRS),$(BUILD_DIR)/$(dir)))

# directory flags
$(BUILD_DIR)/src/libultra/os/%.o: OPTFLAGS := -O1
$(BUILD_DIR)/src/libultra/voice/%.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/io/%.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/libc/%.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/gu/%.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/rmon/%.o: OPTFLAGS := -O2

$(BUILD_DIR)/src/boot/O2/%.o: OPTFLAGS := -O2

$(BUILD_DIR)/src/boot/libc/%.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/boot/libm/%.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/boot/libc64/%.o: OPTFLAGS := -O2

$(BUILD_DIR)/src/audio/%.o: OPTFLAGS := -O2

$(BUILD_DIR)/assets/%.o: OPTFLAGS := -O1
$(BUILD_DIR)/assets/%.o: ASM_PROC_FLAGS := 

# file flags
$(BUILD_DIR)/src/libultra/libc/ll.o: OPTFLAGS := -O1
$(BUILD_DIR)/src/libultra/libc/ll.o: MIPS_VERSION := -mips3 -32
$(BUILD_DIR)/src/libultra/libc/llcvt.o: OPTFLAGS := -O1
$(BUILD_DIR)/src/libultra/libc/llcvt.o: MIPS_VERSION := -mips3 -32

$(BUILD_DIR)/src/boot/fault.o: CFLAGS += -trapuv
$(BUILD_DIR)/src/boot/fault_drawer.o: CFLAGS += -trapuv

$(BUILD_DIR)/src/code/jpegdecoder.o: CC := $(CC_OLD)
$(BUILD_DIR)/src/code/jpegdecoder.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/code/jpegutils.o: CC := $(CC_OLD)
$(BUILD_DIR)/src/code/jpegutils.o: OPTFLAGS := -O2

$(BUILD_DIR)/src/code/osFlash.o: CC := $(CC_OLD)
$(BUILD_DIR)/src/code/osFlash.o: OPTFLAGS := -g
$(BUILD_DIR)/src/code/osFlash.o: MIPS_VERSION := -mips1

# cc & asm-processor
$(BUILD_DIR)/src/libultra/%.o: CC := $(CC_OLD)

$(BUILD_DIR)/src/boot/%.o: CC := $(ASM_PROC) $(ASM_PROC_FLAGS) $(CC) -- $(AS) $(ASFLAGS) --

$(BUILD_DIR)/src/code/%.o: CC := $(ASM_PROC) $(ASM_PROC_FLAGS) $(CC) -- $(AS) $(ASFLAGS) --
$(BUILD_DIR)/src/audio/%.o: CC := $(ASM_PROC) $(ASM_PROC_FLAGS) $(CC) -- $(AS) $(ASFLAGS) --

$(BUILD_DIR)/src/overlays/%.o: CC := $(ASM_PROC) $(ASM_PROC_FLAGS) $(CC) -- $(AS) $(ASFLAGS) --

$(BUILD_DIR)/assets/%.o: CC := $(ASM_PROC) $(ASM_PROC_FLAGS) $(CC) -- $(AS) $(ASFLAGS) --


$(SHIFTJIS_O_FILES): CC_CHECK_WARNINGS += -Wno-multichar -Wno-type-limits -Wno-overflow

#### Main Targets ###

rom: $(ROM)
ifneq ($(COMPARE),0)
	@md5sum $(ROM)
	@md5sum -c $(BASEROM_DIR)/checksum.md5
endif

compress: $(ROMC)
ifneq ($(COMPARE),0)
	@md5sum $(ROMC)
	@md5sum -c $(BASEROM_DIR)/checksum-compressed.md5
endif


$(ROM): $(ELF)
	$(OBJCOPY) --gap-fill=0x00 -O binary $< $@
	$(CHECKSUMMER) $@

$(ROMC): $(ROM) $(ELF) $(BUILD_DIR)/dmadata/compress_ranges.txt
	$(PYTHON) tools/buildtools/compress.py --in $(ROM) --out $@ --dma-start `tools/buildtools/dmadata_start.sh $(NM) $(ELF)` --compress `cat $(BUILD_DIR)/dmadata/compress_ranges.txt` --threads $(N_THREADS)
	$(PYTHON) -m ipl3checksum sum --cic 6105 --update $@

$(ELF): $(TEXTURE_FILES_OUT) $(ASSET_FILES_OUT) $(O_FILES) $(OVL_RELOC_FILES) $(LDSCRIPT) $(LD_FILES)
	$(LD) -T $(LDSCRIPT) -T $(LD_FILES) --no-check-sections --accept-unknown-input-arch --emit-relocs -Map $(MAP) -o $@

## Order-only prerequisites 
# These ensure e.g. the O_FILES are built before the OVL_RELOC_FILES.
# The intermediate phony targets avoid quadratically-many dependencies between the targets and prerequisites.

o_files: $(O_FILES)
$(OVL_RELOC_FILES): | o_files

asset_files: $(TEXTURE_FILES_OUT) $(ASSET_FILES_OUT)
$(O_FILES): | asset_files

schedule_inc_files: $(SCHEDULE_INC_FILES)
$(O_FILES): | schedule_inc_files

.PHONY: o_files asset_files schedule_inc_files


#### Main commands ####

## Cleaning ##
clean:
	$(RM) -r $(BUILD_DIR)

assetclean:
	$(RM) -r $(ASSET_BIN_DIRS)
	$(RM) -r $(BUILD_DIR)/assets
	$(RM) -r assets/text/*.h
	$(RM) -r .extracted-assets.json

distclean: assetclean clean
	$(RM) -r asm data extracted
	$(MAKE) -C tools clean

venv:
	test -d $(VENV) || python3 -m venv $(VENV) || { rm -rf $(VENV); false; }
	$(PYTHON) -m pip install -U pip
	$(PYTHON) -m pip install -U -r requirements.txt

## Extraction step
setup:
	$(MAKE) -C tools
	$(PYTHON) tools/buildtools/decompress_baserom.py $(VERSION)
	$(PYTHON) tools/buildtools/extract_baserom.py $(BASEROM_DIR)/baserom-decompressed.z64 -o $(EXTRACTED_DIR)/baserom --dmadata-start `cat $(BASEROM_DIR)/dmadata_start.txt` --dmadata-names $(BASEROM_DIR)/dmadata_names.txt
	$(PYTHON) tools/buildtools/extract_yars.py $(VERSION)

assets:
	$(PYTHON) extract_assets.py -j $(N_THREADS) -Z Wno-hardcoded-pointer

## Assembly generation
disasm:
	$(RM) -r asm data
	$(PYTHON) tools/disasm/disasm.py -j $(N_THREADS) $(DISASM_FLAGS)

diff-init: rom
	$(RM) -r expected/
	mkdir -p expected/
	cp -r build expected/build

init: distclean
	$(MAKE) venv
	$(MAKE) setup
	$(MAKE) assets
	$(MAKE) disasm
	$(MAKE) all
	$(MAKE) diff-init

run: $(ROM)
ifeq ($(N64_EMULATOR),)
	$(error Emulator path not set. Set N64_EMULATOR in the Makefile, .make_options, or define it as an environment variable)
endif
	$(N64_EMULATOR) $<

.PHONY: all rom compress clean assetclean distclean assets disasm init venv setup run
.DEFAULT_GOAL := rom
all: rom compress


#### Various Recipes ####

$(BUILD_DIR)/%.ld: %.ld
	$(CPP) $(CPPFLAGS) $(IINC) $< > $@

$(BUILD_DIR)/$(SPEC): $(SPEC)
	$(CPP) $(CPPFLAGS) $< | $(SPEC_REPLACE_VARS) > $@

$(LDSCRIPT): $(BUILD_DIR)/$(SPEC)
	$(MKLDSCRIPT) $< $@

$(BUILD_DIR)/dmadata/dmadata_table_spec.h $(BUILD_DIR)/dmadata/compress_ranges.txt &: $(BUILD_DIR)/$(SPEC)
	$(MKDMADATA) $< $(BUILD_DIR)/dmadata/dmadata_table_spec.h $(BUILD_DIR)/dmadata/compress_ranges.txt

# Dependencies for files that may include the dmadata header automatically generated from the spec file
$(BUILD_DIR)/src/boot/z_std_dma.o: $(BUILD_DIR)/dmadata/dmadata_table_spec.h
$(BUILD_DIR)/src/dmadata/dmadata.o: $(BUILD_DIR)/dmadata/dmadata_table_spec.h

$(BUILD_DIR)/%.o: %.s
	$(CPP) $(CPPFLAGS) $(IINC) $< | $(AS) $(ASFLAGS) $(IINC) $(ENDIAN) -o $@

$(BUILD_DIR)/assets/%.o: assets/%.c
	$(CC) -c $(CFLAGS) $(IINC) $(WARNINGS) $(C_DEFINES) $(MIPS_VERSION) $(ENDIAN) $(OPTFLAGS) -o $@ $<
	$(OBJCOPY_BIN)
	$(RM_MDEBUG)

$(BUILD_DIR)/%.yar.o: $(BUILD_DIR)/%.o
	$(MAKEYAR) $< $(@:.yar.o=.yar.bin) $(@:.yar.o=.symbols.o)
	$(OBJCOPY) -I binary -O elf32-big $(@:.yar.o=.yar.bin) $@

$(BUILD_DIR)/baserom/%.o: $(EXTRACTED_DIR)/baserom/%
	$(OBJCOPY) -I binary -O elf32-big $< $@

$(BUILD_DIR)/assets/text/message_data.enc.h: assets/text/message_data.h
	$(PYTHON) tools/msg/nes/msgencNES.py -o $@ $<

$(BUILD_DIR)/assets/text/staff_message_data.enc.h: assets/text/staff_message_data.h
	$(PYTHON) tools/msg/staff/msgencStaff.py -o $@ $<

$(BUILD_DIR)/assets/text/message_data_static.o: $(BUILD_DIR)/assets/text/message_data.enc.h
$(BUILD_DIR)/assets/text/staff_message_data_static.o: $(BUILD_DIR)/assets/text/staff_message_data.enc.h
$(BUILD_DIR)/src/code/z_message.o: $(BUILD_DIR)/assets/text/message_data.enc.h $(BUILD_DIR)/assets/text/staff_message_data.enc.h

$(BUILD_DIR)/src/overlays/%_reloc.o: $(BUILD_DIR)/$(SPEC)
	$(FADO) $$(tools/buildtools/reloc_prereq $< $(*F)) -n $(*F) -o $(@:.o=.s) -M $(@:.o=.d)
	$(AS) $(ASFLAGS) $(ENDIAN) $(IINC) $(@:.o=.s) -o $@

$(SHIFTJIS_O_FILES): $(BUILD_DIR)/src/%.o: src/%.c
	$(SHIFTJIS_CONV) -o $(@:.o=.enc.c) $<
	$(CC_CHECK_COMP) $(CC_CHECK_FLAGS) $(IINC) $(CC_CHECK_WARNINGS) $(C_DEFINES) $(MIPS_BUILTIN_DEFS) -o $@ $(@:.o=.enc.c)
	$(CC) -c $(CFLAGS) $(IINC) $(WARNINGS) $(C_DEFINES) $(MIPS_VERSION) $(ENDIAN) $(OPTFLAGS) -o $@ $(@:.o=.enc.c)
	$(OBJDUMP_CMD)
	$(RM_MDEBUG)

$(BUILD_DIR)/src/libultra/libc/ll.o: src/libultra/libc/ll.c
	$(CC_CHECK_COMP) $(CC_CHECK_FLAGS) $(IINC) $(CC_CHECK_WARNINGS) $(C_DEFINES) $(MIPS_BUILTIN_DEFS) -o $@ $<
	$(CC) -c $(CFLAGS) $(IINC) $(WARNINGS) $(C_DEFINES) $(MIPS_VERSION) $(ENDIAN) $(OPTFLAGS) -o $@ $<
	$(PYTHON) tools/set_o32abi_bit.py $@
	$(OBJDUMP_CMD)
	$(RM_MDEBUG)

$(BUILD_DIR)/src/libultra/libc/llcvt.o: src/libultra/libc/llcvt.c
	$(CC_CHECK_COMP) $(CC_CHECK_FLAGS) $(IINC) $(CC_CHECK_WARNINGS) $(C_DEFINES) $(MIPS_BUILTIN_DEFS) -o $@ $<
	$(CC) -c $(CFLAGS) $(IINC) $(WARNINGS) $(C_DEFINES) $(MIPS_VERSION) $(ENDIAN) $(OPTFLAGS) -o $@ $<
	$(PYTHON) tools/set_o32abi_bit.py $@
	$(OBJDUMP_CMD)
	$(RM_MDEBUG)

$(BUILD_DIR)/%.o: %.c
	$(CC_CHECK_COMP) $(CC_CHECK_FLAGS) $(IINC) $(CC_CHECK_WARNINGS) $(C_DEFINES) $(MIPS_BUILTIN_DEFS) -o $@ $<
	$(CC) -c $(CFLAGS) $(IINC) $(WARNINGS) $(C_DEFINES) $(MIPS_VERSION) $(ENDIAN) $(OPTFLAGS) -o $@ $<
	$(OBJDUMP_CMD)
	$(RM_MDEBUG)

# Build C files from assets

$(BUILD_DIR)/%.inc.c: %.png
	$(ZAPD) btex -eh -tt $(subst .,,$(suffix $*)) -i $< -o $@

$(BUILD_DIR)/assets/%.bin.inc.c: assets/%.bin
	$(ZAPD) bblb -eh -i $< -o $@

$(BUILD_DIR)/assets/%.jpg.inc.c: assets/%.jpg
	$(ZAPD) bren -eh -i $< -o $@

$(BUILD_DIR)/%.schl.inc: %.schl
	$(SCHC) $(SCHC_FLAGS) -o $@ $<

-include $(DEP_FILES)

# Print target for debugging
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
