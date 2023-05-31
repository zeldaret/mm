#ifndef Z_DOOR_SHUTTER_H
#define Z_DOOR_SHUTTER_H

#include "global.h"
#include "z64door.h"

struct DoorShutter;

typedef void (*DoorShutterActionFunc)(struct DoorShutter*, PlayState*);

#define DOORSHUTTER_GET_1F(thisx) ((thisx)->params & 0x1F)
#define DOORSHUTTER_GET_7F(thisx) ((thisx)->params & 0x7F)
#define DOORSHUTTER_GET_380(thisx) (((thisx)->params >> 7) & 7)

typedef struct DoorShutter {
    /* 0x000 */ SlidingDoorActor slidingDoor;
    /* 0x160 */ s16 csId;
    /* 0x0162 */ u8 doorType;
    /* 0x0163 */ u8 unk_163;
    /* 0x0164 */ u8 unk_164;
    /* 0x0165 */ s8 requiredObjBankIndex;
    /* 0x0166 */ s8 unk_166;
    /* 0x0167 */ s8 unk_167;
    /* 0x0168 */ f32 unk_168;
    /* 0x016C */ DoorShutterActionFunc actionFunc;
} DoorShutter; // size = 0x170

#endif // Z_DOOR_SHUTTER_H
