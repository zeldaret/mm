#ifndef Z_OBJ_SWITCH_H
#define Z_OBJ_SWITCH_H

#include "global.h"

struct ObjSwitch;

typedef void (*ObjSwitchActionFunc)(struct ObjSwitch* this, GlobalContext* globalCtx);

typedef struct ObjSwitch {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ ObjSwitchActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0xF8];
} ObjSwitch; // size = 0x258

extern const ActorInit Obj_Switch_InitVars;

#endif // Z_OBJ_SWITCH_H
