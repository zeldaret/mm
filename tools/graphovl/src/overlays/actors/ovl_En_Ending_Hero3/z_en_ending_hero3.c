#include "z_en_ending_hero3.h"

#define FLAGS 0x00000009

#define THIS ((EnEndingHero3*)thisx)

void EnEndingHero3_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero3_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero3_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C23518(EnEndingHero3* this);
void func_80C23534(EnEndingHero3* this, GlobalContext* globalCtx);

const ActorInit En_Ending_Hero3_InitVars = {
    ACTOR_EN_ENDING_HERO3,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TORYO,
    sizeof(EnEndingHero3),
    (ActorFunc)EnEndingHero3_Init,
    (ActorFunc)EnEndingHero3_Destroy,
    (ActorFunc)EnEndingHero3_Update,
    (ActorFunc)EnEndingHero3_Draw,
};

extern FlexSkeletonHeader D_06007150;
extern AnimationHeader D_06000E50;

void EnEndingHero3_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero3* this = THIS;

    this->actor.colChkInfo.mass = 0xFF;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.targetMode = 6;
    this->actor.gravity = -3.0f;
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06007150, &D_06000E50, this->limbDrawTable,
                     this->transitionDrawTable, 17);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 25.0f);
    func_80C23518(this);
}

void EnEndingHero3_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80C23518(EnEndingHero3* this) {
    this->unk258 = 1;
    this->actionFunc = func_80C23534;
}

void func_80C23534(EnEndingHero3* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
}

void EnEndingHero3_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero3* this = THIS;

    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 50.0f, 0x1D);
}

void EnEndingHero3_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero3* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, 0, 0,
                     &this->actor);
}
