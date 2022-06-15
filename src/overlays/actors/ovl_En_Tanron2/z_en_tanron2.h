#ifndef Z_EN_TANRON2_H
#define Z_EN_TANRON2_H

#include "global.h"

struct EnTanron2;

typedef void (*EnTanron2ActionFunc)(struct EnTanron2*, GlobalContext*);

typedef struct EnTanron2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnTanron2ActionFunc actionFunc;
    /* 0x0148 */ s16 unk_148;
    /* 0x014A */ s16 unk_14A;
    /* 0x014C */ s16 unk_14C;
    /* 0x014E */ s16 unk_14E;
    /* 0x0150 */ s16 unk_150;
    /* 0x0152 */ s16 unk_152;
    /* 0x0154 */ s16 unk_154;
    /* 0x0156 */ s16 unk_156;
    /* 0x0158 */ u8 unk_158;
    /* 0x0159 */ u8 unk_159;
    /* 0x015A */ u8 unk_15A;
    /* 0x015B */ u8 unk_15B;
    /* 0x015C */ f32 unk_15C;
    /* 0x0160 */ f32 unk_160;
    /* 0x0164 */ ColliderCylinder collider1;
    /* 0x01B0 */ ColliderCylinder collider2;
} EnTanron2; // size = 0x1FC

extern const ActorInit En_Tanron2_InitVars;

#endif // Z_EN_TANRON2_H
