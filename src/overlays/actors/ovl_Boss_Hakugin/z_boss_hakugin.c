/*
 * File: z_boss_hakugin.c
 * Overlay: ovl_Boss_Hakugin
 * Description: Goht
 */

#include "z_boss_hakugin.h"
#include "z64quake.h"
#include "z64rumble.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"
#include "overlays/actors/ovl_Door_Warp1/z_door_warp1.h"
#include "overlays/actors/ovl_En_Clear_Tag/z_en_clear_tag.h"
#include "overlays/actors/ovl_En_Hakurock/z_en_hakurock.h"
#include "overlays/actors/ovl_Item_B_Heart/z_item_b_heart.h"
#include "overlays/effects/ovl_Effect_Ss_Hitmark/z_eff_ss_hitmark.h"

#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((BossHakugin*)thisx)

#define GOHT_LIMB_DRAW_FLAG(limbIndex) (1 << ((limbIndex)-1))

void BossHakugin_Init(Actor* thisx, PlayState* play2);
void BossHakugin_Destroy(Actor* thisx, PlayState* play);
void BossHakugin_Update(Actor* thisx, PlayState* play);
void BossHakugin_UpdateDead(Actor* thisx, PlayState* play2);
void BossHakugin_Draw(Actor* thisx, PlayState* play);
void BossHakugin_DrawDead(Actor* thisx, PlayState* play);

void BossHakugin_SpawnLargeStalactiteWalls(BossHakugin* this);
void BossHakugin_SpawnBlueWarp(BossHakugin* this, PlayState* play);
void BossHakugin_GenShadowTex(u8* tex, BossHakugin* this);
void BossHakugin_DrawShadowTex(u8* tex, BossHakugin* this, PlayState* play);
void func_80B0D9CC(BossHakugin* this);
void func_80B0DFA8(BossHakugin* this);

void BossHakugin_EntranceCutscene(BossHakugin* this, PlayState* play);
void BossHakugin_SetupFrozenBeforeFight(BossHakugin* this);
void BossHakugin_FrozenBeforeFight(BossHakugin* this, PlayState* play);
void BossHakugin_IntroCutsceneDethaw(BossHakugin* this, PlayState* play);
void BossHakugin_SetupIntroCutsceneWakeUp(BossHakugin* this, PlayState* play);
void BossHakugin_IntroCutsceneWakeUp(BossHakugin* this, PlayState* play);
void BossHakugin_SetupIntroCutsceneRun(BossHakugin* this, PlayState* play);
void BossHakugin_IntroCutsceneRun(BossHakugin* this, PlayState* play);
void BossHakugin_SetupRun(BossHakugin* this);
void BossHakugin_Run(BossHakugin* this, PlayState* play);
void BossHakugin_SetupCharge(BossHakugin* this);
void BossHakugin_Charge(BossHakugin* this, PlayState* play);
void BossHakugin_FallDown(BossHakugin* this, PlayState* play);
void BossHakugin_Throw(BossHakugin* this, PlayState* play);
void BossHakugin_SetupChargeLightning(BossHakugin* this, PlayState* play);
void BossHakugin_ChargeLightning(BossHakugin* this, PlayState* play);
void BossHakugin_SetupShootLightning(BossHakugin* this);
void BossHakugin_ShootLightning(BossHakugin* this, PlayState* play);
void BossHakugin_SetupCutsceneStart(BossHakugin* this);
void BossHakugin_CutsceneStart(BossHakugin* this, PlayState* play);
void BossHakugin_SetupDeathCutscenePart1(BossHakugin* this);
void BossHakugin_DeathCutscenePart1(BossHakugin* this, PlayState* play);
void BossHakugin_SetupDeathCutscenePart2(BossHakugin* this);
void BossHakugin_DeathCutscenePart2(BossHakugin* this, PlayState* play);
void BossHakugin_SetupDead(BossHakugin* this);
void BossHakugin_Dead(BossHakugin* this, PlayState* play);

typedef enum GohtElectricBallState {
    // The electric ball is not active. Goht will start charging the electric ball the next time the player hits it with
    // Goron Spikes while it's running.
    /* 0 */ GOHT_ELECTRIC_BALL_STATE_NONE,

    // Goht is charging the electric ball up and will shoot it forward after a short delay.
    /* 1 */ GOHT_ELECTRIC_BALL_STATE_CHARGE,

    // The electric ball is flying forward from Goht's head and slowing down until its speed reaches 50.0f.
    /* 2 */ GOHT_ELECTRIC_BALL_STATE_FLY_FORWARD,

    // The electric ball is rotating to track the player and gradually moves towards them.
    /* 3 */ GOHT_ELECTRIC_BALL_STATE_FLY_TOWARDS_PLAYER,

    // The electric ball hit the player or the environment, so it's fading away. It can't hurt the player in this state.
    /* 4 */ GOHT_ELECTRIC_BALL_STATE_FADE_OUT
} GohtElectricBallState;

typedef enum GohtDirection {
    /* -1 */ GOHT_DIRECTION_COUNTERCLOCKWISE = -1,
    /*  1 */ GOHT_DIRECTION_CLOCKWISE = 1
} GohtDirection;

typedef enum GohtNextCutsceneType {
    /* 0 */ GOHT_NEXT_CUTSCENE_TYPE_ENTRANCE,
    /* 1 */ GOHT_NEXT_CUTSCENE_TYPE_INTRO
} GohtNextCutsceneType;

ActorInit Boss_Hakugin_InitVars = {
    /**/ ACTOR_BOSS_HAKUGIN,
    /**/ ACTORCAT_BOSS,
    /**/ FLAGS,
    /**/ OBJECT_BOSS_HAKUGIN,
    /**/ sizeof(BossHakugin),
    /**/ BossHakugin_Init,
    /**/ BossHakugin_Destroy,
    /**/ BossHakugin_Update,
    /**/ BossHakugin_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[GOHT_COLLIDER_BODYPART_MAX] = {
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NONE,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { GOHT_LIMB_HEAD, { { 1300, 200, 0 }, 30 }, 270 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { GOHT_LIMB_THORAX, { { 1400, 300, 0 }, 35 }, 270 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { GOHT_LIMB_PELVIS, { { 1600, -400, 0 }, 26 }, 270 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { GOHT_LIMB_FRONT_RIGHT_UPPER_LEG, { { 1700, 200, 400 }, 18 }, 270 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { GOHT_LIMB_FRONT_RIGHT_LOWER_LEG, { { 1000, 0, 0 }, 10 }, 270 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { GOHT_LIMB_FRONT_RIGHT_HOOF, { { 500, 0, 0 }, 9 }, 270 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { GOHT_LIMB_FRONT_LEFT_UPPER_LEG, { { 1700, 200, -400 }, 18 }, 270 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { GOHT_LIMB_FRONT_LEFT_LOWER_LEG, { { 1000, 0, 0 }, 10 }, 270 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { GOHT_LIMB_FRONT_LEFT_HOOF, { { 500, 0, 0 }, 9 }, 270 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { GOHT_LIMB_BACK_RIGHT_THIGH, { { 800, 0, 400 }, 15 }, 270 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { GOHT_LIMB_BACK_RIGHT_SHIN, { { 500, 200, 0 }, 9 }, 270 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { GOHT_LIMB_BACK_RIGHT_PASTERN, { { 300, 0, 0 }, 8 }, 270 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { GOHT_LIMB_BACK_RIGHT_HOOF, { { 500, 100, 0 }, 9 }, 270 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { GOHT_LIMB_BACK_LEFT_THIGH, { { 800, 0, -400 }, 15 }, 270 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { GOHT_LIMB_BACK_LEFT_SHIN, { { 500, 200, 0 }, 9 }, 270 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { GOHT_LIMB_BACK_LEFT_PASTERN, { { 300, 0, 0 }, 8 }, 270 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { GOHT_LIMB_BACK_LEFT_HOOF, { { 500, 100, 0 }, 9 }, 270 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { GOHT_LIMB_HEAD, { { 2400, -400, -2900 }, 12 }, 270 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { GOHT_LIMB_HEAD, { { 2400, -400, 2900 }, 12 }, 270 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sJntSphElementsInit),
    sJntSphElementsInit,
};

static ColliderTrisElementInit sTrisElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK5,
            { 0x20000000, 0x03, 0x08 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NONE,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { { { 22.0f, 0.0f, 100.0f }, { 0.0f, 0.0f, -100.0f }, { -22.0f, 0.0f, 100.0f } } },
    },
};

static ColliderTrisInit sTrisInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_TRIS,
    },
    ARRAY_COUNT(sTrisElementsInit),
    sTrisElementsInit,
};

static ColliderSphereInit sSphereInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_NONE,
        OC2_TYPE_2,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK5,
        { 0x20000000, 0x00, 0x08 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_HARD,
        BUMP_NONE,
        OCELEM_NONE,
    },
    { 1, { { 0, 0, 0 }, 23 }, 100 },
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HARD,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x02, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NONE,
        BUMP_ON,
        OCELEM_ON,
    },
    { 170, 40, 0, { 0, 0, 0 } },
};

typedef enum GohtDamageEffect {
    /* 0x0 */ GOHT_DMGEFF_NONE,
    /* 0x2 */ GOHT_DMGEFF_FIRE = 2,
    /* 0x3 */ GOHT_DMGEFF_FREEZE,
    /* 0x4 */ GOHT_DMGEFF_LIGHT_ORB,
    /* 0xC */ GOHT_DMGEFF_EXPLOSIVE = 0xC,
    /* 0xD */ GOHT_DMGEFF_BLUE_LIGHT_ORB,
    /* 0xE */ GOHT_DMGEFF_ARROW,
    /* 0xF */ GOHT_DMGEFF_GORON_SPIKES
} GohtDamageEffect;

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, GOHT_DMGEFF_NONE),
    /* Deku Stick     */ DMG_ENTRY(1, GOHT_DMGEFF_NONE),
    /* Horse trample  */ DMG_ENTRY(1, GOHT_DMGEFF_NONE),
    /* Explosives     */ DMG_ENTRY(1, GOHT_DMGEFF_EXPLOSIVE),
    /* Zora boomerang */ DMG_ENTRY(1, GOHT_DMGEFF_NONE),
    /* Normal arrow   */ DMG_ENTRY(1, GOHT_DMGEFF_ARROW),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, GOHT_DMGEFF_NONE),
    /* Hookshot       */ DMG_ENTRY(1, GOHT_DMGEFF_NONE),
    /* Goron punch    */ DMG_ENTRY(1, GOHT_DMGEFF_NONE),
    /* Sword          */ DMG_ENTRY(1, GOHT_DMGEFF_NONE),
    /* Goron pound    */ DMG_ENTRY(1, GOHT_DMGEFF_NONE),
    /* Fire arrow     */ DMG_ENTRY(1, GOHT_DMGEFF_FIRE),
    /* Ice arrow      */ DMG_ENTRY(1, GOHT_DMGEFF_FREEZE),
    /* Light arrow    */ DMG_ENTRY(1, GOHT_DMGEFF_LIGHT_ORB),
    /* Goron spikes   */ DMG_ENTRY(1, GOHT_DMGEFF_GORON_SPIKES),
    /* Deku spin      */ DMG_ENTRY(1, GOHT_DMGEFF_NONE),
    /* Deku bubble    */ DMG_ENTRY(1, GOHT_DMGEFF_NONE),
    /* Deku launch    */ DMG_ENTRY(1, GOHT_DMGEFF_NONE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, GOHT_DMGEFF_NONE),
    /* Zora barrier   */ DMG_ENTRY(0, GOHT_DMGEFF_NONE),
    /* Normal shield  */ DMG_ENTRY(0, GOHT_DMGEFF_NONE),
    /* Light ray      */ DMG_ENTRY(0, GOHT_DMGEFF_NONE),
    /* Thrown object  */ DMG_ENTRY(1, GOHT_DMGEFF_NONE),
    /* Zora punch     */ DMG_ENTRY(1, GOHT_DMGEFF_NONE),
    /* Spin attack    */ DMG_ENTRY(1, GOHT_DMGEFF_NONE),
    /* Sword beam     */ DMG_ENTRY(1, GOHT_DMGEFF_BLUE_LIGHT_ORB),
    /* Normal Roll    */ DMG_ENTRY(0, GOHT_DMGEFF_NONE),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, GOHT_DMGEFF_NONE),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, GOHT_DMGEFF_NONE),
    /* Unblockable    */ DMG_ENTRY(0, GOHT_DMGEFF_NONE),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, GOHT_DMGEFF_NONE),
    /* Powder Keg     */ DMG_ENTRY(1, GOHT_DMGEFF_EXPLOSIVE),
};

static CollisionCheckInfoInit sColChkInfoInit = { 30, 80, 100, MASS_IMMOVABLE };

/**
 * For whatever reason, the chin of the "face" on Goht's head relies on the actor to put the texture in segment 0x08 to
 * render properly. Since the texture never changes, the reason for doing it like this is unclear.
 */
TexturePtr sChinTexture = gGohtMetalPlateWithCirclePatternTex;

static s8 sLimbToBodyParts[GOHT_LIMB_MAX] = {
    BODYPART_NONE,                       // GOHT_LIMB_NONE
    BODYPART_NONE,                       // GOHT_LIMB_ROOT
    GOHT_BODYPART_PELVIS,                // GOHT_LIMB_PELVIS
    BODYPART_NONE,                       // GOHT_LIMB_THORAX_ROOT
    BODYPART_NONE,                       // GOHT_LIMB_THORAX_WRAPPER
    BODYPART_NONE,                       // GOHT_LIMB_FRONT_RIGHT_LEG_ROOT
    GOHT_BODYPART_FRONT_RIGHT_UPPER_LEG, // GOHT_LIMB_FRONT_RIGHT_UPPER_LEG
    BODYPART_NONE,                       // GOHT_LIMB_FRONT_RIGHT_LOWER_LEG_ROOT
    GOHT_BODYPART_FRONT_RIGHT_LOWER_LEG, // GOHT_LIMB_FRONT_RIGHT_LOWER_LEG
    GOHT_BODYPART_FRONT_RIGHT_HOOF,      // GOHT_LIMB_FRONT_RIGHT_HOOF
    BODYPART_NONE,                       // GOHT_LIMB_FRONT_LEFT_LEG_ROOT
    GOHT_BODYPART_FRONT_LEFT_UPPER_LEG,  // GOHT_LIMB_FRONT_LEFT_UPPER_LEG
    BODYPART_NONE,                       // GOHT_LIMB_FRONT_LEFT_LOWER_LEG_ROOT
    GOHT_BODYPART_FRONT_LEFT_LOWER_LEG,  // GOHT_LIMB_FRONT_LEFT_LOWER_LEG
    GOHT_BODYPART_FRONT_LEFT_HOOF,       // GOHT_LIMB_FRONT_LEFT_HOOF
    GOHT_BODYPART_THORAX,                // GOHT_LIMB_THORAX
    GOHT_BODYPART_HEAD,                  // GOHT_LIMB_HEAD
    BODYPART_NONE,                       // GOHT_LIMB_JAW_ROOT
    BODYPART_NONE,                       // GOHT_LIMB_JAW
    BODYPART_NONE,                       // GOHT_LIMB_BACK_RIGHT_LEG_ROOT
    BODYPART_NONE,                       // GOHT_LIMB_BACK_RIGHT_LEG_WRAPPER
    GOHT_BODYPART_BACK_RIGHT_THIGH,      // GOHT_LIMB_BACK_RIGHT_THIGH
    GOHT_BODYPART_BACK_RIGHT_SHIN,       // GOHT_LIMB_BACK_RIGHT_SHIN
    BODYPART_NONE,                       // GOHT_LIMB_BACK_RIGHT_PASTERN_ROOT
    BODYPART_NONE,                       // GOHT_LIMB_BACK_RIGHT_PASTERN
    GOHT_BODYPART_BACK_RIGHT_HOOF,       // GOHT_LIMB_BACK_RIGHT_HOOF
    BODYPART_NONE,                       // GOHT_LIMB_BACK_LEFT_LEG_ROOT
    BODYPART_NONE,                       // GOHT_LIMB_BACK_LEFT_LEG_WRAPPER
    GOHT_BODYPART_BACK_LEFT_THIGH,       // GOHT_LIMB_BACK_LEFT_THIGH
    GOHT_BODYPART_BACK_LEFT_SHIN,        // GOHT_LIMB_BACK_LEFT_SHIN
    BODYPART_NONE,                       // GOHT_LIMB_BACK_LEFT_PASTERN_ROOT
    BODYPART_NONE,                       // GOHT_LIMB_BACK_LEFT_PASTERN
    GOHT_BODYPART_BACK_LEFT_HOOF,        // GOHT_LIMB_BACK_LEFT_HOOF
};

s32 D_80B0EAB0[GOHT_MALFUNCTION_NUM_TYPES] = {
    GOHT_LIMB_BACK_LEFT_THIGH,       // FHGFLASH_SHOCK_GOHT_2
    GOHT_LIMB_BACK_RIGHT_PASTERN,    // FHGFLASH_SHOCK_GOHT_3
    GOHT_LIMB_JAW_ROOT,              // FHGFLASH_SHOCK_GOHT_4
    GOHT_LIMB_FRONT_LEFT_LOWER_LEG,  // FHGFLASH_SHOCK_GOHT_5
    GOHT_LIMB_FRONT_RIGHT_UPPER_LEG, // FHGFLASH_SHOCK_GOHT_6
};

static Color_RGBA8 sSparklePrimColor = { 250, 250, 250, 255 };
static Color_RGBA8 sSparkleEnvColor = { 180, 180, 180, 255 };

static Color_RGB8 sLightColor = { 0, 150, 255 }; // For lights and light orbs
static Color_RGB8 sLightningColor = { 0, 255, 255 };

void BossHakugin_Init(Actor* thisx, PlayState* play2) {
    static s32 sTexturesDesegmented = false;
    static InitChainEntry sInitChain[] = {
        ICHAIN_S8(hintId, TATL_HINT_ID_GOHT, ICHAIN_CONTINUE),
        ICHAIN_VEC3F_DIV1000(scale, 27, ICHAIN_CONTINUE),
        ICHAIN_U8(targetMode, TARGET_MODE_5, ICHAIN_CONTINUE),
        ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_STOP),
    };
    PlayState* play = play2;
    BossHakugin* this = THIS;
    Actor** actorPtr;
    s32 pad;
    s32 i;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    SkelAnime_InitFlex(play, &this->skelAnime, &gGohtSkel, &gGohtRunAnim, this->jointTable, this->morphTable,
                       GOHT_LIMB_MAX);

    if (!sTexturesDesegmented) {
        sTexturesDesegmented = true;
        sChinTexture = Lib_SegmentedToVirtual(sChinTexture);
    }

    Collider_InitAndSetJntSph(play, &this->bodyCollider, &this->actor, &sJntSphInit, this->bodyColliderElements);
    for (i = 0; i < GOHT_LIGHTNING_SEGMENT_COUNT; i++) {
        Collider_InitAndSetTris(play, &this->lightningSegments[i].collider, &this->actor, &sTrisInit,
                                this->lightningSegments[i].colliderElements);
    }

    Collider_InitAndSetSphere(play, &this->electricBallCollider, &this->actor, &sSphereInit);
    this->electricBallCollider.dim.worldSphere.radius = 40;
    Collider_InitAndSetCylinder(play, &this->iceCollider, &this->actor, &sCylinderInit);
    this->iceCollider.dim.pos.x = this->actor.world.pos.x - 50.0f;
    this->iceCollider.dim.pos.y = this->actor.world.pos.y;
    this->iceCollider.dim.pos.z = this->actor.world.pos.z;
    this->iceCollider.dim.radius = 150;
    this->iceCollider.dim.height = 300;
    this->lightNode = LightContext_InsertLight(play, &play->lightCtx, &this->lightInfo);
    Lights_PointNoGlowSetInfo(&this->lightInfo, 0, 0, 0, 255, 255, 180, -1);
    this->direction = GOHT_DIRECTION_COUNTERCLOCKWISE;

    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_SNOWHEAD_TEMPLE)) {
        BossHakugin_SpawnBlueWarp(this, play);
        Actor_Kill(&this->actor);
        return;
    }

    for (i = 0; i < ARRAY_COUNT(this->boulders); i++) {
        //! FAKE:
        actorPtr = &this->boulders[i];
        *actorPtr = Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_HAKUROCK, 0.0f, 0.0f, 0.0f, 0, 0,
                                       0, EN_HAKUROCK_TYPE_BOULDER);
    }

    for (i = 0; i < ARRAY_COUNT(this->stalactites); i++) {
        this->stalactites[i] = Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_HAKUROCK, 0.0f, 0.0f,
                                                  0.0f, 0, 0, 0, EN_HAKUROCK_TYPE_FALLING_STALACTITE);
    }

    for (i = 0; i < GOHT_ROCK_EFFECT_COUNT; i++) {
        this->rockEffects[i].timer = -1;
    }

    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    this->baseRotY = this->actor.shape.rot.y;
    this->limbDrawFlags = 0xFFFFFFFF;

    if (CHECK_EVENTINF(EVENTINF_INTRO_CS_WATCHED_GOHT)) {
        SEQCMD_PLAY_SEQUENCE(SEQ_PLAYER_BGM_MAIN, 0, NA_BGM_BOSS | SEQ_FLAG_ASYNC);
        this->actor.world.pos.x = 0.0f;
        BossHakugin_SetupRun(this);
    } else if (CHECK_EVENTINF(EVENTINF_ENTR_CS_WATCHED_GOHT)) {
        this->iceAlpha = 255;
        this->iceScaleY = 2.7f;
        BossHakugin_SpawnLargeStalactiteWalls(this);
        Animation_PlayOnce(&this->skelAnime, &gGohtThawAndBreakWallAnim);
        this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
        BossHakugin_SetupFrozenBeforeFight(this);
    } else {
        this->iceAlpha = 255;
        this->iceScaleY = 2.7f;
        BossHakugin_SpawnLargeStalactiteWalls(this);
        BossHakugin_SetupCutsceneStart(this);
    }
}

void BossHakugin_Destroy(Actor* thisx, PlayState* play) {
    BossHakugin* this = THIS;
    s32 pad;
    s32 i;

    LightContext_RemoveLight(play, &play->lightCtx, this->lightNode);
    Collider_DestroyJntSph(play, &this->bodyCollider);
    Collider_DestroyCylinder(play, &this->iceCollider);

    for (i = 0; i < GOHT_LIGHTNING_SEGMENT_COUNT; i++) {
        Collider_DestroyTris(play, &this->lightningSegments[i].collider);
    }

    Collider_DestroySphere(play, &this->electricBallCollider);
    AudioSfx_StopByPos(&this->sfxPos);
    AudioSfx_StopByPos(&this->electricBallSfxPos);
}

s32 BossHakugin_Vec3fNormalize(Vec3f* vec) {
    f32 magnitude = Math3D_Vec3fMagnitude(vec);

    if (magnitude < 0.0001f) {
        return false;
    }

    Math_Vec3f_Scale(vec, 1.0f / magnitude);
    return true;
}

void func_80B057A4(Vec3f* arg0, Vec3f* arg1, f32 arg2) {
    Vec3f sp34;
    Vec3f sp28;
    f32 temp_fa0 = (arg0->x * arg1->x) + (arg0->y * arg1->y) + (arg0->z * arg1->z);
    f32 var_fv1;

    if (fabsf(temp_fa0) < 1.0f) {
        var_fv1 = Math_FAcosF(temp_fa0);
    } else if (temp_fa0 >= 1.0f) {
        var_fv1 = 0.0f;
    } else {
        var_fv1 = M_PI;
    }

    if (arg2 > var_fv1) {
        arg2 = var_fv1;
    }

    if (arg2 < (M_PI / 180.0f)) {
        return;
    }

    Math3D_CrossProduct(arg0, arg1, &sp34);

    if (BossHakugin_Vec3fNormalize(&sp34)) {
        Matrix_RotateAxisF(arg2, &sp34, MTXMODE_NEW);
        Matrix_MultVec3f(arg0, &sp28);
        Math_Vec3f_Copy(arg0, &sp28);
    }
}

/**
 * Sets up the walls made of large stalactites that confine the player to the part of the boss room near the door; these
 * are the stalactites that are destroyed when Goht is thawed.
 */
void BossHakugin_SpawnLargeStalactiteWalls(BossHakugin* this) {
    s32 i = 0;
    Actor* last;
    Actor* now = this->stalactites[i++];

    now->params = EN_HAKUROCK_TYPE_LARGE_STALACTITE;
    now->world.pos.x = -500.0f;
    now->world.pos.y = this->actor.world.pos.y;
    now->world.pos.z = -3800.0f / 3.0f;
    now->shape.rot.y = this->actor.shape.rot.y + 0x4000;

    // Spawns the six large stalactites in front of Goht
    while (i < 6) {
        last = now;
        now = this->stalactites[i++];

        now->params = EN_HAKUROCK_TYPE_LARGE_STALACTITE;
        now->world.pos.x = last->world.pos.x;
        now->world.pos.y = this->actor.world.pos.y;
        now->world.pos.z = last->world.pos.z - 133.333333f; // 4000 / 3
        now->shape.rot.y = last->shape.rot.y;
    }

    // Spawns the four large stalactites to the left and right of Goht's ice block
    while (i < ARRAY_COUNT(this->stalactites)) {
        last = (i < 8) ? this->stalactites[i - 6] : this->stalactites[i - 4];
        now = this->stalactites[i++];

        now->params = EN_HAKUROCK_TYPE_LARGE_STALACTITE;
        now->world.pos.x = this->actor.world.pos.x;
        now->world.pos.y = this->actor.world.pos.y;
        now->world.pos.z = last->world.pos.z;
        now->shape.rot.y = this->actor.shape.rot.y - 0x4000;
    }
}

void BossHakugin_RequestQuakeAndRumble(BossHakugin* this, PlayState* play, s16 speed, s32 verticalMag, s16 duration) {
    s16 quakeIndex;

    if (verticalMag > 0) {
        quakeIndex = Quake_Request(GET_ACTIVE_CAM(play), QUAKE_TYPE_3);
        Quake_SetSpeed(quakeIndex, speed);
        Quake_SetPerturbations(quakeIndex, verticalMag, 0, 0, 0);
        Quake_SetDuration(quakeIndex, duration);

        Rumble_Request(this->actor.xyzDistToPlayerSq, 180, 20, 100);
    }
}

void BossHakugin_SpawnIceSparkle(BossHakugin* this, PlayState* play) {
    Vec3f pos;

    if (((this->actionFunc == BossHakugin_FrozenBeforeFight) || (this->actionFunc == BossHakugin_EntranceCutscene)) &&
        (Rand_ZeroOne() < 0.1f)) {
        pos.x =
            this->actor.world.pos.x + ((15.0f + (Rand_ZeroOne() * 15.0f)) * ((Rand_ZeroOne() < 0.5f) ? -1 : 1) * 4.0f);
        pos.y = this->actor.world.pos.y + ((10.0f + (Rand_ZeroOne() * 90.0f)) * 2.7f);
        pos.z =
            this->actor.world.pos.z + ((15.0f + (Rand_ZeroOne() * 15.0f)) * ((Rand_ZeroOne() < 0.5f) ? -1 : 1) * 4.0f);

        EffectSsKirakira_SpawnDispersed(play, &pos, &gZeroVec3f, &gZeroVec3f, &sSparklePrimColor, &sSparkleEnvColor,
                                        2000, 5);
    }
}

void BossHakugin_ApplyGoronSpikeBoost(BossHakugin* this, Player* player) {
    if (!this->hasAppliedGoronSpikeBoost && (player->stateFlags3 & PLAYER_STATE3_80000) &&
        !(player->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && (player->actor.velocity.y > 5.0f)) {
        player->actor.velocity.y *= 1.3f;
        player->linearVelocity *= 1.3f;
        this->hasAppliedGoronSpikeBoost = true;
    } else if (player->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        this->hasAppliedGoronSpikeBoost = false;
    }
}

void func_80B05D4C(BossHakugin* this) {
    Vec3f* lightPos = &this->actor.world.pos;
    s32 i;
    s16 var_t1 = 0;

    for (i = 0; i < GOHT_LIGHTNING_SEGMENT_COUNT; i++) {
        if (this->lightningSegments[i].alpha == 255) {
            lightPos = &this->lightningSegments[i].pos;
            var_t1 = 5000;
            break;
        }
    }
    if (i == GOHT_LIGHTNING_SEGMENT_COUNT) {
        if (this->chargingLightOrbScale > 0.0f) {
            lightPos = &this->chargingLightningPos;
            var_t1 = (this->chargingLightOrbScale / 30.0f) * 5000.0f;
        } else if ((this->electricBallState == GOHT_ELECTRIC_BALL_STATE_FLY_TOWARDS_PLAYER) ||
                   (this->electricBallState == GOHT_ELECTRIC_BALL_STATE_FLY_FORWARD)) {
            lightPos = &this->electricBallPos[0];
            var_t1 = 5000;
        } else if (this->electricBallState == GOHT_ELECTRIC_BALL_STATE_FADE_OUT) {
            lightPos = &this->electricBallPos[this->electricBallCount];
            var_t1 = (10 - this->electricBallCount) * 500.0f;
        }
    }
    Lights_PointNoGlowSetInfo(&this->lightInfo, lightPos->x, lightPos->y, lightPos->z, sLightColor.r, sLightColor.g,
                              sLightColor.b, var_t1);
}

void BossHakugin_SpawnBlueWarp(BossHakugin* this, PlayState* play) {
    s16 atan = Math_Atan2S_XY(this->actor.world.pos.z, this->actor.world.pos.x);
    Vec3f warpPos;
    Vec3f heartPos;
    f32 sp50;
    f32 sin;
    f32 cos;

    if (atan > 0x4000) {
        warpPos.x = 1400.0f;
        warpPos.y = 0.0f;
        warpPos.z = -1400.0f;
    } else if (atan < -0x4000) {
        warpPos.x = -1400.0f;
        warpPos.y = 0.0f;
        warpPos.z = -1400.0f;
    } else if (atan > 0) {
        warpPos.x = 1400.0f;
        warpPos.y = -320.0f;
        warpPos.z = 1400.0f;
    } else {
        warpPos.x = -1400.0f;
        warpPos.y = -160.0f;
        warpPos.z = 1400.0f;
    }

    sp50 = this->direction * 300.0f;
    sin = Math_SinS(this->targetRotY);
    cos = Math_CosS(this->targetRotY);
    heartPos.x = ((100.0f * sin) + warpPos.x) + (sp50 * cos);
    heartPos.z = ((100.0f * cos) + warpPos.z) - (sp50 * sin);
    Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_DOOR_WARP1, warpPos.x, warpPos.y, warpPos.z, 0, 0, 0,
                       ENDOORWARP1_FF_1);
    Actor_Spawn(&play->actorCtx, play, ACTOR_ITEM_B_HEART, heartPos.x, warpPos.y, heartPos.z, 0, 0, 0,
                BHEART_PARAM_NORMAL);
}

void func_80B0607C(BossHakugin* this, PlayState* play) {
    CollisionPoly* rightWallPoly = NULL;
    CollisionPoly* leftWallPoly = NULL;
    s32 bgId;
    s16 sp82;
    s16 sp80;
    s16 var_v0;
    Vec3f rightWallResultPos;
    Vec3f leftWallResultPos;
    Vec3f posA;
    Vec3f posB;
    f32 sp48;

    posA.x = this->actor.world.pos.x + (Math_SinS(this->baseRotY) * (5.0f * this->actor.speed));
    posA.y = this->actor.world.pos.y + 450.0f;
    posA.z = this->actor.world.pos.z + (Math_CosS(this->baseRotY) * (5.0f * this->actor.speed));

    posB.x = posA.x - Math_CosS(this->baseRotY) * 1000.0f;
    posB.y = posA.y;
    posB.z = posA.z + (Math_SinS(this->baseRotY) * 1000.0f);

    if (BgCheck_EntityLineTest1(&play->colCtx, &posA, &posB, &rightWallResultPos, &rightWallPoly, true, true, false,
                                true, &bgId)) {
        sp82 =
            Math_Atan2S_XY(COLPOLY_GET_NORMAL(rightWallPoly->normal.z), COLPOLY_GET_NORMAL(rightWallPoly->normal.x)) -
            this->baseRotY;
        this->distToRightWall = Math_Vec3f_DistXZ(&posA, &rightWallResultPos);
    } else {
        sp82 = 0;
        this->distToRightWall = 30000.0f;
    }

    posB.x = (2.0f * posA.x) - posB.x;
    posB.z = (2.0f * posA.z) - posB.z;

    if (BgCheck_EntityLineTest1(&play->colCtx, &posA, &posB, &leftWallResultPos, &leftWallPoly, true, true, false, true,
                                &bgId)) {
        sp80 = Math_Atan2S_XY(COLPOLY_GET_NORMAL(leftWallPoly->normal.z), COLPOLY_GET_NORMAL(leftWallPoly->normal.x)) -
               this->baseRotY;
        this->distToLeftWall = Math_Vec3f_DistXZ(&posA, &leftWallResultPos);
    } else {
        sp80 = 0;
        this->distToLeftWall = 30000.0f;
    }

    if (this->direction == GOHT_DIRECTION_CLOCKWISE) {
        this->distToLeftWall -= 50.0f;
    } else {
        this->distToRightWall -= 50.0f;
    }

    if (this->distToRightWall <= 89.100006f) {
        sp48 = (this->direction == GOHT_DIRECTION_CLOCKWISE) ? 89.100006f : 139.1f;
        this->actor.world.pos.x = (rightWallResultPos.x + (sp48 * Math_CosS(this->baseRotY))) -
                                  (Math_SinS(this->baseRotY) * (5.0f * this->actor.speed));
        this->actor.world.pos.z = (rightWallResultPos.z - (sp48 * Math_SinS(this->baseRotY))) -
                                  (Math_CosS(this->baseRotY) * (5.0f * this->actor.speed));
    } else if (this->distToLeftWall <= 89.100006f) {
        sp48 = (this->direction == GOHT_DIRECTION_CLOCKWISE) ? 139.1f : 89.100006f;
        this->actor.world.pos.x = (leftWallResultPos.x - (sp48 * Math_CosS(this->baseRotY))) -
                                  (Math_SinS(this->baseRotY) * (5.0f * this->actor.speed));
        this->actor.world.pos.z = (leftWallResultPos.z + (sp48 * Math_SinS(this->baseRotY))) -
                                  (Math_CosS(this->baseRotY) * (5.0f * this->actor.speed));
    }

    if ((this->distToLeftWall < 30000.0f) && (this->distToRightWall < 30000.0f)) {
        var_v0 = (s16)(sp82 + sp80) >> 1;
        if (((this->direction == GOHT_DIRECTION_CLOCKWISE) && (var_v0 < 0)) ||
            ((this->direction == GOHT_DIRECTION_COUNTERCLOCKWISE) && (var_v0 > 0))) {
            this->baseRotY += var_v0;
        }
    }
}

void func_80B06558(GohtLightningSegment* lightningSegment) {
    s32 i;
    Vec3f sp38[3];

    Matrix_SetTranslateRotateYXZ(lightningSegment->pos.x, lightningSegment->pos.y, lightningSegment->pos.z,
                                 &lightningSegment->rot);
    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
    for (i = 0; i < 3; i++) {
        Matrix_MultVec3f(&sTrisElementsInit[0].dim.vtx[i], &sp38[i]);
    }
    Collider_SetTrisVertices(&lightningSegment->collider, 0, &sp38[0], &sp38[1], &sp38[2]);
}

void BossHakugin_AddLightningSegment(BossHakugin* this, Vec3f* arg1, PlayState* play) {
    s32 i;
    Player* player = GET_PLAYER(play);
    CollisionPoly* spD4;
    Vec3f spC8;
    Vec3f spBC;
    Vec3f spB0;
    Vec3f spA4;
    Vec3f sp98;
    Vec3f sp8C;
    GohtLightningSegment* lightningSegment;
    s32 bgId;

    Math_Vec3f_Copy(&spC8, arg1);
    spBC.x = player->actor.world.pos.x - (Math_SinS(this->actor.shape.rot.y) * 50.0f);
    spBC.y = player->actor.world.pos.y + 40.0f;
    spBC.z = player->actor.world.pos.z - (Math_CosS(this->actor.shape.rot.y) * 50.0f);
    Actor_OffsetOfPointInActorCoords(&this->actor, &sp98, &spBC);
    Audio_PlaySfx_AtPos(&this->sfxPos, NA_SE_EN_COMMON_THUNDER_THR);

    for (i = 0; i < GOHT_LIGHTNING_SEGMENT_COUNT; i++) {
        lightningSegment = &this->lightningSegments[i];
        Actor_OffsetOfPointInActorCoords(&this->actor, &sp8C, &spC8);

        if (sp98.z < sp8C.z) {
            lightningSegment->rot.y = this->actor.shape.rot.y + ((s32)Rand_Next() >> 0x13);
        } else {
            lightningSegment->rot.y = Math_Vec3f_Yaw(&spC8, &spBC) + ((s32)Rand_Next() >> 0x13);
        }

        lightningSegment->rot.x = Math_Vec3f_Pitch(&spC8, &spBC) + ((s32)Rand_Next() >> 0x13);
        lightningSegment->rot.z = 0;
        lightningSegment->pos.x =
            spC8.x + (80.0f * Math_CosS(lightningSegment->rot.x) * Math_SinS(lightningSegment->rot.y));
        lightningSegment->pos.y = spC8.y - (80.0f * Math_SinS(lightningSegment->rot.x));
        lightningSegment->pos.z =
            spC8.z + (80.0f * Math_CosS(lightningSegment->rot.x) * Math_CosS(lightningSegment->rot.y));
        spB0.x = (2.0f * lightningSegment->pos.x) - spC8.x;
        spB0.y = (2.0f * lightningSegment->pos.y) - spC8.y;
        spB0.z = (2.0f * lightningSegment->pos.z) - spC8.z;

        if (BgCheck_EntityLineTest1(&play->colCtx, &spC8, &spB0, &spA4, &spD4, false, true, false, true, &bgId)) {
            lightningSegment->rot.x -= 0x2000;
            lightningSegment->pos.x =
                spC8.x + (80.0f * Math_CosS(lightningSegment->rot.x) * Math_SinS(lightningSegment->rot.y));
            lightningSegment->pos.y = spC8.y - (80.0f * Math_SinS(lightningSegment->rot.x));
            lightningSegment->pos.z =
                spC8.z + (80.0f * Math_CosS(lightningSegment->rot.x) * Math_CosS(lightningSegment->rot.y));
            spC8.x = (2.0f * lightningSegment->pos.x) - spC8.x;
            spC8.y = (2.0f * lightningSegment->pos.y) - spC8.y;
            spC8.z = (2.0f * lightningSegment->pos.z) - spC8.z;
        } else {
            Math_Vec3f_Copy(&spC8, &spB0);
        }

        lightningSegment->alpha = 255 + 20 * (i + 1);
        func_80B06558(lightningSegment);
        lightningSegment->rot.z = (s32)Rand_Next() >> 0x10;
    }
}

void func_80B0696C(BossHakugin* this, Vec3f* pos) {
    s32 i;
    GohtRockEffect* rockEffect;

    for (i = 0; i < GOHT_ROCK_EFFECT_COUNT; i++) {
        rockEffect = &this->rockEffects[i];
        if (rockEffect->timer < 0) {
            VecGeo velocityGeo;

            Math_Vec3f_Copy(&rockEffect->pos, pos);
            velocityGeo.pitch = Rand_S16Offset(0x1000, 0x3000);
            velocityGeo.yaw = this->actor.shape.rot.y + ((s32)Rand_Next() >> 0x12) + 0x8000;
            velocityGeo.r = Rand_ZeroFloat(5.0f) + 7.0f;
            rockEffect->velocity.x = velocityGeo.r * Math_CosS(velocityGeo.pitch) * Math_SinS(velocityGeo.yaw);
            rockEffect->velocity.y = velocityGeo.r * Math_SinS(velocityGeo.pitch);
            rockEffect->velocity.z = velocityGeo.r * Math_CosS(velocityGeo.pitch) * Math_CosS(velocityGeo.yaw);
            rockEffect->pos.x = pos->x + (Rand_ZeroFloat(3.0f) * rockEffect->velocity.x);
            rockEffect->pos.y = pos->y + (Rand_ZeroFloat(3.0f) * rockEffect->velocity.y);
            rockEffect->pos.z = pos->z + (Rand_ZeroFloat(3.0f) * rockEffect->velocity.z);
            rockEffect->scale = (Rand_ZeroFloat(6.0f) + 15.0f) * 0.0001f;
            rockEffect->timer = 40;
            rockEffect->type = GOHT_ROCK_EFFECT_TYPE_BOULDER;
            break;
        }
    }
}

void BossHakugin_SpawnBoulder(BossHakugin* this, Vec3f* pos) {
    Actor* boulder;
    s32 i;

    if (((this->transformedPlayerPos.z < -200.0f) && (this->actor.speed > 10.0f) &&
         (this->preventBoulderSpawnCount == 0) && (Rand_ZeroOne() < 0.4f))) {
        this->preventBoulderSpawnCount = 4;
    } else {
        if (this->preventBoulderSpawnCount > 0) {
            this->preventBoulderSpawnCount--;
        }
        return;
    }

    for (i = 0; i < ARRAY_COUNT(this->boulders); i++) {
        boulder = this->boulders[i];

        if (EN_HAKUROCK_GET_TYPE(boulder) == EN_HAKUROCK_TYPE_NONE) {
            Math_Vec3f_Copy(&boulder->world.pos, pos);
            boulder->params = EN_HAKUROCK_TYPE_BOULDER;
            break;
        }
    }
}

void BossHakugin_SpawnStalactite(BossHakugin* this) {
    Actor* stalactite;
    s32 i;

    if ((this->preventStalactiteSpawnCount == 0) && (this->actor.colChkInfo.health < 20) && (Rand_ZeroOne() < 0.35f)) {
        this->preventStalactiteSpawnCount = 4;
    } else {
        if (this->preventStalactiteSpawnCount > 0) {
            this->preventStalactiteSpawnCount--;
        }
        return;
    }

    for (i = 0; i < ARRAY_COUNT(this->stalactites); i++) {
        stalactite = this->stalactites[i];

        if (EN_HAKUROCK_GET_TYPE(stalactite) == EN_HAKUROCK_TYPE_NONE) {
            stalactite->params = EN_HAKUROCK_TYPE_FALLING_STALACTITE;
            return;
        }
    }
}

void BossHakugin_SpawnBomb(BossHakugin* this, PlayState* play) {
    EnBom* bomb;
    s16 temp_a1;

    if ((this->actor.speed > 10.0f) && ((s32)this->actor.colChkInfo.health < 10) &&
        (this->preventBombSpawnCount == 0) && (Rand_ZeroOne() < 0.35f)) {
        this->preventBombSpawnCount = 4;
    } else {
        if (this->preventBombSpawnCount > 0) {
            this->preventBombSpawnCount--;
        }
        return;
    }

    bomb = (EnBom*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_BOM,
                               this->bodyCollider.elements[GOHT_COLLIDER_BODYPART_THORAX].dim.worldSphere.center.x -
                                   (100.0f * Math_SinS(this->actor.shape.rot.y)),
                               this->bodyCollider.elements[GOHT_COLLIDER_BODYPART_THORAX].dim.worldSphere.center.y +
                                   100.0f,
                               this->bodyCollider.elements[GOHT_COLLIDER_BODYPART_THORAX].dim.worldSphere.center.z -
                                   (Math_CosS(this->actor.shape.rot.y) * 100.0f),
                               BOMB_EXPLOSIVE_TYPE_BOMB, 0, 0, BOMB_TYPE_BODY);

    if (bomb != NULL) {
        temp_a1 = (this->actor.yawTowardsPlayer - this->actor.shape.rot.y) - 0x8000;
        if (temp_a1 > 0x2000) {
            bomb->actor.world.rot.y = this->actor.shape.rot.y + 0xA000;
        } else if (temp_a1 < -0x2000) {
            bomb->actor.world.rot.y = this->actor.shape.rot.y + 0x6000;
        } else {
            bomb->actor.world.rot.y = this->actor.yawTowardsPlayer;
        }

        bomb->timer = (Rand_Next() >> 0x1C) + 17;
        bomb->actor.velocity.y = 2.0f;
        bomb->actor.speed = this->actor.xzDistToPlayer * 0.01f;
        bomb->actor.speed = CLAMP(bomb->actor.speed, 6.0f, 12.0f);

        Actor_SetScale(&bomb->actor, 0.02f);
    }
}

void BossHakugin_AddMalfunctionEffects(BossHakugin* this, PlayState* play) {
    GohtMalfunctionEffect* malfunctionEffect;
    GohtMalfunctionEffect* malfunctionEffect2;
    GohtMalfunctionEffect* malfunctionEffect3;
    Vec3f spA0;
    GohtBodyPart bodyPartIndex = this->malfunctionBodyPartIndex + 3;
    s32 var_s4;
    s32 type;
    s32 j;
    s32 pad;

    if (bodyPartIndex >= GOHT_BODYPART_MAX) {
        bodyPartIndex = 0;
    }

    for (type = 0; type < GOHT_MALFUNCTION_NUM_TYPES; type++) {
        if (((15 - (3 * type)) < this->actor.colChkInfo.health) ||
            !(GOHT_LIMB_DRAW_FLAG(D_80B0EAB0[type]) & this->limbDrawFlags)) {
            break;
        }

        malfunctionEffect3 = &this->malfunctionEffects[type][bodyPartIndex];
        malfunctionEffect2 = &this->malfunctionEffects[type][this->malfunctionBodyPartIndex];

        Math_Vec3f_Diff(&malfunctionEffect3->pos, &malfunctionEffect2->pos, &spA0);

        spA0.y -= 3.5f;

        var_s4 = Math3D_Vec3fMagnitude(&spA0) / 10.0f;
        if (var_s4 > 1) {
            if (var_s4 > 3) {
                var_s4 = 3;
            }
            Math_Vec3f_Scale(&spA0, 1.0f / var_s4);
        } else {
            var_s4 = 1;
        }

        for (j = 0; j < var_s4; j++) {
            malfunctionEffect = &this->malfunctionEffects[type][this->malfunctionBodyPartIndex + j];

            malfunctionEffect->pos.x = Rand_CenteredFloat(20.0f) + (malfunctionEffect2->pos.x + (spA0.x * j));
            malfunctionEffect->pos.y = Rand_CenteredFloat(20.0f) + (malfunctionEffect2->pos.y + (spA0.y * j));
            malfunctionEffect->pos.z = Rand_CenteredFloat(20.0f) + (malfunctionEffect2->pos.z + (spA0.z * j));
            malfunctionEffect->scaleXY = 0.01f;
            malfunctionEffect->life = 150;
            malfunctionEffect->unk_12 = 5 - j;
        }

        if ((play->gameplayFrames % 2) != 0) {
            EffectSsFhgFlash_SpawnShock(play, &this->actor,
                                        &this->malfunctionEffects[type][this->malfunctionBodyPartIndex].pos, 250,
                                        FHGFLASH_SHOCK_GOHT_2 + type);
        }
    }

    bodyPartIndex = this->malfunctionBodyPartIndex - 3;
    if (bodyPartIndex < 0) {
        this->malfunctionBodyPartIndex = GOHT_BODYPART_MAX - 3;
    } else {
        this->malfunctionBodyPartIndex = bodyPartIndex;
    }
}

// TODO: improve this name a bit
s32 BossHakugin_ChargeUpAttack(BossHakugin* this) {
    s16 rand = (Rand_Next() >> 0x12) + 0x4000;

    this->lightOrbRotZ += rand;
    if (this->chargeUpTimer == 5) {
        if (Math_SmoothStepToS(&this->frontHalfRotZ, -0x900, 4, 0x200, 0x80) == 0) {
            this->chargeUpTimer--;
        }

        this->chargingLightOrbScale = (this->frontHalfRotZ + 0x480) * -0.026041666f; // 30 / 0x480
        this->chargingLightOrbScale = CLAMP_MIN(this->chargingLightOrbScale, 0.001f);

        this->chargingLightningScale = (this->frontHalfRotZ - 0x700) * -0.00021059783f; // 0.62 / 0xB80
        this->chargingLightningScale = CLAMP_MAX(this->chargingLightningScale, 0.62f);

        if (this->chargingLightningScale > 0.0f) {
            this->chargingLightningTranslateZ = -100.0f - (((0.62f / this->chargingLightningScale) - 1.0f) * 200.0f);
        } else {
            this->chargingLightningTranslateZ = -200.0f;
        }

    } else if (this->chargeUpTimer > 0) {
        this->chargeUpTimer--;
    } else if (Math_ScaledStepToS(&this->frontHalfRotZ, 0x700, 0x380)) {
        this->chargingLightningScale = (0x700 - this->frontHalfRotZ) / 4096.0f * 0.62f;
        return true;
    }

    return false;
}

void func_80B07450(BossHakugin* this, PlayState* play) {
    Vec3f velocity;
    Vec3f pos;
    f32 quakeVerticalMag;
    s32 i;

    if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_ICEB_FOOTSTEP_OLD);
        Math_Vec3f_Copy(&pos, &this->bodyPartsPos[sLimbToBodyParts[GOHT_LIMB_FRONT_LEFT_HOOF]]);
        if (this->actor.xzDistToPlayer < 1500.0f) {
            quakeVerticalMag = (1500.0f - this->actor.xzDistToPlayer) * (1.0f / 1500.0f);
            BossHakugin_RequestQuakeAndRumble(this, play, 17000, 6.5f * quakeVerticalMag, 10);
        }

        BossHakugin_SpawnStalactite(this);
    } else if (Animation_OnFrame(&this->skelAnime, 2.0f)) {
        Math_Vec3f_Copy(&pos, &this->bodyPartsPos[sLimbToBodyParts[GOHT_LIMB_BACK_LEFT_HOOF]]);
        BossHakugin_SpawnBoulder(this, &pos);
    } else if (Animation_OnFrame(&this->skelAnime, 3.0f)) {
        Math_Vec3f_Copy(&pos, &this->bodyPartsPos[sLimbToBodyParts[GOHT_LIMB_FRONT_RIGHT_HOOF]]);
        BossHakugin_SpawnBomb(this, play);
    } else if (Animation_OnFrame(&this->skelAnime, 11.0f)) {
        Math_Vec3f_Copy(&pos, &this->bodyPartsPos[sLimbToBodyParts[GOHT_LIMB_BACK_RIGHT_HOOF]]);
        BossHakugin_SpawnBoulder(this, &pos);
    } else {
        return;
    }

    velocity.x = Math_SinS(this->actor.shape.rot.y) * -1.0f;
    velocity.y = 1.0f;
    velocity.z = Math_CosS(this->actor.shape.rot.y) * -1.0f;
    pos.x += 40.0f * velocity.x;
    pos.y += 5.0f;
    pos.z += 40.0f * velocity.z;
    func_800B12F0(play, &pos, &velocity, &gZeroVec3f, Rand_S16Offset(650, 100), Rand_S16Offset(20, 10), 30);
    for (i = 0; i < 4; i++) {
        func_80B0696C(this, &pos);
    }
}

void func_80B07700(BossHakugin* this, PlayState* play, s32 arg2) {
    Vec3f velocity;
    Vec3f pos;

    if (arg2) {
        velocity.y = (this->timer - 30) * (1 / 70.0f);
    } else {
        velocity.y = 0.1f;
    }

    velocity.x = Rand_CenteredFloat(2.0f) * velocity.y;
    velocity.z = Rand_CenteredFloat(2.0f) * velocity.y;

    pos.x = ((velocity.x >= 0.0f ? 1.0f : -1.0f) * (Rand_ZeroFloat(20.0f) + 5.0f) * 4.0f) + this->iceCollider.dim.pos.x;
    pos.z = ((velocity.z >= 0.0f ? 1.0f : -1.0f) * (Rand_ZeroFloat(20.0f) + 5.0f) * 4.0f) + this->iceCollider.dim.pos.z;

    if (arg2) {
        pos.y = this->iceCollider.dim.pos.y + (this->iceCollider.dim.height * velocity.y);
    } else {
        pos.y = (Rand_ZeroFloat(this->iceCollider.dim.height) * 0.8f) + this->iceCollider.dim.pos.y;
    }
    velocity.y += 0.8f;

    EffectSsIceSmoke_Spawn(play, &pos, &velocity, &gZeroVec3f, 600);
}

s32 func_80B0791C(BossHakugin* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 var_v1;
    s32 var_v0_2;
    f32 sp28;
    f32 sp24;

    if (this->transformedPlayerPos.z > 0.0f) {
        return false;
    }
    var_v1 = this->baseRotY - Camera_GetCamDirYaw(GET_ACTIVE_CAM(play));
    var_v0_2 = ABS_ALT(var_v1);

    if (var_v0_2 < 0x4000) {
        if (var_v0_2 < 0x1800) {
            this->lightningHitSomething = false;
        }
        return false;
    }
    if (this->lightningHitSomething == true) {
        return false;
    }
    sp24 = this->actor.world.pos.x * this->direction;
    sp28 = this->actor.world.pos.z * this->direction;
    if (((player->actor.world.pos.x > 1200.0f) && (player->actor.world.pos.z < 1200.0f) &&
         (player->actor.world.pos.z > -1200.0f) && (this->actor.world.pos.x < 0.0f) && (sp28 > 1200.0f)) ||
        ((player->actor.world.pos.x < -1200.0f) && (player->actor.world.pos.z < 1200.0f) &&
         (player->actor.world.pos.z > -1200.0f) && (this->actor.world.pos.x > 0.0f) && (sp28 < -1200.0f)) ||
        ((player->actor.world.pos.z > 1200.0f) && (player->actor.world.pos.x < 1200.0f) &&
         (player->actor.world.pos.x > -1200.0f) && (this->actor.world.pos.z < 0.0f) && (sp24 < -1200.0f)) ||
        ((player->actor.world.pos.z < -1200.0f) && (player->actor.world.pos.x < 1200.0f) &&
         (player->actor.world.pos.x > -1200.0f) && (this->actor.world.pos.z > 0.0f) && (sp24 > 1200.0f))) {
        return true;
    }
    return false;
}

// BossHakugin_Thaw
void func_80B07B88(BossHakugin* this, PlayState* play) {
    if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->drawDmgEffAlpha = 0.0f;
        Actor_SpawnIceEffects(play, &this->actor, this->bodyPartsPos, GOHT_BODYPART_MAX, 3, 0.7f, 0.5f);
    }
}

void BossHakugin_UpdateDrawDmgEffect(BossHakugin* this, PlayState* play, s32 colliderIndex) {
    if (this->actor.colChkInfo.damageEffect == GOHT_DMGEFF_FIRE) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->drawDmgEffAlpha = 3.0f;
        this->drawDmgEffScale = 2.5f;
    } else if (this->actor.colChkInfo.damageEffect == GOHT_DMGEFF_LIGHT_ORB) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
        this->drawDmgEffAlpha = 3.0f;
        this->drawDmgEffScale = 2.5f;
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG,
                    this->bodyCollider.elements[colliderIndex].info.bumper.hitPos.x,
                    this->bodyCollider.elements[colliderIndex].info.bumper.hitPos.y,
                    this->bodyCollider.elements[colliderIndex].info.bumper.hitPos.z, 0, 0, 0,
                    CLEAR_TAG_PARAMS(CLEAR_TAG_LARGE_LIGHT_RAYS));
    } else if (this->actor.colChkInfo.damageEffect == GOHT_DMGEFF_FREEZE) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX;
        this->drawDmgEffScale = 2.5f;
        this->drawDmgEffFrozenSteamScale = 3.75f;
        this->drawDmgEffAlpha = 1.0f;
    } else if (this->actor.colChkInfo.damageEffect == GOHT_DMGEFF_BLUE_LIGHT_ORB) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_BLUE_LIGHT_ORBS;
        this->drawDmgEffScale = 2.5f;
        this->drawDmgEffAlpha = 3.0f;
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG,
                    this->bodyCollider.elements[colliderIndex].info.bumper.hitPos.x,
                    this->bodyCollider.elements[colliderIndex].info.bumper.hitPos.y,
                    this->bodyCollider.elements[colliderIndex].info.bumper.hitPos.z, 0, 0, 3,
                    CLEAR_TAG_PARAMS(CLEAR_TAG_LARGE_LIGHT_RAYS));
    }
}

void BossHakugin_UpdateSubCam(BossHakugin* this, PlayState* play, f32 arg2, s16 arg3) {
    Camera* subCam = Play_GetCamera(play, this->subCamId);
    Vec3f sp38;
    Vec3f sp2C;

    Math_Vec3f_Diff(&subCam->at, &subCam->eye, &sp38);
    Math_Vec3f_StepTo(&subCam->eye, &this->subCamEye, arg2);

    if (BossHakugin_Vec3fNormalize(&sp38)) {
        sp2C.x = Math_CosS(this->subCamRot.x) * Math_SinS(this->subCamRot.y);
        sp2C.y = Math_SinS(this->subCamRot.x);
        sp2C.z = Math_CosS(this->subCamRot.x) * Math_CosS(this->subCamRot.y);
        func_80B057A4(&sp38, &sp2C, BINANG_TO_RAD(arg3));
    }

    subCam->at.x = subCam->eye.x + (50.0f * sp38.x);
    subCam->at.y = subCam->eye.y + (50.0f * sp38.y);
    subCam->at.z = subCam->eye.z + (50.0f * sp38.z);
    Play_SetCameraAtEye(play, this->subCamId, &subCam->at, &subCam->eye);
}

void BossHakugin_SetupEntranceCutscene(BossHakugin* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Vec3f subCamAt;

    Animation_PlayOnce(&this->skelAnime, &gGohtThawAndBreakWallAnim);
    this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;

    this->subCamId = CutsceneManager_GetCurrentSubCamId(this->actor.csId);

    subCamAt.x = player->actor.focus.pos.x;
    subCamAt.y = player->actor.focus.pos.y;
    subCamAt.z = player->actor.focus.pos.z;

    this->subCamEye.x = player->actor.focus.pos.x + (Math_SinS(player->actor.shape.rot.y) * 70.0f);
    this->subCamEye.y = player->actor.focus.pos.y + 20.0f;
    this->subCamEye.z = player->actor.focus.pos.z + (Math_CosS(player->actor.shape.rot.y) * 70.0f);

    Play_SetCameraAtEye(play, this->subCamId, &subCamAt, &this->subCamEye);

    this->subCamRot.x = Math_Atan2S_XY(70.0f, -20.0f);
    this->subCamRot.y = player->actor.shape.rot.y + 0x8000;
    Player_SetCsActionWithHaltedActors(play, &this->actor, PLAYER_CSACTION_21);
    this->timer = 0;
    this->actionFunc = BossHakugin_EntranceCutscene;
}

void BossHakugin_EntranceCutscene(BossHakugin* this, PlayState* play) {
    static Vec3f sSubCamAt = { 492.0f, 28.0f, -1478.0f };

    this->timer++;
    if (this->timer == 30) {
        this->subCamEye.x = 417.0f;
        this->subCamEye.y = 40.0f;
        this->subCamEye.z = -1417.0f;
        Play_SetCameraAtEye(play, this->subCamId, &sSubCamAt, &this->subCamEye);
        func_800BE33C(&this->subCamEye, &sSubCamAt, &this->subCamRot, true);
    } else if (this->timer == 50) {
        this->subCamRot.x = 0x1500;
    } else if (this->timer == 120) {
        CutsceneManager_Stop(this->actor.csId);
        SET_EVENTINF(EVENTINF_ENTR_CS_WATCHED_GOHT);
        BossHakugin_SetupFrozenBeforeFight(this);
        return;
    }

    if (this->timer > 30) {
        BossHakugin_UpdateSubCam(this, play, 5.0f, 0xC0);
    }
}

void BossHakugin_SetupFrozenBeforeFight(BossHakugin* this) {
    this->timer = 0;
    this->actionFunc = BossHakugin_FrozenBeforeFight;
}

void BossHakugin_FrozenBeforeFight(BossHakugin* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (!(player->stateFlags2 & PLAYER_STATE2_4000)) {
        DECR(this->timer);
    }

    if ((this->iceCollider.base.acFlags & AC_HIT) &&
        (this->iceCollider.info.acHitInfo->toucher.dmgFlags == DMG_FIRE_ARROW)) {
        this->iceCollider.base.atFlags &= ~AT_HIT;
        this->iceCollider.base.acFlags &= ~AC_HIT;
        this->iceCollider.base.ocFlags1 &= ~OC1_HIT;
        BossHakugin_SetupCutsceneStart(this);
        return;
    }

    if (this->iceCollider.base.atFlags & AT_HIT) {
        this->timer = 40;
        this->iceCollider.base.atFlags &= ~AT_HIT;
    }

    if (this->timer == 0) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->iceCollider.base);
    }

    CollisionCheck_SetAC(play, &play->colChkCtx, &this->iceCollider.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->iceCollider.base);
    this->disableCollidersTimer = 20;
}

void BossHakugin_SetupIntroCutsceneThaw(BossHakugin* this) {
    this->timer = 100;
    this->subCamId = CutsceneManager_GetCurrentSubCamId(this->actor.csId);
    Play_EnableMotionBlur(140);
    this->actionFunc = BossHakugin_IntroCutsceneDethaw;
}

void BossHakugin_IntroCutsceneDethaw(BossHakugin* this, PlayState* play) {
    Vec3f subCamEye;
    Vec3f subCamAt;
    s32 temp_v1;

    this->timer--;
    if ((this->timer >= 30) && ((this->timer % 2) != 0)) {
        func_80B07700(this, play, true);
    } else if ((this->timer % 4) == 0) {
        func_80B07700(this, play, false);
    }

    if (this->timer == 99) {
        subCamAt.x = 479.0f;
        subCamAt.y = 181.0f;
        subCamAt.z = -1637.0f;
        subCamEye.x = 328.0f;
        subCamEye.y = 164.0f;
        subCamEye.z = -1693.0f;
        Play_SetCameraAtEye(play, this->subCamId, &subCamAt, &subCamEye);
    } else if (this->timer == 75) {
        subCamAt.x = 693.0f;
        subCamAt.y = 162.0f;
        subCamAt.z = -1550.0f;
        subCamEye.x = 638.0f;
        subCamEye.y = 200.0f;
        subCamEye.z = -1407.0f;
        Play_SetCameraAtEye(play, this->subCamId, &subCamAt, &subCamEye);
    } else if (this->timer == 50) {
        subCamAt.x = 825.0f;
        subCamAt.y = 123.0f;
        subCamAt.z = -1637.0f;
        subCamEye.x = 734.0f;
        subCamEye.y = 145.0f;
        subCamEye.z = -1762.0f;
        Play_SetCameraAtEye(play, this->subCamId, &subCamAt, &subCamEye);
    } else if (this->timer == 25) {
        subCamAt.x = 711.0f;
        subCamAt.y = 76.0f;
        subCamAt.z = -1602.0f;
        subCamEye.x = 634.0f;
        subCamEye.y = 54.0f;
        subCamEye.z = -1735.0f;
        Play_SetCameraAtEye(play, this->subCamId, &subCamAt, &subCamEye);
    }

    this->iceScaleY -= 0.027f;
    temp_v1 = (s32)(this->timer * 5.1f) + 50;
    this->iceAlpha = CLAMP_MAX(temp_v1, 255);

    Actor_PlaySfx_Flagged(&this->actor, NA_SE_EV_ICE_MELT_LEVEL - SFX_FLAG);

    if (this->timer == 0) {
        this->iceAlpha = 0;
        BossHakugin_SetupIntroCutsceneWakeUp(this, play);
    }
}

void BossHakugin_SetupIntroCutsceneWakeUp(BossHakugin* this, PlayState* play) {
    static Vec3f sSubCamAt = { 894.0f, 176.0f, -1600.0f };
    static Vec3f sSubCamEye = { 972.0f, 176.0f, -1600.0f };
    Player* player = GET_PLAYER(play);

    Actor_PlaySfx(&this->actor, NA_SE_EN_ICEB_STEAM_DEMO_UP_OLD);
    Play_SetCameraAtEye(play, this->subCamId, &sSubCamAt, &sSubCamEye);
    this->subCamRot.x = -0x1F00;
    this->subCamRot.y = -0x4000;
    this->timer = 70;
    this->subCamEye.x = 680.0f;
    this->subCamEye.y = 370.0f;
    this->subCamEye.z = -1600.0f;
    player->actor.world.pos.x = 250.0f;
    player->actor.world.pos.z = -1560.0f;
    player->actor.shape.rot.y = this->actor.yawTowardsPlayer + 0x8000;
    player->currentYaw = player->actor.world.rot.y = player->actor.shape.rot.y;
    Player_SetCsActionWithHaltedActors(play, &this->actor, PLAYER_CSACTION_131);
    this->actionFunc = BossHakugin_IntroCutsceneWakeUp;
}

void BossHakugin_IntroCutsceneWakeUp(BossHakugin* this, PlayState* play) {
    static Vec3f sSubCamAt = { 377.0f, 140.0f, -1600.0f };
    static Vec3f sSubCamEye = { 282.0f, 108.0f, -1600.0f };
    s32 i;

    this->timer--;
    if (this->timer > 0) {
        BossHakugin_UpdateSubCam(this, play, 7.0f, 0xC0);
    } else if (this->timer == 0) {
        Play_SetCameraAtEye(play, this->subCamId, &sSubCamAt, &sSubCamEye);
        this->subCamRot.y = 0x4000;
        this->subCamRot.x = Math_Atan2S_XY(95.0f, 32.0f);
        this->subCamEye.x = 232.0f;
        this->subCamEye.y = 43.0f;
        this->subCamEye.z = -1600.0f;
        Actor_PlaySfx(&this->actor, NA_SE_EN_ICEB_STEAMS_DEMO_OLD);
    } else {
        BossHakugin_UpdateSubCam(this, play, 1.0f, 0xC0);

        if (Animation_OnFrame(&this->skelAnime, 20.0f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_ICEB_STEAM_DEMO_UP_OLD);
        }

        if (Animation_OnFrame(&this->skelAnime, 45.0f)) {
            SEQCMD_PLAY_SEQUENCE(SEQ_PLAYER_BGM_MAIN, 0, NA_BGM_BOSS | SEQ_FLAG_ASYNC);
        }

        if (Animation_OnFrame(&this->skelAnime, 65.0f)) {
            TitleCard_InitBossName(&play->state, &play->actorCtx.titleCtxt, Lib_SegmentedToVirtual(&gGohtTitleCardTex),
                                   160, 180, 128, 40);
        }

        if (Animation_OnFrame(&this->skelAnime, 86.0f)) {
            Audio_PlaySfx_AtPos(&this->sfxPos, NA_SE_EN_ICEB_CRY_OLD);
        }

        if (Animation_OnFrame(&this->skelAnime, 90.0f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_LAST1_DEMO_BREAK);
            for (i = 6; i < ARRAY_COUNT(this->stalactites); i++) {
                this->stalactites[i]->params = EN_HAKUROCK_TYPE_NONE;
            }
        }

        if (SkelAnime_Update(&this->skelAnime)) {
            BossHakugin_SetupIntroCutsceneRun(this, play);
            return;
        }
    }

    if (((this->timer + 12) >= 0) && ((this->timer % 4) == 0)) {
        func_80B07700(this, play, false);
    }
}

void BossHakugin_SetupIntroCutsceneRun(BossHakugin* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Vec3f sp30;

    this->subCamEye.x = player->actor.world.pos.x - 150.0f;
    this->subCamEye.y = player->actor.world.pos.y + 30.0f;
    this->subCamEye.z = player->actor.world.pos.z - 30.0f;
    sp30.x = this->actor.world.pos.x - 100.0f;
    sp30.y = this->actor.world.pos.y + 100.0f;
    sp30.z = this->actor.world.pos.z;
    func_800BE33C(&this->subCamEye, &sp30, &this->subCamRot, true);
    Animation_Change(&this->skelAnime, &gGohtRunAnim, 1.5f, 0.0f, 0.0f, ANIMMODE_LOOP, -3.0f);
    this->timer = 0;
    this->actor.speed = 5.0f;
    Player_SetCsActionWithHaltedActors(play, &this->actor, PLAYER_CSACTION_END);
    player->stateFlags1 |= PLAYER_STATE1_20;
    play->actorCtx.isOverrideInputOn = true;
    this->actionFunc = BossHakugin_IntroCutsceneRun;
}

void BossHakugin_IntroCutsceneRun(BossHakugin* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Camera* subCam = Play_GetCamera(play, this->subCamId);
    Vec3f subCamAt;
    f32 controlStickMagnitude;
    s32 i;

    Math_ScaledStepToS(&this->frontHalfRotZ, 0x800, 0x80);
    Math_StepToF(&this->actor.speed, 25.0f, 0.5f);
    this->skelAnime.playSpeed = (this->actor.speed / 32.0f) + 0.5f;
    func_80B07450(this, play);
    this->preventBoulderSpawnCount = 10;
    SkelAnime_Update(&this->skelAnime);
    this->timer++;
    if (this->timer < 8) {
        BossHakugin_UpdateSubCam(this, play, 25.0f, 0x120);
    } else if (this->timer == 22) {
        this->subCamEye.x = subCam->eye.x;
        this->subCamEye.y = subCam->eye.y;
        this->subCamEye.z = subCam->eye.z + 450.0f;
    } else if (this->timer == 62) {
        this->actor.flags |= ACTOR_FLAG_TARGETABLE;
        CutsceneManager_Stop(this->actor.csId);
        player->stateFlags1 &= ~PLAYER_STATE1_20;
        SET_EVENTINF(EVENTINF_INTRO_CS_WATCHED_GOHT);
        Play_DisableMotionBlur();
        BossHakugin_SetupRun(this);
        return;
    } else if (this->timer > 22) {
        subCamAt.x = this->actor.world.pos.x;
        subCamAt.y = this->actor.world.pos.y + 150.0f;
        subCamAt.z = this->actor.world.pos.z;
        Math_Vec3f_StepTo(&subCam->eye, &this->subCamEye, 35.0f);
        Play_SetCameraAtEye(play, this->subCamId, &subCamAt, &subCam->eye);

        if (this->timer == 42) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_LAST1_DEMO_WALL);
            for (i = 0; i < 6; i++) {
                this->stalactites[i]->params = EN_HAKUROCK_TYPE_NONE;
            }
        }
    }

    if (this->bodyCollider.base.atFlags & AT_HIT) {
        func_800B8D50(play, &this->actor, 10.0f, 0, 6.0f, 0);
    } else {
        play->actorCtx.isOverrideInputOn = true;
    }

    if (this->timer > 4) {
        controlStickMagnitude = (this->timer - 4) * 5.0f;
        controlStickMagnitude = CLAMP_MAX(controlStickMagnitude, 60.0f);
        Actor_SetControlStickData(play, &play->actorCtx.overrideInput, controlStickMagnitude, -0x4000);
    }
}

void BossHakugin_SetupRun(BossHakugin* this) {
    Animation_Change(&this->skelAnime, &gGohtRunAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP_INTERP, -5.0f);
    this->runOffsetRot = 0;
    this->chargingLightOrbScale = 0.0f;
    this->targetRotY = Rand_CenteredFloat(3072.0f);
    this->timer = 40;
    this->targetSpeed = 16.0f;
    this->actionFunc = BossHakugin_Run;
}

void BossHakugin_Run(BossHakugin* this, PlayState* play) {
    s16 yawDiff;

    if (this->disableCollidersTimer == 0) {
        this->bodyCollider.base.atFlags |= AT_ON;
    }

    if (this->electricBallState == GOHT_ELECTRIC_BALL_STATE_CHARGE) {
        if (BossHakugin_ChargeUpAttack(this)) {
            Math_Vec3f_Copy(&this->electricBallPos[0], &this->chargingLightningPos);
            this->electricBallSpeed = this->actor.speed + 100.0f;
            this->electricBallRot.x = Math_CosS(0xA00) * Math_SinS(this->actor.shape.rot.y);
            this->electricBallRot.y = Math_SinS(0xA00);
            this->electricBallRot.z = Math_CosS(0xA00) * Math_CosS(this->actor.shape.rot.y);
            this->electricBallState = GOHT_ELECTRIC_BALL_STATE_FLY_FORWARD;
            this->chargingLightOrbScale = 0.0f;
            Audio_PlaySfx_AtPos(&this->sfxPos, NA_SE_EN_COMMON_E_BALL_THR);
            this->electricBallCollider.base.atFlags |= AT_ON;
        }
    } else {
        Math_ScaledStepToS(&this->frontHalfRotZ, 0, 0x100);
    }

    if (func_80B0791C(this, play)) {
        BossHakugin_SetupChargeLightning(this, play);
    } else {
        if (this->damagedSpeedUpCounter > 55) {
            this->damagedSpeedUpCounter = 0;
            this->timer = 40;
            this->targetSpeed = 27.0f;
        }

        if ((this->timer == 40) &&
            (Math_SmoothStepToF(&this->actor.speed, this->targetSpeed, 0.15f, 1.0f, 0.1f) < 0.05f)) {
            this->timer--;
        } else if (this->timer != 40) {
            this->timer--;
            if (this->timer == 0) {
                if (this->actor.xzDistToPlayer > 1500.0f) {
                    this->targetSpeed = 12.5f;
                } else if (this->transformedPlayerPos.z > 0.0f) {
                    this->targetSpeed = 21.0f;
                } else {
                    this->targetSpeed = 14.5f;
                }
                this->targetSpeed += (30 - this->actor.colChkInfo.health) * (1.0f / 30.0f);
                this->timer = 40;
            }
        }

        this->skelAnime.playSpeed = (this->actor.speed / 32.0f) + 0.5f;
        SkelAnime_Update(&this->skelAnime);
        func_80B07450(this, play);

        if ((this->distToRightWall < (this->distToLeftWall * 0.5f)) || (this->distToRightWall < 89.100006f)) {
            this->targetRotY = (Rand_ZeroFloat(0.4f) + 0.6f) * 1536.0f;
        } else if ((this->distToLeftWall < (this->distToRightWall * 0.5f)) || (this->distToLeftWall < 89.100006f)) {
            this->targetRotY = -((Rand_ZeroFloat(0.4f) + 0.6f) * 1536.0f);
        } else if ((this->runOffsetRot == this->targetRotY) && (Rand_ZeroOne() < 0.005f)) {
            if (this->targetRotY > 0) {
                this->targetRotY = -((Rand_ZeroFloat(0.4f) + 0.6f) * 1536.0f);
            } else {
                this->targetRotY = ((Rand_ZeroFloat(0.4f) + 0.6f) * 1536.0f);
            }
        }

        Math_SmoothStepToS(&this->runOffsetRot, this->targetRotY, 5, 0x800, 0x10);
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->baseRotY + this->runOffsetRot, 5, 0x800, 0x10);

        yawDiff = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if ((this->lightningHitSomething != true) && (this->actor.xzDistToPlayer > 750.0f) &&
            (this->actor.xzDistToPlayer < 1650.0f) && (ABS_ALT(yawDiff) < 0x3000)) {
            BossHakugin_SetupCharge(this);
        }
    }
}

void BossHakugin_SetupCharge(BossHakugin* this) {
    Animation_Change(&this->skelAnime, &gGohtRunAnim, 1.5f, 0.0f, 0.0f, ANIMMODE_LOOP, -3.0f);
    this->actionFunc = BossHakugin_Charge;
}

void BossHakugin_Charge(BossHakugin* this, PlayState* play) {
    s16 var_v0;

    Math_ScaledStepToS(&this->frontHalfRotZ, 0x800, 0x100);
    Math_StepToF(&this->actor.speed, 25.0f, 2.0f);
    SkelAnime_Update(&this->skelAnime);
    func_80B07450(this, play);

    if ((this->transformedPlayerPos.z < 0.0f) || (this->bodyCollider.base.atFlags & AT_HIT)) {
        BossHakugin_SetupRun(this);
    } else {
        if ((this->distToLeftWall < 89.100006f) || (this->distToRightWall < 89.100006f)) {
            this->targetRotY = this->baseRotY;
        } else {
            if (((this->transformedPlayerPos.x > 0.0f) && (this->transformedPlayerPos.x < this->distToLeftWall)) ||
                ((this->transformedPlayerPos.x <= 0.0f) && (-this->transformedPlayerPos.x < this->distToRightWall))) {
                var_v0 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
                var_v0 = CLAMP(var_v0, -0x3000, 0x3000);
                this->targetRotY = this->actor.shape.rot.y + var_v0;
            } else {
                this->targetRotY =
                    ((s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y) >> 1) + this->actor.shape.rot.y;
            }
        }

        var_v0 = this->targetRotY - this->baseRotY;
        if (var_v0 > 0x1800) {
            this->targetRotY = this->baseRotY + 0x1800;
        } else if (var_v0 < -0x1800) {
            this->targetRotY = this->baseRotY - 0x1800;
        }
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->targetRotY, 5, 0x800, 0x100);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }
}

void BossHakugin_SetupFallDown(BossHakugin* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &gGohtFallDownAnim, -3.0f);
    this->bodyCollider.base.atFlags &= ~AT_ON;
    this->bodyCollider.base.acFlags &= ~AC_HARD;
    this->frontHalfRotZ = 0;
    this->finishedFallingDown = false;
    this->chargingLightOrbScale = 0.0f;
    if (this->electricBallState == GOHT_ELECTRIC_BALL_STATE_CHARGE) {
        Math_Vec3f_Copy(&this->electricBallPos[0], &this->chargingLightningPos);
        this->electricBallSpeed = this->actor.speed + 100.0f;
        this->electricBallRot.x = Math_CosS(0xA00) * Math_SinS(this->actor.shape.rot.y);
        this->electricBallRot.y = Math_SinS(0xA00);
        this->electricBallRot.z = Math_CosS(0xA00) * Math_CosS(this->actor.shape.rot.y);
        this->electricBallState = GOHT_ELECTRIC_BALL_STATE_FLY_FORWARD;
        this->chargingLightOrbScale = 0.0f;
        Audio_PlaySfx_AtPos(&this->sfxPos, NA_SE_EN_COMMON_E_BALL_THR);
        this->electricBallCollider.base.atFlags |= AT_ON;
    }
    this->timer = 60;
    this->actor.speed = 20.0f;
    this->actionFunc = BossHakugin_FallDown;
}

void BossHakugin_FallDown(BossHakugin* this, PlayState* play) {
    CollisionPoly* spBC;
    Vec3f velocity;
    Vec3f pos;
    s32 i;
    s32 bgId;

    Actor_PlaySfx_Flagged(&this->actor, NA_SE_EN_COMMON_WEAKENED - SFX_FLAG);

    if (SkelAnime_Update(&this->skelAnime)) {
        if (!this->finishedFallingDown) {
            this->finishedFallingDown = true;
            BossHakugin_RequestQuakeAndRumble(this, play, 17000, 7, 10);
        }

        if (this->actor.speed > 5.0f) {
            for (i = -1; i < 2; i += 2) {
                s16 temp1 = this->actor.shape.rot.y + (i * 0x7800);
                f32 temp_fs1;

                velocity.x = 2.0f * Math_SinS(temp1);
                velocity.y = 1.0f;
                velocity.z = 2.0f * Math_CosS(temp1);

                temp1 = this->actor.shape.rot.y + (i * 0x4000);
                temp_fs1 = Rand_ZeroFloat(190.0f);
                pos.x = this->actor.world.pos.x + (80.0f * Math_SinS(temp1)) +
                        (Math_SinS(this->actor.shape.rot.y) * temp_fs1);
                pos.z = this->actor.world.pos.z + (80.0f * Math_CosS(temp1)) +
                        (Math_CosS(this->actor.shape.rot.y) * temp_fs1);
                pos.y = this->actor.world.pos.y + 300.0f;
                pos.y = BgCheck_EntityRaycastFloor5_2(play, &play->colCtx, &spBC, &bgId, &this->actor, &pos) + 10.0f;
                func_800B12F0(play, &pos, &velocity, &gZeroVec3f, Rand_S16Offset(750, 100), 10, 30);
            }
        }
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->baseRotY, 5, 0x800, 0x10);
    this->actor.world.rot.y = this->actor.shape.rot.y;

    if (this->actor.speed < 0.1f) {
        this->timer--;
        this->actor.world.pos.x = this->actor.home.pos.x + Rand_CenteredFloat(5.0f);
        this->actor.world.pos.y = this->actor.home.pos.y + Rand_CenteredFloat(5.0f);
        this->actor.world.pos.z = this->actor.home.pos.z + Rand_CenteredFloat(5.0f);
        if (this->timer == 0) {
            this->bodyCollider.base.acFlags |= AC_HARD;
            Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.home.pos);
            BossHakugin_SetupRun(this);
            this->disableCollidersTimer = 20;
        }
    } else if (Math_StepToF(&this->actor.speed, 5.0f, 0.3f)) {
        Math_Vec3f_Copy(&this->actor.home.pos, &this->actor.world.pos);
        this->actor.speed = 0.0f;
    }
}

void BossHakugin_SetupThrow(BossHakugin* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    Animation_MorphToPlayOnce(&this->skelAnime, &gGohtStationaryAnim, -10.0f);
    player->actor.parent = &this->actor;
    this->bodyCollider.base.atFlags &= ~AT_ON;
    this->bodyCollider.base.ocFlags1 &= ~OC1_ON;
    this->timer = 10;
    this->actionFunc = BossHakugin_Throw;
}

void BossHakugin_Throw(BossHakugin* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 sp32;
    f32 sp2C;

    SkelAnime_Update(&this->skelAnime);
    Math_StepToF(&this->actor.speed, 0.0f, 2.0f);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->baseRotY, 5, 0x800, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;

    if (this->timer < 10) {
        this->timer--;
        if (this->timer == 0) {
            this->bodyCollider.base.atFlags |= AT_ON;
            this->bodyCollider.base.ocFlags1 |= OC1_ON;
            BossHakugin_SetupRun(this);
        }
    } else if (Math_ScaledStepToS(&this->frontHalfRotZ, -0x800, 0x1C0)) {
        player->av2.actionVar2 = 100;
        player->actor.parent = NULL;
        player->invincibilityTimer = 0;
        player->actor.shape.rot.x = 0;
        func_800B8D50(play, &this->actor, 10.0f, (this->actor.shape.rot.y + 0x8000), 15.0f, 0x10);
        player->actor.world.pos.y += 30.0f;
        this->timer--;
    } else {
        player->av2.actionVar2 = 0;
        sp32 = -this->headRot.z + 0x1F40;
        player->actor.shape.rot.x = -this->headRot.z + 0x8FC0;

        sp2C = Math_CosS(sp32);
        player->actor.world.pos.x = this->actor.focus.pos.x - (Math_SinS(this->baseRotY) * (20.0f * sp2C));
        player->actor.world.pos.y = this->actor.focus.pos.y - (Math_SinS(sp32) * 20.0f);
        player->actor.world.pos.z = this->actor.focus.pos.z - (Math_CosS(this->baseRotY) * (20.0f * sp2C));
    }
}

void BossHakugin_SetupChargeLightning(BossHakugin* this, PlayState* play) {
    f32 var_fv1;
    s16 atan;

    if (this->actionFunc != BossHakugin_ShootLightning) {
        Animation_MorphToPlayOnce(&this->skelAnime, &gGohtStationaryAnim, -5.0f);
        this->actor.speed = 0.0f;
        atan = Math_Atan2S_XY(this->actor.world.pos.z, this->actor.world.pos.x);

        if (atan < -0x4000) {
            this->actor.world.pos.x = -1200.0f;
            this->actor.shape.rot.y = 0x4000;
            this->actor.world.pos.z = -1200.0f;
        } else if (atan < 0) {
            this->actor.world.pos.x = -1200.0f;
            this->actor.shape.rot.y = -0x8000;
            this->actor.world.pos.z = 1200.0f;
        } else if (atan < 0x4000) {
            this->actor.world.pos.x = 1200.0f;
            this->actor.shape.rot.y = -0x4000;
            this->actor.world.pos.z = 1200.0f;
        } else {
            this->actor.world.pos.x = 1200.0f;
            this->actor.shape.rot.y = 0;
            this->actor.world.pos.z = -1200.0f;
        }

        if (this->direction == GOHT_DIRECTION_CLOCKWISE) {
            var_fv1 = -1.0f;
            this->actor.shape.rot.y -= 0x4000;
        } else {
            var_fv1 = 1.0f;
        }

        this->baseRotY = this->actor.shape.rot.y + (this->direction * 0x6000);
        this->actor.world.rot.y = this->actor.shape.rot.y;
        this->actor.world.pos.x += var_fv1 * 300.0f * Math_CosS(this->actor.shape.rot.y);
        this->actor.world.pos.z -= var_fv1 * 300.0f * Math_SinS(this->actor.shape.rot.y);
        this->actor.world.pos.y += 500.0f;
        this->actor.world.pos.y =
            BgCheck_EntityRaycastFloor1(&play->colCtx, &this->actor.floorPoly, &this->actor.world.pos);
        this->lightningHitSomething = false;
    }

    this->frontHalfRotZ = 0x700;
    this->timer = 150;
    this->chargingLightningTranslateZ = -100.0f;
    this->actionFunc = BossHakugin_ChargeLightning;
}

void BossHakugin_ChargeLightning(BossHakugin* this, PlayState* play) {
    f32 temp_fv1;

    SkelAnime_Update(&this->skelAnime);
    temp_fv1 = fabsf(this->transformedPlayerPos.x);
    Math_StepToF(&this->chargingLightOrbScale, 0.0f, 6.0f);
    if ((this->transformedPlayerPos.z < 0.0f) || (this->actor.xzDistToPlayer < 750.0f) ||
        (this->lightningHitSomething == true)) {
        BossHakugin_SetupRun(this);
        return;
    }

    if ((this->lightningSegments[0].alpha == 0) && (this->chargingLightOrbScale < 0.1f) && (temp_fv1 < 400.0f) &&
        (this->transformedPlayerPos.z > 0.0f)) {
        BossHakugin_SetupShootLightning(this);
        return;
    }

    if ((temp_fv1 > 400.0f) && ((play->gameplayFrames & 15) == 15)) {
        BossHakugin_SpawnStalactite(this);
        return;
    }

    if (this->timer > 0) {
        this->timer--;
    } else {
        this->direction = -this->direction;
        this->baseRotY = this->actor.shape.rot.y;
        this->actor.world.rot.y = this->actor.shape.rot.y;
        BossHakugin_SetupRun(this);
    }
}

void BossHakugin_SetupShootLightning(BossHakugin* this) {
    this->chargeUpTimer = 5;
    this->chargingLightOrbScale = 0.0f;
    this->actionFunc = BossHakugin_ShootLightning;
}

void BossHakugin_ShootLightning(BossHakugin* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    Audio_PlaySfx_AtPos(&this->sfxPos, NA_SE_EN_COMMON_THUNDER - SFX_FLAG);
    if (BossHakugin_ChargeUpAttack(this)) {
        BossHakugin_AddLightningSegment(this, &this->chargingLightningPos, play);
        BossHakugin_SetupChargeLightning(this, play);
    }
}

void BossHakugin_SetupCutsceneStart(BossHakugin* this) {
    CutsceneManager_Queue(this->actor.csId);
    if (this->actionFunc == BossHakugin_FrozenBeforeFight) {
        this->nextCutsceneType = GOHT_NEXT_CUTSCENE_TYPE_INTRO;
    } else {
        this->nextCutsceneType = GOHT_NEXT_CUTSCENE_TYPE_ENTRANCE;
    }

    this->actionFunc = BossHakugin_CutsceneStart;
}

void BossHakugin_CutsceneStart(BossHakugin* this, PlayState* play) {
    if (CutsceneManager_IsNext(this->actor.csId)) {
        CutsceneManager_StartWithPlayerCs(this->actor.csId, &this->actor);
        if (this->actor.colChkInfo.health == 0) {
            BossHakugin_SetupDeathCutscenePart1(this);
        } else if (this->nextCutsceneType == GOHT_NEXT_CUTSCENE_TYPE_INTRO) {
            BossHakugin_SetupIntroCutsceneThaw(this);
        } else {
            BossHakugin_SetupEntranceCutscene(this, play);
        }
    } else {
        CutsceneManager_Queue(this->actor.csId);
    }
}

void BossHakugin_SetupDeathCutscenePart1(BossHakugin* this) {
    f32 direction;

    Animation_Change(&this->skelAnime, &gGohtRunAnim, 1.3f, 0.0f, 0.0f, ANIMMODE_LOOP_INTERP, -3.0f);
    this->subCamId = CutsceneManager_GetCurrentSubCamId(this->actor.csId);

    if ((this->actor.world.pos.z >= 0.0f) && (this->actor.world.pos.x >= 0.0f)) {
        this->targetRotY = -0x4000;
    } else if ((this->actor.world.pos.z >= 0.0f) && (this->actor.world.pos.x < 0.0f)) {
        this->targetRotY = -0x8000;
    } else if ((this->actor.world.pos.x >= 0.0f) && (this->actor.world.pos.z < 0.0f)) {
        this->targetRotY = 0;
    } else {
        this->targetRotY = 0x4000;
    }

    if (this->direction == GOHT_DIRECTION_CLOCKWISE) {
        this->targetRotY -= 0x4000;
    }

    direction = this->direction;
    if ((this->targetRotY > 0x6000) || (this->targetRotY < -0x6000)) {
        this->subCamEye.x = direction * -1200.0f;
        this->subCamEye.y = (direction * 80.0f) + -240.0f + 60.0f;
        this->subCamEye.z = 1200.0f;
    } else if ((this->targetRotY < 0x2000) && (this->targetRotY > -0x2000)) {
        this->subCamEye.x = direction * 1200.0f;
        this->subCamEye.y = 60.0f;
        this->subCamEye.z = -1200.0f;
    } else if (this->targetRotY >= 0x2000) {
        this->subCamEye.x = -1200.0f;
        this->subCamEye.y = (80.0f * direction) + -80.0f + 60.0f;
        this->subCamEye.z = direction * -1200.0f;
    } else {
        this->subCamEye.x = 1200.0f;
        this->subCamEye.y = (-160.0f * direction) + -160.0f + 60.0f;
        this->subCamEye.z = direction * 1200.0f;
    }

    this->chargingLightOrbScale = 0.0f;
    this->frontHalfRotZ = 0;
    Play_EnableMotionBlur(140);
    this->runOffsetRot = Rand_S16Offset(0x800, 0x800) * ((Rand_ZeroOne() < 0.5f) ? -1 : 1);
    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM_MAIN, 1);
    this->actor.home.rot.y = this->actor.shape.rot.y;
    this->timer = 18;
    if ((this->electricBallState == GOHT_ELECTRIC_BALL_STATE_FLY_FORWARD) ||
        (this->electricBallState == GOHT_ELECTRIC_BALL_STATE_FLY_TOWARDS_PLAYER)) {
        this->electricBallState = GOHT_ELECTRIC_BALL_STATE_FADE_OUT;
        this->electricBallCount = 0;
    }

    this->deathCutsceneRandomHeadRot = Rand_ZeroFloat(6144.0f);
    this->headRot.y = 0;
    this->headRot.z = 0;
    this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
    this->actor.speed = CLAMP_MIN(this->actor.speed, 16.0f);
    this->actionFunc = BossHakugin_DeathCutscenePart1;
}

void BossHakugin_DeathCutscenePart1(BossHakugin* this, PlayState* play) {
    Vec3f subCamAt;
    f32 absPosX;
    f32 absPosZ;
    s32 absRotY;

    Math_StepToF(&this->actor.speed, 15.0f, 2.0f);
    SkelAnime_Update(&this->skelAnime);
    this->preventBoulderSpawnCount = 10;
    this->preventStalactiteSpawnCount = 10;
    this->preventBombSpawnCount = 10;
    func_80B07450(this, play);
    Math_SmoothStepToS(&this->actor.home.rot.y, this->baseRotY, 5, 0x800, 0x100);
    this->timer--;
    this->actor.shape.rot.y =
        (s32)(Math_SinF(this->timer * (M_PI / 18.0f)) * this->runOffsetRot) + this->actor.home.rot.y;

    if (this->timer == 0) {
        if (this->runOffsetRot > 0) {
            this->runOffsetRot = -Rand_S16Offset(0x800, 0x800);
        } else {
            this->runOffsetRot = Rand_S16Offset(0x800, 0x800);
        }
        this->timer = 18;
        this->deathCutsceneRandomHeadRot = Rand_ZeroFloat(6144.0f);
    }

    this->headRot.z = (8192.0f * Math_SinS(this->deathCutsceneRandomHeadRot)) * Math_SinF(this->timer * (M_PI / 9));
    this->headRot.y = (8192.0f * Math_CosS(this->deathCutsceneRandomHeadRot)) * Math_SinF(this->timer * (M_PI / 9));
    this->actor.shape.rot.z = Math_SinF(this->timer * (M_PI / 18)) * -(this->runOffsetRot * 0.3f);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    subCamAt.x = (Math_SinS(this->actor.shape.rot.y) * 100.0f) + this->actor.world.pos.x;
    subCamAt.y = this->actor.world.pos.y + 200.0f;
    subCamAt.z = (Math_CosS(this->actor.shape.rot.y) * 100.0f) + this->actor.world.pos.z;
    Play_SetCameraAtEye(play, this->subCamId, &subCamAt, &this->subCamEye);

    if (this->targetRotY == this->baseRotY) {
        absPosX = fabsf(this->actor.world.pos.x);
        absPosZ = fabsf(this->actor.world.pos.z);
        absRotY = ABS_ALT(this->actor.shape.rot.y);

        if (((absPosX > 1289.1f) && (absPosZ < 1110.9f) && ((absRotY < 0x2000) || (absRotY > 0x6000))) ||
            ((absPosZ > 1289.1f) && (absPosX < 1110.9f) && (absRotY > 0x2000) && (absRotY < 0x6000))) {
            BossHakugin_SetupDeathCutscenePart2(this);
        }
    }
}

void BossHakugin_SetupDeathCutscenePart2(BossHakugin* this) {
    if (this->direction == GOHT_DIRECTION_CLOCKWISE) {
        this->targetRotY -= 0x4000;
    } else {
        this->targetRotY += 0x4000;
    }

    this->actor.speed = 15.0f;
    this->actionFunc = BossHakugin_DeathCutscenePart2;
}

void BossHakugin_DeathCutscenePart2(BossHakugin* this, PlayState* play) {
    Vec3f subCamAt;
    Vec3f eyeTarget;
    s32 var_v0;
    s16 temp_a0;

    SkelAnime_Update(&this->skelAnime);
    subCamAt.x = (Math_SinS(this->actor.shape.rot.y) * 100.0f) + this->actor.world.pos.x;
    subCamAt.y = this->actor.world.pos.y + 200.0f;
    subCamAt.z = (Math_CosS(this->actor.shape.rot.y) * 100.0f) + this->actor.world.pos.z;
    temp_a0 = this->actor.shape.rot.y - (this->direction * 0x6000);
    eyeTarget.x = (Math_SinS(temp_a0) * 400.0f) + this->actor.world.pos.x;
    eyeTarget.y = this->actor.world.pos.y + 100.0f;
    eyeTarget.z = Math_CosS(temp_a0) * 400.0f + this->actor.world.pos.z;

    Math_Vec3f_StepTo(&this->subCamEye, &eyeTarget, 25.0f);
    Play_SetCameraAtEye(play, this->subCamId, &subCamAt, &this->subCamEye);
    this->preventBoulderSpawnCount = 10;
    this->preventStalactiteSpawnCount = 10;
    this->preventBombSpawnCount = 10;
    func_80B07450(this, play);

    if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->targetRotY, 0x300) &&
        ((this->distToRightWall <= 189.00002f) || (this->distToLeftWall <= 189.00002f))) {
        BossHakugin_SetupDead(this);
    } else if (((this->direction == GOHT_DIRECTION_CLOCKWISE) && (this->distToRightWall <= 189.00002f)) ||
               ((this->direction == GOHT_DIRECTION_COUNTERCLOCKWISE) && (this->distToLeftWall <= 189.00002f))) {
        var_v0 = ABS_ALT(this->targetRotY);
        if (var_v0 < 0x2000) {
            this->actor.world.pos.z = -1389.0f;
        } else if (var_v0 > 0x6000) {
            this->actor.world.pos.z = 1389.0f;
        } else if (this->targetRotY > 0) {
            this->actor.world.pos.x = -1389.0f;
        } else {
            this->actor.world.pos.x = 1389.0f;
        }
    }

    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void BossHakugin_SetupDead(BossHakugin* this) {
    this->timer = 0;
    this->actor.speed = 0.0f;
    this->skelAnime.playSpeed = 0.5f;
    func_80B0D9CC(this);
    this->actionFunc = BossHakugin_Dead;
}

typedef struct {
    /* 0x0 */ s32 colliderIndex;
    /* 0x4 */ u32 limbHideFlags;
} BossHakuginStruct_B0A8C4; // size = 0x4

static s32 D_80B0EB24[5] = { 0, 15, 26, 33, 36 };

static BossHakuginStruct_B0A8C4 D_80B0EB38[] = {
    { GOHT_COLLIDER_BODYPART_HEAD, GOHT_LIMB_DRAW_FLAG(GOHT_LIMB_HEAD) | GOHT_LIMB_DRAW_FLAG(GOHT_LIMB_JAW) },
    { GOHT_COLLIDER_BODYPART_FRONT_RIGHT_LOWER_LEG, GOHT_LIMB_DRAW_FLAG(GOHT_LIMB_FRONT_RIGHT_UPPER_LEG) |
                                                        GOHT_LIMB_DRAW_FLAG(GOHT_LIMB_FRONT_RIGHT_LOWER_LEG) |
                                                        GOHT_LIMB_DRAW_FLAG(GOHT_LIMB_FRONT_RIGHT_HOOF) },
    { GOHT_COLLIDER_BODYPART_FRONT_LEFT_LOWER_LEG, GOHT_LIMB_DRAW_FLAG(GOHT_LIMB_FRONT_LEFT_UPPER_LEG) |
                                                       GOHT_LIMB_DRAW_FLAG(GOHT_LIMB_FRONT_LEFT_LOWER_LEG) |
                                                       GOHT_LIMB_DRAW_FLAG(GOHT_LIMB_FRONT_LEFT_HOOF) },
    { GOHT_COLLIDER_BODYPART_BACK_LEFT_SHIN, GOHT_LIMB_DRAW_FLAG(GOHT_LIMB_BACK_LEFT_SHIN) |
                                                 GOHT_LIMB_DRAW_FLAG(GOHT_LIMB_BACK_LEFT_PASTERN) |
                                                 GOHT_LIMB_DRAW_FLAG(GOHT_LIMB_BACK_LEFT_HOOF) },
    { GOHT_COLLIDER_BODYPART_BACK_RIGHT_SHIN, GOHT_LIMB_DRAW_FLAG(GOHT_LIMB_BACK_RIGHT_SHIN) |
                                                  GOHT_LIMB_DRAW_FLAG(GOHT_LIMB_BACK_RIGHT_PASTERN) |
                                                  GOHT_LIMB_DRAW_FLAG(GOHT_LIMB_BACK_RIGHT_HOOF) },
    { GOHT_COLLIDER_BODYPART_THORAX, GOHT_LIMB_DRAW_FLAG(GOHT_LIMB_PELVIS) | GOHT_LIMB_DRAW_FLAG(GOHT_LIMB_THORAX) |
                                         GOHT_LIMB_DRAW_FLAG(GOHT_LIMB_BACK_RIGHT_THIGH) |
                                         GOHT_LIMB_DRAW_FLAG(GOHT_LIMB_BACK_LEFT_THIGH) },
};

void BossHakugin_Dead(BossHakugin* this, PlayState* play) {
    EnBom* bomb;
    Vec3s* test;
    Camera* subCam = Play_GetCamera(play, this->subCamId);
    Vec3f eyeTarget;
    s16 temp_s0;
    s32 sp60;
    BossHakuginStruct_B0A8C4* unkStruct;

    SkelAnime_Update(&this->skelAnime);
    sp60 = this->timer / 6;
    temp_s0 = this->actor.shape.rot.y + (0x6000 * this->direction);
    eyeTarget.x = (Math_SinS(temp_s0) * 500.0f) + this->actor.world.pos.x;
    eyeTarget.y = this->actor.world.pos.y + 250.0f;
    eyeTarget.z = (Math_CosS(temp_s0) * 500.0f) + this->actor.world.pos.z;
    Math_Vec3f_StepTo(&this->subCamEye, &eyeTarget, 25.0f);
    Play_SetCameraAtEye(play, this->subCamId, &subCam->at, &this->subCamEye);

    if (sp60 == 30) {
        Camera* mainCam = Play_GetCamera(play, CAM_ID_MAIN);

        Play_DisableMotionBlur();
        CutsceneManager_Stop(this->actor.csId);
        Play_SetCameraAtEye(play, this->subCamId, &mainCam->at, &mainCam->eye);
        BossHakugin_SpawnBlueWarp(this, play);
        func_80B0DFA8(this);
        this->actor.draw = BossHakugin_DrawDead;
        this->actor.update = BossHakugin_UpdateDead;
    } else if (((this->timer % 6) == 0) && (sp60 < 6)) {
        unkStruct = &D_80B0EB38[sp60];
        test = &this->bodyCollider.elements[unkStruct->colliderIndex].dim.worldSphere.center;
        bomb = (EnBom*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_BOM, test->x, test->y, test->z,
                                   BOMB_EXPLOSIVE_TYPE_POWDER_KEG, 0, 0, BOMB_TYPE_BODY);

        if (bomb != NULL) {
            bomb->timer = 0;
        }

        this->limbDrawFlags &= ~unkStruct->limbHideFlags;
        if (sp60 == 5) {
            SEQCMD_PLAY_SEQUENCE(SEQ_PLAYER_BGM_MAIN, 0, NA_BGM_CLEAR_BOSS | SEQ_FLAG_ASYNC);
        }
    }

    if (((this->timer + 3) % 6) == 0) {
        s32 i;

        sp60 = (this->timer + 3) / 6 - 1;
        if (sp60 < 4) {
            for (i = D_80B0EB24[sp60]; i < D_80B0EB24[sp60 + 1]; i++) {
                this->rockEffects[i].velocity.y = Rand_ZeroFloat(5.0f) + 5.0f;
            }
        }

        if (sp60 < 6) {
            if (sp60 & 1) {
                Audio_PlaySfx_AtPos(&this->sfxPos, NA_SE_EN_LAST1_DEMO_WALL);
            } else {
                Audio_PlaySfx_AtPos(&this->sfxPos, NA_SE_EN_LAST1_DEMO_BREAK);
            }
        }
    }

    this->timer++;
}

void func_80B0AC30(BossHakugin* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if ((this->bodyCollider.base.atFlags & AT_HIT) &&
        ((this->actionFunc == BossHakugin_Charge) || !(player->stateFlags3 & PLAYER_STATE3_80000))) {
        if ((this->actionFunc == BossHakugin_Charge) &&
            (this->bodyCollider.elements[GOHT_COLLIDER_BODYPART_HEAD].info.toucherFlags & TOUCH_HIT) &&
            !(this->bodyCollider.base.atFlags & AT_BOUNCED) && play->grabPlayer(play, player)) {
            BossHakugin_SetupThrow(this, play);
        } else if (player->stateFlags3 & PLAYER_STATE3_1000) {
            player->unk_B08 = player->linearVelocity = -5.0f;
            player->unk_B0C += player->unk_B08 * 0.05f;
            player->actor.velocity.y = 10.0f;
            player->unk_B8C = 4;
            player->actor.shape.rot.y = player->actor.home.rot.y = player->currentYaw = player->actor.world.rot.y;

        } else if (!(this->bodyCollider.base.atFlags & AT_BOUNCED)) {
            s16 var_a3 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;

            if (var_a3 > 0) {
                var_a3 = this->actor.shape.rot.y + (s32)(var_a3 / 2.0f) + 0x4000;
            } else {
                var_a3 = this->actor.shape.rot.y + (s32)(var_a3 / 2.0f) - 0x4000;
            }
            func_800B8D50(play, &this->actor, 5.0f, var_a3, 6.0f, 0);
        }
    }
}

s32 BossHakugin_UpdateDamage(BossHakugin* this, PlayState* play) {
    if (this->bodyCollider.base.acFlags & AC_HIT) {
        s32 i;

        for (i = 0; i < GOHT_COLLIDER_BODYPART_MAX; i++) {
            if (this->bodyCollider.elements[i].info.bumperFlags & BUMP_HIT) {
                break;
            }
        }

        if (i == GOHT_COLLIDER_BODYPART_MAX) {
            return false;
        }

        // DMG_DEKU_NUT | DMG_DEKU_STICK | DMG_ZORA_BOOMERANG | DMG_NORMAL_ARROW | DMG_HOOKSHOT | DMG_ICE_ARROW
        // | DMG_LIGHT_ARROW | DMG_DEKU_SPIN | DMG_DEKU_BUBBLE | DMG_DEKU_LAUNCH | DMG_ZORA_BARRIER
        if ((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) &&
            (this->bodyCollider.elements[i].info.acHitInfo->toucher.dmgFlags & 0x000DB0B3)) {
            return false;
        }

        func_80B07B88(this, play);

        if (this->actionFunc == BossHakugin_FallDown) {
            Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_RED, 255, COLORFILTER_BUFFLAG_OPA, 15);
            BossHakugin_UpdateDrawDmgEffect(this, play, i);
            if (Actor_ApplyDamage(&this->actor) == 0) {
                Enemy_StartFinishingBlow(play, &this->actor);
                Actor_PlaySfx(&this->actor, NA_SE_EN_ICEB_DEAD_OLD);
                BossHakugin_SetupCutsceneStart(this);
            } else {
                Actor_PlaySfx(&this->actor, NA_SE_EN_ICEB_DAMAGE_OLD);
            }

            this->disableCollidersTimer = 15;
            return true;
        }

        if (((this->actor.colChkInfo.damageEffect == GOHT_DMGEFF_GORON_SPIKES) ||
             (this->actor.colChkInfo.damageEffect == GOHT_DMGEFF_ARROW) ||
             (this->actor.colChkInfo.damageEffect == GOHT_DMGEFF_FIRE) ||
             (this->actor.colChkInfo.damageEffect == GOHT_DMGEFF_FREEZE) ||
             (this->actor.colChkInfo.damageEffect == GOHT_DMGEFF_LIGHT_ORB) ||
             (this->actor.colChkInfo.damageEffect == GOHT_DMGEFF_BLUE_LIGHT_ORB) ||
             (this->actor.colChkInfo.damageEffect == GOHT_DMGEFF_EXPLOSIVE)) &&
            ((this->actionFunc == BossHakugin_Run) || (this->actionFunc == BossHakugin_ShootLightning) ||
             (this->actionFunc == BossHakugin_ChargeLightning) || (this->actionFunc == BossHakugin_Charge))) {
            Player* player = GET_PLAYER(play);

            if (this->actor.colChkInfo.damageEffect == GOHT_DMGEFF_GORON_SPIKES) {
                player->pushedSpeed = 15.0f;
                if ((s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y) > 0) {
                    player->pushedYaw = this->actor.shape.rot.y + 0x4000;
                } else {
                    player->pushedYaw = this->actor.shape.rot.y - 0x4000;
                }
            }

            this->disableCollidersTimer = 15;
            Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_RED, 255, COLORFILTER_BUFFLAG_OPA, 15);
            this->damagedSpeedUpCounter += 35;
            BossHakugin_UpdateDrawDmgEffect(this, play, i);
            this->actor.colChkInfo.damage = this->bodyCollider.elements[i].info.acHitInfo->toucher.damage;

            if (Actor_ApplyDamage(&this->actor) == 0) {
                Enemy_StartFinishingBlow(play, &this->actor);
                Actor_PlaySfx(&this->actor, NA_SE_EN_ICEB_DEAD_OLD);
                BossHakugin_SetupCutsceneStart(this);
            } else {
                if ((this->actor.colChkInfo.damageEffect == GOHT_DMGEFF_EXPLOSIVE) ||
                    ((this->actor.colChkInfo.damageEffect == GOHT_DMGEFF_GORON_SPIKES) &&
                     (this->actionFunc != BossHakugin_Charge) &&
                     ((this->bodyCollider.elements[GOHT_COLLIDER_BODYPART_HEAD].info.bumperFlags & BUMP_HIT) ||
                      (this->bodyCollider.elements[GOHT_COLLIDER_BODYPART_THORAX].info.bumperFlags & BUMP_HIT) ||
                      (this->bodyCollider.elements[GOHT_COLLIDER_BODYPART_PELVIS].info.bumperFlags & BUMP_HIT) ||
                      (this->bodyCollider.elements[GOHT_COLLIDER_BODYPART_FRONT_RIGHT_UPPER_LEG].info.bumperFlags &
                       BUMP_HIT) ||
                      (this->bodyCollider.elements[GOHT_COLLIDER_BODYPART_FRONT_LEFT_UPPER_LEG].info.bumperFlags &
                       BUMP_HIT) ||
                      (this->bodyCollider.elements[GOHT_COLLIDER_BODYPART_BACK_RIGHT_THIGH].info.bumperFlags &
                       BUMP_HIT) ||
                      (this->bodyCollider.elements[GOHT_COLLIDER_BODYPART_BACK_LEFT_THIGH].info.bumperFlags &
                       BUMP_HIT) ||
                      (this->bodyCollider.elements[GOHT_COLLIDER_BODYPART_RIGHT_HORN].info.bumperFlags & BUMP_HIT) ||
                      (this->bodyCollider.elements[GOHT_COLLIDER_BODYPART_LEFT_HORN].info.bumperFlags & BUMP_HIT)))) {
                    BossHakugin_SetupFallDown(this);
                } else if ((this->electricBallState == GOHT_ELECTRIC_BALL_STATE_NONE) &&
                           (this->electricBallCount == 0) && (this->actionFunc == BossHakugin_Run) &&
                           (this->actor.colChkInfo.damageEffect == GOHT_DMGEFF_GORON_SPIKES)) {
                    this->chargeUpTimer = 5;
                    this->electricBallState = GOHT_ELECTRIC_BALL_STATE_CHARGE;
                }

                Actor_PlaySfx(&this->actor, NA_SE_EN_ICEB_DAMAGE_OLD);
            }

            return true;
        } else {
            s32 j;

            this->disableCollidersTimer = 20;
            for (j = 0; j < ARRAY_COUNT(this->bodyColliderElements); j++) {
                Vec3f hitPos;
                ColliderInfo* hurtbox = &this->bodyCollider.elements[j].info;

                if ((hurtbox->bumperFlags & BUMP_HIT) && (hurtbox->acHitInfo != NULL) &&
                    !(hurtbox->acHitInfo->toucherFlags & TOUCH_SFX_NONE)) {
                    Math_Vec3s_ToVec3f(&hitPos, &hurtbox->bumper.hitPos);
                    EffectSsHitmark_SpawnFixedScale(play, EFFECT_HITMARK_METAL, &hitPos);
                    CollisionCheck_SpawnShieldParticlesMetalSound(play, &hitPos, &this->actor.projectedPos);
                    break;
                }
            }
        }
    }

    return false;
}

void BossHakugin_UpdateRocks(BossHakugin* this) {
    GohtRockEffect* rockEffect;
    s32 i;

    for (i = 0; i < GOHT_ROCK_EFFECT_COUNT; i++) {
        rockEffect = &this->rockEffects[i];

        if (rockEffect->timer >= 0) {
            rockEffect->timer--;
            rockEffect->velocity.y += -1.0f;
            Math_Vec3f_Sum(&rockEffect->pos, &rockEffect->velocity, &rockEffect->pos);
            if (rockEffect->pos.y < -500.0f) {
                rockEffect->timer = -1;
            } else {
                rockEffect->rot.x += (s16)(0x700 + (Rand_Next() >> 0x17));
                rockEffect->rot.y += (s16)(0x900 + (Rand_Next() >> 0x17));
                rockEffect->rot.z += (s16)(0xB00 + (Rand_Next() >> 0x17));
            }
        }
    }
}

void BossHakugin_UpdateRocksDead(BossHakugin* this) {
    GohtRockEffect* rockEffect;
    s32 i;

    for (i = 0; i < 36; i++) {
        rockEffect = &this->rockEffects[i];
        Math_StepToF(&rockEffect->pos.y, rockEffect->velocity.x, rockEffect->velocity.y);
        if (rockEffect->velocity.y > 0.0f) {
            rockEffect->velocity.y += 6.0f;
        }
    }
}

void BossHakugin_UpdateMalfunctionEffects(BossHakugin* this) {
    s32 i;
    s32 j;

    for (i = 0; i < ARRAY_COUNT(this->malfunctionEffects); i++) {
        for (j = 0; j < ARRAY_COUNT(this->malfunctionEffects[0]); j++) {
            GohtMalfunctionEffect* malfunctionEffect = &this->malfunctionEffects[i][j];

            if (malfunctionEffect->life > 0) {
                malfunctionEffect->unk_12--;
                malfunctionEffect->pos.y += 3.5f;
                malfunctionEffect->scaleXY += 0.003f;
                if (malfunctionEffect->unk_12 < 0) {
                    malfunctionEffect->life -= 15;
                    if (malfunctionEffect->life < 0) {
                        malfunctionEffect->life = 0;
                    }
                }
            }
        }
    }
}

void BossHakugin_UpdateLightningSegments(BossHakugin* this, PlayState* play) {
    GohtLightningSegment* lightningSegment;
    s16 rand;
    s32 i;

    for (i = 0; i < GOHT_LIGHTNING_SEGMENT_COUNT; i++) {
        lightningSegment = &this->lightningSegments[i];

        if (lightningSegment->collider.base.atFlags & AT_HIT) {
            Player* player = GET_PLAYER(play);

            this->lightningHitSomething = true;
            Player_PlaySfx(player, NA_SE_EN_COMMON_E_BALL_HIT);
            lightningSegment->collider.base.atFlags &= ~AT_HIT;
        }
        if (lightningSegment->alpha > 0) {
            lightningSegment->alpha -= 20;
            if (lightningSegment->alpha <= 0) {
                lightningSegment->alpha = 0;
            } else if (lightningSegment->alpha <= 255) {
                rand = (s32)Rand_Next() >> 0x10;
                lightningSegment->rot.z = rand;
                if (lightningSegment->alpha > 60) {
                    CollisionCheck_SetAT(play, &play->colChkCtx, &lightningSegment->collider.base);
                }
            }
        }
    }
}

void BossHakugin_UpdateElectricBalls(BossHakugin* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    CollisionPoly* spA0 = NULL;
    Vec3f sp94;
    Vec3f sp88;
    Vec3f sp7C;
    Vec3f sp70;
    Vec3f* sp6C;
    Vec3f* var_s0;
    s32 var_s0_2;
    f32 sp60;
    s32 bgId;
    s32 sp58 = false;
    s16 temp_v1;

    sp6C = &this->electricBallPos[0];

    if (this->electricBallState == GOHT_ELECTRIC_BALL_STATE_FLY_FORWARD) {
        if (Math_StepToF(&this->electricBallSpeed, 50.0f, 3.5f)) {
            this->electricBallState = GOHT_ELECTRIC_BALL_STATE_FLY_TOWARDS_PLAYER;
        }
    } else if (this->electricBallState == GOHT_ELECTRIC_BALL_STATE_FLY_TOWARDS_PLAYER) {
        sp60 = BINANG_TO_RAD(Math3D_Vec3fDistSq(sp6C, &player->actor.world.pos) * (1.0f / SQ(120.0f)) * 32.0f);
        if (sp60 > M_PI / 4.0f) {
            sp60 = M_PI / 4.0f;
        }
        Math_Vec3f_Diff(&player->actor.world.pos, sp6C, &sp70);
        if (BossHakugin_Vec3fNormalize(&sp70)) {
            func_80B057A4(&this->electricBallRot, &sp70, sp60);
        }
    } else if (this->electricBallState != GOHT_ELECTRIC_BALL_STATE_FADE_OUT) {
        return;
    }

    Audio_PlaySfx_AtPos(&this->electricBallSfxPos, NA_SE_EN_COMMON_E_BALL - SFX_FLAG);

    if (this->electricBallCount < 10) {
        this->electricBallCount++;
    }

    if ((this->electricBallState == GOHT_ELECTRIC_BALL_STATE_FADE_OUT) && (this->electricBallCount == 9)) {
        this->electricBallState = GOHT_ELECTRIC_BALL_STATE_NONE;
        this->electricBallCount = 0;
    } else {
        var_s0 = &this->electricBallPos[9];
        while (var_s0 != sp6C) {
            Math_Vec3f_Copy(var_s0, var_s0 - 1);
            var_s0--;
        }

        this->lightOrbRotZ += (s16)(0x4000 + (Rand_Next() >> 0x12));
        if (this->electricBallState != GOHT_ELECTRIC_BALL_STATE_FADE_OUT) {
            if (this->electricBallCollider.base.atFlags & AT_HIT) {
                this->electricBallState = GOHT_ELECTRIC_BALL_STATE_FADE_OUT;
                this->electricBallCount = 0;
                this->electricBallCollider.base.atFlags &= ~AT_HIT;
                this->electricBallCollider.base.atFlags &= ~AT_ON;
                sp58 = true;
                Audio_PlaySfx_AtPos(&this->electricBallSfxPos, NA_SE_EN_COMMON_E_BALL_HIT);
            }

            sp88.x = sp6C->x + (this->electricBallSpeed * this->electricBallRot.x);
            sp88.y = sp6C->y + (this->electricBallSpeed * this->electricBallRot.y);
            sp88.z = sp6C->z + (this->electricBallSpeed * this->electricBallRot.z);

            if (BgCheck_EntityLineTest1(&play->colCtx, sp6C, &sp88, &sp94, &spA0, true, true, true, true, &bgId)) {
                var_s0_2 = 0;
                Math_Vec3f_Copy(sp6C, &sp94);

                if ((spA0->normal.y > -0x6665) && (spA0->normal.y < 0x3FFF)) {
                    temp_v1 = Math_Vec3f_Yaw(sp6C, &player->actor.world.pos) -
                              Math_Atan2S_XY(COLPOLY_GET_NORMAL(spA0->normal.z), COLPOLY_GET_NORMAL(spA0->normal.x));
                    //! FAKE: 0LL
                    var_s0_2 = (ABS_ALT(temp_v1) > 0x4000) ? 1 : 0LL;
                }

                if ((this->electricBallState == GOHT_ELECTRIC_BALL_STATE_FLY_TOWARDS_PLAYER) &&
                    (var_s0_2 || (spA0->normal.y >= 0x4000))) {
                    this->electricBallState = GOHT_ELECTRIC_BALL_STATE_FADE_OUT;
                    this->electricBallCount = 0;
                    if (!sp58) {
                        Audio_PlaySfx_AtPos(&this->electricBallSfxPos, NA_SE_EN_COMMON_E_BALL_HIT);
                    }
                } else {
                    sp7C.x = COLPOLY_GET_NORMAL(spA0->normal.x);
                    sp7C.y = COLPOLY_GET_NORMAL(spA0->normal.y);
                    sp7C.z = COLPOLY_GET_NORMAL(spA0->normal.z);
                    func_80179F64(&this->electricBallRot, &sp7C, &sp70);
                    Math_Vec3f_Copy(&this->electricBallRot, &sp70);
                }
            } else {
                Math_Vec3f_Copy(sp6C, &sp88);
            }

            this->electricBallCollider.dim.worldSphere.center.x = sp6C->x;
            this->electricBallCollider.dim.worldSphere.center.y = sp6C->y;
            this->electricBallCollider.dim.worldSphere.center.z = sp6C->z;
            CollisionCheck_SetAT(play, &play->colChkCtx, &this->electricBallCollider.base);
        }
    }
}

void BossHakugin_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    BossHakugin* this = (BossHakugin*)thisx;
    Vec3s sp70;
    Player* player = GET_PLAYER(play);

    this->blockMalfunctionEffects = false;
    DECR(this->damagedSpeedUpCounter);

    if (this->actionFunc != BossHakugin_CutsceneStart) {
        if (!BossHakugin_UpdateDamage(this, play)) {
            func_80B0AC30(this, play);
        }
    }

    func_80B0607C(this, play);
    Actor_OffsetOfPointInActorCoords(&this->actor, &this->transformedPlayerPos, &player->actor.world.pos);
    this->actionFunc(this, play);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 450.0f, 89.100006f, 0.0f,
                            UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_4 | UPDBGCHECKINFO_FLAG_8 |
                                UPDBGCHECKINFO_FLAG_10);
    func_800BE3D0(&this->actor, this->actor.shape.rot.y, &sp70);
    Math_ScaledStepToS(&this->actor.shape.rot.x, sp70.x, 0x100);
    Math_ScaledStepToS(&this->actor.shape.rot.z, sp70.z, 0x100);

    if (this->actionFunc == BossHakugin_Dead) {
        BossHakugin_UpdateRocksDead(this);
    } else {
        BossHakugin_UpdateRocks(this);
    }

    BossHakugin_UpdateMalfunctionEffects(this);
    BossHakugin_UpdateLightningSegments(this, play);
    BossHakugin_UpdateElectricBalls(this, play);
    BossHakugin_SpawnIceSparkle(this, play);
    BossHakugin_ApplyGoronSpikeBoost(this, player);
    func_80B05D4C(this);

    if ((this->bodyCollider.base.atFlags & AT_ON) && (this->actor.colorFilterTimer == 0)) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->bodyCollider.base);
    } else {
        this->bodyCollider.base.atFlags &= ~AT_HIT;
    }

    if (this->disableCollidersTimer == 0) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->bodyCollider.base);
    } else {
        this->bodyCollider.base.acFlags &= ~AC_HIT;
        this->disableCollidersTimer--;
    }

    if (this->bodyCollider.base.ocFlags1 & OC1_ON) {
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->bodyCollider.base);
    } else {
        this->bodyCollider.base.ocFlags1 &= ~OC1_HIT;
    }

    if (this->drawDmgEffAlpha > 0.0f) {
        if (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
            Math_StepToF(&this->drawDmgEffAlpha, 0.0f, 0.05f);
            this->drawDmgEffScale = (this->drawDmgEffAlpha + 1.0f) * 1.25f;
            this->drawDmgEffScale = CLAMP_MAX(this->drawDmgEffScale, 2.5f);
        } else if (!Math_StepToF(&this->drawDmgEffFrozenSteamScale, 2.5f, 5.0f / 12.0f)) {
            Actor_PlaySfx_Flagged(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
        } else {
            func_80B07B88(this, play);
        }
    }

    if (player->actor.floorHeight < -400.0f) {
        CollisionPoly* sp68 = NULL;
        Vec3f sp5C;
        Vec3f sp50;
        s32 bgId;

        if ((fabsf(player->actor.world.pos.z) < 1200.0f) && (fabsf(player->actor.world.pos.x) < 1200.0f)) {
            s16 temp_v0_5 = Math_Atan2S_XY(player->actor.world.pos.z, player->actor.world.pos.x);

            sp50.x = Math_SinS(temp_v0_5) * 2000.0f;
            sp50.z = Math_CosS(temp_v0_5) * 2000.0f;
        } else {
            if (player->actor.world.pos.z > 1200.0f) {
                sp50.z = 1500.0f;
            } else if (player->actor.world.pos.z < -1200.0f) {
                sp50.z = -1500.0f;
            } else {
                sp50.z = player->actor.world.pos.z;
            }
            if (player->actor.world.pos.x > 1200.0f) {
                sp50.x = 1500.0f;
            } else if (player->actor.world.pos.x < -1200.0f) {
                sp50.x = -1500.0f;
            } else {
                sp50.x = player->actor.world.pos.x;
            }
        }
        sp50.y = 100.0f;

        if (BgCheck_EntityLineTest1(&play->colCtx, &sp50, &player->actor.world.pos, &sp5C, &sp68, true, true, false,
                                    true, &bgId)) {
            Math_Vec3f_Copy(&player->actor.world.pos, &sp5C);
            Math_Vec3f_Copy(&player->actor.home.pos, &player->actor.world.pos);
            Math_Vec3f_Copy(&player->actor.prevPos, &player->actor.world.pos);
            player->actor.floorHeight = player->actor.world.pos.y;
            player->actor.world.pos.y = player->actor.world.pos.y + 1.0f;
        } else {
            player->actor.world.pos.x = 0.0f;
            player->actor.world.pos.y = 1.0f;
            player->actor.world.pos.z = -1200.0f;
            Math_Vec3f_Copy(&player->actor.home.pos, &player->actor.world.pos);
            Math_Vec3f_Copy(&player->actor.prevPos, &player->actor.world.pos);
            player->actor.floorHeight = player->actor.world.pos.y;
        }
    }
}

s32 BossHakugin_OverrideLimbDraw(struct PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                 Actor* thisx) {
    static s32 D_80B0EB68 = GOHT_MALFUNCTION_NUM_TYPES - 1;
    static s32 D_80B0EB6C = GOHT_LIMB_FRONT_RIGHT_UPPER_LEG;
    BossHakugin* this = THIS;

    if (this->actionFunc == BossHakugin_Dead) {
        if (limbIndex == GOHT_LIMB_ROOT) {
            pos->y -= this->actor.shape.yOffset;
        }
        if (!(this->limbDrawFlags & GOHT_LIMB_DRAW_FLAG(limbIndex))) {
            *dList = NULL;
        }
    }

    if (!this->blockMalfunctionEffects && (limbIndex == D_80B0EB6C)) {
        Matrix_MultZero(&this->malfunctionEffects[D_80B0EB68][this->malfunctionBodyPartIndex].pos);
        D_80B0EB68--;
        if (D_80B0EB68 < 0) {
            D_80B0EB68 = GOHT_MALFUNCTION_NUM_TYPES - 1;
        }
        D_80B0EB6C = D_80B0EAB0[D_80B0EB68];
    }

    if (limbIndex == GOHT_LIMB_HEAD) {
        rot->z += this->frontHalfRotZ;
        if (this->actionFunc == BossHakugin_DeathCutscenePart1) {
            rot->z += this->headRot.z;
            rot->y += this->headRot.y;
        }
    } else if (limbIndex == GOHT_LIMB_THORAX_WRAPPER) {
        rot->z += (s16)(this->frontHalfRotZ * 2);
    } else if ((limbIndex == GOHT_LIMB_FRONT_LEFT_LEG_ROOT) || (limbIndex == GOHT_LIMB_FRONT_RIGHT_LEG_ROOT)) {
        rot->z -= (s16)(this->frontHalfRotZ * 3);
    }

    return false;
}

void BossHakugin_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    BossHakugin* this = THIS;
    s8 bodyPartIndex;
    s32 i;
    f32 cos;
    s16 angle;

    Collider_UpdateSpheres(limbIndex, &this->bodyCollider);
    bodyPartIndex = sLimbToBodyParts[limbIndex];
    if (bodyPartIndex > BODYPART_NONE) {
        for (i = 0; i < GOHT_COLLIDER_BODYPART_MAX; i++) {
            if (this->bodyCollider.elements[i].dim.limb == limbIndex) {
                Math_Vec3s_ToVec3f(&this->bodyPartsPos[bodyPartIndex],
                                   &this->bodyCollider.elements[i].dim.worldSphere.center);
                break;
            }
        }
        if (i == GOHT_COLLIDER_BODYPART_MAX) {
            Matrix_MultZero(&this->bodyPartsPos[bodyPartIndex]);
        }
    }
    if (limbIndex == GOHT_LIMB_HEAD) {
        Matrix_MultVecX(3500.0f, &this->actor.focus.pos);
        this->actor.focus.rot.y = this->actor.shape.rot.y;
        if (this->actionFunc != BossHakugin_DeathCutscenePart1) {
            Matrix_MtxFToYXZRot(Matrix_GetCurrent(), &this->headRot, false);
        }

        if (this->chargingLightOrbScale > 0.0f) {
            angle = 0x12C0 - this->headRot.z;
            cos = Math_CosS(angle);
            this->chargingLightningPos.x =
                this->actor.focus.pos.x - (Math_SinS(this->actor.shape.rot.y) * (60.0f * cos));
            this->chargingLightningPos.y = this->actor.focus.pos.y - (Math_SinS(angle) * 60.0f);
            this->chargingLightningPos.z =
                this->actor.focus.pos.z - (Math_CosS(this->actor.shape.rot.y) * (60.0f * cos));
        }
    }
}

void BossHakugin_DrawRocks(BossHakugin* this, PlayState* play) {
    GohtRockEffect* rockEffect;
    s32 i;

    OPEN_DISPS(play->state.gfxCtx);

    gSPDisplayList(POLY_OPA_DISP++, gGohtRockMaterialDL);
    for (i = 0; i < GOHT_ROCK_EFFECT_COUNT; i++) {
        rockEffect = &this->rockEffects[i];
        if ((rockEffect->timer >= 0) && (rockEffect->type == GOHT_ROCK_EFFECT_TYPE_BOULDER)) {
            Matrix_SetTranslateRotateYXZ(rockEffect->pos.x, rockEffect->pos.y, rockEffect->pos.z, &rockEffect->rot);
            Matrix_Scale(rockEffect->scale, rockEffect->scale, rockEffect->scale, MTXMODE_APPLY);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, gGohtRockModelDL);
        }
    }

    gSPDisplayList(POLY_OPA_DISP++, gGohtStalactiteMaterialDL);
    for (i = 0; i < GOHT_ROCK_EFFECT_COUNT; i++) {
        rockEffect = &this->rockEffects[i];
        if ((rockEffect->timer >= 0) && (rockEffect->type == GOHT_ROCK_EFFECT_TYPE_STALACTITE)) {
            Matrix_SetTranslateRotateYXZ(rockEffect->pos.x, rockEffect->pos.y, rockEffect->pos.z, &rockEffect->rot);
            Matrix_Scale(rockEffect->scale, rockEffect->scale, rockEffect->scale, MTXMODE_APPLY);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, gGohtStalactiteModelDL);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void BossHakugin_DrawMalfunctionEffects(BossHakugin* this, PlayState* play) {
    GohtMalfunctionEffect* malfunctionEffect;
    s32 i;
    s32 j;
    s16 camYaw;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);

    gSPDisplayList(POLY_XLU_DISP++, gFrozenSteamMaterialDL);
    camYaw = Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)) + 0x8000;
    gDPSetEnvColor(POLY_XLU_DISP++, 1, 1, 1, 128);

    for (i = 0; i < ARRAY_COUNT(this->malfunctionEffects); i++) {
        for (j = 0; j < ARRAY_COUNT(this->malfunctionEffects[0]); j++) {
            malfunctionEffect = &this->malfunctionEffects[i][j];
            if (malfunctionEffect->life > 0) {
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 0, 0, 0, malfunctionEffect->life);
                gSPSegment(POLY_XLU_DISP++, 0x08,
                           Gfx_TwoTexScroll(play->state.gfxCtx, 0, malfunctionEffect->unk_12 * 3,
                                            malfunctionEffect->unk_12 * 15, 32, 64, 1, 0, 0, 32, 32));
                Matrix_Translate(malfunctionEffect->pos.x, malfunctionEffect->pos.y, malfunctionEffect->pos.z,
                                 MTXMODE_NEW);
                Matrix_RotateYS(camYaw, MTXMODE_APPLY);
                Matrix_Scale(malfunctionEffect->scaleXY, malfunctionEffect->scaleXY, 1.0f, MTXMODE_APPLY);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, gFrozenSteamModelDL);
            }
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void BossHakugin_DrawChargingLightning(BossHakugin* this, PlayState* play) {
    s32 pad;
    s32 i;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);

    if (this->chargingLightOrbScale > 0.0f) {
        gDPSetEnvColor(POLY_XLU_DISP++, sLightningColor.r, sLightningColor.g, sLightningColor.b, 0);
        gSPDisplayList(POLY_XLU_DISP++, gGohtLightningMaterialDL);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, 255);

        for (i = -1; i <= 1; i += 2) {
            Matrix_SetTranslateRotateYXZ(this->chargingLightningPos.x, this->chargingLightningPos.y,
                                         this->chargingLightningPos.z, &this->headRot);
            Matrix_RotateYS(0x1400 * i, MTXMODE_APPLY);
            Matrix_RotateXS(0xC00 * i, MTXMODE_APPLY);
            Matrix_RotateZS(this->lightOrbRotZ, MTXMODE_APPLY);
            Matrix_Scale(0.62f, 0.62f, this->chargingLightningScale, MTXMODE_APPLY);
            Matrix_Translate(0.0f, 0.0f, this->chargingLightningTranslateZ * i, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gGohtLightningModelDL);

            Matrix_RotateZS(0x4000, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gGohtLightningModelDL);
        }

        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetEnvColor(POLY_XLU_DISP++, sLightColor.r, sLightColor.g, sLightColor.b, 0);
        Matrix_Translate(this->chargingLightningPos.x, this->chargingLightningPos.y, this->chargingLightningPos.z,
                         MTXMODE_NEW);
        Matrix_ReplaceRotation(&play->billboardMtxF);
        Matrix_Scale(this->chargingLightOrbScale, this->chargingLightOrbScale, this->chargingLightOrbScale,
                     MTXMODE_APPLY);
        Matrix_RotateZS(this->lightOrbRotZ, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gGohtLightOrbMaterialDL);
        gSPDisplayList(POLY_XLU_DISP++, gGohtLightOrbModelDL);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void BossHakugin_DrawLightningSegments(BossHakugin* this, PlayState* play) {
    GohtLightningSegment* lightningSegment;
    s32 i;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);

    gDPSetEnvColor(POLY_XLU_DISP++, sLightningColor.r, sLightningColor.g, sLightningColor.b, 0);
    gSPDisplayList(POLY_XLU_DISP++, gGohtLightningMaterialDL);

    for (i = 0; i < GOHT_LIGHTNING_SEGMENT_COUNT; i++) {
        lightningSegment = &this->lightningSegments[i];

        if ((lightningSegment->alpha > 0) && (lightningSegment->alpha <= 255)) {
            Matrix_SetTranslateRotateYXZ(lightningSegment->pos.x, lightningSegment->pos.y, lightningSegment->pos.z,
                                         &lightningSegment->rot);
            Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);

            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, lightningSegment->alpha);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gGohtLightningModelDL);

            Matrix_RotateZS(0x4000, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gGohtLightningModelDL);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void BossHakugin_DrawElectricBalls(BossHakugin* this, PlayState* play2) {
    s32 pad[4];
    PlayState* play = play2;
    s32 end;
    f32 scale;
    s32 i;
    s16 rotZ;
    s32 alpha;
    Vec3f* pos;

    if (this->electricBallState == GOHT_ELECTRIC_BALL_STATE_FADE_OUT) {
        i = 9;
        end = this->electricBallCount;
    } else if (this->electricBallCount != 0) {
        i = this->electricBallCount - 1;
        end = 0;
    } else {
        return;
    }

    scale = 30.0f - ((i - 1) * 1.5f);
    alpha = 215 - (i * 15);

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);
    gDPSetEnvColor(POLY_XLU_DISP++, sLightColor.r, sLightColor.g, sLightColor.b, 0);

    rotZ = this->lightOrbRotZ;

    gSPDisplayList(POLY_XLU_DISP++, gGohtLightOrbMaterialDL);

    for (; i >= end; i--) {
        pos = &this->electricBallPos[i];

        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, alpha);
        Matrix_Translate(pos->x, pos->y, pos->z, MTXMODE_NEW);
        Matrix_ReplaceRotation(&play->billboardMtxF);
        Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
        Matrix_RotateZS(rotZ, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gGohtLightOrbModelDL);

        scale += 1.5f;
        alpha += 15;
        rotZ += 0x1000;
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void BossHakugin_DrawIce(BossHakugin* this, PlayState* play) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);
    func_800B8118(&this->actor, play, 0);
    Matrix_Translate(this->iceCollider.dim.pos.x, this->iceCollider.dim.pos.y, this->iceCollider.dim.pos.z,
                     MTXMODE_NEW);
    Matrix_Scale(4.0f, this->iceScaleY, 4.0f, MTXMODE_APPLY);
    Matrix_RotateYS(0xF00, MTXMODE_APPLY);
    Matrix_RotateXS(0x500, MTXMODE_APPLY);
    Matrix_RotateZS(-0x500, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, play->gameplayFrames & 0xFF, 32, 16, 1, 0,
                                (play->gameplayFrames * 2) & 0xFF, 64, 32)); // check
    gDPSetEnvColor(POLY_XLU_DISP++, 0, 50, 100, this->iceAlpha);
    gSPDisplayList(POLY_XLU_DISP++, gEffIceFragment3DL);

    CLOSE_DISPS(play->state.gfxCtx);
}

void BossHakugin_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    BossHakugin* this = THIS;
    u8* tex = GRAPH_ALLOC(play->state.gfxCtx, GOHT_SHADOW_TEX_SIZE);

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, sChinTexture);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          BossHakugin_OverrideLimbDraw, BossHakugin_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);

    Actor_DrawDamageEffects(play, &this->actor, this->bodyPartsPos, GOHT_BODYPART_MAX, this->drawDmgEffScale,
                            this->drawDmgEffFrozenSteamScale, this->drawDmgEffAlpha, this->drawDmgEffType);

    SkinMatrix_Vec3fMtxFMultXYZ(&play->viewProjectionMtxF, &this->chargingLightningPos, &this->sfxPos);
    SkinMatrix_Vec3fMtxFMultXYZ(&play->viewProjectionMtxF, &this->electricBallPos[0], &this->electricBallSfxPos);

    if (!this->blockMalfunctionEffects) {
        BossHakugin_AddMalfunctionEffects(this, play);
    }
    this->blockMalfunctionEffects = true;

    if (this->actor.colorFilterTimer != 0) {
        func_800AE5A0(play);
    }

    if (this->actionFunc == BossHakugin_Dead) {
        BossHakugin_DrawDead(&this->actor, play);
    } else {
        BossHakugin_DrawRocks(this, play);
    }

    BossHakugin_DrawMalfunctionEffects(this, play);
    BossHakugin_DrawChargingLightning(this, play);
    BossHakugin_DrawLightningSegments(this, play);
    BossHakugin_DrawElectricBalls(this, play);

    if (this->iceAlpha > 0) {
        BossHakugin_DrawIce(this, play);
    }

    if (this->actionFunc != BossHakugin_Dead) {
        BossHakugin_GenShadowTex(tex, this);
        BossHakugin_DrawShadowTex(tex, this, play);
    }
}

s32 D_80B0EB70[6] = { 1, 2, 3, 3, 2, 1 };
s32 D_80B0EB88[7] = { 2, 3, 4, 4, 4, 3, 2 };
s32 D_80B0EBA4[8] = { 2, 3, 4, 4, 4, 4, 3, 2 };
s32 D_80B0EBC4[14] = { 2, 4, 5, 6, 7, 8, 8, 8, 8, 7, 6, 5, 4, 2 };

static s32 sParentShadowBodyParts[GOHT_BODYPART_MAX] = {
    GOHT_BODYPART_THORAX,                // GOHT_BODYPART_PELVIS
    BODYPART_NONE,                       // GOHT_BODYPART_THORAX
    GOHT_BODYPART_THORAX,                // GOHT_BODYPART_HEAD
    GOHT_BODYPART_THORAX,                // GOHT_BODYPART_FRONT_RIGHT_UPPER_LEG
    GOHT_BODYPART_FRONT_RIGHT_UPPER_LEG, // GOHT_BODYPART_FRONT_RIGHT_LOWER_LEG
    GOHT_BODYPART_FRONT_RIGHT_LOWER_LEG, // GOHT_BODYPART_FRONT_RIGHT_HOOF
    GOHT_BODYPART_THORAX,                // GOHT_BODYPART_FRONT_LEFT_UPPER_LEG
    GOHT_BODYPART_FRONT_LEFT_UPPER_LEG,  // GOHT_BODYPART_FRONT_LEFT_LOWER_LEG
    GOHT_BODYPART_FRONT_LEFT_LOWER_LEG,  // GOHT_BODYPART_FRONT_LEFT_HOOF
    GOHT_BODYPART_PELVIS,                // GOHT_BODYPART_BACK_RIGHT_THIGH
    GOHT_BODYPART_BACK_RIGHT_THIGH,      // GOHT_BODYPART_BACK_RIGHT_SHIN
    GOHT_BODYPART_BACK_RIGHT_SHIN,       // GOHT_BODYPART_BACK_RIGHT_HOOF
    GOHT_BODYPART_PELVIS,                // GOHT_BODYPART_BACK_LEFT_THIGH
    GOHT_BODYPART_BACK_LEFT_THIGH,       // GOHT_BODYPART_BACK_LEFT_SHIN
    GOHT_BODYPART_BACK_LEFT_SHIN         // GOHT_BODYPART_BACK_LEFT_HOOF
};

static u8 sShadowSizes[GOHT_BODYPART_MAX] = {
    1, // GOHT_BODYPART_PELVIS
    2, // GOHT_BODYPART_THORAX
    1, // GOHT_BODYPART_HEAD
    0, // GOHT_BODYPART_FRONT_RIGHT_UPPER_LEG
    3, // GOHT_BODYPART_FRONT_RIGHT_LOWER_LEG
    3, // GOHT_BODYPART_FRONT_RIGHT_HOOF
    0, // GOHT_BODYPART_FRONT_LEFT_UPPER_LEG
    3, // GOHT_BODYPART_FRONT_LEFT_LOWER_LEG
    3, // GOHT_BODYPART_FRONT_LEFT_HOOF
    0, // GOHT_BODYPART_BACK_RIGHT_THIGH
    3, // GOHT_BODYPART_BACK_RIGHT_SHIN
    3, // GOHT_BODYPART_BACK_RIGHT_HOOF
    0, // GOHT_BODYPART_BACK_LEFT_THIGH
    3, // GOHT_BODYPART_BACK_LEFT_SHIN
    3  // GOHT_BODYPART_BACK_LEFT_HOOF
};

void BossHakugin_FillShadowTex(BossHakugin* this, u8* tex, f32 weight) {
    s32 index;
    s32 i;
    s32 baseX;
    s32 baseY;
    s32 addY;
    s32 x;
    s32 y = BODYPART_NONE;
    Vec3f lerp;
    Vec3f* parentBodyPartPos;
    Vec3f* bodyPartPos;
    Vec3f pos;
    Vec3f startVec;

    for (i = 0; i < GOHT_BODYPART_MAX; i++) {
        if ((weight == 0.0f) || (y = sParentShadowBodyParts[i]) > BODYPART_NONE) {
            bodyPartPos = &this->bodyPartsPos[i];
            if (weight > 0.0f) {
                parentBodyPartPos = &this->bodyPartsPos[y];

                VEC3F_LERPIMPDST(&lerp, bodyPartPos, parentBodyPartPos, weight);

                pos.x = lerp.x - this->actor.world.pos.x;
                pos.y = lerp.y - this->actor.world.pos.y + 76.0f + 30.0f + 30.0f + 600.0f;
                pos.z = lerp.z - this->actor.world.pos.z;
            } else {
                pos.x = bodyPartPos->x - this->actor.world.pos.x;
                pos.y = bodyPartPos->y - this->actor.world.pos.y + 76.0f + 30.0f + 30.0f + 600.0f;
                pos.z = bodyPartPos->z - this->actor.world.pos.z;
            }
            Matrix_MultVec3f(&pos, &startVec);

            startVec.x *= 0.07f;
            startVec.y *= 0.07f;

            baseX = (u16)(s32)(startVec.x + 32.0f);
            baseY = (u16)((s32)startVec.y * 64);

            if (sShadowSizes[i] == 2) {
                for (y = 0, addY = -0x180; y < ARRAY_COUNT(D_80B0EBC4); y++, addY += 0x40) {
                    for (x = -D_80B0EBC4[y]; x < D_80B0EBC4[y]; x++) {
                        index = baseX + x + baseY + addY;
                        if ((index >= 0) && (index < GOHT_SHADOW_TEX_SIZE)) {
                            tex[index] = 255;
                        }
                    }
                }
            } else if (sShadowSizes[i] == 1) {
                for (y = 0, addY = -0x100; y < ARRAY_COUNT(D_80B0EBA4); y++, addY += 0x40) {
                    for (x = -D_80B0EBA4[y]; x < D_80B0EBA4[y]; x++) {
                        index = baseX + x + baseY + addY;
                        if ((index >= 0) && (index < GOHT_SHADOW_TEX_SIZE)) {
                            tex[index] = 255;
                        }
                    }
                }
            } else if (sShadowSizes[i] == 0) {
                for (y = 0, addY = -0xC0; y < ARRAY_COUNT(D_80B0EB88); y++, addY += 0x40) {
                    for (x = -D_80B0EB88[y]; x < D_80B0EB88[y]; x++) {
                        index = baseX + x + baseY + addY;
                        if ((index >= 0) && (index < GOHT_SHADOW_TEX_SIZE)) {
                            tex[index] = 255;
                        }
                    }
                }
            } else {
                for (y = 0, addY = -0x80; y < ARRAY_COUNT(D_80B0EB70); y++, addY += 0x40) {
                    for (x = -D_80B0EB70[y]; x < D_80B0EB70[y]; x++) {
                        index = baseX + x + baseY + addY;
                        if ((index >= 0) && (index < GOHT_SHADOW_TEX_SIZE)) {
                            tex[index] = 255;
                        }
                    }
                }
            }
        }
    }
}

void BossHakugin_GenShadowTex(u8* tex, BossHakugin* this) {
    s32* iter = (s32*)tex;
    s16 i;

    for (i = 0; i < (s32)(GOHT_SHADOW_TEX_SIZE / sizeof(s32)); i++, iter++) {
        *iter = 0;
    }

    Matrix_RotateXFNew(1.0f);

    for (i = 0; i <= 5; i++) {
        BossHakugin_FillShadowTex(this, tex, i / 5.0f);
    }
}

void BossHakugin_DrawShadowTex(u8* tex, BossHakugin* this, PlayState* play) {
    s32 pad[2];
    f32 alpha;
    GraphicsContext* gfxCtx = play->state.gfxCtx;
    MtxF mtx;

    OPEN_DISPS(gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);

    alpha = (400.0f - this->actor.world.pos.y) * (1.0f / 400.0f);
    alpha = CLAMP_MIN(alpha, 0.0f);
    alpha = CLAMP_MAX(alpha, 1.0f);

    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, (s8)(alpha * 80.0f));
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);

    if (this->actor.floorPoly != NULL) {
        func_800C0094(this->actor.floorPoly, this->actor.world.pos.x, this->actor.floorHeight, this->actor.world.pos.z,
                      &mtx);
        Matrix_Put(&mtx);
    }

    Matrix_Scale(4.25f, 1.0f, 4.25f, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gShadowMaterialDL);
    gDPLoadTextureBlock(POLY_OPA_DISP++, tex, G_IM_FMT_I, G_IM_SIZ_8b, GOHT_SHADOW_TEX_WIDTH, GOHT_SHADOW_TEX_HEIGHT, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD);
    gSPDisplayList(POLY_OPA_DISP++, gShadowModelDL);

    CLOSE_DISPS(gfxCtx);
}

void func_80B0D9CC(BossHakugin* this) {
    s32 i;
    Vec3f pos;
    s32 var_s1 = 15;
    GohtRockEffect* rockEffect = this->rockEffects;
    s32 var_v1;
    s32 temp_a0;
    f32 spB4 = Math_SinS(this->actor.shape.rot.y) * 65.0f;
    f32 spB0 = Math_CosS(this->actor.shape.rot.y) * 65.0f;
    f32 spAC = Math_SinS(this->actor.shape.rot.z) * 65.0f;
    f32 temp1;
    f32 temp2;
    f32 temp3;
    f32 temp4;
    f32 temp5;
    s32 pad;

    for (i = 4; i > 0; i--, var_s1 -= 4) {
        temp4 = (30.0f / 13.0f) * spB4;
        temp5 = (30.0f / 13.0f) * spB0;

        pos.x = this->actor.world.pos.x - (i * spB4) + temp4;
        pos.y = this->actor.world.pos.y + (85.0f * (4 - i)) + 20.0f;
        pos.z = this->actor.world.pos.z - (i * spB0) + temp5;

        rockEffect->scale = ((i * 4.5f) + 22.0f) * 0.001f;
        Math_Vec3f_Copy(&rockEffect->pos, &pos);

        temp_a0 = var_s1 >> 1;
        if (temp_a0 == 0) {
            break;
        }
        rockEffect++;

        temp1 = i / (f32)temp_a0;
        temp2 = (spB0 + spB4) * temp1;
        temp3 = (spB0 - spB4) * temp1;

        for (var_v1 = 0; var_v1 < temp_a0; var_v1++, rockEffect++) {
            rockEffect->pos.x = pos.x + temp2 * (temp_a0 - var_v1);
            rockEffect->pos.y = pos.y + i * spAC;
            rockEffect->pos.z = pos.z + temp3 * (temp_a0 - var_v1);
            rockEffect->scale = ((i * 4.5f) + 22.0f) * 0.001f;
        }

        temp4 = (spB4 - spB0) * temp1;
        temp5 = (spB0 + spB4) * temp1;

        for (var_v1 = 0; var_v1 < temp_a0; var_v1++, rockEffect++) {
            rockEffect->pos.x = pos.x + temp4 * (temp_a0 - var_v1);
            rockEffect->pos.y = pos.y - i * spAC;
            rockEffect->pos.z = pos.z + temp5 * (temp_a0 - var_v1);
            rockEffect->scale = ((i * 4.5f) + 22.0f) * 0.001f;
        }
    }

    for (i = 0; i < 36; i++) {
        rockEffect = &this->rockEffects[i];

        rockEffect->scale += Rand_ZeroFloat(5.0f) * 0.001f;
        rockEffect->rot.x = (s32)Rand_Next() >> 0x10;
        rockEffect->rot.y = (s32)Rand_Next() >> 0x10;
        rockEffect->rot.z = (s32)Rand_Next() >> 0x10;
        rockEffect->velocity.x = rockEffect->pos.y;
        rockEffect->velocity.y = 0.0f;
        rockEffect->pos.y += 850.0f;
    }
}

void func_80B0DFA8(BossHakugin* this) {
    s32 i;
    GohtRockEffect* rockEffect;
    ColliderJntSphElement* element;

    for (i = 0; i < 36 / 2; i++) {
        rockEffect = &this->rockEffects[i << 1];
        element = &this->bodyCollider.elements[i];

        element->dim.worldSphere.center.x = rockEffect->pos.x;
        element->dim.worldSphere.center.y = rockEffect->pos.y;
        element->dim.worldSphere.center.z = rockEffect->pos.z;
        element->dim.worldSphere.radius = rockEffect->scale * 3000.0f;
        element->info.bumper.dmgFlags = 0xF3CFBBFF;
        element->info.bumperFlags &= ~BUMP_NO_HITMARK;

        element->info.elemType = ELEMTYPE_UNK0;
    }
    for (; i < ARRAY_COUNT(this->bodyColliderElements); i++) {
        this->bodyCollider.elements[i].info.bumperFlags &= ~BUMP_ON;
        this->bodyCollider.elements[i].info.ocElemFlags &= ~OCELEM_ON;
    }

    this->bodyCollider.base.colType = COLTYPE_HARD;
}

void BossHakugin_UpdateDead(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    BossHakugin* this = THIS;

    func_80B0DFA8(this);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->bodyCollider.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->bodyCollider.base);
}

void BossHakugin_DrawDead(Actor* thisx, PlayState* play) {
    BossHakugin* this = THIS;
    s32 i;
    GohtRockEffect* rockEffect;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    gSPDisplayList(POLY_OPA_DISP++, gGohtRockMaterialDL);

    for (i = 0; i < 36; i++) {
        rockEffect = &this->rockEffects[i];

        Matrix_SetTranslateRotateYXZ(rockEffect->pos.x, rockEffect->pos.y, rockEffect->pos.z, &rockEffect->rot);
        Matrix_Scale(rockEffect->scale, rockEffect->scale, rockEffect->scale, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gGohtRockModelDL);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
