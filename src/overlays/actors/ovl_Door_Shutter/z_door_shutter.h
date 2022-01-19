#ifndef Z_DOOR_SHUTTER_H
#define Z_DOOR_SHUTTER_H

#include "global.h"

struct DoorShutter;

typedef void (*DoorShutterActionFunc)(struct DoorShutter*, GlobalContext*);

#define DOORSHUTTER_GET_1F(thisx) ((thisx)->params & 0x1F)
#define DOORSHUTTER_GET_7F(thisx) ((thisx)->params & 0x7F)
#define DOORSHUTTER_GET_380(thisx) (((thisx)->params >> 7) & 7)
#define DOORSHUTTER_GET_FC00(thisx) (((u16)(thisx)->params >> 0xA))

typedef struct DoorShutter {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ UNK_TYPE1 unk144[0x18];
    /* 0x015C */ s16 unk_15C;
    /* 0x015E */ s16 unk_15E;
    /* 0x0160 */ s16 unk_160;
    /* 0x0162 */ u8 doorType;
    /* 0x0163 */ u8 unk_163;
    /* 0x0164 */ u8 unk_164;
    /* 0x0165 */ s8 requiredObjBankIndex;
    /* 0x0166 */ s8 unk_166;
    /* 0x0167 */ s8 unk_167;
    /* 0x0168 */ f32 unk_168;
    /* 0x016C */ DoorShutterActionFunc actionFunc;
} DoorShutter; // size = 0x170

extern const ActorInit Door_Shutter_InitVars;

#endif // Z_DOOR_SHUTTER_H
