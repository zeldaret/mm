#ifndef Z_EN_DOOR_H
#define Z_EN_DOOR_H

#include "global.h"
#include "z64door.h"
#include "objects/gameplay_keep/gameplay_keep.h"

struct EnDoor;

typedef void (*EnDoorActionFunc)(struct EnDoor*, PlayState*);

#define ENDOOR_GET_TYPE(thisx) (((thisx)->params >> 7) & 7)
#define ENDOOR_GET_PARAM_7F(thisx) (((thisx)->params) & 0x7F)

typedef enum EnDoorType {
    /* 0 */ ENDOOR_TYPE_0,
    /* 1 */ ENDOOR_TYPE_1,
    /* 2 */ ENDOOR_TYPE_2,
    /* 3 */ ENDOOR_TYPE_3,
    /* 4 */ ENDOOR_TYPE_4,
    /* 5 */ ENDOOR_TYPE_5,
    /* 6 */ ENDOOR_TYPE_6,
    /* 7 */ ENDOOR_TYPE_7
} EnDoorType;

typedef struct EnDoor {
    /* 0x000 */ KnobDoorActor knobDoor;
    /* 0x1A4 */ u8 doorType;
    /* 0x1A5 */ u8 switchFlag;
    /* 0x1A6 */ u8 unk_1A6;
    /* 0x1A7 */ s8 unk_1A7;
    /* 0x1A8 */ Vec3s limbTable[DOOR_LIMB_MAX];
    /* 0x1C8 */ EnDoorActionFunc actionFunc;
} EnDoor;

#endif // Z_EN_DOOR_H
