#ifndef Z_BG_F40_SWITCH_H
#define Z_BG_F40_SWITCH_H

#include "global.h"

struct BgF40Switch;

#define BGF40SWITCH_GET_SWITCHFLAG(thisx) (((thisx)->params & 0xFE00) >> 9)

typedef void (*BgF40SwitchActionFunc)(struct BgF40Switch*, GlobalContext*);

typedef struct BgF40Switch {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ s16 switchReleaseDelay; // frames until a pressed switch becomes released if nothing is still pressing it
    /* 0x015E */ s8 isPressed; // Logical state of the switch (pressed or unpressed). Animation state may lag behind this slightly.
    /* 0x015F */ s8 wasPressed; // used as temporary during update function
    // true if this switch is the one that initiated a state change; false if this switch is changing as a result of another switch tied to the same flag.
    // this is a temporary flag related to something currently happening, not a permanent property of the switch.
    /* 0x0160 */ s8 isInitiator;
    /* 0x0164 */ BgF40SwitchActionFunc actionFunc;
} BgF40Switch; // size = 0x168

extern const ActorInit Bg_F40_Switch_InitVars;

#endif // Z_BG_F40_SWITCH_H
