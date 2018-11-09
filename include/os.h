#ifndef _OS_H_
#define _OS_H_

#include <PR/ultratypes.h>

typedef s32 OSPri;

typedef s32 OSId;

typedef union {
    /* 0 */ struct {
        /* 0 */ f32 f_odd;
        /* 4 */ f32 f_even;
    } f;
    /* 0 */ f64 d;
} __OSfp;


typedef struct {
    /* 0 */ u64 at;
    /* 8 */ u64 v0;
    /* 16 */ u64 v1;
    /* 24 */ u64 a0;
    /* 32 */ u64 a1;
    /* 40 */ u64 a2;
    /* 48 */ u64 a3;
    /* 56 */ u64 t0;
    /* 64 */ u64 t1;
    /* 72 */ u64 t2;
    /* 80 */ u64 t3;
    /* 88 */ u64 t4;
    /* 96 */ u64 t5;
    /* 104 */ u64 t6;
    /* 112 */ u64 t7;
    /* 120 */ u64 s0;
    /* 128 */ u64 s1;
    /* 136 */ u64 s2;
    /* 144 */ u64 s3;
    /* 152 */ u64 s4;
    /* 160 */ u64 s5;
    /* 168 */ u64 s6;
    /* 176 */ u64 s7;
    /* 184 */ u64 t8;
    /* 192 */ u64 t9;
    /* 200 */ u64 gp;
    /* 208 */ u64 sp;
    /* 216 */ u64 s8;
    /* 224 */ u64 ra;
    /* 232 */ u64 lo;
    /* 240 */ u64 hi;
    /* 248 */ u32 sr;
    /* 252 */ u32 pc;
    /* 256 */ u32 cause;
    /* 260 */ u32 badvaddr;
    /* 264 */ u32 rcp;
    /* 268 */ u32 fpcsr;
    /* 272 */ __OSfp fp0;
    /* 280 */ __OSfp fp2;
    /* 288 */ __OSfp fp4;
    /* 296 */ __OSfp fp6;
    /* 304 */ __OSfp fp8;
    /* 312 */ __OSfp fp10;
    /* 320 */ __OSfp fp12;
    /* 328 */ __OSfp fp14;
    /* 336 */ __OSfp fp16;
    /* 344 */ __OSfp fp18;
    /* 352 */ __OSfp fp20;
    /* 360 */ __OSfp fp22;
    /* 368 */ __OSfp fp24;
    /* 376 */ __OSfp fp26;
    /* 384 */ __OSfp fp28;
    /* 392 */ __OSfp fp30;
} __OSThreadContext;


typedef struct OSThread_s {
    /* 0 */ struct OSThread_s* next;
    /* 4 */ OSPri priority;
    /* 8 */ struct OSThread_s** queue;
    /* 12 */ struct OSThread_s* tlnext;
    /* 16 */ u16 state;
    /* 18 */ u16 flags;
    /* 20 */ OSId id;
    /* 24 */ int fp;
    /* 32 */ __OSThreadContext context;
} OSThread;

typedef u32 OSEvent;

typedef u32 OSIntMask;

typedef u32 OSPageMask;

typedef void* OSMesg;

typedef struct {
    /* 0 */ OSThread* mtqueue;
    /* 4 */ OSThread* fullqueue;
    /* 8 */ s32 validCount;
    /* 12 */ s32 first;
    /* 16 */ s32 msgCount;
    /* 20 */ OSMesg* msg;
} OSMesgQueue;


typedef struct {
    /* 0 */ u32 errStatus;
    /* 4 */ void* dramAddr;
    /* 8 */ void* C2Addr;
    /* 12 */ u32 sectorSize;
    /* 16 */ u32 C1ErrNum;
    /* 20 */ u32 C1ErrSector[4];
} __OSBlockInfo;


typedef struct {
    /* 0 */ u32 cmdType;
    /* 4 */ u16 transferMode;
    /* 6 */ u16 blockNum;
    /* 8 */ s32 sectorNum;
    /* 12 */ u32 devAddr;
    /* 16 */ u32 bmCtlShadow;
    /* 20 */ u32 seqCtlShadow;
    /* 24 */ __OSBlockInfo block[2];
} __OSTranxInfo;


typedef struct OSPiHandle_s {
    /* 0 */ struct OSPiHandle_s* next;
    /* 4 */ u8 type;
    /* 5 */ u8 latency;
    /* 6 */ u8 pageSize;
    /* 7 */ u8 relDuration;
    /* 8 */ u8 pulse;
    /* 9 */ u8 domain;
    /* 12 */ u32 baseAddress;
    /* 16 */ u32 speed;
    /* 20 */ __OSTranxInfo transferInfo;
} OSPiHandle;


typedef struct {
    /* 0 */ u8 type;
    /* 4 */ u32 address;
} OSPiInfo;


typedef struct {
    /* 0 */ u16 type;
    /* 2 */ u8 pri;
    /* 3 */ u8 status;
    /* 4 */ OSMesgQueue* retQueue;
} OSIoMesgHdr;


typedef struct {
    /* 0 */ OSIoMesgHdr hdr;
    /* 8 */ void* dramAddr;
    /* 12 */ u32 devAddr;
    /* 16 */ u32 size;
} OSIoMesg;


typedef struct {
    /* 0 */ s32 active;
    /* 4 */ OSThread* thread;
    /* 8 */ OSMesgQueue* cmdQueue;
    /* 12 */ OSMesgQueue* evtQueue;
    /* 16 */ OSMesgQueue* acsQueue;
    /* 20 */ s32 (*dma)(... /* ECOFF does not store param types */);
} OSDevMgr;


typedef struct {
    /* 0 */ u32 ctrl;
    /* 4 */ u32 width;
    /* 8 */ u32 burst;
    /* 12 */ u32 vSync;
    /* 16 */ u32 hSync;
    /* 20 */ u32 leap;
    /* 24 */ u32 hStart;
    /* 28 */ u32 xScale;
    /* 32 */ u32 vCurrent;
} OSViCommonRegs;


typedef struct {
    /* 0 */ u32 origin;
    /* 4 */ u32 yScale;
    /* 8 */ u32 vStart;
    /* 12 */ u32 vBurst;
    /* 16 */ u32 vIntr;
} OSViFieldRegs;


typedef struct {
    /* 0 */ u8 type;
    /* 4 */ OSViCommonRegs comRegs;
    /* 40 */ OSViFieldRegs fldRegs[2];
} OSViMode;

typedef u64 OSTime;


typedef struct OSTimer_s {
    /* 0 */ struct OSTimer_s* next;
    /* 4 */ struct OSTimer_s* prev;
    /* 8 */ OSTime interval;
    /* 16 */ OSTime value;
    /* 24 */ OSMesgQueue* mq;
    /* 28 */ OSMesg msg;
} OSTimer;


typedef struct {
    /* 0 */ u16 type;
    /* 2 */ u8 status;
    /* 3 */ u8 errno;
} OSContStatus;


typedef struct {
    /* 0 */ u16 button;
    /* 2 */ s8 stick_x;
    /* 3 */ s8 stick_y;
    /* 4 */ u8 errno;
} OSContPad;


typedef struct {
    /* 0 */ void* address;
    /* 4 */ u8 databuffer[32];
    /* 36 */ u8 addressCrc;
    /* 37 */ u8 dataCrc;
    /* 38 */ u8 errno;
} OSContRamIo;


typedef struct {
    /* 0 */ int status;
    /* 4 */ OSMesgQueue* queue;
    /* 8 */ int channel;
    /* 12 */ u8 id[32];
    /* 44 */ u8 backup_id[32];
    /* 76 */ u8 label[32];
    /* 108 */ int pack_size;
    /* 112 */ int version;
    /* 116 */ int dir_size;
    /* 120 */ int inode_start_page;
} OSPfs;


typedef struct {
    /* 0 */ u32 file_size;
    /* 4 */ u16 company_code;
    /* 6 */ u16 game_code;
    /* 8 */ unsigned char ext_name[4];
    /* 12 */ unsigned char game_name[16];
} OSPfsState;


typedef struct {
    /* 0 */ u16* histo_base;
    /* 4 */ u32 histo_size;
    /* 8 */ u32* text_start;
    /* 12 */ u32* text_end;
} OSProf;

#endif
