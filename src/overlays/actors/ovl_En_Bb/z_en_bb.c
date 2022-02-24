/*
 * File: z_en_bb.c
 * Overlay: ovl_En_Bb
 * Description: Blue Bubble
 */

#include "z_en_bb.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_200)

#define THIS ((EnBb*)thisx)

void EnBb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBb_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808C23EC(EnBb* this, GlobalContext* globalCtx);
void func_808C25E0(EnBb* this, GlobalContext* globalCtx);
void func_808C28CC(EnBb* this, GlobalContext* globalCtx);
void func_808C2B1C(EnBb* this, GlobalContext* globalCtx);
void func_808C2BD0(EnBb* this, GlobalContext* globalCtx);
void func_808C2CB4(EnBb* this, GlobalContext* globalCtx);
void func_808C2D78(EnBb* this, GlobalContext* globalCtx);
void func_808C20D4(EnBb* this);
void func_808C2238(EnBb* this, GlobalContext* globalCtx);
void func_808C2344(EnBb* this);

#if 0
const ActorInit En_Bb_InitVars = {
    ACTOR_EN_BB,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BB,
    sizeof(EnBb),
    (ActorFunc)EnBb_Init,
    (ActorFunc)EnBb_Destroy,
    (ActorFunc)EnBb_Update,
    (ActorFunc)EnBb_Draw,
};

// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_808C37A0 = {
    { COLTYPE_HIT3, AT_NONE | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 0, { { 0, 0, 0 }, 20 }, 100 },
};

// static DamageTable sDamageTable = {
static DamageTable D_808C37CC = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
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
static CollisionCheckInfoInit D_808C37EC = { 2, 20, 40, 50 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808C37F4[] = {
    ICHAIN_S8(hintId, 28, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 10, ICHAIN_STOP),
};

#endif

extern ColliderSphereInit D_808C37A0;
extern DamageTable D_808C37CC;
extern CollisionCheckInfoInit D_808C37EC;
extern InitChainEntry D_808C37F4[];

extern UNK_TYPE D_06000184;
extern AnimationHeader D_06000444;
extern SkeletonHeader D_06001A30;

void EnBb_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBb* this = THIS;

    Actor_ProcessInitChain(&this->actor, D_808C37F4);
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_06001A30, &D_06000444, this->jointTable, this->morphTable, 16);
    Collider_InitAndSetSphere(globalCtx, &this->collider, &this->actor, &D_808C37A0);
    ActorShape_Init(&this->actor.shape, 1500.0f, ActorShadow_DrawCircle, 35.0f);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_808C37CC, &D_808C37EC);

    this->unk_268 = 0.8f;
    this->unk_264 = 1.0f;
    this->actor.world.pos.y += 50.0f;

    if (EN_BB_GET_RIGHT_SHIFT_8_PARAM(&this->actor) == 0xFF) {
        this->unk_260 = 200.0f;
    } else {
        this->unk_260 = EN_BB_GET_RIGHT_SHIFT_8_PARAM(&this->actor) * 4.0f;
    }

    func_808C20D4(this);
}

void EnBb_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBb* this = THIS;

    Collider_DestroySphere(globalCtx, &this->collider);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C1E94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C1F00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C1F74.s")

void func_808C1FF4(EnBb* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C1FF4.s")

void func_808C20D4(EnBb* this) {
    if (this->actionFunc != func_808C2238) {
        Animation_PlayLoop(&this->skelAnime, &D_06000444);
    }

    if (this->actionFunc == func_808C23EC) {
        this->unk_252 = 0x28;
    } else {
        this->unk_252 = 0;
    }

    this->unk_250 = (s32)Rand_ZeroFloat(20.0f) + 0x28;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->unk_25C = (Math_CosS(this->unk_256) * 10.0f) + 30.0f;
    this->unk_254 = Actor_YawToPoint(&this->actor, &this->actor.home.pos);

    if ((this->actor.xzDistToPlayer < (this->unk_260 + 120.0f)) ||
        (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) < 300.0f)) {
        this->unk_254 += (s16)(Rand_Next() >> 0x11);
    }

    this->collider.base.atFlags |= AT_ON;
    this->unk_258 = Rand_ZeroFloat(1.5f) + 1.0f;
    this->actionFunc = func_808C2238;
}

void func_808C2238(EnBb* this, GlobalContext* globalCtx) {
    func_808C1FF4(this);

    if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BUBLE_WING);
    } else if ((Animation_OnFrame(&this->skelAnime, 0.0f)) && (Rand_ZeroOne() < 0.1f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BUBLE_LAUGH);
    }

    DECR(this->unk_252);
    this->unk_250--;

    if ((this->unk_252 == 0) && (this->actor.xzDistToPlayer < this->unk_260) &&
        (Player_GetMask(globalCtx) != PLAYER_MASK_STONE)) {
        func_808C2344(this);
    } else if (this->unk_250 == 0) {
        func_808C20D4(this);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2344.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C23EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C254C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C25E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C272C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C28CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2A00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2B1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2B94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2BD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2C38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2CB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2CF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2D78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C2E34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/EnBb_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C32EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/func_808C3324.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bb/EnBb_Draw.s")
