#ifndef Z_OBJ_MURE_H
#define Z_OBJ_MURE_H

#include "global.h"

struct ObjMure;

typedef void (*ObjMureActionFunc)(struct ObjMure* this, GlobalContext* globalCtx);

#define OBJMURE_MAX_SPAWNS 15

typedef struct {
    Actor actor;
    /* 0x144 */ char unk_144[0x53];
    /* 0x197 */ u8 unk_197;
} ObjMureChild;

typedef struct ObjMure {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjMureActionFunc actionFunc;
    /* 0x0148 */ s16 chNum;
    /* 0x014A */ s16 ptn;
    /* 0x014C */ s16 svNum;
    /* 0x014E */ s16 type;
    /* 0x0158 */ Actor* children[OBJMURE_MAX_SPAWNS];
    /* 0x018C */ u8 childrenStates[OBJMURE_MAX_SPAWNS];
    /* 0x019C */ s16 unk_1A4;
    /* 0x019E */ s16 unk_1A6;
    /* 0x01A0 */ s16 unk_1A8;
} ObjMure; // size = 0x1A4

extern const ActorInit Obj_Mure_InitVars;

#endif // Z_OBJ_MURE_H
