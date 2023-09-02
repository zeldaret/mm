#ifndef PR_OS_INTERNAL_H
#define PR_OS_INTERNAL_H

#include "ultratypes.h"
#include "os_message.h"
#include "os_pi.h"


typedef struct __osHwInt {
    /* 0x00 */ OSMesgQueue* queue;
    /* 0x04 */ OSMesg msg;
} __osHwInt; // size = 0x08

#endif
