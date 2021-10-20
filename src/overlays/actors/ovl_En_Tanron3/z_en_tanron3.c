/*
 * File: z_en_tanron3.c
 * Overlay: ovl_En_Tanron3
 * Description: Small Fish summoned by Gyorg
 */

#include "z_en_tanron3.h"

#define FLAGS 0x00000035

#define THIS ((EnTanron3*)thisx)

void EnTanron3_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTanron3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTanron3_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTanron3_Draw(Actor* thisx, GlobalContext* globalCtx);

static s32 D_80BB9720[] = { 0x00000000, 0x00000000, 0x00000000 };

static Actor* D_80BB972C = NULL;

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
    D_80BB972C = this->actor.parent;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron3/EnTanron3_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron3/func_80BB87D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron3/func_80BB897C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron3/func_80BB8A48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron3/func_80BB91D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron3/func_80BB9288.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron3/func_80BB9308.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron3/EnTanron3_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron3/func_80BB95FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron3/EnTanron3_Draw.s")
