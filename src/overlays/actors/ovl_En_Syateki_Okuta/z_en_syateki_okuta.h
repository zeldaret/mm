#ifndef Z_EN_SYATEKI_OKUTA_H
#define Z_EN_SYATEKI_OKUTA_H

#include "global.h"

#define EN_SYATEKI_OKUTA_GET_F(thisx) ((thisx)->params & 0xF)

struct EnSyatekiOkuta;

typedef void (*EnSyatekiOkutaActionFunc)(struct EnSyatekiOkuta*, GlobalContext*);

typedef struct EnSyatekiOkuta {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnSyatekiOkutaActionFunc actionFunc;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1DC */ Vec3f unk_1D8;
    /* 0x1E4 */ Vec3s jointTable[16];
    /* 0x244 */ Vec3s morphTable[16];
    /* 0x2A4 */ s16 unk_2A4;
    /* 0x2A6 */ s16 unk_2A6;
    /* 0x2A8 */ UNK_TYPE1 unk_2A8[0x2];
    /* 0x2AA */ s16 unk_2AA;
} EnSyatekiOkuta; // size = 0x2AC

extern const ActorInit En_Syateki_Okuta_InitVars;

#endif // Z_EN_SYATEKI_OKUTA_H
