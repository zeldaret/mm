#ifndef _OSINT_H_
#define _OSINT_H_

// TODO should be in libultra/os

#include "libc/stdarg.h"
#include "os.h"
#include "os_internal.h"
#include "ultraerror.h"
#include "ultralog.h"

typedef struct {
    /* 0x0 */ OSMesgQueue* messageQueue;
    /* 0x4 */ OSMesg message;
} __OSEventState;


typedef struct {
    /* 0x0 */ OSThread* next;
    /* 0x4 */ OSPri priority;
} __OSThreadTail;

#endif
