/*
 * File: z_en_rat.c
 * Overlay: ovl_En_Rat
 * Description: Real Bombchu
 */

#include "z_en_rat.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_200)

#define THIS ((EnRat*)thisx)

void EnRat_Init(Actor* thisx, PlayState* play);
void EnRat_Destroy(Actor* thisx, PlayState* play);
void EnRat_Update(Actor* thisx, PlayState* play);
void EnRat_Draw(Actor* thisx, PlayState* play);

void func_80A563CC(EnRat* this);
void func_80A5665C(EnRat* this);
void func_80A57330(EnRat* this);

#if 0
const ActorInit En_Rat_InitVars = {
    ACTOR_EN_RAT,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RAT,
    sizeof(EnRat),
    (ActorFunc)EnRat_Init,
    (ActorFunc)EnRat_Destroy,
    (ActorFunc)EnRat_Update,
    (ActorFunc)EnRat_Draw,
};

// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_80A58400 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 1, { { 0, 0, 0 }, 23 }, 100 },
};

// static DamageTable sDamageTable = {
static DamageTable D_80A5842C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x0),
    /* Ice arrow      */ DMG_ENTRY(2, 0x0),
    /* Light arrow    */ DMG_ENTRY(2, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
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
static CollisionCheckInfoInit D_80A5844C = { 1, 30, 30, 50 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A58464[] = {
    ICHAIN_S8(hintId, 97, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 15, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 5000, ICHAIN_STOP),
};

#endif

extern ColliderSphereInit D_80A58400;
extern DamageTable D_80A5842C;
extern CollisionCheckInfoInit D_80A5844C;
extern InitChainEntry D_80A58464[];

extern UNK_TYPE D_06000174;
extern AnimationHeader D_0600026C;
extern FlexSkeletonHeader D_06001858;

extern s16 D_80A58428;
extern TexturePtr D_80A58454[];
extern EffectBlureInit2 D_80A58470;
extern s32 D_80A58494;

void EnRat_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnRat* this = THIS;
    s32 temp_s1;
    s32 i;

    Actor_ProcessInitChain(&this->actor, D_80A58464);
    Collider_InitAndSetSphere(play, &this->collider, &this->actor, &D_80A58400);
    this->collider.dim.worldSphere.radius = D_80A58428;

    temp_s1 = this->actor.params & 0xFF;
    if (ENRAT_GET_8000(&this->actor)) {
        this->actor.params = 1;
    } else {
        this->actor.params = 0;
    }

    SkelAnime_InitFlex(play, &this->skelAnime, &D_06001858, &D_0600026C, this->jointTable, this->morphTable, 10);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    if (this->actor.params == 0) {
        Effect_Add(play, &this->unk_260, EFFECT_BLURE2, 0, 0, &D_80A58470);
        Effect_Add(play, &this->unk_264, EFFECT_BLURE2, 0, 0, &D_80A58470);
        this->unk_190 = 0x1E;
    } else {
        this->unk_190 = 0x96;
    }

    CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_80A5842C, &D_80A5844C);
    func_80A563CC(this);
    func_80A5665C(this);

    if ((temp_s1 == 0xFF) || (temp_s1 == 0)) {
        this->unk_258 = 350.0f;
    } else if (this->actor.params == 0) {
        this->unk_258 = temp_s1 * 0.1f * 40.0f;
    } else {
        this->unk_258 = temp_s1 * 0.5f * 40.0f;
    }

    if (!D_80A58494) {
        for (i = 0; i < 4; i++) {
            D_80A58454[i] = Lib_SegmentedToVirtual(D_80A58454[i]);
        }

        D_80A58494 = true;
    }

    func_80A57330(this);
}

void EnRat_Destroy(Actor* thisx, PlayState* play) {
    EnRat* this = THIS;

    if (this->actor.params == 0) {
        Effect_Destroy(play, this->unk_260);
        Effect_Destroy(play, this->unk_264);
    }

    Collider_DestroySphere(play, &this->collider);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A563CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A56444.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A5665C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A566E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A56994.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A56AFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A56EB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A56F68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57010.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57118.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57180.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A5723C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57330.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57384.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A574E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A575F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A5764C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57918.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57A08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57A9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/EnRat_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57F10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57F4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/EnRat_Draw.s")
