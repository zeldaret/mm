#ifndef PR_OS_INTERNAL_H
#define PR_OS_INTERNAL_H

#ifdef _LANGUAGE_C

#include "ultratypes.h"

typedef struct __osHwInt {
    /* 0x0 */ s32 (*handler)(void);
    /* 0x4 */ void* stackEnd;
} __osHwInt; // size = 0x8

#else

/* __osHwInt struct member offsets */
#define HWINT_CALLBACK 0x0
#define HWINT_SP       0x4

/* __osHwInt struct size */
#define HWINT_SIZE     0x8

#endif

#endif
