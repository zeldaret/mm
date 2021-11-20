#ifndef Z_BG_DBLUE_ELEVATOR_H
#define Z_BG_DBLUE_ELEVATOR_H

#include "global.h"

struct BgDblueElevator;

typedef void (*BgDblueElevatorActionFunc)(struct BgDblueElevator*, GlobalContext*);

typedef struct BgDblueElevator {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ BgDblueElevatorActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x10];
} BgDblueElevator; // size = 0x170

extern const ActorInit Bg_Dblue_Elevator_InitVars;

#endif // Z_BG_DBLUE_ELEVATOR_H
