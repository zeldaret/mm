#ifndef Z_EN_TWIG_H
#define Z_EN_TWIG_H

#include "global.h"

struct EnTwig;

typedef void (*EnTwigActionFunc)(struct EnTwig*, GlobalContext*);

typedef struct EnTwig {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ EnTwigActionFunc actionFunc;
    /* 0x0160 */ s32 unk_160;
    /* 0x0160 */ char unk164[8];
    /* 0x016C */ s32 unk_16C;
    /* 0x0170 */ f32 unk_170;
    /* 0x0174 */ f32 unk_174;
    /* 0x0178 */ s16 unk_178;
    /* 0x017A */ u16 unk_17A;
    /* 0x017C */ char unk17C[4];
    /* 0x0180 */ Vec3f unk_180;
} EnTwig; // size = 0x18C

extern const ActorInit En_Twig_InitVars;

#endif // Z_EN_TWIG_H
