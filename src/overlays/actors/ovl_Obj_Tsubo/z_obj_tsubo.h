#ifndef Z_OBJ_TSUBO_H
#define Z_OBJ_TSUBO_H

#include "global.h"

struct ObjTsubo;

typedef void (*ObjTsuboActionFunc)(struct ObjTsubo*, GlobalContext*);

typedef void (*ObjTsuboUnkFunc)(struct ObjTsubo* this, GlobalContext* globalCtx);

typedef struct ObjTsubo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjTsuboActionFunc actionFunc;
    /* 0x0148 */ ColliderCylinder cylinderCollider;
    /* 0x0194 */ s8 unk194;
    /* 0x0195 */ s8 unk195;
    /* 0x0196 */ s8 unk196;
    /* 0x0197 */ s8 unk197;
    /* 0x0198 */ s8 unk198;
    /* 0x0199 */ s8 unk199;
    /* 0x019A */ s8 unk19A;
    /* 0x019B */ u8 pad19B;

} ObjTsubo; // size = 0x19C

extern const ActorInit Obj_Tsubo_InitVars;

#endif // Z_OBJ_TSUBO_H
