#ifndef OTHER_TYPES_H
#define OTHER_TYPES_H

#include "ultra64.h"

typedef void* TexturePtr;

typedef union HexFloat {
    u32 hex;
    f32 flt;
} HexFloat;

#endif
