#ifndef Z_OBJ_ICEBLOCK_H
#define Z_OBJ_ICEBLOCK_H

#include "global.h"

struct ObjIceblock;

typedef void (*ObjIceblockActionFunc)(struct ObjIceblock*, GlobalContext*);

typedef struct ObjIceblock {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x64];
    /* 0x01A8 */ ObjIceblockActionFunc actionFunc;
    /* 0x01AC */ char unk_1AC[0x10C];
} ObjIceblock; // size = 0x2B8

extern const ActorInit Obj_Iceblock_InitVars;

#endif // Z_OBJ_ICEBLOCK_H
