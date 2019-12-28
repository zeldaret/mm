# TODO think about how to split this up

AS := $(MIPS_BINUTILS)as
LD := $(MIPS_BINUTILS)ld

IRIX_71_ROOT := ./tools/ido7.1_compiler/
IRIX_53_ROOT := ./tools/ido5.3_compiler/

CFLAGS := -G 0 -non_shared -Xfullwarn -Xcpluscomm
ASFLAGS := -march=vr4300 -32

MIPS_VERSION := -mips2
OPTIMIZATION := -O2 -g3

build/src/libultra/os/%: OPTIMIZATION := -O1
build/src/libultra/io/%: OPTIMIZATION := -O2
build/src/libultra/libc/%: OPTIMIZATION := -O2
build/src/libultra/gu/%: OPTIMIZATION := -O2
build/src/libultra/%: CC := $(QEMU_IRIX) -L $(IRIX_53_ROOT) $(IRIX_53_ROOT)/usr/bin/cc
build/src/libultra/%: CFLAGS := $(CFLAGS) -Wab,-r4300_mul
build/src/boot_O1/%: OPTIMIZATION := -O1
build/src/boot_O2_g3/%: OPTIMIZATION := -O2 -g3
build/src/code/%: CFLAGS := $(CFLAGS) -Wab,-r4300_mul
build/src/actors/%: CFLAGS := $(CFLAGS) -Wab,-r4300_mul
test.txt: OPTIMIZATION := -O2 -g3
test.txt: CC := $(QEMU_IRIX) -L $(IRIX_71_ROOT) $(IRIX_71_ROOT)/usr/bin/cc
test.txt: CFLAGS := $(CFLAGS) -Wab,-r4300_mul

CC := $(QEMU_IRIX) -L $(IRIX_71_ROOT) $(IRIX_71_ROOT)/usr/bin/cc

test.txt: CC := ./tools/preprocess.py $(CC) -- $(AS) $(ASFLAGS) --
build/src/boot_O2_g3/%: CC := ./tools/preprocess.py $(CC) -- $(AS) $(ASFLAGS) --
build/src/code/%: CC := ./tools/preprocess.py $(CC) -- $(AS) $(ASFLAGS) --
build/src/actors/%: CC := ./tools/preprocess.py $(CC) -- $(AS) $(ASFLAGS) --

BASEROM_FILES := $(wildcard baserom/*)
# Exclude dmadata, it will be generated right before packing the rom
BASEROM_FILES := $(subst baserom/dmadata ,,$(BASEROM_FILES))
BASEROM_BUILD_FILES := $(BASEROM_FILES:baserom/%=build/baserom/%)
BASEROM_PRE_DMADATA_FILES := $(BASEROM_BUILD_FILES:build/baserom/%=build/baserom_pre_dmadata/%)

BASE_DECOMP_FILES := $(wildcard decomp/*)
DECOMP_FILES := $(BASE_DECOMP_FILES:decomp/%=build/decomp/%)
DECOMP_PRE_DMADATA_FILES := $(DECOMP_FILES:build/decomp/%=build/decomp_pre_dmadata/%)
COMP_FILES := $(DECOMP_FILES:build/decomp/%=build/comp/%.yaz0)

S_FILES := $(wildcard asm/*)
S_O_FILES = $(S_FILES:asm/%.asm=build/asm/%.o)
C_FILES := $(wildcard src/libultra/*) \
           $(wildcard src/libultra/os/*) \
           $(wildcard src/libultra/io/*) \
           $(wildcard src/libultra/libc/*) \
           $(wildcard src/libultra/gu/*) \
           $(wildcard src/code/*) \
           $(wildcard src/boot_O2_g3/*) \
           $(wildcard src/boot_O1/*) \
           $(wildcard src/actors/Bg_Fu_Kaiten/*) \
           $(wildcard src/actors/Bg_Ikana_Ray/*)
C_O_FILES = $(C_FILES:src/%.c=build/src/%.o)
ROM_FILES := $(shell cat ./tables/makerom_files.txt)


ROM := rom.z64

BUILD_DIR := ./build

# make build directories
$(shell mkdir -p $(BUILD_DIR)/asm)
$(shell mkdir -p $(BUILD_DIR)/baserom)
$(shell mkdir -p $(BUILD_DIR)/baserom_pre_dmadata)
$(shell mkdir -p $(BUILD_DIR)/comp)
$(shell mkdir -p $(BUILD_DIR)/decomp)
$(shell mkdir -p $(BUILD_DIR)/decomp_pre_dmadata)
$(shell mkdir -p $(BUILD_DIR)/src)
$(shell mkdir -p $(BUILD_DIR)/src/libultra)
$(shell mkdir -p $(BUILD_DIR)/src/libultra/os)
$(shell mkdir -p $(BUILD_DIR)/src/libultra/io)
$(shell mkdir -p $(BUILD_DIR)/src/libultra/libc)
$(shell mkdir -p $(BUILD_DIR)/src/libultra/gu)
$(shell mkdir -p $(BUILD_DIR)/src/code)
$(shell mkdir -p $(BUILD_DIR)/src/boot_O2_g3)
$(shell mkdir -p $(BUILD_DIR)/src/boot_O1)
$(shell mkdir -p $(BUILD_DIR)/src/actors/Bg_Fu_Kaiten)
$(shell mkdir -p $(BUILD_DIR)/src/actors/Bg_Ikana_Ray)

check: $(ROM)
	@md5sum -c checksum.md5

$(ROM): $(ROM_FILES)
	@./tools/makerom.py ./tables/dmadata_table.py $@

build/%_pre_dmadata.bin: build/code_pre_dmadata.elf
	$(MIPS_BINUTILS)objcopy --dump-section $*=$@ $<

build/%.bin: build/code.elf
	$(MIPS_BINUTILS)objcopy --dump-section $*=$@ $<

build/code_pre_dmadata.elf: $(S_O_FILES) $(C_O_FILES) linker_scripts/code_script.txt undef.txt linker_scripts/object_script.txt
	$(LD) -r -T linker_scripts/code_script.txt -T undef.txt -T linker_scripts/object_script.txt --no-check-sections --accept-unknown-input-arch -o $@

build/code.elf: $(S_O_FILES) $(C_O_FILES) linker_scripts/code_script.txt undef.txt linker_scripts/object_script.txt linker_scripts/dmadata_script.txt
	$(LD) -T linker_scripts/code_script.txt -T undef.txt -T linker_scripts/object_script.txt -T linker_scripts/dmadata_script.txt --no-check-sections --accept-unknown-input-arch -Map build/mm.map -o $@

linker_scripts/dmadata_script.txt: $(DECOMP_PRE_DMADATA_FILES) $(BASEROM_PRE_DMADATA_FILES)
# TODO is there a better way to avoid this shuffling?
	mv build/baserom build/baserom_temp
	mv build/decomp build/decomp_temp
	mv build/baserom_pre_dmadata build/baserom
	mv build/decomp_pre_dmadata build/decomp
	./tools/dmadata.py ./tables/dmadata_table.py /dev/null -u -l linker_scripts/dmadata_script.txt
	mv build/baserom build/baserom_pre_dmadata
	mv build/decomp build/decomp_pre_dmadata
	mv build/baserom_temp build/baserom
	mv build/decomp_temp build/decomp

test.txt: build/src/test.o
	$(MIPS_BINUTILS)objdump -d -z --adjust-vma=0x80080790 $< > test.txt

clean:
	rm $(ROM) -r build

build/baserom/dmadata: $(COMP_FILES) $(DECOMP_FILES) $(BASEROM_BUILD_FILES)
	./tools/dmadata.py ./tables/dmadata_table.py $@

build/baserom/boot: build/boot.bin
	cp $< $@

build/decomp/code: build/code.bin
	cp $< $@

build/decomp/ovl_title: build/ovl_title.bin
	cp $< $@

build/decomp/ovl_Bg_Fu_Kaiten: build/ovl_Bg_Fu_Kaiten.bin
	cp $< $@

build/decomp/ovl_Bg_Ikana_Ray: build/ovl_Bg_Ikana_Ray.bin
	cp $< $@

build/baserom_pre_dmadata/boot: build/boot_pre_dmadata.bin
	cp $< $@

build/decomp_pre_dmadata/code: build/code_pre_dmadata.bin
	cp $< $@

build/decomp_pre_dmadata/ovl_title: build/ovl_title_pre_dmadata.bin
	cp $< $@

build/decomp_pre_dmadata/ovl_Bg_Fu_Kaiten: build/ovl_Bg_Fu_Kaiten_pre_dmadata.bin
	cp $< $@

build/decomp_pre_dmadata/ovl_Bg_Ikana_Ray: build/ovl_Bg_Ikana_Ray_pre_dmadata.bin
	cp $< $@


disasm:
	@./tools/disasm.py -d ./asm -e ./include -u . -l ./tables/files.py -f ./tables/functions.py -o ./tables/objects.py -v ./tables/variables.py -v ./tables/vrom_variables.py -v ./tables/pre_boot_variables.py
	@while read -r file; do \
		./tools/split_asm.py ./asm/$$file.asm ./asm/nonmatching/$$file; \
	done < ./tables/files_with_nonmatching.txt

# Recipes

build/baserom/%: build/baserom_pre_dmadata/%
	cp $< $@

build/baserom_pre_dmadata/%: baserom/%
	cp $< $@

build/asm/%.o: asm/%.asm
	$(AS) $(ASFLAGS) $^ -o $@

build/src/actors/%.o: src/actors/%.c include/*
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTIMIZATION) -Iinclude -o $@ $<
	./tools/overlay.py $@ build/src/actors/$*_overlay.s
	$(AS) $(ASFLAGS) build/src/actors/$*_overlay.s -o build/src/actors/$*_overlay.o

build/src/%.o: src/%.c include/*
	$(CC) -c $(CFLAGS) $(MIPS_VERSION) $(OPTIMIZATION) -Iinclude -o $@ $<

build/decomp/%: build/decomp_pre_dmadata/%
	cp $< $@

build/decomp_pre_dmadata/%: decomp/%
	cp $< $@

build/comp/%.yaz0: build/decomp/%
	./tools/yaz0.py $< $@

