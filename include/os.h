#ifndef _OS_H_
#define _OS_H_

#include "ultra64/thread.h"
#include "ultra64/message.h"

#define OS_READ     0
#define OS_WRITE    1

typedef u32 OSIntMask;

typedef u32 OSPageMask;

typedef struct {
    /* 0x00 */ u32 errStatus;
    /* 0x04 */ void* dramAddr;
    /* 0x08 */ void* C2Addr;
    /* 0x0C */ u32 sectorSize;
    /* 0x10 */ u32 C1ErrNum;
    /* 0x14 */ u32 C1ErrSector[4];
} __OSBlockInfo; // size = 0x24


typedef struct {
    /* 0x00 */ u32 cmdType;
    /* 0x04 */ u16 transferMode;
    /* 0x06 */ u16 blockNum;
    /* 0x08 */ s32 sectorNum;
    /* 0x0C */ u32 devAddr;
    /* 0x10 */ u32 bmCtlShadow;
    /* 0x14 */ u32 seqCtlShadow;
    /* 0x18 */ __OSBlockInfo block[2];
} __OSTranxInfo; // size = 0x60


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
} OSPiHandle; // size = 0x74


typedef struct {
    /* 0x0 */ u8 type;
    /* 0x4 */ u32 address;
} OSPiInfo; // size = 0x8


typedef struct {
    /* 0x0 */ u16 type;
    /* 0x2 */ u8 pri;
    /* 0x3 */ u8 status;
    /* 0x4 */ OSMesgQueue* retQueue;
} OSIoMesgHdr; // size = 0x8


typedef struct {
    /* 0x00 */ OSIoMesgHdr hdr;
    /* 0x08 */ void* dramAddr;
    /* 0x0C */ u32 devAddr;
    /* 0x10 */ u32 size;
    /* 0x14 */ OSPiHandle* piHandle;
} OSIoMesg; // size = 0x88


typedef struct {
    /* 0x00 */ s32 active; // u32 maybe? need to check
    /* 0x04 */ OSThread* thread;
    /* 0x08 */ OSMesgQueue* cmdQueue;
    /* 0x0C */ OSMesgQueue* evtQueue;
    /* 0x10 */ OSMesgQueue* acsQueue;
    /* 0x14 */ s32 (*piDmaCallback)(s32, u32, void*, u32);
    /* 0x18 */ s32 (*epiDmaCallback)(OSPiHandle*, s32, u32, void*, u32);
} OSDevMgr; // size = 0x1C

typedef u64 OSTime;

typedef struct OSTimer_s {
    /* 0x00 */ struct OSTimer_s* next;
    /* 0x04 */ struct OSTimer_s* prev;
    /* 0x08 */ OSTime interval;
    /* 0x10 */ OSTime value;
    /* 0x18 */ OSMesgQueue* mq;
    /* 0x1C */ OSMesg msg;
} OSTimer; // size = 0x20

typedef struct {
    /* 0x0 */ u16 type;
    /* 0x2 */ u8 status;
    /* 0x3 */ u8 errno;
} OSContStatus; // size = 0x4


typedef struct {
    /* 0x0 */ u16 button;
    /* 0x2 */ s8 stick_x;
    /* 0x3 */ s8 stick_y;
    /* 0x4 */ u8 errno;
} OSContPad; // size = 0x6


typedef struct {
    /* 0x00 */ void* address;
    /* 0x04 */ u8 databuffer[32];
    /* 0x24 */ u8 addressCrc;
    /* 0x25 */ u8 dataCrc;
    /* 0x26 */ u8 errno;
} OSContRamIo; // size = 0x28

typedef struct {
    /* 0x0 */ u16* histo_base;
    /* 0x4 */ u32 histo_size;
    /* 0x8 */ u32* text_start;
    /* 0xC */ u32* text_end;
} OSProf; // size = 0x10

typedef struct {
    /* 0x0 */ OSMesgQueue* mq;
    /* 0x4 */ s32 port; /* Controller port */
    /* 0x8 */ s32 mode;
    /* 0xC */ u8 status;
} OSVoiceHandle; // size = 0x10

#endif
