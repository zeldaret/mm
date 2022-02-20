/*
 * File: z_en_ending_hero5.c
 * Overlay: ovl_En_Ending_Hero5
 * Description: Carpenters watching moon disappearance and Indigo-Go's
 */

#include "z_en_ending_hero5.h"
#include "objects/object_daiku/object_daiku.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnEndingHero5*)thisx)

void EnEndingHero5_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero5_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero5_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero5_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C23980(EnEndingHero5* this);
void func_80C2399C(EnEndingHero5* this, GlobalContext* globalCtx);

const ActorInit En_Ending_Hero5_InitVars = {
    ACTOR_EN_ENDING_HERO5,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DAIKU,
    sizeof(EnEndingHero5),
    (ActorFunc)EnEndingHero5_Init,
    (ActorFunc)EnEndingHero5_Destroy,
    (ActorFunc)EnEndingHero5_Update,
    (ActorFunc)EnEndingHero5_Draw,
};

void EnEndingHero5_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero5* this = THIS;

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.targetMode = 6;
    this->actor.gravity = -3.0f;
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_daiku_Skel_00A850, &object_daiku_Anim_002FA0,
                       this->jointTable, this->morphTable, 17);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    this->unk25C = this->actor.params;
    func_80C23980(this);
}

void EnEndingHero5_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80C23980(EnEndingHero5* this) {
    this->unk258 = 1;
    this->actionFunc = func_80C2399C;
}

void func_80C2399C(EnEndingHero5* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
}

void EnEndingHero5_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero5* this = THIS;

    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 50.0f, 0x1D);
}

Gfx* D_80C23BF0[] = { object_daiku_DL_0070C0, object_daiku_DL_006FB0, object_daiku_DL_006E80, object_daiku_DL_006D70,
                      object_daiku_DL_00A390 };

void EnEndingHero5_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnEndingHero5* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (limbIndex == 15) {
        gSPDisplayList(POLY_OPA_DISP++, D_80C23BF0[this->unk25C]);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnEndingHero5_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnEndingHero5* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    OPEN_DISPS(globalCtx->state.gfxCtx);

    switch (this->unk25C) {
        case 0:
            gDPSetEnvColor(POLY_OPA_DISP++, 170, 10, 70, 255);
            break;
        case 1:
            gDPSetEnvColor(POLY_OPA_DISP++, 170, 200, 255, 255);
            break;
        case 2:
            gDPSetEnvColor(POLY_OPA_DISP++, 0, 230, 70, 255);
            break;
        case 3:
            gDPSetEnvColor(POLY_OPA_DISP++, 200, 0, 150, 255);
            break;
        case 4:
            gDPSetEnvColor(POLY_OPA_DISP++, 245, 155, 0, 255);
            break;
    }

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          NULL, EnEndingHero5_PostLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
