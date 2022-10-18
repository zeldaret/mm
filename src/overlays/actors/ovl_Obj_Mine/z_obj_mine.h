#ifndef Z_OBJ_MINE_H
#define Z_OBJ_MINE_H

#include "global.h"

struct ObjMine;

typedef void (*ObjMineActionFunc)(struct ObjMine*, PlayState*);

typedef struct ObjMine {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x60];
    /* 0x01A4 */ ObjMineActionFunc actionFunc;
    /* 0x01A8 */ char unk_1A8[0x120C];
} ObjMine; // size = 0x13B4

#endif // Z_OBJ_MINE_H
