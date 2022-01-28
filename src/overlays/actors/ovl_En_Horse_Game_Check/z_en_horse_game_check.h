#ifndef Z_EN_HORSE_GAME_CHECK_H
#define Z_EN_HORSE_GAME_CHECK_H

#include "global.h"

struct EnHorseGameCheck;

typedef struct EnHorseGameCheck {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x74];
} EnHorseGameCheck; // size = 0x1B8

extern const ActorInit En_Horse_Game_Check_InitVars;

#endif // Z_EN_HORSE_GAME_CHECK_H
