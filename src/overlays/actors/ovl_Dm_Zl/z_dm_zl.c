/*
 * File: z_dm_zl.c
 * Overlay: ovl_Dm_Zl
 * Description: Child Zelda (Cutscenes)
 */

#include "z_dm_zl.h"

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



extern UNK_TYPE D_0600DE08;
extern UNK_TYPE D_0600E038;

// dont yet know what this data is supposed to be other than 0x18
extern DmZl_UnkStruct D_80A387F0[];

void func_80A38190(SkelAnime *skelAnime, void *arg1, s32 arg2);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/func_80A38190.s")

void DmZl_Init(Actor *thisx, GlobalContext *globalCtx) {
    s32 pad;
    DmZl *this = THIS;

    this->unk2B0 = 0;
    this->unk2BA = 0;
    this->actor.targetArrowOffset = 1000.0f;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, (FlexSkeletonHeader *) &D_0600E038, NULL, NULL, NULL, 0);
    func_80A38190(&this->skelAnime, &D_80A387F0[this->unk2B0], 0);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80A382FC;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/DmZl_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/func_80A382FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/func_80A3830C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/func_80A38468.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/DmZl_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/func_80A3862C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/func_80A38648.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Zl/DmZl_Draw.s")
