#ifndef Z_DOOR_WARP1_H
#define Z_DOOR_WARP1_H

#include "global.h"

struct DoorWarp1;

typedef void (*DoorWarp1ActionFunc)(struct DoorWarp1*, GlobalContext*);

typedef struct DoorWarp1 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x94];
    /* 0x01D8 */ DoorWarp1ActionFunc actionFunc;
    /* 0x01DC */ char unk_1DC[0x27];
    /* 0x0203 */ u8 unk_203;
    /* 0x0204 */ f32 unk_204;
    /* 0x0208 */ char unk_208[0x4];
} DoorWarp1; // size = 0x20C

extern const ActorInit Door_Warp1_InitVars;

#endif // Z_DOOR_WARP1_H
