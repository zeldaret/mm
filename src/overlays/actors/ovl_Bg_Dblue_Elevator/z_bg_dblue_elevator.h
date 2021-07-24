#ifndef Z_BG_DBLUE_ELEVATOR_H
#define Z_BG_DBLUE_ELEVATOR_H

#include "global.h"

struct BgDblueElevator;

typedef struct BgDblueElevator {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2C];
} BgDblueElevator; // size = 0x170

extern const ActorInit Bg_Dblue_Elevator_InitVars;

#endif // Z_BG_DBLUE_ELEVATOR_H
