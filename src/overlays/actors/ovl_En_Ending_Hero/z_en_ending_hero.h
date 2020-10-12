#ifndef Z_EN_ENDING_HERO_H
#define Z_EN_ENDING_HERO_H

#include <global.h>

struct EnEndingHero;

typedef void (*EnEndingHeroActionFunc)(struct BgHakaCurtain*, GlobalContext*);

typedef struct EnEndingHero {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s limbDrawTable[15];
    /* 0x1E2 */ Vec3s transitionDrawTable[15];
    /* 0x23C */ EnEndingHeroActionFunc actionFunc;
    /* 0x240 */ s16 unk240;
    /* 0x242 */ s16 unk242;
    /* 0x244 */ u16 unk244;
} EnEndingHero; // size = 0x248

extern const ActorInit En_Ending_Hero_InitVars;

#endif // Z_EN_ENDING_HERO_H
