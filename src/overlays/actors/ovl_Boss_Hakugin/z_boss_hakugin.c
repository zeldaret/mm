/*
 * File: z_boss_hakugin.c
 * Overlay: ovl_Boss_Hakugin
 * Description: Goht
 */

#include "z_boss_hakugin.h"
#include "z64quake.h"
#include "z64rumble.h"
#include "overlays/actors/ovl_En_Hakurock/z_en_hakurock.h"
#include "overlays/actors/ovl_Item_B_Heart/z_item_b_heart.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((BossHakugin*)thisx)

void BossHakugin_Init(Actor* thisx, PlayState* play2);
void BossHakugin_Destroy(Actor* thisx, PlayState* play);
void BossHakugin_Update(Actor* thisx, PlayState* play);
void BossHakugin_Draw(Actor* thisx, PlayState* play);

void func_80B08018(BossHakugin* this, PlayState* play);
void func_80B0813C(BossHakugin* this, PlayState* play);
void func_80B082AC(BossHakugin* this, PlayState* play);
void func_80B0863C(BossHakugin* this, PlayState* play);
void func_80B08960(BossHakugin* this, PlayState* play);
void func_80B08CB8(BossHakugin* this, PlayState* play);
void func_80B091D8(BossHakugin* this, PlayState* play);
void func_80B094E0(BossHakugin* this, PlayState* play);
void func_80B098BC(BossHakugin* this, PlayState* play);
void func_80B09C78(BossHakugin* this, PlayState* play);
void func_80B09E20(BossHakugin* this, PlayState* play);
void func_80B09EDC(BossHakugin* this, PlayState* play);
void func_80B0A2A4(BossHakugin* this, PlayState* play);
void func_80B0A638(BossHakugin* this, PlayState* play);
void func_80B0A8C4(BossHakugin* this, PlayState* play);
void func_80B058C0(BossHakugin* this);
void func_80B05EE0(BossHakugin* this, PlayState* play);
void func_80B08124(BossHakugin* this);
void func_80B08C1C(BossHakugin* this);
void func_80B09E84(BossHakugin* this);
void func_80B0825C(BossHakugin* this);
void func_80B09F7C(BossHakugin* this);
void func_80B08550(BossHakugin* this, PlayState* play);
void func_80B08848(BossHakugin* this, PlayState* play);

#if 0
ActorInit Boss_Hakugin_InitVars = {
    ACTOR_BOSS_HAKUGIN,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS_HAKUGIN,
    sizeof(BossHakugin),
    (ActorFunc)BossHakugin_Init,
    (ActorFunc)BossHakugin_Destroy,
    (ActorFunc)BossHakugin_Update,
    (ActorFunc)BossHakugin_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[19] = {
static ColliderJntSphElementInit D_80B0E700[19] = {
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 16, { { 1300, 200, 0 }, 30 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 15, { { 1400, 300, 0 }, 35 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 2, { { 1600, -400, 0 }, 26 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 6, { { 1700, 200, 400 }, 18 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 8, { { 1000, 0, 0 }, 10 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 9, { { 500, 0, 0 }, 9 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 11, { { 1700, 200, -400 }, 18 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 13, { { 1000, 0, 0 }, 10 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 14, { { 500, 0, 0 }, 9 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 21, { { 800, 0, 400 }, 15 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 22, { { 500, 200, 0 }, 9 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 24, { { 300, 0, 0 }, 8 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 25, { { 500, 100, 0 }, 9 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 28, { { 800, 0, -400 }, 15 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 29, { { 500, 200, 0 }, 9 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 31, { { 300, 0, 0 }, 8 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 32, { { 500, 100, 0 }, 9 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 16, { { 2400, -400, -2900 }, 12 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 16, { { 2400, -400, 2900 }, 12 }, 270 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80B0E9AC = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    ARRAY_COUNT(sJntSphElementsInit), D_80B0E700, // sJntSphElementsInit,
};

// static ColliderTrisElementInit sTrisElementsInit[1] = {
static ColliderTrisElementInit D_80B0E9BC[1] = {
    {
        { ELEMTYPE_UNK5, { 0x20000000, 0x03, 0x08 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_NONE, OCELEM_NONE, },
        { { { 22.0f, 0.0f, 100.0f }, { 0.0f, 0.0f, -100.0f }, { -22.0f, 0.0f, 100.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_80B0E9F8 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_TYPE_1, COLSHAPE_TRIS, },
    ARRAY_COUNT(sTrisElementsInit), D_80B0E9BC, // sTrisElementsInit,
};

// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_80B0EA08 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_TYPE_2, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK5, { 0x20000000, 0x00, 0x08 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_NONE, OCELEM_NONE, },
    { 1, { { 0, 0, 0 }, 23 }, 100 },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B0EA34 = {
    { COLTYPE_HARD, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x02, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
    { 170, 40, 0, { 0, 0, 0 } },
};

// static DamageTable sDamageTable = {
static DamageTable D_80B0EA60 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xC),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(1, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0xD),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xC),
};

// sColChkInfoInit
static CollisionCheckInfoInit D_80B0EA80 = { 30, 80, 100, MASS_IMMOVABLE };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B0EAD8[] = {
    ICHAIN_S8(hintId, 27, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 27, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, TARGET_MODE_5, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_STOP),
};

#endif

extern ColliderJntSphElementInit D_80B0E700[19];
extern ColliderJntSphInit D_80B0E9AC;
extern ColliderTrisElementInit D_80B0E9BC[1];
extern ColliderTrisInit D_80B0E9F8;
extern ColliderSphereInit D_80B0EA08;
extern ColliderCylinderInit D_80B0EA34;
extern DamageTable D_80B0EA60;
extern CollisionCheckInfoInit D_80B0EA80;
extern TexturePtr D_80B0EA88;
extern s8 D_80B0EA95;
extern s8 D_80B0EA9A;
extern s8 D_80B0EAA5;
extern s8 D_80B0EAAC;
extern s32 D_80B0EAD4;
extern InitChainEntry D_80B0EAD8[];
extern Vec3f D_80B0EAE8;
extern Vec3f D_80B0EAF4;
extern Vec3f D_80B0EB00;
extern Vec3f D_80B0EB0C;
extern Vec3f D_80B0EB18;

extern AnimationHeader D_06002054;    // gGohtThawAndBreakWallAnim
extern AnimationHeader D_0600319C;    // gGohtStationaryAnim
extern Gfx D_06010488[];              // gGohtRockMaterialDL
extern Gfx D_06011208[];              // gGohtLightningMaterialDL
extern Gfx D_06012ED0[];              // gGohtLightOrbMaterialDL
extern AnimationHeader D_060134D0;    // gGohtFallDownAnim
extern AnimationHeader D_06013828;    // gGohtRunAnim
extern TexturePtr D_06014040;         // gGohtTitleCardTex
extern FlexSkeletonHeader D_06013158; // gGohtSkel

#ifdef NON_MATCHING
// requires in-function static, too lazy to import all the data right now
void BossHakugin_Init(Actor* thisx, PlayState* play2) {
    static s32 D_80B0EAD4 = 0;
    PlayState* play = play2;
    BossHakugin* this = THIS;
    Actor** actorPtr;
    s32 pad;
    s32 i;

    Actor_ProcessInitChain(&this->actor, D_80B0EAD8);
    SkelAnime_InitFlex(play, &this->skelAnime, &D_06013158, &D_06013828, this->jointTable, this->morphTable, 0x21);
    if (D_80B0EAD4 == 0) {
        D_80B0EAD4 = 1;
        D_80B0EA88 = Lib_SegmentedToVirtual(D_80B0EA88);
    }

    Collider_InitAndSetJntSph(play, &this->unk_0484, &this->actor, &D_80B0E9AC, this->unk_04A4);
    for (i = 0; i < 20; i++) {
        Collider_InitAndSetTris(play, &this->unk_2618[i].unk_14, &this->actor, &D_80B0E9F8, &this->unk_2618[i].unk_34);
    }

    Collider_InitAndSetSphere(play, &this->unk_37B8, &this->actor, &D_80B0EA08);
    this->unk_37B8.dim.worldSphere.radius = 40;
    Collider_InitAndSetCylinder(play, &this->unk_0964, &this->actor, &D_80B0EA34);
    this->unk_0964.dim.pos.x = (this->actor.world.pos.x - 50.0f);
    this->unk_0964.dim.pos.y = this->actor.world.pos.y;
    this->unk_0964.dim.pos.z = this->actor.world.pos.z;
    this->unk_0964.dim.radius = 150;
    this->unk_0964.dim.height = 300;
    this->lightNode = LightContext_InsertLight(play, &play->lightCtx, &this->lightInfo);
    Lights_PointNoGlowSetInfo(&this->lightInfo, 0, 0, 0, 255, 255, 180, -1);
    this->unk_01B4 = -1;

    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_SNOWHEAD_TEMPLE)) {
        func_80B05EE0(this, play);
        Actor_Kill(&this->actor);
        return;
    }

    for (i = 0; i < 8; i++) {
        actorPtr = &this->unk_09B0[i];
        *actorPtr = Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_HAKUROCK, 0.0f, 0.0f, 0.0f, 0, 0,
                                       0, EN_HAKUROCK_TYPE_BOULDER);
    }

    for (i = 0; i < 10; i++) {
        this->unk_09D0[i] = Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_HAKUROCK, 0.0f, 0.0f, 0.0f,
                                               0, 0, 0, EN_HAKUROCK_TYPE_UNK_2);
    }

    for (i = 0; i < 180; i++) {
        this->unk_09F8[i].unk_18 = -1;
    }

    CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_80B0EA60, &D_80B0EA80);
    this->unk_01A0 = this->actor.shape.rot.y;
    this->unk_01B0 = -1;

    if (CHECK_EVENTINF(EVENTINF_53)) {
        SEQCMD_PLAY_SEQUENCE(SEQ_PLAYER_BGM_MAIN, 0, NA_BGM_BOSS | SEQ_FLAG_ASYNC);
        this->actor.world.pos.x = 0.0f;
        func_80B08C1C(this);
    } else if (CHECK_EVENTINF(EVENTINF_62)) {
        this->unk_0193 = 255;
        this->unk_01D4 = 2.7f;
        func_80B058C0(this);
        Animation_PlayOnce(&this->skelAnime, &D_06002054);
        this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
        func_80B08124(this);
    } else {
        this->unk_0193 = 255;
        this->unk_01D4 = 2.7f;
        func_80B058C0(this);
        func_80B09E84(this);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/BossHakugin_Init.s")
#endif

void BossHakugin_Destroy(Actor* thisx, PlayState* play) {
    BossHakugin* this = THIS;
    s32 pad;
    s32 i;

    LightContext_RemoveLight(play, &play->lightCtx, this->lightNode);
    Collider_DestroyJntSph(play, &this->unk_0484);
    Collider_DestroyCylinder(play, &this->unk_0964);

    for (i = 0; i < 20; i++) {
        Collider_DestroyTris(play, &this->unk_2618[i].unk_14);
    }

    Collider_DestroySphere(play, &this->unk_37B8);
    AudioSfx_StopByPos(&this->unk_0458);
    AudioSfx_StopByPos(&this->unk_0464);
}

s32 func_80B0573C(Vec3f* arg0) {
    f32 magnitude;

    magnitude = Math3D_Vec3fMagnitude(arg0);
    if (magnitude < 0.0001f) {
        return false;
    }

    Math_Vec3f_Scale(arg0, 1.0f / magnitude);
    return true;
}

void func_80B057A4(Vec3f* arg0, Vec3f* arg1, f32 arg2) {
    Vec3f sp34;
    Vec3f sp28;
    f32 temp_fa0;
    f32 var_fv1;

    temp_fa0 = (arg0->x * arg1->x) + (arg0->y * arg1->y) + (arg0->z * arg1->z);
    if (fabsf(temp_fa0) < 1.0f) {
        var_fv1 = Math_FAcosF(temp_fa0);
    } else if (temp_fa0 >= 1.0f) {
        var_fv1 = 0.0f;
    } else {
        var_fv1 = M_PI;
    }

    if (var_fv1 < arg2) {
        arg2 = var_fv1;
    }

    if (!(arg2 < (M_PI / 180.0f))) {
        Math3D_CrossProduct(arg0, arg1, &sp34);
        if (func_80B0573C(&sp34)) {
            Matrix_RotateAxisF(arg2, &sp34, MTXMODE_NEW);
            Matrix_MultVec3f(arg0, &sp28);
            Math_Vec3f_Copy(arg0, &sp28);
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B058C0.s")

void func_80B05A64(BossHakugin* this, PlayState* play, s16 speed, s32 y, s16 duration) {
    s16 quakeIndex;

    if (y > 0) {
        quakeIndex = Quake_Request(play->cameraPtrs[play->activeCamId], QUAKE_TYPE_3);
        Quake_SetSpeed(quakeIndex, speed);
        Quake_SetPerturbations(quakeIndex, y, 0, 0, 0);
        Quake_SetDuration(quakeIndex, duration);
        Rumble_Request(this->actor.xyzDistToPlayerSq, 180, 20, 100);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B05B04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B05CBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B05D4C.s")

void func_80B05EE0(BossHakugin* this, PlayState* play) {
    s16 atan;
    Vec3f warpPos;
    Vec3f heartPos;
    f32 sp50;
    f32 sin;
    f32 cos;

    atan = Math_Atan2S_XY(this->actor.world.pos.z, this->actor.world.pos.x);
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

    sp50 = this->unk_01B4 * 300.0f;
    sin = Math_SinS(this->unk_019E);
    cos = Math_CosS(this->unk_019E);
    heartPos.x = ((100.0f * sin) + warpPos.x) + (sp50 * cos);
    heartPos.z = ((100.0f * cos) + warpPos.z) - (sp50 * sin);
    Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_DOOR_WARP1, warpPos.x, warpPos.y, warpPos.z, 0, 0, 0,
                       1);
    Actor_Spawn(&play->actorCtx, play, ACTOR_ITEM_B_HEART, heartPos.x, warpPos.y, heartPos.z, 0, 0, 0,
                BHEART_PARAM_NORMAL);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0607C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B06558.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B06600.s")

void func_80B0696C(BossHakugin* this, Vec3f* arg1);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0696C.s")

void func_80B06B20(BossHakugin* this, Vec3f* arg1);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B06B20.s")

void func_80B06C08(BossHakugin* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B06C08.s")

void func_80B06D38(BossHakugin* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B06D38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B06F48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0728C.s")

void func_80B07450(BossHakugin* this, PlayState* play) {
    Vec3f velocity;
    Vec3f pos;
    f32 temp;
    s32 i;

    if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_ICEB_FOOTSTEP_OLD);
        Math_Vec3f_Copy(&pos, &this->bodyPartsPos[D_80B0EA9A]);
        if (this->actor.xzDistToPlayer < 1500.0f) {
            temp = (1500.0f - this->actor.xzDistToPlayer) * 0.00066666666f;
            func_80B05A64(this, play, 17000, 6.5f * temp, 10);
        }

        func_80B06C08(this);
    } else if (Animation_OnFrame(&this->skelAnime, 2.0f)) {
        Math_Vec3f_Copy(&pos, &this->bodyPartsPos[D_80B0EAAC]);
        func_80B06B20(this, &pos);
    } else if (Animation_OnFrame(&this->skelAnime, 3.0f)) {
        Math_Vec3f_Copy(&pos, &this->bodyPartsPos[D_80B0EA95]);
        func_80B06D38(this, play);
    } else if (Animation_OnFrame(&this->skelAnime, 11.0f)) {
        Math_Vec3f_Copy(&pos, &this->bodyPartsPos[D_80B0EAA5]);
        func_80B06B20(this, &pos);
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

void func_80B07700(BossHakugin* this, PlayState* play, s32 arg2);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B07700.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0791C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B07B88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B07BFC.s")

void func_80B07DA4(BossHakugin* this, PlayState* play, f32 arg2, s16 arg3) {
    Camera* camera = Play_GetCamera(play, this->unk_01AC);
    Vec3f sp38;
    Vec3f sp2C;

    Math_Vec3f_Diff(&camera->at, &camera->eye, &sp38);
    Math_Vec3f_StepTo(&camera->eye, &this->unk_038C, arg2);

    if (func_80B0573C(&sp38)) {
        sp2C.x = Math_CosS(this->unk_037A.x) * Math_SinS(this->unk_037A.y);
        sp2C.y = Math_SinS(this->unk_037A.x);
        sp2C.z = Math_CosS(this->unk_037A.x) * Math_CosS(this->unk_037A.y);
        func_80B057A4(&sp38, &sp2C, BINANG_TO_RAD(arg3));
    }

    camera->at.x = camera->eye.x + (50.0f * sp38.x);
    camera->at.y = camera->eye.y + (50.0f * sp38.y);
    camera->at.z = camera->eye.z + (50.0f * sp38.z);
    Play_SetCameraAtEye(play, this->unk_01AC, &camera->at, &camera->eye);
}

void func_80B07EEC(BossHakugin* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Vec3f sp20;

    Animation_PlayOnce(&this->skelAnime, &D_06002054);
    this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
    this->unk_01AC = CutsceneManager_GetCurrentSubCamId(this->actor.csId);
    sp20.x = player->actor.focus.pos.x;
    sp20.y = player->actor.focus.pos.y;
    sp20.z = player->actor.focus.pos.z;
    this->unk_038C.x = (Math_SinS(player->actor.shape.rot.y) * 70.0f) + player->actor.focus.pos.x;
    this->unk_038C.y = player->actor.focus.pos.y + 20.0f;
    this->unk_038C.z = (Math_CosS(player->actor.shape.rot.y) * 70.0f) + player->actor.focus.pos.z;
    Play_SetCameraAtEye(play, this->unk_01AC, &sp20, &this->unk_038C);
    this->unk_037A.x = Math_Atan2S_XY(70.0f, -20.0f);
    this->unk_037A.y = player->actor.shape.rot.y + 0x8000;
    func_800B7298(play, &this->actor, PLAYER_CSMODE_21);
    this->unk_019C = 0;
    this->actionFunc = func_80B08018;
}

void func_80B08018(BossHakugin* this, PlayState* play) {
    this->unk_019C++;
    if (this->unk_019C == 30) {
        this->unk_038C.x = 417.0f;
        this->unk_038C.y = 40.0f;
        this->unk_038C.z = -1417.0f;
        Play_SetCameraAtEye(play, this->unk_01AC, &D_80B0EAE8, &this->unk_038C);
        func_800BE33C(&this->unk_038C, &D_80B0EAE8, &this->unk_037A, true);
    } else if (this->unk_019C == 50) {
        this->unk_037A.x = 0x1500;
    } else if (this->unk_019C == 120) {
        CutsceneManager_Stop(this->actor.csId);
        SET_EVENTINF(EVENTINF_62);
        func_80B08124(this);
        return;
    }

    if (this->unk_019C >= 31) {
        func_80B07DA4(this, play, 5.0f, 0xC0);
    }
}

void func_80B08124(BossHakugin* this) {
    this->unk_019C = 0;
    this->actionFunc = func_80B0813C;
}

void func_80B0813C(BossHakugin* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (!(player->stateFlags2 & PLAYER_STATE2_4000)) {
        DECR(this->unk_019C);
    }

    if ((this->unk_0964.base.acFlags & AC_HIT) && (this->unk_0964.info.acHitInfo->toucher.dmgFlags == 0x800)) {
        this->unk_0964.base.atFlags &= ~AT_HIT;
        this->unk_0964.base.acFlags &= ~AC_HIT;
        this->unk_0964.base.ocFlags1 &= ~OC1_HIT;
        func_80B09E84(this);
        return;
    }

    if (this->unk_0964.base.atFlags & AT_HIT) {
        this->unk_019C = 40;
        this->unk_0964.base.atFlags &= ~AT_HIT;
    }

    if (this->unk_019C == 0) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk_0964.base);
    }

    CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk_0964.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk_0964.base);
    this->unk_01A4 = 20;
}

void func_80B0825C(BossHakugin* this) {
    this->unk_019C = 100;
    this->unk_01AC = CutsceneManager_GetCurrentSubCamId(this->actor.csId);
    Play_EnableMotionBlur(140);
    this->actionFunc = func_80B082AC;
}

void func_80B082AC(BossHakugin* this, PlayState* play) {
    Vec3f eye;
    Vec3f at;
    s32 temp_v1;

    this->unk_019C--;
    if ((this->unk_019C >= 30) && (this->unk_019C % 2 != 0)) {
        func_80B07700(this, play, 1);
    } else if ((this->unk_019C % 4 == 0)) {
        func_80B07700(this, play, 0);
    }

    if (this->unk_019C == 99) {
        at.x = 479.0f;
        at.y = 181.0f;
        at.z = -1637.0f;
        eye.x = 328.0f;
        eye.y = 164.0f;
        eye.z = -1693.0f;
        Play_SetCameraAtEye(play, this->unk_01AC, &at, &eye);
    } else if (this->unk_019C == 75) {
        at.x = 693.0f;
        at.y = 162.0f;
        at.z = -1550.0f;
        eye.x = 638.0f;
        eye.y = 200.0f;
        eye.z = -1407.0f;
        Play_SetCameraAtEye(play, this->unk_01AC, &at, &eye);
    } else if (this->unk_019C == 50) {
        at.x = 825.0f;
        at.y = 123.0f;
        at.z = -1637.0f;
        eye.x = 734.0f;
        eye.y = 145.0f;
        eye.z = -1762.0f;
        Play_SetCameraAtEye(play, this->unk_01AC, &at, &eye);
    } else if (this->unk_019C == 25) {
        at.x = 711.0f;
        at.y = 76.0f;
        at.z = -1602.0f;
        eye.x = 634.0f;
        eye.y = 54.0f;
        eye.z = -1735.0f;
        Play_SetCameraAtEye(play, this->unk_01AC, &at, &eye);
    }

    this->unk_01D4 -= 0.027f;
    temp_v1 = (s32)(this->unk_019C * 5.1f) + 50;
    this->unk_0193 = CLAMP_MAX(temp_v1, 255);

    Actor_PlaySfx_Flagged(&this->actor, NA_SE_EV_ICE_MELT_LEVEL - SFX_FLAG);
    if (this->unk_019C == 0) {
        this->unk_0193 = 0;
        func_80B08550(this, play);
    }
}

void func_80B08550(BossHakugin* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    Actor_PlaySfx(&this->actor, NA_SE_EN_ICEB_STEAM_DEMO_UP_OLD);
    Play_SetCameraAtEye(play, this->unk_01AC, &D_80B0EAF4, &D_80B0EB00);
    this->unk_037A.x = -0x1F00;
    this->unk_037A.y = -0x4000;
    this->unk_019C = 70;
    this->unk_038C.x = 680.0f;
    this->unk_038C.y = 370.0f;
    this->unk_038C.z = -1600.0f;
    player->actor.world.pos.x = 250.0f;
    player->actor.world.pos.z = -1560.0f;
    player->actor.shape.rot.y = this->actor.yawTowardsPlayer + 0x8000;
    player->currentYaw = player->actor.world.rot.y = player->actor.shape.rot.y;
    func_800B7298(play, &this->actor, PLAYER_CSMODE_131);
    this->actionFunc = func_80B0863C;
}

void func_80B0863C(BossHakugin* this, PlayState* play) {
    s32 i;

    this->unk_019C--;
    if (this->unk_019C > 0) {
        func_80B07DA4(this, play, 7.0f, 0xC0);
    } else if (this->unk_019C == 0) {
        Play_SetCameraAtEye(play, this->unk_01AC, &D_80B0EB0C, &D_80B0EB18);
        this->unk_037A.y = 0x4000;
        this->unk_037A.x = Math_Atan2S_XY(95.0f, 32.0f);
        this->unk_038C.x = 232.0f;
        this->unk_038C.y = 43.0f;
        this->unk_038C.z = -1600.0f;
        Actor_PlaySfx(&this->actor, NA_SE_EN_ICEB_STEAMS_DEMO_OLD);
    } else {
        func_80B07DA4(this, play, 1.0f, 0xC0);

        if (Animation_OnFrame(&this->skelAnime, 20.0f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_ICEB_STEAM_DEMO_UP_OLD);
        }

        if (Animation_OnFrame(&this->skelAnime, 45.0f)) {
            SEQCMD_PLAY_SEQUENCE(SEQ_PLAYER_BGM_MAIN, 0, NA_BGM_BOSS | SEQ_FLAG_ASYNC);
        }

        if (Animation_OnFrame(&this->skelAnime, 65.0f)) {
            TitleCard_InitBossName(&play->state, &play->actorCtx.titleCtxt, Lib_SegmentedToVirtual(&D_06014040), 160,
                                   180, 128, 40);
        }

        if (Animation_OnFrame(&this->skelAnime, 86.0f)) {
            Audio_PlaySfx_AtPos(&this->unk_0458, NA_SE_EN_ICEB_CRY_OLD);
        }

        if (Animation_OnFrame(&this->skelAnime, 90.0f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_LAST1_DEMO_BREAK);
            for (i = 6; i < 10; i++) {
                this->unk_09D0[i]->params = 0;
            }
        }

        if (SkelAnime_Update(&this->skelAnime)) {
            func_80B08848(this, play);
            return;
        }
    }

    if (((this->unk_019C + 12) >= 0) && (this->unk_019C % 4 == 0)) {
        func_80B07700(this, play, 0);
    }
}

void func_80B08848(BossHakugin* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Vec3f sp30;

    this->unk_038C.x = player->actor.world.pos.x - 150.0f;
    this->unk_038C.y = player->actor.world.pos.y + 30.0f;
    this->unk_038C.z = player->actor.world.pos.z - 30.0f;
    sp30.x = this->actor.world.pos.x - 100.0f;
    sp30.y = this->actor.world.pos.y + 100.0f;
    sp30.z = this->actor.world.pos.z;
    func_800BE33C(&this->unk_038C, &sp30, &this->unk_037A, true);
    Animation_Change(&this->skelAnime, &D_06013828, 1.5f, 0.0f, 0.0f, ANIMMODE_LOOP, -3.0f);
    this->unk_019C = 0;
    this->actor.speed = 5.0f;
    func_800B7298(play, &this->actor, PLAYER_CSMODE_END);
    player->stateFlags1 |= PLAYER_STATE1_20;
    play->actorCtx.unk268 = 1;
    this->actionFunc = func_80B08960;
}

void func_80B08960(BossHakugin* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Camera* camera = Play_GetCamera(play, this->unk_01AC);
    Vec3f at;
    f32 var_fv0;
    s32 i;

    Math_ScaledStepToS(&this->unk_01A6, 0x800, 0x80);
    Math_StepToF(&this->actor.speed, 25.0f, 0.5f);
    this->skelAnime.playSpeed = (this->actor.speed * 0.03125f) + 0.5f;
    func_80B07450(this, play);
    this->unk_018D = 10;
    SkelAnime_Update(&this->skelAnime);
    this->unk_019C++;
    if (this->unk_019C < 8) {
        func_80B07DA4(this, play, 25.0f, 0x120);
    } else if (this->unk_019C == 22) {
        this->unk_038C.x = camera->eye.x;
        this->unk_038C.y = camera->eye.y;
        this->unk_038C.z = camera->eye.z + 450.0f;
    } else if (this->unk_019C == 62) {
        this->actor.flags |= ACTOR_FLAG_TARGETABLE;
        CutsceneManager_Stop(this->actor.csId);
        player->stateFlags1 &= ~PLAYER_STATE1_20;
        SET_EVENTINF(EVENTINF_53);
        Play_DisableMotionBlur();
        func_80B08C1C(this);
        return;
    } else if (this->unk_019C > 22) {
        at.x = this->actor.world.pos.x;
        at.y = this->actor.world.pos.y + 150.0f;
        at.z = this->actor.world.pos.z;
        Math_Vec3f_StepTo(&camera->eye, &this->unk_038C, 35.0f);
        Play_SetCameraAtEye(play, this->unk_01AC, &at, &camera->eye);

        if (this->unk_019C == 42) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_LAST1_DEMO_WALL);
            for (i = 0; i < 6; i++) {
                this->unk_09D0[i]->params = 0;
            }
        }
    }

    if (this->unk_0484.base.atFlags & AT_HIT) {
        func_800B8D50(play, &this->actor, 10.0f, 0, 6.0f, 0);
    } else {
        play->actorCtx.unk268 = 1;
    }

    if (this->unk_019C >= 5) {
        var_fv0 = (this->unk_019C - 4) * 5.0f;
        var_fv0 = CLAMP_MAX(var_fv0, 60.0f);
        func_800B6F20(play, &play->actorCtx.unk_26C, var_fv0, -0x4000);
    }
}

void func_80B08C1C(BossHakugin* this) {
    Animation_Change(&this->skelAnime, &D_06013828, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP_INTERP, -5.0f);
    this->unk_01A2 = 0;
    this->unk_01C8 = 0.0f;
    this->unk_019E = Rand_CenteredFloat(3072.0f);
    this->unk_019C = 40;
    this->unk_01C4 = 16.0f;
    this->actionFunc = func_80B08CB8;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B08CB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B091D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B093C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B094E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09840.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B098BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09A94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09C78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09DFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09E20.s")

void func_80B09E84(BossHakugin* this) {
    CutsceneManager_Queue(this->actor.csId);
    if (this->actionFunc == func_80B0813C) {
        this->unk_019C = 1;
    } else {
        this->unk_019C = 0;
    }

    this->actionFunc = func_80B09EDC;
}

void func_80B09EDC(BossHakugin* this, PlayState* play) {
    if (CutsceneManager_IsNext(this->actor.csId)) {
        CutsceneManager_StartWithPlayerCs(this->actor.csId, &this->actor);
        if (this->actor.colChkInfo.health == 0) {
            func_80B09F7C(this);
        } else if (this->unk_019C == 1) {
            func_80B0825C(this);
        } else {
            func_80B07EEC(this, play);
        }
    } else {
        CutsceneManager_Queue(this->actor.csId);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B09F7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0A2A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0A5EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0A638.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0A87C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0A8C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0AC30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0ADFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0B238.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0B34C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0B3F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0B548.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0B660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/BossHakugin_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0C000.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0C1BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0C398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0C570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0C7B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0CAF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0CCD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0CF24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/BossHakugin_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0D2B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0D69C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0D750.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0D9CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0DFA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0E548.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0E5A4.s")
