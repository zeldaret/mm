#ifndef _Z_OBJ_OSHIHIKI_H_
#define _Z_OBJ_OSHIHIKI_H_

#include <global.h>

struct ObjOshihiki;

typedef struct ObjOshihiki {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x88];
} ObjOshihiki; // size = 0x1CC

extern const ActorInit Obj_Oshihiki_InitVars;

#endif
