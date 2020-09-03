#ifndef _Z_OBJ_ETCETERA_H_
#define _Z_OBJ_ETCETERA_H_

#include <global.h>

struct ObjEtcetera;

typedef struct ObjEtcetera {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x140];
} ObjEtcetera; // size = 0x284

extern const ActorInit Obj_Etcetera_InitVars;

#endif
