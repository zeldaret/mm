#ifndef Z_EN_PAMETFROG_H
#define Z_EN_PAMETFROG_H

#include <global.h>

struct EnPametfrog;

typedef void (*EnPametfrogActionFunc)(struct EnPametfrog*, GlobalContext*);

typedef enum {
    /* 0x0 */ ENPAMETFROG_PRE_SNAPPER,
    /* 0x1 */ ENPAMETFROG_GET_SNAPPER,
    /* 0x2 */ ENPAMETFROG_INIT_SNAPPER,
    /* 0x3 */ ENPAMETFROG_ON_SNAPPER,
    /* 0x4 */ ENPAMETFROG_REAR_ON_SNAPPER,
    /* 0x5 */ ENPAMETFROG_CUTSCENE,
    /* 0x6 */ ENPAMETFROG_FALL_OFF_SNAPPER,
    /* 0x7 */ ENPAMETFROG_RETURN_TO_SNAPPER,
    /* 0x8 */ ENPAMETFROG_JUMP_ON_SNAPPER,
    /* 0x9 */ ENPAMETFROG_DEFEAT,
} EnPametfrogState;

typedef struct EnPametfrog {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s limbDrawTable[24];
    /* 0x218 */ Vec3s transitionDrawTable[24];
    /* 0x2A8 */ EnPametfrogActionFunc actionFunc;
    /* 0x2AC */ u8 mode; // 0/10/20/30
    /* 0x2AD */ u8 wallPauseTimer; // Gekko stops 10 times along wall/ceiling after being blown off of Snapper
    /* 0x2AE */ u8 unk_2AE; // True/False
    /* 0x2B0 */ s16 cutscene;
    /* 0x2B2 */ s16 params;
    /* 0x2B4 */ s16 quake;
    /* 0x2B6 */ s16 timer;
    /* 0x2B8 */ s16 yaw;
    /* 0x2BA */ s16 camId;
    /* 0x2BC */ s16 freezeTimer;
    /* 0x2C0 */ f32 wallRotation;
    /* 0x2C4 */ f32 unk_2C4;
    /* 0x2C8 */ f32 unk_2C8;
    /* 0x2CC */ f32 unk_2CC; 
    /* 0x2D0 */ Vec3f unk_2D0; // MtxF zx/zy/zz
    /* 0x2DC */ Vec3f unk_2DC; // MtxF yx/yy/yz: wallNorm/floorNorm/Base of Gekko walking???
    /* 0x2E8 */ Vec3f unk_2E8; // MtxF xx/xy/xz
    /* 0x2F4 */ Vec3f unk_2F4[12]; 
    /* 0x384 */ ColliderJntSph collider;
    /* 0x3A4 */ ColliderJntSphElement colElement[2];
} EnPametfrog; // size = 0x424

extern const ActorInit En_Pametfrog_InitVars;

#endif // Z_EN_PAMETFROG_H
