#ifndef Z_EN_GIRLA_H
#define Z_EN_GIRLA_H

#include <global.h>

struct EnGirlA;

typedef s32 (*EnGirlAUnkFunc)(GlobalContext*, struct EnGirlA*);

typedef struct EnGirlA {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk144[0x54];
    /* 0x198 */ u16 unk198;
    /* 0x19A */ char unk19A[0x2];
    /* 0x19C */ s32 unk19C;
    /* 0x1A0 */ s16 unk1A0;
    /* 0x1A2 */ char unk1A4[0x2];
    /* 0x1A4 */ EnGirlAUnkFunc unk1A4Func;
    /* 0x1A8 */ EnGirlAUnkFunc unk1A8Func;
    /* 0x1AC */ u16 unk1AC;
    /* 0x1AE */ char unk1AE[0x6];
    /* 0x1B4 */ EnGirlAUnkFunc unk1B4Func;
    /* 0x1B8 */ EnGirlAUnkFunc unk1B8Func;
    /* 0x1BC */ EnGirlAUnkFunc unk1BCFunc;
    /* 0x1C0 */ char unk1C0[0xC];
} EnGirlA; // size = 0x1CC

extern const ActorInit En_GirlA_InitVars;

#endif // Z_EN_GIRLA_H
