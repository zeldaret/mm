#include "z_dm_sa.h"

#define FLAGS 0x00000030

#define THIS ((DmSa*)thisx)

void DmSa_Init(Actor* thisx, GlobalContext* globalCtx);
void DmSa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmSa_Update(Actor* thisx, GlobalContext* globalCtx);
void DmSa_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A2EABC(DmSa* this, GlobalContext* globalCtx);

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

s32 D_80A2ED00[] = {
/* 000232 0x80A2ED00 */ 0x0600CC94,
/* 000233 0x80A2ED04 */ 0x3F800000,
/* 000234 0x80A2ED08 */ 0x00000000,
/* 000235 0x80A2ED0C */ 0xBF800000,
/* 000236 0x80A2ED10 */ 0x00000000,
/* 000237 0x80A2ED14 */ 0x00000000,
/* 000238 0x80A2ED18 */ 0x00000000,
/* 000239 0x80A2ED1C */ 0x00000000
};

void func_80A2E960(SkelAnime* skelAnime, s32 arg1, s32 arg2) {
    f32 temp_f0;
    void *temp_s0;
    f32 phi_f2;

    temp_s0 = arg1 + ((arg2 & 0xFFFF) * 0x18);
    temp_f0 = temp_s0->unkC;
    if (temp_f0 < 0.0f) {
        phi_f2 = (f32) SkelAnime_GetFrameCount(temp_s0->unk0);
    } else {
        phi_f2 = temp_f0;
    }
    SkelAnime_ChangeAnim(arg0, (AnimationHeader *) temp_s0->unk0, (bitwise f32) temp_s0->unk4, (bitwise f32) temp_s0->unk8, phi_f2, (?32) temp_s0->unk10, temp_s0->unk14);
}

void DmSa_Init(Actor* thisx, GlobalContext* globalCtx) {
    DmSa* this = THIS;

    this->unk2E0 = 0;
    this->unk2F0 = 0xFF;
    this->actor.targetArrowOffset = 3000.0f;
    Actor_SetDrawParams(&this->actor.shape, 0.0f, func_800B3FC0, 24.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06013328, NULL, 0, 0, 0);
    func_80A2E960(&this->skelAnime, &D_80A2ED00, 0);
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
