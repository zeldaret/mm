#ifndef Z_EN_MINIFROG_H
#define Z_EN_MINIFROG_H

#include <global.h>

struct EnMinifrog;

typedef void (*EnMinifrogActionFunc)(struct EnMinifrog*, GlobalContext*);

typedef struct EnMinifrog {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime anime;
    /* 0x188 */ Vec3s limbDrawTable[24];
    /* 0x218 */ Vec3s transitionDrawTable[24];
    /* 0x2A8 */ EnMinifrogActionFunc actionFunc;
    /* 0x2AC */ struct EnMinifrog* frog;
    /* 0x2B0 */ u16 unk_2B0;
    /* 0x2B2 */ s16 unk_2B2;
    /* 0x2B4 */ s16 timer;
    /* 0x2B6 */ u16 flags;
    /* 0x2B8 */ ColliderCylinder collider;
} EnMinifrog; // size = 0x304

extern const ActorInit En_Minifrog_InitVars;

#endif // Z_EN_MINIFROG_H
