#ifndef Z_EN_CROW_H
#define Z_EN_CROW_H

#include "global.h"
#include "objects/object_crow/object_crow.h"

struct EnCrow;

typedef void (*EnCrowActionFunc)(struct EnCrow*, GlobalContext*);

typedef struct EnCrow {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnCrowActionFunc actionFunc;
    /* 0x18C */ s8 unk18C;                          /* inferred */
    /* 0x18D */ char pad18D[1];
    /* 0x18E */ s16 unk18E;
    /* 0x190 */ char pad190[4];                     /* maybe part of unk18E[3]? */
    /* 0x194 */ Vec3s unk194;
    /* 0x19A */ char pad19A[0x30];                  /* maybe part of unk194[9]? */
    /* 0x1CA */ Vec3s unk1CA;
    /* 0x1D0 */ char pad1D0[0x30];                  /* maybe part of unk1CA[9]? */
    /* 0x200 */ ColliderJntSph unk200;
    /* 0x220 */ ColliderJntSphElement unk220;
    /* 0x260 */ char pad260[0x30];
    /* 0x290 */ f32 unk290;                         /* inferred */
    /* 0x294 */ f32 unk294;                         /* inferred */
    /* 0x298 */ char pad298[4];
} EnCrow; // size = 0x29C

extern const ActorInit En_Crow_InitVars;

#endif // Z_EN_CROW_H
