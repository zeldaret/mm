#ifndef _Z_OBJ_TOKEI_TOBIRA_H_
#define _Z_OBJ_TOKEI_TOBIRA_H_

#include <global.h>

struct ObjTokeiTobira;

typedef struct ObjTokeiTobira {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2C];
} ObjTokeiTobira; // size = 0x170

extern const ActorInit Obj_Tokei_Tobira_InitVars;

#endif
