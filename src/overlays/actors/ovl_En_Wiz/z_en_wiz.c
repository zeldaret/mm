/*
 * File: z_en_wiz.c
 * Overlay: ovl_En_Wiz
 * Description: Wizzrobe
 */

#include "z_en_wiz.h"

#define FLAGS                                                                                            \
    (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_1000 | ACTOR_FLAG_100000 | \
     ACTOR_FLAG_8000000 | ACTOR_FLAG_80000000)

#define THIS ((EnWiz*)thisx)

void EnWiz_Init(Actor* thisx, PlayState* play);
void EnWiz_Destroy(Actor* thisx, PlayState* play);
void EnWiz_Update(Actor* thisx, PlayState* play);
void EnWiz_Draw(Actor* thisx, PlayState* play);

void func_80A46280(EnWiz* this, PlayState* play);
void func_80A462F8(EnWiz* this, PlayState* play);
void func_80A46414(EnWiz* this, PlayState* play);
void func_80A468CC(EnWiz* this, PlayState* play);
void func_80A46990(EnWiz* this, PlayState* play);

extern FlexSkeletonHeader D_0600B320;
extern UNK_TYPE D_0600211C;
extern AnimationHeader D_060025F0;
extern AnimationHeader D_060066C0;
extern AnimationHeader D_06002458;
extern AnimationHeader D_060060E8;
extern AnimationHeader D_060007B0;
extern AnimationHeader D_06002218;
extern Gfx D_0407D590[];
extern Gfx D_06001860[];

const ActorInit En_Wiz_InitVars = {
    ACTOR_EN_WIZ,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WIZ,
    sizeof(EnWiz),
    (ActorFunc)EnWiz_Init,
    (ActorFunc)EnWiz_Destroy,
    (ActorFunc)EnWiz_Update,
    (ActorFunc)EnWiz_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[10] = {
static ColliderJntSphElementInit D_80A48B50[10] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0x01000202, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A48CB8 = {
    {
        COLTYPE_HIT2,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(D_80A48B50),
    D_80A48B50, // sJntSphElementsInit,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A48CC8 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0xF7CFFFFF, 0x08, 0x04 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 35, 130, 0, { 0, 0, 0 } },
};

// static DamageTable sDamageTable = {
static DamageTable D_80A48CF4 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_D_06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(3, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

// static DamageTable sDamageTable = {
static DamageTable D_80A48D14 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_D_06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(3, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

static AnimationHeader* D_80A48D34[] = {
    &D_060066C0, &D_060025F0, &D_06002458, &D_060060E8, &D_060007B0, &D_06002218,
};

static u8 D_80A48D4C[] = {
    ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE,
};

static Vec3f D_80A48D54 = { 0.006f, 0.006f, 0.006f };

static Color_RGBA8 D_80A48D60 = { 250, 250, 250, 255 };

static Color_RGBA8 D_80A48D64 = { 180, 180, 180, 255 };

void EnWiz_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnWiz* this = THIS;

    SkelAnime_InitFlex(play, &this->skelAnime, &D_0600B320, &D_060066C0, this->jointTable, this->morphTable, 20);
    SkelAnime_InitFlex(play, &this->skelAnime2, &D_0600B320, &D_060066C0, this->jointTable2, this->morphTable2, 20);
    Actor_SetScale(&this->actor, 0.0f);
    this->unk_3C4 = 0;
    this->unk_3C2 = 0xFF;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.targetMode = 3;
    this->unk_450 = 1.0f;
    this->actor.shape.yOffset = 700.0f;
    Collider_InitAndSetJntSph(play, &this->unk_454, &this->actor, &D_80A48CB8, this->unk_474);
    Collider_InitAndSetCylinder(play, &this->unk_6F4, &this->actor, &D_80A48CC8);
    this->unk_388 = Rand_S16Offset(0, 7);
    this->switchFlag = this->actor.params & 0x7F;
    this->unk_74A = (this->actor.params >> 8) & 0xFF;

    if (this->switchFlag == 0x7F) {
        this->switchFlag = -1;
    }

    if ((this->unk_74A == 0) || (this->unk_74A == 2)) {
        this->actor.colChkInfo.damageTable = &D_80A48CF4;
        this->actor.colChkInfo.health = 8;
        this->actor.flags &= ~ACTOR_FLAG_100000;
    } else {
        this->actor.colChkInfo.damageTable = &D_80A48D14;
        this->actor.colChkInfo.health = 6;
    }

    if ((this->switchFlag >= 0) && (Flags_GetSwitch(play, this->switchFlag))) {
        Actor_MarkForDeath(&this->actor);
    } else {
        this->actor.hintId = 0x4B;
        this->unk_748 = 0x309;
        this->unk_454.elements->dim.modelSphere.radius = 0;
        this->unk_454.elements->dim.scale = 0.0f;
        this->unk_454.elements->dim.modelSphere.center.x = 0;
        this->unk_454.elements->dim.modelSphere.center.y = 0;
        this->unk_454.elements->dim.modelSphere.center.z = 0;
        this->actionFunc = func_80A46280;
    }
}

void EnWiz_Destroy(Actor* thisx, PlayState* play) {
    s32 pad;
    EnWiz* this = THIS;

    Collider_DestroyCylinder(play, &this->unk_6F4);
    Collider_DestroyJntSph(play, &this->unk_454);
    if (this->unk_74A != 2) {
        func_801A2ED8();
    }
}

void EnWiz_ChangeAnim(EnWiz* this, s32 animIndex, s32 arg2) {
    this->endFrame = Animation_GetLastFrame(D_80A48D34[animIndex]);
    Animation_Change(&this->skelAnime, D_80A48D34[animIndex], 1.0f, 0.0f, this->endFrame, D_80A48D4C[animIndex], -2.0f);
    if (arg2 != 0) {
        Animation_Change(&this->skelAnime2, D_80A48D34[animIndex], 1.0f, 0.0f, this->endFrame, D_80A48D4C[animIndex],
                         -2.0f);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A456A0.s")

void func_80A45CD8(EnWiz* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A45CD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A460A4.s")

void func_80A46280(EnWiz* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetFlag(this->actor.cutscene, &this->actor);
        this->unk_74E = ActorCutscene_GetCurrentSubCamId(this->actor.cutscene);
        this->actor.flags |= ACTOR_FLAG_100000;
        func_80A462F8(this, play);
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_80A462F8(EnWiz* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 i;
    s16 angle;

    this->unk_3B0 = 1;

    if (this->unk_3B2 == 0) {
        func_80A45CD8(this, play);

        if (this->unk_3CB != 0) {
            angle = Math_Vec3f_Yaw(&this->actor.world.pos, &player->actor.world.pos);
            this->actor.shape.rot.y = angle;
            this->actor.world.rot.y = angle;
            for (i = 0; i < this->unk_740; i++) {
                this->unk_894[i].y = Math_Vec3f_Yaw(&this->unk_81C[i], &player->actor.world.pos);
            }

            EnWiz_ChangeAnim(this, 0, true);
            this->unk_3CA = 0;
            this->unk_3C6 = 0xFF;
            Math_Vec3f_Copy(&this->unk_414, &this->actor.world.pos);

            if (this->unk_3B6 == 0) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_UNARI);
            } else {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_VOICE - SFX_FLAG);
            }
        }

        this->actionFunc = func_80A46414;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A4668C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46764.s")

void func_80A468CC(EnWiz* this, PlayState* play) {
    s16 temp_v0 = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);

    if (!ActorCutscene_GetCanPlayNext(temp_v0)) {
        ActorCutscene_SetIntentToPlay(temp_v0);
    } else {
        ActorCutscene_StartAndSetFlag(temp_v0, &this->actor);
        this->unk_74E = ActorCutscene_GetCurrentSubCamId(temp_v0);
        this->actor.flags |= ACTOR_FLAG_100000;
        EnWiz_ChangeAnim(this, 2, false);
        this->unk_3B0 = 2;
        this->unk_744 = 1;
        this->unk_3BC = 0;
        Math_SmoothStepToS(&this->unk_3C2, 0xFF, 1, 5, 0);
        this->actionFunc = func_80A46990;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46990.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46C88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46CC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46DDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46E24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A47000.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A470D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A47298.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A473B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A4767C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A476C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A477E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/EnWiz_Update.s")

void func_80A47FCC(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    Vec3f sp24 = { 0.0f, 0.0f, 0.0f };
    EnWiz* this = THIS;

    if (limbIndex == 9) {
        sp24.x = 7300.0f;
        sp24.y = -1500.0f;
        if (this->unk_3B0 != 9) {
            sp24.y = 0.0f;
            sp24.x = 5300.0f;
        }

        Matrix_Translate(0.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_MultVec3f(&sp24, &this->unk_3D8);
    }

    Collider_UpdateSpheres(limbIndex, &this->unk_454);

    if ((limbIndex == 1) || (limbIndex == 2) || (limbIndex == 3) || (limbIndex == 4) || (limbIndex == 6) ||
        (limbIndex == 7) || (limbIndex == 0xA) || (limbIndex == 0xB) || (limbIndex == 0xC) || (limbIndex == 0xF) ||
        (limbIndex == 0x12) || (limbIndex == 0xD)) {
        Matrix_MultZero(&this->bodyPartsPos[this->bodyPartsPosIndex]);
        this->bodyPartsPosIndex++;
        if (this->bodyPartsPosIndex >= ARRAY_COUNT(this->bodyPartsPos)) {
            this->bodyPartsPosIndex = 0;
        }
    }
}

void func_80A48138(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    Vec3f sp4C = { 0.0f, 0.0f, 0.0f };
    s32 pad;
    EnWiz* this = THIS;

    if (this->unk_3B0 != 6) {
        if (limbIndex == 9) {
            sp4C.x = 7300.0f;
            sp4C.y = -1500.0f;
            if (this->unk_3B0 != 9) {
                sp4C.y = 0.0f;
                sp4C.x = 5300.0f;
            }

            Matrix_Translate(0.0f, 0.0f, 0.0f, MTXMODE_APPLY);
            Matrix_MultVec3f(&sp4C, &this->unk_3D8);
        }
    } else {
        if (this->unk_3B2 == 0) {
            Vec3f sp38;

            Matrix_Translate(0.0f, 0.0f, 0.0f, MTXMODE_APPLY);
            Matrix_MultVec3f(&sp4C, &sp38);
            sp38.x += randPlusMinusPoint5Scaled(4.0f);
            sp38.y += randPlusMinusPoint5Scaled(7.0f);
            sp38.z += randPlusMinusPoint5Scaled(5.0f);
            func_800B3030(play, &sp38, &gZeroVec3f, &gZeroVec3f, ((Rand_ZeroFloat(1.0f) * 50.0f) + 70.0f), 10, 1);
            SoundSource_PlaySfxAtFixedWorldPos(play, &sp38, 10, NA_SE_EN_EXTINCT);
        }

        if ((limbIndex >= 0x13) && (this->unk_3B2 == 0)) {
            this->unk_3B2 = 4;
        }
    }

    if ((limbIndex == 1) || (limbIndex == 2) || (limbIndex == 3) || (limbIndex == 4) || (limbIndex == 6) ||
        (limbIndex == 7) || (limbIndex == 0xA) || (limbIndex == 0xB) || (limbIndex == 0xC) || (limbIndex == 0xF) ||
        (limbIndex == 0x12) || (limbIndex == 0xD)) {
        Matrix_MultZero(&this->bodyPartsPos[this->bodyPartsPosIndex]);
        this->bodyPartsPosIndex++;
        if (this->bodyPartsPosIndex >= ARRAY_COUNT(this->bodyPartsPos)) {
            this->bodyPartsPosIndex = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/EnWiz_Draw.s")
