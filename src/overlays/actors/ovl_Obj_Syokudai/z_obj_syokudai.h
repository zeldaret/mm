#ifndef Z_OBJ_SYOKUDAI_H
#define Z_OBJ_SYOKUDAI_H

#include "global.h"

struct ObjSyokudai;

typedef struct ObjSyokudai {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder colliderCylinder1;
    /* 0x190 */ ColliderCylinder colliderCylinder2;
    /* 0x1DC */ s16 unk_1DC;
    /* 0x1DE */ u8 unk_1DE;
    /* 0x1DF */ s8 unk1DF;
    /* 0x1E0 */ LightNode* lightNode;
    /* 0x1E4 */ LightInfo lightInfo;
} ObjSyokudai; // size = 0x1F4

extern const ActorInit Obj_Syokudai_InitVars;

#define OBJ_SYOKUDAI_GET_PARAMS_HIGH(thisx) (thisx->params >> 0xC)
#define OBJ_SYOKUDAI_GET_PARAMS_MID(thisx) ((thisx->params >> 7) & 0xF)
#define OBJ_SYOKUDAI_GET_PARAMS_LOW(thisx) (thisx->params & 0x7F)

#endif // Z_OBJ_SYOKUDAI_H
