#ifndef Z_EN_ENDING_HERO2_H
#define Z_EN_ENDING_HERO2_H

#include "global.h"

struct EnEndingHero2;

typedef void (*EnEndingHero2ActionFunc)(struct EnEndingHero2*, GlobalContext*);

typedef struct EnEndingHero2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[20];
    /* 0x200 */ Vec3s morphTable[20];
    /* 0x278 */ EnEndingHero2ActionFunc actionFunc;
    /* 0x27C */ u16 unk27C;
} EnEndingHero2; // size = 0x280

extern const ActorInit En_Ending_Hero2_InitVars;

#endif // Z_EN_ENDING_HERO2_H
