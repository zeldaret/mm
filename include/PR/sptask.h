#ifndef PR_SPTASK_H
#define PR_SPTASK_H

#include "PR/ultratypes.h"


/* Task Flag Fields */
#define OS_TASK_YIELDED  (1 << 0)
#define OS_TASK_DP_WAIT  (1 << 1)
#define OS_TASK_LOADABLE (1 << 2)
#define OS_TASK_SP_ONLY  (1 << 3)
#define OS_TASK_USR0     (1 << 4)
#define OS_TASK_USR1     (1 << 5)
#define OS_TASK_USR2     (1 << 6)
#define OS_TASK_USR3     (1 << 7)

#define OS_YIELD_DATA_SIZE  0xC00
#define OS_YIELD_AUDIO_SIZE 0x400

typedef struct {
    /* 0x00 */ u32 type;
    /* 0x04 */ u32 flags;

    /* 0x08 */ u64* ucode_boot;
    /* 0x0C */ u32 ucode_boot_size; // ucode will load these sizes with lw, so need to be 32-bit

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
} OSTask_t; // size = 0x40

typedef union {
    OSTask_t t;
    long long int force_structure_alignment;
} OSTask;

typedef u32 OSYieldResult;

void osSpTaskLoad(OSTask* intp);
void osSpTaskStartGo(OSTask* tp);

void osSpTaskYield(void);
OSYieldResult osSpTaskYielded(OSTask* task);

#endif
