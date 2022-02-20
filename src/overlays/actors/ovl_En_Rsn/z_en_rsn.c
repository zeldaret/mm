/*
 * File: z_en_rsn.c
 * Overlay: ovl_En_Rsn
 * Description: Bomb Shop Man in the credits
 */

#include "z_en_rsn.h"
#include "objects/object_rs/object_rs.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((EnRsn*)thisx)

void EnRsn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRsn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRsn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRsn_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C25D84(EnRsn* this, GlobalContext* globalCtx);

const ActorInit En_Rsn_InitVars = {
    ACTOR_EN_RSN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_RS,
    sizeof(EnRsn),
    (ActorFunc)EnRsn_Init,
    (ActorFunc)EnRsn_Destroy,
    (ActorFunc)EnRsn_Update,
    (ActorFunc)EnRsn_Draw,
};

static AnimationInfo sAnimations[] = { { &object_rs_Anim_00788C, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f } };

void func_80C25D40(EnRsn* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
    this->actionFunc = func_80C25D84;
}

void func_80C25D84(EnRsn* this, GlobalContext* globalCtx) {
}

void EnRsn_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnRsn* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_rs_Skel_009220, &object_rs_Anim_009120, NULL, NULL, 0);
    this->actor.flags &= ~ACTOR_FLAG_1;
    func_80C25D40(this);
}

void EnRsn_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnRsn* this = THIS;

    SkelAnime_Free(&this->skelAnime, globalCtx);
}

void EnRsn_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnRsn* this = THIS;

    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    SkelAnime_Update(&this->skelAnime);
    func_800E9250(globalCtx, &this->actor, &this->unk1D8, &this->unk1DE, this->actor.focus.pos);
}

s32 EnRsn_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnRsn* this = THIS;

    if (limbIndex == 14) {
        Matrix_InsertXRotation_s(this->unk1D8.y, MTXMODE_APPLY);
    }
    return false;
}

static Vec3f D_80C26028 = { 0.0f, 0.0f, 0.0f };

void EnRsn_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnRsn* this = THIS;
    Vec3f sp18 = D_80C26028;

    if (limbIndex == 14) {
        Matrix_MultiplyVector3fByState(&sp18, &this->actor.focus.pos);
    }
}

void EnRsn_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnRsn* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C5B0(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(object_rs_Tex_005458));
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnRsn_OverrideLimbDraw, EnRsn_PostLimbDraw, &this->actor);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
