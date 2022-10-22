/*
 * File: z_dm_sa.c
 * Overlay: ovl_Dm_Sa
 * Description: Glitched early version of Skull Kid stuck in a T-pose
 */

#include "z_dm_sa.h"
#include "objects/object_stk/object_stk.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmSa*)thisx)

void DmSa_Init(Actor* thisx, PlayState* play);
void DmSa_Destroy(Actor* thisx, PlayState* play);
void DmSa_Update(Actor* thisx, PlayState* play);
void DmSa_Draw(Actor* thisx, PlayState* play);

void DmSa_DoNothing(DmSa* this, PlayState* play);

ActorInit Dm_Sa_InitVars = {
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

static AnimationInfo sAnimationInfo[] = { { &gSkullKidTPoseAnim, 1.0f, 0, -1.0f, ANIMMODE_LOOP, 0 } };

void func_80A2E960(SkelAnime* arg0, AnimationInfo* animations, u16 index) {
    f32 frameCount;

    animations += index;
    if (animations->frameCount < 0.0f) {
        frameCount = Animation_GetLastFrame(animations->animation);
    } else {
        frameCount = animations->frameCount;
    }
    Animation_Change(arg0, animations->animation, animations->playSpeed, animations->startFrame, frameCount,
                     animations->mode, animations->morphFrames);
}

void DmSa_Init(Actor* thisx, PlayState* play) {
    DmSa* this = THIS;

    this->unk2E0 = 0;
    this->alpha = 0xFF;
    this->actor.targetArrowOffset = 3000.0f;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gSkullKidSkel, NULL, NULL, NULL, 0);
    func_80A2E960(&this->skelAnime, sAnimationInfo, 0);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = DmSa_DoNothing;
}

void DmSa_Destroy(Actor* thisx, PlayState* play) {
}

void DmSa_DoNothing(DmSa* this, PlayState* play) {
}

void DmSa_Update(Actor* thisx, PlayState* play) {
    DmSa* this = THIS;

    SkelAnime_Update(&this->skelAnime);
    this->alpha += 0;
    this->actionFunc(this, play);
}

s32 DmSa_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return false;
}

void DmSa_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
}

void DmSa_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
}

Gfx* func_80A2EB58(GraphicsContext* gfxCtx, u32 alpha) {
    Gfx* dList;
    Gfx* dListHead;

    dList = dListHead = GRAPH_ALLOC(gfxCtx, 2 * sizeof(Gfx)); //! @bug this does not allocate enough for 3 Gfx commands
    gDPSetRenderMode(dListHead++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2);
    gDPSetEnvColor(dListHead++, 0, 0, 0, alpha);
    gSPEndDisplayList(dListHead++);

    return dList;
}

Gfx* func_80A2EBB0(GraphicsContext* gfxCtx, u32 alpha) {
    Gfx* dList;
    Gfx* dListHead;

    dList = dListHead = GRAPH_ALLOC(gfxCtx, 2 * sizeof(Gfx));
    gDPSetEnvColor(dListHead++, 0, 0, 0, alpha);
    gSPEndDisplayList(dListHead++);

    return dList;
}

void DmSa_Draw(Actor* thisx, PlayState* play) {
    DmSa* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    if (this->alpha < 0xFF) {
        gSPSegment(POLY_OPA_DISP++, 0x0C, func_80A2EB58(play->state.gfxCtx, this->alpha));
    } else {
        gSPSegment(POLY_OPA_DISP++, 0x0C, func_80A2EBB0(play->state.gfxCtx, this->alpha));
    }

    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, DmSa_OverrideLimbDraw, DmSa_PostLimbDraw,
                                   DmSa_TransformLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
