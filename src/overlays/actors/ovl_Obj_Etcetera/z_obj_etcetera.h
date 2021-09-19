#ifndef Z_OBJ_ETCETERA_H
#define Z_OBJ_ETCETERA_H

#include "global.h"

struct ObjEtcetera;

typedef void (*ObjEtceteraActionFunc)(struct ObjEtcetera*, GlobalContext*);

typedef struct ObjEtcetera {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ SkelAnime skelAnime;
    /* 0x01A0 */ ColliderCylinder collider;
    /* 0x01EC */ char unk_1EC[0x84];
    /* 0x0270 */ f32 unk_270;
    /* 0x0274 */ s16 unk_274;
    /* 0x0276 */ s16 unk_276;
    /* 0x0278 */ u8 unk_278;
    /* 0x027A */ char unk_27A[0x2];
    /* 0x027C */ Gfx* unk_27C;
    /* 0x0280 */ ObjEtceteraActionFunc actionFunc;
} ObjEtcetera; // size = 0x284

extern const ActorInit Obj_Etcetera_InitVars;

#endif // Z_OBJ_ETCETERA_H
