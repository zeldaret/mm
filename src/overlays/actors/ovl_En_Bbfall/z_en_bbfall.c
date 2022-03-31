/*
 * File: z_en_bbfall.c
 * Overlay: ovl_En_Bbfall
 * Description: Red Bubble
 */

#include "z_en_bbfall.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_200)

#define THIS ((EnBbfall*)thisx)

void EnBbfall_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBbfall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBbfall_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBbfall_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808BF734(EnBbfall* this, GlobalContext* globalCtx);
void func_808BF830(EnBbfall* this, GlobalContext* globalCtx);
void func_808BF8DC(EnBbfall* this, GlobalContext* globalCtx);
void func_808BFA3C(EnBbfall* this, GlobalContext* globalCtx);
void func_808BFB4C(EnBbfall* this, GlobalContext* globalCtx);
void func_808BFE58(EnBbfall* this, GlobalContext* globalCtx);
void func_808C00A0(EnBbfall* this, GlobalContext* globalCtx);
void func_808C0178(EnBbfall* this, GlobalContext* globalCtx);
void func_808BF5E0(EnBbfall* this);
void func_808BF7A0(EnBbfall* this);
void func_808BF894(EnBbfall* this);

#if 0
const ActorInit En_Bbfall_InitVars = {
    ACTOR_EN_BBFALL,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BB,
    sizeof(EnBbfall),
    (ActorFunc)EnBbfall_Init,
    (ActorFunc)EnBbfall_Destroy,
    (ActorFunc)EnBbfall_Update,
    (ActorFunc)EnBbfall_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[3] = {
static ColliderJntSphElementInit D_808C0D30[3] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x01, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x01, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_NONE, OCELEM_NONE, },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x01, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_NONE, OCELEM_NONE, },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_808C0D9C = {
    { COLTYPE_HIT3, AT_NONE | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    3, D_808C0D30, // sJntSphElementsInit,
};

// static DamageTable sDamageTable = {
static DamageTable D_808C0DAC = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xE),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
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

// sColChkInfoInit
static CollisionCheckInfoInit D_808C0DCC = { 2, 20, 40, 50 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808C0DD4[] = {
    ICHAIN_S8(hintId, 36, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 10, ICHAIN_STOP),
};

#endif

extern ColliderJntSphElementInit D_808C0D30[3];
extern ColliderJntSphInit D_808C0D9C;
extern DamageTable D_808C0DAC;
extern CollisionCheckInfoInit D_808C0DCC;
extern InitChainEntry D_808C0DD4[];

extern SkeletonHeader D_06001A30;
extern AnimationHeader D_06000184;
extern AnimationHeader D_06000444;

void EnBbfall_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBbfall* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->actor, D_808C0DD4);
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_06001A30, &D_06000444, this->jointTable, this->morphTable, 16);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_808C0DAC, &D_808C0DCC);
    Collider_InitAndSetJntSph(globalCtx, &this->collider, &this->actor, &D_808C0D9C, this->colliderElements);
    ActorShape_Init(&this->actor.shape, 1500.0f, ActorShadow_DrawCircle, 35.0f);
    this->unk_250 = 0;
    func_808BF5E0(this);
    Actor_SetFocus(&this->actor, 0.0f);
    for (i = 0; i < 3; i++) {
        this->collider.elements[i].dim.worldSphere.radius = this->collider.elements[i].dim.modelSphere.radius;
    }
}

void EnBbfall_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBbfall* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF344.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF3B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF438.s")

void func_808BF4B4(EnBbfall* this) {
    if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 5.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BUBLE_MOUTH);
    }

    func_800B9010(&this->actor, NA_SE_EN_BUBLEFALL_FIRE - SFX_FLAG);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF514.s")

void func_808BF578(EnBbfall* this) {
    this->collider.elements->info.toucher.effect = 1;
    this->collider.elements[1].info.toucherFlags |= 1;
    this->collider.elements[2].info.toucherFlags |= 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF5AC.s")

void func_808BF5E0(EnBbfall* this) {
    s32 i;

    Animation_PlayLoop(&this->skelAnime, &D_06000184);
    this->collider.base.atFlags &= ~AT_ON;
    this->collider.base.acFlags &= ~AC_ON;
    this->collider.base.ocFlags1 &= ~OC1_ON;
    this->unk_254 = 0.8f;
    this->unk_258 = 1.0f;
    this->unk_24C = -1;
    this->actor.colChkInfo.health = D_808C0DCC.health;
    this->actor.colorFilterTimer = 0;
    this->unk_24D = 0;
    this->actor.speedXZ = 0.0f;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.home.pos);
    this->actor.world.pos.y -= 90.0f;
    for (i = 0; i < 6; i++) {
        Math_Vec3f_Copy(&this->unk_268[i], &this->actor.world.pos);
        this->unk_268[i].y -= 47.0f;
    }

    this->actor.bgCheckFlags &= ~1;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actionFunc = func_808BF734;
}

void func_808BF734(EnBbfall* this, GlobalContext* globalCtx) {
    if (this->unk_250 != 0) {
        this->unk_250--;
    } else if ((Player_GetMask(globalCtx) != PLAYER_MASK_STONE) && (this->actor.xyzDistToPlayerSq <= SQ(250.0f))) {
        func_808BF7A0(this);
    }
}

void func_808BF7A0(EnBbfall* this) {
    this->actor.gravity = -1.0f;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    this->collider.base.atFlags |= AT_ON;
    this->collider.base.acFlags |= AC_ON;
    this->collider.base.ocFlags1 |= OC1_ON;
    this->actor.velocity.y = 17.0f;
    func_808BF578(this);
    this->actor.flags |= ACTOR_FLAG_1;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BUBLEFALL_APPEAR);
    this->actionFunc = func_808BF830;
}

void func_808BF830(EnBbfall* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (this->actor.home.pos.y < this->actor.world.pos.y) {
        func_808BF894(this);
    }

    func_808BF4B4(this);
}

void func_808BF894(EnBbfall* this) {
    this->unk_24C = 0xFF;
    this->unk_24D = 1;
    this->actor.bgCheckFlags &= ~1;
    this->actor.speedXZ = 5.0f;
    this->actor.gravity = -1.0f;
    this->actionFunc = func_808BF8DC;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF8DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BFA18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BFA3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BFAB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BFB4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BFCCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BFE58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BFF8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808C00A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808C013C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808C0178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808C01E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/EnBbfall_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808C07D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808C080C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/EnBbfall_Draw.s")
