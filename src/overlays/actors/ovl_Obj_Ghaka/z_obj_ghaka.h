#ifndef Z_OBJ_GHAKA_H
#define Z_OBJ_GHAKA_H

#include <global.h>

struct ObjGhaka;

typedef void (*ObjGhakaActionFunc)(struct ObjGhaka*, GlobalContext*);
typedef void (*ObjGhakaActionFunc2)(struct ObjGhaka*, GlobalContext*);

typedef struct ObjGhaka {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ObjGhakaActionFunc actionFunc;
    /* 0x148 */ f32 unk_148;
    /* 0x148 */ char unk_152[0x10];
    /* 0x15C */ ObjGhakaActionFunc2 actionFunc2;
    /* 0x160 */ char unk_160[0x8];
    /* 0x168 */ s16 unk_168;
} ObjGhaka; // size = 0x16C

extern const ActorInit Obj_Ghaka_InitVars;

#endif // Z_OBJ_GHAKA_H
