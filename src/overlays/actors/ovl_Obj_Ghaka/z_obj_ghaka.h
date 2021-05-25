#ifndef Z_OBJ_GHAKA_H
#define Z_OBJ_GHAKA_H

#include <global.h>

struct ObjGhaka;

typedef void (*ObjGhakaActionFunc)(struct ObjGhaka*, GlobalContext*);

typedef struct ObjGhaka {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ObjGhakaActionFunc actionFunc;
    /* 0xXXX */ char unkStuff[0x8];
    /* 0x168 */ s16 unk_168;
} ObjGhaka; // size = 0x16C

extern const ActorInit Obj_Ghaka_InitVars;

extern CollisionHeader D_06003CD0;

#endif // Z_OBJ_GHAKA_H
