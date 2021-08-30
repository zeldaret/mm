#ifndef Z_OBJ_LUPYGAMELIFT_H
#define Z_OBJ_LUPYGAMELIFT_H

#include "global.h"

struct ObjLupygamelift;

typedef void (*ObjLupygameliftActionFunc)(struct ObjLupygamelift*, GlobalContext*);

typedef struct ObjLupygamelift {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ ObjLupygameliftActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x14];
} ObjLupygamelift; // size = 0x174

extern const ActorInit Obj_Lupygamelift_InitVars;

#endif // Z_OBJ_LUPYGAMELIFT_H
