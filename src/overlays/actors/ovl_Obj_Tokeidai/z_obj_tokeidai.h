#ifndef Z_OBJ_TOKEIDAI_H
#define Z_OBJ_TOKEIDAI_H

#include "global.h"

#define OBJ_TOKEIDAI_TYPE(thisx) (((thisx)->params & 0xF000) >> 12)
#define OBJ_TOKEIDAI_GET_CURRENT_HOUR(this) ((s32)(this->currentTime * (24.0f / 0x10000)))
#define OBJ_TOKEIDAI_GET_CURRENT_MINUTE(this) ((s32)(this->currentTime * (360 * 2.0f / 0x10000)) % 30)
#define OBJ_TOKEIDAI_GET_CLOCK_FACE_ROTATION(currentHour) ((s16)(currentHour * (0x10000 / 24.0f)))
#define OBJ_TOKEIDAI_GET_OUTER_RING_OR_GEAR_ROTATION(currentMinute) ((s16)(currentMinute * (0x10000 * 12.0f / 360)))

typedef enum {
    /*  0 */ OBJ_TOKEIDAI_TYPE_TOWER_GEAR_CLOCK_TOWN,
    /*  1 */ OBJ_TOKEIDAI_TYPE_UNUSED_WALL,
    /*  2 */ OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_CLOCK_TOWN,
    /*  3 */ OBJ_TOKEIDAI_TYPE_TOWER_TOP_CLOCK_TOWN,
    /*  4 */ OBJ_TOKEIDAI_TYPE_TOWER_GEAR_TERMINA_FIELD,
    /*  5 */ OBJ_TOKEIDAI_TYPE_TOWER_CLOCK_TERMINA_FIELD,
    /*  6 */ OBJ_TOKEIDAI_TYPE_TOWER_TOP_TERMINA_FIELD,
    /*  8 */ OBJ_TOKEIDAI_TYPE_TOWER_WALLS_TERMINA_FIELD = 8,
    /*  9 */ OBJ_TOKEIDAI_TYPE_SMALL_CLOCK,
    /* 10 */ OBJ_TOKEIDAI_TYPE_VERY_SMALL_CLOCK,
    /* 11 */ OBJ_TOKEIDAI_TYPE_STAIRCASE_INTO_TOWER,
} ObjTokeidaiType;

struct ObjTokeidai;

typedef void (*ObjTokeidaiActionFunc)(struct ObjTokeidai*, GlobalContext*);

typedef struct ObjTokeidai {
    /* 0x000 */ Actor actor;
    /* 0x144 */ Gfx* opaDList;
    /* 0x148 */ Gfx* xluDList;
    /* 0x14C */ s16 outerRingOrGearRotation;
    /* 0x14E */ s16 outerRingOrGearAdditionalRotation;
    /* 0x150 */ s16 outerRingOrGearRotationTimer;
    /* 0x152 */ s16 clockFaceRotation;
    /* 0x154 */ s16 clockFaceAdditionalRotation; // overloaded in transformation seqeuence
    /* 0x156 */ s16 clockFaceRotationTimer; // overloaded in transformation seqeuence
    /* 0x158 */ s32 sunMoonDiskRotation;
    /* 0x15C */ s16 sunMoonDiskAdditionalRotation; // overloaded to also be something weird with the clock
    /* 0x15E */ s16 yTranslation;
    /* 0x160 */ s16 xRotation;
    /* 0x162 */ s16 clockFaceZTranslation; // amount the clock face recesses inwards once it transforms
    /* 0x164 */ s16 reboundCount;
    /* 0x168 */ s32 clockMinute; // only 30 minutes in an hour
    /* 0x16C */ s32 clockHour; // overloaded to also be the light beam intensity
    /* 0x170 */ u16 currentTime;
    /* 0x174 */ ObjTokeidaiActionFunc actionFunc;
} ObjTokeidai; // size = 0x178

extern const ActorInit Obj_Tokeidai_InitVars;

#endif // Z_OBJ_TOKEIDAI_H
