#ifndef _Z_OBJ_TOKEI_STEP_H_
#define _Z_OBJ_TOKEI_STEP_H_

#include <global.h>

struct ObjTokeiStep;

typedef struct ObjTokeiStep {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xA8];
} ObjTokeiStep; // size = 0x1EC

extern const ActorInit Obj_Tokei_Step_InitVars;

#endif
