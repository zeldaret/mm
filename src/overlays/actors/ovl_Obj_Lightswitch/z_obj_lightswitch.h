#ifndef _Z_OBJ_LIGHTSWITCH_H_
#define _Z_OBJ_LIGHTSWITCH_H_

#include <global.h>

struct ObjLightswitch;

typedef struct ObjLightswitch {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x7C];
} ObjLightswitch; // size = 0x1C0

extern const ActorInit Obj_Lightswitch_InitVars;

#endif
