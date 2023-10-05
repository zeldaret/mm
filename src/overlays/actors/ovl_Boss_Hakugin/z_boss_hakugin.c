/*
 * File: z_boss_hakugin.c
 * Overlay: ovl_Boss_Hakugin
 * Description: Goht
 */

#include "z_boss_hakugin.h"
#include "z64quake.h"
#include "z64rumble.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"
#include "overlays/actors/ovl_En_Clear_Tag/z_en_clear_tag.h"
#include "overlays/actors/ovl_En_Hakurock/z_en_hakurock.h"
#include "overlays/actors/ovl_Item_B_Heart/z_item_b_heart.h"
#include "overlays/effects/ovl_Effect_Ss_Fhg_Flash/z_eff_ss_fhg_flash.h"

#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((BossHakugin*)thisx)

void BossHakugin_Init(Actor* thisx, PlayState* play2);
void BossHakugin_Destroy(Actor* thisx, PlayState* play);
void BossHakugin_Update(Actor* thisx, PlayState* play);
void BossHakugin_Draw(Actor* thisx, PlayState* play);
void func_80B0E5A4(Actor* thisx, PlayState* play);

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
void func_80B09DFC(BossHakugin* this);
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
void func_80B0A5EC(BossHakugin* this);
void func_80B0A87C(BossHakugin* this);
void func_80B09178(BossHakugin* this);
void func_80B09A94(BossHakugin* this, PlayState* play);

void BossHakugin_GenShadowTex(u8* tex, BossHakugin* this);
void BossHakugin_DrawShadowTex(u8* tex, BossHakugin* this, PlayState* play);
void func_80B0D9CC(BossHakugin* this);
void func_80B0DFA8(BossHakugin* this);
void func_80B0E548(Actor* thisx, PlayState* play2);

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

static ColliderJntSphElementInit sJntSphElementsInit[19] = {
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NONE,
            BUMP_ON | BUMP_NO_HITMARK,
            OCELEM_ON,
        },
        { 16, { { 1300, 200, 0 }, 30 }, 270 },
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
        { 15, { { 1400, 300, 0 }, 35 }, 270 },
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
        { 2, { { 1600, -400, 0 }, 26 }, 270 },
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
        { 6, { { 1700, 200, 400 }, 18 }, 270 },
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
        { 8, { { 1000, 0, 0 }, 10 }, 270 },
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
        { 9, { { 500, 0, 0 }, 9 }, 270 },
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
        { 11, { { 1700, 200, -400 }, 18 }, 270 },
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
        { 13, { { 1000, 0, 0 }, 10 }, 270 },
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
        { 14, { { 500, 0, 0 }, 9 }, 270 },
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
        { 21, { { 800, 0, 400 }, 15 }, 270 },
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
        { 22, { { 500, 200, 0 }, 9 }, 270 },
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
        { 24, { { 300, 0, 0 }, 8 }, 270 },
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
        { 25, { { 500, 100, 0 }, 9 }, 270 },
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
        { 28, { { 800, 0, -400 }, 15 }, 270 },
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
        { 29, { { 500, 200, 0 }, 9 }, 270 },
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
        { 31, { { 300, 0, 0 }, 8 }, 270 },
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
        { 32, { { 500, 100, 0 }, 9 }, 270 },
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
        { 16, { { 2400, -400, -2900 }, 12 }, 270 },
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
        { 16, { { 2400, -400, 2900 }, 12 }, 270 },
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

static CollisionCheckInfoInit D_80B0EA80 = { 30, 80, 100, MASS_IMMOVABLE };

TexturePtr D_80B0EA88 = gGohtMetalPlateWithCirclePatternTex;

s8 D_80B0EA8C[0x20] = {
    -1, -1, 0,  -1, -1, -1, 3,   -1, 4,  5,   -1, 6,  -1,  7,   8,  1,
    2,  -1, -1, -1, -1, 9,  0xA, -1, -1, 0xB, -1, -1, 0xC, 0xD, -1, -1,
};
s8 D_80B0EAAC = 0xE;
s32 D_80B0EAB0[5] = { 0x1C, 0x18, 0x11, 0xD, 6 };
Color_RGBA8 D_80B0EAC4 = { 0xFA, 0xFA, 0xFA, 0xFF };
Color_RGBA8 D_80B0EAC8 = { 0xB4, 0xB4, 0xB4, 0xFF };
Color_RGB8 D_80B0EACC = { 0, 0x96, 0xFF };
Color_RGB8 D_80B0EAD0 = { 0, 0xFF, 0xFF };

void BossHakugin_Init(Actor* thisx, PlayState* play2) {
    static s32 D_80B0EAD4 = 0;
    static InitChainEntry D_80B0EAD8[] = {
        ICHAIN_S8(hintId, 27, ICHAIN_CONTINUE),
        ICHAIN_VEC3F_DIV1000(scale, 27, ICHAIN_CONTINUE),
        ICHAIN_U8(targetMode, TARGET_MODE_5, ICHAIN_CONTINUE),
        ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_STOP),
    };
    PlayState* play = play2;
    BossHakugin* this = THIS;
    Actor** actorPtr;
    s32 pad;
    s32 i;

    Actor_ProcessInitChain(&this->actor, D_80B0EAD8);
    SkelAnime_InitFlex(play, &this->skelAnime, &gGohtSkel, &gGohtRunAnim, this->jointTable, this->morphTable,
                       GOHT_LIMB_MAX);
    if (D_80B0EAD4 == 0) {
        D_80B0EAD4 = 1;
        D_80B0EA88 = Lib_SegmentedToVirtual(D_80B0EA88);
    }

    Collider_InitAndSetJntSph(play, &this->unk_0484, &this->actor, &sJntSphInit, this->unk_04A4);
    for (i = 0; i < ARRAY_COUNT(this->unk_2618); i++) {
        Collider_InitAndSetTris(play, &this->unk_2618[i].unk_14, &this->actor, &sTrisInit, &this->unk_2618[i].unk_34);
    }

    Collider_InitAndSetSphere(play, &this->unk_37B8, &this->actor, &sSphereInit);
    this->unk_37B8.dim.worldSphere.radius = 40;
    Collider_InitAndSetCylinder(play, &this->unk_0964, &this->actor, &sCylinderInit);
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

    for (i = 0; i < ARRAY_COUNT(this->unk_09B0); i++) {
        actorPtr = &this->unk_09B0[i];
        *actorPtr = Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_HAKUROCK, 0.0f, 0.0f, 0.0f, 0, 0,
                                       0, EN_HAKUROCK_TYPE_BOULDER);
    }

    for (i = 0; i < ARRAY_COUNT(this->unk_09D0); i++) {
        this->unk_09D0[i] = Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_HAKUROCK, 0.0f, 0.0f, 0.0f,
                                               0, 0, 0, EN_HAKUROCK_TYPE_UNK_2);
    }

    for (i = 0; i < ARRAY_COUNT(this->unk_09F8); i++) {
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
        Animation_PlayOnce(&this->skelAnime, &gGohtThawAndBreakWallAnim);
        this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
        func_80B08124(this);
    } else {
        this->unk_0193 = 255;
        this->unk_01D4 = 2.7f;
        func_80B058C0(this);
        func_80B09E84(this);
    }
}

Vec3f D_80B0EAE8 = { 492.0f, 28.0f, -1478.0f };
Vec3f D_80B0EAF4 = { 894.0f, 176.0f, -1600.0f };
Vec3f D_80B0EB00 = { 972.0f, 176.0f, -1600.0f };
Vec3f D_80B0EB0C = { 377.0f, 140.0f, -1600.0f };
Vec3f D_80B0EB18 = { 282.0f, 108.0f, -1600.0f };
s32 D_80B0EB24[5] = { 0, 0xF, 0x1A, 0x21, 0x24 };

typedef struct {
    s32 unk_00;
    u32 unk_04;
} BossHakuginUnkStruct_80B0A8C4;

BossHakuginUnkStruct_80B0A8C4 D_80B0EB38[6] = {
    { 0, 0x28000 }, { 4, 0x1A0 }, { 7, 0x3400 }, { 0xE, 0xD0000000 }, { 0xA, 0x01A00000 }, { 1, 0x08104002 },
};

void BossHakugin_Destroy(Actor* thisx, PlayState* play) {
    BossHakugin* this = THIS;
    s32 pad;
    s32 i;

    LightContext_RemoveLight(play, &play->lightCtx, this->lightNode);
    Collider_DestroyJntSph(play, &this->unk_0484);
    Collider_DestroyCylinder(play, &this->unk_0964);

    for (i = 0; i < ARRAY_COUNT(this->unk_2618); i++) {
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

void func_80B058C0(BossHakugin* this) {
    s32 i = 0;
    Actor* last;
    Actor* now = this->unk_09D0[i++];

    now->params = 4;
    now->world.pos.x = -500.0f;
    now->world.pos.y = this->actor.world.pos.y;
    now->world.pos.z = -1266.6666667f;
    now->shape.rot.y = this->actor.shape.rot.y + 0x4000;

    while (i < 6) {
        last = now;
        now = this->unk_09D0[i++];

        now->params = 4;
        now->world.pos.x = last->world.pos.x;
        now->world.pos.y = this->actor.world.pos.y;
        now->world.pos.z = last->world.pos.z - 133.333333f;
        now->shape.rot.y = last->shape.rot.y;
    }

    while (i < 10) {
        last = (i < 8) ? this->unk_09D0[i - 6] : this->unk_09D0[i - 4];
        now = this->unk_09D0[i++];

        now->params = 4;
        now->world.pos.x = this->actor.world.pos.x;
        now->world.pos.y = this->actor.world.pos.y;
        now->world.pos.z = last->world.pos.z;
        now->shape.rot.y = this->actor.shape.rot.y - 0x4000;
    }
}

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

void func_80B05B04(BossHakugin* this, PlayState* play) {
    Vec3f sp34;
    s32 var_v0;
    f32 sp2C;

    if (((this->actionFunc == func_80B0813C) || (this->actionFunc == func_80B08018)) && (Rand_ZeroOne() < 0.1f)) {
        sp2C = Rand_ZeroOne();
        var_v0 = (Rand_ZeroOne() < 0.5f) ? -1 : 1;
        sp34.x = (var_v0 * (15.0f + (sp2C * 15.0f)) * 4.0f) + this->actor.world.pos.x;

        sp34.y = (((Rand_ZeroOne() * 90.0f) + 10.0f) * 2.7f) + this->actor.world.pos.y;

        sp2C = Rand_ZeroOne();
        var_v0 = (Rand_ZeroOne() < 0.5f) ? -1 : 1;
        sp34.z = (var_v0 * (15.0f + (sp2C * 15.0f)) * 4.0f) + this->actor.world.pos.z;

        EffectSsKirakira_SpawnDispersed(play, &sp34, &gZeroVec3f, &gZeroVec3f, &D_80B0EAC4, &D_80B0EAC8, (s16)0x7D0, 5);
    }
}

void func_80B05CBC(BossHakugin* this, Player* player) {
    if (!this->unk_0194 && (player->stateFlags3 & 0x80000) && !(player->actor.bgCheckFlags & 1) &&
        (player->actor.velocity.y > 5.0f)) {
        player->actor.velocity.y *= 1.3f;
        player->linearVelocity *= 1.3f;
        this->unk_0194 = true;
    } else if (player->actor.bgCheckFlags & 1) {
        this->unk_0194 = false;
    }
}

void func_80B05D4C(BossHakugin* this) {
    Vec3f* var_t0 = &this->actor.world.pos;
    s32 i;
    s16 var_t1 = 0;

    for (i = 0; i < 20; i++) {
        if (this->unk_2618[i].unk_0C == 0xFF) {
            var_t0 = &this->unk_2618[i].unk_00;
            var_t1 = 0x1388;
            break;
        }
    }
    if (i == 20) {
        if (this->unk_01C8 > 0.0f) {
            var_t0 = &this->unk_0380;
            var_t1 = (this->unk_01C8 / 30.0f) * 5000.0f;
        } else if ((this->unk_0192 == 3) || (this->unk_0192 == 2)) {
            var_t0 = &this->unk_3734[0];
            var_t1 = 0x1388;
        } else if (this->unk_0192 == 4) {
            var_t0 = &this->unk_3734[this->unk_01AA];
            var_t1 = (10 - this->unk_01AA) * 500.0f;
        }
    }
    Lights_PointNoGlowSetInfo(&this->lightInfo, var_t0->x, var_t0->y, var_t0->z, D_80B0EACC.r, D_80B0EACC.g,
                              D_80B0EACC.b, var_t1);
}

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

void func_80B0607C(BossHakugin* this, PlayState* play) {
    CollisionPoly* sp8C = NULL;
    CollisionPoly* sp88 = NULL;
    s32 sp84;
    s16 sp82;
    s16 sp80;
    s16 var_v0;
    Vec3f sp70;
    Vec3f sp64;
    Vec3f sp58;
    Vec3f sp4C;
    f32 sp48;

    sp58.x = this->actor.world.pos.x + (Math_SinS(this->unk_01A0) * (5.0f * this->actor.speed));
    sp58.y = this->actor.world.pos.y + 450.0f;
    sp58.z = this->actor.world.pos.z + (Math_CosS(this->unk_01A0) * (5.0f * this->actor.speed));

    sp4C.x = sp58.x - Math_CosS(this->unk_01A0) * 1000.0f;
    sp4C.y = sp58.y;
    sp4C.z = sp58.z + (Math_SinS(this->unk_01A0) * 1000.0f);

    if (BgCheck_EntityLineTest1(&play->colCtx, &sp58, &sp4C, &sp70, &sp8C, 1, 1, 0, 1, &sp84)) {
        sp82 =
            Math_Atan2S_XY(sp8C->normal.z * COLPOLY_NORMAL_FRAC, sp8C->normal.x * COLPOLY_NORMAL_FRAC) - this->unk_01A0;
        this->unk_01BC = Math_Vec3f_DistXZ(&sp58, &sp70);
    } else {
        sp82 = 0;
        this->unk_01BC = 30000.0f;
    }
    sp4C.x = (2.0f * sp58.x) - sp4C.x;
    sp4C.z = (2.0f * sp58.z) - sp4C.z;
    if (BgCheck_EntityLineTest1(&play->colCtx, &sp58, &sp4C, &sp64, &sp88, 1, 1, 0, 1, &sp84)) {
        sp80 =
            Math_Atan2S_XY(sp88->normal.z * COLPOLY_NORMAL_FRAC, sp88->normal.x * COLPOLY_NORMAL_FRAC) - this->unk_01A0;
        this->unk_01C0 = Math_Vec3f_DistXZ(&sp58, &sp64);
    } else {
        sp80 = 0;
        this->unk_01C0 = 30000.0f;
    }
    if (this->unk_01B4 == 1) {
        this->unk_01C0 -= 50.0f;
    } else {
        this->unk_01BC -= 50.0f;
    }
    if (this->unk_01BC <= 89.100006f) {
        sp48 = (this->unk_01B4 == 1) ? 89.100006f : 139.1f;
        this->actor.world.pos.x =
            (sp70.x + (sp48 * Math_CosS(this->unk_01A0))) - (Math_SinS(this->unk_01A0) * (5.0f * this->actor.speed));
        this->actor.world.pos.z =
            (sp70.z - (sp48 * Math_SinS(this->unk_01A0))) - (Math_CosS(this->unk_01A0) * (5.0f * this->actor.speed));
    } else if (this->unk_01C0 <= 89.100006f) {
        sp48 = (this->unk_01B4 == 1) ? 139.1f : 89.100006f;
        this->actor.world.pos.x =
            (sp64.x - (sp48 * Math_CosS(this->unk_01A0))) - (Math_SinS(this->unk_01A0) * (5.0f * this->actor.speed));
        this->actor.world.pos.z =
            (sp64.z + (sp48 * Math_SinS(this->unk_01A0))) - (Math_CosS(this->unk_01A0) * (5.0f * this->actor.speed));
    }
    if ((this->unk_01C0 < 30000.0f) && (this->unk_01BC < 30000.0f)) {
        var_v0 = (s16)(sp82 + sp80) >> 1;
        if (((this->unk_01B4 == 1) && (var_v0 < 0)) || ((this->unk_01B4 == -1) && (var_v0 > 0))) {
            this->unk_01A0 += var_v0;
        }
    }
}

void func_80B06558(BossHakuginUnkStruct_2618* arg0) {
    s32 i;
    Vec3f sp38[3];

    Matrix_SetTranslateRotateYXZ(arg0->unk_00.x, arg0->unk_00.y, arg0->unk_00.z, &arg0->unk_0E);
    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
    for (i = 0; i < 3; i++) {
        Matrix_MultVec3f(&sTrisElementsInit[0].dim.vtx[i], &sp38[i]);
    }
    Collider_SetTrisVertices(&arg0->unk_14, 0, &sp38[0], &sp38[1], &sp38[2]);
}

void func_80B06600(BossHakugin* this, Vec3f* arg1, PlayState* play) {
    s32 i;
    Player* player = GET_PLAYER(play);
    CollisionPoly* spD4;
    Vec3f spC8;
    Vec3f spBC;
    Vec3f spB0;
    Vec3f spA4;
    Vec3f sp98;
    Vec3f sp8C;
    BossHakuginUnkStruct_2618* effect;
    s32 sp84;

    Math_Vec3f_Copy(&spC8, arg1);
    spBC.x = player->actor.world.pos.x - (Math_SinS(this->actor.shape.rot.y) * 50.0f);
    spBC.y = player->actor.world.pos.y + 40.0f;
    spBC.z = player->actor.world.pos.z - (Math_CosS(this->actor.shape.rot.y) * 50.0f);
    Actor_OffsetOfPointInActorCoords(&this->actor, &sp98, &spBC);
    Audio_PlaySfx_AtPos(&this->unk_0458, 0x384DU);
    for (i = 0; i < 20; i++) {
        effect = &this->unk_2618[i];
        Actor_OffsetOfPointInActorCoords(&this->actor, &sp8C, &spC8);
        if (sp98.z < sp8C.z) {
            effect->unk_0E.y = this->actor.shape.rot.y + ((s32)Rand_Next() >> 0x13);
        } else {
            effect->unk_0E.y = Math_Vec3f_Yaw(&spC8, &spBC) + ((s32)Rand_Next() >> 0x13);
        }
        effect->unk_0E.x = Math_Vec3f_Pitch(&spC8, &spBC) + ((s32)Rand_Next() >> 0x13);
        effect->unk_0E.z = 0;
        effect->unk_00.x = spC8.x + (80.0f * Math_CosS(effect->unk_0E.x) * Math_SinS(effect->unk_0E.y));
        effect->unk_00.y = spC8.y - (80.0f * Math_SinS(effect->unk_0E.x));
        effect->unk_00.z = spC8.z + (80.0f * Math_CosS(effect->unk_0E.x) * Math_CosS(effect->unk_0E.y));
        spB0.x = (2.0f * effect->unk_00.x) - spC8.x;
        spB0.y = (2.0f * effect->unk_00.y) - spC8.y;
        spB0.z = (2.0f * effect->unk_00.z) - spC8.z;
        if (BgCheck_EntityLineTest1(&play->colCtx, &spC8, &spB0, &spA4, &spD4, 0, 1, 0, 1, &sp84)) {
            effect->unk_0E.x -= 0x2000;
            effect->unk_00.x = spC8.x + (80.0f * Math_CosS(effect->unk_0E.x) * Math_SinS(effect->unk_0E.y));
            effect->unk_00.y = spC8.y - (80.0f * Math_SinS(effect->unk_0E.x));
            effect->unk_00.z = spC8.z + (80.0f * Math_CosS(effect->unk_0E.x) * Math_CosS(effect->unk_0E.y));
            spC8.x = (2.0f * effect->unk_00.x) - spC8.x;
            spC8.y = (2.0f * effect->unk_00.y) - spC8.y;
            spC8.z = (2.0f * effect->unk_00.z) - spC8.z;
        } else {
            Math_Vec3f_Copy(&spC8, &spB0);
        }
        effect->unk_0C = 0x113 + 0x14 * i;
        func_80B06558(effect);
        effect->unk_0E.z = (s32)Rand_Next() >> 0x10;
    }
}

void func_80B0696C(BossHakugin* this, Vec3f* arg1) {
    s32 i;
    BossHakuginEffect* temp_s0;

    for (i = 0; i < 180; i++) {
        temp_s0 = &this->unk_09F8[i];
        if (temp_s0->unk_18 < 0) {
            s16 sp2E;
            s16 sp2C;
            f32 sp28;

            Math_Vec3f_Copy(&temp_s0->unk_0, arg1);
            sp2C = Rand_S16Offset(0x1000, 0x3000);
            sp2E = this->actor.shape.rot.y + ((s32)Rand_Next() >> 0x12) + 0x8000;
            sp28 = Rand_ZeroFloat(5.0f) + 7.0f;
            temp_s0->unk_C.x = sp28 * Math_CosS(sp2C) * Math_SinS(sp2E);
            temp_s0->unk_C.y = sp28 * Math_SinS(sp2C);
            temp_s0->unk_C.z = sp28 * Math_CosS(sp2C) * Math_CosS(sp2E);
            temp_s0->unk_0.x = arg1->x + (Rand_ZeroFloat(3.0f) * temp_s0->unk_C.x);
            temp_s0->unk_0.y = arg1->y + (Rand_ZeroFloat(3.0f) * temp_s0->unk_C.y);
            temp_s0->unk_0.z = arg1->z + (Rand_ZeroFloat(3.0f) * temp_s0->unk_C.z);
            temp_s0->unk_24 = (Rand_ZeroFloat(6.0f) + 15.0f) * 0.0001f;
            temp_s0->unk_18 = 0x28;
            temp_s0->unk_1A = 0;
            break;
        }
    }
}

void func_80B06B20(BossHakugin* this, Vec3f* arg1) {
    Actor* sp1C;
    s32 i;

    if (((this->unk_044C.z < -200.0f) && (this->actor.speed > 10.0f) && (this->unk_018D == 0) &&
         (Rand_ZeroOne() < 0.4f))) {
        this->unk_018D = 4;
    } else {
        if (this->unk_018D > 0) {
            this->unk_018D--;
        }
        return;
    }

    for (i = 0; i < 8; i++) {
        sp1C = this->unk_09B0[i];

        if (sp1C->params == 0) {
            Math_Vec3f_Copy(&sp1C->world.pos, arg1);
            sp1C->params = 1;
            break;
        }
    }
}

void func_80B06C08(BossHakugin* this) {
    s32 i;

    if ((this->unk_018E == 0) && (this->actor.colChkInfo.health < 0x14) && (Rand_ZeroOne() < 0.35f)) {
        this->unk_018E = 4;
    } else {
        if (this->unk_018E > 0) {
            this->unk_018E--;
        }
        return;
    }
    for (i = 0; i < 10; i++) {
        Actor* tmp = this->unk_09D0[i];

        if (tmp->params == 0) {
            tmp->params = 2;
            return;
        }
    }
}

void func_80B06D38(BossHakugin* this, PlayState* play) {
    EnBom* sp44;
    s16 temp_a1;

    if ((this->actor.speed > 10.0f) && ((s32)this->actor.colChkInfo.health < 0xA) && (this->unk_018F == 0) &&
        (Rand_ZeroOne() < 0.35f)) {
        this->unk_018F = 4;
    } else {
        if (this->unk_018F > 0) {
            this->unk_018F--;
        }
        return;
    }
    sp44 = (EnBom*)Actor_Spawn(
        &play->actorCtx, play, ACTOR_EN_BOM,
        this->unk_0484.elements[1].dim.worldSphere.center.x - (100.0f * Math_SinS(this->actor.shape.rot.y)),
        this->unk_0484.elements[1].dim.worldSphere.center.y + 100.0f,
        this->unk_0484.elements[1].dim.worldSphere.center.z - (Math_CosS(this->actor.shape.rot.y) * 100.0f), 0, 0, 0,
        0);
    if (sp44 != NULL) {
        temp_a1 = (this->actor.yawTowardsPlayer - this->actor.shape.rot.y) - 0x8000;
        if (temp_a1 > 0x2000) {
            sp44->actor.world.rot.y = this->actor.shape.rot.y + 0xA000;
        } else if (temp_a1 < -0x2000) {
            sp44->actor.world.rot.y = this->actor.shape.rot.y + 0x6000;
        } else {
            sp44->actor.world.rot.y = this->actor.yawTowardsPlayer;
        }

        sp44->timer = (Rand_Next() >> 0x1C) + 0x11;
        sp44->actor.velocity.y = 2.0f;
        sp44->actor.speed = this->actor.xzDistToPlayer * 0.01f;
        sp44->actor.speed = CLAMP(sp44->actor.speed, 6.0f, 12.0f);

        Actor_SetScale(&sp44->actor, 0.02f);
    }
}

void func_80B06F48(BossHakugin* this, PlayState* play) {
    BossHakuginFhgFlashUnkStruct* iter;
    BossHakuginFhgFlashUnkStruct* iter2;
    BossHakuginFhgFlashUnkStruct* iter3;
    Vec3f spA0;
    s32 sp9C;
    s32 var_s4;
    s32 i;
    s32 j;
    s32 pad;

    sp9C = this->unk_0191 + 3;
    if (sp9C >= 15) {
        sp9C = 0;
    }

    for (i = 0; i < ARRAY_COUNT(this->unk_3158); i++) {
        if (((15 - (3 * i)) < this->actor.colChkInfo.health) || !((1 << (D_80B0EAB0[i] + 0x1F)) & this->unk_01B0)) {
            break;
        }

        iter3 = &this->unk_3158[i][sp9C];
        iter2 = &this->unk_3158[i][this->unk_0191];

        Math_Vec3f_Diff(&iter3->unk_00, &iter2->unk_00, &spA0);

        spA0.y -= 3.5f;

        var_s4 = Math3D_Vec3fMagnitude(&spA0) / 10.0f;
        if (var_s4 >= 2) {
            if (var_s4 >= 4) {
                var_s4 = 3;
            }
            Math_Vec3f_Scale(&spA0, 1.0f / var_s4);
        } else {
            var_s4 = 1;
        }

        for (j = 0; j < var_s4; j++) {
            iter = &this->unk_3158[i][this->unk_0191 + j];

            iter->unk_00.x = Rand_CenteredFloat(20.0f) + (iter2->unk_00.x + (spA0.x * j));
            iter->unk_00.y = Rand_CenteredFloat(20.0f) + (iter2->unk_00.y + (spA0.y * j));
            iter->unk_00.z = Rand_CenteredFloat(20.0f) + (iter2->unk_00.z + (spA0.z * j));
            iter->unk_0C = 0.01f;
            iter->unk_10 = 150;
            iter->unk_12 = 5 - j;
        }

        if ((play->gameplayFrames % 2) != 0) {
            EffectSsFhgFlash_SpawnShock(play, &this->actor, &this->unk_3158[i][this->unk_0191].unk_00, 250,
                                        i + FHGFLASH_SHOCK_GOHT_2);
        }
    }

    sp9C = this->unk_0191 - 3;
    if (sp9C < 0) {
        this->unk_0191 = 12;
    } else {
        this->unk_0191 = sp9C;
    }
}

s32 func_80B0728C(BossHakugin* this) {
    s16 rand;

    rand = ((Rand_Next() >> 0x12) + 0x4000);
    this->unk_0198 += rand;
    if (this->unk_01A8 == 5) {
        if (Math_SmoothStepToS(&this->unk_01A6, -0x900, 4, 0x200, 0x80) == 0) {
            this->unk_01A8--;
        }

        this->unk_01C8 = (this->unk_01A6 + 0x480) * -0.026041666f;
        this->unk_01C8 = CLAMP_MIN(this->unk_01C8, 0.001f);

        this->unk_01D0 = (this->unk_01A6 - 0x700) * -0.00021059783f;
        this->unk_01D0 = CLAMP_MAX(this->unk_01D0, 0.62f);

        if (this->unk_01D0 > 0.0f) {
            this->unk_01CC = -100.0f - (((0.62f / this->unk_01D0) - 1.0f) * 200.0f);
        } else {
            this->unk_01CC = -200.0f;
        }

    } else if (this->unk_01A8 > 0) {
        this->unk_01A8--;
    } else if (Math_ScaledStepToS(&this->unk_01A6, 0x700, 0x380) != 0) {
        this->unk_01D0 = (0x700 - this->unk_01A6) * 0.00024414062f * 0.62f;
        return 1;
    }

    return 0;
}

void func_80B07450(BossHakugin* this, PlayState* play) {
    Vec3f velocity;
    Vec3f pos;
    f32 temp;
    s32 i;

    if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_ICEB_FOOTSTEP_OLD);
        Math_Vec3f_Copy(&pos, &this->bodyPartsPos[D_80B0EA8C[GOHT_LIMB_FRONT_LEFT_HOOF]]);
        if (this->actor.xzDistToPlayer < 1500.0f) {
            temp = (1500.0f - this->actor.xzDistToPlayer) * 0.00066666666f;
            func_80B05A64(this, play, 17000, 6.5f * temp, 10);
        }

        func_80B06C08(this);
    } else if (Animation_OnFrame(&this->skelAnime, 2.0f)) {
        Math_Vec3f_Copy(&pos, &this->bodyPartsPos[D_80B0EA8C[GOHT_LIMB_BACK_LEFT_HOOF]]);
        func_80B06B20(this, &pos);
    } else if (Animation_OnFrame(&this->skelAnime, 3.0f)) {
        Math_Vec3f_Copy(&pos, &this->bodyPartsPos[D_80B0EA8C[GOHT_LIMB_FRONT_RIGHT_HOOF]]);
        func_80B06D38(this, play);
    } else if (Animation_OnFrame(&this->skelAnime, 11.0f)) {
        Math_Vec3f_Copy(&pos, &this->bodyPartsPos[D_80B0EA8C[GOHT_LIMB_BACK_RIGHT_HOOF]]);
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

void func_80B07700(BossHakugin* this, PlayState* play, s32 arg2) {
    Vec3f vel;
    Vec3f pos;

    if (arg2 != 0) {
        vel.y = (this->unk_019C - 30) * (1 / 70.0f);
    } else {
        vel.y = 0.1f;
    }

    vel.x = Rand_CenteredFloat(2.0f) * vel.y;
    vel.z = Rand_CenteredFloat(2.0f) * vel.y;

    pos.x = ((vel.x >= 0.0f ? 1.0f : -1.0f) * (Rand_ZeroFloat(20.0f) + 5.0f) * 4.0f) + this->unk_0964.dim.pos.x;
    pos.z = ((vel.z >= 0.0f ? 1.0f : -1.0f) * (Rand_ZeroFloat(20.0f) + 5.0f) * 4.0f) + this->unk_0964.dim.pos.z;
    if (arg2 != 0) {
        pos.y = this->unk_0964.dim.pos.y + (this->unk_0964.dim.height * vel.y);
    } else {
        pos.y = (Rand_ZeroFloat(this->unk_0964.dim.height) * 0.8f) + this->unk_0964.dim.pos.y;
    }
    vel.y += 0.8f;

    EffectSsIceSmoke_Spawn(play, &pos, &vel, &gZeroVec3f, 0x258);
}

s32 func_80B0791C(BossHakugin* this, PlayState* play) {
    Player* sp34 = GET_PLAYER(play);
    s16 var_v1;
    s32 var_v0_2;
    f32 sp28;
    f32 sp24;

    if (this->unk_044C.z > 0.0f) {
        return 0;
    }
    var_v1 = this->unk_01A0 - Camera_GetCamDirYaw(GET_ACTIVE_CAM(play));
    var_v0_2 = ABS_ALT(var_v1);

    if (var_v0_2 < 0x4000) {
        if (var_v0_2 < 0x1800) {
            this->unk_018C = 0;
        }
        return 0;
    }
    if (this->unk_018C == 1) {
        return 0;
    }
    sp24 = this->actor.world.pos.x * this->unk_01B4;
    sp28 = this->actor.world.pos.z * this->unk_01B4;
    if (((sp34->actor.world.pos.x > 1200.0f) && (sp34->actor.world.pos.z < 1200.0f) &&
         (sp34->actor.world.pos.z > -1200.0f) && (this->actor.world.pos.x < 0.0f) && (sp28 > 1200.0f)) ||
        ((sp34->actor.world.pos.x < -1200.0f) && (sp34->actor.world.pos.z < 1200.0f) &&
         (sp34->actor.world.pos.z > -1200.0f) && (this->actor.world.pos.x > 0.0f) && (sp28 < -1200.0f)) ||
        ((sp34->actor.world.pos.z > 1200.0f) && (sp34->actor.world.pos.x < 1200.0f) &&
         (sp34->actor.world.pos.x > -1200.0f) && (this->actor.world.pos.z < 0.0f) && (sp24 < -1200.0f)) ||
        ((sp34->actor.world.pos.z < -1200.0f) && (sp34->actor.world.pos.x < 1200.0f) &&
         (sp34->actor.world.pos.x > -1200.0f) && (this->actor.world.pos.z > 0.0f) && (sp24 > 1200.0f))) {
        return 1;
    }
    return 0;
}

void func_80B07B88(BossHakugin* this, PlayState* play) {
    if (this->unk_0196 == 0xA) {
        this->unk_0196 = 0;
        this->unk_01E4 = 0.0f;
        Actor_SpawnIceEffects(play, &this->actor, this->bodyPartsPos, 0xF, 3, 0.7f, 0.5f);
    }
}

void func_80B07BFC(BossHakugin* this, PlayState* play, s32 arg2) {
    if (this->actor.colChkInfo.damageEffect == 0x2) {
        this->unk_0196 = 0;
        this->unk_01E4 = 3.0f;
        this->unk_01DC = 2.5f;
    } else if (this->actor.colChkInfo.damageEffect == 0x4) {
        this->unk_0196 = 0x14;
        this->unk_01E4 = 3.0f;
        this->unk_01DC = 2.5f;
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->unk_0484.elements[arg2].info.bumper.hitPos.x,
                    this->unk_0484.elements[arg2].info.bumper.hitPos.y,
                    this->unk_0484.elements[arg2].info.bumper.hitPos.z, 0, 0, 0,
                    CLEAR_TAG_PARAMS(CLEAR_TAG_LARGE_LIGHT_RAYS));
    } else if (this->actor.colChkInfo.damageEffect == 0x3) {
        this->unk_0196 = 0xA;
        this->unk_01DC = 2.5f;
        this->unk_01E0 = 3.75f;
        this->unk_01E4 = 1.0f;
    } else if (this->actor.colChkInfo.damageEffect == 0xD) {
        this->unk_0196 = 0x15;
        this->unk_01DC = 2.5f;
        this->unk_01E4 = 3.0f;
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->unk_0484.elements[arg2].info.bumper.hitPos.x,
                    this->unk_0484.elements[arg2].info.bumper.hitPos.y,
                    this->unk_0484.elements[arg2].info.bumper.hitPos.z, 0, 0, 3,
                    CLEAR_TAG_PARAMS(CLEAR_TAG_LARGE_LIGHT_RAYS));
    }
}

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

    Animation_PlayOnce(&this->skelAnime, &gGohtThawAndBreakWallAnim);
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
    if ((this->unk_019C >= 30) && ((this->unk_019C % 2) != 0)) {
        func_80B07700(this, play, 1);
    } else if ((this->unk_019C % 4) == 0) {
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
            TitleCard_InitBossName(&play->state, &play->actorCtx.titleCtxt, Lib_SegmentedToVirtual(&gGohtTitleCardTex),
                                   160, 180, 128, 40);
        }

        if (Animation_OnFrame(&this->skelAnime, 86.0f)) {
            Audio_PlaySfx_AtPos(&this->unk_0458, NA_SE_EN_ICEB_CRY_OLD);
        }

        if (Animation_OnFrame(&this->skelAnime, 90.0f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_LAST1_DEMO_BREAK);
            for (i = 6; i < ARRAY_COUNT(this->unk_09D0); i++) {
                this->unk_09D0[i]->params = 0;
            }
        }

        if (SkelAnime_Update(&this->skelAnime)) {
            func_80B08848(this, play);
            return;
        }
    }

    if (((this->unk_019C + 12) >= 0) && ((this->unk_019C % 4) == 0)) {
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
    Animation_Change(&this->skelAnime, &gGohtRunAnim, 1.5f, 0.0f, 0.0f, ANIMMODE_LOOP, -3.0f);
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
    Animation_Change(&this->skelAnime, &gGohtRunAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP_INTERP, -5.0f);
    this->unk_01A2 = 0;
    this->unk_01C8 = 0.0f;
    this->unk_019E = Rand_CenteredFloat(3072.0f);
    this->unk_019C = 40;
    this->unk_01C4 = 16.0f;
    this->actionFunc = func_80B08CB8;
}

void func_80B08CB8(BossHakugin* this, PlayState* play) {
    s16 temp_a0;

    if (this->unk_01A4 == 0) {
        this->unk_0484.base.atFlags |= 1;
    }
    if (this->unk_0192 == 1) {
        if (func_80B0728C(this)) {
            Math_Vec3f_Copy(this->unk_3734, &this->unk_0380);
            this->unk_01B8 = this->actor.speed + 100.0f;
            this->unk_37AC.x = Math_CosS(0xA00) * Math_SinS(this->actor.shape.rot.y);
            this->unk_37AC.y = Math_SinS(0xA00);
            this->unk_37AC.z = Math_CosS(0xA00) * Math_CosS(this->actor.shape.rot.y);
            this->unk_0192 = 2;
            this->unk_01C8 = 0.0f;
            Audio_PlaySfx_AtPos(&this->unk_0458, 0x3852U);
            this->unk_37B8.base.atFlags |= 1;
        }
    } else {
        Math_ScaledStepToS(&this->unk_01A6, 0, 0x100);
    }
    if (func_80B0791C(this, play)) {
        func_80B09A94(this, play);
    } else {
        if (this->unk_019A >= 0x38) {
            this->unk_019A = 0;
            this->unk_019C = 0x28;
            this->unk_01C4 = 27.0f;
        }
        if ((this->unk_019C == 0x28) &&
            (Math_SmoothStepToF(&this->actor.speed, this->unk_01C4, 0.15f, 1.0f, 0.1f) < 0.05f)) {
            this->unk_019C -= 1;
        } else {
            if (this->unk_019C != 0x28) {
                this->unk_019C--;
                if (this->unk_019C == 0) {
                    if (this->actor.xzDistToPlayer > 1500.0f) {
                        this->unk_01C4 = 12.5f;
                    } else if (this->unk_044C.z > 0.0f) {
                        this->unk_01C4 = 21.0f;
                    } else {
                        this->unk_01C4 = 14.5f;
                    }
                    this->unk_01C4 += (0x1E - this->actor.colChkInfo.health) * (1.0f / 30.0f);
                    this->unk_019C = 0x28;
                }
            }
        }
        this->skelAnime.playSpeed = (this->actor.speed * 0.03125f) + 0.5f;
        SkelAnime_Update(&this->skelAnime);
        func_80B07450(this, play);
        if ((this->unk_01BC < (this->unk_01C0 * 0.5f)) || (this->unk_01BC < 89.100006f)) {
            this->unk_019E = (Rand_ZeroFloat(0.4f) + 0.6f) * 1536.0f;
        } else if ((this->unk_01C0 < (this->unk_01BC * 0.5f)) || (this->unk_01C0 < 89.100006f)) {
            this->unk_019E = -((Rand_ZeroFloat(0.4f) + 0.6f) * 1536.0f);
        } else if ((this->unk_01A2 == this->unk_019E) && (Rand_ZeroOne() < 0.005f)) {
            if (this->unk_019E > 0) {
                this->unk_019E = -((Rand_ZeroFloat(0.4f) + 0.6f) * 1536.0f);
            } else {
                this->unk_019E = ((Rand_ZeroFloat(0.4f) + 0.6f) * 1536.0f);
            }
        }
        Math_SmoothStepToS(&this->unk_01A2, this->unk_019E, 5, 0x800, 0x10);
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->unk_01A0 + this->unk_01A2, 5, 0x800, 0x10);

        temp_a0 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if ((this->unk_018C != 1) && (this->actor.xzDistToPlayer > 750.0f) && (this->actor.xzDistToPlayer < 1650.0f) &&
            (ABS_ALT(temp_a0) < 0x3000)) {
            func_80B09178(this);
        }
    }
}

void func_80B09178(BossHakugin* this) {
    Animation_Change(&this->skelAnime, &gGohtRunAnim, 1.5f, 0.0f, 0.0f, 0, -3.0f);
    this->actionFunc = func_80B091D8;
}

void func_80B091D8(BossHakugin* this, PlayState* play) {
    s16 var_v0;

    Math_ScaledStepToS(&this->unk_01A6, 0x800, 0x100);
    Math_StepToF(&this->actor.speed, 25.0f, 2.0f);
    SkelAnime_Update(&this->skelAnime);
    func_80B07450(this, play);
    if ((this->unk_044C.z < 0.0f) || (this->unk_0484.base.atFlags & 2)) {
        func_80B08C1C(this);
    } else {
        if ((this->unk_01C0 < 89.100006f) || (this->unk_01BC < 89.100006f)) {
            this->unk_019E = this->unk_01A0;
        } else {
            if (((this->unk_044C.x > 0.0f) && (this->unk_044C.x < this->unk_01C0)) ||
                ((this->unk_044C.x <= 0.0f) && (-this->unk_044C.x < this->unk_01BC))) {
                var_v0 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
                var_v0 = CLAMP(var_v0, -0x3000, 0x3000);
                this->unk_019E = this->actor.shape.rot.y + var_v0;
            } else {
                this->unk_019E =
                    ((s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y) >> 1) + this->actor.shape.rot.y;
            }
        }

        var_v0 = (this->unk_019E - this->unk_01A0);
        if (var_v0 > 0x1800) {
            this->unk_019E = this->unk_01A0 + 0x1800;
        } else if (var_v0 < -0x1800) {
            this->unk_019E = this->unk_01A0 - 0x1800;
        }
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->unk_019E, 5, 0x800, 0x100);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }
}

void func_80B093C0(BossHakugin* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &gGohtFallDownAnim, -3.0f);
    this->unk_0484.base.atFlags &= ~AT_ON;
    this->unk_0484.base.acFlags &= ~AC_HARD;
    this->unk_01A6 = 0;
    this->unk_0195 = 0;
    this->unk_01C8 = 0.0f;
    if (this->unk_0192 == 1) {
        Math_Vec3f_Copy(&this->unk_3734[0], &this->unk_0380);
        this->unk_01B8 = this->actor.speed + 100.0f;
        this->unk_37AC.x = Math_CosS(0xA00) * Math_SinS(this->actor.shape.rot.y);
        this->unk_37AC.y = Math_SinS(0xA00);
        this->unk_37AC.z = Math_CosS(0xA00) * Math_CosS(this->actor.shape.rot.y);
        this->unk_0192 = 2;
        this->unk_01C8 = 0.0f;
        Audio_PlaySfx_AtPos(&this->unk_0458, NA_SE_EN_COMMON_E_BALL_THR);
        this->unk_37B8.base.atFlags |= AT_ON;
    }
    this->unk_019C = 60;
    this->actor.speed = 20.0f;
    this->actionFunc = func_80B094E0;
}

void func_80B094E0(BossHakugin* this, PlayState* play) {
    CollisionPoly* spBC;
    Vec3f spB0;
    Vec3f spA4;
    s32 i;
    s32 sp9C;

    Actor_PlaySfx_Flagged(&this->actor, 0x301BU);
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->unk_0195 == 0) {
            this->unk_0195 = 1;
            func_80B05A64(this, play, 0x4268, 7, 0xA);
        }

        if (this->actor.speed > 5.0f) {

            for (i = 0; i < 2; i++) {
                s16 temp1 = this->actor.shape.rot.y + (u32)(0xF000 * i - 0x7800); // TODO: seems fake
                s16 temp2;
                f32 temp_fs1;

                spB0.x = 2.0f * Math_SinS(temp1);
                spB0.y = 1.0f;
                spB0.z = 2.0f * Math_CosS(temp1);

                temp2 = this->actor.shape.rot.y + (u32)(0x8000 * i - 0x4000);
                temp_fs1 = Rand_ZeroFloat(190.0f);
                spA4.x = this->actor.world.pos.x + (80.0f * Math_SinS(temp2)) +
                         (Math_SinS(this->actor.shape.rot.y) * temp_fs1);
                spA4.z = this->actor.world.pos.z + (80.0f * Math_CosS(temp2)) +
                         (Math_CosS(this->actor.shape.rot.y) * temp_fs1);
                spA4.y = this->actor.world.pos.y + 300.0f;
                spA4.y = BgCheck_EntityRaycastFloor5_2(play, &play->colCtx, &spBC, &sp9C, &this->actor, &spA4) + 10.0f;
                func_800B12F0(play, &spA4, &spB0, &gZeroVec3f, Rand_S16Offset(0x2EE, 0x64), 0xA, 0x1E);
            }
        }
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->unk_01A0, 5, 0x800, 0x10);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (this->actor.speed < 0.1f) {
        this->unk_019C--;
        this->actor.world.pos.x = this->actor.home.pos.x + Rand_CenteredFloat(5.0f);
        this->actor.world.pos.y = this->actor.home.pos.y + Rand_CenteredFloat(5.0f);
        this->actor.world.pos.z = this->actor.home.pos.z + Rand_CenteredFloat(5.0f);
        if (this->unk_019C == 0) {
            this->unk_0484.base.acFlags |= 4;
            Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.home.pos);
            func_80B08C1C(this);
            this->unk_01A4 = 0x14;
        }
    } else if (Math_StepToF(&this->actor.speed, 5.0f, 0.3f)) {
        Math_Vec3f_Copy(&this->actor.home.pos, &this->actor.world.pos);
        this->actor.speed = 0.0f;
    }
}

void func_80B09840(BossHakugin* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    Animation_MorphToPlayOnce(&this->skelAnime, &gGohtStationaryAnim, -10.0f);
    player->actor.parent = &this->actor;
    this->unk_0484.base.atFlags &= ~AT_ON;
    this->unk_0484.base.ocFlags1 &= ~OC1_ON;
    this->unk_019C = 10;
    this->actionFunc = func_80B098BC;
}

void func_80B098BC(BossHakugin* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 sp32;
    f32 sp2C;

    SkelAnime_Update(&this->skelAnime);
    Math_StepToF(&this->actor.speed, 0.0f, 2.0f);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->unk_01A0, 5, 0x800, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (this->unk_019C < 10) {
        this->unk_019C--;
        if (this->unk_019C == 0) {
            this->unk_0484.base.atFlags |= AT_ON;
            this->unk_0484.base.ocFlags1 |= OC1_ON;
            func_80B08C1C(this);
        }
    } else {
        if (Math_ScaledStepToS(&this->unk_01A6, -0x800, 0x1C0)) {
            player->actionVar2 = 0x64;
            player->actor.parent = NULL;
            player->invincibilityTimer = 0;
            player->actor.shape.rot.x = 0;
            func_800B8D50(play, &this->actor, 10.0f, (this->actor.shape.rot.y + 0x8000), 15.0f, 0x10);
            player->actor.world.pos.y += 30.0f;
            this->unk_019C--;
        } else {
            player->actionVar2 = 0;
            sp32 = -this->unk_0374.z + 0x1F40;
            player->actor.shape.rot.x = -this->unk_0374.z + 0x8FC0;

            sp2C = Math_CosS(sp32);
            player->actor.world.pos.x = this->actor.focus.pos.x - (Math_SinS(this->unk_01A0) * (20.0f * sp2C));
            player->actor.world.pos.y = this->actor.focus.pos.y - (Math_SinS(sp32) * 20.0f);
            player->actor.world.pos.z = this->actor.focus.pos.z - (Math_CosS(this->unk_01A0) * (20.0f * sp2C));
        }
    }
}

void func_80B09A94(BossHakugin* this, PlayState* play) {
    f32 var_fv1;
    s16 atan;

    if (this->actionFunc != func_80B09E20) {
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
        if (this->unk_01B4 == 1) {
            var_fv1 = -1.0f;
            this->actor.shape.rot.y -= 0x4000;
        } else {
            var_fv1 = 1.0f;
        }
        this->unk_01A0 = this->actor.shape.rot.y + (this->unk_01B4 * 0x6000);
        this->actor.world.rot.y = this->actor.shape.rot.y;
        this->actor.world.pos.x += var_fv1 * 300.0f * Math_CosS(this->actor.shape.rot.y);
        this->actor.world.pos.z -= var_fv1 * 300.0f * Math_SinS(this->actor.shape.rot.y);
        this->actor.world.pos.y += 500.0f;
        this->actor.world.pos.y =
            BgCheck_EntityRaycastFloor1(&play->colCtx, &this->actor.floorPoly, &this->actor.world.pos);
        this->unk_018C = 0;
    }
    this->unk_01A6 = 0x700;
    this->unk_019C = 0x96;
    this->unk_01CC = -100.0f;
    this->actionFunc = func_80B09C78;
}

void func_80B09C78(BossHakugin* this, PlayState* play) {
    f32 temp_fv1;
    f32 sp1C;

    SkelAnime_Update(&this->skelAnime);
    temp_fv1 = fabsf(this->unk_044C.x);
    sp1C = temp_fv1;
    Math_StepToF(&this->unk_01C8, 0.0f, 6.0f);
    if ((this->unk_044C.z < 0.0f) || (this->actor.xzDistToPlayer < 750.0f) || (this->unk_018C == 1)) {
        func_80B08C1C(this);
        return;
    }

    if ((this->unk_2618[0].unk_0C == 0) && (this->unk_01C8 < 0.1f) && (temp_fv1 < 400.0f) &&
        (this->unk_044C.z > 0.0f)) {
        func_80B09DFC(this);
        return;
    }

    if ((temp_fv1 > 400.0f) && ((play->gameplayFrames & 0xF) == 0xF)) {
        func_80B06C08(this);
        return;
    }

    if (this->unk_019C > 0) {
        this->unk_019C--;
    } else {
        this->unk_01B4 = -this->unk_01B4;
        this->unk_01A0 = this->actor.shape.rot.y;
        this->actor.world.rot.y = this->actor.shape.rot.y;
        func_80B08C1C(this);
    }
}

void func_80B09DFC(BossHakugin* this) {
    this->unk_01A8 = 5;
    this->unk_01C8 = 0.0f;
    this->actionFunc = func_80B09E20;
}

void func_80B09E20(BossHakugin* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    Audio_PlaySfx_AtPos(&this->unk_0458, NA_SE_EN_COMMON_THUNDER - SFX_FLAG);
    if (func_80B0728C(this) != 0) {
        func_80B06600(this, &this->unk_0380, play);
        func_80B09A94(this, play);
    }
}

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

void func_80B09F7C(BossHakugin* this) {
    f32 temp_fv0_2;

    Animation_Change(&this->skelAnime, &gGohtRunAnim, 1.3f, 0.0f, 0.0f, ANIMMODE_LOOP_INTERP, -3.0f);
    this->unk_01AC = CutsceneManager_GetCurrentSubCamId(this->actor.csId);

    if ((this->actor.world.pos.z >= 0.0f) && (this->actor.world.pos.x >= 0.0f)) {
        this->unk_019E = -0x4000;
    } else {
        if ((this->actor.world.pos.z >= 0.0f) && (this->actor.world.pos.x < 0.0f)) {
            this->unk_019E = -0x8000;
        } else if ((this->actor.world.pos.x >= 0.0f) && (this->actor.world.pos.z < 0.0f)) {
            this->unk_019E = 0;
        } else {
            this->unk_019E = 0x4000;
        }
    }

    if (this->unk_01B4 == 1) {
        this->unk_019E -= 0x4000;
    }

    temp_fv0_2 = this->unk_01B4;
    if ((this->unk_019E > 0x6000) || (this->unk_019E < -0x6000)) {
        this->unk_038C.x = temp_fv0_2 * -1200.0f;
        this->unk_038C.y = (temp_fv0_2 * 80.0f) + -240.0f + 60.0f;
        this->unk_038C.z = 1200.0f;
    } else if ((this->unk_019E < 0x2000) && (this->unk_019E > -0x2000)) {
        this->unk_038C.x = temp_fv0_2 * 1200.0f;
        this->unk_038C.y = 60.0f;
        this->unk_038C.z = -1200.0f;
    } else if (this->unk_019E >= 0x2000) {
        this->unk_038C.x = -1200.0f;
        this->unk_038C.y = (80.0f * temp_fv0_2) + -80.0f + 60.0f;
        this->unk_038C.z = temp_fv0_2 * -1200.0f;
    } else {
        this->unk_038C.x = 1200.0f;
        this->unk_038C.y = (-160.0f * temp_fv0_2) + -160.0f + 60.0f;
        this->unk_038C.z = temp_fv0_2 * 1200.0f;
    }

    this->unk_01C8 = 0.0f;
    this->unk_01A6 = 0;
    Play_EnableMotionBlur(140);
    this->unk_01A2 = Rand_S16Offset(0x800, 0x800) * ((Rand_ZeroOne() < 0.5f) ? -1 : 1);
    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM_MAIN, 1);
    this->actor.home.rot.y = this->actor.shape.rot.y;
    this->unk_019C = 18;
    if ((this->unk_0192 == 2) || (this->unk_0192 == 3)) {
        this->unk_0192 = 4;
        this->unk_01AA = 0;
    }

    this->unk_01AE = Rand_ZeroFloat(6144.0f);
    this->unk_0374.y = 0;
    this->unk_0374.z = 0;
    this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
    this->actor.speed = CLAMP_MIN(this->actor.speed, 16.0f);
    this->actionFunc = func_80B0A2A4;
}

void func_80B0A2A4(BossHakugin* this, PlayState* play) {
    Vec3f at;
    f32 absPosX;
    f32 absPosZ;
    s32 absRotY;

    Math_StepToF(&this->actor.speed, 15.0f, 2.0f);
    SkelAnime_Update(&this->skelAnime);
    this->unk_018D = 10;
    this->unk_018E = 10;
    this->unk_018F = 10;
    func_80B07450(this, play);
    Math_SmoothStepToS(&this->actor.home.rot.y, this->unk_01A0, 5, 0x800, 0x100);
    this->unk_019C--;
    this->actor.shape.rot.y = (s32)(Math_SinF(this->unk_019C * 0.17453294f) * this->unk_01A2) + this->actor.home.rot.y;

    if (this->unk_019C == 0) {
        if (this->unk_01A2 > 0) {
            this->unk_01A2 = -Rand_S16Offset(0x800, 0x800);
        } else {
            this->unk_01A2 = Rand_S16Offset(0x800, 0x800);
        }
        this->unk_019C = 0x12;
        this->unk_01AE = Rand_ZeroFloat(6144.0f);
    }

    this->unk_0374.z = (8192.0f * Math_SinS(this->unk_01AE)) * Math_SinF(this->unk_019C * 0.34906587f);
    this->unk_0374.y = (8192.0f * Math_CosS(this->unk_01AE)) * Math_SinF(this->unk_019C * 0.34906587f);
    this->actor.shape.rot.z = Math_SinF(this->unk_019C * 0.17453294f) * -(this->unk_01A2 * 0.3f);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    at.x = (Math_SinS(this->actor.shape.rot.y) * 100.0f) + this->actor.world.pos.x;
    at.y = this->actor.world.pos.y + 200.0f;
    at.z = (Math_CosS(this->actor.shape.rot.y) * 100.0f) + this->actor.world.pos.z;
    Play_SetCameraAtEye(play, this->unk_01AC, &at, &this->unk_038C);

    if (this->unk_019E == this->unk_01A0) {
        absPosX = fabsf(this->actor.world.pos.x);
        absPosZ = fabsf(this->actor.world.pos.z);
        absRotY = ABS_ALT(this->actor.shape.rot.y);

        if (((absPosX > 1289.1f) && (absPosZ < 1110.9f) && ((absRotY < 0x2000) || (absRotY > 0x6000))) ||
            ((absPosZ > 1289.1f) && (absPosX < 1110.9f) && (absRotY > 0x2000) && (absRotY < 0x6000))) {
            func_80B0A5EC(this);
        }
    }
}

void func_80B0A5EC(BossHakugin* this) {
    if (this->unk_01B4 == 1) {
        this->unk_019E -= 0x4000;
    } else {
        this->unk_019E += 0x4000;
    }

    this->actor.speed = 15.0f;
    this->actionFunc = func_80B0A638;
}

void func_80B0A638(BossHakugin* this, PlayState* play) {
    Vec3f at;
    Vec3f eyeTarget;
    s32 var_v0;
    s16 temp_a0;

    SkelAnime_Update(&this->skelAnime);
    at.x = (Math_SinS(this->actor.shape.rot.y) * 100.0f) + this->actor.world.pos.x;
    at.y = this->actor.world.pos.y + 200.0f;
    at.z = (Math_CosS(this->actor.shape.rot.y) * 100.0f) + this->actor.world.pos.z;
    temp_a0 = this->actor.shape.rot.y - (this->unk_01B4 * 0x6000);
    eyeTarget.x = (Math_SinS(temp_a0) * 400.0f) + this->actor.world.pos.x;
    eyeTarget.y = this->actor.world.pos.y + 100.0f;
    eyeTarget.z = Math_CosS(temp_a0) * 400.0f + this->actor.world.pos.z;
    Math_Vec3f_StepTo(&this->unk_038C, &eyeTarget, 25.0f);
    Play_SetCameraAtEye(play, this->unk_01AC, &at, &this->unk_038C);
    this->unk_018D = 10;
    this->unk_018E = 10;
    this->unk_018F = 10;
    func_80B07450(this, play);

    if ((Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk_019E, 0x300)) &&
        ((this->unk_01BC <= 189.00002f) || (this->unk_01C0 <= 189.00002f))) {
        func_80B0A87C(this);
    } else {
        if (((this->unk_01B4 == 1) && (this->unk_01BC <= 189.00002f)) ||
            ((this->unk_01B4 == -1) && (this->unk_01C0 <= 189.00002f))) {
            var_v0 = ABS_ALT(this->unk_019E);
            if (var_v0 < 0x2000) {
                this->actor.world.pos.z = -1389.0f;
            } else if (var_v0 >= 0x6001) {
                this->actor.world.pos.z = 1389.0f;
            } else if (this->unk_019E > 0) {
                this->actor.world.pos.x = -1389.0f;
            } else {
                this->actor.world.pos.x = 1389.0f;
            }
        }
    }

    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void func_80B0A87C(BossHakugin* this) {
    this->unk_019C = 0;
    this->actor.speed = 0.0f;
    this->skelAnime.playSpeed = 0.5f;
    func_80B0D9CC(this);
    this->actionFunc = func_80B0A8C4;
}

#ifdef NON_MATCHING
// non-matchings seem to be caused by accesses to D_80B0EB38
void func_80B0A8C4(BossHakugin* this, PlayState* play) {
    EnBom* bomb;
    Vec3s* test;
    Camera* camera;
    Vec3f eyeTarget;
    s16 temp_s0;
    s32 sp60;
    s32 i;
    s32 pad;

    camera = Play_GetCamera(play, this->unk_01AC);
    SkelAnime_Update(&this->skelAnime);
    sp60 = this->unk_019C / 6;
    temp_s0 = this->actor.shape.rot.y + (0x6000 * this->unk_01B4);
    eyeTarget.x = (Math_SinS(temp_s0) * 500.0f) + this->actor.world.pos.x;
    eyeTarget.y = this->actor.world.pos.y + 250.0f;
    eyeTarget.z = (Math_CosS(temp_s0) * 500.0f) + this->actor.world.pos.z;
    Math_Vec3f_StepTo(&this->unk_038C, &eyeTarget, 25.0f);
    Play_SetCameraAtEye(play, this->unk_01AC, &camera->at, &this->unk_038C);
    if (sp60 == 30) {
        Camera* camera2 = Play_GetCamera(play, 0);

        Play_DisableMotionBlur();
        CutsceneManager_Stop(this->actor.csId);
        Play_SetCameraAtEye(play, this->unk_01AC, &camera2->at, &camera2->eye);
        func_80B05EE0(this, play);
        func_80B0DFA8(this);
        this->actor.draw = func_80B0E5A4;
        this->actor.update = func_80B0E548;
    } else if (((this->unk_019C % 6) == 0) && (sp60 < 6)) {
        test = &this->unk_0484.elements[D_80B0EB38[sp60].unk_00].dim.worldSphere.center;
        bomb = (EnBom*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_BOM, test->x, test->y, test->z, 1, 0, 0, 0);
        if (bomb != NULL) {
            bomb->timer = 0;
        }
        this->unk_01B0 &= ~D_80B0EB38[sp60].unk_04;
        if (sp60 == 5) {
            AudioSeq_QueueSeqCmd(0x8021U);
        }
    }

    if (((this->unk_019C + 3) % 6) == 0) {
        sp60 = (this->unk_019C + 3) / 6 - 1;
        if (sp60 < 4) {
            for (i = D_80B0EB24[sp60]; i < D_80B0EB24[sp60 + 1]; i++) {
                this->unk_09F8[i].unk_C.y = Rand_ZeroFloat(5.0f) + 5.0f;
            }
        }
        if (sp60 < 6) {
            if (sp60 & 1) {
                Audio_PlaySfx_AtPos(&this->unk_0458, 0x393EU);
            } else {
                Audio_PlaySfx_AtPos(&this->unk_0458, 0x393DU);
            }
        }
        if (1) {} // TODO: probably fake
    }

    this->unk_019C++;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0A8C4.s")
#endif

void func_80B0AC30(BossHakugin* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if ((this->unk_0484.base.atFlags & 2) &&
        ((this->actionFunc == func_80B091D8) || !(player->stateFlags3 & 0x80000))) {
        if ((this->actionFunc == func_80B091D8) && (this->unk_0484.elements->info.toucherFlags & 2) &&
            !(this->unk_0484.base.atFlags & 4) && (play->grabPlayer(play, player))) {
            func_80B09840(this, play);
        } else if (player->stateFlags3 & 0x1000) {
            player->unk_B08 = player->linearVelocity = -5.0f;
            player->unk_B0C += player->unk_B08 * 0.05f;
            player->actor.velocity.y = 10.0f;
            player->unk_B8C = 4;
            player->actor.shape.rot.y = player->actor.home.rot.y = player->currentYaw = player->actor.world.rot.y;

        } else if (!(this->unk_0484.base.atFlags & 4)) {
            s16 var_a3 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;

            if (var_a3 > 0) {
                var_a3 = this->actor.shape.rot.y + (s32)(var_a3 / 2.0f) + 0x4000;
            } else {
                var_a3 = this->actor.shape.rot.y + (s32)(var_a3 / 2.0f) - 0x4000;
            }
            func_800B8D50(play, &this->actor, 5.0f, var_a3, 6.0f, 0U);
        }
    }
}

s32 func_80B0ADFC(BossHakugin* this, PlayState* play) {
    if (this->unk_0484.base.acFlags & 2) {
        s32 i;

        for (i = 0; i < 19; i++) {
            if (this->unk_0484.elements[i].info.bumperFlags & 2) {
                break;
            }
        }
        if (i == 19) {
            return 0;
        }
        if ((this->unk_0196 == 0xA) && (this->unk_0484.elements[i].info.acHitInfo->toucher.dmgFlags & 0xDB0B3)) {
            return 0;
        }
        func_80B07B88(this, play);
        if (this->actionFunc == func_80B094E0) {
            Actor_SetColorFilter(&this->actor, 0x4000U, 0xFFU, 0U, (u16)0xF);
            func_80B07BFC(this, play, i);
            if (Actor_ApplyDamage(&this->actor) == 0) {
                Enemy_StartFinishingBlow(play, &this->actor);
                Actor_PlaySfx(&this->actor, 0x3950U);
                func_80B09E84(this);
            } else {
                Actor_PlaySfx(&this->actor, 0x3951U);
            }
            this->unk_01A4 = 0xF;
            return 1;
        }
        if (((this->actor.colChkInfo.damageEffect == 0xF) || (this->actor.colChkInfo.damageEffect == 0xE) ||
             (this->actor.colChkInfo.damageEffect == 2) || (this->actor.colChkInfo.damageEffect == 3) ||
             (this->actor.colChkInfo.damageEffect == 4) || (this->actor.colChkInfo.damageEffect == 0xD) ||
             (this->actor.colChkInfo.damageEffect == 0xC)) &&
            ((this->actionFunc == func_80B08CB8) || (this->actionFunc == func_80B09E20) ||
             (this->actionFunc == func_80B09C78) || (this->actionFunc == func_80B091D8))) {
            Player* player = GET_PLAYER(play);

            if (this->actor.colChkInfo.damageEffect == 0xF) {
                player->pushedSpeed = 15.0f;
                if ((s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y) > 0) {
                    player->pushedYaw = this->actor.shape.rot.y + 0x4000;
                } else {
                    player->pushedYaw = this->actor.shape.rot.y - 0x4000;
                }
            }
            this->unk_01A4 = 0xF;
            Actor_SetColorFilter(&this->actor, 0x4000U, 0xFF, 0, 0xF);
            this->unk_019A += 0x23;
            func_80B07BFC(this, play, i);
            this->actor.colChkInfo.damage = this->unk_0484.elements[i].info.acHitInfo->toucher.damage;
            if (Actor_ApplyDamage(&this->actor) == 0) {
                Enemy_StartFinishingBlow(play, &this->actor);
                Actor_PlaySfx(&this->actor, 0x3950U);
                func_80B09E84(this);
            } else {
                if ((this->actor.colChkInfo.damageEffect == 0xC) ||
                    ((this->actor.colChkInfo.damageEffect == 0xF) && (this->actionFunc != func_80B091D8) &&
                     ((this->unk_0484.elements[0].info.bumperFlags & 2) ||
                      (this->unk_0484.elements[1].info.bumperFlags & 2) ||
                      (this->unk_0484.elements[2].info.bumperFlags & 2) ||
                      (this->unk_0484.elements[3].info.bumperFlags & 2) ||
                      (this->unk_0484.elements[6].info.bumperFlags & 2) ||
                      (this->unk_0484.elements[9].info.bumperFlags & 2) ||
                      (this->unk_0484.elements[13].info.bumperFlags & 2) ||
                      (this->unk_0484.elements[17].info.bumperFlags & 2) ||
                      (this->unk_0484.elements[18].info.bumperFlags & 2)))) {
                    func_80B093C0(this);
                } else if ((this->unk_0192 == 0) && (this->unk_01AA == 0) && (this->actionFunc == func_80B08CB8) &&
                           (this->actor.colChkInfo.damageEffect == 0xF)) {
                    this->unk_01A8 = 5;
                    this->unk_0192 = 1;
                }
                Actor_PlaySfx(&this->actor, 0x3951U);
            }
            return 1;
        } else {
            s32 j;

            this->unk_01A4 = 0x14;
            for (j = 0; j < 19; j++) {
                Vec3f sp40;
                ColliderInfo* hurtbox = &this->unk_0484.elements[j].info;

                if ((hurtbox->bumperFlags & 2) && (hurtbox->acHitInfo != NULL) &&
                    !(hurtbox->acHitInfo->toucherFlags & 0x18)) {
                    Math_Vec3s_ToVec3f(&sp40, &hurtbox->bumper.hitPos);
                    EffectSsHitmark_SpawnFixedScale(play, 3, &sp40);
                    CollisionCheck_SpawnShieldParticlesMetalSound(play, &sp40, &this->actor.projectedPos);
                    break;
                }
            }
        }
    }

    return 0;
}

void func_80B0B238(BossHakugin* this) {
    BossHakuginEffect* temp_s0;
    s32 i;

    for (i = 0; i < 180; i++) {
        temp_s0 = &this->unk_09F8[i];

        if (temp_s0->unk_18 >= 0) {
            temp_s0->unk_18--;
            temp_s0->unk_C.y += -1.0f;
            Math_Vec3f_Sum(&temp_s0->unk_0, &temp_s0->unk_C, &temp_s0->unk_0);
            if (temp_s0->unk_0.y < -500.0f) {
                temp_s0->unk_18 = -1;
            } else {
                temp_s0->unk_1C.x += (s16)(0x700 + (Rand_Next() >> 0x17));
                temp_s0->unk_1C.y += (s16)(0x900 + (Rand_Next() >> 0x17));
                temp_s0->unk_1C.z += (s16)(0xB00 + (Rand_Next() >> 0x17));
            }
        }
    }
}

void func_80B0B34C(BossHakugin* this) {
    BossHakuginEffect* effect;
    s32 i;

    for (i = 0; i < 36; i++) {
        effect = &this->unk_09F8[i];
        Math_StepToF(&effect->unk_0.y, effect->unk_C.x, effect->unk_C.y);
        if (effect->unk_C.y > 0.0f) {
            effect->unk_C.y = effect->unk_C.y + 6.0f;
        }
    }
}

void func_80B0B3F4(BossHakugin* this) {
    s32 i;
    s32 j;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 15; j++) {
            BossHakuginFhgFlashUnkStruct* effect = &this->unk_3158[i][j];

            if (effect->unk_10 > 0) {
                effect->unk_12--;
                effect->unk_00.y += 3.5f;
                effect->unk_0C += 0.003f;
                if (effect->unk_12 < 0) {
                    effect->unk_10 -= 0xF;
                    if (effect->unk_10 < 0) {
                        effect->unk_10 = 0;
                    }
                }
            }
        }
    }
}

void func_80B0B548(BossHakugin* this, PlayState* play) {
    BossHakuginUnkStruct_2618* unk_str;
    s16 rand;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_2618); i++) {
        unk_str = &this->unk_2618[i];

        if (unk_str->unk_14.base.atFlags & 2) {
            Player* player = GET_PLAYER(play);
            this->unk_018C = 1;
            Player_PlaySfx(player, NA_SE_EN_COMMON_E_BALL_HIT);
            unk_str->unk_14.base.atFlags &= ~2;
        }
        if (unk_str->unk_0C > 0) {
            unk_str->unk_0C -= 0x14;
            if (unk_str->unk_0C <= 0) {
                unk_str->unk_0C = 0;
            } else if (unk_str->unk_0C < 0x100) {
                rand = (s32)Rand_Next() >> 0x10;
                unk_str->unk_0E.z = rand;
                if (unk_str->unk_0C >= 0x3D) {
                    CollisionCheck_SetAT(play, &play->colChkCtx, &unk_str->unk_14.base);
                }
            }
        }
    }
}

void func_80B0B660(BossHakugin* this, PlayState* play) {
    Player* spA4 = GET_PLAYER(play);
    CollisionPoly* spA0 = NULL;
    Vec3f sp94;
    Vec3f sp88;
    Vec3f sp7C;
    Vec3f sp70;
    Vec3f* sp6C;
    Vec3f* var_s0;
    s32 var_s0_2;
    f32 sp60;
    s32 sp5C;
    s32 sp58 = 0;
    s16 temp_v1;

    sp6C = this->unk_3734;

    if (this->unk_0192 == 2) {
        if (Math_StepToF(&this->unk_01B8, 50.0f, 3.5f)) {
            this->unk_0192 = 3;
        }
    } else if (this->unk_0192 == 3) {
        sp60 = BINANG_TO_RAD(Math3D_Vec3fDistSq(sp6C, &spA4->actor.world.pos) * (1.0f / SQ(120.0f)) * 32.0f);
        if (sp60 > M_PI / 4.0f) {
            sp60 = M_PI / 4.0f;
        }
        Math_Vec3f_Diff(&spA4->actor.world.pos, sp6C, &sp70);
        if (func_80B0573C(&sp70)) {
            func_80B057A4(&this->unk_37AC, &sp70, sp60);
        }
    } else if (this->unk_0192 != 4) {
        return;
    }
    Audio_PlaySfx_AtPos(&this->unk_0464, 0x304CU);
    if (this->unk_01AA < 0xA) {
        this->unk_01AA++;
    }
    if ((this->unk_0192 == 4) && (this->unk_01AA == 9)) {
        this->unk_0192 = 0;
        this->unk_01AA = 0;
    } else {
        var_s0 = &this->unk_3734[9];
        while (var_s0 != sp6C) {
            Math_Vec3f_Copy(var_s0, var_s0 - 1);
            var_s0--;
        }
        this->unk_0198 += (s16)(0x4000 + (Rand_Next() >> 0x12));
        if (this->unk_0192 != 4) {
            if (this->unk_37B8.base.atFlags & 2) {
                this->unk_0192 = 4;
                this->unk_01AA = 0;
                this->unk_37B8.base.atFlags &= ~2;
                this->unk_37B8.base.atFlags &= ~1;
                sp58 = 1;
                Audio_PlaySfx_AtPos(&this->unk_0464, 0x384EU);
            }
            sp88.x = sp6C->x + (this->unk_01B8 * this->unk_37AC.x);
            sp88.y = sp6C->y + (this->unk_01B8 * this->unk_37AC.y);
            sp88.z = sp6C->z + (this->unk_01B8 * this->unk_37AC.z);
            if (BgCheck_EntityLineTest1(&play->colCtx, sp6C, &sp88, &sp94, &spA0, 1, 1, 1, 1, &sp5C)) {
                var_s0_2 = 0;
                Math_Vec3f_Copy(sp6C, &sp94);

                if ((spA0->normal.y >= -0x6664) && (spA0->normal.y < 0x3FFF)) {
                    temp_v1 =
                        Math_Vec3f_Yaw(sp6C, &spA4->actor.world.pos) -
                        Math_Atan2S_XY(spA0->normal.z * COLPOLY_NORMAL_FRAC, spA0->normal.x * COLPOLY_NORMAL_FRAC);
                    var_s0_2 = (ABS_ALT(temp_v1) > 0x4000) ? 1 : 0LL; // TODO: make less fake
                }
                if ((this->unk_0192 == 3) && (var_s0_2 || (spA0->normal.y >= 0x4000))) {
                    this->unk_0192 = 4;
                    this->unk_01AA = 0;
                    if (sp58 == 0) {
                        Audio_PlaySfx_AtPos(&this->unk_0464, 0x384EU);
                    }
                } else {
                    sp7C.x = spA0->normal.x * COLPOLY_NORMAL_FRAC;
                    sp7C.y = spA0->normal.y * COLPOLY_NORMAL_FRAC;
                    sp7C.z = spA0->normal.z * COLPOLY_NORMAL_FRAC;
                    func_80179F64(&this->unk_37AC, &sp7C, &sp70);
                    Math_Vec3f_Copy(&this->unk_37AC, &sp70);
                }
            } else {
                Math_Vec3f_Copy(sp6C, &sp88);
            }
            this->unk_37B8.dim.worldSphere.center.x = sp6C->x;
            this->unk_37B8.dim.worldSphere.center.y = sp6C->y;
            this->unk_37B8.dim.worldSphere.center.z = sp6C->z;
            CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk_37B8.base);
        }
    }
}

void BossHakugin_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    BossHakugin* this = (BossHakugin*)thisx;
    Vec3s sp70;
    Player* player = GET_PLAYER(play);

    this->unk_0190 = 0;
    DECR(this->unk_019A);

    if ((this->actionFunc != func_80B09EDC) && (func_80B0ADFC(this, play) == 0)) {
        func_80B0AC30(this, play);
    }
    func_80B0607C(this, play);
    Actor_OffsetOfPointInActorCoords(&this->actor, (Vec3f*)&this->unk_044C.x, &player->actor.world.pos);
    this->actionFunc(this, play);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 450.0f, 89.100006f, 0.0f, 0x1DU);
    func_800BE3D0(&this->actor, this->actor.shape.rot.y, &sp70);
    Math_ScaledStepToS(&this->actor.shape.rot.x, sp70.x, 0x100);
    Math_ScaledStepToS(&this->actor.shape.rot.z, sp70.z, 0x100);
    if (this->actionFunc == func_80B0A8C4) {
        func_80B0B34C(this);
    } else {
        func_80B0B238(this);
    }
    func_80B0B3F4(this);
    func_80B0B548(this, play);
    func_80B0B660(this, play);
    func_80B05B04(this, play);
    func_80B05CBC(this, player);
    func_80B05D4C(this);
    if ((this->unk_0484.base.atFlags & 1) && (this->actor.colorFilterTimer == 0)) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk_0484.base);
    } else {
        this->unk_0484.base.atFlags &= ~2;
    }
    if (this->unk_01A4 == 0) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk_0484.base);
    } else {
        this->unk_0484.base.acFlags &= ~2;
        this->unk_01A4--;
    }
    if (this->unk_0484.base.ocFlags1 & 1) {
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk_0484.base);
    } else {
        this->unk_0484.base.ocFlags1 &= ~2;
    }
    if (this->unk_01E4 > 0.0f) {
        if (this->unk_0196 != 0xA) {
            Math_StepToF(&this->unk_01E4, 0.0f, 0.05f);
            this->unk_01DC = (this->unk_01E4 + 1.0f) * 1.25f;
            this->unk_01DC = CLAMP_MAX(this->unk_01DC, 2.5f);
        } else if (!Math_StepToF(&this->unk_01E0, 2.5f, 0.41666666f)) {
            Actor_PlaySfx_Flagged(&this->actor, 0x20B2U);
        } else {
            func_80B07B88(this, play);
        }
    }

    if (player->actor.floorHeight < -400.0f) {
        CollisionPoly* sp68 = NULL;
        Vec3f sp5C;
        Vec3f sp50;
        s32 sp4C;

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
                                    true, &sp4C)) {
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
    static s32 D_80B0EB68 = 4;
    static s32 D_80B0EB6C = 6;
    BossHakugin* this = THIS;

    if (this->actionFunc == func_80B0A8C4) {
        if (limbIndex == GOHT_LIMB_ROOT) {
            pos->y -= this->actor.shape.yOffset;
        }
        if (!(this->unk_01B0 & (1 << (limbIndex + 0x1F)))) {
            *dList = NULL;
        }
    }

    if ((this->unk_0190 == 0) && (limbIndex == D_80B0EB6C)) {
        Matrix_MultZero(&this->unk_3158[D_80B0EB68][this->unk_0191].unk_00);
        D_80B0EB68--;
        if (D_80B0EB68 < 0) {
            D_80B0EB68 = 4;
        }
        D_80B0EB6C = D_80B0EAB0[D_80B0EB68];
    }

    if (limbIndex == GOHT_LIMB_HEAD) {
        rot->z += this->unk_01A6;
        if (this->actionFunc == func_80B0A2A4) {
            rot->z += this->unk_0374.z;
            rot->y += this->unk_0374.y;
        }
    } else if (limbIndex == GOHT_LIMB_THORAX_WRAPPER) {
        rot->z += (s16)(this->unk_01A6 * 2);
    } else if ((limbIndex == GOHT_LIMB_FRONT_LEFT_LEG_ROOT) || (limbIndex == GOHT_LIMB_FRONT_RIGHT_LEG_ROOT)) {
        rot->z -= (s16)(this->unk_01A6 * 3);
    }

    return false;
}

void BossHakugin_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    BossHakugin* this = THIS;
    s8 bodyPartIndex;
    s32 i;
    f32 cos;
    s16 angle;

    Collider_UpdateSpheres(limbIndex, &this->unk_0484);
    bodyPartIndex = D_80B0EA8C[limbIndex];
    if (bodyPartIndex > BODYPART_NONE) {
        for (i = 0; i < ARRAY_COUNT(this->unk_04A4); i++) {
            if (this->unk_0484.elements[i].dim.limb == limbIndex) {
                Math_Vec3s_ToVec3f(&this->bodyPartsPos[bodyPartIndex],
                                   &this->unk_0484.elements[i].dim.worldSphere.center);
                break;
            }
        }
        if (i == ARRAY_COUNT(this->unk_04A4)) {
            Matrix_MultZero(&this->bodyPartsPos[bodyPartIndex]);
        }
    }
    if (limbIndex == GOHT_LIMB_HEAD) {
        Matrix_MultVecX(3500.0f, &this->actor.focus.pos);
        this->actor.focus.rot.y = this->actor.shape.rot.y;
        if (this->actionFunc != func_80B0A2A4) {
            Matrix_MtxFToYXZRot(Matrix_GetCurrent(), &this->unk_0374, false);
        }

        if (this->unk_01C8 > 0.0f) {
            angle = 0x12C0 - this->unk_0374.z;
            cos = Math_CosS(angle);
            this->unk_0380.x = this->actor.focus.pos.x - (Math_SinS(this->actor.shape.rot.y) * (60.0f * cos));
            this->unk_0380.y = this->actor.focus.pos.y - (Math_SinS(angle) * 60.0f);
            this->unk_0380.z = this->actor.focus.pos.z - (Math_CosS(this->actor.shape.rot.y) * (60.0f * cos));
        }
    }
}

void func_80B0C398(BossHakugin* this, PlayState* play) {
    BossHakuginEffect* effect;
    s32 i;

    OPEN_DISPS(play->state.gfxCtx);

    gSPDisplayList(POLY_OPA_DISP++, gGohtRockMaterialDL);
    for (i = 0; i < ARRAY_COUNT(this->unk_09F8); i++) {
        effect = &this->unk_09F8[i];
        if ((effect->unk_18 >= 0) && (effect->unk_1A == 0)) {
            Matrix_SetTranslateRotateYXZ(effect->unk_0.x, effect->unk_0.y, effect->unk_0.z, &effect->unk_1C);
            Matrix_Scale(effect->unk_24, effect->unk_24, effect->unk_24, MTXMODE_APPLY);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, gGohtRockModelDL);
        }
    }

    gSPDisplayList(POLY_OPA_DISP++, gGohtStalactiteMaterialDL);
    for (i = 0; i < ARRAY_COUNT(this->unk_09F8); i++) {
        effect = &this->unk_09F8[i];
        if ((effect->unk_18 >= 0) && (effect->unk_1A == 1)) {
            Matrix_SetTranslateRotateYXZ(effect->unk_0.x, effect->unk_0.y, effect->unk_0.z, &effect->unk_1C);
            Matrix_Scale(effect->unk_24, effect->unk_24, effect->unk_24, MTXMODE_APPLY);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, gGohtStalactiteModelDL);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_80B0C570(BossHakugin* this, PlayState* play) {
    BossHakuginFhgFlashUnkStruct* iter;
    s32 i;
    s32 j;
    s16 camYaw;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);

    gSPDisplayList(POLY_XLU_DISP++, gFrozenSteamMaterialDL);
    camYaw = Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)) + 0x8000;
    gDPSetEnvColor(POLY_XLU_DISP++, 1, 1, 1, 128);

    for (i = 0; i < ARRAY_COUNT(this->unk_3158); i++) {
        for (j = 0; j < ARRAY_COUNT(this->unk_3158[0]); j++) {
            iter = &this->unk_3158[i][j];
            if (iter->unk_10 > 0) {
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 0, 0, 0, iter->unk_10);
                gSPSegment(POLY_XLU_DISP++, 0x08,
                           Gfx_TwoTexScroll(play->state.gfxCtx, 0, iter->unk_12 * 3, iter->unk_12 * 15, 32, 64, 1, 0, 0,
                                            32, 32));
                Matrix_Translate(iter->unk_00.x, iter->unk_00.y, iter->unk_00.z, MTXMODE_NEW);
                Matrix_RotateYS(camYaw, MTXMODE_APPLY);
                Matrix_Scale(iter->unk_0C, iter->unk_0C, 1.0f, MTXMODE_APPLY);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, gFrozenSteamModelDL);
            }
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_80B0C7B0(BossHakugin* this, PlayState* play) {
    s32 pad;
    s32 i;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);

    if (this->unk_01C8 > 0.0f) {
        gDPSetEnvColor(POLY_XLU_DISP++, D_80B0EAD0.r, D_80B0EAD0.g, D_80B0EAD0.b, 0);
        gSPDisplayList(POLY_XLU_DISP++, gGohtLightningMaterialDL);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, 255);

        for (i = -1; i <= 1; i += 2) {
            Matrix_SetTranslateRotateYXZ(this->unk_0380.x, this->unk_0380.y, this->unk_0380.z, &this->unk_0374);
            Matrix_RotateYS(0x1400 * i, MTXMODE_APPLY);
            Matrix_RotateXS(0xC00 * i, MTXMODE_APPLY);
            Matrix_RotateZS(this->unk_0198, MTXMODE_APPLY);
            Matrix_Scale(0.62f, 0.62f, this->unk_01D0, MTXMODE_APPLY);
            Matrix_Translate(0.0f, 0.0f, this->unk_01CC * i, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gGohtLightningModelDL);

            Matrix_RotateZS(0x4000, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gGohtLightningModelDL);
        }

        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetEnvColor(POLY_XLU_DISP++, D_80B0EACC.r, D_80B0EACC.g, D_80B0EACC.b, 0);
        Matrix_Translate(this->unk_0380.x, this->unk_0380.y, this->unk_0380.z, MTXMODE_NEW);
        Matrix_ReplaceRotation(&play->billboardMtxF);
        Matrix_Scale(this->unk_01C8, this->unk_01C8, this->unk_01C8, MTXMODE_APPLY);
        Matrix_RotateZS(this->unk_0198, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gGohtLightOrbMaterialDL);
        gSPDisplayList(POLY_XLU_DISP++, gGohtLightOrbModelDL);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_80B0CAF0(BossHakugin* this, PlayState* play) {
    BossHakuginUnkStruct_2618* iter;
    s32 i;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);

    gDPSetEnvColor(POLY_XLU_DISP++, D_80B0EAD0.r, D_80B0EAD0.g, D_80B0EAD0.b, 0);
    gSPDisplayList(POLY_XLU_DISP++, gGohtLightningMaterialDL);

    for (i = 0; i < ARRAY_COUNT(this->unk_2618); i++) {
        iter = &this->unk_2618[i];

        if ((iter->unk_0C > 0) && (iter->unk_0C < 256)) {
            Matrix_SetTranslateRotateYXZ(iter->unk_00.x, iter->unk_00.y, iter->unk_00.z, &iter->unk_0E);
            Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);

            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, iter->unk_0C);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gGohtLightningModelDL);

            Matrix_RotateZS(0x4000, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gGohtLightningModelDL);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_80B0CCD8(BossHakugin* this, PlayState* play2) {
    s32 pad[4];
    PlayState* play = play2;
    s32 end;
    f32 scale;
    s32 i;
    s16 rotZ;
    s32 alpha;
    Vec3f* pos;

    if (this->unk_0192 == 4) {
        i = 9;
        end = this->unk_01AA;
    } else if (this->unk_01AA != 0) {
        i = this->unk_01AA - 1;
        end = 0;
    } else {
        return;
    }

    scale = 30.0f - ((i - 1) * 1.5f);
    alpha = 215 - (i * 15);

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);
    gDPSetEnvColor(POLY_XLU_DISP++, D_80B0EACC.r, D_80B0EACC.g, D_80B0EACC.b, 0);

    rotZ = this->unk_0198;

    gSPDisplayList(POLY_XLU_DISP++, gGohtLightOrbMaterialDL);

    for (; i >= end; i--) {
        pos = &this->unk_3734[i];

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

void func_80B0CF24(BossHakugin* this, PlayState* play) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);
    func_800B8118(&this->actor, play, 0);
    Matrix_Translate(this->unk_0964.dim.pos.x, this->unk_0964.dim.pos.y, this->unk_0964.dim.pos.z, MTXMODE_NEW);
    Matrix_Scale(4.0f, this->unk_01D4, 4.0f, MTXMODE_APPLY);
    Matrix_RotateYS(0xF00, MTXMODE_APPLY);
    Matrix_RotateXS(0x500, MTXMODE_APPLY);
    Matrix_RotateZS(-0x500, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, play->gameplayFrames & 0xFF, 32, 16, 1, 0,
                                (play->gameplayFrames * 2) & 0xFF, 64, 32));
    gDPSetEnvColor(POLY_XLU_DISP++, 0, 50, 100, this->unk_0193);
    gSPDisplayList(POLY_XLU_DISP++, gEffIceFragment3DL);

    CLOSE_DISPS(play->state.gfxCtx);
}

void BossHakugin_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    BossHakugin* this = THIS;
    u8* tex = GRAPH_ALLOC(play->state.gfxCtx, sizeof(u8[64][64]));

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, D_80B0EA88);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          BossHakugin_OverrideLimbDraw, BossHakugin_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);

    Actor_DrawDamageEffects(play, &this->actor, this->bodyPartsPos, ARRAY_COUNT(this->bodyPartsPos), this->unk_01DC,
                            this->unk_01E0, this->unk_01E4, this->unk_0196);

    SkinMatrix_Vec3fMtxFMultXYZ(&play->viewProjectionMtxF, &this->unk_0380, &this->unk_0458);
    SkinMatrix_Vec3fMtxFMultXYZ(&play->viewProjectionMtxF, &this->unk_3734[0], &this->unk_0464);

    if (this->unk_0190 == 0) {
        func_80B06F48(this, play);
    }
    this->unk_0190 = 1;

    if (this->actor.colorFilterTimer != 0) {
        func_800AE5A0(play);
    }

    if (this->actionFunc == func_80B0A8C4) {
        func_80B0E5A4(&this->actor, play);
    } else {
        func_80B0C398(this, play);
    }

    func_80B0C570(this, play);
    func_80B0C7B0(this, play);
    func_80B0CAF0(this, play);
    func_80B0CCD8(this, play);

    if (this->unk_0193 > 0) {
        func_80B0CF24(this, play);
    }

    if (this->actionFunc != func_80B0A8C4) {
        BossHakugin_GenShadowTex(tex, this);
        BossHakugin_DrawShadowTex(tex, this, play);
    }
}

s32 D_80B0EB70[6] = { 1, 2, 3, 3, 2, 1 };
s32 D_80B0EB88[7] = { 2, 3, 4, 4, 4, 3, 2 };
s32 D_80B0EBA4[8] = { 2, 3, 4, 4, 4, 4, 3, 2 };
s32 D_80B0EBC4[0xE] = { 2, 4, 5, 6, 7, 8, 8, 8, 8, 7, 6, 5, 4, 2 };
s32 D_80B0EBFC[0xF] = { 1, -1, 1, 1, 3, 4, 1, 6, 7, 0, 9, 0xA, 0, 0xC, 0xD };
u8 D_80B0EC38[0x18] = { 1, 2, 1, 0, 3, 3, 0, 3, 3, 0, 3, 3, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void BossHakugin_FillShadowTex(BossHakugin* this, u8* tex, f32 weight) {
    s32 index;
    s32 i;
    s32 baseX;
    s32 baseY;
    s32 addY;
    s32 x;
    s32 y = -1;
    Vec3f lerp;
    Vec3f* parentBodyPartPos;
    Vec3f* bodyPartPos;
    Vec3f pos;
    Vec3f startVec;

    for (i = 0; i < 15; i++) {
        if ((weight == 0.0f) || (y = D_80B0EBFC[i]) > BODYPART_NONE) {
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

            if (D_80B0EC38[i] == 2) {
                for (y = 0, addY = -0x180; y < 14; y++, addY += 0x40) {
                    for (x = -D_80B0EBC4[y]; x < D_80B0EBC4[y]; x++) {
                        index = baseX + x + baseY + addY;
                        if ((index >= 0) && (index < 0x1000)) {
                            tex[index] = 255;
                        }
                    }
                }
            } else if (D_80B0EC38[i] == 1) {
                for (y = 0, addY = -0x100; y < 8; y++, addY += 0x40) {
                    for (x = -D_80B0EBA4[y]; x < D_80B0EBA4[y]; x++) {
                        index = baseX + x + baseY + addY;
                        if ((index >= 0) && (index < 0x1000)) {
                            tex[index] = 255;
                        }
                    }
                }
            } else if (D_80B0EC38[i] == 0) {
                for (y = 0, addY = -0xC0; y < 7; y++, addY += 0x40) {
                    for (x = -D_80B0EB88[y]; x < D_80B0EB88[y]; x++) {
                        index = baseX + x + baseY + addY;
                        if ((index >= 0) && (index < 0x1000)) {
                            tex[index] = 255;
                        }
                    }
                }
            } else {
                for (y = 0, addY = -0x80; y < 6; y++, addY += 0x40) {
                    for (x = -D_80B0EB70[y]; x < D_80B0EB70[y]; x++) {
                        index = baseX + x + baseY + addY;
                        if ((index >= 0) && (index < 0x1000)) {
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

    for (i = 0; i < (s32)((sizeof(u8[64][64])) / sizeof(s32)); i++, iter++) {
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

    alpha = (400.0f - this->actor.world.pos.y) * 0.0025f;
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
    gDPLoadTextureBlock(POLY_OPA_DISP++, tex, G_IM_FMT_I, G_IM_SIZ_8b, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD);
    gSPDisplayList(POLY_OPA_DISP++, gShadowModelDL);

    CLOSE_DISPS(gfxCtx);
}

#ifdef NON_MATCHING
// Saved float register alloc. Seems related to spB4.
void func_80B0D9CC(BossHakugin* this) {
    s32 var_s3;
    Vec3f spC8;
    s32 var_s1 = 0xF;
    BossHakuginEffect* var_s0 = this->unk_09F8;
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
    f32 pad;

    for (var_s3 = 4; var_s3 > 0; var_s3--, var_s1 -= 4) {
        spC8.x = this->actor.world.pos.x - (var_s3 * spB4) + (2.3076923f * spB4);
        spC8.y = this->actor.world.pos.y + (85.0f * (4 - var_s3)) + 20.0f;
        spC8.z = this->actor.world.pos.z - (var_s3 * spB0) + (2.3076923f * spB0);

        var_s0->unk_24 = ((var_s3 * 4.5f) + 22.0f) * 0.001f;
        Math_Vec3f_Copy(&var_s0->unk_0, &spC8);

        temp_a0 = var_s1 >> 1;
        if (temp_a0 == 0) {
            break;
        }
        var_s0++;

        temp1 = (var_s3 / (f32)temp_a0);
        temp2 = (spB0 + spB4) * temp1;
        temp3 = (spB0 - spB4) * temp1;

        for (var_v1 = 0; var_v1 < temp_a0; var_v1++, var_s0++) {
            var_s0->unk_0.x = spC8.x + temp2 * (temp_a0 - var_v1);
            var_s0->unk_0.y = spC8.y + var_s3 * spAC;
            var_s0->unk_0.z = spC8.z + temp3 * (temp_a0 - var_v1);
            var_s0->unk_24 = ((var_s3 * 4.5f) + 22.0f) * 0.001f;
        }

        temp4 = (spB4 - spB0) * temp1;
        temp5 = (spB0 + spB4) * temp1;

        for (var_v1 = 0; var_v1 < temp_a0; var_v1++, var_s0++) {
            var_s0->unk_0.x = spC8.x + temp4 * (temp_a0 - var_v1);
            var_s0->unk_0.y = spC8.y - var_s3 * spAC;
            var_s0->unk_0.z = spC8.z + temp5 * (temp_a0 - var_v1);
            var_s0->unk_24 = ((var_s3 * 4.5f) + 22.0f) * 0.001f;
        }
    }

    for (var_s3 = 0; var_s3 < 36; var_s3++) {
        var_s0 = &this->unk_09F8[var_s3];

        var_s0->unk_24 += Rand_ZeroFloat(5.0f) * 0.001f;
        var_s0->unk_1C.x = (s32)Rand_Next() >> 0x10;
        var_s0->unk_1C.y = (s32)Rand_Next() >> 0x10;
        var_s0->unk_1C.z = (s32)Rand_Next() >> 0x10;
        var_s0->unk_C.x = var_s0->unk_0.y;
        var_s0->unk_C.y = 0.0f;
        var_s0->unk_0.y += 850.0f;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_Hakugin/func_80B0D9CC.s")
#endif

void func_80B0DFA8(BossHakugin* this) {
    s32 i;
    BossHakuginEffect* effect;
    ColliderJntSphElement* element;

    for (i = 0; i < 18; i++) {
        effect = &this->unk_09F8[i << 1];
        element = &this->unk_0484.elements[i];

        element->dim.worldSphere.center.x = effect->unk_0.x;
        element->dim.worldSphere.center.y = effect->unk_0.y;
        element->dim.worldSphere.center.z = effect->unk_0.z;
        element->dim.worldSphere.radius = effect->unk_24 * 3000.0f;
        element->info.bumper.dmgFlags = 0xF3CFBBFF;
        element->info.bumperFlags &= ~0x40;

        element->info.elemType = 0;
    }
    for (; i < 19; i++) {
        this->unk_0484.elements[i].info.bumperFlags &= ~1;
        this->unk_0484.elements[i].info.ocElemFlags &= ~1;
    }

    this->unk_0484.base.colType = 0xC;
}

void func_80B0E548(Actor* thisx, PlayState* play2) {
    BossHakugin* this = THIS;
    PlayState* play = play2;

    func_80B0DFA8(this);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk_0484.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk_0484.base);
}

void func_80B0E5A4(Actor* thisx, PlayState* play) {
    BossHakugin* this = THIS;
    s32 i;
    BossHakuginEffect* effect;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    gSPDisplayList(POLY_OPA_DISP++, gGohtRockMaterialDL);

    for (i = 0; i < 36; i++) {
        effect = &this->unk_09F8[i];

        Matrix_SetTranslateRotateYXZ(effect->unk_0.x, effect->unk_0.y, effect->unk_0.z, &effect->unk_1C);
        Matrix_Scale(effect->unk_24, effect->unk_24, effect->unk_24, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gGohtRockModelDL);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
