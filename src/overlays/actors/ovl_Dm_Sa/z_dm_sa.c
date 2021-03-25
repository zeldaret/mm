#include "z_dm_sa.h"

#define FLAGS 0x00000030

#define THIS ((DmSa*)thisx)

void DmSa_Init(Actor* thisx, GlobalContext* globalCtx);
void DmSa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmSa_Update(Actor* thisx, GlobalContext* globalCtx);
void DmSa_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A2EABC(DmSa* this, GlobalContext* globalCtx);

typedef struct {
    /* 0x00 */ AnimationHeader* animation;
    /* 0x04 */ f32 playbackSpeed;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 frameCount;
    /* 0x10 */ u8 unk_10;
    /* 0x14 */ f32 transitionRate;
} DmSa_AnimationStruct; // size = 0x18

/*
const ActorInit Dm_Sa_InitVars = {
    ACTOR_DM_SA,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_STK,
    sizeof(DmSa),
    (ActorFunc)DmSa_Init,
    (ActorFunc)DmSa_Destroy,
    (ActorFunc)DmSa_Update,
    (ActorFunc)DmSa_Draw
};
*/

extern SkeletonHeader D_06013328;
extern AnimationHeader D_0600788C;

static DmSa_AnimationStruct animation = { &D_0600788C, 1.0f, 0.0f, 0.0f, 0x00, 0.0f };

void func_80A2E960(SkelAnime* skelAnime, DmSa_AnimationStruct* animation1, s32 arg2) {
    f32 frameCount;
    AnimationHeader* animationHeader;
    f32 phi_f2;

    animationHeader = &animation1[arg2];
    frameCount = animation1->frameCount;
    if (frameCount < 0.0f) {
        phi_f2 = SkelAnime_GetFrameCount(&animationHeader->genericHeader);
    } else {
        phi_f2 = frameCount;
    }
    SkelAnime_ChangeAnim(skelAnime, animationHeader, animation1->playbackSpeed, animation1->unk_08, phi_f2, animation1->unk_10, animation1->transitionRate);
}

void DmSa_Init(Actor* thisx, GlobalContext* globalCtx) {
    DmSa* this = THIS;

    this->unk2E0 = 0;
    this->unk2F0 = 0xFF;
    this->actor.targetArrowOffset = 3000.0f;
    Actor_SetDrawParams(&this->actor.shape, 0.0f, func_800B3FC0, 24.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06013328, NULL, 0, 0, 0);
    func_80A2E960(&this->skelAnime, &animation, 0);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80A2EABC;
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/DmSa_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2EABC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/DmSa_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2EB10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2EB2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2EB44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2EB58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2EBB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/DmSa_Draw.asm")
