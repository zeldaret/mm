#ifndef _ULTRALOG_H_
#define _ULTRALOG_H_

#include <PR/ultratypes.h>

typedef struct {
    /* 0 */ u32 magic;
    /* 4 */ u32 len;
    /* 8 */ u32* base;
    /* 12 */ s32 startCount;
    /* 16 */ s32 writeOffset;
} OSLog;


typedef struct {
    /* 0 */ u32 magic;
    /* 4 */ u32 timeStamp;
    /* 8 */ u16 argCount;
    /* 10 */ u16 eventID;
} OSLogItem;


typedef struct {
    /* 0 */ u32 magic;
    /* 4 */ u32 version;
} OSLogFileHdr;

#endif
