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
    this->unk_204[0] = 50;
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
    this->unk_204[0] = 6;
    this->actor.speedXZ = 10.0f;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_KONB_MINI_DEAD);
}

void func_80BB9288(EnTanron3* this, GlobalContext* globalCtx) {
    Actor_SetVelocityAndMoveXYRotationReverse(&this->actor);
    if (this->unk_204[0] == 0) {
        func_80BB87D4(this, globalCtx);
        Actor_MarkForDeath(&this->actor);
        if (Rand_ZeroOne() < 0.3f) {
            Item_DropCollectibleRandom(globalCtx, NULL, &this->actor.world.pos, 0x60);
        }
    }
}

void func_80BB9308(EnTanron3* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (player->actor.world.pos.y > 350.0f) {
        if (this->collider1.base.atFlags & AT_HIT) {
            this->collider1.base.atFlags &= ~AT_HIT;
            func_800B8D50(globalCtx, NULL, 3.0f, Math_FAtan2F(-player->actor.world.pos.z, -player->actor.world.pos.x),
                          5.0f, 0);
        }
    }
    if (this->collider2.base.acFlags & AC_HIT) {
        this->collider2.base.acFlags &= ~AC_HIT;
        if (this->unk_20A == 0) {
            this->unk_20A = 15;
            this->unk_20C = 15;
            func_80BB91D4(this, globalCtx);
            D_80BB972C->unk_324 = 20;
        }
    }
}

void EnTanron3_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnTanron3* this = THIS;
    s16 i;
    Vec3f sp38;

    if (KREG(63) == 0) {
        this->unk_200 += 1;
        for (i = 0; i < 3; i++) {
            if (this->unk_204[i] != 0) {
                this->unk_204[i]--;
            }
        }
        if (this->unk_20A != 0) {
            this->unk_20A--;
        }
        if (this->unk_20C != 0) {
            this->unk_20C--;
        }
        this->actionFunc(this, globalCtx);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 10.0f, 10.0f, 20.0f, 5);
        if (((this->actor.prevPos.y < this->unk_244) && (this->unk_244 <= this->actor.world.pos.y)) ||
            ((this->actor.prevPos.y > this->unk_244) && (this->unk_244 >= this->actor.world.pos.y))) {
            sp38.x = this->actor.world.pos.x;
            sp38.y = this->unk_244 + 10.0f;
            sp38.z = this->actor.world.pos.z;
            EffectSsGSplash_Spawn(globalCtx, &sp38, NULL, NULL, 1, 500);
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_OUT_OF_WATER);
        }
    }
    func_80BB9308(this, globalCtx);
    Collider_UpdateCylinder(&this->actor, &this->collider1);
    Collider_UpdateCylinder(&this->actor, &this->collider2);
    CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
    if (((s8)D_80BB972C->actor.colChkInfo.health <= 0) && (this->actionFunc != func_80BB9288)) {
        func_80BB91D4(this, globalCtx);
        this->unk_204[0] = 0;
    }
}

s32 func_80BB95FC(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor) {
    EnTanron3* this = (EnTanron3*)actor;

    if (limbIndex == 1) {
        rot->y += this->unk_25C;
    }
    if (limbIndex == 3) {
        rot->y += this->unk_258;
    }
    if (limbIndex == 4) {
        rot->y += this->unk_25A;
    }
    return 0;
}

void EnTanron3_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnTanron3* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    if ((this->unk_20C & 1) != 0) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
    }
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     func_80BB95FC, NULL, &this->actor);
    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
