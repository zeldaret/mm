#ifndef Z_OBJ_MURE3_H
#define Z_OBJ_MURE3_H

#include "global.h"

struct ObjMure3;

typedef void (*ObjMure3ActionFunc)(struct ObjMure3*, PlayState*);
typedef void (*ObjMure3SpawnFunc)(struct ObjMure3*, PlayState*);
typedef struct ObjMure3 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ObjMure3ActionFunc actionFunc;
    /* 0x148 */ EnItem00* unk148[0x6];              
    /* 0x160 */ Actor *unk160;           
    /* 0x164 */ u16 unk164;              
    /* 0x166 */ char pad166[2];
} ObjMure3; // size = 0x168

extern const ActorInit Obj_Mure3_InitVars;

#endif // Z_OBJ_MURE3_H
