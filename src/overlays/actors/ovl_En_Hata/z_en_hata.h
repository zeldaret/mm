#ifndef Z_EN_HATA_H
#define Z_EN_HATA_H

#include "global.h"

struct EnHata;

typedef struct EnHata {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ SkelAnime skelAnime;
    /* 0x1A0 */ Vec3s jointTable;
    /* 0x1A6 */ char pad_1A6[0x78];
    /* 0x21E */ Vec3s morphTable;
    /* 0x224 */ char pad_224[0x78];
    /* 0x29C */ s16 unk_29C;
    /* 0x29E */ char pad_29E;
    /* 0x2A0 */ s16 unk_2A0;
    /* 0x2A4 */ Vec3f unk_2A4;
} EnHata; /* size = 0x2B0 */

extern const ActorInit En_Hata_InitVars;

#endif // Z_EN_HATA_H
