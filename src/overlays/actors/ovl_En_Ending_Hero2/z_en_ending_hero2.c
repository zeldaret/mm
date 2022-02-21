/*
 * File: z_en_ending_hero2.c
 * Overlay: ovl_En_Ending_Hero2
 * Description: Viscen watching moon disappearance and wedding
 */

#include "z_en_ending_hero2.h"
#include "objects/object_bai/object_bai.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnEndingHero2*)thisx)

void EnEndingHero2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero2_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C232E8(EnEndingHero2* this);
void func_80C23304(EnEndingHero2* this, GlobalContext* globalCtx);

const ActorInit En_Ending_Hero2_InitVars = {
    ACTOR_EN_ENDING_HERO2,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BAI,
    sizeof(EnEndingHero2),
    (ActorFunc)EnEndingHero2_Init,
    (ActorFunc)EnEndingHero2_Destroy,
    (ActorFunc)EnEndingHero2_Update,
    (ActorFunc)EnEndingHero2_Draw,
};

void EnEndingHero2_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero2* this = THIS;

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.targetMode = 6;
    this->actor.gravity = -3.0f;
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_bai_Skel_007908, &object_bai_Anim_0011C0, this->jointTable,
                       this->morphTable, 20);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    func_80C232E8(this);
}

void EnEndingHero2_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80C232E8(EnEndingHero2* this) {
    this->unk27C = 1;
    this->actionFunc = func_80C23304;
}

void func_80C23304(EnEndingHero2* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
}

void EnEndingHero2_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero2* this = THIS;

    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 50.0f, 0x1D);
}

void EnEndingHero2_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero2* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          NULL, NULL, &this->actor);
}
