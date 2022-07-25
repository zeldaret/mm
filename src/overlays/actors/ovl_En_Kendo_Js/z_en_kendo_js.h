#ifndef Z_EN_KENDO_JS_H
#define Z_EN_KENDO_JS_H

#include "global.h"

struct EnKendoJs;

typedef void (*EnKendoJsActionFunc)(struct EnKendoJs*, PlayState*);

#define ENKENDOJS_GET_FF(thisx) ((thisx)->params & 0xFF)
#define ENKENDOJS_GET_FF00(thisx) (((thisx)->params & 0xFF00) >> 8)

#define ENKENDOJS_FF_1 1

typedef struct EnKendoJs {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ SkelAnime skelAnime;
    /* 0x1D4 */ EnKendoJsActionFunc actionFunc;
    /* 0x1D8 */ Vec3s jointTable[13];
    /* 0x226 */ Vec3s morphTable[13];
    /* 0x274 */ Vec3s* unk_274;
    /* 0x278 */ Vec3s unk_278;
    /* 0x27E */ Vec3s unk_27E;
    /* 0x284 */ s16 unk_284;
    /* 0x286 */ s16 unk_286;
    /* 0x288 */ s16 unk_288;
    /* 0x28A */ s16 unk_28A;
    /* 0x28C */ s16 unk_28C;
    /* 0x28E */ s16 unk_28E;
    /* 0x290 */ s16 unk_290;
    /* 0x292 */ u8 unk_292;
} EnKendoJs; // size = 0x294

extern const ActorInit En_Kendo_Js_InitVars;

#endif // Z_EN_KENDO_JS_H
