#ifndef Z_EN_MARUTA_H
#define Z_EN_MARUTA_H

#include "global.h"

struct EnMaruta;

typedef void (*EnMarutaActionFunc)(struct EnMaruta*, GlobalContext*);

#define ENMARUTA_GET_FF(thisx) ((thisx)->params & 0xFF)
#define ENMARUTA_GET_FF00(thisx) (((thisx)->params & 0xFF00) >> 8)

typedef struct EnMaruta {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnMarutaActionFunc actionFunc;
    /* 0x0148 */ ColliderCylinder collider;
    /* 0x0194 */ Vec3f unk_194;
    /* 0x01A0 */ Vec3f* unk_1A0;
    /* 0x01A4 */ Vec3f unk_1A4[8];
    /* 0x0204 */ Vec3f unk_204;
    /* 0x0210 */ s32 unk_210;
    /* 0x0214 */ s32 unk_214;
    /* 0x0218 */ s16 unk_218;
    /* 0x021A */ s16 unk_21A;
    /* 0x021C */ s16 unk_21C;
    /* 0x021E */ s16 unk_21E;
    /* 0x0220 */ s16 unk_220;
} EnMaruta; // size = 0x224

extern const ActorInit En_Maruta_InitVars;

#endif // Z_EN_MARUTA_H
