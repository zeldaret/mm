#ifndef Z_OBJ_TOKEI_TURRET_H
#define Z_OBJ_TOKEI_TURRET_H

#include "global.h"

struct ObjTokeiTurret;

typedef struct ObjTokeiTurret {
    /* 0x000 */ DynaPolyActor dyna;
} ObjTokeiTurret; // size = 0x15C

extern const ActorInit Obj_Tokei_Turret_InitVars;

#endif // Z_OBJ_TOKEI_TURRET_H
