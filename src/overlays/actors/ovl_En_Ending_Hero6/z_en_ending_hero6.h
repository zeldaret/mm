#ifndef Z_EN_ENDING_HERO6_H
#define Z_EN_ENDING_HERO6_H

#include "global.h"

struct EnEndingHero6;

typedef void (*EnEndingHero6ActionFunc)(struct EnEndingHero6*, GlobalContext*);

typedef struct EnEndingHero6 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[20];
    /* 0x0200 */ Vec3s morphTable[20];
    /* 0x0278 */ EnEndingHero6ActionFunc actionFunc;
    /* 0x027C */ s32 animIndex;
    /* 0x0280 */ s32 npcIndex;
    /* 0x0284 */ s8 objectIndex;
    /* 0x0286 */ s16 timer;
    /* 0x0288 */ s16 blinkTimer;
    /* 0x028A */ s16 eyeState;
    /* 0x028C */ f32 frameCount;
    /* 0x0290 */ s16 isIdle;
} EnEndingHero6; // size = 0x294

extern const ActorInit En_Ending_Hero6_InitVars;

#endif // Z_EN_ENDING_HERO6_H
