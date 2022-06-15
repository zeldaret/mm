#ifndef Z_EN_KENDO_JS_H
#define Z_EN_KENDO_JS_H

#include "global.h"

struct EnKendoJs;

typedef void (*EnKendoJsActionFunc)(struct EnKendoJs*, GlobalContext*);

#define ENKENDOJS_GET_FF(thisx) ((thisx)->params & 0xFF)
#define ENKENDOJS_GET_FF00(thisx) (((thisx)->params & 0xFF00) >> 8)

#define ENKENDOJS_FF_1 1

typedef struct EnKendoJs {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ SkelAnime skelAnime;
    /* 0x01D4 */ EnKendoJsActionFunc actionFunc;
    /* 0x01D8 */ Vec3s jointTable[13];
    /* 0x0226 */ Vec3s morphTable[13];
    /* 0x0274 */ Vec3s* unk_274;
    /* 0x0278 */ Vec3s unk_278;
    /* 0x027E */ Vec3s unk_27E;
    /* 0x0284 */ s16 unk_284;
    /* 0x0286 */ s16 unk_286;
    /* 0x0288 */ s16 unk_288;
    /* 0x028A */ s16 unk_28A;
    /* 0x028C */ s16 unk_28C;
    /* 0x028E */ s16 unk_28E;
    /* 0x0290 */ s16 unk_290;
    /* 0x0292 */ u8 unk_292;
} EnKendoJs; // size = 0x294

extern const ActorInit En_Kendo_Js_InitVars;

#endif // Z_EN_KENDO_JS_H
