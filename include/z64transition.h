#ifndef _Z64_TRANSITION_H_
#define _Z64_TRANSITION_H_

#include "ultra64.h"

#define TC_SET_PARAMS (1 << 7)

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
        };
    /* 0x00 */ u32 word;
    } loadInfo;
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
    /* 0x003 */ char unk_003[0x22B];
    /* 0x230 */ void* (*init)(void* transition);
    /* 0x234 */ void  (*destroy)(void* transition);
    /* 0x238 */ void  (*update)(void* transition, s32 updateRate);
    /* 0x23C */ void  (*draw)(void* transition, Gfx** gfxP);
    /* 0x240 */ void  (*start)(void* transition);
    /* 0x244 */ void  (*setType)(void* transition, s32 type);
    /* 0x248 */ void  (*setColor)(void* transition, u32 color);
    /* 0x24C */ void  (*setEnvColor)(void* transition, u32 color);
    /* 0x250 */ s32   (*isDone)(void* transition);
    /* 0x254 */ char unk_254[0x4];
} TransitionContext; // size = 0x258

typedef enum {
    /* 1 */ TRANS_FADE_TYPE_IN = 1,
    /* 2 */ TRANS_FADE_TYPE_OUT,
} TransitionTypeFade;

#define TRANS_TYPE_FADE_FLASH 3

typedef struct {
    /* 0x0 */ u8 type;
    /* 0x1 */ u8 isDone;
    /* 0x2 */ u8 direction;
    /* 0x4 */ Color_RGBA8_u32 color;
    /* 0x8 */ u16 timer;
} TransitionFade; // size = 0xC

typedef enum {
 /* 0 */ TRANSITION_CIRCLE_FADE_OUT,
 /* 1 */ TRANSITION_CIRCLE_FADE_IN,
} TransitionCircleDirection;

#define FBDEMO_CIRCLE_GET_MASK_TYPE(type) (type & 1)

typedef struct {
    /* 0x00 */ Color_RGBA8_u32 color;
    /* 0x04 */ f32 referenceRadius; // Reference for where to transition to
    /* 0x08 */ f32 stepValue; // How fast the Transition is 
    /* 0x0C */ f32 startingRadius; // Radius value where transition will begin
    /* 0x10 */ f32 targetRadius; // Final radius of transition circle
    /* 0x14 */ u8 direction; // Direction the circle is transitioning ( In / Out )
    /* 0x15 */ u8 maskType; // Positive / Negative mask type. Value of 0 will create a black circle
    /* 0x16 */ u8 isDone; // Signals when Transition is done updating
    /* 0x18 */ TexturePtr texture;
    /* 0x1C */ u8 masks;
    /* 0x1D */ u8 maskt;
    /* 0x1E */ s8 unk_1E; // Set to 4 and never used
    /* 0x1F */ s8 unk_1F; // Set to 0 and never used
} TransitionCircle; // size = 0x20

#endif
