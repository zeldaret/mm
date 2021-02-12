#ifndef Z_EN_ENDING_HERO3_H
#define Z_EN_ENDING_HERO3_H

#include <global.h>

struct EnEndingHero3;

typedef void (*EnEndingHero3ActionFunc)(struct BgHakaCurtain*, GlobalContext*);

typedef struct EnEndingHero3 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s limbDrawTable[17];
    /* 0x1EE */ Vec3s transitionDrawTable[17];
    /* 0x254 */ EnEndingHero3ActionFunc actionFunc;
    /* 0x258 */ u16 unk258;
} EnEndingHero3; // size = 0x25C

extern const ActorInit En_Ending_Hero3_InitVars;

#endif // Z_EN_ENDING_HERO3_H
