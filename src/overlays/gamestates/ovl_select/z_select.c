/*
 * File: z_select.c
 * Overlay: ovl_select
 * Description:
 */

#include "z_select.h"

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_select/D_80802390.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_select/func_80800910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_select/func_80800930.s")

void func_80800A44(SelectContext* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_select/func_80800A44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_select/func_808013B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_select/D_8080343C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_select/func_80801594.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_select/D_80803588.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_select/func_80801620.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_select/func_808016E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_select/func_8080194C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_select/func_808019FC.s")

void func_80801A64(SelectContext* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_select/func_80801A64.s")

void Select_Main(GameState* thisx) {
    SelectContext* this = (SelectContext*)thisx;

    func_80800A44(this);
    func_80801A64(this);
}

void Select_Destroy(GameState* thisx) {
    ShrinkWindow_Fini();
}

extern UNK_TYPE D_80801C80[];

void Select_Init(GameState* thisx) {
    SelectContext* this = (SelectContext*)thisx;

    this->state.main = Select_Main;
    this->state.destroy = Select_Destroy;

    this->unk_214 = &D_80801C80;
    this->unk_24C = 0;
    this->unk_218 = 0;
    this->unk_220 = 0;
    this->unk_224 = 0x13;
    this->unk_228 = 0x25;
    this->unk_22C = 0x33;
    this->unk_230 = 0x3B;
    this->unk_234 = 0x49;
    this->unk_238 = 0x5B;
    this->unk_21C = 0;
    this->unk_248 = 0;
    this->unk_210 = 0x8F;

    ShrinkWindow_Init();
    View_Init(&this->view, this->state.gfxCtx);
    this->view.flags = 0xA;
    this->unk_25C = 0;
    this->unk_260 = 0;
    this->unk_264 = 0;
    this->unk_268 = 0;
    this->unk_26C = 0;
    this->unk_270 = 0;
    this->unk_274 = 0;

    if ((dREG(80) >= 0) && (dREG(80) < this->unk_210)) {
        this->unk_218 = dREG(80);
        this->unk_24C = dREG(81);
        this->unk_21C = dREG(82);
    }

    Game_SetFramerateDivisor(this, 1);
    gSaveContext.cutscene = 0;
    gSaveContext.playerForm = PLAYER_FORM_HUMAN;
    gSaveContext.linkAge = 0;
}
