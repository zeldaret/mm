#ifndef ULTRA64_OSINT_H
#define ULTRA64_OSINT_H

#include "os_message.h"
#include "os.h"
#include "os_internal.h"

typedef struct {
    /* 0x0 */ OSMesgQueue* messageQueue;
    /* 0x4 */ OSMesg message;
} __OSEventState;


typedef struct {
    /* 0x0 */ OSThread* next;
    /* 0x4 */ OSPri priority;
} __OSThreadTail;

extern __osHwInt __osHwIntTable[];
extern __OSEventState __osEventStateTab[OS_NUM_EVENTS];

#endif
