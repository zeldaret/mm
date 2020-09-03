#ifndef _Z_OBJ_MILK_BIN_H_
#define _Z_OBJ_MILK_BIN_H_

#include <global.h>

struct ObjMilkBin;

typedef struct ObjMilkBin {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x58];
} ObjMilkBin; // size = 0x19C

extern const ActorInit Obj_Milk_Bin_InitVars;

#endif
