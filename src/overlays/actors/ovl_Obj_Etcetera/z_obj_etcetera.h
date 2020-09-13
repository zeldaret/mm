#ifndef Z_OBJ_ETCETERA_H
#define Z_OBJ_ETCETERA_H

#include <global.h>

struct ObjEtcetera;

typedef struct ObjEtcetera {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x140];
} ObjEtcetera; // size = 0x284

extern const ActorInit Obj_Etcetera_InitVars;

#endif // Z_OBJ_ETCETERA_H
