#ifndef PR_OS_INTERNAL_H
#define PR_OS_INTERNAL_H

#include "ultratypes.h"
#include "os_message.h"
#include "os_pi.h"
#include "os_internal_rsp.h"

typedef struct __osHwInt {
    /* 0x0 */ s32 (*handler)(void);
    /* 0x4 */ void* stackEnd;
} __osHwInt; // size = 0x8

#endif
