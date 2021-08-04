#ifndef Z_EN_DEATH_H
#define Z_EN_DEATH_H

#include "global.h"

struct EnDeath;

typedef void (*EnDeathActionFunc)(struct EnDeath*, PlayState*);

typedef struct EnDeath {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnDeathActionFunc unk_188;
    /* 0x18C */ u8 unk_18C;
    /* 0x18D */ u8 unk_18D;
    /* 0x18E */ u8 unk_18E;
    /* 0x18F */ u8 unk_18F;
    /* 0x190 */ s8 unk_190;
    /* 0x191 */ u8 unk_191;
    /* 0x192 */ u8 unk_192;
    /* 0x193 */ char unk_193[0x16];
    /* 0x1A9 */ u8 unk_1A9[56];
    /* 0x1E1 */ char unk_1E1[1]; // likely padding
    /* 0x1E2 */ Vec3s unk_1E2[22];
    /* 0x266 */ Vec3s unk_266[22];
    /* 0x2EA */ s16 unk_2EA;
    /* 0x2EC */ s16 unk_2EC;
    /* 0x2EE */ s16 unk_2EE;
    /* 0x2F0 */ char unk_2F0[0x2];
    /* 0x2F2 */ s16 unk_2F2;
    /* 0x2F4 */ s16 unk_2F4;
    /* 0x2F6 */ s16 unk_2F6;
    /* 0x2F8 */ s16 unk_2F8;
    /* 0x2FA */ s16 unk_2FA;
    /* 0x2FC */ s16 unk_2FC;
    /* 0x2FE */ char unk_2FE[0x2];
    /* 0x300 */ s32 unk_300; // effectIdx
    /* 0x304 */ f32 unk_304;
    /* 0x308 */ f32 unk_308;
    /* 0x30C */ f32 unk_30C;
    /* 0x310 */ f32 unk_310;
    /* 0x314 */ f32 unk_314;
    /* 0x318 */ f32 unk_318;
    /* 0x31C */ f32 unk_31C;
    /* 0x320 */ Vec3f unk_320;
    /* 0x32C */ Vec3f unk_32C;
    /* 0x338 */ Vec3f unk_338;
    /* 0x344 */ Vec3f unk_344;
    /* 0x350 */ Vec3f unk_350;
    /* 0x35C */ Vec3f unk_35C[2]; // TODO size
    /* 0x374 */ char unk_374[0x330];
    /* 0x6A4 */ MtxF unk_6A4;
    /* 0x6E4 */ Actor* unk_6E4[20];
    /* 0x734 */ AnimatedMaterial* unk_734;
    /* 0x738 */ AnimatedMaterial* unk_738;
    /* 0x73C */ ColliderCylinder unk_73C;
    /* 0x788 */ ColliderQuad unk_788;
    /* 0x808 */ ColliderSphere unk_808;
    /* 0x860 */ ColliderTris unk_860;
    /* 0x880 */ ColliderTrisElement unk_880[2];
} EnDeath; // size = 0x938

#endif // Z_EN_DEATH_H
