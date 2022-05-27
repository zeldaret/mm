#ifndef Z_EN_JGAME_TSN_H
#define Z_EN_JGAME_TSN_H

#include "global.h"

struct EnJgameTsn;

typedef void (*EnJgameTsnActionFunc)(struct EnJgameTsn*, GlobalContext*);

typedef struct EnJgameTsn {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x90];
    /* 0x01D4 */ EnJgameTsnActionFunc actionFunc;
    /* 0x01D8 */ char unk_1D8[0x12C];
} EnJgameTsn; // size = 0x304

extern const ActorInit En_Jgame_Tsn_InitVars;

#endif // Z_EN_JGAME_TSN_H
