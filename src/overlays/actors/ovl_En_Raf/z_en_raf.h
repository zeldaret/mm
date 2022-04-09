#ifndef Z_EN_RAF_H
#define Z_EN_RAF_H

#include "global.h"
#include "objects/object_raf/object_raf.h"

#define EN_RAF_GET_F(thisx) (((thisx)->params >> 12) & 0xF)
#define EN_RAF_GET_1F(thisx) (((thisx)->params >> 7) & 0x1F)
#define EN_RAF_GET_SWITCH_FLAG(thisx) ((thisx)->params & 0x7F)

struct EnRaf;

typedef void (*EnRafActionFunc)(struct EnRaf*, GlobalContext*);

typedef struct {
    /* 0x00 */ u8 isVisible;
    /* 0x04 */ Vec3f position;
    /* 0x10 */ Vec3f velocity;
    /* 0x1C */ Vec3f acceleration;
    /* 0x28 */ Vec3s rotation;
    /* 0x30 */ f32 scale;
    /* 0x34 */ s16 timer;
} EnRafParticle; // size = 0x38

typedef struct EnRaf {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ SkelAnime skelAnime;
    /* 0x1A0 */ Vec3s jointTable[CARNIVOROUS_LILY_PAD_LIMB_MAX];
    /* 0x1E8 */ Vec3s morphTable[CARNIVOROUS_LILY_PAD_LIMB_MAX];
    /* 0x230 */ EnRafActionFunc actionFunc;
    /* 0x234 */ Vec3f unk_234[CARNIVOROUS_LILY_PAD_LIMB_MAX];
    /* 0x2C4 */ Vec3f unk_2C4[CARNIVOROUS_LILY_PAD_LIMB_MAX];
    /* 0x354 */ Vec3s unk_354[CARNIVOROUS_LILY_PAD_LIMB_MAX];
    /* 0x39C */ s16 unk_39C;
    /* 0x39E */ u8 unk_39E;
    /* 0x3A0 */ f32 endFrame;
    /* 0x3A4 */ f32 unk_3A4;
    /* 0x3A8 */ f32 unk_3A8;
    /* 0x3AC */ f32 unk_3AC;
    /* 0x3B0 */ f32 unk_3B0;
    /* 0x3B4 */ s16 unk_3B4;
    /* 0x3B6 */ s16 unk_3B6;
    /* 0x3B8 */ s16 unk_3B8;
    /* 0x3BA */ s16 unk_3BA;
    /* 0x3BC */ s16 unk_3BC;
    /* 0x3BE */ s16 unk_3BE;
    /* 0x3C0 */ s16 switchFlag;
    /* 0x3C2 */ s16 unk_3C2;
    /* 0x3C4 */ s16 unk_3C4;
    /* 0x3C6 */ s16 unk_3C6;
    /* 0x3C8 */ s16 unk_3C8;
    /* 0x3CA */ s16 unk_3CA;
    /* 0x3CC */ s16 unk_3CC;
    /* 0x3CE */ s16 unk_3CE;
    /* 0x3D0 */ ColliderCylinder collider;
    /* 0x41C */ EnRafParticle particles[31];
} EnRaf; // size = 0xAE4

extern const ActorInit En_Raf_InitVars;

#endif // Z_EN_RAF_H
