#ifndef Z_EN_JS_H
#define Z_EN_JS_H

#include "global.h"

struct EnJs;

typedef void (*EnJsActionFunc)(struct EnJs*, PlayState*);

typedef struct EnJs {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ ColliderCylinder collider;
    /* 0x1D4 */ Vec3s jointTable[18];
    /* 0x240 */ Vec3s morphTable[18];
    /* 0x2AC */ Path* unk_2AC;
    /* 0x2B0 */ s32 unk_2B0;
    /* 0x2B4 */ f32 unk_2B4;
    /* 0x2B8 */ u16 unk_2B8;
    /* 0x2BA */ s16 unk_2BA;
    /* 0x2BC */ s16 unk_2BC;
    /* 0x2BE */ s16 cutscenes[2];
    /* 0x2C2 */ s16 cutsceneIndex;
    /* 0x2C4 */ EnJsActionFunc actionFunc;
} EnJs; // size = 0x2C8

extern const ActorInit En_Js_InitVars;

#endif // Z_EN_JS_H
