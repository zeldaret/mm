#ifndef Z_OBJ_PURIFY_H
#define Z_OBJ_PURIFY_H

#include "global.h"

struct ObjPurify;

typedef void (*ObjPurifyActionFunc)(struct ObjPurify*, PlayState*);

typedef struct ObjPurify {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ObjPurifyActionFunc actionFunc;
    /* 0x160 */ s32 gfxIndex;
    /* 0x164 */ s16 timer;
    /* 0x166 */ s16 objIndex;
    /* 0x168 */ f32 unk168[2];
} ObjPurify; // size = 0x170

typedef struct ObjPurifyInfo {
    /* 0x00 */ s16 objectId;
    /* 0x04 */ f32 scale;
    /* 0x08 */ Gfx* opaDLists[2];
    /* 0x10 */ Gfx* xluDLists[2];
    /* 0x18 */ AnimatedMaterial* animMat[2];
    /* 0x20 */ CollisionHeader* colHeader;
    /* 0x24 */ s32 isDekuCity;
} ObjPurifyInfo; // size = 0x28

extern const ActorInit Obj_Purify_InitVars;

#endif // Z_OBJ_PURIFY_H
