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
} TransitionInit;

typedef struct {
    /* 0x000 */ char unk_0[0xC];
} TransitionFade; // size = 0xC

extern const TransitionInit TransitionFade_InitVars;

typedef struct {
    /* 0x000 */ char unk_0[0x20];
} TransitionCircle; // size = 0x20

extern const TransitionInit TransitionCircle_InitVars;

#endif
