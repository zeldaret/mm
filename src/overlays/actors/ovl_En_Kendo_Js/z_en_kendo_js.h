#ifndef Z_EN_KENDO_JS_H
#define Z_EN_KENDO_JS_H

#include "global.h"

struct EnKendoJs;

typedef void (*EnKendoJsActionFunc)(struct EnKendoJs* this, GlobalContext* globalCtx);

typedef struct EnKendoJs {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x90];
    /* 0x01D4 */ EnKendoJsActionFunc actionFunc;
    /* 0x01D8 */ char unk_1D8[0xBC];
} EnKendoJs; // size = 0x294

extern const ActorInit En_Kendo_Js_InitVars;

#endif // Z_EN_KENDO_JS_H
