#ifndef Z_BG_DBLUE_ELEVATOR_H
#define Z_BG_DBLUE_ELEVATOR_H

#include "global.h"

struct BgDblueElevator;

typedef void (*BgDblueElevatorActionFunc)(struct BgDblueElevator*, PlayState*);

typedef struct BgDblueElevator {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x18];
    /* 0x15C */ BgDblueElevatorActionFunc actionFunc;
    /* 0x160 */ char unk_160[0x10];
} BgDblueElevator; // size = 0x170

#endif // Z_BG_DBLUE_ELEVATOR_H
