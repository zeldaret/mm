#ifndef Z_BG_IKNV_OBJ_H
#define Z_BG_IKNV_OBJ_H

#include <global.h>

struct BgIknvObj;

typedef void (*BgIknvObjActionFunc)(struct BgIknvObj*, GlobalContext*);

#define IKNV_OBJ_TYPE(x) (x->dyna.actor.params & 0xF)

typedef struct BgIknvObj {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ColliderCylinder collider;
    /* 0x1A8 */ Gfx* displayListPtr;
    /* 0x1AC */ BgIknvObjActionFunc actionFunc;
} BgIknvObj; // size = 0x1B0

typedef enum {
    /* 0 */ BG_IKNV_OBJ_TYPE_UNK0,
    /* 1 */ BG_IKNV_OBJ_TYPE_UNK1,
    /* 2 */ BG_IKNV_OBJ_TYPE_UNK2,
} BgIknvObjType;

extern const ActorInit Bg_Iknv_Obj_InitVars;

#endif // Z_BG_IKNV_OBJ_H
