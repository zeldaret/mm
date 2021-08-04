#ifndef Z_OBJ_KIBAKO_H
#define Z_OBJ_KIBAKO_H

#include "global.h"

#define GET_KIBAKO_COLLECTIBLE_ID(x) (((x->actor.params >> 0x8) & 0x7F) << 8)

struct ObjKibako;

typedef void (*ObjKibakoActionFunc)(struct ObjKibako*, GlobalContext*);

typedef struct ObjKibako {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ObjKibakoActionFunc actionFunc;
    /* 0x148 */ ColliderCylinder collider;
    /* 0x194 */ s16 timer;
    /* 0x196 */ s16 bankIndex;
    /* 0x198 */ s8 isDropCollected;
    /* 0x199 */ s8 unk199; /* room? */
} ObjKibako; // size = 0x19C

extern const ActorInit Obj_Kibako_InitVars;

#endif // Z_OBJ_KIBAKO_H
