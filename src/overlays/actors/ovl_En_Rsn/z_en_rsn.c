#include "z_en_rsn.h"

#define FLAGS 0x02000019

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

extern FlexSkeletonHeader D_06009220;
extern AnimationHeader D_06009120;
extern AnimationHeader D_0600788C;
extern Gfx D_06005458[];

static ActorAnimationEntry animations[] = { { &D_0600788C, 1.0f, 0.0f, 0.0f, 0x00, 0.0f } };

void func_80C25D40(EnRsn* this) {
    func_800BDC5C(&this->skelAnime, animations, 0);
    this->actionFunc = func_80C25D84;
}

void func_80C25D84(EnRsn* this, GlobalContext* globalCtx) {
}

void EnRsn_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnRsn* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 20.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06009220, &D_06009120, NULL, NULL, 0);
    this->actor.flags &= ~1;
    func_80C25D40(this);
}

void EnRsn_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnRsn* this = THIS;

    SkelAnime_Free(&this->skelAnime, globalCtx);
}

void EnRsn_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnRsn* this = THIS;

    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_800E9250(globalCtx, &this->actor, &this->unk1D8, &this->unk1DE, this->actor.focus.pos);
}

s32 EnRsn_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnRsn* this = THIS;

    if (limbIndex == 14) {
        SysMatrix_InsertXRotation_s(this->unk1D8.y, 1);
    }
    return 0;
}

static Vec3f D_80C26028 = { 0.0f, 0.0f, 0.0f };

void EnRsn_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnRsn* this = THIS;
    Vec3f sp18 = D_80C26028;

    if (limbIndex == 14) {
        SysMatrix_MultiplyVector3fByState(&sp18, &this->actor.focus.pos);
    }
}

void EnRsn_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnRsn* this = THIS;
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C5B0(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_06005458));
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     EnRsn_OverrideLimbDraw, EnRsn_PostLimbDraw, &this->actor);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
