/*
 * File: z_daytelop.c
 * Overlay: ovl_daytelop
 * Description:
 */

#include "z_daytelop.h"

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_daytelop/Daytelop_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_daytelop/Daytelop_Draw.s")

void Daytelop_Main(GameState* thisx) {
    DaytelopContext* this = (DaytelopContext*)thisx;

    func_8012CF0C(this->common.gfxCtx, 1, 1, 0, 0, 0);

    OPEN_DISPS(this->common.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x09, this->unk_A4);
    gSPSegment(POLY_OPA_DISP++, 0x0C, this->unk_A8);
    CLOSE_DISPS(this->common.gfxCtx);

    Daytelop_Draw(this);
    Daytelop_Update(this, this);
}

void Daytelop_Destroy(GameState* thisx) {
    ShrinkWindow_Fini();
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_daytelop/Daytelop_nop80815770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_daytelop/Daytelop_LoadGraphics.s")

void Daytelop_Init(GameState* thisx) {
    DaytelopContext* this = (DaytelopContext*)thisx;

    Game_SetFramerateDivisor(thisx, 1);
    SysMatrix_StateAlloc(thisx);
    ShrinkWindow_Fini();
    View_Init(&this->view, thisx->gfxCtx);
    thisx->main = Daytelop_Main;
    thisx->destroy = Daytelop_Destroy;
    this->transitionCountdown = 0x8C;
    this->unk_242 = 0;

    if (gSaveContext.day < 9) {
        if (gSaveContext.day == 0) {
            func_80143AC4();
        }
        Sram_IncrementDay();
    }
    Daytelop_nop80815770(thisx);
    Daytelop_LoadGraphics(thisx);
    play_sound(0x5808U);
}
