#ifndef _OS_H_
#define _OS_H_

#include "PR/ultratypes.h"

typedef s32 OSPri;

typedef s32 OSId;

#define OS_READ     0
#define OS_WRITE    1

typedef union {
    /* 0x0 */ struct {
        /* 0x0 */ f32 f_odd;
        /* 0x4 */ f32 f_even;
    } f;
    /* 0x0 */ f64 d;
} __OSfp;


typedef struct {
    /* 0x0 */ u64 at;
    /* 0x8 */ u64 v0;
    /* 0x10 */ u64 v1;
    /* 0x18 */ u64 a0;
    /* 0x20 */ u64 a1;
    /* 0x28 */ u64 a2;
    /* 0x30 */ u64 a3;
    /* 0x38 */ u64 t0;
    /* 0x40 */ u64 t1;
    /* 0x48 */ u64 t2;
    /* 0x50 */ u64 t3;
    /* 0x58 */ u64 t4;
    /* 0x60 */ u64 t5;
    /* 0x68 */ u64 t6;
    /* 0x70 */ u64 t7;
    /* 0x78 */ u64 s0;
    /* 0x80 */ u64 s1;
    /* 0x88 */ u64 s2;
    /* 0x90 */ u64 s3;
    /* 0x98 */ u64 s4;
    /* 0xA0 */ u64 s5;
    /* 0xA8 */ u64 s6;
    /* 0xB0 */ u64 s7;
    /* 0xB8 */ u64 t8;
    /* 0xC0 */ u64 t9;
    /* 0xC8 */ u64 gp;
    /* 0xD0 */ u64 sp;
    /* 0xD8 */ u64 s8;
    /* 0xE0 */ u64 ra;
    /* 0xE8 */ u64 lo;
    /* 0xF0 */ u64 hi;
    /* 0xF8 */ u32 sr;
    /* 0xFC */ u32 pc;
    /* 0x100 */ u32 cause;
    /* 0x104 */ u32 badvaddr;
    /* 0x108 */ u32 rcp;
    /* 0x10C */ u32 fpcsr;
    /* 0x110 */ __OSfp fp0;
    /* 0x118 */ __OSfp fp2;
    /* 0x120 */ __OSfp fp4;
    /* 0x128 */ __OSfp fp6;
    /* 0x130 */ __OSfp fp8;
    /* 0x138 */ __OSfp fp10;
    /* 0x140 */ __OSfp fp12;
    /* 0x148 */ __OSfp fp14;
    /* 0x150 */ __OSfp fp16;
    /* 0x158 */ __OSfp fp18;
    /* 0x160 */ __OSfp fp20;
    /* 0x168 */ __OSfp fp22;
    /* 0x170 */ __OSfp fp24;
    /* 0x178 */ __OSfp fp26;
    /* 0x180 */ __OSfp fp28;
    /* 0x188 */ __OSfp fp30;
} __OSThreadContext;


typedef struct OSThread_s {
    /* 0x0 */ struct OSThread_s* next;
    /* 0x4 */ OSPri priority;
    /* 0x8 */ struct OSThread_s** queue;
    /* 0xC */ struct OSThread_s* tlnext;
    /* 0x10 */ u16 state;
    /* 0x12 */ u16 flags;
    /* 0x14 */ OSId id;
    /* 0x18 */ int fp;
    /* 0x20 */ __OSThreadContext context;
} OSThread;

typedef u32 OSEvent;

typedef u32 OSIntMask;

typedef u32 OSPageMask;

#define OS_MESG_NOBLOCK         0
#define OS_MESG_BLOCK           1

typedef void* OSMesg;

typedef struct {
    /* 0x00 */ OSThread* mtqueue;
    /* 0x04 */ OSThread* fullqueue;
    /* 0x08 */ s32 validCount;
    /* 0x0C */ s32 first;
    /* 0x10 */ s32 msgCount;
    /* 0x14 */ OSMesg* msg;
} OSMesgQueue; // size = 0x20


typedef struct {
    /* 0x00 */ u32 errStatus;
    /* 0x04 */ void* dramAddr;
    /* 0x08 */ void* C2Addr;
    /* 0x0C */ u32 sectorSize;
    /* 0x10 */ u32 C1ErrNum;
    /* 0x14 */ u32 C1ErrSector[4];
} __OSBlockInfo;


typedef struct {
    /* 0x00 */ u32 cmdType;
    /* 0x04 */ u16 transferMode;
    /* 0x06 */ u16 blockNum;
    /* 0x08 */ s32 sectorNum;
    /* 0x0C */ u32 devAddr;
    /* 0x10 */ u32 bmCtlShadow;
    /* 0x14 */ u32 seqCtlShadow;
    /* 0x18 */ __OSBlockInfo block[2];
} __OSTranxInfo;


typedef struct OSPiHandle_s {
    /* 0x00 */ struct OSPiHandle_s* next;
    /* 0x04 */ u8 type;
    /* 0x05 */ u8 latency;
    /* 0x06 */ u8 pageSize;
    /* 0x07 */ u8 relDuration;
    /* 0x08 */ u8 pulse;
    /* 0x09 */ u8 domain;
    /* 0x0C */ u32 baseAddress;
    /* 0x10 */ u32 speed;
    /* 0x14 */ __OSTranxInfo transferInfo;
} OSPiHandle;


typedef struct {
    /* 0x0 */ u8 type;
    /* 0x4 */ u32 address;
} OSPiInfo;


typedef struct {
    /* 0x0 */ u16 type;
    /* 0x2 */ u8 pri;
    /* 0x3 */ u8 status;
    /* 0x4 */ OSMesgQueue* retQueue;
} OSIoMesgHdr;


typedef struct {
    /* 0x00 */ OSIoMesgHdr hdr;
    /* 0x08 */ void* dramAddr;
    /* 0x0C */ u32 devAddr;
    /* 0x10 */ u32 size;
    /* 0x14 */ OSPiHandle* piHandle;
} OSIoMesg;


typedef struct {
    /* 0x00 */ s32 active; // u32 maybe? need to check
    /* 0x04 */ OSThread* thread;
    /* 0x08 */ OSMesgQueue* cmdQueue;
    /* 0x0C */ OSMesgQueue* evtQueue;
    /* 0x10 */ OSMesgQueue* acsQueue;
    /* 0x14 */ s32 (*piDmaCallback)(s32, u32, void*, u32);
    /* 0x18 */ s32 (*epiDmaCallback)(OSPiHandle*, s32, u32, void*, u32);
} OSDevMgr;


typedef struct {
    /* 0x00 */ u32 ctrl;
    /* 0x04 */ u32 width;
    /* 0x08 */ u32 burst;
    /* 0x0C */ u32 vSync;
    /* 0x10 */ u32 hSync;
    /* 0x14 */ u32 leap;
    /* 0x18 */ u32 hStart;
    /* 0x1C */ u32 xScale;
    /* 0x20 */ u32 vCurrent;
} OSViCommonRegs;


typedef struct {
    /* 0x00 */ u32 origin;
    /* 0x04 */ u32 yScale;
    /* 0x08 */ u32 vStart;
    /* 0x0C */ u32 vBurst;
    /* 0x10 */ u32 vIntr;
} OSViFieldRegs;


typedef struct {
    /* 0x00 */ u8 type;
    /* 0x04 */ OSViCommonRegs comRegs;
    /* 0x28 */ OSViFieldRegs fldRegs[2];
} OSViMode;

typedef u64 OSTime;


typedef struct OSTimer_s {
    /* 0x00 */ struct OSTimer_s* next;
    /* 0x04 */ struct OSTimer_s* prev;
    /* 0x08 */ OSTime interval;
    /* 0x10 */ OSTime value;
    /* 0x18 */ OSMesgQueue* mq;
    /* 0x1C */ OSMesg msg;
} OSTimer;


typedef struct {
    /* 0x0 */ u16 type;
    /* 0x2 */ u8 status;
    /* 0x3 */ u8 errno;
} OSContStatus;


typedef struct {
    /* 0x0 */ u16 button;
    /* 0x2 */ s8 stick_x;
    /* 0x3 */ s8 stick_y;
    /* 0x4 */ u8 errno;
} OSContPad;


typedef struct {
    /* 0x00 */ void* address;
    /* 0x04 */ u8 databuffer[32];
    /* 0x24 */ u8 addressCrc;
    /* 0x25 */ u8 dataCrc;
    /* 0x26 */ u8 errno;
} OSContRamIo;

typedef struct {
    /* 0x0 */ u16* histo_base;
    /* 0x4 */ u32 histo_size;
    /* 0x8 */ u32* text_start;
    /* 0xC */ u32* text_end;
} OSProf;

typedef struct {
    /* 0x0 */ OSMesgQueue* mq;
    /* 0x4 */ s32 port; /* Controller port */
    /* 0x8 */ s32 mode;
    /* 0xC */ u8 status;
} OSVoiceHandle; // size = 0x10

#endif
