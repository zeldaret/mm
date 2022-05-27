#ifndef Z_OBJ_SWITCH_H
#define Z_OBJ_SWITCH_H

#include "global.h"

struct ObjSwitch;

typedef void (*ObjSwitchActionFunc)(struct ObjSwitch*, GlobalContext*);

#define OBJSWITCH_GET_33(thisx) ((thisx)->params & 0x33)
#define OBJSWITCH_GET_7F00(thisx) (((thisx)->params >> 8) & 0x7F)

#define OBJSWITCH_NORMAL_BLUE 0x20
#define OBJSWITCH_INVERSE_BLUE 0x30

typedef struct ObjSwitch {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ ObjSwitchActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0xF8];
} ObjSwitch; // size = 0x258

extern const ActorInit Obj_Switch_InitVars;

#endif // Z_OBJ_SWITCH_H
