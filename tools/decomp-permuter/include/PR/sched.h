#ifndef _SCHED_H_
#define _SCHED_H_

#include <os.h>
#include <sptask.h>

typedef struct {
    /* 0x0 */ short type;
    /* 0x2 */ unsigned char misc[30];
} OSScMsg;


typedef struct OSScTask_s {
    /* 0x0 */ struct OSScTask_s* next;
    /* 0x4 */ u32 state;
    /* 0x8 */ u32 flags;
    /* 0xC */ void* framebuffer;
    /* 0x10 */ OSTask list;
    /* 0x50 */ OSMesgQueue* msgQ;
    /* 0x54 */ OSMesg msg;
} OSScTask;


typedef struct OSScClient_s {
    /* 0x0 */ struct OSScClient_s* next;
    /* 0x4 */ OSMesgQueue* msgQ;
} OSScClient;


typedef struct {
    /* 0x0 */ OSScMsg retraceMsg;
    /* 0x20 */ OSScMsg prenmiMsg;
    /* 0x40 */ OSMesgQueue interruptQ;
    /* 0x58 */ OSMesg intBuf[8];
    /* 0x78 */ OSMesgQueue cmdQ;
    /* 0x90 */ OSMesg cmdMsgBuf[8];
    /* 0xB0 */ OSThread thread;
    /* 0x260 */ OSScClient* clientList;
    /* 0x264 */ OSScTask* audioListHead;
    /* 0x268 */ OSScTask* gfxListHead;
    /* 0x26C */ OSScTask* audioListTail;
    /* 0x270 */ OSScTask* gfxListTail;
    /* 0x274 */ OSScTask* curRSPTask;
    /* 0x278 */ OSScTask* curRDPTask;
    /* 0x27C */ u32 frameCount;
    /* 0x280 */ s32 doAudio;
} OSSched;

#endif
