/*
 * File: z_dm_zl.c
 * Overlay: ovl_Dm_Zl
 * Description: Child Zelda (Cutscenes)
 */

#include "z_dm_zl.h"
#include "objects/object_zl4/object_zl4.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((DmZl*)thisx)

void DmZl_Init(Actor* thisx, GlobalContext* globalCtx);
void DmZl_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmZl_Update(Actor* thisx, GlobalContext* globalCtx);
void DmZl_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A382FC(DmZl* this, GlobalContext* globalCtx);

#if 0
const ActorInit Dm_Zl_InitVars = {
    ACTOR_DM_ZL,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_ZL4,
    sizeof(DmZl),
    (ActorFunc)DmZl_Init,
    (ActorFunc)DmZl_Destroy,
    (ActorFunc)DmZl_Update,
    (ActorFunc)DmZl_Draw,
};

#endif

// data
// mouth textures
extern void* D_80A38898[];

// eye textures
extern void* D_80A388A8[];

// dont yet know what this data is supposed to be other than 0x18
extern AnimationInfo D_80A387F0[];

// DmZl_ChangeAnimation
void func_80A38190(SkelAnime *skelAnime, AnimationInfo animation[], u16 index) {
    f32 endFrame;
    animation += index;
    endFrame = (animation->frameCount < 0.0f) ? Animation_GetLastFrame(animation->animation) : animation->frameCount;

    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, 
          endFrame,
          animation->mode, animation->morphFrames);

}

void DmZl_Init(Actor *thisx, GlobalContext *globalCtx) {
    s32 pad;
    DmZl *this = THIS;

    this->unk2B0 = 0;
    this->unk2BA = 0;
    this->actor.targetArrowOffset = 1000.0f;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, (FlexSkeletonHeader *) &gZl4Skeleton, NULL, NULL, NULL, 0);
    func_80A38190(&this->skelAnime, &D_80A387F0[this->unk2B0], 0);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80A382FC;
}

void DmZl_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    DmZl *this = (DmZl *) thisx;
}

//do nothing
void func_80A382FC(DmZl *this, GlobalContext *globalCtx) {
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/func_80A3830C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/func_80A38468.s")

void DmZl_Update(Actor *thisx, GlobalContext *globalCtx) {
    DmZl *this = THIS;
    func_80A38468(this);
    SkelAnime_Update(&this->skelAnime);
    func_80A3830C(&this->actor, globalCtx);
    this->actionFunc(this, globalCtx);
}

// DmZl_OverrideLimbDraw
s32 func_80A3862C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return 0;
}

// DmZl_PostLimbDraw
void func_80A38648(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx){
    DmZl* this = THIS;

    if (limbIndex == 0x10) {
        if ((this->unk2B0 >= 3) && (this->unk2B0 < 7)) {
            OPEN_DISPS(globalCtx->state.gfxCtx);

            gSPDisplayList(POLY_OPA_DISP++, &gDl4OcarinaDl);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}


void DmZl_Draw(Actor *thisx, GlobalContext *globalCtx) {
    DmZl *this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80A388A8[this->unk2B3]));

    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80A388A8[this->unk2B2]));

    gSPSegment(POLY_OPA_DISP++, 0x0A, Lib_SegmentedToVirtual(D_80A38898[this->unk2B4]));

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, func_80A3862C, func_80A38648, &this->actor);
    CLOSE_DISPS(globalCtx->state.gfxCtx);

}
