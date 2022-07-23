#ifndef Z_EN_PAMETFROG_H
#define Z_EN_PAMETFROG_H

#include "global.h"
#include "objects/object_bigslime/object_bigslime.h"

struct EnPametfrog;

typedef void (*EnPametfrogActionFunc)(struct EnPametfrog*, PlayState*);

typedef enum {
    /* 0x0 */ GEKKO_PRE_SNAPPER,
    /* 0x1 */ GEKKO_GET_SNAPPER,
    /* 0x2 */ GEKKO_INIT_SNAPPER,
    /* 0x3 */ GEKKO_ON_SNAPPER,
    /* 0x4 */ GEKKO_REAR_ON_SNAPPER,
    /* 0x5 */ GEKKO_CUTSCENE,
    /* 0x6 */ GEKKO_FALL_OFF_SNAPPER,
    /* 0x7 */ GEKKO_RETURN_TO_SNAPPER,
    /* 0x8 */ GEKKO_JUMP_ON_SNAPPER,
    /* 0x9 */ GEKKO_DEFEAT,
} EnPametfrogState;

typedef struct EnPametfrog {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[GEKKO_LIMB_MAX];
    /* 0x218 */ Vec3s morphTable[GEKKO_LIMB_MAX];
    /* 0x2A8 */ EnPametfrogActionFunc actionFunc;
    /* 0x2AC */ u8 drawDmgEffType;
    /* 0x2AD */ u8 wallPauseTimer; // Gekko stops 10 times along wall/ceiling after being blown off of Snapper
    /* 0x2AE */ u8 unk_2AE; // True/False
    /* 0x2B0 */ s16 cutscene;
    /* 0x2B2 */ s16 params;
    /* 0x2B4 */ s16 quake;
    /* 0x2B6 */ s16 timer;
    /* 0x2B8 */ s16 spinYaw;
    /* 0x2BA */ s16 subCamId;
    /* 0x2BC */ s16 freezeTimer;
    /* 0x2C0 */ f32 wallRotation;
    /* 0x2C4 */ f32 drawDmgEffAlpha;
    /* 0x2C8 */ f32 drawDmgEffScale;
    /* 0x2CC */ f32 drawDmgEffFrozenSteamScale; 
    /* 0x2D0 */ Vec3f unk_2D0; // MtxF xz/yz/zz
    /* 0x2DC */ Vec3f unk_2DC; // MtxF xy/yy/zy: wallNorm/floorNorm/Base of Gekko walking???
    /* 0x2E8 */ Vec3f unk_2E8; // MtxF xx/yx/zx
    /* 0x2F4 */ Vec3f limbPos[12]; 
    /* 0x384 */ ColliderJntSph collider;
    /* 0x3A4 */ ColliderJntSphElement colElement[2];
} EnPametfrog; // size = 0x424

extern const ActorInit En_Pametfrog_InitVars;

#endif // Z_EN_PAMETFROG_H
