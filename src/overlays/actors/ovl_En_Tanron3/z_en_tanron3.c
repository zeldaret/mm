/*
 * File: z_en_tanron3.c
 * Overlay: ovl_En_Tanron3
 * Description: Small Fish summoned by Gyorg
 */

#include "z_en_tanron3.h"
#include "overlays/actors/ovl_Boss_03/z_boss_03.h"

#define FLAGS 0x00000035

#define THIS ((EnTanron3*)thisx)

void EnTanron3_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTanron3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTanron3_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTanron3_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BB897C(EnTanron3* this, GlobalContext* globalCtx);
void func_80BB8A48(EnTanron3* this, GlobalContext* globalCtx);
void func_80BB9288(EnTanron3* this, GlobalContext* globalCtx);

static s32 D_80BB9720[] = { 0x00000000, 0x00000000, 0x00000000 };

static Boss03* D_80BB972C = NULL;

const ActorInit En_Tanron3_InitVars = {
    ACTOR_EN_TANRON3,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS03,
    sizeof(EnTanron3),
    (ActorFunc)EnTanron3_Init,
    (ActorFunc)EnTanron3_Destroy,
    (ActorFunc)EnTanron3_Update,
    (ActorFunc)EnTanron3_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BB9750 = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK3,
        { 0xF7CFFFFF, 0x00, 0x02 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 7, 10, -5, { 0, 0, 0 } },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BB977C = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK3,
        { 0xF7CFFFFF, 0x00, 0x02 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 20, 20, -10, { 0, 0, 0 } },
};

static s32 D_80BB97A8 = 0x643737FF;

static s32 D_80BB97AC = 0x320A0AFF;

extern FlexSkeletonHeader D_0600DA20;
extern AnimationHeader D_0600DAAC;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron3/func_80BB85A0.s")

void EnTanron3_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTanron3* this = THIS;

    this->actor.gravity = -1.0f;
    Collider_InitAndSetCylinder(globalCtx, &this->collider1, &this->actor, &D_80BB9750);
    Collider_InitAndSetCylinder(globalCtx, &this->collider2, &this->actor, &D_80BB9750);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600DA20, &D_0600DAAC, this->jointTable, this->morphTable, 10);
    Actor_SetScale(&this->actor, 0.02f);
    func_80BB897C(this, globalCtx);
    this->actor.flags &= ~1;
    this->unk_250 = (s32)Rand_ZeroFloat(500000.0f);
    this->unk_244 = 430.0f;
    D_80BB972C = (Boss03*)this->actor.parent;
}

void EnTanron3_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    D_80BB972C->unk_252--;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron3/func_80BB87D4.s")

void func_80BB897C(EnTanron3* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80BB8A48;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_0600DAAC, -10.0f);
    this->unk_234 = 0;
    this->unk_238 = 5;
    this->unk_204 = 0x32;
    this->actor.speedXZ = 5.0f;
    this->unk_240 = 0.5f;
    this->unk_228 = randPlusMinusPoint5Scaled(500.0f);
    this->unk_22C = randPlusMinusPoint5Scaled(100.0f);
    this->unk_230 = randPlusMinusPoint5Scaled(500.0f);
    Math_Vec3f_Copy(&this->unk_21C, &this->actor.world.pos);
    this->unk_200 = Rand_ZeroFloat(100.0f);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron3/func_80BB8A48.s")

void func_80BB91D4(EnTanron3* this, GlobalContext* globalCtx) {
    f32 xDistance;
    f32 yDistance;
    f32 zDistance;
    Player* player = GET_PLAYER(globalCtx);

    this->actionFunc = func_80BB9288;
    xDistance = this->actor.world.pos.x - player->actor.world.pos.x;
    yDistance = this->actor.world.pos.y - player->actor.world.pos.y + 30.0f;
    zDistance = this->actor.world.pos.z - player->actor.world.pos.z;
    this->actor.world.rot.x = Math_FAtan2F(sqrtf(SQ(xDistance) + SQ(zDistance)), -yDistance);
    this->actor.world.rot.y = Math_FAtan2F(zDistance, xDistance);
    this->unk_204 = 6;
    this->actor.speedXZ = 10.0f;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_KONB_MINI_DEAD);
}

void func_80BB9288(EnTanron3* this, GlobalContext* globalCtx) {
    Actor_SetVelocityAndMoveXYRotationReverse(&this->actor);
    if (this->unk_204 == 0) {
        func_80BB87D4(this, globalCtx);
        Actor_MarkForDeath(&this->actor);
        if (Rand_ZeroOne() < 0.3f) {
            Item_DropCollectibleRandom(globalCtx, NULL, &this->actor.world.pos, 0x60);
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron3/func_80BB9308.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron3/EnTanron3_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron3/func_80BB95FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron3/EnTanron3_Draw.s")
