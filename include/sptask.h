#ifndef _SPTASK_H_
#define _SPTASK_H_

#include <PR/ultratypes.h>

typedef struct {
    /* 0 */ u32 type;
    /* 4 */ u32 flags;
    /* 8 */ u64* ucode_boot;
    /* 12 */ u32 ucode_boot_size;
    /* 16 */ u64* ucode;
    /* 20 */ u32 ucode_size;
    /* 24 */ u64* ucode_data;
    /* 28 */ u32 ucode_data_size;
    /* 32 */ u64* dram_stack;
    /* 36 */ u32 dram_stack_size;
    /* 40 */ u64* output_buff;
    /* 44 */ u64* output_buff_size;
    /* 48 */ u64* data_ptr;
    /* 52 */ u32 data_size;
    /* 56 */ u64* yield_data_ptr;
    /* 60 */ u32 yield_data_size;
} OSTask_t;


typedef union {
    /* 0 */ OSTask_t t;
    /* 0 */ long long force_structure_alignment;
} OSTask;

typedef u32 OSYieldResult;

#endif
