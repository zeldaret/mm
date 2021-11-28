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

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Inibs_Movebg/BgInibsMovebg_Init.s")
void BgInibsMovebg_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgInibsMovebg* this = (BgInibsMovebg* ) thisx;
    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 1);

    ((BgInibsMovebg *) thisx)->unk_15C[0] = D_80B96560[((u16) this->dyna.actor.params) & 0xF];
    this->unk_15C[1] = D_80B96568[((u16) this->dyna.actor.params) & 0xF];
    this->unk_164 = D_80B96570[((u16) ((BgInibsMovebg *) thisx)->dyna.actor.params) & 0xF];
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Inibs_Movebg/BgInibsMovebg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Inibs_Movebg/BgInibsMovebg_Draw.s")
