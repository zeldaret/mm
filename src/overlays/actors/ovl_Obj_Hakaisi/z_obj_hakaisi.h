#ifndef Z_OBJ_HAKAISI_H
#define Z_OBJ_HAKAISI_H

#include "global.h"

struct ObjHakaisi;

typedef void (*ObjHakaisiActionFunc)(struct ObjHakaisi* this, GlobalContext* globalCtx);

typedef struct ObjHakaisi {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ ObjHakaisiActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x40];
} ObjHakaisi; // size = 0x1A0

extern const ActorInit Obj_Hakaisi_InitVars;

#endif // Z_OBJ_HAKAISI_H
