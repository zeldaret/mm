#ifndef _ULTRALOG_H_
#define _ULTRALOG_H_

#include <PR/ultratypes.h>

typedef struct {
    /* 0x0 */ u32 magic;
    /* 0x4 */ u32 len;
    /* 0x8 */ u32* base;
    /* 0xC */ s32 startCount;
    /* 0x10 */ s32 writeOffset;
} OSLog;


typedef struct {
    /* 0x0 */ u32 magic;
    /* 0x4 */ u32 timeStamp;
    /* 0x8 */ u16 argCount;
    /* 0xA */ u16 eventID;
} OSLogItem;


typedef struct {
    /* 0x0 */ u32 magic;
    /* 0x4 */ u32 version;
} OSLogFileHdr;

#endif
