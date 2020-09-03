#ifndef _Z_OBJ_SOUND_H_
#define _Z_OBJ_SOUND_H_

#include <global.h>

struct ObjSound;

typedef struct ObjSound {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} ObjSound; // size = 0x148

extern const ActorInit Obj_Sound_InitVars;

#endif
