#ifndef _Z_OBJ_TOKEI_TURRET_H_
#define _Z_OBJ_TOKEI_TURRET_H_

#include <global.h>

struct ObjTokeiTurret;

typedef struct ObjTokeiTurret {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x18];
} ObjTokeiTurret; // size = 0x15C

extern const ActorInit Obj_Tokei_Turret_InitVars;

#endif
