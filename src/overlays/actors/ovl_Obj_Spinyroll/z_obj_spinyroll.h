#ifndef Z_OBJ_SPINYROLL_H
#define Z_OBJ_SPINYROLL_H

#include "global.h"

struct ObjSpinyroll;

typedef void (*ObjSpinyrollActionFunc)(struct ObjSpinyroll*, GlobalContext*);

typedef struct ObjSpinyroll {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x35C];
    /* 0x04A0 */ ObjSpinyrollActionFunc actionFunc;
    /* 0x04A4 */ char unk_4A4[0x40];
} ObjSpinyroll; // size = 0x4E4

extern const ActorInit Obj_Spinyroll_InitVars;

#endif // Z_OBJ_SPINYROLL_H
