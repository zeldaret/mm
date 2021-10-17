#ifndef _OSINT_H_
#define _OSINT_H_

// TODO should be in libultra/os

#include <stdarg.h>
#include <os.h>
#include <os_internal.h>
#include <ultraerror.h>
#include <ultralog.h>
#include <sptask.h>

typedef struct {
    /* 0x0 */ OSMesgQueue* messageQueue;
    /* 0x4 */ OSMesg message;
} __OSEventState;


typedef struct {
    /* 0x0 */ OSThread* next;
    /* 0x4 */ OSPri priority;
} __OSThreadTail;

#include <global.h> // TODO this is just so libultra files can see function and variable declarations.
                    // Once all data sections have been split up, it should be removed.

#endif
