#ifndef Z_OBJ_BEAN_H
#define Z_OBJ_BEAN_H

#include "global.h"

struct ObjBean;

typedef void (*ObjBeanActionFunc)(struct ObjBean* this, GlobalContext* globalCtx);

typedef struct ObjBean {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ ObjBeanActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0xA4];
} ObjBean; // size = 0x204

extern const ActorInit Obj_Bean_InitVars;

#endif // Z_OBJ_BEAN_H
