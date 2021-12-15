#ifndef Z_OBJ_DOWSING_H
#define Z_OBJ_DOWSING_H

#include "global.h"

#define DOWSING_GET_TYPE(this) ((this)->actor.params >> 7)
#define DOWSING_GET_FLAG(this) ((this)->actor.params & 0x7F)

struct ObjDowsing;

typedef enum {
    /* 0 */ DOWSING_UNK_00,
    /* 1 */ DOWSING_COLLECTIBLE,
    /* 2 */ DOWSING_CHEST,
    /* 3 */ DOWSING_SWITCH
} DowsingType;

typedef struct ObjDowsing {
    /* 0x000 */ Actor actor;
} ObjDowsing; // size = 0x144

extern const ActorInit Obj_Dowsing_InitVars;

#endif // Z_OBJ_DOWSING_H
