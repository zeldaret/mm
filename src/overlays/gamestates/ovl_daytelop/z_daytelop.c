/*
 * File: z_daytelop.c
 * Overlay: ovl_daytelop
 * Description:
 */

#include "z_daytelop.h"

extern u8 D_80815FF0;


#ifdef NON_EQUIVALENT
void Daytelop_Update(DaytelopContext* this, GlobalContext* globalCtx) {
    //u8 temp_v0_3;
    s32 phi_a2;

    this->transitionCountdown--;
    if (this->transitionCountdown == 0) {
        if (gSaveContext.day < 9) {
            gSaveContext.gameMode = 0;
        } else {
            gSaveContext.unk_3F4A = 0xFFF6;
            gSaveContext.day = 1;
        }
        this->common.running = 0;
        this->common.nextGameStateSize = 0x19258;
        this->common.nextGameStateInit = Play_Init;
        gSaveContext.time = CLOCK_TIME(6, 0);
        D_801BDBC8 = 0xFE;
    } else if (this->transitionCountdown == 0x5A) {
        this->unk_242 = 1;
        this->unk_244 = 0;
        D_80815FF0 = 0x1E;
    }

    if (this->unk_242 == 1) {
        /*
        phi_a2 = this->unk_244 - 0xFF;
        if (phi_a2 < 0) {
            phi_a2 = 0xFF - this->unk_244;
        }
        this->unk_244 += (phi_a2 / D_80815FF0);
        */
        //this->unk_244 += (((this->unk_244 - 0xFF) < 0 ? 0xFF - this->unk_244 : this->unk_244 - 0xFF) / D_80815FF0);
        //this->unk_244 += ((ABS_ALT(this->unk_244 - 0xFF)) / D_80815FF0);
        phi_a2 = ABS_ALT(this->unk_244 - 0xFF);
        this->unk_244 += (phi_a2 / D_80815FF0);

        D_80815FF0 = (D_80815FF0 - 1) & 0xFF;
        if (D_80815FF0 == 0) {
            this->unk_242 = 2;
            this->unk_244 = 0xFF;
        }
    }
}
#else
void Daytelop_Update(DaytelopContext* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_daytelop/Daytelop_Update.s")
#endif

void Daytelop_Draw(DaytelopContext* this);
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

void Daytelop_nop80815770(s32 arg0) {

}

#ifdef NON_EQUIVALENT
void Daytelop_LoadGraphics(DaytelopContext* this) {
    u8* sp20;
    u32 sp1C;
    TwoHeadArena* sp18;
    s32 temp_a0_2;

    sp1C = _daytelop_staticSegmentRomEnd - _daytelop_staticSegmentRomStart;
    sp18 = &this->common.heap;
    sp20 = _daytelop_staticSegmentRomStart;

    this->unk_A4 = THA_AllocEndAlign16(sp18, sp1C);
    DmaMgr_SendRequest0(this->unk_A4, (u32) sp20, sp1C);
    sp1C = _icon_item_gameover_staticSegmentRomEnd - _icon_item_gameover_staticSegmentRomStart;

    sp20 = _icon_item_gameover_staticSegmentRomStart;
    this->unk_A8 = THA_AllocEndAlign16(sp18, sp1C);
    DmaMgr_SendRequest0(this->unk_A8, sp20, sp1C);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_daytelop/Daytelop_LoadGraphics.s")
#endif

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
