#ifndef Z_OBJ_TOKEI_TURRET_H
#define Z_OBJ_TOKEI_TURRET_H

#include <global.h>

struct ObjTokeiTurret;

typedef struct ObjTokeiTurret {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x18];
} ObjTokeiTurret; // size = 0x15C

extern const ActorInit Obj_Tokei_Turret_InitVars;

#endif // Z_OBJ_TOKEI_TURRET_H
