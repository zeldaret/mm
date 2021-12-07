#ifndef Z_BOSS_03_H
#define Z_BOSS_03_H

#include "global.h"

struct Boss03;

typedef void (*Boss03ActionFunc)(struct Boss03*, GlobalContext*);

typedef struct Boss03 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ UNK_TYPE1 unk_144[0x10E];
    /* 0x0252 */ s8 unk_252; // number of Tanron3 fish that are currently alive
    /* 0x0253 */ UNK_TYPE1 unk_253[0xD1];
    /* 0x0324 */ s16 unk_324;
    /* 0x0326 */ UNK_TYPE1 unk_326[0x2];
    /* 0x0328 */ Boss03ActionFunc actionFunc;
    /* 0x032C */ UNK_TYPE1 unk_32C[0x250];
} Boss03; // size = 0x57C

extern const ActorInit Boss_03_InitVars;

#endif // Z_BOSS_03_H
