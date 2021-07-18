#ifndef Z_EN_PAMERA_H
#define Z_EN_PAMERA_H

#include <global.h>

struct EnPamera;

typedef void (*EnPameraActionFunc)(struct EnPamera*, GlobalContext*);
typedef void (*EnPameraSetupFunc)(struct EnPamera*, GlobalContext*);

typedef struct EnPamera {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider; // size = 0x4C
    /* 0x190 */ SkelAnime skelAnime; // size = 0x44
    /* 0x1D4 */ EnPameraActionFunc actionFunc;
    /* 0x1D8 */ EnPameraSetupFunc setupFunc;
    /* 0x1DC */ Vec3s* unk_1DC;
    /* 0x1E0 */ s32 unk_1E0;
    /* 0x1E4 */ s32 unk_1E4;
    /* 0x1E8 */ AnimatedMaterial* animatedTextures; 
    /* 0x1EC */ s32 unk_1EC;
    /* 0x1F0 */ Vec3s limbDrawTbl[0x17]; // size = 0x8A
    /* 0x27A */ Vec3s transitionDrawTbl[0x17]; // size = 0x8A
    /* 0x304 */ Vec3s limb15Rot; // size = 0x06
    /* 0x30A */ Vec3s limb8Rot; // size = 0x06
    /* 0x310 */ s16 unk_310;
    /* 0x312 */ s16 unk_312;
    /* 0x314 */ s16 unk_314;
    /* 0x316 */ s16 unk_316;
    /* 0x318 */ s16 unk_318[2];
    /* 0x31C */ s16 unk_31C;
    /* 0x31E */ s16 unk_31E;
    /* 0x320 */ char unk_320[0x2];
    /* 0x322 */ s16 unk_322;
    /* 0x324 */ u16 unk_324;
    /* 0x326 */ u16 unk_326;
} EnPamera; // size = 0x328

extern const ActorInit En_Pamera_InitVars;

#endif // Z_EN_PAMERA_H
