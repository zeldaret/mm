#ifndef Z_OBJ_SYOKUDAI_H
#define Z_OBJ_SYOKUDAI_H

#include <global.h>

struct ObjSyokudai;

typedef struct ObjSyokudai {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x98];
    /* 0x1DC */ s16 unk_1DC;
    /* 0x1DE */ char unk_1DE[0x16];
} ObjSyokudai; // size = 0x1F4

extern const ActorInit Obj_Syokudai_InitVars;

#endif // Z_OBJ_SYOKUDAI_H
