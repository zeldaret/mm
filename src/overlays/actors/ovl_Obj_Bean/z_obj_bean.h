#ifndef Z_OBJ_BEAN_H
#define Z_OBJ_BEAN_H

#include "global.h"

struct ObjBean;

typedef void (*ObjBeanActionFunc)(struct ObjBean*, GlobalContext*);

#define OBJBEAN_GET_C000(thisx) (((thisx)->params >> 0xE) & 3)

enum {
    /* 0x00 */ ENOBJBEAN_GET_C000_0,
    /* 0x01 */ ENOBJBEAN_GET_C000_1,
    /* 0x02 */ ENOBJBEAN_GET_C000_2,
};

typedef struct ObjBean {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ ObjBeanActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x80];
    /* 0x01E0 */ s8 unk_1E0;
    /* 0x01E4 */ s32 unk_1E4;
    /* 0x01E8 */ char unk_1E8[0x1C];
} ObjBean; // size = 0x204

extern const ActorInit Obj_Bean_InitVars;

#endif // Z_OBJ_BEAN_H
