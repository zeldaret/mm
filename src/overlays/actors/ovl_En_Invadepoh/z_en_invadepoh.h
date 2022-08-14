#ifndef Z_EN_INVADEPOH_H
#define Z_EN_INVADEPOH_H

#include "global.h"

struct EnInvadepoh;

typedef void (*EnInvadepohInitFunc)(struct EnInvadepoh*, PlayState*);
typedef void (*EnInvadepohDestroyFunc)(struct EnInvadepoh*, PlayState*);
typedef void (*EnInvadepohActionFunc)(struct EnInvadepoh*, PlayState*);

#define INVADEPOH_TYPE(thisx) (((thisx)->params >> 4) & 0xF)

typedef enum{
    /*  0   */ TYPE_UNK0,
    /*  1   */ TYPE_ALIEN,
    /*  2   */ TYPE_PARENT_COW,
    /*  3   */ TYPE_CHILD_COW,
    /*  4   */ TYPE_ROMANI,
    /*  5   */ TYPE_ROMANI1,
    /*  6   */ TYPE_UNK6,
    /*  7   */ TYPE_ROMANI2,
    /*  8   */ TYPE_ROMANI3,
    /*  9   */ TYPE_ROMANI4,
    /*  10  */ TYPE_DOG,
    /*  11  */ TYPE_CREMIA,
    /*  12  */ TYPE_ROMANI5,
    /*  13  */ TYPE_ALIEN_CARRYING_COW
} EnInvadepohType;

typedef enum {
    /* -1 */ DIRECTION_BACKWARD = -1,
    /* 1  */ DIRECTION_FORWARD = 1,
} EnInvadepohDirection;

typedef struct unkStruct80B50350 {
    /* 0x000 */ s8 unk0;
    /* 0x001 */ s8 unk1;
    /* 0x002 */ u8 unk2;
    /* 0x004 */ Vec3f unk4;
} unkStruct80B50350; // size = 0x10;

typedef struct {
    /* 0x00 */ s8* unk00;
    /* 0x04 */ s8 unk04;
} unkstructInvadepoh0; // size = 0x08

typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x04 */ f32 unk04;
} unkstructInvadepoh1; // size = 0x08

typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x04 */ unkstructInvadepoh0* unk04;
} unkstructInvadepoh2; // size = 0x08

typedef struct {
    /* 0x00 */ s8 unk0;
    /* 0x04 */ unkstructInvadepoh0* unk4;
    /* 0x08 */ s8 unk8;
    /* 0x0C */ unkstructInvadepoh1* unkC;
} unkstructInvadepoh3; // size = 0x10

typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x04 */ unkstructInvadepoh0* unk04;
    /* 0x08 */ s8 unk08;
    /* 0x0C */ unkstructInvadepoh1* unk0C;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
} unkstructInvadepoh4; // size = 0x14

typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
} unkstruct80B4EE0C; // size = 0x08

typedef struct EnInvadePohStruct {
    /* 0x000 */ unkstructInvadepoh4* unk0;
    /* 0x004 */ s8 unk4;
    /* 0x008 */ unkstructInvadepoh4* unk8;
    /* 0x00C */ s16 unkC;
    /* 0x00E */ s8 unkE;
    /* 0x00F */ s8 unkF;
} EnInvadePohStruct; // size = 0x10;

typedef struct AlienBehaviorInfo {
    /* 0x000 */ EnInvadePohStruct unk0;
    /* 0x010 */ EnInvadePohStruct unk10;
    /* 0x020 */ Vec3s unk20;
    /* 0x026 */ Vec3s unk26;
    /* 0x02C */ s16 unk2C;
    /* 0x02E */ u16 unk2E;
    /* 0x030 */ f32 unk30;
    /* 0x034 */ f32 unk34;
    /* 0x038 */ f32 unk38;
    /* 0x03C */ f32 unk3C;
    /* 0x040 */ s16 unk40;
    /* 0x042 */ s16 unk42;
    /* 0x044 */ f32 unk44;
    /* 0x048 */ s16 unk48;
    /* 0x04A */ char unk4A[0x2];
    /* 0x04C */ s16 unk4C;
    /* 0x04E */ s16 unk4E;
} AlienBehaviorInfo; // size = 0x50

typedef struct EnInvadepoh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[23];
    /* 0x212 */ Vec3s morphTable[23];
    /* 0x29C */ s8 animPlayFlag;
    /* 0x2A0 */ ColliderCylinder collider;
    /* 0x2EC */ EnInvadepohActionFunc actionFunc;
    /* 0x2F0 */ s16 actionTimer;
    /* 0x2F2 */ s16 counter; // general counter variable
    /* 0x2F4 */ s8 bankIndex;
    /* 0x2F8 */ f32 xzPosAdjFactor;
    /* 0x2FC */ UNK_TYPE unk2FC; // unused
    /* 0x300 */ f32 velocityStep;
    /* 0x304 */ s16 unk304; // angle of some sort
    /* 0x306 */ s16 unk306;
    /* 0x308 */ s8 endPoint;
    /* 0x309 */ s8 pathIndex;
    /* 0x30A */ s8 direction; // only ever 1 or -1
    /* 0x30C */ Vec3s* pathPoints;
    /* 0x310 */ f32 pathTotalDist;
    /* 0x314 */ Vec3f curPathPos;
    /* 0x320 */ f32 clockTime;
    /* 0x324 */ AlienBehaviorInfo behaviorInfo;
    /* 0x374 */ s8 rand;
    /* 0x376 */ u16 textId;
    /* 0x378 */ s8 unk378;
    /* 0x379 */ s8 unk379;
    /* 0x37C */ f32 unk37C[3];
    /* 0x388 */ s8 unk388; // unused
    /* 0x389 */ u8 alienAlpha;
    /* 0x38A */ s8 unk38A; // bool
    /* 0x38B */ s8 drawAlien;
    /* 0x38C */ s8 drawAlienDeathEffect;
    /* 0x38D */ u8 alienBeamAlpha;
    /* 0x390 */ Vec3f alienDeathEffectScale;
    /* 0x39C */ f32 scaleFactorAdj;
    /* 0x3A0 */ f32 scaleTarget;
    /* 0x3A4 */ f32 scaleStep;
    /* 0x3A8 */ s16 scaleAdjAngle;
    /* 0x3AA */ s16 unk3AA;
    /* 0x3AC */ s8 unk3AC; // index for D_80B4EDD0
    /* 0x3AD */ char unk3AD[0xF];
    /* 0x3BC */ s8 unk3BC;
} EnInvadepoh; // size = 0x3C0

extern const ActorInit En_Invadepoh_InitVars;

#endif // Z_EN_INVADEPOH_H
