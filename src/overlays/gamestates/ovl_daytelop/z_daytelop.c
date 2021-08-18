/*
 * File: z_daytelop.c
 * Overlay: ovl_daytelop
 * Description:
 */

#include "z_daytelop.h"
#include "static/daytelop_static/daytelop_static.h"
#include "static/icon_item_gameover_static/icon_item_gameover_static.h"


// unused
UNK_TYPE D_808158E0[] = {
    0x00000C00,
    0x00000000,
    0x00000000,
    0x40000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000C04,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00100000,
    0x00000000,
    0x00000000,
    0x40000002,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x04000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000002,
    0x00000000,
    0x00000000,
    0x00000000,
    0x04000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x0000000F,
    0x00000000,
    0x00000000,
    0x00000000,
    0x0070B000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000000,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x01A00020,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00001000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000002,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000002,
    0x00000000,
    0x00000000,
    0x00000000,
    0x40000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000010,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000003,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00100400,
    0x00000000,
    0x00000000,
    0x00000022,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000080,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000002,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000002,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000C00,
    0x00000000,
    0x00000000,
    0x40000000,
    0x00000102,
    0x00000000,
    0x00000000,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000002,
    0x00000000,
    0x00000000,
    0x00000000,
    0x40000000,
    0x00000070,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x40000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x40000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00100000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00100000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000100,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000080,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000080,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000001,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000002,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000001,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000400,
    0x00100000,
    0x00000000,
    0x00000000,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000001,
    0x00000000,
};

u8 D_80815FF0 = 0;

TexturePtr D_80815FF4[] = {
    gDaytelopFirstDayLeftNESTex,
    gDaytelopSecondDayLeftNESTex,
    gDaytelopFinalDayLeftNESTex,

    // Last element is the new day
    gDaytelopNewDayLeftNESTex,
};

TexturePtr D_80816004[] = {
    gDaytelopFirstDayRightNESTex,
    gDaytelopSecondDayRightNESTex,
    gDaytelopFinalDayRightNESTex,

    // Last element is the new day
    gDaytelopNewDayRightNESTex,
};

TexturePtr D_80816014[] = {
    gDaytelop72HoursNESTex,
    gDaytelop48HoursNESTex,
    gDaytelop24HoursNESTex,
};

#ifdef NON_EQUIVALENT
void Daytelop_Update(DaytelopContext* this, GameState* gameState) {
    s16 temp_v0;
    s32 temp_a1;
    u8 temp_v0_3;
    s32 phi_a2;
    s32 aux_var;

    this->transitionCountdown--;

    if (this->transitionCountdown == 0) {
        if (gSaveContext.day < 9) {
            gSaveContext.gameMode = 0;
        } else {
            gSaveContext.unk_3F4A = 0xFFF6;
            gSaveContext.day = 1;
        }
        this->common.running = false;
        if (1) {}
        this->common.nextGameStateInit = Play_Init;
        this->common.nextGameStateSize = sizeof(GlobalContext); // 0x19258;
        gSaveContext.time = CLOCK_TIME(6, 0);
        D_801BDBC8 = 0xFE;
    } else if (this->transitionCountdown == 0x5A) {
        this->unk_242 = 1;
        this->alpha = 0;
        if (1) {}
        D_80815FF0 = 0x1E;
    }

    if (this->unk_242 == 1) {
    aux_var = D_80815FF0;
        /*
        temp_a1 = this->alpha - 0xFF;
        phi_a2 = temp_a1;
        if (temp_a1 < 0) {
            phi_a2 = 0xFF - this->alpha;
        }
        this->alpha = this->alpha + (s16) (phi_a2 / D_80815FF0);
        */

        
        phi_a2 = ABS_ALT((this->alpha - 0xFF));
        //phi_a2 /= D_80815FF0;
        //this->alpha += phi_a2;
        //this->alpha += (phi_a2 / D_80815FF0--);
        //aux_var = D_80815FF0;
        //aux_var = this->alpha + (phi_a2 / (aux_var));
        aux_var = phi_a2 / aux_var;
        aux_var = this->alpha + aux_var;
        this->alpha = (s16)aux_var;
        

        /*
        phi_a2 =  (ABS_ALT(this->alpha - 0xFF) / D_80815FF0);
        this->alpha += phi_a2;
        */
        
        /*
        temp_v0_3 = (D_80815FF0 - 1) & 0xFF;
        D_80815FF0 = temp_v0_3;
        if (temp_v0_3 == 0) {
            this->unk_242 = 2;
            this->alpha = 0xFF;
        }
        */
        D_80815FF0--;
        if (D_80815FF0 == 0) {
            this->unk_242 = 2;
            this->alpha = 0xFF;
        }

    }
}
#else
void Daytelop_Update(DaytelopContext* this, GameState* gameState);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_daytelop/Daytelop_Update.s")
#endif

void Daytelop_Draw(DaytelopContext* this) {
    GraphicsContext* gfxCtx = this->common.gfxCtx;

    OPEN_DISPS(gfxCtx);
    func_8012C628(this->common.gfxCtx);

    if (gSaveContext.day >= 9) {
        gDPSetRenderMode(POLY_OPA_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(POLY_OPA_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
        gDPFillRectangle(POLY_OPA_DISP++, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    func_8012C628(this->common.gfxCtx);

    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);

    if (gSaveContext.day >= 9) {
        gDPSetAlphaCompare(POLY_OPA_DISP++, G_AC_NONE);
    }

    if (gSaveContext.day < 9) {
        gDPLoadTextureBlock_4b(POLY_OPA_DISP++, D_80815FF4[CURRENT_DAY-1], G_IM_FMT_I, 128, 64, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    } else {
        gDPLoadTextureBlock_4b(POLY_OPA_DISP++, D_80815FF4[ARRAY_COUNT(D_80815FF4) - 1], G_IM_FMT_I, 128, 64, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    }

    gSPTextureRectangle(POLY_OPA_DISP++, 0x0080, 0x0134, 0x0280, 0x0234, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    if (gSaveContext.day < 9) {
        gDPLoadTextureBlock_4b(POLY_OPA_DISP++, D_80816004[CURRENT_DAY-1], G_IM_FMT_I, 128, 64, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    } else {
        gDPLoadTextureBlock_4b(POLY_OPA_DISP++, D_80816004[ARRAY_COUNT(D_80816004) - 1], G_IM_FMT_I, 128, 64, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    }

    gSPTextureRectangle(POLY_OPA_DISP++, 0x0280, 0x0134, 0x0480, 0x0234, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    if (gSaveContext.day < 9) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetRenderMode(POLY_OPA_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, this->alpha);
        gDPLoadTextureBlock_4b(POLY_OPA_DISP++, D_80816014[CURRENT_DAY-1], G_IM_FMT_I, 144, 32, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(POLY_OPA_DISP++, 0x0160, 0x0240, 0x03A0, 0x02C0, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
    }

    CLOSE_DISPS(this->common.gfxCtx);
}


void Daytelop_Main(GameState* thisx) {
    DaytelopContext* this = (DaytelopContext*)thisx;

    func_8012CF0C(this->common.gfxCtx, 1, 1, 0, 0, 0);

    OPEN_DISPS(this->common.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x09, this->unk_A4);
    gSPSegment(POLY_OPA_DISP++, 0x0C, this->unk_A8);
    CLOSE_DISPS(this->common.gfxCtx);

    Daytelop_Draw(this);
    Daytelop_Update(this, &this->common);
}

void Daytelop_Destroy(GameState* thisx) {
    ShrinkWindow_Fini();
}

void Daytelop_nop80815770(DaytelopContext* this) {

}

void Daytelop_LoadGraphics(DaytelopContext* this) {
    size_t segmentSize = SEGMENT_ROM_SIZE(daytelop_static);

    this->unk_A4 = THA_AllocEndAlign16(&this->common.heap, segmentSize);
    DmaMgr_SendRequest0(this->unk_A4, SEGMENT_ROM_START(daytelop_static), segmentSize);

    segmentSize = SEGMENT_ROM_SIZE(icon_item_gameover_static);
    this->unk_A8 = THA_AllocEndAlign16(&this->common.heap, segmentSize);
    DmaMgr_SendRequest0(this->unk_A8, SEGMENT_ROM_START(icon_item_gameover_static), segmentSize);
}

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
    Daytelop_nop80815770(this);
    Daytelop_LoadGraphics(this);
    play_sound(0x5808);
}
