#ifndef Z_EN_JG_H
#define Z_EN_JG_H

#include "global.h"

struct EnJg;

typedef void (*EnJgActionFunc)(struct EnJg*, GlobalContext*);

#define ENSGORO_GET_1(thisx) ((thisx)->params & 1)
#define ENSGORO_GET_FC00(thisx) (((thisx)->params & 0xFC00) >> 0xA)

typedef struct EnJg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ struct EnSGoro* unk_144;
    /* 0x0148 */ struct ObjIcePoly* unk_148;
    /* 0x014C */ ColliderCylinder collider;
    /* 0x0198 */ SkelAnime skelAnime;
    /* 0x01DC */ EnJgActionFunc actionFunc;
    /* 0x01E0 */ Path* path;
    /* 0x01E4 */ s32 unk_1E4;
    /* 0x01E8 */ struct ObjJgGakki* unk_1E8;
    /* 0x01EC */ Vec3s unk_1EC;
    /* 0x01F2 */ Vec3s unk_1F2;
    /* 0x01F8 */ Vec3s jointTable[35];
    /* 0x02CA */ Vec3s morphTable[35];
    /* 0x039C */ s16 unk_39C;
    /* 0x039E */ s16 unk_39E;
    /* 0x03A0 */ s16 unk_3A0;
    /* 0x03A2 */ s16 unk_3A2;
    /* 0x03A4 */ Vec3f unk_3A4;
    /* 0x03B0 */ Vec3f unk_3B0;
    /* 0x03BC */ Vec3f unk_3BC;
    /* 0x03C8 */ s16 unk_3C8;
    /* 0x03CA */ u8 unk_3CA;
    /* 0x03CB */ u8 unk_3CB;
    /* 0x03CC */ u16 unk_3CC;
    /* 0x03CE */ u16 unk_3CE;
    /* 0x03D0 */ u8 unk_3D0;
} EnJg; // size = 0x3D4

extern const ActorInit En_Jg_InitVars;

#endif // Z_EN_JG_H
