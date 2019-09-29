#ifndef _STRUCTS_BITFIELDS_H_
#define _STRUCTS_BITFIELDS_H_

#include <PR/ultratypes.h>

typedef struct {
    u32 cont : 1;
    u32 type : 4;
    u32 offset : 11;
    s32 value : 16;
} z_ActorCompInitEntry;

#endif
