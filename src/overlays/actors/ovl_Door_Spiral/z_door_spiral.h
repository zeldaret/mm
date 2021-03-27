#ifndef Z_DOOR_SPIRAL_H
#define Z_DOOR_SPIRAL_H

#include <global.h>

struct DoorSpiral;

typedef void (*DoorSpiralActionFunc)(struct DoorSpiral*, GlobalContext*);

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

extern const ActorInit Door_Spiral_InitVars;

#endif // Z_DOOR_SPIRAL_H
