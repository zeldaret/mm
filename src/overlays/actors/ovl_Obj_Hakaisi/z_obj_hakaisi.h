#ifndef Z_OBJ_HAKAISI_H
#define Z_OBJ_HAKAISI_H

#include "global.h"

struct ObjHakaisi;

typedef void (*ObjHakaisiActionFunc)(struct ObjHakaisi*, GlobalContext*);

#define OBJHAKAISI_GET_FF(thisx) ((thisx)->params & 0xFF)
#define OBJHAKAISI_GET_SWITCHFLAG(thisx) (((thisx)->params & 0xFF00) >> 8)

typedef struct ObjHakaisi {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ ObjHakaisiActionFunc actionFunc;
    /* 0x0160 */ Vec3f unk_160[3];
    /* 0x0184 */ Vec3f unk_184;
    /* 0x0190 */ s32 switchFlag;
    /* 0x0194 */ s16 unk_194;
    /* 0x0196 */ s16 unk_196;
    /* 0x0198 */ s16 unk_198;
    /* 0x019A */ s16 unk_19A;
    /* 0x019C */ s16 unk_19C;
    /* 0x019E */ u8 unk_19E;
} ObjHakaisi; // size = 0x1A0

extern const ActorInit Obj_Hakaisi_InitVars;

#endif // Z_OBJ_HAKAISI_H
