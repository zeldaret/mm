#ifndef Z_OBJ_TOKEI_TOBIRA_H
#define Z_OBJ_TOKEI_TOBIRA_H

#include "global.h"

struct ObjTokeiTobira;

typedef void (*ObjTokeiTobiraActionFunc)(struct ObjTokeiTobira*, PlayState*);

typedef struct ObjTokeiTobira {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x18];
    /* 0x15C */ ObjTokeiTobiraActionFunc actionFunc;
    /* 0x160 */ char unk_160[0x10];
} ObjTokeiTobira; // size = 0x170

extern const ActorInit Obj_Tokei_Tobira_InitVars;

#endif // Z_OBJ_TOKEI_TOBIRA_H
