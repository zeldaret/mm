#ifndef Z_EN_PAMERA_H
#define Z_EN_PAMERA_H

#include <global.h>

struct EnPamera;

typedef void (*EnPameraActionFunc)(struct EnPamera*, GlobalContext*);
typedef void (*EnPameraSetupFunc)(struct EnPamera*, GlobalContext*);

typedef struct EnPamera {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ SkelAnime skelAnime;
    /* 0x1D4 */ EnPameraActionFunc actionFunc;
    /* 0x1D8 */ EnPameraSetupFunc setupFunc;
    /* 0x1DC */ Vec3s* pathPoints;
    /* 0x1E0 */ s32 pathIndex;
    /* 0x1E4 */ s32 pathPointsCount;
    /* 0x1E8 */ AnimatedMaterial* animatedTextures; 
    /* 0x1EC */ s32 unk_1EC;
    /* 0x1F0 */ Vec3s limbDrawTbl[0x17];
    /* 0x27A */ Vec3s transitionDrawTbl[0x17];
    /* 0x304 */ Vec3s limb15Rot;
    /* 0x30A */ Vec3s limb8Rot;
    /* 0x310 */ s16 unk_310;
    /* 0x312 */ s16 unk_312;
    /* 0x314 */ s16 unk_314;
    /* 0x316 */ s16 unk_316;
    /* 0x318 */ s16 cutscenes[2];
    /* 0x31C */ s16 unk_31C;
    /* 0x31E */ s16 unk_31E;
    /* 0x320 */ UNK_TYPE1 unk_320[0x2];
    /* 0x322 */ s16 unk_322;
    /* 0x324 */ u16 unk_324;
    /* 0x326 */ u16 unk_326;
} EnPamera; // size = 0x328

extern const ActorInit En_Pamera_InitVars;

#endif // Z_EN_PAMERA_H
