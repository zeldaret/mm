#include <ultra64.h>
#include <global.h>

void func_801727F0(TwoHeadGfxArena* thga, Gfx* start, u32 size) {
    GameStateHeap_Init((TwoHeadArena*)thga, start, size);
}

void func_80172810(TwoHeadGfxArena* thga) {
    GameStateHeap_Clear((TwoHeadArena*)thga);
}

u32 func_80172830(TwoHeadGfxArena* thga) {
    return GameStateHeap_GetHasOverflowed((TwoHeadArena*)thga);
}

void func_80172850(TwoHeadGfxArena* thga) {
    GameStateHeap_InitAppend((TwoHeadArena*)thga);
}

s32 func_80172870(TwoHeadGfxArena* thga) {
    return GameStateHeap_GetFreeSize((TwoHeadArena*)thga);
}

Gfx* func_80172890(TwoHeadGfxArena* thga) {
    return GameStateHeap_GetStart((TwoHeadArena*)thga);
}

void func_801728B0(TwoHeadGfxArena* thga, Gfx* start) {
    GameStateHeap_SetStart((TwoHeadArena*)thga, start);
}

Gfx* func_801728D0(TwoHeadGfxArena* thga) {
    return GameStateHeap_GetEnd((TwoHeadArena*)thga);
}

Gfx* func_801728F0(TwoHeadGfxArena* thga, u32 count) {
    return GameStateHeap_Alloc((TwoHeadArena*)thga, count * 8);
}

Gfx* func_80172914(TwoHeadGfxArena* thga) {
    return func_801728F0(thga, 1);
}

Gfx* func_80172934(TwoHeadGfxArena* thga) {
    return func_80172914(thga);
}

Gfx* func_80172954(TwoHeadGfxArena* thga, u32 size) {
    return GameStateHeap_AllocFromEndAlignedTo((TwoHeadArena*)thga, size);
}

Gfx* func_80172974(TwoHeadGfxArena* thga, u32 count) {
    return func_80172954(thga, count * 0x40);
}

Gfx* func_80172998(TwoHeadGfxArena* thga) {
    return func_80172954(thga, 0x40);
}

Gfx* func_801729B8(TwoHeadGfxArena* thga, u32 count) {
    return func_80172954(thga, count * 0x10);
}

Gfx* func_801729DC(TwoHeadGfxArena* thga) {
    return func_80172954(thga, 0x10);
}