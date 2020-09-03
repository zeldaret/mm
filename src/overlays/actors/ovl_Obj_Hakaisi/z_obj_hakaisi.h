#ifndef _Z_OBJ_HAKAISI_H_
#define _Z_OBJ_HAKAISI_H_

#include <global.h>

struct ObjHakaisi;

typedef struct ObjHakaisi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x5C];
} ObjHakaisi; // size = 0x1A0

extern const ActorInit Obj_Hakaisi_InitVars;

#endif
