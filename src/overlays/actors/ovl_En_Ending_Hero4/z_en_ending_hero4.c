/*
 * File: z_en_ending_hero4.c
 * Overlay: ovl_En_Ending_Hero4
 * Description: Soldiers watching moon disappearance and Indigo-Go's
 */

#include "z_en_ending_hero4.h"
#include "objects/object_sdn/object_sdn.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

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

void EnEndingHero4_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero4* this = THIS;

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.targetMode = 6;
    this->actor.gravity = -3.0f;
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gSoldierSkeleton, &gSoldierCheerWithSpear, this->jointTable,
                       this->morphTable, 17);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    func_80C23748(this);
}

void EnEndingHero4_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80C23748(EnEndingHero4* this) {
    this->unk258 = 1;
    this->actionFunc = func_80C23764;
}

void func_80C23764(EnEndingHero4* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
}

void EnEndingHero4_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero4* this = THIS;

    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 50.0f, 0x1D);
}

void EnEndingHero4_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero4* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          NULL, NULL, &this->actor);
}
