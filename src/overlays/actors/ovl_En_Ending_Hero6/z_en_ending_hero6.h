#ifndef Z_EN_ENDING_HERO6_H
#define Z_EN_ENDING_HERO6_H

#include "global.h"

struct EnEndingHero6;

typedef void (*EnEndingHero6ActionFunc)(struct EnEndingHero6*, PlayState*);

typedef struct EnEndingHero6 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[20];
    /* 0x200 */ Vec3s morphTable[20];
    /* 0x278 */ EnEndingHero6ActionFunc actionFunc;
    /* 0x27C */ s32 animIndex;
    /* 0x280 */ s32 npcIndex;
    /* 0x284 */ s8 objectIndex;
    /* 0x286 */ s16 timer;
    /* 0x288 */ s16 blinkTimer;
    /* 0x28A */ s16 eyeState;
    /* 0x28C */ f32 frameCount;
    /* 0x290 */ s16 isIdle;
} EnEndingHero6; // size = 0x294

extern const ActorInit En_Ending_Hero6_InitVars;

#endif // Z_EN_ENDING_HERO6_H
