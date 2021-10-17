#include "z_dm_sa.h"

#define FLAGS 0x00000030

#define THIS ((DmSa*)thisx)

void DmSa_Init(Actor* thisx, GlobalContext* globalCtx);
void DmSa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmSa_Update(Actor* thisx, GlobalContext* globalCtx);
void DmSa_Draw(Actor* thisx, GlobalContext* globalCtx);

void DmSa_DoNothing(DmSa* this, GlobalContext* globalCtx);

const ActorInit Dm_Sa_InitVars = {
    ACTOR_DM_SA,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_STK,
    sizeof(DmSa),
    (ActorFunc)DmSa_Init,
    (ActorFunc)DmSa_Destroy,
    (ActorFunc)DmSa_Update,
    (ActorFunc)DmSa_Draw,
};

extern FlexSkeletonHeader D_06013328;
extern AnimationHeader D_0600CC94;

static ActorAnimationEntry D_80A2ED00[] = { { &D_0600CC94, 1.0f, 0, -1.0f, 0, 0 } };

void func_80A2E960(SkelAnime* arg0, ActorAnimationEntry* animations, u16 index) {
    f32 frameCount;
    animations += index;

    if (animations->frameCount < 0.0f) {
        frameCount = SkelAnime_GetFrameCount(&animations->animation->common);
    } else {
        frameCount = animations->frameCount;
    }
    SkelAnime_ChangeAnim(arg0, animations->animation, animations->playSpeed, animations->startFrame, frameCount,
                         animations->mode, animations->morphFrames);
}

void DmSa_Init(Actor* thisx, GlobalContext* globalCtx) {
    DmSa* this = THIS;

    this->unk2E0 = 0;
    this->alpha = 0xFF;
    this->actor.targetArrowOffset = 3000.0f;
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 24.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06013328, NULL, 0, 0, 0);
    func_80A2E960(&this->skelAnime, D_80A2ED00, 0);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = DmSa_DoNothing;
}

void DmSa_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void DmSa_DoNothing(DmSa* this, GlobalContext* globalCtx) {
}

void DmSa_Update(Actor* thisx, GlobalContext* globalCtx) {
    DmSa* this = THIS;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->alpha += 0;
    this->actionFunc(this, globalCtx);
}

s32 func_80A2EB10(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor) {
    return 0;
}

void func_80A2EB2C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor) {
}

void func_80A2EB44(GlobalContext* globalCtx, s32 limbIndex, Actor* actor) {
}

Gfx* func_80A2EB58(GraphicsContext* gfxCtx, u32 alpha) {
    Gfx* dList;
    Gfx* dListHead;

    dList = dListHead = GRAPH_ALLOC(gfxCtx, sizeof(Gfx) * 2); //! @bug this does not allocate enough for 3 Gfx commands
    gDPSetRenderMode(dListHead++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2);
    gDPSetEnvColor(dListHead++, 0, 0, 0, alpha);
    gSPEndDisplayList(dListHead++);

    return dList;
}

Gfx* func_80A2EBB0(GraphicsContext* gfxCtx, u32 alpha) {
    Gfx* dList;
    Gfx* dListHead;

    dList = dListHead = GRAPH_ALLOC(gfxCtx, sizeof(Gfx) * 2);
    gDPSetEnvColor(dListHead++, 0, 0, 0, alpha);
    gSPEndDisplayList(dListHead++);

    return dList;
}

void DmSa_Draw(Actor* thisx, GlobalContext* globalCtx) {
    DmSa* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    if (this->alpha < 0xFF) {
        gSPSegment(POLY_OPA_DISP++, 0x0C, func_80A2EB58(globalCtx->state.gfxCtx, this->alpha));
    } else {
        gSPSegment(POLY_OPA_DISP++, 0x0C, func_80A2EBB0(globalCtx->state.gfxCtx, this->alpha));
    }

    func_801343C0(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                  func_80A2EB10, func_80A2EB2C, func_80A2EB44, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
