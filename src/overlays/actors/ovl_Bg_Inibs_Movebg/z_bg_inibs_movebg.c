/*
 * File: z_bg_inibs_movebg.c
 * Overlay: ovl_Bg_Inibs_Movebg
 * Description: Twinmold Arena
 */

#include "z_bg_inibs_movebg.h"

#define FLAGS 0x00000030

#define THIS ((BgInibsMovebg*)thisx)

void BgInibsMovebg_Init(Actor* thisx, GlobalContext* globalCtx);
void BgInibsMovebg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgInibsMovebg_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Bg_Inibs_Movebg_InitVars = {
    ACTOR_BG_INIBS_MOVEBG,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_INIBS_OBJECT,
    sizeof(BgInibsMovebg),
    (ActorFunc)BgInibsMovebg_Init,
    (ActorFunc)BgInibsMovebg_Destroy,
    (ActorFunc)Actor_Noop,
    (ActorFunc)BgInibsMovebg_Draw,
};

s32 D_80B96560[] = { 0x060062D8, 0x06001DC0 };
s32 D_80B96568[] = { 0x06006140, 0x06001C10 };
s32 D_80B96570[] = { 0x06006858, 0x06002598 };

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};

void BgInibsMovebg_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgInibsMovebg* this = (BgInibsMovebg*)thisx;
    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 1);

    //for some reason doesn't match if I don't use the THIS macro twice here
    THIS->unk_15C = D_80B96560[BGINIBSMOVEBG_GET_F(this->dyna)];
    this->unk_160 = D_80B96568[BGINIBSMOVEBG_GET_F(this->dyna)];
    this->unk_164 = D_80B96570[BGINIBSMOVEBG_GET_F(THIS->dyna)];
}

void BgInibsMovebg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, THIS->dyna.bgId);
}

void BgInibsMovebg_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 new_var;
    s32 temp_a1;
    BgInibsMovebg* new_var5;
    s32 new_var4;
    new_var5 = THIS;
    new_var = new_var5->unk_164;

    if (new_var != 0) {
        new_var = new_var5->unk_164;
        AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual((void*)new_var));
    }

    temp_a1 = new_var5->unk_15C;
    if (temp_a1 != 0) {
        func_800BDFC0(globalCtx, (void*)temp_a1);
    }

    new_var4 = new_var5->unk_160;
    if (((BgInibsMovebg*)thisx)->unk_160 != 0) {
        func_800BE03C(globalCtx, (void*)new_var4);
    }

    if (new_var5->unk_160 != 0) {}
}
