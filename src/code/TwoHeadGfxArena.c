#include "global.h"

void THGA_Ct(TwoHeadGfxArena* thga, Gfx* start, size_t size) {
    THA_Ct((TwoHeadArena*)thga, start, size);
}

void THGA_Dt(TwoHeadGfxArena* thga) {
    THA_Dt((TwoHeadArena*)thga);
}

u32 THGA_IsCrash(TwoHeadGfxArena* thga) {
    return THA_IsCrash((TwoHeadArena*)thga);
}

void THGA_Init(TwoHeadGfxArena* thga) {
    THA_Init((TwoHeadArena*)thga);
}

s32 THGA_GetSize(TwoHeadGfxArena* thga) {
    return THA_GetSize((TwoHeadArena*)thga);
}

Gfx* THGA_GetHead(TwoHeadGfxArena* thga) {
    return THA_GetHead((TwoHeadArena*)thga);
}

void THGA_SetHead(TwoHeadGfxArena* thga, Gfx* start) {
    THA_SetHead((TwoHeadArena*)thga, start);
}

Gfx* THGA_GetTail(TwoHeadGfxArena* thga) {
    return THA_GetTail((TwoHeadArena*)thga);
}

Gfx* THGA_AllocStartArray8(TwoHeadGfxArena* thga, u32 count) {
    return THA_AllocStart((TwoHeadArena*)thga, count * 8);
}

Gfx* THGA_AllocStart8(TwoHeadGfxArena* thga) {
    return THGA_AllocStartArray8(thga, 1);
}

Gfx* THGA_AllocStart8Wrapper(TwoHeadGfxArena* thga) {
    return THGA_AllocStart8(thga);
}

Gfx* THGA_AllocEnd(TwoHeadGfxArena* thga, size_t size) {
    return THA_AllocEnd((TwoHeadArena*)thga, size);
}

Gfx* THGA_AllocEndArray64(TwoHeadGfxArena* thga, u32 count) {
    return THGA_AllocEnd(thga, count * 0x40);
}

Gfx* THGA_AllocEnd64(TwoHeadGfxArena* thga) {
    return THGA_AllocEnd(thga, 0x40);
}

Gfx* THGA_AllocEndArray16(TwoHeadGfxArena* thga, u32 count) {
    return THGA_AllocEnd(thga, count * 0x10);
}

Gfx* THGA_AllocEnd16(TwoHeadGfxArena* thga) {
    return THGA_AllocEnd(thga, 0x10);
}
