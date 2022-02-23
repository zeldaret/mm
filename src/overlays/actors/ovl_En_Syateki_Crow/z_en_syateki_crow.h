#ifndef Z_EN_SYATEKI_CROW_H
#define Z_EN_SYATEKI_CROW_H

#include "global.h"

#define EN_SYATEKI_CROW_GET_PARAM_FF00(thisx) (((thisx)->params & 0xFF00) >> 8)

struct EnSyatekiCrow;

typedef void (*EnSyatekiCrowActionFunc)(struct EnSyatekiCrow*, GlobalContext*);

typedef struct EnSyatekiCrow {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x30];
    /* 0x174 */ SkelAnime skelAnime;
    /* 0x1B8 */ EnSyatekiCrowActionFunc actionFunc;
    /* 0x1BC */ s16 unk_1BC;
    /* 0x1BE */ char unk_1BE[0x6];
    /* 0x1C4 */ s16 unk_1C4;
    /* 0x1C6 */ char unk_1C6[0x2];
    /* 0x1C8 */ Vec3s* unk_1C8;
    /* 0x1CC */ s16 unk_1CC;
    /* 0x1CE */ s16 unk_1CE;
    /* 0x1D0 */ Vec3s jointTable[9];
    /* 0x206 */ Vec3s morphTable[9];
    /* 0x23C */ ColliderJntSph unk_23C;
    /* 0x25C */ ColliderJntSphElement unk_25C;
} EnSyatekiCrow; // size = 0x29C

extern const ActorInit En_Syateki_Crow_InitVars;

#endif // Z_EN_SYATEKI_CROW_H
