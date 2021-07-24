#include "ultra64.h"
#include "global.h"

void osViExtendVStart(u32 a0) {
    __additional_scanline = a0;
}
