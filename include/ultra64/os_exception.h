#ifndef ULTRA64_OS_EXCEPTION_H
#define ULTRA64_OS_EXCEPTION_H

#include "ultratypes.h"


typedef u32 OSIntMask;

OSIntMask osGetIntMask(void);
OSIntMask osSetIntMask(OSIntMask im);

#endif
