#ifndef Z_EN_PAMETFROG_H
#define Z_EN_PAMETFROG_H

#include <global.h>

struct EnPametfrog;

typedef void (*EnPametfrogActionFunc)(struct EnPametfrog*, GlobalContext*);

typedef struct EnPametfrog {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s limbDrawTable[24];
    /* 0x218 */ Vec3s transitionDrawTable[24];
    /* 0x2A8 */ EnPametfrogActionFunc actionFunc;
    /* 0x2AC */ u8 unk_2AC;
    /* 0x2AD */ u8 unk_2AD;
    /* 0x2AE */ u8 unk_2AE;
    /* 0x2B0 */ s16 cutscene;
    /* 0x2B2 */ s16 params;
    /* 0x2B4 */ s16 unk_2B4;
    /* 0x2B6 */ s16 unk_2B6;
    /* 0x2B8 */ s16 unk_2B8;
    /* 0x2BA */ s16 camId;
    /* 0x2BC */ s16 unk_2BC;
    /* 0x2C0 */ char unk_2C0[0x6];
    /* 0x2C4 */ f32 unk_2C4;
    /* 0x2C8 */ f32 unk_2C8;
    /* 0x2CC */ f32 unk_2CC;
    /* 0x2D0 */ Vec3f unk_2D0; // MtxF zx/zy/zz
    /* 0x2DC */ Vec3f unk_2DC; // MtxF yx/yy/yz
    /* 0x2E8 */ Vec3f unk_2E8; // MtxF xx/xy/xz
    /* 0x2F4 */ Vec3f unk_2F4; // Possibly an array of Vec3f?
    /* 0x2F8 */ char unk_2F8[0x84];
    /* 0x384 */ ColliderJntSph collider;
    /* 0x3A4 */ ColliderJntSphElement colElement[2];
} EnPametfrog; // size = 0x424

extern const ActorInit En_Pametfrog_InitVars;

#endif // Z_EN_PAMETFROG_H
