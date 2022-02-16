#ifndef Z_BG_CTOWER_GEAR_H
#define Z_BG_CTOWER_GEAR_H

#include "global.h"

struct BgCtowerGear;


#define BGCTOWERGEAR_GET_TYPE(thisx) ((thisx)->params & 3)

typedef enum {
    /* 0x00 */ BGCTOWERGEAR_CEILING_COG,
    /* 0x01 */ BGCTOWERGEAR_CENTER_COG,
    /* 0x02 */ BGCTOWERGEAR_WATER_WHEEL,
    /* 0x03 */ BGCTOWERGEAR_ORGAN
} BgCtowerGearType;

typedef struct BgCtowerGear {
    /* 0x000 */ DynaPolyActor dyna;
} BgCtowerGear; // size = 0x15C

extern const ActorInit Bg_Ctower_Gear_InitVars;

#endif // Z_BG_CTOWER_GEAR_H
