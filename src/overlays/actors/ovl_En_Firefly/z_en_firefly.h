#ifndef Z_EN_FIREFLY_H
#define Z_EN_FIREFLY_H

#include <global.h>

struct EnFirefly;


typedef void (*EnFireflyActionFunc)(struct EnFirefly*, GlobalContext*);

typedef struct EnFirefly {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnFireflyActionFunc actionFunc;
    /* 0x18C */ u8 unk_18C;
    /* 0x18D */ u8 unk_18D;
    /* 0x18E */ u8 unk_18E;
    /* 0x18F */ u8 unk_18F;
    /* 0x190 */ s16 unk_190;
    /* 0x192 */ s16 unk_192;
    /* 0x194 */ Vec3s jointTable[28];
    /* 0x23C */ Vec3s morphTable[28];
    /* 0x2E4 */ f32 unk_2E4;
    /* 0x2E8 */ Vec3f unk_2E8;
    /* 0x2F4 */ s32 unk_2F4;
    /* 0x2F8 */ Vec3f unk_2F8;
    /* 0x304 */ Vec3f unk_304;
    /* 0x304 */ Vec3f unk_310;
    /* 0x31C */ ColliderSphere collider;
} EnFirefly; // size = 0x374

extern const ActorInit En_Firefly_InitVars;

#endif // Z_EN_FIREFLY_H
