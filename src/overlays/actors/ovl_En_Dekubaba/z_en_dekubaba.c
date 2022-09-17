/*
 * File: z_en_dekubaba.c
 * Overlay: ovl_En_Dekubaba
 * Description: Deku Baba
 */

#include "z_en_dekubaba.h"
#include "overlays/effects/ovl_Effect_Ss_Hahen/z_eff_ss_hahen.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_400)

#define THIS ((EnDekubaba*)thisx)

void EnDekubaba_Init(Actor* thisx, PlayState* play);
void EnDekubaba_Destroy(Actor* thisx, PlayState* play);
void EnDekubaba_Update(Actor* thisx, PlayState* play);
void EnDekubaba_Draw(Actor* thisx, PlayState* play);

void func_808B18A8(EnDekubaba* this);
void func_808B1B14(EnDekubaba* this, PlayState* play);
void func_808B1BC0(EnDekubaba* this);
void func_808B1CF0(EnDekubaba* this, PlayState* play);
void func_808B2158(EnDekubaba* this);
void func_808B2240(EnDekubaba* this, PlayState* play);
void func_808B2660(EnDekubaba* this, PlayState* play);
void func_808B2890(EnDekubaba* this);
void func_808B28B4(EnDekubaba* this, PlayState* play);
void func_808B2980(EnDekubaba* this);
void func_808B29C4(EnDekubaba* this, PlayState* play);
void func_808B2C40(EnDekubaba* this);
void func_808B2CB8(EnDekubaba* this, PlayState* play);
void func_808B3078(EnDekubaba* this, PlayState* play);
void func_808B3280(EnDekubaba* this, PlayState* play);
void func_808B3404(EnDekubaba* this, PlayState* play);
void func_808B3768(EnDekubaba* this);
void func_808B37E8(EnDekubaba* this, PlayState* play);
void func_808B39AC(EnDekubaba* this);
void func_808B3B48(EnDekubaba* this, PlayState* play);
void func_808B3C50(EnDekubaba* this, PlayState* play);
void func_808B3DA8(EnDekubaba* this, PlayState* play);
void func_808B3E40(EnDekubaba* this, PlayState* play);
void func_808B3EE8(EnDekubaba* this, PlayState* play);

// #if 0
const ActorInit En_Dekubaba_InitVars = {
    ACTOR_EN_DEKUBABA,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DEKUBABA,
    sizeof(EnDekubaba),
    (ActorFunc)EnDekubaba_Init,
    (ActorFunc)EnDekubaba_Destroy,
    (ActorFunc)EnDekubaba_Update,
    (ActorFunc)EnDekubaba_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[7] = {
static ColliderJntSphElementInit D_808B4D60[7] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 1, { { 0, 100, 1000 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 51, { { 0, 0, 1500 }, 8 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 52, { { 0, 0, 500 }, 8 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 53, { { 0, 0, 1500 }, 8 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 54, { { 0, 0, 500 }, 8 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 55, { { 0, 0, 1500 }, 8 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 56, { { 0, 0, 500 }, 8 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_808B4E5C = {
    { COLTYPE_HIT6, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    ARRAY_COUNT(D_808B4D60), D_808B4D60, // sJntSphElementsInit,
};

// sColChkInfoInit
static CollisionCheckInfoInit D_808B4E6C = { 2, 25, 25, MASS_IMMOVABLE };

// static DamageTable sDamageTable = {
static DamageTable D_808B4E74 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(3, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(3, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xD),
    /* Goron punch    */ DMG_ENTRY(2, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(4, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(3, 0x3),
    /* Light arrow    */ DMG_ENTRY(3, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(3, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808B4E94[] = {
    ICHAIN_F32(targetArrowOffset, 1500, ICHAIN_STOP),
};

extern AnimationHeader D_06000208;
extern AnimationHeader D_060002B8;
extern Gfx D_060010F0[];
extern Gfx D_06001330[];
extern Gfx D_06001828[];
extern SkeletonHeader D_06002A40;
extern Gfx D_06003070[];

void EnDekubaba_Init(Actor* thisx, PlayState* play) {
    EnDekubaba* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->actor, D_808B4E94);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 22.0f);
    SkelAnime_Init(play, &this->skelAnime, &D_06002A40, &D_060002B8, this->jointTable, this->morphTable, 8);
    Collider_InitAndSetJntSph(play, &this->collider, &this->actor, &D_808B4E5C, this->colliderElements);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_808B4E74, &D_808B4E6C);

    if (this->actor.params == 1) {
        this->size = 2.5f;

        for (i = 0; i < D_808B4E5C.count; i++) {
            this->collider.elements[i].dim.worldSphere.radius = this->collider.elements[i].dim.modelSphere.radius =
                (D_808B4D60[i].dim.modelSphere.radius * 2.50f);
        }

        this->actor.colChkInfo.health = 4;
        this->actor.hintId = 8;
        this->actor.targetMode = 2;
    } else {
        this->size = 1.0f;

        for (i = 0; i < D_808B4E5C.count; i++) {
            this->collider.elements[i].dim.worldSphere.radius = this->collider.elements[i].dim.modelSphere.radius;
        }
        this->actor.hintId = 7;
        this->actor.targetMode = 1;
    }

    func_808B18A8(this);
    this->timer = 0;
    this->boundFloor = NULL;
}

void EnDekubaba_Destroy(Actor* thisx, PlayState* play) {
    EnDekubaba* this = THIS;

    Collider_DestroyJntSph(play, &this->collider);
}

void func_808B1530(EnDekubaba* this) {
    s32 i;

    for (i = 1; i < ARRAY_COUNT(this->colliderElements); i++) {
        this->collider.elements[i].info.bumperFlags &= ~BUMP_ON;
    }
}

void func_808B15B8(EnDekubaba* this) {
    f32 horizontalHeadShift = (Math_CosS(this->stemSectionAngle[0]) + Math_CosS(this->stemSectionAngle[1]) +
                               Math_CosS(this->stemSectionAngle[2])) *
                              20.0f;

    this->actor.world.pos.x =
        this->actor.home.pos.x + Math_SinS(this->actor.shape.rot.y) * (horizontalHeadShift * this->size);
    this->actor.world.pos.y =
        this->actor.home.pos.y - (Math_SinS(this->stemSectionAngle[0]) + Math_SinS(this->stemSectionAngle[1]) +
                                  Math_SinS(this->stemSectionAngle[2])) *
                                     20.0f * this->size;
    this->actor.world.pos.z =
        this->actor.home.pos.z + Math_CosS(this->actor.shape.rot.y) * (horizontalHeadShift * this->size);
}

void func_808B16BC(EnDekubaba* this, PlayState* play, s32 index) {
    ColliderJntSphElement* sphElement;

    if (this->actor.colChkInfo.damageEffect == 2) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->drawDmgEffScale = 0.75f;
        this->drawDmgEffAlpha = 4.0f;
    } else if (this->actor.colChkInfo.damageEffect == 4) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
        this->drawDmgEffScale = 0.75f;
        this->drawDmgEffAlpha = 4.0f;
        sphElement = &this->collider.elements[index];
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, sphElement->info.bumper.hitPos.x,
                    sphElement->info.bumper.hitPos.y, sphElement->info.bumper.hitPos.z, 0, 0, 0,
                    CLEAR_TAG_SMALL_LIGHT_RAYS);
    }
}

void func_808B1798(EnDekubaba* this) {
    this->drawDmgEffScale = 0.75f;
    this->drawDmgEffFrozenSteamScale = 1.125f;
    this->drawDmgEffAlpha = 1.0f;
    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX;
    this->collider.base.colType = COLTYPE_HIT3;
    this->timer = 80;
    this->actor.flags &= ~ACTOR_FLAG_400;
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 80);
}

void func_808B1814(EnDekubaba* this, PlayState* play) {
    if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->collider.base.colType = COLTYPE_HIT6;
        this->drawDmgEffAlpha = 0.0f;
        Actor_SpawnIceEffects(play, &this->actor, this->bodyPartsPos, ARRAY_COUNT(this->bodyPartsPos), 4,
                              this->size * 0.3f, this->size * 0.2f);
        this->actor.flags |= ACTOR_FLAG_400;
    }
}

void func_808B18A8(EnDekubaba* this) {
    s32 i;
    ColliderJntSphElement* element;

    this->actor.shape.rot.x = -0x4000;
    this->stemSectionAngle[0] = this->stemSectionAngle[1] = this->stemSectionAngle[2] = this->actor.shape.rot.x;

    this->actor.world.pos.x = this->actor.home.pos.x;
    this->actor.world.pos.z = this->actor.home.pos.z;
    this->actor.world.pos.y = this->actor.home.pos.y + 14.0f * this->size;

    Actor_SetScale(&this->actor, this->size * 0.01f * 0.5f);

    this->collider.base.colType = COLTYPE_HARD;
    this->collider.base.acFlags |= AC_HARD;
    this->timer = 45;

    for (i = 1; i < ARRAY_COUNT(this->colliderElements); i++) {
        element = &this->collider.elements[i];
        element->dim.worldSphere.center.x = this->actor.world.pos.x;
        element->dim.worldSphere.center.y = (s32)this->actor.world.pos.y - 7;
        element->dim.worldSphere.center.z = this->actor.world.pos.z;
    }

    this->actionFunc = func_808B1B14;
}

void func_808B1B14(EnDekubaba* this, PlayState* play) {
    if (this->timer != 0) {
        this->timer--;
    }

    this->actor.world.pos.x = this->actor.home.pos.x;
    this->actor.world.pos.z = this->actor.home.pos.z;
    this->actor.world.pos.y = this->actor.home.pos.y + 14.0f * this->size;

    if ((this->timer == 0) && (this->actor.xzDistToPlayer < 200.0f * this->size) &&
        (fabsf(this->actor.playerHeightRel) < 30.0f * this->size)) {
        func_808B1BC0(this);
    }
}

void func_808B1BC0(EnDekubaba* this) {
    s32 i;

    Animation_Change(&this->skelAnime, &D_060002B8, Animation_GetLastFrame(&D_060002B8) * (1.0f / 15), 0.0f,
                     Animation_GetLastFrame(&D_060002B8), ANIMMODE_ONCE, 0.0f);

    this->timer = 15;

    for (i = 2; i < ARRAY_COUNT(this->colliderElements); i++) {
        this->collider.elements[i].info.ocElemFlags |= OCELEM_ON;
    }

    this->collider.base.colType = COLTYPE_HIT6;
    this->collider.base.acFlags &= ~AC_HARD;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_DEKU_WAKEUP);
    this->actionFunc = func_808B1CF0;
}

void func_808B1CF0(EnDekubaba* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 headDistHorizontal;
    f32 headDistVertical;
    f32 headShiftX;
    f32 headShiftZ;

    if (this->timer != 0) {
        this->timer--;
    }

    SkelAnime_Update(&this->skelAnime);

    this->actor.scale.x = this->actor.scale.y = this->actor.scale.z =
        this->size * 0.01f * (0.5f + (15 - this->timer) * 0.5f / 15.0f);
    Math_ScaledStepToS(&this->actor.shape.rot.x, 0x1800, 0x800);

    headDistVertical = sin_rad(CLAMP_MAX((15 - this->timer) * (1.0f / 15), 0.7f) * M_PI) * 32.0f + 14.0f;

    if (this->actor.shape.rot.x < -0x38E3) {
        headDistHorizontal = 0.0f;
    } else if (this->actor.shape.rot.x < -0x238E) {
        Math_ScaledStepToS(&this->stemSectionAngle[0], -0x5555, 0x38E);
        headDistHorizontal = Math_CosS(this->stemSectionAngle[0]) * 20.0f;
    } else if (this->actor.shape.rot.x < -0xE38) {
        Math_ScaledStepToS(&this->stemSectionAngle[0], -0xAAA, 0x38E);
        Math_ScaledStepToS(&this->stemSectionAngle[1], -0x5555, 0x38E);
        Math_ScaledStepToS(&this->stemSectionAngle[2], -0x5555, 0x222);

        headDistHorizontal = 20.0f * (Math_CosS(this->stemSectionAngle[0]) + Math_CosS(this->stemSectionAngle[1])) +
                             (headDistVertical -
                              20.0f * (-Math_SinS(this->stemSectionAngle[0]) - Math_SinS(this->stemSectionAngle[1]))) *
                                 Math_CosS(this->stemSectionAngle[2]) / -Math_SinS(this->stemSectionAngle[2]);
    } else {
        Math_ScaledStepToS(&this->stemSectionAngle[0], -0xAAA, 0x38E);
        Math_ScaledStepToS(&this->stemSectionAngle[1], -0x31C7, 0x222);
        Math_ScaledStepToS(&this->stemSectionAngle[2], -0x5555, 0x222);

        headDistHorizontal = 20.0f * (Math_CosS(this->stemSectionAngle[0]) + Math_CosS(this->stemSectionAngle[1])) +
                             (headDistVertical -
                              20.0f * (-Math_SinS(this->stemSectionAngle[0]) - Math_SinS(this->stemSectionAngle[1]))) *
                                 Math_CosS(this->stemSectionAngle[2]) / -Math_SinS(this->stemSectionAngle[2]);
    }

    if (this->timer < 10) {
        Math_ApproachS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&this->actor.home.pos, &player->actor.world.pos), 2,
                       0xE38);
    }

    this->actor.world.pos.y = this->actor.home.pos.y + (headDistVertical * this->size);
    //! FAKE:
    headShiftX = headDistHorizontal;
    headShiftX = headShiftX * this->size * Math_SinS(this->actor.shape.rot.y);
    headShiftZ = headDistHorizontal;
    headShiftZ = headShiftZ * this->size * Math_CosS(this->actor.shape.rot.y);
    this->actor.world.pos.x = this->actor.home.pos.x + headShiftX;
    this->actor.world.pos.z = this->actor.home.pos.z + headShiftZ;

    EffectSsHahen_SpawnBurst(play, &this->actor.home.pos, this->size * 3.0f, 0, this->size * 12.0f, this->size * 5.0f,
                             1, HAHEN_OBJECT_DEFAULT, 10, NULL);

    if (this->timer == 0) {
        if (Math_Vec3f_DistXZ(&this->actor.home.pos, &player->actor.world.pos) < 240.0f * this->size) {
            func_808B2890(this);
        } else {
            func_808B2158(this);
        }
    }
}

void func_808B2158(EnDekubaba* this) {
    s32 i;

    Animation_Change(&this->skelAnime, &D_060002B8, -1.5f, Animation_GetLastFrame(&D_060002B8), 0.0f, ANIMMODE_ONCE,
                     -3.0f);

    this->timer = 15;

    for (i = 2; i < ARRAY_COUNT(this->colliderElements); i++) {
        this->collider.elements[i].info.ocElemFlags &= ~OCELEM_ON;
    }

    this->actionFunc = func_808B2240;
}

void func_808B2240(EnDekubaba* this, PlayState* play) {
    f32 headDistHorizontal;
    f32 headDistVertical;
    f32 xShift;
    f32 zShift;

    if (this->timer != 0) {
        this->timer--;
    }

    SkelAnime_Update(&this->skelAnime);

    this->actor.scale.x = this->actor.scale.y = this->actor.scale.z =
        this->size * 0.01f * (0.5f + this->timer * (1.0f / 30));
    Math_ScaledStepToS(&this->actor.shape.rot.x, -0x4000, 0x300);

    headDistVertical = (sin_rad(CLAMP_MAX(this->timer * 0.033f, 0.7f) * M_PI) * 32.0f) + 14.0f;

    if (this->actor.shape.rot.x < -0x38E3) {
        headDistHorizontal = 0.0f;
    } else if (this->actor.shape.rot.x < -0x238E) {
        Math_ScaledStepToS(&this->stemSectionAngle[0], -0x4000, 0x555);
        headDistHorizontal = Math_CosS(this->stemSectionAngle[0]) * 20.0f;
    } else if (this->actor.shape.rot.x < -0xE38) {
        Math_ScaledStepToS(&this->stemSectionAngle[0], -0x5555, 0x555);
        Math_ScaledStepToS(&this->stemSectionAngle[1], -0x4000, 0x555);
        Math_ScaledStepToS(&this->stemSectionAngle[2], -0x4000, 0x333);

        headDistHorizontal = 20.0f * (Math_CosS(this->stemSectionAngle[0]) + Math_CosS(this->stemSectionAngle[1])) +
                             (headDistVertical -
                              20.0f * (-Math_SinS(this->stemSectionAngle[0]) - Math_SinS(this->stemSectionAngle[1]))) *
                                 Math_CosS(this->stemSectionAngle[2]) / -Math_SinS(this->stemSectionAngle[2]);
    } else {
        Math_ScaledStepToS(&this->stemSectionAngle[0], -0x5555, 0x555);
        Math_ScaledStepToS(&this->stemSectionAngle[1], -0x5555, 0x333);
        Math_ScaledStepToS(&this->stemSectionAngle[2], -0x4000, 0x333);

        headDistHorizontal = 20.0f * (Math_CosS(this->stemSectionAngle[0]) + Math_CosS(this->stemSectionAngle[1])) +
                             (headDistVertical -
                              20.0f * (-Math_SinS(this->stemSectionAngle[0]) - Math_SinS(this->stemSectionAngle[1]))) *
                                 Math_CosS(this->stemSectionAngle[2]) / -Math_SinS(this->stemSectionAngle[2]);
    }

    this->actor.world.pos.y = this->actor.home.pos.y + (headDistVertical * this->size);
    xShift = headDistHorizontal * this->size * Math_SinS(this->actor.shape.rot.y);
    zShift = headDistHorizontal * this->size * Math_CosS(this->actor.shape.rot.y);
    this->actor.world.pos.x = this->actor.home.pos.x + xShift;
    this->actor.world.pos.z = this->actor.home.pos.z + zShift;

    EffectSsHahen_SpawnBurst(play, &this->actor.home.pos, this->size * 3.0f, 0, this->size * 12.0f, this->size * 5.0f,
                             1, HAHEN_OBJECT_DEFAULT, 10, NULL);
    if (this->timer == 0) {
        func_808B18A8(this);
    }
}

void func_808B2608(EnDekubaba* this) {
    this->timer = Animation_GetLastFrame(&D_060002B8) * 2;
    Animation_MorphToLoop(&this->skelAnime, &D_060002B8, -3.0f);
    this->actionFunc = func_808B2660;
}

void func_808B2660(EnDekubaba* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 12.0f)) {
        if (this->actor.params == 1) {
            Actor_PlaySfxAtPos(&this->actor, 0x385C);
        } else {
            Actor_PlaySfxAtPos(&this->actor, 0x3860);
        }
    }

    if (this->timer != 0) {
        this->timer--;
    }

    Math_ApproachS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&this->actor.home.pos, &player->actor.world.pos), 2,
                   (this->timer % 5) * 0x222);

    if (this->timer < 10) {
        this->stemSectionAngle[0] += 0x16C;
        this->stemSectionAngle[1] += 0x16C;
        this->stemSectionAngle[2] += 0xB6;
        this->actor.shape.rot.x += 0x222;
    } else if (this->timer < 20) {
        this->stemSectionAngle[0] -= 0x16C;
        this->stemSectionAngle[1] += 0x111;
        this->actor.shape.rot.x += 0x16C;
    } else if (this->timer < 30) {
        this->stemSectionAngle[1] -= 0x111;
        this->actor.shape.rot.x -= 0xB6;
    } else {
        this->stemSectionAngle[1] -= 0xB6;
        this->stemSectionAngle[2] += 0xB6;
        this->actor.shape.rot.x -= 0x16C;
    }

    func_808B15B8(this);

    if ((240.0f * this->size) < Math_Vec3f_DistXZ(&this->actor.home.pos, &player->actor.world.pos)) {
        func_808B2158(this);
    } else if ((this->timer == 0) || (this->actor.xzDistToPlayer < (80.0f * this->size))) {
        func_808B2890(this);
    }
}

void func_808B2890(EnDekubaba* this) {
    this->timer = 8;
    this->skelAnime.playSpeed = 0.0f;
    this->actionFunc = func_808B28B4;
}

void func_808B28B4(EnDekubaba* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (this->timer != 0) {
        this->timer--;
    }

    Math_SmoothStepToS(&this->actor.shape.rot.x, 0x1800, 2, 0xE38, 0x71C);
    Math_ApproachS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&this->actor.home.pos, &player->actor.world.pos), 2, 0xE38);
    Math_ScaledStepToS(this->stemSectionAngle, 0xAAA, 0x444);
    Math_ScaledStepToS(&this->stemSectionAngle[1], -0x4718, 0x888);
    Math_ScaledStepToS(&this->stemSectionAngle[2], -0x6AA4, 0x888);
    if (this->timer == 0) {
        func_808B2980(this);
    }
    func_808B15B8(this);
}

void func_808B2980(EnDekubaba* this) {
    Animation_PlayOnce(&this->skelAnime, &D_06000208);
    this->timer = 0;
    this->actionFunc = func_808B29C4;
}

void func_808B29C4(EnDekubaba* this, PlayState* play) {
    static Color_RGBA8 D_808B4E98 = { 105, 255, 105, 255 };
    static Color_RGBA8 D_808B4E9C = { 150, 250, 150, 0 };
    s32 allStepsDone;
    s16 curFrame10;
    Vec3f velocity;

    SkelAnime_Update(&this->skelAnime);

    if (this->timer == 0) {
        if (Animation_OnFrame(&this->skelAnime, 1.0f)) {
            if (this->actor.params == 1) {
                Actor_PlaySfxAtPos(&this->actor, 0x385DU);
            } else {
                Actor_PlaySfxAtPos(&this->actor, 0x3861U);
            }
        }

        Math_ScaledStepToS(&this->actor.shape.rot.x, 0, 0x222);

        curFrame10 = (s32)(this->skelAnime.curFrame * 10.0f);

        allStepsDone = true;
        allStepsDone &= Math_ScaledStepToS(&this->stemSectionAngle[0], -0xE38, curFrame10 + 0x38E);
        allStepsDone &= Math_ScaledStepToS(&this->stemSectionAngle[1], -0xE38, curFrame10 + 0x71C);
        allStepsDone &= Math_ScaledStepToS(&this->stemSectionAngle[2], -0xE38, curFrame10 + 0xE38);
        if (allStepsDone) {
            Animation_PlayLoopSetSpeed(&this->skelAnime, &D_060002B8, 4.0f);
            velocity.x = Math_SinS(this->actor.shape.rot.y) * 5.0f;
            velocity.y = 0.0f;
            velocity.z = Math_CosS(this->actor.shape.rot.y) * 5.0f;
            func_800B0DE0(play, &this->actor.world.pos, &velocity, &gZeroVec3f, &D_808B4E98, &D_808B4E9C, 1,
                          (s32)(this->size * 100.0f));
            this->timer = 1;
        }
    } else if (this->timer > 10) {
        func_808B2C40(this);
    } else {
        this->timer++;

        if ((this->timer >= 4) && !Actor_IsFacingPlayer(&this->actor, 0x16C)) {
            Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xF, 0x71C);
        }

        if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 12.0f)) {
            if (this->actor.params == 1) {
                Actor_PlaySfxAtPos(&this->actor, 0x385CU);
            } else {
                Actor_PlaySfxAtPos(&this->actor, 0x3860U);
            }
        }
    }

    func_808B15B8(this);
}

void func_808B2C40(EnDekubaba* this) {
    Animation_Change(&this->skelAnime, &D_06000208, 1.0f, 15.0f, Animation_GetLastFrame(&D_06000208), ANIMMODE_ONCE,
                     -3.0f);
    this->timer = 0;
    this->actionFunc = func_808B2CB8;
}

void func_808B2CB8(EnDekubaba* this, PlayState* play) {
    Vec3f dustPos;
    f32 xIncr;
    f32 zIncr;
    s32 i;

    SkelAnime_Update(&this->skelAnime);

    if (this->timer == 0) {
        Math_ScaledStepToS(&this->actor.shape.rot.x, -0x93E, 0x38E);
        Math_ScaledStepToS(&this->stemSectionAngle[0], -0x888, 0x16C);
        Math_ScaledStepToS(&this->stemSectionAngle[1], -0x888, 0x16C);

        if (Math_ScaledStepToS(&this->stemSectionAngle[2], -0x888, 0x16C)) {
            xIncr = Math_SinS(this->actor.shape.rot.y) * 30.0f * this->size;
            zIncr = Math_CosS(this->actor.shape.rot.y) * 30.0f * this->size;
            dustPos = this->actor.home.pos;

            for (i = 0; i < 3; i++) {
                func_800B1210(play, &dustPos, &gZeroVec3f, &gZeroVec3f, (s32)(this->size * 500.0f),
                              (s32)(this->size * 50.0f));
                dustPos.x += xIncr;
                dustPos.z += zIncr;
            }

            this->timer = 1;
        }
    } else if (this->timer == 11) {
        Math_ScaledStepToS(&this->actor.shape.rot.x, -0x93E, 0x200);
        Math_ScaledStepToS(this->stemSectionAngle, -0xAAA, 0x200);
        Math_ScaledStepToS(&this->stemSectionAngle[2], -0x5C71, 0x200);

        if (Math_ScaledStepToS(&this->stemSectionAngle[1], 0x238C, 0x200)) {
            this->timer = 12;
        }
    } else if (this->timer == 18) {
        Math_ScaledStepToS(&this->actor.shape.rot.x, 0x2AA8, 0xAAA);

        if (Math_ScaledStepToS(&this->stemSectionAngle[0], 0x1554, 0x5B0)) {
            this->timer = 25;
        }

        Math_ScaledStepToS(&this->stemSectionAngle[1], -0x38E3, 0xAAA);
        Math_ScaledStepToS(&this->stemSectionAngle[2], -0x5C71, 0x2D8);
    } else if (this->timer == 25) {
        Math_ScaledStepToS(&this->actor.shape.rot.x, -0x5550, 0xAAA);

        if (Math_ScaledStepToS(&this->stemSectionAngle[0], -0x6388, 0x93E)) {
            this->timer = 26;
        }

        Math_ScaledStepToS(&this->stemSectionAngle[1], -0x3FFC, 0x4FA);
        Math_ScaledStepToS(&this->stemSectionAngle[2], -0x238C, 0x444);
    } else if (this->timer == 26) {
        Math_ScaledStepToS(&this->actor.shape.rot.x, 0x1800, 0x93E);

        if (Math_ScaledStepToS(&this->stemSectionAngle[0], -0x1555, 0x71C)) {
            this->timer = 27;
        }

        Math_ScaledStepToS(&this->stemSectionAngle[1], -0x38E3, 0x2D8);
        Math_ScaledStepToS(&this->stemSectionAngle[2], -0x5C71, 0x5B0);
    } else if (this->timer >= 27) {
        this->timer++;
        if (this->timer > 30) {
            if (this->actor.xzDistToPlayer < (80.0f * this->size)) {
                func_808B2890(this);
            } else {
                func_808B2608(this);
            }
        }
    } else {
        this->timer++;
        if (this->timer == 10) {
            Actor_PlaySfxAtPos(&this->actor, 0x3863U);
        }

        if (this->timer >= 12) {
            Math_ScaledStepToS(&this->stemSectionAngle[2], -0x5C71, 0x88);
        }
    }

    func_808B15B8(this);
}

void func_808B3044(EnDekubaba* this) {
    this->timer = 9;
    this->collider.base.acFlags |= AC_ON;
    this->skelAnime.playSpeed = -1.0f;
    this->actionFunc = func_808B3078;
}

void func_808B3078(EnDekubaba* this, PlayState* play) {
    s32 temp_s0;

    SkelAnime_Update(&this->skelAnime);

    if (this->timer > 8) {
        temp_s0 = Math_SmoothStepToS(&this->actor.shape.rot.x, 0x1800, 1, 0x11C6, 0x71C);
        temp_s0 |= Math_SmoothStepToS(&this->stemSectionAngle[0], -0x1555, 1, 0xAAA, 0x71C);
        temp_s0 |= Math_SmoothStepToS(&this->stemSectionAngle[1], -0x38E3, 1, 0xE38, 0x71C);
        temp_s0 |= Math_SmoothStepToS(&this->stemSectionAngle[2], -0x5C71, 1, 0x11C6, 0x71C);
        if (!temp_s0) {
            this->timer = 8;
        }
    } else {
        if (this->timer != 0) {
            this->timer--;
        }

        if (this->timer == 0) {
            func_808B2608(this);
        }
    }

    func_808B15B8(this);
}

void func_808B3170(EnDekubaba* this, s32 arg1) {
    Animation_MorphToPlayOnce(&this->skelAnime, &D_06000208, -5.0f);
    this->timer = arg1;
    this->collider.base.acFlags &= ~AC_ON;
    Actor_SetScale(&this->actor, this->size * 0.01f);
    if (arg1 == 2) {
        Actor_SetColorFilter(&this->actor, 0, 155, 0, 42);
    } else if (arg1 == 3) {
        Actor_SetColorFilter(&this->actor, 0, 155, 0, 42);
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_LARGE;
        this->drawDmgEffScale = 0.75f;
        this->drawDmgEffAlpha = 2.0f;
    } else {
        Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 42);
    }
    this->actionFunc = func_808B3280;
}

void func_808B3280(EnDekubaba* this, PlayState* play) {
    s32 temp_s0;

    SkelAnime_Update(&this->skelAnime);
    temp_s0 = true;
    temp_s0 &= Math_ScaledStepToS(&this->actor.shape.rot.x, -0x4000, 0xE38);
    temp_s0 &= Math_ScaledStepToS(this->stemSectionAngle, -0x4000, 0xE38);
    temp_s0 &= Math_ScaledStepToS(&this->stemSectionAngle[1], -0x4000, 0xE38);
    temp_s0 &= Math_ScaledStepToS(&this->stemSectionAngle[2], -0x4000, 0xE38);
    if (temp_s0) {
        if (this->actor.colChkInfo.health == 0) {
            func_808B3768(this);
        } else {
            this->collider.base.acFlags |= AC_ON;

            if (this->timer == 0) {
                if (this->actor.xzDistToPlayer < (80.0f * this->size)) {
                    func_808B2890(this);
                } else {
                    func_808B3044(this);
                }
            } else {
                func_808B39AC(this);
            }
        }
    }

    func_808B15B8(this);
}

void func_808B3390(EnDekubaba* this) {
    this->skelAnime.playSpeed = 0.0f;
    this->timer = 0;
    this->actor.gravity = -0.8f;
    this->actor.velocity.y = 4.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y + 0x8000;
    this->actor.speedXZ = this->size * 3.0f;
    this->collider.base.acFlags &= ~AC_ON;
    this->actor.flags |= ACTOR_FLAG_10 | ACTOR_FLAG_20;
    this->actionFunc = func_808B3404;
}

void func_808B3404(EnDekubaba* this, PlayState* play) {
    s32 i;
    Vec3f dustPos;
    f32 deltaX;
    f32 deltaY;
    f32 deltaZ;

    Math_StepToF(&this->actor.speedXZ, 0.0f, this->size * 0.1f);

    if (this->timer == 0) {
        Math_ScaledStepToS(&this->actor.shape.rot.x, 0x4800, 0x71C);
        Math_ScaledStepToS(this->stemSectionAngle, 0x4800, 0x71C);
        Math_ScaledStepToS(&this->stemSectionAngle[1], 0x4800, 0x71C);

        EffectSsHahen_SpawnBurst(play, &this->actor.world.pos, this->size * 3.0f, 0, (s32)(this->size * 12.0f),
                                 (s32)(this->size * 5.0f), 1, HAHEN_OBJECT_DEFAULT, 10, NULL);

        if ((this->actor.scale.x > 0.005f) && ((this->actor.bgCheckFlags & 2) || (this->actor.bgCheckFlags & 8))) {
            this->actor.scale.z = 0.0f;
            this->actor.scale.y = 0.0f;
            this->actor.scale.x = 0.0f;
            this->actor.speedXZ = 0.0f;
            this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_4);
            EffectSsHahen_SpawnBurst(play, &this->actor.world.pos, this->size * 3.0f, 0, (s32)(this->size * 12.0f),
                                     (s32)(this->size * 5.0f), 15, HAHEN_OBJECT_DEFAULT, 10, NULL);
        }

        if (this->actor.bgCheckFlags & 2) {
            Actor_PlaySfxAtPos(&this->actor, 0x387BU);
            this->timer = 1;
        }
    } else if (this->timer == 1) {
        dustPos = this->actor.world.pos;

        deltaY = 20.0f * Math_SinS(this->actor.shape.rot.x);
        deltaX = -20.0f * Math_CosS(this->actor.shape.rot.x) * Math_SinS(this->actor.shape.rot.y);
        deltaZ = -20.0f * Math_CosS(this->actor.shape.rot.x) * Math_CosS(this->actor.shape.rot.y);

        for (i = 0; i < 4; i++) {
            func_800B1210(play, &dustPos, &gZeroVec3f, &gZeroVec3f, 500, 50);
            dustPos.x += deltaX;
            dustPos.y += deltaY;
            dustPos.z += deltaZ;
        }

        func_800B1210(play, &this->actor.home.pos, &gZeroVec3f, &gZeroVec3f, (s32)(this->size * 500.0f),
                      (s32)(this->size * 100.0f));
        func_808B3E40(this, play);
    }
}

void func_808B3768(EnDekubaba* this) {
    Animation_Change(&this->skelAnime, &D_060002B8, -1.5f, Animation_GetLastFrame(&D_060002B8), 0.0f, ANIMMODE_ONCE,
                     -3.0f);
    this->collider.base.acFlags &= ~AC_ON;
    this->actionFunc = func_808B37E8;
}

void func_808B37E8(EnDekubaba* this, PlayState* play) {
    Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y, this->size * 5.0f);

    if (Math_StepToF(&this->actor.scale.x, this->size * 0.1f * 0.01f, this->size * 0.1f * 0.01f)) {
        func_800B1210(play, &this->actor.home.pos, &gZeroVec3f, &gZeroVec3f, (s32)(this->size * 500.0f),
                      (s32)(this->size * 100.0f));

        if (this->actor.dropFlag == 0) {
            Item_DropCollectible(play, &this->actor.world.pos, 0xCU);
            if (this->actor.params == 1) {
                Item_DropCollectible(play, &this->actor.world.pos, 0xCU);
                Item_DropCollectible(play, &this->actor.world.pos, 0xCU);
            }
        } else {
            Item_DropCollectibleRandom(play, &this->actor, &this->actor.world.pos, 0x30);
        }
        Actor_MarkForDeath(&this->actor);
    }

    this->actor.scale.y = this->actor.scale.z = this->actor.scale.x;
    this->actor.shape.rot.z += 0x1C70;
    EffectSsHahen_SpawnBurst(play, &this->actor.home.pos, this->size * 3.0f, 0, (s32)(this->size * 12.0f),
                             (s32)(this->size * 5.0f), 1, HAHEN_OBJECT_DEFAULT, 10, NULL);
}

void func_808B39AC(EnDekubaba* this) {
    s32 i;

    for (i = 1; i < ARRAY_COUNT(this->colliderElements); i++) {
        this->collider.elements[i].info.bumperFlags |= BUMP_ON;
    }

    if (this->timer == 1) {
        Animation_Change(&this->skelAnime, &D_060002B8, 4.0f, 0.0f, Animation_GetLastFrame(&D_060002B8), ANIMMODE_LOOP,
                         -3.0f);
        this->timer = 0x28;
    } else {
        Animation_Change(&this->skelAnime, &D_060002B8, 0.0f, 0.0f, Animation_GetLastFrame(&D_060002B8), ANIMMODE_LOOP,
                         -3.0f);
        if (this->timer == 2) {
            this->timer = 40;
        } else {
            this->timer = 40;
        }
    }

    this->actor.world.pos.x = this->actor.home.pos.x;
    this->actor.world.pos.y = this->actor.home.pos.y + (60.0f * this->size);
    this->actor.world.pos.z = this->actor.home.pos.z;
    this->actionFunc = func_808B3B48;
}

void func_808B3B48(EnDekubaba* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if (this->timer != 0) {
        this->timer--;
    }

    if (this->timer == 0) {
        func_808B1530(this);

        if (this->actor.xzDistToPlayer < (80.0f * this->size)) {
            func_808B2890(this);
        } else {
            func_808B3044(this);
        }
    }
}

void func_808B3BE4(EnDekubaba* this) {
    this->targetSwayAngle = -0x6000;
    this->stemSectionAngle[2] = -0x5000;
    this->stemSectionAngle[1] = -0x4800;
    func_808B1530(this);
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 35);
    this->collider.base.acFlags &= ~AC_ON;
    this->actionFunc = func_808B3C50;
}

void func_808B3C50(EnDekubaba* this, PlayState* play) {
    s16 temp_v0;
    s16 var_v1;

    SkelAnime_Update(&this->skelAnime);
    Math_ScaledStepToS(&this->actor.shape.rot.x, this->stemSectionAngle[0], 0x71C);
    Math_ScaledStepToS(this->stemSectionAngle, this->stemSectionAngle[1], 0x71C);
    Math_ScaledStepToS(&this->stemSectionAngle[1], this->stemSectionAngle[2], 0x71C);
    if (Math_ScaledStepToS(&this->stemSectionAngle[2], this->targetSwayAngle, 0x71C) != 0) {
        this->targetSwayAngle = -0x4000 - (s32)((this->targetSwayAngle + 0x4000) * 0.8f);
    }

    temp_v0 = this->targetSwayAngle + 0x4000;

    if (ABS_ALT(temp_v0) < 0x100) {
        this->collider.base.acFlags |= AC_ON;
        if (this->actor.xzDistToPlayer < (80.0f * this->size)) {
            func_808B2890(this);
        } else {
            func_808B3044(this);
        }
    }
    func_808B15B8(this);
}

void func_808B3D74(EnDekubaba* this) {
    func_808B1798(this);
    this->actionFunc = func_808B3DA8;
}

void func_808B3DA8(EnDekubaba* this, PlayState* play) {
    if (this->timer != 0) {
        this->timer--;
    }
    if (this->timer == 0) {
        func_808B1814(this, play);
        if (this->actor.colChkInfo.health == 0) {
            func_808B3768(this);
        } else if (this->actor.xzDistToPlayer < (80.0f * this->size)) {
            func_808B2890(this);
        } else {
            func_808B3044(this);
        }
    }
}

void func_808B3E40(EnDekubaba* this, PlayState* play) {
    Actor_SetScale(&this->actor, 0.03f);
    this->actor.shape.rot.x -= 0x4000;
    this->actor.shape.yOffset = 1000.0f;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.shape.shadowScale = 3.0f;
    func_800BC154(play, &play->actorCtx, &this->actor, ACTORCAT_MISC);
    this->actor.flags &= ~ACTOR_FLAG_20;
    this->timer = 200;
    this->drawDmgEffAlpha = 0.0f;
    this->actionFunc = func_808B3EE8;
}

void func_808B3EE8(EnDekubaba* this, PlayState* play) {
    if (this->timer != 0) {
        this->timer--;
    }

    if (Actor_HasParent(&this->actor, play) || (this->timer == 0)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    Actor_PickUpNearby(&this->actor, play, 0x19);
}

void func_808B3F50(EnDekubaba* this, PlayState* play) {
    s32 temp;
    s32 i;
    ColliderJntSphElement* sphElement;
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        Actor_SetDropFlagJntSph(&this->actor, &this->collider);

        if ((this->collider.base.colType != COLTYPE_HARD) && (this->actor.colChkInfo.damageEffect != 0xD)) {
            sphElement = &this->collider.elements[0];
            for (i = 0; i < ARRAY_COUNT(this->colliderElements); i++, sphElement++) {
                if (sphElement->info.bumperFlags & 2) {
                    break;
                }
            }

            if ((i != ARRAY_COUNT(this->colliderElements)) &&
                ((this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) ||
                 (!(sphElement->info.acHitInfo->toucher.dmgFlags & 0xDB0B3)))) {
                func_808B1814(this, play);
                temp = this->actor.colChkInfo.health - this->actor.colChkInfo.damage;

                if (this->actionFunc != func_808B3B48) {
                    if (this->actor.colChkInfo.damageEffect == 3) {
                        func_808B3D74(this);
                    } else if (this->actor.colChkInfo.damageEffect == 5) {
                        func_808B3170(this, 3);
                    } else if (this->actor.colChkInfo.damageEffect == 1) {
                        func_808B3170(this, 2);
                    } else {
                        func_808B16BC(this, play, i);
                        if (this->actionFunc == func_808B2CB8) {
                            if (temp <= 0) {
                                temp = 1;
                            }
                            func_808B3170(this, 1);
                        } else {
                            func_808B3170(this, 0);
                        }
                    }
                } else {
                    if (this->actor.colChkInfo.damageEffect == 0xF) {
                        if (temp > 0) {
                            func_808B3BE4(this);
                        } else {
                            func_808B3390(this);
                        }
                    } else if (this->actor.colChkInfo.damageEffect == 5) {
                        func_808B3170(this, 3);
                    } else if (this->actor.colChkInfo.damageEffect == 1) {
                        func_808B3170(this, 2);
                    } else if (this->actor.colChkInfo.damageEffect == 3) {
                        func_808B3D74(this);
                    } else {
                        func_808B16BC(this, play, i);
                        func_808B3170(this, 0);
                    }
                }

                if (temp < 0) {
                    this->actor.colChkInfo.health = 0;
                } else {
                    this->actor.colChkInfo.health = temp;
                }
            } else {
                return;
            }
        } else {
            return;
        }
    } else if ((((((play->actorCtx.unk2 != 0) && (this->actor.xyzDistToPlayerSq < 40000.0f)) &&
                  (this->collider.base.colType != COLTYPE_HARD)) &&
                 (this->actionFunc != func_808B3B48)) &&
                (this->actionFunc != func_808B3280)) &&
               (this->actor.colChkInfo.health != 0)) {
        this->actor.colChkInfo.health--;
        this->actor.dropFlag = 0;
        func_808B3170(this, 1);
    } else {
        return;
    }

    if (this->actor.colChkInfo.health != 0) {
        if ((this->timer == 2) || (this->timer == 3)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
        } else {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_DEKU_DAMAGE);
        }
    } else {
        Enemy_StartFinishingBlow(play, &this->actor);

        if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
            this->timer = 3;
            this->collider.base.acFlags &= ~AC_ON;
        } else if (this->drawDmgEffAlpha > 1.5f) {
            this->drawDmgEffAlpha = 1.5f;
        }

        if (this->actor.params == 1) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_DEKU_DEAD);
        } else {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_DEKU_JR_DEAD);
        }
    }
}

void EnDekubaba_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnDekubaba* this = THIS;

    if (this->collider.base.atFlags & AT_HIT) {
        this->collider.base.atFlags &= ~AT_HIT;
        func_808B3044(this);
    }

    func_808B3F50(this, play);
    this->actionFunc(this, play);

    if (this->actionFunc == func_808B3404) {
        Actor_MoveWithGravity(&this->actor);
        Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, this->size * 15.0f, 10.0f, 5);
    } else if (this->actionFunc != func_808B3EE8) {
        Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, 4);
        if (this->boundFloor == NULL) {
            this->boundFloor = this->actor.floorPoly;
        }
    }

    if (this->actionFunc == func_808B29C4) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
        this->actor.flags |= ACTOR_FLAG_1000000;
    }

    if (this->collider.base.acFlags & AC_ON) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    }

    if (this->actionFunc != func_808B3EE8) {
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }

    if (this->drawDmgEffAlpha > 0.0f) {
        if (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
            Math_StepToF(&this->drawDmgEffAlpha, 0.0f, 0.05f);
            this->drawDmgEffScale = (this->drawDmgEffAlpha + 1.0f) * 0.375f;
            this->drawDmgEffScale = CLAMP_MAX(this->drawDmgEffScale, 0.75f);
        } else if (!Math_StepToF(&this->drawDmgEffFrozenSteamScale, 0.75f, 0.75f / 40)) {
            func_800B9010(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
        }
    }
}

void func_808B4548(EnDekubaba* this, PlayState* play) {
    f32 horizontalScale;
    s32 i;

    OPEN_DISPS(play->state.gfxCtx);

    horizontalScale = this->size * 0.01f;

    Matrix_Translate(this->actor.home.pos.x, this->actor.home.pos.y + (-6.0f * this->size), this->actor.home.pos.z,
                     MTXMODE_NEW);
    Matrix_RotateZYX(this->stemSectionAngle[0], this->actor.shape.rot.y, 0, MTXMODE_APPLY);
    Matrix_Scale(horizontalScale, horizontalScale, horizontalScale, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_06001330);

    for (i = 1; i < ARRAY_COUNT(this->bodyPartsPos); i++) {
        Matrix_MultZero(&this->bodyPartsPos[i]);
    }

    Actor_SetFocus(&this->actor, 0.0f);

    CLOSE_DISPS(play->state.gfxCtx);
}

extern Gfx* D_808B4EA0[];

void func_808B465C(EnDekubaba* this, PlayState* play) {
    static Gfx* D_808B4EA0[] = { 0x06001330, 0x06001628, 0x06001828 };
    MtxF mtx;
    s32 i;
    f32 scale;
    f32 horizontalStepSize;
    s32 stemSections;

    OPEN_DISPS(play->state.gfxCtx);

    if (this->actionFunc == func_808B3404) {
        stemSections = 2;
    } else {
        stemSections = 3;
    }

    scale = this->size * 0.01f;
    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
    Matrix_Get(&mtx);

    for (i = 0; i < stemSections; i++) {
        mtx.yw += 20.0f * Math_SinS(this->stemSectionAngle[i]) * this->size;
        horizontalStepSize = Math_CosS(this->stemSectionAngle[i]) * 20.0f * this->size;
        mtx.xw -= horizontalStepSize * Math_SinS(this->actor.shape.rot.y);
        mtx.zw -= horizontalStepSize * Math_CosS(this->actor.shape.rot.y);

        Matrix_Put(&mtx);
        Matrix_RotateZYX(this->stemSectionAngle[i], this->actor.shape.rot.y, 0, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, D_808B4EA0[i]);

        Collider_UpdateSpheres(51 + 2 * i, &this->collider);
        Collider_UpdateSpheres(52 + 2 * i, &this->collider);

        if (i == 0) {
            if (this->actionFunc != func_808B3C50) {
                this->actor.focus.pos.x = mtx.xw;
                this->actor.focus.pos.y = mtx.yw;
                this->actor.focus.pos.z = mtx.zw;
            } else {
                this->actor.focus.pos.x = this->actor.home.pos.x;
                this->actor.focus.pos.y = this->actor.home.pos.y + (40.0f * this->size);
                this->actor.focus.pos.z = this->actor.home.pos.z;
            }
        }

        Matrix_MultZero(&this->bodyPartsPos[i + 1]);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_808B48FC(EnDekubaba* this, PlayState* play) {
    OPEN_DISPS(play->state.gfxCtx);

    Matrix_RotateZYX(this->stemSectionAngle[2], this->actor.shape.rot.y, 0, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_06001828);

    Collider_UpdateSpheres(55, &this->collider);
    Collider_UpdateSpheres(56, &this->collider);

    Matrix_MultZero(&this->bodyPartsPos[3]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_808B49C8(EnDekubaba* this, PlayState* play) {
    MtxF mtx;
    f32 horizontalScale;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C448(play->state.gfxCtx);

    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 0, 0, 0, 255);

    func_800C0094(this->boundFloor, this->actor.home.pos.x, this->actor.home.pos.y, this->actor.home.pos.z, &mtx);
    Matrix_Mult(&mtx, MTXMODE_NEW);

    horizontalScale = this->size * 0.15f;
    Matrix_Scale(horizontalScale, 1.0f, horizontalScale, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gCircleShadowDL);

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_808B4ABC(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnDekubaba* this = THIS;

    if (limbIndex == 1) {
        Collider_UpdateSpheres(limbIndex, &this->collider);
    }
}

void EnDekubaba_Draw(Actor* thisx, PlayState* play) {
    EnDekubaba* this = THIS;
    f32 scale;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    Math_Vec3f_Copy(&this->bodyPartsPos[0], &this->actor.world.pos);

    if (this->actionFunc != func_808B3EE8) {
        SkelAnime_DrawOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, NULL, func_808B4ABC,
                          &this->actor);
        if (this->actionFunc == func_808B1B14) {
            func_808B4548(this, play);
        } else {
            func_808B465C(this, play);
        }

        scale = this->size * 0.01f;
        Matrix_Translate(this->actor.home.pos.x, this->actor.home.pos.y, this->actor.home.pos.z, MTXMODE_NEW);
        Matrix_RotateYS(this->actor.home.rot.y, MTXMODE_APPLY);
        Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, D_060010F0);

        if (this->actionFunc == func_808B3404) {
            func_808B48FC(this, play);
        }
        if (this->boundFloor != NULL) {
            func_808B49C8(this, play);
        }
    } else if ((this->timer > 40) || (this->timer & 1)) {
        Matrix_Translate(0.0f, 0.0f, 200.0f, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, D_06003070);
    }

    CLOSE_DISPS(play->state.gfxCtx);
    Actor_DrawDamageEffects(play, &this->actor, this->bodyPartsPos, ARRAY_COUNT(this->bodyPartsPos),
                            this->drawDmgEffScale * this->size, this->drawDmgEffFrozenSteamScale, this->drawDmgEffAlpha,
                            this->drawDmgEffType);
}
