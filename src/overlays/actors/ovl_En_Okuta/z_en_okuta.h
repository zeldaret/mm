#ifndef Z_EN_OKUTA_H
#define Z_EN_OKUTA_H

#include "global.h"

struct EnOkuta;

typedef void (*EnOkutaActionFunc)(struct EnOkuta*, PlayState*);

typedef struct EnOkuta {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime unk144;                   /* inferred */
    /* 0x188 */ EnOkutaActionFunc actionFunc;
    /* 0x18C */ u8 unk18C;
    /* 0x18C */ char pad18D[1];
    /* 0x18E */ s16 unk18E;                         /* inferred */
    /* 0x190 */ s16 unk190;                         /* inferred */
    /* 0x192 */ Vec3s unk192;                       /* inferred */
    /* 0x198 */ char pad198[0x5A];                  /* maybe part of unk192[0x10]? */
    /* 0x1F2 */ Vec3s unk1F2;                       /* inferred */
    /* 0x1F8 */ char pad1F8[0x5C];                  /* maybe part of unk1F2[0x10]? */
    /* 0x254 */ f32 unk254;                         /* inferred */
    /* 0x258 */ f32 unk258;                         /* inferred */
    /* 0x25C */ f32 unk25C;                         /* inferred */
    /* 0x260 */ f32 unk260;                         /* inferred */
    /* 0x264 */ Vec3f unk264;
    /* 0x270 */ Vec3f unk270[10];                       /* inferred */
    /* 0x2E8 */ ColliderCylinder unk2E8;            /* inferred */
} EnOkuta; // size = 0x334

#endif // Z_EN_OKUTA_H
