#ifndef Z_EN_ENDING_HERO4_H
#define Z_EN_ENDING_HERO4_H

#include "global.h"

struct EnEndingHero4;

typedef void (*EnEndingHero4ActionFunc)(struct EnEndingHero4*, GlobalContext*);

typedef struct EnEndingHero4 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[17];
    /* 0x1EE */ Vec3s morphTable[17];
    /* 0x254 */ EnEndingHero4ActionFunc actionFunc;
    /* 0x258 */ u16 unk258;
} EnEndingHero4; // size = 0x25C

extern const ActorInit En_Ending_Hero4_InitVars;

#endif // Z_EN_ENDING_HERO4_H
