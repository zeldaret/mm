#ifndef _Z_EN_JGAME_TSN_H_
#define _Z_EN_JGAME_TSN_H_

#include <global.h>

struct EnJgameTsn;

typedef struct EnJgameTsn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1C0];
} EnJgameTsn; // size = 0x304

extern const ActorInit En_Jgame_Tsn_InitVars;

#endif
