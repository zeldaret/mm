#ifndef Z_OBJ_DORA_H
#define Z_OBJ_DORA_H

#include "global.h"

struct ObjDora;

typedef void (*ObjDoraActionFunc)(struct ObjDora*, GlobalContext*);

typedef struct ObjDora {
    /* 0x0000 */ Actor actor; // good
    /* 0x0144 */ ColliderTris colliderTris; // good, size 0x20
    /* 0x0164 */ ColliderTrisElement colliderTrisElements[6]; // good
    /* 0x038C */ ObjDoraActionFunc actionFunc; // good
    /* 0x0390 */ f32 unk390; // good
    /* 0x0394 */ f32 unk394; // good 
    /* 0x0398 */ f32 unk398; // good
    /* 0x039C */ s16 unk39C; // good
    /* 0x039E */ s16 unk39E; // good
    /* 0x03A0 */ s16 unk3A0; // good
    /* 0x03A2 */ s16 unk3A2; // good
    /* 0x03A4 */ s16 unk3A4; // good
    /* 0x03A6 */ s16 unk3A6; // good
    /* 0x03A8 */ s16 unk3A8; // good
    /* 0x03AA */ s16 unk3AA; // good
} ObjDora; // size = 0x3AC

extern const ActorInit Obj_Dora_InitVars;

#endif // Z_OBJ_DORA_H
