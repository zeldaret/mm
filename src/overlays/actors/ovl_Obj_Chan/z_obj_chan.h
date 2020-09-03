#ifndef _Z_OBJ_CHAN_H_
#define _Z_OBJ_CHAN_H_

#include <global.h>

struct ObjChan;

typedef struct ObjChan {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xA0];
} ObjChan; // size = 0x1E4

extern const ActorInit Obj_Chan_InitVars;

#endif
