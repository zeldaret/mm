#ifndef _MACROS_H_
#define _MACROS_H_

#include "convert.h"

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

// UB: u32 casts here should be uintptr_t casts.
// TODO: After uintptr_t cast change should have an AVOID_UB target that just toggles the KSEG0 bit in the address rather than add/sub 0x80000000
#define PHYSICAL_TO_VIRTUAL(addr) ((u32)(addr) + 0x80000000)
#define PHYSICAL_TO_VIRTUAL2(addr) ((u32)(addr) - 0x80000000)
#define SEGMENTED_TO_VIRTUAL(addr) (void*)(PHYSICAL_TO_VIRTUAL(gRspSegmentPhysAddrs[SEGMENT_NUMBER(addr)]) + SEGMENT_OFFSET(addr))

#define ALIGN16(val) (((val) + 0xF) & ~0xF)

// Currently most often called ctxt in MM, TODO: Refactor names when its used
#define ACTIVE_CAM globalCtx->cameraPtrs[globalCtx->activeCamera]

#define SET_NEXT_GAMESTATE(curState, newInit, newStruct) \
            (curState)->nextGameStateInit = (GameStateFunc)newInit; \
            (curState)->nextGameStateSize = sizeof(newStruct); 
        
#define PLAYER ((ActorPlayer*)globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first)

#define SQ(x) ((x)*(x))
#define DECR(x) ((x) == 0 ? 0 : ((x) -= 1))

extern GraphicsContext* oGfxCtx;

#define OPEN_DISPS(gfxCtx) \
    {                                  \
        GraphicsContext* oGfxCtx;      \
        oGfxCtx = gfxCtx;              \

#define CLOSE_DISPS(gfxCtx)                 \
    }                                       \
    (void)0

#define GRAPH_ALLOC(gfxCtx, size)         \
    ((gfxCtx)->polyOpa.d = (Gfx*)((u8*)(gfxCtx)->polyOpa.d - (size)))

#define SQ(x)      ((x)*(x))
#define ABS(x)     ((x) >= 0 ? (x) : -(x))
#define ABS_ALT(x) ((x) <  0 ? -(x) : (x))
#define DECR(x)    ((x) == 0 ? 0 : ((x) -= 1))

#define CLAMP(x, min, max) ((x) < (min) ? (min) : (x) > (max) ? (max) : (x))
#define CLAMP_MAX(x, max)  ((x) > (max) ? (max) : (x))
#define CLAMP_MIN(x, min)  ((x) < (min) ? (min) : (x))

#endif // _MACROS_H_
