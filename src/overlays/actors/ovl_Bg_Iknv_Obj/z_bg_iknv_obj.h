#ifndef _Z_BG_IKNV_OBJ_H_
#define _Z_BG_IKNV_OBJ_H_

#include <global.h>

struct BgIknvObj;

typedef struct BgIknvObj {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x6C];
} BgIknvObj; // size = 0x1B0

extern const ActorInit Bg_Iknv_Obj_InitVars;

#endif
