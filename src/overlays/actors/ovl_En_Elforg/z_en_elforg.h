#ifndef Z_EN_ELFORG_H
#define Z_EN_ELFORG_H

#include "global.h"

struct EnElforg;

typedef void (*EnElforgActionFunc)(struct EnElforg*, GlobalContext*);

typedef struct EnElforg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[10];
    /* 0x1C4 */ ColliderCylinder collider;
    /* 0x210 */ Actor* enemy;
    /* 0x214 */ u16 unk_214;
    /* 0x216 */ s16 unk_216;
    /* 0x218 */ s16 unk_218;
    /* 0x21C */ s32 unk_21C;
    /* 0x220 */ s32 unk_220;
    /* 0x224 */ f32 unk_224;
    /* 0x228 */ f32 unk_228;
    /* 0x22C */ EnElforgActionFunc actionFunc;
} EnElforg; // size = 0x230

extern const ActorInit En_Elforg_InitVars;

#endif // Z_EN_ELFORG_H
