/*
 * File: z_en_crow.c
 * Overlay: ovl_En_Crow
 * Description: Guay
 */

#include "z_en_crow.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_1000 | ACTOR_FLAG_4000)

#define THIS ((EnCrow*)thisx)

void EnCrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnCrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnCrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnCrow_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_8099AC58(EnCrow* this);
void func_8099AC8C(EnCrow* this, GlobalContext* globalCtx);
void func_8099B0CC(EnCrow* this, GlobalContext* globalCtx);
void func_8099B584(EnCrow* this, GlobalContext* globalCtx);
void func_8099B6C4(EnCrow* this, GlobalContext* globalCtx);
void func_8099B838(EnCrow* this, GlobalContext* globalCtx);
void func_8099B9E8(EnCrow* this, GlobalContext* globalCtx);

const ActorInit En_Crow_InitVars = {
    ACTOR_EN_CROW,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_CROW,
    sizeof(EnCrow),
    (ActorFunc)EnCrow_Init,
    (ActorFunc)EnCrow_Destroy,
    (ActorFunc)EnCrow_Update,
    (ActorFunc)EnCrow_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_8099C070[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_HARD,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 20 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_8099C094 = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    D_8099C070, // sJntSphElementsInit,
};

// sColChkInfoInit
static CollisionCheckInfoInit D_8099C0A4 = { 1, 15, 30, 30 };

// static DamageTable sDamageTable = {
static DamageTable D_8099C0AC = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

s32 D_8099C0CC = 0;

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8099C0D0[] = {
    ICHAIN_F32(uncullZoneForward, 3000, ICHAIN_CONTINUE),
    ICHAIN_S8(hintId, 88, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -500, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_STOP),
};

extern ColliderJntSphElementInit D_8099C070[1];
extern ColliderJntSphInit D_8099C094;
extern CollisionCheckInfoInit D_8099C0A4;
extern DamageTable D_8099C0AC;
extern InitChainEntry D_8099C0D0[];

extern UNK_TYPE D_060000F0;

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/EnCrow_Init.s")
void EnCrow_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnCrow* this = THIS;

    Actor_ProcessInitChain(&this->actor, D_8099C0D0);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_crow_Skel_0010C0, &D_060000F0, &this->unk194, &this->unk1CA,
                       9);
    Collider_InitAndSetJntSph(globalCtx, &this->unk200, &this->actor, &D_8099C094, &this->unk220);
    this->unk200.elements->dim.worldSphere.radius = D_8099C094.elements[0].dim.modelSphere.radius;
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_8099C0AC, &D_8099C0A4);
    ActorShape_Init(&this->actor.shape, 2000.0f, ActorShadow_DrawCircle, 20.0f);
    D_8099C0CC = 0;
    if (this->actor.parent != 0) {
        this->actor.flags &= -2;
    }
    func_8099AC58(this);
}

void EnCrow_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnCrow* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->unk200);
}

void func_8099AC58(EnCrow* this) {
    this->unk18E = 0x64;
    this->unk200.base.acFlags |= 1;
    this->actionFunc = func_8099AC8C;
    this->skelAnime.playSpeed = 1.0f;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099AC8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B098.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B0CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B318.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B384.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B584.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B6AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B6C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B778.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B838.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B8EC.s")

void func_8099B9E8(EnCrow* this, GlobalContext* globalCtx) {
    s16 temp_v0;
    f32 phi_f0;

    DECR(this->unk18E);
    if (this->unk18E == 0) {
        SkelAnime_Update(&this->skelAnime);
        this->actor.draw = EnCrow_Draw;
        if (this->actor.params != 0) {
            phi_f0 = 0.03f;
        } else {
            phi_f0 = 0.01f;
        }
        if (Math_StepToF(&this->actor.scale.x, phi_f0, phi_f0 * 0.1f)) {
            this->actor.flags |= 1;
            this->actor.flags &= ~0x10;
            this->actor.colChkInfo.health = 1;
            func_8099AC58(this);
        }
        this->actor.scale.y = this->actor.scale.x;
        this->actor.scale.z = this->actor.scale.x;
    }
}

void func_8099BAB4(EnCrow* this, GlobalContext* globalCtx) {

    if (this->unk200.base.acFlags & 2) {
        this->unk200.base.acFlags &= ~AT_HIT;
        Actor_SetDropFlag(&this->actor, &this->unk200.elements->info);

        if (this->actor.colChkInfo.damageEffect == 1) {
            func_8099B778(this);

        } else if (this->actor.colChkInfo.damageEffect == 5) {
            this->unk18C = 0x1F;
            this->unk290 = 2.0f;
            this->unk294 = 0.5f;
            func_8099B778(this);

        } else {
            this->actor.colChkInfo.health = 0;
            this->actor.flags &= -2;
            Enemy_StartFinishingBlow(globalCtx, &this->actor);
            func_8099B384(this, globalCtx);
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/EnCrow_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099BE48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099BF20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/EnCrow_Draw.s")
