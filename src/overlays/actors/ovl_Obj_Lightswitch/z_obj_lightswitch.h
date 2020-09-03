#ifndef Z_OBJ_LIGHTSWITCH_H
#define Z_OBJ_LIGHTSWITCH_H

#include <global.h>

struct ObjLightswitch;

typedef struct ObjLightswitch {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x7C];
} ObjLightswitch; // size = 0x1C0

extern const ActorInit Obj_Lightswitch_InitVars;

#endif // Z_OBJ_LIGHTSWITCH_H
