#ifndef _Z64_TRANSITION_H_
#define _Z64_TRANSITION_H_

#include "ultra64.h"

typedef struct {
    /* 0x00 */ void* (*init)(void* transition);
    /* 0x04 */ void  (*destroy)(void* transition);
    /* 0x08 */ void  (*update)(void* transition, s32 updateRate);
    /* 0x0C */ void  (*draw)(void* transition, Gfx** gfxP);
    /* 0x10 */ void  (*start)(void* transition);
    /* 0x14 */ void  (*setType)(void* transition, s32 type);
    /* 0x18 */ void  (*setColor)(void* transition, u32 color);
    /* 0x1C */ void  (*setEnvColor)(void* transition, u32 color);
    /* 0x20 */ s32   (*isDone)(void* transition);
} TransitionInit; // size = 0x24

typedef struct {
    union {
        struct {
    /* 0x00 */ u32 count : 8;
    /* 0x00 */ uintptr_t addr : 24;
        } load;
    /* 0x00 */ u32 loadInfo;
    };
    /* 0x04 */ void* vramStart;
    /* 0x08 */ void* vramEnd;
    /* 0x0C */ uintptr_t vromStart;
    /* 0x10 */ uintptr_t vromEnd;
    /* 0x14 */ TransitionInit* initInfo;
    /* 0x18 */ size_t size;
} TransitionOverlay;
 
typedef struct {
    /* 0x000 */ s16 transitionType;
    /* 0x002 */ s8 fbdemoType;
    /* 0x003 */ char unk03[0x5];
    /* 0x008 */ s32 instanceData;
    /* 0x00C */ char unk0C[0x224];
    /*
    union {
       TransitionFade fade;
       TransitionCircle circle;
       TransitionTriforce triforce;
       TransitionWipe wipe;
    } instanceData;
    */
    /* 0x230 */ void* (*init)(void* transition);
    /* 0x234 */ void  (*destroy)(void* transition);
    /* 0x238 */ void  (*update)(void* transition, s32 updateRate);
    /* 0x23C */ void  (*draw)(void* transition, Gfx** gfxP);
    /* 0x240 */ void  (*start)(void* transition);
    /* 0x244 */ void  (*setType)(void* transition, s32 type);
    /* 0x248 */ void  (*setColor)(void* transition, u32 color);
    /* 0x24C */ void  (*setEnvColor)(void* transition, u32 color);
    /* 0x250 */ s32   (*isDone)(void* transition);
    /* 0x254 */ char unk254[0x4];
} TransitionContext; // size = 0x258

typedef struct {
    /* 0x0 */ char unk_0[0xC];
} TransitionFade; // size = 0xC

extern TransitionInit TransitionFade_InitVars;

typedef struct {
    /* 0x00 */ char unk_0[0x20];
} TransitionCircle; // size = 0x20

extern TransitionInit TransitionCircle_InitVars;

#endif
