#ifndef Z_EN_JS_H
#define Z_EN_JS_H

#include "global.h"

struct EnJs;

typedef void (*EnJsActionFunc)(struct EnJs*, PlayState*);

typedef struct EnJs {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x180];
    /* 0x2C4 */ EnJsActionFunc actionFunc;
} EnJs; // size = 0x2C8

extern const ActorInit En_Js_InitVars;

#endif // Z_EN_JS_H
