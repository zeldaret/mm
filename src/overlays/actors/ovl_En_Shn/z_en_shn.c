/*
 * File: z_en_shn.c
 * Overlay: ovl_En_Shn
 * Description: Swamp Tourist Center Guide
 * Shashin
 */

#include "z_en_shn.h"

#define FLAGS 0x00000009

#define THIS ((EnShn*)thisx)

void EnShn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnShn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnShn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnShn_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AE69E8(EnShn* this, GlobalContext* globalCtx);
void func_80AE6A64(EnShn* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Shn_InitVars = {
    ACTOR_EN_SHN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SHN,
    sizeof(EnShn),
    (ActorFunc)EnShn_Init,
    (ActorFunc)EnShn_Destroy,
    (ActorFunc)EnShn_Update,
    (ActorFunc)EnShn_Draw,
};

#endif

extern UNK_TYPE D_0600B738;
extern UNK_TYPE D_0600E7D0;

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6130.s")
void func_80AE6130(EnShn* this) {
    this->unk148.playSpeed = this->unk2CC;
    SkelAnime_Update(&this->unk148);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE615C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE61C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE625C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE626C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE63A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE65F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6704.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE68F0.s")

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE69E8.s")
void func_80AE69E8(EnShn* this, GlobalContext* globalCtx) {
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
    if ((gSaveContext.weekEventReg[0x17] & 8) && (func_80AE61C0(this))) {
        this->unk1D8 |= 8;
    } else {
        this->unk1D8 &= 0xFFF7;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6A64.s")

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/EnShn_Init.s")
void EnShn_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnShn* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(globalCtx, &this->unk148, &D_0600E7D0, NULL, &this->unk1FA, &this->unk25A, 16);
    this->unk2E8 = -1;
    if ((gSaveContext.weekEventReg[0x17] & 8) != 0) {
        func_80AE615C(this, 0);
    } else {
        func_80AE615C(this, 2);
    }
    this->actor.targetMode = 6;
    Actor_SetScale(&this->actor, 0.01f);
    this->unk2E0 = 0;
    this->unk2D8 = 0;
    this->unk1D8 = 0;
    if (gSaveContext.entranceIndex != 0xA820) {
        func_8013AED4(&this->unk1D8, 3, 7);
        this->unk2BE = 0;
    } else {
        func_8013AED4(&this->unk1D8, 4, 7);
        this->unk2BE = 1;
    }
    this->actionFunc = func_80AE69E8;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/EnShn_Destroy.s")
void EnShn_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/EnShn_Update.s")
void EnShn_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnShn* this = THIS;

    func_80AE68F0(this, globalCtx);
    this->actionFunc(this, globalCtx);
    func_80AE65F4(this, globalCtx);
    func_80AE6130(this);
    func_80AE63A8(this, globalCtx);
    this->unk2E0 = 0;
    func_8013C964(&this->actor, globalCtx, 120.0f, 40.0f, 0, this->unk1D8 & 7);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6CF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6D40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6D90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/EnShn_Draw.s")
