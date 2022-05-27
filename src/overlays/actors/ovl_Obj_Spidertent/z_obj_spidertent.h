#ifndef Z_OBJ_SPIDERTENT_H
#define Z_OBJ_SPIDERTENT_H

#include "global.h"

struct ObjSpidertent;

typedef void (*ObjSpidertentActionFunc)(struct ObjSpidertent*, GlobalContext*);

#define OBJSPIDERTENT_GET_1(thisx) ((thisx)->params & 1)
#define OBJSPIDERTENT_GET_7F00(thisx) (((thisx)->params >> 8) & 0x7F)

typedef struct ObjSpidertent {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ ColliderTris collider;
    /* 0x017C */ ColliderTrisElement colliderElements[6];
    /* 0x03A4 */ Vec3f unk_3A4;
    /* 0x03B0 */ f32 unk_3B0[4];
    /* 0x03C0 */ u8 unk_3C0;
    /* 0x03C1 */ s8 unk_3C1;
    /* 0x03C2 */ u8 unk_3C2;
    /* 0x03C3 */ u8 unk_3C3;
    /* 0x03C4 */ u8 unk_3C4;
    /* 0x03C5 */ u8 unk_3C5;
    /* 0x03C6 */ s8 unk_3C6;
    /* 0x03C7 */ s8 unk_3C7;
    /* 0x03C8 */ ObjSpidertentActionFunc actionFunc;
} ObjSpidertent; // size = 0x3CC

extern const ActorInit Obj_Spidertent_InitVars;

#endif // Z_OBJ_SPIDERTENT_H
