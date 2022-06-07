#ifndef Z_EN_HATA_H
#define Z_EN_HATA_H

#include "global.h"

struct EnHata;

typedef struct EnHata {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ SkelAnime skelAnime;
    /* 0x1A0 */ Vec3s unk1A0;
    /* 0x1A6 */ char pad1A6[0x78];                  /* maybe part of unk1A0[0x15]? */
    /* 0x21E */ Vec3s unk21E;
    /* 0x224 */ char pad224[0x78];                  /* maybe part of unk21E[0x15]? */
    /* 0x29C */ s16 unk29C;                         /* inferred */
    /* 0x29E */ char pad29E[2];
    /* 0x2A0 */ s16 unk2A0;                         /* inferred */
    /* 0x2A2 */ char pad2A2[2];
    /* 0x2A4 */ f32 unk2A4;                         /* inferred */
    /* 0x2A8 */ f32 unk2A8;                         /* inferred */
    /* 0x2AC */ f32 unk2AC;                         /* inferred */
} EnHata;                                           /* size = 0x2B0 */

extern const ActorInit En_Hata_InitVars;

#endif // Z_EN_HATA_H
