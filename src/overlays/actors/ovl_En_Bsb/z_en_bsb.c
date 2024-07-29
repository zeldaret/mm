/*
 * File: z_en_bsb.c
 * Overlay: ovl_En_Bsb
 * Description: Captain Keeta
 */

#include "z_en_bsb.h"
#include "objects/object_bsb/object_bsb.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "z64rumble.h"
#include "z64shrink_window.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_2000000)

#define THIS ((EnBsb*)thisx)

void EnBsb_Init(Actor* thisx, PlayState* play);
void EnBsb_Destroy(Actor* thisx, PlayState* play);
void EnBsb_Update(Actor* thisx, PlayState* play);
void EnBsb_Draw(Actor* thisx, PlayState* play);

void func_80C0B290(EnBsb* this, s32 animIndex);
void func_80C0B31C(PlayState* play, EnBsb* this, Vec3f* pos);
s32 func_80C0B888(EnBsb* this, PlayState* play);
void func_80C0B970(EnBsb* this, PlayState* play);
void func_80C0BA58(EnBsb* this, PlayState* play);
s32 func_80C0BC30(EnBsb* this);
void func_80C0BE1C(EnBsb* this, PlayState* play);
void func_80C0BF2C(EnBsb* this);
void func_80C0BFE8(EnBsb* this, PlayState* play);
void func_80C0C0F4(EnBsb* this, PlayState* play);
void func_80C0C238(EnBsb* this, PlayState* play);
void func_80C0C32C(EnBsb* this);
void func_80C0C364(EnBsb* this, PlayState* play);
void func_80C0C430(EnBsb* this);
void func_80C0C484(EnBsb* this, PlayState* play);
void func_80C0C610(EnBsb* this);
void func_80C0C6A8(EnBsb* this, PlayState* play);
void func_80C0C86C(EnBsb* this);
void func_80C0C8EC(EnBsb* this, PlayState* play);
void func_80C0CA28(EnBsb* this, PlayState* play);
void func_80C0CB3C(EnBsb* this, PlayState* play);
void func_80C0CCCC(EnBsb* this);
void func_80C0CD04(EnBsb* this, PlayState* play);
void func_80C0CD90(EnBsb* this);
void func_80C0CDE4(EnBsb* this, PlayState* play);
void func_80C0CF4C(EnBsb* this);
void func_80C0CFDC(EnBsb* this, PlayState* play);
void func_80C0D00C(EnBsb* this);
void func_80C0D10C(EnBsb* this, PlayState* play);
void func_80C0D214(EnBsb* this);
void func_80C0D27C(EnBsb* this, PlayState* play);
void func_80C0D334(EnBsb* this);
void func_80C0D384(EnBsb* this, PlayState* play);
void func_80C0D3C0(EnBsb* this, PlayState* play);
void func_80C0D51C(EnBsb* this, PlayState* play);
void func_80C0D964(EnBsb* this, PlayState* play);
void func_80C0D9B4(EnBsb* this, PlayState* play);
void func_80C0DA58(EnBsb* this);
void func_80C0DB18(EnBsb* this, PlayState* play);
void func_80C0E178(EnBsb* this);
void func_80C0E1C0(EnBsb* this, PlayState* play);
void func_80C0E3B8(EnBsb* this);
void func_80C0E480(EnBsb* this, PlayState* play);
void func_80C0E4FC(EnBsb* this, PlayState* play);
void func_80C0E618(EnBsb* this, PlayState* play);
s32 func_80C0E9CC(EnBsb* this, PlayState* play);
s32 func_80C0EEA0(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
s32 func_80C0F078(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx, Gfx** gfx);
void func_80C0F170(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);
void func_80C0F544(EnBsb* this, Vec3f* pos, Vec3f* velocity, Vec3f* accel, f32 scale, s16 arg1);
void func_80C0F640(EnBsb* this, PlayState* play);
void func_80C0F758(EnBsb* this, PlayState* play);

f32 D_80C0F8D0 = 0.0f;

static ColliderJntSphElementInit sJntSphElementsInit[7] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 10, { { 1000, 400, 0 }, 40 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x04, 0x08 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 9, { { 0, 700, 200 }, 35 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 6, { { 100, 600, 0 }, 35 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 3, { { 400, 200, 0 }, 40 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 13, { { 700, -100, 0 }, 35 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 16, { { 200, 300, 0 }, 30 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 19, { { 200, 300, 0 }, 30 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HIT6,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sJntSphElementsInit),
    sJntSphElementsInit,
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xD),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xE),
    /* Zora boomerang */ DMG_ENTRY(0, 0xF),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0xD),
    /* Sword          */ DMG_ENTRY(1, 0xD),
    /* Goron pound    */ DMG_ENTRY(1, 0xD),
    /* Fire arrow     */ DMG_ENTRY(0, 0x2),
    /* Ice arrow      */ DMG_ENTRY(0, 0x3),
    /* Light arrow    */ DMG_ENTRY(0, 0x4),
    /* Goron spikes   */ DMG_ENTRY(0, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0xC),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(1, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xD),
    /* Spin attack    */ DMG_ENTRY(1, 0xD),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xD),
};

ActorInit En_Bsb_InitVars = {
    /**/ ACTOR_EN_BSB,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ OBJECT_BSB,
    /**/ sizeof(EnBsb),
    /**/ EnBsb_Init,
    /**/ EnBsb_Destroy,
    /**/ EnBsb_Update,
    /**/ EnBsb_Draw,
};

AnimationHeader* D_80C0FA20[] = {
    &object_bsb_Anim_0086BC, &object_bsb_Anim_00CD88, &object_bsb_Anim_000400, &object_bsb_Anim_0065D8,
    &object_bsb_Anim_000FF0, &object_bsb_Anim_000C50, &object_bsb_Anim_006C48, &object_bsb_Anim_001390,
    &object_bsb_Anim_002AF4, &object_bsb_Anim_002590, &object_bsb_Anim_007120, &object_bsb_Anim_0043A4,
    &object_bsb_Anim_007B18, &object_bsb_Anim_001CD8, &object_bsb_Anim_003E1C, &object_bsb_Anim_003238,
    &object_bsb_Anim_00606C, &object_bsb_Anim_005440, &object_bsb_Anim_004E2C, &object_bsb_Anim_004894,
    &object_bsb_Anim_004208, &object_bsb_Anim_00D3CC, &object_bsb_Anim_004510, &object_bsb_Anim_001F90,
    &object_bsb_Anim_00C790,
};

u8 D_80C0FA84[] = {
    2, 0, 2, 0, 0, 2, 0, 0, 2, 2, 0, 2, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 2, 2, 2,
};

Vec3f D_80C0FAA0 = { 0.0f, 8.0f, 0.0f };

Vec3f D_80C0FAAC = { 0.0f, -1.5f, 0.0f };

Vec3s D_80C0FAB8 = { 0x2EE0, -0x2710, 0xB5C8 };

Vec3s D_80C0FAC0 = { -0x2710, 0x2710, -0x2710 };

Vec3f D_80C0FAC8[] = { { -80.0f, 475.0f, -2330.0f }, { 0.0f, 0.0f, 0.0f } };

void func_80C0B290(EnBsb* this, s32 animIndex) {
    this->unk_02D8 = animIndex;
    this->unk_02C4 = Animation_GetLastFrame(D_80C0FA20[animIndex]);
    Animation_Change(&this->skelAnime, D_80C0FA20[this->unk_02D8], 1.0f, 0.0f, this->unk_02C4,
                     D_80C0FA84[this->unk_02D8], -2.0f);
}

void func_80C0B31C(PlayState* play, EnBsb* this, Vec3f* pos) {
    Vec3f spCC;
    Vec3f spC0;
    Vec3f spB4;
    Vec3f spA8 = D_80C0FAA0;
    Vec3f sp9C = D_80C0FAAC;
    f32 randAngle;
    f32 temp_fs0;
    s32 i;
    u32 pad[4];

    randAngle = (Rand_ZeroOne() - 0.5f) * 12.56f;
    spCC.y = this->actor.floorHeight;
    spCC.x = Math_SinF(randAngle) * 5.0f + pos->x;
    spCC.z = Math_CosF(randAngle) * 5.0f + pos->z;
    sp9C.x = Rand_CenteredFloat(1.0f) * 0.5f;
    sp9C.z = Rand_CenteredFloat(1.0f) * 0.5f;
    spA8.y += (Rand_ZeroOne() - 0.5f) * 15.0f;

    EffectSsHahen_Spawn(play, &spCC, &spA8, &sp9C, 0, Rand_ZeroOne() * 5.0f + 10.0f, -1, 10, NULL);
    func_800BBFB0(play, &spCC, 20.0f, 1, 300, 10, 5);

    if (!this->unk_02AE) {
        this->unk_02AE = true;

        for (i = 0; i < 10; i++) {
            if (!(i & 1)) {
                Math_Vec3f_Copy(&spCC, &this->unk_0304);
            } else {
                Math_Vec3f_Copy(&spCC, &this->unk_02F8);
            }
            spCC.x += Rand_CenteredFloat(5.0f);
            spCC.y += Rand_CenteredFloat(5.0f);
            spCC.z += Rand_CenteredFloat(5.0f);
            spC0.y = -1.0f;
            spB4.x = (Rand_ZeroOne() - 0.5f) * 4.0f;
            spB4.y = (Rand_ZeroOne() * 10.0f) + 4.0f;
            spB4.z = (Rand_ZeroOne() - 0.5f) * 4.0f;
            temp_fs0 = Rand_CenteredFloat(1.0f) * 0.002f + 0.005f;
            func_80C0F544(this, &spCC, &spB4, &spC0, temp_fs0, (s32)Rand_ZeroFloat(10.0f) + 30);
        }
    }
}

void EnBsb_Init(Actor* thisx, PlayState* play) {
    EnBsb* this = THIS;
    s32 csId;
    s32 i;

    Actor_SetScale(&this->actor, 0.04f);
    this->unk_02CA = 0xFF;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;

    if (this->actor.params & 0x8000) {
        SkelAnime_Init(play, &this->skelAnime, &object_bsb_Skel_00C3E0, &object_bsb_Anim_004894, this->unk_0188,
                       this->unk_0206, 21);
        this->unk_02B0 = this->actor.params & 0xFF;
        func_80C0E3B8(this);
        return;
    }

    this->actor.colChkInfo.damageTable = &sDamageTable;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 0.0f);
    SkelAnime_Init(play, &this->skelAnime, &object_bsb_Skel_00C3E0, &object_bsb_Anim_0086BC, this->unk_0188,
                   this->unk_0206, 21);

    this->unk_02B6 = (this->actor.params >> 7) & 0x1F;
    this->unk_02B8 = this->actor.params & 0x7F;
    this->unk_02BA = this->actor.world.rot.z & 0x7F;
    this->actor.colChkInfo.health = 0x18;
    this->actor.hintId = 0x21;
    this->actor.gravity = -2.0f;

    Collider_InitAndSetJntSph(play, &this->unk_0F34, &this->actor, &sJntSphInit, this->unk_0F54);

    if (this->unk_02B6 == 0x1F) {
        Actor_Kill(&this->actor);
        return;
    }

    csId = this->actor.csId;

    for (i=0; csId != CS_ID_NONE;) { 
        this->unk_02CC[i] = csId, csId = CutsceneManager_GetAdditionalCsId(csId); 
        i++;
    }

    this->actor.targetMode = 0xA;

    if (WEEKEVENTREG(0x17) & 4) {
        Actor_Kill(&this->actor);
    } else {
        func_80C0BF2C(this);
    }
}

void EnBsb_Destroy(Actor* thisx, PlayState* play) {
    EnBsb* this = THIS;

    if (this->unk_02B0 == 0) {
        Audio_RestorePrevBgm();
        Collider_DestroyJntSph(play, &this->unk_0F34);
    }
    if (CutsceneManager_GetCurrentCsId() == this->unk_02CC[3]) {
        CutsceneManager_Stop(this->unk_02CC[3]);
    }
}

s32 func_80C0B888(EnBsb* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 temp_v0;

    if (this->unk_02DC == 0) {
        temp_v0 = ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->unk_02BC));
        if (temp_v0 < (s16)(BREG(1) + 0x4000) &&
            (fabsf(this->actor.world.pos.y - player->actor.world.pos.y) < 20.0f) &&
            (this->actor.xzDistToPlayer < 200.0f)) {
            this->unk_02DC = 1;
            Audio_PlayBgm_StorePrevBgm(0x38);
            return 1;
        }
    } else {
        return 1;
    }
    return 0;
}

void func_80C0B970(EnBsb* this, PlayState* play) {
    s16 var_a2;

    if (Animation_OnFrame(&this->skelAnime, 8.0f) || Animation_OnFrame(&this->skelAnime, 14.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_KTIA_WALK);

        var_a2 = (700.0f - this->actor.xzDistToPlayer) * 0.01f;

        if (var_a2 >= 5) {
            var_a2 = 4;
        }

        if (var_a2 > 0) {
            Actor_RequestQuakeAndRumble(&this->actor, play, var_a2, 2);
        }

        if (Animation_OnFrame(&this->skelAnime, 8.0f)) {
            func_80C0B31C(play, this, &this->unk_0304);
        } else {
            func_80C0B31C(play, this, &this->unk_02F8);
        }
    }
}

void func_80C0BA58(EnBsb* this, PlayState* play) {
    s16 var_v1;

    if (Animation_OnFrame(&this->skelAnime, 2.0f) || Animation_OnFrame(&this->skelAnime, 4.0f) ||
        Animation_OnFrame(&this->skelAnime, 6.0f) || Animation_OnFrame(&this->skelAnime, 8.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_KTIA_WALK);
        Actor_RequestQuake(play, BREG(10) + 1, BREG(11) + 2);
        if (Animation_OnFrame(&this->skelAnime, 4.0f) || Animation_OnFrame(&this->skelAnime, 8.0f)) {
            func_80C0B31C(play, this, &this->unk_0304);
        } else {
            func_80C0B31C(play, this, &this->unk_02F8);
        }
    }

    if (this->actor.xzDistToPlayer < BREG(7) + 400.0f) {
        var_v1 = BREG(8) + 160.0f - this->actor.xzDistToPlayer * 0.3f;

        if (var_v1 > 70) {
            var_v1 = 70;
        } else if (var_v1 < 0) {
            var_v1 = 0;
        }

        if (Animation_OnFrame(&this->skelAnime, 1.0f)) {
            Rumble_Override(BREG(15), BREG(12) + var_v1, BREG(13) + 0xF, BREG(14) + 70);
        }
    }
}

s32 func_80C0BC30(EnBsb* this) {
    if (this->actor.world.pos.z < -2180.0f && this->actor.world.pos.z > -2470.0f &&
        fabsf(this->actor.world.pos.y - this->actor.home.pos.y) < 30.0f) {
        Vec3s sp38 = D_80C0FAB8;
        Vec3s sp30 = D_80C0FAC0;

        Math_SmoothStepToS(&this->unk_0316.x, sp38.x, 1, 0x7D0, 0);
        Math_SmoothStepToS(&this->unk_0316.y, sp38.y, 1, 0x7D0, 0);
        Math_SmoothStepToS(&this->unk_0316.z, sp38.z, 1, 0x7D0, 0);
        Math_SmoothStepToS(&this->unk_0310.x, sp30.x, 1, 0x7D0, 0);
        Math_SmoothStepToS(&this->unk_0310.y, sp30.y, 1, 0x7D0, 0);
        Math_SmoothStepToS(&this->unk_0310.z, sp30.z, 1, 0x7D0, 0);
        return true;
    } else if (this->unk_0316.z != 0) {
        Math_SmoothStepToS(&this->unk_0316.x, 0, 1, 0x7D0, 0);
        Math_SmoothStepToS(&this->unk_0316.y, 0, 1, 0x7D0, 0);
        Math_SmoothStepToS(&this->unk_0316.z, 0, 1, 0x7D0, 0);
        Math_SmoothStepToS(&this->unk_0310.x, 0, 1, 0x7D0, 0);
        Math_SmoothStepToS(&this->unk_0310.y, 0, 1, 0x7D0, 0);
        Math_SmoothStepToS(&this->unk_0310.z, 0, 1, 0x7D0, 0);
    }

    return false;
}

void func_80C0BE1C(EnBsb* this, PlayState* play) {
    if (this->unk_111A != 0) {
        Math_ApproachF(&this->unk_1128.x, this->unk_1140.x, 0.5f, 30.0f);
        Math_ApproachF(&this->unk_1128.y, this->unk_1140.y, 0.5f, 30.0f);
        Math_ApproachF(&this->unk_1128.z, this->unk_1140.z, 0.5f, 30.0f);
        Math_ApproachF(&this->unk_1134.x, this->unk_114C.x, 0.5f, 30.0f);
        Math_ApproachF(&this->unk_1134.y, this->unk_114C.y, 0.5f, 30.0f);
        Math_ApproachF(&this->unk_1134.z, this->unk_114C.z, 0.5f, 30.0f);
        Math_ApproachF(&this->unk_1120, this->unk_1124, 0.5f, 10.0f);

        Play_SetCameraAtEye(play, this->unk_111A, &this->unk_1134, &this->unk_1128);
        Play_SetCameraFov(play, this->unk_111A, this->unk_1120);

        ShrinkWindow_Letterbox_SetSizeTarget(27);
    }
}

void func_80C0BF2C(EnBsb* this) {
    s32 i;

    this->unk_0F34.elements->dim.modelSphere.radius = 110;
    this->unk_0F34.elements->dim.modelSphere.center.x = 300;
    this->unk_0F34.elements->dim.modelSphere.center.y = 400;
    this->unk_0F34.base.colType = 0xC;

    for (i = 0; i < 7; i++) {
        this->unk_0F34.elements[i].info.elemType = 2;
    }

    this->actor.flags |= 0x08000000;
    WEEKEVENTREG(0x55) &= 0xBF;
    this->unk_02B4 = 0;
    this->actionFunc = func_80C0BFE8;
}

void func_80C0BFE8(EnBsb* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 temp_v0 = ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y));

    if ((temp_v0 < 0x4300) && !(this->actor.xzDistToPlayer > 300.0f)) {
        if (player->stateFlags2 & 0x08000000) {
            if (this->unk_0290 == 0) {
                Audio_PlaySfx(NA_SE_SY_TRE_BOX_APPEAR);
                this->unk_0290 = 1;
            }
        } else {
            this->unk_0290 = 0;
        }

        if ((play->msgCtx.ocarinaMode == 3) && (play->msgCtx.lastPlayedSong == 0)) {
            play->msgCtx.ocarinaMode = 4;
            Actor_ChangeCategory(play, &play->actorCtx, &this->actor, 9);
            func_80C0C0F4(this, play);
        }
    }
}

void func_80C0C0F4(EnBsb* this, PlayState* play) {
    s32 i;

    this->actor.flags |= 0x02000000;
    this->unk_02A4 = 0;
    this->unk_0F34.elements->dim.modelSphere.radius = 40;
    this->unk_0F34.elements->dim.modelSphere.center.x = 1000;
    this->unk_0F34.elements->dim.modelSphere.center.y = 400;
    this->unk_0F34.base.colType = 0xA;

    for (i = 0; i < 7; i++) {
        this->unk_0F34.elements[i].info.elemType = 0;
    }

    this->unk_02AE = false;

    Actor_PlaySfx(&this->actor, NA_SE_EN_STALTU_UP);

    func_80C0B290(this, 0);

    if (CutsceneManager_IsNext(this->unk_02CC[0]) == 0) {
        CutsceneManager_Queue(this->unk_02CC[0]);
        this->unk_02B4 = 1;
        this->actionFunc = func_80C0C238;
    } else {
        CutsceneManager_StartWithPlayerCs(this->unk_02CC[0], &this->actor);

        this->actor.flags &= ~0x08000000;

        Flags_SetSwitch(play, this->unk_02B8);

        this->unk_02A4 = 1;
        this->unk_02B4 = 1;
        this->actionFunc = func_80C0C238;
    }
}

void func_80C0C238(EnBsb* this, PlayState* play) {
    func_80C0BC30(this);

    if (this->unk_02A4 == 0) {
        if (CutsceneManager_IsNext(this->unk_02CC[0]) == 0) {
            CutsceneManager_Queue(this->unk_02CC[0]);
            return;
        }
        CutsceneManager_StartWithPlayerCs(this->unk_02CC[0], &this->actor);
        this->actor.flags &= ~0x08000000;
        Flags_SetSwitch(play, this->unk_02B8);
        this->unk_02A4 = 1;
    }

    if (this->unk_02A4 == 1) {
        if (!(play->gameplayFrames & 1)) {
            func_80C0B31C(play, this, &this->actor.world.pos);
        }
        Math_ApproachF(&this->actor.shape.shadowScale, 25.0f, 1.0f, 2.5f);
        if (this->unk_02C4 <= this->skelAnime.curFrame) {
            func_80C0C32C(this);
        }
    }
}

void func_80C0C32C(EnBsb* this) {
    this->unk_02A4 = 0;
    func_80C0B290(this, 1);
    this->actionFunc = func_80C0C364;
}

void func_80C0C364(EnBsb* this, PlayState* play) {
    f32 sp2C;
    s16 sp2A = this->actor.yawTowardsPlayer;
    s32 var_v1;

    this->unk_0288 = SubS_GetPathByIndex(play, this->unk_02B6, 31);

    func_80C0BC30(this);

    if (this->unk_0288 != NULL) {
        sp2A = SubS_GetDistSqAndOrientPath(this->unk_0288, this->unk_028C, &this->actor.world.pos, &sp2C);
    }

    this->actor.world.rot.y -= 750;

    var_v1 = ABS_ALT((s16)(this->actor.world.rot.y - sp2A));

    func_80C0B970(this, play);

    if (var_v1 < 0x1000) {
        this->unk_02BC = this->actor.world.rot.y;
        func_80C0C430(this);
    }
}

void func_80C0C430(EnBsb* this) {
    this->unk_02A4 = 0;
    if (this->unk_02D8 != 1) {
        func_80C0B290(this, 1);
    }
    this->unk_0294 = 70;
    this->unk_02B4 = 2;
    this->actionFunc = func_80C0C484;
}

void func_80C0C484(EnBsb* this, PlayState* play) {
    f32 sp34;
    s16 var_a1;
    s16 temp_v1;

    func_80C0BC30(this);

    if (func_80C0B888(this, play) != 0) {
        this->actor.flags &= ~0x02000000;
        func_80C0C86C(this);
        return;
    }

    var_a1 = this->actor.yawTowardsPlayer;

    if (this->unk_0294 == 1) {
        this->actor.flags &= ~0x02000000;
    }

    if (this->unk_0288 != NULL) {
        var_a1 = SubS_GetDistSqAndOrientPath(this->unk_0288, this->unk_028C, &this->actor.world.pos, &sp34);
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, var_a1, 2, 0x2EE, 5);

    temp_v1 = ABS_ALT((s16)(this->actor.world.rot.y - var_a1));

    if (temp_v1 < 0x1000) {
        this->unk_02BC = this->actor.world.rot.y;
        this->actor.speed = 3.5f;
        if (this->unk_02AF == 0) {
            this->unk_02AF = 1;
            Audio_PlayBgm_StorePrevBgm(3);
        }
    }

    func_80C0B970(this, play);

    if (sp34 < 25.0f) {
        if (this->unk_0288 != NULL) {
            this->unk_028C = this->unk_028C + 1;
            if (this->unk_028C >= this->unk_0288->count) {
                this->unk_028C = this->unk_028C - 1;
                func_80C0DA58(this);
            }
        }
    }
}

void func_80C0C610(EnBsb* this) {
    this->unk_02A4 = 0;
    this->actor.speed = 0.0f;

    func_80C0B290(this, 2);
    Actor_PlaySfx(&this->actor, NA_SE_EN_KITA_DAMAGE);

    this->unk_0294 = 0;

    if (this->unk_02DC != 0) {
        this->unk_0294 = 40;
        Actor_PlaySfx(&this->actor, NA_SE_EN_COMMON_FREEZE);
        Actor_SetColorFilter(&this->actor, 0, 255, 0, 40);
    }

    this->unk_02B4 = 3;
    this->actionFunc = func_80C0C6A8;
}

void func_80C0C6A8(EnBsb* this, PlayState* play) {
    f32 sp34 = this->skelAnime.curFrame;

    func_80C0B888(this, play);

    if (((this->unk_02DC == 0) ||
         ((this->unk_02DC != 0) && (this->unk_02D8 == 2) && (this->unk_02C4 <= sp34) && (this->unk_0294 == 0))) &&
        ((this->unk_0324 == 11) || (this->unk_0324 == 10)) && (this->unk_0322 != 0)) {
        Actor_SpawnIceEffects(play, &this->actor, this->unk_0330, 17, 2, this->unk_032C, 0.4f);
        this->unk_0322 = 0;
        this->unk_0324 = 0;
    }

    if ((this->unk_02D8 == 2) && (this->unk_02C4 <= sp34) && (this->unk_0294 == 0)) {
        if (this->unk_02DC == 0) {
            func_80C0B290(this, 3);
            return;
        } else {
            func_80C0C86C(this);
            return;
        }
    }

    if (this->unk_02D8 == 3) {
        Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 1, 2000, 0);
        if ((Animation_OnFrame(&this->skelAnime, 7.0f) != 0) || (Animation_OnFrame(&this->skelAnime, 15.0f) != 0)) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_KTIA_PAUSE_K);
        }

        if (this->unk_02C4 <= sp34) {
            this->unk_02A4++;
            if (this->unk_02A4 >= 2) {
                func_80C0C430(this);
            }
        }
    }
}

void func_80C0C86C(EnBsb* this) {
    this->unk_02A4 = 0;
    this->unk_02DC = 1;
    this->actor.speed = 2.0f;
    func_80C0B290(this, 4);
    this->unk_0294 = Rand_S16Offset(0, 30);
    WEEKEVENTREG(85) |= 0x40;
    this->unk_02B4 = 4;
    this->actionFunc = func_80C0C8EC;
}

void func_80C0C8EC(EnBsb* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (func_80C0BC30(this) == 0) {
        Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 1, 3000, 0);
    }

    if ((this->unk_0294 == 0) && (fabsf(player->actor.world.pos.y - this->actor.world.pos.y) >= 100.0f) &&
        (this->actor.xzDistToPlayer < 500.0f)) {
        func_80C0CA28(this, play);
        return;
    }

    func_80C0BA58(this, play);

    if ((this->unk_0294 == 0) && (Actor_IsFacingPlayer(&this->actor, 4551) != 0) &&
        (fabsf(this->actor.world.pos.y - player->actor.world.pos.y) < 20.0f) && (this->actor.xzDistToPlayer < 180.0f)) {
        func_80C0CD90(this);
    }
}

void func_80C0CA28(EnBsb* this, PlayState* play) {
    this->unk_02A4 = 0;
    this->actor.speed = 0.0f;

    Actor_PlaySfx(&this->actor, NA_SE_EN_KITA_ATTACK_W);

    this->actor.velocity.y = 85.0f;
    this->actor.gravity = -8.0f;

    func_80C0B290(this, 11);
    Actor_SpawnFloorDustRing(play, &this->actor, &this->unk_0304, 5.0f, 10, 8.0f, 1000, 100, 1);
    Actor_SpawnFloorDustRing(play, &this->actor, &this->unk_02F8, 5.0f, 10, 8.0f, 1000, 100, 1);
    Actor_PlaySfx(&this->actor, NA_SE_EN_TEKU_JUMP);

    this->actor.flags |= 0x08000000;
    this->unk_02B4 = 5;
    this->actionFunc = func_80C0CB3C;
}

void func_80C0CB3C(EnBsb* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (this->actor.velocity.y > 0.0f) {
        Math_ApproachF(&this->actor.world.pos.x, player->actor.world.pos.x, 0.5f, 30.0f);
        Math_ApproachF(&this->actor.world.pos.z, player->actor.world.pos.z, 0.5f, 30.0f);
        return;
    }

    this->actor.gravity = -8.0f;

    if (this->unk_02D8 != 22) {
        func_80C0B290(this, 22);
    }

    if ((fabsf(player->actor.world.pos.y - this->actor.world.pos.y) < 40.0f) && (this->actor.xzDistToPlayer < 70.0f) &&
        (player->invincibilityTimer == 0)) {
        func_800B8D50(play, &this->actor, 2.0f, this->actor.yawTowardsPlayer, 5.0f, 16);
    }

    if (this->actor.bgCheckFlags & 1) {
        Actor_SpawnFloorDustRing(play, &this->actor, &this->actor.world.pos, this->actor.shape.shadowScale, 10, 8.0f,
                                 2000, 100, 1);
        Actor_RequestQuakeAndRumble(&this->actor, play, 10, 10);
        Actor_PlaySfx(&this->actor, NA_SE_EN_EYEGOLE_ATTACK);
        func_80C0CCCC(this);
    }
}

void func_80C0CCCC(EnBsb* this) {
    func_80C0B290(this, 23);
    this->actionFunc = func_80C0CD04;
}

void func_80C0CD04(EnBsb* this, PlayState* play) {
    f32 var_0 = this->skelAnime.curFrame;

    if ((this->unk_02D8 == 24) && (var_0 >= this->unk_02C4)) {
        this->actor.flags &= ~0x08000000;
        this->actor.gravity = -2.0f;
        this->unk_0294 = 10;
        func_80C0C86C(this);
    } else if (this->unk_02D8 == 23) {
        func_80C0B290(this, 24);
    }
}

void func_80C0CD90(EnBsb* this) {
    this->unk_02A4 = 0;
    this->actor.speed = 0.0f;
    Actor_PlaySfx(&this->actor, NA_SE_EN_KITA_ATTACK_W);
    func_80C0B290(this, 5);
    this->unk_02B4 = 6;
    this->actionFunc = func_80C0CDE4;
}

void func_80C0CDE4(EnBsb* this, PlayState* play) {
    f32 sp3C;
    f32 curFrame = this->skelAnime.curFrame;
    Vec3f sp34;
    Player* temp_v0 = GET_PLAYER(play);
    f32 x;
    f32 y;
    f32 z;
    f32 temp_fv0;
    s16 temp_v1;

    sp34.x = this->unk_0F34.elements[1].info.bumper.hitPos.x;
    sp34.y = this->unk_0F34.elements[1].info.bumper.hitPos.y;
    sp34.z = this->unk_0F34.elements[1].info.bumper.hitPos.z;

    x = sp34.x - temp_v0->actor.world.pos.x;
    y = sp34.y - temp_v0->actor.world.pos.y;
    z = sp34.z - temp_v0->actor.world.pos.z;

    temp_fv0 = sqrtf((SQ(x) + SQ(y)) + SQ(z));

    if ((this->unk_0F34.base.atFlags & AT_BOUNCED) ||
        ((temp_v0->stateFlags1 & 0x400000) && (temp_fv0 <= 70.0f) &&
         (temp_v1 = (temp_v0->actor.shape.rot.y - this->actor.shape.rot.y) + 0x8000, (temp_v1 < 0x2000)) &&
         (temp_v1 > -0x2000))) {
        this->unk_0F34.base.atFlags &= ~(AT_BOUNCED | AT_HIT);
        EffectSsHitmark_SpawnFixedScale(play, 3, &sp34);
        Actor_PlaySfx(&this->actor, NA_SE_IT_SHIELD_BOUND);
        func_80C0CF4C(this);
        return;
    }

    if (this->unk_02C4 <= curFrame) {
        func_80C0C86C(this);
    }
}

void func_80C0CF4C(EnBsb* this) {
    this->actor.speed = 0.0f;
    this->unk_02A4 = 0;
    Animation_Change(&this->skelAnime, &object_bsb_Anim_000C50, -1.0f, this->skelAnime.curFrame - 1.0f, 0.0f, 2, 0.0f);
    this->unk_0294 = 10;
    Actor_PlaySfx(&this->actor, NA_SE_EN_KTIA_PAUSE_K);
    this->unk_02B4 = 7;
    this->actionFunc = func_80C0CFDC;
}

void func_80C0CFDC(EnBsb* this, PlayState* play) {
    if (this->unk_0294 == 0) {
        func_80C0C86C(this);
    }
}

void func_80C0D00C(EnBsb* this) {
    Vec3f vec;

    this->unk_02A4 = 0;
    this->actor.speed = 0.0f;

    if (this->actor.world.pos.z < -1300.0f) {
        Matrix_RotateYS(((s32)Rand_CenteredFloat(16384.0f) + this->actor.yawTowardsPlayer), MTXMODE_NEW);
        Matrix_MultVecZ(-30.0f, &vec);
    } else {
        Matrix_RotateYS(this->actor.yawTowardsPlayer, MTXMODE_NEW);
        Matrix_MultVecZ(-50.0f, &vec);
        vec.z = 0.0f;
    }

    Math_Vec3f_Copy(&this->unk_0298, &vec);
    Actor_PlaySfx(&this->actor, NA_SE_EN_KITA_DAMAGE);
    func_80C0B290(this, 7);

    this->unk_02AE = true;
    this->unk_02B4 = 8;
    this->actionFunc = func_80C0D10C;
}

void func_80C0D10C(EnBsb* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;

    if (((this->unk_0324 == 11) || (this->unk_0324 == 10)) && (this->unk_0322 != 0)) {
        Actor_SpawnIceEffects(play, &this->actor, this->unk_0330, 17, 2, this->unk_032C, 0.4f);
        this->unk_0322 = 0;
        this->unk_0324 = 0;
    }

    func_80C0B31C(play, this, &this->unk_0304);
    func_80C0B31C(play, this, &this->unk_02F8);

    if (this->unk_02C4 <= curFrame) {
        if ((this->actor.world.pos.z > -1300.0f) || (this->actor.colChkInfo.health < 10)) {
            func_80C0CA28(this, play);
            return;
        }
        func_80C0C86C(this);
    }
}

void func_80C0D214(EnBsb* this) {
    this->unk_0294 = 40;
    this->actor.speed = 0.0f;
    Actor_SetColorFilter(&this->actor, 0, 120, 0, 40);
    Actor_PlaySfx(&this->actor, NA_SE_EN_COMMON_FREEZE);
    this->unk_02B4 = 10;
    this->actionFunc = func_80C0D27C;
}

void func_80C0D27C(EnBsb* this, PlayState* play) {
    if (this->unk_0324 == 11 && this->unk_0322 != 0 && this->unk_0322 < 60) {
        this->unk_0324 = 10;
    }

    if ((this->unk_0324 == 11 || this->unk_0324 == 10) && this->unk_0322 != 0) {
        Actor_SpawnIceEffects(play, &this->actor, this->unk_0330, 17, 2, this->unk_032C, 0.4f);
        this->unk_0322 = 0;
        this->unk_0324 = 0;
    }

    if (this->unk_0294 == 0) {
        func_80C0C86C(this);
    }
}

void func_80C0D334(EnBsb* this) {
    this->actor.speed = 0.0f;
    Actor_PlaySfx(&this->actor, NA_SE_EN_KITA_LAUGH_K);
    func_80C0B290(this, 6);
    this->unk_02B4 = 11;
    this->actionFunc = func_80C0D384;
}

void func_80C0D384(EnBsb* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;

    if (this->unk_02C4 <= curFrame) {
        func_80C0C86C(this);
    }
}

void func_80C0D3C0(EnBsb* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    Audio_RestorePrevBgm();

    this->unk_02A4 = 0;
    this->unk_02A8 = 0;
    this->unk_02AC = 0x4000;
    this->actor.speed = 0.0f;

    player->actor.world.rot.y = player->actor.shape.rot.y = this->actor.yawTowardsPlayer + 0x8000;

    this->unk_1128.x = this->unk_1140.x = Math_SinS(this->actor.yawTowardsPlayer) * 300.0f + this->unk_02E0.x;
    this->unk_1128.y = this->unk_1140.y = this->unk_02E0.y - 30.0f;
    this->unk_1128.z = this->unk_1140.z = Math_CosS(this->actor.yawTowardsPlayer) * 300.0f + this->unk_02E0.z;

    this->unk_1134.x = this->unk_114C.x = Math_SinS(this->actor.yawTowardsPlayer) * 10.0f + this->unk_02E0.x;
    this->unk_1134.y = this->unk_114C.y = this->unk_02E0.y - 10.0f;
    this->unk_1134.z = this->unk_114C.z = Math_CosS(this->actor.yawTowardsPlayer) * 10.0f + this->unk_02E0.z;

    this->unk_1124 = 60.0f;
    func_80C0B290(this, 2);
    this->unk_02B4 = 9;
    this->actionFunc = func_80C0D51C;
    this->actor.velocity.y = 30.0f;
}

void func_80C0D51C(EnBsb* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;
    s32 var_v0;
    f32 sx;
    f32 sy;
    Player* player;

    if (((this->unk_0324 == 11) || (this->unk_0324 == 10)) && (this->unk_0322 != 0)) {
        Actor_SpawnIceEffects(play, &this->actor, this->unk_0330, 17, 2, this->unk_032C, 0.4f);
        this->unk_0322 = 0;
        this->unk_0324 = 0;
    }

    if (this->unk_02A4 == 0) {
        if (CutsceneManager_IsNext(this->unk_02CC[1]) == 0) {
            CutsceneManager_Queue(this->unk_02CC[1]);
            return;
        }
        CutsceneManager_StartWithPlayerCs(this->unk_02CC[1], &this->actor);
        Player_SetCsActionWithHaltedActors(play, &this->actor, 81);
        this->unk_111A = CutsceneManager_GetCurrentSubCamId(this->actor.csId);
        this->unk_02A4 = 1;
    }

    if (this->unk_02A8 == 2) {
        s32 pad;
        sx = Math_SinS(this->actor.world.rot.y) * 380.f;
        sy = Math_CosS(this->actor.world.rot.y) * 380.f;

        this->unk_1140.x = sx + this->unk_02E0.x;
        this->unk_1140.y = this->unk_02E0.y + 30.0f;
        this->unk_1140.z = sy + this->unk_02E0.z;

        this->unk_114C.x = Math_SinS(this->actor.world.rot.y) * 10.0f + this->unk_02E0.x;
        this->unk_114C.y = this->unk_02E0.y - 63.0f;
        this->unk_114C.z = Math_CosS(this->actor.world.rot.y) * 10.0f + this->unk_02E0.z;
    } else {
        this->unk_114C.x = Math_SinS(this->actor.world.rot.y) * 10.0f + this->unk_02E0.x;
        this->unk_114C.y = this->unk_02E0.y - 10.0f;
        this->unk_114C.z = Math_CosS(this->actor.world.rot.y) * 10.0f + this->unk_02E0.z;
    }

    if (this->unk_02A8 == 0) {
        this->actor.world.rot.y += this->unk_02AC;
        Math_SmoothStepToS(&this->unk_02AC, 0x1000, 1, 0x1F4, 0);
        var_v0 = ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->actor.world.rot.y));

        if (this->actor.velocity.y < -5.0f && var_v0 < 0x1000) {
            this->unk_02A8 = 1;
        }
    } else {
        Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 1, 0x3E8, 0);
        var_v0 = ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->actor.world.rot.y));
    }

    if ((this->unk_02A8 != 0) && (var_v0 < 0x100) && (this->actor.world.pos.y < (this->actor.floorHeight + 30.0f))) {
        this->unk_02A8 = 2;
        if (this->unk_02D8 < 9) {
            player = GET_PLAYER(play);
            func_80C0B290(this, 9);
            Player_SetCsActionWithHaltedActors(play, &this->actor, 4);
            player->actor.velocity.y = 5.0f;
            Actor_SpawnFloorDustRing(play, &this->actor, &this->actor.world.pos, this->actor.shape.shadowScale - 20.0f,
                                     0x14, 8.0f, 1000, 100, 1);
            Actor_PlaySfx(&this->actor, NA_SE_EN_EYEGOLE_ATTACK);
            Actor_RequestQuakeAndRumble(&this->actor, play, 4, 10);
        } else if ((this->unk_02D8 == 9) && (curFrame >= this->unk_02C4)) {
            func_80C0B290(this, 0xA);
            Player_SetCsActionWithHaltedActors(play, &this->actor, 0x51);
        }
    }
    func_80C0BE1C(this, play);
    if ((this->unk_02A4 != 0) && (this->unk_02A8 != 0) && (this->unk_02D8 == 0xA) && (curFrame >= this->unk_02C4)) {
        func_80C0D964(this, play);
    }
}

void func_80C0D964(EnBsb* this, PlayState* play) {
    this->unk_02A4 = 0;
    this->unk_02A8 = 0;
    this->actor.textId = 0x1535;
    Message_StartTextbox(play, this->actor.textId, &this->actor);
    this->actionFunc = func_80C0D9B4;
}

void func_80C0D9B4(EnBsb* this, PlayState* play) {
    if ((Message_GetState(&play->msgCtx) == 5) && (Message_ShouldAdvance(play) != 0)) {
        Message_CloseTextbox(play);
        play->nextEntrance = Entrance_CreateFromSpawn(5);
        gSaveContext.nextCutsceneIndex = 0;
        play->transitionTrigger = 0x14;
        play->transitionType = 2;
        gSaveContext.nextTransitionType = 3;
        this->unk_111A = 0;
    }
}

void func_80C0DA58(EnBsb* this) {
    this->unk_1118 = this->unk_111C = 0;
    this->actor.speed = 0.0f;
    this->unk_1120 = 0.0f;
    this->unk_02A4 = 0;
    this->unk_111A = 0;
    // clang-format off
    this->unk_1140.x = -480.0f; this->unk_1128.x = -480.0f;
    this->unk_1140.y = 375.0f; this->unk_1128.y = 375.0f;
    this->unk_1140.z = -1630.0f; this->unk_1128.z = -1630.0f;
    this->unk_114C.x = -360.0f; this->unk_1134.x = -360.0f; this->unk_1124 = 60.0f; if (1);
    this->unk_114C.y = 500.0f; this->unk_1134.y = 500.0f; 
    this->unk_114C.z = -2250.0f; this->unk_1134.z = -2250.0f;
    // clang-format on
    this->unk_1118 = 0;
    WEEKEVENTREG(85) |= 0x40;
    this->unk_02B4 = 13;
    this->actionFunc = func_80C0DB18;
}

void func_80C0DB18(EnBsb* this, PlayState* play) {
    Vec3f sp64 = D_80C0FAC8[0];
    f32 curFrame = this->skelAnime.curFrame;
    s32 pad[3];
    s16 sp52;
    char pad2[2];

    if (this->unk_02A4 == 0) {
        if (CutsceneManager_IsNext(this->unk_02CC[3]) == 0) {
            CutsceneManager_Queue(((void*)0, this->unk_02CC)[3]);
            return;
        }
        CutsceneManager_StartWithPlayerCs(this->unk_02CC[3], &this->actor);
        func_80C0B290(this, 1);
        Player_SetCsActionWithHaltedActors(play, &this->actor, 7);
        this->unk_111A = CutsceneManager_GetCurrentSubCamId(this->actor.csId);
        this->unk_02A4 = 1;
    }

    if (this->unk_02D8 == 1) {
        func_80C0B970(this, play);
    }

    this->unk_1128.x = -480.0f;
    this->unk_1140.x = -480.0f;
    this->unk_1128.y = 375.0f;
    this->unk_1140.y = 375.0f;
    this->unk_1128.z = -1630.0f;
    this->unk_1140.z = -1630.0f;
    this->unk_1134.x = -360.0f;
    this->unk_114C.x = -360.0f;
    this->unk_1134.y = 500.0f;
    this->unk_114C.y = 500.0f;
    this->unk_114C.z = -2250.0f;
    this->unk_1134.z = -2250.0f;

    func_80C0BE1C(this, play);

    switch (this->unk_1118) {
        case 0:
            Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &sp64), 1, 2000, 0);
            Math_ApproachF(&this->actor.world.pos.x, sp64.x, 0.5f, fabsf(Math_SinS(this->actor.world.rot.y) * 3.2f));
            Math_ApproachF(&this->actor.world.pos.z, sp64.z, 0.5f, fabsf(Math_CosS(this->actor.world.rot.y) * 3.2f));
            if (sqrtf(SQ(this->actor.world.pos.x - sp64.x) + SQ(this->actor.world.pos.z - sp64.z)) < 3.0f) {
                this->unk_028C = this->unk_0288->count - 1;
                if (SubS_CopyPointFromPath(this->unk_0288, this->unk_028C, &this->unk_02EC) != 0) {
                    this->unk_02EC.y = this->actor.world.pos.y;
                    func_80C0B290(this, 3);
                    this->unk_1118++;
                }
            }
            break;

        case 1:
            if ((Animation_OnFrame(&this->skelAnime, 7.0f) != 0) || (Animation_OnFrame(&this->skelAnime, 15.0f) != 0)) {
                Actor_PlaySfx(&this->actor, NA_SE_EN_KTIA_PAUSE_K);
            }

            Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_02EC), 1,
                               0x7D0, 0);

            if (this->unk_02C4 <= curFrame) {
                this->unk_111C++;
                if (this->unk_111C >= 3) {
                    func_80C0B290(this, 1);
                    this->unk_111C = 0;
                    this->unk_1118++;
                }
            }
            break;

        case 2:
            sp52 = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_1128);
            Math_SmoothStepToS(&this->actor.world.rot.y, sp52, 1, 2000, 0);

            if (ABS_ALT((s16)(this->actor.world.rot.y - sp52)) < 0x100) {
                Actor_PlaySfx(&this->actor, NA_SE_EN_KITA_LAUGH_K);
                func_80C0B290(this, 21);
                this->unk_1118++;
                Message_StartTextbox(play, 0x1541, &this->actor);
            }
            break;

        case 3:
            if ((Message_GetState(&play->msgCtx) == 5) && Message_ShouldAdvance(play)) {
                Message_CloseTextbox(play);
                func_80C0B290(this, 1);
                this->unk_1118++;
            }
            break;

        case 4:
            sp64.x = -100.0f;
            sp52 = Math_Vec3f_Yaw(&this->actor.world.pos, &sp64);
            Math_SmoothStepToS(&this->actor.world.rot.y, sp52, 1, 2000, 0);

            if (ABS_ALT((s16)(this->actor.world.rot.y - sp52)) < 0x100) {
                Actor_PlaySfx(&this->actor, NA_SE_EN_TEKU_JUMP);
                this->actor.velocity.y = 20.0f;
                this->actor.speed = 3.0f;
                func_80C0B290(this, 11);
                this->unk_1118++;
            }
            break;

        case 5:
            if (this->actor.world.pos.y < (this->actor.home.pos.y + 30.0f)) {
                Actor_SpawnFloorDustRing(play, &this->actor, &this->actor.world.pos,
                                         this->actor.shape.shadowScale - 20.0f, 0x14, 8.0f, 1000, 100, 1);
                this->actor.speed = 0.0f;
                Actor_PlaySfx(&this->actor, NA_SE_EN_GOMA_DOWN);
                Actor_RequestQuakeAndRumble(&this->actor, play, 4, 10);
                this->unk_1118++;
            }
            break;

        case 6:
            this->actor.world.rot.y += 0x2000;

            if (!(play->gameplayFrames & 7)) {
                Math_Vec3f_Copy(&sp64, &this->actor.world.pos);
                sp64.x += Rand_CenteredFloat(40.0f);
                sp64.z += Rand_CenteredFloat(40.0f);
                Actor_SpawnFloorDustRing(play, &this->actor, &sp64, Rand_ZeroFloat(10.0f) + 5.0f, Rand_S16Offset(1, 3),
                                         4.0f, 1000, 100, 1);
            }

            Math_ApproachF(&this->actor.shape.yOffset, -7000.0f, 0.5f, 200.0f);

            if (this->actor.shape.yOffset < -6999.0f) {
                CutsceneManager_Stop(this->unk_02CC[3]);
                Actor_Kill(&this->actor);
            }
            break;
    }
}

void func_80C0E178(EnBsb* this) {
    this->actor.flags |= 0x08000000;
    this->unk_02AE = false;
    this->unk_02A4 = 0;
    this->actor.flags &= ~1;
    this->unk_02B4 = 14;
    this->actionFunc = func_80C0E1C0;
    this->actor.speed = 0.0f;
}

void func_80C0E1C0(EnBsb* this, PlayState* play) {
    s32 i;
    f32 curFrame = this->skelAnime.curFrame;

    if (this->unk_02D8 == 16) {
        if (Animation_OnFrame(&this->skelAnime, 30.0f) != 0) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_KITA_SALUTE);
        } else if ((curFrame < 30.0f) && ((play->csCtx.curFrame == 472) || (play->csCtx.curFrame == 487))) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_KTIA_WALK);
        }
    }

    if ((this->unk_02D8 == 18) && (play->csCtx.curFrame == 897)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_KITA_SALUTE);
    }

    if (this->unk_02A4 == 0) {
        if (WEEKEVENTREG(0x17) & 4) {
            if (1) {}
            D_80C0F8D0 = this->skelAnime.curFrame;

            for (i = 0; i < 17; i++) {
                EnBsb* newActor = (EnBsb*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_BSB, this->actor.world.pos.x,
                                        this->actor.world.pos.y, this->actor.world.pos.z, this->actor.shape.rot.x,
                                        this->actor.shape.rot.y, this->actor.shape.rot.z, this->unk_03FC[i] + 0x8000);
                if (newActor != NULL) {
                    newActor->unk_02C0 = this->unk_0330[i].y;
                }
            }

            this->unk_02A4 = 1;
            this->actor.draw = NULL;
        }
    }

    if (play->csCtx.curFrame == 950) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_GOMA_DOWN);
    }

    if (func_80C0E9CC(this, play) == 0) {
        Actor_Kill(&this->actor);
    }
}

void func_80C0E3B8(EnBsb* this) {
    this->actor.gravity = 0.0f;
    this->actor.speed = 0.0f;
    this->unk_02AE = false;
    this->unk_02A4 = 0;

    Math_Vec3s_Copy(&this->unk_031C, &gZeroVec3s);

    this->actor.flags |= 0x08000000;
    this->actor.flags &= ~1;

    Animation_Change(&this->skelAnime, &object_bsb_Anim_004894, 1.0f, D_80C0F8D0,
                     Animation_GetLastFrame(&object_bsb_Anim_004894), 2, 0.0f);
    SkelAnime_Update(&this->skelAnime);

    this->unk_02B4 = 15;
    this->actionFunc = func_80C0E480;
}

void func_80C0E480(EnBsb* this, PlayState* play) {
    if (this->unk_02C0 != 0.0f) {
        if (this->unk_02C0 <= this->actor.world.pos.y) {
            this->unk_02C0 = this->actor.world.pos.y - 40.0f;
        }
        this->unk_0294 = 2;
        this->unk_02CA = 0xFF;
        this->actionFunc = func_80C0E4FC;
        this->unk_02C0 = this->actor.home.pos.y + (this->actor.world.pos.y - this->unk_02C0);
    }
}

void func_80C0E4FC(EnBsb* this, PlayState* play) {
    if (this->unk_0294 != 0) {
        if (this->unk_0294 == 1) {
            this->actor.speed = 0.0f;
            this->actor.velocity.y = 10.0f;
        }
    } else {
        if (this->actor.velocity.y <= -11.0f) {
            this->unk_02CA -= 0x30;
            if (this->unk_02CA < 0) {
                this->unk_02CA = 0;
            }
        }
        Math_ApproachF(&this->actor.gravity, -3.0f, 0.5f, 0.5f);
        Math_ApproachF(&this->actor.velocity.y, -10.0f, 0.5f, 0.5f);
        this->unk_031C.x += 0x320;
        this->unk_031C.y += 0x320;
        this->unk_031C.z += 0x320;
        if ((this->actor.gravity != 0.0f) && (this->actor.world.pos.y <= this->unk_02C0)) {
            Actor_Kill(&this->actor);
        }
    }
}

void func_80C0E618(EnBsb* this, PlayState* play) {
    s32 var_s0 = 0;
    Vec3f sp48;
    s32 i;

    if ((this->unk_02B4 != 0) && (this->unk_02B4 != 1) && (this->unk_02B4 != 9) && (this->unk_02B4 != 12) &&
        (this->unk_02B4 != 13) && (this->unk_02B4 != 5) && ((this->unk_02B4 != 8) || (this->unk_02DC == 0))) {
        if (!(this->unk_0F34.base.atFlags & 4)) {
            if (this->unk_0F34.elements[1].info.toucherFlags & 2) {
                this->unk_0F34.elements[1].info.toucherFlags &= 0xFFFD;
                if ((this->unk_02B4 != 11) && (this->unk_02B4 != 7)) {
                    func_80C0D334(this);
                }
            }
        }
        if (this->unk_0F34.base.acFlags & 2) {
            switch (this->actor.colChkInfo.damageEffect) {
                case 14:
                    if (this->unk_02DC != 0) {
                        var_s0 = 1;
                        break;
                    }

                case 15:
                    var_s0 = -1;
                    break;

                case 13:
                    if (this->unk_02DC == 0) {
                        this->unk_02DC = 1;
                        Audio_PlayBgm_StorePrevBgm(0x38);
                    }
                    var_s0 = 1;
                    break;

                case 12:
                    if (this->unk_02DC == 0) {
                        this->unk_02DC = 1;
                        Audio_PlayBgm_StorePrevBgm(0x38);
                    }
                    break;

                case 1:
                    if (this->unk_02DC != 0) {
                        func_80C0D214(this);
                    }
                    break;

                case 2:
                    this->unk_0322 = 0x28;
                    this->unk_0324 = 0;
                    var_s0 = -1;
                    break;

                case 3:
                    if (((this->unk_0324 != 11) && (this->unk_0324 != 10)) || (this->unk_0322 == 0)) {
                        this->unk_0322 = 0x50;
                        this->unk_0324 = 0xB;
                        var_s0 = -1;
                        this->unk_0328 = 0.0f;
                        this->unk_032C = 1.5f;
                    }
                    break;

                case 4:
                    this->unk_0322 = 0x28;
                    this->unk_0324 = 0x14;
                    Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.focus.pos.x,
                                this->actor.focus.pos.y, this->actor.focus.pos.z, 0, 0, 0, 4);
                    var_s0 = -1;
                    break;

                case 5:
                    this->unk_0322 = 0x28;
                    this->unk_0324 = 0x20;

                    if (this->unk_02DC == 0) {
                        this->unk_02DC = 1;
                        Audio_PlayBgm_StorePrevBgm(0x38);
                    } else {
                        func_80C0D214(this);
                    }

                    break;
            }
        }

        if (var_s0 == -1) {
            if (this->unk_02B4 != 3) {
                func_80C0C610(this);
            }
        } else if (var_s0 == 1) {
            Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_RED, 255, 0, 8);
            Actor_ApplyDamage(&this->actor);
            if (this->actor.colChkInfo.health <= 0) {
                Enemy_StartFinishingBlow(play, &this->actor);
                Actor_PlaySfx(&this->actor, NA_SE_EN_KITA_DEAD);
                this->actor.flags |= 0x08000000;
                this->actor.flags &= ~1;
                Actor_ChangeCategory(play, &play->actorCtx, &this->actor, 4U);
                func_80C0D3C0(this, play);
            } else {
                for (i = 0; i < 0x7; i++) {
                    if (this->unk_0F34.elements[i].info.bumperFlags & 2) {
                        sp48.x = this->unk_0F34.elements[i].info.bumper.hitPos.x;
                        sp48.y = this->unk_0F34.elements[i].info.bumper.hitPos.y;
                        sp48.z = this->unk_0F34.elements[i].info.bumper.hitPos.z;
                        CollisionCheck_BlueBlood(play, NULL, &sp48);
                    }
                }
                func_80C0D00C(this);
            }
        }
    }
}

s32 func_80C0E9CC(EnBsb* this, PlayState* play) {
    s32 cueChannel;

    if (Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_532) != 0) {
        cueChannel = Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_532);
        if (this->unk_0296 != play->csCtx.actorCues[cueChannel]->id) {
            if (this->unk_02B4 != 14) {
                func_80C0E178(this);
            }

            switch (play->csCtx.actorCues[cueChannel]->id) {
                case 1:
                    func_80C0B290(this, 13);
                    break;

                case 2:
                    if ((this->unk_02D8 != 14) && (this->unk_02D8 != 15)) {
                        func_80C0B290(this, 14);
                    }
                    break;

                case 3:
                    if ((this->unk_02D8 != 16) && (this->unk_02D8 != 17)) {
                        func_80C0B290(this, 16);
                    }
                    break;

                case 4:
                    if ((this->unk_02D8 != 18) && (this->unk_02D8 != 19)) {
                        func_80C0B290(this, 18);
                    }
                    break;

                case 5:
                    WEEKEVENTREG(23) |= 4;
                    Actor_PlaySfx(&this->actor, NA_SE_EN_KITA_BREAK);
                    break;

                case 6:
                    Flags_SetSwitch(play, this->unk_02BA);
                    Actor_PlaySfx(&this->actor, NA_SE_SY_PIECE_OF_HEART);
                    break;
            }
        }
        this->unk_0296 = play->csCtx.actorCues[cueChannel]->id;
        Cutscene_ActorTranslateAndYaw(&this->actor, play, cueChannel);
        return 1;
    } else {
        return 0;
    }
}

void EnBsb_Update(Actor* thisx, PlayState* play) {
    EnBsb* this = THIS;
    s32 pad;
    f32 curFrame;

    DECR(this->unk_0292);

    DECR(this->unk_0294);

    DECR(this->unk_0322);

    if ((this->unk_02B4 != 0) && (this->unk_02B4 != 0xA) && !(gSaveContext.save.saveInfo.weekEventReg[0x17] & 4) &&
        (this->unk_02B0 == 0)) {
        SkelAnime_Update(&this->skelAnime);
    }

    this->actionFunc(this, play);
    Actor_MoveWithGravity(&this->actor);

    if (this->unk_02B0 == 0) {
        func_80C0E618(this, play);
        if ((func_80C0E9CC(this, play) == 0) && (this->unk_02B4 != 0xE)) {
            this->actor.shape.rot.y = this->actor.world.rot.y;
            this->actor.focus.pos.x = Math_SinS(this->actor.world.rot.y) * 20.0f + this->unk_02E0.x;
            this->actor.focus.pos.y = this->unk_02E0.y;
            this->actor.focus.pos.z = (Math_CosS(this->actor.world.rot.y) * 20.0f) + this->unk_02E0.z;
            Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
            if (this->actor.bgCheckFlags & 1) {
                if (this->actor.world.pos.z < -1300.0f) {
                    this->actor.world.pos.z += this->unk_0298.z;
                }
                this->actor.world.pos.x += this->unk_0298.x;
                Math_ApproachZeroF(&this->unk_0298.x, 1.0f, 2.0f);
                Math_ApproachZeroF(&this->unk_0298.z, 1.0f, 2.0f);
            }
        } else {
            curFrame = this->skelAnime.curFrame;
            if ((this->unk_02D8 == 0xE) && (this->unk_02C4 <= curFrame)) {
                func_80C0B290(this, 0xF);
            }
            if ((this->unk_02D8 == 0x10) && (this->unk_02C4 <= curFrame)) {
                func_80C0B290(this, 0x11);
            }
            if ((this->unk_02D8 == 0x12) && (this->unk_02C4 <= curFrame)) {
                func_80C0B290(this, 0x13);
            }
        }

        Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 60.0f, 40.0f, 0x1D);
        func_80C0F640(this, play);

        if (func_80C0E9CC(this, play) == 0) {
            if ((this->unk_02B4 != 9) && (this->unk_02B4 != 0xE) && (this->unk_02B4 != 0xF)) {
                CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk_0F34.base);
                CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk_0F34.base);
                if ((this->unk_02B4 == 6) || (this->unk_02B4 == 4)) {
                    CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk_0F34.base);
                }
            }
        }
    }
}

s32 func_80C0EEA0(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnBsb* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    if (this->unk_02B0 == 0) {
        if (limbIndex == 11) {
            if (this->unk_02B4 == 0) {
                *dList = NULL;
            } else {
                gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, this->unk_02CA);
            }
        } else {
            gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, 255);
        }

        if (limbIndex == 7) {
            rot->x += this->unk_0310.x;
            rot->y += this->unk_0310.y;
            rot->z += this->unk_0310.z;
        }

        if (limbIndex == 4) {
            rot->x += this->unk_0316.x;
            rot->y += this->unk_0316.y;
            rot->z += this->unk_0316.z;
        }
    } else if (limbIndex != this->unk_02B0) {
        *dList = NULL;
    } else if ((limbIndex == 2) || (limbIndex == 3) || (limbIndex == 4) || (limbIndex == 5) || (limbIndex == 6) ||
               (limbIndex == 7) || (limbIndex == 8) || (limbIndex == 9) || (limbIndex == 10) || (limbIndex == 12) ||
               (limbIndex == 13) || (limbIndex == 15) || (limbIndex == 16) || (limbIndex == 17) || (limbIndex == 18) ||
               (limbIndex == 19) || (limbIndex == 20)) {
        rot->x += this->unk_031C.x;
        rot->y += this->unk_031C.y;
        rot->z += this->unk_031C.z;
    }

    CLOSE_DISPS(play->state.gfxCtx);

    return 0;
}

s32 func_80C0F078(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnBsb* this = THIS;

    if (limbIndex != this->unk_02B0) {
        *dList = NULL;
    } else if (limbIndex != this->unk_02B0) {
        *dList = NULL;
    } else if ((limbIndex == 2) || (limbIndex == 3) || (limbIndex == 4) || (limbIndex == 5) || (limbIndex == 6) ||
               (limbIndex == 7) || (limbIndex == 8) || (limbIndex == 9) || (limbIndex == 10) || (limbIndex == 12) ||
               (limbIndex == 13) || (limbIndex == 15) || (limbIndex == 16) || (limbIndex == 17) || (limbIndex == 18) ||
               (limbIndex == 19) || (limbIndex == 20)) {
        rot->x += this->unk_031C.x;
        rot->y += this->unk_031C.y;
        rot->z += this->unk_031C.z;
    }

    return 0;
}

void func_80C0F170(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnBsb* this = THIS;

    if (this->unk_02B0 == 0) {
        if (limbIndex == 10) {
            Matrix_MultVec3f(&gZeroVec3f, &this->unk_02E0);
        }
        if (limbIndex == 17) {
            Matrix_MultVec3f(&gZeroVec3f, &this->unk_0304);
        }
        if (limbIndex == 20) {
            Matrix_MultVec3f(&gZeroVec3f, &this->unk_02F8);
        }

        if ((limbIndex == 2) || (limbIndex == 3) || (limbIndex == 4) || (limbIndex == 5) || (limbIndex == 6) ||
            (limbIndex == 7) || (limbIndex == 8) || (limbIndex == 9) || (limbIndex == 10) || (limbIndex == 12) ||
            (limbIndex == 13) || (limbIndex == 15) || (limbIndex == 16) || (limbIndex == 17) || (limbIndex == 18) ||
            (limbIndex == 19) || (limbIndex == 20)) {
            Matrix_MultZero(&this->unk_0330[this->unk_0440]);
            this->unk_03FC[this->unk_0440] = limbIndex;

            this->unk_0440++;
            if (this->unk_0440 >= 17) {
                this->unk_0440 = 0;
            }
        }
    }
    Collider_UpdateSpheres(limbIndex, &this->unk_0F34);
}

void EnBsb_Draw(Actor* thisx, PlayState* play) {
    EnBsb* this = (EnBsb*)thisx;
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_80C0F758(this, play);

    if (this->unk_02CA == 255) {
        Gfx_SetupDL25_Opa(play->state.gfxCtx);
        Scene_SetRenderModeXlu(play, 0, 1);

        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, this->unk_02CA);

        SkelAnime_DrawOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, func_80C0EEA0, func_80C0F170,
                          &this->actor);

        if (this->unk_0322 != 0) {
            f32 sp3C = this->unk_0322 * 0.05f;

            if (this->unk_0324 == 11 || this->unk_0324 == 10) {
                this->unk_0328 += 0.3f;
                if (this->unk_0328 > 1.0f) {
                    this->unk_0328 = 1.0f;
                }
                Math_ApproachF(&this->unk_032C, this->unk_0328, 0.1f, 0.04f);
            } else {
                this->unk_0328 = 0.8f;
                this->unk_032C = 0.8f;
            }

            Actor_DrawDamageEffects(play, &this->actor, this->unk_0330, 17, this->unk_0328, this->unk_032C, sp3C,
                                    this->unk_0324);
        }
    } else {
        Gfx_SetupDL25_Xlu(play->state.gfxCtx);
        Scene_SetRenderModeXlu(play, 1, 2);

        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, this->unk_02CA);

        POLY_XLU_DISP = SkelAnime_Draw(play, this->skelAnime.skeleton, this->skelAnime.jointTable, func_80C0F078, NULL,
                                       &this->actor, POLY_XLU_DISP++);
    }
    CLOSE_DISPS(play->state.gfxCtx);
}

void func_80C0F544(EnBsb* this, Vec3f* pos, Vec3f* velocity, Vec3f* accel, f32 scale, s16 arg1) {
    EnBsbUnkStruct* var_s0 = this->unk_0444;
    s16 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_0444); i++, var_s0++) {
        if (var_s0->unk_00 == 0) {
            var_s0->unk_00 = 1;
            var_s0->pos = *pos;
            var_s0->velocity = *velocity;
            var_s0->accel = *accel;
            var_s0->scale = scale;
            var_s0->unk_34 = arg1;
            var_s0->rot.x = Rand_CenteredFloat(30000.0f);
            var_s0->rot.y = Rand_CenteredFloat(30000.0f);
            var_s0->rot.z = Rand_CenteredFloat(30000.0f);
            return;
        }
    }
}

void func_80C0F640(EnBsb* this, PlayState* play) {
    s32 i;
    EnBsbUnkStruct* var_v0 = this->unk_0444;

    for (i = 0; i < ARRAY_COUNT(this->unk_0444); i++, var_v0++) {
        if (var_v0->unk_00 != 0) {
            var_v0->rot.x += 0x100;
            var_v0->rot.z += 0x130;
            var_v0->pos.x += var_v0->velocity.x;
            var_v0->pos.y += var_v0->velocity.y;
            var_v0->pos.z += var_v0->velocity.z;

            var_v0->velocity.y += var_v0->accel.y;

            if (var_v0->unk_34 != 0) {
                var_v0->unk_34--;
            } else {
                var_v0->unk_00 = 0;
            }
        }
    }
}

void func_80C0F758(EnBsb* this, PlayState* play) {
    GraphicsContext* gfxCtx = play->state.gfxCtx;
    s32 i;
    EnBsbUnkStruct* var_s0;

    OPEN_DISPS(play->state.gfxCtx);
    var_s0 = this->unk_0444;
    Gfx_SetupDL25_Opa(play->state.gfxCtx);

    for (i = 0; i < ARRAY_COUNT(this->unk_0444); i++, var_s0++) {
        if (var_s0->unk_00 != 0) {
            Matrix_Push();
            Matrix_Translate(var_s0->pos.x, var_s0->pos.y, var_s0->pos.z, MTXMODE_NEW);
            Matrix_RotateXS(var_s0->rot.x, MTXMODE_APPLY);
            Matrix_RotateYS(var_s0->rot.y, MTXMODE_APPLY);
            Matrix_RotateZS(var_s0->rot.z, MTXMODE_APPLY);
            Matrix_Scale(var_s0->scale, var_s0->scale, var_s0->scale, MTXMODE_APPLY);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x80, 255, 255, 255, 255);

            gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, 255);

            gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_06AB30);

            Matrix_Pop();
        }
    }
    CLOSE_DISPS(play->state.gfxCtx);
}

