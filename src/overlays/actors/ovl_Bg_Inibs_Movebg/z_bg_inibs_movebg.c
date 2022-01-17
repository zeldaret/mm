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

extern Gfx D_06001C10[];
extern Gfx D_06001DC0[];
extern AnimatedMaterial D_06002598;
extern Gfx D_06006140[];
extern Gfx D_060062D8[];
extern AnimatedMaterial D_06006858;
Gfx* D_80B96560[] = { D_060062D8, D_06001DC0 };
Gfx* D_80B96568[] = { D_06006140, D_06001C10 };
AnimatedMaterial* D_80B96570[] = { &D_06006858, &D_06002598 };

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};

void BgInibsMovebg_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgInibsMovebg* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 1);

    this->unk_15C = D_80B96560[BGINIBSMOVEBG_GET_F(thisx)];
    this->unk_160 = D_80B96568[BGINIBSMOVEBG_GET_F(thisx)];
    this->unk_164 = D_80B96570[BGINIBSMOVEBG_GET_F(thisx)];
}

void BgInibsMovebg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgInibsMovebg* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void BgInibsMovebg_Draw(Actor* thisx, GlobalContext* globalCtx) {
    BgInibsMovebg* this = THIS;

    AnimatedMaterial* animMat;
    Gfx* dl1;
    Gfx* dl2;

    animMat = this->unk_164;
    if (animMat != NULL) {
        AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(this->unk_164));
    }

    dl1 = this->unk_15C;
    if (dl1 != NULL) {
        Gfx_DrawDListOpa(globalCtx, this->unk_15C);
    }

    dl2 = this->unk_160;
    if (dl2 != NULL) {
        Gfx_DrawDListXlu(globalCtx, this->unk_160);
    }
}
