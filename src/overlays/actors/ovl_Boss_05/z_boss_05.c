/*
 * File: z_boss_05.c
 * Overlay: ovl_Boss_05
 * Description: Bio Deku Baba
 */

#include "z_boss_05.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY)

#define THIS ((Boss05*)thisx)

void Boss05_Init(Actor* thisx, PlayState* play);
void Boss05_Destroy(Actor* thisx, PlayState* play);
void Boss05_Update(Actor* thisx, PlayState* play);
void Boss05_Draw(Actor* thisx, PlayState* play);

void Boss05_LilyPadWithHead_SetupMove(Boss05* this, PlayState* play);
void Boss05_LilyPadWithHead_Move(Boss05* this, PlayState* play);
void Boss05_LilyPad_Idle(Boss05* this, PlayState* play);
void Boss05_FallingHead_Fall(Boss05* this, PlayState* play);
void Boss05_WalkingHead_SetupTransform(Boss05* this, PlayState* play);
void Boss05_WalkingHead_Transform(Boss05* this, PlayState* play);
void Boss05_WalkingHead_SetupIdle(Boss05* this, PlayState* play);
void Boss05_WalkingHead_Idle(Boss05* this, PlayState* play);
void Boss05_WalkingHead_SetupWalk(Boss05* this, PlayState* play);
void Boss05_WalkingHead_Walk(Boss05* this, PlayState* play);
void Boss05_WalkingHead_SetupSpottedPlayer(Boss05* this, PlayState* play);
void Boss05_WalkingHead_SpottedPlayer(Boss05* this, PlayState* play);
void Boss05_WalkingHead_SetupCharge(Boss05* this, PlayState* arg1);
void Boss05_WalkingHead_Charge(Boss05* this, PlayState* play);
void Boss05_WalkingHead_SetupAttack(Boss05* this, PlayState* arg1);
void Boss05_WalkingHead_Attack(Boss05* this, PlayState* play);
void Boss05_WalkingHead_SetupDamaged(Boss05* this, PlayState* play);
void Boss05_WalkingHead_Damaged(Boss05* this, PlayState* play);
void Boss05_WalkingHead_SetupStunned(Boss05* this, PlayState* play);
void Boss05_WalkingHead_SetupFreeze(Boss05* this, PlayState* play);
void Boss05_WalkingHead_Stunned(Boss05* this, PlayState* play);
void Boss05_Fragment_Move(Boss05* this, PlayState* play);

#include "assets/overlays/ovl_Boss_05/ovl_Boss_05.c"

static ColliderJntSphElementInit sLilyPadJntSphElementsInit[] = {
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_HARD,
            BUMP_ON,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_HARD,
            BUMP_ON,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 15 }, 100 },
    },
};

static ColliderJntSphInit sLilyPadJntSphInit = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sLilyPadJntSphElementsInit),
    sLilyPadJntSphElementsInit,
};

static ColliderJntSphElementInit sHeadJntSphElementsInit1[] = {
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_HARD,
            BUMP_ON,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
};

static ColliderJntSphInit sHeadJntSphInit1 = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sHeadJntSphElementsInit1),
    sHeadJntSphElementsInit1,
};

static ColliderJntSphElementInit sHeadJntSphElementsInit2[] = {
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7FFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_HARD,
            BUMP_ON,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 15 }, 100 },
    },
};

static ColliderJntSphInit sHeadJntSphInit2 = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sHeadJntSphElementsInit2),
    sHeadJntSphElementsInit2, // sJntSphElementsInit,
};

Color_RGBA8 D_809F1BEC = { 170, 255, 255, 255 };
Color_RGBA8 D_809F1BF0 = { 200, 200, 255, 255 };
Vec3f D_809F1BF4 = { 0.0f, -1.0f, 0.0f };

static DamageTable sDamageTable1 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(3, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(3, 0x0),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xE),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(3, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(3, 0xF),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
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

static DamageTable sDamageTable2 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(3, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x1),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, 0x2),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

ActorInit Boss_05_InitVars = {
    /**/ ACTOR_BOSS_05,
    /**/ ACTORCAT_ENEMY,
    /**/ FLAGS,
    /**/ OBJECT_BOSS05,
    /**/ sizeof(Boss05),
    /**/ Boss05_Init,
    /**/ Boss05_Destroy,
    /**/ Boss05_Update,
    /**/ Boss05_Draw,
};

void Boss05_WalkingHead_Thaw(Boss05* this, PlayState* play) {
    Vec3f icePos;
    Vec3f iceVelocity;
    s32 i;

    SoundSource_PlaySfxAtFixedWorldPos(play, &this->bodyPartsPos[0], 30, NA_SE_EV_ICE_BROKEN);
    for (i = 0; i < 8; i++) {
        iceVelocity.x = Rand_CenteredFloat(7.0f);
        iceVelocity.z = Rand_CenteredFloat(7.0f);
        iceVelocity.y = Rand_ZeroFloat(6.0f) + 4.0f;
        icePos.x = this->bodyPartsPos[0].x + iceVelocity.x;
        icePos.y = this->bodyPartsPos[0].y + iceVelocity.y;
        icePos.z = this->bodyPartsPos[0].z + iceVelocity.z;
        EffectSsEnIce_Spawn(play, &icePos, Rand_ZeroFloat(0.5f) + 0.7f, &iceVelocity, &D_809F1BF4, &D_809F1BEC,
                            &D_809F1BF0, 30);
    }
}

/**
 * Manually sets the position of a sphere collider to a specific position.
 */
void Boss05_SetColliderSphere(s32 index, ColliderJntSph* collider, Vec3f* sphereCenter) {
    collider->elements[index].dim.worldSphere.center.x = sphereCenter->x;
    collider->elements[index].dim.worldSphere.center.y = sphereCenter->y;
    collider->elements[index].dim.worldSphere.center.z = sphereCenter->z;
    collider->elements[index].dim.worldSphere.radius =
        collider->elements[index].dim.modelSphere.radius * collider->elements[index].dim.scale;
}

void Boss05_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    Boss05* this = THIS;
    CollisionHeader* colHeader = NULL;

    this->dyna.actor.targetMode = TARGET_MODE_3;
    this->dyna.actor.colChkInfo.mass = MASS_HEAVY;
    this->dyna.actor.colChkInfo.health = 2;
    this->frameCounter = (s32)Rand_ZeroFloat(1000.0f);
    this->lowerJawScaleXZ = 1.0f;
    this->dyna.actor.gravity = -0.3f;

    Actor_SetScale(&this->dyna.actor, 0.01f);

    if ((this->dyna.actor.params == BIO_DEKU_BABA_LILY_PAD_WITH_HEAD) ||
        (this->dyna.actor.params == BIO_DEKU_BABA_NO_LEAF_LILY_PAD_WITH_HEAD)) {
        if (this->dyna.actor.world.rot.z == 0) {
            this->dyna.actor.world.rot.z = 0;
        }

        this->dyna.actor.shape.rot.z = 0;
        this->unk168 = this->dyna.actor.world.rot.z;
        this->dyna.actor.world.rot.z = this->dyna.actor.shape.rot.z;
        this->dyna.actor.colChkInfo.damageTable = &sDamageTable1;

        DynaPolyActor_Init(&this->dyna, 0);
        CollisionHeader_GetVirtual(&sBioBabaLilypadCol, &colHeader);
        this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);
        Boss05_LilyPadWithHead_SetupMove(this, play);

        SkelAnime_InitFlex(play, &this->lilyPadSkelAnime, &gBioDekuBabaLilyPadSkel, &gBioDekuBabaLilyPadIdleAnim,
                           this->lilyPadJointTable, this->lilyPadMorphTable, BIO_DEKU_BABA_LILY_PAD_LIMB_MAX);
        SkelAnime_InitFlex(play, &this->headSkelAnime, &gBioDekuBabaHeadSkel, &gBioDekuBabaHeadChompAnim,
                           this->headJointTable, this->headMorphTable, BIO_DEKU_BABA_HEAD_LIMB_MAX);
        this->animEndFrame = Animation_GetLastFrame(&gBioDekuBabaHeadChompAnim);

        Collider_InitAndSetJntSph(play, &this->lilyPadCollider, &this->dyna.actor, &sLilyPadJntSphInit,
                                  this->lilyPadColliderElements);
        Collider_InitAndSetJntSph(play, &this->headCollider, &this->dyna.actor, &sHeadJntSphInit1,
                                  this->headColliderElements);

        if (Flags_GetClear(play, play->roomCtx.curRoom.num)) {
            this->dyna.actor.params = BIO_DEKU_BABA_TYPE_LILY_PAD;
            this->actionFunc = Boss05_LilyPad_Idle;
            this->dyna.actor.flags &= ~ACTOR_FLAG_TARGETABLE;
            func_800BC154(play, &play->actorCtx, &this->dyna.actor, ACTORCAT_BG);
        }
    } else if (this->dyna.actor.params == BIO_DEKU_BABA_TYPE_LILY_PAD) {
        this->actionFunc = Boss05_LilyPad_Idle;

        CollisionHeader_GetVirtual(&sBioBabaLilypadCol, &colHeader);
        this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);

        SkelAnime_InitFlex(play, &this->lilyPadSkelAnime, &gBioDekuBabaLilyPadSkel, &gBioDekuBabaLilyPadIdleAnim,
                           this->lilyPadJointTable, this->lilyPadMorphTable, BIO_DEKU_BABA_LILY_PAD_LIMB_MAX);
        this->dyna.actor.flags &= ~ACTOR_FLAG_TARGETABLE;
        func_800BC154(play, &play->actorCtx, &this->dyna.actor, ACTORCAT_BG);
    } else if (this->dyna.actor.params == BIO_DEKU_BABA_TYPE_FALLING_HEAD) {
        this->actionFunc = Boss05_FallingHead_Fall;
        this->fallingHeadLimbScale = 1.0f;

        SkelAnime_InitFlex(play, &this->lilyPadSkelAnime, &gBioDekuBabaLilyPadSkel, &gBioDekuBabaLilyPadIdleAnim,
                           this->lilyPadJointTable, this->lilyPadMorphTable, BIO_DEKU_BABA_LILY_PAD_LIMB_MAX);
        SkelAnime_InitFlex(play, &this->headSkelAnime, &gBioDekuBabaHeadSkel, &gBioDekuBabaHeadChompAnim,
                           this->headJointTable, this->headMorphTable, BIO_DEKU_BABA_HEAD_LIMB_MAX);
        this->animEndFrame = Animation_GetLastFrame(&gBioDekuBabaHeadChompAnim);

        Collider_InitAndSetJntSph(play, &this->lilyPadCollider, &this->dyna.actor, &sLilyPadJntSphInit,
                                  this->lilyPadColliderElements);
        Collider_InitAndSetJntSph(play, &this->headCollider, &this->dyna.actor, &sHeadJntSphInit1,
                                  this->headColliderElements);

        ActorShape_Init(&this->dyna.actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
        this->dyna.actor.colChkInfo.damageTable = &sDamageTable1;
    } else if (this->dyna.actor.params == BIO_DEKU_BABA_TYPE_WALKING_HEAD) {
        Boss05_WalkingHead_SetupTransform(this, play);
        this->dyna.actor.colChkInfo.mass = 90;

        SkelAnime_InitFlex(play, &this->headSkelAnime, &gBioDekuBabaHeadSkel, &gBioDekuBabaHeadChompAnim,
                           this->headJointTable, this->headMorphTable, BIO_DEKU_BABA_HEAD_LIMB_MAX);

        Collider_InitAndSetJntSph(play, &this->headCollider, &this->dyna.actor, &sHeadJntSphInit2,
                                  this->headColliderElements);

        ActorShape_Init(&this->dyna.actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
        this->dyna.actor.colChkInfo.damageTable = &sDamageTable2;
        this->dyna.actor.flags |= ACTOR_FLAG_10 | ACTOR_FLAG_20;
    } else if (this->dyna.actor.params >= BIO_DEKU_BABA_TYPE_FRAGMENT_LOWER_JAW) {
        SkelAnime_InitFlex(play, &this->headSkelAnime, &gBioDekuBabaHeadSkel, &gBioDekuBabaHeadChompAnim,
                           this->headJointTable, this->headMorphTable, BIO_DEKU_BABA_HEAD_LIMB_MAX);

        this->dyna.actor.gravity = 0.0f;
        this->dyna.actor.world.rot.y = (s32)Rand_ZeroFloat(0x8000);
        this->dyna.actor.speed = Rand_ZeroFloat(3.0f) + 3.0f;
        this->dyna.actor.velocity.y = Rand_ZeroFloat(1.5f) + 1.5f;

        this->unk500.x = (s32)Rand_CenteredFloat(700.0f);
        this->unk500.y = (s32)Rand_CenteredFloat(1500.0f);
        this->unk162[0] = (s32)(Rand_ZeroFloat(30.0f) + 50.0f);

        this->dyna.actor.flags &= ~ACTOR_FLAG_TARGETABLE;
        this->actionFunc = Boss05_Fragment_Move;
    }
}

void Boss05_Destroy(Actor* thisx, PlayState* play) {
    Boss05* this = THIS;

    if ((this->dyna.actor.params == BIO_DEKU_BABA_TYPE_LILY_PAD) ||
        (this->dyna.actor.params == BIO_DEKU_BABA_LILY_PAD_WITH_HEAD) ||
        (this->dyna.actor.params == BIO_DEKU_BABA_NO_LEAF_LILY_PAD_WITH_HEAD)) {
        DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
    }
}

s32 Boss05_LilyPadWithHead_UpdateDamage(Boss05* this, PlayState* play) {
    if (this->unk16C == 0) {
        s32 i = 0;

        while (true) {
            if (this->lilyPadCollider.elements[i].info.bumperFlags & BUMP_HIT) {
                switch (this->dyna.actor.colChkInfo.damageEffect) {
                    case 2:
                        return 11;
                    case 3:
                        return 20;
                    case 4:
                        return 30;
                    default:
                        return 10;
                }
            }

            i++;
            if (i == 2) {
                if (this->headCollider.elements[0].info.bumperFlags & BUMP_HIT) {
                    u8 damage = this->dyna.actor.colChkInfo.damage;
                    this->dyna.actor.colChkInfo.health -= damage;
                    if ((s8)this->dyna.actor.colChkInfo.health <= 0) {
                        Enemy_StartFinishingBlow(play, &this->dyna.actor);
                        return 2;
                    } else {
                        Actor_PlaySfx(&this->dyna.actor, NA_SE_EN_MIZUBABA2_DAMAGE);
                        this->unk16C = 15;
                        this->unk15C = 0;
                        this->unk162[0] = 30;
                        return 0;
                    }
                }

                break;
            }
        }
    }

    return 0;
}

void Boss05_LilyPadWithHead_SetupMove(Boss05* this, PlayState* play) {
    this->actionFunc = Boss05_LilyPadWithHead_Move;
}

Vec3s D_809F1C60[7] = {
    { 0x3200, 0, 0 }, { -0x1E00, 0, 0 }, { -0x1400, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
};
Vec3s D_809F1C8C[7] = {
    { -0x3200, 0, 0 }, { 0, 0, 0 }, { 0x1E00, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
};

void Boss05_LilyPadWithHead_Move(Boss05* this, PlayState* play) {
    s32 i;
    Player* sp108 = GET_PLAYER(play);
    s32 j;
    u8 sp103 = 0;
    Vec3s spD8[7];
    s32 spD4;
    s32 spD0;
    s32 spCC;
    s32 spC8;
    s32 spC4;
    s32 spC0;
    s32 spBC;
    s32 spB8;
    s32 spB4;
    s32 var_s6;
    s32 var_s7;
    s16 var_s5;
    s16 var_s4;
    f32 spA4;
    f32 var_fv1;
    Vec3f sp94;
    s32 var_s4_2;

    this->dyna.actor.hintId = TATL_HINT_ID_BIO_DEKU_BABA;

    if (this->unk174 == 0) {
        spD4 = 0x3E8;
        spD0 = 0x3E80;
        spCC = 0x7D0;

        spC8 = 0x5DC;
        spC4 = 0x1770;
        spC0 = 0xBB8;

        spBC = 0x514;
        spB8 = 0x5208;
        spB4 = 0xDAC;

        var_s6 = 0xA;
        var_s7 = 0x300;

        if (this->unk16C != 0) {
            spD4 = 0x1B58;
            spCC = 0x1770;

            spC0 = 0x1770;

            spBC = 0x1C84;
            spB4 = 0x1964;

            var_s6 = 1;
            var_s7 = 0x1000;
        }
    } else if (this->unk174 == 3) {
        spD4 = 0x1B58;
        spD0 = 0x3E80;
        spCC = 0x1388;

        spC8 = 0x5DC;
        spC4 = 0x2328;
        spC0 = 0x1388;

        spBC = 0x1C84;
        spB8 = 0x5208;
        spB4 = 0x157C;

        var_s6 = 1;
        var_s7 = 0x1000;
    } else {
        spD4 = spD0 = spCC = spC8 = spC4 = spC0 = spBC = spB8 = spB4 = var_s6 = var_s7 = 0;
    }

    for (i = 0; i < 7; i++) {
        if ((this->unk174 == 0) || (this->unk174 == 3)) {
            if (i < 3) {
                spD8[i].y = 0;
                spD8[i].x = (s32)(Math_SinS((this->frameCounter * spD4) + (i * spD0)) * spCC);
            } else {
                spD8[i].x = 0;
                spD8[i].y = (s32)(Math_SinS((this->frameCounter * spC8) + (i * spC4)) * spC0);
            }

            if ((i == 4) || (i == 6)) {
                spD8[i].z = (s32)(Math_SinS((this->frameCounter * spBC) + (i * spB8)) * spB4 * 2.0f);
            } else {
                spD8[i].z = (s32)(Math_SinS((this->frameCounter * spBC) + (i * spB8)) * spB4);
            }

            var_s4 = var_s6;
            var_s5 = var_s7;
        } else {
            if (this->unk174 == 1) {
                var_s6 = 5;
                var_s7 = 0x1000;

                spD8[i].x = D_809F1C60[i].x;
                spD8[i].y = D_809F1C60[i].y;
                spD8[i].z = D_809F1C60[i].z;
            } else if (this->unk174 == 2) {
                var_s6 = 1;
                var_s7 = 0x2000;

                spD8[i].x = D_809F1C8C[i].x;
                spD8[i].y = D_809F1C8C[i].y;
                spD8[i].z = D_809F1C8C[i].z;
            }
            var_s4 = var_s6;
            var_s5 = var_s7;
        }

        Math_ApproachS(&this->unk19E[i].x, spD8[i].x, var_s6, var_s7);
        Math_ApproachS(&this->unk19E[i].y, spD8[i].y, var_s6, var_s7);
        Math_ApproachS(&this->unk19E[i].z, spD8[i].z, var_s6, var_s7);
    }

    spA4 = (sp108->actor.world.pos.y - this->dyna.actor.world.pos.y) + 10.0f;
    if (spA4 < 0.0f) {
        Math_ApproachS(&this->dyna.actor.shape.rot.y, this->dyna.actor.yawTowardsPlayer, var_s4, var_s5);
    }

    SkelAnime_Update(&this->headSkelAnime);
    Math_ApproachF(&this->lowerJawScaleXZ, 1.0f, 0.1f, 0.1f);

    if (this->unk15C != 10) {
        Math_ApproachS(&this->dyna.actor.shape.rot.x, 0, 0x14, 0x800);
    }

    switch (this->unk15C) {
        case 0:
            this->unk174 = 0;
            this->headSkelAnime.playSpeed = 1.0f;
            if (spA4 < 0.0f) {
                if (sp108->actor.speed > 10.0f) {
                    var_fv1 = 220.0f;
                } else {
                    var_fv1 = 150.0f;
                }
                if ((this->unk162[0] == 0) && (sqrtf(this->dyna.actor.xyzDistToPlayerSq) <= var_fv1)) {
                    this->unk15C = 1;
                    this->unk162[0] = 10;
                }
                this->unk15E = 0;
            } else {
                sp103 = 1;

                if (sqrtf(this->dyna.actor.xyzDistToPlayerSq) <= 40.0f) {
                    this->unk15E++;
                    if (this->unk15E > 30) {
                        this->unk15C = 10;
                        this->unk162[0] = 30;
                        Actor_PlaySfx(&this->dyna.actor, NA_SE_EN_MIZUBABA1_ATTACK);
                    }
                } else {
                    this->unk15E = 0;
                }
            }
            if (((this->frameCounter % 4) == 0) && (Rand_ZeroOne() < 0.5f)) {
                Actor_PlaySfx(&this->dyna.actor, NA_SE_EN_MIZUBABA1_MOUTH);
            }
            break;

        case 10:
            if ((this->frameCounter % 2) == 0) {
                Actor_PlaySfx(&this->dyna.actor, NA_SE_EN_MIZUBABA1_MOUTH);
            }
            this->unk19C = (this->unk162[0] & 1) * 0x200;
            this->unk174 = 3;
            this->headSkelAnime.playSpeed = 4.0f;
            Math_ApproachS(&this->dyna.actor.shape.rot.x, -0x8000, 2, 0x2000);
            Math_ApproachS(&this->dyna.actor.shape.rot.y, this->dyna.actor.yawTowardsPlayer, 2, 0x2000);
            if (this->unk162[0] == 0) {
                this->unk15E = 0;
                this->unk15C = 0;
                this->unk162[0] = 100;
            }
            if (this->unk162[0] == 27) {
                Math_Vec3f_Copy(&sp94, &this->dyna.actor.world.pos);
                sp94.y += 40.0f;
                EffectSsGSplash_Spawn(play, &sp94, NULL, NULL, 1, 2000);
                Actor_PlaySfx(&this->dyna.actor, NA_SE_EV_OUT_OF_WATER);
            }
            break;

        case 1:
            if (Animation_OnFrame(&this->headSkelAnime, this->animEndFrame)) {
                this->headSkelAnime.playSpeed = 0.0f;
            }
            this->unk174 = 1;
            if (this->unk162[0] == 0) {
                this->unk15C = 2;
                this->unk162[0] = 20;
                Actor_PlaySfx(&this->dyna.actor, NA_SE_EN_MIZUBABA1_ATTACK);
            }
            break;

        case 2:
            if ((this->frameCounter % 2) == 0) {
                Actor_PlaySfx(&this->dyna.actor, NA_SE_EN_MIZUBABA1_MOUTH);
            }
            this->unk19C = (this->unk162[0] & 1) * 0x200;
            this->headSkelAnime.playSpeed = 4.0f;
            Math_ApproachF(&this->lowerJawScaleXZ, 1.5f, 1.0f, 0.7f);
            this->unk174 = 2;
            if (this->unk162[0] == 0) {
                this->unk15C = 0;
                this->unk162[0] = 30;
            }
            break;
    }

    var_s4_2 = Boss05_LilyPadWithHead_UpdateDamage(this, play);
    if ((var_s4_2 != 0) || (this->unk168 == 1)) {
        Boss05* temp_v0_6;

        this->dyna.actor.params = BIO_DEKU_BABA_TYPE_LILY_PAD;
        this->actionFunc = Boss05_LilyPad_Idle;
        this->dyna.actor.flags &= ~ACTOR_FLAG_TARGETABLE;
        func_800BC154(play, &play->actorCtx, &this->dyna.actor, ACTORCAT_BG);
        if (this->unk168 != 0) {
            var_s4_2 = 10;
        }

        if (var_s4_2 >= 10) {
            temp_v0_6 = (Boss05*)Actor_SpawnAsChild(
                &play->actorCtx, &this->dyna.actor, play, ACTOR_BOSS_05, this->dyna.actor.world.pos.x,
                this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, this->dyna.actor.shape.rot.x,
                this->dyna.actor.shape.rot.y, this->dyna.actor.shape.rot.z, BIO_DEKU_BABA_TYPE_FALLING_HEAD);

            if (temp_v0_6 != NULL) {
                Player* player = GET_PLAYER(play);

                if (player->lockOnActor == &this->dyna.actor) {
                    player->lockOnActor = &temp_v0_6->dyna.actor;
                    play->actorCtx.targetCtx.fairyActor = &temp_v0_6->dyna.actor;
                    play->actorCtx.targetCtx.lockOnActor = &temp_v0_6->dyna.actor;
                }

                for (i = 0; i < BIO_DEKU_BABA_LILY_PAD_LIMB_MAX; i++) {
                    temp_v0_6->lilyPadSkelAnime.jointTable[i] = this->lilyPadSkelAnime.jointTable[i];
                }

                for (i = 0; i < BIO_DEKU_BABA_HEAD_LIMB_MAX; i++) {
                    temp_v0_6->headSkelAnime.jointTable[i] = this->headSkelAnime.jointTable[i];
                }

                Actor_PlaySfx(&this->dyna.actor, NA_SE_EN_MIZUBABA1_DAMAGE);
                if (var_s4_2 > 10) {
                    temp_v0_6->drawDmgEffState = var_s4_2 - 10;
                }
            }
        } else if (var_s4_2 == 2) {
            for (i = 0; i < 2; i++) {
                temp_v0_6 =
                    (Boss05*)Actor_SpawnAsChild(&play->actorCtx, &this->dyna.actor, play, ACTOR_BOSS_05, this->unk324.x,
                                                this->unk324.y, this->unk324.z, this->unk330.x, this->unk330.y,
                                                this->unk330.z, i + BIO_DEKU_BABA_TYPE_FRAGMENT_LOWER_JAW);
                if (temp_v0_6 != NULL) {
                    for (j = 0; j < BIO_DEKU_BABA_HEAD_LIMB_MAX; j++) {
                        temp_v0_6->headSkelAnime.jointTable[j] = this->headSkelAnime.jointTable[j];
                    }

                    temp_v0_6->unk162[0] = (s32)(Rand_ZeroFloat(20.0f) + 20.0f);
                }
            }
            Actor_PlaySfx(&this->dyna.actor, NA_SE_EN_MIZUBABA_DEAD);
        }
    }

    if (sp103 == 0) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->lilyPadCollider.base);
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->headCollider.base);
    }

    CollisionCheck_SetAC(play, &play->colChkCtx, &this->lilyPadCollider.base);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->headCollider.base);
}

void Boss05_LilyPad_Idle(Boss05* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 distToPlayer = sqrtf(this->dyna.actor.xyzDistToPlayerSq);
    s16 var_a1;

    if ((distToPlayer < 50.0f) && (player->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
        var_a1 = (s32)(distToPlayer * 80.0f);
        var_a1 = CLAMP_MAX(var_a1, 0x7D0);

        Math_ApproachS(&this->unk178, var_a1, 0x14, 0x7D0);
        Math_ApproachS(&this->unk176, this->dyna.actor.yawTowardsPlayer, 0x14, 0xFA0);
        if ((this->frameCounter % 16) == 0) {
            EffectSsGRipple_Spawn(play, &this->dyna.actor.world.pos, 500, 1000, 0);
        }
    } else {
        Math_ApproachS(&this->unk178, 0, 0x14, 0x100);
    }
}

void Boss05_FallingHead_Fall(Boss05* this, PlayState* play) {
    s32 i;
    Vec3f unusedPos;
    Vec3f bubblePos;
    Boss05* temp_v0;
    Player* player;

    Actor_MoveWithGravity(&this->dyna.actor);
    this->dyna.actor.world.pos.y -= 85.0f;
    this->dyna.actor.prevPos.y -= 85.0f;
    Actor_UpdateBgCheckInfo(play, &this->dyna.actor, 20.0f, 50.0f, 40.0f,
                            UPDBGCHECKINFO_FLAG_4 | UPDBGCHECKINFO_FLAG_40);
    this->dyna.actor.world.pos.y += 85.0f;
    this->dyna.actor.prevPos.y += 85.0f;

    if (this->dyna.actor.bgCheckFlags & BGCHECKFLAG_WATER) {
        this->dyna.actor.gravity = -0.3f;
        this->dyna.actor.terminalVelocity = -5.0f;
    } else {
        this->dyna.actor.gravity = -2.0f;
        this->dyna.actor.terminalVelocity = -20.0f;
    }

    if (this->dyna.actor.bgCheckFlags & BGCHECKFLAG_WATER_TOUCH) {
        this->dyna.actor.velocity.y = -3.0f;
        this->dyna.actor.gravity = -0.3f;
        this->dyna.actor.terminalVelocity = -5.0f;
        Math_Vec3f_Copy(&unusedPos, &this->dyna.actor.world.pos);
        unusedPos.y += 20.0f;
        EffectSsGSplash_Spawn(play, &this->dyna.actor.world.pos, NULL, NULL, 1, 1000);
        this->unk162[2] = 20;
    }

    if (this->unk162[2] != 0) {
        for (i = 0; i < 3; i++) {
            bubblePos.x = Rand_CenteredFloat(40.0f) + this->dyna.actor.world.pos.x;
            bubblePos.y = Rand_CenteredFloat(40.0f) + this->dyna.actor.world.pos.y;
            bubblePos.z = Rand_CenteredFloat(40.0f) + this->dyna.actor.world.pos.z;
            EffectSsBubble_Spawn(play, &bubblePos, 20.0f, 10.0f, 20.0f, 0.13f);
        }
    }

    if (this->dyna.actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        if ((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) && (this->drawDmgEffTimer != 0)) {
            this->drawDmgEffTimer = 0;
        }

        Math_ApproachZeroF(&this->fallingHeadLimbScale, 1.0f, 0.05f);

        if (this->fallingHeadLimbScale == 0.0f) {
            temp_v0 = (Boss05*)Actor_SpawnAsChild(&play->actorCtx, &this->dyna.actor, play, ACTOR_BOSS_05,
                                                  this->unk324.x, this->unk324.y, this->unk324.z, this->unk330.x,
                                                  this->unk330.y, this->unk330.z, BIO_DEKU_BABA_TYPE_WALKING_HEAD);

            if (temp_v0 != NULL) {
                player = GET_PLAYER(play);
                if (player->lockOnActor == &this->dyna.actor) {
                    player->lockOnActor = &temp_v0->dyna.actor;
                    play->actorCtx.targetCtx.fairyActor = &temp_v0->dyna.actor;
                    play->actorCtx.targetCtx.lockOnActor = &temp_v0->dyna.actor;
                }

                for (i = 0; i < BIO_DEKU_BABA_HEAD_LIMB_MAX; i++) {
                    temp_v0->headSkelAnime.jointTable[i] = this->headSkelAnime.jointTable[i];
                }

                Actor_PlaySfx(&temp_v0->dyna.actor, NA_SE_EN_MIZUBABA_TRANSFORM);
            }
            Actor_Kill(&this->dyna.actor);
        }
    }
}

void Boss05_WalkingHead_UpdateDamage(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss05* this = THIS;
    u8 attackDealsDamage = false;
    ColliderInfo* hitInfo;

    if ((this->unk16A == 0) && (this->headCollider.elements[0].info.bumperFlags & BUMP_HIT)) {
        this->headCollider.elements[0].info.bumperFlags &= ~BUMP_HIT;
        hitInfo = this->headCollider.elements[0].info.acHitInfo;
        if (hitInfo->toucher.dmgFlags & 0x300000) { // (DMG_NORMAL_SHIELD | DMG_LIGHT_RAY)
            this->unk338 = -12.0f;
            this->unk348 = this->dyna.actor.yawTowardsPlayer;
            this->unk16A = 6;
            return;
        }

        this->unk16A = 10;
        this->dyna.actor.speed = 0.0f;
        this->unk338 = -20.0f;
        this->unk348 = this->dyna.actor.yawTowardsPlayer;

        Actor_PlaySfx(&this->dyna.actor, NA_SE_EN_MIZUBABA2_DAMAGE);

        switch (this->dyna.actor.colChkInfo.damageEffect) {
            case 1:
                Boss05_WalkingHead_SetupStunned(this, play);
                break;

            case 2:
                this->drawDmgEffState = 1;
                attackDealsDamage = true;
                break;

            case 3:
                Boss05_WalkingHead_SetupFreeze(this, play);
                this->drawDmgEffState = 10;
                break;

            case 4:
                this->drawDmgEffState = 20;
                attackDealsDamage = true;
                break;

            default:
                attackDealsDamage = true;
                break;
        }

        if (attackDealsDamage) {
            u8 damage;

            if ((this->actionFunc == Boss05_WalkingHead_Stunned) &&
                (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) && (this->drawDmgEffTimer != 0)) {
                Boss05_WalkingHead_Thaw(this, play);
                this->drawDmgEffState = 0;
            }

            damage = this->dyna.actor.colChkInfo.damage;
            this->dyna.actor.colChkInfo.health -= damage;
            if ((s8)this->dyna.actor.colChkInfo.health <= 0) {
                Enemy_StartFinishingBlow(play, &this->dyna.actor);
            }

            Boss05_WalkingHead_SetupDamaged(this, play);
            this->unk16C = 15;
        }
    }
}

s32 Boss05_WalkingHead_IsLookingAtPlayer(Boss05* this, PlayState* play) {
    s16 yawDiff = this->dyna.actor.yawTowardsPlayer - this->dyna.actor.shape.rot.y;

    if (ABS_ALT(yawDiff) < 0x3000) {
        return true;
    } else {
        return false;
    }
}

void Boss05_WalkingHead_CheckIfPlayerWasSpotted(Boss05* this, PlayState* play) {
    if (Boss05_WalkingHead_IsLookingAtPlayer(this, play) && (this->dyna.actor.xyzDistToPlayerSq <= SQ(200.0f)) &&
        (fabsf(this->dyna.actor.playerHeightRel) < 70.0f)) {
        Boss05_WalkingHead_SetupSpottedPlayer(this, play);
    }
}

void Boss05_WalkingHead_SetupTransform(Boss05* this, PlayState* play) {
    this->actionFunc = Boss05_WalkingHead_Transform;
    Animation_MorphToPlayOnce(&this->headSkelAnime, &gBioDekuBabaHeadTransformAnim, -5.0f);
}

void Boss05_WalkingHead_Transform(Boss05* this, PlayState* play) {
    SkelAnime_Update(&this->headSkelAnime);
    Math_ApproachS(&this->dyna.actor.shape.rot.x, 0, 2, 0x400);
    Math_ApproachS(&this->dyna.actor.shape.rot.z, 0, 2, 0x400);
    Math_ApproachF(&this->bodyScale, 1.0f, 1.0f, 0.5f);
    Math_ApproachF(&this->limbScale, 1.0f, 1.0f, 0.14f);

    if (this->limbScale == 1.0f) {
        Boss05_WalkingHead_SetupIdle(this, play);
    }
}

void Boss05_WalkingHead_SetupIdle(Boss05* this, PlayState* play) {
    this->actionFunc = Boss05_WalkingHead_Idle;
    Animation_MorphToLoop(&this->headSkelAnime, &gBioDekuBabaHeadIdleAnim, -10.0f);
    this->unk162[0] = (s32)(Rand_ZeroFloat(25.0f) + 25.0f);
    Actor_PlaySfx(&this->dyna.actor, NA_SE_EN_MIZUBABA1_MOUTH);
}

void Boss05_WalkingHead_Idle(Boss05* this, PlayState* play) {
    SkelAnime_Update(&this->headSkelAnime);
    Math_ApproachZeroF(&this->dyna.actor.speed, 1.0f, 2.5f);
    Math_ApproachS(&this->dyna.actor.shape.rot.x, 0, 2, 0x400);
    Math_ApproachS(&this->dyna.actor.shape.rot.z, 0, 2, 0x400);

    if (this->unk162[0] == 0) {
        Boss05_WalkingHead_SetupWalk(this, play);
    }

    Boss05_WalkingHead_CheckIfPlayerWasSpotted(this, play);
}

void Boss05_WalkingHead_SetupWalk(Boss05* this, PlayState* play) {
    this->actionFunc = Boss05_WalkingHead_Walk;
    Animation_MorphToLoop(&this->headSkelAnime, &gBioDekuBabaHeadWalkAnim, 0.0f);
    this->unk162[0] = (s32)(Rand_ZeroFloat(80.0f) + 60.0f);
    this->unk34C.x = Rand_CenteredFloat(400.0f) + this->dyna.actor.world.pos.x;
    this->unk34C.z = Rand_CenteredFloat(400.0f) + this->dyna.actor.world.pos.z;
    this->unk358 = 0.0f;
}

void Boss05_WalkingHead_Walk(Boss05* this, PlayState* play) {
    f32 deltaX;
    f32 deltaZ;

    Actor_PlaySfx(&this->dyna.actor, NA_SE_EN_MIZUBABA2_WALK - SFX_FLAG);
    SkelAnime_Update(&this->headSkelAnime);
    Math_ApproachF(&this->dyna.actor.speed, 5.0f, 1.0f, 2.0f);
    deltaX = this->unk34C.x - this->dyna.actor.world.pos.x;
    deltaZ = this->unk34C.z - this->dyna.actor.world.pos.z;
    Math_ApproachS(&this->dyna.actor.world.rot.y, Math_Atan2S(deltaX, deltaZ), 5, (s32)this->unk358);
    Math_ApproachF(&this->unk358, 2000.0f, 1.0f, 100.0f);

    if ((this->unk162[0] == 0) || ((SQ(deltaX) + SQ(deltaZ)) < 2500.0f)) {
        Boss05_WalkingHead_SetupIdle(this, play);
    }

    Boss05_WalkingHead_CheckIfPlayerWasSpotted(this, play);
}

void Boss05_WalkingHead_SetupSpottedPlayer(Boss05* this, PlayState* play) {
    this->actionFunc = Boss05_WalkingHead_SpottedPlayer;
    Animation_MorphToPlayOnce(&this->headSkelAnime, &gBioDekuBabaHeadSpotAnim, 0.0f);
    this->unk162[0] = 20;
}

void Boss05_WalkingHead_SpottedPlayer(Boss05* this, PlayState* play) {
    SkelAnime_Update(&this->headSkelAnime);
    Actor_PlaySfx(&this->dyna.actor, NA_SE_EN_MIZUBABA2_VOICE - SFX_FLAG);
    Math_ApproachZeroF(&this->dyna.actor.speed, 1.0f, 2.5f);
    Math_ApproachS(&this->dyna.actor.world.rot.y, this->dyna.actor.yawTowardsPlayer, 5, 0x1000);
    if (this->unk162[0] == 0) {
        Boss05_WalkingHead_SetupCharge(this, play);
    }
}

void Boss05_WalkingHead_SetupCharge(Boss05* this, PlayState* arg1) {
    this->actionFunc = Boss05_WalkingHead_Charge;
    Animation_MorphToLoop(&this->headSkelAnime, &gBioDekuBabaHeadChargeAnim, 0.0f);
    this->unk162[0] = 60;
    this->unk358 = 0.0f;
}

void Boss05_WalkingHead_Charge(Boss05* this, PlayState* play) {
    Actor_PlaySfx(&this->dyna.actor, NA_SE_EN_MIZUBABA2_VOICE - SFX_FLAG);
    SkelAnime_Update(&this->headSkelAnime);
    Math_ApproachF(&this->dyna.actor.speed, 8.0f, 1.0f, 4.0f);
    Math_ApproachS(&this->dyna.actor.world.rot.y, this->dyna.actor.yawTowardsPlayer, 5, (s32)this->unk358);
    Math_ApproachF(&this->unk358, 4000.0f, 1.0f, 400.0f);

    if ((this->unk162[0] == 0) || (this->dyna.actor.xyzDistToPlayerSq <= SQ(150.0f))) {
        Boss05_WalkingHead_SetupAttack(this, play);
    }
}

void Boss05_WalkingHead_SetupAttack(Boss05* this, PlayState* arg1) {
    this->actionFunc = Boss05_WalkingHead_Attack;
    Animation_MorphToPlayOnce(&this->headSkelAnime, &gBioDekuBabaHeadAttackAnim, 0.0f);
    this->animEndFrame = Animation_GetLastFrame(&gBioDekuBabaHeadAttackAnim);
    Actor_PlaySfx(&this->dyna.actor, NA_SE_EN_MIZUBABA2_ATTACK);
}

void Boss05_WalkingHead_Attack(Boss05* this, PlayState* play) {
    SkelAnime_Update(&this->headSkelAnime);
    if (Animation_OnFrame(&this->headSkelAnime, this->animEndFrame)) {
        Boss05_WalkingHead_SetupIdle(this, play);
    }
}

void Boss05_WalkingHead_SetupDamaged(Boss05* this, PlayState* play) {
    this->actionFunc = Boss05_WalkingHead_Damaged;
    Animation_MorphToPlayOnce(&this->headSkelAnime, &gBioDekuBabaHeadDamagedAnim, 0.0f);
    this->animEndFrame = Animation_GetLastFrame(&gBioDekuBabaHeadAttackAnim);
    Actor_SetColorFilter(&this->dyna.actor, COLORFILTER_COLORFLAG_RED, 120, COLORFILTER_BUFFLAG_OPA, 30);
}

void Boss05_WalkingHead_Damaged(Boss05* this, PlayState* play) {
    s32 i;
    s32 j;
    Vec3f bubblePos;
    Boss05* fragment;

    SkelAnime_Update(&this->headSkelAnime);
    if ((s8)this->dyna.actor.colChkInfo.health <= 0) {
        if (Animation_OnFrame(&this->headSkelAnime, 22.0f)) {
            for (i = 0; i < 14; i++) {
                fragment = (Boss05*)Actor_SpawnAsChild(
                    &play->actorCtx, &this->dyna.actor, play, ACTOR_BOSS_05, this->dyna.actor.world.pos.x,
                    this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, this->dyna.actor.shape.rot.x,
                    this->dyna.actor.shape.rot.y, this->dyna.actor.shape.rot.z, i + BIO_DEKU_BABA_TYPE_FRAGMENT_BASE);

                if (fragment != NULL) {
                    for (j = 0; j < BIO_DEKU_BABA_HEAD_LIMB_MAX; j++) {
                        fragment->headSkelAnime.jointTable[j] = this->headSkelAnime.jointTable[j];
                    }
                }
            }

            for (i = 0; i < 20; i++) {
                bubblePos.x = Rand_CenteredFloat(40.0f) + this->dyna.actor.world.pos.x;
                bubblePos.y = Rand_CenteredFloat(40.0f) + this->dyna.actor.world.pos.y;
                bubblePos.z = Rand_CenteredFloat(40.0f) + this->dyna.actor.world.pos.z;
                EffectSsBubble_Spawn(play, &bubblePos, 20.0f, 10.0f, 20.0f, 0.13f);
            }

            SoundSource_PlaySfxAtFixedWorldPos(play, &this->dyna.actor.world.pos, 40, NA_SE_EN_MIZUBABA_DEAD);
            Actor_Kill(&this->dyna.actor);
            Item_DropCollectibleRandom(play, NULL, &this->dyna.actor.world.pos, 0xE0);
        }
    } else if (Animation_OnFrame(&this->headSkelAnime, this->animEndFrame)) {
        Boss05_WalkingHead_SetupSpottedPlayer(this, play);
    }
}

void Boss05_WalkingHead_SetupStunned(Boss05* this, PlayState* play) {
    this->actionFunc = Boss05_WalkingHead_Stunned;
    Actor_PlaySfx(&this->dyna.actor, NA_SE_EN_MIZUBABA2_DAMAGE);
    this->unk162[0] = 40;
    Actor_SetColorFilter(&this->dyna.actor, COLORFILTER_COLORFLAG_BLUE, 120, COLORFILTER_BUFFLAG_OPA, 40);
}

void Boss05_WalkingHead_SetupFreeze(Boss05* this, PlayState* play) {
    this->actionFunc = Boss05_WalkingHead_Stunned;
    Actor_PlaySfx(&this->dyna.actor, NA_SE_EN_MIZUBABA2_DAMAGE);
    this->unk162[0] = 80;
    Actor_SetColorFilter(&this->dyna.actor, COLORFILTER_COLORFLAG_BLUE, 120, COLORFILTER_BUFFLAG_OPA, 80);
}

void Boss05_WalkingHead_Stunned(Boss05* this, PlayState* play) {
    Math_ApproachZeroF(&this->dyna.actor.speed, 1.0f, 2.5f);
    if (this->unk162[0] == 0) {
        Boss05_WalkingHead_SetupIdle(this, play);
    }
}

void Boss05_Fragment_Move(Boss05* this, PlayState* play) {
    Actor_MoveWithGravity(&this->dyna.actor);

    if (this->unk15C == 0) {
        Actor_UpdateBgCheckInfo(play, &this->dyna.actor, 20.0f, 50.0f, 40.0f,
                                UPDBGCHECKINFO_FLAG_4 | UPDBGCHECKINFO_FLAG_40);
        if (this->dyna.actor.bgCheckFlags & BGCHECKFLAG_WATER) {
            this->unk15C = 1;
        } else {
            this->unk15C = 2;
        }
    }

    if (this->unk15C == 1) {
        Math_ApproachF(&this->dyna.actor.velocity.y, 1.0f, 1.0f, 0.1f);
        Math_ApproachZeroF(&this->dyna.actor.speed, 0.5f, 0.5f);
        this->dyna.actor.shape.rot.x += this->unk500.x;
        this->dyna.actor.shape.rot.y += this->unk500.y;

        if (this->unk162[0] == 0) {
            Actor_Kill(&this->dyna.actor);
        }
    } else {
        switch (this->unk15C) {
            case 2:
                this->dyna.actor.velocity.y = Rand_ZeroFloat(3.0f) + 3.0f;
                this->dyna.actor.speed = Rand_CenteredFloat(5.0f) + 5.0f;
                this->dyna.actor.world.rot.y = (s32)Rand_ZeroFloat(0x10000);
                this->dyna.actor.gravity = -1.0f;
                this->unk15C = 3;
                break;

            case 3:
                Actor_MoveWithGravity(&this->dyna.actor);

                if (this->unk324.y < (this->dyna.actor.floorHeight - 30.0f)) {
                    Actor_Kill(&this->dyna.actor);
                }
                break;

            default:
                break;
        }
    }
}

void Boss05_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    Boss05* this = (Boss05*)thisx;
    s16 i;

    this->frameCounter++;

    for (i = 0; i < ARRAY_COUNT(this->unk162); i++) {
        DECR(this->unk162[i]);
    }

    DECR(this->unk16A);
    DECR(this->unk16C);
    DECR(this->unk168);
    DECR(this->drawDmgEffTimer);

    this->actionFunc(this, play);

    if (this->dyna.actor.params == BIO_DEKU_BABA_TYPE_WALKING_HEAD) {
        Actor_MoveWithGravity(&this->dyna.actor);
        Matrix_RotateYS(this->unk348, MTXMODE_NEW);
        Matrix_MultVecZ(this->unk338, &this->unk33C);
        this->dyna.actor.world.pos.x += this->unk33C.x;
        this->dyna.actor.world.pos.z += this->unk33C.z;
        Math_ApproachZeroF(&this->unk338, 1.0f, 1.0f);
        Actor_UpdateBgCheckInfo(play, &this->dyna.actor, 20.0f, 50.0f, 40.0f,
                                UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_4 | UPDBGCHECKINFO_FLAG_40);
        Boss05_WalkingHead_UpdateDamage(&this->dyna.actor, play);
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->headCollider.base);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->headCollider.base);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->headCollider.base);
        this->dyna.actor.shape.rot.y = this->dyna.actor.world.rot.y;
    }

    switch (this->drawDmgEffState) {
        case 0:
            this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
            this->drawDmgEffTimer = 0;
            this->drawDmgEffAlpha = 0.0f;
            break;

        case 1:
            this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
            this->drawDmgEffTimer = 80;
            this->drawDmgEffAlpha = 1.0f;
            this->drawDmgEffState++;
            this->drawDmgEffScale = 0.0f;
            // fallthrough
        case 2:
            if (this->drawDmgEffTimer == 0) {
                Math_ApproachZeroF(&this->drawDmgEffAlpha, 1.0f, 0.02f);
                if (this->drawDmgEffAlpha == 0.0f) {
                    this->drawDmgEffState = 0;
                }
            } else {
                Math_ApproachF(&this->drawDmgEffScale, 1.0f, 0.1f, 0.5f);
            }
            break;

        case 10:
            this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX;
            this->drawDmgEffTimer = 80;
            this->drawDmgEffAlpha = 1.0f;
            this->drawDmgEffState++;
            this->drawDmgEffScale = 0.0f;
            this->dmgEffFrozenSteamScale = 2.0f;
            // fallthrough
        case 11:
            if (this->drawDmgEffTimer == 0) {
                Boss05_WalkingHead_Thaw(this, play);
                this->drawDmgEffState = 0;
            } else {
                Math_ApproachF(&this->drawDmgEffScale, 1.0f, 1.0f, 0.25f);
                Math_ApproachF(&this->dmgEffFrozenSteamScale, 1.0f, 0.1f, 0.1f);
            }
            break;

        case 20:
            this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
            this->drawDmgEffTimer = 80;
            this->drawDmgEffAlpha = 1.0f;
            this->drawDmgEffState++;
            this->drawDmgEffScale = 0.0f;
            break;

        case 21:
            if (this->drawDmgEffTimer == 0) {
                Math_ApproachZeroF(&this->drawDmgEffScale, 1.0f, 0.03f);

                if (this->drawDmgEffScale == 0.0f) {
                    this->drawDmgEffState = 0;
                    this->drawDmgEffAlpha = 0.0f;
                }
            } else {
                Math_ApproachF(&this->drawDmgEffScale, 1.0f, 0.5f, 0.5f);
            }
            break;
    }
}

s8 D_809F1CB8[] = {
    -1, // BIO_DEKU_BABA_LILY_PAD_LIMB_NONE
    -1, // BIO_DEKU_BABA_LILY_PAD_LIMB_ROOTS
    0,  // BIO_DEKU_BABA_LILY_PAD_LIMB_UPPER_STEM
    1,  // BIO_DEKU_BABA_LILY_PAD_LIMB_MIDDLE_STEM
    2,  // BIO_DEKU_BABA_LILY_PAD_LIMB_LOWER_STEM
    3,  // BIO_DEKU_BABA_LILY_PAD_LIMB_LEFT_UPPER_ARM
    4,  // BIO_DEKU_BABA_LILY_PAD_LIMB_LEFT_LOWER_ARM
    5,  // BIO_DEKU_BABA_LILY_PAD_LIMB_RIGHT_UPPER_ARM
    6,  // BIO_DEKU_BABA_LILY_PAD_LIMB_RIGHT_LOWER_ARM
    -1, // BIO_DEKU_BABA_LILY_PAD_LIMB_LEAF
    -1, // BIO_DEKU_BABA_LILY_PAD_LIMB_MAX
};

s32 Boss05_OverrideLimbDraw_LilyPadWithHead(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                            Actor* thisx) {
    Boss05* this = THIS;
    s8 temp_v1;

    if (limbIndex == KREG(32)) {
        if ((this->frameCounter % 4) == 0) {
            *dList = NULL;
        }

        rot->x += KREG(33) * 0x100;
        rot->y += KREG(34) * 0x100;
        rot->z += KREG(35) * 0x100;
    }

    if ((this->dyna.actor.params == BIO_DEKU_BABA_NO_LEAF_LILY_PAD_WITH_HEAD) &&
        (limbIndex == BIO_DEKU_BABA_LILY_PAD_LIMB_LEAF)) {
        *dList = NULL;
    }

    if (limbIndex == BIO_DEKU_BABA_LILY_PAD_LIMB_UPPER_STEM) {
        rot->x += this->unk19C;
    }

    temp_v1 = D_809F1CB8[limbIndex];
    if (temp_v1 >= 0) {
        rot->x = rot->x + this->unk19E[temp_v1].x;
        rot->y = rot->y + this->unk19E[temp_v1].y;
        rot->z = rot->z + this->unk19E[temp_v1].z;
    }

    return false;
}

Vec3f D_809F1CC4 = { 0.0f, -1400.0f, 600.0f };

void Boss05_PostLimbDraw_LilyPad(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    Boss05* this = THIS;
    MtxF mf;
    Vec3f spherePos0;
    Vec3f spherePos1;

    if (limbIndex == BIO_DEKU_BABA_LILY_PAD_LIMB_LOWER_STEM) {
        Matrix_MultVec3f(&D_809F1CC4, &this->unk324);

        if (this->actionFunc == Boss05_FallingHead_Fall) {
            Matrix_MultVec3f(&D_809F1CC4, &this->dyna.actor.focus.pos);
        }

        Matrix_Get(&mf);
        Matrix_MtxFToYXZRot(&mf, &this->unk330, false);
        this->unk330.x += 0xF00;
    }

    if (limbIndex == BIO_DEKU_BABA_LILY_PAD_LIMB_UPPER_STEM) {
        Matrix_MultZero(&spherePos0);
        Boss05_SetColliderSphere(0, &this->lilyPadCollider, &spherePos0);
    }

    if (limbIndex == BIO_DEKU_BABA_LILY_PAD_LIMB_MIDDLE_STEM) {
        Matrix_MultVecY(-500.0f, &spherePos1);
        Boss05_SetColliderSphere(1, &this->lilyPadCollider, &spherePos1);

        if (this->actionFunc == Boss05_LilyPadWithHead_Move) {
            Matrix_MultVecY(1500.0f, &this->dyna.actor.focus.pos);
        }
    }
}

s32 Boss05_OverrideLimbDraw_Head(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return false;
}

Vec3f D_809F1CD0 = { 1600.0f, -300.0f, 0.0f };
Vec3f D_809F1CDC = { 700.0f, 0.0f, 0.0f };

Vec3f D_809F2110;

void Boss05_PostLimbDraw_Head(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    Boss05* this = THIS;

    if (limbIndex == BIO_DEKU_BABA_HEAD_LIMB_BODY) {
        Matrix_MultVec3f(&D_809F1CD0, &D_809F2110);
        Boss05_SetColliderSphere(0, &this->headCollider, &D_809F2110);

        if (this->dyna.actor.params == BIO_DEKU_BABA_TYPE_WALKING_HEAD) {
            Matrix_MultVec3f(&D_809F1CDC, &thisx->focus.pos);
        }

        if (this->drawDmgEffState != 0) {
            Matrix_MultVec3f(&D_809F1CDC, &this->bodyPartsPos[0]);
            if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FIRE) {
                this->bodyPartsPos[0].y -= 15.0f;
            }
        }
    }
}

void Boss05_TransformLimbDraw_Head(PlayState* play, s32 limbIndex, Actor* thisx) {
    Boss05* this = THIS;

    if ((limbIndex == BIO_DEKU_BABA_HEAD_LIMB_LOWER_JAW) || (limbIndex == BIO_DEKU_BABA_HEAD_LIMB_UPPER_JAW)) {
        Matrix_Scale(this->lowerJawScaleXZ, 1.0f, this->lowerJawScaleXZ, MTXMODE_APPLY);
    }

    if (limbIndex == BIO_DEKU_BABA_HEAD_LIMB_BODY) {
        Matrix_Scale(this->bodyScale, this->bodyScale, this->bodyScale, MTXMODE_APPLY);
    }

    if ((limbIndex >= BIO_DEKU_BABA_HEAD_LIMB_BACK_UPPER_LEG) && (limbIndex <= BIO_DEKU_BABA_HEAD_LIMB_LEAVES)) {
        Matrix_Scale(this->limbScale, this->limbScale, this->limbScale, MTXMODE_APPLY);
    }
}

s32 Boss05_OverrideLimbDraw_LilyPad(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if ((limbIndex >= BIO_DEKU_BABA_LILY_PAD_LIMB_MIDDLE_STEM) &&
        (limbIndex <= BIO_DEKU_BABA_LILY_PAD_LIMB_RIGHT_LOWER_ARM)) {
        *dList = NULL;
    }

    return false;
}

s32 Boss05_OverrideLimbDraw_FallingHeadLilyPad(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                               Actor* thisx) {
    if ((limbIndex == BIO_DEKU_BABA_LILY_PAD_LIMB_ROOTS) || (limbIndex == BIO_DEKU_BABA_LILY_PAD_LIMB_UPPER_STEM) ||
        (limbIndex == BIO_DEKU_BABA_LILY_PAD_LIMB_LEAF)) {
        *dList = NULL;
    }

    return false;
}

void Boss05_TransformLimbDraw_FallingHeadLilyPad(PlayState* play, s32 limbIndex, Actor* thisx) {
    Boss05* this = THIS;

    if ((limbIndex >= BIO_DEKU_BABA_LILY_PAD_LIMB_MIDDLE_STEM) &&
        (limbIndex <= BIO_DEKU_BABA_LILY_PAD_LIMB_RIGHT_LOWER_ARM)) {
        Matrix_Scale(this->fallingHeadLimbScale, this->fallingHeadLimbScale, this->fallingHeadLimbScale, MTXMODE_APPLY);
    }
}

BioDekuBabaHeadLimb D_809F1CE8[] = {
    BIO_DEKU_BABA_HEAD_LIMB_LOWER_JAW,            // BIO_DEKU_BABA_TYPE_FRAGMENT_LOWER_JAW
    BIO_DEKU_BABA_HEAD_LIMB_UPPER_JAW,            // BIO_DEKU_BABA_TYPE_FRAGMENT_UPPER_JAW
    BIO_DEKU_BABA_HEAD_LIMB_BODY,                 // BIO_DEKU_BABA_TYPE_FRAGMENT_BODY
    BIO_DEKU_BABA_HEAD_LIMB_BACK_UPPER_LEG,       // BIO_DEKU_BABA_TYPE_FRAGMENT_BACK_UPPER_LEG
    BIO_DEKU_BABA_HEAD_LIMB_BACK_LOWER_LEG,       // BIO_DEKU_BABA_TYPE_FRAGMENT_BACK_LOWER_LEG
    BIO_DEKU_BABA_HEAD_LIMB_LEFT_UPPER_LEG,       // BIO_DEKU_BABA_TYPE_FRAGMENT_LEFT_UPPER_LEG
    BIO_DEKU_BABA_HEAD_LIMB_LEFT_LOWER_LEG,       // BIO_DEKU_BABA_TYPE_FRAGMENT_LEFT_LOWER_LEG
    BIO_DEKU_BABA_HEAD_LIMB_LEFT_LOWER_EYESTALK,  // BIO_DEKU_BABA_TYPE_FRAGMENT_LEFT_LOWER_EYESTALK
    BIO_DEKU_BABA_HEAD_LIMB_LEFT_UPPER_EYESTALK,  // BIO_DEKU_BABA_TYPE_FRAGMENT_LEFT_UPPER_EYESTALK
    BIO_DEKU_BABA_HEAD_LIMB_RIGHT_LOWER_EYESTALK, // BIO_DEKU_BABA_TYPE_FRAGMENT_RIGHT_LOWER_EYESTALK
    BIO_DEKU_BABA_HEAD_LIMB_RIGHT_UPPER_EYESTALK, // BIO_DEKU_BABA_TYPE_FRAGMENT_RIGHT_UPPER_EYESTALK
    BIO_DEKU_BABA_HEAD_LIMB_RIGHT_UPPER_LEG,      // BIO_DEKU_BABA_TYPE_FRAGMENT_RIGHT_UPPER_LEG
    BIO_DEKU_BABA_HEAD_LIMB_RIGHT_LOWER_LEG,      // BIO_DEKU_BABA_TYPE_FRAGMENT_RIGHT_LOWER_LEG
    BIO_DEKU_BABA_HEAD_LIMB_LEAVES,               // BIO_DEKU_BABA_TYPE_FRAGMENT_LEAVES
};

s32 Boss05_OverrideLimbDraw_Fragment(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                     Actor* thisx) {
    Boss05* this = THIS;

    if (limbIndex != D_809F1CE8[this->dyna.actor.params - BIO_DEKU_BABA_TYPE_FRAGMENT_BASE]) {
        *dList = NULL;
    } else if (this->unk15C >= 2) {
        rot->x += this->frameCounter * 0x3000;
        rot->y += this->frameCounter * 0x1A00;
        rot->z += this->frameCounter * 0x2000;
    }
    return false;
}

void Boss05_PostLimbDraw_Fragment(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    Boss05* this = THIS;

    if (limbIndex != D_809F1CE8[this->dyna.actor.params - BIO_DEKU_BABA_TYPE_FRAGMENT_BASE]) {
        Matrix_MultZero(&this->unk324);
    }
}

void Boss05_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    Boss05* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);

    if (this->actionFunc == Boss05_LilyPadWithHead_Move) {
        SkelAnime_DrawFlexOpa(play, this->lilyPadSkelAnime.skeleton, this->lilyPadSkelAnime.jointTable,
                              this->lilyPadSkelAnime.dListCount, Boss05_OverrideLimbDraw_LilyPadWithHead,
                              Boss05_PostLimbDraw_LilyPad, &this->dyna.actor);

        if ((this->unk16C % 2) != 0) {
            POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
        }

        Matrix_Translate(this->unk324.x, this->unk324.y, this->unk324.z, MTXMODE_NEW);
        Matrix_RotateYS(this->unk330.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->unk330.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->unk330.z, MTXMODE_APPLY);
        Matrix_Scale(this->dyna.actor.scale.x, this->dyna.actor.scale.y, this->dyna.actor.scale.z, MTXMODE_APPLY);

        AnimatedMat_Draw(play, Lib_SegmentedToVirtual(gBioDekuBabaHeadEyeFlashTexAnim));

        SkelAnime_DrawTransformFlexOpa(play, this->headSkelAnime.skeleton, this->headSkelAnime.jointTable,
                                       this->headSkelAnime.dListCount, Boss05_OverrideLimbDraw_Head,
                                       Boss05_PostLimbDraw_Head, Boss05_TransformLimbDraw_Head, &this->dyna.actor);
    } else if (this->dyna.actor.params == BIO_DEKU_BABA_TYPE_LILY_PAD) {
        Matrix_Translate(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z,
                         MTXMODE_NEW);
        Matrix_RotateYS(this->unk176, MTXMODE_APPLY);
        Matrix_RotateXS(this->unk178, MTXMODE_APPLY);
        Matrix_RotateYS(-this->unk176, MTXMODE_APPLY);
        Matrix_RotateYS(this->dyna.actor.shape.rot.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->dyna.actor.shape.rot.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->dyna.actor.shape.rot.z, MTXMODE_APPLY);
        Matrix_Scale(this->dyna.actor.scale.x, this->dyna.actor.scale.y, this->dyna.actor.scale.z, MTXMODE_APPLY);

        SkelAnime_DrawFlexOpa(play, this->lilyPadSkelAnime.skeleton, this->lilyPadSkelAnime.jointTable,
                              this->lilyPadSkelAnime.dListCount, Boss05_OverrideLimbDraw_LilyPad, NULL,
                              &this->dyna.actor);
    } else if (this->dyna.actor.params == BIO_DEKU_BABA_TYPE_FALLING_HEAD) {
        SkelAnime_DrawTransformFlexOpa(play, this->lilyPadSkelAnime.skeleton, this->lilyPadSkelAnime.jointTable,
                                       this->lilyPadSkelAnime.dListCount, Boss05_OverrideLimbDraw_FallingHeadLilyPad,
                                       Boss05_PostLimbDraw_LilyPad, Boss05_TransformLimbDraw_FallingHeadLilyPad,
                                       &this->dyna.actor);

        Matrix_Translate(this->unk324.x, this->unk324.y, this->unk324.z, MTXMODE_NEW);
        Matrix_RotateYS(this->unk330.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->unk330.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->unk330.z, MTXMODE_APPLY);
        Matrix_Scale(this->dyna.actor.scale.x, this->dyna.actor.scale.y, this->dyna.actor.scale.z, MTXMODE_APPLY);

        AnimatedMat_Draw(play, Lib_SegmentedToVirtual(gBioDekuBabaHeadEyeFlashTexAnim));

        SkelAnime_DrawTransformFlexOpa(play, this->headSkelAnime.skeleton, this->headSkelAnime.jointTable,
                                       this->headSkelAnime.dListCount, Boss05_OverrideLimbDraw_Head,
                                       Boss05_PostLimbDraw_Head, Boss05_TransformLimbDraw_Head, &this->dyna.actor);

        Actor_DrawDamageEffects(play, &this->dyna.actor, this->bodyPartsPos, ARRAY_COUNT(this->bodyPartsPos),
                                this->drawDmgEffScale, this->dmgEffFrozenSteamScale, this->drawDmgEffAlpha,
                                this->drawDmgEffType);
    } else if (this->dyna.actor.params == BIO_DEKU_BABA_TYPE_WALKING_HEAD) {
        AnimatedMat_Draw(play, Lib_SegmentedToVirtual(gBioDekuBabaHeadEyeFlashTexAnim));

        if ((this->unk16C % 2) != 0) {
            POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
        }

        SkelAnime_DrawTransformFlexOpa(play, this->headSkelAnime.skeleton, this->headSkelAnime.jointTable,
                                       this->headSkelAnime.dListCount, Boss05_OverrideLimbDraw_Head,
                                       Boss05_PostLimbDraw_Head, Boss05_TransformLimbDraw_Head, &this->dyna.actor);

        Actor_DrawDamageEffects(play, &this->dyna.actor, this->bodyPartsPos, ARRAY_COUNT(this->bodyPartsPos),
                                this->drawDmgEffScale, this->dmgEffFrozenSteamScale, this->drawDmgEffAlpha,
                                this->drawDmgEffType);
    } else if (this->dyna.actor.params >= BIO_DEKU_BABA_TYPE_FRAGMENT_LOWER_JAW) {
        AnimatedMat_Draw(play, Lib_SegmentedToVirtual(gBioDekuBabaHeadEyeFlashTexAnim));

        SkelAnime_DrawFlexOpa(play, this->headSkelAnime.skeleton, this->headSkelAnime.jointTable,
                              this->headSkelAnime.dListCount, Boss05_OverrideLimbDraw_Fragment,
                              Boss05_PostLimbDraw_Fragment, &this->dyna.actor);
    }

    POLY_OPA_DISP = Play_SetFog(play, POLY_OPA_DISP);

    CLOSE_DISPS(play->state.gfxCtx);
}
