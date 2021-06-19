#ifndef _SPTASK_H_
#define _SPTASK_H_

#include <PR/ultratypes.h>

#define OS_YIELD_DATA_SIZE 0xC00

typedef struct {
    /* 0x0 */ u32 type;
    /* 0x4 */ u32 flags;
    /* 0x8 */ u64* ucode_boot;
    /* 0xC */ u32 ucode_boot_size;
    /* 0x10 */ u64* ucode;
    /* 0x14 */ u32 ucode_size;
    /* 0x18 */ u64* ucode_data;
    /* 0x1C */ u32 ucode_data_size;
    /* 0x20 */ u64* dram_stack;
    /* 0x24 */ u32 dram_stack_size;
    /* 0x28 */ u64* output_buff;
    /* 0x2C */ u64* output_buff_size;
    /* 0x30 */ u64* data_ptr;
    /* 0x34 */ u32 data_size;
    /* 0x38 */ u64* yield_data_ptr;
    /* 0x3C */ u32 yield_data_size;
} OSTask_t;


typedef union {
    /* 0x0 */ OSTask_t t;
    /* 0x0 */ long long force_structure_alignment;
} OSTask;

typedef u32 OSYieldResult;

#endif
