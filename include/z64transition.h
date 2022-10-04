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
    /* 0x0 */ char unk_0[0xC];
} TransitionFade; // size = 0xC

extern const TransitionInit TransitionFade_InitVars;


typedef enum {
 /* 0 */ TRANSITION_CIRCLE_IN,
 /* 1 */ TRANSITION_CIRCLE_OUT,
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
    /* 0x17 */ UNK_TYPE1 pad_17; // struct padding
    /* 0x18 */ TexturePtr texture;
    /* 0x1C */ u8 masks;
    /* 0x1D */ u8 maskt;
    /* 0x1E */ s8 unk_1E; // Set to 4 and never used
    /* 0x1F */ s8 unk_1F; // Set to 0 and never used
} TransitionCircle; // size = 0x20

extern const TransitionInit TransitionCircle_InitVars;

#endif
