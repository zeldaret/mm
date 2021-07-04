#include "z_en_ending_hero4.h"

#define FLAGS 0x00000009

#define THIS ((EnEndingHero4*)thisx)

void EnEndingHero4_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero4_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero4_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C23748(EnEndingHero4* this);
void func_80C23764(EnEndingHero4* this, GlobalContext* globalCtx);

const ActorInit En_Ending_Hero4_InitVars = {
    ACTOR_EN_ENDING_HERO4,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SDN,
    sizeof(EnEndingHero4),
    (ActorFunc)EnEndingHero4_Init,
    (ActorFunc)EnEndingHero4_Destroy,
    (ActorFunc)EnEndingHero4_Update,
    (ActorFunc)EnEndingHero4_Draw,
};

extern FlexSkeletonHeader D_0600D640;
extern AnimationHeader D_06002A84;

void EnEndingHero4_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero4* this = THIS;

    this->actor.colChkInfo.mass = 0xFF;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.targetMode = 6;
    this->actor.gravity = -3.0f;
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600D640, &D_06002A84, this->limbDrawTable,
                     this->transitionDrawTable, 17);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 25.0f);
    func_80C23748(this);
}

void EnEndingHero4_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80C23748(EnEndingHero4* this) {
    this->unk258 = 1;
    this->actionFunc = func_80C23764;
}

void func_80C23764(EnEndingHero4* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
}

void EnEndingHero4_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero4* this = THIS;

    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 50.0f, 0x1D);
}

void EnEndingHero4_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero4* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, 0, 0,
                     &this->actor);
}
