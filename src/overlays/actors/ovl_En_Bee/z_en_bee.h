#ifndef Z_EN_BEE_H
#define Z_EN_BEE_H

#include "global.h"

struct EnBee;

typedef void (*EnBeeActionFunc)(struct EnBee*, PlayState*);

typedef struct EnBee {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;                   /* inferred */
    /* 0x188 */ Vec3s morphTable;                       /* inferred */
    /* 0x18E */ char pad18E[0x36];                  /* maybe part of unk188[0xA]? */
    /* 0x1C4 */ Vec3s jointTable;                       /* inferred */
    /* 0x1CA */ char pad1CA[0x36];                  /* maybe part of unk1C4[0xA]? */
    /* 0x200 */ EnBeeActionFunc actionFunc;
    /* 0x204 */ s16 unk204;
    /* 0x206 */ s16 unk206;                         /* inferred */
    /* 0x208 */ s16 unk208;
    s32 unk20C;
    /* 0x210 */ s32 unk210; // ex s32
                //s16 unk212;
    /* 0x214 */ s32 unk214;
    /* 0x218 */ s32 unk218;
    /* 0x21C */ Vec3f unk21C;
    /* 0x228 */ Vec3f unk228;
    /* 0x234 */ char pad234[8];
    /* 0x23C */ ColliderCylinder unk23C;
} EnBee;

extern const ActorInit En_Bee_InitVars;

#endif // Z_EN_BEE_H
