#ifndef Z_OBJ_PURIFY_H
#define Z_OBJ_PURIFY_H

#include "global.h"

struct ObjPurify;

typedef void (*ObjPurifyActionFunc)(struct ObjPurify*, PlayState*);

typedef struct ObjPurify {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ObjPurifyActionFunc actionFunc;
    /* 0x160 */ s32 gfxIndex;
    /* 0x164 */ s16 unk164;
    /* 0x166 */ s16 objIndex; // object index?
    /* 0x168 */ f32 unk168[2];
} ObjPurify; // size = 0x170

// scene info? 
typedef struct ObjPurifyStruct00 {
    /* 0x00 */ s16 id; // ObjectId?
    /* 0x02 */ UNK_TYPE1 pad2[2];
    /* 0x04 */ f32 scale;
    /* 0x08 */ Gfx* opaDList[2];
    /* 0x10 */ Gfx* xluDList[2];
    /* 0x18 */ AnimatedMaterial* animMat[2];
    /* 0x20 */ CollisionHeader* colHeader;
    /* 0x24 */ s32 unk24; // true if scene is deku city? false if scene is woodfall temple?
} ObjPurifyStruct00; // size = 0x28

extern const ActorInit Obj_Purify_InitVars;

#endif // Z_OBJ_PURIFY_H
