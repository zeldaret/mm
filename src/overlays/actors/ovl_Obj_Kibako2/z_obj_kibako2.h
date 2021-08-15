#ifndef Z_OBJ_KIBAKO2_H
#define Z_OBJ_KIBAKO2_H

#include "global.h"

struct ObjKibako2;

typedef void (*ObjKibako2ActionFunc)(struct ObjKibako2*, GlobalContext*);

typedef struct ObjKibako2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x64];
    /* 0x01A8 */ ObjKibako2ActionFunc actionFunc;
    /* 0x01AC */ char unk_1AC[0x4];
} ObjKibako2; // size = 0x1B0

extern const ActorInit Obj_Kibako2_InitVars;

#endif // Z_OBJ_KIBAKO2_H
