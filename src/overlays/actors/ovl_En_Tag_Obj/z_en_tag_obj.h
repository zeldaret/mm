#ifndef Z_EN_TAG_OBJ_H
#define Z_EN_TAG_OBJ_H

#include <global.h>

struct EnTagObj;

typedef struct EnTagObj {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x54];
} EnTagObj; // size = 0x198

extern const ActorInit En_Tag_Obj_InitVars;

#endif // Z_EN_TAG_OBJ_H
