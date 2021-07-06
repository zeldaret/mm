#ifndef Z_EN_INVADEPOH_H
#define Z_EN_INVADEPOH_H

#include <global.h>

struct EnInvadepoh;

typedef void (*EnInvadepohInitFunc)(struct EnInvadepoh*, GlobalContext*);
typedef void (*EnInvadepohDestroyFunc)(struct EnInvadepoh*, GlobalContext*);
typedef void (*EnInvadepohActionFunc)(struct EnInvadepoh*, GlobalContext*);
typedef void (*OtherFunc)(struct unkStruct_80B50350*);
typedef void (*OtherSubstructFunc)(struct EnInvadePohStruct*, s32 arg1);

typedef struct unkStruct_80B50350{
    /* 0x000 */ s8 unk0;
    /* 0x001 */ s8 unk1;
    /* 0x002 */ u8 unk2;
    /* 0x004 */ Vec3f unk4; // boundary 
} unkStruct_80B50350; // size = 0x10;

typedef struct {
    /* 0x00 */ s8* unk00;
    /* 0x04 */ s8 unk04;
} unkstruct_invadepoh_0; // size = 0x05

typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x04 */ f32 unk04;
} unkstruct_invadepoh_1; // size = 0x08

typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x04 */ unkstruct_invadepoh_0* unk04;
} unkstruct_invadepoh_2; // size = 0x08

typedef struct {
    /* 0x00 */ s8 unk0;
    /* 0x04 */ unkstruct_invadepoh_0* unk4;
    /* 0x08 */ s8 unk8;
    /* 0x0C */ unkstruct_invadepoh_1* unkC;
} unkstruct_invadepoh_3; // size = 0x10

typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x04 */ unkstruct_invadepoh_0* unk04;
    /* 0x08 */ s8 unk08;
    /* 0x0C */ unkstruct_invadepoh_1* unk0C;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
} unkstruct_invadepoh_4; // size = 0x14

typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
} unkstruct_80B4EE0C; // size = 0x08

typedef union unkstruct_invadepoh_union {
    struct {
        /* 0x0 */ s8 unk00;
        /* 0x4 */ unkstruct_invadepoh_0* unk04;
    } unkstruct_invadepoh_5;
    unkstruct_invadepoh_2 unk_struct_2_elem;
    unkstruct_invadepoh_3 unk_struct_3_elem;
    unkstruct_invadepoh_4 unk_struct_4_elem;
} unkstruct_invadepoh_union;

typedef struct EnInvadePohStruct{
    /* 0x000 */ s32* unk0;
    /* 0x004 */ s8 unk4;
    /* 0x005 */ char unk5[0x3];
    /* 0x008 */ unkstruct_invadepoh_4* unk8; // pointer to another struct
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
    /* 0x188 */ Vec3s limbDrawTable[23];
    /* 0x212 */ Vec3s transitionDrawTable[23];
    /* 0x29C */ s8 animPlayFlag;
    /* 0x2A0 */ ColliderCylinder collider;
    /* 0x2EC */ EnInvadepohActionFunc actionFunc;
    /* 0x2F0 */ s16 actionTimer;
    /* 0x2F2 */ s16 counter; // general counter variable
    /* 0x2F4 */ s8 bankIndex;
    /* 0x2F8 */ f32 unk2F8;
    /* 0x2FC */ f32 unk2FC;
    /* 0x300 */ f32 unk300;
    /* 0x304 */ s16 unk304; // angle of some sort
    /* 0x306 */ s16 unk306;
    /* 0x308 */ s8 unk308; // size of unk37C?
    /* 0x309 */ s8 unk309;
    /* 0x30A */ s8 unk30A;
    /* 0x30B */ s8 unk30B;
    /* 0x30C */ Vec3s* pathPoints;
    /* 0x310 */ f32 pathTotalDist;
    /* 0x314 */ Vec3f curPathPos;
    /* 0x320 */ f32 clockTime;
    /* 0x324 */ AlienBehaviorInfo behaviorInfo;
    /* 0x374 */ s8 unk374;
    /* 0x375 */ s8 unk375;
    /* 0x376 */ u16 textId;
    /* 0x378 */ s8 unk378;
    /* 0x379 */ s8 unk379;
    /* 0x37C */ f32 unk37C[3];
    /* 0x388 */ s8 unk388;
    /* 0x389 */ u8 alienAlpha;
    /* 0x38A */ s8 unk38A;
    /* 0x38B */ s8 drawAlien;
    /* 0x38C */ s8 drawAlienDeathEffect;
    /* 0x38D */ u8 alienBeamAlpha;
    /* 0x390 */ Vec3f alienDeathEffectScale;
    /* 0x39C */ f32 unk39C;
    /* 0x3A0 */ f32 unk3A0;
    /* 0x3A4 */ f32 unk3A4;
    /* 0x3A8 */ s16 unk3A8;
    /* 0x3AA */ s16 unk3AA;
    /* 0x3AC */ s8 unk3AC;
    /* 0x3B0 */ Vec3f unk3B0;
    /* 0x3BC */ s8 unk3BC;
} EnInvadepoh; // size = 0x3C0

extern const ActorInit En_Invadepoh_InitVars;

#endif // Z_EN_INVADEPOH_H

//look at en_ma_yts for inspiration for improvements

/* TO-DO:
-clean up jank functions
-look into structs and make sure they make sense
-make sure including en_door.h is okay as is"
-rename OtherFunc
-look into phi_s0 = D_80B50350 stuff
*/
