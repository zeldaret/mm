#ifndef _Z_OBJ_TOUDAI_H_
#define _Z_OBJ_TOUDAI_H_

#include <global.h>

struct ObjToudai;

typedef struct ObjToudai {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xFC];
} ObjToudai; // size = 0x240

extern const ActorInit Obj_Toudai_InitVars;

#endif
