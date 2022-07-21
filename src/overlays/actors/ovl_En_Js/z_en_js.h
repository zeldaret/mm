#ifndef Z_EN_JS_H
#define Z_EN_JS_H

#include "global.h"

struct EnJs;

typedef void (*EnJsActionFunc)(struct EnJs*, PlayState*);

typedef struct EnJs {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;                   /* inferred */
    /* 0x188 */ ColliderCylinder collider;            /* inferred */
    /* 0x1D4 */ Vec3s unk1D4;                       /* inferred */
    /* 0x1DA */ char pad1DA[0x66];                  /* maybe part of unk1D4[0x12]? */
    /* 0x240 */ Vec3s unk240;                       /* inferred */
    /* 0x246 */ char pad246[0x66];                  /* maybe part of unk240[0x12]? */
    /* 0x2AC */ Path *unk2AC;                       /* inferred */
    /* 0x2B0 */ s32 unk2B0;                         /* inferred */
    /* 0x2B4 */ f32 unk2B4;
    /* 0x2B8 */ u16 unk2B8;
    /* 0x2BA */ s16 unk2BA;
    /* 0x2BC */ s16 unk2BC;
    /* 0x2BE */ s16 cutscenes[2];
    /* 0x2C2 */ s16 cutsceneIndex;
    /* 0x2C4 */ EnJsActionFunc actionFunc;
} EnJs; // size = 0x2C8

extern const ActorInit En_Js_InitVars;

#endif // Z_EN_JS_H
