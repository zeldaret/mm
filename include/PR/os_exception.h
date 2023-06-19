#ifndef ULTRA64_OS_EXCEPTION_H
#define ULTRA64_OS_EXCEPTION_H

#include "ultratypes.h"


typedef u32 OSIntMask;
typedef u32 OSHWIntr;

OSIntMask osGetIntMask(void);
OSIntMask osSetIntMask(OSIntMask im);


// Internal
void __osSetHWIntrRoutine(OSHWIntr idx, OSMesgQueue* queue, OSMesg msg);
void __osGetHWIntrRoutine(OSHWIntr idx, OSMesgQueue** outQueue, OSMesg* outMsg);
void __osSetGlobalIntMask(OSHWIntr mask);
void __osResetGlobalIntMask(OSHWIntr mask);


#endif
