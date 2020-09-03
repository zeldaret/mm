#ifndef Z_EN_KENDO_JS_H
#define Z_EN_KENDO_JS_H

#include <global.h>

struct EnKendoJs;

typedef struct EnKendoJs {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x150];
} EnKendoJs; // size = 0x294

extern const ActorInit En_Kendo_Js_InitVars;

#endif // Z_EN_KENDO_JS_H
