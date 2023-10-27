/* SPDX-FileCopyrightText: © 2023 ZeldaRET */
/* SPDX-License-Identifier: MIT */

/**
 * Program to generate compressed yar (Yaz0 ARchive) files.
 *
 * The program expects an .o elf file and outputs a raw yar binary file and a
 * "symbols" elf.
 *
 * A yar file consists of multiple Yaz0 files compressed individually. The
 * archive begins with a header of non-fixed size, which describes the
 * location of each individual Yaz0 block within the archive itself. This
 * header is followed by each Yaz0 file.
 *
 * The first word (a 4 byte group) of the header indicates the size in bytes of
 * the header itself (also describes the offset of the first Yaz0 block). The
 * rest of the header consists of words describing the offsets of each Yaz0
 * block relative to the end of the header, because the first Yaz0
 * block is omitted from the offsets in the header.
 *
 * Each Yaz0 block is 0xFF-padded to a multiple of 0x10 in size.
 *
 * The entire archive is 0-padded to a multiple of 0x10 in size.
 *
 * The program works by compressing each .data symbol in the input elf file as
 * its own Yaz0 compressed file, appending them in order for the generated
 * archive. Other elf sections are ignored for the resulting yar file.
 *
 * The program also outputs an elf file that's identical to the elf input,
 * but with its .data section zero'ed out completely. This "symbols" elf can be
 * used for referencing each symbol as the whole file were completely
 * uncompressed.
 */


#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "elf32.h"
#include "yaz0.h"
#include "util.h"


typedef struct Bytearray {
    uint8_t *bytes;
    size_t size;
} Bytearray;

typedef struct SymbolList {
    struct Elf32_Symbol *symbols;
    size_t size; // allocated size
    size_t len; // elements in the list
} SymbolList;

typedef struct DataSection {
    Bytearray data;
    uint32_t dataOffset;
    SymbolList symbols;
} DataSection;


void Bytearray_Init(Bytearray *bytearr, const uint8_t *bytes, size_t size) {
    bytearr->bytes = malloc(size);
    if (bytearr->bytes == NULL) {
        util_fatal_error("memory error");
    }

    memcpy(bytearr->bytes, bytes, size);
    bytearr->size = size;
}

void Bytearray_InitValue(Bytearray *bytearr, uint8_t val, size_t count) {
    bytearr->bytes = malloc(count * sizeof(uint8_t));
    if (bytearr->bytes == NULL) {
        util_fatal_error("memory error");
    }

    memset(bytearr->bytes, val, count);
    bytearr->size = count;
}

void Bytearray_ExtendValue(Bytearray *bytearr, uint8_t val, size_t count) {
    size_t newSize = bytearr->size + count;

    bytearr->bytes = realloc(bytearr->bytes, newSize);
    if (bytearr->bytes == NULL) {
        util_fatal_error("memory error");
    }

    memset(&bytearr->bytes[bytearr->size], val, count);
    bytearr->size = newSize;
}

void Bytearray_Extend(Bytearray *bytearr, const uint8_t *bytes, size_t size) {
    size_t newSize = bytearr->size + size;

    bytearr->bytes = realloc(bytearr->bytes, newSize);
    if (bytearr->bytes == NULL) {
        util_fatal_error("memory error");
    }

    memcpy(&bytearr->bytes[bytearr->size], bytes, size);
    bytearr->size = newSize;
}

void Bytearray_Destroy(Bytearray *bytearr) {
    free(bytearr->bytes);
}

void SymbolList_Init(SymbolList *list, size_t initialAmount) {
    list->symbols = malloc(initialAmount * sizeof(struct Elf32_Symbol));
    if (list->symbols == NULL) {
        util_fatal_error("memory error");
    }
    list->size = initialAmount;
    list->len = 0;
}

void SymbolList_Destroy(SymbolList *list) {
    free(list->symbols);
}

void DataSection_FromElf(DataSection *dst, const Bytearray *elfBytes){
    struct Elf32 elf;
    size_t i;
    int symIndex;
    size_t dataShndx = 0;

    if (!elf32_init(&elf, elfBytes->bytes, elfBytes->size) || (elf.machine != ELF_MACHINE_MIPS)) {
        util_fatal_error("not a valid 32-bit MIPS ELF file");
    }

    for (i = 0; i < elf.shnum; i++) {
        struct Elf32_Section sec;

        if (!elf32_get_section(&elf, &sec, i)) {
            util_fatal_error("invalid or corrupt ELF file");
        }

        if (strcmp(sec.name, ".data") == 0) {
            dst->dataOffset = sec.offset;
            Bytearray_Init(&dst->data, &elfBytes->bytes[sec.offset], sec.size);
            dataShndx = i;
            break;
        }
    }

    SymbolList_Init(&dst->symbols, elf.numsymbols);
    for (symIndex = 0; symIndex < elf.numsymbols; symIndex++) {
        struct Elf32_Symbol sym;

        if (!elf32_get_symbol(&elf, &sym, symIndex)) {
            util_fatal_error("invalid or corrupt ELF file");
        }

        if (sym.shndx != dataShndx) {
            continue;
        }
        if (sym.st_type != STT_OBJECT) {
            continue;
        }

        dst->symbols.symbols[dst->symbols.len++] = sym;
    }
}

void DataSection_Destroy(DataSection *dataSect) {
    Bytearray_Destroy(&dataSect->data);
    SymbolList_Destroy(&dataSect->symbols);
}

#define ALIGN16(val) (((val) + 0xF) & ~0xF)

void createArchive(Bytearray *archive, const DataSection *dataSect) {
    uint32_t firstEntryOffset = (dataSect->symbols.len + 1) * sizeof(uint32_t);
    size_t i;
    size_t offset;

    // Fill with zeroes until the compressed data start
    Bytearray_InitValue(archive, 0, firstEntryOffset);

    util_write_uint32_be(&archive->bytes[0], firstEntryOffset);

    offset = firstEntryOffset;
    for (i = 0; i < dataSect->symbols.len; i++) {
        const struct Elf32_Symbol *sym = &dataSect->symbols.symbols[i];
        size_t realUncompressedSize = sym->size;
        size_t alignedUncompressedSize = ALIGN16(realUncompressedSize);
        uint8_t *inputBuf = malloc(alignedUncompressedSize* sizeof(uint8_t));
        uint8_t *output = malloc(alignedUncompressedSize * sizeof(uint8_t)); // assume compressed shouldn't be bigger than uncompressed
        size_t compressedSize;

        // Make sure to pad each entry to a 0x10 boundary
        memcpy(inputBuf, &dataSect->data.bytes[sym->value], realUncompressedSize);
        if (realUncompressedSize < alignedUncompressedSize) {
            memset(&inputBuf[realUncompressedSize], 0, alignedUncompressedSize - realUncompressedSize);
        }

        output[0] = 'Y';
        output[1] = 'a';
        output[2] = 'z';
        output[3] = '0';
        util_write_uint32_be(&output[4], alignedUncompressedSize);
        memset(&output[8], 0, 8);
        compressedSize = 0x10;

        compressedSize += yaz0_encode(inputBuf, &output[0x10], alignedUncompressedSize);

        // Pad to 0x10
        while (compressedSize % 0x10 != 0) {
            output[compressedSize++] = 0xFF;
        }

        Bytearray_Extend(archive, output, compressedSize);

        if (i > 0) {
            util_write_uint32_be(&archive->bytes[i * sizeof(uint32_t)], offset - firstEntryOffset);
        }

        offset += compressedSize;
        free(output);
    }

    util_write_uint32_be(&archive->bytes[i * sizeof(uint32_t)], offset - firstEntryOffset);

    if (archive->size % 16 != 0) {
        size_t extraPad = ALIGN16(archive->size) - archive->size;

        Bytearray_ExtendValue(archive, 0, extraPad);
    }
}


int main(int argc, char *argv[]) {
    const char *inPath;
    const char *binPath;
    const char *symPath;
    Bytearray elfBytes;
    DataSection dataSect;
    Bytearray archive;

    if (argc != 4) {
        fprintf(stderr, "%s in_file out_bin out_sym\n", argv[0]);
        exit(1);
    }

    inPath = argv[1];
    binPath = argv[2];
    symPath = argv[3];

    elfBytes.bytes = util_read_whole_file(inPath, &elfBytes.size);

    DataSection_FromElf(&dataSect, &elfBytes);

    createArchive(&archive, &dataSect);

    // Write the compressed archive file as a raw binary
    util_write_whole_file(binPath, archive.bytes, archive.size);

    // Zero out data
    memset(&elfBytes.bytes[dataSect.dataOffset], 0, dataSect.data.size);

    util_write_whole_file(symPath, elfBytes.bytes, elfBytes.size);

    Bytearray_Destroy(&archive);
    DataSection_Destroy(&dataSect);
    Bytearray_Destroy(&elfBytes);

    return 0;
}
