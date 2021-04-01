#ifndef Z_OBJ_KEPN_KOYA_H
#define Z_OBJ_KEPN_KOYA_H

#include <global.h>

struct ObjKepnKoya;

typedef struct ObjKepnKoya {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ UNK_TYPE1 unk15C;
} ObjKepnKoya; // size = 0x160

extern const ActorInit Obj_Kepn_Koya_InitVars;

#endif // Z_OBJ_KEPN_KOYA_H
