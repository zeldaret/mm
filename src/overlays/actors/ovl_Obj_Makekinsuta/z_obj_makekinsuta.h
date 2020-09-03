#ifndef _Z_OBJ_MAKEKINSUTA_H_
#define _Z_OBJ_MAKEKINSUTA_H_

#include <global.h>

struct ObjMakekinsuta;

typedef struct ObjMakekinsuta {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} ObjMakekinsuta; // size = 0x148

extern const ActorInit Obj_Makekinsuta_InitVars;

#endif
