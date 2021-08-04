#ifndef _SPTASK_H_
#define _SPTASK_H_

#include "PR/ultratypes.h"

/* Task Types */
#define M_NULTASK 0
#define M_GFXTASK 1
#define M_AUDTASK 2
#define M_VIDTASK 3
#define M_NJPEGTASK 4
#define M_HVQTASK 6
#define M_HVQMTASK 7

/* Task Flags  */
#define M_TASK_FLAG0 1
#define M_TASK_FLAG1 2

/* Task Flag Fields */
#define OS_TASK_YIELDED       0x0001
#define OS_TASK_DP_WAIT       0x0002
#define OS_TASK_LOADABLE      0x0004
#define OS_TASK_SP_ONLY       0x0008
#define OS_TASK_USR0          0x0010
#define OS_TASK_USR1          0x0020
#define OS_TASK_USR2          0x0040
#define OS_TASK_USR3          0x0080

#define OS_YIELD_DATA_SIZE 0xC00
#define OS_YIELD_AUDIO_SIZE 0x400

/* SpStatus */
#define SPSTATUS_CLEAR_HALT         0x00000001
#define SPSTATUS_SET_HALT           0x00000002
#define SPSTATUS_CLEAR_BROKE        0x00000004
#define SPSTATUS_CLEAR_INTR         0x00000008
#define SPSTATUS_SET_INTR           0x00000010
#define SPSTATUS_CLEAR_SSTEP        0x00000020
#define SPSTATUS_SET_SSTEP          0x00000040
#define SPSTATUS_CLEAR_INTR_ON_BREAK 0x00000080
#define SPSTATUS_SET_INTR_ON_BREAK  0x00000100
#define SPSTATUS_CLEAR_SIGNAL0      0x00000200
#define SPSTATUS_SET_SIGNAL0        0x00000400
#define SPSTATUS_CLEAR_SIGNAL1      0x00000800
#define SPSTATUS_SET_SIGNAL1        0x00001000
#define SPSTATUS_CLEAR_SIGNAL2      0x00002000
#define SPSTATUS_SET_SIGNAL2        0x00004000
#define SPSTATUS_CLEAR_SIGNAL3      0x00008000
#define SPSTATUS_SET_SIGNAL3        0x00010000
#define SPSTATUS_CLEAR_SIGNAL4      0x00020000
#define SPSTATUS_SET_SIGNAL4        0x00040000
#define SPSTATUS_CLEAR_SIGNAL5      0x00080000
#define SPSTATUS_SET_SIGNAL5        0x00100000
#define SPSTATUS_CLEAR_SIGNAL6      0x00200000
#define SPSTATUS_SET_SIGNAL6        0x00800000
#define SPSTATUS_CLEAR_SIGNAL7      0x01000000
#define SPSTATUS_SET_SIGNAL7        0x02000000

#define SPSTATUS_HALT               0x0001
#define SPSTATUS_BROKE              0x0002
#define SPSTATUS_DMA_BUSY           0x0004
#define SPSTATUS_DMA_FULL           0x0008
#define SPSTATUS_IO_FULL            0x0010
#define SPSTATUS_SINGLE_STEP        0x0020
#define SPSTATUS_INTERRUPT_ON_BREAK 0x0040
#define SPSTATUS_SIGNAL0_SET        0x0080
#define SPSTATUS_SIGNAL1_SET        0x0100
#define SPSTATUS_SIGNAL2_SET        0x0200
#define SPSTATUS_SIGNAL3_SET        0x0400
#define SPSTATUS_SIGNAL4_SET        0x0800
#define SPSTATUS_SIGNAL5_SET        0x1000
#define SPSTATUS_SIGNAL6_SET        0x2000
#define SPSTATUS_SIGNAL7_SET        0x4000

typedef struct {
    /* 0x00 */ u32 type;
    /* 0x04 */ u32 flags;

    /* 0x08 */ u64* ucode_boot;
    /* 0x0C */ u32 ucode_boot_size;

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

typedef union
{
    OSTask_t t;
    long long int force_structure_alignment;
} OSTask;

typedef u32 OSYieldResult;

#endif
