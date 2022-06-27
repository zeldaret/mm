#ifndef Z_OBJ_FIRESHIELD_H
#define Z_OBJ_FIRESHIELD_H

#include "global.h"

struct ObjFireshield;

typedef void (*ObjFireshieldActionFunc)(struct ObjFireshield*);

#define OBJFIRESHIELD_GET_7F(thisx) ((thisx)->params & 0x7F)
#define OBJFIRESHIELD_GET_1F00(thisx) (((thisx)->params >> 8) & 0x1F)
#define OBJFIRESHIELD_GET_2000(thisx) (((thisx)->params >> 0xD) & 1)
#define OBJFIRESHIELD_GET_3F80(thisx) (((thisx)->params >> 7) & 0x7F)
#define OBJFIRESHIELD_GET_C000(thisx) (((thisx)->params >> 0xE) & 3)
#define OBJFIRESHIELD_GET_ROTX(thisx) ((thisx)->home.rot.x & 1)

typedef struct ObjFireshield {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ ObjFireshieldActionFunc actionFunc;
    /* 0x0194 */ s32 unk_194;
    /* 0x0198 */ f32 unk_198;
    /* 0x019C */ s32 unk_19C;
    /* 0x01A0 */ s32 unk_1A0;
    /* 0x01A4 */ s16 unk_1A4;
    /* 0x01A6 */ u8 unk_1A6;
    /* 0x01A7 */ s8 unk_1A7;
    /* 0x01A8 */ s8 unk_1A8;
} ObjFireshield; // size = 0x1AC

extern const ActorInit Obj_Fireshield_InitVars;

#endif // Z_OBJ_FIRESHIELD_H
