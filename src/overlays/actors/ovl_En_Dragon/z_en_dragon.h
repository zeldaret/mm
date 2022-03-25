#ifndef Z_EN_DRAGON_H
#define Z_EN_DRAGON_H

#include "global.h"
#include "objects/object_utubo/object_utubo.h"

#define EN_DRAGON_GET_PYTHON_INDEX(thisx) (((thisx)->params >> 7) & 0x1F)

struct EnDragon;

typedef void (*EnDragonActionFunc)(struct EnDragon*, GlobalContext*);

typedef struct EnDragon {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[DEEP_PYTHON_LIMB_MAX];
    /* 0x1E8 */ Vec3s morphTable[DEEP_PYTHON_LIMB_MAX];
    /* 0x248 */ EnDragonActionFunc actionFunc;
    /* 0x24C */ s32 animationIndex;
    /* 0x250 */ s32 pythonIndex;
    /* 0x254 */ Vec3f unk_254;
    /* 0x260 */ Vec3f unk_260;
    /* 0x26C */ Vec3f unk_26C;
    /* 0x278 */ Vec3f cameraEye;
    /* 0x278 */ Vec3f cameraAt;
    /* 0x290 */ Vec3f unk_290;
    /* 0x29C */ Vec3f unk_29C;
    /* 0x2A8 */ s16 jawZRotation;
    /* 0x2AA */ s16 jawYRotation; // Never initialized by the actor
    /* 0x2AC */ s16 jawXRotation; // Never initialized by the actor
    /* 0x2AE */ s16 unk_2AE;
    /* 0x2B0 */ s16 unk_2B0;
    /* 0x2B2 */ s16 unk_2B2;
    /* 0x2B4 */ s16 unk_2B4;
    /* 0x2B6 */ s16 unk_2B6;
    /* 0x2B8 */ s16 unk_2B8;
    /* 0x2BA */ s16 unk_2BA;
    /* 0x2BC */ UNK_TYPE1 unk_2BC[0x2];
    /* 0x2BE */ s16 unk_2BE;
    /* 0x2C0 */ s16 unk_2C0;
    /* 0x2C2 */ s16 unk_2C2;
    /* 0x2C4 */ UNK_TYPE1 unk_2C4[0x4];
    /* 0x2C8 */ s16 cameraId;
    /* 0x2CA */ s16 unk_2CA;
    /* 0x2CC */ s16 unk_2CC;
    /* 0x2CE */ UNK_TYPE1 unk_2CE[0x2];
    /* 0x2D0 */ f32 endFrame;
    /* 0x2D4 */ f32 unk_2D4;
    /* 0x2D8 */ UNK_TYPE1 unk_2D8[0x4];
    /* 0x2DC */ ColliderJntSph collider;
    /* 0x2FC */ ColliderJntSphElement colliderElements[8];
} EnDragon; // size = 0x4FC

extern const ActorInit En_Dragon_InitVars;

#endif // Z_EN_DRAGON_H
