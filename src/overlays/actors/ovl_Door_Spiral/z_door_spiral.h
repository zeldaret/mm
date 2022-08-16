#ifndef Z_DOOR_SPIRAL_H
#define Z_DOOR_SPIRAL_H

#include "global.h"

struct DoorSpiral;

#define DOORSPIRAL_GET_ORIENTATION(thisx) (((thisx)->params >> 7) & 0x1)
#define DOORSPIRAL_GET_UNK145(thisx) (((thisx)->params >> 8) & 0x3)
#define DOORSPIRAL_GET_TRANSITION_ID(thisx) ((u16)(thisx)->params >> 10)

typedef void (*DoorSpiralActionFunc)(struct DoorSpiral*, PlayState*);

typedef struct DoorSpiral {
    /* 0x000 */ Actor actor;
    /* 0x144 */ u8 shouldClimb; // Flag used to determine if the player should climb the stairs
    /* 0x145 */ u8 unk145;
    /* 0x146 */ u8 orientation; // Upward or downward staircase
    /* 0x147 */ u8 objectType;  // Index to list of objects
    /* 0x148 */ u8 spiralType;  // Type of skin the staircase should use
    /* 0x149 */ s8 bankIndex;   // Object bank to use
    /* 0x14A */ s8 unk14A;
    /* 0x14C */ DoorSpiralActionFunc actionFunc;
} DoorSpiral; // size = 0x150

#endif // Z_DOOR_SPIRAL_H
