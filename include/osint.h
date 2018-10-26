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
    /* 0 */ OSMesgQueue* messageQueue;
    /* 4 */ OSMesg message;
} __OSEventState;


typedef struct {
    /* 0 */ OSThread* next;
    /* 4 */ OSPri priority;
} __OSThreadTail;

#include <variables.h> // TODO all variables should be moved to the file that logically defines them
                       // maybe put externs here?
#include <functions.h>

#endif
