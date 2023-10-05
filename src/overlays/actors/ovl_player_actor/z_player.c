/*
 * File: z_player.c
 * Overlay: ovl_player_actor
 * Description: Player
 */

#include "global.h"
#include "z64horse.h"
#include "z64quake.h"
#include "z64rumble.h"
#include "z64shrink_window.h"

#include "overlays/actors/ovl_Arms_Hook/z_arms_hook.h"
#include "overlays/actors/ovl_Door_Spiral/z_door_spiral.h"
#include "overlays/actors/ovl_Door_Shutter/z_door_shutter.h"
#include "overlays/actors/ovl_En_Arrow/z_en_arrow.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"
#include "overlays/actors/ovl_En_Boom/z_en_boom.h"
#include "overlays/actors/ovl_En_Box/z_en_box.h"
#include "overlays/actors/ovl_En_Dnp/z_en_dnp.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"
#include "overlays/actors/ovl_En_Elf/z_en_elf.h"
#include "overlays/actors/ovl_En_Fish/z_en_fish.h"
#include "overlays/actors/ovl_En_Horse/z_en_horse.h"
#include "overlays/actors/ovl_En_Ishi/z_en_ishi.h"
#include "overlays/actors/ovl_En_Mushi2/z_en_mushi2.h"
#include "overlays/actors/ovl_En_Ot/z_en_ot.h"
#include "overlays/actors/ovl_En_Test3/z_en_test3.h"
#include "overlays/actors/ovl_En_Test5/z_en_test5.h"
#include "overlays/actors/ovl_En_Test7/z_en_test7.h"
#include "overlays/actors/ovl_En_Torch2/z_en_torch2.h"
#include "overlays/actors/ovl_En_Zoraegg/z_en_zoraegg.h"
#include "overlays/actors/ovl_Obj_Aqua/z_obj_aqua.h"

#include "overlays/effects/ovl_Effect_Ss_Fhg_Flash/z_eff_ss_fhg_flash.h"
#include "overlays/effects/ovl_Effect_Ss_G_Splash/z_eff_ss_g_splash.h"

#include "objects/gameplay_keep/gameplay_keep.h"

#include "objects/object_link_boy/object_link_boy.h"
#include "objects/object_link_goron/object_link_goron.h"
#include "objects/object_link_zora/object_link_zora.h"
#include "objects/object_link_nuts/object_link_nuts.h"
#include "objects/object_link_child/object_link_child.h"

#define THIS ((Player*)thisx)

void Player_Init(Actor* thisx, PlayState* play);
void Player_Destroy(Actor* thisx, PlayState* play);
void Player_Update(Actor* thisx, PlayState* play);
void Player_Draw(Actor* thisx, PlayState* play);

s32 Player_GrabPlayer(PlayState* play, Player* this);
s32 func_8085B28C(PlayState* play, Player* this, PlayerCsMode csMode);
void func_8085B384(Player* this, PlayState* play);
s32 Player_InflictDamage(PlayState* play, s32 damage);
void Player_TalkWithPlayer(PlayState* play, Actor* actor);
void func_8085B74C(PlayState* play);
void func_8085B820(PlayState* play, s16 arg1);
PlayerItemAction func_8085B854(PlayState* play, Player* this, ItemId itemId);
s32 func_8085B930(PlayState* play, PlayerAnimationHeader* talkAnim, AnimationMode animMode);

void Player_UpdateCommon(Player* this, PlayState* play, Input* input);
s32 Player_StartFishing(PlayState* play);
void func_8085B170(PlayState* play, Player* this);
s32 func_8083A658(PlayState* play, Player* this);
void Player_InitItemAction(PlayState* play, Player* this, PlayerItemAction itemAction);

void Player_UseItem(PlayState* play, Player* this, ItemId item);

void func_80836988(Player* this, PlayState* play);

void func_808484F0(Player* this);

void func_80838A20(PlayState* play, Player* this);
void func_80839978(PlayState* play, Player* this);
void func_80839A10(PlayState* play, Player* this);

typedef enum AnimSfxType {
    /*  1 */ ANIMSFX_TYPE_GENERAL = 1,
    /*  2 */ ANIMSFX_TYPE_FLOOR,
    /*  3 */ ANIMSFX_TYPE_FLOOR_BY_AGE,
    /*  4 */ ANIMSFX_TYPE_VOICE,
    /*  5 */ ANIMSFX_TYPE_FLOOR_LAND, // does not use sfxId
    /*  6 */ ANIMSFX_TYPE_6,          // FLOOR_WALK_Something // does not use sfxId
    /*  7 */ ANIMSFX_TYPE_FLOOR_JUMP, // does not use sfxId
    /*  8 */ ANIMSFX_TYPE_8,          // FLOOR_WALK_Something2 // does not use sfxId
    /*  9 */ ANIMSFX_TYPE_9,          // Uses NA_SE_PL_WALK_LADDER // does not use sfxId, unused
    /* 10 */ ANIMSFX_TYPE_SURFACE
} AnimSfxType;

#define ANIMSFX_SHIFT_TYPE(type) ((type) << 11)

#define ANIMSFX_CONTINUE (1)
#define ANIMSFX_STOP (0)

#define ANIMSFX_FLAGS(type, frame, cont) \
    (((ANIMSFX_##cont) == ANIMSFX_STOP ? -1 : 1) * (ANIMSFX_SHIFT_TYPE(type) | ((frame)&0x7FF)))

#define ANIMSFX(type, frame, sfxId, cont) \
    { (sfxId), ANIMSFX_FLAGS(type, frame, cont) }

#define ANIMSFX_GET_TYPE(data) ((data)&0x7800)
#define ANIMSFX_GET_FRAME(data) ((data)&0x7FF)

typedef struct AnimSfxEntry {
    /* 0x0 */ u16 sfxId;
    /* 0x2 */ s16 flags; // negative marks the end
} AnimSfxEntry;          // size = 0x4

/* action funcs */
void Player_Action_0(Player* this, PlayState* play);
void Player_Action_1(Player* this, PlayState* play);
void Player_Action_2(Player* this, PlayState* play);
void Player_Action_3(Player* this, PlayState* play);
void Player_Action_4(Player* this, PlayState* play);
void Player_Action_5(Player* this, PlayState* play);
void Player_Action_6(Player* this, PlayState* play);
void Player_Action_7(Player* this, PlayState* play);
void Player_Action_8(Player* this, PlayState* play);
void Player_Action_9(Player* this, PlayState* play);
void Player_Action_10(Player* this, PlayState* play);
void Player_Action_11(Player* this, PlayState* play);
void Player_Action_12(Player* this, PlayState* play);
void Player_Action_13(Player* this, PlayState* play);
void Player_Action_14(Player* this, PlayState* play);
void Player_Action_15(Player* this, PlayState* play);
void Player_Action_16(Player* this, PlayState* play);
void Player_Action_17(Player* this, PlayState* play);
void Player_Action_18(Player* this, PlayState* play);
void Player_Action_19(Player* this, PlayState* play);
void Player_Action_20(Player* this, PlayState* play);
void Player_Action_21(Player* this, PlayState* play);
void Player_Action_22(Player* this, PlayState* play);
void Player_Action_23(Player* this, PlayState* play);
void Player_Action_24(Player* this, PlayState* play);
void Player_Action_25(Player* this, PlayState* play);
void Player_Action_26(Player* this, PlayState* play);
void Player_Action_27(Player* this, PlayState* play);
void Player_Action_28(Player* this, PlayState* play);
void Player_Action_29(Player* this, PlayState* play);
void Player_Action_30(Player* this, PlayState* play);
void Player_Action_31(Player* this, PlayState* play);
void Player_Action_32(Player* this, PlayState* play);
void Player_Action_33(Player* this, PlayState* play);
void Player_Action_34(Player* this, PlayState* play);
void Player_Action_35(Player* this, PlayState* play);
void Player_Action_36(Player* this, PlayState* play);
void Player_Action_37(Player* this, PlayState* play);
void Player_Action_38(Player* this, PlayState* play);
void Player_Action_39(Player* this, PlayState* play);
void Player_Action_40(Player* this, PlayState* play);
void Player_Action_41(Player* this, PlayState* play);
void Player_Action_42(Player* this, PlayState* play);
void Player_Action_43(Player* this, PlayState* play);
void Player_Action_44(Player* this, PlayState* play);
void Player_Action_45(Player* this, PlayState* play);
void Player_Action_46(Player* this, PlayState* play);
void Player_Action_47(Player* this, PlayState* play);
void Player_Action_48(Player* this, PlayState* play);
void Player_Action_49(Player* this, PlayState* play);
void Player_Action_50(Player* this, PlayState* play);
void Player_Action_51(Player* this, PlayState* play);
void Player_Action_52(Player* this, PlayState* play);
void Player_Action_53(Player* this, PlayState* play);
void Player_Action_54(Player* this, PlayState* play);
void Player_Action_55(Player* this, PlayState* play);
void Player_Action_56(Player* this, PlayState* play);
void Player_Action_57(Player* this, PlayState* play);
void Player_Action_58(Player* this, PlayState* play);
void Player_Action_59(Player* this, PlayState* play);
void Player_Action_60(Player* this, PlayState* play);
void Player_Action_61(Player* this, PlayState* play);
void Player_Action_62(Player* this, PlayState* play);
void Player_Action_63(Player* this, PlayState* play);
void Player_Action_64(Player* this, PlayState* play);
void Player_Action_65(Player* this, PlayState* play);
void Player_Action_66(Player* this, PlayState* play);
void Player_Action_67(Player* this, PlayState* play);
void Player_Action_68(Player* this, PlayState* play);
void Player_Action_69(Player* this, PlayState* play);
void Player_Action_70(Player* this, PlayState* play);
void Player_Action_71(Player* this, PlayState* play);
void Player_Action_72(Player* this, PlayState* play);
void Player_Action_73(Player* this, PlayState* play);
void Player_Action_74(Player* this, PlayState* play);
void Player_Action_75(Player* this, PlayState* play);
void Player_Action_76(Player* this, PlayState* play);
void Player_Action_77(Player* this, PlayState* play);
void Player_Action_78(Player* this, PlayState* play);
void Player_Action_79(Player* this, PlayState* play);
void Player_Action_80(Player* this, PlayState* play);
void Player_Action_81(Player* this, PlayState* play);
void Player_Action_82(Player* this, PlayState* play);
void Player_Action_83(Player* this, PlayState* play);
void Player_Action_84(Player* this, PlayState* play);
void Player_Action_85(Player* this, PlayState* play);
void Player_Action_86(Player* this, PlayState* play);
void Player_Action_87(Player* this, PlayState* play);
void Player_Action_88(Player* this, PlayState* play);
void Player_Action_89(Player* this, PlayState* play);
void Player_Action_90(Player* this, PlayState* play);
void Player_Action_91(Player* this, PlayState* play);
void Player_Action_92(Player* this, PlayState* play);
void Player_Action_93(Player* this, PlayState* play);
void Player_Action_94(Player* this, PlayState* play);
void Player_Action_95(Player* this, PlayState* play);
void Player_Action_96(Player* this, PlayState* play);
void Player_Action_97(Player* this, PlayState* play);

s32 Player_UpperAction_0(Player* this, PlayState* play);
s32 Player_UpperAction_1(Player* this, PlayState* play);
s32 Player_UpperAction_ChangeHeldItem(Player* this, PlayState* play);
s32 Player_UpperAction_3(Player* this, PlayState* play);
s32 Player_UpperAction_4(Player* this, PlayState* play);
s32 Player_UpperAction_5(Player* this, PlayState* play);
s32 Player_UpperAction_6(Player* this, PlayState* play);
s32 Player_UpperAction_7(Player* this, PlayState* play);
s32 Player_UpperAction_8(Player* this, PlayState* play);
s32 Player_UpperAction_9(Player* this, PlayState* play);
s32 Player_UpperAction_10(Player* this, PlayState* play);
s32 Player_UpperAction_11(Player* this, PlayState* play);
s32 Player_UpperAction_12(Player* this, PlayState* play);
s32 Player_UpperAction_13(Player* this, PlayState* play);
s32 Player_UpperAction_14(Player* this, PlayState* play);
s32 Player_UpperAction_15(Player* this, PlayState* play);
s32 Player_UpperAction_16(Player* this, PlayState* play);

void Player_InitItemAction_DoNothing(PlayState* play, Player* this);
void Player_InitItemAction_DekuStick(PlayState* play, Player* this);
void Player_InitItemAction_2(PlayState* play, Player* this);
void Player_InitItemAction_SpawnExplosive(PlayState* play, Player* this);
void Player_InitItemAction_SpawnHookshot(PlayState* play, Player* this);
void Player_InitItemAction_5(PlayState* play, Player* this);

s32 Player_ActionChange_0(Player* this, PlayState* play);
s32 Player_ActionChange_1(Player* this, PlayState* play);
s32 Player_ActionChange_2(Player* this, PlayState* play);
s32 Player_ActionChange_3(Player* this, PlayState* play);
s32 Player_ActionChange_4(Player* this, PlayState* play);
s32 Player_ActionChange_5(Player* this, PlayState* play);
s32 Player_ActionChange_6(Player* this, PlayState* play);
s32 Player_ActionChange_7(Player* this, PlayState* play);
s32 Player_ActionChange_8(Player* this, PlayState* play);
s32 Player_ActionChange_9(Player* this, PlayState* play);
s32 Player_ActionChange_10(Player* this, PlayState* play);
s32 Player_ActionChange_11(Player* this, PlayState* play);
s32 Player_ActionChange_12(Player* this, PlayState* play);
s32 Player_ActionChange_13(Player* this, PlayState* play);
s32 Player_ActionChange_14(Player* this, PlayState* play);

/* Init Mode functions */
void Player_InitMode_0(PlayState* play, Player* this);
void Player_InitMode_1(PlayState* play, Player* this);
void Player_InitMode_2(PlayState* play, Player* this);
void Player_InitMode_3(PlayState* play, Player* this);
void Player_InitMode_4(PlayState* play, Player* this);
void Player_InitMode_5(PlayState* play, Player* this);
void Player_InitMode_6(PlayState* play, Player* this);
void Player_InitMode_7(PlayState* play, Player* this);
void func_80841744(PlayState* play, Player* this);
void func_80841744(PlayState* play, Player* this);
void func_8083ADF0(PlayState* play, Player* this);
void Player_InitMode_B(PlayState* play, Player* this);
void Player_InitMode_Telescope(PlayState* play, Player* this);
void Player_InitMode_D(PlayState* play, Player* this);
void func_8083ADF0(PlayState* play, Player* this);
void Player_InitMode_F(PlayState* play, Player* this);

/* Cutscene functions */
void Player_CsAction_0(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_1(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_2(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_3(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_4(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_5(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_6(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_7(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_8(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_9(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_10(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_11(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_12(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_13(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_14(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_15(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_16(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_17(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_18(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_19(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_20(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_21(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_22(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_23(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_TranslateReverse(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_25(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_26(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_27(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_28(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_29(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_30(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_31(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_32(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_33(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_34(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_35(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_36(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_37(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_38(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_39(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_40(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_41(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_42(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_43(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_44(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_45(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_46(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_End(PlayState* play, Player* this, CsCmdActorCue* cue);
void Player_CsAction_48(PlayState* play, Player* this, CsCmdActorCue* cue);

void Player_CsAnim_1(PlayState* play, Player* this, void* arg2);   // void* arg2
void Player_CsAnim_2(PlayState* play, Player* this, void* anim);   // PlayerAnimationHeader* anim
void Player_CsAnim_3(PlayState* play, Player* this, void* anim);   // PlayerAnimationHeader* anim
void Player_CsAnim_4(PlayState* play, Player* this, void* anim);   // PlayerAnimationHeader* anim
void Player_CsAnim_5(PlayState* play, Player* this, void* anim);   // PlayerAnimationHeader* anim
void Player_CsAnim_6(PlayState* play, Player* this, void* anim);   // PlayerAnimationHeader* anim
void Player_CsAnim_7(PlayState* play, Player* this, void* anim);   // PlayerAnimationHeader* anim
void Player_CsAnim_8(PlayState* play, Player* this, void* anim);   // PlayerAnimationHeader* anim
void Player_CsAnim_9(PlayState* play, Player* this, void* anim);   // PlayerAnimationHeader* anim
void Player_CsAnim_10(PlayState* play, Player* this, void* anim);  // PlayerAnimationHeader* anim
void Player_CsAnim_11(PlayState* play, Player* this, void* cue);   // CsCmdActorCue* cue
void Player_CsAnim_12(PlayState* play, Player* this, void* anim);  // PlayerAnimationHeader* anim
void Player_CsAnim_13(PlayState* play, Player* this, void* anim);  // PlayerAnimationHeader* anim
void Player_CsAnim_14(PlayState* play, Player* this, void* anim);  // PlayerAnimationHeader* anim
void Player_CsAnim_15(PlayState* play, Player* this, void* anim);  // PlayerAnimationHeader* anim
void Player_CsAnim_16(PlayState* play, Player* this, void* anim);  // PlayerAnimationHeader* anim
void Player_CsAnim_17(PlayState* play, Player* this, void* anim);  // PlayerAnimationHeader* anim
void Player_CsAnim_18(PlayState* play, Player* this, void* entry); // AnimSfxEntry* entry
void Player_CsAnim_19(PlayState* play, Player* this, void* anim);  // PlayerAnimationHeader* anim

typedef struct struct_8085C2A4 {
    /* 0x0 */ PlayerAnimationHeader* unk_0;
    /* 0x4 */ PlayerAnimationHeader* unk_4;
    /* 0x8 */ PlayerAnimationHeader* unk_8;
} struct_8085C2A4; // size = 0xC

typedef struct BlureColors {
    /* 0x0 */ u8 p1StartColor[4];
    /* 0x4 */ u8 p2StartColor[4];
    /* 0x8 */ u8 p1EndColor[4];
    /* 0xC */ u8 p2EndColor[4];
} BlureColors; // size = 0x10

typedef void (*PlayerCsAnim)(PlayState*, Player*, void*);
typedef void (*PlayerCsAction)(PlayState*, Player*, CsCmdActorCue*);

typedef enum {
    /*   -1 */ PLAYER_CSTYPE_ACTION = -1,
    /* 0x00 */ PLAYER_CSTYPE_NONE,
    /* 0x01 */ PLAYER_CSTYPE_ANIM_1,
    /* 0x02 */ PLAYER_CSTYPE_ANIM_2,
    /* 0x03 */ PLAYER_CSTYPE_ANIM_3,
    /* 0x04 */ PLAYER_CSTYPE_ANIM_4,
    /* 0x05 */ PLAYER_CSTYPE_ANIM_5,
    /* 0x06 */ PLAYER_CSTYPE_ANIM_6,
    /* 0x07 */ PLAYER_CSTYPE_ANIM_7,
    /* 0x08 */ PLAYER_CSTYPE_ANIM_8,
    /* 0x09 */ PLAYER_CSTYPE_ANIM_9,
    /* 0x0A */ PLAYER_CSTYPE_ANIM_10,
    /* 0x0B */ PLAYER_CSTYPE_ANIM_11,
    /* 0x0C */ PLAYER_CSTYPE_ANIM_12,
    /* 0x0D */ PLAYER_CSTYPE_ANIM_13,
    /* 0x0E */ PLAYER_CSTYPE_ANIM_14,
    /* 0x0F */ PLAYER_CSTYPE_ANIM_15,
    /* 0x10 */ PLAYER_CSTYPE_ANIM_16,
    /* 0x11 */ PLAYER_CSTYPE_ANIM_17,
    /* 0x12 */ PLAYER_CSTYPE_ANIM_18,
    /* 0x13 */ PLAYER_CSTYPE_ANIM_19
} PlayerCsType;

typedef struct PlayerCsModeEntry {
    /* 0x0 */ s8 type; // PlayerCsType enum
    /* 0x4 */ union {
        void* ptr; // Do not use, required in the absence of designated initialisors
        PlayerCsAction csActionFunc;
        void* csAnimArg2; // Can point to any of the below in the union
        PlayerAnimationHeader* anim;
        AnimSfxEntry* entry;
        CsCmdActorCue* cue;
    };
} PlayerCsModeEntry; // size = 0x8

typedef struct struct_8085E368 {
    /* 0x0 */ Vec3s base;
    /* 0x6 */ Vec3s range;
} struct_8085E368; // size = 0xC

typedef struct struct_8085D910 {
    /* 0x0 */ u8 unk_0;
    /* 0x1 */ u8 unk_1;
    /* 0x2 */ u8 unk_2;
    /* 0x3 */ u8 unk_3;
} struct_8085D910; // size = 0x4

typedef struct struct_8085D848_unk_00 {
    /* 0x0 */ s16 fogNear;
    /* 0x2 */ u8 fogColor[3];
    /* 0x5 */ u8 ambientColor[3];
} struct_8085D848_unk_00; // size = 0x8

typedef struct struct_8085D848_unk_18 {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ u8 color[3];
    /* 0x10 */ s16 radius;
} struct_8085D848_unk_18; // size = 0x14

typedef struct struct_8085D848 {
    /* 0x00 */ struct_8085D848_unk_00 unk_00[3];
    /* 0x18 */ struct_8085D848_unk_18 light[3];
} struct_8085D848; // size = 0x54

typedef struct struct_8085D80C {
    /* 0x0 */ s16 actorId;
    /* 0x2 */ s16 params;
} struct_8085D80C; // size = 0x4

typedef struct struct_8085D798 {
    /* 0x0 */ s16 actorId;
    /* 0x2 */ s8 actorParams;
    /* 0x3 */ u8 itemId;
    /* 0x4 */ u8 itemAction;
    /* 0x5 */ u8 textId;
} struct_8085D798; // size = 0x6

typedef struct struct_8085D714 {
    /* 0x0 */ u8 unk_0;
    /* 0x4 */ PlayerAnimationHeader* unk_4;
} struct_8085D714; // size = 0x8

typedef struct struct_8085D224 {
    /* 0x0 */ PlayerAnimationHeader* anim;
    /* 0x4 */ f32 unk_4;
    /* 0x8 */ f32 unk_8;
} struct_8085D224; // size = 0xC

typedef struct FallImpactInfo {
    /* 0x0 */ s8 damage;
    /* 0x1 */ u8 sourceIntensity;
    /* 0x2 */ u8 decayTimer;
    /* 0x3 */ u8 decayStep;
    /* 0x4 */ u16 sfxId;
} FallImpactInfo; // size = 0x6

typedef struct AttackAnimInfo {
    /* 0x00 */ PlayerAnimationHeader* unk_0;
    /* 0x04 */ PlayerAnimationHeader* unk_4;
    /* 0x08 */ PlayerAnimationHeader* unk_8;
    /* 0x0C */ u8 unk_C;
    /* 0x0D */ u8 unk_D;
} AttackAnimInfo; // size = 0x10

typedef struct MeleeWeaponDamageInfo {
    /* 0x0 */ s32 dmgFlags;
    // Presumably these two fields are intended for Fierce Deity, but will also work for Deku if it can equip a sword
    /* 0x4 */ u8 dmgTransformedNormal;
    /* 0x5 */ u8 dmgTransformedStrong;
    /* 0x6 */ u8 dmgHumanNormal;
    /* 0x7 */ u8 dmgHumanStrong;
} MeleeWeaponDamageInfo; // size = 0x8

typedef struct ItemChangeInfo {
    /* 0x0 */ PlayerAnimationHeader* anim;
    /* 0x4 */ u8 changeFrame;
} ItemChangeInfo; // size = 0x8

typedef struct {
    /* 0x0 */ u8 itemId;
    /* 0x2 */ s16 actorId;
} ExplosiveInfo; // size = 0x4

typedef struct {
    /* 0x0 */ Color_RGB8 ambientColor;
    /* 0x3 */ Color_RGB8 diffuseColor;
    /* 0x6 */ Color_RGB8 fogColor;
    /* 0xA */ s16 fogNear;
    /* 0xC */ s16 zFar;
} PlayerEnvLighting; // size = 0xE

typedef struct GetItemEntry {
    /* 0x0 */ u8 itemId;
    /* 0x1 */ u8 field; // various bit-packed data
    /* 0x2 */ s8 gid;   // defines the draw id and chest opening animation
    /* 0x3 */ u8 textId;
    /* 0x4 */ u16 objectId;
} GetItemEntry; // size = 0x6

typedef struct struct_8085D200 {
    /* 0x0 */ PlayerAnimationHeader* unk_0;
    /* 0x4 */ PlayerAnimationHeader* unk_4;
    /* 0x8 */ u8 unk_8;
    /* 0x9 */ u8 unk_9;
} struct_8085D200; // size = 0xC

f32 sPlayerControlStickMagnitude;
s16 sPlayerControlStickAngle;
s16 D_80862B02; // analog stick yaw + camera yaw
s32 D_80862B04; // boolean, set to the return value of Player_UpdateUpperBody
FloorType sPlayerFloorType;
u32 sPlayerTouchedWallFlags;
ConveyorSpeed sPlayerConveyorSpeedIndex;
s16 sPlayerIsOnFloorConveyor;
s16 sPlayerConveyorYaw;
f32 sPlayerYDistToFloor;
FloorProperty sPlayerPrevFloorProperty;
s32 sPlayerShapeYawToTouchedWall;
s32 sPlayerWorldYawToTouchedWall;
s16 sPlayerFloorPitchShape;
s32 D_80862B2C; // D_80862B2C = player->currentMask;
Vec3f sPlayerInteractWallCheckResult;
f32 D_80862B3C;
FloorEffect sPlayerFloorEffect;
Input* sPlayerControlInput;
s32 sPlayerUseHeldItem;              // When true, the current held item is used. Is reset to false every frame.
s32 sPlayerHeldItemButtonIsHeldDown; // Indicates if the button for the current held item is held down.
AdjLightSettings D_80862B50;         // backup of lay->envCtx.adjLightSettings
s32 D_80862B6C;                      // this->skelAnime.moveFlags // sPlayerSkelMoveFlags?

s32 func_8082DA90(PlayState* play) {
    return (play->transitionTrigger != TRANS_TRIGGER_OFF) || (play->transitionMode != TRANS_MODE_OFF);
}

void Player_StopHorizontalMovement(Player* this) {
    this->linearVelocity = 0.0f;
    this->actor.speed = 0.0f;
}

void func_8082DAD4(Player* this) {
    Player_StopHorizontalMovement(this);
    this->unk_AA5 = PLAYER_UNKAA5_0;
}

s32 func_8082DAFC(PlayState* play) {
    Player* player = GET_PLAYER(play);

    return CHECK_FLAG_ALL(player->actor.flags, ACTOR_FLAG_TALK_REQUESTED);
}

void Player_AnimationPlayOnce(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    PlayerAnimation_PlayOnce(play, &this->skelAnime, anim);
}

void Player_AnimationPlayLoop(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    PlayerAnimation_PlayLoop(play, &this->skelAnime, anim);
}

void func_8082DB60(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    PlayerAnimation_PlayLoopSetSpeed(play, &this->skelAnime, anim, 2.0f / 3.0f);
}

void func_8082DB90(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    PlayerAnimation_PlayOnceSetSpeed(play, &this->skelAnime, anim, 2.0f / 3.0f);
}

void Player_AnimationPlayOnceReverse(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    PlayerAnimation_Change(play, &this->skelAnime, anim, -2.0f / 3.0f, Animation_GetLastFrame(anim), 0.0f,
                           ANIMMODE_ONCE, 0.0f);
}

void func_8082DC28(Player* this) {
    this->skelAnime.jointTable[PLAYER_LIMB_WAIST - 1].y = 0;
}

void func_8082DC38(Player* this) {
    this->stateFlags2 &= ~PLAYER_STATE2_20000;
    this->meleeWeaponState = PLAYER_MELEE_WEAPON_STATE_0;
    this->meleeWeaponInfo[2].active = false;
    this->meleeWeaponInfo[1].active = false;
    this->meleeWeaponInfo[0].active = false;
}

void func_8082DC64(PlayState* play, Player* this) {
    if ((this->subCamId != CAM_ID_NONE) && (play->cameraPtrs[this->subCamId] != NULL)) {
        this->subCamId = CAM_ID_NONE;
    }

    this->stateFlags2 &= ~(PLAYER_STATE2_400 | PLAYER_STATE2_800);
}

void Player_DetachHeldActor(PlayState* play, Player* this) {
    Actor* heldActor = this->heldActor;

    if ((heldActor != NULL) && !Player_IsHoldingHookshot(this)) {
        this->actor.child = NULL;
        this->heldActor = NULL;
        this->interactRangeActor = NULL;
        heldActor->parent = NULL;
        this->stateFlags1 &= ~PLAYER_STATE1_800;
    }

    if (Player_GetExplosiveHeld(this) > PLAYER_EXPLOSIVE_NONE) {
        Player_InitItemAction(play, this, PLAYER_IA_NONE);
        this->heldItemId = ITEM_FE;
    }
}

void func_8082DD2C(PlayState* play, Player* this) {
    if ((this->stateFlags1 & PLAYER_STATE1_800) && (this->heldActor == NULL)) {
        if (this->interactRangeActor != NULL) {
            if (this->getItemId == GI_NONE) {
                this->stateFlags1 &= ~PLAYER_STATE1_800;
                this->interactRangeActor = NULL;
            }
        } else {
            this->stateFlags1 &= ~PLAYER_STATE1_800;
        }
    }

    func_8082DC38(this);
    this->unk_AA5 = PLAYER_UNKAA5_0;
    func_8082DC64(play, this);
    func_800E0238(Play_GetCamera(play, CAM_ID_MAIN));
    this->stateFlags1 &=
        ~(PLAYER_STATE1_4 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000 | PLAYER_STATE1_100000 | PLAYER_STATE1_200000);
    this->stateFlags2 &= ~(PLAYER_STATE2_10 | PLAYER_STATE2_80);
    this->unk_ADD = 0;
    this->unk_ADC = 0;
    this->actor.shape.rot.x = 0;
    this->actor.shape.rot.z = 0;
    this->unk_ABC = 0.0f;
    this->unk_AC0 = 0.0f;
}

s32 func_8082DE14(PlayState* play, Player* this) {
    if (this->heldItemAction > PLAYER_IA_LAST_USED) {
        Player_UseItem(play, this, ITEM_NONE);
        return true;
    } else {
        return false;
    }
}

void func_8082DE50(PlayState* play, Player* this) {
    func_8082DD2C(play, this);
    Player_DetachHeldActor(play, this);
}

s32 func_8082DE88(Player* this, s32 arg1, s32 arg2) {
    s16 controlStickAngleDiff = this->prevControlStickAngle - sPlayerControlStickAngle;

    this->actionVar2 +=
        arg1 + TRUNCF_BINANG(ABS_ALT(controlStickAngleDiff) * fabsf(sPlayerControlStickMagnitude) * (1.0f / 0x600F0));

    if (CHECK_BTN_ANY(sPlayerControlInput->press.button, BTN_B | BTN_A)) {
        this->actionVar2 += 5;
    }

    return this->actionVar2 >= arg2;
}

void func_8082DF2C(PlayState* play) {
    if (play->actorCtx.freezeFlashTimer == 0) {
        play->actorCtx.freezeFlashTimer = 1;
    }
}

u8 sPlayerUpperBodyLimbCopyMap[PLAYER_LIMB_MAX] = {
    false, // PLAYER_LIMB_NONE
    false, // PLAYER_LIMB_ROOT
    false, // PLAYER_LIMB_WAIST
    false, // PLAYER_LIMB_LOWER_ROOT
    false, // PLAYER_LIMB_R_THIGH
    false, // PLAYER_LIMB_R_SHIN
    false, // PLAYER_LIMB_R_FOOT
    false, // PLAYER_LIMB_L_THIGH
    false, // PLAYER_LIMB_L_SHIN
    false, // PLAYER_LIMB_L_FOOT
    true,  // PLAYER_LIMB_UPPER_ROOT
    true,  // PLAYER_LIMB_HEAD
    true,  // PLAYER_LIMB_HAT
    true,  // PLAYER_LIMB_COLLAR
    true,  // PLAYER_LIMB_L_SHOULDER
    true,  // PLAYER_LIMB_L_FOREARM
    true,  // PLAYER_LIMB_L_HAND
    true,  // PLAYER_LIMB_R_SHOULDER
    true,  // PLAYER_LIMB_R_FOREARM
    true,  // PLAYER_LIMB_R_HAND
    true,  // PLAYER_LIMB_SHEATH
    true,  // PLAYER_LIMB_TORSO
};
u8 D_8085BA08[PLAYER_LIMB_MAX] = {
    false, // PLAYER_LIMB_NONE
    false, // PLAYER_LIMB_ROOT
    false, // PLAYER_LIMB_WAIST
    false, // PLAYER_LIMB_LOWER_ROOT
    false, // PLAYER_LIMB_R_THIGH
    false, // PLAYER_LIMB_R_SHIN
    false, // PLAYER_LIMB_R_FOOT
    false, // PLAYER_LIMB_L_THIGH
    false, // PLAYER_LIMB_L_SHIN
    false, // PLAYER_LIMB_L_FOOT
    false, // PLAYER_LIMB_UPPER_ROOT
    false, // PLAYER_LIMB_HEAD
    false, // PLAYER_LIMB_HAT
    false, // PLAYER_LIMB_COLLAR
    true,  // PLAYER_LIMB_L_SHOULDER
    true,  // PLAYER_LIMB_L_FOREARM
    true,  // PLAYER_LIMB_L_HAND
    false, // PLAYER_LIMB_R_SHOULDER
    false, // PLAYER_LIMB_R_FOREARM
    false, // PLAYER_LIMB_R_HAND
    false, // PLAYER_LIMB_SHEATH
    false, // PLAYER_LIMB_TORSO
};
u8 D_8085BA20[PLAYER_LIMB_MAX] = {
    false, // PLAYER_LIMB_NONE
    false, // PLAYER_LIMB_ROOT
    false, // PLAYER_LIMB_WAIST
    false, // PLAYER_LIMB_LOWER_ROOT
    false, // PLAYER_LIMB_R_THIGH
    false, // PLAYER_LIMB_R_SHIN
    false, // PLAYER_LIMB_R_FOOT
    false, // PLAYER_LIMB_L_THIGH
    false, // PLAYER_LIMB_L_SHIN
    false, // PLAYER_LIMB_L_FOOT
    false, // PLAYER_LIMB_UPPER_ROOT
    false, // PLAYER_LIMB_HEAD
    false, // PLAYER_LIMB_HAT
    false, // PLAYER_LIMB_COLLAR
    false, // PLAYER_LIMB_L_SHOULDER
    false, // PLAYER_LIMB_L_FOREARM
    false, // PLAYER_LIMB_L_HAND
    true,  // PLAYER_LIMB_R_SHOULDER
    true,  // PLAYER_LIMB_R_FOREARM
    true,  // PLAYER_LIMB_R_HAND
    false, // PLAYER_LIMB_SHEATH
    false, // PLAYER_LIMB_TORSO
};

void Player_RequestRumble(PlayState* play, Player* this, s32 sourceIntensity, s32 decayTimer, s32 decayStep,
                          s32 distSq) {
    if (this == GET_PLAYER(play)) {
        Rumble_Request(distSq, sourceIntensity, decayTimer, decayStep);
    }
}

// TODO: less dumb name
#define SFX_VOICE_BANK_SIZE 0x20

PlayerAgeProperties sPlayerAgeProperties[PLAYER_FORM_MAX] = {
    {
        // ceilingCheckHeight
        84.0f,
        // shadowScale
        90.0f,
        // unk_08
        1.5f,
        // unk_0C
        166.5f,
        // unk_10
        105.0f,
        // unk_14
        119.100006f,
        // unk_18
        88.5f,
        // unk_1C
        61.5f,
        // unk_20
        28.5f,
        // unk_24
        54.0f,
        // unk_28
        75.0f,
        // unk_2C
        84.0f,
        // unk_30
        102.0f,
        // unk_34
        70.0f,
        // wallCheckRadius
        27.0f,
        // unk_3C
        24.75f,
        // unk_40
        105.0f,
        // unk_44
        { 9, 0x123F, 0x167 },
        {
            { 8, 0x1256, 0x17C },
            { 9, 0x17EA, 0x167 },
            { 8, 0x1256, 0x17C },
            { 9, 0x17EA, 0x167 },
        },
        {
            { 9, 0x17EA, 0x167 },
            { 9, 0x1E0D, 0x17C },
            { 9, 0x17EA, 0x167 },
            { 9, 0x1E0D, 0x17C },
        },
        {
            { 8, 0x1256, 0x17C },
            { 9, 0x17EA, 0x167 },
            { -0x638, 0x1256, 0x17C },
            { -0x637, 0x17EA, 0x167 },
        },
        // voiceSfxIdOffset
        SFX_VOICE_BANK_SIZE * 0,
        // surfaceSfxIdOffset
        0x80,
        // unk_98
        33.0f,
        // unk_9C
        44.15145f,
        // openChestAnim
        &gPlayerAnim_link_demo_Tbox_open,
        // unk_A4
        &gPlayerAnim_link_demo_back_to_past,
        // unk_A8
        &gPlayerAnim_link_demo_return_to_past,
        // unk_AC
        &gPlayerAnim_link_normal_climb_startA,
        // unk_B0
        &gPlayerAnim_link_normal_climb_startB,
        // unk_B4
        {
            &gPlayerAnim_link_normal_climb_upL,
            &gPlayerAnim_link_normal_climb_upR,
            &gPlayerAnim_link_normal_Fclimb_upL,
            &gPlayerAnim_link_normal_Fclimb_upR,
        },
        // unk_C4
        {
            &gPlayerAnim_link_normal_Fclimb_sideL,
            &gPlayerAnim_link_normal_Fclimb_sideR,
        },
        // unk_CC
        {
            &gPlayerAnim_link_normal_climb_endAL,
            &gPlayerAnim_link_normal_climb_endAR,
        },
        // unk_D4
        {
            &gPlayerAnim_link_normal_climb_endBR,
            &gPlayerAnim_link_normal_climb_endBL,
        },
    },
    {
        // ceilingCheckHeight
        70.0f,
        // shadowScale
        90.0f,
        // unk_08
        0.74f,
        // unk_0C
        111.0f,
        // unk_10
        70.0f,
        // unk_14
        79.4f,
        // unk_18
        59.0f,
        // unk_1C
        41.0f,
        // unk_20
        19.0f,
        // unk_24
        36.0f,
        // unk_28
        50.0f,
        // unk_2C
        56.0f,
        // unk_30
        68.0f,
        // unk_34
        70.0f,
        // wallCheckRadius
        19.5f,
        // unk_3C
        18.2f,
        // unk_40
        80.0f,
        // unk_44
        { 0x17, 0xF3B, 0xDF },
        {
            { 0x18, 0xF3B, 0xDF },
            { 0x17, 0x14CF, 0xDF },
            { 0x18, 0xF3B, 0xDF },
            { 0x17, 0x14CF, 0xDF },
        },
        {
            { 0x17, 0x14CF, 0xDF },
            { 0x18, 0x1AF2, 0xDF },
            { 0x17, 0x14CF, 0xDF },
            { 0x18, 0x1AF2, 0xDF },
        },
        {
            { 8, 0x1256, 0x17C },
            { 9, 0x17EA, 0x167 },
            { -0x638, 0x1256, 0x17C },
            { -0x637, 0x17EA, 0x167 },
        },
        // voiceSfxIdOffset
        SFX_VOICE_BANK_SIZE * 6,
        // surfaceSfxIdOffset
        0x150,
        // unk_98
        -25.0f,
        // unk_9C
        42.0f,
        // openChestAnim
        &gPlayerAnim_pg_Tbox_open,
        // unk_A4
        &gPlayerAnim_link_demo_back_to_past,
        // unk_A8
        &gPlayerAnim_link_demo_return_to_past,
        // unk_AC
        &gPlayerAnim_pg_climb_startA,
        // unk_B0
        &gPlayerAnim_pg_climb_startB,
        // unk_B4
        {
            &gPlayerAnim_pg_climb_upL,
            &gPlayerAnim_pg_climb_upR,
            &gPlayerAnim_pg_climb_upL,
            &gPlayerAnim_pg_climb_upR,
        },
        // unk_C4
        {
            &gPlayerAnim_link_normal_Fclimb_sideL,
            &gPlayerAnim_link_normal_Fclimb_sideR,
        },
        // unk_CC
        {
            &gPlayerAnim_pg_climb_endAL,
            &gPlayerAnim_pg_climb_endAR,
        },
        // unk_D4
        {
            &gPlayerAnim_pg_climb_endBR,
            &gPlayerAnim_pg_climb_endBL,
        },
    },
    {
        // ceilingCheckHeight
        56.0f,
        // shadowScale
        90.0f,
        // unk_08
        1.0f,
        // unk_0C
        111.0f,
        // unk_10
        70.0f,
        // unk_14
        79.4f,
        // unk_18
        59.0f,
        // unk_1C
        41.0f,
        // unk_20
        19.0f,
        // unk_24
        36.0f,
        // unk_28
        50.0f,
        // unk_2C
        56.0f,
        // unk_30
        68.0f,
        // unk_34
        70.0f,
        // wallCheckRadius
        18.0f,
        // unk_3C
        23.0f,
        // unk_40
        70.0f,
        // unk_44
        { 0x17, 0x1323, -0x6D },
        {
            { 0x17, 0x1323, -0x58 },
            { 0x17, 0x18B7, -0x6D },
            { 0x17, 0x1323, -0x58 },
            { 0x17, 0x18B7, -0x6D },
        },
        {
            { 0x17, 0x18B7, -0x6D },
            { 0x18, 0x1EDA, -0x58 },
            { 0x17, 0x18B7, -0x6D },
            { 0x18, 0x1EDA, -0x58 },
        },
        {
            { 8, 0x1256, 0x17C },
            { 9, 0x17EA, 0x167 },
            { -0x638, 0x1256, 0x17C },
            { -0x637, 0x17EA, 0x167 },
        },
        // voiceSfxIdOffset
        SFX_VOICE_BANK_SIZE * 5,
        // surfaceSfxIdOffset
        0x120,
        // unk_98
        22.0f,
        // unk_9C
        36.0f,
        // openChestAnim
        &gPlayerAnim_pz_Tbox_open,
        // unk_A4
        &gPlayerAnim_link_demo_back_to_past,
        // unk_A8
        &gPlayerAnim_link_demo_return_to_past,
        // unk_AC
        &gPlayerAnim_pz_climb_startA,
        // unk_B0
        &gPlayerAnim_pz_climb_startB,
        // unk_B4
        {
            &gPlayerAnim_pz_climb_upL,
            &gPlayerAnim_pz_climb_upR,
            &gPlayerAnim_link_normal_Fclimb_upL,
            &gPlayerAnim_link_normal_Fclimb_upR,
        },
        // unk_C4
        {
            &gPlayerAnim_link_normal_Fclimb_sideL,
            &gPlayerAnim_link_normal_Fclimb_sideR,
        },
        // unk_CC
        {
            &gPlayerAnim_pz_climb_endAL,
            &gPlayerAnim_pz_climb_endAR,
        },
        // unk_D4
        {
            &gPlayerAnim_pz_climb_endBR,
            &gPlayerAnim_pz_climb_endBL,
        },
    },
    {
        // ceilingCheckHeight
        35.0f,
        // shadowScale
        50.0f,
        // unk_08
        0.3f,
        // unk_0C
        71.0f,
        // unk_10
        50.0f,
        // unk_14
        49.0f,
        // unk_18
        39.0f,
        // unk_1C
        27.0f,
        // unk_20
        19.0f,
        // unk_24
        8.0f,
        // unk_28
        13.6f,
        // unk_2C
        24.0f,
        // unk_30
        24.0f,
        // unk_34
        70.0f,
        // wallCheckRadius
        14.0f,
        // unk_3C
        12.0f,
        // unk_40
        55.0f,
        // unk_44
        { -0x18, 0xDED, 0x36C },
        {
            { -0x18, 0xD92, 0x35E },
            { -0x18, 0x1371, 0x3A9 },
            { 8, 0x1256, 0x17C },
            { 9, 0x17EA, 0x167 },
        },
        {
            { -0x18, 0x1371, 0x3A9 },
            { -0x18, 0x195F, 0x3A9 },
            { 9, 0x17EA, 0x167 },
            { 9, 0x1E0D, 0x17C },
        },
        {
            { 8, 0x1256, 0x17C },
            { 9, 0x17EA, 0x167 },
            { -0x638, 0x1256, 0x17C },
            { -0x637, 0x17EA, 0x167 },
        },
        // voiceSfxIdOffset
        SFX_VOICE_BANK_SIZE * 4,
        // surfaceSfxIdOffset
        0xF0,
        // unk_98
        -21.0f,
        // unk_9C
        33.0f,
        // openChestAnim
        &gPlayerAnim_pn_Tbox_open,
        // unk_A4
        &gPlayerAnim_link_demo_back_to_past,
        // unk_A8
        &gPlayerAnim_link_demo_return_to_past,
        // unk_AC
        &gPlayerAnim_clink_normal_climb_startA,
        // unk_B0
        &gPlayerAnim_clink_normal_climb_startB,
        // unk_B4
        {
            &gPlayerAnim_clink_normal_climb_upL,
            &gPlayerAnim_clink_normal_climb_upR,
            &gPlayerAnim_link_normal_Fclimb_upL,
            &gPlayerAnim_link_normal_Fclimb_upR,
        },
        // unk_C4
        {
            &gPlayerAnim_link_normal_Fclimb_sideL,
            &gPlayerAnim_link_normal_Fclimb_sideR,
        },
        // unk_CC
        {
            &gPlayerAnim_clink_normal_climb_endAL,
            &gPlayerAnim_clink_normal_climb_endAR,
        },
        // unk_D4
        {
            &gPlayerAnim_clink_normal_climb_endBR,
            &gPlayerAnim_clink_normal_climb_endBL,
        },
    },
    {
        // ceilingCheckHeight
        40.0f,
        // shadowScale
        60.0f,
        // unk_08
        11.0f / 17.0f,
        // unk_0C
        71.0f,
        // unk_10
        50.0f,
        // unk_14
        49.0f,
        // unk_18
        39.0f,
        // unk_1C
        27.0f,
        // unk_20
        19.0f,
        // unk_24
        22.0f,
        // unk_28
        32.4f,
        // unk_2C
        32.0f,
        // unk_30
        48.0f,
        // unk_34
        11.0f / 17.0f * 70.0f,
        // wallCheckRadius
        14.0f,
        // unk_3C
        12.0f,
        // unk_40
        55.0f,
        // unk_44
        { -0x18, 0xDED, 0x36C },
        {
            { -0x18, 0xD92, 0x35E },
            { -0x18, 0x1371, 0x3A9 },
            { 8, 0x1256, 0x17C },
            { 9, 0x17EA, 0x167 },
        },
        {
            { -0x18, 0x1371, 0x3A9 },
            { -0x18, 0x195F, 0x3A9 },
            { 9, 0x17EA, 0x167 },
            { 9, 0x1E0D, 0x17C },
        },
        {
            { 8, 0x1256, 0x17C },
            { 9, 0x17EA, 0x167 },
            { -0x638, 0x1256, 0x17C },
            { -0x637, 0x17EA, 0x167 },
        },
        // voiceSfxIdOffset
        SFX_VOICE_BANK_SIZE * 1,
        // surfaceSfxIdOffset
        0,
        // unk_98
        22.0f,
        // unk_9C
        29.4343f,
        // openChestAnim
        &gPlayerAnim_clink_demo_Tbox_open,
        // unk_A4
        &gPlayerAnim_clink_demo_goto_future,
        // unk_A8
        &gPlayerAnim_clink_demo_return_to_future,
        // unk_AC
        &gPlayerAnim_clink_normal_climb_startA,
        // unk_B0
        &gPlayerAnim_clink_normal_climb_startB,
        // unk_B4
        {
            &gPlayerAnim_clink_normal_climb_upL,
            &gPlayerAnim_clink_normal_climb_upR,
            &gPlayerAnim_link_normal_Fclimb_upL,
            &gPlayerAnim_link_normal_Fclimb_upR,
        },
        // unk_C4
        {
            &gPlayerAnim_link_normal_Fclimb_sideL,
            &gPlayerAnim_link_normal_Fclimb_sideR,
        },
        // unk_CC
        {
            &gPlayerAnim_clink_normal_climb_endAL,
            &gPlayerAnim_clink_normal_climb_endAR,
        },
        // unk_D4
        {
            &gPlayerAnim_clink_normal_climb_endBR,
            &gPlayerAnim_clink_normal_climb_endBL,
        },
    },
};

PlayerAnimationHeader* D_8085BE84[PLAYER_ANIMGROUP_MAX][PLAYER_ANIMTYPE_MAX] = {
    // PLAYER_ANIMGROUP_0
    {
        &gPlayerAnim_link_normal_wait_free,  // Default idle standing, looking forward
        &gPlayerAnim_link_normal_wait,       // Default idle standing, looking forward, sword and shield
        &gPlayerAnim_link_normal_wait,       // Default idle standing, looking forward, sword and shield
        &gPlayerAnim_link_fighter_wait_long, // Default idle standing, looking forward, two hand weapon
        &gPlayerAnim_link_normal_wait_free,  // Default idle standing, looking forward
        &gPlayerAnim_link_normal_wait_free,  // Default idle standing, looking forward
    },
    // PLAYER_ANIMGROUP_1
    {
        &gPlayerAnim_link_normal_walk_free,
        &gPlayerAnim_link_normal_walk,
        &gPlayerAnim_link_normal_walk,
        &gPlayerAnim_link_fighter_walk_long,
        &gPlayerAnim_link_normal_walk_free,
        &gPlayerAnim_link_normal_walk_free,
    },
    // PLAYER_ANIMGROUP_2
    {
        &gPlayerAnim_link_normal_run_free, // Running with empty hands
        &gPlayerAnim_link_fighter_run,     // Running with Sword and Shield in hands
        &gPlayerAnim_link_normal_run,
        &gPlayerAnim_link_fighter_run_long, // Running with Two handed weapon
        &gPlayerAnim_link_normal_run_free,  // Running with empty hands
        &gPlayerAnim_link_normal_run_free,  // Running with empty hands
    },
    // PLAYER_ANIMGROUP_3
    {
        &gPlayerAnim_link_normal_damage_run_free,
        &gPlayerAnim_link_fighter_damage_run,
        &gPlayerAnim_link_normal_damage_run_free,
        &gPlayerAnim_link_fighter_damage_run_long,
        &gPlayerAnim_link_normal_damage_run_free,
        &gPlayerAnim_link_normal_damage_run_free,
    },
    // PLAYER_ANIMGROUP_4
    {
        &gPlayerAnim_link_normal_waitL_free,
        &gPlayerAnim_link_anchor_waitL,
        &gPlayerAnim_link_anchor_waitL,
        &gPlayerAnim_link_fighter_waitL_long,
        &gPlayerAnim_link_normal_waitL_free,
        &gPlayerAnim_link_normal_waitL_free,
    },
    // PLAYER_ANIMGROUP_5
    {
        &gPlayerAnim_link_normal_waitR_free,
        &gPlayerAnim_link_anchor_waitR,
        &gPlayerAnim_link_anchor_waitR,
        &gPlayerAnim_link_fighter_waitR_long,
        &gPlayerAnim_link_normal_waitR_free,
        &gPlayerAnim_link_normal_waitR_free,
    },
    // PLAYER_ANIMGROUP_6
    {
        &gPlayerAnim_link_fighter_wait2waitR_long,
        &gPlayerAnim_link_normal_wait2waitR,
        &gPlayerAnim_link_normal_wait2waitR,
        &gPlayerAnim_link_fighter_wait2waitR_long,
        &gPlayerAnim_link_fighter_wait2waitR_long,
        &gPlayerAnim_link_fighter_wait2waitR_long,
    },
    // PLAYER_ANIMGROUP_7
    {
        &gPlayerAnim_link_normal_normal2fighter_free,
        &gPlayerAnim_link_fighter_normal2fighter,
        &gPlayerAnim_link_fighter_normal2fighter,
        &gPlayerAnim_link_normal_normal2fighter_free,
        &gPlayerAnim_link_normal_normal2fighter_free,
        &gPlayerAnim_link_normal_normal2fighter_free,
    },
    // PLAYER_ANIMGROUP_8
    {
        &gPlayerAnim_link_demo_doorA_link_free,
        &gPlayerAnim_link_demo_doorA_link,
        &gPlayerAnim_link_demo_doorA_link,
        &gPlayerAnim_link_demo_doorA_link_free,
        &gPlayerAnim_link_demo_doorA_link_free,
        &gPlayerAnim_link_demo_doorA_link_free,
    },
    // PLAYER_ANIMGROUP_9
    {
        &gPlayerAnim_clink_demo_doorA_link,
        &gPlayerAnim_clink_demo_doorA_link,
        &gPlayerAnim_clink_demo_doorA_link,
        &gPlayerAnim_clink_demo_doorA_link,
        &gPlayerAnim_clink_demo_doorA_link,
        &gPlayerAnim_clink_demo_doorA_link,
    },
    // PLAYER_ANIMGROUP_10
    {
        &gPlayerAnim_link_demo_doorB_link_free,
        &gPlayerAnim_link_demo_doorB_link,
        &gPlayerAnim_link_demo_doorB_link,
        &gPlayerAnim_link_demo_doorB_link_free,
        &gPlayerAnim_link_demo_doorB_link_free,
        &gPlayerAnim_link_demo_doorB_link_free,
    },
    // PLAYER_ANIMGROUP_11
    {
        &gPlayerAnim_clink_demo_doorB_link,
        &gPlayerAnim_clink_demo_doorB_link,
        &gPlayerAnim_clink_demo_doorB_link,
        &gPlayerAnim_clink_demo_doorB_link,
        &gPlayerAnim_clink_demo_doorB_link,
        &gPlayerAnim_clink_demo_doorB_link,
    },
    // PLAYER_ANIMGROUP_12
    {
        &gPlayerAnim_link_normal_carryB_free, // Grabbing something from the floor
        &gPlayerAnim_link_normal_carryB,      //
        &gPlayerAnim_link_normal_carryB,      //
        &gPlayerAnim_link_normal_carryB_free, // Grabbing something from the floor
        &gPlayerAnim_link_normal_carryB_free, // Grabbing something from the floor
        &gPlayerAnim_link_normal_carryB_free, // Grabbing something from the floor
    },
    // PLAYER_ANIMGROUP_13
    {
        &gPlayerAnim_link_normal_landing_free,
        &gPlayerAnim_link_normal_landing,
        &gPlayerAnim_link_normal_landing,
        &gPlayerAnim_link_normal_landing_free,
        &gPlayerAnim_link_normal_landing_free,
        &gPlayerAnim_link_normal_landing_free,
    },
    // PLAYER_ANIMGROUP_14
    {
        &gPlayerAnim_link_normal_short_landing_free,
        &gPlayerAnim_link_normal_short_landing,
        &gPlayerAnim_link_normal_short_landing,
        &gPlayerAnim_link_normal_short_landing_free,
        &gPlayerAnim_link_normal_short_landing_free,
        &gPlayerAnim_link_normal_short_landing_free,
    },
    // PLAYER_ANIMGROUP_15
    {
        &gPlayerAnim_link_normal_landing_roll_free,  // Rolling with nothing in hands
        &gPlayerAnim_link_normal_landing_roll,       // Rolling with sword and shield
        &gPlayerAnim_link_normal_landing_roll,       // Rolling with sword and shield
        &gPlayerAnim_link_fighter_landing_roll_long, // Rolling with two hand weapon
        &gPlayerAnim_link_normal_landing_roll_free,  // Rolling with nothing in hands
        &gPlayerAnim_link_normal_landing_roll_free,  // Rolling with nothing in hands
    },
    // PLAYER_ANIMGROUP_16
    {
        &gPlayerAnim_link_normal_hip_down_free, // Rolling bonk
        &gPlayerAnim_link_normal_hip_down,      // Rolling bonk swrod and shield
        &gPlayerAnim_link_normal_hip_down,      // Rolling bonk swrod and shield
        &gPlayerAnim_link_normal_hip_down_long, // Rolling bonk two hand weapon
        &gPlayerAnim_link_normal_hip_down_free, // Rolling bonk
        &gPlayerAnim_link_normal_hip_down_free, // Rolling bonk
    },
    // PLAYER_ANIMGROUP_17
    {
        &gPlayerAnim_link_normal_walk_endL_free,
        &gPlayerAnim_link_normal_walk_endL,
        &gPlayerAnim_link_normal_walk_endL,
        &gPlayerAnim_link_fighter_walk_endL_long,
        &gPlayerAnim_link_normal_walk_endL_free,
        &gPlayerAnim_link_normal_walk_endL_free,
    },
    // PLAYER_ANIMGROUP_18
    {
        &gPlayerAnim_link_normal_walk_endR_free,
        &gPlayerAnim_link_normal_walk_endR,
        &gPlayerAnim_link_normal_walk_endR,
        &gPlayerAnim_link_fighter_walk_endR_long,
        &gPlayerAnim_link_normal_walk_endR_free,
        &gPlayerAnim_link_normal_walk_endR_free,
    },
    // PLAYER_ANIMGROUP_19
    {
        &gPlayerAnim_link_normal_defense_free,
        &gPlayerAnim_link_normal_defense,
        &gPlayerAnim_link_normal_defense,
        &gPlayerAnim_link_normal_defense_free,
        &gPlayerAnim_link_bow_defense,
        &gPlayerAnim_link_normal_defense_free,
    },
    // PLAYER_ANIMGROUP_20
    {
        &gPlayerAnim_link_normal_defense_wait_free,
        &gPlayerAnim_link_normal_defense_wait,
        &gPlayerAnim_link_normal_defense_wait,
        &gPlayerAnim_link_normal_defense_wait_free,
        &gPlayerAnim_link_bow_defense_wait,
        &gPlayerAnim_link_normal_defense_wait_free,
    },
    // PLAYER_ANIMGROUP_21
    {
        &gPlayerAnim_link_normal_defense_end_free,
        &gPlayerAnim_link_normal_defense_end,
        &gPlayerAnim_link_normal_defense_end,
        &gPlayerAnim_link_normal_defense_end_free,
        &gPlayerAnim_link_normal_defense_end_free,
        &gPlayerAnim_link_normal_defense_end_free,
    },
    // PLAYER_ANIMGROUP_22
    {
        &gPlayerAnim_link_normal_side_walk_free,
        &gPlayerAnim_link_normal_side_walk,
        &gPlayerAnim_link_normal_side_walk,
        &gPlayerAnim_link_fighter_side_walk_long,
        &gPlayerAnim_link_normal_side_walk_free,
        &gPlayerAnim_link_normal_side_walk_free,
    },
    // PLAYER_ANIMGROUP_23
    {
        &gPlayerAnim_link_normal_side_walkL_free, // Side walking
        &gPlayerAnim_link_anchor_side_walkL,      // Side walking with sword and shield in hands
        &gPlayerAnim_link_anchor_side_walkL,      // Side walking with sword and shield in hands
        &gPlayerAnim_link_fighter_side_walkL_long,
        &gPlayerAnim_link_normal_side_walkL_free, // Side walking
        &gPlayerAnim_link_normal_side_walkL_free, // Side walking
    },
    // PLAYER_ANIMGROUP_24
    {
        &gPlayerAnim_link_normal_side_walkR_free,
        &gPlayerAnim_link_anchor_side_walkR,
        &gPlayerAnim_link_anchor_side_walkR,
        &gPlayerAnim_link_fighter_side_walkR_long,
        &gPlayerAnim_link_normal_side_walkR_free,
        &gPlayerAnim_link_normal_side_walkR_free,
    },
    // PLAYER_ANIMGROUP_25
    {
        &gPlayerAnim_link_normal_45_turn_free,
        &gPlayerAnim_link_normal_45_turn,
        &gPlayerAnim_link_normal_45_turn,
        &gPlayerAnim_link_normal_45_turn_free,
        &gPlayerAnim_link_normal_45_turn_free,
        &gPlayerAnim_link_normal_45_turn_free,
    },
    // PLAYER_ANIMGROUP_26
    {
        &gPlayerAnim_link_normal_waitL2wait,
        &gPlayerAnim_link_normal_waitL2wait,
        &gPlayerAnim_link_normal_waitL2wait,
        &gPlayerAnim_link_fighter_waitL2wait_long,
        &gPlayerAnim_link_fighter_waitL2wait_long,
        &gPlayerAnim_link_fighter_waitL2wait_long,
    },
    // PLAYER_ANIMGROUP_27
    {
        &gPlayerAnim_link_normal_waitR2wait,
        &gPlayerAnim_link_normal_waitR2wait,
        &gPlayerAnim_link_normal_waitR2wait,
        &gPlayerAnim_link_fighter_waitR2wait_long,
        &gPlayerAnim_link_fighter_waitR2wait_long,
        &gPlayerAnim_link_fighter_waitR2wait_long,
    },
    // PLAYER_ANIMGROUP_28
    {
        &gPlayerAnim_link_normal_throw_free,
        &gPlayerAnim_link_normal_throw,
        &gPlayerAnim_link_normal_throw,
        &gPlayerAnim_link_normal_throw_free,
        &gPlayerAnim_link_normal_throw_free,
        &gPlayerAnim_link_normal_throw_free,
    },
    // PLAYER_ANIMGROUP_29
    {
        &gPlayerAnim_link_normal_put_free,
        &gPlayerAnim_link_normal_put,
        &gPlayerAnim_link_normal_put,
        &gPlayerAnim_link_normal_put_free,
        &gPlayerAnim_link_normal_put_free,
        &gPlayerAnim_link_normal_put_free,
    },
    // PLAYER_ANIMGROUP_30
    {
        &gPlayerAnim_link_normal_back_walk,
        &gPlayerAnim_link_normal_back_walk,
        &gPlayerAnim_link_normal_back_walk,
        &gPlayerAnim_link_normal_back_walk,
        &gPlayerAnim_link_normal_back_walk,
        &gPlayerAnim_link_normal_back_walk,
    },
    // PLAYER_ANIMGROUP_31
    {
        &gPlayerAnim_link_normal_check_free,
        &gPlayerAnim_link_normal_check,
        &gPlayerAnim_link_normal_check,
        &gPlayerAnim_link_normal_check_free,
        &gPlayerAnim_link_normal_check_free,
        &gPlayerAnim_link_normal_check_free,
    },
    // PLAYER_ANIMGROUP_32
    {
        &gPlayerAnim_link_normal_check_wait_free,
        &gPlayerAnim_link_normal_check_wait,
        &gPlayerAnim_link_normal_check_wait,
        &gPlayerAnim_link_normal_check_wait_free,
        &gPlayerAnim_link_normal_check_wait_free,
        &gPlayerAnim_link_normal_check_wait_free,
    },
    // PLAYER_ANIMGROUP_33
    {
        &gPlayerAnim_link_normal_check_end_free,
        &gPlayerAnim_link_normal_check_end,
        &gPlayerAnim_link_normal_check_end,
        &gPlayerAnim_link_normal_check_end_free,
        &gPlayerAnim_link_normal_check_end_free,
        &gPlayerAnim_link_normal_check_end_free,
    },
    // PLAYER_ANIMGROUP_34
    {
        &gPlayerAnim_link_normal_pull_start_free,
        &gPlayerAnim_link_normal_pull_start,
        &gPlayerAnim_link_normal_pull_start,
        &gPlayerAnim_link_normal_pull_start_free,
        &gPlayerAnim_link_normal_pull_start_free,
        &gPlayerAnim_link_normal_pull_start_free,
    },
    // PLAYER_ANIMGROUP_35
    {
        &gPlayerAnim_link_normal_pulling_free,
        &gPlayerAnim_link_normal_pulling,
        &gPlayerAnim_link_normal_pulling,
        &gPlayerAnim_link_normal_pulling_free,
        &gPlayerAnim_link_normal_pulling_free,
        &gPlayerAnim_link_normal_pulling_free,
    },
    // PLAYER_ANIMGROUP_36
    {
        &gPlayerAnim_link_normal_pull_end_free,
        &gPlayerAnim_link_normal_pull_end,
        &gPlayerAnim_link_normal_pull_end,
        &gPlayerAnim_link_normal_pull_end_free,
        &gPlayerAnim_link_normal_pull_end_free,
        &gPlayerAnim_link_normal_pull_end_free,
    },
    // PLAYER_ANIMGROUP_37
    {
        &gPlayerAnim_link_normal_fall_up_free,
        &gPlayerAnim_link_normal_fall_up,
        &gPlayerAnim_link_normal_fall_up,
        &gPlayerAnim_link_normal_fall_up_free,
        &gPlayerAnim_link_normal_fall_up_free,
        &gPlayerAnim_link_normal_fall_up_free,
    },
    // PLAYER_ANIMGROUP_38
    {
        &gPlayerAnim_link_normal_jump_climb_hold_free,
        &gPlayerAnim_link_normal_jump_climb_hold,
        &gPlayerAnim_link_normal_jump_climb_hold,
        &gPlayerAnim_link_normal_jump_climb_hold_free,
        &gPlayerAnim_link_normal_jump_climb_hold_free,
        &gPlayerAnim_link_normal_jump_climb_hold_free,
    },
    // PLAYER_ANIMGROUP_39
    {
        &gPlayerAnim_link_normal_jump_climb_wait_free,
        &gPlayerAnim_link_normal_jump_climb_wait,
        &gPlayerAnim_link_normal_jump_climb_wait,
        &gPlayerAnim_link_normal_jump_climb_wait_free,
        &gPlayerAnim_link_normal_jump_climb_wait_free,
        &gPlayerAnim_link_normal_jump_climb_wait_free,
    },
    // PLAYER_ANIMGROUP_40
    {
        &gPlayerAnim_link_normal_jump_climb_up_free,
        &gPlayerAnim_link_normal_jump_climb_up,
        &gPlayerAnim_link_normal_jump_climb_up,
        &gPlayerAnim_link_normal_jump_climb_up_free,
        &gPlayerAnim_link_normal_jump_climb_up_free,
        &gPlayerAnim_link_normal_jump_climb_up_free,
    },
    // PLAYER_ANIMGROUP_41
    {
        &gPlayerAnim_link_normal_down_slope_slip_end_free,
        &gPlayerAnim_link_normal_down_slope_slip_end,
        &gPlayerAnim_link_normal_down_slope_slip_end,
        &gPlayerAnim_link_normal_down_slope_slip_end_long,
        &gPlayerAnim_link_normal_down_slope_slip_end_free,
        &gPlayerAnim_link_normal_down_slope_slip_end_free,
    },
    // PLAYER_ANIMGROUP_42
    {
        &gPlayerAnim_link_normal_up_slope_slip_end_free,
        &gPlayerAnim_link_normal_up_slope_slip_end,
        &gPlayerAnim_link_normal_up_slope_slip_end,
        &gPlayerAnim_link_normal_up_slope_slip_end_long,
        &gPlayerAnim_link_normal_up_slope_slip_end_free,
        &gPlayerAnim_link_normal_up_slope_slip_end_free,
    },
    // PLAYER_ANIMGROUP_43
    {
        &gPlayerAnim_sude_nwait,
        &gPlayerAnim_lkt_nwait,
        &gPlayerAnim_lkt_nwait,
        &gPlayerAnim_sude_nwait,
        &gPlayerAnim_sude_nwait,
        &gPlayerAnim_sude_nwait,
    }
};

struct_8085C2A4 D_8085C2A4[] = {
    /* 0 / Forward */
    {
        &gPlayerAnim_link_fighter_front_jump,
        &gPlayerAnim_link_fighter_front_jump_end,
        &gPlayerAnim_link_fighter_front_jump_endR,
    },
    /* 1 / Left */
    {
        &gPlayerAnim_link_fighter_Lside_jump,
        &gPlayerAnim_link_fighter_Lside_jump_end,
        &gPlayerAnim_link_fighter_Lside_jump_endL,
    },
    /* 2 / Back */
    {
        &gPlayerAnim_link_fighter_backturn_jump,
        &gPlayerAnim_link_fighter_backturn_jump_end,
        &gPlayerAnim_link_fighter_backturn_jump_endR,
    },
    /* 3 / Right */
    {
        &gPlayerAnim_link_fighter_Rside_jump,
        &gPlayerAnim_link_fighter_Rside_jump_end,
        &gPlayerAnim_link_fighter_Rside_jump_endR,
    },
    /* 4 /  */
    {
        &gPlayerAnim_link_normal_newroll_jump_20f,
        &gPlayerAnim_link_normal_newroll_jump_end_20f,
        &gPlayerAnim_link_normal_newroll_jump_end_20f,
    },
    /* 5 /  */
    {
        &gPlayerAnim_link_normal_newside_jump_20f,
        &gPlayerAnim_link_normal_newside_jump_end_20f,
        &gPlayerAnim_link_normal_newside_jump_end_20f,
    },
};

// sCylinderInit
ColliderCylinderInit D_8085C2EC = {
    {
        COLTYPE_HIT5,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_PLAYER,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 12, 60, 0, { 0, 0, 0 } },
};

// sShieldCylinderInit
ColliderCylinderInit D_8085C318 = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_PLAYER,
        AC_ON | AC_HARD | AC_TYPE_ENEMY,
        OC1_NONE,
        OC2_TYPE_PLAYER,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00100000, 0x00, 0x02 },
        { 0xD7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 25, 60, 0, { 0, 0, 0 } },
};

// sMeleeWeaponQuadInit
ColliderQuadInit D_8085C344 = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER,
        AC_NONE,
        OC1_NONE,
        OC2_TYPE_PLAYER,
        COLSHAPE_QUAD,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00000000, 0x00, 0x01 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_NONE,
    },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

// sShieldQuadInit
ColliderQuadInit D_8085C394 = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_PLAYER,
        AC_ON | AC_HARD | AC_TYPE_ENEMY,
        OC1_NONE,
        OC2_TYPE_PLAYER,
        COLSHAPE_QUAD,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00100000, 0x00, 0x00 },
        { 0xD7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

f32 D_8085C3E4 = 1.0f;
f32 D_8085C3E8 = 1.0f;

// ANIMSFX_TYPE_VOICE
void Player_AnimSfx_PlayVoice(Player* this, u16 sfxId) {
    u16 sfxOffset;

    if (this->currentMask == PLAYER_MASK_GIANT) {
        Audio_PlaySfx_GiantsMask(&this->actor.projectedPos, sfxId);
    } else if (this->actor.id == ACTOR_PLAYER) {
        if (this->currentMask == PLAYER_MASK_SCENTS) {
            sfxOffset = SFX_VOICE_BANK_SIZE * 7;
        } else {
            sfxOffset = this->ageProperties->voiceSfxIdOffset;
        }

        Player_PlaySfx(this, sfxOffset + sfxId);
    }
}

u16 D_8085C3EC[] = {
    NA_SE_VO_LI_SWEAT,
    NA_SE_VO_LI_SNEEZE,
    NA_SE_VO_LI_RELAX,
    NA_SE_VO_LI_FALL_L,
};

void func_8082E00C(Player* this) {
    s32 i;
    u16* sfxIdPtr = D_8085C3EC;

    for (i = 0; i < ARRAY_COUNT(D_8085C3EC); i++) {
        AudioSfx_StopById((u16)(*sfxIdPtr + this->ageProperties->voiceSfxIdOffset));
        sfxIdPtr++;
    }
}

u16 Player_GetFloorSfx(Player* this, u16 sfxId) {
    return sfxId + this->floorSfxOffset;
}

// ANIMSFX_TYPE_FLOOR
void Player_AnimSfx_PlayFloor(Player* this, u16 sfxId) {
    Player_PlaySfx(this, Player_GetFloorSfx(this, sfxId));
}

u16 Player_GetFloorSfxByAge(Player* this, u16 sfxId) {
    return sfxId + this->floorSfxOffset + this->ageProperties->surfaceSfxIdOffset;
}

// ANIMSFX_TYPE_FLOOR_BY_AGE
void Player_AnimSfx_PlayFloorByAge(Player* this, u16 sfxId) {
    Player_PlaySfx(this, Player_GetFloorSfxByAge(this, sfxId));
}

// ANIMSFX_TYPE_6 and ANIMSFX_TYPE_8
void Player_AnimSfx_PlayFloorWalk(Player* this, f32 freqVolumeLerp) {
    s32 sfxId;

    if (this->currentMask == PLAYER_MASK_GIANT) {
        sfxId = NA_SE_PL_GIANT_WALK;
    } else {
        sfxId = Player_GetFloorSfxByAge(this, NA_SE_PL_WALK_GROUND);
    }

    // Audio_PlaySfx_AtPosForMetalEffectsWithSyncedFreqAndVolume
    Audio_PlaySfx_AtPosForMetalEffectsWithSyncedFreqAndVolume(&this->actor.projectedPos, sfxId, freqVolumeLerp);
}

// ANIMSFX_TYPE_FLOOR_JUMP
void Player_AnimSfx_PlayFloorJump(Player* this) {
    Player_PlaySfx(this, Player_GetFloorSfxByAge(this, NA_SE_PL_JUMP_GROUND));
}

// ANIMSFX_TYPE_FLOOR_LAND
void Player_AnimSfx_PlayFloorLand(Player* this) {
    Player_PlaySfx(this, Player_GetFloorSfxByAge(this, NA_SE_PL_LAND_GROUND));
}

void func_8082E1F0(Player* this, u16 sfxId) {
    Player_PlaySfx(this, sfxId);
    this->stateFlags2 |= PLAYER_STATE2_8;
}

void Player_PlayAnimSfx(Player* this, AnimSfxEntry* entry) {
    s32 cond;

    do {
        s32 data = ABS_ALT(entry->flags);
        s32 type = ANIMSFX_GET_TYPE(data);

        if (PlayerAnimation_OnFrame(&this->skelAnime, fabsf(ANIMSFX_GET_FRAME(data)))) {
            if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_GENERAL)) {
                Player_PlaySfx(this, entry->sfxId);
            } else if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_FLOOR)) {
                Player_AnimSfx_PlayFloor(this, entry->sfxId);
            } else if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_FLOOR_BY_AGE)) {
                Player_AnimSfx_PlayFloorByAge(this, entry->sfxId);
            } else if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_VOICE)) {
                Player_AnimSfx_PlayVoice(this, entry->sfxId);
            } else if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_FLOOR_LAND)) {
                Player_AnimSfx_PlayFloorLand(this);
            } else if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_6)) {
                Player_AnimSfx_PlayFloorWalk(this, 6.0f);
            } else if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_FLOOR_JUMP)) {
                Player_AnimSfx_PlayFloorJump(this);
            } else if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_8)) {
                Player_AnimSfx_PlayFloorWalk(this, 0.0f);
            } else if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_9)) {
                // Audio_PlaySfx_AtPosForMetalEffectsWithSyncedFreqAndVolume
                Audio_PlaySfx_AtPosForMetalEffectsWithSyncedFreqAndVolume(
                    &this->actor.projectedPos, this->ageProperties->surfaceSfxIdOffset + NA_SE_PL_WALK_LADDER, 0.0f);
            } else if (type == ANIMSFX_SHIFT_TYPE(ANIMSFX_TYPE_SURFACE)) {
                Player_PlaySfx(this, entry->sfxId + this->ageProperties->surfaceSfxIdOffset);
            }
        }

        cond = entry->flags >= 0;
        entry++;
    } while (cond);
}

void func_8082E438(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    PlayerAnimation_Change(play, &this->skelAnime, anim, 3.0f / 3.0f, 0.0f, Animation_GetLastFrame(anim), ANIMMODE_ONCE,
                           -6.0f);
}

void func_8082E4A4(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    PlayerAnimation_Change(play, &this->skelAnime, anim, 2.0f / 3.0f, 0.0f, Animation_GetLastFrame(anim), ANIMMODE_ONCE,
                           -6.0f);
}

void func_8082E514(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    PlayerAnimation_Change(play, &this->skelAnime, anim, 3.0f / 3.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -6.0f);
}

void func_8082E55C(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    PlayerAnimation_Change(play, &this->skelAnime, anim, 2.0f / 3.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -6.0f);
}

void func_8082E5A8(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    PlayerAnimation_Change(play, &this->skelAnime, anim, 3.0f / 3.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f);
}

void func_8082E5EC(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    PlayerAnimation_Change(play, &this->skelAnime, anim, 2.0f / 3.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f);
}

void func_8082E634(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    PlayerAnimation_Change(play, &this->skelAnime, anim, 3.0f / 3.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -16.0f);
}

// Player_AnimationPlayLoopIfCurrentFinished
s32 func_8082E67C(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        Player_AnimationPlayLoop(play, this, anim);
        return true;
    } else {
        return false;
    }
}

void func_8082E6D0(Player* this) {
    this->skelAnime.prevTransl = this->skelAnime.baseTransl;
    this->skelAnime.prevRot = this->actor.shape.rot.y;
}

void func_8082E6F8(Player* this) {
    func_8082E6D0(this);
    this->skelAnime.prevTransl.x *= this->ageProperties->unk_08;
    this->skelAnime.prevTransl.y *= this->ageProperties->unk_08;
    this->skelAnime.prevTransl.z *= this->ageProperties->unk_08;
}

void func_8082E784(Player* this) {
    this->skelAnime.jointTable[PLAYER_LIMB_WAIST - 1].y = 0;
}

void func_8082E794(Player* this) {
    if (this->skelAnime.moveFlags) {
        func_8082DC28(this);
        this->skelAnime.jointTable[PLAYER_LIMB_ROOT - 1].x = this->skelAnime.baseTransl.x;
        this->skelAnime.jointTable[PLAYER_LIMB_ROOT - 1].z = this->skelAnime.baseTransl.z;

        if (this->skelAnime.moveFlags & ANIM_FLAG_8) {
            if (this->skelAnime.moveFlags & ANIM_FLAG_UPDATE_Y) {
                this->skelAnime.jointTable[PLAYER_LIMB_ROOT - 1].y = this->skelAnime.prevTransl.y;
            }
        } else {
            this->skelAnime.jointTable[PLAYER_LIMB_ROOT - 1].y = this->skelAnime.baseTransl.y;
        }
        func_8082E6D0(this);
        this->skelAnime.moveFlags = 0;
    }
}

void func_8082E820(Player* this, s32 moveFlags) {
    Vec3f pos;

    this->skelAnime.moveFlags = moveFlags;
    this->skelAnime.prevTransl = this->skelAnime.baseTransl;
    SkelAnime_UpdateTranslation(&this->skelAnime, &pos, this->actor.shape.rot.y);

    if (moveFlags & ANIM_FLAG_1) {
        pos.x *= this->ageProperties->unk_08;
        pos.z *= this->ageProperties->unk_08;
        this->actor.world.pos.x += pos.x * this->actor.scale.x;
        this->actor.world.pos.z += pos.z * this->actor.scale.z;
    }

    if (moveFlags & ANIM_FLAG_UPDATE_Y) {
        if (!(moveFlags & ANIM_FLAG_4)) {
            pos.y *= this->ageProperties->unk_08;
        }
        this->actor.world.pos.y += pos.y * this->actor.scale.y;
    }

    func_8082DC28(this);
}

void func_8082E920(PlayState* play, Player* this, s32 moveFlags) {
    if (moveFlags & ANIM_FLAG_200) {
        func_8082E6F8(this);
    } else if ((moveFlags & ANIM_FLAG_100) || this->skelAnime.moveFlags) {
        func_8082E6D0(this);
    } else {
        this->skelAnime.prevTransl = this->skelAnime.jointTable[PLAYER_LIMB_ROOT - 1];
        this->skelAnime.prevRot = this->actor.shape.rot.y;
    }

    this->skelAnime.moveFlags = moveFlags;
    Player_StopHorizontalMovement(this);
    AnimationContext_DisableQueue(play);
}

void func_8082E9C8(PlayState* play, Player* this, PlayerAnimationHeader* anim, s32 moveFlags, f32 playSpeed) {
    PlayerAnimation_PlayOnceSetSpeed(play, &this->skelAnime, anim, playSpeed);
    func_8082E920(play, this, moveFlags);
}

void func_8082EA10(PlayState* play, Player* this, PlayerAnimationHeader* anim, s32 moveFlags) {
    func_8082E9C8(play, this, anim, moveFlags, 3.0f / 3.0f);
}

void func_8082EA38(PlayState* play, Player* this, PlayerAnimationHeader* anim, s32 moveFlags) {
    func_8082E9C8(play, this, anim, moveFlags, 2.0f / 3.0f);
}

void func_8082EA60(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    func_8082EA38(play, this, anim, ANIM_FLAG_4 | ANIM_FLAG_8 | ANIM_FLAG_200);
}

void func_8082EA80(PlayState* play, Player* this, PlayerAnimationHeader* anim, s32 moveFlags, f32 playSpeed) {
    PlayerAnimation_PlayLoopSetSpeed(play, &this->skelAnime, anim, playSpeed);
    func_8082E920(play, this, moveFlags);
}

void func_8082EAC8(PlayState* play, Player* this, PlayerAnimationHeader* anim, s32 moveFlags) {
    func_8082EA80(play, this, anim, moveFlags, 3.0f / 3.0f);
}

void func_8082EAF0(PlayState* play, Player* this, PlayerAnimationHeader* anim, s32 moveFlags) {
    func_8082EA80(play, this, anim, moveFlags, 2.0f / 3.0f);
}

void func_8082EB18(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    func_8082EAF0(play, this, anim, ANIM_FLAG_4 | ANIM_FLAG_8 | ANIM_FLAG_NOMOVE);
}

void Player_ProcessControlStick(PlayState* play, Player* this) {
    s8 var_v0;
    s8 var_v1;

    this->prevControlStickMagnitude = sPlayerControlStickMagnitude;
    this->prevControlStickAngle = sPlayerControlStickAngle;

    Lib_GetControlStickData(&sPlayerControlStickMagnitude, &sPlayerControlStickAngle, sPlayerControlInput);

    if (sPlayerControlStickMagnitude < 8.0f) {
        sPlayerControlStickMagnitude = 0.0f;
    }

    D_80862B02 = Camera_GetInputDirYaw(GET_ACTIVE_CAM(play)) + sPlayerControlStickAngle;

    this->unk_ADE = (this->unk_ADE + 1) % ARRAY_COUNT(this->unk_ADF);

    if (sPlayerControlStickMagnitude < 55.0f) {
        var_v0 = -1;
        var_v1 = -1;
    } else {
        var_v1 = ((u16)(sPlayerControlStickAngle + 0x2000)) >> 9;
        var_v0 = ((u16)(BINANG_SUB(D_80862B02, this->actor.shape.rot.y) + 0x2000)) >> 14;
    }

    this->unk_ADF[this->unk_ADE] = var_v1;
    this->unk_AE3[this->unk_ADE] = var_v0;
}

void func_8082EC9C(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    PlayerAnimation_PlayOnceSetSpeed(play, &this->skelAnime, anim, D_8085C3E4);
}

s32 func_8082ECCC(Player* this) {
    return this->stateFlags1 & PLAYER_STATE1_1000000;
}

#define CHEST_ANIM_SHORT 0
#define CHEST_ANIM_LONG 1

// TODO: consider what to do with the NONEs: cannot use a zero-argument macro like OoT since the text id is involved.
#define GET_ITEM(itemId, objectId, drawId, textId, field, chestAnim) \
    { itemId, field, (chestAnim != CHEST_ANIM_SHORT ? 1 : -1) * (drawId + 1), textId, objectId }

#define GIFIELD_GET_DROP_TYPE(field) ((field)&0x1F)
#define GIFIELD_20 (1 << 5)
#define GIFIELD_40 (1 << 6)
#define GIFIELD_NO_COLLECTIBLE (1 << 7)
/**
 * `flags` must be 0, GIFIELD_20, GIFIELD_40 or GIFIELD_NO_COLLECTIBLE (which can be or'ed together)
 * `dropType` must be either a value from the `Item00Type` enum or 0 if the `GIFIELD_NO_COLLECTIBLE` flag was used
 */
#define GIFIELD(flags, dropType) ((flags) | (dropType))

GetItemEntry sGetItemTable[GI_MAX - 1] = {
    // GI_RUPEE_GREEN
    GET_ITEM(ITEM_RUPEE_GREEN, OBJECT_GI_RUPY, GID_RUPEE_GREEN, 0xC4, GIFIELD(0, ITEM00_RUPEE_GREEN), CHEST_ANIM_SHORT),
    // GI_RUPEE_BLUE
    GET_ITEM(ITEM_RUPEE_BLUE, OBJECT_GI_RUPY, GID_RUPEE_BLUE, 0x2, GIFIELD(0, ITEM00_RUPEE_BLUE), CHEST_ANIM_SHORT),
    // GI_RUPEE_10
    GET_ITEM(ITEM_RUPEE_10, OBJECT_GI_RUPY, GID_RUPEE_RED, 0x3, GIFIELD(0, ITEM00_RUPEE_RED), CHEST_ANIM_SHORT),
    // GI_RUPEE_RED
    GET_ITEM(ITEM_RUPEE_RED, OBJECT_GI_RUPY, GID_RUPEE_RED, 0x4, GIFIELD(0, ITEM00_RUPEE_RED), CHEST_ANIM_SHORT),
    // GI_RUPEE_PURPLE
    GET_ITEM(ITEM_RUPEE_PURPLE, OBJECT_GI_RUPY, GID_RUPEE_PURPLE, 0x5, GIFIELD(0, ITEM00_RUPEE_PURPLE),
             CHEST_ANIM_SHORT),
    // GI_RUPEE_SILVER
    GET_ITEM(ITEM_RUPEE_SILVER, OBJECT_GI_RUPY, GID_RUPEE_SILVER, 0x6, GIFIELD(0, ITEM00_RUPEE_PURPLE),
             CHEST_ANIM_SHORT),
    // GI_RUPEE_HUGE
    GET_ITEM(ITEM_RUPEE_HUGE, OBJECT_GI_RUPY, GID_RUPEE_HUGE, 0x7, GIFIELD(0, ITEM00_RUPEE_HUGE), CHEST_ANIM_SHORT),
    // GI_WALLET_ADULT
    GET_ITEM(ITEM_WALLET_ADULT, OBJECT_GI_PURSE, GID_WALLET_ADULT, 0x8, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_WALLET_GIANT
    GET_ITEM(ITEM_WALLET_GIANT, OBJECT_GI_PURSE, GID_WALLET_GIANT, 0x9, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_RECOVERY_HEART
    GET_ITEM(ITEM_RECOVERY_HEART, OBJECT_GI_HEART, GID_RECOVERY_HEART, 0xA, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_0B
    GET_ITEM(ITEM_RECOVERY_HEART, OBJECT_GI_HEART, GID_RECOVERY_HEART, 0xB,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_HEART_PIECE
    GET_ITEM(ITEM_HEART_PIECE_2, OBJECT_GI_HEARTS, GID_HEART_PIECE, 0xC,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_HEART_CONTAINER
    GET_ITEM(ITEM_HEART_CONTAINER, OBJECT_GI_HEARTS, GID_HEART_CONTAINER, 0xD,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_MAGIC_JAR_SMALL
    GET_ITEM(ITEM_MAGIC_JAR_SMALL, OBJECT_GI_MAGICPOT, GID_MAGIC_JAR_SMALL, 0xE,
             GIFIELD(GIFIELD_20 | GIFIELD_40, ITEM00_MAGIC_JAR_SMALL), CHEST_ANIM_SHORT),
    // GI_MAGIC_JAR_BIG
    GET_ITEM(ITEM_MAGIC_JAR_BIG, OBJECT_GI_MAGICPOT, GID_MAGIC_JAR_BIG, 0xF,
             GIFIELD(GIFIELD_20 | GIFIELD_40, ITEM00_MAGIC_JAR_BIG), CHEST_ANIM_SHORT),
    // GI_10
    GET_ITEM(ITEM_RECOVERY_HEART, OBJECT_GI_HEART, GID_RECOVERY_HEART, 0x10, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_STRAY_FAIRY
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x11, 0, 0),
    // GI_12
    GET_ITEM(ITEM_RECOVERY_HEART, OBJECT_GI_HEART, GID_RECOVERY_HEART, 0x12, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_13
    GET_ITEM(ITEM_RECOVERY_HEART, OBJECT_GI_HEART, GID_RECOVERY_HEART, 0x13, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_BOMBS_1
    GET_ITEM(ITEM_BOMB, OBJECT_GI_BOMB_1, GID_BOMB, 0x14, GIFIELD(GIFIELD_40, ITEM00_BOMBS_0), CHEST_ANIM_SHORT),
    // GI_BOMBS_5
    GET_ITEM(ITEM_BOMBS_5, OBJECT_GI_BOMB_1, GID_BOMB, 0x15, GIFIELD(GIFIELD_40, ITEM00_BOMBS_0), CHEST_ANIM_SHORT),
    // GI_BOMBS_10
    GET_ITEM(ITEM_BOMBS_10, OBJECT_GI_BOMB_1, GID_BOMB, 0x16, GIFIELD(GIFIELD_40, ITEM00_BOMBS_0), CHEST_ANIM_SHORT),
    // GI_BOMBS_20
    GET_ITEM(ITEM_BOMBS_20, OBJECT_GI_BOMB_1, GID_BOMB, 0x17, GIFIELD(GIFIELD_40, ITEM00_BOMBS_0), CHEST_ANIM_SHORT),
    // GI_BOMBS_30
    GET_ITEM(ITEM_BOMBS_30, OBJECT_GI_BOMB_1, GID_BOMB, 0x18, GIFIELD(GIFIELD_40, ITEM00_BOMBS_0), CHEST_ANIM_SHORT),
    // GI_DEKU_STICKS_1
    GET_ITEM(ITEM_DEKU_STICK, OBJECT_GI_STICK, GID_DEKU_STICK, 0x19, GIFIELD(0, ITEM00_DEKU_STICK), CHEST_ANIM_SHORT),
    // GI_BOMBCHUS_10
    GET_ITEM(ITEM_BOMBCHUS_10, OBJECT_GI_BOMB_2, GID_BOMBCHU, 0x1A, GIFIELD(GIFIELD_40 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    // GI_BOMB_BAG_20
    GET_ITEM(ITEM_BOMB_BAG_20, OBJECT_GI_BOMBPOUCH, GID_BOMB_BAG_20, 0x1B,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_BOMB_BAG_30
    GET_ITEM(ITEM_BOMB_BAG_30, OBJECT_GI_BOMBPOUCH, GID_BOMB_BAG_30, 0x1C,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_BOMB_BAG_40
    GET_ITEM(ITEM_BOMB_BAG_40, OBJECT_GI_BOMBPOUCH, GID_BOMB_BAG_40, 0x1D,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_ARROWS_10
    GET_ITEM(ITEM_ARROWS_10, OBJECT_GI_ARROW, GID_ARROWS_SMALL, 0x1E, GIFIELD(GIFIELD_40, ITEM00_ARROWS_30),
             CHEST_ANIM_SHORT),
    // GI_ARROWS_30
    GET_ITEM(ITEM_ARROWS_30, OBJECT_GI_ARROW, GID_ARROWS_MEDIUM, 0x1F, GIFIELD(GIFIELD_40, ITEM00_ARROWS_40),
             CHEST_ANIM_SHORT),
    // GI_ARROWS_40
    GET_ITEM(ITEM_ARROWS_40, OBJECT_GI_ARROW, GID_ARROWS_LARGE, 0x20, GIFIELD(GIFIELD_40, ITEM00_ARROWS_50),
             CHEST_ANIM_SHORT),
    // GI_ARROWS_50
    GET_ITEM(ITEM_ARROWS_40, OBJECT_GI_ARROW, GID_ARROWS_LARGE, 0x21, GIFIELD(GIFIELD_40, ITEM00_ARROWS_50),
             CHEST_ANIM_SHORT),
    // GI_QUIVER_30
    GET_ITEM(ITEM_BOW, OBJECT_GI_BOW, GID_BOW, 0x22, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_QUIVER_40
    GET_ITEM(ITEM_QUIVER_40, OBJECT_GI_ARROWCASE, GID_QUIVER_40, 0x23, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_QUIVER_50
    GET_ITEM(ITEM_QUIVER_50, OBJECT_GI_ARROWCASE, GID_QUIVER_50, 0x24, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_ARROW_FIRE
    GET_ITEM(ITEM_ARROW_FIRE, OBJECT_GI_M_ARROW, GID_ARROW_FIRE, 0x25, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_ARROW_ICE
    GET_ITEM(ITEM_ARROW_ICE, OBJECT_GI_M_ARROW, GID_ARROW_ICE, 0x26, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_ARROW_LIGHT
    GET_ITEM(ITEM_ARROW_LIGHT, OBJECT_GI_M_ARROW, GID_ARROW_LIGHT, 0x27,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_DEKU_NUTS_1
    GET_ITEM(ITEM_DEKU_NUT, OBJECT_GI_NUTS, GID_DEKU_NUTS, 0x28, GIFIELD(0, ITEM00_DEKU_NUTS_1), CHEST_ANIM_SHORT),
    // GI_DEKU_NUTS_5
    GET_ITEM(ITEM_DEKU_NUTS_5, OBJECT_GI_NUTS, GID_DEKU_NUTS, 0x29, GIFIELD(0, ITEM00_DEKU_NUTS_1), CHEST_ANIM_SHORT),
    // GI_DEKU_NUTS_10
    GET_ITEM(ITEM_DEKU_NUTS_10, OBJECT_GI_NUTS, GID_DEKU_NUTS, 0x2A, GIFIELD(0, ITEM00_DEKU_NUTS_1), CHEST_ANIM_SHORT),
    // GI_2B
    GET_ITEM(ITEM_DEKU_NUT_UPGRADE_30, OBJECT_GI_NUTS, GID_DEKU_NUTS, 0x2B,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_SHORT),
    // GI_2C
    GET_ITEM(ITEM_DEKU_NUT_UPGRADE_30, OBJECT_GI_NUTS, GID_DEKU_NUTS, 0x2C,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_SHORT),
    // GI_2D
    GET_ITEM(ITEM_DEKU_NUT_UPGRADE_40, OBJECT_GI_NUTS, GID_DEKU_NUTS, 0x2D,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_SHORT),
    // GI_BOMBCHUS_20
    GET_ITEM(ITEM_BOMBCHUS_20, OBJECT_GI_BOMB_2, GID_BOMBCHU, 0x2E, GIFIELD(GIFIELD_40 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    // GI_2F
    GET_ITEM(ITEM_DEKU_STICK_UPGRADE_20, OBJECT_GI_STICK, GID_DEKU_STICK, 0x2F,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_SHORT),
    // GI_30
    GET_ITEM(ITEM_DEKU_STICK_UPGRADE_20, OBJECT_GI_STICK, GID_DEKU_STICK, 0x30,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_SHORT),
    // GI_31
    GET_ITEM(ITEM_DEKU_STICK_UPGRADE_30, OBJECT_GI_STICK, GID_DEKU_STICK, 0x31,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_SHORT),
    // GI_SHIELD_HERO
    GET_ITEM(ITEM_SHIELD_HERO, OBJECT_GI_SHIELD_2, GID_SHIELD_HERO, 0x32,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_SHORT),
    // GI_SHIELD_MIRROR
    GET_ITEM(ITEM_SHIELD_MIRROR, OBJECT_GI_SHIELD_3, GID_SHIELD_MIRROR, 0x33,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_POWDER_KEG
    GET_ITEM(ITEM_POWDER_KEG, OBJECT_GI_BIGBOMB, GID_POWDER_KEG, 0x34, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_MAGIC_BEANS
    GET_ITEM(ITEM_MAGIC_BEANS, OBJECT_GI_BEAN, GID_MAGIC_BEANS, 0x35, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    // GI_BOMBCHUS_1
    GET_ITEM(ITEM_BOMBCHUS_1, OBJECT_GI_BOMB_2, GID_BOMBCHU, 0x36, GIFIELD(GIFIELD_40 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    // GI_SWORD_KOKIRI
    GET_ITEM(ITEM_SWORD_KOKIRI, OBJECT_GI_SWORD_1, GID_SWORD_KOKIRI, 0x37,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_SWORD_RAZOR
    GET_ITEM(ITEM_SWORD_RAZOR, OBJECT_GI_SWORD_2, GID_SWORD_RAZOR, 0x38,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_SWORD_GILDED
    GET_ITEM(ITEM_SWORD_GILDED, OBJECT_GI_SWORD_3, GID_SWORD_GILDED, 0x39,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_BOMBCHUS_5
    GET_ITEM(ITEM_BOMBCHUS_5, OBJECT_GI_BOMB_2, GID_BOMBCHU, 0x3A, GIFIELD(GIFIELD_40 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    // GI_SWORD_GREAT_FAIRY
    GET_ITEM(ITEM_SWORD_GREAT_FAIRY, OBJECT_GI_SWORD_4, GID_SWORD_GREAT_FAIRY, 0x3B,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_KEY_SMALL
    GET_ITEM(ITEM_KEY_SMALL, OBJECT_GI_KEY, GID_KEY_SMALL, 0x3C, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    // GI_KEY_BOSS
    GET_ITEM(ITEM_KEY_BOSS, OBJECT_GI_BOSSKEY, GID_KEY_BOSS, 0x3D, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_MAP
    GET_ITEM(ITEM_DUNGEON_MAP, OBJECT_GI_MAP, GID_DUNGEON_MAP, 0x3E, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_COMPASS
    GET_ITEM(ITEM_COMPASS, OBJECT_GI_COMPASS, GID_COMPASS, 0x3F, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_40
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x40, 0, 0),
    // GI_HOOKSHOT
    GET_ITEM(ITEM_HOOKSHOT, OBJECT_GI_HOOKSHOT, GID_HOOKSHOT, 0x41, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_LENS_OF_TRUTH
    GET_ITEM(ITEM_LENS_OF_TRUTH, OBJECT_GI_GLASSES, GID_LENS, 0x42, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_PICTOGRAPH_BOX
    GET_ITEM(ITEM_PICTOGRAPH_BOX, OBJECT_GI_CAMERA, GID_PICTOGRAPH_BOX, 0x43,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_44
    GET_ITEM(ITEM_PICTOGRAPH_BOX, OBJECT_UNSET_0, GID_NONE, 0x44, GIFIELD(0, ITEM00_RUPEE_GREEN), 0),
    // GI_45
    GET_ITEM(ITEM_RECOVERY_HEART, OBJECT_GI_HEART, GID_RECOVERY_HEART, 0x45, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_46
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x46, 0, 0),
    // GI_47
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x47, 0, 0),
    // GI_48
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x48, 0, 0),
    // GI_49
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x49, 0, 0),
    // GI_4A
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x4A, 0, 0),
    // GI_4B
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x4B, 0, 0),
    // GI_OCARINA_OF_TIME
    GET_ITEM(ITEM_OCARINA_OF_TIME, OBJECT_GI_OCARINA, GID_OCARINA, 0x4C,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_4D
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x4D, 0, 0),
    // GI_4E
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x4E, 0, 0),
    // GI_4F
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x4F, 0, 0),
    // GI_BOMBERS_NOTEBOOK
    GET_ITEM(ITEM_BOMBERS_NOTEBOOK, OBJECT_GI_SCHEDULE, GID_BOMBERS_NOTEBOOK, 0x50, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_51
    GET_ITEM(ITEM_NONE, OBJECT_GI_MAP, GID_STONE_OF_AGONY, 0x51, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_SKULL_TOKEN
    GET_ITEM(ITEM_SKULL_TOKEN, OBJECT_GI_SUTARU, GID_SKULL_TOKEN, 0x52, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_SHORT),
    // GI_53
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x53, 0, 0),
    // GI_54
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x54, 0, 0),
    // GI_REMAINS_ODOLWA
    GET_ITEM(ITEM_REMAINS_ODOLWA, OBJECT_UNSET_0, GID_REMAINS_ODOLWA, 0x55, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_REMAINS_GOHT
    GET_ITEM(ITEM_REMAINS_GOHT, OBJECT_UNSET_0, GID_REMAINS_GOHT, 0x56, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_REMAINS_GYORG
    GET_ITEM(ITEM_REMAINS_GYORG, OBJECT_UNSET_0, GID_REMAINS_GYORG, 0x57, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_REMAINS_TWINMOLD
    GET_ITEM(ITEM_REMAINS_TWINMOLD, OBJECT_UNSET_0, GID_REMAINS_TWINMOLD, 0x58, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_POTION_RED_BOTTLE
    GET_ITEM(ITEM_LONGSHOT, OBJECT_GI_BOTTLE_RED, GID_57, GIFIELD(GIFIELD_40, ITEM00_BOMBS_0),
             GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_BOTTLE
    GET_ITEM(ITEM_BOTTLE, OBJECT_GI_BOTTLE, GID_BOTTLE, 0x5A, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_POTION_RED
    GET_ITEM(ITEM_POTION_RED, OBJECT_GI_LIQUID, GID_POTION_RED, 0x5B, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_POTION_GREEN
    GET_ITEM(ITEM_POTION_GREEN, OBJECT_GI_LIQUID, GID_POTION_GREEN, 0x5C, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_POTION_BLUE
    GET_ITEM(ITEM_POTION_BLUE, OBJECT_GI_LIQUID, GID_POTION_BLUE, 0x5D, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_FAIRY
    GET_ITEM(ITEM_FAIRY, OBJECT_GI_BOTTLE_04, GID_FAIRY, 0x5E, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_DEKU_PRINCESS
    GET_ITEM(ITEM_FAIRY, OBJECT_GI_BOTTLE, GID_BOTTLE, 0x5F, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_MILK_BOTTLE
    GET_ITEM(ITEM_MILK_BOTTLE, OBJECT_GI_MILK, GID_MILK, 0x60, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_MILK_HALF
    GET_ITEM(ITEM_MILK_HALF, OBJECT_GI_MILK, GID_MILK, 0x61, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_FISH
    GET_ITEM(ITEM_FISH, OBJECT_GI_FISH, GID_FISH, 0x62, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_BUG
    GET_ITEM(ITEM_BUG, OBJECT_GI_INSECT, GID_BUG, 0x63, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_BLUE_FIRE
    GET_ITEM(ITEM_BLUE_FIRE, OBJECT_UNSET_0, GID_NONE, 0x64, GIFIELD(0, ITEM00_RUPEE_GREEN), 0),
    // GI_POE
    GET_ITEM(ITEM_BOTTLE, OBJECT_GI_BOTTLE, GID_BOTTLE, 0x65, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_BIG_POE
    GET_ITEM(ITEM_BIG_POE, OBJECT_GI_GHOST, GID_BIG_POE, 0x66, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_SPRING_WATER
    GET_ITEM(ITEM_SPRING_WATER, OBJECT_UNSET_0, GID_NONE, 0x67, GIFIELD(0, ITEM00_RUPEE_GREEN), 0),
    // GI_HOT_SPRING_WATER
    GET_ITEM(ITEM_HOT_SPRING_WATER, OBJECT_UNSET_0, GID_NONE, 0x68, GIFIELD(0, ITEM00_RUPEE_GREEN), 0),
    // GI_ZORA_EGG
    GET_ITEM(ITEM_ZORA_EGG, OBJECT_GI_BOTTLE_15, GID_ZORA_EGG, 0x69, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_GOLD_DUST
    GET_ITEM(ITEM_GOLD_DUST, OBJECT_GI_BOTTLE_16, GID_SEAHORSE, 0x6A, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_MUSHROOM
    GET_ITEM(ITEM_MUSHROOM, OBJECT_GI_MAGICMUSHROOM, GID_MUSHROOM, 0x6B, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_6C
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x6C, GIFIELD(0, ITEM00_RUPEE_GREEN), 0),
    // GI_6D
    GET_ITEM(ITEM_BOTTLE, OBJECT_GI_BOTTLE, GID_BOTTLE, 0x6D, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_SEAHORSE
    GET_ITEM(ITEM_SEAHORSE, OBJECT_GI_BOTTLE_16, GID_SEAHORSE, 0x6E, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_CHATEAU_BOTTLE
    GET_ITEM(ITEM_CHATEAU, OBJECT_GI_BOTTLE_21, GID_CHATEAU, 0x6F, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_HYLIAN_LOACH
    GET_ITEM(ITEM_BOTTLE, OBJECT_GI_BOTTLE, GID_BOTTLE, 0x70, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_71
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x71, 0, 0),
    // GI_72
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x72, 0, 0),
    // GI_73
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x73, 0, 0),
    // GI_74
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x74, 0, 0),
    // GI_75
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x75, 0, 0),
    // GI_ICE_TRAP
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x76, 0, 0),
    // GI_77
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x77, 0, 0),
    // GI_MASK_DEKU
    GET_ITEM(ITEM_MASK_DEKU, OBJECT_GI_NUTSMASK, GID_MASK_DEKU, 0x78, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_MASK_GORON
    GET_ITEM(ITEM_MASK_GORON, OBJECT_GI_GOLONMASK, GID_MASK_GORON, 0x79,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_MASK_ZORA
    GET_ITEM(ITEM_MASK_ZORA, OBJECT_GI_ZORAMASK, GID_MASK_ZORA, 0x7A, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_MASK_FIERCE_DEITY
    GET_ITEM(ITEM_MASK_FIERCE_DEITY, OBJECT_GI_MASK03, GID_MASK_FIERCE_DEITY, 0x7B,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_MASK_CAPTAIN
    GET_ITEM(ITEM_MASK_CAPTAIN, OBJECT_GI_MASK18, GID_MASK_CAPTAIN, 0x7C,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_MASK_GIANT
    GET_ITEM(ITEM_MASK_GIANT, OBJECT_GI_MASK23, GID_MASK_GIANT, 0x7D, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_MASK_ALL_NIGHT
    GET_ITEM(ITEM_MASK_ALL_NIGHT, OBJECT_GI_MASK06, GID_MASK_ALL_NIGHT, 0x7E,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_MASK_BUNNY
    GET_ITEM(ITEM_MASK_BUNNY, OBJECT_GI_RABIT_MASK, GID_MASK_BUNNY, 0x7F,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_MASK_KEATON
    GET_ITEM(ITEM_MASK_KEATON, OBJECT_GI_KI_TAN_MASK, GID_MASK_KEATON, 0x80,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_MASK_GARO
    GET_ITEM(ITEM_MASK_GARO, OBJECT_GI_MASK09, GID_MASK_GARO, 0x81, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_MASK_ROMANI
    GET_ITEM(ITEM_MASK_ROMANI, OBJECT_GI_MASK10, GID_MASK_ROMANI, 0x82, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_MASK_CIRCUS_LEADER
    GET_ITEM(ITEM_MASK_CIRCUS_LEADER, OBJECT_GI_MASK11, GID_MASK_CIRCUS_LEADER, 0x83,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_MASK_POSTMAN
    GET_ITEM(ITEM_MASK_POSTMAN, OBJECT_GI_MASK12, GID_MASK_POSTMAN, 0x84,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_MASK_COUPLE
    GET_ITEM(ITEM_MASK_COUPLE, OBJECT_GI_MASK13, GID_MASK_COUPLE, 0x85, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_MASK_GREAT_FAIRY
    GET_ITEM(ITEM_MASK_GREAT_FAIRY, OBJECT_GI_MASK14, GID_MASK_GREAT_FAIRY, 0x86,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_MASK_GIBDO
    GET_ITEM(ITEM_MASK_GIBDO, OBJECT_GI_MASK15, GID_MASK_GIBDO, 0x87, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_MASK_DON_GERO
    GET_ITEM(ITEM_MASK_DON_GERO, OBJECT_GI_MASK16, GID_MASK_DON_GERO, 0x88,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_MASK_KAMARO
    GET_ITEM(ITEM_MASK_KAMARO, OBJECT_GI_MASK17, GID_MASK_KAMARO, 0x89, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_MASK_TRUTH
    GET_ITEM(ITEM_MASK_TRUTH, OBJECT_GI_TRUTH_MASK, GID_MASK_TRUTH, 0x8A,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_MASK_STONE
    GET_ITEM(ITEM_MASK_STONE, OBJECT_GI_STONEMASK, GID_MASK_STONE, 0x8B,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_MASK_BREMEN
    GET_ITEM(ITEM_MASK_BREMEN, OBJECT_GI_MASK20, GID_MASK_BREMEN, 0x8C, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_MASK_BLAST
    GET_ITEM(ITEM_MASK_BLAST, OBJECT_GI_MASK21, GID_MASK_BLAST, 0x8D, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_MASK_SCENTS
    GET_ITEM(ITEM_MASK_SCENTS, OBJECT_GI_MASK22, GID_MASK_SCENTS, 0x8E, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_MASK_KAFEIS_MASK
    GET_ITEM(ITEM_MASK_KAFEIS_MASK, OBJECT_GI_MASK05, GID_MASK_KAFEIS_MASK, 0x8F,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_90
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0x90, 0, 0),
    // GI_CHATEAU
    GET_ITEM(ITEM_CHATEAU_2, OBJECT_GI_BOTTLE_21, GID_CHATEAU, 0x91, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_MILK
    GET_ITEM(ITEM_MILK, OBJECT_GI_MILK, GID_MILK, 0x92, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_GOLD_DUST_2
    GET_ITEM(ITEM_GOLD_DUST_2, OBJECT_GI_GOLD_DUST, GID_GOLD_DUST, 0x93, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_HYLIAN_LOACH_2
    GET_ITEM(ITEM_HYLIAN_LOACH_2, OBJECT_GI_LOACH, GID_HYLIAN_LOACH, 0x94, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_SEAHORSE_CAUGHT
    GET_ITEM(ITEM_SEAHORSE_CAUGHT, OBJECT_GI_SEAHORSE, GID_SEAHORSE_CAUGHT, 0x95, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_MOONS_TEAR
    GET_ITEM(ITEM_MOONS_TEAR, OBJECT_GI_RESERVE00, GID_MOONS_TEAR, 0x96, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_DEED_LAND
    GET_ITEM(ITEM_DEED_LAND, OBJECT_GI_RESERVE01, GID_DEED_LAND, 0x97, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_DEED_SWAMP
    GET_ITEM(ITEM_DEED_SWAMP, OBJECT_GI_RESERVE01, GID_DEED_SWAMP, 0x98, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_DEED_MOUNTAIN
    GET_ITEM(ITEM_DEED_MOUNTAIN, OBJECT_GI_RESERVE01, GID_DEED_MOUNTAIN, 0x99, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_DEED_OCEAN
    GET_ITEM(ITEM_DEED_OCEAN, OBJECT_GI_RESERVE01, GID_DEED_OCEAN, 0x9A, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_SWORD_GREAT_FAIRY_STOLEN
    GET_ITEM(ITEM_SWORD_GREAT_FAIRY, OBJECT_GI_SWORD_4, GID_SWORD_GREAT_FAIRY, 0x9B,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_SWORD_KOKIRI_STOLEN
    GET_ITEM(ITEM_SWORD_KOKIRI, OBJECT_GI_SWORD_1, GID_SWORD_KOKIRI, 0x9C,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_SWORD_RAZOR_STOLEN
    GET_ITEM(ITEM_SWORD_RAZOR, OBJECT_GI_SWORD_2, GID_SWORD_RAZOR, 0x9D,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_SWORD_GILDED_STOLEN
    GET_ITEM(ITEM_SWORD_GILDED, OBJECT_GI_SWORD_3, GID_SWORD_GILDED, 0x9E,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_SHIELD_HERO_STOLEN
    GET_ITEM(ITEM_SHIELD_HERO, OBJECT_GI_SHIELD_2, GID_SHIELD_HERO, 0x9F,
             GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_SHORT),
    // GI_ROOM_KEY
    GET_ITEM(ITEM_ROOM_KEY, OBJECT_GI_RESERVE_B_00, GID_ROOM_KEY, 0xA0, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_LETTER_TO_MAMA
    GET_ITEM(ITEM_LETTER_MAMA, OBJECT_GI_RESERVE_B_01, GID_LETTER_MAMA, 0xA1, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_A2
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xA2, 0, 0),
    // GI_A3
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xA3, 0, 0),
    // GI_A4
    GET_ITEM(ITEM_NONE, OBJECT_GI_KI_TAN_MASK, GID_MASK_KEATON, 0xA4, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_A5
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xA5, 0, 0),
    // GI_A6
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xA6, 0, 0),
    // GI_A7
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xA7, 0, 0),
    // GI_A8
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xA8, 0, 0),
    // GI_BOTTLE_STOLEN
    GET_ITEM(ITEM_BOTTLE, OBJECT_GI_BOTTLE, GID_BOTTLE, 0xA9, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_LETTER_TO_KAFEI
    GET_ITEM(ITEM_LETTER_TO_KAFEI, OBJECT_GI_RESERVE_C_00, GID_LETTER_TO_KAFEI, 0xAA,
             GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_PENDANT_OF_MEMORIES
    GET_ITEM(ITEM_PENDANT_OF_MEMORIES, OBJECT_GI_RESERVE_C_01, GID_PENDANT_OF_MEMORIES, 0xAB,
             GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_AC
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xAC, 0, 0),
    // GI_AD
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xAD, 0, 0),
    // GI_AE
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xAE, 0, 0),
    // GI_AF
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xAF, 0, 0),
    // GI_B0
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xB0, 0, 0),
    // GI_B1
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xB1, 0, 0),
    // GI_B2
    GET_ITEM(ITEM_NONE, OBJECT_UNSET_0, GID_NONE, 0xB2, 0, 0),
    // GI_B3
    GET_ITEM(ITEM_NONE, OBJECT_GI_MSSA, GID_MASK_SUN, 0xB3, GIFIELD(GIFIELD_NO_COLLECTIBLE, 0), CHEST_ANIM_LONG),
    // GI_TINGLE_MAP_CLOCK_TOWN
    GET_ITEM(ITEM_TINGLE_MAP, OBJECT_GI_FIELDMAP, GID_TINGLE_MAP, 0xB4, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_TINGLE_MAP_WOODFALL
    GET_ITEM(ITEM_TINGLE_MAP, OBJECT_GI_FIELDMAP, GID_TINGLE_MAP, 0xB5, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_TINGLE_MAP_SNOWHEAD
    GET_ITEM(ITEM_TINGLE_MAP, OBJECT_GI_FIELDMAP, GID_TINGLE_MAP, 0xB6, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_TINGLE_MAP_ROMANI_RANCH
    GET_ITEM(ITEM_TINGLE_MAP, OBJECT_GI_FIELDMAP, GID_TINGLE_MAP, 0xB7, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_TINGLE_MAP_GREAT_BAY
    GET_ITEM(ITEM_TINGLE_MAP, OBJECT_GI_FIELDMAP, GID_TINGLE_MAP, 0xB8, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
    // GI_TINGLE_MAP_STONE_TOWER
    GET_ITEM(ITEM_TINGLE_MAP, OBJECT_GI_FIELDMAP, GID_TINGLE_MAP, 0xB9, GIFIELD(GIFIELD_20 | GIFIELD_NO_COLLECTIBLE, 0),
             CHEST_ANIM_LONG),
};

// Player_UpdateCurrentGetItemDrawId?
void func_8082ECE0(Player* this) {
    GetItemEntry* giEntry = &sGetItemTable[this->getItemId - 1];

    this->getItemDrawIdPlusOne = ABS_ALT(giEntry->gid);
}

PlayerAnimationHeader* func_8082ED20(Player* this) {
    if ((this->transformation == PLAYER_FORM_ZORA) || (this->actor.id != ACTOR_PLAYER)) {
        return &gPlayerAnim_pz_wait;
    }
    if (this->transformation == PLAYER_FORM_GORON) {
        return &gPlayerAnim_pg_wait;
    }
    if (this->currentMask == PLAYER_MASK_SCENTS) {
        return &gPlayerAnim_cl_msbowait;
    }
    return D_8085BE84[PLAYER_ANIMGROUP_0][this->modelAnimType];
}

PlayerAnimationHeader* sPlayerIdleAnimations[][2] = {
    { &gPlayerAnim_link_normal_wait_typeA_20f, &gPlayerAnim_link_normal_waitF_typeA_20f }, // ROOM_BEHAVIOR_TYPE2_0
    { &gPlayerAnim_link_normal_wait_typeC_20f, &gPlayerAnim_link_normal_waitF_typeC_20f }, // ROOM_BEHAVIOR_TYPE2_1
    { &gPlayerAnim_link_normal_wait_typeB_20f, &gPlayerAnim_link_normal_waitF_typeB_20f }, // ROOM_BEHAVIOR_TYPE2_2
    { &gPlayerAnim_link_normal_wait_typeB_20f, &gPlayerAnim_link_normal_waitF_typeB_20f }, // ROOM_BEHAVIOR_TYPE2_HOT
    { &gPlayerAnim_link_wait_typeD_20f, &gPlayerAnim_link_waitF_typeD_20f },               // ROOM_BEHAVIOR_TYPE2_4
    { &gPlayerAnim_link_wait_typeD_20f, &gPlayerAnim_link_waitF_typeD_20f },               // ROOM_BEHAVIOR_TYPE2_5
    { &gPlayerAnim_link_wait_typeD_20f, &gPlayerAnim_link_waitF_typeD_20f },               // ROOM_BEHAVIOR_TYPE2_6
    { &gPlayerAnim_link_wait_heat1_20f, &gPlayerAnim_link_waitF_heat1_20f },
    { &gPlayerAnim_link_wait_heat2_20f, &gPlayerAnim_link_waitF_heat2_20f },
    { &gPlayerAnim_link_wait_itemD1_20f, &gPlayerAnim_link_wait_itemD1_20f },
    { &gPlayerAnim_link_wait_itemA_20f, &gPlayerAnim_link_waitF_itemA_20f },
    { &gPlayerAnim_link_wait_itemB_20f, &gPlayerAnim_link_waitF_itemB_20f },
    { &gPlayerAnim_link_wait_itemC_20f, &gPlayerAnim_link_wait_itemC_20f },
    { &gPlayerAnim_link_wait_itemD2_20f, &gPlayerAnim_link_wait_itemD2_20f },
    { &gPlayerAnim_cl_msbowait, &gPlayerAnim_cl_msbowait },
};

AnimSfxEntry D_8085C8C4[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 8, NA_SE_VO_LI_SNEEZE, STOP),
};
AnimSfxEntry D_8085C8C8[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 18, NA_SE_VO_LI_SWEAT, STOP),
};
AnimSfxEntry D_8085C8CC[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 13, NA_SE_VO_LI_BREATH_REST, STOP),
};
AnimSfxEntry D_8085C8D0[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 10, NA_SE_VO_LI_BREATH_REST, STOP),
};

AnimSfxEntry D_8085C8D4[] = {
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 44, NA_SE_PL_CALM_HIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 48, NA_SE_PL_CALM_HIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 52, NA_SE_PL_CALM_HIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 56, NA_SE_PL_CALM_HIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 60, NA_SE_PL_CALM_HIT, STOP),
};

AnimSfxEntry D_8085C8E8[] = {
    ANIMSFX(ANIMSFX_TYPE_8, 25, NA_SE_NONE, CONTINUE), ANIMSFX(ANIMSFX_TYPE_8, 30, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_8, 44, NA_SE_NONE, CONTINUE), ANIMSFX(ANIMSFX_TYPE_8, 48, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_8, 52, NA_SE_NONE, CONTINUE), ANIMSFX(ANIMSFX_TYPE_8, 56, NA_SE_NONE, STOP),
};

AnimSfxEntry D_8085C900[] = {
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 16, NA_SE_IT_SHIELD_SWING, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 20, NA_SE_IT_SHIELD_SWING, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 70, NA_SE_IT_SHIELD_SWING, STOP),
};

AnimSfxEntry D_8085C90C[] = {
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 10, NA_SE_IT_HAMMER_SWING, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 10, NA_SE_VO_LI_AUTO_JUMP, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 22, NA_SE_IT_SWORD_SWING, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 22, NA_SE_VO_LI_SWORD_N, STOP),
};

AnimSfxEntry D_8085C91C[] = {
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 39, NA_SE_IT_SWORD_SWING, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 39, NA_SE_VO_LI_SWORD_N, STOP),
};
AnimSfxEntry D_8085C924[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 20, NA_SE_VO_LI_RELAX, STOP),
};

AnimSfxEntry D_8085C928[] = {
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 4, NA_SE_VO_LI_POO_WAIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 12, NA_SE_VO_LI_POO_WAIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 30, NA_SE_VO_LI_POO_WAIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 61, NA_SE_VO_LI_POO_WAIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 68, NA_SE_VO_LI_POO_WAIT, STOP),
};

AnimSfxEntry* D_8085C93C[] = {
    D_8085C8C4, D_8085C8C8, D_8085C8CC, D_8085C8D0, D_8085C8D4, D_8085C8E8,
    D_8085C900, D_8085C90C, D_8085C91C, D_8085C924, D_8085C928, NULL,
};

// Used to index into D_8085C93C
u8 D_8085C96C[] = {
    0, 0, 1, 1, 2, 2, 2, 2, 10, 10, 10, 10, 10, 10, 3, 3, 4, 4, 8, 8, 5, 5, 6, 6, 7, 7, 9, 9, 11, 11,
};

s32 func_8082ED94(Player* this) {
    PlayerAnimationHeader** entry;
    s32 i;

    if ((this->skelAnime.animation != &gPlayerAnim_link_normal_newroll_jump_end_20f) &&
        (this->skelAnime.animation != &gPlayerAnim_link_normal_newside_jump_end_20f)) {
        if ((this->skelAnime.animation != func_8082ED20(this)) ||
            (this->skelAnime.animation == &gPlayerAnim_cl_msbowait)) {
            for (i = 0, entry = &sPlayerIdleAnimations[0][0]; i < ARRAY_COUNT_2D(sPlayerIdleAnimations); i++) {
                if (this->skelAnime.animation == *entry) {
                    return i + 1;
                }
                entry++;
            }

            return 0;
        }
    }

    return -1;
}

void func_8082EEA4(Player* this, s32 arg1) {
    u8 temp_v0 = D_8085C96C[arg1];

    if (temp_v0 != 0) {
        Player_PlayAnimSfx(this, D_8085C93C[temp_v0 - 1]);
    }
}

PlayerAnimationHeader* func_8082EEE0(Player* this) {
    if (this->unk_B64 != 0) {
        return D_8085BE84[PLAYER_ANIMGROUP_3][this->modelAnimType];
    } else {
        return D_8085BE84[PLAYER_ANIMGROUP_2][this->modelAnimType];
    }
}

s32 func_8082EF20(Player* this) {
    return func_8082ECCC(this) && (this->unk_ACC != 0);
}

PlayerAnimationHeader* func_8082EF54(Player* this) {
    if (func_8082EF20(this)) {
        return &gPlayerAnim_link_boom_throw_waitR;
    } else {
        return D_8085BE84[PLAYER_ANIMGROUP_5][this->modelAnimType];
    }
}

PlayerAnimationHeader* func_8082EF9C(Player* this) {
    if (func_8082EF20(this)) {
        return &gPlayerAnim_link_boom_throw_waitL;
    } else {
        return D_8085BE84[PLAYER_ANIMGROUP_4][this->modelAnimType];
    }
}

PlayerAnimationHeader* func_8082EFE4(Player* this) {
    if (func_800B7128(this)) {
        return &gPlayerAnim_link_bow_side_walk;
    } else {
        return D_8085BE84[PLAYER_ANIMGROUP_22][this->modelAnimType];
    }
}

void Player_LerpEnvLighting(PlayState* play, PlayerEnvLighting* lighting, f32 lerp) {
    Environment_LerpAmbientColor(play, &lighting->ambientColor, lerp);
    Environment_LerpDiffuseColor(play, &lighting->diffuseColor, lerp);
    Environment_LerpFogColor(play, &lighting->fogColor, lerp);
    Environment_LerpFog(play, lighting->fogNear, lighting->zFar, lerp);
}

/**
 * Revert cylinder to normal properties
 */
void Player_ResetCylinder(Player* this) {
    this->cylinder.base.colType = COLTYPE_HIT5;
    this->cylinder.base.atFlags = AT_NONE;
    this->cylinder.base.acFlags = AC_ON | AC_TYPE_ENEMY;
    this->cylinder.base.ocFlags1 = OC1_ON | OC1_TYPE_ALL;
    this->cylinder.info.elemType = ELEMTYPE_UNK1;
    this->cylinder.info.toucher.dmgFlags = 0;
    this->cylinder.info.bumper.dmgFlags = 0xF7CFFFFF;
    this->cylinder.info.toucherFlags = TOUCH_NONE | TOUCH_SFX_NORMAL;
    this->cylinder.dim.radius = 12;
}

/**
 * Give cylinder special properties for attacks, uses include
 * - Normal roll
 * - Deku spin
 * - Deku launch
 * - Goron pound
 * - Goron spike roll
 * - Zora barrier
 *
 * and possibly more.
 *
 * @param dmgFlags Damage flags (DMGFLAG defines)
 * @param damage to do
 * @param radius of cylinder
 */
void Player_SetCylinderForAttack(Player* this, u32 dmgFlags, s32 damage, s32 radius) {
    this->cylinder.base.atFlags = AT_ON | AT_TYPE_PLAYER;
    if (radius > 30) {
        this->cylinder.base.ocFlags1 = OC1_NONE;
    } else {
        this->cylinder.base.ocFlags1 = OC1_ON | OC1_TYPE_ALL;
    }

    this->cylinder.info.elemType = ELEMTYPE_UNK2;
    this->cylinder.info.toucherFlags = TOUCH_ON | TOUCH_NEAREST | TOUCH_SFX_NORMAL;
    this->cylinder.dim.radius = radius;
    this->cylinder.info.toucher.dmgFlags = dmgFlags;
    this->cylinder.info.toucher.damage = damage;

    if (dmgFlags & DMG_GORON_POUND) {
        this->cylinder.base.acFlags = AC_NONE;
    } else {
        this->cylinder.base.colType = COLTYPE_NONE;
        this->cylinder.info.bumper.dmgFlags = 0xF7CFFFFF;

        if (dmgFlags & DMG_ZORA_BARRIER) {
            this->cylinder.base.acFlags = AC_NONE;
        } else {
            this->cylinder.base.acFlags = AC_ON | AC_TYPE_ENEMY;
        }
    }
}

// Check for starting Zora barrier
void func_8082F164(Player* this, u16 button) {
    if ((this->transformation == PLAYER_FORM_ZORA) && CHECK_BTN_ALL(sPlayerControlInput->cur.button, button)) {
        this->stateFlags1 |= PLAYER_STATE1_10;
    }
}

PlayerEnvLighting sZoraBarrierEnvLighting = {
    { 0, 0, 0 },       // ambientColor
    { 255, 255, 155 }, // diffuseColor
    { 20, 20, 50 },    // fogColor
    940,               // fogNear
    5000,              // zFar
};

// Run Zora Barrier
void func_8082F1AC(PlayState* play, Player* this) {
    s32 sp4C = this->unk_B62;
    f32 temp;
    s16 sp46;
    s16 sp44;
    f32 sp40;
    f32 sp3C;
    s32 var_v0;

    if ((gSaveContext.save.saveInfo.playerData.magic != 0) && (this->stateFlags1 & PLAYER_STATE1_10)) {
        if (gSaveContext.magicState == MAGIC_STATE_IDLE) {
            Magic_Consume(play, 0, MAGIC_CONSUME_GORON_ZORA);
        }

        temp = 16.0f;
        if (gSaveContext.save.saveInfo.playerData.magic >= 16) {
            var_v0 = 255;
        } else {
            var_v0 = (gSaveContext.save.saveInfo.playerData.magic / temp) * 255.0f;
        }
        Math_StepToS(&this->unk_B62, var_v0, 50);
    } else if (Math_StepToS(&this->unk_B62, 0, 50) && (gSaveContext.magicState != MAGIC_STATE_IDLE)) {
        Magic_Reset(play);
    }

    if ((this->unk_B62 != 0) || (sp4C != 0)) {
        f32 sp34;
        f32 new_var;

        sp46 = play->gameplayFrames * 7000;
        sp44 = play->gameplayFrames * 14000;
        Player_LerpEnvLighting(play, &sZoraBarrierEnvLighting, this->unk_B62 / 255.0f);

        sp34 = Math_SinS(sp44) * 40.0f;
        sp40 = Math_CosS(sp44) * 40.0f;
        sp3C = Math_SinS(sp46) * sp34;
        new_var = Math_CosS(sp46) * sp34;

        Lights_PointNoGlowSetInfo(&this->lightInfo, this->actor.world.pos.x + sp40, this->actor.world.pos.y + sp3C,
                                  this->actor.world.pos.z + new_var, 100, 200, 255, 600);

        Player_PlaySfx(this, NA_SE_PL_ZORA_SPARK_BARRIER - SFX_FLAG);
        Actor_SetPlayerImpact(play, PLAYER_IMPACT_ZORA_BARRIER, 2, 100.0f, &this->actor.world.pos);
    }
}

void Player_SetUpperAction(PlayState* play, Player* this, PlayerUpperActionFunc upperActionFunc) {
    this->upperActionFunc = upperActionFunc;
    this->unk_ACE = 0;
    this->skelAnimeUpperBlendWeight = 0.0f;
    func_8082E00C(this);
}

#define GET_PLAYER_ANIM(group, type) ((PlayerAnimationHeader**)D_8085BE84)[group * PLAYER_ANIMTYPE_MAX + type]

void Player_InitItemActionWithAnim(PlayState* play, Player* this, PlayerItemAction itemAction) {
    PlayerAnimationHeader* curAnim = this->skelAnime.animation;
    PlayerAnimationHeader*(*iter)[PLAYER_ANIMTYPE_MAX] = (void*)&D_8085BE84[0][this->modelAnimType];
    s32 animGroup;

    this->stateFlags1 &= ~(PLAYER_STATE1_8 | PLAYER_STATE1_1000000);

    for (animGroup = 0; animGroup < PLAYER_ANIMGROUP_MAX; animGroup++) {
        if (curAnim == **iter) {
            break;
        }
        iter++;
    }

    Player_InitItemAction(play, this, itemAction);

    if (animGroup < PLAYER_ANIMGROUP_MAX) {
        this->skelAnime.animation = GET_PLAYER_ANIM(animGroup, this->modelAnimType);
    }
}

s8 sItemItemActions[] = {
    PLAYER_IA_OCARINA,                 // ITEM_OCARINA_OF_TIME,
    PLAYER_IA_BOW,                     // ITEM_BOW,
    PLAYER_IA_BOW_FIRE,                // ITEM_ARROW_FIRE,
    PLAYER_IA_BOW_ICE,                 // ITEM_ARROW_ICE,
    PLAYER_IA_BOW_LIGHT,               // ITEM_ARROW_LIGHT,
    PLAYER_IA_PICTOGRAPH_BOX,          // ITEM_OCARINA_FAIRY,
    PLAYER_IA_BOMB,                    // ITEM_BOMB,
    PLAYER_IA_BOMBCHU,                 // ITEM_BOMBCHU,
    PLAYER_IA_DEKU_STICK,              // ITEM_DEKU_STICK,
    PLAYER_IA_DEKU_NUT,                // ITEM_DEKU_NUT,
    PLAYER_IA_MAGIC_BEANS,             // ITEM_MAGIC_BEANS,
    PLAYER_IA_PICTOGRAPH_BOX,          // ITEM_SLINGSHOT,
    PLAYER_IA_POWDER_KEG,              // ITEM_POWDER_KEG,
    PLAYER_IA_PICTOGRAPH_BOX,          // ITEM_PICTOGRAPH_BOX,
    PLAYER_IA_LENS_OF_TRUTH,           // ITEM_LENS_OF_TRUTH,
    PLAYER_IA_HOOKSHOT,                // ITEM_HOOKSHOT,
    PLAYER_IA_SWORD_TWO_HANDED,        // ITEM_SWORD_GREAT_FAIRY,
    PLAYER_IA_PICTOGRAPH_BOX,          // ITEM_LONGSHOT, // OoT Leftover
    PLAYER_IA_BOTTLE_EMPTY,            // ITEM_BOTTLE,
    PLAYER_IA_BOTTLE_POTION_RED,       // ITEM_POTION_RED,
    PLAYER_IA_BOTTLE_POTION_GREEN,     // ITEM_POTION_GREEN,
    PLAYER_IA_BOTTLE_POTION_BLUE,      // ITEM_POTION_BLUE,
    PLAYER_IA_BOTTLE_FAIRY,            // ITEM_FAIRY,
    PLAYER_IA_BOTTLE_DEKU_PRINCESS,    // ITEM_DEKU_PRINCESS,
    PLAYER_IA_BOTTLE_MILK,             // ITEM_MILK_BOTTLE,
    PLAYER_IA_BOTTLE_MILK_HALF,        // ITEM_MILK_HALF,
    PLAYER_IA_BOTTLE_FISH,             // ITEM_FISH,
    PLAYER_IA_BOTTLE_BUG,              // ITEM_BUG,
    PLAYER_IA_BOTTLE_BUG,              // ITEM_BLUE_FIRE, // !
    PLAYER_IA_BOTTLE_POE,              // ITEM_POE,
    PLAYER_IA_BOTTLE_BIG_POE,          // ITEM_BIG_POE,
    PLAYER_IA_BOTTLE_SPRING_WATER,     // ITEM_SPRING_WATER,
    PLAYER_IA_BOTTLE_HOT_SPRING_WATER, // ITEM_HOT_SPRING_WATER,
    PLAYER_IA_BOTTLE_ZORA_EGG,         // ITEM_ZORA_EGG,
    PLAYER_IA_BOTTLE_GOLD_DUST,        // ITEM_GOLD_DUST,
    PLAYER_IA_BOTTLE_MUSHROOM,         // ITEM_MUSHROOM,
    PLAYER_IA_BOTTLE_SEAHORSE,         // ITEM_SEA_HORSE,
    PLAYER_IA_BOTTLE_CHATEAU,          // ITEM_CHATEAU,
    PLAYER_IA_BOTTLE_HYLIAN_LOACH,     // ITEM_HYLIAN_LOACH,
    PLAYER_IA_BOTTLE_POE,              // ITEM_OBABA_DRINK, // !
    PLAYER_IA_MOONS_TEAR,              // ITEM_MOONS_TEAR,
    PLAYER_IA_DEED_LAND,               // ITEM_DEED_LAND,
    PLAYER_IA_DEED_SWAMP,              // ITEM_DEED_SWAMP,
    PLAYER_IA_DEED_MOUNTAIN,           // ITEM_DEED_MOUNTAIN,
    PLAYER_IA_DEED_OCEAN,              // ITEM_DEED_OCEAN,
    PLAYER_IA_ROOM_KEY,                // ITEM_ROOM_KEY,
    PLAYER_IA_LETTER_MAMA,             // ITEM_LETTER_MAMA,
    PLAYER_IA_LETTER_TO_KAFEI,         // ITEM_LETTER_TO_KAFEI,
    PLAYER_IA_PENDANT_OF_MEMORIES,     // ITEM_PENDANT_MEMORIES,
    PLAYER_IA_38,                      // ITEM_TINGLE_MAP, // !
    PLAYER_IA_MASK_DEKU,               // ITEM_MASK_DEKU,
    PLAYER_IA_MASK_GORON,              // ITEM_MASK_GORON,
    PLAYER_IA_MASK_ZORA,               // ITEM_MASK_ZORA,
    PLAYER_IA_MASK_FIERCE_DEITY,       // ITEM_MASK_FIERCE_DEITY,
    PLAYER_IA_MASK_TRUTH,              // ITEM_MASK_TRUTH,
    PLAYER_IA_MASK_KAFEIS_MASK,        // ITEM_MASK_KAFEIS_MASK,
    PLAYER_IA_MASK_ALL_NIGHT,          // ITEM_MASK_ALL_NIGHT,
    PLAYER_IA_MASK_BUNNY,              // ITEM_MASK_BUNNY,
    PLAYER_IA_MASK_KEATON,             // ITEM_MASK_KEATON,
    PLAYER_IA_MASK_GARO,               // ITEM_MASK_GARO,
    PLAYER_IA_MASK_ROMANI,             // ITEM_MASK_ROMANI,
    PLAYER_IA_MASK_CIRCUS_LEADER,      // ITEM_MASK_CIRCUS_LEADER,
    PLAYER_IA_MASK_POSTMAN,            // ITEM_MASK_POSTMAN,
    PLAYER_IA_MASK_COUPLE,             // ITEM_MASK_COUPLE,
    PLAYER_IA_MASK_GREAT_FAIRY,        // ITEM_MASK_GREAT_FAIRY,
    PLAYER_IA_MASK_GIBDO,              // ITEM_MASK_GIBDO,
    PLAYER_IA_MASK_DON_GERO,           // ITEM_MASK_DON_GERO,
    PLAYER_IA_MASK_KAMARO,             // ITEM_MASK_KAMARO,
    PLAYER_IA_MASK_CAPTAIN,            // ITEM_MASK_CAPTAIN,
    PLAYER_IA_MASK_STONE,              // ITEM_MASK_STONE,
    PLAYER_IA_MASK_BREMEN,             // ITEM_MASK_BREMEN,
    PLAYER_IA_MASK_BLAST,              // ITEM_MASK_BLAST,
    PLAYER_IA_MASK_SCENTS,             // ITEM_MASK_SCENTS,
    PLAYER_IA_MASK_GIANT,              // ITEM_MASK_GIANT,
    PLAYER_IA_BOW_FIRE,                // ITEM_BOW_FIRE,
    PLAYER_IA_BOW_ICE,                 // ITEM_BOW_ICE,
    PLAYER_IA_BOW_LIGHT,               // ITEM_BOW_LIGHT,
    PLAYER_IA_SWORD_KOKIRI,            // ITEM_SWORD_KOKIRI,
    PLAYER_IA_SWORD_RAZOR,             // ITEM_SWORD_RAZOR,
    PLAYER_IA_SWORD_GILDED,            // ITEM_SWORD_GILDED,
    PLAYER_IA_SWORD_TWO_HANDED,        // ITEM_SWORD_DEITY,
};

PlayerItemAction Player_ItemToItemAction(Player* this, ItemId item) {
    if (item >= ITEM_FD) {
        return PLAYER_IA_NONE;
    } else if (item == ITEM_FC) {
        return PLAYER_IA_LAST_USED;
    } else if (item == ITEM_FISHING_ROD) {
        return PLAYER_IA_FISHING_ROD;
    } else if ((item == ITEM_SWORD_KOKIRI) && (this->transformation == PLAYER_FORM_ZORA)) {
        return PLAYER_IA_ZORA_FINS;
    } else {
        return sItemItemActions[item];
    }
}

PlayerUpperActionFunc sPlayerUpperActionUpdateFuncs[PLAYER_IA_MAX] = {
    Player_UpperAction_0,  // PLAYER_IA_NONE
    Player_UpperAction_0,  // PLAYER_IA_LAST_USED
    Player_UpperAction_0,  // PLAYER_IA_FISHING_ROD
    Player_UpperAction_1,  // PLAYER_IA_SWORD_KOKIRI
    Player_UpperAction_1,  // PLAYER_IA_SWORD_RAZOR
    Player_UpperAction_1,  // PLAYER_IA_SWORD_GILDED
    Player_UpperAction_1,  // PLAYER_IA_SWORD_TWO_HANDED
    Player_UpperAction_0,  // PLAYER_IA_DEKU_STICK
    Player_UpperAction_0,  // PLAYER_IA_ZORA_FINS
    Player_UpperAction_6,  // PLAYER_IA_BOW
    Player_UpperAction_6,  // PLAYER_IA_BOW_FIRE
    Player_UpperAction_6,  // PLAYER_IA_BOW_ICE
    Player_UpperAction_6,  // PLAYER_IA_BOW_LIGHT
    Player_UpperAction_6,  // PLAYER_IA_HOOKSHOT
    Player_UpperAction_10, // PLAYER_IA_BOMB
    Player_UpperAction_10, // PLAYER_IA_POWDER_KEG
    Player_UpperAction_10, // PLAYER_IA_BOMBCHU
    Player_UpperAction_11, // PLAYER_IA_11
    Player_UpperAction_6,  // PLAYER_IA_DEKU_NUT
    Player_UpperAction_0,  // PLAYER_IA_PICTOGRAPH_BOX
    Player_UpperAction_0,  // PLAYER_IA_OCARINA
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_EMPTY
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_FISH
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_SPRING_WATER
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_HOT_SPRING_WATER
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_ZORA_EGG
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_DEKU_PRINCESS
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_GOLD_DUST
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_1C
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_SEA_HORSE
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_MUSHROOM
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_HYLIAN_LOACH
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_BUG
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_POE
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_BIG_POE
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_POTION_RED
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_POTION_BLUE
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_POTION_GREEN
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_MILK
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_MILK_HALF
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_CHATEAU
    Player_UpperAction_0,  // PLAYER_IA_BOTTLE_FAIRY
    Player_UpperAction_0,  // PLAYER_IA_MOONS_TEAR
    Player_UpperAction_0,  // PLAYER_IA_DEED_LAND
    Player_UpperAction_0,  // PLAYER_IA_ROOM_KEY
    Player_UpperAction_0,  // PLAYER_IA_LETTER_TO_KAFEI
    Player_UpperAction_0,  // PLAYER_IA_MAGIC_BEANS
    Player_UpperAction_0,  // PLAYER_IA_DEED_SWAMP
    Player_UpperAction_0,  // PLAYER_IA_DEED_MOUNTAIN
    Player_UpperAction_0,  // PLAYER_IA_DEED_OCEAN
    Player_UpperAction_0,  // PLAYER_IA_32
    Player_UpperAction_0,  // PLAYER_IA_LETTER_MAMA
    Player_UpperAction_0,  // PLAYER_IA_34
    Player_UpperAction_0,  // PLAYER_IA_35
    Player_UpperAction_0,  // PLAYER_IA_PENDANT_MEMORIES
    Player_UpperAction_0,  // PLAYER_IA_37
    Player_UpperAction_0,  // PLAYER_IA_38
    Player_UpperAction_0,  // PLAYER_IA_39
    Player_UpperAction_0,  // PLAYER_IA_MASK_TRUTH
    Player_UpperAction_0,  // PLAYER_IA_MASK_KAFEIS_MASK
    Player_UpperAction_0,  // PLAYER_IA_MASK_ALL_NIGHT
    Player_UpperAction_0,  // PLAYER_IA_MASK_BUNNY
    Player_UpperAction_0,  // PLAYER_IA_MASK_KEATON
    Player_UpperAction_0,  // PLAYER_IA_MASK_GARO
    Player_UpperAction_0,  // PLAYER_IA_MASK_ROMANI
    Player_UpperAction_0,  // PLAYER_IA_MASK_CIRCUS_LEADER
    Player_UpperAction_0,  // PLAYER_IA_MASK_POSTMAN
    Player_UpperAction_0,  // PLAYER_IA_MASK_COUPLE
    Player_UpperAction_0,  // PLAYER_IA_MASK_GREAT_FAIRY
    Player_UpperAction_0,  // PLAYER_IA_MASK_GIBDO
    Player_UpperAction_0,  // PLAYER_IA_MASK_DON_GERO
    Player_UpperAction_0,  // PLAYER_IA_MASK_KAMARO
    Player_UpperAction_0,  // PLAYER_IA_MASK_CAPTAIN
    Player_UpperAction_0,  // PLAYER_IA_MASK_STONE
    Player_UpperAction_0,  // PLAYER_IA_MASK_BREMEN
    Player_UpperAction_0,  // PLAYER_IA_MASK_BLAST
    Player_UpperAction_0,  // PLAYER_IA_MASK_SCENTS
    Player_UpperAction_0,  // PLAYER_IA_MASK_GIANT
    Player_UpperAction_0,  // PLAYER_IA_MASK_FIERCE_DEITY
    Player_UpperAction_0,  // PLAYER_IA_MASK_GORON
    Player_UpperAction_0,  // PLAYER_IA_MASK_ZORA
    Player_UpperAction_0,  // PLAYER_IA_MASK_DEKU
    Player_UpperAction_0,  // PLAYER_IA_LENS_OF_TRUTH
};

typedef void (*PlayerInitItemActionFunc)(PlayState*, Player*);

PlayerInitItemActionFunc sPlayerItemActionInitFuncs[PLAYER_IA_MAX] = {
    Player_InitItemAction_DoNothing,      // PLAYER_IA_NONE
    Player_InitItemAction_DoNothing,      // PLAYER_IA_LAST_USED
    Player_InitItemAction_DoNothing,      // PLAYER_IA_FISHING_ROD
    Player_InitItemAction_DoNothing,      // PLAYER_IA_SWORD_KOKIRI
    Player_InitItemAction_DoNothing,      // PLAYER_IA_SWORD_RAZOR
    Player_InitItemAction_DoNothing,      // PLAYER_IA_SWORD_GILDED
    Player_InitItemAction_DoNothing,      // PLAYER_IA_SWORD_TWO_HANDED
    Player_InitItemAction_DekuStick,      // PLAYER_IA_DEKU_STICK
    Player_InitItemAction_5,              // PLAYER_IA_ZORA_FINS
    Player_InitItemAction_2,              // PLAYER_IA_BOW
    Player_InitItemAction_2,              // PLAYER_IA_BOW_FIRE
    Player_InitItemAction_2,              // PLAYER_IA_BOW_ICE
    Player_InitItemAction_2,              // PLAYER_IA_BOW_LIGHT
    Player_InitItemAction_SpawnHookshot,  // PLAYER_IA_HOOKSHOT
    Player_InitItemAction_SpawnExplosive, // PLAYER_IA_BOMB
    Player_InitItemAction_SpawnExplosive, // PLAYER_IA_POWDER_KEG
    Player_InitItemAction_SpawnExplosive, // PLAYER_IA_BOMBCHU
    Player_InitItemAction_5,              // PLAYER_IA_11
    Player_InitItemAction_2,              // PLAYER_IA_DEKU_NUT
    Player_InitItemAction_DoNothing,      // PLAYER_IA_PICTOGRAPH_BOX
    Player_InitItemAction_DoNothing,      // PLAYER_IA_OCARINA
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_EMPTY
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_FISH
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_SPRING_WATER
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_HOT_SPRING_WATER
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_ZORA_EGG
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_DEKU_PRINCESS
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_GOLD_DUST
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_1C
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_SEA_HORSE
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_MUSHROOM
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_HYLIAN_LOACH
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_BUG
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_POE
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_BIG_POE
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_POTION_RED
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_POTION_BLUE
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_POTION_GREEN
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_MILK
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_MILK_HALF
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_CHATEAU
    Player_InitItemAction_DoNothing,      // PLAYER_IA_BOTTLE_FAIRY
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MOONS_TEAR
    Player_InitItemAction_DoNothing,      // PLAYER_IA_DEED_LAND
    Player_InitItemAction_DoNothing,      // PLAYER_IA_ROOM_KEY
    Player_InitItemAction_DoNothing,      // PLAYER_IA_LETTER_TO_KAFEI
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MAGIC_BEANS
    Player_InitItemAction_DoNothing,      // PLAYER_IA_DEED_SWAMP
    Player_InitItemAction_DoNothing,      // PLAYER_IA_DEED_MOUNTAIN
    Player_InitItemAction_DoNothing,      // PLAYER_IA_DEED_OCEAN
    Player_InitItemAction_DoNothing,      // PLAYER_IA_32
    Player_InitItemAction_DoNothing,      // PLAYER_IA_LETTER_MAMA
    Player_InitItemAction_DoNothing,      // PLAYER_IA_34
    Player_InitItemAction_DoNothing,      // PLAYER_IA_35
    Player_InitItemAction_DoNothing,      // PLAYER_IA_PENDANT_MEMORIES
    Player_InitItemAction_DoNothing,      // PLAYER_IA_37
    Player_InitItemAction_DoNothing,      // PLAYER_IA_38
    Player_InitItemAction_DoNothing,      // PLAYER_IA_39
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_TRUTH
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_KAFEIS_MASK
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_ALL_NIGHT
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_BUNNY
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_KEATON
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_GARO
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_ROMANI
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_CIRCUS_LEADER
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_POSTMAN
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_COUPLE
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_GREAT_FAIRY
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_GIBDO
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_DON_GERO
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_KAMARO
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_CAPTAIN
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_STONE
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_BREMEN
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_BLAST
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_SCENTS
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_GIANT
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_FIERCE_DEITY
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_GORON
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_ZORA
    Player_InitItemAction_DoNothing,      // PLAYER_IA_MASK_DEKU
    Player_InitItemAction_DoNothing,      // PLAYER_IA_LENS_OF_TRUTH
};

void Player_InitItemAction_DoNothing(PlayState* play, Player* this) {
}

void Player_InitItemAction_DekuStick(PlayState* play, Player* this) {
    this->unk_B28 = 0;
    this->unk_B0C = 1.0f;
}

void Player_InitItemAction_2(PlayState* play, Player* this) {
    this->stateFlags1 |= PLAYER_STATE1_8;

    if (this->heldItemAction == PLAYER_IA_DEKU_NUT) {
        this->unk_B28 = -2;
    } else {
        this->unk_B28 = -1;
    }
    this->unk_ACC = 0;
}

void func_8082F5FC(Player* this, Actor* actor) {
    this->heldActor = actor;
    this->interactRangeActor = actor;
    this->getItemId = GI_NONE;
    this->leftHandWorld.rot.y = actor->shape.rot.y - this->actor.shape.rot.y;
    this->stateFlags1 |= PLAYER_STATE1_800;
}

typedef enum ItemChangeType {
    /*  0 */ PLAYER_ITEM_CHG_0,
    /*  1 */ PLAYER_ITEM_CHG_1,
    /*  2 */ PLAYER_ITEM_CHG_2,
    /*  3 */ PLAYER_ITEM_CHG_3,
    /*  4 */ PLAYER_ITEM_CHG_4,
    /*  5 */ PLAYER_ITEM_CHG_5,
    /*  6 */ PLAYER_ITEM_CHG_6,
    /*  7 */ PLAYER_ITEM_CHG_7,
    /*  8 */ PLAYER_ITEM_CHG_8,
    /*  9 */ PLAYER_ITEM_CHG_9,
    /* 10 */ PLAYER_ITEM_CHG_10,
    /* 11 */ PLAYER_ITEM_CHG_11,
    /* 12 */ PLAYER_ITEM_CHG_12,
    /* 13 */ PLAYER_ITEM_CHG_13,
    /* 14 */ PLAYER_ITEM_CHG_14,
    /* 15 */ PLAYER_ITEM_CHG_MAX
} ItemChangeType;

ItemChangeInfo sPlayerItemChangeInfo[PLAYER_ITEM_CHG_MAX] = {
    { &gPlayerAnim_link_normal_free2free, 12 },     // PLAYER_ITEM_CHG_0
    { &gPlayerAnim_link_normal_normal2fighter, 6 }, // PLAYER_ITEM_CHG_1
    { &gPlayerAnim_link_hammer_normal2long, 8 },    // PLAYER_ITEM_CHG_2
    { &gPlayerAnim_link_normal_normal2free, 8 },    // PLAYER_ITEM_CHG_3
    { &gPlayerAnim_link_fighter_fighter2long, 8 },  // PLAYER_ITEM_CHG_4
    { &gPlayerAnim_link_normal_fighter2free, 10 },  // PLAYER_ITEM_CHG_5
    { &gPlayerAnim_link_hammer_long2free, 7 },      // PLAYER_ITEM_CHG_6
    { &gPlayerAnim_link_hammer_long2long, 11 },     // PLAYER_ITEM_CHG_7
    { &gPlayerAnim_link_normal_free2free, 12 },     // PLAYER_ITEM_CHG_8
    { &gPlayerAnim_link_normal_normal2bom, 4 },     // PLAYER_ITEM_CHG_9
    { &gPlayerAnim_link_normal_long2bom, 4 },       // PLAYER_ITEM_CHG_10
    { &gPlayerAnim_link_normal_free2bom, 4 },       // PLAYER_ITEM_CHG_11
    { &gPlayerAnim_link_anchor_anchor2fighter, 5 }, // PLAYER_ITEM_CHG_12
    { &gPlayerAnim_link_normal_free2freeB, 13 },    // PLAYER_ITEM_CHG_13
    { &gPlayerAnim_pz_bladeon, 4 },                 // PLAYER_ITEM_CHG_14
};

// Maps the appropriate ItemChangeType based on current and next animtype.
// A negative type value means the corresponding animation should be played in reverse.
s8 sPlayerItemChangeTypes[PLAYER_ANIMTYPE_MAX][PLAYER_ANIMTYPE_MAX] = {
    {
        PLAYER_ITEM_CHG_8,  // PLAYER_ANIMTYPE_DEFAULT -> PLAYER_ANIMTYPE_DEFAULT
        -PLAYER_ITEM_CHG_5, // PLAYER_ANIMTYPE_DEFAULT -> PLAYER_ANIMTYPE_1
        -PLAYER_ITEM_CHG_3, // PLAYER_ANIMTYPE_DEFAULT -> PLAYER_ANIMTYPE_2
        -PLAYER_ITEM_CHG_6, // PLAYER_ANIMTYPE_DEFAULT -> PLAYER_ANIMTYPE_3
        PLAYER_ITEM_CHG_8,  // PLAYER_ANIMTYPE_DEFAULT -> PLAYER_ANIMTYPE_4
        PLAYER_ITEM_CHG_11, // PLAYER_ANIMTYPE_DEFAULT -> PLAYER_ANIMTYPE_5
    },
    {
        PLAYER_ITEM_CHG_5,  // PLAYER_ANIMTYPE_1 -> PLAYER_ANIMTYPE_DEFAULT
        PLAYER_ITEM_CHG_0,  // PLAYER_ANIMTYPE_1 -> PLAYER_ANIMTYPE_1
        -PLAYER_ITEM_CHG_1, // PLAYER_ANIMTYPE_1 -> PLAYER_ANIMTYPE_2
        PLAYER_ITEM_CHG_4,  // PLAYER_ANIMTYPE_1 -> PLAYER_ANIMTYPE_3
        PLAYER_ITEM_CHG_5,  // PLAYER_ANIMTYPE_1 -> PLAYER_ANIMTYPE_4
        PLAYER_ITEM_CHG_9,  // PLAYER_ANIMTYPE_1 -> PLAYER_ANIMTYPE_5
    },
    {
        PLAYER_ITEM_CHG_3, // PLAYER_ANIMTYPE_2 -> PLAYER_ANIMTYPE_DEFAULT
        PLAYER_ITEM_CHG_1, // PLAYER_ANIMTYPE_2 -> PLAYER_ANIMTYPE_1
        PLAYER_ITEM_CHG_0, // PLAYER_ANIMTYPE_2 -> PLAYER_ANIMTYPE_2
        PLAYER_ITEM_CHG_2, // PLAYER_ANIMTYPE_2 -> PLAYER_ANIMTYPE_3
        PLAYER_ITEM_CHG_3, // PLAYER_ANIMTYPE_2 -> PLAYER_ANIMTYPE_4
        PLAYER_ITEM_CHG_9, // PLAYER_ANIMTYPE_2 -> PLAYER_ANIMTYPE_5
    },
    {
        PLAYER_ITEM_CHG_6,  // PLAYER_ANIMTYPE_3 -> PLAYER_ANIMTYPE_DEFAULT
        -PLAYER_ITEM_CHG_4, // PLAYER_ANIMTYPE_3 -> PLAYER_ANIMTYPE_1
        -PLAYER_ITEM_CHG_2, // PLAYER_ANIMTYPE_3 -> PLAYER_ANIMTYPE_2
        PLAYER_ITEM_CHG_7,  // PLAYER_ANIMTYPE_3 -> PLAYER_ANIMTYPE_3
        PLAYER_ITEM_CHG_6,  // PLAYER_ANIMTYPE_3 -> PLAYER_ANIMTYPE_4
        PLAYER_ITEM_CHG_10, // PLAYER_ANIMTYPE_3 -> PLAYER_ANIMTYPE_5
    },
    {
        PLAYER_ITEM_CHG_8,  // PLAYER_ANIMTYPE_4 -> PLAYER_ANIMTYPE_DEFAULT
        -PLAYER_ITEM_CHG_5, // PLAYER_ANIMTYPE_4 -> PLAYER_ANIMTYPE_1
        -PLAYER_ITEM_CHG_3, // PLAYER_ANIMTYPE_4 -> PLAYER_ANIMTYPE_2
        -PLAYER_ITEM_CHG_6, // PLAYER_ANIMTYPE_4 -> PLAYER_ANIMTYPE_3
        PLAYER_ITEM_CHG_8,  // PLAYER_ANIMTYPE_4 -> PLAYER_ANIMTYPE_4
        PLAYER_ITEM_CHG_11, // PLAYER_ANIMTYPE_4 -> PLAYER_ANIMTYPE_5
    },
    {
        PLAYER_ITEM_CHG_8,  // PLAYER_ANIMTYPE_5 -> PLAYER_ANIMTYPE_DEFAULT
        -PLAYER_ITEM_CHG_5, // PLAYER_ANIMTYPE_5 -> PLAYER_ANIMTYPE_1
        -PLAYER_ITEM_CHG_3, // PLAYER_ANIMTYPE_5 -> PLAYER_ANIMTYPE_2
        -PLAYER_ITEM_CHG_6, // PLAYER_ANIMTYPE_5 -> PLAYER_ANIMTYPE_3
        PLAYER_ITEM_CHG_8,  // PLAYER_ANIMTYPE_5 -> PLAYER_ANIMTYPE_4
        PLAYER_ITEM_CHG_11, // PLAYER_ANIMTYPE_5 -> PLAYER_ANIMTYPE_5
    },
};

ExplosiveInfo sPlayerExplosiveInfo[PLAYER_EXPLOSIVE_MAX] = {
    { ITEM_BOMB, ACTOR_EN_BOM },        // PLAYER_EXPLOSIVE_BOMB
    { ITEM_POWDER_KEG, ACTOR_EN_BOM },  // PLAYER_EXPLOSIVE_POWDER_KEG
    { ITEM_BOMBCHU, ACTOR_EN_BOM_CHU }, // PLAYER_EXPLOSIVE_BOMBCHU
};

void Player_InitItemAction_SpawnExplosive(PlayState* play, Player* this) {
    PlayerExplosive explosiveType;
    ExplosiveInfo* explosiveInfo;
    Actor* explosiveActor;

    if (this->stateFlags1 & PLAYER_STATE1_800) {
        func_8082DE14(play, this);
        return;
    }

    explosiveType = Player_GetExplosiveHeld(this);
    explosiveInfo = &sPlayerExplosiveInfo[explosiveType];
    if ((explosiveType == PLAYER_EXPLOSIVE_POWDER_KEG) && (gSaveContext.powderKegTimer == 0)) {
        gSaveContext.powderKegTimer = 200;
    }

    explosiveActor = Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, explosiveInfo->actorId,
                                        this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                                        (explosiveType == PLAYER_EXPLOSIVE_POWDER_KEG) ? BOMB_EXPLOSIVE_TYPE_POWDER_KEG
                                                                                       : BOMB_EXPLOSIVE_TYPE_BOMB,
                                        this->actor.shape.rot.y, 0, BOMB_TYPE_BODY);
    if (explosiveActor != NULL) {
        if ((explosiveType == PLAYER_EXPLOSIVE_BOMB) && (play->unk_1887E != 0)) {
            play->unk_1887E--;
            if (play->unk_1887E == 0) {
                play->unk_1887E = -1;
            }
        } else if ((explosiveType == PLAYER_EXPLOSIVE_BOMBCHU) && (play->unk_1887D != 0)) {
            play->unk_1887D--;
            if (play->unk_1887D == 0) {
                play->unk_1887D = -1;
            }
        } else {
            Inventory_ChangeAmmo(explosiveInfo->itemId, -1);
        }
        func_8082F5FC(this, explosiveActor);
    } else if (explosiveType == PLAYER_EXPLOSIVE_POWDER_KEG) {
        gSaveContext.powderKegTimer = 0;
    }
}

void Player_InitItemAction_SpawnHookshot(PlayState* play, Player* this) {
    ArmsHook* armsHook;

    this->stateFlags1 |= PLAYER_STATE1_8;
    this->unk_B28 = -3;
    this->unk_B48 = 0.0f;

    this->heldActor =
        Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_ARMS_HOOK, this->actor.world.pos.x,
                           this->actor.world.pos.y, this->actor.world.pos.z, 0, this->actor.shape.rot.y, 0, 0);

    if (this->heldActor == NULL) {
        Player_UseItem(play, this, ITEM_NONE);
        return;
    }
    armsHook = (ArmsHook*)this->heldActor;
    armsHook->actor.objectSlot = this->actor.objectSlot;
    armsHook->unk_208 = this->transformation;
}

void Player_InitItemAction_5(PlayState* play, Player* this) {
    this->stateFlags1 |= PLAYER_STATE1_1000000;
}

void Player_InitItemAction(PlayState* play, Player* this, PlayerItemAction itemAction) {
    this->itemAction = this->heldItemAction = itemAction;
    this->modelGroup = this->nextModelGroup;

    this->stateFlags1 &= ~(PLAYER_STATE1_1000000 | PLAYER_STATE1_8);

    this->unk_B08 = 0.0f;
    this->unk_B0C = 0.0f;
    this->unk_B28 = 0;

    sPlayerItemActionInitFuncs[itemAction](play, this);
    Player_SetModelGroup(this, this->modelGroup);
}

// AttackAnimInfo sMeleeAttackAnimInfo
AttackAnimInfo sMeleeAttackAnimInfo[PLAYER_MWA_MAX] = {
    // PLAYER_MWA_FORWARD_SLASH_1H
    { &gPlayerAnim_link_fighter_normal_kiru, &gPlayerAnim_link_fighter_normal_kiru_end,
      &gPlayerAnim_link_fighter_normal_kiru_endR, 1, 4 },
    // PLAYER_MWA_FORWARD_SLASH_2H
    { &gPlayerAnim_link_fighter_Lnormal_kiru, &gPlayerAnim_link_fighter_Lnormal_kiru_end,
      &gPlayerAnim_link_anchor_Lnormal_kiru_endR, 1, 4 },
    // PLAYER_MWA_FORWARD_COMBO_1H
    { &gPlayerAnim_link_fighter_normal_kiru_finsh, &gPlayerAnim_link_fighter_normal_kiru_finsh_end,
      &gPlayerAnim_link_anchor_normal_kiru_finsh_endR, 0, 5 },
    // PLAYER_MWA_FORWARD_COMBO_2H
    { &gPlayerAnim_link_fighter_Lnormal_kiru_finsh, &gPlayerAnim_link_fighter_Lnormal_kiru_finsh_end,
      &gPlayerAnim_link_anchor_Lnormal_kiru_finsh_endR, 1, 7 },
    // PLAYER_MWA_RIGHT_SLASH_1H
    { &gPlayerAnim_link_fighter_Lside_kiru, &gPlayerAnim_link_fighter_Lside_kiru_end,
      &gPlayerAnim_link_anchor_Lside_kiru_endR, 1, 4 },
    // PLAYER_MWA_RIGHT_SLASH_2H
    { &gPlayerAnim_link_fighter_LLside_kiru, &gPlayerAnim_link_fighter_LLside_kiru_end,
      &gPlayerAnim_link_anchor_LLside_kiru_endL, 0, 5 },
    // PLAYER_MWA_RIGHT_COMBO_1H
    { &gPlayerAnim_link_fighter_Lside_kiru_finsh, &gPlayerAnim_link_fighter_Lside_kiru_finsh_end,
      &gPlayerAnim_link_anchor_Lside_kiru_finsh_endR, 2, 8 },
    // PLAYER_MWA_RIGHT_COMBO_2H
    { &gPlayerAnim_link_fighter_LLside_kiru_finsh, &gPlayerAnim_link_fighter_LLside_kiru_finsh_end,
      &gPlayerAnim_link_anchor_LLside_kiru_finsh_endR, 3, 8 },
    // PLAYER_MWA_LEFT_SLASH_1H
    { &gPlayerAnim_link_fighter_Rside_kiru, &gPlayerAnim_link_fighter_Rside_kiru_end,
      &gPlayerAnim_link_anchor_Rside_kiru_endR, 0, 4 },
    // PLAYER_MWA_LEFT_SLASH_2H
    { &gPlayerAnim_link_fighter_LRside_kiru, &gPlayerAnim_link_fighter_LRside_kiru_end,
      &gPlayerAnim_link_anchor_LRside_kiru_endR, 0, 5 },
    // PLAYER_MWA_LEFT_COMBO_1H
    { &gPlayerAnim_link_fighter_Rside_kiru_finsh, &gPlayerAnim_link_fighter_Rside_kiru_finsh_end,
      &gPlayerAnim_link_anchor_Rside_kiru_finsh_endR, 0, 6 },
    // PLAYER_MWA_LEFT_COMBO_2H
    { &gPlayerAnim_link_fighter_LRside_kiru_finsh, &gPlayerAnim_link_fighter_LRside_kiru_finsh_end,
      &gPlayerAnim_link_anchor_LRside_kiru_finsh_endL, 1, 5 },
    // PLAYER_MWA_STAB_1H
    { &gPlayerAnim_link_fighter_pierce_kiru, &gPlayerAnim_link_fighter_pierce_kiru_end,
      &gPlayerAnim_link_anchor_pierce_kiru_endR, 0, 3 },
    // PLAYER_MWA_STAB_2H
    { &gPlayerAnim_link_fighter_Lpierce_kiru, &gPlayerAnim_link_fighter_Lpierce_kiru_end,
      &gPlayerAnim_link_anchor_Lpierce_kiru_endL, 0, 3 },
    // PLAYER_MWA_STAB_COMBO_1H
    { &gPlayerAnim_link_fighter_pierce_kiru_finsh, &gPlayerAnim_link_fighter_pierce_kiru_finsh_end,
      &gPlayerAnim_link_anchor_pierce_kiru_finsh_endR, 1, 9 },
    // PLAYER_MWA_STAB_COMBO_2H
    { &gPlayerAnim_link_fighter_Lpierce_kiru_finsh, &gPlayerAnim_link_fighter_Lpierce_kiru_finsh_end,
      &gPlayerAnim_link_anchor_Lpierce_kiru_finsh_endR, 1, 8 },
    // PLAYER_MWA_FLIPSLASH_START
    { &gPlayerAnim_link_fighter_jump_rollkiru, &gPlayerAnim_link_fighter_jump_kiru_finsh,
      &gPlayerAnim_link_fighter_jump_kiru_finsh, 7, 99 },
    // PLAYER_MWA_JUMPSLASH_START
    { &gPlayerAnim_link_fighter_Lpower_jump_kiru, &gPlayerAnim_link_fighter_Lpower_jump_kiru_hit,
      &gPlayerAnim_link_fighter_Lpower_jump_kiru_hit, 7, 99 },
    // PLAYER_MWA_ZORA_JUMPKICK_START
    { &gPlayerAnim_pz_jumpAT, &gPlayerAnim_pz_jumpATend, &gPlayerAnim_pz_jumpATend, 8, 99 },
    // PLAYER_MWA_FLIPSLASH_FINISH
    { &gPlayerAnim_link_fighter_jump_kiru_finsh, &gPlayerAnim_link_fighter_jump_kiru_finsh_end,
      &gPlayerAnim_link_fighter_jump_kiru_finsh_end, 1, 2 },
    // PLAYER_MWA_JUMPSLASH_FINISH
    { &gPlayerAnim_link_fighter_Lpower_jump_kiru_hit, &gPlayerAnim_link_fighter_Lpower_jump_kiru_end,
      &gPlayerAnim_link_fighter_Lpower_jump_kiru_end, 1, 2 },
    // PLAYER_MWA_ZORA_JUMPKICK_FINISH
    { &gPlayerAnim_pz_jumpATend, &gPlayerAnim_pz_wait, &gPlayerAnim_link_normal_waitR_free, 1, 2 },
    // PLAYER_MWA_BACKSLASH_RIGHT
    { &gPlayerAnim_link_fighter_turn_kiruR, &gPlayerAnim_link_fighter_turn_kiruR_end,
      &gPlayerAnim_link_fighter_turn_kiruR_end, 1, 5 },
    // PLAYER_MWA_BACKSLASH_LEFT
    { &gPlayerAnim_link_fighter_turn_kiruL, &gPlayerAnim_link_fighter_turn_kiruL_end,
      &gPlayerAnim_link_fighter_turn_kiruL_end, 1, 4 },
    // PLAYER_MWA_GORON_PUNCH_LEFT
    { &gPlayerAnim_pg_punchA, &gPlayerAnim_pg_punchAend, &gPlayerAnim_pg_punchAendR, 6, 8 },
    // PLAYER_MWA_GORON_PUNCH_RIGHT
    { &gPlayerAnim_pg_punchB, &gPlayerAnim_pg_punchBend, &gPlayerAnim_pg_punchBendR, 12, 18 },
    // PLAYER_MWA_GORON_PUNCH_BUTT
    { &gPlayerAnim_pg_punchC, &gPlayerAnim_pg_punchCend, &gPlayerAnim_pg_punchCendR, 8, 14 },
    // PLAYER_MWA_ZORA_PUNCH_LEFT
    { &gPlayerAnim_pz_attackA, &gPlayerAnim_pz_attackAend, &gPlayerAnim_pz_attackAendR, 2, 5 },
    // PLAYER_MWA_ZORA_PUNCH_COMBO
    { &gPlayerAnim_pz_attackB, &gPlayerAnim_pz_attackBend, &gPlayerAnim_pz_attackBendR, 3, 8 },
    // PLAYER_MWA_ZORA_PUNCH_KICK
    { &gPlayerAnim_pz_attackC, &gPlayerAnim_pz_attackCend, &gPlayerAnim_pz_attackCendR, 3, 10 },
    // PLAYER_MWA_SPIN_ATTACK_1H
    { &gPlayerAnim_link_fighter_rolling_kiru, &gPlayerAnim_link_fighter_rolling_kiru_end,
      &gPlayerAnim_link_anchor_rolling_kiru_endR, 0, 12 },
    // PLAYER_MWA_SPIN_ATTACK_2H
    { &gPlayerAnim_link_fighter_Lrolling_kiru, &gPlayerAnim_link_fighter_Lrolling_kiru_end,
      &gPlayerAnim_link_anchor_Lrolling_kiru_endR, 0, 15 },
    // PLAYER_MWA_BIG_SPIN_1H
    { &gPlayerAnim_link_fighter_Wrolling_kiru, &gPlayerAnim_link_fighter_Wrolling_kiru_end,
      &gPlayerAnim_link_anchor_rolling_kiru_endR, 0, 16 },
    // PLAYER_MWA_BIG_SPIN_2H
    { &gPlayerAnim_link_fighter_Wrolling_kiru, &gPlayerAnim_link_fighter_Wrolling_kiru_end,
      &gPlayerAnim_link_anchor_Lrolling_kiru_endR, 0, 16 },
};

PlayerAnimationHeader* D_8085CF50[] = {
    &gPlayerAnim_link_fighter_power_kiru_start,
    &gPlayerAnim_link_fighter_Lpower_kiru_start,
};
PlayerAnimationHeader* D_8085CF58[] = {
    &gPlayerAnim_link_fighter_power_kiru_startL,
    &gPlayerAnim_link_fighter_Lpower_kiru_start,
};
PlayerAnimationHeader* D_8085CF60[] = {
    &gPlayerAnim_link_fighter_power_kiru_wait,
    &gPlayerAnim_link_fighter_Lpower_kiru_wait,
};
PlayerAnimationHeader* D_8085CF68[] = {
    &gPlayerAnim_link_fighter_power_kiru_wait_end,
    &gPlayerAnim_link_fighter_Lpower_kiru_wait_end,
};
PlayerAnimationHeader* D_8085CF70[] = {
    &gPlayerAnim_link_fighter_power_kiru_walk,
    &gPlayerAnim_link_fighter_Lpower_kiru_walk,
};
PlayerAnimationHeader* D_8085CF78[] = {
    &gPlayerAnim_link_fighter_power_kiru_side_walk,
    &gPlayerAnim_link_fighter_Lpower_kiru_side_walk,
};

u8 D_8085CF80[] = {
    PLAYER_MWA_SPIN_ATTACK_1H,
    PLAYER_MWA_SPIN_ATTACK_2H,
};
u8 D_8085CF84[] = {
    PLAYER_MWA_BIG_SPIN_1H,
    PLAYER_MWA_BIG_SPIN_2H,
};

// sBlureColors
BlureColors D_8085CF88[] = {
    { { 255, 255, 255, 255 }, { 255, 255, 255, 64 }, { 255, 255, 255, 0 }, { 255, 255, 255, 0 } },
    { { 165, 185, 255, 185 }, { 205, 225, 255, 50 }, { 255, 255, 255, 0 }, { 255, 255, 255, 0 } },
};

void Player_OverrideBlureColors(PlayState* play, Player* this, s32 colorType, s32 elemDuration) {
    EffectBlure* blure0 = Effect_GetByIndex(this->meleeWeaponEffectIndex[0]);
    EffectBlure* blure1 = Effect_GetByIndex(this->meleeWeaponEffectIndex[1]);
    s32 i;

    for (i = 0; i < 4; i++) {
        blure0->p1StartColor[i] = D_8085CF88[colorType].p1StartColor[i];
        blure0->p2StartColor[i] = D_8085CF88[colorType].p2StartColor[i];
        blure0->p1EndColor[i] = D_8085CF88[colorType].p1EndColor[i];
        blure0->p2EndColor[i] = D_8085CF88[colorType].p2EndColor[i];
        blure1->p1StartColor[i] = D_8085CF88[colorType].p1StartColor[i];
        blure1->p2StartColor[i] = D_8085CF88[colorType].p2StartColor[i];
        blure1->p1EndColor[i] = D_8085CF88[colorType].p1EndColor[i];
        blure1->p2EndColor[i] = D_8085CF88[colorType].p2EndColor[i];
    }

    if (this->transformation == PLAYER_FORM_DEKU) {
        elemDuration = 8;
    }
    blure0->elemDuration = elemDuration;
    blure1->elemDuration = elemDuration;
}

void func_8082FA5C(PlayState* play, Player* this, PlayerMeleeWeaponState meleeWeaponState) {
    u16 voiceSfxId;
    u16 itemSfxId;

    if (this->meleeWeaponState == PLAYER_MELEE_WEAPON_STATE_0) {
        voiceSfxId = NA_SE_VO_LI_SWORD_N;
        if (this->transformation == PLAYER_FORM_GORON) {
            itemSfxId = NA_SE_IT_GORON_PUNCH_SWING;
        } else {
            itemSfxId = NA_SE_NONE;
            if (this->meleeWeaponAnimation >= PLAYER_MWA_SPIN_ATTACK_1H) {
                voiceSfxId = NA_SE_VO_LI_SWORD_L;
            } else if (this->meleeWeaponAnimation == PLAYER_MWA_ZORA_PUNCH_KICK) {
                itemSfxId = NA_SE_IT_GORON_PUNCH_SWING;
            } else {
                itemSfxId = NA_SE_IT_SWORD_SWING_HARD;
                if (this->unk_ADD >= 3) {
                    voiceSfxId = NA_SE_VO_LI_SWORD_L;
                } else {
                    itemSfxId = (this->heldItemAction == PLAYER_IA_SWORD_TWO_HANDED) ? NA_SE_IT_HAMMER_SWING
                                                                                     : NA_SE_IT_SWORD_SWING;
                }
            }
        }

        if (itemSfxId != NA_SE_NONE) {
            func_8082E1F0(this, itemSfxId);
        }

        if (!((this->meleeWeaponAnimation >= PLAYER_MWA_FLIPSLASH_START) &&
              (this->meleeWeaponAnimation <= PLAYER_MWA_ZORA_JUMPKICK_FINISH))) {
            Player_AnimSfx_PlayVoice(this, voiceSfxId);
        }

        Player_OverrideBlureColors(play, this, 0, 4);
    }

    this->meleeWeaponState = meleeWeaponState;
}

s32 func_8082FB68(Player* this) {
    if ((this->lockOnActor != NULL) &&
        CHECK_FLAG_ALL(this->lockOnActor->flags, ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY)) {
        this->stateFlags3 |= PLAYER_STATE3_80000000;
        return true;
    }

    if (this->stateFlags3 & PLAYER_STATE3_80000000) {
        this->stateFlags3 &= ~PLAYER_STATE3_80000000;
        if (this->linearVelocity == 0.0f) {
            this->currentYaw = this->actor.shape.rot.y;
        }
    }

    return false;
}

s32 func_8082FBE8(Player* this) {
    return func_80123420(this) || func_80123434(this);
}

s32 func_8082FC24(Player* this) {
    return func_8082FB68(this) || func_80123434(this);
}

void func_8082FC60(Player* this) {
    this->unk_B44 = 0.0f;
    this->unk_B40 = 0.0f;
}

s32 Player_ItemIsInUse(Player* this, ItemId item) {
    if ((item < ITEM_FD) && (Player_ItemToItemAction(this, item) == this->itemAction)) {
        return true;
    } else {
        return false;
    }
}

s32 Player_ItemIsItemAction(Player* this, ItemId item, PlayerItemAction itemAction) {
    if ((item < ITEM_FD) && (Player_ItemToItemAction(this, item) == itemAction)) {
        return true;
    } else {
        return false;
    }
}

EquipSlot func_8082FD0C(Player* this, PlayerItemAction itemAction) {
    s32 btn;

    for (btn = EQUIP_SLOT_C_LEFT; btn <= EQUIP_SLOT_C_RIGHT; btn++) {
        if (Player_ItemIsItemAction(this, GET_CUR_FORM_BTN_ITEM(btn), itemAction)) {
            return btn;
        }
    }

    return EQUIP_SLOT_NONE;
}

u16 sPlayerItemButtons[] = {
    BTN_B,
    BTN_CLEFT,
    BTN_CDOWN,
    BTN_CRIGHT,
};

// Return currently-pressed button, in order of priority B, CLEFT, CDOWN, CRIGHT.
EquipSlot func_8082FDC4(void) {
    EquipSlot i;

    for (i = 0; i < ARRAY_COUNT(sPlayerItemButtons); i++) {
        if (CHECK_BTN_ALL(sPlayerControlInput->press.button, sPlayerItemButtons[i])) {
            break;
        }
    }

    return i;
}

/**
 * Handles the high level item usage and changing process based on the B and C buttons.
 */
void Player_ProcessItemButtons(Player* this, PlayState* play) {
    if (this->stateFlags1 & (PLAYER_STATE1_800 | PLAYER_STATE1_20000000)) {
        return;
    }
    if (this->stateFlags2 & PLAYER_STATE2_2000000) {
        return;
    }
    if (this->stateFlags3 & PLAYER_STATE3_20000000) {
        return;
    }
    if (func_801240DC(this)) {
        return;
    }

    if (this->transformation == PLAYER_FORM_HUMAN) {
        if (this->currentMask != PLAYER_MASK_NONE) {
            PlayerItemAction maskItemAction = GET_IA_FROM_MASK(this->currentMask);
            EquipSlot btn = func_8082FD0C(this, maskItemAction);

            if (btn <= EQUIP_SLOT_NONE) {
                s32 maskIdMinusOne =
                    GET_MASK_FROM_IA(Player_ItemToItemAction(this, GET_CUR_FORM_BTN_ITEM(this->unk_154))) - 1;

                if ((maskIdMinusOne < PLAYER_MASK_TRUTH - 1) || (maskIdMinusOne >= PLAYER_MASK_MAX - 1)) {
                    maskIdMinusOne = this->currentMask - 1;
                }
                Player_UseItem(play, this, Player_MaskIdToItemId(maskIdMinusOne));
                return;
            }

            if ((this->currentMask == PLAYER_MASK_GIANT) && (gSaveContext.save.saveInfo.playerData.magic == 0)) {
                func_80838A20(play, this);
            }

            this->unk_154 = btn;
        }
    }

    if (((this->actor.id == ACTOR_PLAYER) && (this->itemAction >= PLAYER_IA_FISHING_ROD)) &&
        !(((Player_GetHeldBButtonSword(this) == PLAYER_B_SWORD_NONE) || (gSaveContext.jinxTimer == 0)) &&
          (Player_ItemIsInUse(this, (IREG(1) != 0) ? ITEM_FISHING_ROD : Inventory_GetBtnBItem(play)) ||
           Player_ItemIsInUse(this, C_BTN_ITEM(EQUIP_SLOT_C_LEFT)) ||
           Player_ItemIsInUse(this, C_BTN_ITEM(EQUIP_SLOT_C_DOWN)) ||
           Player_ItemIsInUse(this, C_BTN_ITEM(EQUIP_SLOT_C_RIGHT))))) {
        Player_UseItem(play, this, ITEM_NONE);
    } else {
        s32 pad;
        ItemId item;
        EquipSlot i = func_8082FDC4();

        i = ((i >= EQUIP_SLOT_A) && (this->transformation == PLAYER_FORM_FIERCE_DEITY) &&
             (this->heldItemAction != PLAYER_IA_SWORD_TWO_HANDED))
                ? EQUIP_SLOT_B
                : i;

        item = Player_GetItemOnButton(play, this, i);

        if (item >= ITEM_FD) {
            for (i = 0; i < ARRAY_COUNT(sPlayerItemButtons); i++) {
                if (CHECK_BTN_ALL(sPlayerControlInput->cur.button, sPlayerItemButtons[i])) {
                    break;
                }
            }

            item = Player_GetItemOnButton(play, this, i);
            if ((item < ITEM_FD) && (Player_ItemToItemAction(this, item) == this->heldItemAction)) {
                sPlayerHeldItemButtonIsHeldDown = true;
            }
        } else if (item == ITEM_F0) {
            if (this->blastMaskTimer == 0) {
                EnBom* bomb = (EnBom*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_BOM, this->actor.focus.pos.x,
                                                  this->actor.focus.pos.y, this->actor.focus.pos.z,
                                                  BOMB_EXPLOSIVE_TYPE_BOMB, 0, 0, BOMB_TYPE_BODY);

                if (bomb != NULL) {
                    bomb->timer = 0;
                    this->blastMaskTimer = 310;
                }
            }
        } else if (item == ITEM_F1) {
            func_80839978(play, this);
        } else if (item == ITEM_F2) {
            func_80839A10(play, this);
        } else if ((Player_BButtonSwordFromIA(this, Player_ItemToItemAction(this, item)) != PLAYER_B_SWORD_NONE) &&
                   (gSaveContext.jinxTimer != 0)) {
            if (Message_GetState(&play->msgCtx) == TEXT_STATE_NONE) {
                Message_StartTextbox(play, 0xF7, NULL);
            }
        } else {
            this->heldItemButton = i;
            Player_UseItem(play, this, item);
        }
    }
}

void Player_StartChangingHeldItem(Player* this, PlayState* play) {
    PlayerAnimationHeader* anim;
    s32 pad[3];
    u8 nextModelAnimType;
    s32 itemChangeType;
    s8 heldItemAction = Player_ItemToItemAction(this, this->heldItemId);
    s32 pad3;
    f32 startFrame;
    f32 endFrame;
    f32 frameSpeed;

    Player_SetUpperAction(play, this, Player_UpperAction_ChangeHeldItem);

    nextModelAnimType = gPlayerModelTypes[this->nextModelGroup].modelAnimType;
    itemChangeType = sPlayerItemChangeTypes[gPlayerModelTypes[this->modelGroup].modelAnimType][nextModelAnimType];

    if ((heldItemAction == PLAYER_IA_ZORA_FINS) || (this->heldItemAction == PLAYER_IA_ZORA_FINS)) {
        itemChangeType = (heldItemAction == PLAYER_IA_NONE) ? -PLAYER_ITEM_CHG_14 : PLAYER_ITEM_CHG_14;
    } else if ((heldItemAction == PLAYER_IA_BOTTLE_EMPTY) || (heldItemAction == PLAYER_IA_11) ||
               ((heldItemAction == PLAYER_IA_NONE) &&
                ((this->heldItemAction == PLAYER_IA_BOTTLE_EMPTY) || (this->heldItemAction == PLAYER_IA_11)))) {
        itemChangeType = (heldItemAction == PLAYER_IA_NONE) ? -PLAYER_ITEM_CHG_13 : PLAYER_ITEM_CHG_13;
    }

    this->itemChangeType = ABS_ALT(itemChangeType);
    anim = sPlayerItemChangeInfo[this->itemChangeType].anim;

    if ((anim == &gPlayerAnim_link_normal_fighter2free) && (this->currentShield == PLAYER_SHIELD_NONE)) {
        anim = &gPlayerAnim_link_normal_free2fighter_free;
    }

    endFrame = Animation_GetLastFrame(anim);

    if (itemChangeType >= 0) {
        frameSpeed = 1.2f;
        startFrame = 0.0f;
    } else {
        frameSpeed = -1.2f;
        startFrame = endFrame;
        endFrame = 0.0f;
    }

    if (heldItemAction != PLAYER_IA_NONE) {
        frameSpeed *= 2.0f;
    }

    PlayerAnimation_Change(play, &this->skelAnimeUpper, anim, frameSpeed, startFrame, endFrame, ANIMMODE_ONCE, 0.0f);

    this->stateFlags3 &= ~PLAYER_STATE3_START_CHANGING_HELD_ITEM;
}

void Player_UpdateItems(Player* this, PlayState* play) {
    if ((this->actor.id == ACTOR_PLAYER) && !(this->stateFlags3 & PLAYER_STATE3_START_CHANGING_HELD_ITEM)) {
        if ((this->heldItemAction == this->itemAction) || (this->stateFlags1 & PLAYER_STATE1_400000)) {
            if ((gSaveContext.save.saveInfo.playerData.health != 0) && (play->csCtx.state == CS_STATE_IDLE)) {
                if ((this->csMode == PLAYER_CSMODE_NONE) && (play->unk_1887C == 0) &&
                    (play->activeCamId == CAM_ID_MAIN)) {
                    if (!func_8082DA90(play) && (gSaveContext.timerStates[TIMER_ID_MINIGAME_2] != TIMER_STATE_STOP)) {
                        Player_ProcessItemButtons(this, play);
                    }
                }
            }
        }
    }

    if (this->stateFlags3 & PLAYER_STATE3_START_CHANGING_HELD_ITEM) {
        Player_StartChangingHeldItem(this, play);
    }
}

// EN_ARROW ammo related?
s32 func_808305BC(PlayState* play, Player* this, ItemId* item, ArrowType* typeParam) {
    if (this->heldItemAction == PLAYER_IA_DEKU_NUT) {
        *item = ITEM_DEKU_NUT;
        *typeParam = (this->transformation == PLAYER_FORM_DEKU) ? ARROW_TYPE_DEKU_BUBBLE : ARROW_TYPE_SLINGSHOT;
    } else {
        *item = ITEM_BOW;
        *typeParam = (this->stateFlags1 & PLAYER_STATE1_800000)
                         ? ARROW_TYPE_NORMAL_HORSE
                         : (this->heldItemAction - PLAYER_IA_BOW + ARROW_TYPE_NORMAL);
    }

    if (this->transformation == PLAYER_FORM_DEKU) {
        return ((gSaveContext.save.saveInfo.playerData.magic >= 2) ||
                (CHECK_WEEKEVENTREG(WEEKEVENTREG_08_01) && (play->sceneId == SCENE_BOWLING)))
                   ? 1
                   : 0;
    }
    if (this->stateFlags3 & PLAYER_STATE3_400) {
        return 1;
    }
    if (gSaveContext.minigameStatus == MINIGAME_STATUS_ACTIVE) {
        return play->interfaceCtx.minigameAmmo;
    }
    if (play->unk_1887C != 0) {
        return play->unk_1887C;
    }

    return AMMO(*item);
}

u16 D_8085CFB0[] = {
    NA_SE_PL_BOW_DRAW,
    NA_SE_NONE,
    NA_SE_IT_HOOKSHOT_READY,
};

u8 sMagicArrowCosts[] = {
    4, // ARROW_MAGIC_FIRE
    4, // ARROW_MAGIC_ICE
    8, // ARROW_MAGIC_LIGHT
    2, // ARROW_MAGIC_DEKU_BUBBLE
};

// Draw bow or hookshot / first person items?
s32 func_808306F8(Player* this, PlayState* play) {
    if ((this->heldItemAction >= PLAYER_IA_BOW_FIRE) && (this->heldItemAction <= PLAYER_IA_BOW_LIGHT) &&
        (gSaveContext.magicState != MAGIC_STATE_IDLE)) {
        Audio_PlaySfx(NA_SE_SY_ERROR);
    } else {
        Player_SetUpperAction(play, this, Player_UpperAction_7);

        this->stateFlags3 |= PLAYER_STATE3_40;
        this->unk_ACC = 14;

        if (this->unk_B28 >= 0) {
            s32 var_v1 = ABS_ALT(this->unk_B28);
            ItemId item;
            ArrowType arrowType;
            ArrowMagic magicArrowType;

            if (var_v1 != 2) {
                Player_PlaySfx(this, D_8085CFB0[var_v1 - 1]);
            }

            if (!Player_IsHoldingHookshot(this) && (func_808305BC(play, this, &item, &arrowType) > 0)) {
                if (this->unk_B28 >= 0) {
                    magicArrowType = ARROW_GET_MAGIC_FROM_TYPE(arrowType);

                    if ((ARROW_GET_MAGIC_FROM_TYPE(arrowType) >= ARROW_MAGIC_FIRE) &&
                        (ARROW_GET_MAGIC_FROM_TYPE(arrowType) <= ARROW_MAGIC_LIGHT)) {
                        if (((void)0, gSaveContext.save.saveInfo.playerData.magic) < sMagicArrowCosts[magicArrowType]) {
                            arrowType = ARROW_TYPE_NORMAL;
                            magicArrowType = ARROW_MAGIC_INVALID;
                        }
                    } else if ((arrowType == ARROW_TYPE_DEKU_BUBBLE) &&
                               (!CHECK_WEEKEVENTREG(WEEKEVENTREG_08_01) || (play->sceneId != SCENE_BOWLING))) {
                        magicArrowType = ARROW_MAGIC_DEKU_BUBBLE;
                    } else {
                        magicArrowType = ARROW_MAGIC_INVALID;
                    }

                    this->heldActor = Actor_SpawnAsChild(
                        &play->actorCtx, &this->actor, play, ACTOR_EN_ARROW, this->actor.world.pos.x,
                        this->actor.world.pos.y, this->actor.world.pos.z, 0, this->actor.shape.rot.y, 0, arrowType);

                    if ((this->heldActor != NULL) && (magicArrowType > ARROW_MAGIC_INVALID)) {
                        Magic_Consume(play, sMagicArrowCosts[magicArrowType], MAGIC_CONSUME_NOW);
                    }
                }
            }
        }

        return true;
    }

    return false;
}

void Player_FinishItemChange(PlayState* play, Player* this) {
    s32 isGoronOrDeku = (this->transformation == PLAYER_FORM_GORON) || (this->transformation == PLAYER_FORM_DEKU);

    if ((this->heldItemAction != PLAYER_IA_NONE) && !isGoronOrDeku) {
        if (Player_SwordFromIA(this, this->heldItemAction) > PLAYER_SWORD_NONE) {
            func_8082E1F0(this, NA_SE_IT_SWORD_PUTAWAY);
        } else {
            func_8082E1F0(this, NA_SE_PL_CHANGE_ARMS);
        }
    }

    Player_UseItem(play, this, this->heldItemId);

    if (!isGoronOrDeku) {
        if (Player_SwordFromIA(this, this->heldItemAction) > PLAYER_SWORD_NONE) {
            func_8082E1F0(this, NA_SE_IT_SWORD_PICKOUT);
        } else if (this->heldItemAction != PLAYER_IA_NONE) {
            func_8082E1F0(this, NA_SE_PL_CHANGE_ARMS);
        }
    }
}

void func_808309CC(PlayState* play, Player* this) {
    if (Player_UpperAction_ChangeHeldItem == this->upperActionFunc) {
        Player_FinishItemChange(play, this);
    }

    Player_SetUpperAction(play, this, sPlayerUpperActionUpdateFuncs[this->heldItemAction]);
    this->unk_ACC = 0;
    this->unk_AA4 = 0;
    Player_DetachHeldActor(play, this);
    this->stateFlags3 &= ~PLAYER_STATE3_START_CHANGING_HELD_ITEM;
}

PlayerAnimationHeader* D_8085CFBC[2] = {
    &gPlayerAnim_link_anchor_waitR2defense,
    &gPlayerAnim_link_anchor_waitR2defense_long,
};
PlayerAnimationHeader* D_8085CFC4[2] = {
    &gPlayerAnim_link_anchor_waitL2defense,
    &gPlayerAnim_link_anchor_waitL2defense_long,
};
PlayerAnimationHeader* D_8085CFCC[2] = {
    &gPlayerAnim_link_anchor_defense_hit,
    &gPlayerAnim_link_anchor_defense_long_hitL,
};
PlayerAnimationHeader* D_8085CFD4[2] = {
    &gPlayerAnim_link_anchor_defense_hit,
    &gPlayerAnim_link_anchor_defense_long_hitR,
};
PlayerAnimationHeader* D_8085CFDC[2] = {
    &gPlayerAnim_link_normal_defense_hit,
    &gPlayerAnim_link_fighter_defense_long_hit,
};

PlayerAnimationHeader* func_80830A58(PlayState* play, Player* this) {
    Player_SetUpperAction(play, this, Player_UpperAction_3);
    Player_DetachHeldActor(play, this);

    if (this->unk_B40 < 0.5f) {
        return D_8085CFBC[Player_IsHoldingTwoHandedWeapon(this)];
    } else {
        return D_8085CFC4[Player_IsHoldingTwoHandedWeapon(this)];
    }
}

void func_80830AE8(Player* this) {
    s32 sfxId = (this->transformation == PLAYER_FORM_GORON)
                    ? NA_SE_PL_GORON_SQUAT
                    : ((this->transformation == PLAYER_FORM_DEKU) ? NA_SE_PL_CHANGE_ARMS : NA_SE_IT_SHIELD_SWING);

    Player_PlaySfx(this, sfxId);
}

void func_80830B38(Player* this) {
    s32 sfxId = (this->transformation == PLAYER_FORM_GORON)
                    ? NA_SE_PL_BALL_TO_GORON
                    : ((this->transformation == PLAYER_FORM_DEKU) ? NA_SE_PL_TAKE_OUT_SHIELD : NA_SE_IT_SHIELD_REMOVE);

    Player_PlaySfx(this, sfxId);
}

s32 func_80830B88(PlayState* play, Player* this) {
    if (CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_R)) {
        if (!(this->stateFlags1 & (PLAYER_STATE1_400000 | PLAYER_STATE1_800000 | PLAYER_STATE1_20000000))) {
            if (!(this->stateFlags1 & PLAYER_STATE1_8000000) || ((this->currentBoots >= PLAYER_BOOTS_ZORA_UNDERWATER) &&
                                                                 (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND))) {
                if ((play->unk_1887C == 0) && (this->heldItemAction == this->itemAction)) {
                    if ((this->transformation == PLAYER_FORM_FIERCE_DEITY) ||
                        (!Player_IsGoronOrDeku(this) &&
                         ((((this->transformation == PLAYER_FORM_ZORA)) &&
                           !(this->stateFlags1 & PLAYER_STATE1_2000000)) ||
                          ((this->transformation == PLAYER_FORM_HUMAN) &&
                           (this->currentShield != PLAYER_SHIELD_NONE))) &&
                         func_8082FBE8(this))) {
                        PlayerAnimationHeader* anim = func_80830A58(play, this);
                        f32 endFrame = Animation_GetLastFrame(anim);

                        PlayerAnimation_Change(play, &this->skelAnimeUpper, anim, 3.0f / 3.0f, endFrame, endFrame,
                                               ANIMMODE_ONCE, 0.0f);
                        func_80830AE8(this);
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

void func_80830CE8(PlayState* play, Player* this) {
    Player_SetUpperAction(play, this, Player_UpperAction_5);

    if (this->itemAction <= PLAYER_IA_MINUS1) {
        func_80123C58(this);
    }

    Animation_Reverse(&this->skelAnimeUpper);
    func_80830B38(this);
}

void Player_WaitToFinishItemChange(PlayState* play, Player* this) {
    ItemChangeInfo* itemChangeEntry = &sPlayerItemChangeInfo[this->itemChangeType];
    f32 changeFrame = itemChangeEntry->changeFrame;

    if (this->skelAnimeUpper.playSpeed < 0.0f) {
        changeFrame -= 1.0f;
    }

    if (PlayerAnimation_OnFrame(&this->skelAnimeUpper, changeFrame)) {
        Player_FinishItemChange(play, this);
    }

    func_8082FB68(this);
}

s32 func_80830DF0(Player* this, PlayState* play) {
    if (this->stateFlags3 & PLAYER_STATE3_START_CHANGING_HELD_ITEM) {
        Player_StartChangingHeldItem(this, play);
    } else {
        return false;
    }
    return true;
}

s32 func_80830E30(Player* this, PlayState* play) {
    if ((this->heldItemAction == PLAYER_IA_11) || (this->transformation == PLAYER_FORM_ZORA)) {
        Player_SetUpperAction(play, this, Player_UpperAction_12);

        PlayerAnimation_PlayOnce(play, &this->skelAnimeUpper,
                                 (this->meleeWeaponAnimation == PLAYER_MWA_ZORA_PUNCH_LEFT)
                                     ? &gPlayerAnim_pz_cutterwaitA
                                     : ((this->meleeWeaponAnimation == PLAYER_MWA_ZORA_PUNCH_COMBO)
                                            ? &gPlayerAnim_pz_cutterwaitB
                                            : &gPlayerAnim_pz_cutterwaitC));
        this->unk_ACC = 0xA;
    } else {
        if (!func_808306F8(this, play)) {
            return false;
        }

        PlayerAnimation_PlayOnce(play, &this->skelAnimeUpper,
                                 (Player_IsHoldingHookshot(this))
                                     ? &gPlayerAnim_link_hook_shot_ready
                                     : ((this->transformation == PLAYER_FORM_DEKU) ? &gPlayerAnim_pn_tamahakidf
                                                                                   : &gPlayerAnim_link_bow_bow_ready));
    }

    if (this->stateFlags1 & PLAYER_STATE1_800000) {
        Player_AnimationPlayLoop(play, this, &gPlayerAnim_link_uma_anim_walk);
    } else if ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && (this->transformation != PLAYER_FORM_ZORA)) {
        Player_AnimationPlayLoop(play, this, func_8082ED20(this));
    }

    return true;
}

s32 func_80830F9C(PlayState* play) {
    return (play->unk_1887C > 0) && CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_B);
}

s32 func_80830FD4(PlayState* play) {
    return (play->unk_1887C != 0) &&
           ((play->unk_1887C < 0) || CHECK_BTN_ANY(sPlayerControlInput->cur.button,
                                                   BTN_CRIGHT | BTN_CLEFT | BTN_CDOWN | BTN_CUP | BTN_B | BTN_A));
}

s32 func_80831010(Player* this, PlayState* play) {
    if ((this->unk_AA5 == PLAYER_UNKAA5_0) || (this->unk_AA5 == PLAYER_UNKAA5_3)) {
        if (func_8082FBE8(this) || (this->lockOnActor != NULL) ||
            (Camera_CheckValidMode(Play_GetCamera(play, CAM_ID_MAIN), CAM_MODE_BOWARROW) == 0)) {
            return true;
        }
        this->unk_AA5 = PLAYER_UNKAA5_3;
    }
    return false;
}

s32 func_80831094(Player* this, PlayState* play) {
    if ((this->doorType == PLAYER_DOORTYPE_NONE) && !(this->stateFlags1 & PLAYER_STATE1_2000000)) {
        if (sPlayerUseHeldItem || func_80830F9C(play)) {
            if (func_80830E30(this, play)) {
                return func_80831010(this, play);
            }
        }
    }
    return false;
}

s32 func_80831124(PlayState* play, Player* this) {
    if (this->actor.child != NULL) {
        if (this->heldActor == NULL) {
            this->heldActor = this->actor.child;
            Player_RequestRumble(play, this, 255, 10, 250, SQ(0));
            Player_PlaySfx(this, NA_SE_IT_HOOKSHOT_RECEIVE);
        }
        return true;
    }
    return false;
}

s32 func_80831194(PlayState* play, Player* this) {
    if (this->heldActor != NULL) {
        if (!Player_IsHoldingHookshot(this)) {
            ItemId item;
            ArrowType arrowType;

            func_808305BC(play, this, &item, &arrowType);
            if ((this->transformation != PLAYER_FORM_DEKU) && !(this->stateFlags3 & PLAYER_STATE3_400)) {
                if (gSaveContext.minigameStatus == MINIGAME_STATUS_ACTIVE) {
                    if ((play->sceneId != SCENE_SYATEKI_MIZU) && (play->sceneId != SCENE_F01) &&
                        (play->sceneId != SCENE_SYATEKI_MORI)) {
                        play->interfaceCtx.minigameAmmo--;
                    }
                } else if (play->unk_1887C != 0) {
                    play->unk_1887C--;
                } else {
                    Inventory_ChangeAmmo(item, -1);
                }
            }

            if (play->unk_1887C == 1) {
                play->unk_1887C = -10;
            }

            Player_RequestRumble(play, this, 150, 10, 150, SQ(0));
        } else {
            Player_RequestRumble(play, this, 255, 20, 150, SQ(0));
            this->unk_B48 = 0.0f;
        }

        this->unk_D57 = (this->transformation == PLAYER_FORM_DEKU) ? 20 : 4;

        this->heldActor->parent = NULL;
        this->actor.child = NULL;
        this->heldActor = NULL;
        return true;
    }

    return false;
}

void func_8083133C(Player* this) {
    this->stateFlags1 |= PLAYER_STATE1_20000;

    if (!(this->skelAnime.moveFlags & ANIM_FLAG_80) && (this->actor.bgCheckFlags & BGCHECKFLAG_PLAYER_WALL_INTERACT) &&
        (sPlayerShapeYawToTouchedWall < 0x2000)) {
        this->currentYaw = this->actor.shape.rot.y = this->actor.wallYaw + 0x8000;
    }

    this->targetYaw = this->actor.shape.rot.y;
}

s32 func_808313A8(PlayState* play, Player* this, Actor* actor) {
    if (actor == NULL) {
        func_8082DE50(play, this);
        func_80836988(this, play);
        return true;
    }

    return false;
}

void func_808313F0(Player* this, PlayState* play) {
    if (!func_808313A8(play, this, this->heldActor)) {
        Player_SetUpperAction(play, this, Player_UpperAction_10);
        PlayerAnimation_PlayLoop(play, &this->skelAnimeUpper, &gPlayerAnim_link_normal_carryB_wait);
    }
}

// Stops the current fanfare if a stateflag is set; these two are Kamaro Dancing and Bremen Marching.
void func_80831454(Player* this) {
    if ((this->stateFlags3 & PLAYER_STATE3_20000000) || (this->stateFlags2 & PLAYER_STATE2_2000000)) {
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 0);
    }
}

s32 Player_SetAction(PlayState* play, Player* this, PlayerActionFunc actionFunc, s32 arg3) {
    s32 i;
    f32* ptr;

    if (actionFunc == this->actionFunc) {
        return false;
    }

    play->actorCtx.flags &= ~ACTORCTX_FLAG_PICTO_BOX_ON;

    if (this->actor.flags & ACTOR_FLAG_20000000) {
        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
        this->actor.flags &= ~ACTOR_FLAG_20000000;
    } else if ((Player_Action_96 == this->actionFunc) || (Player_Action_93 == this->actionFunc)) {
        this->actor.shape.shadowDraw = ActorShadow_DrawFeet;
        this->actor.shape.shadowScale = this->ageProperties->shadowScale;
        this->unk_ABC = 0.0f;
        if (Player_Action_96 == this->actionFunc) {
            if (this->stateFlags3 & PLAYER_STATE3_80000) {
                Magic_Reset(play);
            }
            func_8082DD2C(play, this);
            this->actor.shape.rot.x = 0;
            this->actor.shape.rot.z = 0;
            this->actor.bgCheckFlags &= ~BGCHECKFLAG_PLAYER_800;
        } else {
            Actor_SetScale(&this->actor, 0.01f);
        }
    } else if ((this->transformation == PLAYER_FORM_GORON) &&
               (Player_GetMeleeWeaponHeld(this) != PLAYER_MELEEWEAPON_NONE)) {
        Player_UseItem(play, this, ITEM_NONE);
    }

    func_800AEF44(Effect_GetByIndex(this->meleeWeaponEffectIndex[2]));
    this->actionFunc = actionFunc;

    if ((this->itemAction != this->heldItemAction) && (!(arg3 & 1) || !(this->stateFlags1 & PLAYER_STATE1_400000))) {
        func_80123C58(this);
    }

    if (!(arg3 & 1) && !(this->stateFlags1 & PLAYER_STATE1_800)) {
        func_808309CC(play, this);
        PlayerAnimation_PlayLoop(play, &this->skelAnimeUpper, func_8082ED20(this));
        this->stateFlags1 &= ~PLAYER_STATE1_400000;
    }

    func_80831454(this);
    func_8082E794(this);

    this->stateFlags1 &= ~(PLAYER_STATE1_40 | PLAYER_STATE1_4000000 | PLAYER_STATE1_10000000 | PLAYER_STATE1_20000000 |
                           PLAYER_STATE1_80000000);
    this->stateFlags2 &= ~(PLAYER_STATE2_80000 | PLAYER_STATE2_800000 | PLAYER_STATE2_2000000 | PLAYER_STATE2_8000000 |
                           PLAYER_STATE2_10000000);
    this->stateFlags3 &=
        ~(PLAYER_STATE3_2 | PLAYER_STATE3_8 | PLAYER_STATE3_80 | PLAYER_STATE3_200 | PLAYER_STATE3_2000 |
          PLAYER_STATE3_8000 | PLAYER_STATE3_10000 | PLAYER_STATE3_20000 | PLAYER_STATE3_40000 | PLAYER_STATE3_80000 |
          PLAYER_STATE3_200000 | PLAYER_STATE3_1000000 | PLAYER_STATE3_20000000);

    this->actionVar1 = 0;
    this->actionVar2 = 0;
    this->unk_AA4 = 0;
    this->unk_B86[0] = 0;
    this->unk_B86[1] = 0;
    this->unk_B8A = 0;
    this->unk_B8C = 0;
    this->unk_B8E = 0;

    // TODO: Is there no other way to write this that works?
    i = 0;
    ptr = this->unk_B10;
    do {
        *ptr = 0.0f;
        ptr++;
        i++;
    } while (i < ARRAY_COUNT(this->unk_B10));

    this->actor.shape.rot.z = 0;

    Player_ResetCylinder(this);
    func_8082E00C(this);

    return true;
}

void Player_SetAction_PreserveMoveFlags(PlayState* play, Player* this, PlayerActionFunc actionFunc, s32 arg3) {
    s32 moveFlags = this->skelAnime.moveFlags;

    this->skelAnime.moveFlags = 0;
    Player_SetAction(play, this, actionFunc, arg3);
    this->skelAnime.moveFlags = moveFlags;
}

void Player_SetAction_PreserveItemAction(PlayState* play, Player* this, PlayerActionFunc actionFunc, s32 arg3) {
    if (this->itemAction > PLAYER_IA_MINUS1) {
        PlayerItemAction heldItemAction = this->itemAction;

        this->itemAction = this->heldItemAction;
        Player_SetAction(play, this, actionFunc, arg3);
        this->itemAction = heldItemAction;

        Player_SetModels(this, Player_ActionToModelGroup(this, this->itemAction));
    }
}

void Player_DestroyHookshot(Player* this) {
    if (Player_IsHoldingHookshot(this)) {
        if (this->heldActor != NULL) {
            Actor_Kill(this->heldActor);
            this->actor.child = NULL;
            this->heldActor = NULL;
        }
    }
}

s32 func_80831814(Player* this, PlayState* play, PlayerUnkAA5 arg2) {
    if (!(this->stateFlags1 & (PLAYER_STATE1_4 | PLAYER_STATE1_800 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000))) {
        if (Camera_CheckValidMode(Play_GetCamera(play, CAM_ID_MAIN), CAM_MODE_FIRSTPERSON) != 0) {
            if ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) ||
                (func_801242B4(this) && (this->actor.depthInWater < this->ageProperties->unk_2C))) {
                this->unk_AA5 = arg2;
                return true;
            }
        }
    }
    return false;
}

// Toggle Lens
void func_808318C0(PlayState* play) {
    if (Magic_Consume(play, 0, MAGIC_CONSUME_LENS)) {
        if (play->actorCtx.lensActive) {
            Actor_DeactivateLens(play);
        } else {
            play->actorCtx.lensActive = true;
        }

        Audio_PlaySfx(play->actorCtx.lensActive ? NA_SE_SY_GLASSMODE_ON : NA_SE_SY_GLASSMODE_OFF);
    } else {
        Audio_PlaySfx(NA_SE_SY_ERROR);
    }
}

// Toggle Lens from a button press
void func_80831944(PlayState* play, Player* this) {
    if (Player_GetItemOnButton(play, this, func_8082FDC4()) == ITEM_LENS_OF_TRUTH) {
        func_808318C0(play);
    }
}

void Player_UseItem(PlayState* play, Player* this, ItemId item) {
    PlayerItemAction itemAction = Player_ItemToItemAction(this, item);

    if ((((this->heldItemAction == this->itemAction) &&
          (!(this->stateFlags1 & PLAYER_STATE1_400000) ||
           (Player_MeleeWeaponFromIA(itemAction) != PLAYER_MELEEWEAPON_NONE) || (itemAction == PLAYER_IA_NONE))) ||
         ((this->itemAction <= PLAYER_IA_MINUS1) &&
          ((Player_MeleeWeaponFromIA(itemAction) != PLAYER_MELEEWEAPON_NONE) || (itemAction == PLAYER_IA_NONE)))) &&
        ((itemAction == PLAYER_IA_NONE) || !(this->stateFlags1 & PLAYER_STATE1_8000000) ||
         (itemAction == PLAYER_IA_MASK_ZORA) ||
         ((this->currentBoots >= PLAYER_BOOTS_ZORA_UNDERWATER) && (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)))) {
        s32 var_v1 = ((itemAction >= PLAYER_IA_MASK_MIN) && (itemAction <= PLAYER_IA_MASK_MAX) &&
                      ((this->transformation != PLAYER_FORM_HUMAN) || (itemAction >= PLAYER_IA_MASK_GIANT)));
        CollisionPoly* sp5C;
        s32 sp58;
        f32 sp54;
        PlayerExplosive explosiveType;

        if (var_v1 ||
            (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_TALK_REQUESTED) && (itemAction != PLAYER_IA_NONE)) ||
            (itemAction == PLAYER_IA_OCARINA) ||
            ((itemAction > PLAYER_IA_BOTTLE_MIN) && itemAction < PLAYER_IA_MASK_MIN) ||
            ((itemAction == PLAYER_IA_PICTOGRAPH_BOX) && (this->talkActor != NULL) &&
             (this->exchangeItemAction > PLAYER_IA_NONE))) {
            if (var_v1) {
                PlayerTransformation playerForm = (itemAction < PLAYER_IA_MASK_FIERCE_DEITY)
                                                      ? PLAYER_FORM_HUMAN
                                                      : itemAction - PLAYER_IA_MASK_FIERCE_DEITY;

                if (((this->currentMask != PLAYER_MASK_GIANT) && (itemAction == PLAYER_IA_MASK_GIANT) &&
                     ((gSaveContext.magicState != MAGIC_STATE_IDLE) ||
                      (gSaveContext.save.saveInfo.playerData.magic == 0))) ||
                    (!(this->stateFlags1 & PLAYER_STATE1_8000000) &&
                     BgCheck_EntityCheckCeiling(&play->colCtx, &sp54, &this->actor.world.pos,
                                                sPlayerAgeProperties[playerForm].ceilingCheckHeight, &sp5C, &sp58,
                                                &this->actor))) {
                    Audio_PlaySfx(NA_SE_SY_ERROR);
                    return;
                }
            }
            if ((itemAction == PLAYER_IA_MAGIC_BEANS) && (AMMO(ITEM_MAGIC_BEANS) == 0)) {
                Audio_PlaySfx(NA_SE_SY_ERROR);
            } else {
                this->itemAction = itemAction;
                this->unk_AA5 = PLAYER_UNKAA5_5;
            }
        } else if (((itemAction == PLAYER_IA_DEKU_STICK) && (AMMO(ITEM_DEKU_STICK) == 0)) ||
                   (((play->unk_1887D != 0) || (play->unk_1887E != 0)) &&
                    (play->actorCtx.actorLists[ACTORCAT_EXPLOSIVES].length >= 5)) ||
                   ((play->unk_1887D == 0) && (play->unk_1887E == 0) &&
                    ((explosiveType = Player_ExplosiveFromIA(this, itemAction)) > PLAYER_EXPLOSIVE_NONE) &&
                    ((AMMO(sPlayerExplosiveInfo[explosiveType].itemId) == 0) ||
                     (play->actorCtx.actorLists[ACTORCAT_EXPLOSIVES].length >= 3)))) {
            // Prevent some items from being used if player is out of ammo.
            // Also prevent explosives from being used if too many are active
            Audio_PlaySfx(NA_SE_SY_ERROR);
        } else if (itemAction == PLAYER_IA_LENS_OF_TRUTH) {
            // Handle Lens of Truth
            func_808318C0(play);
        } else if (itemAction == PLAYER_IA_PICTOGRAPH_BOX) {
            // Handle Pictograph Box
            if (!func_80831814(this, play, PLAYER_UNKAA5_2)) {
                Audio_PlaySfx(NA_SE_SY_ERROR);
            }
        } else if ((itemAction == PLAYER_IA_DEKU_NUT) &&
                   ((this->transformation != PLAYER_FORM_DEKU) || (this->heldItemButton != 0))) {
            // Handle Deku Nuts
            if (AMMO(ITEM_DEKU_NUT) != 0) {
                func_8083A658(play, this);
            } else {
                Audio_PlaySfx(NA_SE_SY_ERROR);
            }
        } else if ((this->transformation == PLAYER_FORM_HUMAN) && (itemAction >= PLAYER_IA_MASK_MIN) &&
                   (itemAction < PLAYER_IA_MASK_GIANT)) {
            PlayerMask maskId = GET_MASK_FROM_IA(itemAction);

            // Handle wearable masks
            this->prevMask = this->currentMask;
            if (maskId == this->currentMask) {
                this->currentMask = PLAYER_MASK_NONE;
                func_8082E1F0(this, NA_SE_PL_TAKE_OUT_SHIELD);
            } else {
                this->currentMask = maskId;
                func_8082E1F0(this, NA_SE_PL_CHANGE_ARMS);
            }
            gSaveContext.save.equippedMask = this->currentMask;
        } else if ((itemAction != this->heldItemAction) ||
                   ((this->heldActor == NULL) && (Player_ExplosiveFromIA(this, itemAction) > PLAYER_EXPLOSIVE_NONE))) {
            u8 nextAnimType;

            // Handle using a new held item
            this->nextModelGroup = Player_ActionToModelGroup(this, itemAction);
            nextAnimType = gPlayerModelTypes[this->nextModelGroup].modelAnimType;
            var_v1 = ((this->transformation != PLAYER_FORM_GORON) || (itemAction == PLAYER_IA_POWDER_KEG));

            if (var_v1 && (this->heldItemAction >= 0) && (item != this->heldItemId) &&
                (sPlayerItemChangeTypes[gPlayerModelTypes[this->modelGroup].modelAnimType][nextAnimType] !=
                 PLAYER_ITEM_CHG_0)) {
                // Start the held item change process
                this->heldItemId = item;
                this->stateFlags3 |= PLAYER_STATE3_START_CHANGING_HELD_ITEM;
            } else {
                // Init new held item for use
                Player_DestroyHookshot(this);
                Player_DetachHeldActor(play, this);
                Player_InitItemActionWithAnim(play, this, itemAction);
                if (!var_v1) {
                    sPlayerUseHeldItem = true;
                    sPlayerHeldItemButtonIsHeldDown = true;
                }
            }
        } else {
            sPlayerUseHeldItem = true;
            sPlayerHeldItemButtonIsHeldDown = true;
        }
    }
}

void func_80831F34(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    s32 sp24 = func_801242B4(this);

    func_8082DE50(play, this);
    Player_SetAction(play, this, sp24 ? Player_Action_62 : Player_Action_24, 0);
    Player_AnimationPlayOnce(play, this, anim);

    if (anim == &gPlayerAnim_link_derth_rebirth) {
        this->skelAnime.endFrame = 84.0f;
    }

    this->stateFlags1 |= PLAYER_STATE1_80;

    func_8082DAD4(this);
    Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_DOWN);

    if (this == GET_PLAYER(play)) {
        this->csId = play->playerCsIds[PLAYER_CS_ID_DEATH];
        Audio_SetBgmVolumeOff();
        gSaveContext.powderKegTimer = 0;
        gSaveContext.unk_1014 = 0;
        gSaveContext.jinxTimer = 0;

        if (Inventory_ConsumeFairy(play)) {
            play->gameOverCtx.state = GAMEOVER_REVIVE_START;
            this->actionVar1 = 1;
        } else {
            play->gameOverCtx.state = GAMEOVER_DEATH_START;
            func_801A41F8(0);
            Audio_PlayFanfare(NA_BGM_GAME_OVER);
            gSaveContext.seqId = (u8)NA_BGM_DISABLED;
            gSaveContext.ambienceId = AMBIENCE_ID_DISABLED;
        }

        ShrinkWindow_Letterbox_SetSizeTarget(32);
    }
}

s32 Player_CanUpdateItems(Player* this) {
    return (!(Player_Action_34 == this->actionFunc) ||
            ((this->stateFlags3 & PLAYER_STATE3_START_CHANGING_HELD_ITEM) &&
             ((this->heldItemId == ITEM_FC) || (this->heldItemId == ITEM_NONE)))) &&
           (!(Player_UpperAction_ChangeHeldItem == this->upperActionFunc) ||
            Player_ItemToItemAction(this, this->heldItemId) == this->heldItemAction);
}

// Whether action is Bremen marching or Kamaro dancing
s32 func_8083213C(Player* this) {
    return (Player_Action_11 == this->actionFunc) || (Player_Action_12 == this->actionFunc);
}

s32 Player_UpdateUpperBody(Player* this, PlayState* play) {
    if (!(this->stateFlags1 & PLAYER_STATE1_800000) && (this->actor.parent != NULL) && Player_IsHoldingHookshot(this)) {
        Player_SetAction(play, this, Player_Action_92, 1);
        this->stateFlags3 |= PLAYER_STATE3_80;
        Player_AnimationPlayOnce(play, this, &gPlayerAnim_link_hook_fly_start);
        func_8082E920(play, this, (ANIM_FLAG_1 | ANIM_FLAG_UPDATE_Y | ANIM_FLAG_8 | ANIM_FLAG_NOMOVE | ANIM_FLAG_80));
        func_8082DAD4(this);
        this->currentYaw = this->actor.shape.rot.y;
        this->actor.bgCheckFlags &= ~BGCHECKFLAG_GROUND;
        this->unk_AA6 |= 0x43;
        Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_LASH);
        return true;
    }

    if (Player_CanUpdateItems(this)) {
        Player_UpdateItems(this, play);
        if (Player_Action_64 == this->actionFunc) {
            return true;
        }
    }

    if (!this->upperActionFunc(this, play)) {
        return false;
    }

    if (this->skelAnimeUpperBlendWeight != 0.0f) {
        if ((func_8082ED94(this) == 0) || (this->linearVelocity != 0.0f)) {
            AnimationContext_SetCopyFalse(play, this->skelAnime.limbCount, this->skelAnimeUpper.jointTable,
                                          this->skelAnime.jointTable, sPlayerUpperBodyLimbCopyMap);
        }
        if ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && !(this->skelAnime.moveFlags & ANIM_FLAG_8)) {
            Math_StepToF(&this->skelAnimeUpperBlendWeight, 0.0f, 0.25f);
            AnimationContext_SetInterp(play, this->skelAnime.limbCount, this->skelAnime.jointTable,
                                       this->skelAnimeUpper.jointTable, 1.0f - this->skelAnimeUpperBlendWeight);
        }
    } else if ((func_8082ED94(this) == 0) || (this->linearVelocity != 0.0f) ||
               (this->skelAnime.moveFlags & ANIM_FLAG_8)) {
        AnimationContext_SetCopyTrue(play, this->skelAnime.limbCount, this->skelAnime.jointTable,
                                     this->skelAnimeUpper.jointTable, sPlayerUpperBodyLimbCopyMap);
    } else {
        AnimationContext_SetCopyAll(play, this->skelAnime.limbCount, this->skelAnime.jointTable,
                                    this->skelAnimeUpper.jointTable);
    }

    return true;
}

s32 func_808323C0(Player* this, s16 csId) {
    if ((csId > CS_ID_NONE) && (CutsceneManager_GetCurrentCsId() != csId)) {
        if (!CutsceneManager_IsNext(csId)) {
            CutsceneManager_Queue(csId);

            return false;
        }
        CutsceneManager_Start(csId, &this->actor);
    }
    this->csId = csId;

    return true;
}

s32 func_80832444(Player* this) {
    if (this->csId > CS_ID_NONE) {
        if (!CutsceneManager_IsNext(this->csId)) {
            CutsceneManager_Queue(this->csId);
            return false;
        }

        CutsceneManager_Start(this->csId, &this->actor);
    }
    return true;
}

s32 func_8083249C(Player* this) {
    if ((this->csId > CS_ID_NONE) && (CutsceneManager_GetCurrentCsId() != this->csId)) {
        return func_80832444(this);
    }
    return true;
}

s32 func_808324EC(PlayState* play, Player* this, PlayerFuncD58 arg2, s32 csId) {
    this->unk_D58 = arg2;
    this->csId = csId;
    Player_SetAction(play, this, Player_Action_34, 0);
    func_8083249C(this);
    this->stateFlags2 |= PLAYER_STATE2_40;
    return func_8082DE14(play, this);
}

s32 func_80832558(PlayState* play, Player* this, PlayerFuncD58 arg2) {
    return func_808324EC(play, this, arg2, CS_ID_NONE);
}

// To do with turning, related to targeting
void func_80832578(Player* this, PlayState* play) {
    s16 previousYaw = this->actor.shape.rot.y;

    if (!(this->stateFlags2 & (PLAYER_STATE2_20 | PLAYER_STATE2_40))) {
        Actor* lockOnActor = this->lockOnActor;

        if ((lockOnActor != NULL) && ((play->actorCtx.targetCtx.rotZTick != 0) || (this != GET_PLAYER(play))) &&
            (lockOnActor->id != ACTOR_OBJ_NOZOKI)) {
            Math_ScaledStepToS(&this->actor.shape.rot.y,
                               Math_Vec3f_Yaw(&this->actor.world.pos, &lockOnActor->focus.pos), 0xFA0);
        } else if ((this->stateFlags1 & PLAYER_STATE1_20000) &&
                   !(this->stateFlags2 & (PLAYER_STATE2_20 | PLAYER_STATE2_40))) {
            Math_ScaledStepToS(&this->actor.shape.rot.y, this->targetYaw, 0xFA0);
        }
    } else if (!(this->stateFlags2 & PLAYER_STATE2_40)) {
        Math_ScaledStepToS(&this->actor.shape.rot.y, this->currentYaw, 0x7D0);
    }

    this->unk_B4C = this->actor.shape.rot.y - previousYaw;
}

s16 func_80832660(s16* pValue, s16 target, s16 step, s16 arg3, s16 arg4, s16 arg5) {
    s16 temp1;
    s16 temp2;
    s16 temp3;

    temp1 = temp2 = arg4 - *pValue;
    temp2 = CLAMP(temp2, -arg5, arg5);
    *pValue += BINANG_SUB(temp1, temp2);

    Math_ScaledStepToS(pValue, target, step);

    temp3 = *pValue;
    if (*pValue < -arg3) {
        *pValue = -arg3;
    } else if (arg3 < *pValue) {
        *pValue = arg3;
    }
    return temp3 - *pValue;
}

s16 func_80832754(Player* this, s32 arg1) {
    s16 sp36;
    s16 var_s1 = this->actor.shape.rot.y;

    if (arg1) {
        this->upperLimbRot.x = this->actor.focus.rot.x;
        var_s1 = this->actor.focus.rot.y;
        this->unk_AA6 |= 0x41;
    } else {
        s16 temp =
            func_80832660(&this->headLimbRot.x, this->actor.focus.rot.x, 0x258, 0x2710, this->actor.focus.rot.x, 0);

        func_80832660(&this->upperLimbRot.x, temp, 0xC8, 0xFA0, this->headLimbRot.x, 0x2710);

        sp36 = this->actor.focus.rot.y - var_s1;
        func_80832660(&sp36, 0, 0xC8, 0x5DC0, this->upperLimbRot.y, 0x1F40);
        var_s1 = this->actor.focus.rot.y - sp36;
        func_80832660(&this->headLimbRot.y, (sp36 - this->upperLimbRot.y), 0xC8, 0x1F40, sp36, 0x1F40);
        func_80832660(&this->upperLimbRot.y, sp36, 0xC8, 0x1F40, this->headLimbRot.y, 0x1F40);
        this->unk_AA6 |= 0xD9;
    }

    return var_s1;
}

void func_80832888(Player* this, PlayState* play) {
    s32 ignoreLeash = false;
    Actor* var_v1_2;
    s32 heldZ = CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_Z);
    s32 temp_v0_3;
    s32 var_a1;

    if (!heldZ) {
        this->stateFlags1 &= ~PLAYER_STATE1_40000000;
    }

    if ((play->csCtx.state != CS_STATE_IDLE) || (this->csMode != PLAYER_CSMODE_NONE) ||
        (this->stateFlags1 & (PLAYER_STATE1_80 | PLAYER_STATE1_20000000)) || (this->stateFlags3 & PLAYER_STATE3_80)) {
        this->unk_738 = 0;
    } else if (heldZ || (this->stateFlags2 & PLAYER_STATE2_2000) || (this->unk_A78 != NULL)) {
        if (this->unk_738 <= 5) {
            this->unk_738 = 5;
        } else {
            this->unk_738--;
        }
    } else if (this->stateFlags1 & PLAYER_STATE1_20000) {
        this->unk_738 = 0;
    } else if (this->unk_738 != 0) {
        this->unk_738--;
    }

    if (this->unk_738 > 5) {
        ignoreLeash = true;
    }

    temp_v0_3 = func_8082DAFC(play);
    if (temp_v0_3 || (this->unk_738 != 0) || (this->stateFlags1 & (PLAYER_STATE1_1000 | PLAYER_STATE1_2000000))) {
        if (!temp_v0_3) {
            if (!(this->stateFlags1 & PLAYER_STATE1_2000000) &&
                ((this->heldItemAction != PLAYER_IA_FISHING_ROD) || (this->unk_B28 == 0)) &&
                CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_Z)) {
                var_v1_2 = (this == GET_PLAYER(play)) ? play->actorCtx.targetCtx.fairyActor : &GET_PLAYER(play)->actor;
                var_a1 = (gSaveContext.options.zTargetSetting != 0) || (this != GET_PLAYER(play));
                this->stateFlags1 |= PLAYER_STATE1_8000;
                if ((this->currentMask != PLAYER_MASK_GIANT) && (var_v1_2 != NULL) &&
                    !(var_v1_2->flags & ACTOR_FLAG_CANT_LOCK_ON) &&
                    !(this->stateFlags3 & (PLAYER_STATE3_200 | PLAYER_STATE3_2000))) {
                    if ((var_v1_2 == this->lockOnActor) && (this == GET_PLAYER(play))) {
                        var_v1_2 = play->actorCtx.targetCtx.arrowPointedActor;
                    }

                    if ((var_v1_2 != NULL) &&
                        (((var_v1_2 != this->lockOnActor)) || (var_v1_2->flags & ACTOR_FLAG_80000))) {
                        var_v1_2->flags &= ~ACTOR_FLAG_80000;
                        if (!var_a1) {
                            this->stateFlags2 |= PLAYER_STATE2_2000;
                        }
                        this->lockOnActor = var_v1_2;
                        this->unk_738 = 0xF;
                        this->stateFlags2 &= ~(PLAYER_STATE2_2 | PLAYER_STATE2_200000);
                    } else if (!var_a1) {
                        Player_Untarget(this);
                    }
                    this->stateFlags1 &= ~PLAYER_STATE1_40000000;
                } else if (!(this->stateFlags1 & (PLAYER_STATE1_20000 | PLAYER_STATE1_40000000)) &&
                           (Player_Action_95 != this->actionFunc)) {
                    func_8083133C(this);
                }
            }

            if (this->lockOnActor != NULL) {
                if ((this == GET_PLAYER(play)) && (this->lockOnActor != this->unk_A78) &&
                    Target_OutsideLeashRange(this->lockOnActor, this, ignoreLeash)) {
                    Player_Untarget(this);
                    this->stateFlags1 |= PLAYER_STATE1_40000000;
                } else if (this->lockOnActor != NULL) {
                    this->lockOnActor->targetPriority = 0x28;
                }
            } else if (this->unk_A78 != NULL) {
                this->lockOnActor = this->unk_A78;
            }
        }

        if ((this->lockOnActor != NULL) && !(this->stateFlags3 & (PLAYER_STATE3_200 | PLAYER_STATE3_2000))) {
            this->stateFlags1 &= ~(PLAYER_STATE1_10000 | PLAYER_STATE1_20000);
            if ((this->stateFlags1 & PLAYER_STATE1_800) ||
                !CHECK_FLAG_ALL(this->lockOnActor->flags, ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY)) {
                this->stateFlags1 |= PLAYER_STATE1_10000;
            }
        } else if (this->stateFlags1 & PLAYER_STATE1_20000) {
            this->stateFlags2 &= ~PLAYER_STATE2_2000;
        } else {
            func_80123DC0(this);
        }
    } else {
        func_80123DC0(this);
    }
}

/**
 * These defines exist to simplify the variable used to toggle the different speed modes.
 * While the `speedMode` variable is a float and can contain a non-boolean value,
 * `Player_CalcSpeedAndYawFromControlStick` never actually uses the value for anything.
 * It simply checks if the value is non-zero to toggle the "curved" mode.
 * In practice, 0.0f or 0.018f are the only values passed to this function.
 *
 * It's clear that this value was intended to mean something in the curved mode calculation at
 * some point in development, but was either never implemented or removed.
 *
 * To see the difference between linear and curved mode, with interactive toggles for
 * speed cap and floor pitch, see the following desmos graph: https://www.desmos.com/calculator/hri7dcws4c
 */

// Linear mode is a straight line, increasing target speed at a steady rate relative to the control stick magnitude
#define SPEED_MODE_LINEAR 0.0f

// Curved mode drops any input below 20 units of magnitude, resulting in zero for target speed.
// Beyond 20 units, a gradual curve slowly moves up until around the 40 unit mark
// when target speed ramps up very quickly.
#define SPEED_MODE_CURVED 0.018f

/**
 * Calculates target speed and yaw based on input from the control stick.
 * See `Player_GetMovementSpeedAndYaw` for detailed argument descriptions.
 *
 * @return true if the control stick has any magnitude, false otherwise.
 */
s32 Player_CalcSpeedAndYawFromControlStick(PlayState* play, Player* this, f32* outSpeedTarget, s16* outYawTarget,
                                           f32 speedMode) {
    f32 temp;

    if ((this->unk_AA5 != PLAYER_UNKAA5_0) || func_8082DA90(play) || (this->stateFlags1 & PLAYER_STATE1_1)) {
        *outSpeedTarget = 0.0f;
        *outYawTarget = this->actor.shape.rot.y;
    } else {
        *outSpeedTarget = sPlayerControlStickMagnitude;
        *outYawTarget = sPlayerControlStickAngle;

        // The value of `speedMode` is never actually used. It only toggles this condition.
        // See the definition of `SPEED_MODE_LINEAR` and `SPEED_MODE_CURVED` for more information.
        if (speedMode != SPEED_MODE_LINEAR) {
            *outSpeedTarget -= 20.0f;

            if (*outSpeedTarget < 0.0f) {
                // If control stick magnitude is below 20, return zero speed.
                *outSpeedTarget = 0.0f;
            } else {
                // Cosine of the control stick magnitude isn't exactly meaningful, but
                // it happens to give a desirable curve for grounded movement speed relative
                // to control stick magnitude.
                temp = 1.0f - Math_CosS(*outSpeedTarget * 450.0f);
                *outSpeedTarget = (SQ(temp) * 30.0f) + 7.0f;
            }
        } else {
            // Speed increases linearly relative to control stick magnitude
            *outSpeedTarget *= 0.8f;
        }

        if (this->transformation == PLAYER_FORM_FIERCE_DEITY) {
            *outSpeedTarget *= 1.5f;
        }

        if (sPlayerControlStickMagnitude != 0.0f) {
            f32 floorPitchInfluence = Math_SinS(this->floorPitch);
            f32 speedCap = this->unk_B50;
            f32 var_fa1;

            if (this->unk_AB8 != 0.0f) {
                var_fa1 = (this->lockOnActor != NULL) ? 0.002f : 0.008f;

                speedCap -= this->unk_AB8 * var_fa1;
                speedCap = CLAMP_MIN(speedCap, 2.0f);
            }

            *outSpeedTarget = (*outSpeedTarget * 0.14f) - (8.0f * floorPitchInfluence * floorPitchInfluence);
            *outSpeedTarget = CLAMP(*outSpeedTarget, 0.0f, speedCap);

            //! FAKE
            if (floorPitchInfluence) {}

            return true;
        }
    }

    return false;
}

s32 func_80832F24(Player* this) {
    return Math_StepToF(&this->linearVelocity, 0.0f, REG(43) / 100.0f);
}

/**
 * Gets target speed and yaw values for movement based on control stick input.
 * Control stick magnitude and angle are processed in `Player_CalcSpeedAndYawFromControlStick` to get target values.
 * Additionally, this function does extra processing on the target yaw value if the control stick is neutral.
 *
 * @param outSpeedTarget  a pointer to the variable that will hold the resulting target speed value
 * @param outYawTarget    a pointer to the variable that will hold the resulting target yaw value
 * @param speedMode       toggles between a linear and curved mode for the speed value
 *
 * @see Player_CalcSpeedAndYawFromControlStick for more information on the linear vs curved speed mode.
 *
 * @return true if the control stick has any magnitude, false otherwise.
 */
s32 Player_GetMovementSpeedAndYaw(Player* this, f32* outSpeedTarget, s16* outYawTarget, f32 speedMode,
                                  PlayState* play) {
    if (!Player_CalcSpeedAndYawFromControlStick(play, this, outSpeedTarget, outYawTarget, speedMode)) {
        *outYawTarget = this->actor.shape.rot.y;

        if (this->lockOnActor != NULL) {
            if ((play->actorCtx.targetCtx.rotZTick != 0) && !(this->stateFlags2 & PLAYER_STATE2_40)) {
                *outYawTarget = Math_Vec3f_Yaw(&this->actor.world.pos, &this->lockOnActor->focus.pos);
            }
        } else if (func_80123434(this)) {
            *outYawTarget = this->targetYaw;
        }

        return false;
    }

    *outYawTarget += Camera_GetInputDirYaw(GET_ACTIVE_CAM(play));
    return true;
}

typedef enum ActionChangeIndex {
    /* 0x0 */ PLAYER_ACTION_CHG_0,
    /* 0x1 */ PLAYER_ACTION_CHG_1,
    /* 0x2 */ PLAYER_ACTION_CHG_2,
    /* 0x3 */ PLAYER_ACTION_CHG_3,
    /* 0x4 */ PLAYER_ACTION_CHG_4,
    /* 0x5 */ PLAYER_ACTION_CHG_5,
    /* 0x6 */ PLAYER_ACTION_CHG_6,
    /* 0x7 */ PLAYER_ACTION_CHG_7,
    /* 0x8 */ PLAYER_ACTION_CHG_8,
    /* 0x9 */ PLAYER_ACTION_CHG_9,
    /* 0xA */ PLAYER_ACTION_CHG_10,
    /* 0xB */ PLAYER_ACTION_CHG_11,
    /* 0xC */ PLAYER_ACTION_CHG_12,
    /* 0xD */ PLAYER_ACTION_CHG_13,
    /* 0xE */ PLAYER_ACTION_CHG_14,
    /* 0xF */ PLAYER_ACTION_CHG_MAX
} ActionChangeIndex;

/**
 * The values of following arrays are used as indices for the `sPlayerActionChangeFuncs` array.
 * Each index correspond to a function which will be called sequentially until any of them return `true`.
 * Negative marks the end of the array.
 */
s8 sPlayerActionChangeList1[] = {
    /* 0 */ PLAYER_ACTION_CHG_13,
    /* 1 */ PLAYER_ACTION_CHG_2,
    /* 2 */ PLAYER_ACTION_CHG_4,
    /* 3 */ PLAYER_ACTION_CHG_9,
    /* 4 */ PLAYER_ACTION_CHG_10,
    /* 5 */ PLAYER_ACTION_CHG_11,
    /* 6 */ PLAYER_ACTION_CHG_8,
    /* 7 */ -PLAYER_ACTION_CHG_7,
};

s8 sPlayerActionChangeList2[] = {
    /*  0 */ PLAYER_ACTION_CHG_13,
    /*  1 */ PLAYER_ACTION_CHG_1,
    /*  2 */ PLAYER_ACTION_CHG_2,
    /*  3 */ PLAYER_ACTION_CHG_5,
    /*  4 */ PLAYER_ACTION_CHG_3,
    /*  5 */ PLAYER_ACTION_CHG_4,
    /*  6 */ PLAYER_ACTION_CHG_9,
    /*  7 */ PLAYER_ACTION_CHG_10,
    /*  8 */ PLAYER_ACTION_CHG_11,
    /*  9 */ PLAYER_ACTION_CHG_7,
    /* 10 */ PLAYER_ACTION_CHG_8,
    /* 11 */ -PLAYER_ACTION_CHG_6,
};

s8 sPlayerActionChangeList3[] = {
    /*  0 */ PLAYER_ACTION_CHG_13,
    /*  1 */ PLAYER_ACTION_CHG_1,
    /*  2 */ PLAYER_ACTION_CHG_2,
    /*  3 */ PLAYER_ACTION_CHG_3,
    /*  4 */ PLAYER_ACTION_CHG_4,
    /*  5 */ PLAYER_ACTION_CHG_9,
    /*  6 */ PLAYER_ACTION_CHG_10,
    /*  7 */ PLAYER_ACTION_CHG_11,
    /*  8 */ PLAYER_ACTION_CHG_8,
    /*  9 */ PLAYER_ACTION_CHG_7,
    /* 10 */ -PLAYER_ACTION_CHG_6,
};

s8 sPlayerActionChangeList4[] = {
    /* 0 */ PLAYER_ACTION_CHG_13,
    /* 1 */ PLAYER_ACTION_CHG_2,
    /* 2 */ PLAYER_ACTION_CHG_4,
    /* 3 */ PLAYER_ACTION_CHG_9,
    /* 4 */ PLAYER_ACTION_CHG_10,
    /* 5 */ PLAYER_ACTION_CHG_11,
    /* 6 */ PLAYER_ACTION_CHG_8,
    /* 7 */ -PLAYER_ACTION_CHG_7,
};

s8 sPlayerActionChangeList5[] = {
    /* 0 */ PLAYER_ACTION_CHG_13,
    /* 1 */ PLAYER_ACTION_CHG_2,
    /* 2 */ PLAYER_ACTION_CHG_4,
    /* 3 */ PLAYER_ACTION_CHG_9,
    /* 4 */ PLAYER_ACTION_CHG_10,
    /* 5 */ PLAYER_ACTION_CHG_11,
    /* 6 */ PLAYER_ACTION_CHG_12,
    /* 7 */ PLAYER_ACTION_CHG_8,
    /* 8 */ -PLAYER_ACTION_CHG_7,
};

s8 sPlayerActionChangeList6[] = {
    /* 0 */ -PLAYER_ACTION_CHG_7,
};

s8 sPlayerActionChangeList7[] = {
    /*  0 */ PLAYER_ACTION_CHG_0,
    /*  1 */ PLAYER_ACTION_CHG_11,
    /*  2 */ PLAYER_ACTION_CHG_1,
    /*  3 */ PLAYER_ACTION_CHG_2,
    /*  4 */ PLAYER_ACTION_CHG_3,
    /*  5 */ PLAYER_ACTION_CHG_5,
    /*  6 */ PLAYER_ACTION_CHG_4,
    /*  7 */ PLAYER_ACTION_CHG_9,
    /*  8 */ PLAYER_ACTION_CHG_8,
    /*  9 */ PLAYER_ACTION_CHG_7,
    /* 10 */ -PLAYER_ACTION_CHG_6,
};

s8 sPlayerActionChangeList8[] = {
    /*  0 */ PLAYER_ACTION_CHG_0,
    /*  1 */ PLAYER_ACTION_CHG_11,
    /*  2 */ PLAYER_ACTION_CHG_1,
    /*  3 */ PLAYER_ACTION_CHG_2,
    /*  4 */ PLAYER_ACTION_CHG_3,
    /*  5 */ PLAYER_ACTION_CHG_12,
    /*  6 */ PLAYER_ACTION_CHG_5,
    /*  7 */ PLAYER_ACTION_CHG_4,
    /*  8 */ PLAYER_ACTION_CHG_9,
    /*  9 */ PLAYER_ACTION_CHG_8,
    /* 10 */ PLAYER_ACTION_CHG_7,
    /* 11 */ -PLAYER_ACTION_CHG_6,
};

s8 sPlayerActionChangeList9[] = {
    /*  0 */ PLAYER_ACTION_CHG_13,
    /*  1 */ PLAYER_ACTION_CHG_1,
    /*  2 */ PLAYER_ACTION_CHG_2,
    /*  3 */ PLAYER_ACTION_CHG_3,
    /*  4 */ PLAYER_ACTION_CHG_12,
    /*  5 */ PLAYER_ACTION_CHG_5,
    /*  6 */ PLAYER_ACTION_CHG_4,
    /*  7 */ PLAYER_ACTION_CHG_9,
    /*  8 */ PLAYER_ACTION_CHG_10,
    /*  9 */ PLAYER_ACTION_CHG_11,
    /* 10 */ PLAYER_ACTION_CHG_8,
    /* 11 */ PLAYER_ACTION_CHG_7,
    /* 12 */ -PLAYER_ACTION_CHG_6,
};

s8 sPlayerActionChangeList10[] = {
    /* 0 */ PLAYER_ACTION_CHG_10,
    /* 1 */ PLAYER_ACTION_CHG_8,
    /* 2 */ -PLAYER_ACTION_CHG_7,
};

s8 sPlayerActionChangeList11[] = {
    /* 0 */ PLAYER_ACTION_CHG_0,
    /* 1 */ PLAYER_ACTION_CHG_12,
    /* 2 */ PLAYER_ACTION_CHG_5,
    /* 3 */ PLAYER_ACTION_CHG_4,
    /* 4 */ -PLAYER_ACTION_CHG_14,
};

s8 sPlayerActionChangeList12[] = {
    /* 0 */ PLAYER_ACTION_CHG_13,
    /* 1 */ PLAYER_ACTION_CHG_2,
    /* 2 */ -PLAYER_ACTION_CHG_4,
};

s32 (*sPlayerActionChangeFuncs[PLAYER_ACTION_CHG_MAX])(Player*, PlayState*) = {
    Player_ActionChange_0,  // PLAYER_ACTION_CHG_0
    Player_ActionChange_1,  // PLAYER_ACTION_CHG_1
    Player_ActionChange_2,  // PLAYER_ACTION_CHG_2
    Player_ActionChange_3,  // PLAYER_ACTION_CHG_3
    Player_ActionChange_4,  // PLAYER_ACTION_CHG_4
    Player_ActionChange_5,  // PLAYER_ACTION_CHG_5
    Player_ActionChange_6,  // PLAYER_ACTION_CHG_6
    Player_ActionChange_7,  // PLAYER_ACTION_CHG_7
    Player_ActionChange_8,  // PLAYER_ACTION_CHG_8
    Player_ActionChange_9,  // PLAYER_ACTION_CHG_9
    Player_ActionChange_10, // PLAYER_ACTION_CHG_10
    Player_ActionChange_11, // PLAYER_ACTION_CHG_11
    Player_ActionChange_12, // PLAYER_ACTION_CHG_12
    Player_ActionChange_13, // PLAYER_ACTION_CHG_13
    Player_ActionChange_14, // PLAYER_ACTION_CHG_14
};

/**
 * This function processes "Action Change Lists", which run various functions that
 * check if it is appropriate to change to a new action.
 *
 * Action Change Lists are a list of indices for the `sPlayerActionChangeFuncs` array.
 * The functions are ran in order until one of them returns true, or the end of the list is reached.
 * An Action Change index having a negative value indicates that it is the last member in the list.
 *
 * Because these lists are processed sequentially, the order of the indices in the list determines its priority.
 *
 * If the `updateUpperBody` argument is true, Player's upper body will update before the Action Change List
 * is processed. This allows for Upper Action functions to run.
 *
 * @return true if a new action has been chosen
 *
 */
s32 Player_TryActionChangeList(PlayState* play, Player* this, s8* actionChangeList, s32 updateUpperBody) {
    if (!(this->stateFlags1 & (PLAYER_STATE1_1 | PLAYER_STATE1_80 | PLAYER_STATE1_20000000)) && !func_8082DA90(play)) {
        if (updateUpperBody) {
            D_80862B04 = Player_UpdateUpperBody(this, play);
            if (Player_Action_64 == this->actionFunc) {
                return true;
            }
        }

        if (func_801240DC(this)) {
            this->unk_AA6 |= 0x41;
            return true;
        }

        if (!(this->stateFlags3 & PLAYER_STATE3_START_CHANGING_HELD_ITEM) &&
            (Player_UpperAction_ChangeHeldItem != this->upperActionFunc)) {
            // Process all entries in the Action Change List with a positive index
            while (*actionChangeList >= 0) {
                if (sPlayerActionChangeFuncs[*actionChangeList](this, play)) {
                    return true;
                }
                actionChangeList++;
            }

            // Try the last entry in the list. Negate the index to make it positive again.
            if (sPlayerActionChangeFuncs[-*actionChangeList](this, play)) {
                return true;
            }
        }

        if (func_8083213C(this)) {
            return true;
        }
    } else if (this->stateFlags1 & PLAYER_STATE1_800) {
        Player_UpdateUpperBody(this, play);
    }

    return false;
}

s32 func_808331FC(PlayState* play, Player* this, SkelAnime* skelAnime, f32 frame) {
    if ((skelAnime->endFrame - frame) <= skelAnime->curFrame) {
        f32 speedTarget;
        s16 yawTarget;

        if (Player_TryActionChangeList(play, this, sPlayerActionChangeList7, true)) {
            return 0;
        }

        if (D_80862B04 || Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_CURVED, play)) {
            return 1;
        }
    }
    return -1;
}

void func_808332A0(PlayState* play, Player* this, s32 magicCost, s32 isSwordBeam) {
    if (magicCost != 0) {
        this->unk_B08 = 0.0f;
    } else {
        this->unk_B08 = 0.5f;
    }

    this->stateFlags1 |= PLAYER_STATE1_1000;
    if ((this->actor.id == ACTOR_PLAYER) && (isSwordBeam || (this->transformation == PLAYER_FORM_HUMAN))) {
        s16 pitch = 0;
        Actor* thunder;

        if (isSwordBeam) {
            if (this->lockOnActor != NULL) {
                pitch = Math_Vec3f_Pitch(&this->bodyPartsPos[PLAYER_BODYPART_WAIST], &this->lockOnActor->focus.pos);
            }
            if (gSaveContext.save.saveInfo.playerData.magic == 0) {
                return;
            }
        }

        thunder = Actor_Spawn(&play->actorCtx, play, ACTOR_EN_M_THUNDER, this->bodyPartsPos[PLAYER_BODYPART_WAIST].x,
                              this->bodyPartsPos[PLAYER_BODYPART_WAIST].y, this->bodyPartsPos[PLAYER_BODYPART_WAIST].z,
                              pitch, 0, 0, (this->heldItemAction - PLAYER_IA_SWORD_KOKIRI) | magicCost);

        if ((thunder != NULL) && isSwordBeam) {
            Magic_Consume(play, 1, MAGIC_CONSUME_DEITY_BEAM);
            this->unk_D57 = 4;
        }
    }
}

// Check for inputs for quickspin
s32 func_808333CC(Player* this) {
    s8 sp3C[4];
    s8* iter;
    s8* iter2;
    s8 temp1;
    s8 temp2;
    s32 i;

    if (this->heldItemAction == PLAYER_IA_DEKU_STICK) {
        return false;
    }

    iter = &this->unk_ADF[0];
    iter2 = &sp3C[0];
    for (i = 0; i < 4; i++, iter++, iter2++) {
        if ((*iter2 = *iter) < 0) {
            return false;
        }
        *iter2 *= 2;
    }

    temp1 = sp3C[0] - sp3C[1];
    if (ABS_ALT(temp1) < 10) {
        return false;
    }

    iter2 = &sp3C[1];
    for (i = 1; i < 3; i++, iter2++) {
        temp2 = *iter2 - *(iter2 + 1);
        if ((ABS_ALT(temp2) < 10) || (temp2 * temp1 < 0)) {
            return false;
        }
    }

    return true;
}

void func_808334D4(PlayState* play, Player* this) {
    PlayerAnimationHeader* anim;

    if ((this->meleeWeaponAnimation >= PLAYER_MWA_RIGHT_SLASH_1H) &&
        (this->meleeWeaponAnimation <= PLAYER_MWA_RIGHT_COMBO_2H)) {
        anim = D_8085CF58[Player_IsHoldingTwoHandedWeapon(this)];
    } else {
        anim = D_8085CF50[Player_IsHoldingTwoHandedWeapon(this)];
    }

    func_8082DC38(this);
    PlayerAnimation_Change(play, &this->skelAnime, anim, 1.0f, 8.0f, Animation_GetLastFrame(anim), ANIMMODE_ONCE,
                           -9.0f);
    func_808332A0(play, this, 2 << 8, false);
}

void func_808335B0(PlayState* play, Player* this) {
    Player_SetAction(play, this, Player_Action_30, 1);
    func_808334D4(play, this);
}

s8 D_8085D090[] = {
    PLAYER_MWA_STAB_1H,
    PLAYER_MWA_RIGHT_SLASH_1H,
    PLAYER_MWA_RIGHT_SLASH_1H,
    PLAYER_MWA_LEFT_SLASH_1H,
};

s8 D_8085D094[][3] = {
    { PLAYER_MWA_ZORA_PUNCH_LEFT, PLAYER_MWA_ZORA_PUNCH_COMBO, PLAYER_MWA_ZORA_PUNCH_KICK },
    { PLAYER_MWA_GORON_PUNCH_LEFT, PLAYER_MWA_GORON_PUNCH_RIGHT, PLAYER_MWA_GORON_PUNCH_BUTT },
};

PlayerMeleeWeaponAnimation func_808335F4(Player* this) {
    s32 temp_a1;
    PlayerMeleeWeaponAnimation meleeWeaponAnim;

    temp_a1 = this->unk_AE3[this->unk_ADE];
    if ((this->transformation == PLAYER_FORM_ZORA) || (this->transformation == PLAYER_FORM_GORON)) {
        s8* meleeWeaponAnims = (this->transformation == PLAYER_FORM_ZORA) ? D_8085D094[0] : D_8085D094[1];
        s32 unk_ADD = this->unk_ADD;

        meleeWeaponAnim = meleeWeaponAnims[unk_ADD];

        if (unk_ADD != 0) {
            this->meleeWeaponAnimation = meleeWeaponAnim;
            if (unk_ADD >= 2) {
                this->unk_ADD = -1;
            }
        }
    } else {
        if (func_808333CC(this)) {
            meleeWeaponAnim = PLAYER_MWA_SPIN_ATTACK_1H;
        } else {
            if (temp_a1 < 0) {
                meleeWeaponAnim = func_8082FBE8(this) ? PLAYER_MWA_FORWARD_SLASH_1H : PLAYER_MWA_RIGHT_SLASH_1H;
            } else {
                meleeWeaponAnim = D_8085D090[temp_a1];
                if (meleeWeaponAnim == PLAYER_MWA_STAB_1H) {
                    this->stateFlags2 |= PLAYER_STATE2_40000000;
                    if (!func_8082FBE8(this)) {
                        meleeWeaponAnim = PLAYER_MWA_FORWARD_SLASH_1H;
                    }
                }
            }

            if (this->heldItemAction == PLAYER_IA_DEKU_STICK) {
                meleeWeaponAnim = PLAYER_MWA_FORWARD_SLASH_1H;
            }
        }

        if (Player_IsHoldingTwoHandedWeapon(this)) {
            meleeWeaponAnim++;
        }
    }
    return meleeWeaponAnim;
}

void func_80833728(Player* this, s32 index, u32 dmgFlags, s32 damage) {
    this->meleeWeaponQuads[index].info.toucher.dmgFlags = dmgFlags;
    this->meleeWeaponQuads[index].info.toucher.damage = damage;

    if (dmgFlags == DMG_DEKU_STICK) {
        this->meleeWeaponQuads[index].info.toucherFlags = (TOUCH_ON | TOUCH_NEAREST | TOUCH_SFX_WOOD);
    } else {
        this->meleeWeaponQuads[index].info.toucherFlags = (TOUCH_ON | TOUCH_NEAREST);
    }
}

MeleeWeaponDamageInfo D_8085D09C[PLAYER_MELEEWEAPON_MAX] = {
    { DMG_GORON_PUNCH, 2, 2, 0, 0 }, // PLAYER_MELEEWEAPON_NONE
    { DMG_SWORD, 4, 8, 1, 2 },       // PLAYER_MELEEWEAPON_SWORD_KOKIRI
    { DMG_SWORD, 4, 8, 2, 4 },       // PLAYER_MELEEWEAPON_SWORD_RAZOR
    { DMG_SWORD, 4, 8, 3, 6 },       // PLAYER_MELEEWEAPON_SWORD_GILDED
    { DMG_SWORD, 4, 8, 4, 8 },       // PLAYER_MELEEWEAPON_SWORD_TWO_HANDED
    { DMG_DEKU_STICK, 0, 0, 2, 4 },  // PLAYER_MELEEWEAPON_DEKU_STICK
    { DMG_ZORA_PUNCH, 1, 2, 0, 0 },  // PLAYER_MELEEWEAPON_ZORA_FINS
};

// New function in NE0: split out of func_80833864 to be able to call it to patch Power Crouch Stab.
void func_8083375C(Player* this, PlayerMeleeWeaponAnimation meleeWeaponAnim) {
    MeleeWeaponDamageInfo* dmgInfo = &D_8085D09C[0];
    s32 damage;

    if (this->actor.id == ACTOR_EN_TEST3) {
        // Was Kafei originally intended to be able to punch?
        meleeWeaponAnim = PLAYER_MWA_GORON_PUNCH_LEFT;
        this->meleeWeaponAnimation = -1;
    } else {
        //! @bug Quick Put Away Damage: Since 0 is also the "no weapon" value, producing a weapon quad without a weapon
        //! in hand, such as during Quick Put Away, produced a quad with the Goron punch properties, which does 0 damage
        //! as human.
        dmgInfo = &D_8085D09C[(this->transformation == PLAYER_FORM_GORON) ? PLAYER_MELEEWEAPON_NONE
                                                                          : Player_GetMeleeWeaponHeld(this)];
    }

    //! @bug Great Deku Sword: Presumably the dmgTransformed fields are intended for Fierce Deity, but also work for
    //! Deku if it is able to equip a sword (such as with the "0th day" glitch), giving Great Fairy's Sword damage.
    damage =
        ((meleeWeaponAnim >= PLAYER_MWA_FLIPSLASH_START) && (meleeWeaponAnim <= PLAYER_MWA_ZORA_JUMPKICK_FINISH))
            ? ((this->transformation == PLAYER_FORM_HUMAN) ? dmgInfo->dmgHumanStrong : dmgInfo->dmgTransformedStrong)
            : ((this->transformation == PLAYER_FORM_HUMAN) ? dmgInfo->dmgHumanNormal : dmgInfo->dmgTransformedNormal);

    func_80833728(this, 0, dmgInfo->dmgFlags, damage);
    func_80833728(this, 1, dmgInfo->dmgFlags, damage);
}

void func_80833864(PlayState* play, Player* this, PlayerMeleeWeaponAnimation meleeWeaponAnim) {
    func_8083375C(this, meleeWeaponAnim);
    Player_SetAction(play, this, Player_Action_84, 0);
    this->actionVar2 = 0;

    if ((meleeWeaponAnim < PLAYER_MWA_FLIPSLASH_FINISH) || (meleeWeaponAnim > PLAYER_MWA_ZORA_JUMPKICK_FINISH)) {
        func_8082DC38(this);
    }

    // Accumulate consecutive slashes to do the "third slash" types
    if ((meleeWeaponAnim != this->meleeWeaponAnimation) || (this->unk_ADD >= 3)) {
        this->unk_ADD = 0;
    }

    this->unk_ADD++;
    if (this->unk_ADD >= 3) {
        meleeWeaponAnim += 2;
    }

    this->meleeWeaponAnimation = meleeWeaponAnim;
    func_8082DB90(play, this, sMeleeAttackAnimInfo[meleeWeaponAnim].unk_0);
    this->unk_ADC = this->skelAnime.animLength + 4.0f;

    if ((meleeWeaponAnim < PLAYER_MWA_FLIPSLASH_START) || (meleeWeaponAnim > PLAYER_MWA_ZORA_JUMPKICK_START)) {
        func_8082E920(play, this, (ANIM_FLAG_1 | ANIM_FLAG_8 | ANIM_FLAG_NOMOVE));
    }
    this->currentYaw = this->actor.shape.rot.y;
}

void func_80833998(Player* this, s32 invincibilityTimer) {
    if (this->invincibilityTimer >= 0) {
        this->invincibilityTimer = invincibilityTimer;
        this->unk_B5F = 0;
    }
}

void func_808339B4(Player* this, s32 invincibilityTimer) {
    if (this->invincibilityTimer > invincibilityTimer) {
        this->invincibilityTimer = invincibilityTimer;
    }
    this->unk_B5F = 0;
}

// Player_InflictDamageImpl?
s32 func_808339D4(PlayState* play, Player* this, s32 damage) {
    if ((this->invincibilityTimer != 0) || (this->stateFlags3 & PLAYER_STATE3_400000) ||
        (this->actor.id != ACTOR_PLAYER)) {
        return 1;
    }

    if (this->actor.category != ACTORCAT_PLAYER) {
        this->actor.colChkInfo.damage = -damage;
        return Actor_ApplyDamage(&this->actor);
    }

    if (this->currentMask == PLAYER_MASK_GIANT) {
        damage >>= 2;
    }

    return Health_ChangeBy(play, damage);
}

void func_80833A64(Player* this) {
    this->skelAnime.prevTransl = this->skelAnime.jointTable[PLAYER_LIMB_ROOT - 1];
    func_8082E820(this, 1 | ANIM_FLAG_UPDATE_Y);
}

void func_80833AA0(Player* this, PlayState* play) {
    if (Player_SetAction(play, this, Player_Action_25, 0)) {
        Player_AnimationPlayLoop(play, this, &gPlayerAnim_link_normal_landing_wait);
        this->actionVar2 = 1;
    }
    if (this->unk_AA5 != PLAYER_UNKAA5_4) {
        this->unk_AA5 = PLAYER_UNKAA5_0;
    }
}

// TODO: this can be one array, but should it be?
PlayerAnimationHeader* D_8085D0D4[] = {
    &gPlayerAnim_link_normal_front_shit,
    &gPlayerAnim_link_normal_front_shitR,
    &gPlayerAnim_link_normal_back_shit,
    &gPlayerAnim_link_normal_back_shitR,
    // };
    // PlayerAnimationHeader* D_8085D0E4[] = {
    &gPlayerAnim_link_normal_front_hit,
    &gPlayerAnim_link_anchor_front_hitR,
    &gPlayerAnim_link_normal_back_hit,
    &gPlayerAnim_link_anchor_back_hitR,
};

void func_80833B18(PlayState* play, Player* this, s32 arg2, f32 speed, f32 velocityY, s16 arg5,
                   s32 invincibilityTimer) {
    PlayerAnimationHeader* anim = NULL;

    if (this->stateFlags1 & PLAYER_STATE1_2000) {
        func_80833A64(this);
    }

    this->unk_B64 = 0;

    Player_PlaySfx(this, NA_SE_PL_DAMAGE);

    if (func_808339D4(play, this, -this->actor.colChkInfo.damage) == 0) {
        this->stateFlags2 &= ~PLAYER_STATE2_80;
        if ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) || (this->stateFlags1 & PLAYER_STATE1_8000000)) {
            return;
        }
    }

    if (this->actor.colChkInfo.damage != 0) {
        func_80833998(this, invincibilityTimer);
    }

    if (this->stateFlags2 & PLAYER_STATE2_10) {
        return;
    }

    if (arg2 == 3) {
        Player_SetAction(play, this, Player_Action_82, 0);
        anim = &gPlayerAnim_link_normal_ice_down;
        func_8082DAD4(this);
        this->actor.velocity.y = 0.0f;

        Player_RequestRumble(play, this, 255, 10, 40, SQ(0));

        Player_PlaySfx(this, NA_SE_PL_FREEZE_S);
        Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_FREEZE);
    } else if (arg2 == 4) {
        Player_SetAction(play, this, Player_Action_83, 0);
        func_8082DB60(play, this, &gPlayerAnim_link_normal_electric_shock);
        func_8082DAD4(this);

        this->actionVar2 = 20;
        this->actor.velocity.y = 0.0f;

        Player_RequestRumble(play, this, 255, 80, 150, SQ(0));
    } else {
        arg5 -= this->actor.shape.rot.y;

        if (this->stateFlags1 & PLAYER_STATE1_8000000) {
            Player_SetAction(play, this, Player_Action_61, 0);
            Player_RequestRumble(play, this, 180, 20, 50, SQ(0));

            if (arg2 == 1) {
                this->linearVelocity = speed * 1.5f;
                this->actor.velocity.y = velocityY * 0.7f;
            } else {
                this->linearVelocity = 4.0f;
                this->actor.velocity.y = 0.0f;
            }

            Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_DAMAGE_S);
            anim = &gPlayerAnim_link_swimer_swim_hit;
        } else if ((arg2 == 1) || (arg2 == 2) || !(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) ||
                   (this->stateFlags1 &
                    (PLAYER_STATE1_4 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000 | PLAYER_STATE1_200000))) {
            Player_SetAction(play, this, Player_Action_21, 0);

            this->stateFlags3 |= PLAYER_STATE3_2;

            Player_RequestRumble(play, this, 255, 20, 150, SQ(0));
            func_8082DAD4(this);

            if (arg2 == 2) {
                this->actionVar2 = 4;

                this->actor.speed = 3.0f;
                this->linearVelocity = 3.0f;
                this->actor.velocity.y = 6.0f;

                func_8082E5A8(play, this, D_8085BE84[PLAYER_ANIMGROUP_3][this->modelAnimType]);
                Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_DAMAGE_S);
            } else {
                this->actor.speed = speed;
                this->linearVelocity = speed;
                this->actor.velocity.y = velocityY;

                if (ABS_ALT(arg5) > 0x4000) {
                    anim = &gPlayerAnim_link_normal_front_downA;
                } else {
                    anim = &gPlayerAnim_link_normal_back_downA;
                }
                Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_FALL_L);
            }
            this->actor.bgCheckFlags &= ~BGCHECKFLAG_GROUND;
        } else if ((this->linearVelocity > 4.0f) && !func_80123420(this)) {
            this->unk_B64 = 20;

            Player_RequestRumble(play, this, 120, 20, 10, SQ(0));
            Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_DAMAGE_S);

            return;
        } else {
            PlayerAnimationHeader** animPtr = D_8085D0D4;

            Player_SetAction(play, this, Player_Action_20, 0);
            func_8082FC60(this);

            if (this->actor.colChkInfo.damage < 5) {
                Player_RequestRumble(play, this, 120, 20, 10, SQ(0));
            } else {
                Player_RequestRumble(play, this, 180, 20, 100, SQ(0));
                this->linearVelocity = 23.0f;

                animPtr += 4;
            }

            if (ABS_ALT(arg5) <= 0x4000) {
                animPtr += 2;
            }

            if (func_80123420(this)) {
                animPtr++;
            }

            anim = *animPtr;
            Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_DAMAGE_S);
        }

        this->actor.shape.rot.y += arg5;
        this->currentYaw = this->actor.shape.rot.y;
        this->actor.world.rot.y = this->actor.shape.rot.y;

        if (ABS_ALT(arg5) > 0x4000) {
            this->actor.shape.rot.y += 0x8000;
        }
    }

    func_8082DE50(play, this);

    this->stateFlags1 |= PLAYER_STATE1_4000000;

    if (anim != NULL) {
        func_8082DB90(play, this, anim);
    }
}

s32 func_808340AC(FloorType floorType) {
    s32 temp_v0 = floorType - FLOOR_TYPE_2;

    if ((temp_v0 >= FLOOR_TYPE_2 - FLOOR_TYPE_2) && (temp_v0 <= FLOOR_TYPE_3 - FLOOR_TYPE_2)) {
        return temp_v0;
    }
    return -1;
}

s32 func_808340D4(FloorType floorType) {
    return (floorType == FLOOR_TYPE_4) || (floorType == FLOOR_TYPE_7) || (floorType == FLOOR_TYPE_12);
}

void func_80834104(PlayState* play, Player* this) {
    Player_SetAction(play, this, Player_Action_77, 0);
    this->stateFlags1 |= PLAYER_STATE1_20000000 | PLAYER_STATE1_80000000;
}

void func_80834140(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    if (!(this->stateFlags1 & PLAYER_STATE1_80)) {
        func_80834104(play, this);
        if (func_8082DA90(play)) {
            this->actionVar2 = -30;
        }
        this->stateFlags1 |= PLAYER_STATE1_80;
        PlayerAnimation_Change(play, &this->skelAnime, anim, 1.0f, 0.0f, 84.0f, ANIMMODE_ONCE, -6.0f);
        this->actionVar1 = 1;
        this->linearVelocity = 0.0f;
    }
}

s32 func_808341F4(PlayState* play, Player* this) {
    f32 temp_fv0;
    f32 flameScale;
    f32 flameIntensity;
    s32 i;
    s32 timerStep;
    s32 spawnedFlame = false;
    s32 var_v0;
    s32 var_v1;
    u8* timerPtr = this->flameTimers;

    if ((this->transformation == PLAYER_FORM_ZORA) || (this->transformation == PLAYER_FORM_DEKU)) {
        timerStep = 0;
        if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
            if (this->cylinder.base.ocFlags1 & OC1_HIT) {
                Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.prevPos);
                this->linearVelocity = 0.0f;
            }
            func_80834140(play, this, &gPlayerAnim_link_derth_rebirth);
        }
    } else {
        if (this->transformation == PLAYER_FORM_GORON) {
            var_v1 = 20;
        } else {
            var_v1 = (s32)(this->linearVelocity * 0.4f) + 1;
        }

        if (this->stateFlags2 & PLAYER_STATE2_8) {
            var_v0 = 100;
        } else {
            var_v0 = 0;
        }

        timerStep = var_v0 + var_v1;
    }

    for (i = 0; i < PLAYER_BODYPART_MAX; i++, timerPtr++) {
        if (*timerPtr <= timerStep) {
            *timerPtr = 0;
        } else {
            spawnedFlame = true;
            *timerPtr -= timerStep;
            if (*timerPtr > 20.0f) {
                temp_fv0 = (*timerPtr - 20.0f) * 0.01f;
                flameScale = CLAMP(temp_fv0, 0.19999999f, 0.2f);
            } else {
                flameScale = *timerPtr * 0.01f;
            }

            flameIntensity = (*timerPtr - 25.0f) * 0.02f;
            flameIntensity = CLAMP(flameIntensity, 0.0f, 1.0f);
            EffectSsFireTail_SpawnFlameOnPlayer(play, flameScale, i, flameIntensity);
        }
    }

    if (spawnedFlame) {
        Player_PlaySfx(this, NA_SE_EV_TORCH - SFX_FLAG);
        if ((play->gameplayFrames % 4) == 0) {
            Player_InflictDamage(play, -1);
        }
    } else {
        this->isBurning = false;
    }

    return this->stateFlags1 & PLAYER_STATE1_80;
}

s32 func_808344C0(PlayState* play, Player* this) {
    s32 i = 0;

    while (i < ARRAY_COUNT(this->flameTimers)) {
        this->flameTimers[i] = Rand_S16Offset(0, 200);
        i++;
    }

    this->isBurning = true;
    return func_808341F4(play, this);
}

s32 func_80834534(PlayState* play, Player* this) {
    Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_FALL_L);
    return func_808344C0(play, this);
}

s32 func_8083456C(PlayState* play, Player* this) {
    if (this->actor.colChkInfo.acHitEffect == 1) {
        return func_80834534(play, this);
    }
    return false;
}

void func_808345A8(Player* this) {
    if ((this->invincibilityTimer > 0) && (this->invincibilityTimer < 20)) {
        this->invincibilityTimer = 20;
    }
}

void func_808345C8(void) {
    if (INV_CONTENT(ITEM_MASK_DEKU) == ITEM_MASK_DEKU) {
        gSaveContext.save.playerForm = PLAYER_FORM_HUMAN;
        gSaveContext.save.equippedMask = PLAYER_MASK_NONE;
    }
}

s32 func_80834600(Player* this, PlayState* play) {
    s32 pad74;
    s32 var_v0;

    if (this->unk_D6A != 0) {
        if (!Player_InBlockingCsMode(play, this)) {
            Player_InflictDamage(play, -16);
            this->unk_D6A = 0;
        }
    } else if ((var_v0 = ((Player_GetHeight(this) - 8.0f) < (this->unk_AB8 * this->actor.scale.y))) ||
               (this->actor.bgCheckFlags & BGCHECKFLAG_CRUSHED) || (sPlayerFloorType == FLOOR_TYPE_9) ||
               (this->stateFlags2 & PLAYER_STATE2_80000000)) {
        Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_DAMAGE_S);

        if (var_v0) {
            func_80169FDC(&play->state);
            func_808345C8();
            Scene_SetExitFade(play);
        } else {
            func_80169EFC(&play->state);
            func_808345C8();
        }

        Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_TAKEN_AWAY);
        play->haltAllActors = true;
        Audio_PlaySfx(NA_SE_OC_ABYSS);
    } else if ((this->unk_B75 != 0) && ((this->unk_B75 >= 3) || (this->invincibilityTimer == 0))) {
        u8 sp6C[] = { 0, 2, 1, 1 };

        if (!func_8083456C(play, this)) {
            if (this->unk_B75 == 4) {
                this->shockTimer = 40;
            }

            this->actor.colChkInfo.damage += this->unk_B74;
            func_80833B18(play, this, sp6C[this->unk_B75 - 1], this->unk_B78, this->unk_B7C, this->unk_B76, 20);
        }
    } else if ((this->shieldQuad.base.acFlags & AC_BOUNCED) || (this->shieldCylinder.base.acFlags & AC_BOUNCED) ||
               ((this->invincibilityTimer < 0) && (this->cylinder.base.acFlags & AC_HIT) &&
                (this->cylinder.info.acHitInfo != NULL) &&
                (this->cylinder.info.acHitInfo->toucher.dmgFlags != DMG_UNBLOCKABLE))) {
        PlayerAnimationHeader* var_a2;
        s32 sp64;

        Player_RequestRumble(play, this, 180, 20, 100, SQ(0));
        if ((this->invincibilityTimer >= 0) && !Player_IsGoronOrDeku(this)) {
            sp64 = (Player_Action_18 == this->actionFunc);
            if (!func_801242B4(this)) {
                Player_SetAction(play, this, Player_Action_19, 0);
            }

            this->actionVar1 = sp64;
            if ((s8)sp64 == 0) {
                Player_SetUpperAction(play, this, Player_UpperAction_4);
                var_a2 = (this->unk_B40 < 0.5f) ? D_8085CFD4[Player_IsHoldingTwoHandedWeapon(this)]
                                                : D_8085CFCC[Player_IsHoldingTwoHandedWeapon(this)];
                PlayerAnimation_PlayOnce(play, &this->skelAnimeUpper, var_a2);
            } else {
                Player_AnimationPlayOnce(play, this, D_8085CFDC[Player_IsHoldingTwoHandedWeapon(this)]);
            }
        }

        if (!(this->stateFlags1 & (PLAYER_STATE1_4 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000 | PLAYER_STATE1_200000))) {
            this->linearVelocity = -18.0f;
            this->currentYaw = this->actor.shape.rot.y;
        }

        return false;
    } else if ((this->unk_D6B != 0) || (this->invincibilityTimer > 0) || (this->stateFlags1 & PLAYER_STATE1_4000000) ||
               (this->csMode != PLAYER_CSMODE_NONE) || (this->meleeWeaponQuads[0].base.atFlags & AT_HIT) ||
               (this->meleeWeaponQuads[1].base.atFlags & AT_HIT) || (this->cylinder.base.atFlags & AT_HIT) ||
               (this->shieldCylinder.base.atFlags & AT_HIT)) {
        return false;
    } else if (this->cylinder.base.acFlags & AC_HIT) {
        Actor* sp60 = this->cylinder.base.ac;
        s32 var_a2_2;

        if (sp60->flags & ACTOR_FLAG_1000000) {
            Player_PlaySfx(this, NA_SE_PL_BODY_HIT);
        }

        if (this->actor.colChkInfo.acHitEffect == 2) {
            var_a2_2 = 3;
        } else if (this->actor.colChkInfo.acHitEffect == 3) {
            var_a2_2 = 4;
        } else if (this->actor.colChkInfo.acHitEffect == 7) {
            var_a2_2 = 1;
            this->shockTimer = 40;
        } else if (this->actor.colChkInfo.acHitEffect == 9) {
            var_a2_2 = 1;
            if (func_80834534(play, this)) {
                return true;
            }

        } else if (((this->actor.colChkInfo.acHitEffect == 4) && (this->currentMask != PLAYER_MASK_GIANT)) ||
                   (this->stateFlags3 & PLAYER_STATE3_1000)) {
            var_a2_2 = 1;
        } else {
            var_a2_2 = 0;
            if (func_8083456C(play, this)) {
                return true;
            }
        }
        func_80833B18(play, this, var_a2_2, 4.0f, 5.0f, Actor_WorldYawTowardActor(sp60, &this->actor), 20);
    } else if (this->invincibilityTimer != 0) {
        return false;
    } else {
        s32 sp58 = func_808340AC(sPlayerFloorType);
        u32 isSurfaceWallDamage = SurfaceType_IsWallDamage(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId);
        s32 var_a1 = false;
        s32 var_v1_2;
        s32 pad48;

        if ((sp58 < 0) || (!isSurfaceWallDamage && (this->transformation == PLAYER_FORM_GORON) &&
                           !(this->actor.depthInWater > 0.0f))) {
            var_a1 = (this->actor.wallPoly != NULL) &&
                     SurfaceType_IsWallDamage(&play->colCtx, this->actor.wallPoly, this->actor.wallBgId);
            if (!var_a1) {
                //! FAKE?
                goto label;
            }
        }
        var_v1_2 = var_a1 ? this->actor.wallBgId : this->actor.floorBgId;
        if (((this->transformation == PLAYER_FORM_DEKU) || (this->transformation == PLAYER_FORM_ZORA)) &&
            ((sp58 >= 0) && !isSurfaceWallDamage && !(this->stateFlags1 & PLAYER_STATE1_8000000) &&
             (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && (this->actor.depthInWater < -30.0f))) {
            func_80834534(play, this);
        } else {
            this->actor.colChkInfo.damage = 4;
            func_80833B18(play, this, (var_v1_2 == BGCHECK_SCENE) ? 0 : 1, 4.0f, 5.0f,
                          var_a1 ? this->actor.wallYaw : this->actor.shape.rot.y, 20);
            return true;
        }
    }

    //! FAKE?
    if (0) {
    label:
        return false;
    }

    return true;
}

void func_80834CD0(Player* this, f32 arg1, u16 sfxId) {
    this->actor.velocity.y = arg1 * D_8085C3E4;
    this->actor.bgCheckFlags &= ~BGCHECKFLAG_GROUND;

    if (sfxId != NA_SE_NONE) {
        Player_AnimSfx_PlayFloorJump(this);
        Player_AnimSfx_PlayVoice(this, sfxId);
    }

    this->stateFlags1 |= PLAYER_STATE1_40000;
    this->fallStartHeight = this->actor.world.pos.y;
}

void func_80834D50(PlayState* play, Player* this, PlayerAnimationHeader* anim, f32 speed, u16 sfxId) {
    Player_SetAction(play, this, Player_Action_25, 1);
    if (anim != NULL) {
        func_8082DB90(play, this, anim);
    }
    func_80834CD0(this, speed, sfxId);
}

void func_80834DB8(Player* this, PlayerAnimationHeader* anim, f32 speed, PlayState* play) {
    func_80834D50(play, this, anim, speed, NA_SE_VO_LI_SWORD_N);
}

s32 Player_ActionChange_12(Player* this, PlayState* play) {
    if ((this->transformation != PLAYER_FORM_GORON) &&
        ((this->transformation != PLAYER_FORM_DEKU) || func_801242B4(this) ||
         (this->ledgeClimbType <= PLAYER_LEDGE_CLIMB_3)) &&
        !(this->stateFlags1 & PLAYER_STATE1_800) && (this->ledgeClimbType >= PLAYER_LEDGE_CLIMB_2) &&
        (!(this->stateFlags1 & PLAYER_STATE1_8000000) || (this->yDistToLedge < this->ageProperties->unk_14))) {
        s32 var_v1 = false;
        PlayerAnimationHeader* anim;
        f32 yDistToLedge;

        if (func_801242B4(this)) {
            f32 depth = (this->transformation == PLAYER_FORM_FIERCE_DEITY) ? 80.0f : 50.0f;

            if (this->actor.depthInWater < depth) {
                if ((this->ledgeClimbType <= PLAYER_LEDGE_CLIMB_1) ||
                    (this->ageProperties->unk_10 < this->yDistToLedge)) {
                    return false;
                }
            } else if ((this->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER) ||
                       (this->ledgeClimbType >= PLAYER_LEDGE_CLIMB_3)) {
                return false;
            }
        } else if (!(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) ||
                   ((this->ageProperties->unk_14 <= this->yDistToLedge) &&
                    (this->stateFlags1 & PLAYER_STATE1_8000000))) {
            return false;
        }

        if ((this->actor.wallBgId != BGCHECK_SCENE) && (sPlayerTouchedWallFlags & WALL_FLAG_6)) {
            if (this->ledgeClimbDelayTimer >= 6) {
                this->stateFlags2 |= PLAYER_STATE2_4;
                if (CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_A)) {
                    var_v1 = true;
                }
            }
        } else if ((this->ledgeClimbDelayTimer >= 6) || CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_A)) {
            var_v1 = true;
        }

        if (var_v1) {
            Player_SetAction(play, this, Player_Action_33, 0);
            yDistToLedge = this->yDistToLedge;

            if (this->ageProperties->unk_14 <= yDistToLedge) {
                anim = &gPlayerAnim_link_normal_250jump_start;
                this->linearVelocity = 1.0f;
            } else {
                CollisionPoly* poly;
                s32 bgId;
                f32 wallPolyNormalX = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.x);
                f32 wallPolyNormalZ = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.z);
                f32 var_fv1 = this->distToInteractWall + 0.5f;
                f32 yIntersect;
                s32 pad;

                this->stateFlags1 |= PLAYER_STATE1_4;

                if (func_801242B4(this)) {
                    yDistToLedge -= 60.0f * this->ageProperties->unk_08;
                    anim = &gPlayerAnim_link_swimer_swim_15step_up;
                    this->stateFlags1 &= ~PLAYER_STATE1_8000000;
                } else if (this->ageProperties->unk_18 <= yDistToLedge) {
                    yDistToLedge -= 59.0f * this->ageProperties->unk_08;
                    anim = &gPlayerAnim_link_normal_150step_up;
                } else {
                    yDistToLedge -= 41.0f * this->ageProperties->unk_08;
                    anim = &gPlayerAnim_link_normal_100step_up;
                }

                this->unk_ABC -= yDistToLedge * 100.0f;

                this->actor.world.pos.x -= var_fv1 * wallPolyNormalX;
                this->actor.world.pos.y += this->yDistToLedge + 10.0f;
                this->actor.world.pos.z -= var_fv1 * wallPolyNormalZ;

                yIntersect =
                    BgCheck_EntityRaycastFloor5(&play->colCtx, &poly, &bgId, &this->actor, &this->actor.world.pos);
                if ((this->actor.world.pos.y - yIntersect) <= 20.0f) {
                    this->actor.world.pos.y = yIntersect;
                    if (bgId != BGCHECK_SCENE) {
                        DynaPoly_SetPlayerOnTop(&play->colCtx, bgId);
                    }
                }

                func_8082DAD4(this);
                this->actor.velocity.y = 0.0f;
            }

            this->actor.bgCheckFlags |= BGCHECKFLAG_GROUND;
            PlayerAnimation_PlayOnceSetSpeed(play, &this->skelAnime, anim, 1.3f);
            AnimationContext_DisableQueue(play);
            this->actor.shape.rot.y = this->currentYaw = this->actor.wallYaw + 0x8000;
            return true;
        }
    } else if ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && (this->ledgeClimbType == PLAYER_LEDGE_CLIMB_1) &&
               (this->ledgeClimbDelayTimer >= 3)) {
        f32 temp = (this->yDistToLedge * 0.08f) + 5.5f;

        func_80834DB8(this, &gPlayerAnim_link_normal_jump, temp, play);
        this->linearVelocity = 2.5f;
        return true;
    }

    return false;
}

void func_80835324(PlayState* play, Player* this, f32 arg2, s16 arg3) {
    Player_SetAction(play, this, Player_Action_35, 0);
    func_8082DD2C(play, this);

    this->csId = CS_ID_NONE;
    this->actionVar1 = 1;
    this->actionVar2 = 1;

    this->unk_3A0.x = Math_SinS(arg3) * arg2 + this->actor.world.pos.x;
    this->unk_3A0.z = Math_CosS(arg3) * arg2 + this->actor.world.pos.z;

    Player_AnimationPlayOnce(play, this, func_8082ED20(this));
}

void func_808353DC(PlayState* play, Player* this) {
    Player_SetAction(play, this, Player_Action_54, 0);
    func_8082E634(play, this, &gPlayerAnim_link_swimer_swim_wait);
}

s32 func_80835428(PlayState* play, Player* this) {
    if (!func_8082DA90(play) && (this->stateFlags1 & PLAYER_STATE1_80000000)) {
        func_80834104(play, this);
        Player_AnimationPlayLoop(play, this, &gPlayerAnim_link_normal_landing_wait);
        Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_FALL_S);
        Audio_PlaySfx_2(NA_SE_OC_SECRET_WARP_IN);
        return true;
    }
    return false;
}

/**
 * The actual entrances each "return entrance" value can map to.
 * This is used by scenes that are shared between locations.
 *
 * This 1D array is split into groups of entrances.
 * The start of each group is indexed by `sReturnEntranceGroupIndices` values.
 * The resulting groups are then indexed by the spawn value.
 *
 * The spawn value (`PlayState.curSpawn`) is set to a different value depending on the entrance used to enter the
 * scene, which allows these dynamic "return entrances" to link back to the previous scene.
 *
 * Seems unused in MM
 */
u16 sReturnEntranceGroupData[] = {
    // 0xFE00
    /* 0 */ 0x1000,
};

/**
 * The values are indices into `sReturnEntranceGroupData` marking the start of each group
 */
u8 sReturnEntranceGroupIndices[] = {
    0, // 0xFE00
};

// subfunction of OoT's func_80839034
void func_808354A4(PlayState* play, s32 exitIndex, s32 arg2) {
    play->nextEntrance = play->setupExitList[exitIndex];

    if (play->nextEntrance == 0xFFFF) {
        gSaveContext.respawnFlag = 4;
        play->nextEntrance = gSaveContext.respawn[RESPAWN_MODE_UNK_3].entrance;
        play->transitionType = TRANS_TYPE_FADE_WHITE;
        gSaveContext.nextTransitionType = TRANS_TYPE_FADE_WHITE;
    } else if (play->nextEntrance >= 0xFE00) {
        play->nextEntrance =
            sReturnEntranceGroupData[sReturnEntranceGroupIndices[play->nextEntrance - 0xFE00] + play->curSpawn];

        Scene_SetExitFade(play);
    } else {
        if (arg2) {
            gSaveContext.respawn[RESPAWN_MODE_DOWN].entrance = play->nextEntrance;
            func_80169EFC(&play->state);
            gSaveContext.respawnFlag = -2;
        }

        gSaveContext.retainWeatherMode = true;
        Scene_SetExitFade(play);
    }

    play->transitionTrigger = TRANS_TRIGGER_START;
}

void func_808355D8(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    func_80833AA0(this, play);
    this->actionVar2 = -2;
    func_8082E5EC(play, this, anim);
    func_8082E1F0(this, NA_SE_IT_DEKUNUTS_FLOWER_CLOSE);
}

s32 Player_HandleExitsAndVoids(PlayState* play, Player* this, CollisionPoly* poly, s32 bgId) {
    s32 exitIndexPlusOne;
    FloorType floorType;
    s32 sp34;
    s32 sp30;

    if ((this == GET_PLAYER(play)) && !(this->stateFlags1 & PLAYER_STATE1_80) && !func_8082DA90(play) &&
        (this->csMode == PLAYER_CSMODE_NONE) && !(this->stateFlags1 & PLAYER_STATE1_1)) {
        exitIndexPlusOne = 0;

        if (((poly != NULL) &&
             (exitIndexPlusOne = SurfaceType_GetSceneExitIndex(&play->colCtx, poly, bgId), (exitIndexPlusOne != 0)) &&
             (((play->sceneId != SCENE_GORONRACE) && (play->sceneId != SCENE_DEKU_KING)) || (exitIndexPlusOne < 3)) &&
             (((play->sceneId != SCENE_20SICHITAI) && (play->sceneId != SCENE_20SICHITAI2)) ||
              (exitIndexPlusOne < 0x15)) &&
             ((play->sceneId != SCENE_11GORONNOSATO) || (exitIndexPlusOne < 6))) ||
            (func_808340D4(sPlayerFloorType) && (this->floorProperty == FLOOR_PROPERTY_12))) {

            sp34 = this->unk_D68 - (s32)this->actor.world.pos.y;

            if (!(this->stateFlags1 & (PLAYER_STATE1_800000 | PLAYER_STATE1_8000000 | PLAYER_STATE1_20000000)) &&
                !(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && (sp34 < 400) && (sPlayerYDistToFloor > 100.0f)) {
                if ((this->floorProperty != FLOOR_PROPERTY_5) && (this->floorProperty != FLOOR_PROPERTY_12)) {
                    this->linearVelocity = 0.0f;
                }
                return false;
            }

            if (this->stateFlags3 & PLAYER_STATE3_1000000) {
                func_808355D8(play, this, &gPlayerAnim_pn_kakkufinish);
            }

            if (exitIndexPlusOne == 0) {
                func_80169EFC(&play->state);
                Scene_SetExitFade(play);
            } else {
                func_808354A4(play, exitIndexPlusOne - 1,
                              SurfaceType_GetFloorEffect(&play->colCtx, poly, bgId) == FLOOR_EFFECT_2);

                if ((this->stateFlags1 & PLAYER_STATE1_8000000) && (this->floorProperty == FLOOR_PROPERTY_5)) {
                    Audio_PlaySfx_2(NA_SE_OC_TUNAMI);
                    func_801A4058(5);
                    gSaveContext.seqId = (u8)NA_BGM_DISABLED;
                    gSaveContext.ambienceId = AMBIENCE_ID_DISABLED;
                } else if (!(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) &&
                           (this->floorProperty == FLOOR_PROPERTY_12)) {
                    Audio_PlaySfx_2(NA_SE_OC_SECRET_WARP_IN);
                }

                if (this->stateFlags1 & PLAYER_STATE1_800000) {
                    if (D_801BDAA0) {
                        D_801BDAA0 = false;
                    } else {
                        gHorseIsMounted = true;
                    }
                }
            }

            if (!(this->stateFlags1 & (PLAYER_STATE1_800000 | PLAYER_STATE1_8000000 | PLAYER_STATE1_20000000)) &&
                ((floorType = SurfaceType_GetFloorType(&play->colCtx, poly, bgId)) != FLOOR_TYPE_10) &&
                ((sp34 < 100) || (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND))) {
                if (floorType == FLOOR_TYPE_11) {
                    Audio_PlaySfx_2(NA_SE_OC_SECRET_HOLE_OUT);
                    func_801A4058(5);
                    gSaveContext.seqId = (u8)NA_BGM_DISABLED;
                    gSaveContext.ambienceId = AMBIENCE_ID_DISABLED;
                } else {
                    func_8085B74C(play);
                }
            } else if (!(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
                Player_StopHorizontalMovement(this);
            }

            Camera_ChangeSetting(Play_GetCamera(play, CAM_ID_MAIN), CAM_SET_SCENE0);
            this->stateFlags1 |= PLAYER_STATE1_1 | PLAYER_STATE1_20000000;
            return true;
        }
        if ((this->stateFlags1 & PLAYER_STATE1_8000000) && (this->actor.floorPoly == NULL)) {
            BgCheck_EntityRaycastFloor7(&play->colCtx, &this->actor.floorPoly, &sp30, &this->actor,
                                        &this->actor.world.pos);
            if (this->actor.floorPoly == NULL) {
                func_80169EFC(&play->state);
                return false;
            }
            //! FAKE
            if (1) {}
        }

        if (!(this->stateFlags1 & PLAYER_STATE1_80000000)) {
            if (((this->actor.world.pos.y < -4000.0f) ||
                 (((this->floorProperty == FLOOR_PROPERTY_5) || (this->floorProperty == FLOOR_PROPERTY_12) ||
                   (this->floorProperty == FLOOR_PROPERTY_13)) &&
                  ((sPlayerYDistToFloor < 100.0f) || (this->fallDistance > 400))))) {
                if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
                    if (this->floorProperty == FLOOR_PROPERTY_5) {
                        func_80169FDC(&play->state);
                        func_808345C8();
                    } else {
                        func_80169EFC(&play->state);
                    }
                    if (!SurfaceType_IsWallDamage(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId)) {
                        gSaveContext.respawnFlag = -5;
                    }

                    play->transitionType = TRANS_TYPE_FADE_BLACK_FAST;
                    Audio_PlaySfx(NA_SE_OC_ABYSS);
                } else {
                    if (this->stateFlags3 & PLAYER_STATE3_1000000) {
                        func_808355D8(play, this, &gPlayerAnim_pn_kakkufinish);
                    }

                    if (this->floorProperty == FLOOR_PROPERTY_13) {
                        Player_SetAction(play, this, Player_Action_1, 0);
                        this->stateFlags1 |= PLAYER_STATE1_20000000;
                    } else {
                        func_80834104(play, this);
                        this->actionVar2 = 9999;
                        if (this->floorProperty == FLOOR_PROPERTY_5) {
                            this->actionVar1 = -1;
                        } else {
                            this->actionVar1 = 1;
                        }
                    }
                }
            }
        }

        this->unk_D68 = this->actor.world.pos.y;
    }

    return false;
}

/**
 * Gets a position relative to player's yaw.
 * An offset is applied to the provided base position in the direction of shape y rotation.
 * The resulting position is stored in `dst`
 */
void Player_TranslateAndRotateY(Player* this, Vec3f* translation, Vec3f* src, Vec3f* dst) {
    Lib_Vec3f_TranslateAndRotateY(translation, this->actor.shape.rot.y, src, dst);
}

// Player_GetPosInACertainDirectionFromARadiusAway
void func_80835BF8(Vec3f* srcPos, s16 rotY, f32 radius, Vec3f* dstPos) {
    dstPos->x = Math_SinS(rotY) * radius + srcPos->x;
    dstPos->z = Math_CosS(rotY) * radius + srcPos->z;
}

Actor* Player_SpawnFairy(PlayState* play, Player* this, Vec3f* translation, Vec3f* pos, s32 fairyParams) {
    Vec3f spawnPos;

    Player_TranslateAndRotateY(this, translation, pos, &spawnPos);

    return Actor_Spawn(&play->actorCtx, play, ACTOR_EN_ELF, spawnPos.x, spawnPos.y, spawnPos.z, 0, 0, 0, fairyParams);
}

f32 func_80835CD8(PlayState* play, Player* this, Vec3f* arg2, Vec3f* pos, CollisionPoly** outPoly, s32* outBgId) {
    Player_TranslateAndRotateY(this, &this->actor.world.pos, arg2, pos);

    return BgCheck_EntityRaycastFloor5(&play->colCtx, outPoly, outBgId, &this->actor, pos);
}

f32 func_80835D2C(PlayState* play, Player* this, Vec3f* arg2, Vec3f* pos) {
    CollisionPoly* poly;
    s32 bgId;

    return func_80835CD8(play, this, arg2, pos, &poly, &bgId);
}

/**
 * Checks if a line between the player's position and the provided `offset` intersect a wall.
 *
 * Point A of the line is at player's world position offset by the height provided in `offset`.
 * Point B of the line is at player's world position offset by the entire `offset` vector.
 * Point A and B are always at the same height, meaning this is a horizontal line test.
 */
s32 Player_PosVsWallLineTest(PlayState* play, Player* this, Vec3f* offset, CollisionPoly** wallPoly, s32* bgId,
                             Vec3f* posResult) {
    Vec3f posA;
    Vec3f posB;

    posA.x = this->actor.world.pos.x;
    posA.y = this->actor.world.pos.y + offset->y;
    posA.z = this->actor.world.pos.z;

    Player_TranslateAndRotateY(this, &this->actor.world.pos, offset, &posB);

    return BgCheck_EntityLineTest2(&play->colCtx, &posA, &posB, posResult, wallPoly, true, false, false, true, bgId,
                                   &this->actor);
}

Vec3f D_8085D100 = { 0.0f, 50.0f, 0.0f };

s32 func_80835DF8(PlayState* play, Player* this, CollisionPoly** outPoly, s32* outBgId) {
    Vec3f pos;
    f32 yIntersect = func_80835CD8(play, this, &D_8085D100, &pos, outPoly, outBgId);

    if ((*outBgId == BGCHECK_SCENE) && (fabsf(this->actor.world.pos.y - yIntersect) < 10.0f)) {
        Environment_ChangeLightSetting(play, SurfaceType_GetLightSettingIndex(&play->colCtx, *outPoly, *outBgId));
        return true;
    }
    return false;
}

/**
 * PLAYER_DOORTYPE_STAIRCASE: DoorSpiral
 */
void Player_Door_Staircase(PlayState* play, Player* this, Actor* door) {
    static Vec3f D_8085D10C = { 20.0f, 0.0f, 20.0f };
    DoorSpiral* doorStaircase = (DoorSpiral*)door;

    this->currentYaw = doorStaircase->actor.home.rot.y + 0x8000;
    this->actor.shape.rot.y = this->currentYaw;
    if (this->linearVelocity <= 0.0f) {
        this->linearVelocity = 0.1f;
    }
    func_80835324(play, this, 50.0f, this->actor.shape.rot.y);

    this->unk_397 = this->doorType;
    this->actionVar1 = 0;
    this->stateFlags1 |= PLAYER_STATE1_20000000;
    func_80835BF8(&doorStaircase->actor.world.pos, doorStaircase->actor.shape.rot.y, -140.0f, &this->unk_3A0);

    D_8085D10C.x = (this->doorDirection != 0) ? -400.0f : 400.0f;
    D_8085D10C.z = 200.0f;
    Player_TranslateAndRotateY(this, &this->unk_3A0, &D_8085D10C, &this->unk_3AC);

    doorStaircase->shouldClimb = true;

    func_8082DAD4(this);

    if (this->doorTimer != 0) {
        this->actionVar2 = 0;
        func_8082E438(play, this, func_8082ED20(this));
        this->skelAnime.endFrame = 0.0f;
    } else {
        this->linearVelocity = 0.1f;
    }

    Camera_ChangeSetting(Play_GetCamera(play, CAM_ID_MAIN), CAM_SET_SCENE0);
    this->doorBgCamIndex =
        play->doorCtx.transitionActorList[DOOR_GET_TRANSITION_ID(&doorStaircase->actor)].sides[0].bgCamIndex;
    Actor_DeactivateLens(play);
    this->floorSfxOffset = NA_SE_PL_WALK_CONCRETE - SFX_FLAG;
}

/**
 * PLAYER_DOORTYPE_SLIDING: DoorShutter, BgOpenShutter
 */
void Player_Door_Sliding(PlayState* play, Player* this, Actor* door) {
    SlidingDoorActor* doorSliding = (SlidingDoorActor*)door;
    Vec3f sp38;

    this->currentYaw = doorSliding->dyna.actor.home.rot.y;
    if (this->doorDirection > 0) {
        this->currentYaw -= 0x8000;
    }
    this->actor.shape.rot.y = this->currentYaw;
    if (this->linearVelocity <= 0.0f) {
        this->linearVelocity = 0.1f;
    }

    func_80835324(play, this, 50.0f, this->actor.shape.rot.y);
    this->actionVar1 = 0;
    this->unk_397 = this->doorType;
    this->stateFlags1 |= PLAYER_STATE1_20000000;
    Actor_OffsetOfPointInActorCoords(&doorSliding->dyna.actor, &sp38, &this->actor.world.pos);

    func_80835BF8(&this->actor.world.pos, doorSliding->dyna.actor.shape.rot.y,
                  (42.0f - fabsf(sp38.z)) * this->doorDirection, &this->actor.world.pos);
    func_80835BF8(&this->actor.world.pos, doorSliding->dyna.actor.shape.rot.y, this->doorDirection * 20.0f,
                  &this->unk_3A0);
    func_80835BF8(&this->actor.world.pos, doorSliding->dyna.actor.shape.rot.y, this->doorDirection * -120.0f,
                  &this->unk_3AC);

    doorSliding->unk_15C = 1;
    func_8082DAD4(this);

    if (this->doorTimer != 0) {
        this->actionVar2 = 0;
        func_8082E438(play, this, func_8082ED20(this));
        this->skelAnime.endFrame = 0.0f;
    } else {
        this->linearVelocity = 0.1f;
    }

    if (doorSliding->dyna.actor.category == ACTORCAT_DOOR) {
        this->doorBgCamIndex = play->doorCtx.transitionActorList[DOOR_GET_TRANSITION_ID(&doorSliding->dyna.actor)]
                                   .sides[this->doorDirection > 0 ? 0 : 1]
                                   .bgCamIndex;
        Actor_DeactivateLens(play);
    }
}

// sPlayerOpenDoorLeftAnimPerForm
PlayerAnimationHeader* D_8085D118[] = {
    &gPlayerAnim_pg_doorA_open, // PLAYER_FORM_GORON
    &gPlayerAnim_pz_doorA_open, // PLAYER_FORM_ZORA
    &gPlayerAnim_pn_doorA_open, // PLAYER_FORM_DEKU
};
// sPlayerOpenDoorRightAnimPerForm
PlayerAnimationHeader* D_8085D124[] = {
    &gPlayerAnim_pg_doorB_open, // PLAYER_FORM_GORON
    &gPlayerAnim_pz_doorB_open, // PLAYER_FORM_ZORA
    &gPlayerAnim_pn_doorB_open, // PLAYER_FORM_DEKU
};

/**
 * PLAYER_DOORTYPE_TALKING: EnDoorEtc
 * PLAYER_DOORTYPE_HANDLE: EnDoor
 * PLAYER_DOORTYPE_FAKE:
 * PLAYER_DOORTYPE_PROXIMITY: EnDoor
 */
void Player_Door_Knob(PlayState* play, Player* this, Actor* door) {
    s32 temp = this->transformation - 1;
    PlayerAnimationHeader* anim;
    f32 temp_fv0; // sp5C
    KnobDoorActor* knobDoor = (KnobDoorActor*)door;

    knobDoor->animIndex = this->transformation;

    if (this->doorDirection < 0) {
        if (this->transformation == PLAYER_FORM_FIERCE_DEITY) {
            anim = D_8085BE84[PLAYER_ANIMGROUP_8][this->modelAnimType];
        } else if (this->transformation == PLAYER_FORM_HUMAN) {
            anim = D_8085BE84[PLAYER_ANIMGROUP_9][this->modelAnimType];
        } else {
            anim = D_8085D118[temp];
        }
    } else {
        knobDoor->animIndex += PLAYER_FORM_MAX;

        if (this->transformation == PLAYER_FORM_FIERCE_DEITY) {
            anim = D_8085BE84[PLAYER_ANIMGROUP_10][this->modelAnimType];
        } else if (this->transformation == PLAYER_FORM_HUMAN) {
            anim = D_8085BE84[PLAYER_ANIMGROUP_11][this->modelAnimType];
        } else {
            anim = D_8085D124[temp];
        }
    }

    Player_SetAction(play, this, Player_Action_36, 0);
    this->stateFlags2 |= PLAYER_STATE2_800000;
    func_8082DE14(play, this);
    if (this->doorDirection < 0) {
        this->actor.shape.rot.y = knobDoor->dyna.actor.shape.rot.y;
    } else {
        this->actor.shape.rot.y = knobDoor->dyna.actor.shape.rot.y - 0x8000;
    }

    this->currentYaw = this->actor.shape.rot.y;
    temp_fv0 = this->doorDirection * 22.0f;
    func_80835BF8(&knobDoor->dyna.actor.world.pos, knobDoor->dyna.actor.shape.rot.y, temp_fv0, &this->actor.world.pos);
    func_8082EC9C(play, this, anim);

    if (this->doorTimer != 0) {
        this->skelAnime.endFrame = 0.0f;
    }

    func_8082DAD4(this);
    func_8082E920(play, this,
                  ANIM_FLAG_1 | ANIM_FLAG_UPDATE_Y | ANIM_FLAG_4 | ANIM_FLAG_8 | ANIM_FLAG_80 | ANIM_FLAG_200);
    knobDoor->playOpenAnim = true;
    if (this->doorType != PLAYER_DOORTYPE_FAKE) {
        CollisionPoly* poly;
        s32 bgId;
        Vec3f pos;
        s32 enDoorType = ENDOOR_GET_TYPE(&knobDoor->dyna.actor);

        this->stateFlags1 |= PLAYER_STATE1_20000000;

        if (this->actor.category == ACTORCAT_PLAYER) {
            Actor_DeactivateLens(play);
            func_80835BF8(&knobDoor->dyna.actor.world.pos, knobDoor->dyna.actor.shape.rot.y, -temp_fv0, &pos);
            pos.y = knobDoor->dyna.actor.world.pos.y + 10.0f;
            BgCheck_EntityRaycastFloor5(&play->colCtx, &poly, &bgId, &this->actor, &pos);

            if (Player_HandleExitsAndVoids(play, this, poly, BGCHECK_SCENE)) {
                gSaveContext.entranceSpeed = 2.0f;
            } else if (enDoorType != ENDOOR_TYPE_7) {
                Camera* mainCam;

                this->actionVar1 = 38.0f * D_8085C3E8;
                mainCam = Play_GetCamera(play, CAM_ID_MAIN);

                Camera_ChangeDoorCam(mainCam, &knobDoor->dyna.actor,
                                     play->doorCtx.transitionActorList[DOOR_GET_TRANSITION_ID(&knobDoor->dyna.actor)]
                                         .sides[(this->doorDirection > 0) ? 0 : 1]
                                         .bgCamIndex,
                                     0.0f, this->actionVar1, 26.0f * D_8085C3E8, 10.0f * D_8085C3E8);
            }
        }
    }
}

// door stuff
s32 Player_ActionChange_1(Player* this, PlayState* play) {
    if ((gSaveContext.save.saveInfo.playerData.health != 0) && (this->doorType != PLAYER_DOORTYPE_NONE)) {
        if ((this->actor.category != ACTORCAT_PLAYER) ||
            ((((this->doorType <= PLAYER_DOORTYPE_TALKING) && CutsceneManager_IsNext(CS_ID_GLOBAL_TALK)) ||
              ((this->doorType >= PLAYER_DOORTYPE_HANDLE) && CutsceneManager_IsNext(CS_ID_GLOBAL_DOOR))) &&
             (!(this->stateFlags1 & PLAYER_STATE1_800) &&
              (CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_A) || (Player_Action_78 == this->actionFunc) ||
               (this->doorType == PLAYER_DOORTYPE_STAIRCASE) || (this->doorType == PLAYER_DOORTYPE_PROXIMITY))))) {
            Actor* doorActor = this->doorActor;
            Actor* var_v0_3;

            if (this->doorType <= PLAYER_DOORTYPE_TALKING) {
                Player_TalkWithPlayer(play, doorActor);
                if (doorActor->textId == 0x1821) {
                    doorActor->flags |= ACTOR_FLAG_TALK_REQUESTED;
                }
                return true;
            }

            gSaveContext.respawn[RESPAWN_MODE_DOWN].data = 0;

            if (this->doorType == PLAYER_DOORTYPE_STAIRCASE) {
                Player_Door_Staircase(play, this, doorActor);
            } else if (this->doorType == PLAYER_DOORTYPE_SLIDING) {
                Player_Door_Sliding(play, this, doorActor);
            } else {
                Player_Door_Knob(play, this, doorActor);
            }

            if (this->actor.category == ACTORCAT_PLAYER) {
                this->csId = CS_ID_GLOBAL_DOOR;
                CutsceneManager_Start(this->csId, &this->actor);
            }

            if (this->actor.category == ACTORCAT_PLAYER) {
                if ((this->doorType < PLAYER_DOORTYPE_FAKE) && (doorActor->category == ACTORCAT_DOOR) &&
                    ((this->doorType != PLAYER_DOORTYPE_HANDLE) || (ENDOOR_GET_TYPE(doorActor) != ENDOOR_TYPE_7))) {
                    s8 roomNum = play->doorCtx.transitionActorList[DOOR_GET_TRANSITION_ID(doorActor)]
                                     .sides[(this->doorDirection > 0) ? 0 : 1]
                                     .room;

                    if ((roomNum >= 0) && (roomNum != play->roomCtx.curRoom.num)) {
                        Room_StartRoomTransition(play, &play->roomCtx, roomNum);
                    }
                }
            }

            doorActor->room = play->roomCtx.curRoom.num;
            if (((var_v0_3 = doorActor->child) != NULL) || ((var_v0_3 = doorActor->parent) != NULL)) {
                var_v0_3->room = play->roomCtx.curRoom.num;
            }
            return true;
        }
    }

    return false;
}

void func_80836888(Player* this, PlayState* play) {
    PlayerAnimationHeader* anim;

    Player_SetAction(play, this, Player_Action_2, 1);

    if (this->unk_B40 < 0.5f) {
        anim = func_8082EF54(this);
        this->unk_B40 = 0.0f;
    } else {
        anim = func_8082EF9C(this);
        this->unk_B40 = 1.0f;
    }

    this->unk_B44 = this->unk_B40;
    Player_AnimationPlayLoop(play, this, anim);
    this->currentYaw = this->actor.shape.rot.y;
}

void func_8083692C(Player* this, PlayState* play) {
    Player_SetAction(play, this, Player_Action_3, 1);
    func_8082E438(play, this, func_8082ED20(this));
    this->currentYaw = this->actor.shape.rot.y;
}

void func_80836988(Player* this, PlayState* play) {
    if (func_80123420(this)) {
        func_80836888(this, play);
    } else if (func_80123434(this)) {
        func_8083692C(this, play);
    } else {
        func_8085B384(this, play);
    }
}

void func_808369F4(Player* this, PlayState* play) {
    PlayerActionFunc actionFunc;

    if (func_80123420(this)) {
        actionFunc = Player_Action_2;
    } else if (func_80123434(this)) {
        actionFunc = Player_Action_3;
    } else {
        actionFunc = Player_Action_4;
    }
    Player_SetAction(play, this, actionFunc, 1);
}

void func_80836A5C(Player* this, PlayState* play) {
    func_808369F4(this, play);
    if (func_80123420(this)) {
        this->actionVar2 = 1;
    }
}

void func_80836A98(Player* this, PlayerAnimationHeader* anim, PlayState* play) {
    func_80836A5C(this, play);
    func_8082EC9C(play, this, anim);
}

void func_80836AD8(PlayState* play, Player* this) {
    Player_SetAction(play, this, Player_Action_96, 0);
    this->unk_B28 = 0;
    this->unk_B86[1] = 0;
    this->unk_AF0[0].x = 0.0f;
    this->unk_AF0[0].y = 0.0f;
    this->unk_AF0[0].z = 0.0f;
    this->unk_B08 = 0.0f;
    this->unk_B0C = 0.0f;
    Player_PlaySfx(this, NA_SE_PL_GORON_TO_BALL);
}

void func_80836B3C(PlayState* play, Player* this, f32 arg2) {
    this->currentYaw = this->actor.shape.rot.y;
    this->actor.world.rot.y = this->actor.shape.rot.y;

    if (this->transformation == PLAYER_FORM_GORON) {
        func_80836AD8(play, this);
        PlayerAnimation_Change(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_15][this->modelAnimType],
                               1.5f * D_8085C3E4, 0.0f, 6.0f, ANIMMODE_ONCE, 0.0f);
    } else {
        PlayerAnimationHeader* anim = D_8085BE84[PLAYER_ANIMGROUP_15][this->modelAnimType];

        Player_SetAction(play, this, Player_Action_26, 0);
        PlayerAnimation_Change(play, &this->skelAnime, anim, 1.25f * D_8085C3E4, arg2, Animation_GetLastFrame(anim),
                               ANIMMODE_ONCE, 0.0f);
    }
}

void func_80836C70(PlayState* play, Player* this, PlayerBodyPart bodyPartIndex) {
    static Vec3f D_8085D130 = { 0, 0, 0 };
    s32 i;

    for (i = 0; i < 4; i++) {
        Vec3f velocity;

        velocity.x = Rand_CenteredFloat(4.0f);
        velocity.y = Rand_ZeroFloat(2.0f);
        velocity.z = Rand_CenteredFloat(4.0f);
        D_8085D130.y = -0.2f;
        EffectSsHahen_Spawn(play, &this->bodyPartsPos[bodyPartIndex], &velocity, &D_8085D130, 0, 10, OBJECT_LINK_NUTS,
                            16, object_link_nuts_DL_008860);
    }
}

void func_80836D8C(Player* this) {
    this->actor.focus.rot.x = 0;
    this->actor.focus.rot.z = 0;
    this->headLimbRot.x = 0;
    this->headLimbRot.y = 0;
    this->headLimbRot.z = 0;
    this->upperLimbRot.x = 0;
    this->upperLimbRot.y = 0;
    this->upperLimbRot.z = 0;
    this->actor.shape.rot.y = this->actor.focus.rot.y;
    this->currentYaw = this->actor.focus.rot.y;
}

s32 func_80836DC0(PlayState* play, Player* this) {
    if ((MREG(48) != 0) || func_800C9DDC(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId)) {
        Player_SetAction(play, this, Player_Action_93, 0);
        this->stateFlags1 &= ~(PLAYER_STATE1_20000 | PLAYER_STATE1_40000000);
        func_8082E438(play, this, &gPlayerAnim_pn_attack);
        Player_StopHorizontalMovement(this);
        func_80836D8C(this);
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->unk_B48 = -2000.0f;
        this->actor.shape.shadowScale = 13.0f;
        func_8082E1F0(this, NA_SE_PL_DEKUNUTS_IN_GRD);
        return true;
    }

    return false;
}

void Player_RequestQuake(PlayState* play, u16 speed, s16 y, s16 duration) {
    s16 quakeIndex = Quake_Request(Play_GetCamera(play, CAM_ID_MAIN), QUAKE_TYPE_3);

    Quake_SetSpeed(quakeIndex, speed);
    Quake_SetPerturbations(quakeIndex, y, 0, 0, 0);
    Quake_SetDuration(quakeIndex, duration);
}

FallImpactInfo sFallImpactInfos[] = {
    { -8, 180, 40, 100, NA_SE_VO_LI_LAND_DAMAGE_S },
    { -16, 255, 140, 150, NA_SE_VO_LI_LAND_DAMAGE_S },
};

// Player_FallAgainstTheFloor, Player_LetTheBodiesHitTheFloor, Player_ImpactFloor, Player_ProcessFallDamage,
// Player_DamageOnFloorImpact, Player_CalculateFallDamage
s32 func_80836F10(PlayState* play, Player* this) {
    s32 fallDistance;

    if ((sPlayerFloorType == FLOOR_TYPE_6) || (sPlayerFloorType == FLOOR_TYPE_9) ||
        (this->csMode != PLAYER_CSMODE_NONE)) {
        fallDistance = 0;
    } else {
        fallDistance = this->fallDistance;
    }

    Math_StepToF(&this->linearVelocity, 0.0f, 1.0f);
    this->stateFlags1 &= ~(PLAYER_STATE1_40000 | PLAYER_STATE1_80000);

    // Height enough for fall damage
    if (fallDistance >= 400) {
        s32 index;
        FallImpactInfo* entry;

        if (this->fallDistance < 800) {
            // small fall
            index = 0;
        } else {
            // big fall
            index = 1;
        }

        Player_PlaySfx(this, NA_SE_PL_BODY_HIT);

        entry = &sFallImpactInfos[index];
        Player_AnimSfx_PlayVoice(this, entry->sfxId);

        if (Player_InflictDamage(play, entry->damage)) {
            // Player's dead
            return -1;
        }

        func_80833998(this, 40);
        Player_RequestQuake(play, 32967, 2, 30);
        Player_RequestRumble(play, this, entry->sourceIntensity, entry->decayTimer, entry->decayStep, SQ(0));

        return index + 1;
    }

    // Tiny fall, won't damage player
    if (fallDistance > 200) {
        fallDistance = fallDistance * 2;
        fallDistance = CLAMP_MAX(fallDistance, 255);

        Player_RequestRumble(play, this, fallDistance, fallDistance * 0.1f, fallDistance, SQ(0));
        if (sPlayerFloorType == FLOOR_TYPE_6) {
            //! @bug unreachable code: When sPlayerFloorType is equal to FLOOR_TYPE_6 then fallDistance is
            //! ignored (set to zero), so the previous check based on said variable will always fail, producing this
            //! current check to always be false.
            Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_CLIMB_END);
        }
    }

    Player_AnimSfx_PlayFloorLand(this);
    return 0;
}

s32 func_808370D4(PlayState* play, Player* this) {
    if ((this->fallDistance < 800) && (this->unk_AE3[this->unk_ADE] == 0) && !(this->stateFlags1 & PLAYER_STATE1_800)) {
        func_80836B3C(play, this, 0.0f);

        return true;
    }
    return false;
}

void func_80837134(PlayState* play, Player* this) {
    PlayerAnimationHeader* anim = D_8085BE84[PLAYER_ANIMGROUP_13][this->modelAnimType];
    s32 temp_v0_2; // sp28

    this->stateFlags1 &= ~(PLAYER_STATE1_40000 | PLAYER_STATE1_80000);

    if (this->transformation == PLAYER_FORM_DEKU) {
        s32 var_v1 = false;

        if ((this->skelAnime.animation == &gPlayerAnim_pn_rakkafinish) ||
            (this->skelAnime.animation == &gPlayerAnim_pn_kakkufinish)) {
            func_80836C70(play, this, PLAYER_BODYPART_LEFT_HAND);
            func_80836C70(play, this, PLAYER_BODYPART_RIGHT_HAND);
            var_v1 = true;
        }

        if (CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_A) && func_80836DC0(play, this)) {
            return;
        }

        if (var_v1) {
            func_80836A98(this, anim, play);
            Player_AnimSfx_PlayFloorLand(this);
            return;
        }
    } else if (this->stateFlags2 & PLAYER_STATE2_80000) {
        if (func_80123420(this)) {
            anim = D_8085C2A4[this->actionVar1].unk_8;
        } else {
            anim = D_8085C2A4[this->actionVar1].unk_4;
        }
    } else if (this->skelAnime.animation == &gPlayerAnim_link_normal_run_jump) {
        anim = &gPlayerAnim_link_normal_run_jump_end;
    } else if (func_80123420(this)) {
        anim = &gPlayerAnim_link_anchor_landingR;
        func_8082FC60(this);
    } else if (this->fallDistance <= 80) {
        anim = D_8085BE84[PLAYER_ANIMGROUP_14][this->modelAnimType];
    } else if (func_808370D4(play, this)) {
        return;
    }

    temp_v0_2 = func_80836F10(play, this);
    if (temp_v0_2 > 0) { // Player suffered damage because of this fall
        func_80836A98(this, D_8085BE84[PLAYER_ANIMGROUP_13][this->modelAnimType], play);
        this->skelAnime.endFrame = 8.0f;

        if (temp_v0_2 == 1) {
            this->actionVar2 = 0xA;
        } else {
            this->actionVar2 = 0x14;
        }
    } else if (temp_v0_2 == 0) {
        func_80836A98(this, anim, play);
    }
}

void func_808373A4(PlayState* play, Player* this) {
    func_8082E438(play, this, &gPlayerAnim_pn_attack);
    this->unk_B10[0] = 20000.0f;
    this->unk_B10[1] = 0x30000;
    Player_PlaySfx(this, NA_SE_PL_DEKUNUTS_ATTACK);
}

s32 func_808373F8(PlayState* play, Player* this, u16 sfxId) {
    PlayerAnimationHeader* anim;
    f32 speed;
    s16 yawDiff = this->currentYaw - this->actor.shape.rot.y;

    if ((IREG(66) / 100.0f) < this->linearVelocity) {
        speed = IREG(67) / 100.0f;
    } else {
        speed = (IREG(68) / 100.0f + (IREG(69) * this->linearVelocity) / 1000.0f);

        if ((this->transformation == PLAYER_FORM_DEKU) && (speed < 8.0f)) {
            speed = 8.0f;
        } else if (speed < 5.0f) {
            speed = 5.0f;
        }
    }

    if ((ABS_ALT(yawDiff) >= 0x1000) || (this->linearVelocity <= 4.0f)) {
        anim = &gPlayerAnim_link_normal_jump;
    } else {
        s32 var_v1;

        if ((this->transformation != PLAYER_FORM_DEKU) &&
            ((sPlayerPrevFloorProperty == FLOOR_PROPERTY_1) || (sPlayerPrevFloorProperty == FLOOR_PROPERTY_2))) {
            if (sPlayerPrevFloorProperty == FLOOR_PROPERTY_1) {
                var_v1 = 4;
            } else {
                var_v1 = 5;
            }

            func_80834D50(play, this, D_8085C2A4[var_v1].unk_0, speed, ((var_v1 == 4) ? NA_SE_VO_LI_SWORD_N : sfxId));
            this->actionVar2 = -1;
            this->stateFlags2 |= PLAYER_STATE2_80000;
            this->actionVar1 = var_v1;
            return true;
        }
        anim = &gPlayerAnim_link_normal_run_jump;
    }

    // Deku hopping
    if (this->transformation == PLAYER_FORM_DEKU) {
        speed *= 0.3f + ((5 - this->remainingHopsCounter) * 0.18f);
        if (speed < 4.0f) {
            speed = 4.0f;
        }

        if ((this->actor.depthInWater > 0.0f) && (this->remainingHopsCounter != 0)) {
            this->actor.world.pos.y += this->actor.depthInWater;
            func_80834D50(play, this, anim, speed, NA_SE_NONE);
            this->actionVar2 = 1;
            this->stateFlags3 |= PLAYER_STATE3_200000;
            Player_PlaySfx(this, (NA_SE_PL_DEKUNUTS_JUMP5 + 1 - this->remainingHopsCounter));
            Player_AnimSfx_PlayVoice(this, sfxId);
            this->remainingHopsCounter--;
            if (this->remainingHopsCounter == 0) {
                this->stateFlags2 |= PLAYER_STATE2_80000;
                func_808373A4(play, this);
            }

            return true;
        }

        if (this->actor.velocity.y > 0.0f) {
            sfxId = NA_SE_NONE;
        }
    }

    func_80834D50(play, this, anim, speed, sfxId);
    this->actionVar2 = 1;

    return true;
}

s32 func_80837730(PlayState* play, Player* this, f32 arg2, s32 scale) {
    f32 sp3C = fabsf(arg2);

    if (sp3C > 2.0f) {
        WaterBox* waterBox;
        f32 sp34;
        Vec3f pos;

        Math_Vec3f_Copy(&pos, &this->bodyPartsPos[PLAYER_BODYPART_WAIST]);
        pos.y += 20.0f;
        if (WaterBox_GetSurface1(play, &play->colCtx, pos.x, pos.z, &pos.y, &waterBox)) {
            sp34 = pos.y - this->bodyPartsPos[PLAYER_BODYPART_LEFT_FOOT].y;
            if ((sp34 > -2.0f) && (sp34 < 100.0f)) {
                EffectSsGSplash_Spawn(play, &pos, NULL, NULL,
                                      (sp3C <= 10.0f) ? EFFSSGSPLASH_TYPE_0 : EFFSSGSPLASH_TYPE_1, scale);
                return true;
            }
        }
    }

    return false;
}

s32 func_8083784C(Player* this) {
    if (this->actor.velocity.y < 0.0f) {
        if ((this->actor.depthInWater > 0.0f) &&
            ((this->ageProperties->unk_2C - this->actor.depthInWater) < sPlayerYDistToFloor)) {
            if ((this->remainingHopsCounter != 0) && (gSaveContext.save.saveInfo.playerData.health != 0) &&
                !(this->stateFlags1 & PLAYER_STATE1_4000000)) {
                if (((this->talkActor == NULL) || !(this->talkActor->flags & ACTOR_FLAG_10000))) {
                    return true;
                }
            }
        }
    }

    return false;
}

void func_808378FC(PlayState* play, Player* this) {
    if (!func_8082FC24(this)) {
        this->stateFlags2 |= PLAYER_STATE2_20;
    }

    if (func_8083784C(this) && func_808373F8(play, this, NA_SE_VO_LI_AUTO_JUMP)) {
        func_80837730(play, this, 20.0f, this->actor.velocity.y * 50.0f);
    }
}

s32 func_8083798C(Player* this) {
    return (this->interactRangeActor != NULL) && (this->heldActor == NULL) &&
           (this->transformation != PLAYER_FORM_DEKU);
}

void func_808379C0(PlayState* play, Player* this) {
    if (func_8083798C(this)) {
        Actor* interactRangeActor = this->interactRangeActor;
        PlayerAnimationHeader* anim;

        if ((interactRangeActor->id == ACTOR_EN_ISHI) && (ENISHI_GET_1(interactRangeActor) != 0)) {
            Player_SetAction(play, this, Player_Action_38, 0);
            anim = &gPlayerAnim_link_silver_carry;
        } else if (((interactRangeActor->id == ACTOR_EN_BOMBF) || (interactRangeActor->id == ACTOR_EN_KUSA) ||
                    (interactRangeActor->id == ACTOR_EN_KUSA2) || (interactRangeActor->id == ACTOR_OBJ_GRASS_CARRY)) &&
                   (Player_GetStrength() <= PLAYER_STRENGTH_DEKU)) {
            Player_SetAction(play, this, Player_Action_40, 0);
            anim = &gPlayerAnim_link_normal_nocarry_free;

            this->actor.world.pos.x =
                (Math_SinS(interactRangeActor->yawTowardsPlayer) * 20.0f) + interactRangeActor->world.pos.x;
            this->actor.world.pos.z =
                (Math_CosS(interactRangeActor->yawTowardsPlayer) * 20.0f) + interactRangeActor->world.pos.z;

            this->currentYaw = this->actor.shape.rot.y = interactRangeActor->yawTowardsPlayer + 0x8000;
        } else {
            Player_SetAction(play, this, Player_Action_37, 0);
            anim = D_8085BE84[PLAYER_ANIMGROUP_12][this->modelAnimType];
        }

        Player_AnimationPlayOnce(play, this, anim);
    } else {
        func_80836988(this, play);
        this->stateFlags1 &= ~PLAYER_STATE1_800;
    }
}

void func_80837B60(PlayState* play, Player* this) {
    Player_SetAction_PreserveMoveFlags(play, this, Player_Action_44, 0);

    this->exchangeItemAction = PLAYER_IA_NONE;
    this->stateFlags1 |= (PLAYER_STATE1_40 | PLAYER_STATE1_20000000);
    if (this->actor.textId != 0) {
        Message_StartTextbox(play, this->actor.textId, this->talkActor);
    }
    this->lockOnActor = this->talkActor;
}

void func_80837BD0(PlayState* play, Player* this) {
    Player_SetAction_PreserveMoveFlags(play, this, Player_Action_52, 0);
}

void func_80837BF8(PlayState* play, Player* this) {
    Player_SetAction(play, this, Player_Action_45, 0);
}

void func_80837C20(PlayState* play, Player* this) {
    s32 sp1C = this->actionVar2;
    s32 sp18 = this->actionVar1;

    Player_SetAction_PreserveMoveFlags(play, this, Player_Action_50, 0);
    this->actor.velocity.y = 0.0f;

    this->actionVar2 = sp1C;
    this->actionVar1 = sp18;
}

void func_80837C78(PlayState* play, Player* this) {
    Player_SetAction_PreserveMoveFlags(play, this, Player_Action_65, 0);
    this->stateFlags1 |= (PLAYER_STATE1_400 | PLAYER_STATE1_20000000);

    if (this->getItemId == GI_HEART_CONTAINER) {
        this->actionVar2 = 20;
    } else if (this->getItemId >= GI_NONE) {
        this->actionVar2 = 1;
    } else {
        this->getItemId = -this->getItemId;
    }
}

void func_80837CEC(PlayState* play, Player* this, CollisionPoly* arg2, f32 arg3, PlayerAnimationHeader* anim) {
    f32 nx = COLPOLY_GET_NORMAL(arg2->normal.x);
    f32 nz = COLPOLY_GET_NORMAL(arg2->normal.z);

    Player_SetAction(play, this, Player_Action_48, 0);
    func_8082DE50(play, this);
    Player_AnimationPlayOnce(play, this, anim);

    this->actor.world.pos.x -= (arg3 + 1.0f) * nx;
    this->actor.world.pos.z -= (arg3 + 1.0f) * nz;
    this->actor.shape.rot.y = Math_Atan2S_XY(nz, nx);
    this->currentYaw = this->actor.shape.rot.y;

    func_8082DAD4(this);
    this->actor.velocity.y = 0.0f;
    func_8082E6D0(this);
}

s32 func_80837DEC(Player* this, PlayState* play) {
    if ((this->transformation != PLAYER_FORM_GORON) && (this->transformation != PLAYER_FORM_DEKU) &&
        (this->actor.depthInWater < -80.0f)) {
        //! @bug `floorPitch` and `floorPitchAlt` are cleared to 0 before this function is called,
        //! because the player left the ground. The angles will always be zero and therefore will always
        //! pass these checks. The intention seems to be to prevent ledge hanging or vine grabbing when
        //! walking off of a steep enough slope.
        if ((ABS_ALT(this->floorPitch) < 0xAAA) && (ABS_ALT(this->floorPitchAlt) < 0xAAA)) {
            CollisionPoly* entityPoly;
            CollisionPoly* sp90;
            s32 entityBgId;
            s32 sp88;
            Vec3f sp7C;
            Vec3f sp70;
            f32 temp_fv1_2;
            f32 entityNormalX;
            f32 entityNormalY;
            f32 entityNormalZ;
            f32 temp_fv0_2;
            f32 var_fv1;

            sp7C.x = this->actor.prevPos.x - this->actor.world.pos.x;
            sp7C.z = this->actor.prevPos.z - this->actor.world.pos.z;

            var_fv1 = sqrtf(SQXZ(sp7C));
            if (var_fv1 != 0.0f) {
                var_fv1 = 5.0f / var_fv1;
            } else {
                var_fv1 = 0.0f;
            }

            sp7C.x = this->actor.prevPos.x + (sp7C.x * var_fv1);
            sp7C.y = this->actor.world.pos.y;
            sp7C.z = this->actor.prevPos.z + (sp7C.z * var_fv1);

            if (BgCheck_EntityLineTest2(&play->colCtx, &this->actor.world.pos, &sp7C, &sp70, &entityPoly, true, false,
                                        false, true, &entityBgId, &this->actor)) {
                if (ABS_ALT(entityPoly->normal.y) < 0x258) {
                    s32 var_v1_2; // sp54

                    entityNormalX = COLPOLY_GET_NORMAL(entityPoly->normal.x);
                    entityNormalY = COLPOLY_GET_NORMAL(entityPoly->normal.y);
                    entityNormalZ = COLPOLY_GET_NORMAL(entityPoly->normal.z);

                    temp_fv0_2 = Math3D_UDistPlaneToPos(entityNormalX, entityNormalY, entityNormalZ, entityPoly->dist,
                                                        &this->actor.world.pos);

                    sp70.x = this->actor.world.pos.x - ((temp_fv0_2 + 1.0f) * entityNormalX);
                    sp70.z = this->actor.world.pos.z - ((temp_fv0_2 + 1.0f) * entityNormalZ);
                    sp70.y = this->actor.world.pos.y + 268 * 0.1f;

                    temp_fv1_2 = this->actor.world.pos.y -
                                 BgCheck_EntityRaycastFloor5(&play->colCtx, &sp90, &sp88, &this->actor, &sp70);
                    if ((temp_fv1_2 >= -11.0f) && (temp_fv1_2 <= 0.0f)) {
                        var_v1_2 = (sPlayerPrevFloorProperty == FLOOR_PROPERTY_6);
                        if (!var_v1_2) {
                            if (SurfaceType_GetWallFlags(&play->colCtx, entityPoly, entityBgId) & WALL_FLAG_3) {
                                var_v1_2 = true;
                            }
                        }

                        func_80837CEC(play, this, entityPoly, temp_fv0_2,
                                      var_v1_2 ? &gPlayerAnim_link_normal_Fclimb_startB
                                               : &gPlayerAnim_link_normal_fall);
                        if (var_v1_2) {
                            func_80832558(play, this, func_80837C20);

                            this->actor.shape.rot.y = this->currentYaw += 0x8000;
                            this->stateFlags1 |= PLAYER_STATE1_200000;
                            func_8082E920(play, this,
                                          ANIM_FLAG_1 | ANIM_FLAG_UPDATE_Y | ANIM_FLAG_4 | ANIM_FLAG_8 |
                                              ANIM_FLAG_NOMOVE | ANIM_FLAG_80);
                            this->actionVar2 = -1;
                            this->actionVar1 = var_v1_2;
                        } else {
                            this->stateFlags1 |= PLAYER_STATE1_2000;
                            this->stateFlags1 &= ~PLAYER_STATE1_20000;
                        }

                        Player_PlaySfx(this, NA_SE_PL_SLIPDOWN);
                        Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_HANG);
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

void func_808381A0(Player* this, PlayerAnimationHeader* anim, PlayState* play) {
    Player_SetAction(play, this, Player_Action_49, 0);
    PlayerAnimation_PlayOnceSetSpeed(play, &this->skelAnime, anim, 1.3f);
}

Vec3f D_8085D148 = { 0.0f, 50.0f, 0.0f };

s32 func_808381F8(PlayState* play, Player* this) {
    CollisionPoly* poly;
    s32 bgId;
    Vec3f pos;
    f32 yIntersect;

    Player_TranslateAndRotateY(this, &this->actor.prevPos, &D_8085D148, &pos);

    yIntersect = BgCheck_EntityRaycastFloor5(&play->colCtx, &poly, &bgId, &this->actor, &pos);

    return fabsf(yIntersect - this->actor.world.pos.y) < 10.0f;
}

Vec3f D_8085D154 = { 0.0f, 0.0f, 100.0f };

void func_8083827C(Player* this, PlayState* play) {
    s32 temp_t0; // sp64
    CollisionPoly* sp60;
    s32 sp5C;
    WaterBox* sp58;
    Vec3f sp4C;
    f32 sp48;
    f32 sp44;

    this->fallDistance = this->fallStartHeight - (s32)this->actor.world.pos.y;
    if (!(this->stateFlags1 & (PLAYER_STATE1_8000000 | PLAYER_STATE1_20000000)) &&
        ((this->stateFlags1 & PLAYER_STATE1_80000000) ||
         !(this->stateFlags3 & (PLAYER_STATE3_200 | PLAYER_STATE3_2000))) &&
        !(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
        if (func_80835428(play, this)) {
            return;
        }

        if (sPlayerPrevFloorProperty == FLOOR_PROPERTY_8) {
            this->actor.world.pos.x = this->actor.prevPos.x;
            this->actor.world.pos.z = this->actor.prevPos.z;
            return;
        }

        if ((this->stateFlags3 & PLAYER_STATE3_2) || (this->skelAnime.moveFlags & ANIM_FLAG_80)) {
            return;
        }

        if ((Player_Action_25 == this->actionFunc) || (Player_Action_27 == this->actionFunc) ||
            (Player_Action_28 == this->actionFunc) || (Player_Action_96 == this->actionFunc) ||
            (Player_Action_82 == this->actionFunc) || (Player_Action_83 == this->actionFunc)) {
            return;
        }

        if ((sPlayerPrevFloorProperty == FLOOR_PROPERTY_7) || (this->meleeWeaponState != PLAYER_MELEE_WEAPON_STATE_0) ||
            ((this->skelAnime.moveFlags & ANIM_FLAG_8) && func_808381F8(play, this))) {
            Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.prevPos);
            if (this->linearVelocity > 0.0f) {
                Player_StopHorizontalMovement(this);
            }
            this->actor.bgCheckFlags |= BGCHECKFLAG_GROUND_TOUCH;
            return;
        }

        temp_t0 = BINANG_SUB(this->currentYaw, this->actor.shape.rot.y);
        Player_SetAction(play, this, Player_Action_25, 1);
        func_8082DD2C(play, this);

        this->floorSfxOffset = this->prevFloorSfxOffset;
        if ((this->transformation != PLAYER_FORM_GORON) &&
            ((this->transformation != PLAYER_FORM_DEKU) || (this->remainingHopsCounter != 0)) &&
            (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND_LEAVE)) {
            if (!(this->stateFlags1 & PLAYER_STATE1_8000000)) {
                if ((sPlayerPrevFloorProperty != FLOOR_PROPERTY_6) && (sPlayerPrevFloorProperty != FLOOR_PROPERTY_9) &&
                    (sPlayerYDistToFloor > 20.0f) && (this->meleeWeaponState == PLAYER_MELEE_WEAPON_STATE_0)) {
                    if ((ABS_ALT(temp_t0) < 0x2000) && (this->linearVelocity > 3.0f)) {
                        if (!(this->stateFlags1 & PLAYER_STATE1_800)) {
                            if (((this->transformation == PLAYER_FORM_ZORA) &&
                                 CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_A)) ||
                                ((sPlayerPrevFloorProperty == FLOOR_PROPERTY_11) &&
                                 (this->transformation != PLAYER_FORM_GORON) &&
                                 (this->transformation != PLAYER_FORM_DEKU))) {

                                sp48 = func_80835CD8(play, this, &D_8085D154, &sp4C, &sp60, &sp5C);
                                sp44 = this->actor.world.pos.y;

                                if (WaterBox_GetSurface1(play, &play->colCtx, sp4C.x, sp4C.z, &sp44, &sp58) &&
                                    ((sp44 - sp48) > 50.0f)) {
                                    func_80834DB8(this, &gPlayerAnim_link_normal_run_jump_water_fall, 6.0f, play);
                                    Player_SetAction(play, this, Player_Action_27, 0);
                                    return;
                                }
                            }
                        }
                        func_808373F8(play, this, NA_SE_VO_LI_AUTO_JUMP);
                        return;
                    }
                }
            }
        }

        // Checking if the ledge is tall enough for Player to hang from
        if ((sPlayerPrevFloorProperty == FLOOR_PROPERTY_9) || (sPlayerYDistToFloor <= this->ageProperties->unk_34) ||
            !func_80837DEC(this, play)) {
            Player_AnimationPlayLoop(play, this, &gPlayerAnim_link_normal_landing_wait);
        }
    } else {
        this->fallStartHeight = this->actor.world.pos.y;
        this->remainingHopsCounter = 5;
    }
}

s32 func_8083868C(PlayState* play, Player* this) {
    s32 camMode;
    Camera* camera;

    if (this->unk_AA5 == PLAYER_UNKAA5_3) {
        if (func_800B7118(this)) {
            if (this->transformation == PLAYER_FORM_HUMAN) {
                camMode = CAM_MODE_SLINGSHOT;
            } else if (this->transformation == PLAYER_FORM_DEKU) {
                camMode = CAM_MODE_DEKUSHOOT;
            } else {
                camMode = CAM_MODE_BOWARROW;
            }
        } else {
            camMode = CAM_MODE_ZORAFIN;
        }
    } else {
        camMode = CAM_MODE_FIRSTPERSON;
    }

    camera = (this->actor.id == ACTOR_PLAYER) ? Play_GetCamera(play, CAM_ID_MAIN)
                                              : Play_GetCamera(play, ((EnTest3*)this)->subCamId);

    return Camera_ChangeMode(camera, camMode);
}

void Player_StopCutscene(Player* this) {
    if (this->csId > CS_ID_NONE) {
        CutsceneManager_Stop(this->csId);
        this->csId = CS_ID_NONE;
    }
}

s32 func_808387A0(PlayState* play, Player* this) {
    if (this->unk_AA5 == PLAYER_UNKAA5_4) {
        Player_StopCutscene(this);
        this->actor.flags &= ~ACTOR_FLAG_TALK_REQUESTED;
        Player_SetAction(play, this, Player_Action_97, 0);
        if (this->unk_3BA) {
            this->stateFlags1 |= PLAYER_STATE1_20000000;
        }
        func_8082DC38(this);

        return true;
    }
    return false;
}

void func_80838830(Player* this, s16 objectId) {
    s32 pad[2];

    if (objectId != OBJECT_UNSET_0) {
        this->giObjectLoading = true;
        osCreateMesgQueue(&this->giObjectLoadQueue, &this->giObjectLoadMsg, 1);
        DmaMgr_SendRequestImpl(&this->giObjectDmaRequest, this->giObjectSegment, gObjectTable[objectId].vromStart,
                               gObjectTable[objectId].vromEnd - gObjectTable[objectId].vromStart, 0,
                               &this->giObjectLoadQueue, NULL);
    }
}

PlayerAnimationHeader* D_8085D160[PLAYER_FORM_MAX] = {
    &gPlayerAnim_pz_maskoffstart, // PLAYER_FORM_FIERCE_DEITY
    &gPlayerAnim_pg_maskoffstart, // PLAYER_FORM_GORON
    &gPlayerAnim_pz_maskoffstart, // PLAYER_FORM_ZORA
    &gPlayerAnim_pn_maskoffstart, // PLAYER_FORM_DEKU
    &gPlayerAnim_cl_setmask,      // PLAYER_FORM_HUMAN
};

void func_808388B8(PlayState* play, Player* this, PlayerTransformation playerForm) {
    func_8082DE50(play, this);
    Player_SetAction_PreserveItemAction(play, this, Player_Action_86, 0);
    func_8082E4A4(play, this, D_8085D160[this->transformation]);
    gSaveContext.save.playerForm = playerForm;
    this->stateFlags1 |= PLAYER_STATE1_2;

    D_80862B50 = play->envCtx.adjLightSettings;
    this->actor.velocity.y = 0.0f;
    Actor_DeactivateLens(play);
}

void func_808389BC(PlayState* play, Player* this) {
    Player_SetAction_PreserveItemAction(play, this, Player_Action_89, 0);
    func_8082E4A4(play, this, &gPlayerAnim_cl_setmask);
    this->stateFlags1 |= (PLAYER_STATE1_100 | PLAYER_STATE1_20000000);
    func_8082DAD4(this);
}

void func_80838A20(PlayState* play, Player* this) {
    Player_SetAction_PreserveItemAction(play, this, Player_Action_90, 0);
    func_8082DB90(play, this, &gPlayerAnim_cl_maskoff);
    this->currentMask = PLAYER_MASK_NONE;
    this->stateFlags1 |= (PLAYER_STATE1_100 | PLAYER_STATE1_20000000);
    func_8082DAD4(this);
    Magic_Reset(play);
}

u8 sPlayerMass[PLAYER_FORM_MAX] = {
    100, // PLAYER_FORM_FIERCE_DEITY
    200, // PLAYER_FORM_GORON
    80,  // PLAYER_FORM_ZORA
    20,  // PLAYER_FORM_DEKU
    50,  // PLAYER_FORM_HUMAN
};

PlayerAnimationHeader* D_8085D17C[PLAYER_FORM_MAX] = {
    &gPlayerAnim_link_normal_okarina_start, // PLAYER_FORM_FIERCE_DEITY
    &gPlayerAnim_pg_gakkistart,             // PLAYER_FORM_GORON
    &gPlayerAnim_pz_gakkistart,             // PLAYER_FORM_ZORA
    &gPlayerAnim_pn_gakkistart,             // PLAYER_FORM_DEKU
    &gPlayerAnim_link_normal_okarina_start, // PLAYER_FORM_HUMAN
};
PlayerAnimationHeader* D_8085D190[PLAYER_FORM_MAX] = {
    &gPlayerAnim_link_normal_okarina_swing, // PLAYER_FORM_FIERCE_DEITY
    &gPlayerAnim_pg_gakkiplay,              // PLAYER_FORM_GORON
    &gPlayerAnim_pz_gakkiplay,              // PLAYER_FORM_ZORA
    &gPlayerAnim_pn_gakkiplay,              // PLAYER_FORM_DEKU
    &gPlayerAnim_link_normal_okarina_swing, // PLAYER_FORM_HUMAN
};

u8 D_8085D1A4[PLAYER_IA_MAX] = {
    GI_NONE,                // PLAYER_IA_NONE
    GI_NONE,                // PLAYER_IA_LAST_USED
    GI_NONE,                // PLAYER_IA_FISHING_ROD
    GI_SWORD_KOKIRI,        // PLAYER_IA_SWORD_KOKIRI
    GI_SWORD_RAZOR,         // PLAYER_IA_SWORD_RAZOR
    GI_SWORD_GILDED,        // PLAYER_IA_SWORD_GILDED
    GI_SWORD_GREAT_FAIRY,   // PLAYER_IA_SWORD_TWO_HANDED
    GI_DEKU_STICKS_1,       // PLAYER_IA_DEKU_STICK
    GI_SWORD_KOKIRI,        // PLAYER_IA_ZORA_FINS
    GI_QUIVER_30,           // PLAYER_IA_BOW
    GI_ARROW_FIRE,          // PLAYER_IA_BOW_FIRE
    GI_ARROW_ICE,           // PLAYER_IA_BOW_ICE
    GI_ARROW_LIGHT,         // PLAYER_IA_BOW_LIGHT
    GI_HOOKSHOT,            // PLAYER_IA_HOOKSHOT
    GI_BOMBS_1,             // PLAYER_IA_BOMB
    GI_POWDER_KEG,          // PLAYER_IA_POWDER_KEG
    GI_BOMBCHUS_10,         // PLAYER_IA_BOMBCHU
    GI_40,                  // PLAYER_IA_11
    GI_DEKU_NUTS_1,         // PLAYER_IA_DEKU_NUT
    GI_PICTOGRAPH_BOX,      // PLAYER_IA_PICTOGRAPH_BOX
    GI_OCARINA_OF_TIME,     // PLAYER_IA_OCARINA
    GI_BOTTLE,              // PLAYER_IA_BOTTLE_EMPTY
    GI_FISH,                // PLAYER_IA_BOTTLE_FISH
    GI_75,                  // PLAYER_IA_BOTTLE_SPRING_WATER
    GI_ICE_TRAP,            // PLAYER_IA_BOTTLE_HOT_SPRING_WATER
    GI_ZORA_EGG,            // PLAYER_IA_BOTTLE_ZORA_EGG
    GI_GOLD_DUST,           // PLAYER_IA_BOTTLE_DEKU_PRINCESS
    GI_6C,                  // PLAYER_IA_BOTTLE_GOLD_DUST
    GI_SEAHORSE,            // PLAYER_IA_BOTTLE_1C
    GI_MUSHROOM,            // PLAYER_IA_BOTTLE_SEAHORSE
    GI_HYLIAN_LOACH,        // PLAYER_IA_BOTTLE_MUSHROOM
    GI_DEKU_PRINCESS,       // PLAYER_IA_BOTTLE_HYLIAN_LOACH
    GI_BUG,                 // PLAYER_IA_BOTTLE_BUG
    GI_POE,                 // PLAYER_IA_BOTTLE_POE
    GI_BIG_POE,             // PLAYER_IA_BOTTLE_BIG_POE
    GI_POTION_RED,          // PLAYER_IA_BOTTLE_POTION_RED
    GI_POTION_BLUE,         // PLAYER_IA_BOTTLE_POTION_BLUE
    GI_POTION_GREEN,        // PLAYER_IA_BOTTLE_POTION_GREEN
    GI_MILK_HALF,           // PLAYER_IA_BOTTLE_MILK
    GI_MILK_HALF,           // PLAYER_IA_BOTTLE_MILK_HALF
    GI_CHATEAU,             // PLAYER_IA_BOTTLE_CHATEAU
    GI_FAIRY,               // PLAYER_IA_BOTTLE_FAIRY
    GI_MOONS_TEAR,          // PLAYER_IA_MOONS_TEAR
    GI_DEED_LAND,           // PLAYER_IA_DEED_LAND
    GI_ROOM_KEY,            // PLAYER_IA_ROOM_KEY
    GI_LETTER_TO_KAFEI,     // PLAYER_IA_LETTER_TO_KAFEI
    GI_MAGIC_BEANS,         // PLAYER_IA_MAGIC_BEANS
    GI_DEED_SWAMP,          // PLAYER_IA_DEED_SWAMP
    GI_DEED_MOUNTAIN,       // PLAYER_IA_DEED_MOUNTAIN
    GI_DEED_OCEAN,          // PLAYER_IA_DEED_OCEAN
    GI_MOONS_TEAR,          // PLAYER_IA_32
    GI_LETTER_TO_MAMA,      // PLAYER_IA_LETTER_MAMA
    GI_A7,                  // PLAYER_IA_34
    GI_A8,                  // PLAYER_IA_35
    GI_PENDANT_OF_MEMORIES, // PLAYER_IA_PENDANT_OF_MEMORIES
    GI_PENDANT_OF_MEMORIES, // PLAYER_IA_37
    GI_PENDANT_OF_MEMORIES, // PLAYER_IA_38
    GI_PENDANT_OF_MEMORIES, // PLAYER_IA_39
    GI_MASK_TRUTH,          // PLAYER_IA_MASK_TRUTH
    GI_MASK_KAFEIS_MASK,    // PLAYER_IA_MASK_KAFEIS_MASK
    GI_MASK_ALL_NIGHT,      // PLAYER_IA_MASK_ALL_NIGHT
    GI_MASK_BUNNY,          // PLAYER_IA_MASK_BUNNY
    GI_MASK_KEATON,         // PLAYER_IA_MASK_KEATON
    GI_MASK_GARO,           // PLAYER_IA_MASK_GARO
    GI_MASK_ROMANI,         // PLAYER_IA_MASK_ROMANI
    GI_MASK_CIRCUS_LEADER,  // PLAYER_IA_MASK_CIRCUS_LEADER
    GI_MASK_POSTMAN,        // PLAYER_IA_MASK_POSTMAN
    GI_MASK_COUPLE,         // PLAYER_IA_MASK_COUPLE
    GI_MASK_GREAT_FAIRY,    // PLAYER_IA_MASK_GREAT_FAIRY
    GI_MASK_GIBDO,          // PLAYER_IA_MASK_GIBDO
    GI_MASK_DON_GERO,       // PLAYER_IA_MASK_DON_GERO
    GI_MASK_KAMARO,         // PLAYER_IA_MASK_KAMARO
    GI_MASK_CAPTAIN,        // PLAYER_IA_MASK_CAPTAIN
    GI_MASK_STONE,          // PLAYER_IA_MASK_STONE
    GI_MASK_BREMEN,         // PLAYER_IA_MASK_BREMEN
    GI_MASK_BLAST,          // PLAYER_IA_MASK_BLAST
    GI_MASK_SCENTS,         // PLAYER_IA_MASK_SCENTS
    GI_MASK_GIANT,          // PLAYER_IA_MASK_GIANT
    GI_MASK_FIERCE_DEITY,   // PLAYER_IA_MASK_FIERCE_DEITY
    GI_MASK_GORON,          // PLAYER_IA_MASK_GORON
    GI_MASK_ZORA,           // PLAYER_IA_MASK_ZORA
    GI_MASK_DEKU,           // PLAYER_IA_MASK_DEKU
    GI_LENS_OF_TRUTH,       // PLAYER_IA_LENS_OF_TRUTH
};

PlayerAnimationHeader* D_8085D1F8[] = {
    &gPlayerAnim_link_normal_give_other,
    &gPlayerAnim_link_normal_take_out, // Hold up cutscene item; "this item doesn't work here"
};

s32 Player_ActionChange_13(Player* this, PlayState* play) {
    PlayerBottle bottleAction;

    if (this->unk_AA5 != PLAYER_UNKAA5_0) {
        if (!(this->actor.bgCheckFlags & (BGCHECKFLAG_GROUND | BGCHECKFLAG_GROUND_TOUCH)) &&
            !(this->stateFlags1 & PLAYER_STATE1_8000000) && !(this->stateFlags1 & PLAYER_STATE1_800000) &&
            !(this->stateFlags3 & PLAYER_STATE3_8) && !(this->skelAnime.moveFlags & ANIM_FLAG_8)) {
            Player_StopCutscene(this);
            func_80833AA0(this, play);
            return true;
        }
        if (!func_808387A0(play, this)) {
            if (this->unk_AA5 == PLAYER_UNKAA5_5) {
                if ((this->itemAction >= PLAYER_IA_MASK_MIN) && (this->itemAction <= PLAYER_IA_MASK_MAX)) {
                    PlayerMask maskId = GET_MASK_FROM_IA(this->itemAction);

                    this->prevMask = this->currentMask;
                    if ((u32)(maskId == this->currentMask) || (this->itemAction < PLAYER_IA_MASK_GIANT) ||
                        ((this->itemAction == PLAYER_IA_MASK_GIANT) && (this->transformation != PLAYER_FORM_HUMAN))) {
                        if (maskId == this->currentMask) {
                            this->currentMask = PLAYER_MASK_NONE;
                        } else {
                            this->currentMask = maskId;
                        }

                        if (this->transformation == PLAYER_FORM_HUMAN) {
                            func_80838A20(play, this);
                            return true;
                        }

                        func_808388B8(play, this, PLAYER_FORM_HUMAN);
                    } else {
                        this->currentMask = maskId;
                        if (this->currentMask == PLAYER_MASK_GIANT) {
                            func_808389BC(play, this);
                            return true;
                        }
                        func_808388B8(play, this, this->itemAction - PLAYER_IA_MASK_FIERCE_DEITY);
                    }
                    gSaveContext.save.equippedMask = this->currentMask;
                } else if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_TALK_REQUESTED) ||
                           (this->itemAction == PLAYER_IA_PICTOGRAPH_BOX) ||
                           ((this->itemAction != this->unk_B2B) &&
                            ((this->itemAction == PLAYER_IA_BOTTLE_BIG_POE) ||
                             ((this->itemAction >= PLAYER_IA_BOTTLE_ZORA_EGG) &&
                              (this->itemAction <= PLAYER_IA_BOTTLE_HYLIAN_LOACH)) ||
                             (this->itemAction > PLAYER_IA_BOTTLE_FAIRY) ||
                             ((this->talkActor != NULL) && (this->exchangeItemAction > PLAYER_IA_NONE) &&
                              (((this->exchangeItemAction == PLAYER_IA_MAGIC_BEANS) &&
                                (this->itemAction == PLAYER_IA_MAGIC_BEANS)) ||
                               ((this->exchangeItemAction != PLAYER_IA_MAGIC_BEANS) &&
                                (Player_BottleFromIA(this, this->itemAction) > PLAYER_BOTTLE_NONE))))))) {
                    Actor* talkActor;
                    s32 heldItemTemp = this->itemAction;

                    Player_StopCutscene(this);
                    this->itemAction = PLAYER_IA_NONE;
                    Player_SetAction_PreserveItemAction(play, this, Player_Action_71, 0);
                    talkActor = this->talkActor;
                    this->itemAction = heldItemTemp;
                    this->csId = CS_ID_NONE;

                    if ((talkActor != NULL) && (((this->exchangeItemAction == PLAYER_IA_MAGIC_BEANS) &&
                                                 (this->itemAction == PLAYER_IA_MAGIC_BEANS)) ||
                                                ((this->exchangeItemAction != PLAYER_IA_MAGIC_BEANS) &&
                                                 (this->exchangeItemAction > PLAYER_IA_NONE)))) {
                        this->stateFlags1 |= (PLAYER_STATE1_20000000 | PLAYER_STATE1_40);
                        if (this->exchangeItemAction == PLAYER_IA_MAGIC_BEANS) {
                            Inventory_ChangeAmmo(ITEM_MAGIC_BEANS, -1);
                            Player_SetAction_PreserveItemAction(play, this, Player_Action_17, 0);
                            this->currentYaw = talkActor->yawTowardsPlayer + 0x8000;
                            this->actor.shape.rot.y = this->currentYaw;
                            if (talkActor->xzDistToPlayer < 40.0f) {
                                func_8082DB90(play, this, &gPlayerAnim_link_normal_backspace);
                                func_8082E920(play, this, ANIM_FLAG_1 | ANIM_FLAG_8 | ANIM_FLAG_NOMOVE);
                            } else {
                                func_8082E438(play, this, D_8085BE84[31][this->modelAnimType]);
                            }
                            this->stateFlags1 |= PLAYER_STATE1_20000000;
                            this->actionVar2 = 80;
                            this->actionVar1 = -1;
                            this->lockOnActor = this->talkActor;
                        } else {
                            this->csId = CS_ID_GLOBAL_TALK;
                        }

                        talkActor->flags |= ACTOR_FLAG_TALK_REQUESTED;
                        this->actor.textId = 0;
                        this->lockOnActor = this->talkActor;
                    } else {
                        this->stateFlags1 |= (PLAYER_STATE1_20000000 | PLAYER_STATE1_10000000 | PLAYER_STATE1_40);
                        this->csId = play->playerCsIds[PLAYER_CS_ID_ITEM_SHOW];
                        this->actionVar1 = 1;
                        this->actor.textId = 0xFE;
                    }
                    this->actor.flags |= ACTOR_FLAG_TALK_REQUESTED;
                    this->exchangeItemAction = this->itemAction;
                    if (this->actionVar1 >= 0) {
                        Player_AnimationPlayOnce(play, this, D_8085D1F8[this->actionVar1]);
                    }
                    func_8082DAD4(this);
                    return true;
                } else {
                    bottleAction = Player_BottleFromIA(this, this->itemAction);

                    if (bottleAction > PLAYER_BOTTLE_NONE) {
                        Player_StopCutscene(this);
                        if (bottleAction >= PLAYER_BOTTLE_FAIRY) {
                            Player_SetAction_PreserveItemAction(play, this, Player_Action_69, 0);
                            func_8082DB90(play, this, &gPlayerAnim_link_bottle_bug_out);
                        } else if ((bottleAction > PLAYER_BOTTLE_EMPTY) && (bottleAction < PLAYER_BOTTLE_POE)) {
                            Player_SetAction_PreserveItemAction(play, this, Player_Action_70, 0);
                            func_8082DB90(play, this, &gPlayerAnim_link_bottle_fish_out);
                            this->csId = play->playerCsIds[PLAYER_CS_ID_ITEM_BOTTLE];
                        } else {
                            Player_SetAction_PreserveItemAction(play, this, Player_Action_67, 0);
                            func_8082E4A4(play, this,
                                          (this->transformation == PLAYER_FORM_DEKU)
                                              ? &gPlayerAnim_pn_drinkstart
                                              : &gPlayerAnim_link_bottle_drink_demo_start);
                        }
                    } else {
                        Actor* actorUnkA90 = this->unk_A90;

                        if ((actorUnkA90 == NULL) || (actorUnkA90->id == ACTOR_EN_ZOT) ||
                            (actorUnkA90->csId == CS_ID_NONE)) {
                            if (!func_808323C0(this, play->playerCsIds[PLAYER_CS_ID_ITEM_OCARINA])) {
                                return false;
                            }
                        } else {
                            this->csId = CS_ID_NONE;
                        }
                        Player_SetAction_PreserveItemAction(play, this, Player_Action_63, 0);
                        if ((this->skelAnime.playSpeed < 0.0f) ||
                            ((this->skelAnime.animation != D_8085D17C[this->transformation]) &&
                             (this->skelAnime.animation != D_8085D190[this->transformation]))) {
                            func_8082DB90(play, this, D_8085D17C[this->transformation]);
                        }
                        this->stateFlags2 |= PLAYER_STATE2_8000000;
                        if (actorUnkA90 != NULL) {
                            this->actor.flags |= ACTOR_FLAG_20000000;
                            if (actorUnkA90->id == ACTOR_EN_ZOT) {
                                this->unk_A94 = -1.0f;
                            } else {
                                actorUnkA90->flags |= ACTOR_FLAG_20000000;
                            }
                        }
                    }
                }
            } else {
                if (func_8083868C(play, this) != CAM_MODE_NORMAL) {
                    Player_StopCutscene(this);
                    if (!(this->stateFlags1 & PLAYER_STATE1_800000)) {
                        Player_SetAction(play, this, Player_Action_43, 1);
                        this->actionVar2 = 13;
                        func_80836D8C(this);
                        if (this->unk_AA5 == PLAYER_UNKAA5_2) {
                            play->actorCtx.flags |= ACTORCTX_FLAG_PICTO_BOX_ON;
                        }
                    }
                    this->stateFlags1 |= PLAYER_STATE1_100000;
                    Audio_PlaySfx(NA_SE_SY_CAMERA_ZOOM_UP);
                    Player_StopHorizontalMovement(this);
                    return true;
                }
                this->unk_AA5 = PLAYER_UNKAA5_0;
                Audio_PlaySfx(NA_SE_SY_ERROR);
                return false;
            }
            this->stateFlags1 |= (PLAYER_STATE1_20000000 | PLAYER_STATE1_10000000);
            func_8082DAD4(this);
        }
        return true;
    }
    return false;
}

s32 Player_ActionChange_4(Player* this, PlayState* play) {
    if (gSaveContext.save.saveInfo.playerData.health != 0) {
        Actor* talkActor = this->talkActor;
        Actor* lockOnActor = this->lockOnActor;
        Actor* var_a1 = NULL;
        s32 var_t1 = false;
        s32 var_t2 = false;

        if (this->tatlActor != NULL) {
            var_t2 = (lockOnActor != NULL) &&
                     (CHECK_FLAG_ALL(lockOnActor->flags, ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_40000) ||
                      (lockOnActor->hintId != TATL_HINT_ID_NONE));

            if (var_t2 || (this->tatlTextId != 0)) {
                //! @bug The comparison `((ABS_ALT(this->tatlTextId) & 0xFF00) != 0x10000)` always evaluates to `true`
                var_t1 = (this->tatlTextId < 0) && ((ABS_ALT(this->tatlTextId) & 0xFF00) != 0x10000);

                if (var_t1 || !var_t2) {
                    var_a1 = this->tatlActor;
                    if (var_t1) {
                        lockOnActor = NULL;
                        talkActor = NULL;
                    }
                } else {
                    var_a1 = lockOnActor;
                }
            }
        }

        if ((talkActor != NULL) || (var_a1 != NULL)) {
            if ((lockOnActor == NULL) || (lockOnActor == talkActor) || (lockOnActor == var_a1)) {
                if (!(this->stateFlags1 & PLAYER_STATE1_800) ||
                    ((this->heldActor != NULL) &&
                     (var_t1 || (talkActor == this->heldActor) || (var_a1 == this->heldActor) ||
                      ((talkActor != NULL) && (talkActor->flags & ACTOR_FLAG_10000))))) {
                    if (((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) ||
                         (this->stateFlags1 & PLAYER_STATE1_800000) || func_801242B4(this))) {
                        if (talkActor != NULL) {
                            if ((lockOnActor == NULL) || (lockOnActor == talkActor)) {
                                this->stateFlags2 |= PLAYER_STATE2_2;
                            }

                            if (!CutsceneManager_IsNext(CS_ID_GLOBAL_TALK)) {
                                return false;
                            }

                            if (CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_A) ||
                                (talkActor->flags & ACTOR_FLAG_10000)) {
                                var_a1 = NULL;
                            } else if (var_a1 == NULL) {
                                return false;
                            }
                        }

                        if (var_a1 != NULL) {
                            if (!var_t1) {
                                this->stateFlags2 |= PLAYER_STATE2_200000;
                                if (!CutsceneManager_IsNext(CS_ID_GLOBAL_TALK) ||
                                    !CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_CUP)) {
                                    return false;
                                }
                            }

                            talkActor = var_a1;
                            this->talkActor = NULL;

                            if (var_t1 || !var_t2) {
                                var_a1->textId = ABS_ALT(this->tatlTextId);
                            } else if (var_a1->hintId != 0xFF) {
                                var_a1->textId = var_a1->hintId + 0x1900;
                            }
                        }

                        this->currentMask = D_80862B2C;
                        gSaveContext.save.equippedMask = this->currentMask;
                        Player_TalkWithPlayer(play, talkActor);
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

s32 Player_ActionChange_0(Player* this, PlayState* play) {
    if (this->unk_AA5 != PLAYER_UNKAA5_0) {
        Player_ActionChange_13(this, play);
        return true;
    } else if ((this->lockOnActor != NULL) &&
               (CHECK_FLAG_ALL(this->lockOnActor->flags, ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_40000) ||
                (this->lockOnActor->hintId != TATL_HINT_ID_NONE))) {
        this->stateFlags2 |= PLAYER_STATE2_200000;
    } else if ((this->tatlTextId == 0) && !func_80123420(this) &&
               CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_CUP) &&
               !func_80831814(this, play, PLAYER_UNKAA5_1)) {
        Audio_PlaySfx(NA_SE_SY_ERROR);
    }
    return false;
}

// Jumpslash/Jumpkick start
void func_808395F0(PlayState* play, Player* this, PlayerMeleeWeaponAnimation meleeWeaponAnim, f32 linearVelocity,
                   f32 yVelocity) {
    if (this->transformation == PLAYER_FORM_ZORA) {
        linearVelocity *= 1.1f;
        meleeWeaponAnim = PLAYER_MWA_ZORA_JUMPKICK_START;
        yVelocity *= 0.9f;
    }

    func_80833864(play, this, meleeWeaponAnim);
    Player_SetAction(play, this, Player_Action_29, 0);
    this->stateFlags3 |= PLAYER_STATE3_2;
    this->linearVelocity = linearVelocity;
    this->currentYaw = this->actor.shape.rot.y;
    this->actor.velocity.y = yVelocity;
    this->actor.bgCheckFlags &= ~BGCHECKFLAG_GROUND;
    Player_AnimSfx_PlayFloorJump(this);
    Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_SWORD_L);
}

s32 func_808396B8(PlayState* play, Player* this) {
    if (!(this->stateFlags1 & PLAYER_STATE1_400000) &&
        (((this->actor.id != ACTOR_PLAYER) && CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_B)) ||
         ((Player_GetMeleeWeaponHeld(this) != PLAYER_MELEEWEAPON_NONE) &&
          ((this->transformation != PLAYER_FORM_GORON) || (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) &&
          ((this->transformation != PLAYER_FORM_ZORA) || !(this->stateFlags1 & PLAYER_STATE1_2000000)) &&
          sPlayerUseHeldItem))) {
        return true;
    }

    return false;
}

s32 func_80839770(Player* this, PlayState* play) {
    if (func_808396B8(play, this)) {
        if ((this->transformation != PLAYER_FORM_GORON) && (sPlayerFloorType != FLOOR_TYPE_7)) {
            func_808395F0(play, this,
                          (this->transformation == PLAYER_FORM_ZORA) ? PLAYER_MWA_ZORA_JUMPKICK_START
                                                                     : PLAYER_MWA_JUMPSLASH_START,
                          3.0f, 4.5f);
            return true;
        }
    }
    return false;
}

s32 func_80839800(Player* this, PlayState* play) {
    if ((this->unk_AE3[this->unk_ADE] == 0) && (sPlayerFloorType != FLOOR_TYPE_7)) {
        func_80836B3C(play, this, 0.0f);
        return true;
    }
    return false;
}

void func_80839860(Player* this, PlayState* play, s32 arg2) {
    s32 pad;
    f32 speed = (!(arg2 & 1) ? 5.8f : 3.5f);

    if (this->currentBoots == PLAYER_BOOTS_GIANT) {
        speed /= 2.0f;
    }

    //! FAKE
    if (arg2 == 2) {}

    func_80834D50(play, this, D_8085C2A4[arg2].unk_0, speed, NA_SE_VO_LI_SWORD_N);

    this->actionVar2 = 1;
    this->actionVar1 = arg2;

    this->currentYaw = this->actor.shape.rot.y + (arg2 << 0xE);
    this->linearVelocity = !(arg2 & 1) ? 6.0f : 8.5f;

    this->stateFlags2 |= PLAYER_STATE2_80000;
    Player_PlaySfx(this, ((arg2 << 0xE) == 0x8000) ? NA_SE_PL_ROLL : NA_SE_PL_SKIP);
}

void func_80839978(PlayState* play, Player* this) {
    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        this->itemAction = PLAYER_IA_OCARINA;
        Player_SetAction_PreserveItemAction(play, this, Player_Action_11, 0);
        func_8082DB60(play, this, &gPlayerAnim_clink_normal_okarina_walk);
        func_8082E920(play, this, ANIM_FLAG_4 | ANIM_FLAG_200);
        this->stateFlags3 |= PLAYER_STATE3_20000000;
        this->unk_B48 = this->linearVelocity;
        Audio_PlayFanfare(NA_BGM_BREMEN_MARCH);
    }
}

void func_80839A10(PlayState* play, Player* this) {
    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        this->itemAction = PLAYER_IA_NONE;
        Player_SetAction_PreserveItemAction(play, this, Player_Action_12, 0);
        func_8082DB60(play, this, &gPlayerAnim_alink_dance_loop);
        this->stateFlags2 |= PLAYER_STATE2_2000000;
        Audio_PlayFanfare(NA_BGM_KAMARO_DANCE);
    }
}

s32 func_80839A84(PlayState* play, Player* this) {
    if (this->transformation == PLAYER_FORM_DEKU) {
        if (func_80836DC0(play, this)) {
            return true;
        }
    } else {
        return false;
    }

    Player_SetAction(play, this, Player_Action_95, 0);
    this->stateFlags1 &= ~(PLAYER_STATE1_20000 | PLAYER_STATE1_40000000);
    this->unk_ADC = 4;
    func_808373A4(play, this);
    return true;
}

s32 Player_ActionChange_10(Player* this, PlayState* play) {
    if (CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_A) &&
        (play->roomCtx.curRoom.behaviorType1 != ROOM_BEHAVIOR_TYPE1_2) && (sPlayerFloorType != FLOOR_TYPE_7) &&
        (sPlayerFloorEffect != FLOOR_EFFECT_1)) {
        s32 temp_a2 = this->unk_AE3[this->unk_ADE];

        if (temp_a2 <= 0) {
            if (func_8082FBE8(this)) {
                if (this->actor.category != ACTORCAT_PLAYER) {
                    if (temp_a2 < 0) {
                        func_80834DB8(this, &gPlayerAnim_link_normal_jump, REG(69) / 100.0f, play);
                    } else {
                        func_80836B3C(play, this, 0.0f);
                    }
                } else if (!(this->stateFlags1 & PLAYER_STATE1_8000000) &&
                           (Player_GetMeleeWeaponHeld(this) != PLAYER_MELEEWEAPON_NONE) &&
                           Player_CanUpdateItems(this) && (this->transformation != PLAYER_FORM_GORON)) {
                    func_808395F0(play, this, PLAYER_MWA_JUMPSLASH_START, 5.0f, 5.0f);
                } else if (!func_80839A84(play, this)) {
                    func_80836B3C(play, this, 0.0f);
                }

                return true;
            }
        } else {
            func_80839860(this, play, temp_a2);
            return true;
        }
    }

    return false;
}

void func_80839CD8(Player* this, PlayState* play) {
    PlayerAnimationHeader* anim;
    f32 var_fv0 = this->unk_B38 - 3.0f;

    if (var_fv0 < 0.0f) {
        var_fv0 += 29.0f;
    }

    if (var_fv0 < 14.0f) {
        anim = D_8085BE84[PLAYER_ANIMGROUP_17][this->modelAnimType];
        var_fv0 = 11.0f - var_fv0;
        if (var_fv0 < 0.0f) {
            var_fv0 = -var_fv0 * 1.375f;
        }
        var_fv0 = var_fv0 / 11.0f;
    } else {
        anim = D_8085BE84[PLAYER_ANIMGROUP_18][this->modelAnimType];
        var_fv0 = 26.0f - var_fv0;
        if (var_fv0 < 0.0f) {
            var_fv0 = -var_fv0 * 2;
        }
        var_fv0 = var_fv0 / 12.0f;
    }

    PlayerAnimation_Change(play, &this->skelAnime, anim, 1.0f, 0.0f, Animation_GetLastFrame(anim), ANIMMODE_ONCE,
                           4.0f * var_fv0);
    this->currentYaw = this->actor.shape.rot.y;
}

void func_80839E3C(Player* this, PlayState* play) {
    func_808369F4(this, play);
    func_80839CD8(this, play);
}

void func_80839E74(Player* this, PlayState* play) {
    Player_SetAction(play, this, Player_Action_4, 1);
    Player_AnimationPlayOnce(play, this, func_8082ED20(this));
    this->currentYaw = this->actor.shape.rot.y;
}

void func_80839ED0(Player* this, PlayState* play) {
    if (!(this->stateFlags3 & PLAYER_STATE3_80) && (Player_Action_64 != this->actionFunc) && !func_8083213C(this)) {
        func_80836D8C(this);
        if (!(this->stateFlags1 & PLAYER_STATE1_40)) {
            if (func_801242B4(this)) {
                func_808353DC(play, this);
            } else {
                func_80836988(this, play);
            }
        }
        if (this->unk_AA5 < PLAYER_UNKAA5_5) {
            this->unk_AA5 = PLAYER_UNKAA5_0;
        }
    }
    this->stateFlags1 &= ~(PLAYER_STATE1_4 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000 | PLAYER_STATE1_100000);
}

s32 func_80839F98(PlayState* play, Player* this) {
    if (!(this->stateFlags1 & PLAYER_STATE1_8000000)) {
        if (this->linearVelocity != 0.0f) {
            func_80836B3C(play, this, 0.0f);
            return true;
        }
        func_80836AD8(play, this);
        PlayerAnimation_Change(play, &this->skelAnime, &gPlayerAnim_pg_maru_change, 2.0f / 3.0f, 0.0f, 7.0f,
                               ANIMMODE_ONCE, 0.0f);
        return true;
    }
    return false;
}

// Toggles swimming/walking underwater as Zora
void func_8083A04C(Player* this) {
    if (this->currentBoots == PLAYER_BOOTS_ZORA_UNDERWATER) {
        if (CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_A)) {
            this->currentBoots = PLAYER_BOOTS_ZORA_LAND;
        }
        if (Player_Action_54 == this->actionFunc) {
            this->actionVar2 = 20;
        }
    } else {
        if (CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_B)) {
            this->currentBoots = PLAYER_BOOTS_ZORA_UNDERWATER;
        }
    }
}

s32 Player_ActionChange_14(Player* this, PlayState* play) {
    if (!D_80862B04 && (this->transformation == PLAYER_FORM_ZORA)) {
        func_8083A04C(this);
    }
    return false;
}

s32 Player_ActionChange_6(Player* this, PlayState* play) {
    if (!D_80862B04 && !(this->stateFlags1 & PLAYER_STATE1_800000) && !func_8082FB68(this)) {
        if ((this->transformation == PLAYER_FORM_ZORA) && (this->stateFlags1 & PLAYER_STATE1_8000000)) {
            func_8083A04C(this);
        } else if (CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_A) && !func_8082FB68(this)) {
            if (this->transformation == PLAYER_FORM_GORON) {
                if (func_80839F98(play, this)) {
                    return true;
                }
            } else if (func_80839A84(play, this) || func_80839800(this, play)) {
                return true;
            }

            if ((this->putAwayCountdown == 0) && (this->heldItemAction >= PLAYER_IA_SWORD_KOKIRI) &&
                (this->transformation != PLAYER_FORM_FIERCE_DEITY)) {
                Player_UseItem(play, this, ITEM_NONE);
            } else {
                this->stateFlags2 ^= PLAYER_STATE2_100000;
            }
        }
    }

    return false;
}

s32 Player_ActionChange_11(Player* this, PlayState* play) {
    if (CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_R) && (this->unk_AA5 == PLAYER_UNKAA5_0) &&
        (play->unk_1887C == 0)) {
        if (Player_IsGoronOrDeku(this) ||
            ((((this->transformation == PLAYER_FORM_ZORA) && !(this->stateFlags1 & PLAYER_STATE1_2000000)) ||
              ((this->transformation == PLAYER_FORM_HUMAN) && (this->currentShield != PLAYER_SHIELD_NONE))) &&
             !func_80123434(this) && (this->lockOnActor == NULL))) {
            func_8082DC38(this);
            Player_DetachHeldActor(play, this);
            if (Player_SetAction(play, this, Player_Action_18, 0)) {
                this->stateFlags1 |= PLAYER_STATE1_400000;
                if (this->transformation != PLAYER_FORM_GORON) {
                    PlayerAnimationHeader* anim;
                    f32 endFrame;

                    if (!Player_IsGoronOrDeku(this)) {
                        Player_SetModelsForHoldingShield(this);
                        anim = D_8085BE84[PLAYER_ANIMGROUP_19][this->modelAnimType];
                    } else {
                        anim = (this->transformation == PLAYER_FORM_DEKU) ? &gPlayerAnim_pn_gurd
                                                                          : &gPlayerAnim_clink_normal_defense_ALL;
                    }

                    if (anim != this->skelAnime.animation) {
                        if (func_80123420(this)) {
                            this->unk_B3C = 1.0f;
                        } else {
                            this->unk_B3C = 0.0f;
                            func_8082FC60(this);
                        }
                        this->upperLimbRot.x = 0;
                        this->upperLimbRot.y = 0;
                        this->upperLimbRot.z = 0;
                    }

                    endFrame = Animation_GetLastFrame(anim);
                    PlayerAnimation_Change(play, &this->skelAnime, anim, 2.0f / 3.0f,
                                           (anim == &gPlayerAnim_pn_gurd) ? 0.0f : endFrame, endFrame, ANIMMODE_ONCE,
                                           0.0f);
                }
                func_80830AE8(this);
            }

            return true;
        }
    }

    return false;
}

s32 func_8083A4A4(Player* this, f32* arg1, s16* arg2, f32 arg3) {
    s16 yaw = this->currentYaw - *arg2;

    if (ABS_ALT(yaw) > 0x6000) {
        if (Math_StepToF(&this->linearVelocity, 0.0f, arg3)) {
            *arg1 = 0.0f;
            *arg2 = this->currentYaw;
        } else {
            return true;
        }
    }
    return false;
}

void func_8083A548(Player* this) {
    if ((this->unk_ADC > 0) && !CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_B)) {
        this->unk_ADC = -this->unk_ADC;
    }
}

s32 Player_ActionChange_8(Player* this, PlayState* play) {
    if (CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_B)) {
        if (!(this->stateFlags1 & PLAYER_STATE1_400000) &&
            (Player_GetMeleeWeaponHeld(this) != PLAYER_MELEEWEAPON_NONE)) {
            if ((this->unk_ADC > 0) && (((this->transformation == PLAYER_FORM_ZORA)) ||
                                        ((this->unk_ADC == 1) && (this->heldItemAction != PLAYER_IA_DEKU_STICK)))) {
                if (this->transformation == PLAYER_FORM_ZORA) {
                    func_80830E30(this, play);
                } else {
                    func_808335B0(play, this);
                }
                return true;
            }
        }
    } else {
        func_8083A548(this);
    }
    return false;
}

s32 func_8083A658(PlayState* play, Player* this) {
    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        Player_SetAction(play, this, Player_Action_64, 0);
        Player_AnimationPlayOnce(play, this, &gPlayerAnim_link_normal_light_bom);
        this->unk_AA5 = PLAYER_UNKAA5_0;
        return true;
    }
    return false;
}

struct_8085D200 D_8085D200[] = {
    { &gPlayerAnim_link_bottle_bug_miss, &gPlayerAnim_link_bottle_bug_in, 2, 3 },
    { &gPlayerAnim_link_bottle_fish_miss, &gPlayerAnim_link_bottle_fish_in, 5, 3 },
};

s32 func_8083A6C0(PlayState* play, Player* this) {
    if (sPlayerUseHeldItem) {
        if (Player_GetBottleHeld(this) > PLAYER_BOTTLE_NONE) {
            Player_SetAction(play, this, Player_Action_68, 0);
            if (this->actor.depthInWater > 12.0f) {
                this->actionVar2 = 1;
            }
            func_8082DB90(play, this, D_8085D200[this->actionVar2].unk_0);
            Player_PlaySfx(this, NA_SE_IT_SWORD_SWING);
            Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_AUTO_JUMP);
            return true;
        }
        return false;
    }
    return false;
}

void func_8083A794(Player* this, PlayState* play) {
    if ((Player_Action_13 != this->actionFunc) && (Player_Action_14 != this->actionFunc)) {
        this->unk_B70 = 0;
        this->unk_B34 = 0.0f;
        this->unk_B38 = 0.0f;
        func_8082E514(play, this, D_8085BE84[PLAYER_ANIMGROUP_2][this->modelAnimType]);
    }

    Player_SetAction(play, this, func_8082FBE8(this) ? Player_Action_14 : Player_Action_13, 1);
}

void func_8083A844(Player* this, PlayState* play, s16 currentYaw) {
    this->currentYaw = currentYaw;
    this->actor.shape.rot.y = this->currentYaw;
    func_8083A794(this, play);
}

s32 func_8083A878(PlayState* play, Player* this, f32 arg2) {
    WaterBox* waterBox;
    f32 ySurface = this->actor.world.pos.y;

    if (WaterBox_GetSurface1(play, &play->colCtx, this->actor.world.pos.x, this->actor.world.pos.z, &ySurface,
                             &waterBox)) {
        ySurface -= this->actor.world.pos.y;
        if (this->ageProperties->unk_24 <= ySurface) {
            Player_SetAction(play, this, Player_Action_55, 0);
            func_8082E634(play, this, &gPlayerAnim_link_swimer_swim);
            this->stateFlags1 |= (PLAYER_STATE1_8000000 | PLAYER_STATE1_20000000);
            this->actionVar2 = 20;
            this->linearVelocity = 2.0f;
            func_80123140(play, this);
            return false;
        }
    }
    func_80835324(play, this, arg2, this->actor.shape.rot.y);
    this->stateFlags1 |= PLAYER_STATE1_20000000;
    return true;
}

/**
 * Update for using telescopes. SCENE_AYASHIISHOP acts quite differently: it has a different camera mode and cannot use
 * zooming.
 *
 * - Stick inputs move the view; shape.rot.y is used as a base position which cannot be looked too far away from. (This
 * is not necessarily the same as the original angle of the spawn.)
 * - A can be used to zoom (except in SCENE_AYASHIISHOP)
 * - B exits, using the RESPAWN_MODE_DOWN entrance
 */
void func_8083A98C(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Player* this = THIS;
    s32 camMode;

    if (play->csCtx.state != CS_STATE_IDLE) {
        return;
    }

    if (DECR(this->actionVar2) != 0) {
        camMode = (play->sceneId != SCENE_AYASHIISHOP) ? CAM_MODE_FIRSTPERSON : CAM_MODE_DEKUHIDE;

        // Show controls overlay. SCENE_AYASHIISHOP does not have Zoom, so has a different one.
        if (this->actionVar2 == 1) {
            Message_StartTextbox(play, (play->sceneId == SCENE_AYASHIISHOP) ? 0x2A00 : 0x5E6, NULL);
        }
    } else {
        sPlayerControlInput = play->state.input;
        if (play->view.fovy >= 25.0f) {
            s16 prevFocusX = thisx->focus.rot.x;
            s16 prevFocusY = thisx->focus.rot.y;
            s16 inputY;
            s16 inputX;
            s16 newYaw; // from base position shape.rot.y

            // Pitch:
            inputY = sPlayerControlInput->rel.stick_y * 4;
            // Add input, clamped to prevent turning too fast
            thisx->focus.rot.x += CLAMP(inputY, -0x12C, 0x12C);
            // Prevent looking too far up or down
            thisx->focus.rot.x = CLAMP(thisx->focus.rot.x, -0x2EE0, 0x2EE0);

            // Yaw: shape.rot.y is used as a fixed starting position
            inputX = sPlayerControlInput->rel.stick_x * -4;
            // Start from current position: no input -> no change
            newYaw = thisx->focus.rot.y - thisx->shape.rot.y;
            // Add input, clamped to prevent turning too fast
            newYaw += CLAMP(inputX, -0x12C, 0x12C);
            // Prevent looking too far left or right of base position
            newYaw = CLAMP(newYaw, -0x3E80, 0x3E80);
            thisx->focus.rot.y = thisx->shape.rot.y + newYaw;

            if (play->sceneId == SCENE_00KEIKOKU) {
                f32 focusDeltaX = (s16)(thisx->focus.rot.x - prevFocusX);
                f32 focusDeltaY = (s16)(thisx->focus.rot.y - prevFocusY);

                Audio_PlaySfx_AtPosWithFreq(&gSfxDefaultPos, NA_SE_PL_TELESCOPE_MOVEMENT - SFX_FLAG,
                                            sqrtf(SQ(focusDeltaX) + SQ(focusDeltaY)) / 300.0f);
            }
        }

        if (play->sceneId == SCENE_AYASHIISHOP) {
            camMode = CAM_MODE_DEKUHIDE;
        } else if (CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_A)) { // Zoom
            camMode = CAM_MODE_TARGET;
        } else {
            camMode = CAM_MODE_NORMAL;
        }

        // Exit
        if (CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_B)) {
            Message_CloseTextbox(play);

            if (play->sceneId == SCENE_00KEIKOKU) {
                gSaveContext.respawn[RESPAWN_MODE_DOWN].entrance = ENTRANCE(ASTRAL_OBSERVATORY, 2);
            } else {
                u16 entrance;

                if (play->sceneId == SCENE_AYASHIISHOP) {
                    entrance = ENTRANCE(CURIOSITY_SHOP, 3);
                } else {
                    entrance = ENTRANCE(PIRATES_FORTRESS_INTERIOR, 8);
                }
                gSaveContext.respawn[RESPAWN_MODE_DOWN].entrance = entrance;
            }

            func_80169EFC(&play->state);
            gSaveContext.respawnFlag = -2;
            play->transitionType = TRANS_TYPE_CIRCLE;
        }
    }

    Camera_ChangeSetting(Play_GetCamera(play, CAM_ID_MAIN), CAM_SET_TELESCOPE);
    Camera_ChangeMode(Play_GetCamera(play, CAM_ID_MAIN), camMode);
}

// Set up using a telescope
void Player_InitMode_Telescope(PlayState* play, Player* this) {
    this->actor.update = func_8083A98C;
    this->actor.draw = NULL;
    if (play->sceneId == SCENE_00KEIKOKU) {
        this->actor.focus.rot.x = 0xBD8;
        this->actor.focus.rot.y = -0x4D74;
        this->actionVar2 = 20;
    } else if (play->sceneId == SCENE_AYASHIISHOP) {
        this->actor.focus.rot.x = 0x9A6;
        this->actor.focus.rot.y = 0x2102;
        this->actionVar2 = 2;
    } else {
        this->actor.focus.rot.x = 0x9A6;
        this->actor.focus.rot.y = 0x2102;
        this->actionVar2 = 20;
    }
    play->actorCtx.flags |= ACTORCTX_FLAG_1;
}

void Player_InitMode_B(PlayState* play, Player* this) {
    func_8085B384(this, play);
}

void Player_InitMode_D(PlayState* play, Player* this) {
    if (func_8083A878(play, this, 180.0f)) {
        this->actionVar2 = -20;
    }
}

// InitModes 0xA and 0xE
void func_8083ADF0(PlayState* play, Player* this) {
    this->linearVelocity = 2.0f;
    gSaveContext.entranceSpeed = 2.0f;

    if (func_8083A878(play, this, 120.0f)) {
        this->actionVar2 = -15;
    }
}

void Player_InitMode_F(PlayState* play, Player* this) {
    if (gSaveContext.entranceSpeed < 0.1f) {
        gSaveContext.entranceSpeed = 0.1f;
    }

    this->linearVelocity = gSaveContext.entranceSpeed;
    if (func_8083A878(play, this, 800.0f)) {
        this->actionVar2 = -80.0f / this->linearVelocity;
        if (this->actionVar2 < -20) {
            this->actionVar2 = -20;
        }
    }
}

void func_8083AECC(Player* this, s16 currentYaw, PlayState* play) {
    Player_SetAction(play, this, Player_Action_6, 1);
    PlayerAnimation_CopyJointToMorph(play, &this->skelAnime);
    this->unk_B38 = 0.0f;
    this->unk_B34 = 0.0f;
    this->currentYaw = currentYaw;
}

void func_8083AF30(Player* this, PlayState* play) {
    Player_SetAction(play, this, Player_Action_5, 1);
    func_8082E514(play, this, D_8085BE84[PLAYER_ANIMGROUP_1][this->modelAnimType]);
}

void func_8083AF8C(Player* this, s16 currentYaw, PlayState* play) {
    Player_SetAction(play, this, Player_Action_15, 1);
    PlayerAnimation_Change(play, &this->skelAnime, &gPlayerAnim_link_anchor_back_walk, 1.0f, 0.0f,
                           Animation_GetLastFrame(&gPlayerAnim_link_anchor_back_walk), ANIMMODE_ONCE, -6.0f);
    this->linearVelocity = 8.0f;
    this->currentYaw = currentYaw;
}

void func_8083B030(Player* this, PlayState* play) {
    Player_SetAction(play, this, Player_Action_9, 1);
    func_8082E514(play, this, D_8085BE84[PLAYER_ANIMGROUP_24][this->modelAnimType]);
    this->unk_B38 = 0.0f;
}

void func_8083B090(Player* this, PlayState* play) {
    Player_SetAction(play, this, Player_Action_16, 1);
    PlayerAnimation_PlayOnceSetSpeed(play, &this->skelAnime, &gPlayerAnim_link_anchor_back_brake, 6.0f / 3.0f);
}

void func_8083B0E4(PlayState* play, Player* this, s16 currentYaw) {
    this->currentYaw = currentYaw;
    Player_SetAction(play, this, Player_Action_10, 1);
    this->unk_B4E = 1200;
    this->unk_B4E *= D_8085C3E4;
    PlayerAnimation_Change(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_25][this->modelAnimType], 1.0f, 0.0f,
                           0.0f, ANIMMODE_LOOP, -6.0f);
}

void func_8083B1A0(Player* this, PlayState* play) {
    PlayerAnimationHeader* anim;

    Player_SetAction(play, this, Player_Action_4, 1);
    if (this->unk_B40 < 0.5f) {
        anim = D_8085BE84[PLAYER_ANIMGROUP_27][this->modelAnimType];
    } else {
        anim = D_8085BE84[PLAYER_ANIMGROUP_26][this->modelAnimType];
    }
    Player_AnimationPlayOnce(play, this, anim);
    this->currentYaw = this->actor.shape.rot.y;
}

void func_8083B23C(Player* this, PlayState* play) {
    Player_SetAction(play, this, Player_Action_2, 1);
    func_8082E438(play, this, D_8085BE84[PLAYER_ANIMGROUP_6][this->modelAnimType]);
    this->actionVar2 = 1;
}

void func_8083B29C(Player* this, PlayState* play) {
    if (this->linearVelocity != 0.0f) {
        func_8083A794(this, play);
    } else {
        func_8083B1A0(this, play);
    }
}

void func_8083B2E4(Player* this, PlayState* play) {
    if (this->linearVelocity != 0.0f) {
        func_8083A794(this, play);
    } else {
        func_80836988(this, play);
    }
}

void func_8083B32C(PlayState* play, Player* this, f32 arg2) {
    this->stateFlags1 |= PLAYER_STATE1_40000;
    this->stateFlags1 &= ~PLAYER_STATE1_8000000;
    func_8082DC64(play, this);

    if (func_80837730(play, this, arg2, 500)) {
        Player_PlaySfx(this, NA_SE_EV_JUMP_OUT_WATER);
    }
    func_80123140(play, this);
}

s32 func_8083B3B4(PlayState* play, Player* this, Input* input) {
    if ((!(this->stateFlags1 & PLAYER_STATE1_400) && !(this->stateFlags2 & PLAYER_STATE2_400) &&
         (this->transformation != PLAYER_FORM_ZORA)) &&
        ((input == NULL) ||
         ((((this->interactRangeActor == NULL) || (this->interactRangeActor->id != ACTOR_EN_ZOG)) &&
           CHECK_BTN_ALL(input->press.button, BTN_A)) &&
          ((ABS_ALT(this->unk_AAA) < 0x2EE0) && (this->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER) &&
           ((s32)SurfaceType_GetConveyorSpeed(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId) <=
            CONVEYOR_SPEED_SLOW))))) {
        if (Player_Action_97 != this->actionFunc) {
            Player_SetAction(play, this, Player_Action_59, 0);
        }

        Player_AnimationPlayOnce(play, this, &gPlayerAnim_link_swimer_swim_deep_start);
        this->unk_AAA = 0;
        this->stateFlags2 |= PLAYER_STATE2_400;
        this->actor.velocity.y = 0.0f;
        if (input != NULL) {
            this->stateFlags2 |= PLAYER_STATE2_800;
            Player_PlaySfx(this, NA_SE_PL_DIVE_BUBBLE);
        }

        return true;
    }

    if ((this->transformation != PLAYER_FORM_DEKU) &&
        ((this->stateFlags1 & PLAYER_STATE1_400) ||
         ((this->stateFlags2 & PLAYER_STATE2_400) &&
          (((Player_Action_56 != this->actionFunc) && !(this->stateFlags3 & PLAYER_STATE3_8000)) ||
           (this->unk_AAA < -0x1555)))) &&
        ((this->actor.depthInWater - this->actor.velocity.y) < this->ageProperties->unk_30)) {
        s32 temp_v0_3;
        s16 sp2A;
        f32 sp24;

        this->stateFlags2 &= ~PLAYER_STATE2_400;
        func_8082DC64(play, this);
        temp_v0_3 = func_80837730(play, this, this->actor.velocity.y, 0x1F4);
        if (this->stateFlags3 & PLAYER_STATE3_8000) {
            sp2A = this->unk_B86[1];
            sp24 = this->unk_B48 * 1.5f;
            Player_SetAction(play, this, Player_Action_28, 1);
            this->stateFlags3 |= PLAYER_STATE3_8000;
            this->stateFlags1 &= ~PLAYER_STATE1_8000000;
            sp24 = CLAMP_MAX(sp24, 13.5f);
            this->linearVelocity = Math_CosS(this->unk_AAA) * sp24;
            this->actor.velocity.y = -Math_SinS(this->unk_AAA) * sp24;
            this->unk_B86[1] = sp2A;
            Player_PlaySfx(this, NA_SE_EV_JUMP_OUT_WATER);
            return true;
        }

        if (temp_v0_3) {
            Player_PlaySfx(this, NA_SE_PL_FACE_UP);
        } else {
            Player_PlaySfx(this, NA_SE_PL_FACE_UP);
        }

        if (input != NULL) {
            Player_SetAction(play, this, Player_Action_60, 1);
            if (this->stateFlags1 & PLAYER_STATE1_400) {
                this->stateFlags1 |= (PLAYER_STATE1_400 | PLAYER_STATE1_800 | PLAYER_STATE1_20000000);
            }
            this->actionVar2 = 2;
        }

        func_8082E438(play, this,
                      (this->stateFlags1 & PLAYER_STATE1_800) ? &gPlayerAnim_link_swimer_swim_get
                                                              : &gPlayerAnim_link_swimer_swim_deep_end);
        return true;
    }

    return false;
}

void func_8083B73C(PlayState* play, Player* this, s16 currentYaw) {
    Player_SetAction(play, this, Player_Action_57, 0);
    func_8082E634(play, this, &gPlayerAnim_link_swimer_swim);
    this->actor.shape.rot.y = currentYaw;
    this->currentYaw = currentYaw;
}

void func_8083B798(PlayState* play, Player* this) {
    if (this->transformation == PLAYER_FORM_ZORA) {
        Player_SetAction(play, this, Player_Action_57, 0);
        PlayerAnimation_Change(play, &this->skelAnime, &gPlayerAnim_link_swimer_swim, 1.0f,
                               Animation_GetLastFrame(&gPlayerAnim_link_swimer_swim), 0.0f, ANIMMODE_LOOP, 0.0f);
        this->unk_B48 = 2.0f;
    } else {
        Player_AnimationPlayLoop(play, this, &gPlayerAnim_link_swimer_swim);
        this->actionVar2 = 1;
    }

    this->unk_AAA = 0x3E80;
}

void func_8083B850(PlayState* play, Player* this) {
    this->currentBoots = PLAYER_BOOTS_ZORA_LAND;
    this->prevBoots = PLAYER_BOOTS_ZORA_LAND;
    Player_SetAction(play, this, Player_Action_56, 0);
    this->unk_B48 = sqrtf(SQ(this->linearVelocity) + SQ(this->actor.velocity.y));
    Player_OverrideBlureColors(play, this, 1, 8);
    this->currentBoots = PLAYER_BOOTS_ZORA_LAND;
    this->prevBoots = PLAYER_BOOTS_ZORA_LAND;
}

void func_8083B8D0(PlayState* play, Player* this) {
    if (func_80837730(play, this, this->actor.velocity.y, 500)) {
        Player_PlaySfx(this, NA_SE_EV_DIVE_INTO_WATER);
        if (this->fallDistance > 800) {
            Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_CLIMB_END);
        }
    }
}

void func_8083B930(PlayState* play, Player* this) {
    PlayerAnimationHeader* var_a2;

    if ((this->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER) || !(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) ||
        (Player_Action_96 == this->actionFunc)) {
        func_8082DE50(play, this);

        if (Player_Action_28 == this->actionFunc) {
            func_8083B850(play, this);
            this->stateFlags3 |= PLAYER_STATE3_8000;
        } else if ((this->transformation == PLAYER_FORM_ZORA) && (Player_Action_27 == this->actionFunc)) {
            func_8083B850(play, this);
            this->stateFlags3 |= PLAYER_STATE3_8000;
            func_8082DB60(play, this, &gPlayerAnim_pz_fishswim);
        } else if ((this->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER) && (this->stateFlags2 & PLAYER_STATE2_400)) {
            this->stateFlags2 &= ~PLAYER_STATE2_400;
            func_8083B3B4(play, this, NULL);
            this->actionVar1 = 1;
        } else if (Player_Action_27 == this->actionFunc) {
            Player_SetAction(play, this, Player_Action_59, 0);
            func_8083B798(play, this);
        } else {
            Player_SetAction(play, this, Player_Action_54, 1);
            func_8082E438(play, this,
                          (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) ? &gPlayerAnim_link_swimer_wait2swim_wait
                                                                          : &gPlayerAnim_link_swimer_land2swim_wait);
        }
    }
    if (!(this->stateFlags1 & PLAYER_STATE1_8000000) || (this->actor.depthInWater < this->ageProperties->unk_2C)) {
        func_8083B8D0(play, this);
    }

    this->stateFlags1 |= PLAYER_STATE1_8000000;
    this->stateFlags2 |= PLAYER_STATE2_400;
    this->stateFlags1 &= ~(PLAYER_STATE1_40000 | PLAYER_STATE1_80000);

    this->unk_AEC = 0.0f;
    func_80123140(play, this);
}

void func_8083BB4C(PlayState* play, Player* this) {
    f32 sp1C = this->actor.depthInWater - this->ageProperties->unk_2C;

    if (sp1C < 0.0f) {
        this->underwaterTimer = 0;
        if ((this->transformation == PLAYER_FORM_ZORA) && (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
            this->currentBoots = PLAYER_BOOTS_ZORA_LAND;
        }
        func_801A3E38(0);
    } else {
        func_801A3E38(0x20);
        if ((this->transformation == PLAYER_FORM_ZORA) || (sp1C < 10.0f)) {
            this->underwaterTimer = 0;
        } else if (this->underwaterTimer < 300) {
            this->underwaterTimer++;
        }
    }

    if ((this->actor.parent == NULL) && (Player_Action_33 != this->actionFunc) &&
        (Player_Action_49 != this->actionFunc) &&
        ((Player_Action_28 != this->actionFunc) || (this->actor.velocity.y < -2.0f))) {
        if (this->ageProperties->unk_2C < this->actor.depthInWater) {
            if (this->transformation == PLAYER_FORM_GORON) {
                func_80834140(play, this, &gPlayerAnim_link_swimer_swim_down);
                func_808345C8();
                func_8083B8D0(play, this);
            } else if (this->transformation == PLAYER_FORM_DEKU) {
                if (this->remainingHopsCounter != 0) {
                    func_808373F8(play, this, NA_SE_VO_LI_AUTO_JUMP);
                } else {
                    if ((play->sceneId == SCENE_20SICHITAI) && (this->unk_3CF == 0)) {
                        if (CHECK_EVENTINF(EVENTINF_50)) {
                            play->nextEntrance = ENTRANCE(TOURIST_INFORMATION, 2);
                        } else {
                            play->nextEntrance = ENTRANCE(TOURIST_INFORMATION, 1);
                        }
                        play->transitionTrigger = TRANS_TRIGGER_START;
                        play->transitionType = TRANS_TYPE_FADE_BLACK_FAST;
                        this->stateFlags1 |= PLAYER_STATE1_200;
                        Audio_PlaySfx(NA_SE_SY_DEKUNUTS_JUMP_FAILED);
                    } else if ((this->unk_3CF == 0) &&
                               ((play->sceneId == SCENE_30GYOSON) || (play->sceneId == SCENE_31MISAKI) ||
                                (play->sceneId == SCENE_TORIDE))) {
                        func_80169EFC(&play->state);
                        func_808345C8();
                    } else {
                        Player_SetAction(play, this, Player_Action_1, 0);
                        this->stateFlags1 |= PLAYER_STATE1_20000000;
                    }
                    func_8083B8D0(play, this);
                }
            } else if (!(this->stateFlags1 & PLAYER_STATE1_8000000) ||
                       (((this->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER) ||
                         !(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) &&
                        (Player_Action_43 != this->actionFunc) && (Player_Action_61 != this->actionFunc) &&
                        (Player_Action_62 != this->actionFunc) && (Player_Action_54 != this->actionFunc) &&
                        (Player_Action_57 != this->actionFunc) && (Player_Action_58 != this->actionFunc) &&
                        (Player_Action_59 != this->actionFunc) && (Player_Action_60 != this->actionFunc) &&
                        (Player_Action_55 != this->actionFunc) && (Player_Action_56 != this->actionFunc))) {
                func_8083B930(play, this);
            }
        } else if ((this->stateFlags1 & PLAYER_STATE1_8000000) &&
                   (this->actor.depthInWater < this->ageProperties->unk_24) &&
                   (((Player_Action_56 != this->actionFunc) && !(this->stateFlags3 & PLAYER_STATE3_8000)) ||
                    (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND))) {
            if (this->skelAnime.moveFlags == 0) {
                func_8083B0E4(play, this, this->actor.shape.rot.y);
            }
            func_8083B32C(play, this, this->actor.velocity.y);
        }
    }
}

void func_8083BF54(PlayState* play, Player* this) {
    Vec3f sp84;
    s32 temp_v0;
    s32 var_a2;

    this->actor.terminalVelocity = -20.0f;
    this->actor.gravity = REG(68) / 100.0f;

    var_a2 = false;
    temp_v0 = func_808340D4(sPlayerFloorType);

    if (temp_v0 || ((var_a2 = (sPlayerFloorType == FLOOR_TYPE_14) || (sPlayerFloorType == FLOOR_TYPE_15)) ||
                    (sPlayerFloorType == FLOOR_TYPE_13))) {
        f32 temp_fv1_2;
        f32 var_fa1;
        f32 var_ft4;
        f32 var_fv0;
        u16 sfxId;

        var_ft4 = fabsf(this->linearVelocity + D_80862B3C) * 20.0f;
        if (temp_v0) {
            if (sPlayerFloorType == FLOOR_TYPE_4) {
                var_fa1 = 1300.0f;
            } else if (sPlayerFloorType == FLOOR_TYPE_7) {
                var_fa1 = 20000.0f;
                var_ft4 = 0.0f;
            } else {
                var_fa1 = 10000.0f;
                var_ft4 *= 1.6f;
            }
            sfxId = NA_SE_PL_SINK_ON_SAND - SFX_FLAG;
        } else if (var_a2) {
            if (sPlayerFloorType == FLOOR_TYPE_14) {
                var_fa1 = 400.0f;
                var_ft4 *= 10.0f;
            } else {
                var_fa1 = 1300.0f;
                var_ft4 = 0.0f;
            }
            sfxId = NA_SE_PL_SINK_ON_SNOW - SFX_FLAG;
        } else {
            var_fa1 = (this->transformation == PLAYER_FORM_GORON) ? 10000.0f : 1000.0f;
            var_ft4 = 0.0f;
            sfxId = NA_SE_PL_SINK_ON_SAND - SFX_FLAG;
        }

        var_fa1 = CLAMP_MIN(var_fa1, this->unk_AB8);

        var_fv0 = (sPlayerFloorType == FLOOR_TYPE_14) ? 200.0f : (var_fa1 - this->unk_AB8) * 0.02f;
        var_fv0 = CLAMP(var_fv0, 0.0f, 300.0f);

        temp_fv1_2 = this->unk_AB8;
        this->unk_AB8 += var_fv0 - var_ft4;
        this->unk_AB8 = CLAMP(this->unk_AB8, 0.0f, var_fa1);

        if ((this->linearVelocity == 0.0f) && (fabsf(this->unk_AB8 - temp_fv1_2) > 2.0f)) {
            Actor_PlaySfx_FlaggedCentered1(&this->actor, sfxId);
        }

        this->actor.gravity -= this->unk_AB8 * 0.004f;
    } else {
        this->unk_AB8 = 0.0f;
    }

    if ((this->stateFlags3 & PLAYER_STATE3_10) && (this->actor.bgCheckFlags & BGCHECKFLAG_WATER)) {
        if (this->actor.depthInWater < 50.0f) {
            f32 temp_fv1_5;
            Vec3f* bodyPartsPos;
            f32 var_fa0_3;
            f32 var_ft4_2;

            var_ft4_2 = fabsf(this->bodyPartsPos[PLAYER_BODYPART_WAIST].x - this->unk_D6C.x) +
                        fabsf(this->bodyPartsPos[PLAYER_BODYPART_WAIST].y - this->unk_D6C.y) +
                        fabsf(this->bodyPartsPos[PLAYER_BODYPART_WAIST].z - this->unk_D6C.z);
            var_ft4_2 = CLAMP_MAX(var_ft4_2, 4.0f);

            this->unk_AEC += var_ft4_2;
            if (this->unk_AEC > 15.0f) {
                this->unk_AEC = 0.0f;
                sp84.x = (Rand_ZeroOne() * 10.0f) + this->actor.world.pos.x;
                sp84.y = this->actor.world.pos.y + this->actor.depthInWater;
                sp84.z = (Rand_ZeroOne() * 10.0f) + this->actor.world.pos.z;

                EffectSsGRipple_Spawn(play, &sp84, 100, 500, 0);

                if ((this->linearVelocity > 4.0f) && !func_801242B4(this) &&
                    ((this->actor.world.pos.y + this->actor.depthInWater) <
                     this->bodyPartsPos[PLAYER_BODYPART_WAIST].y)) {
                    func_80837730(play, this, 20.0f,
                                  (fabsf(this->linearVelocity) * 50.0f) + (this->actor.depthInWater * 5.0f));
                } else if (this->stateFlags3 & PLAYER_STATE3_8000) {
                    s32 i;

                    var_fa0_3 = (this->actor.world.pos.y + this->actor.depthInWater) - 5.0f;
                    bodyPartsPos = this->bodyPartsPos;

                    for (i = 0; i < PLAYER_BODYPART_MAX; i++, bodyPartsPos++) {
                        temp_fv1_5 = bodyPartsPos->y - var_fa0_3;

                        if (temp_fv1_5 > 0.0f) {
                            func_80837730(play, this, 20.0f,
                                          fabsf(this->linearVelocity) * 20.0f + (temp_fv1_5 * 10.0f));
                        }
                    }
                }
            }
        }

        if (this->ageProperties->unk_2C < this->actor.depthInWater) {
            s32 numBubbles = 0;
            s32 i;
            f32 var_fv1;

            var_fv1 = (this->stateFlags1 & PLAYER_STATE1_4000000)
                          ? -fabsf(this->linearVelocity)
                          : ((Player_Action_56 == this->actionFunc)
                                 ? (ABS_ALT(this->unk_B8A) * -0.004f) + (this->unk_B48 * -0.38f)
                                 : this->actor.velocity.y);

            if ((var_fv1 > -1.0f) || ((this->currentBoots == PLAYER_BOOTS_ZORA_UNDERWATER) &&
                                      (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND))) {
                if (Rand_ZeroOne() < 0.2f) {
                    numBubbles = 1;
                }
            } else {
                numBubbles = var_fv1 * -0.3f;
                if (numBubbles > 8) {
                    numBubbles = 8;
                }
            }

            for (i = 0; i < numBubbles; i++) {
                EffectSsBubble_Spawn(play, &this->actor.world.pos, 20.0f, 10.0f, 20.0f, 0.13f);
            }
        }
    }
}

s32 func_8083C62C(Player* this, s32 arg1) {
    Actor* lockOnActor = this->lockOnActor;
    Vec3f headPos;
    s16 pitchTarget;
    s16 yawTarget;

    headPos.x = this->actor.world.pos.x;
    headPos.y = this->bodyPartsPos[PLAYER_BODYPART_HEAD].y + 3.0f;
    headPos.z = this->actor.world.pos.z;

    pitchTarget = Math_Vec3f_Pitch(&headPos, &lockOnActor->focus.pos);
    yawTarget = Math_Vec3f_Yaw(&headPos, &lockOnActor->focus.pos);

    Math_SmoothStepToS(&this->actor.focus.rot.y, yawTarget, 4, 0x2710, 0);
    Math_SmoothStepToS(&this->actor.focus.rot.x, pitchTarget, 4, 0x2710, 0);

    this->unk_AA6 |= 2;

    return func_80832754(this, arg1);
}

Vec3f D_8085D218 = { 0.0f, 100.0f, 40.0f };

void func_8083C6E8(Player* this, PlayState* play) {
    if (this->lockOnActor != NULL) {
        if (func_800B7128(this) || func_8082EF20(this)) {
            func_8083C62C(this, true);
        } else {
            func_8083C62C(this, false);
        }
        return;
    }

    if (sPlayerFloorType == FLOOR_TYPE_11) {
        Math_SmoothStepToS(&this->actor.focus.rot.x, -20000, 10, 4000, 800);
    } else {
        s16 sp46 = 0;
        f32 yIntersect;
        Vec3f pos;
        s16 temp_v0;

        yIntersect = func_80835D2C(play, this, &D_8085D218, &pos);
        if (yIntersect > BGCHECK_Y_MIN) {
            temp_v0 = Math_Atan2S_XY(40.0f, this->actor.world.pos.y - yIntersect);
            sp46 = CLAMP(temp_v0, -4000, 4000);
        }
        this->actor.focus.rot.y = this->actor.shape.rot.y;
        Math_SmoothStepToS(&this->actor.focus.rot.x, sp46, 14, 4000, 30);
    }

    func_80832754(this, func_800B7128(this) || func_8082EF20(this));
}

void func_8083C85C(Player* this) {
    Math_ScaledStepToS(&this->upperLimbRot.x, D_80862B3C * -500.0f, 900);
    this->headLimbRot.x = (-(f32)this->upperLimbRot.x * 0.5f);
    this->unk_AA6 |= 0x48;
}

void func_8083C8E8(Player* this, PlayState* play) {
    if (!func_800B7128(this) && !func_8082EF20(this) && ((this->linearVelocity > 5.0f) || (D_80862B3C != 0.0f))) {
        s16 temp1;
        s16 temp2;

        temp1 = this->linearVelocity * 200.0f;
        temp2 = BINANG_SUB(this->currentYaw, this->actor.shape.rot.y) * this->linearVelocity * 0.1f;

        temp1 = CLAMP(temp1, -0xFA0, 0xFA0);

        temp1 += (s16)(s32)(D_80862B3C * -500.0f);

        temp1 = CLAMP(temp1, -0x2EE0, 0x2EE0);

        temp2 = CLAMP(-temp2, -0xFA0, 0xFA0);

        Math_ScaledStepToS(&this->upperLimbRot.x, temp1, 0x384);
        this->headLimbRot.x = -(f32)this->upperLimbRot.x * 0.5f;
        Math_ScaledStepToS(&this->headLimbRot.z, temp2, 0x12C);
        Math_ScaledStepToS(&this->upperLimbRot.z, temp2, 0xC8);
        this->unk_AA6 |= 0x168;
    } else {
        func_8083C6E8(this, play);
    }
}

void func_8083CB04(Player* this, f32 arg1, s16 arg2, f32 arg3, f32 arg4, s16 arg5) {
    Math_AsymStepToF(&this->linearVelocity, arg1, arg3, arg4);
    Math_ScaledStepToS(&this->currentYaw, arg2, arg5);
}

void func_8083CB58(Player* this, f32 arg1, s16 arg2) {
    func_8083CB04(this, arg1, arg2, REG(19) / 100.0f, 1.5f, REG(27));
}

s32 func_8083CBC4(Player* this, f32 arg1, s16 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6) {
    s16 temp_v0 = this->currentYaw - arg2;

    if ((this->unk_B50 * 1.5f) < fabsf(this->linearVelocity)) {
        arg5 *= 4.0f;
        arg3 *= 4.0f;
    }

    if (ABS_ALT(temp_v0) > 0x6000) {
        if (!Math_StepToF(&this->linearVelocity, 0.0f, arg3)) {
            return false;
        }

        this->currentYaw = arg2;
    } else {
        Math_AsymStepToF(&this->linearVelocity, arg1, arg4, arg5);
        Math_ScaledStepToS(&this->currentYaw, arg2, arg6);
    }

    return true;
}

struct_8085D224 D_8085D224[][2] = {
    {
        { &gPlayerAnim_link_uma_left_up, 35.17f, 6.6099997f },
        { &gPlayerAnim_link_uma_right_up, -34.16f, 7.91f },
    },
    {
        { &gPlayerAnim_cl_uma_leftup, 22.718237f, 2.3294117f },
        { &gPlayerAnim_cl_uma_rightup, -22.0f, 1.9800001f },
    },
};

u16 D_8085D254[] = {
    0x1804, // PLAYER_FORM_GORON
    0x1805, // PLAYER_FORM_ZORA
    0x1806, // PLAYER_FORM_DEKU
    0x1806, // PLAYER_FORM_HUMAN
};

u16 D_8085D25C[] = {
    0x1804, // PLAYER_FORM_FIERCE_DEITY
    0x1804, // PLAYER_FORM_GORON
    0x1805, // PLAYER_FORM_ZORA
    0x1806, // PLAYER_FORM_DEKU
};

// Player_MountHorse
s32 Player_ActionChange_3(Player* this, PlayState* play) {
    EnHorse* rideActor = (EnHorse*)this->rideActor;

    if (rideActor != NULL) {
        if ((rideActor->type != HORSE_TYPE_2) && (this->transformation != PLAYER_FORM_FIERCE_DEITY)) {
            if (CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_A)) {
                if (CutsceneManager_IsNext(CS_ID_GLOBAL_TALK)) {
                    rideActor->actor.textId = D_8085D254[this->transformation - 1];
                    Player_TalkWithPlayer(play, &rideActor->actor);
                    return true;
                }
            }

            CutsceneManager_Queue(CS_ID_GLOBAL_TALK);
        } else if ((rideActor->type == HORSE_TYPE_2) && (this->transformation != PLAYER_FORM_HUMAN)) {
            if (CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_A)) {
                if (CutsceneManager_IsNext(CS_ID_GLOBAL_TALK)) {
                    rideActor->actor.textId = D_8085D25C[this->transformation];
                    Player_TalkWithPlayer(play, &rideActor->actor);
                    return true;
                }
            }

            CutsceneManager_Queue(CS_ID_GLOBAL_TALK);
        } else {
            if (CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_A)) {
                s32 pad[2];
                f32 sp28 = Math_CosS(rideActor->actor.shape.rot.y);
                f32 sp24 = Math_SinS(rideActor->actor.shape.rot.y);
                struct_8085D224* entry;
                f32 temp_fv0;
                f32 temp_fv1;

                func_80832558(play, this, func_80837BD0);

                this->stateFlags1 |= PLAYER_STATE1_800000;
                this->actor.bgCheckFlags &= ~BGCHECKFLAG_WATER;
                this->isBurning = false;

                if (this->transformation == PLAYER_FORM_FIERCE_DEITY) {
                    entry = D_8085D224[0];
                } else {
                    entry = D_8085D224[1];
                }
                if (this->mountSide >= 0) {
                    entry++;
                }

                temp_fv0 = entry->unk_4;
                temp_fv1 = entry->unk_8;
                this->actor.world.pos.x =
                    rideActor->actor.world.pos.x + rideActor->riderPos.x + ((temp_fv0 * sp28) + (temp_fv1 * sp24));
                this->actor.world.pos.z =
                    rideActor->actor.world.pos.z + rideActor->riderPos.z + ((temp_fv1 * sp28) - (temp_fv0 * sp24));
                this->unk_B48 = rideActor->actor.world.pos.y - this->actor.world.pos.y;

                this->currentYaw = this->actor.shape.rot.y = rideActor->actor.shape.rot.y;

                Actor_MountHorse(play, this, &rideActor->actor);
                Player_AnimationPlayOnce(play, this, entry->anim);
                func_8082E920(play, this,
                              ANIM_FLAG_1 | ANIM_FLAG_UPDATE_Y | ANIM_FLAG_8 | ANIM_FLAG_NOMOVE | ANIM_FLAG_80);
                this->actor.parent = this->rideActor;
                func_8082DAD4(this);
                Actor_DeactivateLens(play);

                return true;
            }
        }
    }

    return false;
}

PlayerAnimationHeader* sPlayerSlopeSlipAnims[] = {
    &gPlayerAnim_link_normal_down_slope_slip,
    &gPlayerAnim_link_normal_up_slope_slip,
};

s32 Player_HandleSlopes(PlayState* play, Player* this) {
    if (!Player_InBlockingCsMode(play, this) && !(this->cylinder.base.ocFlags1 & OC1_HIT)) {
        if ((Player_Action_73 != this->actionFunc) && (Player_Action_96 != this->actionFunc) &&
            (sPlayerFloorEffect == FLOOR_EFFECT_1)) {
            s16 playerVelYaw = Math_Atan2S_XY(this->actor.velocity.z, this->actor.velocity.x);
            Vec3f slopeNormal;
            s16 downwardSlopeYaw;
            s16 velYawToDownwardSlope;
            f32 slopeSlowdownSpeed;
            f32 temp_fv1;
            f32 var_fa1;
            f32 slopeSlowdownSpeedStep;

            Actor_GetSlopeDirection(this->actor.floorPoly, &slopeNormal, &downwardSlopeYaw);
            velYawToDownwardSlope = downwardSlopeYaw - playerVelYaw;

            if (ABS_ALT(velYawToDownwardSlope) > 0x3E80) { // 87.9 degrees
                var_fa1 = (Player_Action_96 == this->actionFunc) ? Math_CosS(this->floorPitch) : slopeNormal.y;
                slopeSlowdownSpeed = (1.0f - var_fa1) * 40.0f;
                temp_fv1 = fabsf(this->actor.speed) + slopeSlowdownSpeed;
                slopeSlowdownSpeedStep = SQ(temp_fv1) * 0.011f;
                slopeSlowdownSpeedStep = CLAMP_MIN(slopeSlowdownSpeedStep, 2.2f);

                // slows down speed as player is climbing a slope
                this->pushedYaw = downwardSlopeYaw;
                Math_StepToF(&this->pushedSpeed, slopeSlowdownSpeed, slopeSlowdownSpeedStep);
            } else {
                Player_SetAction(play, this, Player_Action_73, 0);
                func_8082DE50(play, this);
                func_8082E514(play, this, sPlayerSlopeSlipAnims[this->actionVar1]);
                this->linearVelocity = sqrtf(SQXZ(this->actor.velocity));
                this->currentYaw = downwardSlopeYaw;
                if (sPlayerFloorPitchShape >= 0) {
                    this->actionVar1 = 1;
                    Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_HANG);
                }

                return true;
            }
        }
    }

    return false;
}

void func_8083D168(PlayState* play, Player* this, GetItemEntry* giEntry) {
    Item00Type dropType = GIFIELD_GET_DROP_TYPE(giEntry->field);

    if (!(giEntry->field & GIFIELD_NO_COLLECTIBLE)) {
        Item_DropCollectible(play, &this->actor.world.pos, dropType | 0x8000);

        if ((dropType == ITEM00_BOMBS_A) || (dropType == ITEM00_ARROWS_30) || (dropType == ITEM00_ARROWS_40) ||
            (dropType == ITEM00_ARROWS_50) || (dropType == ITEM00_RUPEE_GREEN) || (dropType == ITEM00_RUPEE_BLUE) ||
            (dropType == ITEM00_RUPEE_RED) || (dropType == ITEM00_RUPEE_PURPLE) || (dropType == ITEM00_RUPEE_HUGE)) {
            return;
        }
    }

    Item_Give(play, giEntry->itemId);
    Audio_PlaySfx((this->getItemId < GI_NONE) ? NA_SE_SY_GET_BOXITEM : NA_SE_SY_GET_ITEM);
}

s32 Player_ActionChange_2(Player* this, PlayState* play) {
    if (gSaveContext.save.saveInfo.playerData.health != 0) {
        Actor* interactRangeActor = this->interactRangeActor;

        if (interactRangeActor != NULL) {
            if (this->getItemId > GI_NONE) {
                if (this->getItemId < GI_MAX) {
                    GetItemEntry* giEntry = &sGetItemTable[this->getItemId - 1];

                    interactRangeActor->parent = &this->actor;
                    if ((Item_CheckObtainability(giEntry->itemId) == ITEM_NONE) ||
                        ((s16)giEntry->objectId == OBJECT_GI_BOMB_2)) {
                        Player_DetachHeldActor(play, this);
                        func_80838830(this, giEntry->objectId);

                        if (!(this->stateFlags2 & PLAYER_STATE2_400) ||
                            (this->currentBoots == PLAYER_BOOTS_ZORA_UNDERWATER)) {
                            Player_StopCutscene(this);
                            func_808324EC(play, this, func_80837C78, play->playerCsIds[PLAYER_CS_ID_ITEM_GET]);
                            func_8082DB90(play, this,
                                          (this->transformation == PLAYER_FORM_DEKU)
                                              ? &gPlayerAnim_pn_getB
                                              : &gPlayerAnim_link_demo_get_itemB);
                        }

                        this->stateFlags1 |= (PLAYER_STATE1_400 | PLAYER_STATE1_800 | PLAYER_STATE1_20000000);
                        func_8082DAD4(this);

                        return true;
                    }

                    func_8083D168(play, this, giEntry);
                    this->getItemId = GI_NONE;
                }
            } else if (this->csMode == PLAYER_CSMODE_NONE) {
                if (!(this->stateFlags1 & PLAYER_STATE1_800)) {
                    if (this->getItemId != GI_NONE) {
                        if (CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_A)) {
                            GetItemEntry* giEntry = &sGetItemTable[-this->getItemId - 1];
                            EnBox* chest = (EnBox*)interactRangeActor;

                            if ((giEntry->itemId != ITEM_NONE) &&
                                (((Item_CheckObtainability(giEntry->itemId) == ITEM_NONE) &&
                                  (giEntry->field & GIFIELD_40)) ||
                                 (((Item_CheckObtainability(giEntry->itemId) != ITEM_NONE)) &&
                                  (giEntry->field & GIFIELD_20)))) {
                                this->getItemId =
                                    (giEntry->itemId == ITEM_MASK_CAPTAIN) ? -GI_RECOVERY_HEART : -GI_RUPEE_BLUE;
                                giEntry = &sGetItemTable[-this->getItemId - 1];
                            }

                            func_80832558(play, this, func_80837C78);
                            this->stateFlags1 |= (PLAYER_STATE1_400 | PLAYER_STATE1_800 | PLAYER_STATE1_20000000);
                            func_80838830(this, giEntry->objectId);

                            this->actor.world.pos.x =
                                interactRangeActor->world.pos.x -
                                (Math_SinS(interactRangeActor->shape.rot.y) * this->ageProperties->unk_9C);
                            this->actor.world.pos.z =
                                interactRangeActor->world.pos.z -
                                (Math_CosS(interactRangeActor->shape.rot.y) * this->ageProperties->unk_9C);
                            this->actor.world.pos.y = interactRangeActor->world.pos.y;
                            this->currentYaw = this->actor.shape.rot.y = interactRangeActor->shape.rot.y;

                            func_8082DAD4(this);
                            if ((giEntry->itemId != ITEM_NONE) && (giEntry->gid >= 0) &&
                                (Item_CheckObtainability(giEntry->itemId) == ITEM_NONE)) {
                                this->csId = chest->csId2;
                                func_8082DB90(play, this, this->ageProperties->openChestAnim);
                                func_8082E920(play, this,
                                              ANIM_FLAG_1 | ANIM_FLAG_UPDATE_Y | ANIM_FLAG_4 | ANIM_FLAG_8 |
                                                  ANIM_FLAG_NOMOVE | ANIM_FLAG_80);
                                this->actor.bgCheckFlags &= ~BGCHECKFLAG_WATER;
                                chest->unk_1EC = 1;
                            } else {
                                Player_AnimationPlayOnce(play, this, &gPlayerAnim_link_normal_box_kick);
                                chest->unk_1EC = -1;
                            }

                            return true;
                        }
                    } else if (!(this->stateFlags1 & PLAYER_STATE1_8000000) &&
                               (this->transformation != PLAYER_FORM_DEKU)) {
                        if ((this->heldActor == NULL) || Player_IsHoldingHookshot(this)) {
                            EnBom* bomb = (EnBom*)interactRangeActor;

                            if (((this->transformation != PLAYER_FORM_GORON) &&
                                 (((bomb->actor.id == ACTOR_EN_BOM) && bomb->isPowderKeg) ||
                                  ((interactRangeActor->id == ACTOR_EN_ISHI) && (interactRangeActor->params & 1)) ||
                                  (interactRangeActor->id == ACTOR_EN_MM)))) {
                                return false;
                            }

                            this->stateFlags2 |= PLAYER_STATE2_10000;
                            if (CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_A)) {
                                func_80832558(play, this, func_808379C0);
                                func_8082DAD4(this);
                                this->stateFlags1 |= PLAYER_STATE1_800;

                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

// Player_SetAction_Throwing
void func_8083D6DC(Player* this, PlayState* play) {
    Player_SetAction(play, this, Player_Action_42, 1);
    Player_AnimationPlayOnce(play, this, D_8085BE84[PLAYER_ANIMGROUP_28][this->modelAnimType]);
}

// Determines whether a held actor should be dropped or thrown: false implies droppable.
s32 func_8083D738(Player* this, Actor* heldActor) {
    if ((heldActor != NULL) && !(heldActor->flags & ACTOR_FLAG_800000) &&
        ((this->linearVelocity < 1.1f) || (heldActor->id == ACTOR_EN_BOM_CHU))) {
        return false;
    }
    return true;
}

s32 Player_ActionChange_9(Player* this, PlayState* play) {
    if (this->stateFlags1 & PLAYER_STATE1_800) {
        if ((this->heldActor != NULL) &&
            CHECK_BTN_ANY(sPlayerControlInput->press.button, BTN_CRIGHT | BTN_CLEFT | BTN_CDOWN | BTN_B | BTN_A)) {
            if (!func_808313A8(play, this, this->heldActor)) {
                if (!func_8083D738(this, this->heldActor)) {
                    Player_SetAction(play, this, Player_Action_41, 1);
                    Player_AnimationPlayOnce(play, this, D_8085BE84[PLAYER_ANIMGROUP_29][this->modelAnimType]);
                    return true;
                }
                func_8083D6DC(this, play);
            }

            return true;
        }
    }
    return false;
}

s32 func_8083D860(Player* this, PlayState* play) {
    if ((this->yDistToLedge >= 79.0f) &&
        (!(this->stateFlags1 & PLAYER_STATE1_8000000) || (this->currentBoots == PLAYER_BOOTS_ZORA_UNDERWATER) ||
         (this->actor.depthInWater < this->ageProperties->unk_2C))) {
        s32 var_t0 = (sPlayerTouchedWallFlags & WALL_FLAG_3) ? 2 : 0;
        s32 temp_t2 = sPlayerTouchedWallFlags & WALL_FLAG_1;

        if ((var_t0 != 0) || temp_t2 ||
            SurfaceType_CheckWallFlag2(&play->colCtx, this->actor.wallPoly, this->actor.wallBgId)) {
            CollisionPoly* wallPoly = this->actor.wallPoly;
            f32 sp78;
            f32 sp74;
            f32 zOut;
            f32 yOut;
            Vec3f sp48[3];
            s32 i;
            f32 sp40;
            Vec3f* sp3C;
            f32 xOut;

            yOut = xOut = 0.0f;
            if (var_t0 != 0) {
                sp78 = this->actor.world.pos.x;
                sp74 = this->actor.world.pos.z;
            } else {
                sp3C = sp48;
                CollisionPoly_GetVerticesByBgId(wallPoly, this->actor.wallBgId, &play->colCtx, sp48);
                sp78 = xOut = sp48[0].x;
                sp74 = zOut = sp48[0].z;
                yOut = sp48[0].y;

                for (i = 1; i < ARRAY_COUNT(sp48); i++) {
                    sp3C++;

                    if (sp78 > sp3C->x) {
                        sp78 = sp3C->x;
                    } else if (xOut < sp3C->x) {
                        xOut = sp3C->x;
                    }

                    if (sp74 > sp3C->z) {
                        sp74 = sp3C->z;
                    } else if (zOut < sp3C->z) {
                        zOut = sp3C->z;
                    }

                    if (yOut > sp3C->y) {
                        yOut = sp3C->y;
                    }
                }

                sp78 = (sp78 + xOut) * 0.5f;
                sp74 = (sp74 + zOut) * 0.5f;

                xOut = ((this->actor.world.pos.x - sp78) * COLPOLY_GET_NORMAL(wallPoly->normal.z)) -
                       ((this->actor.world.pos.z - sp74) * COLPOLY_GET_NORMAL(wallPoly->normal.x));

                sp40 = this->actor.world.pos.y - yOut;
                yOut = ((s32)((sp40 / 15.0f) + 0.5f) * 15.0f) - sp40;
                xOut = fabsf(xOut);
            }

            if (xOut < 8.0f) {
                f32 wallPolyNormalX = COLPOLY_GET_NORMAL(wallPoly->normal.x);
                f32 wallPolyNormalZ = COLPOLY_GET_NORMAL(wallPoly->normal.z);
                f32 distToInteractWall = this->distToInteractWall;
                PlayerAnimationHeader* anim;

                func_80832558(play, this, func_80837C20);

                this->stateFlags1 |= PLAYER_STATE1_200000;
                this->stateFlags1 &= ~PLAYER_STATE1_8000000;

                if ((var_t0 != 0) || temp_t2) {
                    if ((this->actionVar1 = var_t0) != 0) {
                        if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
                            anim = &gPlayerAnim_link_normal_Fclimb_startA;

                        } else {
                            anim = &gPlayerAnim_link_normal_Fclimb_hold2upL;
                        }
                        distToInteractWall = (this->ageProperties->unk_3C + 4.0f) - distToInteractWall;
                    } else {
                        anim = this->ageProperties->unk_AC;
                        distToInteractWall = 20.5f;
                    }

                    this->actionVar2 = -2;
                    this->actor.world.pos.y += yOut;

                    this->actor.shape.rot.y = this->currentYaw = this->actor.wallYaw + 0x8000;
                } else {
                    anim = this->ageProperties->unk_B0;
                    distToInteractWall = (this->ageProperties->wallCheckRadius - this->ageProperties->unk_3C) + 17.0f;
                    this->actionVar2 = -4;

                    this->actor.shape.rot.y = this->currentYaw = i = this->actor.wallYaw; //! FAKE
                }

                this->actor.world.pos.x = (distToInteractWall * wallPolyNormalX) + sp78;
                this->actor.world.pos.z = (distToInteractWall * wallPolyNormalZ) + sp74;
                func_8082DAD4(this);
                Math_Vec3f_Copy(&this->actor.prevPos, &this->actor.world.pos);
                Player_AnimationPlayOnce(play, this, anim);
                func_8082E920(play, this,
                              ANIM_FLAG_1 | ANIM_FLAG_UPDATE_Y | ANIM_FLAG_4 | ANIM_FLAG_8 | ANIM_FLAG_NOMOVE |
                                  ANIM_FLAG_80);
                return true;
            }
        }
    }

    return false;
}

void func_8083DCC4(Player* this, PlayerAnimationHeader* anim, PlayState* play) {
    Player_SetAction_PreserveMoveFlags(play, this, Player_Action_51, 0);
    PlayerAnimation_PlayOnceSetSpeed(play, &this->skelAnime, anim, 4.0f / 3.0f);
}

s32 func_8083DD1C(PlayState* play, Player* this, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    CollisionPoly* wallPoly;
    s32 bgId;
    Vec3f sp74;
    Vec3f sp68;
    Vec3f sp5C;
    f32 cos = Math_CosS(this->actor.shape.rot.y);
    f32 sin = Math_SinS(this->actor.shape.rot.y);

    sp74.x = this->actor.world.pos.x + (arg5 * sin);
    sp74.z = this->actor.world.pos.z + (arg5 * cos);
    sp68.x = this->actor.world.pos.x + (arg4 * sin);
    sp68.z = this->actor.world.pos.z + (arg4 * cos);
    sp74.y = sp68.y = this->actor.world.pos.y + arg2;

    if (BgCheck_EntityLineTest2(&play->colCtx, &sp74, &sp68, &sp5C, &this->actor.wallPoly, true, false, false, true,
                                &bgId, &this->actor)) {
        f32 wallPolyNormalX;
        f32 wallPolyNormalZ;

        wallPoly = this->actor.wallPoly;
        this->actor.bgCheckFlags |= BGCHECKFLAG_PLAYER_WALL_INTERACT;
        this->actor.wallBgId = bgId;
        sPlayerTouchedWallFlags = SurfaceType_GetWallFlags(&play->colCtx, wallPoly, bgId);

        wallPolyNormalX = COLPOLY_GET_NORMAL(wallPoly->normal.x);
        wallPolyNormalZ = COLPOLY_GET_NORMAL(wallPoly->normal.z);

        Math_ScaledStepToS(&this->actor.shape.rot.y, Math_Atan2S_XY(-wallPolyNormalZ, -wallPolyNormalX), 0x320);

        this->currentYaw = this->actor.shape.rot.y;
        this->actor.world.pos.x = sp5C.x - (Math_SinS(this->actor.shape.rot.y) * arg3);
        this->actor.world.pos.z = sp5C.z - (Math_CosS(this->actor.shape.rot.y) * arg3);

        return true;
    }

    this->actor.bgCheckFlags &= ~BGCHECKFLAG_PLAYER_WALL_INTERACT;
    return false;
}

void func_8083DEE4(PlayState* play, Player* this) {
    f32 temp_fv0 = this->ageProperties->wallCheckRadius;

    func_8083DD1C(play, this, 268 * 0.1f, temp_fv0 + 5.0f, temp_fv0 + 15.0f, 0.0f);
}

void func_8083DF38(Player* this, PlayerAnimationHeader* anim, PlayState* play) {
    if (!func_80832558(play, this, func_80837BF8)) {
        Player_SetAction(play, this, Player_Action_45, 0);
    }

    Player_AnimationPlayOnce(play, this, anim);
    func_8082DAD4(this);

    this->actor.shape.rot.y = this->currentYaw = this->actor.wallYaw + 0x8000;
}

s32 Player_ActionChange_5(Player* this, PlayState* play) {
    if (!(this->stateFlags1 & PLAYER_STATE1_800) && (this->actor.bgCheckFlags & BGCHECKFLAG_PLAYER_WALL_INTERACT) &&
        (sPlayerShapeYawToTouchedWall < 0x3000)) {
        if ((this->linearVelocity > 0.0f) && func_8083D860(this, play)) {
            return true;
        }

        if (!func_801242B4(this) && ((this->linearVelocity == 0.0f) || !(this->stateFlags2 & PLAYER_STATE2_4)) &&
            (sPlayerTouchedWallFlags & WALL_FLAG_6) && (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) &&
            (this->yDistToLedge >= 39.0f)) {
            this->stateFlags2 |= PLAYER_STATE2_1;

            if (CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_A)) {
                DynaPolyActor* dyna;

                if ((this->actor.wallBgId != BGCHECK_SCENE) &&
                    ((dyna = DynaPoly_GetActor(&play->colCtx, this->actor.wallBgId)) != NULL)) {
                    this->rightHandActor = &dyna->actor;
                } else {
                    this->rightHandActor = NULL;
                }

                func_8083DF38(this, &gPlayerAnim_link_normal_push_wait, play);
                return true;
            }
        }
    }

    return false;
}

s32 func_8083E14C(PlayState* play, Player* this) {
    if ((this->actor.bgCheckFlags & BGCHECKFLAG_PLAYER_WALL_INTERACT) &&
        ((this->stateFlags2 & PLAYER_STATE2_10) || CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_A))) {
        DynaPolyActor* var_v1 = NULL;

        if (this->actor.wallBgId != BGCHECK_SCENE) {
            var_v1 = DynaPoly_GetActor(&play->colCtx, this->actor.wallBgId);
        }

        if (&var_v1->actor == this->rightHandActor) {
            if (this->stateFlags2 & PLAYER_STATE2_10) {
                return true;
            }
            return false;
        }
    }

    func_808369F4(this, play);
    Player_AnimationPlayOnce(play, this, &gPlayerAnim_link_normal_push_wait_end);
    this->stateFlags2 &= ~PLAYER_STATE2_10;
    return true;
}

void func_8083E234(Player* this, PlayState* play) {
    Player_SetAction(play, this, Player_Action_46, 0);
    Player_AnimationPlayOnce(play, this, &gPlayerAnim_link_normal_push_start);
    this->stateFlags2 |= PLAYER_STATE2_10;
}

void func_8083E28C(Player* this, PlayState* play) {
    Player_SetAction(play, this, Player_Action_47, 0);
    Player_AnimationPlayOnce(play, this, D_8085BE84[PLAYER_ANIMGROUP_34][this->modelAnimType]);
    this->stateFlags2 |= PLAYER_STATE2_10;
}

void func_8083E2F4(Player* this, PlayState* play) {
    this->stateFlags1 &= ~(PLAYER_STATE1_200000 | PLAYER_STATE1_8000000);
    func_80833AA0(this, play);

    if (this->transformation == PLAYER_FORM_DEKU) {
        this->linearVelocity = -1.7f;
    } else {
        this->linearVelocity = -0.4f;
    }
}

s32 func_8083E354(Player* this, PlayState* play) {
    if (!CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_A) &&
        (this->actor.bgCheckFlags & BGCHECKFLAG_PLAYER_WALL_INTERACT)) {
        if ((sPlayerTouchedWallFlags & WALL_FLAG_3) || (sPlayerTouchedWallFlags & WALL_FLAG_1) ||
            SurfaceType_CheckWallFlag2(&play->colCtx, this->actor.wallPoly, this->actor.wallBgId)) {
            return false;
        }
    }

    func_8083E2F4(this, play);
    Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_AUTO_JUMP);
    return true;
}

s32 func_8083E404(Player* this, f32 arg1, s16 arg2) {
    f32 sp1C = BINANG_SUB(arg2, this->actor.shape.rot.y);
    f32 temp_fv1;

    if (this->lockOnActor != NULL) {
        func_8083C62C(this, func_800B7128(this) || func_8082EF20(this));
    }

    temp_fv1 = fabsf(sp1C) / 0x8000;
    if (((SQ(temp_fv1) * 50.0f) + 6.0f) < arg1) {
        return 1;
    }

    if ((((1.0f - temp_fv1) * 10.0f) + 6.8f) < arg1) {
        return -1;
    }
    return 0;
}

s32 func_8083E514(Player* this, f32* arg2, s16* arg3, PlayState* play) {
    s16 temp_v1 = *arg3 - this->targetYaw;
    u16 var_a2 = ABS_ALT(temp_v1);

    if ((func_800B7128(this) || func_8082EF20(this)) && (this->lockOnActor == NULL)) {
        *arg2 *= Math_SinS(var_a2);

        if (*arg2 != 0.0f) {
            *arg3 = (((temp_v1 >= 0) ? 1 : -1) * 0x4000) + this->actor.shape.rot.y;
        } else {
            *arg3 = this->actor.shape.rot.y;
        }

        if (this->lockOnActor != NULL) {
            func_8083C62C(this, true);
        } else {
            Math_SmoothStepToS(&this->actor.focus.rot.x, (sPlayerControlInput->rel.stick_y * 240.0f), 0xE, 0xFA0, 0x1E);
            func_80832754(this, true);
        }
    } else {
        if (this->lockOnActor != NULL) {
            return func_8083E404(this, *arg2, *arg3);
        }

        func_8083C6E8(this, play);
        if ((*arg2 != 0.0f) && (var_a2 < 0x1770)) {
            return 1;
        }

        if ((Math_SinS(0x4000 - (var_a2 >> 1)) * 200.0f) < *arg2) {
            return -1;
        }
    }
    return 0;
}

s32 func_8083E758(Player* this, f32* arg1, s16* arg2) {
    f32 temp_fv0;
    u16 temp_v0;
    s16 var_v1;

    var_v1 = *arg2 - this->actor.shape.rot.y;
    temp_v0 = ABS_ALT(var_v1);
    temp_fv0 = Math_CosS(temp_v0);
    *arg1 *= temp_fv0;

    // Can't be (*arg1 != 0.0f)
    if (*arg1 != 0) {
        if (temp_fv0 > 0.0f) {
            return 1;
        }
        return -1;
    }
    return 0;
}

s32 func_8083E7F8(Player* this, f32* arg1, s16* arg2, PlayState* play) {
    func_8083C6E8(this, play);

    if ((*arg1 != 0.0f) || (ABS_ALT(this->unk_B4C) > 0x190)) {
        s16 temp_a0 = *arg2 - (u16)Camera_GetInputDirYaw(GET_ACTIVE_CAM(play));
        u16 temp;

        temp = (ABS_ALT(temp_a0) - 0x2000);
        if ((temp < 0x4000) || (this->unk_B4C != 0)) {
            return -1;
        }
        return 1;
    }

    return 0;
}

void func_8083E8E0(Player* this, f32 arg1, s16 arg2) {
    s16 temp = arg2 - this->actor.shape.rot.y;

    if (arg1 > 0.0f) {
        if (temp < 0) {
            this->unk_B44 = 0.0f;
        } else {
            this->unk_B44 = 1.0f;
        }
    }

    Math_StepToF(&this->unk_B40, this->unk_B44, 0.3f);
}

void func_8083E958(PlayState* play, Player* this) {
    PlayerAnimation_BlendToJoint(play, &this->skelAnime, func_8082EF54(this), this->unk_B38, func_8082EF9C(this),
                                 this->unk_B38, this->unk_B40, this->blendTableBuffer);
}

s32 func_8083E9C4(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 temp_fv0;

    if ((arg3 == 0.0f) && (arg1 > 0.0f)) {
        arg3 = arg2;
    }
    temp_fv0 = (arg0 + arg1) - arg3;
    if (((temp_fv0 * arg1) >= 0.0f) && (((temp_fv0 - arg1) * arg1) < 0.0f)) {
        return true;
    }
    return false;
}

void func_8083EA44(Player* this, f32 arg1) {
    s32 sp24;
    f32 updateScale = R_UPDATE_RATE / 2.0f;

    arg1 *= updateScale;
    if (arg1 < -7.25f) {
        arg1 = -7.25f;
    } else if (arg1 > 7.25f) {
        arg1 = 7.25f;
    }

    sp24 = func_8083E9C4(this->unk_B38, arg1, 29.0f, 10.0f);

    if (sp24 || func_8083E9C4(this->unk_B38, arg1, 29.0f, 24.0f)) {
        Player_AnimSfx_PlayFloorWalk(this, this->linearVelocity);
        if (this->linearVelocity > 4.0f) {
            this->stateFlags2 |= PLAYER_STATE2_8;
        }
        this->actor.shape.unk_17 = sp24 ? 1 : 2;
    }

    this->unk_B38 += arg1;
    if (this->unk_B38 < 0.0f) {
        this->unk_B38 += 29.0f;
    } else if (this->unk_B38 >= 29.0f) {
        this->unk_B38 -= 29.0f;
    }
}

void Player_ChooseIdleAnim(PlayState* play, Player* this) {
    PlayerAnimationHeader* anim;
    u32 healthIsCritical;
    PlayerAnimationHeader** animPtr;
    s32 animIndex;
    s32 rand;
    f32 morphFrames;
    s16 endFrame;

    if (((this->actor.id != ACTOR_PLAYER) && !(healthIsCritical = (this->actor.colChkInfo.health < 0x64))) ||
        ((this->actor.id == ACTOR_PLAYER) &&
         (((this->lockOnActor != NULL) ||
           ((this->transformation != PLAYER_FORM_FIERCE_DEITY) && (this->transformation != PLAYER_FORM_HUMAN)) ||
           (this->currentMask == PLAYER_MASK_SCENTS)) ||
          (!(healthIsCritical = LifeMeter_IsCritical()) && (this->unk_AA4 = ((this->unk_AA4 + 1) & 1)))))) {
        this->stateFlags2 &= ~PLAYER_STATE2_10000000;
        anim = func_8082ED20(this);
    } else {
        this->stateFlags2 |= PLAYER_STATE2_10000000;

        if (this->stateFlags1 & PLAYER_STATE1_800) {
            anim = func_8082ED20(this);
        } else {
            animIndex = play->roomCtx.curRoom.behaviorType2;

            if (healthIsCritical) {
                if (this->unk_AA4 >= 0) {
                    animIndex = 7;
                    this->unk_AA4 = -1;
                } else {
                    animIndex = 8;
                }
            } else {
                rand = Rand_ZeroOne() * 5.0f;
                if (rand < 4) {
                    if (((rand != 0) && (rand != 3)) ||
                        ((this->rightHandType == PLAYER_MODELTYPE_RH_SHIELD) &&
                         ((rand == 3) || (Player_GetMeleeWeaponHeld(this) != PLAYER_MELEEWEAPON_NONE)))) {
                        if ((rand == 0) && Player_IsHoldingTwoHandedWeapon(this)) {
                            rand = 4;
                        }
                        animIndex = rand + 9;
                    }
                }
            }

            animPtr = &sPlayerIdleAnimations[animIndex][0];
            if (this->modelAnimType != PLAYER_ANIMTYPE_1) {
                animPtr = &sPlayerIdleAnimations[animIndex][1];
            }
            anim = *animPtr;
        }
    }

    endFrame = Animation_GetLastFrame(anim);
    if ((this->skelAnime.animation == anim) || (this->skelAnime.animation == &gPlayerAnim_pz_attackAend) ||
        (this->skelAnime.animation == &gPlayerAnim_pz_attackBend) ||
        (this->skelAnime.animation == &gPlayerAnim_pz_attackCend)) {
        morphFrames = 0.0f;
    } else {
        morphFrames = -6.0f;
    }

    PlayerAnimation_Change(play, &this->skelAnime, anim, (2.0f / 3.0f) * D_8085C3E4, 0.0f, endFrame, ANIMMODE_ONCE,
                           morphFrames);
}

void func_8083EE60(Player* this, PlayState* play) {
    f32 temp_fv0;
    f32 var_fs0;

    if (this->unk_B34 < 1.0f) {
        f32 temp_fs0 = R_UPDATE_RATE / 2.0f;

        func_8083EA44(this, REG(35) / 1000.0f);
        PlayerAnimation_LoadToJoint(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_30][this->modelAnimType],
                                    this->unk_B38);
        this->unk_B34 += (1.0f * 1.0f) * temp_fs0;
        if (this->unk_B34 >= 1.0f) {
            this->unk_B34 = 1.0f;
        }
        var_fs0 = this->unk_B34;
    } else {
        temp_fv0 = this->linearVelocity - (REG(48) / 100.0f);

        if (temp_fv0 < 0.0f) {
            var_fs0 = 1.0f;
            func_8083EA44(this, ((REG(35)) / 1000.0f) + (((REG(36)) / 1000.0f) * this->linearVelocity));

            PlayerAnimation_LoadToJoint(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_30][this->modelAnimType],
                                        this->unk_B38);
        } else {
            var_fs0 = (REG(37) / 1000.0f) * temp_fv0;
            if (var_fs0 < 1.0f) {
                func_8083EA44(this, (REG(35) / 1000.0f) + ((REG(36) / 1000.0f) * this->linearVelocity));
            } else {
                var_fs0 = 1.0f;
                func_8083EA44(this, (REG(39) / 100.0f) + ((REG(38) / 1000.0f) * temp_fv0));
            }

            PlayerAnimation_LoadToMorph(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_30][this->modelAnimType],
                                        this->unk_B38);
            PlayerAnimation_LoadToJoint(play, &this->skelAnime, &gPlayerAnim_link_normal_back_run,
                                        this->unk_B38 * (16.0f / 29.0f));
        }
    }
    if (var_fs0 < 1.0f) {
        PlayerAnimation_InterpJointMorph(play, &this->skelAnime, 1.0f - var_fs0);
    }
}

void func_8083F144(Player* this, PlayState* play) {
    Player_SetAction(play, this, Player_Action_7, 1);
    func_8082E438(play, this, &gPlayerAnim_link_normal_back_brake);
}

s32 func_8083F190(Player* this, f32* arg1, s16* arg2, PlayState* play) {
    if (this->linearVelocity > 6.0f) {
        func_8083F144(this, play);
        return true;
    }

    if (*arg1 != 0.0f) {
        if (func_80832F24(this)) {
            *arg1 = 0.0f;
            *arg2 = this->currentYaw;
        } else {
            return true;
        }
    }
    return false;
}

void func_8083F230(Player* this, PlayState* play) {
    Player_SetAction(play, this, Player_Action_8, 1);
    Player_AnimationPlayOnce(play, this, &gPlayerAnim_link_normal_back_brake_end);
}

void func_8083F27C(PlayState* play, Player* this) {
    f32 temp_fv0;
    PlayerAnimationHeader* sp38;
    PlayerAnimationHeader* sp34;

    sp38 = D_8085BE84[PLAYER_ANIMGROUP_23][this->modelAnimType];
    sp34 = D_8085BE84[PLAYER_ANIMGROUP_24][this->modelAnimType];

    this->skelAnime.animation = sp38;

    func_8083EA44(this, (REG(30) / 1000.0f) + ((REG(32) / 1000.0f) * this->linearVelocity));

    temp_fv0 = this->unk_B38 * (16.0f / 29.0f);
    PlayerAnimation_BlendToJoint(play, &this->skelAnime, sp34, temp_fv0, sp38, temp_fv0, this->unk_B40,
                                 this->blendTableBuffer);
}

void func_8083F358(Player* this, s32 arg1, PlayState* play) {
    PlayerAnimationHeader* climbAnim;
    f32 var_fv1;
    s16 var_a1;

    if (ABS_ALT(sPlayerFloorPitchShape) < 0xE38) {
        var_a1 = 0;
    } else {
        var_a1 = CLAMP(sPlayerFloorPitchShape, -0x2AAA, 0x2AAA);
    }

    Math_ScaledStepToS(&this->unk_B70, var_a1, 0x190);
    if ((this->modelAnimType == PLAYER_ANIMTYPE_3) || ((this->unk_B70 == 0) && (this->unk_AB8 <= 0.0f))) {
        if (arg1 == 0) {
            PlayerAnimation_LoadToJoint(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_1][this->modelAnimType],
                                        this->unk_B38);
        } else {
            PlayerAnimation_LoadToMorph(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_1][this->modelAnimType],
                                        this->unk_B38);
        }
        return;
    }

    if (this->unk_B70 != 0) {
        var_fv1 = this->unk_B70 / (f32)0x2AAA;
    } else {
        var_fv1 = this->unk_AB8 * 0.0006f;
    }

    var_fv1 *= fabsf(this->linearVelocity) * 0.5f;
    if (var_fv1 > 1.0f) {
        var_fv1 = 1.0f;
    }

    if (var_fv1 < 0.0f) {
        climbAnim = &gPlayerAnim_link_normal_climb_down;
        var_fv1 = -var_fv1;
    } else {
        climbAnim = &gPlayerAnim_link_normal_climb_up;
    }

    if (arg1 == 0) {
        PlayerAnimation_BlendToJoint(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_1][this->modelAnimType],
                                     this->unk_B38, climbAnim, this->unk_B38, var_fv1, this->blendTableBuffer);
    } else {
        PlayerAnimation_BlendToMorph(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_1][this->modelAnimType],
                                     this->unk_B38, climbAnim, this->unk_B38, var_fv1, this->blendTableBuffer);
    }
}

void func_8083F57C(Player* this, PlayState* play) {
    f32 temp_fv0;
    f32 var_fs0;

    if (this->unk_B34 < 1.0f) {
        f32 temp_fs0;

        temp_fs0 = R_UPDATE_RATE / 2.0f;
        func_8083EA44(this, REG(35) / 1000.0f);
        PlayerAnimation_LoadToJoint(play, &this->skelAnime, D_8085BE84[PLAYER_ANIMGROUP_1][this->modelAnimType],
                                    this->unk_B38);

        // required
        this->unk_B34 += 1 * temp_fs0;
        if (this->unk_B34 >= 1.0f) {
            this->unk_B34 = 1.0f;
        }
        var_fs0 = this->unk_B34;
    } else {
        temp_fv0 = (this->linearVelocity - (REG(48) / 100.0f));
        if (temp_fv0 < 0.0f) {
            var_fs0 = 1.0f;
            func_8083EA44(this, (REG(35) / 1000.0f) + ((REG(36) / 1000.0f) * this->linearVelocity));
            func_8083F358(this, 0, play);
        } else {
            var_fs0 = (REG(37) / 1000.0f) * temp_fv0;
            if (var_fs0 < 1.0f) {
                func_8083EA44(this, (REG(35) / 1000.0f) + ((REG(36) / 1000.0f) * this->linearVelocity));
            } else {
                var_fs0 = 1.0f;
                func_8083EA44(this, (REG(39) / 100.0f) + ((REG(38) / 1000.0f) * temp_fv0));
            }
            func_8083F358(this, 1, play);
            PlayerAnimation_LoadToJoint(play, &this->skelAnime, func_8082EEE0(this), this->unk_B38 * (20.0f / 29.0f));
        }
    }

    if (var_fs0 < 1.0f) {
        PlayerAnimation_InterpJointMorph(play, &this->skelAnime, 1.0f - var_fs0);
    }
}

void func_8083F828(Vec3f* arg0, Vec3f* arg1, f32 arg2, f32 arg3, f32 arg4) {
    arg1->x = Rand_CenteredFloat(arg3) + arg0->x;
    arg1->y = Rand_CenteredFloat(arg4) + (arg0->y + arg2);
    arg1->z = Rand_CenteredFloat(arg3) + arg0->z;
}

Color_RGBA8 D_8085D26C = { 255, 255, 255, 255 };
Vec3f D_8085D270 = { 0.0f, 0.04f, 0.0f };

s32 func_8083F8A8(PlayState* play, Player* this, f32 radius, s32 countMax, f32 randAccelWeight, s32 scale,
                  s32 scaleStep, s32 useLighting) {
    static Vec3f D_8085D27C = { 0.0f, 0.0f, 0.0f };
    static Vec3f D_8085D288 = { 0.0f, 0.0f, 0.0f };

    if ((countMax < 0) || (this->floorSfxOffset == NA_SE_PL_WALK_SNOW - SFX_FLAG)) {
        s32 count = func_80173B48(&play->state) / 20000000;
        Vec3f pos;
        s32 i;

        count = (count >= ABS_ALT(countMax)) ? ABS_ALT(countMax) : count;
        for (i = 0; i < count; i++) {
            func_8083F828(&this->actor.world.pos, &pos, 0.0f, 40.0f, 10.0f);
            D_8085D27C.x = Rand_CenteredFloat(3.0f);
            D_8085D27C.z = Rand_CenteredFloat(3.0f);
            EffectSsDust_Spawn(play, 0, &pos, &D_8085D27C, &D_8085D270, &D_8085D26C, &D_8085D26C, scale, scaleStep, 42,
                               0);
        }

        return true;
    } else if ((this->floorSfxOffset == NA_SE_PL_WALK_GROUND - SFX_FLAG) ||
               (this->floorSfxOffset == NA_SE_PL_WALK_SAND - SFX_FLAG)) {
        s32 count = func_80173B48(&play->state) / 12000000;

        if (count > 0) {
            Actor_SpawnFloorDustRing(play, &this->actor, &this->actor.world.pos, radius,
                                     (count < countMax) ? count : countMax, randAccelWeight, scale, scaleStep,
                                     useLighting);

            return true;
        }
    } else if (this->floorSfxOffset == NA_SE_PL_WALK_GRASS - SFX_FLAG) {
        s32 count = func_80173B48(&play->state) / 12000000;
        Vec3f velocity;
        Vec3f pos;
        s32 i;

        count = (count >= countMax) ? countMax : count;
        for (i = 0; i < count; i++) {
            func_8083F828(&this->actor.world.pos, &pos, 0.0f, 20.0f, 20.0f);
            velocity.x = Rand_CenteredFloat(3.0f);
            velocity.y = Rand_ZeroFloat(2.0f);
            velocity.z = Rand_CenteredFloat(3.0f);
            D_8085D288.y = -0.1f;
            EffectSsHahen_Spawn(play, &pos, &velocity, &D_8085D288, 0, 0x96, 1, 0x10, gKakeraLeafTip);
        }
    }

    return false;
}

s32 func_8083FBC4(PlayState* play, Player* this) {
    if ((this->floorSfxOffset == NA_SE_PL_WALK_GROUND - SFX_FLAG) ||
        (this->floorSfxOffset == NA_SE_PL_WALK_SAND - SFX_FLAG)) {
        Vec3f* feetPos = this->actor.shape.feetPos;
        s32 i;

        for (i = 0; i < ARRAY_COUNT(this->actor.shape.feetPos); i++) {
            func_800B1210(play, feetPos, &gZeroVec3f, &gZeroVec3f, 50, 30);
            feetPos++;
        }

        return true;
    }

    if (this->floorSfxOffset == NA_SE_PL_WALK_SNOW - SFX_FLAG) {
        Vec3f* feetPos = this->actor.shape.feetPos;
        s32 i;

        for (i = 0; i < ARRAY_COUNT(this->actor.shape.feetPos); i++) {
            EffectSsDust_Spawn(play, 0, feetPos, &gZeroVec3f, &D_8085D270, &D_8085D26C, &D_8085D26C, 100, 40, 17, 0);
            feetPos++;
        }

        return true;
    }

    return false;
}

s32 func_8083FCF0(PlayState* play, Player* this, f32 arg2, f32 arg3, f32 arg4) {
    if (arg4 < this->skelAnime.curFrame) {
        func_8082DC38(this);
    } else if (arg2 <= this->skelAnime.curFrame) {
        this->stateFlags3 |= PLAYER_STATE3_2000000;
        func_8082FA5C(play, this,
                      (arg3 <= this->skelAnime.curFrame) ? PLAYER_MELEE_WEAPON_STATE_1
                                                         : PLAYER_MELEE_WEAPON_STATE_MINUS_1);
        return true;
    }
    return false;
}

// Crouch-stabbing
s32 func_8083FD80(Player* this, PlayState* play) {
    if (!Player_IsGoronOrDeku(this) && (Player_GetMeleeWeaponHeld(this) != PLAYER_MELEEWEAPON_NONE) &&
        (this->transformation != PLAYER_FORM_ZORA) && sPlayerUseHeldItem) {
        //! Calling this function sets the meleeWeaponQuads' damage properties correctly, patching "Power Crouch Stab".
        func_8083375C(this, PLAYER_MWA_STAB_1H);
        Player_AnimationPlayOnce(play, this, &gPlayerAnim_link_normal_defense_kiru);
        this->actionVar1 = 1;
        this->meleeWeaponAnimation = PLAYER_MWA_STAB_1H;
        this->currentYaw = this->actor.shape.rot.y + this->upperLimbRot.y;
        this->unk_ADD = 0;
        return true;
    }
    return false;
}

s32 func_8083FE38(Player* this, PlayState* play) {
    return Player_ActionChange_13(this, play) || Player_ActionChange_4(this, play) || Player_ActionChange_2(this, play);
}

void Player_RequestQuakeAndRumble(PlayState* play, Player* this, u16 sfxId) {
    Player_RequestQuake(play, 27767, 7, 20);
    Player_RequestRumble(play, this, 255, 20, 150, SQ(0));
    Player_PlaySfx(this, sfxId);
}

void func_8083FEF4(PlayState* play, Player* this) {
    Inventory_ChangeAmmo(ITEM_DEKU_STICK, -1);
    Player_UseItem(play, this, ITEM_NONE);
}

s32 func_8083FF30(PlayState* play, Player* this) {
    if ((this->heldItemAction == PLAYER_IA_DEKU_STICK) && (this->unk_B0C > 0.5f)) {
        if (AMMO(ITEM_DEKU_STICK) != 0) {
            EffectSsStick_Spawn(play, &this->bodyPartsPos[PLAYER_BODYPART_RIGHT_HAND],
                                BINANG_ADD(this->actor.shape.rot.y, 0x8000));
            this->unk_B0C = 0.5f;
            func_8083FEF4(play, this);
            Player_PlaySfx(this, NA_SE_IT_WOODSTICK_BROKEN);
        }
        return true;
    }

    return false;
}

// handles razor sword health and breaking
s32 func_8083FFEC(PlayState* play, Player* this) {
    if (this->heldItemAction == PLAYER_IA_SWORD_RAZOR) {
        if (gSaveContext.save.saveInfo.playerData.swordHealth > 0) {
            gSaveContext.save.saveInfo.playerData.swordHealth--;
            if (gSaveContext.save.saveInfo.playerData.swordHealth <= 0) {
                Item_Give(play, ITEM_SWORD_KOKIRI);
                Player_UseItem(play, this, ITEM_SWORD_KOKIRI);
                Player_PlaySfx(this, NA_SE_IT_MAJIN_SWORD_BROKEN);
                if (Message_GetState(&play->msgCtx) == TEXT_STATE_NONE) {
                    Message_StartTextbox(play, 0xF9, NULL);
                }
            }
        }
        return true;
    }
    return false;
}

// Could return the last function, but never used as such
void func_80840094(PlayState* play, Player* this) {
    func_8083FF30(play, this);
    func_8083FFEC(play, this);
}

PlayerAnimationHeader* D_8085D294[] = {
    &gPlayerAnim_link_fighter_rebound,
    &gPlayerAnim_link_fighter_rebound_long,
    &gPlayerAnim_link_fighter_reboundR,
    &gPlayerAnim_link_fighter_rebound_longR,
};

void func_808400CC(PlayState* play, Player* this) {
    if (Player_Action_18 != this->actionFunc) {
        func_8082DD2C(play, this);
        if ((this->transformation != PLAYER_FORM_HUMAN) && (this->transformation != PLAYER_FORM_FIERCE_DEITY)) {
            u8 moveFlags = this->skelAnime.moveFlags;
            s32 pad;

            this->skelAnime.moveFlags = 0;
            Player_SetAction(play, this, Player_Action_85, 0);
            this->skelAnime.moveFlags = moveFlags;
        } else {
            s32 var_v1;
            s32 pad;

            Player_SetAction(play, this, Player_Action_85, 0);
            if (func_80123420(this)) {
                var_v1 = 2;
            } else {
                var_v1 = 0;
            }
            func_8082DB90(play, this, D_8085D294[Player_IsHoldingTwoHandedWeapon(this) + var_v1]);
        }
    }

    Player_RequestRumble(play, this, 180, 20, 100, SQ(0));
    this->linearVelocity = -18.0f;
    func_80840094(play, this);
}

s32 func_808401F4(PlayState* play, Player* this) {
    if (this->meleeWeaponState >= PLAYER_MELEE_WEAPON_STATE_1) {
        s32 temp_v0_3;

        if (this->meleeWeaponAnimation < PLAYER_MWA_SPIN_ATTACK_1H) {
            if (!(this->meleeWeaponQuads[0].base.atFlags & AT_BOUNCED) &&
                !(this->meleeWeaponQuads[1].base.atFlags & AT_BOUNCED)) {
                if (this->skelAnime.curFrame >= 2.0f) {
                    CollisionPoly* poly;
                    s32 bgId;
                    Vec3f spC8;
                    Vec3f pos;
                    Vec3f spB0;
                    Vec3f* var_a1;
                    Vec3f* temp_a0 = &this->meleeWeaponInfo[0].tip;
                    f32 var_fv1;

                    if (this->linearVelocity >= 0.0f) {
                        var_a1 = &this->meleeWeaponInfo[0].base;
                        if ((this->transformation == PLAYER_FORM_GORON) || (this->actor.id == ACTOR_EN_TEST3)) {
                            var_a1 = &this->unk_AF0[1];
                        }

                        var_fv1 = Math_Vec3f_DistXYZAndStoreDiff(temp_a0, var_a1, &spB0);
                        if (var_fv1 != 0.0f) {
                            var_fv1 = (var_fv1 + 10.0f) / var_fv1;
                        }

                        spC8.x = temp_a0->x + (spB0.x * var_fv1);
                        spC8.y = temp_a0->y + (spB0.y * var_fv1);
                        spC8.z = temp_a0->z + (spB0.z * var_fv1);
                        if (BgCheck_EntityLineTest2(&play->colCtx, &spC8, temp_a0, &pos, &poly, 1, 0, 0, 1, &bgId,
                                                    &this->actor)) {
                            if (!SurfaceType_IsIgnoredByEntities(&play->colCtx, poly, bgId) &&
                                (SurfaceType_GetFloorType(&play->colCtx, poly, bgId) != FLOOR_TYPE_6) &&
                                !func_800B90AC(play, &this->actor, poly, bgId, &pos)) {
                                if (this->transformation == PLAYER_FORM_GORON) {
                                    MtxF sp64;
                                    Vec3s actorRot;
                                    DynaPolyActor* temp_v0;

                                    func_8082DF2C(play);
                                    Player_RequestQuakeAndRumble(play, this, NA_SE_IT_HAMMER_HIT);
                                    if (this->transformation == PLAYER_FORM_GORON) {
                                        Actor_SetPlayerImpact(play, PLAYER_IMPACT_BONK, 2, 100.0f,
                                                              &this->actor.world.pos);
                                        func_800C0094(poly, pos.x, pos.y, pos.z, &sp64);
                                        Matrix_MtxFToYXZRot(&sp64, &actorRot, true);
                                        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_TEST, pos.x, pos.y, pos.z,
                                                    actorRot.x, actorRot.y, actorRot.z, 500);
                                    }

                                    if (bgId != BGCHECK_SCENE) {
                                        temp_v0 = DynaPoly_GetActor(&play->colCtx, bgId);

                                        if (((this->meleeWeaponQuads[0].base.atFlags & AT_HIT) &&
                                             (&temp_v0->actor == this->meleeWeaponQuads[0].base.at)) ||
                                            ((this->meleeWeaponQuads[1].base.atFlags & AT_HIT) &&
                                             (&temp_v0->actor == this->meleeWeaponQuads[1].base.at))) {
                                            return false;
                                        }
                                    }

                                    func_808400CC(play, this);
                                    if (this->transformation != PLAYER_FORM_GORON) {
                                        return true;
                                    }
                                    return false;
                                }

                                if (this->linearVelocity >= 0.0f) {
                                    SurfaceMaterial surfaceMaterial =
                                        SurfaceType_GetMaterial(&play->colCtx, poly, bgId);

                                    if (surfaceMaterial == SURFACE_MATERIAL_WOOD) {
                                        CollisionCheck_SpawnShieldParticlesWood(play, &pos, &this->actor.projectedPos);
                                    } else {
                                        pos.x += 8.0f * COLPOLY_GET_NORMAL(poly->normal.x);
                                        pos.y += 8.0f * COLPOLY_GET_NORMAL(poly->normal.y);
                                        pos.x += 8.0f * COLPOLY_GET_NORMAL(poly->normal.z);
                                        CollisionCheck_SpawnShieldParticles(play, &pos);

                                        if (surfaceMaterial == SURFACE_MATERIAL_DIRT_SOFT) {
                                            Player_PlaySfx(this, NA_SE_IT_WALL_HIT_SOFT);
                                        } else {
                                            Player_PlaySfx(this, NA_SE_IT_WALL_HIT_HARD);
                                        }
                                    }

                                    func_80840094(play, this);
                                    Player_RequestRumble(play, this, 180, 20, 100, SQ(0));
                                    this->linearVelocity = -14.0f;
                                }
                            }
                        }
                    }
                }
            } else {
                func_808400CC(play, this);
                func_8082DF2C(play);
                return true;
            }
        }

        temp_v0_3 = (this->meleeWeaponQuads[0].base.atFlags & AT_HIT) != 0;
        if (temp_v0_3 || (this->meleeWeaponQuads[1].base.atFlags & AT_HIT)) {
            if ((this->meleeWeaponAnimation < PLAYER_MWA_SPIN_ATTACK_1H) &&
                (this->transformation != PLAYER_FORM_GORON)) {
                Actor* temp_v1 = this->meleeWeaponQuads[temp_v0_3 ? 0 : 1].base.at;

                if ((temp_v1 != NULL) && (temp_v1->id != ACTOR_EN_KANBAN)) {
                    func_8082DF2C(play);
                }
            }

            if (!func_8083FF30(play, this)) {
                func_8083FFEC(play, this);
                if (this->actor.colChkInfo.atHitEffect == 1) {
                    this->actor.colChkInfo.damage = 8;
                    func_80833B18(play, this, 4, 0.0f, 0.0f, this->actor.shape.rot.y, 20);
                    return true;
                }
            }
        }
    }

    return false;
}

Vec3f D_8085D2A4 = { 0.0f, 0.0f, 5.0f };

void func_80840770(PlayState* play, Player* this) {
    if (this->actionVar2 != 0) {
        if (this->actionVar2 > 0) {
            this->actionVar2--;
            if (this->actionVar2 == 0) {
                if (this->stateFlags1 & PLAYER_STATE1_8000000) {
                    PlayerAnimation_Change(play, &this->skelAnime, &gPlayerAnim_link_swimer_swim_wait, 1.0f, 0.0f,
                                           Animation_GetLastFrame(&gPlayerAnim_link_swimer_swim_wait), ANIMMODE_ONCE,
                                           -16.0f);
                } else {
                    PlayerAnimation_Change(play, &this->skelAnime, &gPlayerAnim_link_derth_rebirth, 1.0f, 99.0f,
                                           Animation_GetLastFrame(&gPlayerAnim_link_derth_rebirth), ANIMMODE_ONCE,
                                           0.0f);
                }
                gSaveContext.healthAccumulator = 0xA0;
                this->actionVar2 = -1;
            }
        } else if (gSaveContext.healthAccumulator == 0) {
            Player_StopCutscene(this);

            this->stateFlags1 &= ~PLAYER_STATE1_80;
            if (this->stateFlags1 & PLAYER_STATE1_8000000) {
                func_808353DC(play, this);
            } else {
                func_8085B384(this, play);
            }

            this->unk_D6B = 20;
            func_808339B4(this, -20);
            Audio_SetBgmVolumeOn();
        }
    } else if (this->actionVar1 != 0) {
        Player_StopCutscene(this);
        this->csId = play->playerCsIds[PLAYER_CS_ID_REVIVE];
        this->actionVar2 = 60;
        Player_SpawnFairy(play, this, &this->actor.world.pos, &D_8085D2A4, FAIRY_PARAMS(FAIRY_TYPE_5, false, 0));
        Player_PlaySfx(this, NA_SE_EV_FIATY_HEAL - SFX_FLAG);
    } else if (play->gameOverCtx.state == GAMEOVER_DEATH_WAIT_GROUND) {
        play->gameOverCtx.state = GAMEOVER_DEATH_FADE_OUT;
    }
}

void func_80840980(Player* this, u16 sfxId) {
    Player_AnimSfx_PlayVoice(this, sfxId);
}

void func_808409A8(PlayState* play, Player* this, f32 speed, f32 yVelocity) {
    Actor* heldActor = this->heldActor;

    if (!func_808313A8(play, this, heldActor)) {
        heldActor->world.rot.y = this->actor.shape.rot.y;
        heldActor->speed = speed;
        heldActor->velocity.y = yVelocity;
        func_808309CC(play, this);
        Player_PlaySfx(this, NA_SE_PL_THROW);
        Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_SWORD_N);
    }
}

// Check if bonked and if so, rumble, play sound, etc.
s32 func_80840A30(PlayState* play, Player* this, f32* arg2, f32 arg3) {
    Actor* cylinderOc = NULL;

    if (arg3 <= *arg2) {
        // If interacting with a wall and close to facing it
        if (((this->actor.bgCheckFlags & BGCHECKFLAG_PLAYER_WALL_INTERACT) &&
             (sPlayerWorldYawToTouchedWall < 0x1C00)) ||
            // or, impacting something's cylinder
            (((this->cylinder.base.ocFlags1 & OC1_HIT) && (cylinderOc = this->cylinder.base.oc) != NULL) &&
             // and that something is a Beaver Race ring,
             ((cylinderOc->id == ACTOR_EN_TWIG) ||
              // or something is a tree and `this` is close to facing it (note the this actor's facing direction would
              // be antiparallel to the cylinder's actor's yaw if this was directly facing it)
              (((cylinderOc->id == ACTOR_EN_WOOD02) || (cylinderOc->id == ACTOR_EN_SNOWWD) ||
                (cylinderOc->id == ACTOR_OBJ_TREE)) &&
               (ABS_ALT(BINANG_SUB(this->actor.world.rot.y, cylinderOc->yawTowardsPlayer)) > 0x6000))))) {

            if (!func_8082DA90(play)) {
                if (this->doorType == PLAYER_DOORTYPE_STAIRCASE) {
                    func_8085B384(this, play);
                    return true;
                }

                if (cylinderOc != NULL) {
                    cylinderOc->home.rot.y = 1;
                } else if (this->actor.wallBgId != BGCHECK_SCENE) { // i.e. was an actor
                    DynaPolyActor* wallPolyActor = DynaPoly_GetActor(&play->colCtx, this->actor.wallBgId);

                    // Large crates, barrels and palm trees
                    if ((wallPolyActor != NULL) &&
                        ((wallPolyActor->actor.id == ACTOR_OBJ_KIBAKO2) ||
                         (wallPolyActor->actor.id == ACTOR_OBJ_TARU) || (wallPolyActor->actor.id == ACTOR_OBJ_YASI))) {
                        wallPolyActor->actor.home.rot.z = 1;
                    }
                }

                if (!(this->stateFlags3 & PLAYER_STATE3_1000)) {
                    if ((this->stateFlags3 & PLAYER_STATE3_8000) && (Player_Action_28 != this->actionFunc)) {
                        Player_SetAction(play, this, Player_Action_61, 0);
                        func_8082DB90(play, this, &gPlayerAnim_link_swimer_swim_hit);
                        func_8082DD2C(play, this);
                        this->linearVelocity *= 0.2f;
                    } else {
                        Player_SetAction(play, this, Player_Action_26, 0);
                        Player_AnimationPlayOnce(play, this, D_8085BE84[PLAYER_ANIMGROUP_16][this->modelAnimType]);
                        this->actionVar2 = 1;
                    }
                }

                this->linearVelocity = -this->linearVelocity;
                Player_RequestQuake(play, 33267, 3, 12);
                Player_RequestRumble(play, this, 255, 20, 150, SQ(0));
                Actor_SetPlayerImpact(play, PLAYER_IMPACT_BONK, 2, 100.0f, &this->actor.world.pos);
                Player_PlaySfx(this, NA_SE_PL_BODY_HIT);
                Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_CLIMB_END);
                return true;
            }
        }
    }
    return false;
}

s32 func_80840CD4(Player* this, PlayState* play) {
    if (func_808387A0(play, this)) {
        this->stateFlags2 |= PLAYER_STATE2_20000;
    } else if (!CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_B)) {
        PlayerMeleeWeaponAnimation meleeWeaponAnim;

        if ((this->unk_B08 >= 0.85f) || func_808333CC(this)) {
            meleeWeaponAnim = D_8085CF84[Player_IsHoldingTwoHandedWeapon(this)];
        } else {
            meleeWeaponAnim = D_8085CF80[Player_IsHoldingTwoHandedWeapon(this)];
        }
        func_80833864(play, this, meleeWeaponAnim);
        func_808339B4(this, -8);
        this->stateFlags2 |= PLAYER_STATE2_20000;
        if (this->unk_AE3[this->unk_ADE] == 0) {
            this->stateFlags2 |= PLAYER_STATE2_40000000;
        }
    } else {
        return false;
    }

    return true;
}

void func_80840DEC(Player* this, PlayState* play) {
    Player_SetAction(play, this, Player_Action_31, 1);
}

void func_80840E24(Player* this, PlayState* play) {
    Player_SetAction(play, this, Player_Action_32, 1);
}

void func_80840E5C(Player* this, PlayState* play) {
    func_808369F4(this, play);
    func_8082DC38(this);
    func_8082E438(play, this, D_8085CF68[Player_IsHoldingTwoHandedWeapon(this)]);
    this->currentYaw = this->actor.shape.rot.y;
}

void func_80840EC0(Player* this, PlayState* play) {
    Player_SetAction(play, this, Player_Action_30, 1);
    Player_AnimationPlayLoop(play, this, D_8085CF60[Player_IsHoldingTwoHandedWeapon(this)]);
    this->actionVar2 = 1;
    this->unk_B38 = 0.0f;
}

// Spin attack size
void func_80840F34(Player* this) {
    Math_StepToF(&this->unk_B08, CHECK_WEEKEVENTREG(WEEKEVENTREG_OBTAINED_GREAT_SPIN_ATTACK) ? 1.0f : 0.5f, 0.02f);
}

s32 func_80840F90(PlayState* play, Player* this, CsCmdActorCue* cue, f32 arg3, s16 arg4, s32 arg5) {
    if ((arg5 != 0) && (this->linearVelocity == 0.0f)) {
        return PlayerAnimation_Update(play, &this->skelAnime);
    }

    if (arg5 != 2) {
        f32 halfUpdateRate = R_UPDATE_RATE / 2.0f;
        f32 curDiffX = cue->endPos.x - this->actor.world.pos.x;
        f32 curDiffZ = cue->endPos.z - this->actor.world.pos.z;
        f32 scaledCurDist = sqrtf(SQ(curDiffX) + SQ(curDiffZ)) / halfUpdateRate;
        s32 framesLeft = (cue->endFrame - play->csCtx.curFrame) + 1;

        arg4 = Math_Atan2S_XY(curDiffZ, curDiffX);

        if (arg5 == 1) {
            f32 distX = cue->endPos.x - cue->startPos.x;
            f32 distZ = cue->endPos.z - cue->startPos.z;
            s32 temp =
                (((sqrtf(SQ(distX) + SQ(distZ)) / halfUpdateRate) / (cue->endFrame - cue->startFrame)) / 1.5f) * 4.0f;
            if (temp >= framesLeft) {
                arg3 = 0.0f;
                arg4 = this->actor.shape.rot.y;
            } else {
                arg3 = scaledCurDist / ((framesLeft - temp) + 1);
            }
        } else {
            arg3 = scaledCurDist / framesLeft;
        }
    }

    this->stateFlags2 |= PLAYER_STATE2_20;
    func_8083F57C(this, play);
    func_8083CB58(this, arg3, arg4);
    if ((arg3 == 0.0f) && (this->linearVelocity == 0.0f)) {
        func_80839CD8(this, play);
    }

    return false;
}

s32 func_808411D4(PlayState* play, Player* this, f32* arg2, s32 arg3) {
    f32 xDiff = this->unk_3A0.x - this->actor.world.pos.x;
    f32 yDiff = this->unk_3A0.z - this->actor.world.pos.z;
    s32 sp2C;
    s32 pad2;
    s16 var_v1;

    sp2C = sqrtf(SQ(xDiff) + SQ(yDiff));
    var_v1 = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_3A0);
    if (sp2C < arg3) {
        *arg2 = 0.0f;
        var_v1 = this->actor.shape.rot.y;
    }
    if (func_80840F90(play, this, NULL, *arg2, var_v1, 2)) {
        return 0;
    }
    return sp2C;
}

void Player_InitMode_0(PlayState* play, Player* this) {
    this->actor.update = func_801229EC;
    this->actor.draw = NULL;
}

void Player_InitMode_2(PlayState* play, Player* this) {
    Player_SetAction(play, this, Player_Action_76, 0);
    this->stateFlags1 |= PLAYER_STATE1_20000000;
    PlayerAnimation_Change(play, &this->skelAnime, &gPlayerAnim_link_okarina_warp_goal, 2.0f / 3.0f, 0.0f, 24.0f,
                           ANIMMODE_ONCE, 0.0f);
    this->actor.world.pos.y += 800.0f;
}

u8 D_8085D2B0[] = {
    ITEM_SWORD_RAZOR,
    ITEM_SWORD_KOKIRI,
};

// OoT leftover?
void func_80841358(PlayState* play, Player* this, s32 arg2) {
    ItemId item;
    PlayerItemAction itemAction;

    //! @bug OoB read if player is goron, deku or human
    item = D_8085D2B0[this->transformation];
    itemAction = sItemItemActions[item];
    Player_DestroyHookshot(this);
    Player_DetachHeldActor(play, this);
    this->heldItemId = item;
    this->nextModelGroup = Player_ActionToModelGroup(this, itemAction);
    Player_InitItemAction(play, this, itemAction);
    func_808309CC(play, this);
    if (arg2) {
        Player_PlaySfx(this, NA_SE_IT_SWORD_PICKOUT);
    }
}

Vec3f D_8085D2B4 = { -1.0f, 69.0f, 20.0f };

void Player_InitMode_1(PlayState* play, Player* this) {
    Player_SetAction(play, this, Player_Action_66, 0);
    this->stateFlags1 |= PLAYER_STATE1_20000000;
    Math_Vec3f_Copy(&this->actor.world.pos, &D_8085D2B4);
    this->currentYaw = this->actor.shape.rot.y = -0x8000;
    PlayerAnimation_Change(play, &this->skelAnime, this->ageProperties->unk_A8, 2.0f / 3.0f, 0.0f, 0.0f, ANIMMODE_ONCE,
                           0.0f);
    func_8082E920(play, this,
                  ANIM_FLAG_1 | ANIM_FLAG_UPDATE_Y | ANIM_FLAG_4 | ANIM_FLAG_8 | ANIM_FLAG_80 | ANIM_FLAG_200);
    if (this->transformation == PLAYER_FORM_FIERCE_DEITY) {
        func_80841358(play, this, false);
    }
    this->actionVar2 = 20;
}

void Player_InitMode_3(PlayState* play, Player* this) {
    Player_SetAction(play, this, Player_Action_78, 0);
    func_8082E920(play, this, ANIM_FLAG_1 | ANIM_FLAG_UPDATE_Y | ANIM_FLAG_8 | ANIM_FLAG_NOMOVE | ANIM_FLAG_80);
}

void Player_InitMode_4(PlayState* play, Player* this) {
    func_80834DB8(this, &gPlayerAnim_link_normal_jump, 12.0f, play);
    Player_SetAction(play, this, Player_Action_79, 0);
    this->stateFlags1 |= PLAYER_STATE1_20000000;
    this->fallStartHeight = this->actor.world.pos.y;
}

void Player_InitMode_7(PlayState* play, Player* this) {
    func_80833B18(play, this, 1, 2.0f, 2.0f, this->actor.shape.rot.y + 0x8000, 0);
}

void Player_InitMode_5(PlayState* play, Player* this) {
    Player_SetAction(play, this, Player_Action_75, 0);
    this->actor.draw = NULL;
    this->stateFlags1 |= PLAYER_STATE1_20000000;
}

void Player_InitMode_6(PlayState* play, Player* this) {
    if (gSaveContext.save.isOwlSave) {
        Player_SetAction(play, this, Player_Action_0, 0);
        func_8082E514(play, this, D_8085BE84[PLAYER_ANIMGROUP_43][this->modelAnimType]);
        this->stateFlags1 |= PLAYER_STATE1_20000000;
        this->actionVar2 = 0x28;
        gSaveContext.save.isOwlSave = false;
    } else {
        Player_SetAction(play, this, Player_Action_4, 0);
        func_8082E514(play, this, D_8085BE84[PLAYER_ANIMGROUP_43][this->modelAnimType]);
        this->stateFlags1 |= PLAYER_STATE1_20000000;
        this->stateFlags2 |= PLAYER_STATE2_20000000;
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_TEST7, this->actor.world.pos.x, this->actor.world.pos.y,
                    this->actor.world.pos.z, 0, 0, 0, ENTEST7_MINUS1);
    }
}

// InitModes 0x8 and 0x9
void func_80841744(PlayState* play, Player* this) {
    Player_SetAction(play, this, Player_Action_91, 0);
    if (PLAYER_GET_INITMODE(&this->actor) == PLAYER_INITMODE_8) {
        Player_AnimationPlayOnceReverse(play, this, D_8085D17C[this->transformation]);
        this->itemAction = PLAYER_IA_OCARINA;
        Player_SetModels(this, Player_ActionToModelGroup(this, this->itemAction));
    } else {
        func_8082DB60(play, this, D_8085BE84[PLAYER_ANIMGROUP_43][this->modelAnimType]);
    }
    this->stateFlags1 |= PLAYER_STATE1_20000000;
    this->unk_ABC = -10000.0f;
    this->actionVar2 = 0x2710;
    this->unk_B10[5] = 8.0f;
}

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 500, ICHAIN_STOP),
};

Vec3s sPlayerSkeletonBaseTransl = { -57, 3377, 0 };

void Player_InitCommon(Player* this, PlayState* play, FlexSkeletonHeader* skelHeader) {
    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->currentYaw = this->actor.world.rot.y;

    if ((PLAYER_GET_INITMODE(&this->actor) != PLAYER_INITMODE_TELESCOPE) &&
        ((gSaveContext.respawnFlag != 2) ||
         (gSaveContext.respawn[RESPAWN_MODE_RETURN].playerParams != PLAYER_PARAMS(0xFF, PLAYER_INITMODE_TELESCOPE)))) {
        func_808309CC(play, this);
        SkelAnime_InitPlayer(play, &this->skelAnime, skelHeader, D_8085BE84[PLAYER_ANIMGROUP_0][this->modelAnimType],
                             1 | 8, this->jointTableBuffer, this->morphTableBuffer, PLAYER_LIMB_MAX);
        this->skelAnime.baseTransl = sPlayerSkeletonBaseTransl;

        SkelAnime_InitPlayer(play, &this->skelAnimeUpper, skelHeader, func_8082ED20(this), 1 | 8,
                             this->jointTableUpperBuffer, this->morphTableUpperBuffer, PLAYER_LIMB_MAX);
        this->skelAnimeUpper.baseTransl = sPlayerSkeletonBaseTransl;

        if (this->transformation == PLAYER_FORM_GORON) {
            SkelAnime_InitFlex(play, &this->unk_2C8, &gLinkGoronShieldingSkel, &gLinkGoronShieldingAnim,
                               this->jointTable, this->morphTable, LINK_GORON_SHIELDING_LIMB_MAX);
        }

        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFeet, this->ageProperties->shadowScale);
    }

    this->subCamId = CAM_ID_NONE;
    Collider_InitAndSetCylinder(play, &this->cylinder, &this->actor, &D_8085C2EC);
    Collider_InitAndSetCylinder(play, &this->shieldCylinder, &this->actor, &D_8085C318);
    Collider_InitAndSetQuad(play, &this->meleeWeaponQuads[0], &this->actor, &D_8085C344);
    Collider_InitAndSetQuad(play, &this->meleeWeaponQuads[1], &this->actor, &D_8085C344);
    Collider_InitAndSetQuad(play, &this->shieldQuad, &this->actor, &D_8085C394);
}

void func_80841A50(PlayState* play, Player* this) {
    if ((play->roomCtx.curRoom.num >= 0) && (play->roomCtx.prevRoom.num < 0)) {
        Math_Vec3f_Copy(&this->unk_3C0, &this->actor.world.pos);
        this->unk_3CC = this->actor.shape.rot.y;
        this->unk_3CE = play->roomCtx.curRoom.num;
        this->unk_3CF = 1;
    }
}

typedef void (*PlayerInitModeFunc)(PlayState*, Player*);

// Initialisation functions for various gameplay modes depending on spawn params. There may be at most 0x10 due to it
// using a single nybble.
// sInitModeFuncs
PlayerInitModeFunc D_8085D2CC[0x10] = {
    /* 0x0 */ Player_InitMode_0,
    /* 0x1 */ Player_InitMode_1,
    /* 0x2 */ Player_InitMode_2,
    /* 0x3 */ Player_InitMode_3,
    /* 0x4 */ Player_InitMode_4,
    /* 0x5 */ Player_InitMode_5,
    /* 0x6 */ Player_InitMode_6,
    /* 0x7 */ Player_InitMode_7,
    /* 0x8 */ func_80841744,
    /* 0x9 */ func_80841744,
    /* 0xA */ func_8083ADF0,
    /* 0xB */ Player_InitMode_B,
    /* 0xC */ Player_InitMode_Telescope,
    /* 0xD */ Player_InitMode_D,
    /* 0xE */ func_8083ADF0,
    /* 0xF */ Player_InitMode_F,
};

// sBlureInit
EffectBlureInit2 D_8085D30C = {
    0, 8, 0, { 255, 255, 255, 255 }, { 255, 255, 255, 64 }, { 255, 255, 255, 0 }, { 255, 255, 255, 0 }, 4,
    0, 2, 0, { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
};

// sTireMarkInit ?
EffectTireMarkInit D_8085D330 = { 0, 63, { 0, 0, 15, 100 } };

// sTireMarkGoronColor ?
Color_RGBA8 D_8085D338 = { 0, 0, 15, 100 };
// sTireMarkOtherColor ?
Color_RGBA8 D_8085D33C = { 0, 0, 0, 150 };
Vec3f D_8085D340 = { 0.0f, 50.0f, 0.0f };

void Player_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    Player* this = THIS;
    s8 objectSlot;
    s32 respawnFlag;
    s32 var_a1;
    PlayerInitMode initMode;

    play->playerInit = Player_InitCommon;
    play->playerUpdate = Player_UpdateCommon;
    play->unk_18770 = func_8085B170;
    play->startPlayerFishing = Player_StartFishing;
    play->grabPlayer = Player_GrabPlayer;
    play->startPlayerCutscene = func_8085B28C;
    play->func_18780 = func_8085B384;
    play->damagePlayer = Player_InflictDamage;
    play->talkWithPlayer = Player_TalkWithPlayer;
    play->unk_1878C = func_8085B74C;
    play->unk_18790 = func_8085B820;
    play->unk_18794 = func_8085B854;
    play->setPlayerTalkAnim = func_8085B930;

    gActorOverlayTable[ACTOR_PLAYER].initInfo->objectId = GAMEPLAY_KEEP;

    this->actor.room = -1;
    this->csId = CS_ID_NONE;

    if (this->actor.shape.rot.x != 0) {
        this->transformation = this->actor.shape.rot.x - 1;

        objectSlot = Object_GetSlot(&play->objectCtx, gPlayerFormObjectIds[this->transformation]);
        this->actor.objectSlot = objectSlot;
        if (objectSlot <= OBJECT_SLOT_NONE) {
            Actor_Kill(&this->actor);
            return;
        }

        Actor_SetObjectDependency(play, &this->actor);
    } else {
        this->transformation = GET_PLAYER_FORM;
        if (this->transformation == PLAYER_FORM_HUMAN) {
            if (gSaveContext.save.equippedMask == PLAYER_MASK_GIANT) {
                gSaveContext.save.equippedMask = PLAYER_MASK_NONE;
            }
            this->currentMask = gSaveContext.save.equippedMask;
        } else {
            this->currentMask = this->transformation + PLAYER_MASK_FIERCE_DEITY;
            gSaveContext.save.equippedMask = PLAYER_MASK_NONE;
        }

        Inventory_UpdateDeitySwordEquip(play);

        this->unk_B28 = 0;
        this->unk_B90 = 0;
        this->unk_B92 = 0;
        this->unk_B94 = 0;
        this->unk_B96 = 0;
        this->stateFlags1 &= ~(PLAYER_STATE1_8 | PLAYER_STATE1_1000 | PLAYER_STATE1_1000000 | PLAYER_STATE1_2000000);
        this->stateFlags2 &= ~(PLAYER_STATE2_20000 | PLAYER_STATE2_1000000 | PLAYER_STATE2_40000000);
        this->stateFlags3 &=
            ~(PLAYER_STATE3_8 | PLAYER_STATE3_40 | PLAYER_STATE3_80 | PLAYER_STATE3_100 | PLAYER_STATE3_200 |
              PLAYER_STATE3_800 | PLAYER_STATE3_1000 | PLAYER_STATE3_2000 | PLAYER_STATE3_8000 | PLAYER_STATE3_10000 |
              PLAYER_STATE3_40000 | PLAYER_STATE3_80000 | PLAYER_STATE3_100000 | PLAYER_STATE3_200000 |
              PLAYER_STATE3_800000 | PLAYER_STATE3_1000000 | PLAYER_STATE3_2000000);
        this->unk_B08 = 0.0f;
        this->unk_B0C = 0.0f;
    }

    if (this->transformation == PLAYER_FORM_ZORA) {
        if (this->stateFlags1 & PLAYER_STATE1_8000000) {
            this->unk_B10[0] = 1.0f;
        } else {
            this->unk_B10[0] = 0.0f;
        }
    }

    this->actor.flags &= ~(ACTOR_FLAG_CAN_PRESS_HEAVY_SWITCH | ACTOR_FLAG_CAN_PRESS_SWITCH);
    if (this->transformation != PLAYER_FORM_DEKU) {
        this->actor.flags |= ACTOR_FLAG_CAN_PRESS_SWITCH;
        if (this->transformation == PLAYER_FORM_GORON) {
            this->actor.flags |= ACTOR_FLAG_CAN_PRESS_HEAVY_SWITCH;
        }
    }

    this->ageProperties = &sPlayerAgeProperties[this->transformation];

    this->itemAction = PLAYER_IA_NONE;
    this->heldItemAction = PLAYER_IA_NONE;
    this->heldItemId = ITEM_NONE;

    Player_UseItem(play, this, ITEM_NONE);
    Player_SetEquipmentData(play, this);
    this->prevBoots = this->currentBoots;
    Player_InitCommon(this, play, gPlayerSkeletons[this->transformation]);

    if (this->actor.shape.rot.z != 0) {
        EffectTireMark* tireMark;

        this->actor.shape.rot.z = 0;
        Player_OverrideBlureColors(play, this, 0, 4);

        tireMark = Effect_GetByIndex(this->meleeWeaponEffectIndex[2]);
        if (this->transformation == PLAYER_FORM_GORON) {
            tireMark->color = D_8085D338;
        } else {
            tireMark->color = D_8085D33C;
        }

        if ((this->csMode == PLAYER_CSMODE_9) || (this->csMode == PLAYER_CSMODE_93)) {
            Player_SetAction(play, this, Player_Action_97, 0);
            this->stateFlags1 |= PLAYER_STATE1_20000000;
        } else {
            Player_SetAction(play, this, Player_Action_87, 0);
            this->actor.shape.rot.y = this->currentYaw;

            if (this->prevMask != PLAYER_MASK_NONE) {
                func_8082DB90(play, this, &gPlayerAnim_cl_maskoff);
            } else if (this->transformation == PLAYER_FORM_HUMAN) {
                PlayerAnimation_Change(play, &this->skelAnime, D_8085D160[this->transformation], -2.0f / 3.0f, 9.0f,
                                       0.0f, ANIMMODE_ONCE, 0.0f);
            } else {
                func_8082DB60(play, this, &gPlayerAnim_cl_setmaskend);
            }

            this->stateFlags1 |= (PLAYER_STATE1_10000000 | PLAYER_STATE1_20000000);
            this->stateFlags3 |= PLAYER_STATE3_20000;
            this->unk_B10[5] = 3.0f;
        }
        return;
    }

    this->prevMask = this->currentMask;

    Effect_Add(play, &this->meleeWeaponEffectIndex[0], EFFECT_BLURE2, 0, 0, &D_8085D30C);
    Effect_Add(play, &this->meleeWeaponEffectIndex[1], EFFECT_BLURE2, 0, 0, &D_8085D30C);

    Player_OverrideBlureColors(play, this, 0, 4);
    if (this->transformation == PLAYER_FORM_GORON) {
        D_8085D330.color = D_8085D338;
    } else {
        D_8085D330.color = D_8085D33C;
    }
    Effect_Add(play, &this->meleeWeaponEffectIndex[2], EFFECT_TIRE_MARK, 0, 0, &D_8085D330);

    if (this->actor.shape.rot.x != 0) {
        this->actor.shape.rot.x = 0;
        this->csMode = PLAYER_CSMODE_68;
        Player_SetAction(play, this, Player_Action_97, 0);
        this->stateFlags1 |= PLAYER_STATE1_20000000;
        return;
    }

    play->unk_1887C = 0;
    play->unk_1887D = 0;
    play->unk_1887E = 0;
    this->giObjectSegment = ZeldaArena_Malloc(0x2000);
    this->maskObjectSegment = ZeldaArena_Malloc(0x3800);

    Lights_PointNoGlowSetInfo(&this->lightInfo, this->actor.world.pos.x, this->actor.world.pos.y,
                              this->actor.world.pos.z, 255, 128, 0, -1);
    this->lightNode = LightContext_InsertLight(play, &play->lightCtx, &this->lightInfo);
    Play_AssignPlayerCsIdsFromScene(&play->state, this->actor.csId);

    respawnFlag = gSaveContext.respawnFlag;
    if (respawnFlag != 0) {
        if (respawnFlag == -3) {
            this->actor.params = gSaveContext.respawn[RESPAWN_MODE_UNK_3].playerParams;
        } else {
            if ((respawnFlag == 1) || (respawnFlag == -1)) {
                this->unk_D6A = -2;
            }

            if (respawnFlag != -7) {
                s32 respawnIndex;

                if ((respawnFlag == -8) || (respawnFlag == -5) || (respawnFlag == -4)) {
                    respawnFlag = 1;
                }

                if ((respawnFlag < 0) && (respawnFlag != -1) && (respawnFlag != -6)) {
                    respawnIndex = RESPAWN_MODE_DOWN;
                } else {
                    respawnIndex = (respawnFlag < 0) ? RESPAWN_MODE_TOP : respawnFlag - 1;

                    Math_Vec3f_Copy(&this->actor.world.pos, &gSaveContext.respawn[respawnIndex].pos);
                    Math_Vec3f_Copy(&this->actor.home.pos, &this->actor.world.pos);
                    Math_Vec3f_Copy(&this->actor.prevPos, &this->actor.world.pos);
                    Math_Vec3f_Copy(&this->actor.focus.pos, &this->actor.world.pos);

                    this->fallStartHeight = this->actor.world.pos.y;

                    this->currentYaw = this->actor.shape.rot.y = gSaveContext.respawn[respawnIndex].yaw;
                    this->actor.params = gSaveContext.respawn[respawnIndex].playerParams;
                }

                play->actorCtx.sceneFlags.switches[2] = gSaveContext.respawn[respawnIndex].tempSwitchFlags;
                play->actorCtx.sceneFlags.collectible[1] = gSaveContext.respawn[respawnIndex].unk_18;
                play->actorCtx.sceneFlags.collectible[2] = gSaveContext.respawn[respawnIndex].tempCollectFlags;
            }
        }
    }

    var_a1 = ((respawnFlag == 4) || (gSaveContext.respawnFlag == -4)) ? 1 : 0;
    if (func_801226E0(play, var_a1) == 0) {
        gSaveContext.respawn[RESPAWN_MODE_DOWN].playerParams = PLAYER_PARAMS(thisx->params, PLAYER_INITMODE_D);
    }

    gSaveContext.respawn[RESPAWN_MODE_DOWN].data = 1;
    if (respawnFlag == 0) {
        gSaveContext.respawn[RESPAWN_MODE_TOP] = gSaveContext.respawn[RESPAWN_MODE_DOWN];
    }
    gSaveContext.respawn[RESPAWN_MODE_TOP].playerParams =
        PLAYER_PARAMS(gSaveContext.respawn[RESPAWN_MODE_TOP].playerParams, PLAYER_INITMODE_D);

    initMode = PLAYER_GET_INITMODE(&this->actor);
    if (((initMode == PLAYER_INITMODE_5) || (initMode == PLAYER_INITMODE_6)) &&
        (gSaveContext.save.cutsceneIndex >= 0xFFF0)) {
        initMode = PLAYER_INITMODE_D;
    }

    D_8085D2CC[initMode](play, this);

    if ((this->actor.draw != NULL) && gSaveContext.save.hasTatl &&
        ((gSaveContext.gameMode == GAMEMODE_NORMAL) || (gSaveContext.gameMode == GAMEMODE_END_CREDITS)) &&
        (play->sceneId != SCENE_SPOT00)) {
        this->tatlActor =
            Player_SpawnFairy(play, this, &this->actor.world.pos, &D_8085D340, FAIRY_PARAMS(FAIRY_TYPE_0, false, 0));

        if (gSaveContext.dogParams != 0) {
            gSaveContext.dogParams |= 0x8000;
        }

        if (gSaveContext.powderKegTimer != 0) {
            this->nextModelGroup = Player_ActionToModelGroup(this, PLAYER_IA_POWDER_KEG);
            this->heldItemId = ITEM_POWDER_KEG;
            Player_InitItemAction(play, this, PLAYER_IA_POWDER_KEG);
            func_808313F0(this, play);
        } else if (gSaveContext.unk_1014 != 0) {
            func_8082F5FC(this, Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_MM,
                                                   this->actor.world.pos.x, this->actor.world.pos.y,
                                                   this->actor.world.pos.z, 0, this->actor.shape.rot.y, 0, 0x8000));
            func_808313F0(this, play);
        }
    }

    Minimap_SavePlayerRoomInitInfo(play);
    func_80841A50(play, this);
    this->unk_3CF = 0;
    R_PLAY_FILL_SCREEN_ON = 0;
}

void func_80842510(s16* arg0) {
    s16 temp_ft0;

    temp_ft0 = (ABS_ALT(*arg0) * 100.0f) / 1000.0f;
    temp_ft0 = CLAMP(temp_ft0, 0x190, 0xFA0);

    Math_ScaledStepToS(arg0, 0, temp_ft0);
}

void func_808425B4(Player* this) {
    if (!(this->unk_AA6 & 2)) {
        s16 sp26 = this->actor.focus.rot.y - this->actor.shape.rot.y;

        func_80842510(&sp26);
        this->actor.focus.rot.y = this->actor.shape.rot.y + sp26;
    }
    if (!(this->unk_AA6 & 1)) {
        func_80842510(&this->actor.focus.rot.x);
    }
    if (!(this->unk_AA6 & 8)) {
        func_80842510(&this->headLimbRot.x);
    }
    if (!(this->unk_AA6 & 0x40)) {
        func_80842510(&this->upperLimbRot.x);
    }
    if (!(this->unk_AA6 & 4)) {
        func_80842510(&this->actor.focus.rot.z);
    }
    if (!(this->unk_AA6 & 0x10)) {
        func_80842510(&this->headLimbRot.y);
    }
    if (!(this->unk_AA6 & 0x20)) {
        func_80842510(&this->headLimbRot.z);
    }
    if (!(this->unk_AA6 & 0x80)) {
        if (this->unk_AA8 != 0) {
            func_80842510(&this->unk_AA8);
        } else {
            func_80842510(&this->upperLimbRot.y);
        }
    }
    if (!(this->unk_AA6 & 0x100)) {
        func_80842510(&this->upperLimbRot.z);
    }

    this->unk_AA6 = 0;
}

/**
 * Sets the DoAction for the interface A/B buttons, depending on a significant number of things
 */
void Player_SetDoAction(PlayState* play, Player* this) {
    DoAction doActionB;
    s32 sp38;

    if (this != GET_PLAYER(play)) {
        return;
    }

    doActionB = -1;
    sp38 = func_801242B4(this) || (Player_Action_28 == this->actionFunc);

    // Set B do action
    if (this->transformation == PLAYER_FORM_GORON) {
        if (this->stateFlags3 & PLAYER_STATE3_80000) {
            doActionB = DO_ACTION_NONE;
        } else if (this->stateFlags3 & PLAYER_STATE3_1000) {
            doActionB = DO_ACTION_POUND;
        } else {
            doActionB = DO_ACTION_PUNCH;
        }
    } else if (this->transformation == PLAYER_FORM_ZORA) {
        if ((!(this->stateFlags1 & PLAYER_STATE1_8000000)) ||
            (!sp38 && (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND))) {
            doActionB = DO_ACTION_PUNCH;
        } else {
            doActionB = DO_ACTION_DIVE;
        }
    } else if (this->transformation == PLAYER_FORM_DEKU) {
        doActionB = DO_ACTION_SHOOT;
    } else { // PLAYER_FORM_HUMAN
        if (this->currentMask == PLAYER_MASK_BLAST) {
            doActionB = DO_ACTION_EXPLODE;
        } else if (this->currentMask == PLAYER_MASK_BREMEN) {
            doActionB = DO_ACTION_MARCH;
        } else if (this->currentMask == PLAYER_MASK_KAMARO) {
            doActionB = DO_ACTION_DANCE;
        }
    }

    if (doActionB > -1) {
        func_801155B4(play, doActionB);
    } else if (play->interfaceCtx.unk_21C != 0) {
        play->interfaceCtx.unk_21C = 0;
        play->interfaceCtx.bButtonDoAction = 0;
    }

    // Set A do action
    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_NONE) ||
        ((play->msgCtx.currentTextId >= 0x100) && (play->msgCtx.currentTextId <= 0x200)) ||
        ((play->msgCtx.currentTextId >= 0x1BB2) && (play->msgCtx.currentTextId < 0x1BB7))) {
        Actor* heldActor = this->heldActor;
        Actor* interactRangeActor = this->interactRangeActor;
        s32 pad;
        s32 sp28 = this->unk_AE3[this->unk_ADE];
        s32 sp24;
        DoAction doActionA =
            ((this->transformation == PLAYER_FORM_GORON) && !(this->stateFlags1 & PLAYER_STATE1_400000))
                ? DO_ACTION_CURL
                : DO_ACTION_NONE;

        if (play->actorCtx.flags & ACTORCTX_FLAG_PICTO_BOX_ON) {
            doActionA = DO_ACTION_SNAP;
        } else if (Player_InBlockingCsMode(play, this) || (this->actor.flags & ACTOR_FLAG_20000000) ||
                   (this->stateFlags1 & PLAYER_STATE1_1000) || (this->stateFlags3 & PLAYER_STATE3_80000) ||
                   (Player_Action_80 == this->actionFunc)) {
            doActionA = DO_ACTION_NONE;
        } else if (this->stateFlags1 & PLAYER_STATE1_100000) {
            doActionA = DO_ACTION_RETURN;
        } else if ((this->heldItemAction == PLAYER_IA_FISHING_ROD) && (this->unk_B28 != 0)) {
            doActionA = (this->unk_B28 == 2) ? DO_ACTION_REEL : DO_ACTION_NONE;
            doActionA = (this->unk_B28 == 2) ? DO_ACTION_REEL : DO_ACTION_NONE; //! FAKE: duplicated statement
        } else if (this->stateFlags3 & PLAYER_STATE3_2000) {
            doActionA = DO_ACTION_DOWN;
        } else if ((this->doorType != PLAYER_DOORTYPE_NONE) && (this->doorType != PLAYER_DOORTYPE_STAIRCASE) &&
                   !(this->stateFlags1 & PLAYER_STATE1_800)) {
            doActionA = DO_ACTION_OPEN;
        } else if (this->stateFlags3 & PLAYER_STATE3_200000) {
            static u8 D_8085D34C[] = {
                DO_ACTION_1, DO_ACTION_2, DO_ACTION_3, DO_ACTION_4, DO_ACTION_5, DO_ACTION_6, DO_ACTION_7, DO_ACTION_8,
            };

            doActionA = D_8085D34C[this->remainingHopsCounter];
        } else if ((!(this->stateFlags1 & PLAYER_STATE1_800) || (heldActor == NULL)) && (interactRangeActor != NULL) &&
                   (this->getItemId < GI_NONE)) {
            doActionA = DO_ACTION_OPEN;
        } else if (!sp38 && (this->stateFlags2 & PLAYER_STATE2_1)) {
            doActionA = DO_ACTION_GRAB;
        } else if ((this->stateFlags2 & PLAYER_STATE2_4) ||
                   (!(this->stateFlags1 & PLAYER_STATE1_800000) && (this->rideActor != NULL))) {
            doActionA = DO_ACTION_CLIMB;
        } else if ((this->stateFlags1 & PLAYER_STATE1_800000) &&
                   (!EN_HORSE_CHECK_4((EnHorse*)this->rideActor) && (Player_Action_53 != this->actionFunc))) {
            if ((this->stateFlags2 & PLAYER_STATE2_2) && (this->talkActor != NULL)) {
                if ((this->talkActor->category == ACTORCAT_NPC) || (this->talkActor->id == ACTOR_DM_CHAR08)) {
                    doActionA = DO_ACTION_SPEAK;
                } else {
                    doActionA = DO_ACTION_CHECK;
                }
            } else if (!func_8082DA90(play) && !func_800B7128(this) && !(this->stateFlags1 & PLAYER_STATE1_100000)) {
                doActionA = DO_ACTION_FASTER;
            } else {
                doActionA = DO_ACTION_NONE;
            }
        } else if ((this->stateFlags2 & PLAYER_STATE2_2) && (this->talkActor != NULL)) {
            if ((this->talkActor->category == ACTORCAT_NPC) || (this->talkActor->category == ACTORCAT_ENEMY) ||
                (this->talkActor->id == ACTOR_DM_CHAR08)) {
                doActionA = DO_ACTION_SPEAK;
            } else {
                doActionA = DO_ACTION_CHECK;
            }
        } else if ((this->stateFlags1 & (PLAYER_STATE1_2000 | PLAYER_STATE1_200000)) ||
                   ((this->stateFlags1 & PLAYER_STATE1_800000) && (this->stateFlags2 & PLAYER_STATE2_400000))) {
            doActionA = DO_ACTION_DOWN;
        } else if ((this->stateFlags1 & PLAYER_STATE1_800) && (this->getItemId == GI_NONE) && (heldActor != NULL)) {
            if ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) || (heldActor->id == ACTOR_EN_NIW)) {
                if (!func_8083D738(this, heldActor)) {
                    doActionA = DO_ACTION_DROP;
                } else {
                    doActionA = DO_ACTION_THROW;
                }
            } else {
                doActionA = DO_ACTION_NONE;
            }
        } else if (this->stateFlags2 & PLAYER_STATE2_10000) {
            doActionA = DO_ACTION_GRAB;
        } else if (this->stateFlags2 & PLAYER_STATE2_800) {
            static u8 D_8085D354[] = { DO_ACTION_1, DO_ACTION_2 };
            s32 var_v0;

            var_v0 = ((120.0f - this->actor.depthInWater) / 40.0f);
            var_v0 = CLAMP(var_v0, 0, ARRAY_COUNT(D_8085D354) - 1);

            doActionA = D_8085D354[var_v0];
        } else if (this->stateFlags3 & PLAYER_STATE3_100) {
            doActionA = DO_ACTION_JUMP;
        } else if (this->stateFlags3 & PLAYER_STATE3_1000) {
            doActionA = DO_ACTION_RETURN;
        } else if (!func_8082FBE8(this) && (this->stateFlags1 & PLAYER_STATE1_8000000) && !sp38) {
            doActionA = DO_ACTION_SURFACE;
        } else if (((this->transformation != PLAYER_FORM_DEKU) &&
                    (sp38 || ((this->stateFlags1 & PLAYER_STATE1_8000000) &&
                              !(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)))) ||
                   ((this->transformation == PLAYER_FORM_DEKU) && (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) &&
                    func_800C9DDC(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId))) {
            doActionA = (this->transformation == PLAYER_FORM_ZORA) ? DO_ACTION_SWIM
                        : ((this->stateFlags1 & PLAYER_STATE1_8000000) && (interactRangeActor != NULL) &&
                           (interactRangeActor->id == ACTOR_EN_ZOG))
                            ? DO_ACTION_GRAB
                            : DO_ACTION_DIVE;
        } else {
            sp24 = func_8082FBE8(this);
            if ((sp24 && (this->transformation != PLAYER_FORM_DEKU)) || !(this->stateFlags1 & PLAYER_STATE1_400000) ||
                !Player_IsGoronOrDeku(this)) {
                if ((this->transformation != PLAYER_FORM_GORON) &&
                    !(this->stateFlags1 & (PLAYER_STATE1_4 | PLAYER_STATE1_4000)) && (sp28 <= 0) &&
                    (func_80123420(this) ||
                     ((sPlayerFloorType != FLOOR_TYPE_7) &&
                      (func_80123434(this) || ((play->roomCtx.curRoom.behaviorType1 != ROOM_BEHAVIOR_TYPE1_2) &&
                                               !(this->stateFlags1 & PLAYER_STATE1_400000) && (sp28 == 0)))))) {
                    doActionA = DO_ACTION_ATTACK;
                } else if ((play->roomCtx.curRoom.behaviorType1 != ROOM_BEHAVIOR_TYPE1_2) && sp24 && (sp28 > 0)) {
                    doActionA = DO_ACTION_JUMP;
                } else if ((this->transformation == PLAYER_FORM_DEKU) && !(this->stateFlags1 & PLAYER_STATE1_8000000) &&
                           (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
                    doActionA = DO_ACTION_ATTACK;
                } else if (((this->transformation == PLAYER_FORM_HUMAN) ||
                            (this->transformation == PLAYER_FORM_ZORA)) &&
                           ((this->heldItemAction >= PLAYER_IA_SWORD_KOKIRI) ||
                            ((this->stateFlags2 & PLAYER_STATE2_100000) &&
                             (play->actorCtx.targetCtx.fairyActor == NULL)))) {
                    doActionA = DO_ACTION_PUTAWAY;

                    if (play->msgCtx.currentTextId == 0) {} //! FAKE
                }
            }
        }

        if (doActionA != DO_ACTION_PUTAWAY) {
            this->putAwayCountdown = 20;
        } else if (this->putAwayCountdown != 0) {
            doActionA = DO_ACTION_NONE;
            this->putAwayCountdown--;
        }

        func_8011552C(play, doActionA);

        // Set Tatl state
        if (!Play_InCsMode(play) && (this->stateFlags2 & PLAYER_STATE2_200000) &&
            !(this->stateFlags3 & PLAYER_STATE3_100)) {
            if (this->lockOnActor != NULL) {
                func_80115764(play, 0x2B);
            } else {
                func_80115764(play, 0x2A);
            }
            CutsceneManager_Queue(CS_ID_GLOBAL_TALK);
        } else {
            func_80115764(play, 0x2C);
        }
    }
}

s32 func_808430E0(Player* this) {
    if ((this->transformation == PLAYER_FORM_DEKU) && (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) &&
        func_8083784C(this)) {
        this->actor.bgCheckFlags &= ~BGCHECKFLAG_GROUND;
    }
    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        return false;
    }

    if (!(this->stateFlags1 & PLAYER_STATE1_8000000)) {
        sPlayerFloorType = FLOOR_TYPE_0;
    }
    this->floorPitch = 0;
    this->floorPitchAlt = 0;
    sPlayerFloorPitchShape = 0;
    return true;
}

/**
 * Performs the following tasks related to scene collision:
 *
 * This includes:
 * - Update BgCheckInfo, parameters adjusted due to various state flags
 * - Update floor type, floor property and floor sfx offset
 * - Update conveyor, reverb and light settings according to the current floor poly
 * - Handle exits and voids
 * - Update information relating to the "interact wall"
 * - Update information for ledge climbing
 * - Calculate floor poly angles
 */
void Player_ProcessSceneCollision(PlayState* play, Player* this) {
    u8 nextLedgeClimbType = PLAYER_LEDGE_CLIMB_NONE;
    CollisionPoly* floorPoly;
    f32 wallCheckRadius;
    f32 speedScale;
    f32 ceilingCheckHeight;
    u32 updBgCheckInfoFlags;
    s32 spAC = (Player_Action_35 == this->actionFunc) && (this->unk_397 == 4);

    sPlayerPrevFloorProperty = this->floorProperty;

    wallCheckRadius = this->ageProperties->wallCheckRadius;
    ceilingCheckHeight = this->ageProperties->ceilingCheckHeight;

    if (this->stateFlags1 & (PLAYER_STATE1_20000000 | PLAYER_STATE1_80000000)) {
        if ((!(this->stateFlags1 & PLAYER_STATE1_80) && !(this->stateFlags2 & PLAYER_STATE2_4000) &&
             (this->stateFlags1 & PLAYER_STATE1_80000000)) ||
            spAC) {
            updBgCheckInfoFlags = UPDBGCHECKINFO_FLAG_8 | UPDBGCHECKINFO_FLAG_10 | UPDBGCHECKINFO_FLAG_20;
            this->actor.bgCheckFlags &= ~BGCHECKFLAG_GROUND;
        } else if ((this->stateFlags1 & PLAYER_STATE1_1) &&
                   (play->roomCtx.curRoom.behaviorType1 != ROOM_BEHAVIOR_TYPE1_1) &&
                   ((this->unk_D68 - (s32)this->actor.world.pos.y) >= 100)) {
            updBgCheckInfoFlags =
                UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_8 | UPDBGCHECKINFO_FLAG_10 | UPDBGCHECKINFO_FLAG_20;
        } else if (!(this->stateFlags1 & PLAYER_STATE1_1) &&
                   ((Player_Action_36 == this->actionFunc) || (Player_Action_35 == this->actionFunc))) {
            updBgCheckInfoFlags =
                UPDBGCHECKINFO_FLAG_4 | UPDBGCHECKINFO_FLAG_8 | UPDBGCHECKINFO_FLAG_10 | UPDBGCHECKINFO_FLAG_20;
            this->actor.bgCheckFlags &= ~(BGCHECKFLAG_WALL | BGCHECKFLAG_PLAYER_WALL_INTERACT);
        } else {
            updBgCheckInfoFlags = UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_4 |
                                  UPDBGCHECKINFO_FLAG_8 | UPDBGCHECKINFO_FLAG_10 | UPDBGCHECKINFO_FLAG_20;
        }
    } else {
        if (Player_Action_93 == this->actionFunc) {
            updBgCheckInfoFlags = UPDBGCHECKINFO_FLAG_4 | UPDBGCHECKINFO_FLAG_10 | UPDBGCHECKINFO_FLAG_800;
        } else if ((this->stateFlags3 & (PLAYER_STATE3_1000 | PLAYER_STATE3_80000)) && (this->linearVelocity >= 8.0f)) {
            updBgCheckInfoFlags = UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_4 |
                                  UPDBGCHECKINFO_FLAG_10 | UPDBGCHECKINFO_FLAG_20 | UPDBGCHECKINFO_FLAG_100 |
                                  UPDBGCHECKINFO_FLAG_200;
        } else {
            updBgCheckInfoFlags = UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_4 |
                                  UPDBGCHECKINFO_FLAG_8 | UPDBGCHECKINFO_FLAG_10 | UPDBGCHECKINFO_FLAG_20;
        }
    }

    if (this->stateFlags3 & PLAYER_STATE3_1) {
        updBgCheckInfoFlags &= ~(UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_4);
    }

    if (updBgCheckInfoFlags & UPDBGCHECKINFO_FLAG_4) {
        this->stateFlags3 |= PLAYER_STATE3_10;
    }

    if (func_801242B4(this)) {
        updBgCheckInfoFlags &= ~(UPDBGCHECKINFO_FLAG_8 | UPDBGCHECKINFO_FLAG_10);
    }

    Actor_UpdateBgCheckInfo(play, &this->actor, 268 * 0.1f, wallCheckRadius, ceilingCheckHeight, updBgCheckInfoFlags);

    this->unk_AC0 -= (this->actor.world.pos.y - this->actor.prevPos.y) / this->actor.scale.y;
    this->unk_AC0 = CLAMP(this->unk_AC0, -1000.0f, 1000.0f);

    if (this->actor.bgCheckFlags & BGCHECKFLAG_CEILING) {
        this->actor.velocity.y = 0.0f;
    }

    sPlayerYDistToFloor = this->actor.world.pos.y - this->actor.floorHeight;
    sPlayerConveyorSpeedIndex = CONVEYOR_SPEED_DISABLED;
    floorPoly = this->actor.floorPoly;

    if ((floorPoly != NULL) && (updBgCheckInfoFlags & UPDBGCHECKINFO_FLAG_4)) {
        this->floorProperty = SurfaceType_GetFloorProperty(&play->colCtx, floorPoly, this->actor.floorBgId);

        if (this == GET_PLAYER(play)) {
            func_801A3CF4(SurfaceType_GetEcho(&play->colCtx, floorPoly, this->actor.floorBgId));

            if (this->actor.floorBgId == BGCHECK_SCENE) {
                Environment_ChangeLightSetting(
                    play, SurfaceType_GetLightSettingIndex(&play->colCtx, floorPoly, this->actor.floorBgId));
            } else {
                DynaPoly_SetPlayerAbove(&play->colCtx, this->actor.floorBgId);
            }
        }

        sPlayerConveyorSpeedIndex = SurfaceType_GetConveyorSpeed(&play->colCtx, floorPoly, this->actor.floorBgId);

        if (sPlayerConveyorSpeedIndex != CONVEYOR_SPEED_DISABLED) {
            sPlayerIsOnFloorConveyor = SurfaceType_IsFloorConveyor(&play->colCtx, floorPoly, this->actor.floorBgId);

            if ((!sPlayerIsOnFloorConveyor && (this->actor.depthInWater > 20.0f)) ||
                (sPlayerIsOnFloorConveyor && (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND))) {
                sPlayerConveyorYaw = CONVEYOR_DIRECTION_TO_BINANG(
                    SurfaceType_GetConveyorDirection(&play->colCtx, floorPoly, this->actor.floorBgId));
            } else {
                sPlayerConveyorSpeedIndex = CONVEYOR_SPEED_DISABLED;
            }
        }
    }

    this->actor.bgCheckFlags &= ~BGCHECKFLAG_PLAYER_WALL_INTERACT;

    if (this->actor.bgCheckFlags & BGCHECKFLAG_WALL) {
        static Vec3f sInteractWallCheckOffset = { 0.0f, 0.0f, 0.0f };
        CollisionPoly* wallPoly;
        s32 wallBgId;
        s16 yawDiff;
        s32 pad;

        sInteractWallCheckOffset.y = 178.0f * 0.1f;
        sInteractWallCheckOffset.z = this->ageProperties->wallCheckRadius + 10.0f;

        if (Player_PosVsWallLineTest(play, this, &sInteractWallCheckOffset, &wallPoly, &wallBgId,
                                     &sPlayerInteractWallCheckResult)) {
            this->actor.bgCheckFlags |= BGCHECKFLAG_PLAYER_WALL_INTERACT;

            if (this->actor.wallPoly != wallPoly) {
                this->actor.wallPoly = wallPoly;
                this->actor.wallBgId = wallBgId;
                this->actor.wallYaw = Math_Atan2S_XY(wallPoly->normal.z, wallPoly->normal.x);
            }
        }

        yawDiff = this->actor.shape.rot.y - BINANG_ADD(this->actor.wallYaw, 0x8000);
        sPlayerTouchedWallFlags = SurfaceType_GetWallFlags(&play->colCtx, this->actor.wallPoly, this->actor.wallBgId);
        sPlayerShapeYawToTouchedWall = ABS_ALT(yawDiff);

        yawDiff = BINANG_SUB(this->currentYaw, BINANG_ADD(this->actor.wallYaw, 0x8000));
        sPlayerWorldYawToTouchedWall = ABS_ALT(yawDiff);

        speedScale = sPlayerWorldYawToTouchedWall * 0.00008f;

        if (!(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) || (speedScale >= 1.0f)) {
            this->unk_B50 = R_RUN_SPEED_LIMIT / 100.0f;
        } else {
            this->unk_B50 = ceilingCheckHeight = (R_RUN_SPEED_LIMIT / 100.0f) * speedScale;
            if (this->unk_B50 < 0.1f) {
                this->unk_B50 = 0.1f;
            }
        }

        if ((this->actor.bgCheckFlags & BGCHECKFLAG_PLAYER_WALL_INTERACT) && (sPlayerShapeYawToTouchedWall < 0x3000)) {
            CollisionPoly* wallPoly = this->actor.wallPoly;

            if (ABS_ALT(wallPoly->normal.y) < 600) {
                f32 wallPolyNormalX = COLPOLY_GET_NORMAL(wallPoly->normal.x);
                f32 wallPolyNormalY = COLPOLY_GET_NORMAL(wallPoly->normal.y);
                f32 wallPolyNormalZ = COLPOLY_GET_NORMAL(wallPoly->normal.z);
                f32 ledgeCheckOffsetXZ;
                CollisionPoly* ledgeFloorPoly;
                CollisionPoly* poly;
                s32 bgId;
                Vec3f ledgeCheckPos;
                f32 ledgePosY;
                f32 ceillingPosY;
                s32 wallYawDiff;

                this->distToInteractWall = Math3D_UDistPlaneToPos(wallPolyNormalX, wallPolyNormalY, wallPolyNormalZ,
                                                                  wallPoly->dist, &this->actor.world.pos);

                ledgeCheckOffsetXZ = this->distToInteractWall + 10.0f;

                ledgeCheckPos.x = this->actor.world.pos.x - (ledgeCheckOffsetXZ * wallPolyNormalX);
                ledgeCheckPos.z = this->actor.world.pos.z - (ledgeCheckOffsetXZ * wallPolyNormalZ);
                ledgeCheckPos.y = this->actor.world.pos.y + this->ageProperties->unk_0C;

                ledgePosY =
                    BgCheck_EntityRaycastFloor5(&play->colCtx, &ledgeFloorPoly, &bgId, &this->actor, &ledgeCheckPos);
                this->yDistToLedge = ledgePosY - this->actor.world.pos.y;

                if ((this->yDistToLedge < 178.0f * 0.1f) ||
                    BgCheck_EntityCheckCeiling(&play->colCtx, &ceillingPosY, &this->actor.world.pos,
                                               (ledgePosY - this->actor.world.pos.y) + 20.0f, &poly, &bgId,
                                               &this->actor)) {
                    this->yDistToLedge = LEDGE_DIST_MAX;
                } else {
                    sInteractWallCheckOffset.y = (ledgePosY + 5.0f) - this->actor.world.pos.y;

                    if (Player_PosVsWallLineTest(play, this, &sInteractWallCheckOffset, &poly, &bgId,
                                                 &sPlayerInteractWallCheckResult) &&
                        (wallYawDiff = (s32)(this->actor.wallYaw - Math_Atan2S_XY(poly->normal.z, poly->normal.x)),
                         ABS_ALT(wallYawDiff) < 0x4000) &&
                        !SurfaceType_CheckWallFlag1(&play->colCtx, poly, bgId)) {
                        this->yDistToLedge = LEDGE_DIST_MAX;
                    } else if (!SurfaceType_CheckWallFlag0(&play->colCtx, wallPoly, this->actor.wallBgId)) {
                        if (this->ageProperties->unk_1C <= this->yDistToLedge) {
                            if (ABS_ALT(ledgeFloorPoly->normal.y) > 0x5DC0) {
                                if ((this->ageProperties->unk_14 <= this->yDistToLedge) || func_801242B4(this)) {
                                    nextLedgeClimbType = PLAYER_LEDGE_CLIMB_4;
                                } else if (this->ageProperties->unk_18 <= this->yDistToLedge) {
                                    nextLedgeClimbType = PLAYER_LEDGE_CLIMB_3;
                                } else {
                                    nextLedgeClimbType = PLAYER_LEDGE_CLIMB_2;
                                }
                            }
                        } else {
                            nextLedgeClimbType = PLAYER_LEDGE_CLIMB_1;
                        }
                    }
                }
            }
        }
    } else {
        this->unk_B50 = R_RUN_SPEED_LIMIT / 100.0f;
        this->yDistToLedge = 0.0f;
        this->ledgeClimbDelayTimer = 0;
    }

    if (nextLedgeClimbType == this->ledgeClimbType) {
        if (this->linearVelocity != 0.0f) {
            if (this->ledgeClimbDelayTimer < 100) {
                this->ledgeClimbDelayTimer++;
            }
        }
    } else {
        this->ledgeClimbType = nextLedgeClimbType;
        this->ledgeClimbDelayTimer = 0;
    }

    sPlayerFloorType = SurfaceType_GetFloorType(&play->colCtx, floorPoly, this->actor.floorBgId);

    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        f32 floorPolyNormalX;
        f32 floorPolyNormalY;
        f32 floorPolyNormalZ;
        f32 sin;
        s32 pad;
        f32 cos;

        sPlayerFloorEffect = SurfaceType_GetFloorEffect(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId);

        if (!func_808430E0(this)) {
            floorPolyNormalY = COLPOLY_GET_NORMAL(floorPoly->normal.y);

            if (this->actor.floorBgId != BGCHECK_SCENE) {
                DynaPoly_SetPlayerOnTop(&play->colCtx, this->actor.floorBgId);
            } else if (!(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND_TOUCH) && (this->actor.depthInWater <= 24.0f) &&
                       (sPlayerFloorEffect != FLOOR_EFFECT_1) &&
                       (sPlayerConveyorSpeedIndex == CONVEYOR_SPEED_DISABLED) && (floorPolyNormalY > 0.5f)) {
                if (CutsceneManager_GetCurrentCsId() != play->playerCsIds[PLAYER_CS_ID_SONG_WARP]) {
                    func_80841A50(play, this);
                }
            }

            floorPolyNormalX = COLPOLY_GET_NORMAL(floorPoly->normal.x);
            floorPolyNormalY = 1.0f / floorPolyNormalY;
            floorPolyNormalZ = COLPOLY_GET_NORMAL(floorPoly->normal.z);

            sin = Math_SinS(this->currentYaw);
            cos = Math_CosS(this->currentYaw);

            this->floorPitch =
                Math_Atan2S_XY(1.0f, (-(floorPolyNormalX * sin) - (floorPolyNormalZ * cos)) * floorPolyNormalY);
            this->floorPitchAlt =
                Math_Atan2S_XY(1.0f, (-(floorPolyNormalX * cos) - (floorPolyNormalZ * sin)) * floorPolyNormalY);

            sin = Math_SinS(this->actor.shape.rot.y);
            cos = Math_CosS(this->actor.shape.rot.y);

            sPlayerFloorPitchShape =
                Math_Atan2S_XY(1.0f, (-(floorPolyNormalX * sin) - (floorPolyNormalZ * cos)) * floorPolyNormalY);

            Player_HandleSlopes(play, this);
        }
    } else {
        func_808430E0(this);
        sPlayerFloorEffect = FLOOR_EFFECT_0;
    }

    if (floorPoly != NULL) {
        this->prevFloorSfxOffset = this->floorSfxOffset;

        if (spAC) {
            this->floorSfxOffset = NA_SE_PL_WALK_CONCRETE - SFX_FLAG;
            return;
        }

        if (this->actor.bgCheckFlags & BGCHECKFLAG_WATER) {
            if (this->actor.depthInWater < 50.0f) {
                if (this->actor.depthInWater < 20.0f) {
                    this->floorSfxOffset = (sPlayerFloorType == FLOOR_TYPE_13) ? NA_SE_PL_WALK_DIRT - SFX_FLAG
                                                                               : NA_SE_PL_WALK_WATER0 - SFX_FLAG;
                } else {
                    this->floorSfxOffset = (sPlayerFloorType == FLOOR_TYPE_13) ? NA_CODE_DIRT_DEEP - SFX_FLAG
                                                                               : NA_SE_PL_WALK_WATER1 - SFX_FLAG;
                }

                return;
            }
        }

        if (this->stateFlags2 & PLAYER_STATE2_FORCE_SAND_FLOOR_SOUND) {
            this->floorSfxOffset = NA_SE_PL_WALK_SAND - SFX_FLAG;
        } else if (COLPOLY_GET_NORMAL(floorPoly->normal.y) > 0.5f) {
            this->floorSfxOffset = SurfaceType_GetSfxOffset(&play->colCtx, floorPoly, this->actor.floorBgId);
        }
    }
}

void Player_UpdateCamAndSeqModes(PlayState* play, Player* this) {
    u8 seqMode;
    s32 pad[2];
    Camera* camera;
    s32 camMode;

    if (this == GET_PLAYER(play)) {
        seqMode = SEQ_MODE_DEFAULT;
        if (this->stateFlags1 & PLAYER_STATE1_100000) {
            seqMode = SEQ_MODE_STILL;
        } else if (this->csMode != PLAYER_CSMODE_NONE) {
            Camera_ChangeMode(Play_GetCamera(play, CAM_ID_MAIN), CAM_MODE_NORMAL);
        } else {
            camera = (this->actor.id == ACTOR_PLAYER) ? Play_GetCamera(play, CAM_ID_MAIN)
                                                      : Play_GetCamera(play, ((EnTest3*)this)->subCamId);
            if ((this->actor.parent != NULL) && (this->stateFlags3 & PLAYER_STATE3_80)) {
                camMode = CAM_MODE_HOOKSHOT;
                Camera_SetViewParam(camera, CAM_VIEW_TARGET, this->actor.parent);
            } else if (Player_Action_21 == this->actionFunc) {
                camMode = CAM_MODE_STILL;
            } else if (this->stateFlags3 & PLAYER_STATE3_8000) {
                if (this->stateFlags1 & PLAYER_STATE1_8000000) {
                    camMode = CAM_MODE_GORONDASH;
                } else {
                    camMode = CAM_MODE_FREEFALL;
                }
            } else if (this->stateFlags3 & PLAYER_STATE3_80000) {
                if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
                    camMode = CAM_MODE_GORONDASH;
                } else {
                    camMode = CAM_MODE_GORONJUMP;
                }
            } else if (this->stateFlags2 & PLAYER_STATE2_100) {
                camMode = CAM_MODE_PUSHPULL;
            } else if (this->lockOnActor != NULL) {
                if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_TALK_REQUESTED)) {
                    camMode = CAM_MODE_TALK;
                } else if (this->stateFlags1 & PLAYER_STATE1_10000) {
                    if (this->stateFlags1 & PLAYER_STATE1_2000000) {
                        camMode = CAM_MODE_FOLLOWBOOMERANG;
                    } else {
                        camMode = CAM_MODE_FOLLOWTARGET;
                    }
                } else {
                    camMode = CAM_MODE_BATTLE;
                }
                Camera_SetViewParam(camera, CAM_VIEW_TARGET, this->lockOnActor);
            } else if (this->stateFlags1 & PLAYER_STATE1_1000) {
                camMode = CAM_MODE_CHARGE;
            } else if (this->stateFlags3 & PLAYER_STATE3_100) {
                camMode = CAM_MODE_DEKUHIDE;
            } else if (this->stateFlags1 & PLAYER_STATE1_2000000) {
                camMode = CAM_MODE_FOLLOWBOOMERANG;
                Camera_SetViewParam(camera, CAM_VIEW_TARGET, this->boomerangActor);
            } else if (this->stateFlags1 & (PLAYER_STATE1_4 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000)) {
                if (func_80123434(this)) {
                    camMode = CAM_MODE_HANGZ;
                } else {
                    camMode = CAM_MODE_HANG;
                }
            } else if ((this->stateFlags3 & PLAYER_STATE3_2000) && (this->actor.velocity.y < 0.0f)) {
                if (this->stateFlags1 & (PLAYER_STATE1_20000 | PLAYER_STATE1_40000000)) {
                    camMode = CAM_MODE_DEKUFLYZ;
                } else {
                    camMode = CAM_MODE_DEKUFLY;
                }
            } else if (this->stateFlags1 & (PLAYER_STATE1_20000 | PLAYER_STATE1_40000000)) {
                if (func_800B7128(this) || func_8082EF20(this)) {
                    camMode = CAM_MODE_BOWARROWZ;
                } else if (this->stateFlags1 & PLAYER_STATE1_200000) {
                    camMode = CAM_MODE_CLIMBZ;
                } else {
                    camMode = CAM_MODE_TARGET;
                }
            } else if ((this->stateFlags1 & PLAYER_STATE1_400000) && (this->transformation != 0)) {
                camMode = CAM_MODE_STILL;
            } else if (this->stateFlags1 & PLAYER_STATE1_40000) {
                camMode = CAM_MODE_JUMP;
            } else if (this->stateFlags1 & PLAYER_STATE1_200000) {
                camMode = CAM_MODE_CLIMB;
            } else if (this->stateFlags1 & PLAYER_STATE1_80000) {
                camMode = CAM_MODE_FREEFALL;
            } else if (((Player_Action_84 == this->actionFunc) &&
                        (this->meleeWeaponAnimation >= PLAYER_MWA_FORWARD_SLASH_1H) &&
                        (this->meleeWeaponAnimation <= PLAYER_MWA_ZORA_PUNCH_KICK)) ||
                       (this->stateFlags3 & PLAYER_STATE3_8) ||
                       ((Player_Action_52 == this->actionFunc) && (this->actionVar2 == 0)) ||
                       (Player_Action_53 == this->actionFunc)) {
                camMode = CAM_MODE_STILL;
            } else {
                camMode = CAM_MODE_NORMAL;
                if ((this->linearVelocity == 0.0f) &&
                    (!(this->stateFlags1 & PLAYER_STATE1_800000) || (this->rideActor->speed == 0.0f))) {
                    seqMode = SEQ_MODE_STILL;
                }
            }

            Camera_ChangeMode(camera, camMode);
        }

        if (play->actorCtx.targetCtx.bgmEnemy != NULL) {
            seqMode = SEQ_MODE_ENEMY;
            Audio_UpdateEnemyBgmVolume(sqrtf(play->actorCtx.targetCtx.bgmEnemy->xyzDistToPlayerSq));
        }

        Audio_SetSequenceMode(seqMode);
    }
}

Vec3f D_8085D364 = { 0.0f, 0.5f, 0.0f };
Vec3f D_8085D370 = { 0.0f, 0.5f, 0.0f };
Color_RGBA8 D_8085D37C = { 255, 255, 100, 255 };
Color_RGBA8 D_8085D380 = { 255, 50, 0, 0 };

void func_808442D8(PlayState* play, Player* this) {
    f32 var_fa0;
    f32 temp_fv1;

    if (this->unk_B0C == 0.0f) {
        Player_UseItem(play, this, ITEM_NONE);
        return;
    }

    var_fa0 = 1.0f;
    if (DECR(this->unk_B28) == 0) {
        Inventory_ChangeAmmo(ITEM_DEKU_STICK, -1);
        this->unk_B28 = 1;
        this->unk_B0C = 0.0f;
        var_fa0 = 0.0f;
    } else if (this->unk_B28 >= 0xC9) {
        var_fa0 = (0xD2 - this->unk_B28) / 10.0f;
    } else if (this->unk_B28 < 0x14) {
        var_fa0 = this->unk_B28 / 20.0f;
        this->unk_B0C = var_fa0;
    }

    if (var_fa0 > 0.0f) {
        func_800B0EB0(play, &this->meleeWeaponInfo[0].tip, &D_8085D364, &D_8085D370, &D_8085D37C, &D_8085D380,
                      (var_fa0 * 200.0f), 0, 8);
        if (play->roomCtx.curRoom.enablePosLights || (MREG(93) != 0)) {
            temp_fv1 = (Rand_ZeroOne() * 30.0f) + 225.0f;
            Lights_PointSetColorAndRadius(&this->lightInfo, temp_fv1, temp_fv1 * 0.7f, 0, var_fa0 * 300.0f);
        }
    }
}

void func_808445C4(PlayState* play, Player* this) {
    this->shockTimer--;
    this->unk_B66 += this->shockTimer;
    if (this->unk_B66 > 20) {
        Vec3f pos;
        Vec3f* bodyPartsPos;
        s32 scale;
        s32 randIndex;

        this->unk_B66 -= 20;
        scale = this->shockTimer * 2;
        if (scale > 40) {
            scale = 40;
        }

        randIndex = Rand_ZeroFloat(PLAYER_BODYPART_MAX - 0.1f);
        bodyPartsPos = randIndex + this->bodyPartsPos;

        pos.x = (Rand_CenteredFloat(5.0f) + bodyPartsPos->x) - this->actor.world.pos.x;
        pos.y = (Rand_CenteredFloat(5.0f) + bodyPartsPos->y) - this->actor.world.pos.y;
        pos.z = (Rand_CenteredFloat(5.0f) + bodyPartsPos->z) - this->actor.world.pos.z;
        EffectSsFhgFlash_SpawnShock(play, &this->actor, &pos, scale, FHGFLASH_SHOCK_PLAYER);
        Actor_PlaySfx_FlaggedCentered1(&this->actor, NA_SE_PL_SPARK - SFX_FLAG);
    }
}

/**
 * Rumbles the controller when close to a secret.
 */
void Player_DetectSecrets(PlayState* play, Player* this) {
    f32 step = (SQ(200.0f) * 5.0f) - (this->closestSecretDistSq * 5.0f);

    if (step < 0.0f) {
        step = 0.0f;
    }

    this->secretRumbleCharge += step;
    if (this->secretRumbleCharge > SQ(2000.0f)) {
        this->secretRumbleCharge = 0.0f;
        Player_RequestRumble(play, this, 120, 20, 10, SQ(0));
    }
}

// Making a player csMode negative will behave as its positive counterpart
// except will disable setting the start position
#define DISABLE_PLAYER_CSMODE_START_POS(csMode) -(csMode)

s8 sPlayerCsModes[PLAYER_CUEID_MAX] = {
    /* PLAYER_CUEID_NONE */ PLAYER_CSMODE_NONE,
    /* PLAYER_CUEID_1 */ PLAYER_CSMODE_2,
    /* PLAYER_CUEID_2 */ PLAYER_CSMODE_2,
    /* PLAYER_CUEID_3 */ PLAYER_CSMODE_4,
    /* PLAYER_CUEID_4 */ PLAYER_CSMODE_3,
    /* PLAYER_CUEID_5 */ PLAYER_CSMODE_56,
    /* PLAYER_CUEID_6 */ PLAYER_CSMODE_8,
    /* PLAYER_CUEID_7 */ PLAYER_CSMODE_NONE,
    /* PLAYER_CUEID_8 */ PLAYER_CSMODE_NONE,
    /* PLAYER_CUEID_9 */ PLAYER_CSMODE_135,
    /* PLAYER_CUEID_10 */ PLAYER_CSMODE_21,
    /* PLAYER_CUEID_11 */ PLAYER_CSMODE_61,
    /* PLAYER_CUEID_12 */ PLAYER_CSMODE_62,
    /* PLAYER_CUEID_13 */ PLAYER_CSMODE_60,
    /* PLAYER_CUEID_14 */ PLAYER_CSMODE_63,
    /* PLAYER_CUEID_15 */ PLAYER_CSMODE_64,
    /* PLAYER_CUEID_16 */ PLAYER_CSMODE_65,
    /* PLAYER_CUEID_17 */ PLAYER_CSMODE_66,
    /* PLAYER_CUEID_18 */ PLAYER_CSMODE_70,
    /* PLAYER_CUEID_19 */ PLAYER_CSMODE_19,
    /* PLAYER_CUEID_20 */ PLAYER_CSMODE_71,
    /* PLAYER_CUEID_21 */ PLAYER_CSMODE_72,
    /* PLAYER_CUEID_22 */ PLAYER_CSMODE_67,
    /* PLAYER_CUEID_23 */ PLAYER_CSMODE_73,
    /* PLAYER_CUEID_24 */ PLAYER_CSMODE_74,
    /* PLAYER_CUEID_25 */ PLAYER_CSMODE_75,
    /* PLAYER_CUEID_26 */ PLAYER_CSMODE_68,
    /* PLAYER_CUEID_27 */ PLAYER_CSMODE_69,
    /* PLAYER_CUEID_28 */ PLAYER_CSMODE_76,
    /* PLAYER_CUEID_29 */ PLAYER_CSMODE_116,
    /* PLAYER_CUEID_30 */ PLAYER_CSMODE_NONE,
    /* PLAYER_CUEID_31 */ PLAYER_CSMODE_40,
    /* PLAYER_CUEID_32 */ PLAYER_CSMODE_NONE,
    /* PLAYER_CUEID_33 */ DISABLE_PLAYER_CSMODE_START_POS(PLAYER_CSMODE_52),
    /* PLAYER_CUEID_34 */ PLAYER_CSMODE_42,
    /* PLAYER_CUEID_35 */ PLAYER_CSMODE_43,
    /* PLAYER_CUEID_36 */ PLAYER_CSMODE_57,
    /* PLAYER_CUEID_37 */ PLAYER_CSMODE_81,
    /* PLAYER_CUEID_38 */ PLAYER_CSMODE_41,
    /* PLAYER_CUEID_39 */ PLAYER_CSMODE_53,
    /* PLAYER_CUEID_40 */ PLAYER_CSMODE_54,
    /* PLAYER_CUEID_41 */ PLAYER_CSMODE_44,
    /* PLAYER_CUEID_42 */ PLAYER_CSMODE_55,
    /* PLAYER_CUEID_43 */ PLAYER_CSMODE_45,
    /* PLAYER_CUEID_44 */ PLAYER_CSMODE_46,
    /* PLAYER_CUEID_45 */ PLAYER_CSMODE_47,
    /* PLAYER_CUEID_46 */ PLAYER_CSMODE_48,
    /* PLAYER_CUEID_47 */ PLAYER_CSMODE_49,
    /* PLAYER_CUEID_48 */ PLAYER_CSMODE_50,
    /* PLAYER_CUEID_49 */ PLAYER_CSMODE_51,
    /* PLAYER_CUEID_50 */ PLAYER_CSMODE_77,
    /* PLAYER_CUEID_51 */ PLAYER_CSMODE_78,
    /* PLAYER_CUEID_52 */ PLAYER_CSMODE_79,
    /* PLAYER_CUEID_53 */ PLAYER_CSMODE_80,
    /* PLAYER_CUEID_54 */ PLAYER_CSMODE_81,
    /* PLAYER_CUEID_55 */ PLAYER_CSMODE_82,
    /* PLAYER_CUEID_56 */ PLAYER_CSMODE_83,
    /* PLAYER_CUEID_57 */ PLAYER_CSMODE_84,
    /* PLAYER_CUEID_58 */ PLAYER_CSMODE_85,
    /* PLAYER_CUEID_59 */ PLAYER_CSMODE_86,
    /* PLAYER_CUEID_60 */ PLAYER_CSMODE_87,
    /* PLAYER_CUEID_61 */ PLAYER_CSMODE_88,
    /* PLAYER_CUEID_62 */ PLAYER_CSMODE_89,
    /* PLAYER_CUEID_63 */ PLAYER_CSMODE_90,
    /* PLAYER_CUEID_64 */ PLAYER_CSMODE_91,
    /* PLAYER_CUEID_65 */ PLAYER_CSMODE_92,
    /* PLAYER_CUEID_66 */ PLAYER_CSMODE_94,
    /* PLAYER_CUEID_67 */ PLAYER_CSMODE_95,
    /* PLAYER_CUEID_68 */ PLAYER_CSMODE_100,
    /* PLAYER_CUEID_69 */ PLAYER_CSMODE_101,
    /* PLAYER_CUEID_70 */ PLAYER_CSMODE_98,
    /* PLAYER_CUEID_71 */ PLAYER_CSMODE_99,
    /* PLAYER_CUEID_72 */ PLAYER_CSMODE_102,
    /* PLAYER_CUEID_73 */ PLAYER_CSMODE_103,
    /* PLAYER_CUEID_74 */ PLAYER_CSMODE_104,
    /* PLAYER_CUEID_75 */ PLAYER_CSMODE_112,
    /* PLAYER_CUEID_76 */ PLAYER_CSMODE_113,
    /* PLAYER_CUEID_77 */ PLAYER_CSMODE_117,
    /* PLAYER_CUEID_78 */ PLAYER_CSMODE_104,
    /* PLAYER_CUEID_79 */ PLAYER_CSMODE_104,
    /* PLAYER_CUEID_80 */ PLAYER_CSMODE_105,
    /* PLAYER_CUEID_81 */ PLAYER_CSMODE_106,
    /* PLAYER_CUEID_82 */ PLAYER_CSMODE_107,
    /* PLAYER_CUEID_83 */ PLAYER_CSMODE_108,
    /* PLAYER_CUEID_84 */ PLAYER_CSMODE_109,
    /* PLAYER_CUEID_85 */ PLAYER_CSMODE_110,
    /* PLAYER_CUEID_86 */ PLAYER_CSMODE_118,
    /* PLAYER_CUEID_87 */ PLAYER_CSMODE_119,
    /* PLAYER_CUEID_88 */ PLAYER_CSMODE_120,
    /* PLAYER_CUEID_89 */ PLAYER_CSMODE_114,
    /* PLAYER_CUEID_90 */ PLAYER_CSMODE_111,
    /* PLAYER_CUEID_91 */ PLAYER_CSMODE_122,
};

f32 D_8085D3E0[PLAYER_FORM_MAX] = {
    0.8f, // PLAYER_FORM_FIERCE_DEITY
    0.6f, // PLAYER_FORM_GORON
    0.8f, // PLAYER_FORM_ZORA
    1.5f, // PLAYER_FORM_DEKU
    1.0f, // PLAYER_FORM_HUMAN
};

void func_80844784(PlayState* play, Player* this) {
    f32 var_fv0;
    s16 var_a3;
    f32 temp_ft4;
    s32 temp_ft2;
    f32 temp_fv1_2;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 temp_fa0;
    f32 temp_fa1;
    s16 temp_v0;
    f32 temp_fv0_2;

    if ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && (sPlayerFloorType == FLOOR_TYPE_5) &&
        (this->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER)) {
        var_a3 = this->currentYaw;
        var_fv0 = this->linearVelocity;
        temp_v0 = this->actor.world.rot.y - var_a3;

        if ((ABS_ALT(temp_v0) > 0x6000) && (this->actor.speed != 0.0f)) {
            var_fv0 = 0.0f;
            var_a3 += 0x8000;
        }

        if (Math_StepToF(&this->actor.speed, var_fv0, 0.35f) && (var_fv0 == 0.0f)) {
            this->actor.world.rot.y = this->currentYaw;
        }

        if (this->linearVelocity != 0.0f) {
            temp_ft2 = (fabsf(this->linearVelocity) * 700.0f) - (fabsf(this->actor.speed) * 100.0f);
            temp_ft2 = CLAMP(temp_ft2, 0, 0x546);

            Math_ScaledStepToS(&this->actor.world.rot.y, var_a3, temp_ft2);
        }
        if ((this->linearVelocity == 0.0f) && (this->actor.speed != 0.0f)) {
            Audio_PlaySfx_AtPosWithSyncedFreqAndVolume(
                &this->actor.projectedPos, Player_GetFloorSfx(this, NA_SE_PL_SLIP_LEVEL - SFX_FLAG), this->actor.speed);
        }
    } else {
        this->actor.speed = this->linearVelocity;
        this->actor.world.rot.y = this->currentYaw;
    }

    Actor_UpdateVelocityWithGravity(&this->actor);
    D_80862B3C = 0.0f;
    if ((gSaveContext.save.saveInfo.playerData.health != 0) &&
        ((this->pushedSpeed != 0.0f) || (this->windSpeed != 0.0f) || (play->envCtx.windSpeed >= 50.0f)) &&
        (!Player_InCsMode(play)) &&
        !(this->stateFlags1 & (PLAYER_STATE1_4 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000 | PLAYER_STATE1_200000)) &&
        !(this->stateFlags3 & PLAYER_STATE3_100) && (Player_Action_33 != this->actionFunc) &&
        (this->actor.id == ACTOR_PLAYER)) {
        this->actor.velocity.x += this->pushedSpeed * Math_SinS(this->pushedYaw);
        this->actor.velocity.z += this->pushedSpeed * Math_CosS(this->pushedYaw);
        temp_fv1_2 = 10.0f - this->actor.velocity.y;
        if (temp_fv1_2 > 0.0f) {
            sp58 = D_8085D3E0[this->transformation];
            sp54 = this->windSpeed * sp58;
            sp50 = Math_SinS(this->windAngleX) * sp54;
            sp4C = Math_CosS(this->windAngleX) * sp54;
            sp48 = Math_SinS(this->windAngleY) * sp4C;
            sp44 = Math_CosS(this->windAngleY) * sp4C;

            if ((sp50 > 0.0f) && (this->transformation == PLAYER_FORM_DEKU) &&
                !(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
                if (Player_SetAction(play, this, Player_Action_94, 1)) {
                    this->stateFlags3 |= PLAYER_STATE3_2000 | PLAYER_STATE3_1000000;
                    func_8082E1F0(this, NA_SE_IT_DEKUNUTS_FLOWER_OPEN);
                    Audio_SetSfxTimerLerpInterval(4, 2);
                }

                this->actionVar2 = 0x270F;
                Math_Vec3f_Copy(this->unk_AF0, &this->actor.world.pos);
            }

            if (play->envCtx.windSpeed >= 50.0f) {
                temp_fa0 = play->envCtx.windDirection.x;
                temp_fa1 = play->envCtx.windDirection.y;
                temp_ft4 = play->envCtx.windDirection.z;

                temp_fv0_2 = sqrtf(SQ(temp_fa0) + SQ(temp_fa1) + SQ(temp_ft4));
                if (temp_fv0_2 != 0.0f) {
                    temp_fv0_2 = ((play->envCtx.windSpeed - 50.0f) * 0.1f * sp58) / temp_fv0_2;

                    sp48 -= temp_fa0 * temp_fv0_2;
                    sp50 -= temp_fa1 * temp_fv0_2;
                    sp44 -= temp_ft4 * temp_fv0_2;
                }
            }

            if (temp_fv1_2 < sp50) {
                temp_fv1_2 /= sp50;

                sp48 *= temp_fv1_2;
                sp50 *= temp_fv1_2;
                sp44 *= temp_fv1_2;
            }

            if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
                D_80862B3C = (sp44 * Math_CosS(this->currentYaw)) + (Math_SinS(this->currentYaw) * sp48);
                if (fabsf(D_80862B3C) > 4.0f) {
                    func_8083FBC4(play, this);
                }

                Audio_PlaySfx_AtPosWithSyncedFreqAndVolume(&this->actor.projectedPos,
                                                           Player_GetFloorSfx(this, NA_SE_PL_SLIP_LEVEL - SFX_FLAG),
                                                           fabsf(D_80862B3C));
            }

            this->actor.velocity.x += sp48;
            this->actor.velocity.z += sp44;
            this->actor.velocity.y += sp50;
        }
    }

    Actor_UpdatePos(&this->actor);
}

Color_RGBA8 D_8085D3F4 = { 100, 255, 255, 0 };
Color_RGBA8 D_8085D3F8 = { 0, 100, 100, 0 };

void func_80844D80(PlayState* play, Player* this) {
    Vec3f pos;
    Vec3f spA0;
    Vec3f velocity;
    Vec3f accel;
    Vec3f sp7C;
    s32 i;

    Math_Vec3f_Diff(&this->meleeWeaponInfo[0].tip, &this->meleeWeaponInfo[0].base, &sp7C);
    Math_Vec3f_SumScaled(&this->meleeWeaponInfo[0].base, &sp7C, 0.3f, &spA0);

    for (i = 0; i < 2; i++) {
        Math_Vec3f_SumScaled(&this->meleeWeaponInfo[0].base, &sp7C, Rand_ZeroOne(), &pos);
        Math_Vec3f_AddRand(&pos, 15.0f, &pos);
        Math_Vec3f_DistXYZAndStoreNormDiff(&spA0, &pos, 1.7f, &velocity);
        Math_Vec3f_ScaleAndStore(&velocity, 0.01f, &accel);
        EffectSsKirakira_SpawnDispersed(play, &pos, &velocity, &accel, &D_8085D3F4, &D_8085D3F8,
                                        Rand_S16Offset(-20, -120), 15);
    }
}

f32 D_8085D3FC[] = { 0.005f, 0.05f };

f32 sWaterConveyorSpeeds[CONVEYOR_SPEED_MAX - 1] = {
    2.0f,  // CONVEYOR_SPEED_SLOW
    4.0f,  // CONVEYOR_SPEED_MEDIUM
    11.0f, // CONVEYOR_SPEED_FAST
};
f32 sFloorConveyorSpeeds[CONVEYOR_SPEED_MAX - 1] = {
    0.5f, // CONVEYOR_SPEED_SLOW
    1.0f, // CONVEYOR_SPEED_MEDIUM
    3.0f, // CONVEYOR_SPEED_FAST
};

void Player_UpdateCommon(Player* this, PlayState* play, Input* input) {
    f32 temp_fv0;
    f32 temp_fv1;

    sPlayerControlInput = input;
    if (this->unk_D6A < 0) {
        this->unk_D6A++;
        if (this->unk_D6A == 0) {
            this->unk_D6A = 1;
            Audio_PlaySfx(NA_SE_OC_REVENGE);
        }
    }

    Math_Vec3f_Copy(&this->actor.prevPos, &this->actor.home.pos);

    temp_fv1 = fabsf(this->linearVelocity) * (fabsf(Math_SinS(this->floorPitch) * 800.0f) + 100.0f);

    Math_StepToF(&this->unk_AC0, 0.0f, CLAMP_MIN(temp_fv1, 300.0f));

    if (this->unk_D57 != 0) {
        this->unk_D57--;
    }

    if (this->unk_B5E != 0) {
        this->unk_B5E--;
    }

    if (this->unk_D6B != 0) {
        this->unk_D6B--;
    }

    if (this->invincibilityTimer < 0) {
        this->invincibilityTimer++;
    } else if (this->invincibilityTimer > 0) {
        this->invincibilityTimer--;
    }

    if (this->unk_B64 != 0) {
        this->unk_B64--;
    }

    if (this->blastMaskTimer != 0) {
        this->blastMaskTimer--;
    }

    if (gSaveContext.jinxTimer != 0) {
        gSaveContext.jinxTimer--;
    }

    func_80122C20(play, &this->unk_3D0);
    if ((this->transformation == PLAYER_FORM_FIERCE_DEITY) && func_8082FBE8(this)) {
        func_80844D80(play, this);
    }
    if (this->transformation == PLAYER_FORM_ZORA) {
        s32 var_v0 = (this->stateFlags1 & PLAYER_STATE1_8000000) ? 1 : 0;

        Math_StepToF(&this->unk_B10[0], var_v0, D_8085D3FC[var_v0]);
    }
    func_80832888(this, play);
    if (play->roomCtx.curRoom.enablePosLights) {
        Lights_PointSetColorAndRadius(&this->lightInfo, 255, 255, 255, 60);
    } else {
        this->lightInfo.params.point.radius = -1;
    }

    if ((this->heldItemAction == PLAYER_IA_DEKU_STICK) && (this->unk_B28 != 0)) {
        func_808442D8(play, this);
    } else if (this->heldItemAction == PLAYER_IA_FISHING_ROD) {
        if (this->unk_B28 < 0) {
            this->unk_B28++;
        }
    }

    if (this->shockTimer != 0) {
        func_808445C4(play, this);
    }
    if (this->isBurning) {
        func_808341F4(play, this);
    }

    if (this->stateFlags2 & PLAYER_STATE2_8000) {
        if (!(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
            Player_StopHorizontalMovement(this);
            Actor_MoveWithGravity(&this->actor);
        }
        Player_ProcessSceneCollision(play, this);
    } else {
        f32 temp_fa0;
        f32 var_fv1_2;
        s32 var_v1;
        s32 pad;

        if (this->currentBoots != this->prevBoots) {
            if (this->currentBoots == PLAYER_BOOTS_ZORA_UNDERWATER) {
                if (this->stateFlags1 & PLAYER_STATE1_8000000) {
                    func_8082DC64(play, this);
                    if (this->ageProperties->unk_2C < this->actor.depthInWater) {
                        this->stateFlags2 |= PLAYER_STATE2_400;
                    }
                }
            } else if ((this->stateFlags1 & PLAYER_STATE1_8000000) &&
                       ((this->prevBoots == PLAYER_BOOTS_ZORA_UNDERWATER) ||
                        (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND))) {
                func_8083B930(play, this);
                this->stateFlags2 &= ~PLAYER_STATE2_400;
                if (Player_Action_54 == this->actionFunc) {
                    this->actionVar2 = 20;
                }
            }
            this->prevBoots = this->currentBoots;
        }
        if ((this->actor.parent == NULL) && (this->stateFlags1 & PLAYER_STATE1_800000)) {
            this->actor.parent = this->rideActor;
            func_80837BD0(play, this);
            this->actionVar2 = -1;
            Player_AnimationPlayOnce(play, this, &gPlayerAnim_link_uma_wait_1);
            func_8082E920(play, this, ANIM_FLAG_1 | ANIM_FLAG_UPDATE_Y | ANIM_FLAG_8 | ANIM_FLAG_NOMOVE | ANIM_FLAG_80);
        }

        if (this->unk_ADC == 0) {
            this->unk_ADD = 0;
        } else if (this->unk_ADC < 0) {
            this->unk_ADC++;
        } else {
            this->unk_ADC--;
        }

        if (!(this->stateFlags3 & PLAYER_STATE3_2000)) {
            Math_ScaledStepToS(&this->unk_AAA, 0, 0x190);
        }

        if ((this->transformation >= PLAYER_FORM_GORON) && (this->transformation <= PLAYER_FORM_DEKU)) {
            func_800BBB74(&this->blinkInfo, 20, 80, 3);
        } else {
            func_800BBAC0(&this->blinkInfo, 20, 80, 6);
        }

        this->actor.shape.face = ((play->gameplayFrames & 0x20) ? 0 : 3) + this->blinkInfo.eyeTexIndex;

        if (this->currentMask == PLAYER_MASK_BUNNY) {
            Player_UpdateBunnyEars(this);
        }

        if (func_800B7118(this)) {
            func_808484F0(this);
        }

        if ((play->unk_18844 == 0) && !(this->skelAnime.moveFlags & ANIM_FLAG_80)) {
            if (!(this->stateFlags1 & PLAYER_STATE1_2) && (this->actor.parent == NULL)) {
                func_80844784(play, this);
            }
            Player_ProcessSceneCollision(play, this);
        } else {
            sPlayerFloorType = FLOOR_TYPE_0;
            this->floorProperty = FLOOR_PROPERTY_0;
            if (this->stateFlags1 & PLAYER_STATE1_800000) {
                this->actor.floorPoly = this->rideActor->floorPoly;
                this->actor.floorBgId = this->rideActor->floorBgId;
            }
            sPlayerConveyorSpeedIndex = CONVEYOR_SPEED_DISABLED;
            this->pushedSpeed = 0.0f;
        }

        Player_HandleExitsAndVoids(play, this, this->actor.floorPoly, this->actor.floorBgId);
        if (sPlayerConveyorSpeedIndex != CONVEYOR_SPEED_DISABLED) {
            f32 conveyorSpeed;
            s32 pad2;

            sPlayerConveyorSpeedIndex--;
            if (!sPlayerIsOnFloorConveyor) {
                conveyorSpeed = sWaterConveyorSpeeds[sPlayerConveyorSpeedIndex];
                if (!(this->stateFlags1 & PLAYER_STATE1_8000000)) {
                    conveyorSpeed /= 4.0f;
                }
            } else {
                conveyorSpeed = sFloorConveyorSpeeds[sPlayerConveyorSpeedIndex];
            }

            Math_StepToF(&this->pushedSpeed, conveyorSpeed, conveyorSpeed * 0.1f);
            Math_ScaledStepToS(&this->pushedYaw, sPlayerConveyorYaw,
                               ((this->stateFlags1 & PLAYER_STATE1_8000000) ? 400.0f : 800.0f) * conveyorSpeed);
        } else if (this->pushedSpeed != 0.0f) {
            Math_StepToF(&this->pushedSpeed, 0.0f, (this->stateFlags1 & PLAYER_STATE1_8000000) ? 0.5f : 2.0f);
        }
        if (!(this->stateFlags1 & (PLAYER_STATE1_80 | PLAYER_STATE1_20000000)) &&
            !(this->stateFlags3 & PLAYER_STATE3_80) && (Player_Action_80 != this->actionFunc)) {
            func_8083BB4C(play, this);
            if (!Play_InCsMode(play)) {
                if ((this->actor.id == ACTOR_PLAYER) && !(this->stateFlags1 & PLAYER_STATE1_80000000) &&
                    (gSaveContext.save.saveInfo.playerData.health == 0) &&
                    func_808323C0(this, play->playerCsIds[PLAYER_CS_ID_DEATH])) {
                    if (this->stateFlags3 & PLAYER_STATE3_1000000) {
                        func_808355D8(play, this, &gPlayerAnim_pn_kakkufinish);
                    } else if (this->stateFlags1 &
                               (PLAYER_STATE1_4 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000 | PLAYER_STATE1_200000)) {
                        func_8082DD2C(play, this);
                        func_80833AA0(this, play);
                    } else if ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) ||
                               (this->stateFlags1 & PLAYER_STATE1_8000000)) {
                        func_80831F34(play, this,
                                      func_801242B4(this)
                                          ? &gPlayerAnim_link_swimer_swim_down
                                          : ((this->shockTimer != 0) ? &gPlayerAnim_link_normal_electric_shock_end
                                                                     : &gPlayerAnim_link_derth_rebirth));
                    }
                } else {
                    if ((this->actor.parent == NULL) &&
                        (func_8082DA90(play) || (this->unk_D6B != 0) || !func_80834600(this, play))) {
                        func_8083827C(this, play);
                    } else {
                        this->fallStartHeight = this->actor.world.pos.y;
                    }

                    Player_DetectSecrets(play, this);
                }
            }
        } else if (!(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && (Player_Action_35 == this->actionFunc) &&
                   (this->unk_397 == 4)) {
            this->actor.world.pos.y = this->actor.prevPos.y;
        }

        if (play->csCtx.state != CS_STATE_IDLE) {
            if ((this->csMode != PLAYER_CSMODE_5) && !(this->stateFlags1 & PLAYER_STATE1_800000)) {
                if (!(this->stateFlags2 & PLAYER_STATE2_80) && (this->actor.id == ACTOR_PLAYER)) {
                    if ((play->csCtx.playerCue != NULL) &&
                        (sPlayerCsModes[play->csCtx.playerCue->id] != PLAYER_CSMODE_NONE)) {
                        func_800B7298(play, NULL, PLAYER_CSMODE_5);
                        Player_StopHorizontalMovement(this);
                    } else if (((u32)this->csMode == PLAYER_CSMODE_NONE) &&
                               !(this->stateFlags2 & (PLAYER_STATE2_400 | PLAYER_STATE2_8000000)) &&
                               (play->csCtx.state != CS_STATE_STOP)) {
                        func_800B7298(play, NULL, PLAYER_CSMODE_20);
                        Player_StopHorizontalMovement(this);
                    }
                }
            }
        }

        if ((u32)this->csMode != PLAYER_CSMODE_NONE) {
            if ((this->csMode != PLAYER_CSMODE_END) ||
                !(this->stateFlags1 & (PLAYER_STATE1_4 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000 |
                                       PLAYER_STATE1_200000 | PLAYER_STATE1_4000000))) {
                if (Player_Action_97 != this->actionFunc) {
                    this->unk_AA5 = PLAYER_UNKAA5_4;
                    if (this->csMode == PLAYER_CSMODE_5) {
                        func_808387A0(play, this);
                        func_8082DAD4(this);
                    }
                }
            } else if (Player_Action_97 != this->actionFunc) {
                Player_CsAction_End(play, this, NULL);
            }
        } else {
            this->prevCsMode = PLAYER_CSMODE_NONE;
        }

        func_8083BF54(play, this);
        Lights_PointSetPosition(&this->lightInfo, this->actor.world.pos.x, this->actor.world.pos.y + 40.0f,
                                this->actor.world.pos.z);

        if (((this->lockOnActor == NULL) || (this->lockOnActor == this->talkActor) ||
             (this->lockOnActor->hintId == TATL_HINT_ID_NONE)) &&
            (this->tatlTextId == 0)) {
            this->stateFlags2 &= ~(PLAYER_STATE2_2 | PLAYER_STATE2_200000);
        }

        this->stateFlags1 &= ~(PLAYER_STATE1_10 | PLAYER_STATE1_1000 | PLAYER_STATE1_400000);
        this->stateFlags2 &=
            ~(PLAYER_STATE2_1 | PLAYER_STATE2_4 | PLAYER_STATE2_8 | PLAYER_STATE2_20 | PLAYER_STATE2_40 |
              PLAYER_STATE2_100 | PLAYER_STATE2_FORCE_SAND_FLOOR_SOUND | PLAYER_STATE2_1000 | PLAYER_STATE2_4000 |
              PLAYER_STATE2_10000 | PLAYER_STATE2_400000 | PLAYER_STATE2_4000000);
        this->stateFlags3 &= ~(PLAYER_STATE3_10 | PLAYER_STATE3_40 | PLAYER_STATE3_100 | PLAYER_STATE3_800 |
                               PLAYER_STATE3_1000 | PLAYER_STATE3_100000 | PLAYER_STATE3_2000000 |
                               PLAYER_STATE3_4000000 | PLAYER_STATE3_8000000 | PLAYER_STATE3_10000000);
        func_808425B4(this);
        Player_ProcessControlStick(play, this);

        D_8085C3E4 = (this->stateFlags1 & PLAYER_STATE1_8000000) ? 0.5f : 1.0f;
        D_8085C3E8 = 1.0f / D_8085C3E4;

        sPlayerUseHeldItem = sPlayerHeldItemButtonIsHeldDown = false;

        var_v1 = Play_InCsMode(play);
        D_80862B2C = this->currentMask;
        if (!(this->stateFlags3 & PLAYER_STATE3_4)) {
            this->actionFunc(this, play);
        }

        if (!var_v1) {
            Player_SetDoAction(play, this);
        }

        Player_UpdateCamAndSeqModes(play, this);

        if (this->skelAnime.moveFlags & ANIM_FLAG_8) {
            AnimationContext_SetMoveActor(play, &this->actor, &this->skelAnime,
                                          (this->skelAnime.moveFlags & ANIM_FLAG_4) ? 1.0f
                                                                                    : this->ageProperties->unk_08);
        }

        func_80832578(this, play);
        if (this->actor.flags & ACTOR_FLAG_TALK_REQUESTED) {
            this->talkActorDistance = 0.0f;
        } else {
            this->talkActor = NULL;
            this->exchangeItemAction = PLAYER_IA_NONE;
            this->talkActorDistance = FLT_MAX;
        }
        if (!(this->actor.flags & ACTOR_FLAG_20000000) && (this->unk_AA5 != PLAYER_UNKAA5_5)) {
            this->unk_A90 = NULL;
            this->unk_A94 = FLT_MAX;
        }
        if (!(this->stateFlags1 & PLAYER_STATE1_800)) {
            this->interactRangeActor = NULL;
            this->getItemDirection = 0x6000;
        }
        if (this->actor.parent == NULL) {
            this->rideActor = NULL;
        }

        this->tatlTextId = 0;
        this->unk_B2B = -1;
        this->closestSecretDistSq = FLT_MAX;
        this->doorType = PLAYER_DOORTYPE_NONE;
        this->unk_B75 = 0;
        this->unk_A78 = NULL;

        Math_StepToF(&this->windSpeed, 0.0f, 0.5f);
        if ((this->unk_B62 != 0) ||
            ((gSaveContext.magicState == MAGIC_STATE_IDLE) && (gSaveContext.save.saveInfo.playerData.magic != 0) &&
             (this->stateFlags1 & PLAYER_STATE1_10))) {
            func_8082F1AC(play, this);
        }

        temp_fv0 = this->actor.world.pos.y - this->actor.prevPos.y;
        var_fv1_2 =
            temp_fv0 +
            ((this->bodyPartsPos[PLAYER_BODYPART_LEFT_FOOT].y + this->bodyPartsPos[PLAYER_BODYPART_RIGHT_FOOT].y) *
             0.5f);
        temp_fv0 += this->bodyPartsPos[PLAYER_BODYPART_HEAD].y + 10.0f;

        if (this->cylinder.info.toucher.dmgFlags == 0x80000) {
            this->cylinder.dim.height = 80;
            var_fv1_2 = ((temp_fv0 + var_fv1_2) * 0.5f) - 40.0f;
        } else {
            this->cylinder.dim.height = temp_fv0 - var_fv1_2;

            if (this->cylinder.dim.height < 0) {
                temp_fa0 = temp_fv0;
                temp_fv0 = var_fv1_2;
                var_fv1_2 = temp_fa0;
                this->cylinder.dim.height = -this->cylinder.dim.height;
            }
        }

        this->cylinder.dim.yShift = var_fv1_2 - this->actor.world.pos.y;

        if (this->unk_B62 != 0) {
            this->shieldCylinder.base.acFlags = AC_NONE;
            this->shieldCylinder.info.toucher.dmgFlags = 0x80000;
            this->shieldCylinder.info.toucherFlags = TOUCH_ON;
            this->shieldCylinder.info.bumperFlags = BUMP_NONE;
            this->shieldCylinder.dim.height = 80;
            this->shieldCylinder.dim.radius = 50;
            this->shieldCylinder.dim.yShift = ((temp_fv0 + var_fv1_2) * 0.5f - 40.0f) - this->actor.world.pos.y;

            Collider_UpdateCylinder(&this->actor, &this->shieldCylinder);
            CollisionCheck_SetAT(play, &play->colChkCtx, &this->shieldCylinder.base);
        } else if (this->stateFlags1 & PLAYER_STATE1_400000) {
            if ((this->transformation == PLAYER_FORM_GORON) || (this->transformation == PLAYER_FORM_DEKU)) {
                this->shieldCylinder.base.acFlags = AC_ON | AC_HARD | AC_TYPE_ENEMY;
                this->shieldCylinder.info.toucher.dmgFlags = 0x100000;
                this->shieldCylinder.info.toucherFlags = TOUCH_NONE;
                this->shieldCylinder.info.bumperFlags = BUMP_ON;

                if (this->transformation == PLAYER_FORM_GORON) {
                    this->shieldCylinder.dim.height = 35;
                } else {
                    this->shieldCylinder.dim.height = 30;
                }

                if (this->transformation == PLAYER_FORM_GORON) {
                    this->shieldCylinder.dim.radius = 30;
                } else {
                    this->shieldCylinder.dim.radius = 20;
                }

                this->shieldCylinder.dim.yShift = 0;
                Collider_UpdateCylinder(&this->actor, &this->shieldCylinder);
                CollisionCheck_SetAC(play, &play->colChkCtx, &this->shieldCylinder.base);
                this->cylinder.dim.yShift = 0;
                this->cylinder.dim.height = this->shieldCylinder.dim.height;
            } else {
                this->cylinder.dim.height = this->cylinder.dim.height * 0.8f;
            }
        }

        Collider_UpdateCylinder(&this->actor, &this->cylinder);
        if (!(this->stateFlags2 & PLAYER_STATE2_4000)) {
            if (!(this->stateFlags1 & (PLAYER_STATE1_4 | PLAYER_STATE1_80 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000 |
                                       PLAYER_STATE1_800000)) &&
                !(this->stateFlags3 & PLAYER_STATE3_10000000)) {
                if ((Player_Action_93 != this->actionFunc) && (Player_Action_73 != this->actionFunc) &&
                    (this->actor.draw != NULL)) {
                    if ((this->actor.id != ACTOR_PLAYER) && (this->csMode == PLAYER_CSMODE_110)) {
                        this->cylinder.dim.radius = 8;
                    }
                    CollisionCheck_SetOC(play, &play->colChkCtx, &this->cylinder.base);
                }
            }
            if (!(this->stateFlags1 & (PLAYER_STATE1_80 | PLAYER_STATE1_4000000)) && (this->invincibilityTimer <= 0)) {
                if ((Player_Action_93 != this->actionFunc) &&
                    ((Player_Action_96 != this->actionFunc) || (this->actionVar1 != 1))) {
                    if (this->cylinder.base.atFlags != AT_NONE) {
                        CollisionCheck_SetAT(play, &play->colChkCtx, &this->cylinder.base);
                    }
                    CollisionCheck_SetAC(play, &play->colChkCtx, &this->cylinder.base);
                }
            }
        }

        AnimationContext_SetNextQueue(play);
    }

    func_801229FC(this);
    Math_Vec3f_Copy(&this->actor.home.pos, &this->actor.world.pos);

    if ((this->stateFlags1 & (PLAYER_STATE1_80 | PLAYER_STATE1_10000000 | PLAYER_STATE1_20000000)) ||
        (this != GET_PLAYER(play))) {
        this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    } else {
        this->actor.colChkInfo.mass = sPlayerMass[this->transformation];
    }

    this->stateFlags3 &= ~(PLAYER_STATE3_4 | PLAYER_STATE3_400);
    Collider_ResetCylinderAC(play, &this->cylinder.base);
    Collider_ResetCylinderAC(play, &this->shieldCylinder.base);
    Collider_ResetCylinderAT(play, &this->shieldCylinder.base);
    Collider_ResetQuadAT(play, &this->meleeWeaponQuads[0].base);
    Collider_ResetQuadAT(play, &this->meleeWeaponQuads[1].base);
    Collider_ResetQuadAC(play, &this->shieldQuad.base);

    if (!(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) || (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND_TOUCH) ||
        (this->actor.floorBgId != BGCHECK_SCENE)) {
        this->unk_AC0 = 0.0f;
    }
    this->actor.shape.yOffset = this->unk_ABC + this->unk_AC0;
}

Vec3f D_8085D41C = { 0.0f, 0.0f, -30.0f };

void Player_Update(Actor* thisx, PlayState* play) {
    static Vec3f sDogSpawnPos;
    Player* this = (Player*)thisx;
    s32 dogParams;
    s32 pad;
    Input input;
    s32 pad2;

    this->stateFlags3 &= ~PLAYER_STATE3_10;

    // This block is a leftover dog-following mechanic from OoT
    if (gSaveContext.dogParams < 0) {
        if (Object_GetSlot(&play->objectCtx, OBJECT_DOG) < 0) {
            gSaveContext.dogParams = 0;
        } else {
            Actor* dog;

            gSaveContext.dogParams &= (u16)~0x8000;
            Player_TranslateAndRotateY(this, &this->actor.world.pos, &D_8085D41C, &sDogSpawnPos);

            dogParams = gSaveContext.dogParams;

            dog = Actor_Spawn(&play->actorCtx, play, ACTOR_EN_DG, sDogSpawnPos.x, sDogSpawnPos.y, sDogSpawnPos.z, 0,
                              this->actor.shape.rot.y, 0, dogParams | 0x8000);
            if (dog != NULL) {
                dog->room = -1;
            }
        }
    }

    if ((this->interactRangeActor != NULL) && (this->interactRangeActor->update == NULL)) {
        this->interactRangeActor = NULL;
    }

    if ((this->heldActor != NULL) && (this->heldActor->update == NULL)) {
        Player_DetachHeldActor(play, this);
    }

    if ((play->actorCtx.unk268 != 0) && (this == GET_PLAYER(play))) {
        input = play->actorCtx.unk_26C;
    } else if ((this->csMode == PLAYER_CSMODE_5) || (this->stateFlags1 & (PLAYER_STATE1_20 | PLAYER_STATE1_20000000)) ||
               (this != GET_PLAYER(play)) || func_8082DA90(play) ||
               (gSaveContext.save.saveInfo.playerData.health == 0)) {
        bzero(&input, sizeof(Input));
        this->fallStartHeight = this->actor.world.pos.y;
    } else {
        input = *CONTROLLER1(&play->state);
        if (this->unk_B5E != 0) {
            input.cur.button &= ~(BTN_CUP | BTN_B | BTN_A);
            input.press.button &= ~(BTN_CUP | BTN_B | BTN_A);
        }
    }

    Player_UpdateCommon(this, play, &input);
    play->actorCtx.unk268 = 0;
    bzero(&play->actorCtx.unk_26C, sizeof(Input));

    MREG(52) = this->actor.world.pos.x;
    MREG(53) = this->actor.world.pos.y;
    MREG(54) = this->actor.world.pos.z;
    MREG(55) = this->actor.world.rot.y;
}

void Player_DrawGameplay(PlayState* play, Player* this, s32 lod, Gfx* cullDList,
                         OverrideLimbDrawFlex overrideLimbDraw) {
    OPEN_DISPS(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x0C, cullDList);
    gSPSegment(POLY_XLU_DISP++, 0x0C, cullDList);

    Player_DrawImpl(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, lod,
                    this->transformation, 0, this->actor.shape.face, overrideLimbDraw, Player_PostLimbDrawGameplay,
                    &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_80846460(Player* this) {
    Vec3f* pos;
    Vec3f* bodyPartPosPtr;
    s32 i;

    this->actor.focus.pos.x = this->actor.world.pos.x;
    this->actor.focus.pos.z = this->actor.world.pos.z;
    this->actor.focus.pos.y = this->actor.world.pos.y + 24.0f;

    pos = &this->actor.world.pos;
    bodyPartPosPtr = this->bodyPartsPos;
    for (i = 0; i < PLAYER_BODYPART_MAX; i++) {
        Math_Vec3f_Copy(bodyPartPosPtr, pos);
        bodyPartPosPtr++;
    }

    this->bodyPartsPos[PLAYER_BODYPART_HEAD].y = this->actor.world.pos.y + 24.0f;
    this->bodyPartsPos[PLAYER_BODYPART_WAIST].y = this->actor.world.pos.y + 60.0f;
    Math_Vec3f_Copy(&this->actor.shape.feetPos[0], pos);
    Math_Vec3f_Copy(&this->actor.shape.feetPos[1], pos);
}

struct_80124618 D_8085D428[] = {
    { 0, { 0, 0, 0 } },       { 1, { 80, 170, 80 } },   { 3, { 100, 80, 100 } },
    { 7, { 100, 100, 100 } }, { 8, { 100, 100, 100 } },
};
struct_80124618 D_8085D450[] = {
    { 0, { 0, 0, 0 } },       { 1, { 80, 170, 80 } },   { 3, { 100, 80, 100 } },
    { 7, { 100, 100, 100 } }, { 8, { 100, 100, 100 } },
};
struct_80124618 D_8085D478[] = {
    { 0, { 0, 0, 0 } },
    { 8, { 0, 0, 0 } },
};
struct_80124618 D_8085D488[] = {
    { 0, { 100, 100, 100 } }, { 1, { 100, 60, 100 } },  { 3, { 100, 140, 100 } },
    { 7, { 100, 80, 100 } },  { 9, { 100, 100, 100 } },
};
struct_80124618 D_8085D4B0[] = {
    { 0, { 100, 100, 100 } }, { 1, { 100, 70, 100 } },  { 3, { 100, 120, 100 } },
    { 6, { 100, 80, 100 } },  { 8, { 100, 100, 100 } }, { 9, { 100, 100, 100 } },
};
struct_80124618 D_8085D4E0[] = {
    { 0, { 0, 0, 0 } },       { 1, { 0, 0, 0 } },    { 3, { 100, 130, 100 } },
    { 5, { 130, 130, 130 } }, { 7, { 80, 90, 80 } }, { 9, { 100, 100, 100 } },
};
struct_80124618 D_8085D510[] = {
    { 0, { 0, 50, 0 } },
    { 1, { 0, 50, 0 } },
};
struct_80124618 D_8085D520[] = {
    { 0, { 100, 120, 100 } },
    { 1, { 100, 120, 100 } },
};
struct_80124618 D_8085D530[] = {
    { 0, { 160, 120, 160 } },
    { 1, { 160, 120, 160 } },
};
struct_80124618 D_8085D540[] = {
    { 0, { 0, 0, 0 } },
    { 2, { 100, 100, 100 } },
};

struct_80124618* D_8085D550[3] = {
    D_8085D488,
    D_8085D4B0,
    D_8085D4E0,
};
struct_80124618* D_8085D55C[3] = {
    D_8085D428,
    D_8085D450,
    D_8085D478,
};
struct_80124618* D_8085D568[3] = {
    D_8085D510,
    D_8085D520,
    D_8085D530,
};

Gfx* D_8085D574[] = {
    object_link_nuts_DL_009C48,
    object_link_nuts_DL_009AB8,
    object_link_nuts_DL_009DB8,
};

Color_RGB8 D_8085D580 = { 255, 255, 255 };
Color_RGB8 D_8085D584 = { 80, 80, 200 };

void Player_Draw(Actor* thisx, PlayState* play) {
    Player* this = THIS;
    f32 one = 1.0f;
    s32 spEC = false;

    Math_Vec3f_Copy(&this->unk_D6C, &this->bodyPartsPos[PLAYER_BODYPART_WAIST]);
    if (this->stateFlags3 & (PLAYER_STATE3_100 | PLAYER_STATE3_40000)) {
        struct_80124618** spE8 = D_8085D550;
        struct_80124618** spE4;
        f32 spE0;
        Gfx** spDC;
        s32 i;

        OPEN_DISPS(play->state.gfxCtx);

        Matrix_Push();
        func_8012C268(&play->state);
        spEC = true;
        if (this->stateFlags3 & PLAYER_STATE3_40000) {
            Matrix_SetTranslateRotateYXZ(this->unk_AF0[0].x, this->unk_AF0[0].y, this->unk_AF0[0].z, &gZeroVec3s);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            spE8 = D_8085D568;
            spE0 = 0.0f;
        } else {
            Matrix_Translate(0.0f, -this->unk_ABC, 0.0f, MTXMODE_APPLY);
            spE0 = this->actionVar2 - 6;
            if (spE0 < 0.0f) {
                spE8 = D_8085D55C;
                spE0 = this->unk_B86[0];
            }
        }

        spE4 = spE8;
        spDC = D_8085D574;

        for (i = 0; i < 3; i++, spE4++, spDC++) {
            Matrix_Push();
            func_80124618(*spE4, spE0, &this->unk_AF0[1]);
            Matrix_Scale(this->unk_AF0[1].x, this->unk_AF0[1].y, this->unk_AF0[1].z, MTXMODE_APPLY);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, *spDC);

            Matrix_Pop();
        }
        Matrix_Pop();

        CLOSE_DISPS(play->state.gfxCtx);
    }

    if (!(this->stateFlags2 & PLAYER_STATE2_20000000) && (this->unk_ABC > -3900.0f)) {
        OPEN_DISPS(play->state.gfxCtx);

        if (!spEC) {
            func_8012C268(&play->state);
        }

        Gfx_SetupDL25_Xlu(play->state.gfxCtx);

        func_800B8050(&this->actor, play, 0);
        func_800B8118(&this->actor, play, 0);
        func_80122868(play, this);

        if (this->stateFlags3 & PLAYER_STATE3_1000) {
            Color_RGB8 spBC;
            f32 spB8 = this->unk_ABC + 1.0f;
            f32 spB4 = 1.0f - (this->unk_ABC * 0.5f);

            func_80846460(this);
            Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y + (1200.0f * this->actor.scale.y * spB8),
                             this->actor.world.pos.z, MTXMODE_NEW);

            if (this->unk_B86[0] != 0) {
                Matrix_RotateYS(this->unk_B28, MTXMODE_APPLY);
                Matrix_RotateXS(this->unk_B86[0], MTXMODE_APPLY);
                Matrix_RotateYS(-this->unk_B28, MTXMODE_APPLY);
            }

            Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
            Matrix_RotateZS(this->actor.shape.rot.z, MTXMODE_APPLY);

            Matrix_Scale(this->actor.scale.x * spB4 * 1.15f, this->actor.scale.y * spB8 * 1.15f,
                         CLAMP_MIN(spB8, spB4) * this->actor.scale.z * 1.15f, MTXMODE_APPLY);
            Matrix_RotateXS(this->actor.shape.rot.x, MTXMODE_APPLY);
            Scene_SetRenderModeXlu(play, 0, 1);
            Color_RGB8_Lerp(&D_8085D580, &D_8085D584, this->unk_B10[0], &spBC);

            gDPSetEnvColor(POLY_OPA_DISP++, spBC.r, spBC.g, spBC.b, 255);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, gLinkGoronCurledDL);

            if (this->unk_B86[1] != 0) {
                if (this->unk_B86[1] < 3) {
                    func_80124618(D_8085D540, this->unk_B86[1], this->unk_AF0);
                    Matrix_Scale(this->unk_AF0[0].x, this->unk_AF0[0].y, this->unk_AF0[0].z, MTXMODE_APPLY);
                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                }

                gSPDisplayList(POLY_OPA_DISP++, object_link_goron_DL_00C540);
            }

            func_80122BA4(play, &this->unk_3D0, 1, 255);
            func_80122BA4(play, &this->unk_3D0, 2, 255);

            if (this->unk_B86[1] < 3) {
                if (this->actionVar1 >= 5) {
                    f32 var_fa1;
                    u8 sp9B;

                    var_fa1 = (this->actionVar1 - 4) * 0.02f;

                    if (this->unk_B86[1] != 0) {
                        sp9B = (-this->unk_B86[1] * 0x55) + 0xFF;
                    } else {
                        sp9B = (200.0f * var_fa1);
                    }

                    if (this->unk_B86[1] != 0) {
                        var_fa1 = 0.65f;
                    } else {
                        var_fa1 *= one;
                    }

                    Matrix_Scale(1.0f, var_fa1, var_fa1, MTXMODE_APPLY);

                    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    AnimatedMat_DrawXlu(play, Lib_SegmentedToVirtual(&object_link_goron_Matanimheader_013138));
                    gDPSetEnvColor(POLY_XLU_DISP++, 155, 0, 0, sp9B);
                    gSPDisplayList(POLY_XLU_DISP++, object_link_goron_DL_0127B0);
                    AnimatedMat_DrawXlu(play, Lib_SegmentedToVirtual(&object_link_goron_Matanimheader_014684));
                    gSPDisplayList(POLY_XLU_DISP++, object_link_goron_DL_0134D0);
                }
            }
        } else if ((this->transformation == PLAYER_FORM_GORON) && (this->stateFlags1 & PLAYER_STATE1_400000)) {
            func_80846460(this);
            SkelAnime_DrawFlexOpa(play, this->unk_2C8.skeleton, this->unk_2C8.jointTable, this->unk_2C8.dListCount,
                                  NULL, NULL, NULL);
        } else {
            OverrideLimbDrawFlex sp84 = Player_OverrideLimbDrawGameplayDefault;
            s32 lod = ((this->csMode != PLAYER_CSMODE_NONE) || (this->actor.projectedPos.z < 320.0f)) ? 0 : 1;
            Vec3f sp74;

            //! FAKE
            if (this->transformation == PLAYER_FORM_FIERCE_DEITY) {}

            if (this->stateFlags1 & PLAYER_STATE1_100000) {
                SkinMatrix_Vec3fMtxFMultXYZ(&play->viewProjectionMtxF, &this->actor.focus.pos, &sp74);
                if (sp74.z < -4.0f) {
                    sp84 = Player_OverrideLimbDrawGameplayFirstPerson;
                }
            }

            if (this->stateFlags2 & PLAYER_STATE2_4000000) {
                s16 temp_s0_2 = play->gameplayFrames * 600;
                s16 sp70 = (play->gameplayFrames * 1000) & 0xFFFF;

                Matrix_Push();

                this->actor.scale.y = -this->actor.scale.y;
                Matrix_SetTranslateRotateYXZ(this->actor.world.pos.x,
                                             this->actor.world.pos.y + (2.0f * this->actor.depthInWater) +
                                                 (this->unk_ABC * this->actor.scale.y),
                                             this->actor.world.pos.z, &this->actor.shape.rot);
                Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
                Matrix_RotateXS(temp_s0_2, MTXMODE_APPLY);
                Matrix_RotateYS(sp70, MTXMODE_APPLY);
                Matrix_Scale(1.1f, 0.95f, 1.05f, MTXMODE_APPLY);
                Matrix_RotateYS(-sp70, MTXMODE_APPLY);
                Matrix_RotateXS(-temp_s0_2, MTXMODE_APPLY);
                Player_DrawGameplay(play, this, lod, gCullFrontDList, sp84);
                this->actor.scale.y = -this->actor.scale.y;

                Matrix_Pop();
            }

            gSPClearGeometryMode(POLY_OPA_DISP++, G_CULL_BOTH);

            gSPClearGeometryMode(POLY_XLU_DISP++, G_CULL_BOTH);

            if ((this->transformation == PLAYER_FORM_ZORA) && (this->unk_B62 != 0) &&
                !(this->stateFlags3 & PLAYER_STATE3_8000)) {
                Matrix_Push();
                Matrix_RotateXS(-0x4000, MTXMODE_APPLY);
                Matrix_Translate(0.0f, 0.0f, -1800.0f, MTXMODE_APPLY);
                Player_DrawZoraShield(play, this);
                Matrix_Pop();
            }

            Player_DrawGameplay(play, this, lod, gCullBackDList, sp84);
        }

        func_801229A0(play, this);
        if (this->stateFlags2 & PLAYER_STATE2_4000) {
            f32 temp_fa0 = this->unk_B48;

            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, -(s32)play->gameplayFrames & 0x7F, 0x20, 0x20, 1, 0,
                                        ((s32)play->gameplayFrames * -2) & 0x7F, 0x20, 0x20));

            Matrix_Scale(temp_fa0, temp_fa0, temp_fa0, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            gDPSetEnvColor(POLY_XLU_DISP++, 0, 50, 100, 255);

            gSPDisplayList(POLY_XLU_DISP++, gEffIceFragment3DL);
        }

        if (this->getItemDrawIdPlusOne > GID_NONE + 1) {
            Player_DrawGetItem(play, this);
        }

        func_80122D44(play, &this->unk_3D0);

        CLOSE_DISPS(play->state.gfxCtx);
    }

    play->actorCtx.flags &= ~ACTORCTX_FLAG_3;
}

void Player_Destroy(Actor* thisx, PlayState* play) {
    Player* this = (Player*)thisx;

    Effect_Destroy(play, this->meleeWeaponEffectIndex[0]);
    Effect_Destroy(play, this->meleeWeaponEffectIndex[1]);
    Effect_Destroy(play, this->meleeWeaponEffectIndex[2]);
    LightContext_RemoveLight(play, &play->lightCtx, this->lightNode);
    Collider_DestroyCylinder(play, &this->cylinder);
    Collider_DestroyCylinder(play, &this->shieldCylinder);
    Collider_DestroyQuad(play, &this->meleeWeaponQuads[0]);
    Collider_DestroyQuad(play, &this->meleeWeaponQuads[1]);
    Collider_DestroyQuad(play, &this->shieldQuad);
    ZeldaArena_Free(this->giObjectSegment);
    ZeldaArena_Free(this->maskObjectSegment);
    Magic_Reset(play);
    func_80831454(this);
}

s32 func_80847190(PlayState* play, Player* this, s32 arg2) {
    s32 pad;
    s16 var_s0;

    if (!func_800B7128(this) && !func_8082EF20(this) && !arg2) {
        var_s0 = sPlayerControlInput->rel.stick_y * 0xF0;
        Math_SmoothStepToS(&this->actor.focus.rot.x, var_s0, 0xE, 0xFA0, 0x1E);

        var_s0 = sPlayerControlInput->rel.stick_x * -0x10;
        var_s0 = CLAMP(var_s0, -0xBB8, 0xBB8);
        this->actor.focus.rot.y += var_s0;
    } else {
        s16 temp3;

        temp3 = ((sPlayerControlInput->rel.stick_y >= 0) ? 1 : -1) *
                (s32)((1.0f - Math_CosS(sPlayerControlInput->rel.stick_y * 0xC8)) * 1500.0f);
        this->actor.focus.rot.x += temp3;

        if (this->stateFlags1 & PLAYER_STATE1_800000) {
            this->actor.focus.rot.x = CLAMP(this->actor.focus.rot.x, -0x1F40, 0xFA0);
        } else {
            this->actor.focus.rot.x = CLAMP(this->actor.focus.rot.x, -0x36B0, 0x36B0);
        }

        var_s0 = this->actor.focus.rot.y - this->actor.shape.rot.y;
        temp3 = ((sPlayerControlInput->rel.stick_x >= 0) ? 1 : -1) *
                (s32)((1.0f - Math_CosS(sPlayerControlInput->rel.stick_x * 0xC8)) * -1500.0f);
        var_s0 += temp3;

        this->actor.focus.rot.y = CLAMP(var_s0, -0x4AAA, 0x4AAA) + this->actor.shape.rot.y;
    }

    this->unk_AA6 |= 2;

    return func_80832754(this, (play->unk_1887C != 0) || func_800B7128(this) || func_8082EF20(this));
}

void func_8084748C(Player* this, f32* speed, f32 speedTarget, s16 yawTarget) {
    f32 incrStep = this->skelAnime.curFrame - 10.0f;
    f32 maxSpeed = (R_RUN_SPEED_LIMIT / 100.0f) * 0.8f;

    if (*speed > maxSpeed) {
        *speed = maxSpeed;
    }

    if ((0.0f < incrStep) && (incrStep < 16.0f)) {
        incrStep = fabsf(incrStep) * 0.5f;
    } else {
        speedTarget = 0.0f;
        incrStep = 0.0f;
    }

    Math_AsymStepToF(speed, speedTarget * 0.8f, incrStep, (fabsf(*speed) * 0.02f) + 0.05f);
    Math_ScaledStepToS(&this->currentYaw, yawTarget, 1600); // 1 ESS turn, also one frame of first-person rotation
}

void func_808475B4(Player* this) {
    f32 sp4;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 var_ft4 = -5.0f;
    f32 var_ft5 = this->ageProperties->unk_28;
    f32 var_ft5_4;

    temp_fv0 = this->actor.depthInWater - var_ft5;
    if (this->actor.velocity.y < 0.0f) {
        var_ft5 += 1.0f;
    }

    if (this->actor.depthInWater < var_ft5) {
        temp_fv0 = CLAMP(temp_fv0, -0.4f, -0.1f);
        sp4 = temp_fv0 - ((this->actor.velocity.y <= 0.0f) ? 0.0f : this->actor.velocity.y * 0.5f);
    } else {
        if (!(this->stateFlags1 & PLAYER_STATE1_80) && (this->currentBoots >= PLAYER_BOOTS_ZORA_UNDERWATER) &&
            (this->actor.velocity.y >= -5.0f)) {
            sp4 = -0.3f;
        } else if ((this->transformation == PLAYER_FORM_DEKU) && (this->actor.velocity.y < 0.0f)) {
            var_ft4 = 0.0f;
            sp4 = -this->actor.velocity.y;
        } else {
            var_ft4 = 2.0f;
            var_ft5_4 = CLAMP(temp_fv0, 0.1f, 0.4f);
            sp4 = ((this->actor.velocity.y >= 0.0f) ? 0.0f : this->actor.velocity.y * -0.3f) + var_ft5_4;
        }

        if (this->actor.depthInWater > 100.0f) {
            this->stateFlags2 |= PLAYER_STATE2_400;
        }
    }

    this->actor.velocity.y += sp4;
    if (((this->actor.velocity.y - var_ft4) * sp4) > 0.0f) {
        this->actor.velocity.y = var_ft4;
    }
    this->actor.gravity = 0.0f;
}

void func_808477D0(PlayState* play, Player* this, Input* input, f32 arg3) {
    f32 var_fv0;

    if ((input != NULL) && CHECK_BTN_ANY(input->press.button, BTN_B | BTN_A)) {
        var_fv0 = 1.0f;
    } else {
        var_fv0 = 0.5f;
    }

    var_fv0 = var_fv0 * arg3;
    var_fv0 = CLAMP(var_fv0, 1.0f, 2.5f);
    this->skelAnime.playSpeed = var_fv0;

    PlayerAnimation_Update(play, &this->skelAnime);
}

s32 func_80847880(PlayState* play, Player* this) {
    if (play->unk_1887C != 0) {
        if (play->sceneId == SCENE_20SICHITAI) {
            Player_SetAction(play, this, Player_Action_80, 0);
            play->unk_1887C = 0;
            this->csMode = PLAYER_CSMODE_NONE;
            return true;
        }

        func_8082DE50(play, this);
        Player_SetAction(play, this, Player_Action_81, 0);
        if (!func_800B7118(this) || Player_IsHoldingHookshot(this)) {
            Player_UseItem(play, this, ITEM_BOW);
        }
        Player_AnimationPlayOnce(play, this, func_8082ED20(this));
        this->csMode = PLAYER_CSMODE_NONE;
        this->stateFlags1 |= PLAYER_STATE1_100000;
        Player_StopHorizontalMovement(this);
        func_80836D8C(this);

        return true;
    }
    return false;
}

s32 func_80847994(PlayState* play, Player* this) {
    if (this->stateFlags3 & PLAYER_STATE3_20) {
        this->stateFlags3 &= ~PLAYER_STATE3_20;
        this->itemAction = PLAYER_IA_OCARINA;
        this->unk_AA5 = PLAYER_UNKAA5_5;
        Player_ActionChange_13(this, play);
        return true;
    }
    return false;
}

void func_808479F4(PlayState* play, Player* this, f32 arg2) {
    if (this->actor.wallBgId != BGCHECK_SCENE) {
        DynaPolyActor* actor = DynaPoly_GetActor(&play->colCtx, this->actor.wallBgId);

        if (actor != NULL) {
            func_800B72F8(actor, arg2, this->actor.world.rot.y);
        }
    }
}

void func_80847A50(Player* this) {
    Player_PlaySfx(this, ((this->actionVar1 != 0) ? NA_SE_PL_WALK_METAL1 : NA_SE_PL_WALK_LADDER) +
                             this->ageProperties->surfaceSfxIdOffset);
}

Vec3f D_8085D588[] = {
    { 30.0f, 0.0f, 0.0f },
    { -30.0f, 0.0f, 0.0f },
};
Vec3f D_8085D5A0[] = {
    { 60.0f, 20.0f, 0.0f },
    { -60.0f, 20.0f, 0.0f },
};
Vec3f D_8085D5B8[] = {
    { 60.0f, -20.0f, 0.0f },
    { -60.0f, -20.0f, 0.0f },
};
Vec3f D_8085D5D0 = { 0.0f, 0.0f, -30.0f };

// related to mounting/unmounting the horse
s32 func_80847A94(PlayState* play, Player* this, s32 arg2, f32* arg3) {
    Actor* rideActor = this->rideActor;
    f32 sp60 = rideActor->world.pos.y + 20.0f;
    f32 sp5C = rideActor->world.pos.y - 20.0f;
    Vec3f sp50;
    Vec3f sp44;
    CollisionPoly* wallPoly;
    CollisionPoly* floorPoly;
    s32 wallBgId;
    s32 floorBgId;

    *arg3 = func_80835CD8(play, this, &D_8085D588[arg2], &sp50, &floorPoly, &floorBgId);

    if ((sp5C < *arg3) && (*arg3 < sp60)) {
        if (!Player_PosVsWallLineTest(play, this, &D_8085D5A0[arg2], &wallPoly, &wallBgId, &sp44)) {
            if (!Player_PosVsWallLineTest(play, this, &D_8085D5B8[arg2], &wallPoly, &wallBgId, &sp44)) {
                this->actor.floorPoly = floorPoly;
                //! @note: no poly is assigned to `wallBgId` when `Player_PosVsWallLineTest` fails.
                //! Therefore, the default value `BGCHECK_SCENE` is assigned.
                this->actor.floorBgId = wallBgId;
                this->floorSfxOffset = SurfaceType_GetSfxOffset(&play->colCtx, floorPoly, floorBgId);
                return true;
            }
        }
    }
    return false;
}

s32 func_80847BF0(Player* this, PlayState* play) {
    EnHorse* rideActor = (EnHorse*)this->rideActor;
    s32 var_a2;
    f32 sp34;

    if (this->actionVar2 < 0) {
        this->actionVar2 = 0x63;
    } else {
        var_a2 = (this->mountSide < 0) ? 0 : 1;

        if (!func_80847A94(play, this, var_a2, &sp34)) {
            var_a2 ^= 1;
            if (!func_80847A94(play, this, var_a2, &sp34)) {
                return false;
            }

            this->mountSide = -this->mountSide;
        }

        if (play->csCtx.state == CS_STATE_IDLE) {
            if (!func_8082DA90(play)) {
                if (EN_HORSE_CHECK_1(rideActor) || EN_HORSE_CHECK_4(rideActor)) {
                    this->stateFlags2 |= PLAYER_STATE2_400000;

                    if (EN_HORSE_CHECK_1(rideActor) ||
                        (EN_HORSE_CHECK_4(rideActor) && CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_A))) {
                        rideActor->actor.child = NULL;

                        Player_SetAction_PreserveMoveFlags(play, this, Player_Action_53, 0);
                        this->unk_B48 = sp34 - rideActor->actor.world.pos.y;

                        Player_AnimationPlayOnce(play, this,
                                                 (this->mountSide < 0) ? &gPlayerAnim_link_uma_left_down
                                                                       : &gPlayerAnim_link_uma_right_down);

                        return true;
                    }
                }
            }
        }
    }

    return false;
}

// Used in 2 horse-related functions
void func_80847E2C(Player* this, f32 arg1, f32 minFrame) {
    f32 addend;
    f32 dir;

    if ((this->unk_B48 != 0.0f) && (minFrame <= this->skelAnime.curFrame)) {
        if (arg1 < fabsf(this->unk_B48)) {
            dir = (this->unk_B48 >= 0.0f) ? 1 : -1;
            addend = dir * arg1;
        } else {
            addend = this->unk_B48;
        }
        this->actor.world.pos.y += addend;
        this->unk_B48 -= addend;
    }
}

s32 func_80847ED4(Player* this) {
    return (this->interactRangeActor != NULL) && (this->interactRangeActor->id == ACTOR_EN_ZOG) &&
           CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_A);
}

void func_80847F1C(Player* this) {
    s32 pad;
    f32 yPos;
    s16 yaw;
    Actor* interactRangeActor = this->interactRangeActor;

    if (func_80847ED4(this)) {
        yPos = this->actor.world.pos.y;
        yaw = this->currentYaw - interactRangeActor->shape.rot.y;
        Lib_Vec3f_TranslateAndRotateY(&interactRangeActor->world.pos, interactRangeActor->shape.rot.y, &D_8085D5D0,
                                      &this->actor.world.pos);
        this->actor.world.pos.y = yPos;
        this->actor.shape.rot.y = interactRangeActor->shape.rot.y;

        interactRangeActor->speed = Math_CosS(ABS_ALT(yaw)) * this->linearVelocity * 0.5f;
        if (interactRangeActor->speed < 0.0f) {
            interactRangeActor->speed = 0.0f;
        }
        func_8083133C(this);
    }
}

AnimSfxEntry D_8085D5DC[] = {
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 0, NA_SE_PL_SWIM, STOP),
};

void func_80847FF8(Player* this, f32* arg1, f32 arg2, s16 arg3) {
    func_8084748C(this, arg1, arg2, arg3);
    Player_PlayAnimSfx(this, D_8085D5DC);
    func_80847F1C(this);
}

void func_80848048(PlayState* play, Player* this) {
    Player_SetAction(play, this, Player_Action_58, 0);
    func_8082E634(play, this, &gPlayerAnim_link_swimer_swim);
}

s32 func_80848094(PlayState* play, Player* this, f32* arg2, s16* arg3) {
    PlayerAnimationHeader* anim;
    s16 temp_v0 = this->currentYaw - *arg3;
    s32 temp_v0_2;

    if (ABS_ALT(temp_v0) > 0x6000) {
        anim = &gPlayerAnim_link_swimer_swim_wait;
        if (Math_StepToF(&this->linearVelocity, 0.0f, 1.0f)) {
            this->currentYaw = *arg3;
        } else {
            *arg2 = 0.0f;
            *arg3 = this->currentYaw;
        }
    } else {
        temp_v0_2 = func_8083E514(this, arg2, arg3, play);
        if (temp_v0_2 > 0) {
            anim = &gPlayerAnim_link_swimer_swim;
        } else if (temp_v0_2 < 0) {
            anim = &gPlayerAnim_link_swimer_back_swim;
        } else {
            s16 diff = BINANG_SUB(this->actor.shape.rot.y, *arg3);

            if (diff > 0) {
                anim = &gPlayerAnim_link_swimer_Rside_swim;
            } else {
                anim = &gPlayerAnim_link_swimer_Lside_swim;
            }
        }
    }

    if (anim != this->skelAnime.animation) {
        func_8082E634(play, this, anim);
        return true;
    }
    return false;
}

void func_808481CC(PlayState* play, Player* this, f32 arg2) {
    f32 speedTarget;
    s16 yawTarget;

    Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);
    func_8084748C(this, &this->linearVelocity, speedTarget / 2.0f, yawTarget);
    func_8084748C(this, &this->actor.velocity.y, arg2, this->currentYaw);
}

void func_80848250(PlayState* play, Player* this) {
    this->getItemDrawIdPlusOne = GID_NONE + 1;
    this->stateFlags1 &= ~(PLAYER_STATE1_400 | PLAYER_STATE1_800);
    this->getItemId = GI_NONE;
    func_800E0238(Play_GetCamera(play, CAM_ID_MAIN));
}

void func_80848294(PlayState* play, Player* this) {
    func_80848250(play, this);
    func_8082DC28(this);
    func_80839E74(this, play);
    this->currentYaw = this->actor.shape.rot.y;
}

// Player_GetItem?
s32 func_808482E0(PlayState* play, Player* this) {
    if (this->getItemId == GI_NONE) {
        return true;
    }

    if (this->actionVar1 == 0) {
        GetItemEntry* giEntry = &sGetItemTable[this->getItemId - 1];

        this->actionVar1 = 1;
        Message_StartTextbox(play, giEntry->textId, &this->actor);
        Item_Give(play, giEntry->itemId);

        if ((this->getItemId >= GI_MASK_DEKU) && (this->getItemId <= GI_MASK_KAFEIS_MASK)) {
            Audio_PlayFanfare(NA_BGM_GET_NEW_MASK);
        } else if (((this->getItemId >= GI_RUPEE_GREEN) && (this->getItemId <= GI_RUPEE_10)) ||
                   (this->getItemId == GI_RECOVERY_HEART)) {
            Audio_PlaySfx(NA_SE_SY_GET_BOXITEM);
        } else {
            s32 seqId;

            if ((this->getItemId == GI_HEART_CONTAINER) ||
                ((this->getItemId == GI_HEART_PIECE) && EQ_MAX_QUEST_HEART_PIECE_COUNT)) {
                seqId = NA_BGM_GET_HEART | 0x900;
            } else {
                s32 var_v1;

                if ((this->getItemId == GI_HEART_PIECE) ||
                    ((this->getItemId >= GI_RUPEE_PURPLE) && (this->getItemId <= GI_RUPEE_HUGE))) {
                    var_v1 = NA_BGM_GET_SMALL_ITEM;
                } else {
                    var_v1 = NA_BGM_GET_ITEM | 0x900;
                }
                seqId = var_v1;
            }

            Audio_PlayFanfare(seqId);
        }
    } else if (Message_GetState(&play->msgCtx) == TEXT_STATE_CLOSING) {
        if (this->getItemId == GI_OCARINA_OF_TIME) {
            // zelda teaching song of time cs?
            play->nextEntrance = ENTRANCE(CUTSCENE, 0);
            gSaveContext.nextCutsceneIndex = 0xFFF2;
            play->transitionTrigger = TRANS_TRIGGER_START;
            play->transitionType = TRANS_TYPE_FADE_WHITE;
            gSaveContext.nextTransitionType = TRANS_TYPE_FADE_WHITE;
            this->stateFlags1 &= ~PLAYER_STATE1_20000000;
            func_8085B28C(play, NULL, PLAYER_CSMODE_WAIT);
        }
        this->getItemId = GI_NONE;
    }

    return false;
}

AnimSfxEntry D_8085D5E0[] = {
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 60, NA_SE_IT_MASTER_SWORD_SWING, STOP),
};

void func_808484CC(Player* this) {
    Player_PlayAnimSfx(this, D_8085D5E0);
}

void func_808484F0(Player* this) {
    this->unk_B08 += this->unk_B0C;
    this->unk_B0C -= this->unk_B08 * 5.0f;
    this->unk_B0C *= 0.3f;

    if (fabsf(this->unk_B0C) < 0.00001f) {
        this->unk_B0C = 0.0f;
        if (fabsf(this->unk_B08) < 0.00001f) {
            this->unk_B08 = 0.0f;
        }
    }
}

s32 Player_ActionChange_7(Player* this, PlayState* play) {
    if (!func_8083A6C0(play, this)) {
        if (func_808396B8(play, this)) {
            PlayerMeleeWeaponAnimation meleeWeaponAnim = func_808335F4(this);

            func_80833864(play, this, meleeWeaponAnim);
            if ((meleeWeaponAnim >= PLAYER_MWA_SPIN_ATTACK_1H) ||
                ((this->transformation == PLAYER_FORM_FIERCE_DEITY) && func_8082FBE8(this))) {
                this->stateFlags2 |= PLAYER_STATE2_20000;
                func_808332A0(play, this, 0, meleeWeaponAnim < PLAYER_MWA_SPIN_ATTACK_1H);
            }
        } else {
            return false;
        }
    }
    return true;
}

// elegy of emptiness
void func_80848640(PlayState* play, Player* this) {
    EnTorch2* torch2;
    Actor* effChange;

    torch2 = play->actorCtx.elegyShells[this->transformation];
    if (torch2 != NULL) {
        Math_Vec3f_Copy(&torch2->actor.home.pos, &this->actor.world.pos);
        torch2->actor.home.rot.y = this->actor.shape.rot.y;
        torch2->state = 0;
        torch2->framesUntilNextState = 20;
    } else {
        torch2 = (EnTorch2*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_TORCH2, this->actor.world.pos.x,
                                        this->actor.world.pos.y, this->actor.world.pos.z, 0, this->actor.shape.rot.y, 0,
                                        this->transformation);
    }

    if (torch2 != NULL) {
        play->actorCtx.elegyShells[this->transformation] = torch2;
        Play_SetupRespawnPoint(&play->state, this->transformation + 3, PLAYER_PARAMS(0xFF, PLAYER_INITMODE_B));
    }

    effChange = Actor_Spawn(&play->actorCtx, play, ACTOR_EFF_CHANGE, this->actor.world.pos.x, this->actor.world.pos.y,
                            this->actor.world.pos.z, 0, this->actor.shape.rot.y, 0,
                            (GET_PLAYER_FORM << 3) | this->transformation);
    if (effChange != NULL) {
        //! @bug: This function should only pass Player*: it uses *(this + 0x153), which is meant to be
        //! player->currentMask, but in this case is garbage in the skelAnime
        Player_PlaySfx((Player*)effChange, NA_SE_PL_TRANSFORM);
    }
}

s32 Player_UpperAction_0(Player* this, PlayState* play) {
    if (func_80830B88(play, this)) {
        return true;
    }
    return false;
}

s32 Player_UpperAction_1(Player* this, PlayState* play) {
    if (func_80830B88(play, this) || func_80830DF0(this, play)) {
        return true;
    }
    return false;
}

s32 Player_UpperAction_ChangeHeldItem(Player* this, PlayState* play) {
    if (PlayerAnimation_Update(play, &this->skelAnimeUpper) ||
        ((Player_ItemToItemAction(this, this->heldItemId) == this->heldItemAction) &&
         (sPlayerUseHeldItem =
              (sPlayerUseHeldItem || ((this->modelAnimType != PLAYER_ANIMTYPE_3) &&
                                      (this->heldItemAction != PLAYER_IA_DEKU_STICK) && (play->unk_1887C == 0)))))) {
        Player_SetUpperAction(play, this, sPlayerUpperActionUpdateFuncs[this->heldItemAction]);
        this->unk_ACC = 0;
        this->unk_AA4 = 0;
        sPlayerHeldItemButtonIsHeldDown = sPlayerUseHeldItem;
        return this->upperActionFunc(this, play);
    }

    if (func_8082ED94(this) != 0) {
        Player_WaitToFinishItemChange(play, this);
        Player_AnimationPlayOnce(play, this, func_8082ED20(this));
        this->unk_AA4 = 0;
    } else {
        Player_WaitToFinishItemChange(play, this);
    }

    return true;
}

s32 Player_UpperAction_3(Player* this, PlayState* play) {
    PlayerAnimation_Update(play, &this->skelAnimeUpper);
    if (!CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_R)) {
        func_80830CE8(play, this);
    } else {
        this->stateFlags1 |= PLAYER_STATE1_400000;
        Player_SetModelsForHoldingShield(this);
        if ((this->transformation == PLAYER_FORM_ZORA) && CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_B)) {
            func_8082F164(this, BTN_R | BTN_B);
        }
    }
    return true;
}

s32 Player_UpperAction_4(Player* this, PlayState* play) {
    if (PlayerAnimation_Update(play, &this->skelAnimeUpper)) {
        PlayerAnimationHeader* anim;
        f32 endFrame;

        anim = func_80830A58(play, this);
        endFrame = Animation_GetLastFrame(anim);
        PlayerAnimation_Change(play, &this->skelAnimeUpper, anim, 1.0f, endFrame, endFrame, ANIMMODE_ONCE, 0.0f);
    }

    this->stateFlags1 |= PLAYER_STATE1_400000;
    Player_SetModelsForHoldingShield(this);
    return true;
}

s32 Player_UpperAction_5(Player* this, PlayState* play) {
    sPlayerUseHeldItem = sPlayerHeldItemButtonIsHeldDown;
    if (sPlayerUseHeldItem || PlayerAnimation_Update(play, &this->skelAnimeUpper)) {
        Player_SetUpperAction(play, this, sPlayerUpperActionUpdateFuncs[this->heldItemAction]);
        PlayerAnimation_PlayLoop(play, &this->skelAnimeUpper, D_8085BE84[PLAYER_ANIMGROUP_0][this->modelAnimType]);
        this->unk_AA4 = 0;
        this->upperActionFunc(this, play);
        return false;
    }
    return true;
}

s32 Player_UpperAction_6(Player* this, PlayState* play) {
    if (this->unk_B28 >= 0) {
        this->unk_B28 = -this->unk_B28;
    }

    if (!Player_IsHoldingHookshot(this) || func_80831124(play, this)) {
        if (!func_80830B88(play, this) && !func_80831094(this, play)) {
            return false;
        }
    }
    return true;
}

PlayerAnimationHeader* D_8085D5E4[] = {
    &gPlayerAnim_link_hook_walk2ready,
    &gPlayerAnim_link_bow_walk2ready,
    &gPlayerAnim_pn_tamahakidf,
};

PlayerAnimationHeader* D_8085D5F0[] = {
    &gPlayerAnim_link_hook_wait,
    &gPlayerAnim_link_bow_bow_wait,
    &gPlayerAnim_pn_tamahakidf,
};

u16 D_8085D5FC[] = {
    NA_SE_IT_BOW_FLICK,
    NA_SE_PL_DEKUNUTS_MISS_FIRE,
    NA_SE_NONE,
    NA_SE_NONE,
};

s32 Player_UpperAction_7(Player* this, PlayState* play) {
    s32 index;
    s32 temp;

    if (Player_IsHoldingHookshot(this)) {
        index = 0;
    } else {
        temp = (this->transformation != PLAYER_FORM_DEKU) ? 1 : 2;
        index = temp;
    }

    if (this->transformation != PLAYER_FORM_DEKU) {
        Math_ScaledStepToS(&this->upperLimbRot.z, 0x4B0, 0x190);
        this->unk_AA6 |= 0x100;
    }

    if ((this->unk_ACE == 0) && (func_8082ED94(this) == 0) &&
        (this->skelAnime.animation == &gPlayerAnim_link_bow_side_walk)) {
        PlayerAnimation_PlayOnce(play, &this->skelAnimeUpper, D_8085D5E4[index]);
        this->unk_ACE = -1;
    } else if (PlayerAnimation_Update(play, &this->skelAnimeUpper)) {
        PlayerAnimation_PlayLoop(play, &this->skelAnimeUpper, D_8085D5F0[index]);
        this->unk_ACE = 1;
    } else if (this->unk_ACE == 1) {
        this->unk_ACE = 2;
    }

    if (this->unk_ACC >= 0xB) {
        this->unk_ACC--;
    }

    func_80831010(this, play);
    if ((this->unk_ACE > 0) && ((this->unk_B28 < 0) || (!sPlayerHeldItemButtonIsHeldDown && !func_80830FD4(play)))) {
        Player_SetUpperAction(play, this, Player_UpperAction_8);
        if (this->unk_B28 >= 0) {
            if (index != 0) {
                if (!func_80831194(play, this)) {
                    Player_PlaySfx(this, D_8085D5FC[this->unk_B28 - 1]);
                }

                if (this->transformation == PLAYER_FORM_DEKU) {
                    PlayerAnimation_PlayOnceSetSpeed(play, &this->skelAnimeUpper, &gPlayerAnim_pn_tamahaki,
                                                     2.0f / 3.0f);
                }
            } else if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
                func_80831194(play, this);
            }
        }
        this->unk_ACC = 0xA;
        Player_StopHorizontalMovement(this);
    } else {
        this->stateFlags3 |= PLAYER_STATE3_40;
    }

    return 1;
}

s32 Player_UpperAction_8(Player* this, PlayState* play) {
    s32 animFinished = PlayerAnimation_Update(play, &this->skelAnimeUpper);

    if (Player_IsHoldingHookshot(this) && !func_80831124(play, this)) {
        return true;
    }

    if (!func_80830B88(play, this) &&
        ((((this->unk_B28 < 0) && sPlayerHeldItemButtonIsHeldDown) ||
          ((animFinished || (this->transformation != PLAYER_FORM_DEKU)) && sPlayerUseHeldItem)) ||
         func_80830F9C(play))) {

        this->unk_B28 = ABS_ALT(this->unk_B28);
        if (func_808306F8(this, play)) {
            if (Player_IsHoldingHookshot(this)) {
                this->unk_ACE = 1;
            } else {
                PlayerAnimation_PlayOnce(play, &this->skelAnimeUpper,
                                         (this->transformation == PLAYER_FORM_DEKU)
                                             ? &gPlayerAnim_pn_tamahakidf
                                             : &gPlayerAnim_link_bow_bow_shoot_next);
            }
        }
    } else {
        if (this->unk_ACC != 0) {
            this->unk_ACC--;
        }

        if ((func_8082FBE8(this)) || (this->unk_AA5 != PLAYER_UNKAA5_0) || (this->stateFlags1 & PLAYER_STATE1_100000)) {
            if (this->unk_ACC == 0) {
                this->unk_ACC++;
            }
            return true;
        }

        if (Player_IsHoldingHookshot(this)) {
            Player_SetUpperAction(play, this, Player_UpperAction_6);
        } else {
            Player_SetUpperAction(play, this, Player_UpperAction_9);
            PlayerAnimation_PlayOnce(play, &this->skelAnimeUpper,
                                     (this->transformation == PLAYER_FORM_DEKU) ? &gPlayerAnim_pn_tamahakidf
                                                                                : &gPlayerAnim_link_bow_bow_shoot_end);
        }
        this->unk_ACC = 0;
    }

    return true;
}

s32 Player_UpperAction_9(Player* this, PlayState* play) {
    if (!(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) || PlayerAnimation_Update(play, &this->skelAnimeUpper)) {
        Player_SetUpperAction(play, this, Player_UpperAction_6);
    }
    return true;
}

s32 Player_UpperAction_10(Player* this, PlayState* play) {
    Actor* heldActor = this->heldActor;

    if (heldActor == NULL) {
        func_808309CC(play, this);
    }

    if (func_80830B88(play, this)) {
        return true;
    }

    if (this->stateFlags1 & PLAYER_STATE1_800) {
        if (PlayerAnimation_Update(play, &this->skelAnimeUpper)) {
            PlayerAnimation_PlayLoop(play, &this->skelAnimeUpper, &gPlayerAnim_link_normal_carryB_wait);
        }

        if ((heldActor->id == ACTOR_EN_NIW) && (this->actor.velocity.y <= 0.0f)) {
            this->actor.terminalVelocity = -2.0f;
            this->actor.gravity = -0.5f;
            this->fallStartHeight = this->actor.world.pos.y;
        }
        return true;
    }
    return Player_UpperAction_0(this, play);
}

s32 Player_UpperAction_11(Player* this, PlayState* play) {
    if (func_80830B88(play, this)) {
        return true;
    }

    if (this->stateFlags1 & PLAYER_STATE1_2000000) {
        Player_SetUpperAction(play, this, Player_UpperAction_15);
    } else if (func_80831094(this, play)) {
        return true;
    }

    return false;
}

s32 Player_UpperAction_12(Player* this, PlayState* play) {
    if (PlayerAnimation_Update(play, &this->skelAnimeUpper)) {
        Player_SetUpperAction(play, this, Player_UpperAction_13);
        PlayerAnimation_PlayLoop(play, &this->skelAnimeUpper, &gPlayerAnim_pz_cutterwaitanim);
    }
    if (this->skelAnimeUpper.animation == &gPlayerAnim_pz_cutterwaitanim) {
        func_80831010(this, play);
    }
    return true;
}

s32 Player_UpperAction_13(Player* this, PlayState* play) {
    PlayerAnimation_Update(play, &this->skelAnimeUpper);
    func_80831010(this, play);
    if (!sPlayerHeldItemButtonIsHeldDown) {
        Player_SetUpperAction(play, this, Player_UpperAction_14);
        PlayerAnimation_PlayOnce(play, &this->skelAnimeUpper, &gPlayerAnim_pz_cutterattack);
    }
    return true;
}

s32 Player_UpperAction_14(Player* this, PlayState* play) {
    if (PlayerAnimation_Update(play, &this->skelAnimeUpper)) {
        Player_SetUpperAction(play, this, Player_UpperAction_15);
        this->unk_ACC = 0;
    } else if (PlayerAnimation_OnFrame(&this->skelAnimeUpper, 6.0f)) {
        Vec3f pos;
        s16 untargetedRotY;

        func_80835BF8(&this->bodyPartsPos[PLAYER_BODYPART_LEFT_HAND], this->actor.shape.rot.y, 0.0f, &pos);
        pos.y = this->actor.world.pos.y + 50.0f;

        untargetedRotY = this->actor.shape.rot.y - 0x190;
        this->boomerangActor = Actor_Spawn(
            &play->actorCtx, play, ACTOR_EN_BOOM, pos.x, pos.y, pos.z, this->actor.focus.rot.x,
            (this->lockOnActor != NULL) ? this->actor.shape.rot.y + 0x36B0 : untargetedRotY, 0, ZORA_BOOMERANG_LEFT);

        if (this->boomerangActor != NULL) {
            EnBoom* leftBoomerang = (EnBoom*)this->boomerangActor;
            EnBoom* rightBoomerang;

            leftBoomerang->moveTo = this->lockOnActor;
            if (leftBoomerang->moveTo != NULL) {
                leftBoomerang->unk_1CF = 0x10;
            }
            leftBoomerang->unk_1CC = leftBoomerang->unk_1CF + 0x24;

            func_80835BF8(&this->bodyPartsPos[PLAYER_BODYPART_RIGHT_HAND], this->actor.shape.rot.y, 0.0f, &pos);

            untargetedRotY = (this->actor.shape.rot.y + 0x190);
            rightBoomerang =
                (EnBoom*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_BOOM, pos.x, pos.y, pos.z, this->actor.focus.rot.x,
                                     (this->lockOnActor != NULL) ? this->actor.shape.rot.y - 0x36B0 : untargetedRotY, 0,
                                     ZORA_BOOMERANG_RIGHT);

            if (rightBoomerang != NULL) {
                rightBoomerang->moveTo = this->lockOnActor;
                if (rightBoomerang->moveTo != NULL) {
                    rightBoomerang->unk_1CF = 0x10;
                }

                rightBoomerang->unk_1CC = rightBoomerang->unk_1CF + 0x24;
                leftBoomerang->actor.child = &rightBoomerang->actor;
                rightBoomerang->actor.parent = &leftBoomerang->actor;
            }

            this->stateFlags1 |= PLAYER_STATE1_2000000;
            this->stateFlags3 &= ~PLAYER_STATE3_800000;
            if (!func_80123420(this)) {
                func_8083133C(this);
            }

            this->unk_D57 = 20;

            Player_PlaySfx(this, NA_SE_IT_BOOMERANG_THROW);
            Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_SWORD_N);
        }
    }

    return true;
}

s32 Player_UpperAction_15(Player* this, PlayState* play) {
    if (func_80830B88(play, this)) {
        return true;
    }

    if (this->stateFlags3 & PLAYER_STATE3_800000) {
        Player_SetUpperAction(play, this, Player_UpperAction_16);
        PlayerAnimation_PlayOnce(play, &this->skelAnimeUpper, &gPlayerAnim_pz_cuttercatch);
        this->stateFlags3 &= ~PLAYER_STATE3_800000;
        Player_PlaySfx(this, NA_SE_PL_CATCH_BOOMERANG);
        Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_SWORD_N);
        return true;
    }

    return false;
}

s32 Player_UpperAction_16(Player* this, PlayState* play) {
    if (!Player_UpperAction_11(this, play) && PlayerAnimation_Update(play, &this->skelAnimeUpper)) {
        if (this->stateFlags1 & PLAYER_STATE1_2000000) {
            Player_SetUpperAction(play, this, Player_UpperAction_15);
            this->unk_ACC = 0;
        } else {
            Player_SetUpperAction(play, this, Player_UpperAction_0);
        }
    }
    return true;
}

void Player_Action_0(Player* this, PlayState* play) {
    PlayerAnimation_Update(play, &this->skelAnime);
    func_808323C0(this, play->playerCsIds[PLAYER_CS_ID_ITEM_BOTTLE]);

    if (DECR(this->actionVar2) == 0) {
        if (Message_GetState(&play->msgCtx) == TEXT_STATE_NONE) {
            Player_StopCutscene(this);
            Player_SetAction(play, this, Player_Action_4, 0);
            this->stateFlags1 &= ~PLAYER_STATE1_20000000;
        }
    } else if (this->actionVar2 == 30) {
        if (Message_GetState(&play->msgCtx) != TEXT_STATE_NONE) {
            this->actionVar2++;
        } else {
            Message_StartTextbox(play, 0xC03, NULL);
        }
    }
}

void Player_Action_1(Player* this, PlayState* play) {
    this->stateFlags3 |= PLAYER_STATE3_10000000;
    PlayerAnimation_Update(play, &this->skelAnime);
    Player_UpdateUpperBody(this, play);

    if (R_PLAY_FILL_SCREEN_ON == 0) {
        R_PLAY_FILL_SCREEN_ON = 20;
        R_PLAY_FILL_SCREEN_ALPHA = 0;
        R_PLAY_FILL_SCREEN_R = R_PLAY_FILL_SCREEN_G = R_PLAY_FILL_SCREEN_B = R_PLAY_FILL_SCREEN_ALPHA;
        Audio_PlaySfx(NA_SE_SY_DEKUNUTS_JUMP_FAILED);
    } else if (R_PLAY_FILL_SCREEN_ON > 0) {
        R_PLAY_FILL_SCREEN_ALPHA += R_PLAY_FILL_SCREEN_ON;
        if (R_PLAY_FILL_SCREEN_ALPHA > 255) {
            R_PLAY_FILL_SCREEN_ALPHA = 255;
            if (this->unk_B86[0] == 0) {
                this->unk_B86[0] = 1;
                func_8082DE50(play, this);
            } else {
                R_PLAY_FILL_SCREEN_ON = -20;
                this->stateFlags1 &= ~PLAYER_STATE1_8000000;
                this->actor.bgCheckFlags &= ~BGCHECKFLAG_GROUND;
                Player_SetEquipmentData(play, this);
                this->prevBoots = this->currentBoots;

                if (this->unk_3CF != 0) {
                    Math_Vec3f_Copy(&this->actor.world.pos, &this->unk_3C0);
                    this->actor.shape.rot.y = this->unk_3CC;
                } else {
                    Math_Vec3f_Copy(&this->actor.world.pos, &gSaveContext.respawn[RESPAWN_MODE_DOWN].pos);
                    this->actor.shape.rot.y = gSaveContext.respawn[RESPAWN_MODE_DOWN].yaw;
                }

                Math_Vec3f_Copy(&this->actor.prevPos, &this->actor.world.pos);
                this->linearVelocity = 0.0f;
                this->currentYaw = this->actor.shape.rot.y;
                this->actor.velocity.y = 0.0f;
                Player_AnimationPlayOnce(play, this, func_8082ED20(this));

                if ((play->roomCtx.curRoom.num == this->unk_3CE) && (play->roomCtx.prevRoom.num < 0)) {
                    this->actionVar2 = 5;
                } else {
                    play->roomCtx.curRoom.num = -1;
                    play->roomCtx.prevRoom.num = -1;
                    play->roomCtx.curRoom.segment = NULL;
                    play->roomCtx.prevRoom.segment = NULL;

                    func_8012EBF8(play, &play->roomCtx);
                    this->actionVar2 = -1;
                    this->actionVar1 = this->unk_3CE;
                }
            }
        }
    } else if (this->actionVar2 < 0) {
        if (Room_StartRoomTransition(play, &play->roomCtx, this->actionVar1)) {
            Map_InitRoomData(play, play->roomCtx.curRoom.num);
            Minimap_SavePlayerRoomInitInfo(play);
            this->actionVar2 = 5;
        }
    } else if (this->actionVar2 > 0) {
        this->actionVar2--;
    } else {
        R_PLAY_FILL_SCREEN_ALPHA += R_PLAY_FILL_SCREEN_ON;
        if (R_PLAY_FILL_SCREEN_ALPHA < 0) {
            R_PLAY_FILL_SCREEN_ALPHA = 0;
            R_PLAY_FILL_SCREEN_ON = 0;
            func_808339B4(this, -40);
            func_8085B384(this, play);
            this->actor.bgCheckFlags |= BGCHECKFLAG_GROUND;
        }
    }
}

void Player_Action_2(Player* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;
    s32 temp_v0;

    if (this->actionVar2 != 0) {
        if (PlayerAnimation_Update(play, &this->skelAnime)) {
            func_8082E794(this);
            Player_AnimationPlayLoop(play, this, func_8082EF54(this));
            this->actionVar2 = 0;
            this->stateFlags3 &= ~PLAYER_STATE3_8;
        }
        func_8082FC60(this);
    } else {
        func_8083E958(play, this);
    }

    func_80832F24(this);
    if (Player_TryActionChangeList(play, this, sPlayerActionChangeList1, true)) {
        return;
    }

    if (!func_8082FB68(this) && (!func_80123434(this) || (Player_UpperAction_3 != this->upperActionFunc))) {
        func_8083B29C(this, play);
        return;
    }

    Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);

    temp_v0 = func_8083E404(this, speedTarget, yawTarget);
    if (temp_v0 > 0) {
        func_8083A844(this, play, yawTarget);
    } else if (temp_v0 < 0) {
        func_8083AF8C(this, yawTarget, play);
    } else if (speedTarget > 4.0f) {
        func_8083B030(this, play);
    } else {
        u32 temp_v0_2;

        func_8083EA44(this, this->linearVelocity * 0.3f + 1.0f);
        func_8083E8E0(this, speedTarget, yawTarget);

        temp_v0_2 = this->unk_B38;
        if ((temp_v0_2 < 6) || ((temp_v0_2 - 0xE) < 6)) {
            Math_StepToF(&this->linearVelocity, 0.0f, 1.5f);
        } else {
            s16 temp_v0_3 = yawTarget - this->currentYaw;
            s32 var_v1 = ABS_ALT(temp_v0_3);

            if (var_v1 > 0x4000) {
                if (Math_StepToF(&this->linearVelocity, 0.0f, 1.5f)) {
                    this->currentYaw = yawTarget;
                }
            } else {
                Math_AsymStepToF(&this->linearVelocity, speedTarget * 0.3f, 2.0f, 1.5f);
                Math_ScaledStepToS(&this->currentYaw, yawTarget, var_v1 * 0.1f);
            }
        }
    }
}

void Player_Action_3(Player* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;
    s32 temp_v0;

    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        func_8082E794(this);
        Player_AnimationPlayOnce(play, this, func_8082ED20(this));
        this->stateFlags3 &= ~PLAYER_STATE3_8;
    }

    func_80832F24(this);
    if (Player_TryActionChangeList(play, this, sPlayerActionChangeList2, true)) {
        return;
    }

    if (func_8082FB68(this)) {
        func_8083B23C(this, play);
        return;
    }
    if (!func_80123434(this)) {
        Player_SetAction_PreserveMoveFlags(play, this, Player_Action_4, 1);
        this->currentYaw = this->actor.shape.rot.y;
        return;
    }
    if (Player_UpperAction_3 == this->upperActionFunc) {
        func_8083B23C(this, play);
        return;
    }

    Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);

    temp_v0 = func_8083E514(this, &speedTarget, &yawTarget, play);
    if (temp_v0 > 0) {
        func_8083A844(this, play, yawTarget);
    } else if (temp_v0 < 0) {
        func_8083AECC(this, yawTarget, play);
    } else if (speedTarget > 4.9f) {
        func_8083B030(this, play);
        func_8082FC60(this);
    } else if (speedTarget != 0.0f) {
        func_8083AF30(this, play);
    } else {
        s16 temp_v0_2 = yawTarget - this->actor.shape.rot.y;

        if (ABS_ALT(temp_v0_2) > 0x320) {
            func_8083B0E4(play, this, yawTarget);
        }
    }
}

void Player_Action_4(Player* this, PlayState* play) {
    s32 temp_v0 = func_8082ED94(this);
    s32 animFinished = PlayerAnimation_Update(play, &this->skelAnime);
    f32 speedTarget;
    s16 yawTarget;
    s16 temp_v1_2;

    func_8083C85C(this);
    if (temp_v0 > 0) {
        func_8082EEA4(this, temp_v0 - 1);
    }

    if (animFinished ||
        ((this->currentMask == PLAYER_MASK_SCENTS) && (this->skelAnime.animation != &gPlayerAnim_cl_msbowait)) ||
        ((this->currentMask != PLAYER_MASK_SCENTS) && (this->skelAnime.animation == &gPlayerAnim_cl_msbowait))) {
        if (this->actionVar2 != 0) {
            if (DECR(this->actionVar2) == 0) {
                this->skelAnime.endFrame = this->skelAnime.animLength - 1.0f;
            }

            this->skelAnime.jointTable[PLAYER_LIMB_ROOT - 1].y =
                (this->skelAnime.jointTable[PLAYER_LIMB_ROOT - 1].y + ((this->actionVar2 & 1) * 0x50)) - 0x28;
        } else {
            func_8082E794(this);
            Player_ChooseIdleAnim(play, this);
        }
        this->stateFlags3 &= ~PLAYER_STATE3_8;
    }

    func_80832F24(this);
    if ((this->actionVar2 == 0) && !func_80847880(play, this) &&
        !Player_TryActionChangeList(play, this, sPlayerActionChangeList7, true)) {
        if (func_8082FB68(this)) {
            func_8083B23C(this, play);
            return;
        }
        if (func_80123434(this)) {
            func_8083692C(this, play);
            return;
        }

        Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_CURVED, play);

        if (speedTarget != 0.0f) {
            func_8083A844(this, play, yawTarget);
            return;
        }
        temp_v1_2 = yawTarget - this->actor.shape.rot.y;

        if (ABS_ALT(temp_v1_2) > 0x320) {
            func_8083B0E4(play, this, yawTarget);
        } else {
            Math_ScaledStepToS(&this->actor.shape.rot.y, yawTarget, 0x4B0);
            this->currentYaw = this->actor.shape.rot.y;
            if (func_8082ED20(this) == this->skelAnime.animation) {
                func_8083C6E8(this, play);
            }
        }
    }
}

void Player_Action_5(Player* this, PlayState* play) {
    f32 var_fv0;
    s16 temp_v0_3;
    f32 speedTarget;
    s16 yawTarget;
    s32 var_v0;
    s32 temp_v0_2;
    s32 var_v1;
    f32 var_fv1;

    this->skelAnime.mode = 0;
    PlayerAnimation_SetUpdateFunction(&this->skelAnime);

    this->skelAnime.animation = func_8082EFE4(this);
    if (this->skelAnime.animation == &gPlayerAnim_link_bow_side_walk) {
        var_fv0 = 24.0f;
        var_fv1 = -(MREG(95) / 100.0f);
    } else {
        var_fv0 = 29.0f;
        var_fv1 = MREG(95) / 100.0f;
    }

    this->skelAnime.animLength = var_fv0;
    this->skelAnime.endFrame = var_fv0 - 1.0f;
    if (BINANG_SUB(this->currentYaw, this->actor.shape.rot.y) >= 0) {
        var_v0 = 1;
    } else {
        var_v0 = -1;
    }

    this->skelAnime.playSpeed = var_v0 * (this->linearVelocity * var_fv1);

    PlayerAnimation_Update(play, &this->skelAnime);
    if (PlayerAnimation_OnFrame(&this->skelAnime, 0.0f) || PlayerAnimation_OnFrame(&this->skelAnime, var_fv0 / 2.0f)) {
        Player_AnimSfx_PlayFloorWalk(this, this->linearVelocity);
    }

    if (Player_TryActionChangeList(play, this, sPlayerActionChangeList3, true)) {
        return;
    }

    if (func_8082FB68(this)) {
        func_8083B23C(this, play);
        return;
    }
    if (!func_80123434(this)) {
        func_8085B384(this, play);
        return;
    }

    Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);

    temp_v0_2 = func_8083E514(this, &speedTarget, &yawTarget, play);
    if (temp_v0_2 > 0) {
        func_8083A844(this, play, yawTarget);
        return;
    }
    if (temp_v0_2 < 0) {
        func_8083AECC(this, yawTarget, play);
        return;
    }
    if (speedTarget > 4.9f) {
        func_8083B030(this, play);
        func_8082FC60(this);
        return;
    }
    if ((speedTarget == 0.0f) && (this->linearVelocity == 0.0f)) {
        func_8083692C(this, play);
        return;
    }

    temp_v0_3 = yawTarget - this->currentYaw;
    var_v1 = ABS_ALT(temp_v0_3);
    if (var_v1 > 0x4000) {
        if (Math_StepToF(&this->linearVelocity, 0.0f, 1.5f)) {
            this->currentYaw = yawTarget;
        }
    } else {
        Math_AsymStepToF(&this->linearVelocity, speedTarget * 0.4f, 1.5f, 1.5f);
        Math_ScaledStepToS(&this->currentYaw, yawTarget, var_v1 * 0.1f);
    }
}

void Player_Action_6(Player* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;
    s32 sp2C;

    func_8083EE60(this, play);
    if (Player_TryActionChangeList(play, this, sPlayerActionChangeList4, true)) {
        return;
    }

    if (func_8082FC24(this) == 0) {
        func_8083A844(this, play, this->currentYaw);
        return;
    }

    Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);

    sp2C = func_8083E514(this, &speedTarget, &yawTarget, play);
    if (sp2C >= 0) {
        if (!func_8083F190(this, &speedTarget, &yawTarget, play)) {
            if (sp2C != 0) {
                func_8083A794(this, play);
            } else if (speedTarget > 4.9f) {
                func_8083B030(this, play);
            } else {
                func_8083AF30(this, play);
            }
        }
    } else {
        s16 sp2A = yawTarget - this->currentYaw;

        Math_AsymStepToF(&this->linearVelocity, speedTarget * 1.5f, 1.5f, 2.0f);
        Math_ScaledStepToS(&this->currentYaw, yawTarget, sp2A * 0.1f);
        if ((speedTarget == 0.0f) && (this->linearVelocity == 0.0f)) {
            func_8083692C(this, play);
        }
    }
}

void Player_Action_7(Player* this, PlayState* play) {
    s32 animFinished = PlayerAnimation_Update(play, &this->skelAnime);
    f32 speedTarget;
    s16 yawTarget;

    func_80832F24(this);

    if (Player_TryActionChangeList(play, this, sPlayerActionChangeList4, true)) {
        return;
    }

    Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);

    if (this->linearVelocity != 0.0f) {
        return;
    }

    this->currentYaw = this->actor.shape.rot.y;
    if (func_8083E514(this, &speedTarget, &yawTarget, play) > 0) {
        func_8083A794(this, play);
    } else if ((speedTarget != 0.0f) || animFinished) {
        func_8083F230(this, play);
    }
}

void Player_Action_8(Player* this, PlayState* play) {
    s32 animFinished = PlayerAnimation_Update(play, &this->skelAnime);

    if (Player_TryActionChangeList(play, this, sPlayerActionChangeList4, true)) {
        return;
    }

    if (animFinished) {
        func_8083692C(this, play);
    }
}

void Player_Action_9(Player* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;
    s32 var_v0;

    func_8083F27C(play, this);
    if (Player_TryActionChangeList(play, this, sPlayerActionChangeList5, true)) {
        return;
    }

    if (!func_8082FC24(this)) {
        func_8083A794(this, play);
        return;
    }

    Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);

    if (func_80123434(this)) {
        var_v0 = func_8083E514(this, &speedTarget, &yawTarget, play);
    } else {
        var_v0 = func_8083E404(this, speedTarget, yawTarget);
    }

    if (var_v0 > 0) {
        func_8083A794(this, play);
    } else if (var_v0 < 0) {
        if (func_80123434(this)) {
            func_8083AECC(this, yawTarget, play);
        } else {
            func_8083AF8C(this, yawTarget, play);
        }
    } else if ((this->linearVelocity < 3.6f) && (speedTarget < 4.0f)) {
        if (!func_80123420(this) && func_80123434(this)) {
            func_8083AF30(this, play);
        } else {
            func_80836988(this, play);
        }
    } else {
        s16 temp_v0;
        s32 var_v1;
        s32 pad;

        func_8083E8E0(this, speedTarget, yawTarget);

        temp_v0 = yawTarget - this->currentYaw;
        var_v1 = ABS_ALT(temp_v0);
        if (var_v1 > 0x4000) {
            if (Math_StepToF(&this->linearVelocity, 0.0f, 3.0f)) {
                this->currentYaw = yawTarget;
            }
        } else {
            speedTarget *= 0.9f;
            Math_AsymStepToF(&this->linearVelocity, speedTarget, 2.0f, 3.0f);
            Math_ScaledStepToS(&this->currentYaw, yawTarget, var_v1 * 0.1f);
        }
    }
}

void Player_Action_10(Player* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    PlayerAnimation_Update(play, &this->skelAnime);
    if (Player_IsHoldingTwoHandedWeapon(this)) {
        AnimationContext_SetLoadFrame(play, func_8082ED20(this), 0, this->skelAnime.limbCount,
                                      this->skelAnime.morphTable);
        AnimationContext_SetCopyTrue(play, this->skelAnime.limbCount, this->skelAnime.jointTable,
                                     this->skelAnime.morphTable, sPlayerUpperBodyLimbCopyMap);
    }

    Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_CURVED, play);

    if ((this != GET_PLAYER(play)) && (this->lockOnActor == NULL)) {
        yawTarget = this->actor.home.rot.y;
    }

    if (Player_TryActionChangeList(play, this, sPlayerActionChangeList6, true)) {
        return;
    }

    if (speedTarget != 0.0f) {
        this->actor.shape.rot.y = yawTarget;
        func_8083A794(this, play);
    } else if (Math_ScaledStepToS(&this->actor.shape.rot.y, yawTarget, this->unk_B4E)) {
        func_80839E74(this, play);
    }
    this->currentYaw = this->actor.shape.rot.y;
}

void Player_Action_11(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;

    if (this->linearVelocity < 1.0f) {
        this->skelAnime.animation = &gPlayerAnim_clink_normal_okarina_walk;
    } else {
        this->skelAnime.animation = &gPlayerAnim_clink_normal_okarina_walkB;
    }
    PlayerAnimation_Update(play, &this->skelAnime);

    if (!func_80847880(play, this) && (!Player_TryActionChangeList(play, this, sPlayerActionChangeList7, true) ||
                                       (Player_Action_11 == this->actionFunc))) {
        f32 speedTarget;
        f32 temp_fv0;
        f32 temp_fv1;
        s16 yawTarget;
        s16 sp30;

        if (!CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_B)) {
            func_80839E74(this, play);
            return;
        }

        this->linearVelocity = this->unk_B48;
        Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_CURVED, play);
        sp30 = yawTarget;

        if (!func_8083A4A4(this, &speedTarget, &yawTarget, REG(43) / 100.0f)) {
            func_8083CB04(this, speedTarget, yawTarget, REG(19) / 100.0f, 1.5f, 0x3E8);
            func_8083C8E8(this, play);
            if ((this->linearVelocity == 0.0f) && (speedTarget == 0.0f)) {
                this->currentYaw = sp30;
                this->actor.shape.rot.y = this->currentYaw;
            }
        }

        this->unk_B48 = this->linearVelocity;
        temp_fv0 = this->skelAnime.curFrame + 5.0f;
        temp_fv1 = this->skelAnime.animLength / 2.0f;

        // effectively an fmodf
        temp_fv0 -= temp_fv1 * (s32)(temp_fv0 / temp_fv1);
        this->linearVelocity *= Math_CosS(temp_fv0 * 1000.0f) * 0.4f;
    }
}

void Player_Action_12(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;
    PlayerAnimation_Update(play, &this->skelAnime);
    func_80832F24(this);
    if (!func_80847880(play, this)) {
        if (!Player_TryActionChangeList(play, this, sPlayerActionChangeList7, false) ||
            (Player_Action_12 == this->actionFunc)) {
            if (!CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_B)) {
                func_80839E74(this, play);
            }
        }
    }
}

void Player_Action_13(Player* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    this->stateFlags2 |= PLAYER_STATE2_20;
    func_8083F57C(this, play);
    if (Player_TryActionChangeList(play, this, sPlayerActionChangeList8, true)) {
        return;
    }

    if (func_8082FC24(this)) {
        func_8083A794(this, play);
        return;
    }

    Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_CURVED, play);

    if (this->currentMask == PLAYER_MASK_BUNNY) {
        speedTarget *= 1.5f;
    }

    if (!func_8083A4A4(this, &speedTarget, &yawTarget, REG(43) / 100.0f)) {
        func_8083CB58(this, speedTarget, yawTarget);
        func_8083C8E8(this, play);
        if ((this->linearVelocity == 0.0f) && (speedTarget == 0.0f)) {
            func_80839E3C(this, play);
        }
    }
}

void Player_Action_14(Player* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    this->stateFlags2 |= PLAYER_STATE2_20;

    func_8083F57C(this, play);
    if (Player_TryActionChangeList(play, this, sPlayerActionChangeList9, true)) {
        return;
    }

    if (!func_8082FC24(this)) {
        func_8083A794(this, play);
        return;
    }

    Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);

    if (!func_8083A4A4(this, &speedTarget, &yawTarget, REG(43) / 100.0f)) {
        if ((func_80123434(this) && (speedTarget != 0) && (func_8083E514(this, &speedTarget, &yawTarget, play) <= 0)) ||
            (!func_80123434(this) && (func_8083E404(this, speedTarget, yawTarget) <= 0))) {
            func_80836988(this, play);
        } else {
            func_8083CB58(this, speedTarget, yawTarget);
            func_8083C8E8(this, play);
            if ((this->linearVelocity == 0.0f) && (speedTarget == 0.0f)) {
                func_80836988(this, play);
            }
        }
    }
}

void Player_Action_15(Player* this, PlayState* play) {
    s32 animFinished = PlayerAnimation_Update(play, &this->skelAnime);
    f32 speedTarget;
    s16 yawTarget;

    if (Player_TryActionChangeList(play, this, sPlayerActionChangeList5, true)) {
        return;
    }

    if (!func_8082FC24(this)) {
        func_8083A794(this, play);
        return;
    }

    Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);

    if ((this->skelAnime.morphWeight == 0.0f) && (this->skelAnime.curFrame > 5.0f)) {
        func_80832F24(this);
        if ((this->skelAnime.curFrame > 10.0f) && (func_8083E404(this, speedTarget, yawTarget) < 0)) {
            func_8083AF8C(this, yawTarget, play);
        } else if (animFinished) {
            func_8083B090(this, play);
        }
    }
}

void Player_Action_16(Player* this, PlayState* play) {
    s32 animFinished = PlayerAnimation_Update(play, &this->skelAnime);
    f32 speedTarget;
    s16 yawTarget;

    func_80832F24(this);
    if (Player_TryActionChangeList(play, this, sPlayerActionChangeList10, true)) {
        return;
    }

    Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);

    if (this->linearVelocity == 0.0f) {
        this->currentYaw = this->actor.shape.rot.y;
        if (func_8083E404(this, speedTarget, yawTarget) > 0) {
            func_8083A794(this, play);
        } else if ((speedTarget != 0.0f) || animFinished) {
            func_80836988(this, play);
        }
    }
}

void Player_Action_17(Player* this, PlayState* play) {
    if (this->skelAnime.animation == &gPlayerAnim_link_normal_backspace) {
        if (PlayerAnimation_Update(play, &this->skelAnime)) {
            func_8082E794(this);
            func_8082E438(play, this, D_8085BE84[PLAYER_ANIMGROUP_31][this->modelAnimType]);
        }
    } else {
        func_8082E67C(play, this, D_8085BE84[PLAYER_ANIMGROUP_32][this->modelAnimType]);
    }

    if (DECR(this->actionVar2) == 0) {
        if (!Player_ActionChange_13(this, play)) {
            func_80836A98(this, D_8085BE84[PLAYER_ANIMGROUP_33][this->modelAnimType], play);
        }
        this->actor.flags &= ~ACTOR_FLAG_TALK_REQUESTED;
        func_800E0238(Play_GetCamera(play, CAM_ID_MAIN));
    }
}

// Player_Action_Shielding
void Player_Action_18(Player* this, PlayState* play) {
    func_80832F24(this);

    if (this->transformation == PLAYER_FORM_GORON) {
        SkelAnime_Update(&this->unk_2C8);

        if (!func_8083FE38(this, play)) {
            if (!Player_ActionChange_11(this, play)) {
                this->stateFlags1 &= ~PLAYER_STATE1_400000;

                if (this->itemAction <= PLAYER_IA_MINUS1) {
                    func_80123C58(this);
                }

                func_80836A98(this, D_8085BE84[PLAYER_ANIMGROUP_21][this->modelAnimType], play);
                func_80830B38(this);
            } else {
                this->stateFlags1 |= PLAYER_STATE1_400000;
            }
        }

        return;
    }

    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        if (!Player_IsGoronOrDeku(this)) {
            Player_AnimationPlayLoop(play, this, D_8085BE84[PLAYER_ANIMGROUP_20][this->modelAnimType]);
        }

        this->actionVar2 = 1;
        this->actionVar1 = 0;
    }

    if (!Player_IsGoronOrDeku(this)) {
        this->stateFlags1 |= PLAYER_STATE1_400000;
        Player_UpdateUpperBody(this, play);
        this->stateFlags1 &= ~PLAYER_STATE1_400000;
        if (this->transformation == PLAYER_FORM_ZORA) {
            func_8082F164(this, BTN_R | BTN_B);
        }
    }

    if (this->actionVar2 != 0) {
        f32 yStick = sPlayerControlInput->rel.stick_y * 180;
        f32 xStick = sPlayerControlInput->rel.stick_x * -120;
        s16 temp_a0 = this->actor.shape.rot.y - Camera_GetInputDirYaw(GET_ACTIVE_CAM(play));
        s16 var_a1;
        s16 temp_ft5;
        s16 var_a2;
        s16 var_a3;

        var_a1 = (yStick * Math_CosS(temp_a0)) + (Math_SinS(temp_a0) * xStick);
        temp_ft5 = (xStick * Math_CosS(temp_a0)) - (Math_SinS(temp_a0) * yStick);

        var_a1 = CLAMP_MAX(var_a1, 0xDAC);
        var_a2 = ABS_ALT(var_a1 - this->actor.focus.rot.x) * 0.25f;
        var_a2 = CLAMP_MIN(var_a2, 0x64);

        var_a3 = ABS_ALT(temp_ft5 - this->upperLimbRot.y) * 0.25f;
        var_a3 = CLAMP_MIN(var_a3, 0x32);
        Math_ScaledStepToS(&this->actor.focus.rot.x, var_a1, var_a2);

        this->upperLimbRot.x = this->actor.focus.rot.x;
        Math_ScaledStepToS(&this->upperLimbRot.y, temp_ft5, var_a3);

        if (this->actionVar1 != 0) {
            if (!func_808401F4(play, this)) {
                if (this->skelAnime.curFrame < 2.0f) {
                    func_8082FA5C(play, this, PLAYER_MELEE_WEAPON_STATE_1);
                }
            } else {
                this->actionVar2 = 1;
                this->actionVar1 = 0;
            }
        } else if (!func_8083FE38(this, play)) {
            if (Player_ActionChange_11(this, play)) {
                func_8083FD80(this, play);
            } else {
                this->stateFlags1 &= ~PLAYER_STATE1_400000;
                func_8082DC38(this);

                if (Player_IsGoronOrDeku(this)) {
                    func_80836A5C(this, play);
                    PlayerAnimation_Change(play, &this->skelAnime, this->skelAnime.animation, 1.0f,
                                           Animation_GetLastFrame(this->skelAnime.animation), 0.0f, 2, 0.0f);
                } else {
                    if (this->itemAction <= PLAYER_IA_MINUS1) {
                        func_80123C58(this);
                    }

                    func_80836A98(this, D_8085BE84[PLAYER_ANIMGROUP_21][this->modelAnimType], play);
                }

                Player_PlaySfx(this, NA_SE_IT_SHIELD_REMOVE);
                return;
            }
        } else {
            return;
        }
    }

    this->stateFlags1 |= PLAYER_STATE1_400000;
    Player_SetModelsForHoldingShield(this);
    this->unk_AA6 |= 0xC1;
}

void Player_Action_19(Player* this, PlayState* play) {
    func_80832F24(this);
    if (this->actionVar1 == 0) {
        D_80862B04 = Player_UpdateUpperBody(this, play);
        if ((Player_UpperAction_3 == this->upperActionFunc) ||
            (func_808331FC(play, this, &this->skelAnimeUpper, 4.0f) > 0)) {
            Player_SetAction(play, this, Player_Action_2, 1);
        }
    } else {
        s32 temp_v0;

        this->stateFlags1 |= PLAYER_STATE1_400000;
        temp_v0 = func_808331FC(play, this, &this->skelAnime, 4.0f);
        if ((temp_v0 != 0) && ((temp_v0 > 0) || PlayerAnimation_Update(play, &this->skelAnime))) {
            PlayerAnimationHeader* anim;
            f32 endFrame;

            Player_SetAction(play, this, Player_Action_18, 1);
            Player_SetModelsForHoldingShield(this);
            anim = D_8085BE84[PLAYER_ANIMGROUP_19][this->modelAnimType];
            endFrame = Animation_GetLastFrame(anim);
            PlayerAnimation_Change(play, &this->skelAnime, anim, 1.0f, endFrame, endFrame, ANIMMODE_ONCE, 0.0f);
        }
    }
}

void Player_Action_20(Player* this, PlayState* play) {
    s32 temp_v0;

    func_80832F24(this);
    temp_v0 = func_808331FC(play, this, &this->skelAnime, 16.0f);
    if (temp_v0 != 0) {
        if (PlayerAnimation_Update(play, &this->skelAnime) || (temp_v0 > 0)) {
            func_80836988(this, play);
        }
    }
}

void Player_Action_21(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20 | PLAYER_STATE2_40;
    func_808345A8(this);

    if (!(this->stateFlags1 & PLAYER_STATE1_20000000) && (this->actionVar2 == 0) && (this->unk_B75 != 0)) {
        s16 temp_v0 = this->unk_B76;
        s16 temp_v1 = this->actor.shape.rot.y - temp_v0;

        this->actor.shape.rot.y = temp_v0;
        this->currentYaw = temp_v0;
        this->linearVelocity = this->unk_B78;

        if (ABS_ALT(temp_v1) > 0x4000) {
            this->actor.shape.rot.y = temp_v0 + 0x8000;
        }

        if (this->actor.velocity.y < 0.0f) {
            this->actor.gravity = 0.0f;
            this->actor.velocity.y = 0.0f;
        }
    }

    if (PlayerAnimation_Update(play, &this->skelAnime) && (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
        if (this->actionVar2 != 0) {
            this->actionVar2--;
            if (this->actionVar2 == 0) {
                func_8085B384(this, play);
            }
        } else if ((this->stateFlags1 & PLAYER_STATE1_20000000) ||
                   (!(this->cylinder.base.acFlags & AC_HIT) && (this->unk_B75 == 0))) {
            if (this->stateFlags1 & PLAYER_STATE1_20000000) {
                this->actionVar2++;
            } else {
                Player_SetAction(play, this, Player_Action_22, 0);
                this->stateFlags1 |= PLAYER_STATE1_4000000;
            }

            Player_AnimationPlayOnce(play, this,
                                     (this->currentYaw != this->actor.shape.rot.y)
                                         ? &gPlayerAnim_link_normal_front_downB
                                         : &gPlayerAnim_link_normal_back_downB);
            Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_FREEZE);
        }
    }

    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND_TOUCH) {
        Player_AnimSfx_PlayFloor(this, NA_SE_PL_BOUND);
    }
}

void Player_Action_22(Player* this, PlayState* play) {
    this->stateFlags2 |= (PLAYER_STATE2_20 | PLAYER_STATE2_40);
    func_808345A8(this);
    func_80832F24(this);
    if (PlayerAnimation_Update(play, &this->skelAnime) && (this->linearVelocity == 0.0f)) {
        if (this->stateFlags1 & PLAYER_STATE1_20000000) {
            this->actionVar2++;
        } else {
            Player_SetAction(play, this, Player_Action_23, 0);
            this->stateFlags1 |= PLAYER_STATE1_4000000;
        }

        func_8082DB90(play, this,
                      (this->currentYaw != this->actor.shape.rot.y) ? &gPlayerAnim_link_normal_front_down_wake
                                                                    : &gPlayerAnim_link_normal_back_down_wake);
        this->currentYaw = this->actor.shape.rot.y;
    }
}

AnimSfxEntry D_8085D604[] = {
    ANIMSFX(ANIMSFX_TYPE_8, 20, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_8, 30, NA_SE_NONE, STOP),
};

void Player_Action_23(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;

    func_808345A8(this);
    if (this->stateFlags1 & PLAYER_STATE1_20000000) {
        PlayerAnimation_Update(play, &this->skelAnime);
    } else {
        s32 temp_v0 = func_808331FC(play, this, &this->skelAnime, 16.0f);

        if (temp_v0 != 0) {
            if (PlayerAnimation_Update(play, &this->skelAnime) || (temp_v0 > 0)) {
                func_80836988(this, play);
            }
        }
    }

    Player_PlayAnimSfx(this, D_8085D604);
}

AnimSfxEntry D_8085D60C[] = {
    ANIMSFX(ANIMSFX_TYPE_FLOOR, 60, NA_SE_PL_BOUND, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_8, 140, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_8, 164, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_8, 170, NA_SE_NONE, STOP),
};

void Player_Action_24(Player* this, PlayState* play) {
    if ((this->transformation != PLAYER_FORM_GORON) && (this->actor.depthInWater <= 0.0f)) {
        if ((play->roomCtx.curRoom.behaviorType2 == ROOM_BEHAVIOR_TYPE2_HOT) || (sPlayerFloorType == FLOOR_TYPE_9) ||
            ((func_808340AC(sPlayerFloorType) >= 0) &&
             !SurfaceType_IsWallDamage(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId))) {
            func_808344C0(play, this);
        }
    }

    func_80832F24(this);
    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        if (this == GET_PLAYER(play)) {
            func_80840770(play, this);
        }
    } else if (this->skelAnime.animation == &gPlayerAnim_link_derth_rebirth) {
        Player_PlayAnimSfx(this, D_8085D60C);
    } else if ((this->skelAnime.animation == &gPlayerAnim_link_normal_electric_shock_end) &&
               PlayerAnimation_OnFrame(&this->skelAnime, 88.0f)) {
        Player_AnimSfx_PlayFloor(this, NA_SE_PL_BOUND);
    }
}

s32 func_8084C124(PlayState* play, Player* this) {
    if (func_80837730(play, this, 3.0f, 500)) {
        Player_PlaySfx(this, NA_SE_EV_DIVE_INTO_WATER);
        return true;
    }
    return false;
}

void Player_Action_25(Player* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;
    Actor* heldActor;

    if (func_80123420(this)) {
        this->actor.gravity = -1.2f;
    }

    if (!(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
        Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);

        if (this->stateFlags1 & PLAYER_STATE1_800) {
            heldActor = this->heldActor;
            if (!func_808313A8(play, this, heldActor) && (heldActor->id == ACTOR_EN_NIW) &&
                CHECK_BTN_ANY(sPlayerControlInput->press.button, BTN_CRIGHT | BTN_CLEFT | BTN_CDOWN | BTN_B | BTN_A)) {
                func_808409A8(play, this, this->linearVelocity + 2.0f, this->actor.velocity.y + 2.0f);
            }
        }

        PlayerAnimation_Update(play, &this->skelAnime);
        if ((this->skelAnime.animation == &gPlayerAnim_link_normal_newroll_jump_20f) &&
            PlayerAnimation_OnFrame(&this->skelAnime, 4.0f)) {
            Player_PlaySfx(this, NA_SE_PL_ROLL);
        }

        if (this->transformation == PLAYER_FORM_DEKU) {
            s16 prevYaw = this->currentYaw;

            func_808378FC(play, this);
            func_8083CBC4(this, speedTarget * 0.5f, yawTarget, 2.0f, 0.2f, 0.1f, 0x190);

            if (this->skelAnime.animation == &gPlayerAnim_pn_attack) {
                this->stateFlags2 |= (PLAYER_STATE2_20 | PLAYER_STATE2_40);

                this->unk_B10[0] += -800.0f;
                this->actor.shape.rot.y += BINANG_ADD((s16)this->unk_B10[0], BINANG_SUB(this->currentYaw, prevYaw));
                Math_StepToF(&this->unk_B10[1], 0.0f, this->unk_B10[0]);
            }
        } else {
            func_8083CBC4(this, speedTarget, yawTarget, 1.0f, 0.05f, 0.1f, 0xC8);
        }

        Player_UpdateUpperBody(this, play);
        if ((((this->stateFlags2 & PLAYER_STATE2_80000) && ((this->actionVar1 == 2) || (this->actionVar1 >= 4))) ||
             !func_80839770(this, play)) &&
            (this->actor.velocity.y < 0.0f)) {
            if (this->actionVar2 >= 0) {
                if ((this->actor.bgCheckFlags & BGCHECKFLAG_WALL) || (this->actionVar2 == 0) ||
                    (this->fallDistance > 0)) {
                    if ((sPlayerYDistToFloor > 800.0f) || (this->stateFlags3 & PLAYER_STATE3_10000)) {
                        func_80840980(this, NA_SE_VO_LI_FALL_S);
                        this->stateFlags3 &= ~PLAYER_STATE3_10000;
                    }
                    PlayerAnimation_Change(play, &this->skelAnime, &gPlayerAnim_link_normal_landing, 1.0f, 0.0f, 0.0f,
                                           ANIMMODE_ONCE, 8.0f);
                    this->actionVar2 = -1;
                }
            } else {
                if ((this->actionVar2 == -1) && (this->fallDistance > 120) && (sPlayerYDistToFloor > 280.0f)) {
                    this->actionVar2 = -2;
                    func_80840980(this, NA_SE_VO_LI_FALL_L);
                }

                if ((this->actor.bgCheckFlags & BGCHECKFLAG_PLAYER_WALL_INTERACT) &&
                    !(this->stateFlags1 & (PLAYER_STATE1_800 | PLAYER_STATE1_8000000)) &&
                    (this->linearVelocity > 0.0f)) {
                    if ((this->transformation != PLAYER_FORM_GORON) &&
                        ((this->transformation != PLAYER_FORM_DEKU) || (this->remainingHopsCounter != 0))) {
                        if ((this->yDistToLedge >= 150.0f) && (this->unk_AE3[this->unk_ADE] == 0)) {
                            if (func_8083D860(this, play)) {
                                func_8084C124(play, this);
                            }
                        } else if ((this->ledgeClimbType >= PLAYER_LEDGE_CLIMB_2) &&
                                   ((this->yDistToLedge < (150.0f * this->ageProperties->unk_08)) &&
                                    (((this->actor.world.pos.y - this->actor.floorHeight) + this->yDistToLedge)) >
                                        (70.0f * this->ageProperties->unk_08))) {
                            AnimationContext_DisableQueue(play);
                            if (this->stateFlags3 & PLAYER_STATE3_10000) {
                                Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_HOOKSHOT_HANG);
                            } else {
                                Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_HANG);
                            }

                            this->actor.world.pos.y += this->yDistToLedge;
                            func_80837CEC(play, this, this->actor.wallPoly, this->distToInteractWall,
                                          GET_PLAYER_ANIM(PLAYER_ANIMGROUP_38, this->modelAnimType));
                            this->currentYaw += 0x8000;
                            this->actor.shape.rot.y = this->currentYaw;
                            this->stateFlags1 |= PLAYER_STATE1_2000;

                            func_8084C124(play, this);
                        }
                    }
                }
            }
        }
    } else {
        func_80837134(play, this);
        Player_UpdateUpperBody(this, play);
    }

    Player_ActionChange_13(this, play);
}

// sPlayerRollingAnimSfx
AnimSfxEntry D_8085D61C[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 1, NA_SE_VO_LI_SWORD_N, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_FLOOR_BY_AGE, 6, NA_SE_PL_WALK_GROUND, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 6, NA_SE_PL_ROLL, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_FLOOR_LAND, 18, NA_SE_NONE, STOP),
};

// Player_Action_Rolling // Handles bonking too?
void Player_Action_26(Player* this, PlayState* play) {
    s32 animFinished;

    this->stateFlags2 |= PLAYER_STATE2_20;
    this->stateFlags3 |= PLAYER_STATE3_8000000;

    animFinished = PlayerAnimation_Update(play, &this->skelAnime);
    if (PlayerAnimation_OnFrame(&this->skelAnime, 8.0f)) {
        func_808339B4(this, -10);
    }

    if (this->skelAnime.curFrame >= 8.0f) {
        if (this->skelAnime.curFrame < 18.0f) {
            Player_SetCylinderForAttack(this, DMG_NORMAL_ROLL, 1, 12);
        } else {
            Player_ResetCylinder(this);
        }
    }

    if (func_8083FE38(this, play)) {
        return;
    }

    if (this->actionVar2 != 0) {
        s32 temp_v0;

        Math_StepToF(&this->linearVelocity, 0.0f, 2.0f);
        temp_v0 = func_808331FC(play, this, &this->skelAnime, 5.0f);
        if (temp_v0 != 0) {
            if ((temp_v0 > 0) || animFinished) {
                func_80836A5C(this, play);
            }
        }
    } else if (!func_80840A30(play, this, &this->linearVelocity, 6.0f)) {
        if ((this->skelAnime.curFrame < 15.0f) || !Player_ActionChange_7(this, play)) {
            f32 speedTarget;
            s16 yawTarget;

            if (this->skelAnime.curFrame >= 20.0f) {
                func_80836A5C(this, play);
                return;
            }

            Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_CURVED, play);
            speedTarget *= 1.5f;

            if ((speedTarget < 3.0f) || (this->unk_AE3[this->unk_ADE] != 0)) {
                speedTarget = 3.0f;
            }
            func_8083CB58(this, speedTarget, this->actor.shape.rot.y);

            if (func_8083FBC4(play, this)) {
                Actor_PlaySfx_FlaggedCentered1(&this->actor, (this->floorSfxOffset == NA_SE_PL_WALK_SNOW - SFX_FLAG)
                                                                 ? NA_SE_PL_ROLL_SNOW_DUST - SFX_FLAG
                                                                 : NA_SE_PL_ROLL_DUST - SFX_FLAG);
            }

            Player_PlayAnimSfx(this, D_8085D61C);
        }
    }
}

void Player_Action_27(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;

    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        Player_AnimationPlayLoop(play, this, &gPlayerAnim_link_normal_run_jump_water_fall_wait);
    }

    Math_StepToF(&this->linearVelocity, 0.0f, 0.05f);
    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        if (this->fallDistance >= 400) {
            this->actor.colChkInfo.damage = 0x10;
            func_80833B18(play, this, 1, 4.0f, 5.0f, this->actor.shape.rot.y, 20);
        } else {
            func_80836B3C(play, this, 4.0f);
        }
    }
}

void Player_Action_28(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;

    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        func_8082DB60(play, this, &gPlayerAnim_pz_fishswim);
    }

    Math_SmoothStepToS(&this->unk_B86[1], 0, 6, 0x7D0, 0x190);
    if (!func_80840A30(play, this, &this->linearVelocity, 0.0f)) {
        if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
            if (this->unk_AAA > 0x36B0) {
                this->actor.colChkInfo.damage = 0x10;
                func_80833B18(play, this, 1, 4.0f, 5.0f, this->actor.shape.rot.y, 20);
            } else {
                func_80836B3C(play, this, 4.0f);
            }
        } else {
            this->actor.gravity = -1.0f;
            this->unk_AAA = Math_Atan2S_XY(this->actor.speed, -this->actor.velocity.y);
            func_8082F164(this, BTN_R);
        }
    }
}

void Player_Action_29(Player* this, PlayState* play) {
    AttackAnimInfo* attackInfoEntry = &sMeleeAttackAnimInfo[this->meleeWeaponAnimation];
    f32 speedTarget;
    s16 yawTarget;

    this->stateFlags2 |= PLAYER_STATE2_20;

    if (this->transformation == PLAYER_FORM_ZORA) {
        this->actor.gravity = -0.8f;
    } else {
        this->actor.gravity = -1.2f;
    }

    PlayerAnimation_Update(play, &this->skelAnime);

    if (!func_808401F4(play, this)) {
        func_8083FCF0(play, this, 6.0f, attackInfoEntry->unk_C, attackInfoEntry->unk_D);
        if (!(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
            Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);
            func_8083CBC4(this, speedTarget, this->currentYaw, 1.0f, 0.05f, 0.1f, 200);
        } else if (func_80836F10(play, this) >= 0) { // Player didn't die because of this fall
            this->meleeWeaponAnimation += 3;
            func_80833864(play, this, this->meleeWeaponAnimation);
            this->unk_ADD = 3;
            this->meleeWeaponState = PLAYER_MELEE_WEAPON_STATE_0;
            Player_AnimSfx_PlayFloorLand(this);
        }
    }
}

void Player_Action_30(Player* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;
    s32 temp_v0;

    this->stateFlags1 |= PLAYER_STATE1_1000;
    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        func_8082E794(this);
        func_8083133C(this);
        this->stateFlags1 &= ~PLAYER_STATE1_20000;
        Player_AnimationPlayLoop(play, this, D_8085CF60[Player_IsHoldingTwoHandedWeapon(this)]);
        this->actionVar2 = -1;
    }

    func_80832F24(this);
    if (!func_8083FE38(this, play) && (this->actionVar2 != 0)) {
        func_80840F34(this);
        if (this->actionVar2 < 0) {
            if (this->unk_B08 >= 0.1f) {
                this->unk_ADD = 0;
                this->actionVar2 = 1;
            } else if (!CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_B)) {
                func_80840E5C(this, play);
            }
        } else if (!func_80840CD4(this, play)) {
            Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);
            temp_v0 = func_8083E7F8(this, &speedTarget, &yawTarget, play);
            if (temp_v0 > 0) {
                func_80840DEC(this, play);
            } else if (temp_v0 < 0) {
                func_80840E24(this, play);
            }
        }
    }
}

void Player_Action_31(Player* this, PlayState* play) {
    s32 var_v1;
    s32 temp_v0_2;
    f32 temp_ft4;
    f32 var_fa0;
    f32 speedTarget;
    s16 yawTarget;
    s16 temp_v0;
    f32 temp_fv1;
    s32 pad;
    s32 sp44;

    temp_v0 = this->currentYaw - this->actor.shape.rot.y;
    var_v1 = ABS_ALT(temp_v0);

    temp_ft4 = fabsf(this->linearVelocity);
    this->stateFlags1 |= PLAYER_STATE1_1000;

    var_fa0 = temp_ft4 * 1.5f;
    var_fa0 = CLAMP_MIN(var_fa0, 1.5f);

    var_fa0 = ((var_v1 < 0x4000) ? -1.0f : 1.0f) * var_fa0;

    func_8083EA44(this, var_fa0);

    var_fa0 = CLAMP(temp_ft4 * 0.5f, 0.5f, 1.0f);

    PlayerAnimation_BlendToJoint(play, &this->skelAnime, D_8085CF60[Player_IsHoldingTwoHandedWeapon(this)], 0.0f,
                                 D_8085CF70[Player_IsHoldingTwoHandedWeapon(this)], this->unk_B38 * 0.7241379f, var_fa0,
                                 this->blendTableBuffer);
    if (!func_8083FE38(this, play) && !func_80840CD4(this, play)) {
        func_80840F34(this);
        Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);

        temp_v0_2 = func_8083E7F8(this, &speedTarget, &yawTarget, play);
        if (temp_v0_2 < 0) {
            func_80840E24(this, play);
            return;
        }

        if (temp_v0_2 == 0) {
            speedTarget = 0.0f;
            yawTarget = this->currentYaw;
        }

        sp44 = ABS_ALT(BINANG_SUB(yawTarget, this->currentYaw));
        if (sp44 > 0x4000) {
            if (Math_StepToF(&this->linearVelocity, 0.0f, 1.0f)) {
                this->currentYaw = yawTarget;
            }
        } else {
            Math_AsymStepToF(&this->linearVelocity, speedTarget * 0.2f, 1.0f, 0.5f);
            Math_ScaledStepToS(&this->currentYaw, yawTarget, sp44 * 0.1f);
            if ((speedTarget == 0.0f) && (this->linearVelocity == 0.0f)) {
                func_80840EC0(this, play);
            }
        }
    }
}

void Player_Action_32(Player* this, PlayState* play) {
    f32 sp5C = fabsf(this->linearVelocity);
    f32 var_fa0;

    this->stateFlags1 |= PLAYER_STATE1_1000;

    if (sp5C == 0.0f) {
        sp5C = ABS_ALT(this->unk_B4C) * 0.0015f;
        if (sp5C < 400.0f) {
            sp5C = 0.0f;
        }

        func_8083EA44(this, ((this->unk_B4C >= 0) ? 1 : -1) * sp5C);
    } else {
        var_fa0 = sp5C * 1.5f;
        var_fa0 = CLAMP_MIN(var_fa0, 1.5f);
        func_8083EA44(this, var_fa0);
    }

    var_fa0 = CLAMP(sp5C * 0.5f, 0.5f, 1.0f);

    PlayerAnimation_BlendToJoint(play, &this->skelAnime, D_8085CF60[Player_IsHoldingTwoHandedWeapon(this)], 0.0f,
                                 D_8085CF78[Player_IsHoldingTwoHandedWeapon(this)], this->unk_B38 * 0.7241379f, var_fa0,
                                 this->blendTableBuffer);
    if (!func_8083FE38(this, play) && !func_80840CD4(this, play)) {
        f32 speedTarget;
        s16 yawTarget;
        s32 temp_v0;
        s16 temp_v0_2;
        s32 var_v1;

        func_80840F34(this);
        Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);
        temp_v0 = func_8083E7F8(this, &speedTarget, &yawTarget, play);
        if (temp_v0 > 0) {
            func_80840DEC(this, play);
            return;
        }

        if (temp_v0 == 0) {
            speedTarget = 0.0f;
            yawTarget = this->currentYaw;
        }

        var_v1 = ABS_ALT(BINANG_SUB(yawTarget, this->currentYaw));
        if (var_v1 > 0x4000) {
            if (Math_StepToF(&this->linearVelocity, 0.0f, 1.0f)) {
                this->currentYaw = yawTarget;
            }
        } else {
            Math_AsymStepToF(&this->linearVelocity, speedTarget * 0.2f, 1.0f, 0.5f);
            Math_ScaledStepToS(&this->currentYaw, yawTarget, var_v1 * 0.1f);
            if ((speedTarget == 0.0f) && (this->linearVelocity == 0.0f) && (sp5C == 0.0f)) {
                func_80840EC0(this, play);
            }
        }
    }
}

void Player_Action_33(Player* this, PlayState* play) {
    s32 animFinished;
    f32 frame;
    s32 temp_v0;

    this->stateFlags2 |= PLAYER_STATE2_20;
    animFinished = PlayerAnimation_Update(play, &this->skelAnime);

    if (this->skelAnime.animation == &gPlayerAnim_link_normal_250jump_start) {
        this->linearVelocity = 1.0f;
        if (PlayerAnimation_OnFrame(&this->skelAnime, 8.0f)) {
            f32 speed = this->yDistToLedge;

            speed = CLAMP_MAX(speed, this->ageProperties->unk_0C);
            if (this->stateFlags1 & PLAYER_STATE1_8000000) {
                speed *= 0.085f;
            } else {
                speed *= 0.072f;
            }

            if (this->transformation == PLAYER_FORM_HUMAN) {
                speed += 1.0f;
            }

            func_80834D50(play, this, NULL, speed, NA_SE_VO_LI_AUTO_JUMP);
            this->actionVar2 = -1;
        }
    } else {
        temp_v0 = func_808331FC(play, this, &this->skelAnime, 4.0f);
        if (temp_v0 == 0) {
            this->stateFlags1 &= ~(PLAYER_STATE1_4 | PLAYER_STATE1_4000 | PLAYER_STATE1_40000);
            return;
        }
        if (animFinished || (temp_v0 > 0)) {
            func_80839E74(this, play);
            this->stateFlags1 &= ~(PLAYER_STATE1_4 | PLAYER_STATE1_4000 | PLAYER_STATE1_40000);
            this->unk_ABC = 0.0f;
            return;
        }

        frame = 0.0f;
        if (this->skelAnime.animation == &gPlayerAnim_link_swimer_swim_15step_up) {
            if (PlayerAnimation_OnFrame(&this->skelAnime, 30.0f)) {
                func_8083B32C(play, this, 10.0f);
            }
            frame = 50.0f;
        } else if (this->skelAnime.animation == &gPlayerAnim_link_normal_150step_up) {
            frame = 30.0f;
        } else if (this->skelAnime.animation == &gPlayerAnim_link_normal_100step_up) {
            frame = 16.0f;
        }

        if (PlayerAnimation_OnFrame(&this->skelAnime, frame)) {
            Player_AnimSfx_PlayFloorLand(this);
            Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_CLIMB_END);
        }

        if ((this->skelAnime.animation == &gPlayerAnim_link_normal_100step_up) || (this->skelAnime.curFrame > 5.0f)) {
            if (this->actionVar2 == 0) {
                Player_AnimSfx_PlayFloorJump(this);
                this->actionVar2 = 1;
            }
            Math_SmoothStepToF(&this->unk_ABC, 0.0f, 0.1f, 400.0f, 150.0f);
        }
    }
}

void Player_Action_34(Player* this, PlayState* play) {
    s32 temp_v0;

    this->stateFlags2 |= (PLAYER_STATE2_20 | PLAYER_STATE2_40);
    if (this->unk_D58 == func_80837BF8) {
        this->stateFlags2 |= PLAYER_STATE2_1;
    }

    PlayerAnimation_Update(play, &this->skelAnime);
    func_8083249C(this);

    temp_v0 = Player_UpdateUpperBody(this, play);
    if (((this->stateFlags1 & PLAYER_STATE1_800) && (this->heldActor != NULL) && (this->getItemId == GI_NONE)) ||
        !temp_v0) {
        this->unk_D58(play, this);
    }
}

void Player_Action_35(Player* this, PlayState* play) {
    if (!Player_ActionChange_13(this, play)) {
        if ((this->stateFlags3 & PLAYER_STATE3_10) && !(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
            func_80833AA0(this, play);
            this->stateFlags1 |= PLAYER_STATE1_20000000;
        } else if (this->actionVar2 == 0) {
            PlayerAnimation_Update(play, &this->skelAnime);
            if (DECR(this->doorTimer) == 0) {
                this->linearVelocity = 0.1f;
                this->actionVar2 = 1;
            }
        } else if (this->actionVar1 == 0) {
            f32 sp6C = 5.0f * D_8085C3E4;
            s32 var_t0 = func_808411D4(play, this, &sp6C, -1);

            if (this->unk_397 == 4) {
                if (R_PLAY_FILL_SCREEN_ON < 0) {
                    if (play->roomCtx.status != 1) {
                        R_PLAY_FILL_SCREEN_ALPHA += R_PLAY_FILL_SCREEN_ON;
                        if (R_PLAY_FILL_SCREEN_ALPHA < 0) {
                            R_PLAY_FILL_SCREEN_ALPHA = 0;
                        }

                        this->actor.world.pos.y += (this->doorDirection != 0) ? 3.0f : -3.0f;
                        this->actor.prevPos.y = this->actor.world.pos.y;
                    }
                } else if (R_PLAY_FILL_SCREEN_ON == 0) {
                    CollisionPoly* sp64;
                    s32 sp60;

                    if (func_80835DF8(play, this, &sp64, &sp60)) {
                        this->actor.floorPoly = sp64;
                        this->actor.floorBgId = sp60;
                    }
                }
            }

            if (var_t0 < 0x1E) {
                this->actionVar1 = 1;
                this->stateFlags1 |= PLAYER_STATE1_20000000;
                this->unk_3A0.x = this->unk_3AC.x;
                this->unk_3A0.z = this->unk_3AC.z;
            }
        } else {
            f32 sp5C = 5.0f;
            s32 sp58 = 0x14;
            s32 temp_v0_8;

            if (this->stateFlags1 & PLAYER_STATE1_1) {
                sp5C = gSaveContext.entranceSpeed;
                if (sPlayerConveyorSpeedIndex != CONVEYOR_SPEED_DISABLED) {
                    this->unk_3A0.x = (Math_SinS(sPlayerConveyorYaw) * 400.0f) + this->actor.world.pos.x;
                    this->unk_3A0.z = (Math_CosS(sPlayerConveyorYaw) * 400.0f) + this->actor.world.pos.z;
                }
            } else {
                if (this->actionVar2 < 0) {
                    this->actionVar2++;
                    sp5C = gSaveContext.entranceSpeed;
                    sp58 = -1;
                } else if (this->unk_397 == 4) {
                    if (R_PLAY_FILL_SCREEN_ON == 0) {
                        R_PLAY_FILL_SCREEN_ON = 16;
                        R_PLAY_FILL_SCREEN_ALPHA = 0;

                        R_PLAY_FILL_SCREEN_R = R_PLAY_FILL_SCREEN_G = R_PLAY_FILL_SCREEN_B = R_PLAY_FILL_SCREEN_ALPHA;
                    } else if (R_PLAY_FILL_SCREEN_ON >= 0) {
                        R_PLAY_FILL_SCREEN_ALPHA += R_PLAY_FILL_SCREEN_ON;
                        if (R_PLAY_FILL_SCREEN_ALPHA > 255) {
                            TransitionActorEntry* temp_v1_4; // sp50
                            s32 roomNum;

                            temp_v1_4 = &play->doorCtx.transitionActorList[this->doorNext];
                            roomNum = temp_v1_4->sides[0].room;
                            R_PLAY_FILL_SCREEN_ALPHA = 255;

                            if ((roomNum != play->roomCtx.curRoom.num) && (play->roomCtx.curRoom.num >= 0)) {
                                play->roomCtx.prevRoom = play->roomCtx.curRoom;

                                play->roomCtx.curRoom.num = -1;
                                play->roomCtx.curRoom.segment = NULL;
                                func_8012EBF8(play, &play->roomCtx);
                            } else {
                                static Vec3f D_8085D62C = { 0.0f, 0.0f, 0.0f };
                                static Vec3f D_8085D638 = { 0.0f, 0.0f, 0.0f };
                                static Vec3f D_8085D644 = { 0.0f, 0.0f, 0.0f };

                                R_PLAY_FILL_SCREEN_ON = -16;
                                if (play->roomCtx.curRoom.num < 0) {
                                    Room_StartRoomTransition(play, &play->roomCtx, temp_v1_4->sides[0].room);
                                    play->roomCtx.prevRoom.num = -1;
                                    play->roomCtx.prevRoom.segment = NULL;
                                }

                                this->actor.world.pos.x = temp_v1_4->pos.x;
                                this->actor.world.pos.y = temp_v1_4->pos.y;
                                this->actor.world.pos.z = temp_v1_4->pos.z;

                                this->actor.shape.rot.y = ((((temp_v1_4->rotY >> 7) & 0x1FF) / 180.0f) * 0x8000);

                                D_8085D62C.x = (this->doorDirection != 0) ? -120.0f : 120.0f;
                                D_8085D62C.y = (this->doorDirection != 0) ? -75.0f : 75.0f;
                                D_8085D62C.z = -240.0f;
                                if (this->doorDirection != 0) {
                                    Camera_ChangeDoorCam(play->cameraPtrs[0], &this->actor, -2, 0.0f,
                                                         temp_v1_4->pos.x + 0x32, temp_v1_4->pos.y + 0x5F,
                                                         temp_v1_4->pos.z - 0x32);
                                } else {
                                    Camera_ChangeDoorCam(play->cameraPtrs[0], &this->actor, -2, 0.0f,
                                                         temp_v1_4->pos.x - 0x32, temp_v1_4->pos.y + 5,
                                                         temp_v1_4->pos.z - 0x32);
                                }

                                Player_TranslateAndRotateY(this, &this->actor.world.pos, &D_8085D62C,
                                                           &this->actor.world.pos);

                                D_8085D638.x = (this->doorDirection != 0) ? 130.0f : -130.0f;
                                D_8085D638.z = 160.0f;
                                Player_TranslateAndRotateY(this, &this->actor.world.pos, &D_8085D638, &this->unk_3A0);
                                D_8085D644.z = 160.0f;
                                Player_TranslateAndRotateY(this, &this->unk_3A0, &D_8085D644, &this->unk_3AC);

                                this->actor.shape.rot.y += (this->doorDirection != 0) ? 0x4000 : -0x4000;
                                this->actionVar1 = 0;

                                this->actor.world.rot.y = this->currentYaw = this->actor.shape.rot.y;
                            }
                        }

                        this->actor.world.pos.y += (this->doorDirection != 0) ? 3.0f : -3.0f;
                        this->actor.prevPos.y = this->actor.world.pos.y;
                    }
                }
            }

            temp_v0_8 = func_808411D4(play, this, &sp5C, sp58);
            if ((this->actionVar2 == 0) || ((temp_v0_8 == 0) && (this->linearVelocity == 0.0f) &&
                                            (Play_GetCamera(play, CAM_ID_MAIN)->stateFlags & CAM_STATE_4))) {
                if (this->unk_397 == 4) {
                    Map_InitRoomData(play, play->roomCtx.curRoom.num);
                    Minimap_SavePlayerRoomInitInfo(play);
                }

                R_PLAY_FILL_SCREEN_ON = 0;
                func_800E0238(Play_GetCamera(play, CAM_ID_MAIN));
                Player_StopCutscene(this);
                if (!(this->stateFlags3 & PLAYER_STATE3_20000)) {
                    func_801226E0(play, ((void)0, gSaveContext.respawn[RESPAWN_MODE_DOWN].data));
                }

                if (play->unk_1887C != 0) {
                    play->func_18780(this, play);
                    Player_SetAction(play, this, Player_Action_80, 0);
                    if (play->sceneId == SCENE_20SICHITAI) {
                        play->unk_1887C = 0;
                    }
                } else if (!Player_ActionChange_4(this, play)) {
                    func_8083B2E4(this, play);
                }
            }
        }
    }

    if (this->stateFlags1 & PLAYER_STATE1_800) {
        Player_UpdateUpperBody(this, play);
    }
}

// door stuff
void Player_Action_36(Player* this, PlayState* play) {
    EnDoor* doorActor = (EnDoor*)this->doorActor;
    s32 sp38 = (doorActor != NULL) && (doorActor->doorType == ENDOOR_TYPE_7);
    s32 animFinished;
    CollisionPoly* poly;
    s32 bgId;

    this->stateFlags2 |= PLAYER_STATE2_20;

    if (DECR(this->actionVar1) == 0) {
        func_80835DF8(play, this, &poly, &bgId);
    }

    animFinished = PlayerAnimation_Update(play, &this->skelAnime);
    Player_UpdateUpperBody(this, play);

    if (animFinished) {
        if (this->actionVar2 == 0) {
            if (DECR(this->doorTimer) == 0) {
                this->actionVar2 = 1;
                this->skelAnime.endFrame = this->skelAnime.animLength - 1.0f;
            }
        } else {
            Player_StopCutscene(this);
            func_80839E74(this, play);

            if ((this->actor.category == ACTORCAT_PLAYER) && !sp38) {
                if (play->roomCtx.prevRoom.num >= 0) {
                    func_8012EBF8(play, &play->roomCtx);
                }

                func_800E0238(Play_GetCamera(play, CAM_ID_MAIN));
                Play_SetupRespawnPoint(&play->state, RESPAWN_MODE_DOWN, PLAYER_PARAMS(0xFF, PLAYER_INITMODE_B));
            }
        }
    } else if (!(this->stateFlags1 & PLAYER_STATE1_20000000) && PlayerAnimation_OnFrame(&this->skelAnime, 15.0f)) {
        Player_StopCutscene(this);
        play->func_18780(this, play);
    } else if (sp38 && PlayerAnimation_OnFrame(&this->skelAnime, 15.0f)) {
        s16 exitIndexPlusOne = (this->doorDirection < 0) ? doorActor->knobDoor.dyna.actor.world.rot.x
                                                         : doorActor->knobDoor.dyna.actor.world.rot.z;

        if (exitIndexPlusOne != 0) {
            func_808354A4(play, exitIndexPlusOne - 1, false);
        }
    }
}

// grab/hold an actor (?)
void Player_Action_37(Player* this, PlayState* play) {
    func_80832F24(this);

    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        func_80836988(this, play);
        func_808313F0(this, play);
    } else if (PlayerAnimation_OnFrame(&this->skelAnime, 4.0f)) {
        Actor* interactRangeActor = this->interactRangeActor;

        if (!func_808313A8(play, this, interactRangeActor)) {
            this->actor.child = interactRangeActor;
            this->heldActor = interactRangeActor;
            interactRangeActor->parent = &this->actor;
            interactRangeActor->bgCheckFlags &=
                ~(BGCHECKFLAG_GROUND | BGCHECKFLAG_GROUND_TOUCH | BGCHECKFLAG_GROUND_LEAVE | BGCHECKFLAG_WALL |
                  BGCHECKFLAG_CEILING | BGCHECKFLAG_WATER | BGCHECKFLAG_WATER_TOUCH | BGCHECKFLAG_GROUND_STRICT);
            this->leftHandWorld.rot.y = interactRangeActor->shape.rot.y - this->actor.shape.rot.y;
        }
    } else {
        Math_ScaledStepToS(&this->leftHandWorld.rot.y, 0, 0xFA0);
    }
}

// grab/hold an actor (?)
void Player_Action_38(Player* this, PlayState* play) {
    func_80832F24(this);

    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        Player_AnimationPlayLoop(play, this, &gPlayerAnim_link_silver_wait);
        this->actionVar2 = 1;
    } else if (this->actionVar2 == 0) {
        if (PlayerAnimation_OnFrame(&this->skelAnime, 27.0f)) {
            Actor* interactRangeActor = this->interactRangeActor;

            this->heldActor = interactRangeActor;
            this->actor.child = interactRangeActor;
            interactRangeActor->parent = &this->actor;
        } else if (PlayerAnimation_OnFrame(&this->skelAnime, 25.0f)) {
            Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_SWORD_L);
        }
    } else if (CHECK_BTN_ANY(sPlayerControlInput->press.button, BTN_CRIGHT | BTN_CLEFT | BTN_CDOWN | BTN_B | BTN_A)) {
        Player_SetAction(play, this, Player_Action_39, 1);
        Player_AnimationPlayOnce(play, this, &gPlayerAnim_link_silver_throw);
    }
}

// throw held actor (?)
void Player_Action_39(Player* this, PlayState* play) {
    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        func_80836988(this, play);
    } else if (PlayerAnimation_OnFrame(&this->skelAnime, 6.0f)) {
        Actor* heldActor = this->heldActor;

        heldActor->world.rot.y = this->actor.shape.rot.y;
        heldActor->speed = 10.0f;
        heldActor->velocity.y = 20.0f;
        func_808309CC(play, this);
        Player_PlaySfx(this, NA_SE_PL_THROW);
        Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_SWORD_N);
    }
}

void Player_Action_40(Player* this, PlayState* play) {
    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        Player_AnimationPlayLoop(play, this, &gPlayerAnim_link_normal_nocarry_free_wait);
        this->actionVar2 = 15;
    } else if (this->actionVar2 != 0) {
        this->actionVar2--;
        if (this->actionVar2 == 0) {
            func_80836A98(this, &gPlayerAnim_link_normal_nocarry_free_end, play);
            this->stateFlags1 &= ~PLAYER_STATE1_800;
            Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_DAMAGE_S);
        }
    }
}

// Player_Action_PutDownObject?
void Player_Action_41(Player* this, PlayState* play) {
    func_80832F24(this);

    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        func_80836988(this, play);
    } else if (PlayerAnimation_OnFrame(&this->skelAnime, 4.0f)) {
        Actor* heldActor = this->heldActor;

        if (!func_808313A8(play, this, heldActor)) {
            heldActor->velocity.y = 0.0f;
            heldActor->speed = 0.0f;
            func_808309CC(play, this);
            if (heldActor->id == ACTOR_EN_BOM_CHU) {
                func_80831814(this, play, PLAYER_UNKAA5_0);
            }
        }
    }
}

// Player_Action_Throwing
void Player_Action_42(Player* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    func_80832F24(this);

    if (PlayerAnimation_Update(play, &this->skelAnime) ||
        ((this->skelAnime.curFrame >= 8.0f) &&
         Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_CURVED, play))) {
        func_80836988(this, play);
    } else if (PlayerAnimation_OnFrame(&this->skelAnime, 3.0f)) {
        func_808409A8(play, this, this->linearVelocity + 8.0f, 12.0f);
    }
}

void Player_Action_43(Player* this, PlayState* play) {
    if (this->stateFlags1 & PLAYER_STATE1_8000000) {
        func_808475B4(this);
        func_8084748C(this, &this->linearVelocity, 0.0f, this->actor.shape.rot.y);
    } else {
        func_80832F24(this);
    }

    if (this->unk_AA5 == PLAYER_UNKAA5_3) {
        if (func_800B7118(this) || func_8082ECCC(this)) {
            Player_UpdateUpperBody(this, play);
        }
    }

    if (((this->unk_AA5 == PLAYER_UNKAA5_2) && !(play->actorCtx.flags & ACTORCTX_FLAG_PICTO_BOX_ON)) ||
        ((this->unk_AA5 != PLAYER_UNKAA5_2) &&
         ((((this->csMode != PLAYER_CSMODE_NONE) || ((u32)this->unk_AA5 == PLAYER_UNKAA5_0) ||
            (this->unk_AA5 >= PLAYER_UNKAA5_5) || func_8082FB68(this) || (this->lockOnActor != NULL) ||
            (func_8083868C(play, this) == CAM_MODE_NORMAL) ||
            ((this->unk_AA5 == PLAYER_UNKAA5_3) &&
             (((Player_ItemToItemAction(this, Inventory_GetBtnBItem(play)) != this->heldItemAction) &&
               CHECK_BTN_ANY(sPlayerControlInput->press.button, BTN_B)) ||
              CHECK_BTN_ANY(sPlayerControlInput->press.button, BTN_R | BTN_A) || func_80123434(this) ||
              (!func_800B7128(this) && !func_8082EF20(this))))) ||
           ((this->unk_AA5 == PLAYER_UNKAA5_1) &&
            CHECK_BTN_ANY(sPlayerControlInput->press.button,
                          BTN_CRIGHT | BTN_CLEFT | BTN_CDOWN | BTN_CUP | BTN_R | BTN_B | BTN_A))) ||
          Player_ActionChange_4(this, play)))) {
        func_80839ED0(this, play);
        Audio_PlaySfx(NA_SE_SY_CAMERA_ZOOM_UP);
    } else if ((DECR(this->actionVar2) == 0) || (this->unk_AA5 != PLAYER_UNKAA5_3)) {
        if (func_801240DC(this)) {
            this->unk_AA6 |= 0x43;
        } else {
            this->actor.shape.rot.y = func_80847190(play, this, 0);
        }
    }

    this->currentYaw = this->actor.shape.rot.y;
}

void Player_Action_44(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;

    func_8083249C(this);
    Player_UpdateUpperBody(this, play);
    if (Message_GetState(&play->msgCtx) == TEXT_STATE_CLOSING) {
        this->actor.flags &= ~ACTOR_FLAG_TALK_REQUESTED;
        if (!CHECK_FLAG_ALL(this->talkActor->flags, ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY)) {
            this->stateFlags2 &= ~PLAYER_STATE2_2000;
        }

        func_800E0238(Play_GetCamera(play, CAM_ID_MAIN));
        CutsceneManager_Stop(CS_ID_GLOBAL_TALK);
        if (this->stateFlags1 & PLAYER_STATE1_800000) {
            s32 sp44 = this->actionVar2;

            func_80837BD0(play, this);
            this->actionVar2 = sp44;
        } else if (!func_80847994(play, this) && !func_80847880(play, this) && !func_808387A0(play, this) &&
                   ((this->talkActor != this->interactRangeActor) || !Player_ActionChange_2(this, play))) {
            if (func_801242B4(this)) {
                func_808353DC(play, this);
            } else {
                func_8085B384(this, play);
            }
        }

        this->unk_B5E = 0xA;
        return;
    }

    if (this->stateFlags1 & PLAYER_STATE1_800000) {
        Player_Action_52(this, play);
    } else if (func_801242B4(this)) {
        Player_Action_54(this, play);
        if (this->actor.depthInWater > 100.0f) {
            this->actor.velocity.y = 0.0f;
            this->actor.gravity = 0.0f;
        }
    } else if (!func_80123420(this) && PlayerAnimation_Update(play, &this->skelAnime)) {
        if (this->skelAnime.moveFlags != 0) {
            func_8082E794(this);
            if ((this->talkActor->category == ACTORCAT_NPC) && (this->heldItemAction != PLAYER_IA_FISHING_ROD)) {
                func_8082DB90(play, this, &gPlayerAnim_link_normal_talk_free);
            } else {
                Player_AnimationPlayLoop(play, this, func_8082ED20(this));
            }
        } else {
            func_8082DB60(play, this, &gPlayerAnim_link_normal_talk_free_wait);
        }
    }

    if (this->lockOnActor != NULL) {
        this->currentYaw = func_8083C62C(this, false);
        this->actor.shape.rot.y = this->currentYaw;
        if (this->actionVar1 != 0) {
            if (!(this->stateFlags1 & PLAYER_STATE1_800)) {
                if (PlayerAnimation_Update(play, &this->skelAnimeUpper)) {
                    this->actionVar1--;
                    if (this->actionVar1 != 0) {
                        PlayerAnimation_Change(play, &this->skelAnimeUpper, &gPlayerAnim_link_normal_talk_free, 1.0f,
                                               0.0f, Animation_GetLastFrame(&gPlayerAnim_link_normal_talk_free),
                                               ANIMMODE_ONCE, -6.0f);
                    }
                }
            }
            AnimationContext_SetCopyFalse(play, this->skelAnime.limbCount, this->skelAnime.jointTable,
                                          this->skelAnimeUpper.jointTable, sPlayerUpperBodyLimbCopyMap);
        } else if (!(this->stateFlags1 & PLAYER_STATE1_800) &&
                   (this->skelAnime.animation == &gPlayerAnim_link_normal_talk_free_wait)) {
            s32 temp_v0 = this->actor.focus.rot.y - this->actor.shape.rot.y;

            if (ABS_ALT(temp_v0) > 0xFA0) {
                PlayerAnimation_Change(
                    play, &this->skelAnimeUpper, D_8085BE84[PLAYER_ANIMGROUP_25][this->modelAnimType], 0.4f, 0.0f,
                    Animation_GetLastFrame(D_8085BE84[PLAYER_ANIMGROUP_25][this->modelAnimType]), ANIMMODE_ONCE, -6.0f);
                this->actionVar1 = 2;
            }
        }
    }
}

void Player_Action_45(Player* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;
    s32 temp_v0;

    this->stateFlags2 |= (PLAYER_STATE2_1 | PLAYER_STATE2_40 | PLAYER_STATE2_100);
    func_8083DEE4(play, this);

    if (PlayerAnimation_Update(play, &this->skelAnime) && !func_8083E14C(play, this)) {
        Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);
        temp_v0 = func_8083E758(this, &speedTarget, &yawTarget);
        if (temp_v0 > 0) {
            func_8083E234(this, play);
        } else if (temp_v0 < 0) {
            func_8083E28C(this, play);
        }
    }
}

AnimSfxEntry D_8085D650[] = {
    ANIMSFX(ANIMSFX_TYPE_FLOOR, 3, NA_SE_PL_SLIP, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_FLOOR, 21, NA_SE_PL_SLIP, STOP),
};

void Player_Action_46(Player* this, PlayState* play) {
    this->stateFlags2 |= (PLAYER_STATE2_1 | PLAYER_STATE2_40 | PLAYER_STATE2_100);

    if (func_8082E67C(play, this, &gPlayerAnim_link_normal_pushing)) {
        this->actionVar2 = 1;
    } else if ((this->actionVar2 == 0) && PlayerAnimation_OnFrame(&this->skelAnime, 11.0f)) {
        Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_PUSH);
    }

    Player_PlayAnimSfx(this, D_8085D650);
    func_8083DEE4(play, this);

    if (!func_8083E14C(play, this)) {
        f32 speedTarget;
        s16 yawTarget;
        s32 temp_v0;

        Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);
        temp_v0 = func_8083E758(this, &speedTarget, &yawTarget);
        if (temp_v0 < 0) {
            func_8083E28C(this, play);
        } else if (temp_v0 == 0) {
            func_8083DF38(this, &gPlayerAnim_link_normal_push_end, play);
        } else {
            this->stateFlags2 |= PLAYER_STATE2_10;
        }
    }

    if (this->stateFlags2 & PLAYER_STATE2_10) {
        func_808479F4(play, this, 2.0f);
        this->linearVelocity = 2.0f;
    }
}

AnimSfxEntry D_8085D658[] = {
    ANIMSFX(ANIMSFX_TYPE_FLOOR, 4, NA_SE_PL_SLIP, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_FLOOR, 24, NA_SE_PL_SLIP, STOP),
};

Vec3f D_8085D660 = { 0.0f, 268 * 0.1f, -60.0f };

void Player_Action_47(Player* this, PlayState* play) {
    PlayerAnimationHeader* anim = D_8085BE84[PLAYER_ANIMGROUP_35][this->modelAnimType];

    this->stateFlags2 |= (PLAYER_STATE2_1 | PLAYER_STATE2_40 | PLAYER_STATE2_100);

    if (func_8082E67C(play, this, anim)) {
        this->actionVar2 = 1;
    } else if (this->actionVar2 == 0) {
        if (PlayerAnimation_OnFrame(&this->skelAnime, 11.0f)) {
            Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_PUSH);
        }

        //! FAKE
        if (1) {}
    } else {
        Player_PlayAnimSfx(this, D_8085D658);
    }

    func_8083DEE4(play, this);
    if (!func_8083E14C(play, this)) {
        f32 speedTarget;
        s16 yawTarget;
        s32 temp_v0;

        Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);

        temp_v0 = func_8083E758(this, &speedTarget, &yawTarget);
        if (temp_v0 > 0) {
            func_8083E234(this, play);
        } else if (temp_v0 == 0) {
            func_8083DF38(this, D_8085BE84[PLAYER_ANIMGROUP_36][this->modelAnimType], play);
        } else {
            this->stateFlags2 |= PLAYER_STATE2_10;
        }
    }

    if (this->stateFlags2 & PLAYER_STATE2_10) {
        Vec3f sp64;
        f32 yIntersect = func_80835D2C(play, this, &D_8085D660, &sp64) - this->actor.world.pos.y;
        CollisionPoly* poly;
        s32 bgId;
        Vec3f sp4C;
        Vec3f sp40;

        if (fabsf(yIntersect) < 268 * 0.1f) {
            sp64.y -= 7.0f;
            sp4C.x = this->actor.world.pos.x;
            sp4C.z = this->actor.world.pos.z;
            sp4C.y = sp64.y;
            if (!BgCheck_EntityLineTest2(&play->colCtx, &sp4C, &sp64, &sp40, &poly, 1, 0, 0, 1, &bgId, &this->actor)) {
                func_808479F4(play, this, -2.0f);
                return;
            }
        }
        this->stateFlags2 &= ~PLAYER_STATE2_10;
    }
}

void Player_Action_48(Player* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    this->stateFlags2 |= PLAYER_STATE2_40;

    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        Player_AnimationPlayLoop(play, this,
                                 (this->actionVar1 > 0) ? &gPlayerAnim_link_normal_fall_wait
                                                        : D_8085BE84[PLAYER_ANIMGROUP_39][this->modelAnimType]);
    } else if (this->actionVar1 == 0) {
        f32 frame;

        if (this->skelAnime.animation == &gPlayerAnim_link_normal_fall) {
            frame = 11.0f;
        } else {
            frame = 1.0f;
        }

        if (PlayerAnimation_OnFrame(&this->skelAnime, frame)) {
            Player_AnimSfx_PlayFloor(this, NA_SE_PL_WALK_GROUND);
            if (this->skelAnime.animation == &gPlayerAnim_link_normal_fall) {
                this->actionVar1 = 1;
            } else {
                this->actionVar1 = -1;
            }
        }
    }

    Math_ScaledStepToS(&this->actor.shape.rot.y, this->currentYaw, 0x800);
    if (this->actionVar1 != 0) {
        Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);
        if (this->unk_ADF[this->unk_ADE] >= 0) {
            func_808381A0(this,
                          (this->actionVar1 > 0) ? D_8085BE84[PLAYER_ANIMGROUP_37][this->modelAnimType]
                                                 : D_8085BE84[PLAYER_ANIMGROUP_40][this->modelAnimType],
                          play);
        } else if (CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_A) || (this->actor.shape.feetFloorFlags != 0)) {
            func_80833A64(this);

            if (this->actionVar1 < 0) {
                this->linearVelocity = -0.8f;
            } else {
                this->linearVelocity = 0.8f;
            }

            func_80833AA0(this, play);
            this->stateFlags1 &= ~(PLAYER_STATE1_4 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000);
            this->actor.bgCheckFlags &= ~BGCHECKFLAG_GROUND;
        }
    }
}

void Player_Action_49(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_40;

    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        this->currentYaw = this->skelAnime.jointTable[PLAYER_LIMB_WAIST - 1].y + this->actor.shape.rot.y;
        func_8082E820(this, 1);
        this->actor.shape.rot.y = this->currentYaw;
        func_80839E74(this, play);
        this->stateFlags1 &= ~(PLAYER_STATE1_4 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000);
    } else if (PlayerAnimation_OnFrame(&this->skelAnime, this->skelAnime.endFrame - 6.0f)) {
        Player_AnimSfx_PlayFloorLand(this);
    } else if (PlayerAnimation_OnFrame(&this->skelAnime, this->skelAnime.endFrame - 34.0f)) {
        Player_PlaySfx(this, NA_SE_PL_CLIMB_CLIFF);
        Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_CLIMB_END);
        func_8084C124(play, this);
    }
}

void Player_Action_50(Player* this, PlayState* play) {
    s32 yStick = sPlayerControlInput->rel.stick_y;
    s32 xStick = sPlayerControlInput->rel.stick_x;
    f32 var_fv0;
    f32 var_fv1;
    Vec3f sp7C;
    s32 sp78;
    Vec3f sp6C;
    Vec3f sp60;
    DynaPolyActor* dyna;
    PlayerAnimationHeader* anim1;
    PlayerAnimationHeader* anim2;

    this->fallStartHeight = this->actor.world.pos.y;

    this->stateFlags2 |= PLAYER_STATE2_40;

    if ((this->actionVar1 != 0) && (ABS_ALT(yStick) < ABS_ALT(xStick))) {
        var_fv0 = ABS_ALT(xStick) * 0.0325f;
        yStick = 0;
    } else {
        var_fv0 = ABS_ALT(yStick) * 0.05f;
        xStick = 0;
    }

    if (var_fv0 < 1.0f) {
        var_fv0 = 1.0f;
    } else if (var_fv0 > 3.35f) {
        var_fv0 = 3.35f;
    }

    if (this->skelAnime.playSpeed >= 0.0f) {
        var_fv1 = 1.0f;
    } else {
        var_fv1 = -1.0f;
    }

    this->skelAnime.playSpeed = var_fv1 * var_fv0;

    if (this->actionVar2 >= 0) {
        if ((this->actor.wallPoly != NULL) && (this->actor.wallBgId != BGCHECK_SCENE)) {
            dyna = DynaPoly_GetActor(&play->colCtx, this->actor.wallBgId);

            if (dyna != NULL) {
                Math_Vec3f_Diff(&dyna->actor.world.pos, &dyna->actor.prevPos, &sp7C);
                Math_Vec3f_Sum(&this->actor.world.pos, &sp7C, &this->actor.world.pos);
            }
        }

        Actor_UpdateBgCheckInfo(play, &this->actor, 268 * 0.1f, 6.0f, this->ageProperties->ceilingCheckHeight + 15.0f,
                                UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_4);
        func_8083DD1C(play, this, 268 * 0.1f, this->ageProperties->unk_3C, 50.0f, -20.0f);
    }

    func_80831944(play, this);

    if ((this->actionVar2 < 0) || !func_8083E354(this, play)) {
        if (PlayerAnimation_Update(play, &this->skelAnime)) {
            if (this->actionVar2 < 0) {
                this->actionVar2 = ABS_ALT(this->actionVar2) & 1;
            } else if (yStick != 0) {
                f32 yIntersect;

                sp78 = this->actionVar1 + this->actionVar2;

                if (yStick > 0) {
                    sp6C.x = 0.0f;
                    sp6C.y = this->ageProperties->unk_40;
                    sp6C.z = this->ageProperties->unk_3C + 10.0f;

                    yIntersect = func_80835D2C(play, this, &sp6C, &sp60);

                    if (this->actor.world.pos.y < yIntersect) {
                        if (this->actionVar1 != 0) {
                            this->actor.world.pos.y = yIntersect;
                            this->stateFlags1 &= ~PLAYER_STATE1_200000;
                            func_80837CEC(play, this, this->actor.wallPoly, this->ageProperties->unk_3C,
                                          &gPlayerAnim_link_normal_jump_climb_up_free);
                            this->currentYaw += 0x8000;
                            this->actor.shape.rot.y = this->currentYaw;
                            func_808381A0(this, &gPlayerAnim_link_normal_jump_climb_up_free, play);
                            this->stateFlags1 |= PLAYER_STATE1_4000;
                        } else {
                            func_8083DCC4(this, this->ageProperties->unk_D4[this->actionVar2], play);
                        }
                    } else {
                        this->skelAnime.prevTransl = this->ageProperties->unk_4A[sp78];
                        Player_AnimationPlayOnce(play, this, this->ageProperties->unk_B4[sp78]);
                    }
                } else if ((this->actor.world.pos.y - this->actor.floorHeight) < 15.0f) {
                    if (this->actionVar1 != 0) {
                        func_8083E2F4(this, play);
                    } else {
                        if (this->actionVar2 != 0) {
                            this->skelAnime.prevTransl = this->ageProperties->unk_44;
                        }

                        func_8083DCC4(this, this->ageProperties->unk_CC[this->actionVar2], play);
                        this->actionVar2 = 1;
                    }
                } else {
                    sp78 ^= 1;
                    this->skelAnime.prevTransl = this->ageProperties->unk_62[sp78];
                    anim1 = this->ageProperties->unk_B4[sp78];
                    PlayerAnimation_Change(play, &this->skelAnime, anim1, -1.0f, Animation_GetLastFrame(anim1), 0.0f, 2,
                                           0.0f);
                }

                this->actionVar2 ^= 1;
            } else if ((this->actionVar1 != 0) && (xStick != 0)) {
                anim2 = this->ageProperties->unk_C4[this->actionVar2];

                if (xStick > 0) {
                    this->skelAnime.prevTransl = this->ageProperties->unk_7A[this->actionVar2];
                    Player_AnimationPlayOnce(play, this, anim2);
                } else {
                    this->skelAnime.prevTransl = this->ageProperties->unk_7A[this->actionVar2 + 2];
                    PlayerAnimation_Change(play, &this->skelAnime, anim2, -1.0f, Animation_GetLastFrame(anim2), 0.0f, 2,
                                           0.0f);
                }
            } else {
                this->stateFlags2 |= PLAYER_STATE2_1000;
            }

            return;
        }
    }

    if (this->actionVar2 < 0) {
        if (((this->actionVar2 == -2) &&
             (PlayerAnimation_OnFrame(&this->skelAnime, 14.0f) || PlayerAnimation_OnFrame(&this->skelAnime, 29.0f))) ||
            ((this->actionVar2 == -4) &&
             (PlayerAnimation_OnFrame(&this->skelAnime, 22.0f) || PlayerAnimation_OnFrame(&this->skelAnime, 35.0f) ||
              PlayerAnimation_OnFrame(&this->skelAnime, 49.0f) || PlayerAnimation_OnFrame(&this->skelAnime, 55.0f)))) {
            func_80847A50(this);
        }
    } else if (PlayerAnimation_OnFrame(&this->skelAnime, (this->skelAnime.playSpeed > 0.0f) ? 20.0f : 0.0f)) {
        func_80847A50(this);
    }
}

f32 D_8085D66C[] = { 11.0f, 21.0f };
f32 D_8085D674[] = { 40.0f, 50.0f };

AnimSfxEntry D_8085D67C[] = {
    ANIMSFX(ANIMSFX_TYPE_SURFACE, 10, NA_SE_PL_WALK_LADDER, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_SURFACE, 20, NA_SE_PL_WALK_LADDER, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_SURFACE, 30, NA_SE_PL_WALK_LADDER, STOP),
};

void Player_Action_51(Player* this, PlayState* play) {
    s32 temp_v0;

    this->stateFlags2 |= PLAYER_STATE2_40;

    temp_v0 = func_808331FC(play, this, &this->skelAnime, 4.0f);
    if (temp_v0 == 0) {
        this->stateFlags1 &= ~PLAYER_STATE1_200000;
    } else if ((temp_v0 > 0) || PlayerAnimation_Update(play, &this->skelAnime)) {
        func_80839E74(this, play);
        this->stateFlags1 &= ~PLAYER_STATE1_200000;
    } else {
        f32* var_v1 = D_8085D66C;

        if (this->actionVar2 != 0) {
            Player_PlayAnimSfx(this, D_8085D67C);
            var_v1 = D_8085D674;
        }

        if (PlayerAnimation_OnFrame(&this->skelAnime, var_v1[0]) ||
            PlayerAnimation_OnFrame(&this->skelAnime, var_v1[1])) {
            CollisionPoly* poly;
            s32 bgId;
            Vec3f pos;

            pos.x = this->actor.world.pos.x;
            pos.y = this->actor.world.pos.y + 20.0f;
            pos.z = this->actor.world.pos.z;
            if (BgCheck_EntityRaycastFloor5(&play->colCtx, &poly, &bgId, &this->actor, &pos) != 0.0f) {
                this->floorSfxOffset = SurfaceType_GetSfxOffset(&play->colCtx, poly, bgId);
                Player_AnimSfx_PlayFloorLand(this);
            }
        }
    }
}

void func_8084FD7C(PlayState* play, Player* this, Actor* actor) {
    s16 var_a3;

    if (this->unk_B86[0] != 0) {
        this->unk_B86[0]--;
        return;
    }

    this->upperLimbRot.y = func_80847190(play, this, 1) - this->actor.shape.rot.y;

    var_a3 = ABS_ALT(this->upperLimbRot.y) - 0x4000;
    if (var_a3 > 0) {
        var_a3 = CLAMP_MAX(var_a3, 0x15E);
        actor->shape.rot.y += var_a3 * ((this->upperLimbRot.y >= 0) ? 1 : -1);
        actor->world.rot.y = actor->shape.rot.y;
    }

    this->upperLimbRot.y += 0x2710;
    this->unk_AA8 = -0x1388;
}

s32 func_8084FE48(Player* this) {
    return (this->lockOnActor == NULL) && !func_8082FC24(this);
}

PlayerAnimationHeader* D_8085D688[] = {
    &gPlayerAnim_link_uma_anim_stop,    &gPlayerAnim_link_uma_anim_stand,   &gPlayerAnim_link_uma_anim_walk,
    &gPlayerAnim_link_uma_anim_slowrun, &gPlayerAnim_link_uma_anim_fastrun, &gPlayerAnim_link_uma_anim_jump100,
    &gPlayerAnim_link_uma_anim_jump200,
};

PlayerAnimationHeader* D_8085D6A4[] = {
    NULL,
    NULL,
    &gPlayerAnim_link_uma_anim_walk_muti,
    &gPlayerAnim_link_uma_anim_walk_muti,
    &gPlayerAnim_link_uma_anim_walk_muti,
    &gPlayerAnim_link_uma_anim_slowrun_muti,
    &gPlayerAnim_link_uma_anim_fastrun_muti,
    &gPlayerAnim_link_uma_anim_fastrun_muti,
    &gPlayerAnim_link_uma_anim_fastrun_muti,
    NULL,
    NULL,
};

PlayerAnimationHeader* D_8085D6D0[] = {
    &gPlayerAnim_link_uma_wait_3,
    &gPlayerAnim_link_uma_wait_1,
    &gPlayerAnim_link_uma_wait_2,
};

u8 D_8085D6DC[][2] = {
    { 32, 58 },
    { 25, 42 },
};

Vec3s D_8085D6E0 = { -0x45, 0x1BEA, -0x10A };

AnimSfxEntry D_8085D6E8[] = {
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 48, NA_SE_PL_CALM_HIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 58, NA_SE_PL_CALM_HIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 68, NA_SE_PL_CALM_HIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 92, NA_SE_PL_CALM_PAT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 110, NA_SE_PL_CALM_PAT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 126, NA_SE_PL_CALM_PAT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 132, NA_SE_PL_CALM_PAT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 136, NA_SE_PL_CALM_PAT, STOP),
};

void Player_Action_52(Player* this, PlayState* play) {
    EnHorse* rideActor = (EnHorse*)this->rideActor;

    this->stateFlags2 |= PLAYER_STATE2_40;

    func_80847E2C(this, 1.0f, 10.0f);
    if (this->actionVar2 == 0) {
        if (PlayerAnimation_Update(play, &this->skelAnime)) {
            this->skelAnime.animation = &gPlayerAnim_link_uma_wait_1;
            this->actionVar2 = 0x63;
        } else {
            s32 var_v0 = (this->mountSide < 0) ? 0 : 1;

            if (PlayerAnimation_OnFrame(&this->skelAnime, D_8085D6DC[var_v0][0])) {
                Actor_SetCameraHorseSetting(play, this);
                Player_PlaySfx(this, NA_SE_PL_CLIMB_CLIFF);
            } else if (PlayerAnimation_OnFrame(&this->skelAnime, D_8085D6DC[var_v0][1])) {
                Player_PlaySfx(this, NA_SE_PL_SIT_ON_HORSE);
            }
        }
    } else {
        if (rideActor->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
            func_80841A50(play, this);
        }

        Actor_SetCameraHorseSetting(play, this);

        this->skelAnime.prevTransl = D_8085D6E0;

        if ((this->actionVar2 < 0) || ((rideActor->animIndex != (this->actionVar2 & 0xFFFF)) &&
                                       ((rideActor->animIndex >= ENHORSE_ANIM_STOPPING) || (this->actionVar2 >= 2)))) {
            s32 animIndex = rideActor->animIndex;

            if (animIndex < ENHORSE_ANIM_STOPPING) {
                f32 temp_fv0 = Rand_ZeroOne();
                s32 index = 0;

                animIndex = ENHORSE_ANIM_WHINNY;
                if (temp_fv0 < 0.1f) {
                    index = 2;
                } else if (temp_fv0 < 0.2f) {
                    index = 1;
                }

                Player_AnimationPlayOnce(play, this, D_8085D6D0[index]);
            } else {
                this->skelAnime.animation = D_8085D688[animIndex - 2];
                if (this->actionVar2 >= 0) {
                    Animation_SetMorph(play, &this->skelAnime, 8.0f);
                }

                if (animIndex < ENHORSE_ANIM_WALK) {
                    func_808309CC(play, this);
                    this->actionVar1 = 0;
                }
            }

            this->actionVar2 = animIndex;
        }

        if (this->actionVar2 == 1) {
            if (D_80862B04 || func_8082DAFC(play)) {
                Player_AnimationPlayOnce(play, this, &gPlayerAnim_link_uma_wait_3);
            } else if (PlayerAnimation_Update(play, &this->skelAnime)) {
                this->actionVar2 = 0x63;
            } else if (this->skelAnime.animation == &gPlayerAnim_link_uma_wait_1) {
                Player_PlayAnimSfx(this, D_8085D6E8);
            }
        } else {
            this->skelAnime.curFrame = rideActor->curFrame;
            PlayerAnimation_AnimateFrame(play, &this->skelAnime);
        }

        AnimationContext_SetCopyAll(play, this->skelAnime.limbCount, this->skelAnime.morphTable,
                                    this->skelAnime.jointTable);

        if ((play->csCtx.state != CS_STATE_IDLE) || (this->csMode != PLAYER_CSMODE_NONE)) {
            this->unk_AA5 = PLAYER_UNKAA5_0;
            this->actionVar1 = 0;
        } else if ((this->actionVar2 < 2) || (this->actionVar2 >= 4)) {
            D_80862B04 = Player_UpdateUpperBody(this, play);
            if (D_80862B04) {
                this->actionVar1 = 0;
            }
        }

        this->actor.world.pos.x = rideActor->actor.world.pos.x + rideActor->riderPos.x;
        this->actor.world.pos.y = rideActor->actor.world.pos.y + rideActor->riderPos.y - 27.0f;
        this->actor.world.pos.z = rideActor->actor.world.pos.z + rideActor->riderPos.z;

        this->currentYaw = this->actor.shape.rot.y = rideActor->actor.shape.rot.y;

        if (!D_80862B04) {
            if (this->actionVar1 != 0) {
                if (PlayerAnimation_Update(play, &this->skelAnimeUpper)) {
                    rideActor->stateFlags &= ~ENHORSE_FLAG_8;
                    this->actionVar1 = 0;
                }

                if (this->skelAnimeUpper.animation == &gPlayerAnim_link_uma_stop_muti) {
                    if (PlayerAnimation_OnFrame(&this->skelAnimeUpper, 23.0f)) {
                        Player_PlaySfx(this, NA_SE_IT_LASH);
                        Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_LASH);
                    }

                    AnimationContext_SetCopyAll(play, this->skelAnime.limbCount, this->skelAnime.jointTable,
                                                this->skelAnimeUpper.jointTable);
                } else {
                    if (PlayerAnimation_OnFrame(&this->skelAnimeUpper, 10.0f)) {
                        Player_PlaySfx(this, NA_SE_IT_LASH);
                        Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_LASH);
                    }

                    AnimationContext_SetCopyTrue(play, this->skelAnime.limbCount, this->skelAnime.jointTable,
                                                 this->skelAnimeUpper.jointTable, sPlayerUpperBodyLimbCopyMap);
                }
            } else if (!CHECK_FLAG_ALL(this->actor.flags, 0x100)) {
                PlayerAnimationHeader* anim = NULL;

                if (EN_HORSE_CHECK_3(rideActor)) {
                    anim = &gPlayerAnim_link_uma_stop_muti;
                } else if (EN_HORSE_CHECK_2(rideActor)) {
                    if ((this->actionVar2 >= 2) && (this->actionVar2 != 0x63)) {
                        anim = D_8085D6A4[this->actionVar2];
                    }
                }

                if (anim != NULL) {
                    PlayerAnimation_PlayOnce(play, &this->skelAnimeUpper, anim);
                    this->actionVar1 = 1;
                }
            }
        }

        if (this->stateFlags1 & PLAYER_STATE1_100000) {
            if (CHECK_BTN_ANY(sPlayerControlInput->press.button, BTN_A) || !func_8084FE48(this)) {
                this->unk_AA5 = PLAYER_UNKAA5_0;
                this->stateFlags1 &= ~PLAYER_STATE1_100000;
            } else {
                func_8084FD7C(play, this, &rideActor->actor);
            }
        } else if ((this->csMode != PLAYER_CSMODE_NONE) ||
                   (!func_8082DAFC(play) && ((rideActor->actor.speed != 0.0f) || !Player_ActionChange_4(this, play)) &&
                    !func_80847BF0(this, play) && !Player_ActionChange_13(this, play))) {
            if (this->lockOnActor != NULL) {
                if (func_800B7128(this)) {
                    this->upperLimbRot.y = func_8083C62C(this, true) - this->actor.shape.rot.y;
                    this->upperLimbRot.y = CLAMP(this->upperLimbRot.y, -0x4AAA, 0x4AAA);
                    this->actor.focus.rot.y = this->actor.shape.rot.y + this->upperLimbRot.y;
                    this->upperLimbRot.y += 0xFA0;
                    this->unk_AA6 |= 0x80;
                } else {
                    func_8083C62C(this, false);
                }

                this->unk_AA8 = 0;
            } else if (func_8084FE48(this)) {
                if (func_800B7128(this)) {
                    func_80831010(this, play);
                }

                this->unk_B86[0] = 0xC;
            } else if (func_800B7128(this)) {
                func_8084FD7C(play, this, &rideActor->actor);
            }
        }
    }

    if (this->csMode == PLAYER_CSMODE_END) {
        this->csMode = PLAYER_CSMODE_NONE;
    }
}

AnimSfxEntry D_8085D708[] = {
    ANIMSFX(ANIMSFX_TYPE_FLOOR_LAND, 0, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 10, NA_SE_PL_GET_OFF_HORSE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 25, NA_SE_PL_SLIPDOWN, STOP),
};

void Player_Action_53(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_40;
    func_80847E2C(this, 1.0f, 10.0f);

    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        Actor* rideActor = this->rideActor;

        Camera_ChangeSetting(Play_GetCamera(play, CAM_ID_MAIN), CAM_SET_NORMAL0);
        func_80839E74(this, play);

        this->stateFlags1 &= ~PLAYER_STATE1_800000;
        this->actor.parent = NULL;
        gHorseIsMounted = false;

        if (CHECK_QUEST_ITEM(QUEST_SONG_EPONA) || (DREG(1) != 0)) {
            gSaveContext.save.saveInfo.horseData.sceneId = play->sceneId;
            gSaveContext.save.saveInfo.horseData.pos.x = rideActor->world.pos.x;
            gSaveContext.save.saveInfo.horseData.pos.y = rideActor->world.pos.y;
            gSaveContext.save.saveInfo.horseData.pos.z = rideActor->world.pos.z;
            gSaveContext.save.saveInfo.horseData.yaw = rideActor->shape.rot.y;
        }
    } else {
        if (this->mountSide < 0) {
            D_8085D708[0].flags = ANIMSFX_FLAGS(ANIMSFX_TYPE_FLOOR_LAND, 40, CONTINUE);
        } else {
            D_8085D708[0].flags = ANIMSFX_FLAGS(ANIMSFX_TYPE_FLOOR_LAND, 29, CONTINUE);
        }

        Player_PlayAnimSfx(this, D_8085D708);
    }
}

s32 func_80850734(PlayState* play, Player* this) {
    if ((this->transformation == PLAYER_FORM_ZORA) && (this->windSpeed == 0.0f) &&
        (this->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER) && CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_A)) {
        func_8083B850(play, this);
        this->stateFlags2 |= PLAYER_STATE2_400;
        PlayerAnimation_Change(play, &this->skelAnime, &gPlayerAnim_pz_waterroll, 2.0f / 3.0f, 4.0f,
                               Animation_GetLastFrame(&gPlayerAnim_pz_waterroll), ANIMMODE_ONCE, -6.0f);
        this->actionVar2 = 5;
        this->unk_B86[0] = 0;
        this->unk_B48 = this->linearVelocity;
        this->actor.velocity.y = 0.0f;
        Player_PlaySfx(this, NA_SE_PL_ZORA_SWIM_DASH);
        return true;
    }
    return false;
}

s32 func_80850854(PlayState* play, Player* this) {
    if ((this->transformation == PLAYER_FORM_DEKU) && (this->remainingHopsCounter != 0) &&
        (gSaveContext.save.saveInfo.playerData.health != 0) && (sPlayerControlStickMagnitude != 0.0f)) {
        func_808373F8(play, this, 0);
        return true;
    }
    return false;
}

void Player_Action_54(Player* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    this->stateFlags2 |= PLAYER_STATE2_20;

    func_8082E67C(play, this, &gPlayerAnim_link_swimer_swim_wait);
    func_808475B4(this);

    if (this->actionVar2 != 0) {
        this->actionVar2--;
    }

    func_8082F164(this, BTN_R);

    if (CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_A)) {
        this->actionVar2 = 0;
    }

    if (!func_8082DAFC(play) && !Player_TryActionChangeList(play, this, sPlayerActionChangeList11, true) &&
        !func_8083B3B4(play, this, sPlayerControlInput) && ((this->actionVar2 != 0) || !func_80850734(play, this))) {
        speedTarget = 0.0f;
        yawTarget = this->actor.shape.rot.y;

        if (this->unk_AA5 > PLAYER_UNKAA5_2) {
            this->unk_AA5 = PLAYER_UNKAA5_0;
        }

        if (this->currentBoots >= PLAYER_BOOTS_ZORA_UNDERWATER) {
            if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
                func_80836A98(this, D_8085BE84[PLAYER_ANIMGROUP_14][this->modelAnimType], play);
                Player_AnimSfx_PlayFloorLand(this);
            }
        } else if (!func_80850854(play, this)) {
            Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);

            if (speedTarget != 0.0f) {
                if ((ABS_ALT(BINANG_SUB(this->actor.shape.rot.y, yawTarget)) > 0x6000) &&
                    !Math_StepToF(&this->linearVelocity, 0.0f, 1.0f)) {
                    return;
                }

                if (func_8082FC24(this) || func_80847ED4(this)) {
                    func_80848048(play, this);
                } else {
                    func_8083B73C(play, this, yawTarget);
                }
            }
        }

        func_8084748C(this, &this->linearVelocity, speedTarget, yawTarget);
        func_80847F1C(this);
    }
}

void Player_Action_55(Player* this, PlayState* play) {
    if (!Player_ActionChange_13(this, play)) {
        this->stateFlags2 |= PLAYER_STATE2_20;
        func_808477D0(play, this, NULL, this->linearVelocity);
        func_808475B4(this);

        if (DECR(this->actionVar2) == 0) {
            func_808353DC(play, this);
        }
    }
}

void func_80850BA8(Player* this) {
    this->linearVelocity = Math_CosS(this->unk_AAA) * this->unk_B48;
    this->actor.velocity.y = -Math_SinS(this->unk_AAA) * this->unk_B48;
}

void func_80850BF8(Player* this, f32 arg1) {
    f32 temp_fv0;
    s16 temp_ft0;

    Math_AsymStepToF(&this->unk_B48, arg1, 1.0f, (fabsf(this->unk_B48) * 0.01f) + 0.4f);
    temp_fv0 = Math_CosS(sPlayerControlInput->rel.stick_x * 0x10E);

    temp_ft0 = (((sPlayerControlInput->rel.stick_x >= 0) ? 1 : -1) * (1.0f - temp_fv0) * -1100.0f);
    temp_ft0 = CLAMP(temp_ft0, -0x1F40, 0x1F40);

    this->currentYaw += temp_ft0;
}

void func_80850D20(PlayState* play, Player* this) {
    func_8083F8A8(play, this, 12.0f, -1, 1.0f, 160, 20, true);
}

void Player_Action_56(Player* this, PlayState* play) {
    f32 speedTarget;
    s16 sp42;
    s16 yawTarget;
    s16 sp3E;
    s16 sp3C;
    s16 sp3A;

    this->stateFlags2 |= PLAYER_STATE2_20;

    func_808475B4(this);
    func_8082F164(this, BTN_R);

    if (Player_TryActionChangeList(play, this, sPlayerActionChangeList11, false)) {
        return;
    }

    if (func_8083B3B4(play, this, sPlayerControlInput)) {
        return;
    }

    if (func_80840A30(play, this, &this->linearVelocity, 0.0f)) {
        return;
    }

    speedTarget = 0.0f;

    if (this->actionVar2 != 0) {
        if ((!func_8082DA90(play) && !CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_A)) ||
            (this->currentBoots != PLAYER_BOOTS_ZORA_LAND)) {
            this->unk_B86[0] = 1;
        }

        if (PlayerAnimation_Update(play, &this->skelAnime) && (DECR(this->actionVar2) == 0)) {
            if (this->unk_B86[0] != 0) {
                this->stateFlags3 &= ~PLAYER_STATE3_8000;
                func_8082DB90(play, this, &gPlayerAnim_pz_swimtowait);
            } else {
                func_8082DB60(play, this, &gPlayerAnim_pz_fishswim);
            }
        } else {
            Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);
            Math_ScaledStepToS(&this->currentYaw, yawTarget, 0x640);

            if (this->skelAnime.curFrame >= 13.0f) {
                speedTarget = 12.0f;

                if (PlayerAnimation_OnFrame(&this->skelAnime, 13.0f)) {
                    this->unk_B48 = 16.0f;
                }
                this->stateFlags3 |= PLAYER_STATE3_8000;
            } else {
                speedTarget = 0.0f;
            }
        }

        Math_SmoothStepToS(&this->unk_B86[1], sPlayerControlInput->rel.stick_x * 0xC8, 0xA, 0x3E8, 0x64);
        Math_SmoothStepToS(&this->unk_B8E, this->unk_B86[1], IREG(40) + 1, IREG(41), IREG(42));
    } else if (this->unk_B86[0] == 0) {
        PlayerAnimation_Update(play, &this->skelAnime);

        if ((!func_8082DA90(play) && !CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_A)) ||
            (this->currentBoots != PLAYER_BOOTS_ZORA_LAND) || (this->windSpeed > 9.0f)) {
            this->stateFlags3 &= ~PLAYER_STATE3_8000;
            func_8082DB90(play, this, &gPlayerAnim_pz_swimtowait);
            this->unk_B86[0] = 1;
        } else {
            speedTarget = 9.0f;
            Actor_PlaySfx_FlaggedCentered1(&this->actor, NA_SE_PL_ZORA_SWIM_LV - SFX_FLAG);
        }

        // Y
        sp3E = sPlayerControlInput->rel.stick_y * 0xC8;
        if (this->unk_B8C != 0) {
            this->unk_B8C--;
            sp3E = CLAMP_MAX(sp3E, (s16)(this->floorPitch - 0xFA0));
        }

        if ((this->unk_AAA >= -0x1555) && (this->actor.depthInWater < (this->ageProperties->unk_24 + 10.0f))) {
            sp3E = CLAMP_MIN(sp3E, 0x7D0);
        }
        Math_SmoothStepToS(&this->unk_AAA, sp3E, 4, 0xFA0, 0x190);

        // X
        sp42 = sPlayerControlInput->rel.stick_x * 0x64;
        if (Math_ScaledStepToS(&this->unk_B8A, sp42, 0x384) && (sp42 == 0)) {
            Math_SmoothStepToS(&this->unk_B86[1], 0, 4, 0x5DC, 0x64);
            Math_SmoothStepToS(&this->unk_B8E, this->unk_B86[1], IREG(44) + 1, IREG(45), IREG(46));
        } else {
            sp3C = this->unk_B86[1];
            sp3A = (this->unk_B8A < 0) ? -0x3A98 : 0x3A98;
            this->unk_B86[1] += this->unk_B8A;
            Math_SmoothStepToS(&this->unk_B8E, this->unk_B86[1], IREG(47) + 1, IREG(48), IREG(49));

            if ((ABS_ALT(this->unk_B8A) > 0xFA0) && ((((sp3C + this->unk_B8A) - sp3A) * (sp3C - sp3A)) <= 0)) {
                Player_PlaySfx(this, NA_SE_PL_ZORA_SWIM_ROLL);
            }
        }

        if (sPlayerYDistToFloor < 20.0f) {
            func_80850D20(play, this);
        }
    } else {
        Math_SmoothStepToS(&this->unk_B86[1], 0, 4, 0xFA0, 0x190);
        if ((this->skelAnime.curFrame <= 5.0f) || !func_80850734(play, this)) {
            if (PlayerAnimation_Update(play, &this->skelAnime)) {
                func_808353DC(play, this);
            }
        }

        Player_ResetCylinder(this);
    }

    if ((this->unk_B8C < 8) && (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
        DynaPolyActor* dynaActor;

        if ((this->actor.floorBgId == BGCHECK_SCENE) ||
            ((dynaActor = DynaPoly_GetActor(&play->colCtx, this->actor.floorBgId)) == NULL) ||
            (dynaActor->actor.id != ACTOR_EN_TWIG)) {
            this->unk_AAA += (s16)((-this->floorPitch - this->unk_AAA) * 2);
            this->unk_B8C = 0xF;
        }

        func_80850D20(play, this);
        Player_PlaySfx(this, NA_SE_PL_BODY_BOUND);
    }

    func_80850BF8(this, speedTarget);
    func_80850BA8(this);
}

void Player_Action_57(Player* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;
    s16 sp30;
    s16 var_v0;

    this->stateFlags2 |= PLAYER_STATE2_20;
    func_808475B4(this);
    func_8082F164(this, BTN_R);
    if (!Player_TryActionChangeList(play, this, sPlayerActionChangeList11, true) &&
        !func_8083B3B4(play, this, sPlayerControlInput) && !func_80850854(play, this)) {
        func_808477D0(play, this, sPlayerControlInput, this->linearVelocity);
        if (func_8082DA90(play)) {
            speedTarget = this->linearVelocity;
            yawTarget = this->actor.shape.rot.y;
        } else {
            Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);
        }
        sp30 = this->actor.shape.rot.y - yawTarget;
        if (!func_80850734(play, this)) {
            if (func_8082FC24(this) || func_80847ED4(this)) {
                func_80848048(play, this);
            } else {
                if ((speedTarget == 0.0f) || (ABS_ALT(sp30) > 0x6000) ||
                    (this->currentBoots >= PLAYER_BOOTS_ZORA_UNDERWATER)) {
                    func_808353DC(play, this);
                }
            }
            func_80847FF8(this, &this->linearVelocity, speedTarget, yawTarget);
        }
    }
}

void Player_Action_58(Player* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    func_808477D0(play, this, sPlayerControlInput, this->linearVelocity);
    func_808475B4(this);
    func_8082F164(this, BTN_R);

    if (!Player_TryActionChangeList(play, this, sPlayerActionChangeList11, true) &&
        !func_8083B3B4(play, this, sPlayerControlInput)) {
        Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);

        if (speedTarget == 0.0f) {
            func_808353DC(play, this);
        } else if (!func_8082FC24(this) && !func_80847ED4(this)) {
            func_8083B73C(play, this, yawTarget);
        } else {
            func_80848094(play, this, &speedTarget, &yawTarget);
        }

        func_80847FF8(this, &this->linearVelocity, speedTarget, yawTarget);
    }
}

void Player_Action_59(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;

    this->actor.gravity = 0.0f;
    Player_UpdateUpperBody(this, play);
    func_8082F164(this, BTN_R);

    if (Player_ActionChange_13(this, play)) {
        return;
    }

    if (this->currentBoots >= PLAYER_BOOTS_ZORA_UNDERWATER) {
        func_808353DC(play, this);
    } else if (this->actionVar1 == 0) {
        f32 temp_fv0;

        if (this->actionVar2 == 0) {
            if (PlayerAnimation_Update(play, &this->skelAnime) ||
                ((this->skelAnime.curFrame >= 22.0f) && !CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_A))) {
                func_8083B798(play, this);
            } else if (PlayerAnimation_OnFrame(&this->skelAnime, 20.0f)) {
                this->actor.velocity.y = -2.0f;
            }
            func_80832F24(this);
        } else {
            func_808477D0(play, this, sPlayerControlInput, this->actor.velocity.y);
            this->unk_AAA = 0x3E80;

            if (CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_A) && !Player_ActionChange_2(this, play) &&
                !(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && (this->actor.depthInWater < 120.0f)) {
                func_808481CC(play, this, -2.0f);
            } else {
                this->actionVar1++;
                func_8082E634(play, this, &gPlayerAnim_link_swimer_swim_wait);
            }
        }

        temp_fv0 = (this->actor.depthInWater - this->ageProperties->unk_30) * 0.04f;
        if (temp_fv0 < this->actor.velocity.y) {
            this->actor.velocity.y = temp_fv0;
        }
    } else if (this->actionVar1 == 1) {
        PlayerAnimation_Update(play, &this->skelAnime);
        func_808475B4(this);
        if (this->unk_AAA < 0x2710) {
            this->actionVar1++;
            this->actionVar2 = this->actor.depthInWater;
            func_8082E634(play, this, &gPlayerAnim_link_swimer_swim);
        }
    } else if (!func_8083B3B4(play, this, sPlayerControlInput)) {
        f32 var_fv1 = (this->actionVar2 * 0.018f) + 4.0f;

        if (this->stateFlags1 & PLAYER_STATE1_800) {
            sPlayerControlInput = NULL;
        }

        func_808477D0(play, this, sPlayerControlInput, fabsf(this->actor.velocity.y));
        Math_ScaledStepToS(&this->unk_AAA, -0x2710, 0x320);

        var_fv1 = CLAMP_MAX(var_fv1, 8.0f);
        func_808481CC(play, this, var_fv1);
    }
}

void Player_Action_60(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;

    func_8082F164(this, BTN_R);
    if (((this->stateFlags1 & PLAYER_STATE1_400) || (this->skelAnime.curFrame <= 1.0f) || !func_80850734(play, this)) &&
        PlayerAnimation_Update(play, &this->skelAnime)) {
        if (!(this->stateFlags1 & PLAYER_STATE1_400) || func_808482E0(play, this)) {
            func_80848250(play, this);
            func_808353DC(play, this);
            func_8082DC64(play, this);
        }
    } else {
        if ((this->stateFlags1 & PLAYER_STATE1_400) && PlayerAnimation_OnFrame(&this->skelAnime, 10.0f)) {
            func_8082ECE0(this);
            func_8082DC64(play, this);
        } else if (PlayerAnimation_OnFrame(&this->skelAnime, 5.0f)) {
            Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_BREATH_DRINK);
        }
    }

    func_808475B4(this);
    func_8084748C(this, &this->linearVelocity, 0.0f, this->actor.shape.rot.y);
}

void Player_Action_61(Player* this, PlayState* play) {
    func_808475B4(this);
    Math_StepToF(&this->linearVelocity, 0.0f, 0.4f);
    if (PlayerAnimation_Update(play, &this->skelAnime) && (this->linearVelocity < 10.0f)) {
        func_808353DC(play, this);
    }
}

void Player_Action_62(Player* this, PlayState* play) {
    func_808475B4(this);
    if (PlayerAnimation_Update(play, &this->skelAnime) && (this == GET_PLAYER(play))) {
        func_80840770(play, this);
    }
    func_8084748C(this, &this->linearVelocity, 0.0f, this->actor.shape.rot.y);
}

s32 func_80851C40(PlayState* play, Player* this) {
    return ((play->sceneId == SCENE_MILK_BAR) && Audio_IsSequencePlaying(NA_BGM_BALLAD_OF_THE_WIND_FISH)) ||
           (((play->sceneId != SCENE_MILK_BAR) && (this->csMode == PLAYER_CSMODE_68)) ||
            ((play->msgCtx.msgMode == MSGMODE_SONG_PLAYED) ||
             (play->msgCtx.msgMode == MSGMODE_SETUP_DISPLAY_SONG_PLAYED) ||
             (play->msgCtx.msgMode == MSGMODE_DISPLAY_SONG_PLAYED) ||
             ((play->msgCtx.ocarinaMode != OCARINA_MODE_ACTIVE) &&
              ((this->csMode == PLAYER_CSMODE_5) || (play->msgCtx.ocarinaMode == OCARINA_MODE_EVENT) ||
               play->msgCtx.ocarinaAction == OCARINA_ACTION_FREE_PLAY_DONE))));
}

// Deku playing the pipes? The loops both overwrite unk_AF0[0].y,z and unk_AF0[1].x,y,z
void func_80851D30(PlayState* play, Player* this) {
    f32* var_s0 = &this->unk_AF0[0].y; // TODO: what is going on around here in the struct?
    Vec3f sp50;

    if (func_80851C40(play, this)) {
        s32 i;

        if (this->skelAnime.mode != ANIMMODE_LOOP) {
            func_8082DB60(play, this, D_8085D190[this->transformation]);
        }
        func_80124618(D_801C03A0, this->skelAnime.curFrame, &sp50);

        for (i = 0; i < 5; i++) {
            *var_s0 = sp50.x;
            var_s0++;
        }
    } else if (play->msgCtx.ocarinaMode == OCARINA_MODE_ACTIVE) {
        if (play->msgCtx.ocarinaButtonIndex != OCARINA_BTN_INVALID) {
            var_s0[play->msgCtx.ocarinaButtonIndex] = 1.2f;
            func_8082DB90(play, this, D_8085D190[this->transformation]);
        } else {
            s32 i;

            for (i = 0; i < 5; i++) {
                Math_StepToF(var_s0++, 1.0f, 0.04000001f);
            }
        }
    }
}

void func_80851EAC(Player* this) {
    this->unk_B86[0] = -1;
    this->unk_B86[1] = -1;
    this->unk_B10[0] = 0.0f;
}

struct_8085D714 D_8085D714[] = {
    { 1, &gPlayerAnim_pg_gakkiplayA }, { 1, &gPlayerAnim_pg_gakkiplayL }, { 1, &gPlayerAnim_pg_gakkiplayD },
    { 0, &gPlayerAnim_pg_gakkiplayU }, { 0, &gPlayerAnim_pg_gakkiplayR },
};

void func_80851EC8(PlayState* play, Player* this) {
    struct_8085D714* temp3 = &D_8085D714[play->msgCtx.ocarinaButtonIndex];
    f32* temp2 = &this->unk_B10[play->msgCtx.ocarinaButtonIndex];
    s16* temp_a3 = &this->unk_B86[temp3->unk_0];

    temp_a3[0] = play->msgCtx.ocarinaButtonIndex;
    temp2[0] = 3.0f;
}

void func_80851F18(PlayState* play, Player* this) {
    struct_8085D714* temp;
    f32* temp_v0;
    s32 i;

    i = this->unk_B86[0];
    if (i >= 0) {
        temp = &D_8085D714[i];
        i = 0;
        temp_v0 = &this->unk_B10[this->unk_B86[i]];

        AnimationContext_SetLoadFrame(play, temp->unk_4, *temp_v0, this->skelAnime.limbCount,
                                      this->skelAnime.morphTable);
        AnimationContext_SetCopyTrue(play, this->skelAnime.limbCount, this->skelAnime.jointTable,
                                     this->skelAnime.morphTable, D_8085BA08);
    }
    i = this->unk_B86[1];
    if (i >= 0) {
        temp = &D_8085D714[i];
        i = 1;
        temp_v0 = &this->unk_B10[this->unk_B86[i]];

        AnimationContext_SetLoadFrame(play, temp->unk_4, *temp_v0, this->skelAnime.limbCount,
                                      ALIGN16((uintptr_t)this->blendTableBuffer));
        AnimationContext_SetCopyTrue(play, this->skelAnime.limbCount, this->skelAnime.jointTable,
                                     ALIGN16((uintptr_t)this->blendTableBuffer), D_8085BA20);
    }

    temp_v0 = this->unk_B10;
    for (i = 0; i < 5; i++) {
        *temp_v0 += 1.0f;
        if (*temp_v0 >= 9.0f) {
            *temp_v0 = 8.0f;
            if (this->unk_B86[0] == i) {
                this->unk_B86[0] = -1;
            } else if (this->unk_B86[1] == i) {
                this->unk_B86[1] = -1;
            }
        }
        temp_v0++;
    }
}

// Goron playing the drums?
void func_808521E0(PlayState* play, Player* this) {
    if (func_80851C40(play, this)) {
        if (this->skelAnime.animation != &gPlayerAnim_pg_gakkiplay) {
            func_8082DB60(play, this, &gPlayerAnim_pg_gakkiplay);
        }

        func_80124618(D_801C0490, this->skelAnime.curFrame, &this->unk_AF0[1]);
    } else if (play->msgCtx.ocarinaMode == OCARINA_MODE_ACTIVE) {
        if (play->msgCtx.ocarinaButtonIndex != OCARINA_BTN_INVALID) {
            func_80851EC8(play, this);
        }

        func_80851F18(play, this);
    }
}

// Zora playing the guitar?
void func_80852290(PlayState* play, Player* this) {
    if (func_80851C40(play, this)) {
        if (this->skelAnime.mode != ANIMMODE_LOOP) {
            func_8082DB60(play, this, D_8085D190[this->transformation]);
        }

        this->unk_B8A = 8;
    } else {
        f32 sp3C;
        s16 var_a1_3;
        s16 sp38;

        if ((play->msgCtx.ocarinaMode == OCARINA_MODE_ACTIVE) &&
            (play->msgCtx.ocarinaButtonIndex != OCARINA_BTN_INVALID)) {
            if ((this->unk_A90 != NULL) && (this->unk_A94 < 0.0f)) {
                this->unk_A90->flags |= ACTOR_FLAG_20000000;
                this->unk_A94 = 0.0f;
            }

            func_8082DB90(play, this, D_8085D190[this->transformation]);
            this->unk_B8A = 8;
        }

        sPlayerControlInput = play->state.input;
        Lib_GetControlStickData(&sp3C, &sp38, sPlayerControlInput);

        if (BINANG_ADD(sp38, 0x4000) < 0) {
            sp38 -= 0x8000;
            sp3C = -sp3C;
        }

        if (sp38 < -0x1F40) {
            sp38 = -0x1F40;
        } else if (sp38 > 0x2EE0) {
            sp38 = 0x2EE0;
        }

        var_a1_3 = (sp3C * -100.0f);
        var_a1_3 = CLAMP_MAX(var_a1_3, 0xFA0);
        Math_SmoothStepToS(&this->upperLimbRot.x, var_a1_3, 4, 0x7D0, 0);
        Math_SmoothStepToS(&this->upperLimbRot.y, sp38, 4, 0x7D0, 0);
        this->headLimbRot.x = -this->upperLimbRot.x;
        this->unk_AA6 |= 0xC8;

        var_a1_3 = ABS_ALT(this->upperLimbRot.x);
        if (var_a1_3 < 0x7D0) {
            this->actor.shape.face = 0;
        } else if (var_a1_3 < 0xFA0) {
            this->actor.shape.face = 13;
        } else {
            this->actor.shape.face = 8;
        }
    }

    if (DECR(this->unk_B8A) != 0) {
        this->unk_B86[0] += (s16)(this->upperLimbRot.x * 2.5f);
        this->unk_B86[1] += (s16)(this->upperLimbRot.y * 3.0f);
    } else {
        this->unk_B86[0] = 0;
        this->unk_B86[1] = 0;
    }
}

void func_8085255C(PlayState* play, Player* this) {
    if (this->transformation == PLAYER_FORM_DEKU) {
        func_80851D30(play, this);
    } else if (this->transformation == PLAYER_FORM_GORON) {
        func_808521E0(play, this);
    } else if (this->transformation == PLAYER_FORM_ZORA) {
        func_80852290(play, this);
    }
}

void func_808525C4(PlayState* play, Player* this) {
    if (this->actionVar2++ >= 3) {
        if ((this->transformation == PLAYER_FORM_ZORA) || (this->transformation == PLAYER_FORM_DEKU)) {
            func_8082E5A8(play, this, D_8085D190[this->transformation]);
        } else if (this->transformation == PLAYER_FORM_GORON) {
            func_80851EAC(this);
            func_8082DB60(play, this, &gPlayerAnim_pg_gakkiwait);
        } else {
            func_8082DB60(play, this, D_8085D190[this->transformation]);
        }

        this->unk_B48 = 1.0f;
    }
}

void Player_Action_63(Player* this, PlayState* play) {
    if ((this->unk_AA5 != PLAYER_UNKAA5_4) && ((PlayerAnimation_Update(play, &this->skelAnime) &&
                                                (this->skelAnime.animation == D_8085D17C[this->transformation])) ||
                                               ((this->skelAnime.mode == 0) && (this->actionVar2 == 0)))) {
        func_808525C4(play, this);
        if (!(this->actor.flags & ACTOR_FLAG_20000000) || (this->unk_A90->id == ACTOR_EN_ZOT)) {
            Message_DisplayOcarinaStaff(play, OCARINA_ACTION_FREE_PLAY);
        }
    } else if (this->actionVar2 != 0) {
        if (play->msgCtx.ocarinaMode == OCARINA_MODE_END) {
            play->interfaceCtx.unk_222 = 0;
            CutsceneManager_Stop(play->playerCsIds[PLAYER_CS_ID_ITEM_OCARINA]);
            this->actor.flags &= ~ACTOR_FLAG_20000000;

            if ((this->talkActor != NULL) && (this->talkActor == this->unk_A90) && (this->unk_A94 >= 0.0f)) {
                Player_TalkWithPlayer(play, this->talkActor);
            } else if (this->tatlTextId < 0) {
                this->talkActor = this->tatlActor;
                this->tatlActor->textId = -this->tatlTextId;
                Player_TalkWithPlayer(play, this->talkActor);
            } else if (!Player_ActionChange_13(this, play)) {
                func_80836A5C(this, play);
                Player_AnimationPlayOnceReverse(play, this, D_8085D17C[this->transformation]);
            }
        } else {
            s32 var_v1 = (play->msgCtx.ocarinaMode >= OCARINA_MODE_WARP_TO_GREAT_BAY_COAST) &&
                         (play->msgCtx.ocarinaMode <= OCARINA_MODE_WARP_TO_ENTRANCE);
            s32 pad[2];

            if (var_v1 || (play->msgCtx.ocarinaMode == OCARINA_MODE_APPLY_SOT) ||
                (play->msgCtx.ocarinaMode == OCARINA_MODE_APPLY_DOUBLE_SOT) ||
                (play->msgCtx.ocarinaMode == OCARINA_MODE_APPLY_INV_SOT_FAST) ||
                (play->msgCtx.ocarinaMode == OCARINA_MODE_APPLY_INV_SOT_SLOW)) {
                if (play->msgCtx.ocarinaMode == OCARINA_MODE_APPLY_SOT) {
                    if (!func_8082DA90(play)) {
                        if (gSaveContext.save.saveInfo.playerData.threeDayResetCount == 1) {
                            play->nextEntrance = ENTRANCE(CUTSCENE, 1);
                        } else {
                            play->nextEntrance = ENTRANCE(CUTSCENE, 0);
                        }

                        gSaveContext.nextCutsceneIndex = 0xFFF7;
                        play->transitionTrigger = TRANS_TRIGGER_START;
                    }
                } else {
                    Actor* actor;

                    play->interfaceCtx.unk_222 = 0;
                    CutsceneManager_Stop(play->playerCsIds[PLAYER_CS_ID_ITEM_OCARINA]);
                    this->actor.flags &= ~ACTOR_FLAG_20000000;

                    actor = Actor_Spawn(&play->actorCtx, play, var_v1 ? ACTOR_EN_TEST7 : ACTOR_EN_TEST6,
                                        this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0, 0,
                                        0, play->msgCtx.ocarinaMode);
                    if (actor != NULL) {
                        this->stateFlags1 &= ~PLAYER_STATE1_20000000;
                        this->csMode = PLAYER_CSMODE_NONE;
                        func_8085B28C(play, NULL, PLAYER_CSMODE_19);
                        this->stateFlags1 |= PLAYER_STATE1_10000000 | PLAYER_STATE1_20000000;
                    } else {
                        func_80836A5C(this, play);
                        Player_AnimationPlayOnceReverse(play, this, D_8085D17C[this->transformation]);
                    }
                }
            } else if ((play->msgCtx.ocarinaMode == OCARINA_MODE_EVENT) &&
                       (play->msgCtx.lastPlayedSong == OCARINA_SONG_ELEGY)) {
                play->interfaceCtx.unk_222 = 0;
                CutsceneManager_Stop(play->playerCsIds[PLAYER_CS_ID_ITEM_OCARINA]);

                this->actor.flags &= ~ACTOR_FLAG_20000000;
                Player_SetAction_PreserveItemAction(play, this, Player_Action_88, 0);
                this->stateFlags1 |= PLAYER_STATE1_10000000 | PLAYER_STATE1_20000000;
            } else if (this->unk_AA5 == PLAYER_UNKAA5_4) {
                f32 temp_fa0 = this->skelAnime.jointTable[PLAYER_LIMB_ROOT - 1].x;
                f32 temp_fa1 = this->skelAnime.jointTable[PLAYER_LIMB_ROOT - 1].z;
                f32 var_fv1;

                var_fv1 = sqrtf(SQ(temp_fa0) + SQ(temp_fa1));
                if (var_fv1 != 0.0f) {
                    var_fv1 = (var_fv1 - 100.0f) / var_fv1;
                    var_fv1 = CLAMP_MIN(var_fv1, 0.0f);
                }

                this->skelAnime.jointTable[PLAYER_LIMB_ROOT - 1].x = temp_fa0 * var_fv1;
                this->skelAnime.jointTable[PLAYER_LIMB_ROOT - 1].z = temp_fa1 * var_fv1;
            } else {
                func_8085255C(play, this);
            }
        }
    }
}

void Player_Action_64(Player* this, PlayState* play) {
    func_80832F24(this);

    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        func_80836A98(this, &gPlayerAnim_link_normal_light_bom_end, play);
    } else if (PlayerAnimation_OnFrame(&this->skelAnime, 3.0f)) {
        if (Actor_Spawn(&play->actorCtx, play, ACTOR_EN_ARROW, this->bodyPartsPos[PLAYER_BODYPART_RIGHT_HAND].x,
                        this->bodyPartsPos[PLAYER_BODYPART_RIGHT_HAND].y,
                        this->bodyPartsPos[PLAYER_BODYPART_RIGHT_HAND].z, 0xFA0, this->actor.shape.rot.y, 0,
                        ARROW_TYPE_DEKU_NUT) != NULL) {
            Inventory_ChangeAmmo(ITEM_DEKU_NUT, -1);
            this->unk_D57 = 4;
        }

        Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_SWORD_N);
    }
}

AnimSfxEntry D_8085D73C[] = {
    ANIMSFX(ANIMSFX_TYPE_FLOOR_JUMP, 87, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 87, NA_SE_VO_LI_CLIMB_END, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 69, NA_SE_VO_LI_AUTO_JUMP, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_FLOOR_LAND, 123, NA_SE_NONE, STOP),
};

AnimSfxEntry D_8085D74C[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 13, NA_SE_VO_LI_AUTO_JUMP, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_FLOOR_JUMP, 13, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_FLOOR_LAND, 73, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_FLOOR_LAND, 120, NA_SE_NONE, STOP),
};

void Player_Action_65(Player* this, PlayState* play) {
    func_8083249C(this);

    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        if (this->actionVar2 != 0) {
            if (this->actionVar2 > 1) {
                this->actionVar2--;
            }

            if (func_808482E0(play, this) && (this->actionVar2 == 1)) {
                Player_SetModels(this, Player_ActionToModelGroup(this, this->itemAction));

                if ((this->getItemDrawIdPlusOne == GID_REMAINS_ODOLWA + 1) ||
                    (this->getItemDrawIdPlusOne == GID_REMAINS_GOHT + 1) ||
                    (this->getItemDrawIdPlusOne == GID_REMAINS_GYORG + 1) ||
                    (this->getItemDrawIdPlusOne == GID_REMAINS_TWINMOLD + 1)) {
                    Player_StopCutscene(this);
                    func_80848250(play, this);
                    this->stateFlags1 &= ~PLAYER_STATE1_20000000;
                    func_8085B28C(play, NULL, PLAYER_CSMODE_93);
                } else {
                    s32 var_a2 = ((this->talkActor != NULL) && (this->exchangeItemAction <= PLAYER_IA_MINUS1)) ||
                                 (this->stateFlags3 & PLAYER_STATE3_20);

                    if (var_a2 || (gSaveContext.healthAccumulator == 0)) {
                        Player_StopCutscene(this);
                        if (var_a2) {
                            func_80848250(play, this);
                            this->exchangeItemAction = PLAYER_IA_NONE;
                            if (!func_80847994(play, this)) {
                                Player_TalkWithPlayer(play, this->talkActor);
                            }
                        } else {
                            func_80848294(play, this);
                        }
                    }
                }
            }
        } else {
            func_8082E794(this);

            if ((this->getItemId == GI_STRAY_FAIRY) || (this->getItemId == GI_SKULL_TOKEN) ||
                (this->getItemId == GI_ICE_TRAP)) {
                Player_StopCutscene(this);
                this->stateFlags1 &= ~(PLAYER_STATE1_400 | PLAYER_STATE1_800);
                if (this->getItemId == GI_STRAY_FAIRY) {
                    func_80839E74(this, play);
                } else {
                    this->actor.colChkInfo.damage = 0;
                    func_80833B18(play, this, 3, 0.0f, 0.0f, 0, 20);
                }
            } else {
                if (this->skelAnime.animation == &gPlayerAnim_link_normal_box_kick) {
                    func_8082DB90(play, this,
                                  (this->transformation == PLAYER_FORM_DEKU) ? &gPlayerAnim_pn_getB
                                                                             : &gPlayerAnim_link_demo_get_itemB);
                } else {
                    func_8082DB90(play, this,
                                  (this->transformation == PLAYER_FORM_DEKU) ? &gPlayerAnim_pn_getA
                                                                             : &gPlayerAnim_link_demo_get_itemA);
                }

                func_8082E920(play, this,
                              ANIM_FLAG_1 | ANIM_FLAG_UPDATE_Y | ANIM_FLAG_4 | ANIM_FLAG_8 | ANIM_FLAG_NOMOVE |
                                  ANIM_FLAG_80);
                Player_StopCutscene(this);
                this->csId = play->playerCsIds[PLAYER_CS_ID_ITEM_GET];
                this->actionVar2 = 2;
            }
        }
    } else if (this->actionVar2 == 0) {
        if (this->transformation == PLAYER_FORM_HUMAN) {
            Player_PlayAnimSfx(this, D_8085D73C);
        } else if (this->transformation == PLAYER_FORM_DEKU) {
            Player_PlayAnimSfx(this, D_8085D74C);
        }
    } else {
        if ((this->skelAnime.animation == &gPlayerAnim_link_demo_get_itemB) ||
            (this->skelAnime.animation == &gPlayerAnim_pn_getB)) {
            Math_ScaledStepToS(&this->actor.shape.rot.y, BINANG_ADD(Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)), 0x8000),
                               0xFA0);
        } else if ((this->skelAnime.animation == &gPlayerAnim_pn_getA) &&
                   PlayerAnimation_OnFrame(&this->skelAnime, 10.0f)) {
            Player_AnimSfx_PlayFloorLand(this);
        }

        if (PlayerAnimation_OnFrame(&this->skelAnime, 21.0f)) {
            func_8082ECE0(this);
        }
    }
}

AnimSfxEntry D_8085D75C[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 5, NA_SE_VO_LI_AUTO_JUMP, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_FLOOR_LAND, 15, NA_SE_NONE, STOP),
};

void Player_Action_66(Player* this, PlayState* play) {
    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        if (this->actionVar1 == 0) {
            if (DECR(this->actionVar2) == 0) {
                this->actionVar1 = 1;
                this->skelAnime.endFrame = this->skelAnime.animLength - 1.0f;
            }
        } else {
            func_80839E74(this, play);
        }
    } else if ((this->transformation == PLAYER_FORM_FIERCE_DEITY) &&
               PlayerAnimation_OnFrame(&this->skelAnime, 158.0f)) {
        Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_SWORD_N);
    } else if (this->transformation != PLAYER_FORM_FIERCE_DEITY) {
        Player_PlayAnimSfx(this, D_8085D75C);
    } else {
        func_808484CC(this);
    }
}

Vec3f D_8085D764 = { 0.0f, 24.0f, 19.0f };
Vec3f D_8085D770 = { 0.0f, 0.0f, 2.0f };
Vec3f D_8085D77C = { 0.0f, 0.0f, -0.2f };

Color_RGBA8 D_8085D788 = { 255, 255, 255, 255 };
Color_RGBA8 D_8085D78C = { 255, 255, 255, 255 };

void func_808530E0(PlayState* play, Player* this) {
    Vec3f pos;
    Vec3f velocity;
    Vec3f accel;

    Player_TranslateAndRotateY(this, &this->actor.world.pos, &D_8085D764, &pos);
    Player_TranslateAndRotateY(this, &gZeroVec3f, &D_8085D770, &velocity);
    Player_TranslateAndRotateY(this, &gZeroVec3f, &D_8085D77C, &accel);
    func_800B0EB0(play, &pos, &velocity, &accel, &D_8085D788, &D_8085D78C, 40, 10, 10);
}

u8 D_8085D790[] = {
    1,     // PLAYER_IA_BOTTLE_POTION_RED
    1 | 2, // PLAYER_IA_BOTTLE_POTION_BLUE
    2,     // PLAYER_IA_BOTTLE_POTION_GREEN
    4,     // PLAYER_IA_BOTTLE_MILK
    4,     // PLAYER_IA_BOTTLE_MILK_HALF
    1 | 2, // PLAYER_IA_BOTTLE_CHATEAU
};

void Player_Action_67(Player* this, PlayState* play) {
    func_808323C0(this, play->playerCsIds[PLAYER_CS_ID_ITEM_BOTTLE]);

    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        if (this->actionVar2 == 0) {
            if (this->itemAction == PLAYER_IA_BOTTLE_POE) {
                s32 health = Rand_S16Offset(-1, 3);

                if (health == 0) {
                    health = 3;
                }
                if ((health < 0) && (gSaveContext.save.saveInfo.playerData.health <= 0x10)) {
                    health = 3;
                }

                if (health < 0) {
                    Health_ChangeBy(play, -0x10);
                } else {
                    gSaveContext.healthAccumulator = health * 0x10;
                }
            } else {
                s32 temp_v1 = D_8085D790[this->itemAction - PLAYER_IA_BOTTLE_POTION_RED];

                if (temp_v1 & 1) {
                    gSaveContext.healthAccumulator = 0x140;
                }
                if (temp_v1 & 2) {
                    Magic_Add(play, MAGIC_FILL_TO_CAPACITY);
                }
                if (temp_v1 & 4) {
                    gSaveContext.healthAccumulator = 0x50;
                }

                if (this->itemAction == PLAYER_IA_BOTTLE_CHATEAU) {
                    SET_WEEKEVENTREG(WEEKEVENTREG_DRANK_CHATEAU_ROMANI);
                }

                gSaveContext.jinxTimer = 0;
            }

            func_8082DB60(play, this,
                          (this->transformation == PLAYER_FORM_DEKU) ? &gPlayerAnim_pn_drink
                                                                     : &gPlayerAnim_link_bottle_drink_demo_wait);
            this->actionVar2 = 1;

        //! FAKE
        dummy_label_235515:;
        } else if (this->actionVar2 < 0) {
            this->actionVar2++;
            if (this->actionVar2 == 0) {
                this->actionVar2 = 3;
                this->skelAnime.endFrame = this->skelAnime.animLength - 1.0f;
            } else if (this->actionVar2 == -6) {
                func_808530E0(play, this);
            }
        } else {
            Player_StopCutscene(this);
            func_80839E74(this, play);
        }
    } else if (this->actionVar2 == 1) {
        if ((gSaveContext.healthAccumulator == 0) && (gSaveContext.magicState != MAGIC_STATE_FILL)) {
            if (this->transformation == PLAYER_FORM_DEKU) {
                PlayerAnimation_Change(play, &this->skelAnime, &gPlayerAnim_pn_drinkend, 2.0f / 3.0f, 0.0f, 5.0f, 2,
                                       -6.0f);
                this->actionVar2 = -7;
            } else {
                func_8082E4A4(play, this, &gPlayerAnim_link_bottle_drink_demo_end);
                this->actionVar2 = 2;
            }

            Player_UpdateBottleHeld(play, this,
                                    (this->itemAction == PLAYER_IA_BOTTLE_MILK) ? ITEM_MILK_HALF : ITEM_BOTTLE,
                                    PLAYER_IA_BOTTLE_EMPTY);
        }

        Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_DRINK - SFX_FLAG);
    } else if ((this->actionVar2 == 2) && PlayerAnimation_OnFrame(&this->skelAnime, 29.0f)) {
        Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_BREATH_DRINK);
    }
}

#define BOTTLE_CATCH_PARAMS_ANY -1

struct_8085D798 D_8085D798[] = {
    { ACTOR_EN_ELF, FAIRY_PARAMS(FAIRY_TYPE_2, false, 0), ITEM_FAIRY, PLAYER_IA_BOTTLE_FAIRY, 0x5E },
    { ACTOR_EN_FISH, BOTTLE_CATCH_PARAMS_ANY, ITEM_FISH, PLAYER_IA_BOTTLE_FISH, 0x62 },
    { ACTOR_EN_INSECT, BOTTLE_CATCH_PARAMS_ANY, ITEM_BUG, PLAYER_IA_BOTTLE_BUG, 0x63 },
    { ACTOR_EN_MUSHI2, BOTTLE_CATCH_PARAMS_ANY, ITEM_BUG, PLAYER_IA_BOTTLE_BUG, 0x63 },
    { ACTOR_EN_TEST5, ENTEST5_PARAMS(false), ITEM_SPRING_WATER, PLAYER_IA_BOTTLE_SPRING_WATER, 0x67 },
    { ACTOR_EN_TEST5, ENTEST5_PARAMS(true), ITEM_HOT_SPRING_WATER, PLAYER_IA_BOTTLE_HOT_SPRING_WATER, 0x68 },
    { ACTOR_BG_GORON_OYU, BOTTLE_CATCH_PARAMS_ANY, ITEM_HOT_SPRING_WATER, PLAYER_IA_BOTTLE_HOT_SPRING_WATER, 0x68 },
    { ACTOR_EN_ZORAEGG, BOTTLE_CATCH_PARAMS_ANY, ITEM_ZORA_EGG, PLAYER_IA_BOTTLE_ZORA_EGG, 0x69 },
    { ACTOR_EN_DNP, BOTTLE_CATCH_PARAMS_ANY, ITEM_DEKU_PRINCESS, PLAYER_IA_BOTTLE_DEKU_PRINCESS, 0x5F },
    { ACTOR_EN_OT, BOTTLE_CATCH_PARAMS_ANY, ITEM_SEAHORSE, PLAYER_IA_BOTTLE_SEAHORSE, 0x6E },
    { ACTOR_OBJ_KINOKO, BOTTLE_CATCH_PARAMS_ANY, ITEM_MUSHROOM, PLAYER_IA_BOTTLE_SEAHORSE, 0x6B },
    { ACTOR_EN_POH, BOTTLE_CATCH_PARAMS_ANY, ITEM_POE, PLAYER_IA_BOTTLE_POE, 0x65 },
    { ACTOR_EN_BIGPO, BOTTLE_CATCH_PARAMS_ANY, ITEM_BIG_POE, PLAYER_IA_BOTTLE_BIG_POE, 0x66 },
    { ACTOR_EN_ELF, FAIRY_PARAMS(FAIRY_TYPE_6, false, 0), ITEM_FAIRY, PLAYER_IA_BOTTLE_FAIRY, 0x5E },
};

void Player_Action_68(Player* this, PlayState* play) {
    struct_8085D200* sp24 = &D_8085D200[this->actionVar2];

    func_80832F24(this);

    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        if (this->actionVar1 != 0) {
            func_808323C0(this, play->playerCsIds[PLAYER_CS_ID_ITEM_SHOW]);

            if (this->actionVar2 == 0) {
                Message_StartTextbox(play, D_8085D798[this->actionVar1 - 1].textId, &this->actor);

                Audio_PlayFanfare(NA_BGM_GET_ITEM | 0x900);
                this->actionVar2 = 1;
            } else if (Message_GetState(&play->msgCtx) == TEXT_STATE_CLOSING) {
                Actor* talkActor;

                this->actionVar1 = 0;
                Player_StopCutscene(this);
                func_800E0238(Play_GetCamera(play, CAM_ID_MAIN));

                talkActor = this->talkActor;
                if ((talkActor != NULL) && (this->exchangeItemAction <= PLAYER_IA_MINUS1)) {
                    Player_TalkWithPlayer(play, talkActor);
                }
            }
        } else {
            func_80839E74(this, play);
        }
    } else {
        if (this->actionVar1 == 0) {
            s32 temp_ft5 = this->skelAnime.curFrame - sp24->unk_8;

            if ((temp_ft5 >= 0) && (sp24->unk_9 >= temp_ft5)) {
                if ((this->actionVar2 != 0) && (temp_ft5 == 0)) {
                    Player_PlaySfx(this, NA_SE_IT_SCOOP_UP_WATER);
                }

                if (Player_GetItemOnButton(play, this, this->heldItemButton) == ITEM_BOTTLE) {
                    Actor* interactRangeActor = this->interactRangeActor;

                    if (interactRangeActor != NULL) {
                        struct_8085D798* entry = D_8085D798;
                        s32 i;

                        for (i = 0; i < ARRAY_COUNT(D_8085D798); i++) {
                            if (((interactRangeActor->id == entry->actorId) &&
                                 ((entry->actorParams <= BOTTLE_CATCH_PARAMS_ANY) ||
                                  (interactRangeActor->params == entry->actorParams)))) {
                                break;
                            }
                            entry++;
                        }

                        if (i < ARRAY_COUNT(D_8085D798)) {
                            this->actionVar1 = i + 1;
                            this->actionVar2 = 0;
                            this->stateFlags1 |= PLAYER_STATE1_10000000 | PLAYER_STATE1_20000000;
                            interactRangeActor->parent = &this->actor;
                            Player_UpdateBottleHeld(play, this, entry->itemId, entry->itemAction);
                            func_8082DB90(play, this, sp24->unk_4);
                        }
                    }
                }
            }
        }

        if (this->skelAnime.curFrame <= 7.0f) {
            this->stateFlags3 |= PLAYER_STATE3_800;
        }
    }
}

Vec3f D_8085D7EC = { 0.0f, 0.0f, 5.0f };

void Player_Action_69(Player* this, PlayState* play) {
    func_808323C0(this, play->playerCsIds[PLAYER_CS_ID_ITEM_BOTTLE]);

    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        Player_StopCutscene(this);
        func_80839E74(this, play);
    } else if (PlayerAnimation_OnFrame(&this->skelAnime, 37.0f)) {
        s32 fairyParams = FAIRY_PARAMS(FAIRY_TYPE_8, false, 0);

        Player_PlaySfx(this, NA_SE_EV_BOTTLE_CAP_OPEN);
        Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_AUTO_JUMP);
        if (this->itemAction == PLAYER_IA_BOTTLE_FAIRY) {
            Player_UpdateBottleHeld(play, this, ITEM_BOTTLE, PLAYER_IA_BOTTLE_EMPTY);
            Player_PlaySfx(this, NA_SE_EV_FIATY_HEAL - SFX_FLAG);
            fairyParams = FAIRY_PARAMS(FAIRY_TYPE_1, false, 0);
        }

        Player_SpawnFairy(play, this, &this->leftHandWorld.pos, &D_8085D7EC, fairyParams);
    }
}

void Player_Action_70(Player* this, PlayState* play) {
    static Vec3f D_8085D7F8 = { 10.0f, 268 * 0.1f, 30.0f };
    static s8 D_8085D804[PLAYER_FORM_MAX] = {
        0x2D, // PLAYER_FORM_FIERCE_DEITY
        0x4B, // PLAYER_FORM_GORON
        0x37, // PLAYER_FORM_ZORA
        0x23, // PLAYER_FORM_DEKU
        0x28, // PLAYER_FORM_HUMAN
    };
    static struct_8085D80C D_8085D80C[] = {
        { ACTOR_EN_FISH, FISH_PARAMS(ENFISH_0) },                   // PLAYER_BOTTLE_FISH
        { ACTOR_OBJ_AQUA, AQUA_PARAMS(AQUA_TYPE_COLD) },            // PLAYER_BOTTLE_SPRING_WATER
        { ACTOR_OBJ_AQUA, AQUA_PARAMS(AQUA_TYPE_HOT) },             // PLAYER_BOTTLE_HOT_SPRING_WATER
        { ACTOR_EN_ZORAEGG, ZORA_EGG_PARAMS(ZORA_EGG_TYPE_11, 0) }, // PLAYER_BOTTLE_ZORA_EGG
        { ACTOR_EN_DNP, DEKU_PRINCESS_PARAMS(DEKU_PRINCESS_TYPE_RELEASED_FROM_BOTTLE) }, // PLAYER_BOTTLE_DEKU_PRINCESS
        { ACTOR_EN_MUSHI2, ENMUSHI2_PARAMS(ENMUSHI2_0) },                                // PLAYER_BOTTLE_GOLD_DUST
        { ACTOR_EN_MUSHI2, ENMUSHI2_PARAMS(ENMUSHI2_0) },                                // PLAYER_BOTTLE_1C
        { ACTOR_EN_OT, SEAHORSE_PARAMS(SEAHORSE_TYPE_2, 0, 0) },                         // PLAYER_BOTTLE_SEAHORSE
        { ACTOR_EN_MUSHI2, ENMUSHI2_PARAMS(ENMUSHI2_0) },                                // PLAYER_BOTTLE_MUSHROOM
        { ACTOR_EN_MUSHI2, ENMUSHI2_PARAMS(ENMUSHI2_0) },                                // PLAYER_BOTTLE_HYLIAN_LOACH
        { ACTOR_EN_MUSHI2, ENMUSHI2_PARAMS(ENMUSHI2_0) },                                // PLAYER_BOTTLE_BUG
    };
    static AnimSfxEntry D_8085D838[] = {
        ANIMSFX(ANIMSFX_TYPE_VOICE, 38, NA_SE_VO_LI_AUTO_JUMP, CONTINUE),
        ANIMSFX(ANIMSFX_TYPE_GENERAL, 40, NA_SE_EV_BOTTLE_CAP_OPEN, STOP),
    };

    CollisionPoly* sp6C;
    s32 sp68;
    Vec3f sp5C;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    struct_8085D80C* sp4C;

    D_8085D7F8.z = D_8085D804[this->transformation];
    if (Player_PosVsWallLineTest(play, this, &D_8085D7F8, &sp6C, &sp68, &sp5C)) {
        temp_fv1 = this->actor.world.pos.x - sp5C.x;
        temp_fa0 = this->actor.world.pos.z - sp5C.z;
        temp_fv0 = sqrtf(SQ(temp_fv1) + SQ(temp_fa0));

        if (temp_fv0 != 0.0f) {
            temp_fv0 = 3.0f / temp_fv0;

            this->actor.world.pos.x += temp_fv1 * temp_fv0;
            this->actor.world.pos.z += temp_fa0 * temp_fv0;
        }
    }

    func_80832F24(this);
    func_8083249C(this);

    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        Player_StopCutscene(this);
        if (!Player_ActionChange_13(this, play)) {
            func_80839E74(this, play);
        }
    } else if (PlayerAnimation_OnFrame(&this->skelAnime, 76.0f)) {
        sp4C = &D_8085D80C[GET_BOTTLE_FROM_IA(this->itemAction) - 1];

        Actor_Spawn(&play->actorCtx, play, sp4C->actorId,
                    (Math_SinS(this->actor.shape.rot.y) * 5.0f) + this->leftHandWorld.pos.x, this->leftHandWorld.pos.y,
                    (Math_CosS(this->actor.shape.rot.y) * 5.0f) + this->leftHandWorld.pos.z, 0x4000,
                    this->actor.shape.rot.y, 0, sp4C->params);
        Player_UpdateBottleHeld(play, this, ITEM_BOTTLE, PLAYER_IA_BOTTLE_EMPTY);
    } else {
        Player_PlayAnimSfx(this, D_8085D838);
    }
}

AnimSfxEntry D_8085D840[] = {
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 30, NA_SE_PL_PUT_OUT_ITEM, STOP),
};

void Player_Action_71(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;
    this->stateFlags3 |= PLAYER_STATE3_4000000;

    func_8083249C(this);

    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        if (this->exchangeItemAction == PLAYER_IA_NONE) {
            Actor* talkActor = this->talkActor;

            Player_StopCutscene(this);
            this->getItemDrawIdPlusOne = GID_NONE + 1;

            if ((talkActor->textId != 0) && (talkActor->textId != 0xFFFF)) {
                this->actor.flags |= ACTOR_FLAG_TALK_REQUESTED;
            }
            Player_TalkWithPlayer(play, talkActor);
        } else {
            GetItemEntry* giEntry = &sGetItemTable[D_8085D1A4[this->exchangeItemAction] - 1];

            if (Player_BottleFromIA(this, this->itemAction) <= PLAYER_BOTTLE_NONE) {
                this->getItemDrawIdPlusOne = ABS_ALT(giEntry->gid);
            }

            if (this->actionVar2 == 0) {
                if ((this->actor.textId != 0) && (this->actor.textId != 0xFFFF)) {
                    Message_StartTextbox(play, this->actor.textId, &this->actor);
                }

                this->actionVar2 = 1;
            } else if (Message_GetState(&play->msgCtx) == TEXT_STATE_CLOSING) {
                Player_StopCutscene(this);
                this->getItemDrawIdPlusOne = GID_NONE + 1;
                this->actor.flags &= ~ACTOR_FLAG_TALK_REQUESTED;
                func_80839E74(this, play);
                this->unk_B5E = 0xA;
            }
        }
    } else if (this->actionVar2 >= 0) {
        if ((Player_BottleFromIA(this, this->itemAction) > PLAYER_BOTTLE_NONE) &&
            PlayerAnimation_OnFrame(&this->skelAnime, 36.0f)) {
            Player_SetModels(this, PLAYER_MODELGROUP_BOTTLE);
        } else if (PlayerAnimation_OnFrame(&this->skelAnime, 2.0f)) {
            GetItemEntry* giEntry = &sGetItemTable[D_8085D1A4[this->itemAction] - 1];

            func_80838830(this, giEntry->objectId);
        }
        Player_PlayAnimSfx(this, D_8085D840);
    }

    if ((this->actionVar1 == 0) && (this->lockOnActor != NULL)) {
        this->currentYaw = func_8083C62C(this, 0);
        this->actor.shape.rot.y = this->currentYaw;
    }
}

void Player_Action_72(Player* this, PlayState* play) {
    this->stateFlags2 |= (PLAYER_STATE2_20 | PLAYER_STATE2_40);

    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        Player_AnimationPlayLoop(play, this, &gPlayerAnim_link_normal_re_dead_attack_wait);
    }

    if (play->sceneId != SCENE_SEA_BS) {
        func_8082F164(this, BTN_R);
    }

    if (func_8082DE88(this, 0, 0x64)) {
        func_80836988(this, play);
        this->stateFlags2 &= ~PLAYER_STATE2_80;
    }
}

void Player_Action_73(Player* this, PlayState* play) {
    CollisionPoly* floorPoly;
    f32 var_fv0;
    f32 temp_fv1;
    f32 var_fa0;
    s16 downwardSlopeYaw;
    s16 var_v0;
    Vec3f slopeNormal;

    this->stateFlags2 |= (PLAYER_STATE2_20 | PLAYER_STATE2_40);
    PlayerAnimation_Update(play, &this->skelAnime);
    func_8083FBC4(play, this);
    Audio_PlaySfx_AtPosWithSyncedFreqAndVolume(
        &this->actor.projectedPos, Player_GetFloorSfx(this, NA_SE_PL_SLIP_LEVEL - SFX_FLAG), this->actor.speed);

    if (Player_ActionChange_13(this, play)) {
        return;
    }

    if ((this->transformation == PLAYER_FORM_GORON) && Player_ActionChange_6(this, play)) {
        return;
    }

    floorPoly = this->actor.floorPoly;
    if (floorPoly == NULL) {
        func_80833AA0(this, play);
        return;
    }

    Actor_GetSlopeDirection(floorPoly, &slopeNormal, &downwardSlopeYaw);
    var_v0 = downwardSlopeYaw;
    if (this->actionVar1 != 0) {
        var_v0 = downwardSlopeYaw + 0x8000;
    }
    if (this->linearVelocity < 0.0f) {
        downwardSlopeYaw += 0x8000;
    }

    var_fv0 = (1.0f - slopeNormal.y) * 40.0f;
    var_fv0 = CLAMP(var_fv0, 0.0f, 10.0f);

    temp_fv1 = var_fv0 * var_fv0 * 0.015f;
    var_fa0 = slopeNormal.y * 0.01f;
    if (SurfaceType_GetFloorEffect(&play->colCtx, floorPoly, this->actor.floorBgId) != FLOOR_EFFECT_1) {
        var_fv0 = 0.0f;
        var_fa0 = slopeNormal.y * 10.0f;
    }
    temp_fv1 = CLAMP_MIN(temp_fv1, 1.0f);

    if (Math_AsymStepToF(&this->linearVelocity, var_fv0, temp_fv1, var_fa0) && (var_fv0 == 0.0f)) {
        func_80836A98(this,
                      (this->actionVar1 == 0) ? D_8085BE84[PLAYER_ANIMGROUP_41][this->modelAnimType]
                                              : D_8085BE84[PLAYER_ANIMGROUP_42][this->modelAnimType],
                      play);
    }

    Math_SmoothStepToS(&this->currentYaw, downwardSlopeYaw, 0xA, 0xFA0, 0x320);
    Math_ScaledStepToS(&this->actor.shape.rot.y, var_v0, 0x7D0);
}

void func_80859CE0(PlayState* play, Player* this, s32 arg2);

void Player_Action_74(Player* this, PlayState* play) {
    if ((DECR(this->actionVar2) == 0) && func_808387A0(play, this)) {
        func_80859CE0(play, this, 0);
        Player_SetAction(play, this, Player_Action_97, 0);
        Player_Action_97(this, play);
    }
}

void Player_Action_75(Player* this, PlayState* play) {
    Player_SetAction(play, this, Player_Action_74, 0);
    this->actionVar2 = 0x28;
    Actor_Spawn(&play->actorCtx, play, ACTOR_DEMO_KANKYO, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0x10);
}

void Player_Cutscene_SetPosAndYawToStart(Player* this, CsCmdActorCue* cue);

void Player_Action_76(Player* this, PlayState* play) {
    if (sPlayerYDistToFloor < 150.0f) {
        if (PlayerAnimation_Update(play, &this->skelAnime)) {
            if (this->actionVar2 == 0) {
                if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
                    this->skelAnime.endFrame = this->skelAnime.animLength - 1.0f;
                    Player_AnimSfx_PlayFloorLand(this);
                    this->actionVar2 = 1;
                }
            } else {
                func_8085B384(this, play);
            }
        }

        Math_SmoothStepToF(&this->actor.velocity.y, 2.0f, 0.3f, 8.0f, 0.5f);
    }

    if (play->csCtx.state != CS_STATE_IDLE) {
        if (play->csCtx.playerCue != NULL) {
            s32 pad;
            f32 sp28 = this->actor.world.pos.y;

            Player_Cutscene_SetPosAndYawToStart(this, play->csCtx.playerCue);
            this->actor.world.pos.y = sp28;
        }
    }
}

void Player_Action_77(Player* this, PlayState* play) {
    if (this->skelAnime.animation == NULL) {
        this->stateFlags2 |= PLAYER_STATE2_4000;
    } else {
        PlayerAnimation_Update(play, &this->skelAnime);
        if ((this->skelAnime.animation == &gPlayerAnim_link_derth_rebirth) &&
            PlayerAnimation_OnFrame(&this->skelAnime, 60.0f)) {
            Player_AnimSfx_PlayFloor(this, NA_SE_PL_BOUND);
            Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_DAMAGE_S);
        }
    }

    if ((this->actionVar2++ >= 9) && !func_8082DA90(play)) {
        if (this->actionVar1 != 0) {
            if (this->actionVar1 < 0) {
                func_80169FDC(&play->state);
            } else {
                func_80169EFC(&play->state);
            }
            if (!SurfaceType_IsWallDamage(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId)) {
                gSaveContext.respawnFlag = -5;
            }

            play->transitionType = TRANS_TYPE_FADE_BLACK_FAST;
            Audio_PlaySfx(NA_SE_OC_ABYSS);
        } else {
            play->transitionType = TRANS_TYPE_FADE_BLACK;
            gSaveContext.nextTransitionType = TRANS_TYPE_FADE_BLACK;
            gSaveContext.seqId = (u8)NA_BGM_DISABLED;
            gSaveContext.ambienceId = AMBIENCE_ID_DISABLED;
        }

        play->transitionTrigger = TRANS_TRIGGER_START;
    }
}

void Player_Action_78(Player* this, PlayState* play) {
    Player_ActionChange_1(this, play);
}

void Player_Action_79(Player* this, PlayState* play) {
    this->actor.gravity = -1.0f;
    PlayerAnimation_Update(play, &this->skelAnime);

    if (this->actor.velocity.y < 0.0f) {
        func_80833AA0(this, play);
    } else if (this->actor.velocity.y < 6.0f) {
        Math_StepToF(&this->linearVelocity, 3.0f, 0.5f);
    }
}

void Player_Action_80(Player* this, PlayState* play) {
    if (play->unk_1887C < 0) {
        play->unk_1887C = 0;
        func_80839ED0(this, play);
    } else if (this->actionVar1 == 0) {
        if ((play->sceneId != SCENE_20SICHITAI) && CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_B)) {
            play->unk_1887C = 10;
            func_80847880(play, this);
            Player_SetAction(play, this, Player_Action_80, 1);
            this->actionVar1 = 1;
        } else {
            play->unk_1887C = 0;
            func_80847190(play, this, 0);

            if (play->actorCtx.flags & ACTORCTX_FLAG_PICTO_BOX_ON) {
                this->stateFlags1 |= PLAYER_STATE1_100000;
                func_8083868C(play, this);
            } else {
                this->stateFlags1 &= ~PLAYER_STATE1_100000;
                if ((play->sceneId == SCENE_20SICHITAI) &&
                    (Player_GetItemOnButton(play, this, func_8082FDC4()) == ITEM_PICTOGRAPH_BOX)) {
                    s32 requiredScopeTemp;

                    play->actorCtx.flags |= ACTORCTX_FLAG_PICTO_BOX_ON;
                }
            }
        }
    } else if (CHECK_BTN_ANY(sPlayerControlInput->press.button,
                             BTN_CRIGHT | BTN_CLEFT | BTN_CDOWN | BTN_CUP | BTN_R | BTN_A)) {
        play->unk_1887C = -1;
        Player_Action_81(this, play);
        Player_SetAction(play, this, Player_Action_80, 0);
        this->actionVar1 = 0;
    } else {
        play->unk_1887C = 10;
        Player_Action_81(this, play);
    }
}

void Player_Action_81(Player* this, PlayState* play) {
    this->unk_AA5 = PLAYER_UNKAA5_3;
    func_8083868C(play, this);
    PlayerAnimation_Update(play, &this->skelAnime);
    Player_UpdateUpperBody(this, play);
    this->upperLimbRot.y = func_80847190(play, this, 1) - this->actor.shape.rot.y;
    this->unk_AA6 |= 0x80;

    if (play->unk_1887C < 0) {
        play->unk_1887C++;
        if (play->unk_1887C == 0) {
            func_80839ED0(this, play);
        }
    }
}

void Player_Action_82(Player* this, PlayState* play) {
    if (this->actionVar1 >= 0) {
        if (this->actionVar1 < 6) {
            this->actionVar1++;
        } else {
            this->unk_B48 = (this->actionVar1 >> 1) * 22.0f;
            if (func_8082DE88(this, 1, 0x64)) {
                this->actionVar1 = -1;
                EffectSsIcePiece_SpawnBurst(play, &this->actor.world.pos, this->actor.scale.x);
                Player_PlaySfx(this, NA_SE_PL_ICE_BROKEN);
            }

            if (this->transformation == PLAYER_FORM_ZORA) {
                func_80834104(play, this);
                this->skelAnime.animation = NULL;
                this->actionVar2 = -0x28;
                this->actionVar1 = 1;
                this->linearVelocity = 0.0f;
            } else if (play->gameplayFrames % 4 == 0) {
                Player_InflictDamage(play, -1);
            }
        }

        this->stateFlags2 |= PLAYER_STATE2_4000;
    } else if (PlayerAnimation_Update(play, &this->skelAnime)) {
        func_80836988(this, play);
        func_808339B4(this, 20);
    }
}

void Player_Action_83(Player* this, PlayState* play) {
    PlayerAnimation_Update(play, &this->skelAnime);
    func_808345A8(this);

    if (((this->actionVar2 % 25) != 0) || (func_808339D4(play, this, -1) != 0)) {
        if (DECR(this->actionVar2) == 0) {
            func_80836988(this, play);
        }
    }

    this->shockTimer = 40;
    Actor_PlaySfx_FlaggedCentered1(&this->actor,
                                   this->ageProperties->voiceSfxIdOffset + (NA_SE_VO_LI_TAKEN_AWAY - SFX_FLAG));
}

void Player_Action_84(Player* this, PlayState* play) {
    AttackAnimInfo* attackInfoEntry = &sMeleeAttackAnimInfo[this->meleeWeaponAnimation];

    if (this->skelAnime.curFrame < (this->skelAnime.endFrame - 6.0f)) {
        this->stateFlags2 |= PLAYER_STATE2_20;
    }

    if (func_808401F4(play, this)) {
        return;
    }

    if (this->linearVelocity >= 0.0f) {
        func_8083FCF0(play, this, (this->transformation == PLAYER_FORM_GORON) ? 5.0f : 0.0f, attackInfoEntry->unk_C,
                      attackInfoEntry->unk_D);
    }

    if ((this->meleeWeaponAnimation == PLAYER_MWA_GORON_PUNCH_LEFT) ||
        (this->meleeWeaponAnimation == PLAYER_MWA_GORON_PUNCH_RIGHT)) {
        this->unk_3D0.unk_00 = 3;
    }

    //! @bug Lunge Storage: If this block is prevented from running at the end of an animation that produces a lunge,
    //! the prepared lunge will be retained until next time execution passes through here, which usually means the next
    //! sword slash.
    if ((this->stateFlags2 & PLAYER_STATE2_40000000) && PlayerAnimation_OnFrame(&this->skelAnime, 0.0f)) {
        this->linearVelocity = 15.0f;
        this->stateFlags2 &= ~PLAYER_STATE2_40000000;
    }

    if (this->linearVelocity > 12.0f) {
        func_8083FBC4(play, this);
    }

    Math_StepToF(&this->linearVelocity, 0.0f, 5.0f);
    func_8083A548(this);

    if (PlayerAnimation_Update(play, &this->skelAnime) ||
        ((this->meleeWeaponAnimation >= PLAYER_MWA_FLIPSLASH_FINISH) &&
         (this->meleeWeaponAnimation <= PLAYER_MWA_ZORA_JUMPKICK_FINISH) && (this->skelAnime.curFrame > 2.0f) &&
         func_808333CC(this))) {
        sPlayerUseHeldItem = this->actionVar2;

        if (!Player_ActionChange_7(this, play)) {
            PlayerAnimationHeader* anim = func_80123420(this) ? attackInfoEntry->unk_8 : attackInfoEntry->unk_4;

            func_8082DC38(this);

            if (anim == NULL) {
                this->skelAnime.moveFlags &= ~8;
                func_8085B384(this, play);
            } else {
                u8 moveFlags = this->skelAnime.moveFlags;

                if (this->transformation == PLAYER_FORM_ZORA) {
                    if (Player_ActionChange_8(this, play)) {
                        anim = this->skelAnimeUpper.animation;
                    }
                    this->unk_ADC = 0;
                } else if ((anim == &gPlayerAnim_link_fighter_Lpower_jump_kiru_end) &&
                           (this->modelAnimType != PLAYER_ANIMTYPE_3)) {
                    anim = &gPlayerAnim_link_fighter_power_jump_kiru_end;
                }

                this->skelAnime.moveFlags = 0;
                Player_SetAction(play, this, Player_Action_4, 1);
                func_8082EC9C(play, this, anim);
                this->currentYaw = this->actor.shape.rot.y;
                this->skelAnime.moveFlags = moveFlags;
            }
            this->stateFlags3 |= PLAYER_STATE3_8;
        }
    } else if (((this->transformation == PLAYER_FORM_ZORA) &&
                (this->meleeWeaponAnimation != PLAYER_MWA_ZORA_PUNCH_KICK) &&
                (this->meleeWeaponAnimation != PLAYER_MWA_ZORA_JUMPKICK_FINISH)) ||
               ((this->transformation == PLAYER_FORM_GORON) &&
                (this->meleeWeaponAnimation != PLAYER_MWA_GORON_PUNCH_BUTT))) {
        this->actionVar2 |= CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_B) ? 1 : 0;
    }
}

void Player_Action_85(Player* this, PlayState* play) {
    PlayerAnimation_Update(play, &this->skelAnime);
    func_80832F24(this);

    if (this->skelAnime.curFrame >= 6.0f) {
        func_80836988(this, play);
    }
}

// Array colour interpolation
// arg0 is the interpolation parameter
// arg1,5,9 are out colours
// arg2,6,0xA are first values
// arg3,7,0xB are second values
// arg4,8,0xC are subtracted after interpolation
void func_80854CD0(f32 arg0, s16* arg1, u8* arg2, u8* arg3, u8* arg4, s16* arg5, u8* arg6, u8* arg7, u8* arg8,
                   s16* arg9, u8* argA, u8* argB, u8* argC) {
    s32 i;

    for (i = 0; i < 3; i++) {
        *arg1 = ((s32)((*arg2 - *arg3) * arg0) + *arg3) - *arg4;
        *arg5 = ((s32)((*arg6 - *arg7) * arg0) + *arg7) - *arg8;
        *arg9 = ((s32)((*argA - *argB) * arg0) + *argB) - *argC;

        arg1++;
        arg2++;
        arg3++;
        arg4++;
        arg5++;
        arg6++;
        arg7++;
        arg8++;
        arg9++;
        argA++;
        argB++;
        argC++;
    }
}

// Black, probably in-function static
u8 D_8085D844[] = { 0, 0, 0 };

// arg1 is the colour interpolation parameter
void func_80854EFC(PlayState* play, f32 arg1, struct_8085D848_unk_00* arg2) {
    struct_8085D848_unk_00 sp70;
    struct_8085D848_unk_00* var_t0;
    struct_8085D848_unk_00* var_v1;
    u8* var_t3;
    u8* var_t4;
    u8* new_var;
    s32 pad[4];

    new_var = play->envCtx.lightSettings.light1Color;
    sp70.fogNear = play->envCtx.lightSettings.fogNear;
    sp70.fogColor[0] = play->envCtx.lightSettings.fogColor[0];
    sp70.fogColor[1] = play->envCtx.lightSettings.fogColor[1];
    sp70.fogColor[2] = play->envCtx.lightSettings.fogColor[2];
    sp70.ambientColor[0] = play->envCtx.lightSettings.ambientColor[0];
    sp70.ambientColor[1] = play->envCtx.lightSettings.ambientColor[1];
    sp70.ambientColor[2] = play->envCtx.lightSettings.ambientColor[2];

    if (arg1 <= 1.0f) {
        arg1 -= 0.0f;

        var_v1 = &arg2[0];
        var_t0 = &sp70;
        var_t3 = D_8085D844;
        var_t4 = new_var;
    } else if (arg1 <= 2.0f) {
        arg1 -= 1.0f;
        var_v1 = &arg2[1];
        var_t0 = &arg2[0];
        var_t3 = D_8085D844;
        var_t4 = D_8085D844;

    } else if (arg1 <= 3.0f) {
        arg1 -= 2.0f;
        var_v1 = &arg2[2];
        var_t0 = &arg2[1];
        var_t3 = D_8085D844;
        var_t4 = D_8085D844;

    } else {
        arg1 -= 3.0f;
        var_v1 = &sp70;
        var_t0 = &arg2[2];
        var_t3 = new_var;
        var_t4 = D_8085D844;
    }

    play->envCtx.adjLightSettings.fogNear =
        ((s16)((var_v1->fogNear - var_t0->fogNear) * arg1) + var_t0->fogNear) - play->envCtx.lightSettings.fogNear;

    func_80854CD0(arg1, play->envCtx.adjLightSettings.fogColor, var_v1->fogColor, var_t0->fogColor,
                  play->envCtx.lightSettings.fogColor, play->envCtx.adjLightSettings.ambientColor, var_v1->ambientColor,
                  var_t0->ambientColor, play->envCtx.lightSettings.ambientColor,
                  play->envCtx.adjLightSettings.light1Color, var_t3, var_t4, new_var);
}

struct_8085D848 D_8085D848[] = {
    {
        {
            { 650, { 0, 0, 0 }, { 10, 0, 30 } },
            { 300, { 200, 200, 255 }, { 0, 0, 0 } },
            { 600, { 0, 0, 0 }, { 0, 0, 200 } },
        },
        {
            { { -40.0f, 20.0f, -10.0f }, { 120, 200, 255 }, 1000 },
            { { 0.0f, -10.0f, 0.0f }, { 255, 255, 255 }, 5000 },
            { { -10.0f, 4.0f, 3.0f }, { 200, 200, 255 }, 5000 },
        },
    },
    {
        {
            { 650, { 0, 0, 0 }, { 10, 0, 30 } },
            { 300, { 200, 200, 255 }, { 0, 0, 0 } },
            { 600, { 0, 0, 0 }, { 0, 0, 200 } },
        },
        {
            { { 0.0f, 0.0f, 5.0f }, { 155, 255, 255 }, 100 },
            { { 0.0f, 0.0f, 5.0f }, { 155, 255, 255 }, 100 },
            { { 0.0f, 0.0f, 5.0f }, { 155, 255, 255 }, 100 },
        },
    },
};

// arg2 is the colour interpolation parameter
// arg3 both selects the light to use and scales the radius
// arg4 selects the env fog/colour info
void func_808550D0(PlayState* play, Player* this, f32 arg2, f32 arg3, s32 arg4) {
    struct_8085D848* temp_a2 = &D_8085D848[arg4];
    struct_8085D848_unk_18* lightInit = temp_a2->light;
    Vec3f pos;

    func_80854EFC(play, arg2, temp_a2->unk_00);

    if (arg3 > 2.0f) {
        arg3 -= 2.0f;
        lightInit += 2;
    } else if (arg3 > 1.0f) {
        arg3 -= 1.0f;
        lightInit++;
    }

    Player_TranslateAndRotateY(this, &this->actor.world.pos, &lightInit->pos, &pos);
    Lights_PointNoGlowSetInfo(&this->lightInfo, pos.x, pos.y, pos.z, lightInit->color[0], lightInit->color[1],
                              lightInit->color[2], lightInit->radius * arg3);
}

AnimSfxEntry D_8085D8F0[] = {
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 2, NA_SE_PL_PUT_OUT_ITEM, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 4, NA_SE_IT_SET_TRANSFORM_MASK, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 11, NA_SE_PL_FREEZE_S, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 30, NA_SE_PL_TRANSFORM_VOICE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 20, NA_SE_IT_TRANSFORM_MASK_BROKEN, STOP),
};

AnimSfxEntry D_8085D904[] = {
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 8, NA_SE_IT_SET_TRANSFORM_MASK, STOP),
};

void func_80855218(PlayState* play, Player* this, struct_8085D910** arg2) {
    if (PlayerAnimation_Update(play, &this->skelAnime) && (this->skelAnime.animation == &gPlayerAnim_cl_setmask)) {
        func_8082DB60(play, this, &gPlayerAnim_cl_setmaskend);
    } else if ((this->skelAnime.animation == &gPlayerAnim_cl_setmask) ||
               (this->skelAnime.animation == &gPlayerAnim_cl_setmaskend)) {
        if (this->actionVar1 >= 58) {
            Math_StepToS(&this->actionVar2, 255, 50);
        }

        if (this->actionVar1 >= 64) {
            Math_StepToF(&this->unk_B10[2], 0.0f, 0.015f);
        } else if (this->actionVar1 >= 0xE) {
            Math_StepToF(&this->unk_B10[2], 0.3f, 0.3f);
        }

        if (this->actionVar1 > 65) {
            Math_StepToF(&this->unk_B10[3], 0.0f, 0.02f);
        } else if (this->actionVar1 >= 0x10) {
            Math_StepToF(&this->unk_B10[3], -0.1f, 0.1f);
        }

        if ((R_PLAY_FILL_SCREEN_ON == 0) && (this->skelAnime.animation == &gPlayerAnim_cl_setmask)) {
            Player_PlayAnimSfx(this, D_8085D8F0);
        }
    } else {
        if (this->actionVar1 >= 20) {
            Math_StepToS(&this->actionVar2, 255, 20);
        }

        if (R_PLAY_FILL_SCREEN_ON == 0) {
            Player_PlayAnimSfx(this, D_8085D904);
            if (this->actionVar1 == 15) {
                Player_PlaySfx(this, NA_SE_PL_FACE_CHANGE);
            }
        }
    }
}

u16 D_8085D908[] = {
    WEEKEVENTREG_30_80, // PLAYER_FORM_FIERCE_DEITY
    WEEKEVENTREG_30_20, // PLAYER_FORM_GORON
    WEEKEVENTREG_30_40, // PLAYER_FORM_ZORA
    WEEKEVENTREG_30_10, // PLAYER_FORM_DEKU
};
struct_8085D910 D_8085D910[] = {
    { 0x10, 0xA, 0x3B, 0x3F },
    { 9, 0x32, 0xA, 0xD },
};

void Player_Action_86(Player* this, PlayState* play) {
    struct_8085D910* sp4C = D_8085D910;
    s32 sp48 = false;

    func_808323C0(this, play->playerCsIds[PLAYER_CS_ID_MASK_TRANSFORMATION]);
    sPlayerControlInput = play->state.input;

    Camera_ChangeMode(GET_ACTIVE_CAM(play),
                      (this->transformation == PLAYER_FORM_HUMAN) ? CAM_MODE_NORMAL : CAM_MODE_JUMP);
    this->stateFlags2 |= PLAYER_STATE2_40;
    this->actor.shape.rot.y = Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)) + 0x8000;

    func_80855218(play, this, &sp4C);

    if (this->actionVar1 == 0x14) {
        Play_EnableMotionBlurPriority(100);
    }

    if (R_PLAY_FILL_SCREEN_ON != 0) {
        R_PLAY_FILL_SCREEN_ALPHA += R_PLAY_FILL_SCREEN_ON;
        if (R_PLAY_FILL_SCREEN_ALPHA > 255) {
            R_PLAY_FILL_SCREEN_ALPHA = 255;
            this->actor.update = func_8012301C;
            this->actor.draw = NULL;
            this->actionVar1 = 0;
            Play_DisableMotionBlurPriority();
            SET_WEEKEVENTREG(D_8085D908[GET_PLAYER_FORM]);
        }
    } else if ((this->actionVar1++ > ((this->transformation == PLAYER_FORM_HUMAN) ? 0x53 : 0x37)) ||
               ((this->actionVar1 >= 5) &&
                (sp48 =
                     ((this->transformation != PLAYER_FORM_HUMAN) || CHECK_WEEKEVENTREG(D_8085D908[GET_PLAYER_FORM])) &&
                     CHECK_BTN_ANY(sPlayerControlInput->press.button,
                                   BTN_CRIGHT | BTN_CLEFT | BTN_CDOWN | BTN_CUP | BTN_B | BTN_A)))) {
        R_PLAY_FILL_SCREEN_ON = 45;
        R_PLAY_FILL_SCREEN_R = 220;
        R_PLAY_FILL_SCREEN_G = 220;
        R_PLAY_FILL_SCREEN_B = 220;
        R_PLAY_FILL_SCREEN_ALPHA = 0;

        if (sp48) {
            if (CutsceneManager_GetCurrentCsId() == this->csId) {
                func_800E0348(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(this->csId)));
            }

            if (this->transformation == PLAYER_FORM_HUMAN) {
                AudioSfx_StopById(NA_SE_PL_TRANSFORM_VOICE);
                AudioSfx_StopById(NA_SE_IT_TRANSFORM_MASK_BROKEN);
            } else {
                AudioSfx_StopById(NA_SE_PL_FACE_CHANGE);
            }
        }

        Player_PlaySfx(this, NA_SE_SY_TRANSFORM_MASK_FLASH);
    }

    if (this->actionVar1 >= sp4C->unk_0) {
        if (this->actionVar1 < sp4C->unk_2) {
            Math_StepToF(&this->unk_B10[4], 1.0f, sp4C->unk_1 / 100.0f);
        } else if (this->actionVar1 < sp4C->unk_3) {
            if (this->actionVar1 == sp4C->unk_2) {
                Lib_PlaySfx_2(NA_SE_EV_LIGHTNING_HARD);
            }

            Math_StepToF(&this->unk_B10[4], 2.0f, 0.5f);
        } else {
            Math_StepToF(&this->unk_B10[4], 3.0f, 0.2f);
        }
    }

    if (this->actionVar1 >= 0x10) {
        if (this->actionVar1 < 0x40) {
            Math_StepToF(&this->unk_B10[5], 1.0f, 0.2f);
        } else if (this->actionVar1 < 0x37) {
            Math_StepToF(&this->unk_B10[5], 2.0f, 1.0f);
        } else {
            Math_StepToF(&this->unk_B10[5], 3.0f, 0.55f);
        }
    }

    func_808550D0(play, this, this->unk_B10[4], this->unk_B10[5], (this->transformation == PLAYER_FORM_HUMAN) ? 0 : 1);
}

void Player_Action_87(Player* this, PlayState* play) {
    Camera_ChangeMode(GET_ACTIVE_CAM(play), (this->prevMask == PLAYER_MASK_NONE) ? CAM_MODE_NORMAL : CAM_MODE_JUMP);

    if (R_PLAY_FILL_SCREEN_ON != 0) {
        R_PLAY_FILL_SCREEN_ALPHA -= R_PLAY_FILL_SCREEN_ON;
        if (R_PLAY_FILL_SCREEN_ALPHA < 0) {
            R_PLAY_FILL_SCREEN_ON = 0;
            R_PLAY_FILL_SCREEN_ALPHA = 0;
        }
    }

    if (this->actionVar1++ < 4) {
        if ((this->prevMask == PLAYER_MASK_NONE) && (this->actionVar1 == 4)) {
            PlayerAnimation_Change(play, &this->skelAnime, func_8082ED20(this), 1.0f, 0.0f, 20.0f, ANIMMODE_ONCE,
                                   20.0f);
        }
    } else {
        s32 pad;
        f32 dist;
        s16 angle;

        Lib_GetControlStickData(&dist, &angle, play->state.input);
        if (PlayerAnimation_Update(play, &this->skelAnime) || ((this->actionVar1 > 10) && (dist != 0.0f))) {
            if (R_PLAY_FILL_SCREEN_ON == 0) {
                this->stateFlags1 &= ~PLAYER_STATE1_2;
                this->prevMask = this->currentMask;
                this->csId = play->playerCsIds[PLAYER_CS_ID_MASK_TRANSFORMATION];
                Player_StopCutscene(this);
                play->envCtx.adjLightSettings = D_80862B50;
                func_8085B384(this, play);
                return;
            }
        }

        Math_StepToF(&this->unk_B10[5], 4.0f, 0.2f);
    }

    func_808550D0(play, this, 0, this->unk_B10[5], (this->prevMask == PLAYER_MASK_NONE) ? 0 : 1);
}

void Player_Action_88(Player* this, PlayState* play) {
    if (this->actionVar2++ > 90) {
        play->msgCtx.ocarinaMode = OCARINA_MODE_END;
        func_8085B384(this, play);
    } else if (this->actionVar2 == 10) {
        func_80848640(play, this);
    }
}

// Giant's Mask
void Player_Action_89(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_40;

    func_80855218(play, this, NULL);
    this->actionVar1++;

    if (!(this->stateFlags1 & PLAYER_STATE1_100)) {
        this->prevMask = this->currentMask;
        gSaveContext.save.equippedMask = this->currentMask = PLAYER_MASK_GIANT;
        Magic_Consume(play, 0, MAGIC_CONSUME_GIANTS_MASK);
        this->currentBoots = PLAYER_BOOTS_GIANT;
        this->prevBoots = PLAYER_BOOTS_GIANT;
        func_80123140(play, this);
        func_8085B384(this, play);
    }
}

void Player_Action_90(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_40;

    PlayerAnimation_Update(play, &this->skelAnime);

    if (!(this->stateFlags1 & PLAYER_STATE1_100)) {
        this->prevMask = this->currentMask;

        gSaveContext.save.equippedMask = this->currentMask = PLAYER_MASK_NONE;

        this->currentBoots = PLAYER_BOOTS_HYLIAN;
        this->prevBoots = PLAYER_BOOTS_HYLIAN;
        func_80123140(play, this);
        func_8085B384(this, play);
    }
}

void Player_Action_91(Player* this, PlayState* play) {
    s16 sp3E;
    s32 pad;
    PlayerAnimationHeader* sp34;
    s32 var_a0;

    func_808323C0(this, play->playerCsIds[PLAYER_CS_ID_WARP_PAD_MOON]);
    sp3E = BINANG_SUB(this->actor.shape.rot.y, this->actor.world.rot.y);

    var_a0 = 0;
    if ((this->actor.floorHeight - this->actor.world.pos.y) < 60.0f) {
        Math_StepToF(&this->unk_B10[5], 200.0f, 150.0f);
        var_a0 = Math_StepToS(&this->actionVar2, 0xFA0, 0x15E);
    }

    this->actor.shape.rot.y += this->actionVar2;
    this->skelAnime.jointTable[PLAYER_LIMB_ROOT - 1].x = 0;
    this->skelAnime.jointTable[PLAYER_LIMB_ROOT - 1].z = 0;
    this->unk_ABC += this->unk_B10[5];

    if (this->unk_ABC >= 0.0f) {
        this->unk_ABC = 0.0f;
        if ((var_a0 != 0) && (sp3E < 0)) {
            if (BINANG_SUB(this->actor.shape.rot.y, this->actor.world.rot.y) >= 0) {
                this->actor.shape.rot.y = this->actor.world.rot.y;
                Player_StopCutscene(this);
                if (PLAYER_GET_INITMODE(&this->actor) == PLAYER_INITMODE_8) {
                    sp34 = D_8085D17C[this->transformation];
                    func_80836A5C(this, play);
                    PlayerAnimation_Change(play, &this->skelAnime, sp34, -2.0f / 3.0f, Animation_GetLastFrame(sp34),
                                           0.0f, ANIMMODE_ONCE, -6.0f);
                } else {
                    func_80839E74(this, play);
                }
            }
        }
    } else if (this->actionVar1 == 0) {
        Player_PlaySfx(this, NA_SE_PL_WARP_PLATE_OUT);
        this->actionVar1 = 1;
    }
}

void Player_Action_92(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20;

    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        Player_AnimationPlayLoop(play, this, &gPlayerAnim_link_hook_fly_wait);
    }

    Math_Vec3f_Sum(&this->actor.world.pos, &this->actor.velocity, &this->actor.world.pos);
    if (func_80831124(play, this)) {
        f32 var_fv0;

        Math_Vec3f_Copy(&this->actor.prevPos, &this->actor.world.pos);
        Player_ProcessSceneCollision(play, this);

        var_fv0 = this->actor.world.pos.y - this->actor.floorHeight;
        var_fv0 = CLAMP_MAX(var_fv0, 20.0f);

        this->actor.world.pos.y = this->actor.world.pos.y - var_fv0;
        this->actor.shape.rot.x = 0;
        this->linearVelocity = 1.0f;
        this->actor.velocity.y = 0.0f;
        this->actor.world.rot.x = this->actor.shape.rot.x;
        func_80833AA0(this, play);
        this->stateFlags2 &= ~PLAYER_STATE2_400;
        this->actor.bgCheckFlags |= BGCHECKFLAG_GROUND;
        this->stateFlags3 |= PLAYER_STATE3_10000;
    } else if ((this->skelAnime.animation != &gPlayerAnim_link_hook_fly_start) || (this->skelAnime.curFrame >= 4.0f)) {
        this->actor.gravity = 0.0f;
        Math_ScaledStepToS(&this->actor.shape.rot.x, this->actor.world.rot.x, 0x800);
        Player_RequestRumble(play, this, 100, 2, 100, SQ(0));
    }
}

void func_80855F9C(PlayState* play, Player* this) {
    f32 speedTarget;
    s16 yawTarget;

    this->stateFlags2 |= PLAYER_STATE2_20;
    Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_CURVED, play);
    Math_ScaledStepToS(&this->currentYaw, yawTarget, 0x258);
}

s32 func_80856000(PlayState* play, Player* this) {
    CollisionPoly* poly;
    s32 bgId;
    Vec3f pos;
    f32 sp28;

    pos.x = this->actor.world.pos.x;
    pos.y = this->actor.world.pos.y - 20.0f;
    pos.z = this->actor.world.pos.z;
    return BgCheck_EntityCheckCeiling(&play->colCtx, &sp28, &pos, 30.0f, &poly, &bgId, &this->actor);
}

void func_80856074(PlayState* play, Player* this) {
    if (func_8083F8A8(play, this, 12.0f, 4, 0.0f, 10, 50, true)) {
        EffectSsHahen_SpawnBurst(play, &this->actor.world.pos, 3.0f, 0, 4, 8, 2, -1, 10, NULL);
    }
}

void func_80856110(PlayState* play, Player* this, f32 arg2, f32 arg3, f32 arg4, s16 scale, s16 scaleStep, s16 life) {
    static Vec3f D_8085D918 = { 0.0f, 0.5f, 0.0f };        // velocity
    static Vec3f D_8085D924 = { 0.0f, 0.5f, 0.0f };        // accel
    static Color_RGBA8 D_8085D930 = { 255, 255, 55, 255 }; // primColor
    static Color_RGBA8 D_8085D934 = { 100, 50, 0, 0 };     // envColor
    Vec3f pos;

    pos.x = this->actor.world.pos.x;
    pos.y = this->actor.world.pos.y + arg2;
    pos.z = this->actor.world.pos.z;

    D_8085D918.y = arg3;
    D_8085D924.y = arg4;

    func_800B0EB0(play, &pos, &D_8085D918, &D_8085D924, &D_8085D930, &D_8085D934, scale, scaleStep, life);
}

// Deku Flower related
void Player_Action_93(Player* this, PlayState* play) {
    DynaPolyActor* dyna;
    s32 aux = 0xAE;
    f32 temp_fv0_2;
    s32 sp38;
    s32 var_v1;

    PlayerAnimation_Update(play, &this->skelAnime);

    if (Player_ActionChange_13(this, play)) {
        return;
    }

    if (this->actionVar1 == 0) {
        this->unk_ABC += this->unk_B48;
        if (this->unk_ABC < -1000.0f) {
            this->unk_ABC = -1000.0f;
            this->actionVar1 = 1;
            this->unk_B48 = 0.0f;
        }
        func_80856074(play, this);
    } else if (this->actionVar1 == 1) {
        this->unk_B48 += -22.0f;
        if (this->unk_B48 < -170.0f) {
            this->unk_B48 = -170.0f;
        }
        this->unk_ABC += this->unk_B48;
        if (this->unk_ABC < -3900.0f) {
            this->unk_ABC = -3900.0f;
            this->actionVar1 = 2;
            this->actor.shape.rot.y = Camera_GetInputDirYaw(GET_ACTIVE_CAM(play));
            this->actor.scale.y = 0.01f;
            this->currentYaw = this->actor.world.rot.y = this->actor.shape.rot.y;
        } else {
            temp_fv0_2 = Math_SinS((1000.0f + this->unk_ABC) * (-30.0f)) * 0.004f;
            this->actor.scale.y = 0.01f + temp_fv0_2;
            this->actor.scale.z = this->actor.scale.x = 0.01f - (this->unk_B48 * -0.000015f);

            this->actor.shape.rot.y += (s16)(this->unk_B48 * 130.0f);
            if (this->actor.floorBgId != BGCHECK_SCENE) {
                dyna = DynaPoly_GetActor(&play->colCtx, this->actor.floorBgId);

                if (dyna != NULL) {
                    Math_Vec3f_StepToXZ(&this->actor.world.pos, &dyna->actor.world.pos, 1.0f);
                }
            }
        }

        func_80856074(play, this);
    } else if (this->actionVar1 == 2) {
        if (!CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_A)) {
            if (func_80856000(play, this)) {
                this->actionVar2 = 0;
            } else {
                this->actionVar1 = 3;
                if (this->actionVar2 >= 10) {
                    this->unk_B48 = 2700.0f;
                } else {
                    this->unk_B48 = 1450.0f;
                }
                func_8082E1F0(this, NA_SE_PL_DEKUNUTS_OUT_GRD);
            }
        } else if (this->actionVar2 < 15) {
            this->actionVar2++;
            if (this->actionVar2 == 10) {
                func_80856110(play, this, 20.0f, 3.8f, -0.1f, 140, 23, 15);
            }
        }
        func_80855F9C(play, this);
    } else {
        this->unk_ABC += this->unk_B48;

        temp_fv0_2 = this->unk_ABC;
        if (temp_fv0_2 >= 0.0f) {
            f32 speed;

            sp38 = (this->actionVar2 >= 10);
            var_v1 = -1;
            speed = this->unk_B48 * this->actor.scale.y;
            if (this->actor.floorBgId != BGCHECK_SCENE) {
                dyna = DynaPoly_GetActor(&play->colCtx, this->actor.floorBgId);
                var_v1 = 0;
                if ((dyna != NULL) && (dyna->actor.id == ACTOR_OBJ_ETCETERA) && (dyna->actor.params & 0x100)) {
                    var_v1 = 1;
                    speed *= aux / 100.0f;
                }
            }

            Math_Vec3f_Copy(this->unk_AF0, &this->actor.world.pos);
            this->unk_ABC = 0.0f;
            this->actor.world.pos.y += temp_fv0_2 * this->actor.scale.y;
            func_80834DB8(this, &gPlayerAnim_pn_kakku, speed, play);
            Player_SetAction(play, this, Player_Action_94, 1);
            this->boomerangActor = NULL;

            this->stateFlags3 |= PLAYER_STATE3_200;
            if (sp38 != 0) {
                this->stateFlags3 |= PLAYER_STATE3_2000;
            }
            if (var_v1 < 0) {
                this->stateFlags3 |= PLAYER_STATE3_40000;
            }

            this->actionVar1 = var_v1;
            this->actionVar2 = 9999;
            Player_SetCylinderForAttack(this, DMG_DEKU_LAUNCH, 2, 20);
        } else if (this->unk_ABC < 0.0f) {
            func_80856074(play, this);
        }
    }

    if (this->unk_ABC < -1500.0f) {
        this->stateFlags3 |= PLAYER_STATE3_100;
        if (this->unk_B86[0] < 8) {
            this->unk_B86[0]++;
            if (this->unk_B86[0] == 8) {
                func_8082E1F0(this, NA_SE_PL_DEKUNUTS_BUD);
            }
        }
    }
}

void func_808566C0(PlayState* play, Player* this, PlayerBodyPart bodyPartIndex, f32 arg3, f32 arg4, f32 arg5,
                   s32 life) {
    Color_RGBA8 primColor = { 255, 200, 200, 0 };
    Color_RGBA8 envColor = { 255, 255, 0, 0 };
    static Vec3f D_8085D940 = { 0.0f, 0.3f, 0.0f };
    static Vec3f D_8085D94C = { 0.0f, -0.025f, 0.0f };
    Vec3f pos;
    s32 scale;
    f32 sp34;
    Vec3f* temp_v0;

    if (Rand_ZeroOne() < 0.5f) {
        sp34 = -1.0f;
    } else {
        sp34 = 1.0f;
    }

    D_8085D940.x = (Rand_ZeroFloat(arg4) + arg3) * sp34;
    D_8085D94C.x = arg5 * sp34;
    if (Rand_ZeroOne() < 0.5f) {
        sp34 = -1.0f;
    } else {
        sp34 = 1.0f;
    }

    temp_v0 = &this->bodyPartsPos[bodyPartIndex];
    D_8085D940.z = (Rand_ZeroFloat(arg4) + arg3) * sp34;
    D_8085D94C.z = arg5 * sp34;
    pos.x = temp_v0->x;
    pos.y = Rand_ZeroFloat(15.0f) + temp_v0->y;
    pos.z = temp_v0->z;
    if (Rand_ZeroOne() < 0.5f) {
        scale = 2000;
    } else {
        scale = -150;
    }

    EffectSsKirakira_SpawnDispersed(play, &pos, &D_8085D940, &D_8085D94C, &primColor, &envColor, scale, life);
}

void func_8085687C(Player* this) {
}

s32 func_80856888(f32* arg0, f32 arg1, f32 arg2) {
    if (arg2 != 0.0f) {
        if (arg1 < *arg0) {
            arg2 = -arg2;
        }

        *arg0 += arg2;
        if (((*arg0 - arg1) * arg2) >= 0.0f) {
            *arg0 = arg1;
            return true;
        }
    } else if (arg1 == *arg0) {
        return true;
    }

    return false;
}

f32 D_8085D958[] = { 600.0f, 960.0f };
Vec3f D_8085D960 = { -30.0f, 50.0f, 0.0f };
Vec3f D_8085D96C = { 30.0f, 50.0f, 0.0f };

// Flying as Deku?
void Player_Action_94(Player* this, PlayState* play) {
    if ((this->boomerangActor != NULL) && (this->boomerangActor->update == NULL)) {
        this->boomerangActor = NULL;
    }

    if (Player_ActionChange_13(this, play)) {
        return;
    }

    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        func_80837134(play, this);
        return;
    }

    if ((this->actor.velocity.y > 0.0f) && (this->stateFlags3 & PLAYER_STATE3_200)) {
        this->actor.terminalVelocity = -20.0f;
        this->actor.gravity = -5.5f;
        Player_SetCylinderForAttack(this, DMG_DEKU_LAUNCH, 2, 20);
        func_80856110(play, this, 0.0f, 0.0f, -1.0f, 500, 0, 8);

        if (this->actor.bgCheckFlags & BGCHECKFLAG_CEILING) {
            func_80833AA0(this, play);
        }
    } else if (!(this->stateFlags3 & PLAYER_STATE3_2000)) {
        func_80833AA0(this, play);
    } else if (this->stateFlags3 & PLAYER_STATE3_200) {
        if (this->actor.velocity.y < 0.0f) {
            if (this->actionVar1 < 0) {
                func_80833AA0(this, play);
            } else {
                PlayerAnimation_Update(play, &this->skelAnime);
                if (this->skelAnime.curFrame > 6.0f) {
                    this->actor.velocity.y = 6.0f;
                    this->stateFlags3 &= ~PLAYER_STATE3_200;
                    this->stateFlags3 |= PLAYER_STATE3_1000000;
                    func_8082E1F0(this, NA_SE_IT_DEKUNUTS_FLOWER_OPEN);
                    Audio_SetSfxTimerLerpInterval(4, 2);
                }
            }
        }

        this->actor.terminalVelocity = -10.0f;
        this->actor.gravity = -0.5f;
        Player_ResetCylinder(this);
    } else if (CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_A)) {
        func_808355D8(play, this, &gPlayerAnim_pn_kakkufinish);
    } else {
        s16 temp_a0;
        f32 temp_fv1;
        s16 sp76;
        s16 var_v1;
        s16 var_a1;
        f32 speedTarget;
        f32 sp68;
        s16 yawTarget;
        s16 temp_ft0;
        s32 temp;
        s16 var_v1_4;

        this->linearVelocity = sqrtf(SQXZ(this->actor.velocity));
        if (this->linearVelocity != 0.0f) {
            var_a1 = Math_Atan2S_XY(this->actor.velocity.z, this->actor.velocity.x);

            temp_a0 = this->actor.shape.rot.y - var_a1;
            if (ABS_ALT(temp_a0) > 0x4000) {
                this->linearVelocity = -this->linearVelocity;
                var_a1 = var_a1 + 0x8000;
            }
            this->currentYaw = var_a1;
        }

        if (this->windSpeed != 0.0f) {
            Math_SmoothStepToS(&this->unk_B8C, this->windAngleX, 3, 0x1F40, 0x190);
        }

        func_8085687C(this);

        if (this->actionVar2 != 0) {
            this->actionVar2--;
        }

        temp_fv1 = D_8085D958[this->actionVar1] - Math_Vec3f_DistXZ(&this->actor.world.pos, this->unk_AF0);
        PlayerAnimation_Update(play, &this->skelAnime);

        if ((this->actionVar2 != 0) && (temp_fv1 > 300.0f)) {
            sp76 = 0x1770;
            if (this->skelAnime.animation != &gPlayerAnim_pn_kakku) {
                func_8082E5EC(play, this, &gPlayerAnim_pn_kakkufinish);
            } else if (PlayerAnimation_OnFrame(&this->skelAnime, 8.0f)) {
                s32 i;

                Player_TranslateAndRotateY(this, &this->actor.world.pos, &D_8085D960,
                                           &this->bodyPartsPos[PLAYER_BODYPART_LEFT_HAND]);
                Player_TranslateAndRotateY(this, &this->actor.world.pos, &D_8085D96C,
                                           &this->bodyPartsPos[PLAYER_BODYPART_RIGHT_HAND]);

                for (i = 0; i < 13; i++) {
                    func_808566C0(play, this, PLAYER_BODYPART_LEFT_HAND, 0.6f, 1.0f, 0.8f, 17);
                    func_808566C0(play, this, PLAYER_BODYPART_RIGHT_HAND, 0.6f, 1.0f, 0.8f, 17);
                }
            }
        } else if ((this->actionVar2 == 0) || (temp_fv1 < 0.0f)) {
            sp76 = 0;
            func_808355D8(play, this, &gPlayerAnim_pn_rakkafinish);
        } else {
            sp76 = 0x1770 - (s32)((300.0f - temp_fv1) * 10.0f);

            if (this->skelAnime.animation != &gPlayerAnim_pn_batabata) {
                func_8082E55C(play, this, &gPlayerAnim_pn_batabata);
            } else if (PlayerAnimation_OnFrame(&this->skelAnime, 6.0f)) {
                Player_PlaySfx(this, NA_SE_PL_DEKUNUTS_STRUGGLE);
            }
        }

        Math_AsymStepToS(&this->unk_B86[1], sp76, 0x190, 0x190);

        this->unk_B8A += this->unk_B86[1];
        temp = ABS_ALT(this->unk_B86[1]);
        if (temp > 0xFA0) {
            this->unk_B66 += (u8)(ABS_ALT(this->unk_B86[1]) * 0.01f);
        }

        if (this->unk_B66 > 200) {
            this->unk_B66 -= 200;
            func_808566C0(play, this, PLAYER_BODYPART_LEFT_HAND, 0.0f, 1.0f, 0.0f, 32);
            func_808566C0(play, this, PLAYER_BODYPART_RIGHT_HAND, 0.0f, 1.0f, 0.0f, 32);
        }

        Audio_PlaySfx_AtPosWithTimer(&this->actor.projectedPos, 0x1851, 2.0f * (this->unk_B86[1] * (1.0f / 6000.0f)));
        if ((this->boomerangActor == NULL) && CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_B)) {
            if (AMMO(ITEM_DEKU_NUT) == 0) {
                Audio_PlaySfx(NA_SE_SY_ERROR);
            } else {
                this->boomerangActor =
                    Actor_Spawn(&play->actorCtx, play, ACTOR_EN_ARROW, this->bodyPartsPos[PLAYER_BODYPART_WAIST].x,
                                this->bodyPartsPos[PLAYER_BODYPART_WAIST].y,
                                this->bodyPartsPos[PLAYER_BODYPART_WAIST].z, -1, 0, 0, ARROW_TYPE_DEKU_NUT);
                if (this->boomerangActor != NULL) {
                    this->boomerangActor->velocity.x = this->actor.velocity.x * 1.5f;
                    this->boomerangActor->velocity.z = this->actor.velocity.z * 1.5f;
                    Inventory_ChangeAmmo(ITEM_DEKU_NUT, -1);
                    Actor_PlaySfx(this->boomerangActor, NA_SE_PL_DEKUNUTS_DROP_BOMB);
                }
            }
        }

        if (this->actor.velocity.y < 0.0f) {
            if (sp76 != 0) {
                this->actor.terminalVelocity = -0.38f;
                this->actor.gravity = -0.2f;
            } else {
                this->actor.terminalVelocity = (this->unk_B86[1] * 0.0033f) + -20.0f;
                this->actor.gravity = (this->unk_B86[1] * 0.00004f) + (REG(68) / 100.0f);
            }
        }

        this->fallStartHeight = this->actor.world.pos.y;
        Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);

        if (speedTarget == 0.0f) {
            sp68 = 0.1f;
        } else {
            s16 temp_v0_6 = this->currentYaw - yawTarget;

            if (ABS_ALT(temp_v0_6) > 0x4000) {
                speedTarget = -speedTarget;
                yawTarget += 0x8000;
            }
            sp68 = 0.25f;
        }

        Math_SmoothStepToS(&this->unk_B8C, speedTarget * 600.0f, 8, 0xFA0, 0x64);
        Math_ScaledStepToS(&this->currentYaw, yawTarget, 0xFA);

        temp_ft0 = BINANG_SUB(yawTarget, this->currentYaw) * -2.0f;
        temp_ft0 = CLAMP(temp_ft0, -0x1F40, 0x1F40);
        Math_SmoothStepToS(&this->unk_B8E, temp_ft0, 0x14, 0x320, 0x14);
        speedTarget = (speedTarget * (this->unk_B86[1] * 0.0004f)) * fabsf(Math_SinS(this->unk_B8C));
        func_80856888(&this->linearVelocity, speedTarget, sp68);

        speedTarget = sqrtf(SQ(this->linearVelocity) + SQ(this->actor.velocity.y));
        if (speedTarget > 8.0f) {
            speedTarget = 8.0f / speedTarget;
            this->linearVelocity *= speedTarget;
            this->actor.velocity.y *= speedTarget;
        }
    }

    func_808378FC(play, this);
}

// Deku spinning related
void Player_Action_95(Player* this, PlayState* play) {
    this->stateFlags2 |= PLAYER_STATE2_20 | PLAYER_STATE2_40;

    PlayerAnimation_Update(play, &this->skelAnime);
    Player_SetCylinderForAttack(this, DMG_DEKU_SPIN, 1, 30);

    if (!Player_ActionChange_13(this, play)) {
        s16 prevYaw = this->currentYaw;
        f32 speedTarget;
        s16 yawTarget;

        Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_CURVED, play);
        speedTarget *= 1.0f - (0.9f * ((11100.0f - this->unk_B10[0]) / 11100.0f));

        if (!func_8083A4A4(this, &speedTarget, &yawTarget, REG(43) / 100.0f)) {
            func_8083CB58(this, speedTarget, yawTarget);
        }

        this->unk_B10[0] += -800.0f;
        this->actor.shape.rot.y += BINANG_ADD((s16)this->unk_B10[0], BINANG_SUB(this->currentYaw, prevYaw));

        if (Math_StepToF(&this->unk_B10[1], 0.0f, this->unk_B10[0])) {
            this->actor.shape.rot.y = this->currentYaw;
            func_8083B2E4(this, play);
        } else if (this->skelAnime.animation == &gPlayerAnim_pn_attack) {
            this->stateFlags3 |= PLAYER_STATE3_100000;

            if (this->unk_B10[1] < 0.0f) {
                func_8082E438(play, this, func_8082ED20(this));
            }
        }

        func_808566C0(play, this, PLAYER_BODYPART_WAIST, 1.0f, 0.5f, 0.0f, 32);

        if (this->unk_B10[0] > 9500.0f) {
            func_8083F8A8(play, this, 2.0f, 1, 2.5f, 10, 18, true);
        }

        func_800AE930(&play->colCtx, Effect_GetByIndex(this->meleeWeaponEffectIndex[2]), &this->actor.world.pos, 2.0f,
                      this->currentYaw, this->actor.floorPoly, this->actor.floorBgId);
        Actor_PlaySfx_FlaggedCentered1(&this->actor, Player_GetFloorSfx(this, NA_SE_PL_SLIP_LEVEL - SFX_FLAG));
    }
}

void func_80857640(Player* this, f32 arg1, s32 arg2) {
    func_80834CD0(this, arg1, NA_SE_VO_LI_SWORD_N);
    Player_PlaySfx(this, NA_SE_PL_GORON_BALLJUMP);
    Player_StopHorizontalMovement(this);
    if (this->actionVar2 < arg2) {
        this->actionVar2 = arg2;
    }
    this->actionVar1 = 1;
    this->unk_B48 = 1.0f;
}

void func_808576BC(PlayState* play, Player* this) {
    s32 var_v0 = ((this->actor.velocity.z * Math_CosS(this->currentYaw)) +
                  (this->actor.velocity.x * Math_SinS(this->currentYaw))) *
                 800.0f;

    var_v0 -= this->actionVar2;
    var_v0 = ABS_ALT(var_v0);

    if (var_v0 <= 0x7D0) {
        return;
    }

    if (var_v0 > 0x1770) {
        Actor_PlaySfx_FlaggedCentered1(&this->actor, NA_SE_PL_GORON_SLIP - SFX_FLAG);
    }

    if (func_8083F8A8(play, this, 12.0f, -1 - (var_v0 >> 0xC), (var_v0 >> 0xA) + 1.0f, (var_v0 >> 7) + 160, 20, true)) {
        Player_PlaySfx(this, (this->floorSfxOffset == NA_SE_PL_WALK_SNOW - SFX_FLAG)
                                 ? NA_SE_PL_ROLL_SNOW_DUST - SFX_FLAG
                                 : NA_SE_PL_ROLL_DUST - SFX_FLAG);
    }
}

void func_808577E0(Player* this) {
    f32 temp_fa1 = ABS_ALT(this->actionVar2) * 0.00004f;

    if (this->unk_ABC < temp_fa1) {
        this->unk_B48 += 0.08f;
    } else {
        this->unk_B48 += -0.07f;
    }

    this->unk_B48 = CLAMP(this->unk_B48, -0.2f, 0.14f);
    if (fabsf(this->unk_B48) < 0.12f) {
        if (Math_StepUntilF(&this->unk_ABC, temp_fa1, this->unk_B48)) {
            this->unk_B48 = 0.0f;
        }
    } else {
        this->unk_ABC += this->unk_B48;
        this->unk_ABC = CLAMP(this->unk_ABC, -0.7f, 0.3f);
    }
}

s32 func_80857950(PlayState* play, Player* this) {
    if (((this->unk_B86[1] == 0) && !CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_A)) ||
        ((this->actionVar1 == 3) && (this->actor.velocity.y < 0.0f))) {
        Player_SetAction(play, this, Player_Action_4, 1);
        Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.prevPos);
        PlayerAnimation_Change(play, &this->skelAnime, &gPlayerAnim_pg_maru_change, -2.0f / 3.0f, 7.0f, 0.0f,
                               ANIMMODE_ONCE, 0.0f);
        Player_PlaySfx(this, NA_SE_PL_BALL_TO_GORON);
        return true;
    }

    return false;
}

s32 func_80857A44(PlayState* play, Player* this) {
    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        func_8082E794(this);

        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.bgCheckFlags |= BGCHECKFLAG_PLAYER_800;
        this->actionVar1 = 4;
        this->actor.shape.shadowScale = 30.0f;
        this->actionVar2 = this->linearVelocity * 500.0f;
        this->unk_B08 = this->linearVelocity;
        this->unk_B0C = 0.0f;
        this->actor.home.rot.y = this->currentYaw;

        return true;
    }

    return false;
}

void func_80857AEC(PlayState* play, Player* this) {
    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND_TOUCH) {
        this->unk_B0C += this->unk_B08 * 0.05f;

        if (this->unk_B86[1] == 0) {
            if (this->actionVar1 == 1) {
                this->actionVar1 = 2;
                Player_RequestQuakeAndRumble(play, this, NA_SE_PL_GORON_PUNCH);
                play->actorCtx.unk2 = 4;
                EffectSsBlast_SpawnWhiteShockwave(play, &this->actor.world.pos, &gZeroVec3f, &gZeroVec3f);
                this->actionVar2 = 0;
                this->unk_B08 = 0.0f;
                Actor_Spawn(&play->actorCtx, play, ACTOR_EN_TEST, this->actor.world.pos.x, this->actor.world.pos.y,
                            this->actor.world.pos.z, 0, 0, 0, 0);
            } else {
                this->actionVar1 = 4;
            }
        }

        Player_AnimSfx_PlayFloorLand(this);
    }
}

// Goron rolling related
void Player_Action_96(Player* this, PlayState* play) {
    if (Player_TryActionChangeList(play, this, sPlayerActionChangeList12, false)) {
        return;
    }

    if ((this->actionVar1 == 0) && !func_80857A44(play, this)) {
        return;
    }

    this->stateFlags3 |= PLAYER_STATE3_1000;
    func_808577E0(this);

    if (!func_80857950(play, this)) {
        f32 speedTarget = 0.0f;
        s16 yawTarget = this->currentYaw;
        u16 spE0;
        s32 spDC;
        s32 spD8;

        if (func_80840A30(play, this, &this->unk_B08, (this->doorType == PLAYER_DOORTYPE_STAIRCASE) ? 0.0f : 12.0f)) {
            if (Player_Action_96 != this->actionFunc) {
                return;
            }

            this->linearVelocity *= 0.1f;
            func_80834CD0(this, 10.0f, 0);
            if (this->unk_B86[1] != 0) {
                this->unk_B86[1] = 0;
                this->actionVar1 = 3;
            }
        } else if ((this->actor.bgCheckFlags & BGCHECKFLAG_WALL) && (this->unk_B08 >= 12.0f)) {
            s16 temp_v0 = this->currentYaw - BINANG_ADD(this->actor.wallYaw, 0x8000);
            s16 temp_v2;
            s32 var_a2 = ABS_ALT(temp_v0);

            this->unk_B0C += this->unk_B08 * 0.05f;
            temp_v2 = ((temp_v0 >= 0) ? 1 : -1) * ((var_a2 + 0x100) & ~0x1FF);
            this->currentYaw += BINANG_SUB(0x8000, (s16)(temp_v2 * 2));
            this->actor.home.rot.y = this->currentYaw;
            this->actor.shape.rot.y = this->currentYaw;

            this->unk_B8C = 4;
            Player_PlaySfx(this, NA_SE_IT_GORON_ROLLING_REFLECTION);
        }

        this->stateFlags2 |= (PLAYER_STATE2_20 | PLAYER_STATE2_40);

        if (this->unk_B8E != 0) {
            this->unk_B8E--;
        } else {
            Player_GetMovementSpeedAndYaw(this, &speedTarget, &yawTarget, SPEED_MODE_LINEAR, play);
            speedTarget *= 2.6f;
        }

        if (this->unk_B8C != 0) {
            this->unk_B8C--;
            yawTarget = this->currentYaw;
        }

        if (this->unk_B86[1] != 0) {
            speedTarget = 18.0f;
            Math_StepToC(&this->actionVar1, 4, 1);

            if ((this->stateFlags3 & PLAYER_STATE3_80000) && (!CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_A) ||
                                                              (gSaveContext.save.saveInfo.playerData.magic == 0) ||
                                                              ((this->actionVar1 == 4) && (this->unk_B08 < 12.0f)))) {
                if (Math_StepToS(&this->unk_B86[1], 0, 1)) {
                    this->stateFlags3 &= ~PLAYER_STATE3_80000;
                    Magic_Reset(play);
                    Player_PlaySfx(this, NA_SE_PL_GORON_BALL_CHARGE_FAILED);
                }
                this->actionVar1 = 4;
            } else if (this->unk_B86[1] < 7) {
                if (!(this->stateFlags3 & PLAYER_STATE3_80000)) {
                    this->unk_3D0.unk_00 = 2;
                }
                this->unk_B86[1]++;
            }
        }

        spDC = speedTarget * 900.0f;

        Math_AsymStepToF(&this->unk_B10[0], (this->unk_B8A != 0) ? 1.0f : 0.0f, 0.8f, 0.05f);
        if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
            func_80857AEC(play, this);
            if (this->actionVar1 == 2) {
                if (this->unk_B8A == 0) {
                    this->actionVar1 = 4;
                } else {
                    this->unk_B8A--;
                    this->unk_ABC = 0.0f;
                    this->unk_B48 = 0.14f;
                }
            } else if ((this->unk_B86[1] == 0) && CHECK_BTN_ALL(sPlayerControlInput->press.button, BTN_B) &&
                       (Inventory_GetBtnBItem(play) < ITEM_FD)) {
                func_80857640(this, 14.0f, 0x1F40);
            } else {
                f32 spCC;
                s16 spCA;
                s16 spC8;
                s32 var_a0;
                s32 spC0;
                f32 spBC;
                f32 spB8;
                f32 spB4;
                f32 spB0;
                f32 spAC;
                f32 spA8;
                f32 spA4;
                f32 spA0;
                Vec3f slopeNormal;
                s16 downwardSlopeYaw;
                s16 sp90 = this->currentYaw;
                s16 sp8E = this->currentYaw - this->actor.home.rot.y;
                f32 sp88 = Math_CosS(sp8E);

                if (this->unk_B86[1] == 0) {
                    this->unk_B0C = 0.0f;
                    if (this->actionVar1 >= 0x36) {
                        Magic_Consume(play, 2, MAGIC_CONSUME_GORON_ZORA);
                        this->unk_B08 = 18.0f;
                        this->unk_B86[1] = 1;
                        this->stateFlags3 |= PLAYER_STATE3_80000;
                        func_8082E1F0(this, NA_SE_PL_GORON_BALL_CHARGE_DASH);
                    }
                } else {
                    this->unk_B0C = CLAMP(this->unk_B0C, 0.0f, 0.9f);
                }

                spBC = (1.0f - this->unk_B0C) * this->unk_B08 * sp88;
                if ((spBC < 0.0f) || ((speedTarget == 0.0f) && (ABS_ALT(sp8E) > 0xFA0))) {
                    spBC = 0.0f;
                }

                Math_StepToF(&this->unk_B0C, 0.0f, fabsf(sp88) * 20.0f);
                var_a0 = spBC * 500.0f;
                var_a0 = CLAMP_MIN(var_a0, 0);

                spC0 = (s32)(speedTarget * 400.0f) - var_a0;
                spC0 = CLAMP_MIN(spC0, 0);

                spDC = CLAMP_MIN(spDC, var_a0);

                spAC = spBC * Math_SinS(this->actor.home.rot.y);
                spA8 = spBC * Math_CosS(this->actor.home.rot.y);
                spB4 = this->unk_B08 * Math_SinS(this->currentYaw);
                spB0 = this->unk_B08 * Math_CosS(this->currentYaw);

                spA4 = spB4 - spAC;
                spA0 = spB0 - spA8;
                this->linearVelocity = spBC;
                this->currentYaw = this->actor.home.rot.y;
                spCC = speedTarget;
                spCA = yawTarget;

                if (func_8083A4A4(this, &spCC, &spCA, (this->actionVar1 >= 5) ? 0.0f : 1.0f)) {
                    if (this->unk_B86[1] == 0) {
                        this->actionVar1 = 4;
                    }

                    if (this->actionVar1 == 4) {
                        spDC = -0xFA0;
                    }
                } else {
                    static Vec3f D_8085D978 = { -30.0f, 60.0f, 0.0f };
                    static Vec3f D_8085D984 = { 30.0f, 60.0f, 0.0f };
                    f32 sp84 = (((this->floorSfxOffset == NA_SE_PL_WALK_SNOW - SFX_FLAG) ||
                                 (this->floorSfxOffset == NA_SE_PL_WALK_ICE - SFX_FLAG) ||
                                 (this->floorSfxOffset == NA_SE_PL_WALK_SAND - SFX_FLAG) ||
                                 (sPlayerFloorType == FLOOR_TYPE_5)) &&
                                (spC0 >= 0x7D0))
                                   ? 0.08f
                                   : this->actionVar2 * 0.0003f;
                    f32 sp80 = (Math_SinS(this->floorPitch) * 8.0f) + 0.6f;
                    s16 var_a3;
                    s16 sp7C;
                    Vec3f sp70;
                    f32 sp6C;
                    f32 var_fa1;

                    if (this->unk_B86[1] == 0) {
                        if ((gSaveContext.magicState == MAGIC_STATE_IDLE) &&
                            (gSaveContext.save.saveInfo.playerData.magic >= 2) && (this->actionVar2 >= 0x36B0)) {
                            this->actionVar1++;
                            Actor_PlaySfx_FlaggedCentered1(&this->actor, NA_SE_PL_GORON_BALL_CHARGE - SFX_FLAG);
                        } else {
                            this->actionVar1 = 4;
                        }
                    }

                    if (speedTarget != spCC) {
                        this->currentYaw = yawTarget;
                    }

                    sp84 = CLAMP_MIN(sp84, 0.0f);
                    sp80 = CLAMP_MIN(sp80, 0.0f);

                    Math_AsymStepToF(&this->linearVelocity, speedTarget, sp84, sp80);
                    spC8 = (s16)(fabsf(this->actor.speed) * 20.0f) + 300;
                    spC8 = CLAMP_MIN(spC8, 100);

                    sp7C = (s32)(BINANG_SUB(yawTarget, this->currentYaw) * -0.5f);
                    this->unk_B0C += (f32)(SQ(sp7C)) * 8e-9f;
                    Math_ScaledStepToS(&this->currentYaw, yawTarget, spC8);
                    sp6C = func_80835D2C(play, this, &D_8085D978, &sp70);

                    var_fa1 = func_80835D2C(play, this, &D_8085D984, &sp70) - sp6C;
                    if (fabsf(var_fa1) > 100.0f) {
                        var_fa1 = 0.0f;
                    }

                    var_a3 = Math_Atan2S_XY(60.0f, var_fa1);
                    if (ABS_ALT(var_a3) > 0x2AAA) {
                        var_a3 = 0;
                    }

                    Math_ScaledStepToS(&this->actor.shape.rot.z, var_a3 + sp7C, spC8);
                }

                spBC = this->linearVelocity;
                this->actor.home.rot.y = this->currentYaw;
                this->currentYaw = sp90;
                Actor_GetSlopeDirection(this->actor.floorPoly, &slopeNormal, &downwardSlopeYaw);

                spB8 = sqrtf(SQ(spA4) + SQ(spA0));
                if (this->unk_B86[1] != 0) {
                    if ((ABS_ALT(sp8E) + ABS_ALT(this->floorPitch)) > 0x3A98) {
                        this->unk_B86[1] = 0;
                        this->actionVar1 = 4;
                        this->unk_B8E = 0x14;
                        this->actionVar2 = 0;
                        this->stateFlags3 &= ~PLAYER_STATE3_80000;
                        Magic_Reset(play);
                    }
                } else {
                    f32 temp_ft4_2 = (0.6f * slopeNormal.x) + spA4;
                    f32 temp_ft5 = (0.6f * slopeNormal.z) + spA0;
                    f32 temp_fv0_3 = sqrtf(SQ(temp_ft4_2) + SQ(temp_ft5));

                    if ((temp_fv0_3 < spB8) || (temp_fv0_3 < 6.0f)) {
                        spA4 = temp_ft4_2;
                        spA0 = temp_ft5;
                        spB8 = temp_fv0_3;
                    }
                }

                if (spB8 != 0.0f) {
                    f32 pad;
                    f32 sp54 = spB8 - 0.3f;

                    sp54 = CLAMP_MIN(sp54, 0.0f);

                    spB8 = sp54 / spB8;

                    spA4 *= spB8;
                    spA0 *= spB8;

                    if (sp54 != 0.0f) {
                        this->unk_B28 = Math_Atan2S_XY(spA0, spA4);
                    }

                    if (this->actionVar2 == 0) {
                        s32 temp_v0_10 = this->unk_B86[0];
                        s32 temp_ft3_2 = sp54 * 800.0f;

                        this->unk_B86[0] += (s16)temp_ft3_2;
                        if ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && (temp_ft3_2 != 0) &&
                            (((temp_v0_10 + temp_ft3_2) * temp_v0_10) <= 0)) {
                            spE0 = Player_GetFloorSfx(this, NA_SE_PL_GORON_ROLL);
                            Audio_PlaySfx_AtPosWithSyncedFreqAndVolume(&this->actor.projectedPos, spE0, sp54);
                        }
                    }
                }

                spAC = Math_SinS(this->actor.home.rot.y) * spBC;
                spA8 = Math_CosS(this->actor.home.rot.y) * spBC;

                spB4 = spAC + spA4;
                spB0 = spA8 + spA0;

                this->unk_B08 = sqrtf(SQ(spB4) + SQ(spB0));
                this->unk_B08 = CLAMP_MAX(this->unk_B08, 18.0f);

                this->currentYaw = Math_Atan2S_XY(spB0, spB4);
            }

            func_808576BC(play, this);

            if (ABS_ALT(this->actionVar2) > 0xFA0) {
                this->stateFlags2 |= PLAYER_STATE2_8;
            }

            if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
                this->linearVelocity = this->unk_B08 * Math_CosS(this->floorPitch);
                this->actor.velocity.y = this->unk_B08 * Math_SinS(this->floorPitch);
            }

            if ((this->unk_B86[1] != 0) ||
                SurfaceType_HasMaterialProperty(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId,
                                                MATERIAL_PROPERTY_SOFT_IMPRINT)) {
                func_800AE930(&play->colCtx, Effect_GetByIndex(this->meleeWeaponEffectIndex[2]), &this->actor.world.pos,
                              15.0f, this->actor.shape.rot.y, this->actor.floorPoly, this->actor.floorBgId);
            } else {
                func_800AEF44(Effect_GetByIndex(this->meleeWeaponEffectIndex[2]));
            }
        } else {
            Math_ScaledStepToS(&this->actor.shape.rot.z, 0, 0x190);

            this->unk_B86[0] = 0;
            if (this->unk_B86[1] != 0) {
                this->actor.gravity = -1.0f;
                Math_ScaledStepToS(&this->actor.home.rot.y, yawTarget, 0x190);

                this->unk_B08 = sqrtf(SQ(this->linearVelocity) + SQ(this->actor.velocity.y)) *
                                ((this->linearVelocity >= 0.0f) ? 1.0f : -1.0f);
                this->unk_B08 = CLAMP_MAX(this->unk_B08, 18.0f);
            } else {
                this->unk_B48 += this->actor.velocity.y * 0.005f;
                if (this->actionVar1 == 1) {
                    if (this->actor.velocity.y > 0.0f) {
                        if ((this->actor.velocity.y + this->actor.gravity) < 0.0f) {
                            this->actor.velocity.y = -this->actor.gravity;
                        }
                    } else {
                        this->unk_B8A = 0xA;
                        if (this->actor.velocity.y > -1.0f) {
                            this->actor.gravity = -0.2f;
                        } else {
                            this->unk_3D0.unk_00 = 1;
                            this->actor.gravity = -10.0f;
                        }
                    }
                }
                this->unk_B08 = this->linearVelocity;
            }

            func_800AEF44(Effect_GetByIndex(this->meleeWeaponEffectIndex[2]));
        }

        Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 0x7D0);

        Math_AsymStepToS(&this->actionVar2, spDC, (spDC >= 0) ? 0x7D0 : 0x3E8, 0x4B0);

        if (this->actionVar2 != 0) {
            spD8 = this->actor.shape.rot.x;
            this->actor.shape.rot.x += this->actionVar2;

            Math_ScaledStepToS(&this->unk_B86[0], 0, ABS_ALT(this->actionVar2));
            if ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && (((this->actionVar2 + spD8) * spD8) <= 0)) {
                spE0 =
                    Player_GetFloorSfx(this, (this->unk_B86[1] != 0) ? NA_SE_PL_GORON_CHG_ROLL : NA_SE_PL_GORON_ROLL);
                Audio_PlaySfx_AtPosWithSyncedFreqAndVolume(&this->actor.projectedPos, spE0, this->unk_B08);
            }
        }

        if (this->actionVar1 == 2) {
            Player_SetCylinderForAttack(this, DMG_GORON_POUND, 4, 60);
            Actor_SetPlayerImpact(play, PLAYER_IMPACT_GORON_GROUND_POUND, 2, 100.0f, &this->actor.world.pos);
        } else if (this->unk_B86[1] != 0) {
            Player_SetCylinderForAttack(this, DMG_GORON_SPIKES, 1, 25);
        } else {
            Player_SetCylinderForAttack(this, DMG_NORMAL_ROLL, 1, 25);
        }
    }
}

void func_80858C84(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    func_8082E784(this);
    func_8082E438(play, this, anim);
    Player_StopHorizontalMovement(this);
}

void func_80858CC8(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    func_8082E784(this);
    PlayerAnimation_Change(play, &this->skelAnime, anim, 2.0f / 3.0f, 0.0f, Animation_GetLastFrame(anim), ANIMMODE_ONCE,
                           -8.0f);
    Player_StopHorizontalMovement(this);
}

void func_80858D48(PlayState* play, Player* this, PlayerAnimationHeader* anim) {
    func_8082E784(this);
    PlayerAnimation_Change(play, &this->skelAnime, anim, 2.0f / 3.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -8.0f);
    Player_StopHorizontalMovement(this);
}

PlayerCsAnim sPlayerCsModeAnimFuncs[] = {
    NULL,             // PLAYER_CSTYPE_NONE
    Player_CsAnim_1,  // PLAYER_CSTYPE_ANIM_1
    Player_CsAnim_2,  // PLAYER_CSTYPE_ANIM_2
    Player_CsAnim_3,  // PLAYER_CSTYPE_ANIM_3
    Player_CsAnim_4,  // PLAYER_CSTYPE_ANIM_4
    Player_CsAnim_5,  // PLAYER_CSTYPE_ANIM_5
    Player_CsAnim_6,  // PLAYER_CSTYPE_ANIM_6
    Player_CsAnim_7,  // PLAYER_CSTYPE_ANIM_7
    Player_CsAnim_8,  // PLAYER_CSTYPE_ANIM_8
    Player_CsAnim_9,  // PLAYER_CSTYPE_ANIM_9
    Player_CsAnim_10, // PLAYER_CSTYPE_ANIM_10
    Player_CsAnim_11, // PLAYER_CSTYPE_ANIM_11
    Player_CsAnim_12, // PLAYER_CSTYPE_ANIM_12
    Player_CsAnim_13, // PLAYER_CSTYPE_ANIM_13
    Player_CsAnim_14, // PLAYER_CSTYPE_ANIM_14
    Player_CsAnim_15, // PLAYER_CSTYPE_ANIM_15
    Player_CsAnim_16, // PLAYER_CSTYPE_ANIM_16
    Player_CsAnim_17, // PLAYER_CSTYPE_ANIM_17
    Player_CsAnim_18, // PLAYER_CSTYPE_ANIM_18
    Player_CsAnim_19, // PLAYER_CSTYPE_ANIM_19
};

void Player_CsAnim_1(PlayState* play, Player* this, void* arg2) {
    Player_StopHorizontalMovement(this);
}

void Player_CsAnim_2(PlayState* play, Player* this, void* anim) {
    func_80858C84(play, this, anim);
}

void Player_CsAnim_14(PlayState* play, Player* this, void* anim) {
    func_8082E784(this);
    func_8082E5A8(play, this, anim);
    Player_StopHorizontalMovement(this);
}

void Player_CsAnim_3(PlayState* play, Player* this, void* anim) {
    func_80858CC8(play, this, anim);
}

void Player_CsAnim_4(PlayState* play, Player* this, void* anim) {
    func_80858D48(play, this, anim);
}

void Player_CsAnim_5(PlayState* play, Player* this, void* anim) {
    func_8082EA60(play, this, anim);
}

void Player_CsAnim_6(PlayState* play, Player* this, void* anim) {
    func_8082EA10(play, this, anim, ANIM_FLAG_4 | ANIM_FLAG_8 | ANIM_FLAG_NOMOVE | ANIM_FLAG_80);
}

void Player_CsAnim_19(PlayState* play, Player* this, void* anim) {
    Player_AnimationPlayOnceReverse(play, this, anim);
    func_8082E920(play, this, ANIM_FLAG_4 | ANIM_FLAG_8 | ANIM_FLAG_NOMOVE | ANIM_FLAG_80);
}

void Player_CsAnim_7(PlayState* play, Player* this, void* anim) {
    func_8082EB18(play, this, anim);
}

void Player_CsAnim_8(PlayState* play, Player* this, void* anim) {
    func_8082EAC8(play, this, anim, ANIM_FLAG_4 | ANIM_FLAG_8 | ANIM_FLAG_NOMOVE | ANIM_FLAG_80);
}

void Player_CsAnim_9(PlayState* play, Player* this, void* anim) {
    Player_AnimationPlayOnce(play, this, anim);
}

void Player_CsAnim_10(PlayState* play, Player* this, void* anim) {
    Player_AnimationPlayLoop(play, this, anim);
}

void Player_CsAnim_15(PlayState* play, Player* this, void* anim) {
    func_8082DB90(play, this, anim);
}

void Player_CsAnim_16(PlayState* play, Player* this, void* anim) {
    func_8082DB60(play, this, anim);
}

void Player_CsAnim_11(PlayState* play, Player* this, void* cue) {
    PlayerAnimation_Update(play, &this->skelAnime);
}

void func_80858FE8(Player* this) {
    if (this->skelAnime.animation == &gPlayerAnim_lost_horse_wait) {
        Player_AnimSfx_PlayFloor(this, NA_SE_PL_SLIP_LEVEL - SFX_FLAG);
        Player_PlaySfx(this, NA_SE_VO_LK_DRAGGED_DAMAGE - SFX_FLAG);
    }
}

AnimSfxEntry D_8085D9E0[] = {
    ANIMSFX(ANIMSFX_TYPE_FLOOR_LAND, 34, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 45, NA_SE_PL_CALM_HIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 51, NA_SE_PL_CALM_HIT, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 64, NA_SE_PL_CALM_HIT, STOP),
};
AnimSfxEntry D_8085D9F0[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 7, NA_SE_VO_LI_DEMO_DAMAGE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_FLOOR, 18, NA_SE_PL_BOUND, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 18, NA_SE_VO_LI_FREEZE, STOP),
};
AnimSfxEntry D_8085D9FC[] = {
    ANIMSFX(ANIMSFX_TYPE_FLOOR_BY_AGE, 14, NA_SE_PL_LAND_GROUND, STOP),
};
AnimSfxEntry D_8085DA00[] = {
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 6, NA_SE_PL_GET_UP, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 18, NA_SE_VO_LK_WAKE_UP, STOP),
};
AnimSfxEntry D_8085DA08[] = {
    ANIMSFX(ANIMSFX_TYPE_FLOOR_BY_AGE, 26, NA_SE_PL_LAND_GROUND, STOP),
};
AnimSfxEntry D_8085DA0C[] = {
    ANIMSFX(ANIMSFX_TYPE_8, 16, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_FLOOR_JUMP, 36, NA_SE_NONE, STOP),
};
AnimSfxEntry D_8085DA14[] = {
    ANIMSFX(ANIMSFX_TYPE_FLOOR_JUMP, 55, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 55, NA_SE_VO_LK_CATCH_DEMO, STOP),
};
AnimSfxEntry D_8085DA1C[] = {
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 4, NA_SE_VO_LK_USING_UP_ENERGY, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_FLOOR, 16, NA_SE_PL_BOUND, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 16, NA_SE_VO_LI_DAMAGE_S, STOP),
};
AnimSfxEntry D_8085DA28[] = {
    ANIMSFX(ANIMSFX_TYPE_FLOOR_BY_AGE, 28, NA_SE_PL_LAND_GROUND, STOP),
};
AnimSfxEntry D_8085DA2C[] = {
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 1, NA_SE_VO_LK_USING_UP_ENERGY, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_FLOOR_JUMP, 42, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 44, NA_SE_VO_LI_FALL_L, STOP),
};
AnimSfxEntry D_8085DA38[] = {
    ANIMSFX(ANIMSFX_TYPE_FLOOR, 1, NA_SE_PL_BOUND, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 1, NA_SE_VO_LI_DAMAGE_S, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_FLOOR_BY_AGE, 39, NA_SE_PL_LAND_GROUND, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_FLOOR_LAND, 49, NA_SE_NONE, STOP),
};

// gPlayerAnim_cl_nigeru
AnimSfxEntry D_8085DA48[] = {
    ANIMSFX(ANIMSFX_TYPE_6, 1, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_6, 5, NA_SE_NONE, STOP),
};
AnimSfxEntry D_8085DA50[] = {
    ANIMSFX(ANIMSFX_TYPE_6, 10, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_6, 13, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_6, 16, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_6, 19, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_6, 22, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_FLOOR, 22, NA_SE_PL_SLIP, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_VOICE, 55, NA_SE_VO_LI_DAMAGE_S, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_FLOOR_LAND, 62, NA_SE_NONE, STOP),
};

AnimSfxEntry D_8085DA70[] = {
    ANIMSFX(ANIMSFX_TYPE_6, 42, NA_SE_NONE, CONTINUE),
    ANIMSFX(ANIMSFX_TYPE_6, 48, NA_SE_NONE, STOP),
};
AnimSfxEntry D_8085DA78[] = {
    ANIMSFX(ANIMSFX_TYPE_FLOOR, 2, NA_SE_PL_BOUND, STOP),
};
AnimSfxEntry D_8085DA7C[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 5, NA_SE_VO_LI_FREEZE, STOP),
};
AnimSfxEntry D_8085DA80[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 1, NA_SE_VO_LI_FALL_L, STOP),
};
AnimSfxEntry D_8085DA84[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 13, NA_SE_VO_LI_HANG, STOP),
};
AnimSfxEntry D_8085DA88[] = {
    ANIMSFX(ANIMSFX_TYPE_FLOOR_LAND, 26, NA_SE_NONE, STOP),
};
AnimSfxEntry D_8085DA8C[] = {
    ANIMSFX(ANIMSFX_TYPE_VOICE, 4, NA_SE_VO_LI_SURPRISE, STOP),
};
AnimSfxEntry D_8085DA90[] = {
    ANIMSFX(ANIMSFX_TYPE_GENERAL, 18, NA_SE_PL_SIT_ON_HORSE, STOP),
};

void Player_CsAnim_12(PlayState* play, Player* this, void* anim) {
    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        func_80858D48(play, this, anim);
        this->actionVar2 = 1;
    }

    if (this->skelAnime.animation == &gPlayerAnim_okiagaru_tatu) {
        Player_PlayAnimSfx(this, D_8085DA08);
    } else if (this->skelAnime.animation == &gPlayerAnim_lost_horse) {
        Player_PlayAnimSfx(this, D_8085DA14);
    } else if (this->skelAnime.animation == &gPlayerAnim_sirimochi) {
        Player_PlayAnimSfx(this, D_8085DA38);
    } else if (this->skelAnime.animation == &gPlayerAnim_alink_somukeru) {
        Player_PlayAnimSfx(this, D_8085DA7C);
    } else if (this->skelAnime.animation == &gPlayerAnim_al_fuwafuwa) {
        Player_PlayAnimSfx(this, D_8085DA84);
    } else if (this->skelAnime.animation == &gPlayerAnim_cl_umanoru) {
        Player_PlayAnimSfx(this, D_8085DA90);
    } else {
        func_80858FE8(this);
    }
}

void Player_CsAnim_17(PlayState* play, Player* this, void* anim) {
    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        func_8082E794(this);
        func_8082DB60(play, this, anim);
    }
}

void Player_CsAnim_13(PlayState* play, Player* this, void* anim) {
    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        func_8082EB18(play, this, anim);
        this->actionVar2 = 1;
    }
}

void Player_CsAnim_18(PlayState* play, Player* this, void* entry) {
    PlayerAnimation_Update(play, &this->skelAnime);
    Player_PlayAnimSfx(this, entry);
}

void func_80859248(Player* this) {
    if ((this->csActor == NULL) || (this->csActor->update == NULL)) {
        this->csActor = NULL;
    }
    this->lockOnActor = this->csActor;
    if (this->csActor != NULL) {
        this->actor.shape.rot.y = func_8083C62C(this, 0);
    }
}

void func_8085929C(PlayState* play, Player* this, UNK_TYPE arg2) {
    this->stateFlags1 |= PLAYER_STATE1_8000000;
    this->stateFlags2 |= PLAYER_STATE2_400;
    this->stateFlags1 &= ~(PLAYER_STATE1_40000 | PLAYER_STATE1_80000);
    Player_AnimationPlayLoop(play, this, &gPlayerAnim_link_swimer_swim);
    this->linearVelocity = 0.0f;
}

void func_80859300(PlayState* play, Player* this, UNK_TYPE arg2) {
    this->actor.gravity = 0.0f;

    if (this->actionVar1 == 0) {
        if ((this->transformation == PLAYER_FORM_DEKU) || func_8083B3B4(play, this, NULL)) {
            this->actionVar1 = 1;
        } else {
            func_808477D0(play, this, NULL, fabsf(this->actor.velocity.y));
            Math_ScaledStepToS(&this->unk_AAA, -0x2710, 0x320);
            func_8084748C(this, &this->actor.velocity.y, 4.0f, this->currentYaw);
        }
    } else {
        if (PlayerAnimation_Update(play, &this->skelAnime)) {
            if (this->actionVar1 == 1) {
                func_8082E634(play, this, &gPlayerAnim_link_swimer_swim_wait);
            } else {
                Player_AnimationPlayLoop(play, this, &gPlayerAnim_link_swimer_swim_wait);
            }
        }
        func_808475B4(this);
        func_8084748C(this, &this->linearVelocity, 0.0f, this->actor.shape.rot.y);
    }
}

PlayerCsModeEntry sPlayerCsModeInitFuncs[PLAYER_CSMODE_MAX] = {
    /* PLAYER_CSMODE_NONE   */ { PLAYER_CSTYPE_NONE, { NULL } },
    /* PLAYER_CSMODE_1   */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_1 } },
    /* PLAYER_CSMODE_2   */ { PLAYER_CSTYPE_NONE, { NULL } },
    /* PLAYER_CSMODE_3   */ { PLAYER_CSTYPE_NONE, { NULL } },
    /* PLAYER_CSMODE_4   */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_link_demo_bikkuri } },
    /* PLAYER_CSMODE_5   */ { PLAYER_CSTYPE_NONE, { NULL } },
    /* PLAYER_CSMODE_END  */ { PLAYER_CSTYPE_NONE, { NULL } },
    /* PLAYER_CSMODE_WAIT */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_1 } },
    /* PLAYER_CSMODE_8   */ { PLAYER_CSTYPE_ANIM_2, { &gPlayerAnim_link_demo_furimuki } },
    /* PLAYER_CSMODE_9   */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_5 } },
    /* PLAYER_CSMODE_10  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_link_demo_warp } },
    /* PLAYER_CSMODE_11  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_clink_demo_standup } },
    /* PLAYER_CSMODE_12  */ { PLAYER_CSTYPE_ANIM_7, { &gPlayerAnim_clink_demo_standup_wait } },
    /* PLAYER_CSMODE_13  */ { PLAYER_CSTYPE_ANIM_2, { &gPlayerAnim_link_demo_baru_op3 } },
    /* PLAYER_CSMODE_14  */ { PLAYER_CSTYPE_NONE, { NULL } },
    /* PLAYER_CSMODE_15  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_link_demo_jibunmiru } },
    /* PLAYER_CSMODE_16  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_14 } },
    /* PLAYER_CSMODE_17  */ { PLAYER_CSTYPE_ANIM_2, { &gPlayerAnim_link_normal_okarina_end } },
    /* PLAYER_CSMODE_18  */ { PLAYER_CSTYPE_ANIM_16, { &gPlayerAnim_link_normal_hang_up_down } },
    /* PLAYER_CSMODE_19  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_16 } },
    /* PLAYER_CSMODE_20  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_1 } },
    /* PLAYER_CSMODE_21  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_clink_demo_mimawasi } },
    /* PLAYER_CSMODE_22  */ { PLAYER_CSTYPE_ANIM_6, { &gPlayerAnim_om_get_mae } },
    /* PLAYER_CSMODE_23  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_link_demo_look_hand } },
    /* PLAYER_CSMODE_24  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_link_normal_wait_typeB_20f } },
    /* PLAYER_CSMODE_25  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_17 } },
    /* PLAYER_CSMODE_26  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_37 } },
    /* PLAYER_CSMODE_27  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_link_demo_zeldamiru } },
    /* PLAYER_CSMODE_28  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_link_demo_kenmiru1 } },
    /* PLAYER_CSMODE_29  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_link_demo_kenmiru2 } },
    /* PLAYER_CSMODE_30  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_link_demo_kenmiru2_modori } },
    /* PLAYER_CSMODE_31  */ { PLAYER_CSTYPE_ANIM_6, { &gameplay_keep_Linkanim_00D310 } },
    /* PLAYER_CSMODE_32  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_22 } },
    /* PLAYER_CSMODE_33  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_demo_rakka } },
    /* PLAYER_CSMODE_34  */ { PLAYER_CSTYPE_ANIM_4, { &gPlayerAnim_demo_pikupiku } },
    /* PLAYER_CSMODE_35  */ { PLAYER_CSTYPE_ANIM_3, { &gameplay_keep_Linkanim_00D2B8 } },
    /* PLAYER_CSMODE_36  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_25 } },
    /* PLAYER_CSMODE_37  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_27 } },
    /* PLAYER_CSMODE_38  */ { PLAYER_CSTYPE_ANIM_6, { &gameplay_keep_Linkanim_00D278 } },
    /* PLAYER_CSMODE_39  */ { PLAYER_CSTYPE_ANIM_6, { &gameplay_keep_Linkanim_00D288 } },
    /* PLAYER_CSMODE_40  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_rakuba } },
    /* PLAYER_CSMODE_41  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_bajyo_furikaeru } },
    /* PLAYER_CSMODE_42  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_okiagaru } },
    /* PLAYER_CSMODE_43  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_okiagaru_tatu } },
    /* PLAYER_CSMODE_44  */ { PLAYER_CSTYPE_ANIM_7, { &gPlayerAnim_bajyo_walk } },
    /* PLAYER_CSMODE_45  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_rakka } },
    /* PLAYER_CSMODE_46  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_sirimochi } },
    /* PLAYER_CSMODE_47  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_spotlight } },
    /* PLAYER_CSMODE_48  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_al_hensin } },
    /* PLAYER_CSMODE_49  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_dl_jibunmiru } },
    /* PLAYER_CSMODE_50  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_vs_yousei } },
    /* PLAYER_CSMODE_51  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_urusai } },
    /* PLAYER_CSMODE_52  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_okarinatori } },
    /* PLAYER_CSMODE_53  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_lost_horse } },
    /* PLAYER_CSMODE_54  */ { PLAYER_CSTYPE_ANIM_4, { &gPlayerAnim_lost_horse_wait } },
    /* PLAYER_CSMODE_55  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_lost_horse2 } },
    /* PLAYER_CSMODE_56  */ { PLAYER_CSTYPE_ANIM_14, { &gPlayerAnim_okarinatori } },
    /* PLAYER_CSMODE_57  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_cl_tobikakaru } },
    /* PLAYER_CSMODE_58  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_5 } },
    /* PLAYER_CSMODE_59  */ { PLAYER_CSTYPE_ANIM_5, { &gameplay_keep_Linkanim_00D0A0 } },
    /* PLAYER_CSMODE_60  */ { PLAYER_CSTYPE_ANIM_2, { &gPlayerAnim_cl_furafura } },
    /* PLAYER_CSMODE_61  */ { PLAYER_CSTYPE_ANIM_7, { &gPlayerAnim_cl_nigeru } },
    /* PLAYER_CSMODE_62  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_cl_ononoki } },
    /* PLAYER_CSMODE_63  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_al_gaku } },
    /* PLAYER_CSMODE_64  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_al_fuwafuwa } },
    /* PLAYER_CSMODE_65  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_al_fuwafuwa_modori } },
    /* PLAYER_CSMODE_66  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_al_elf_tobidasi } },
    /* PLAYER_CSMODE_67  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_3 } },
    /* PLAYER_CSMODE_68  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_29 } },
    /* PLAYER_CSMODE_69  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_31 } },
    /* PLAYER_CSMODE_70  */ { PLAYER_CSTYPE_ANIM_7, { &gPlayerAnim_cl_tewofuru } },
    /* PLAYER_CSMODE_71  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_cl_jibun_miru } },
    /* PLAYER_CSMODE_72  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_cl_hoo } },
    /* PLAYER_CSMODE_73  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_al_yareyare } },
    /* PLAYER_CSMODE_74  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_al_yes } },
    /* PLAYER_CSMODE_75  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_al_no } },
    /* PLAYER_CSMODE_76  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_al_unun } },
    /* PLAYER_CSMODE_77  */ { PLAYER_CSTYPE_ANIM_7, { &gPlayerAnim_dl_yusaburu } },
    /* PLAYER_CSMODE_78  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_dl_kokeru } },
    /* PLAYER_CSMODE_79  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_alink_powerup } },
    /* PLAYER_CSMODE_80  */ { PLAYER_CSTYPE_ANIM_4, { &gPlayerAnim_alink_rakkatyu } },
    /* PLAYER_CSMODE_81  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_alink_kyoro } },
    /* PLAYER_CSMODE_82  */ { PLAYER_CSTYPE_ANIM_4, { &gPlayerAnim_alink_yurayura } },
    /* PLAYER_CSMODE_83  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_alink_somukeru } },
    /* PLAYER_CSMODE_84  */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_alink_fukitobu } },
    /* PLAYER_CSMODE_85  */ { PLAYER_CSTYPE_ANIM_3, { &gameplay_keep_Linkanim_00CFC8 } },
    /* PLAYER_CSMODE_86  */ { PLAYER_CSTYPE_ANIM_4, { &gPlayerAnim_alink_tereru } },
    /* PLAYER_CSMODE_87  */ { PLAYER_CSTYPE_ANIM_5, { &gameplay_keep_Linkanim_00D1D0 } },
    /* PLAYER_CSMODE_88  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_alink_kaitenmiss } },
    /* PLAYER_CSMODE_89  */ { PLAYER_CSTYPE_ANIM_4, { &gameplay_keep_Linkanim_00CFC0 } },
    /* PLAYER_CSMODE_90  */ { PLAYER_CSTYPE_ANIM_4, { &gameplay_keep_Linkanim_00CFB8 } },
    /* PLAYER_CSMODE_91  */ { PLAYER_CSTYPE_ANIM_4, { &gameplay_keep_Linkanim_00D050 } },
    /* PLAYER_CSMODE_92  */ { PLAYER_CSTYPE_ANIM_4, { &gameplay_keep_Linkanim_00D048 } },
    /* PLAYER_CSMODE_93  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_42 } },
    /* PLAYER_CSMODE_94  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_alink_ozigi } },
    /* PLAYER_CSMODE_95  */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_alink_ozigi_modori } },
    /* PLAYER_CSMODE_96  */ { PLAYER_CSTYPE_ANIM_9, { &gPlayerAnim_link_normal_back_downA } },
    /* PLAYER_CSMODE_97  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_35 } },
    /* PLAYER_CSMODE_98  */ { PLAYER_CSTYPE_ANIM_15, { &gPlayerAnim_cl_maskoff } },
    /* PLAYER_CSMODE_99  */ { PLAYER_CSTYPE_ANIM_7, { &gPlayerAnim_cl_kubisime } },
    /* PLAYER_CSMODE_100 */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_alink_ee } },
    /* PLAYER_CSMODE_101 */ { PLAYER_CSTYPE_ANIM_3, { &gameplay_keep_Linkanim_00CFF0 } },
    /* PLAYER_CSMODE_102 */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_40 } },
    /* PLAYER_CSMODE_103 */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_45 } },
    /* PLAYER_CSMODE_104 */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_cl_dakisime } },
    /* PLAYER_CSMODE_105 */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_kf_omen } },
    /* PLAYER_CSMODE_106 */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_kf_dakiau } },
    /* PLAYER_CSMODE_107 */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_kf_hanare } },
    /* PLAYER_CSMODE_108 */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_kf_miseau } },
    /* PLAYER_CSMODE_109 */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_kf_awase } },
    /* PLAYER_CSMODE_110 */ { PLAYER_CSTYPE_ANIM_7, { &gPlayerAnim_kf_tetunagu_loop } },
    /* PLAYER_CSMODE_111 */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_link_keirei } },
    /* PLAYER_CSMODE_112 */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_cl_umanoru } },
    /* PLAYER_CSMODE_113 */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_cl_wakare } },
    /* PLAYER_CSMODE_114 */ { PLAYER_CSTYPE_ANIM_4, { &gPlayerAnim_alink_dance_loop } },
    /* PLAYER_CSMODE_115 */ { PLAYER_CSTYPE_ANIM_2, { &gPlayerAnim_link_demo_goma_furimuki } },
    /* PLAYER_CSMODE_116 */ { PLAYER_CSTYPE_ANIM_7, { &gPlayerAnim_link_uma_anim_fastrun } },
    /* PLAYER_CSMODE_117 */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_cl_umamiage } },
    /* PLAYER_CSMODE_118 */ { PLAYER_CSTYPE_ANIM_7, { &gPlayerAnim_demo_suwari1 } },
    /* PLAYER_CSMODE_119 */ { PLAYER_CSTYPE_ANIM_7, { &gPlayerAnim_demo_suwari2 } },
    /* PLAYER_CSMODE_120 */ { PLAYER_CSTYPE_ANIM_7, { &gPlayerAnim_demo_suwari3 } },
    /* PLAYER_CSMODE_121 */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_7 } },
    /* PLAYER_CSMODE_122 */ { PLAYER_CSTYPE_NONE, { NULL } },
    /* PLAYER_CSMODE_123 */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_9 } },
    /* PLAYER_CSMODE_124 */ { PLAYER_CSTYPE_ANIM_7, { &gPlayerAnim_clink_demo_get1 } },
    /* PLAYER_CSMODE_125 */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_clink_demo_get2 } },
    /* PLAYER_CSMODE_126 */ { PLAYER_CSTYPE_ANIM_5, { &gPlayerAnim_clink_demo_get3 } },
    /* PLAYER_CSMODE_127 */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_link_demo_gurad } },
    /* PLAYER_CSMODE_128 */ { PLAYER_CSTYPE_ANIM_4, { &gPlayerAnim_link_demo_sita_wait } },
    /* PLAYER_CSMODE_129 */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_L_1kyoro } },
    /* PLAYER_CSMODE_130 */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_L_2kyoro } },
    /* PLAYER_CSMODE_131 */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_L_sagaru } },
    /* PLAYER_CSMODE_132 */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_L_bouzen } },
    /* PLAYER_CSMODE_133 */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_L_kamaeru } },
    /* PLAYER_CSMODE_134 */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_L_hajikareru } },
    /* PLAYER_CSMODE_135 */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_L_ken_miru } },
    /* PLAYER_CSMODE_136 */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_L_mukinaoru } },
    /* PLAYER_CSMODE_137 */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_link_demo_return_to_past } },
    /* PLAYER_CSMODE_138 */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_link_last_hit_motion1 } },
    /* PLAYER_CSMODE_139 */ { PLAYER_CSTYPE_ANIM_3, { &gPlayerAnim_link_last_hit_motion2 } },
};

PlayerCsModeEntry sPlayerCsModeUpdateFuncs[PLAYER_CSMODE_MAX] = {
    /* PLAYER_CSMODE_NONE   */ { PLAYER_CSTYPE_NONE, { NULL } },
    /* PLAYER_CSMODE_1   */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_0 } },
    /* PLAYER_CSMODE_2   */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_11 } },
    /* PLAYER_CSMODE_3   */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_13 } },
    /* PLAYER_CSMODE_4   */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_5   */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_48 } },
    /* PLAYER_CSMODE_END  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_End } },
    /* PLAYER_CSMODE_WAIT */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_2 } },
    /* PLAYER_CSMODE_8   */ { PLAYER_CSTYPE_ANIM_18, { D_8085DA70 } },
    /* PLAYER_CSMODE_9   */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_6 } },
    /* PLAYER_CSMODE_10  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_15 } },
    /* PLAYER_CSMODE_11  */ { PLAYER_CSTYPE_ANIM_18, { D_8085D9E0 } },
    /* PLAYER_CSMODE_12  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_13  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_14  */ { PLAYER_CSTYPE_NONE, { NULL } },
    /* PLAYER_CSMODE_15  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_16  */ { PLAYER_CSTYPE_ANIM_17, { &gPlayerAnim_link_normal_okarina_swing } },
    /* PLAYER_CSMODE_17  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_18  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_19  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_39 } },
    /* PLAYER_CSMODE_20  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_2 } },
    /* PLAYER_CSMODE_21  */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_clink_demo_mimawasi_wait } },
    /* PLAYER_CSMODE_22  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_19 } },
    /* PLAYER_CSMODE_23  */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_link_demo_look_hand_wait } },
    /* PLAYER_CSMODE_24  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_25  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_26  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_38 } },
    /* PLAYER_CSMODE_27  */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_link_demo_zeldamiru_wait } },
    /* PLAYER_CSMODE_28  */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_link_demo_kenmiru1_wait } },
    /* PLAYER_CSMODE_29  */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_link_demo_kenmiru2_wait } },
    /* PLAYER_CSMODE_30  */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_demo_link_nwait } },
    /* PLAYER_CSMODE_31  */ { PLAYER_CSTYPE_ANIM_12, { &gameplay_keep_Linkanim_00D318 } },
    /* PLAYER_CSMODE_32  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_23 } },
    /* PLAYER_CSMODE_33  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_TranslateReverse } },
    /* PLAYER_CSMODE_34  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_35  */ { PLAYER_CSTYPE_ANIM_12, { &gameplay_keep_Linkanim_00D2C0 } },
    /* PLAYER_CSMODE_36  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_26 } },
    /* PLAYER_CSMODE_37  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_28 } },
    /* PLAYER_CSMODE_38  */ { PLAYER_CSTYPE_ANIM_12, { &gameplay_keep_Linkanim_00D280 } },
    /* PLAYER_CSMODE_39  */ { PLAYER_CSTYPE_ANIM_12, { &gameplay_keep_Linkanim_00D290 } },
    /* PLAYER_CSMODE_40  */ { PLAYER_CSTYPE_ANIM_18, { D_8085D9F0 } },
    /* PLAYER_CSMODE_41  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_42  */ { PLAYER_CSTYPE_ANIM_18, { D_8085DA00 } },
    /* PLAYER_CSMODE_43  */ { PLAYER_CSTYPE_ANIM_13, { &gPlayerAnim_okiagaru_wait } },
    /* PLAYER_CSMODE_44  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_32 } },
    /* PLAYER_CSMODE_45  */ { PLAYER_CSTYPE_ANIM_18, { D_8085DA2C } },
    /* PLAYER_CSMODE_46  */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_sirimochi_wait } },
    /* PLAYER_CSMODE_47  */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_spotlight_wait } },
    /* PLAYER_CSMODE_48  */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_al_hensin_loop } },
    /* PLAYER_CSMODE_49  */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_dl_jibunmiru_wait } },
    /* PLAYER_CSMODE_50  */ { PLAYER_CSTYPE_ANIM_18, { D_8085DA50 } },
    /* PLAYER_CSMODE_51  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_52  */ { PLAYER_CSTYPE_ANIM_18, { D_8085D9FC } },
    /* PLAYER_CSMODE_53  */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_lost_horse_wait } },
    /* PLAYER_CSMODE_54  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_32 } },
    /* PLAYER_CSMODE_55  */ { PLAYER_CSTYPE_ANIM_18, { D_8085DA1C } },
    /* PLAYER_CSMODE_56  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_57  */ { PLAYER_CSTYPE_ANIM_18, { D_8085DA0C } },
    /* PLAYER_CSMODE_58  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_8 } },
    /* PLAYER_CSMODE_59  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_60  */ { PLAYER_CSTYPE_ANIM_18, { D_8085DA28 } },
    /* PLAYER_CSMODE_61  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_32 } },
    /* PLAYER_CSMODE_62  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_63  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_64  */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_al_fuwafuwa_loop } },
    /* PLAYER_CSMODE_65  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_33 } },
    /* PLAYER_CSMODE_66  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_67  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_4 } },
    /* PLAYER_CSMODE_68  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_30 } },
    /* PLAYER_CSMODE_69  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_70  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_71  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_33 } },
    /* PLAYER_CSMODE_72  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_73  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_74  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_75  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_76  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_77  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_78  */ { PLAYER_CSTYPE_ANIM_18, { D_8085DA78 } },
    /* PLAYER_CSMODE_79  */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_alink_powerup_loop } },
    /* PLAYER_CSMODE_80  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_32 } },
    /* PLAYER_CSMODE_81  */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_alink_kyoro_loop } },
    /* PLAYER_CSMODE_82  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_83  */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_alink_somukeru_loop } },
    /* PLAYER_CSMODE_84  */ { PLAYER_CSTYPE_ANIM_18, { D_8085DA80 } },
    /* PLAYER_CSMODE_85  */ { PLAYER_CSTYPE_ANIM_12, { &gameplay_keep_Linkanim_00CFD0 } },
    /* PLAYER_CSMODE_86  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_87  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_88  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_89  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_90  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_91  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_92  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_93  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_43 } },
    /* PLAYER_CSMODE_94  */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_alink_ozigi_loop } },
    /* PLAYER_CSMODE_95  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_96  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_34 } },
    /* PLAYER_CSMODE_97  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_36 } },
    /* PLAYER_CSMODE_98  */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_46 } },
    /* PLAYER_CSMODE_99  */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_100 */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_alink_ee_loop } },
    /* PLAYER_CSMODE_101 */ { PLAYER_CSTYPE_ANIM_12, { &gameplay_keep_Linkanim_00CFF8 } },
    /* PLAYER_CSMODE_102 */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_41 } },
    /* PLAYER_CSMODE_103 */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_104 */ { PLAYER_CSTYPE_ANIM_13, { &gPlayerAnim_cl_dakisime_loop } },
    /* PLAYER_CSMODE_105 */ { PLAYER_CSTYPE_ANIM_13, { &gPlayerAnim_kf_omen_loop } },
    /* PLAYER_CSMODE_106 */ { PLAYER_CSTYPE_ANIM_13, { &gPlayerAnim_kf_dakiau_loop } },
    /* PLAYER_CSMODE_107 */ { PLAYER_CSTYPE_ANIM_13, { &gPlayerAnim_kf_hanare_loop } },
    /* PLAYER_CSMODE_108 */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_109 */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_110 */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_111 */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_link_kei_wait } },
    /* PLAYER_CSMODE_112 */ { PLAYER_CSTYPE_ANIM_13, { &gPlayerAnim_cl_umanoru_loop } },
    /* PLAYER_CSMODE_113 */ { PLAYER_CSTYPE_ANIM_13, { &gPlayerAnim_cl_wakare_loop } },
    /* PLAYER_CSMODE_114 */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_115 */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_44 } },
    /* PLAYER_CSMODE_116 */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_117 */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_32 } },
    /* PLAYER_CSMODE_118 */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_119 */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_120 */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_121 */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_8 } },
    /* PLAYER_CSMODE_122 */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_12 } },
    /* PLAYER_CSMODE_123 */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_10 } },
    /* PLAYER_CSMODE_125 */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_124 */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_126 */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_127 */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_link_demo_gurad_wait } },
    /* PLAYER_CSMODE_128 */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_129 */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_L_kw } },
    /* PLAYER_CSMODE_130 */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_131 */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_132 */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_133 */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_134 */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_18 } },
    /* PLAYER_CSMODE_135 */ { PLAYER_CSTYPE_ANIM_11, { NULL } },
    /* PLAYER_CSMODE_136 */ { PLAYER_CSTYPE_ANIM_12, { &gPlayerAnim_L_kennasi_w } },
    /* PLAYER_CSMODE_137 */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_20 } },
    /* PLAYER_CSMODE_138 */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_21 } },
    /* PLAYER_CSMODE_139 */ { PLAYER_CSTYPE_ACTION, { Player_CsAction_21 } },
};

void Player_CsAction_0(PlayState* play, Player* this, CsCmdActorCue* cue) {
    func_80859248(this);

    if (func_801242B4(this)) {
        func_80859300(play, this, 0);
    } else {
        PlayerAnimation_Update(play, &this->skelAnime);
        if (func_801240DC(this) || (this->stateFlags1 & PLAYER_STATE1_800)) {
            Player_UpdateUpperBody(this, play);
        } else if ((this->interactRangeActor != NULL) && (this->interactRangeActor->textId == 0xFFFF)) {
            Player_ActionChange_2(this, play);
        }
    }
}

void Player_CsAction_1(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if (this->stateFlags1 & PLAYER_STATE1_8000000) {
        func_8085929C(play, this, 0);
    } else {
        PlayerAnimationHeader* anim = D_8085BE84[PLAYER_ANIMGROUP_43][this->modelAnimType];

        if ((this->cueId == PLAYER_CUEID_6) || (this->cueId == PLAYER_CUEID_46)) {
            Player_AnimationPlayOnce(play, this, anim);
        } else {
            func_8082E784(this);
            PlayerAnimation_Change(play, &this->skelAnime, anim, 2.0f / 3.0f, 0.0f, Animation_GetLastFrame(anim),
                                   ANIMMODE_LOOP, -4.0f);
        }
        Player_StopHorizontalMovement(this);
    }
}

void Player_CsAction_2(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if (func_80847880(play, this)) {
        return;
    }

    if ((this->csMode == PLAYER_CSMODE_20) && (play->csCtx.state == CS_STATE_IDLE)) {
        func_800B7298(play, NULL, PLAYER_CSMODE_END);
    } else if (this->stateFlags1 & PLAYER_STATE1_8000000) {
        func_80859300(play, this, 0);
        this->actor.velocity.y = 0.0f;
    } else {
        PlayerAnimation_Update(play, &this->skelAnime);
        if (func_801240DC(this) || (this->stateFlags1 & PLAYER_STATE1_800)) {
            Player_UpdateUpperBody(this, play);
        }
    }
}

void Player_CsAction_3(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if (this->actor.id == ACTOR_EN_TEST3) {
        func_80838830(this, OBJECT_GI_MSSA);
        this->stateFlags1 |= PLAYER_STATE1_400;
    }

    func_8082DB90(play, this,
                  (this->transformation == PLAYER_FORM_DEKU) ? &gPlayerAnim_pn_getA : &gPlayerAnim_link_demo_get_itemA);
}

void Player_CsAction_4(PlayState* play, Player* this, CsCmdActorCue* cue) {
    PlayerAnimation_Update(play, &this->skelAnime);
    if ((this->actor.id == ACTOR_EN_TEST3) && Animation_OnFrame(&this->skelAnime, 20.0f)) {
        this->getItemDrawIdPlusOne = GID_MASK_SUN + 1;
        Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_ESCAPED_SAKONS_HIDEOUT);
        Audio_PlayFanfare(NA_BGM_GET_NEW_MASK);
    }
}

void Player_CsAction_5(PlayState* play, Player* this, CsCmdActorCue* cue) {
    f32 linearVelocity;
    s16 yaw;

    this->stateFlags1 &= ~PLAYER_STATE1_2000000;

    yaw = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_3A0);
    linearVelocity = this->linearVelocity;
    this->actor.world.rot.y = yaw;
    this->actor.shape.rot.y = yaw;
    this->currentYaw = yaw;
    if (linearVelocity <= 0.0f) {
        this->linearVelocity = 0.1f;
    } else if (linearVelocity > 2.5f) {
        this->linearVelocity = 2.5f;
    }

    if ((this->transformation != PLAYER_FORM_HUMAN) && (play->roomCtx.curRoom.behaviorType1 == ROOM_BEHAVIOR_TYPE1_5)) {
        R_PLAY_FILL_SCREEN_ON = 45;
        R_PLAY_FILL_SCREEN_R = 255;
        R_PLAY_FILL_SCREEN_G = 255;
        R_PLAY_FILL_SCREEN_B = 255;
        R_PLAY_FILL_SCREEN_ALPHA = 0;
        Audio_PlaySfx(NA_SE_SY_WHITE_OUT_T);
    }
}

void Player_CsAction_6(PlayState* play, Player* this, CsCmdActorCue* cue) {
    f32 sp24;

    if (R_PLAY_FILL_SCREEN_ON > 0) {
        R_PLAY_FILL_SCREEN_ALPHA += R_PLAY_FILL_SCREEN_ON;
        if (R_PLAY_FILL_SCREEN_ALPHA > 255) {
            R_PLAY_FILL_SCREEN_ON = -64;
            R_PLAY_FILL_SCREEN_ALPHA = 255;
            gSaveContext.save.playerForm = PLAYER_FORM_HUMAN;
            this->actor.update = func_8012301C;
            this->actor.draw = NULL;
            this->actionVar1 = 0;
        }
    } else if (R_PLAY_FILL_SCREEN_ON < 0) {
        R_PLAY_FILL_SCREEN_ALPHA += R_PLAY_FILL_SCREEN_ON;
        if (R_PLAY_FILL_SCREEN_ALPHA < 0) {
            R_PLAY_FILL_SCREEN_ON = 0;
            R_PLAY_FILL_SCREEN_ALPHA = 0;
        }
    } else {
        sp24 = 2.5f;
        func_808411D4(play, this, &sp24, 0xA);
        this->actionVar2++;
        if (this->actionVar2 >= 0x15) {
            this->csMode = PLAYER_CSMODE_10;
        }
    }
}

void Player_CsAction_7(PlayState* play, Player* this, CsCmdActorCue* cue) {
    this->linearVelocity = 2.5f;
    func_80835BF8(&this->actor.world.pos, this->actor.shape.rot.y, 180.0f, &this->unk_3A0);
}

void Player_CsAction_8(PlayState* play, Player* this, CsCmdActorCue* cue) {
    f32 sp1C = 2.5f;

    func_808411D4(play, this, &sp1C, 0xA);
}

void Player_CsAction_9(PlayState* play, Player* this, CsCmdActorCue* cue) {
    func_8083B23C(this, play);
}

void Player_CsAction_10(PlayState* play, Player* this, CsCmdActorCue* cue) {
    func_80859248(this);
    if (this->actionVar2 != 0) {
        if (PlayerAnimation_Update(play, &this->skelAnime)) {
            Player_AnimationPlayLoop(play, this, func_8082EF54(this));
            this->actionVar2 = 0;
        }
        func_8082FC60(this);
    } else {
        func_8083E958(play, this);
    }
}

void Player_CsAction_11(PlayState* play, Player* this, CsCmdActorCue* cue) {
    func_80840F90(play, this, cue, 0.0f, 0, 0);
}

void Player_CsAction_12(PlayState* play, Player* this, CsCmdActorCue* cue) {
    this->actor.shape.face = 0xF;
    func_80840F90(play, this, cue, 0.0f, 0, 0);
}

void Player_CsAction_13(PlayState* play, Player* this, CsCmdActorCue* cue) {
    func_80840F90(play, this, cue, 0.0f, 0, 1);
}

void Player_CsAction_14(PlayState* play, Player* this, CsCmdActorCue* cue) {
    func_80858CC8(play, this, &gPlayerAnim_link_normal_okarina_start);
    this->itemAction = PLAYER_IA_OCARINA;
    Player_SetModels(this, Player_ActionToModelGroup(this, this->itemAction));
}

void Player_Cutscene_Translate(PlayState* play, Player* this, CsCmdActorCue* cue) {
    f32 startX = cue->startPos.x;
    f32 startY = cue->startPos.y;
    f32 startZ = cue->startPos.z;
    f32 diffX = cue->endPos.x - startX;
    f32 diffY = cue->endPos.y - startY;
    f32 diffZ = cue->endPos.z - startZ;
    f32 progress = (((f32)(play->csCtx.curFrame - cue->startFrame)) / ((f32)(cue->endFrame - cue->startFrame)));

    this->actor.world.pos.x = (diffX * progress) + startX;
    this->actor.world.pos.y = (diffY * progress) + startY;
    this->actor.world.pos.z = (diffZ * progress) + startZ;
}

void Player_CsAction_15(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if (cue != NULL) {
        Player_Cutscene_Translate(play, this, cue);
    }

    PlayerAnimation_Update(play, &this->skelAnime);
}

void Player_CsAction_16(PlayState* play, Player* this, CsCmdActorCue* cue) {
    func_8082E514(play, this, D_8085BE84[PLAYER_ANIMGROUP_43][this->modelAnimType]);
    Player_StopHorizontalMovement(this);
}

void func_80859CE0(PlayState* play, Player* this, s32 arg2) {
    this->actor.draw = Player_Draw;
}

void Player_CsAction_17(PlayState* play, Player* this, CsCmdActorCue* cue) {
    func_80841358(play, this, false);
    func_8082DB90(play, this, &gPlayerAnim_link_demo_return_to_past);
}

void Player_CsAction_18(PlayState* play, Player* this, CsCmdActorCue* cue) {
    PlayerAnimation_Update(play, &this->skelAnime);
}

PlayerAnimationHeader* D_8085E354[PLAYER_FORM_MAX] = {
    &gPlayerAnim_L_okarina_get, // PLAYER_FORM_FIERCE_DEITY
    &gPlayerAnim_L_okarina_get, // PLAYER_FORM_GORON
    &gPlayerAnim_L_okarina_get, // PLAYER_FORM_ZORA
    &gPlayerAnim_L_okarina_get, // PLAYER_FORM_DEKU
    &gPlayerAnim_om_get,        // PLAYER_FORM_HUMAN
};

struct_8085E368 D_8085E368[PLAYER_FORM_MAX] = {
    { { -200, 700, 100 }, { 800, 600, 800 } }, // PLAYER_FORM_FIERCE_DEITY
    { { -200, 700, 100 }, { 800, 600, 800 } }, // PLAYER_FORM_GORON
    { { -200, 700, 100 }, { 800, 600, 800 } }, // PLAYER_FORM_ZORA
    { { -200, 700, 100 }, { 800, 600, 800 } }, // PLAYER_FORM_DEKU
    { { -200, 500, 0 }, { 600, 400, 600 } },   // PLAYER_FORM_HUMAN
};

Color_RGBA8 D_8085E3A4 = { 255, 255, 255, 0 };
Color_RGBA8 D_8085E3A8 = { 0, 128, 128, 0 };

void Player_CsAction_19(PlayState* play, Player* this, CsCmdActorCue* cue) {
    struct_8085E368* posInfo;
    Vec3f effectPos;
    Vec3f randPos;

    Player_CsAnim_13(play, this, D_8085E354[this->transformation]);

    if (this->rightHandType != 0xFF) {
        this->rightHandType = 0xFF;
    } else {
        posInfo = &D_8085E368[this->transformation];
        randPos.x = Rand_CenteredFloat(posInfo->range.x) + posInfo->base.x;
        randPos.y = Rand_CenteredFloat(posInfo->range.y) + posInfo->base.y;
        randPos.z = Rand_CenteredFloat(posInfo->range.z) + posInfo->base.z;
        SkinMatrix_Vec3fMtxFMultXYZ(&this->shieldMf, &randPos, &effectPos);
        EffectSsKirakira_SpawnDispersed(play, &effectPos, &gZeroVec3f, &gZeroVec3f, &D_8085E3A4, &D_8085E3A8, 600, -10);
    }
}

void Player_CsAction_20(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        Player_CsAction_End(play, this, cue);
    } else if (this->actionVar2 == 0) {
        Item_Give(play, ITEM_SWORD_RAZOR);
        func_80841358(play, this, false);
    } else {
        func_808484CC(this);
    }
}

void Player_CsAction_21(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        func_8083FCF0(play, this, 0.0f, 99.0f, this->skelAnime.endFrame - 8.0f);
    }
    if (this->heldItemAction != PLAYER_IA_SWORD_GILDED) {
        func_80841358(play, this, true);
    }
}

void Player_CsAction_22(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if (this->transformation != PLAYER_FORM_DEKU) {
        gSaveContext.save.playerForm = PLAYER_FORM_DEKU;
    }
}

void Player_CsAction_23(PlayState* play, Player* this, CsCmdActorCue* cue) {
    PlayerAnimation_Update(play, &this->skelAnime);
    if (GET_PLAYER_FORM != this->transformation) {
        this->actor.update = func_8012301C;
        this->actor.draw = NULL;
    }
}

void Player_CsAction_TranslateReverse(PlayState* play, Player* this, CsCmdActorCue* cue) {
    s32 pad;
    f32 xEnd;
    f32 yEnd;
    f32 zEnd;
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;
    f32 progress;

    xEnd = cue->endPos.x;
    yEnd = cue->endPos.y;
    zEnd = cue->endPos.z;

    xDiff = cue->startPos.x - xEnd;
    yDiff = cue->startPos.y - yEnd;
    zDiff = cue->startPos.z - zEnd;

    //! FAKE:
    if (1) {}

    progress = ((f32)(cue->endFrame - play->csCtx.curFrame)) / ((f32)(cue->endFrame - cue->startFrame));

    this->actor.world.pos.x = (xDiff * progress) + xEnd;
    this->actor.world.pos.y = (yDiff * progress) + yEnd;
    this->actor.world.pos.z = (zDiff * progress) + zEnd;
    PlayerAnimation_Update(play, &this->skelAnime);
}

void Player_CsAction_25(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if (this->transformation != PLAYER_FORM_FIERCE_DEITY) {
        gSaveContext.save.playerForm = PLAYER_FORM_FIERCE_DEITY;
    }
}

void Player_CsAction_26(PlayState* play, Player* this, CsCmdActorCue* cue) {
    PlayerAnimation_Update(play, &this->skelAnime);
    if (GET_PLAYER_FORM != this->transformation) {
        this->actor.update = func_8012301C;
        this->actor.draw = NULL;
    }
}

void Player_CsAction_27(PlayState* play, Player* this, CsCmdActorCue* cue) {
    Player_AnimationPlayOnce(play, this, &gPlayerAnim_demo_rakka);
    this->unk_AAA = -0x8000;
}

void Player_CsAction_28(PlayState* play, Player* this, CsCmdActorCue* cue) {
    PlayerAnimation_Update(play, &this->skelAnime);
    this->actor.gravity = 0.0f;
    Math_StepToF(&this->actor.velocity.y, -this->actor.terminalVelocity, -((f32)REG(68) / 100.0f));
}

void Player_CsAction_29(PlayState* play, Player* this, CsCmdActorCue* cue) {
    func_8082DB90(play, this, D_8085D17C[this->transformation]);
    this->itemAction = PLAYER_IA_OCARINA;
    Player_SetModels(this, Player_ActionToModelGroup(this, this->itemAction));
}

void Player_CsAction_30(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if ((PlayerAnimation_Update(play, &this->skelAnime)) &&
        (this->skelAnime.animation == D_8085D17C[this->transformation])) {
        func_808525C4(play, this);
        return;
    }
    if (this->actionVar2 != 0) {
        func_8085255C(play, this);
    }
}

void Player_CsAction_31(PlayState* play, Player* this, CsCmdActorCue* cue) {
    Player_AnimationPlayOnceReverse(play, this, D_8085D17C[this->transformation]);
}

void Player_CsAction_32(PlayState* play, Player* this, CsCmdActorCue* cue) {
    Player_Cutscene_Translate(play, this, cue);
    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        func_8082EB18(play, this, &gPlayerAnim_cl_umamiage_loop);
    }

    if (this->skelAnime.animation == &gPlayerAnim_cl_nigeru) {
        Player_PlayAnimSfx(this, D_8085DA48);
    } else if (this->skelAnime.animation == &gPlayerAnim_alink_rakkatyu) {
        Actor_PlaySfx_FlaggedCentered1(&this->actor, NA_SE_PL_FLYING_AIR - SFX_FLAG);
    } else {
        func_80858FE8(this);
    }
}

void Player_CsAction_33(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        Player_CsAction_16(play, this, cue);
    } else if (this->skelAnime.animation == &gPlayerAnim_al_fuwafuwa_modori) {
        Player_PlayAnimSfx(this, D_8085DA88);
    } else if (this->skelAnime.animation == &gPlayerAnim_cl_jibun_miru) {
        Player_PlayAnimSfx(this, D_8085DA8C);
    }
}

void Player_CsAction_34(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if (PlayerAnimation_Update(play, &this->skelAnime) && (this->actionVar2 == 0) &&
        (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
        Player_AnimationPlayOnce(play, this, &gPlayerAnim_link_normal_back_downB);
        this->actionVar2 = 1;
    }
    if (this->actionVar2 != 0) {
        func_80832F24(this);
    }
}

void Player_CsAction_35(PlayState* play, Player* this, CsCmdActorCue* cue) {
    PlayerAnimation_Change(play, &this->skelAnime, &gPlayerAnim_link_normal_give_other, 1.0f,
                           (play->sceneId == SCENE_ALLEY) ? IREG(56) : 0.0f,
                           Animation_GetLastFrame(&gPlayerAnim_link_normal_give_other), ANIMMODE_ONCE, -8.0f);
}

void Player_CsAction_36(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        if (this->actionVar2++ >= 0x15) {
            PlayerAnimation_Change(play, &this->skelAnime, &gPlayerAnim_pz_wait, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP,
                                   -16.0f);
        }
    }
}

void Player_CsAction_37(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if (func_801242B4(this)) {
        func_8085929C(play, this, 0);
    } else {
        Player_CsAnim_3(play, this, &gPlayerAnim_link_demo_kousan);
    }
}

void Player_CsAction_38(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if (func_801242B4(this)) {
        func_80859300(play, this, 0);
    } else {
        Player_CsAnim_11(play, this, cue);
    }
}

void Player_CsAction_39(PlayState* play, Player* this, CsCmdActorCue* cue) {
    Player_CsAnim_11(play, this, cue);
    if (Player_ActionChange_2(this, play)) {
        play->csCtx.state = CS_STATE_STOP;
        CutsceneManager_Stop(CutsceneManager_GetCurrentCsId());
    }
}

void Player_CsAction_40(PlayState* play, Player* this, CsCmdActorCue* cue) {
    func_80838830(this, OBJECT_GI_RESERVE_C_01);
    Player_CsAnim_3(play, this, &gPlayerAnim_link_normal_give_other);
    this->stateFlags2 &= ~PLAYER_STATE2_1000000;
}

void Player_CsAction_41(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        if (this->actionVar2 == 0) {
            if ((Message_GetState(&play->msgCtx) == TEXT_STATE_CLOSING) ||
                (Message_GetState(&play->msgCtx) == TEXT_STATE_NONE)) {
                this->getItemDrawIdPlusOne = GID_NONE + 1;
                this->actionVar2 = -1;
            } else {
                this->getItemDrawIdPlusOne = GID_PENDANT_OF_MEMORIES + 1;
            }
        } else if (this->actionVar2 < 0) {
            if (Actor_HasParent(&this->actor, play)) {
                this->actor.parent = NULL;
                this->actionVar2 = 1;
            } else {
                Actor_OfferGetItem(&this->actor, play, GI_PENDANT_OF_MEMORIES, 9999.9f, 9999.9f);
            }
        }
    } else if (PlayerAnimation_OnFrame(&this->skelAnime, 4.0f)) {
        SET_WEEKEVENTREG(WEEKEVENTREG_RECEIVED_PENDANT_OF_MEMORIES);
    }
}

void Player_CsAction_42(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if ((this->transformation != PLAYER_FORM_HUMAN) && (play->roomCtx.curRoom.behaviorType1 == ROOM_BEHAVIOR_TYPE1_5)) {
        R_PLAY_FILL_SCREEN_ON = 45;
        R_PLAY_FILL_SCREEN_R = 255;
        R_PLAY_FILL_SCREEN_G = 255;
        R_PLAY_FILL_SCREEN_B = 255;
        R_PLAY_FILL_SCREEN_ALPHA = 0;
        Audio_PlaySfx(NA_SE_SY_WHITE_OUT_T);
    }
}

void Player_CsAction_43(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if (R_PLAY_FILL_SCREEN_ON > 0) {
        R_PLAY_FILL_SCREEN_ALPHA += R_PLAY_FILL_SCREEN_ON;
        if (R_PLAY_FILL_SCREEN_ALPHA > 255) {
            R_PLAY_FILL_SCREEN_ON = -64;
            R_PLAY_FILL_SCREEN_ALPHA = 255;
            gSaveContext.save.playerForm = PLAYER_FORM_HUMAN;
            this->actor.update = func_8012301C;
            this->actor.draw = NULL;
            this->actionVar1 = 0;
        }
    } else if (R_PLAY_FILL_SCREEN_ON < 0) {
        R_PLAY_FILL_SCREEN_ALPHA += R_PLAY_FILL_SCREEN_ON;
        if (R_PLAY_FILL_SCREEN_ALPHA < 0) {
            R_PLAY_FILL_SCREEN_ON = 0;
            R_PLAY_FILL_SCREEN_ALPHA = 0;
        }
    } else {
        PlayerAnimation_Update(play, &this->skelAnime);
    }
}

void Player_CsAction_44(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if (PlayerAnimation_Update(play, &this->skelAnime) && (CutsceneManager_GetCurrentCsId() == CS_ID_GLOBAL_DOOR)) {
        CutsceneManager_Stop(CS_ID_GLOBAL_DOOR);
    }
}

void Player_CsAction_45(PlayState* play, Player* this, CsCmdActorCue* cue) {
    func_80848640(play, this);
}

void Player_CsAction_46(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if (PlayerAnimation_Update(play, &this->skelAnime)) {
        this->stateFlags2 |= PLAYER_STATE2_1000000;
    }
}

void Player_CsAction_End(PlayState* play, Player* this, CsCmdActorCue* cue) {
    if (func_801242B4(this)) {
        func_808353DC(play, this);
        func_8082DC64(play, this);
    } else {
        func_80839ED0(this, play);
        if (!Player_ActionChange_4(this, play)) {
            Player_ActionChange_2(this, play);
        }
    }

    this->csMode = PLAYER_CSMODE_NONE;
    this->unk_AA5 = PLAYER_UNKAA5_0;
}

void Player_Cutscene_SetPosAndYawToStart(Player* this, CsCmdActorCue* cue) {
    this->actor.world.pos.x = cue->startPos.x;
    this->actor.world.pos.y = cue->startPos.y;
    this->actor.world.pos.z = cue->startPos.z;

    this->currentYaw = this->actor.shape.rot.y = cue->rot.y;
}

void Player_Cutscene_8085ABA8(Player* this, CsCmdActorCue* cue) {
    f32 xDiff = cue->startPos.x - (s32)this->actor.world.pos.x;
    f32 yDiff = cue->startPos.y - (s32)this->actor.world.pos.y;
    f32 zDiff = cue->startPos.z - (s32)this->actor.world.pos.z;
    f32 dist;
    s16 temp_v0;

    temp_v0 = (s16)cue->rot.y - this->actor.shape.rot.y;
    dist = sqrtf(SQ(xDiff) + SQ(yDiff) + SQ(zDiff));
    if (this->linearVelocity == 0.0f) {
        if ((dist > 50.0f) || (ABS_ALT(temp_v0) > 0x4000)) {
            Player_Cutscene_SetPosAndYawToStart(this, cue);
        }
    }

    this->skelAnime.moveFlags = 0;
    func_8082E784(this);
}

void func_8085AC9C(PlayState* play, Player* this, CsCmdActorCue* cue, PlayerCsModeEntry* csEntry) {
    if (csEntry->type > PLAYER_CSTYPE_NONE) {
        sPlayerCsModeAnimFuncs[csEntry->type](play, this, csEntry->csAnimArg2);
    } else if (csEntry->type <= PLAYER_CSTYPE_ACTION) {
        csEntry->csActionFunc(play, this, cue);
    }

    if ((D_80862B6C & 4) && !(this->skelAnime.moveFlags & ANIM_FLAG_4)) {
        this->skelAnime.morphTable[PLAYER_LIMB_ROOT - 1].y /= this->ageProperties->unk_08;
        D_80862B6C = 0;
    }
}

void func_8085AD5C(PlayState* play, Player* this, PlayerCsMode csMode) {
    if ((csMode != PLAYER_CSMODE_1) && (csMode != PLAYER_CSMODE_WAIT) && (csMode != PLAYER_CSMODE_20) &&
        (csMode != PLAYER_CSMODE_END)) {
        Player_DetachHeldActor(play, this);
    }
}

void Player_CsAction_48(PlayState* play, Player* this, CsCmdActorCue* cue) {
    CsCmdActorCue* playerCue = (this->actor.id == ACTOR_EN_TEST3)
                                   ? play->csCtx.actorCues[Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_506)]
                                   : play->csCtx.playerCue;
    s32 var_a0 = false;
    s32 pad;
    s32 csMode;

    if ((play->csCtx.state == CS_STATE_IDLE) || (play->csCtx.state == CS_STATE_STOP) ||
        (play->csCtx.state == CS_STATE_RUN_UNSTOPPABLE)) {
        if ((sPlayerCsModes[this->cueId] == PLAYER_CSMODE_68) && (play->sceneId == SCENE_OKUJOU)) {
            this->unk_AA5 = PLAYER_UNKAA5_5;

            if (Player_ActionChange_13(this, play)) {
                this->csMode = PLAYER_CSMODE_NONE;
            }
            return;
        }

        var_a0 = true;

        if (sPlayerCsModes[this->cueId] != PLAYER_CSMODE_16) {
            this->csMode = PLAYER_CSMODE_END;
            func_800B7298(play, NULL, PLAYER_CSMODE_END);
            this->cueId = PLAYER_CUEID_NONE;
            Player_StopHorizontalMovement(this);
            return;
        }
    }

    if (!var_a0 && (playerCue == NULL)) {
        this->actor.flags &= ~ACTOR_FLAG_40;
        return;
    }

    if (!var_a0 && (this->cueId != playerCue->id)) {
        csMode = sPlayerCsModes[playerCue->id];

        // Negative csModes will skip this block
        if ((csMode >= PLAYER_CSMODE_NONE) && !gDisablePlayerCsModeStartPos) {
            if ((csMode == PLAYER_CSMODE_2) || (csMode == PLAYER_CSMODE_3)) {
                Player_Cutscene_8085ABA8(this, playerCue);
            } else {
                Player_Cutscene_SetPosAndYawToStart(this, playerCue);
            }
        }

        if (csMode == PLAYER_CSMODE_108) {
            this->stateFlags3 |= PLAYER_STATE3_20000000;
        } else if (csMode == PLAYER_CSMODE_110) {
            this->stateFlags3 &= ~PLAYER_STATE3_20000000;
        }

        D_80862B6C = this->skelAnime.moveFlags;

        func_8082E794(this);
        func_8085AD5C(play, this, ABS_ALT(csMode));
        func_8085AC9C(play, this, playerCue, &sPlayerCsModeInitFuncs[ABS_ALT(csMode)]);

        this->actionVar2 = 0;
        this->actionVar1 = 0;
        this->cueId = playerCue->id;
    }

    csMode = sPlayerCsModes[this->cueId];
    func_8085AC9C(play, this, playerCue, &sPlayerCsModeUpdateFuncs[ABS_ALT(csMode)]);

    if ((u16)playerCue->rot.x != 0) {
        Math_SmoothStepToS(&this->actor.focus.rot.x, (u16)playerCue->rot.x, 4, 0x2710, 0);
        func_80832754(this, false);
    }
}

void Player_Action_97(Player* this, PlayState* play) {
    if (this->csMode != this->prevCsMode) {
        D_80862B6C = this->skelAnime.moveFlags;
        func_8082E794(this);

        this->prevCsMode = this->csMode;
        func_8085AD5C(play, this, this->csMode);
        func_8085AC9C(play, this, NULL, &sPlayerCsModeInitFuncs[this->csMode]);
    }

    func_8085AC9C(play, this, NULL, &sPlayerCsModeUpdateFuncs[this->csMode]);
}

s32 Player_StartFishing(PlayState* play) {
    Player* player = GET_PLAYER(play);

    func_8082DE50(play, player);
    Player_UseItem(play, player, ITEM_FISHING_ROD);
    return 1;
}

// Player_GrabPlayerImpl? Player_GrabPlayerNoChecks?
void func_8085B170(PlayState* play, Player* this) {
    func_8082DE50(play, this);
    Player_SetAction(play, this, Player_Action_72, 0);
    Player_AnimationPlayOnce(play, this, &gPlayerAnim_link_normal_re_dead_attack);
    this->stateFlags2 |= PLAYER_STATE2_80;
    func_8082DAD4(this);
    Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_HELD);
}

s32 Player_GrabPlayer(PlayState* play, Player* this) {
    if (!Player_InBlockingCsMode(play, this) && (this->invincibilityTimer >= 0) && !func_801240DC(this)) {
        if (!(this->stateFlags1 & (PLAYER_STATE1_80 | PLAYER_STATE1_2000 | PLAYER_STATE1_4000 | PLAYER_STATE1_100000 |
                                   PLAYER_STATE1_200000 | PLAYER_STATE1_800000))) {
            if (!(this->stateFlags2 & PLAYER_STATE2_80) && !(this->stateFlags3 & PLAYER_STATE3_80)) {
                func_8085B170(play, this);
                return true;
            }
        }
    }

    return false;
}

s32 func_8085B28C(PlayState* play, Player* this, PlayerCsMode csMode) {
    Player* player = GET_PLAYER(play);

    if (this != NULL) {
        if (csMode == PLAYER_CSMODE_NONE) {
            return Player_Action_36 == this->actionFunc;
        }

        if ((this->actor.id == ACTOR_EN_TEST3) && (csMode < 0)) {
            func_8083B0E4(play, this, this->actor.home.rot.y);
            return false;
        }

        if (this->actor.id == ACTOR_EN_TEST3) {
            player = this;
        }
    }

    if ((player->actor.id == ACTOR_EN_TEST3) || !Player_InBlockingCsMode(play, player)) {
        func_8082DE50(play, player);
        Player_SetAction(play, player, Player_Action_97, 0);
        player->csMode = csMode;
        player->csActor = &this->actor;
        func_8082DAD4(player);

        return true;
    }

    return false;
}

void func_8085B384(Player* this, PlayState* play) {
    Player_SetAction(play, this, Player_Action_4, 1);
    func_8082E438(play, this, func_8082ED20(this));
    this->currentYaw = this->actor.shape.rot.y;
}

/**
 * Returns true if Player's health reaches zero
 */
s32 Player_InflictDamage(PlayState* play, s32 damage) {
    Player* player = GET_PLAYER(play);

    if ((player->stateFlags2 & PLAYER_STATE2_80) || !Player_InBlockingCsMode(play, player)) {
        if (func_808339D4(play, player, damage) == 0) {
            player->stateFlags2 &= ~PLAYER_STATE2_80;
            return true;
        }
    }

    return false;
}

// Start talking with the given actor
void Player_TalkWithPlayer(PlayState* play, Actor* actor) {
    s32 pad;
    Player* player = GET_PLAYER(play);

    func_808323C0(player, CS_ID_GLOBAL_TALK);
    if ((player->talkActor != NULL) || (actor == player->tatlActor) ||
        CHECK_FLAG_ALL(actor->flags, ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_40000)) {
        actor->flags |= ACTOR_FLAG_TALK_REQUESTED;
    }

    player->talkActor = actor;
    player->exchangeItemAction = PLAYER_IA_NONE;
    player->lockOnActor = actor;

    if (actor->textId == 0xFFFF) {
        func_800B7298(play, actor, PLAYER_CSMODE_1);
        actor->flags |= ACTOR_FLAG_TALK_REQUESTED;
        func_8082DE14(play, player);
    } else {
        if (player->actor.flags & ACTOR_FLAG_TALK_REQUESTED) {
            player->actor.textId = 0;
        } else {
            player->actor.flags |= ACTOR_FLAG_TALK_REQUESTED;
            player->actor.textId = actor->textId;
        }

        if (player->stateFlags1 & PLAYER_STATE1_800000) {
            s32 sp24 = player->actionVar2;

            func_8082DE14(play, player);
            func_80837B60(play, player);
            player->actionVar2 = sp24;
        } else {
            if (func_801242B4(player)) {
                func_80832558(play, player, func_80837B60);
                func_8082E634(play, player, &gPlayerAnim_link_swimer_swim_wait);
            } else if ((actor->category != ACTORCAT_NPC) || (player->heldItemAction == PLAYER_IA_FISHING_ROD)) {
                func_80837B60(play, player);

                if (!func_80123420(player)) {
                    if ((actor != player->tatlActor) && (actor->xzDistToPlayer < (actor->colChkInfo.cylRadius + 40))) {
                        func_8082DB90(play, player, &gPlayerAnim_link_normal_backspace);
                    } else {
                        Player_AnimationPlayLoop(play, player, func_8082ED20(player));
                    }
                }
            } else {
                func_80832558(play, player, func_80837B60);
                func_8082DB90(play, player,
                              (actor->xzDistToPlayer < (actor->colChkInfo.cylRadius + 40))
                                  ? &gPlayerAnim_link_normal_backspace
                                  : &gPlayerAnim_link_normal_talk_free);
            }

            if (player->skelAnime.animation == &gPlayerAnim_link_normal_backspace) {
                func_8082E920(play, player, ANIM_FLAG_1 | ANIM_FLAG_8 | ANIM_FLAG_NOMOVE);
            }
            func_8082DAD4(player);
        }

        player->stateFlags1 |= PLAYER_STATE1_40 | PLAYER_STATE1_20000000;
    }

    if ((player->tatlActor == player->talkActor) && ((player->talkActor->textId & 0xFF00) != 0x200)) {
        player->tatlActor->flags |= ACTOR_FLAG_TALK_REQUESTED;
    }
}

void func_8085B74C(PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 temp_fv1;
    f32 linearVelocity = player->linearVelocity;

    if (linearVelocity < 0.0f) {
        linearVelocity = -linearVelocity;
        player->actor.world.rot.y += 0x8000;
    }

    temp_fv1 = R_RUN_SPEED_LIMIT / 100.0f;

    if (temp_fv1 < linearVelocity) {
        gSaveContext.entranceSpeed = temp_fv1;
    } else {
        gSaveContext.entranceSpeed = linearVelocity;
    }

    func_80835324(play, player, 400.0f,
                  (sPlayerConveyorSpeedIndex != CONVEYOR_SPEED_DISABLED) ? sPlayerConveyorYaw
                                                                         : player->actor.world.rot.y);
    player->stateFlags1 |= (PLAYER_STATE1_1 | PLAYER_STATE1_20000000);
}

void func_8085B820(PlayState* play, s16 arg1) {
    Player* player = GET_PLAYER(play);

    player->actor.focus.rot.y = arg1;
    func_80836D8C(player);
}

PlayerItemAction func_8085B854(PlayState* play, Player* this, ItemId itemId) {
    PlayerItemAction itemAction = Player_ItemToItemAction(this, itemId);

    if ((itemAction >= PLAYER_IA_MASK_MIN) && (itemAction <= PLAYER_IA_MASK_MAX) &&
        (itemAction == GET_IA_FROM_MASK(this->currentMask))) {
        itemAction = PLAYER_IA_NONE;
    }

    if ((itemAction <= PLAYER_IA_NONE) || (itemAction >= PLAYER_IA_MAX)) {
        return PLAYER_IA_MINUS1;
    }

    this->itemAction = PLAYER_IA_NONE;
    this->actionFunc = NULL;
    Player_SetAction_PreserveItemAction(play, this, Player_Action_71, 0);
    this->csId = CS_ID_GLOBAL_TALK;
    this->itemAction = itemAction;
    Player_AnimationPlayOnce(play, this, &gPlayerAnim_link_normal_give_other);
    this->stateFlags1 |= (PLAYER_STATE1_40 | PLAYER_STATE1_20000000);
    this->getItemDrawIdPlusOne = GID_NONE + 1;
    this->exchangeItemAction = itemAction;

    return itemAction;
}

s32 func_8085B930(PlayState* play, PlayerAnimationHeader* talkAnim, AnimationMode animMode) {
    Player* player = GET_PLAYER(play);

    if (!(player->actor.flags & ACTOR_FLAG_TALK_REQUESTED)) {
        return false;
    }

    PlayerAnimation_Change(play, &player->skelAnime, (talkAnim == NULL) ? func_8082ED20(player) : talkAnim, 2.0f / 3.0f,
                           0.0f, Animation_GetLastFrame(talkAnim), animMode, -6.0f);
    return true;
}
