#ifndef Z_OBJ_UM_H
#define Z_OBJ_UM_H

#include "global.h"
#include "overlays/actors/ovl_En_Horse/z_en_horse.h"

struct ObjUm;

typedef void (*ObjUmActionFunc)(struct ObjUm*, GlobalContext*);

typedef enum {
    /* 00 */ UM_LIMB_NONE,
    /* 01 */ UM_LIMB_01, // Chair and donkey attachment
    /* 02 */ UM_LIMB_WAGGON_ROOT,
    /* 03 */ UM_LIMB_WAGGON_RIGHT_WHEEL,
    /* 04 */ UM_LIMB_WAGGON_LEFT_WHEEL,
    /* 05 */ UM_LIMB_WAGGON_CART_BED,
    /* 06 */ UM_LIMB_WAGGON_HAND_BRAKE,
    /* 07 */ UM_LIMB_WAGGON_CART_COVER,
    /* 08 */ UM_LIMB_WAGGON_LEFT_LEAF_SPRING,
    /* 09 */ UM_LIMB_WAGGON_RIGHT_LEAF_SPRING,
    /* 10 */ UM_LIMB_WAGGON_STEERING_WHEEL,
    /* 11 */ UM_LIMB_CREMIA_ROOT,
    /* 12 */ UM_LIMB_CREMIA_THORAX,
    /* 13 */ UM_LIMB_CREMIA_HEAD,
    /* 14 */ UM_LIMB_CREMIA_HAIR,
    /* 15 */ UM_LIMB_CREMIA_LEFT_ARM,
    /* 16 */ UM_LIMB_CREMIA_LEFT_FOREARM,
    /* 17 */ UM_LIMB_CREMIA_LEFT_HAND,
    /* 18 */ UM_LIMB_CREMIA_RIGHT_ARM,
    /* 19 */ UM_LIMB_CREMIA_RIGHT_FOREARM,
    /* 20 */ UM_LIMB_CREMIA_RIGHT_HAND,
    /* 21 */ UM_LIMB_CREMIA_LOWER_BODY,
    /* 22 */ UM_LIMB_MAX
} ObjectUmLimbs;

typedef struct ObjUm {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ObjUmActionFunc actionFunc;
    /* 0x160 */ SkelAnime skelAnime;
    /* 0x1A4 */ Vec3s jointTable[UM_LIMB_MAX];
    /* 0x228 */ Vec3s morphTable[UM_LIMB_MAX];
    /* 0x2AC */ s16 unk_2AC; // x angle
    /* 0x2AE */ s16 type;
    /* 0x2B0 */ s16 unk_2B0;
    /* 0x2B4 */ s32 unk_2B4;
    /* 0x2B8 */ EnHorse* donkey;
    /* 0x2BC */ s32 pathIdx;
    /* 0x2BE */ s32 pointIdx;
    /* 0x2C4 */ Vec3f unk_2C4;
    /* 0x2D0 */ Vec3f unk_2D0;
    /* 0x2DC */ Vec3f unk_2DC;
    /* 0x2E8 */ Vec3f unk_2E8;
    /* 0x2F4 */ s32 flags;
    /* 0x2BC */ Vec3s unk_2F8;
    /* 0x2FE */ Vec3s unk_2FE;
    /* 0x304 */ s32 unk_304;
    /* 0x308 */ Vec3f unk_308;
    /* 0x314 */ s32 unk_314[3];
    /* 0x320 */ s32 unk_320[3];
    /* 0x32C */ Vec3f unk_32C[3];
    /* 0x350 */ s32 unk_350; // unused counter?
    /* 0x354 */ s32 unk_354; // unused?
    /* 0x358 */ EnHorse* bandit1;
    /* 0x35C */ EnHorse* bandit2;
    /* 0x360 */ Vec3f unk_360[16];
    /* 0x420 */ s32 unk_420;
    /* 0x424 */ ColliderCylinder banditsCollisions[2];
    /* 0x4BC */ Vec3f unk_4BC;
    /* 0x4C8 */ u16 unk_4C8; // time?
    /* 0x4CC */ s32 unk_4CC;
    /* 0x4D0 */ s32 eyeTexIndex;
    /* 0x4D4 */ s32 mouthTexIndex;
    /* 0x4D8 */ s32 unk_4D8;
    /* 0x4DC */ s32 unk_4DC;
    /* 0x4E0 */ s32 arePotsBroken;
} ObjUm; // size = 0x4E4

extern const ActorInit Obj_Um_InitVars;

typedef enum {
    /* 0 */ OBJ_UM_TYPE_TERMINA_FIELD,
    /* 1 */ OBJ_UM_TYPE_RANCH,
    /* 2 */ OBJ_UM_TYPE_PRE_MILK_RUN, // milk road, pre-minigame
    /* 3 */ OBJ_UM_TYPE_MILK_RUN_MINIGAME,
    /* 4 */ OBJ_UM_TYPE_POST_MILK_RUN // milk road, post-minigame
} ObjUmType;

#define OBJ_UM_PARSE_TYPE(params) ((params) & 0xFF00) >> 8

#define OBJ_UM_FLAG_0000 0x0000
#define OBJ_UM_FLAG_0001 0x0001
#define OBJ_UM_FLAG_0002 0x0002
#define OBJ_UM_FLAG_0004 0x0004
#define OBJ_UM_FLAG_0008 0x0008
#define OBJ_UM_FLAG_0010 0x0010
#define OBJ_UM_FLAG_0020 0x0020
#define OBJ_UM_FLAG_0040 0x0040
#define OBJ_UM_FLAG_0080 0x0080
#define OBJ_UM_FLAG_0100 0x0100
#define OBJ_UM_FLAG_0200 0x0200
#define OBJ_UM_FLAG_0400 0x0400
#define OBJ_UM_FLAG_0800 0x0800
#define OBJ_UM_FLAG_1000 0x1000
#define OBJ_UM_FLAG_2000 0x2000

#endif // Z_OBJ_UM_H
