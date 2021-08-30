#ifndef Z_EN_ENDING_HERO6_H
#define Z_EN_ENDING_HERO6_H

#include "global.h"

struct EnEndingHero6;

typedef void (*EnEndingHero6ActionFunc)(struct EnEndingHero6*, GlobalContext*);

typedef struct EnEndingHero6 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x134];
    /* 0x0278 */ EnEndingHero6ActionFunc actionFunc;
    /* 0x027C */ char unk_27C[0x18];
} EnEndingHero6; // size = 0x294

extern const ActorInit En_Ending_Hero6_InitVars;

#endif // Z_EN_ENDING_HERO6_H
