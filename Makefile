# TODO think about how to split this up

#### Tools ####
ifeq ($(shell type mips-linux-gnu-ld >/dev/null 2>/dev/null; echo $$?), 0)
  MIPS_BINUTILS_PREFIX := mips-linux-gnu-
else
  MIPS_BINUTILS_PREFIX := mips64-elf-
endif

AS := $(MIPS_BINUTILS_PREFIX)as
LD := $(MIPS_BINUTILS_PREFIX)ld

QEMU_IRIX    ?= ./tools/qemu-mips
IRIX_71_ROOT := ./tools/ido7.1_compiler/
IRIX_53_ROOT := ./tools/ido5.3_compiler/

CFLAGS := -G 0 -non_shared -Xfullwarn -Xcpluscomm
ASFLAGS := -march=vr4300 -32

MIPS_VERSION := -mips2
OPTIMIZATION := -O2 -g3

build/src/libultra/os/%: OPTIMIZATION := -O1
build/src/libultra/io/%: OPTIMIZATION := -O2
build/src/libultra/libc/%: OPTIMIZATION := -O2
build/src/libultra/libc/ll%: OPTIMIZATION := -O1
build/src/libultra/libc/ll%: MIPS_VERSION := -mips3 -32
build/src/libultra/gu/%: OPTIMIZATION := -O2
build/src/libultra/rmon/%: OPTIMIZATION := -O2
build/src/libultra/%: CC := $(QEMU_IRIX) -L $(IRIX_53_ROOT) $(IRIX_53_ROOT)/usr/bin/cc
build/src/libultra/%: CFLAGS := $(CFLAGS) -Wab,-r4300_mul
build/src/boot_O1/%: OPTIMIZATION := -O1
build/src/boot_O2/%: OPTIMIZATION := -O2
build/src/boot_O2_g3/%: OPTIMIZATION := -O2 -g3
build/src/boot_O2_g3_trapuv/%: OPTIMIZATION := -O2 -g3
build/src/code/%: CFLAGS := $(CFLAGS) -Wab,-r4300_mul
build/src/actors/%: CFLAGS := $(CFLAGS) -Wab,-r4300_mul
build/src/boot_O2_g3_trapuv/%: CFLAGS := $(CFLAGS) -trapuv
test.txt: OPTIMIZATION := -O2 -g3
test.txt: CC := $(QEMU_IRIX) -L $(IRIX_71_ROOT) $(IRIX_71_ROOT)/usr/bin/cc
test.txt: CFLAGS := $(CFLAGS) -Wab,-r4300_mul

CC := $(QEMU_IRIX) -L $(IRIX_71_ROOT) $(IRIX_71_ROOT)/usr/bin/cc

test.txt: CC := ./tools/preprocess.py $(CC) -- $(AS) $(ASFLAGS) --
build/src/boot_O2/%: CC := ./tools/preprocess.py $(CC) -- $(AS) $(ASFLAGS) --
build/src/boot_O2_g3/%: CC := ./tools/preprocess.py $(CC) -- $(AS) $(ASFLAGS) --
build/src/boot_O2_g3_trapuv/%: CC := ./tools/preprocess.py $(CC) -- $(AS) $(ASFLAGS) --
build/src/code/%: CC := ./tools/preprocess.py $(CC) -- $(AS) $(ASFLAGS) --
build/src/actors/%: CC := ./tools/preprocess.py $(CC) -- $(AS) $(ASFLAGS) --

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

S_FILES := $(wildcard asm/*)
S_O_FILES = $(S_FILES:asm/%.asm=build/asm/%.o)
C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
C_O_FILES = $(C_FILES:src/%.c=build/src/%.o)
ROM_FILES := $(shell cat ./tables/makerom_files.txt)


ROM := rom.z64

BUILD_DIR := ./build

# make build directories
$(shell mkdir -p $(BUILD_DIR)/asm)
$(shell mkdir -p $(BUILD_DIR)/baserom)
$(shell mkdir -p $(BUILD_DIR)/comp)
$(shell mkdir -p $(BUILD_DIR)/decomp)
$(foreach dir,$(SRC_DIRS),$(shell mkdir -p build/$(dir)))

check: $(ROM)
	@md5sum -c checksum.md5

$(ROM): $(ROM_FILES)
	@./tools/makerom.py ./tables/dmadata_table.txt $@

build/code_pre_dmadata.elf: $(S_O_FILES) $(C_O_FILES) linker_scripts/code_script.txt undef.txt linker_scripts/object_script.txt
	$(LD) -r -T linker_scripts/code_script.txt -T undef.txt -T linker_scripts/object_script.txt --no-check-sections --accept-unknown-input-arch -N -o $@

build/code.elf: $(S_O_FILES) $(C_O_FILES) linker_scripts/code_script.txt undef.txt linker_scripts/object_script.txt linker_scripts/dmadata_script.txt
	$(LD) -T linker_scripts/code_script.txt -T undef.txt -T linker_scripts/object_script.txt -T linker_scripts/dmadata_script.txt --no-check-sections --accept-unknown-input-arch -Map build/mm.map -N -o $@

linker_scripts/dmadata_script.txt: $(DMADATA_FILES) build/code_pre_dmadata.elf
	./tools/dmadata.py ./tables/dmadata_table.txt /dev/null -u -l linker_scripts/dmadata_script.txt -e build/code_pre_dmadata.elf

test.txt: build/src/test.o
	$(MIPS_BINUTILS_PREFIX)objdump -d -z --adjust-vma=0x80080790 $< > test.txt

clean:
	rm -f $(ROM) -r build

build/baserom/dmadata: $(COMP_FILES) $(DECOMP_FILES) $(BASEROM_BUILD_FILES)
	./tools/dmadata.py ./tables/dmadata_table.txt $@

build/baserom/boot: build/boot.bin
	cp $< $@

build/decomp/code: build/code.bin
	cp $< $@

build/decomp/ovl_%: build/code.elf
	$(MIPS_BINUTILS_PREFIX)objcopy --dump-section ovl_$*=$@ $< /dev/null


disasm:
	@./tools/disasm.py -d ./asm -u . -l ./tables/files.txt -f ./tables/functions.txt -o ./tables/objects.txt -v ./tables/variables.txt -v ./tables/vrom_variables.txt -v ./tables/pre_boot_variables.txt
	@while read -r file; do \
		./tools/split_asm.py ./asm/$$file.asm ./asm/non_matchings/$$file; \
	done < ./tables/files_with_nonmatching.txt

# Recipes

build/%.bin: build/code.elf
	$(MIPS_BINUTILS_PREFIX)objcopy --dump-section $*=$@ $< /dev/null

build/baserom/%: baserom/%
	cp $< $@

build/asm/%.o: asm/%.asm
	$(AS) $(ASFLAGS) $^ -o $@

build/src/actors/%.o: src/actors/%.c include/*
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTIMIZATION) -Iinclude -o $@ $<
	./tools/overlay.py $@ build/src/actors/$*_overlay.s
	$(AS) $(ASFLAGS) build/src/actors/$*_overlay.s -o build/src/actors/$*_overlay.o

build/src/%.o: src/%.c include/*
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTIMIZATION) -Iinclude -o $@ $<

build/src/libultra/libc/ll.o: src/libultra/libc/ll.c include/*
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTIMIZATION) -Iinclude -o $@ $<
	./tools/set_o32abi_bit.py $@

build/src/libultra/libc/llcvt.o: src/libultra/libc/llcvt.c include/*
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTIMIZATION) -Iinclude -o $@ $<
	./tools/set_o32abi_bit.py $@

build/decomp/%: decomp/%
	cp $< $@

build/comp/%.yaz0: build/decomp/%
	./tools/yaz0.py $< $@

