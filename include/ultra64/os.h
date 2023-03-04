#ifndef OS_H
#define OS_H

#include "libc/stdint.h"
#include "libc/stdlib.h"
#include "os_message.h"
#include "os_thread.h"


typedef u32 OSPageMask;

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
