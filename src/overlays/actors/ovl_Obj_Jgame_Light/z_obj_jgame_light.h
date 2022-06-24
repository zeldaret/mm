#ifndef Z_OBJ_JGAME_LIGHT_H
#define Z_OBJ_JGAME_LIGHT_H

#include "global.h"

struct ObjJgameLight;

#define OBJJGAMELIGHT_GET_7F(thisx) ((thisx)->params & 0x7F)

typedef struct ObjJgameLight {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ UNK_TYPE1 pad_190[4];
    /* 0x194 */ LightNode* lightNode;
    /* 0x198 */ LightInfo lightInfo;
    /* 0x1A8 */ f32 unk_1A8;
    /* 0x1AC */ s16 unk_1AC;
    /* 0x1AE */ s16 unk_1AE;
    /* 0x1B0 */ UNK_TYPE1 pad_1B0[2];
    /* 0x1B2 */ s16 unk_1B2;
    /* 0x1B4 */ s16 unk_1B4;
    /* 0x1B6 */ s16 unk_1B6;
    /* 0x1B8 */ u8 unk_1B8;
} ObjJgameLight; /* size = 0x1BC */

extern const ActorInit Obj_Jgame_Light_InitVars;

#endif // Z_OBJ_JGAME_LIGHT_H
