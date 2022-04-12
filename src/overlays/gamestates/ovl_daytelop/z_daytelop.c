/*
 * File: z_daytelop.c
 * Overlay: ovl_daytelop
 * Description: "Dawn of ... day" screen
 */

#include "z_daytelop.h"
#include "misc/daytelop_static/daytelop_static.h"
#include "interface/icon_item_gameover_static/icon_item_gameover_static.h"

// unused
UNK_TYPE D_808158E0[] = {
    0x00000C00, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000C04, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x80000000, 0x00000000, 0x00000000, 0x00000000, 0x80000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00100000, 0x00000000, 0x00000000, 0x40000002, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x04000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x04000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000000F, 0x00000000, 0x00000000, 0x00000000,
    0x0070B000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x80000000, 0x00000000, 0x00000400, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x80000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x01A00020, 0x00000000, 0x00000000,
    0x00000000, 0x00000400, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00001000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000002, 0x00000400,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x80000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000010, 0x00000000, 0x00000000, 0x00000000, 0x00000003, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x80000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x80000000, 0x00100400, 0x00000000, 0x00000000, 0x00000022, 0x00000400,
    0x00000000, 0x00000000, 0x00000080, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000400, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x80000002, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x80000000, 0x00000C00, 0x00000000, 0x00000000,
    0x40000000, 0x00000102, 0x00000000, 0x00000000, 0x00000400, 0x00000000, 0x00000000, 0x00000000, 0x00000002,
    0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000070, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00100000, 0x00000000, 0x00000000, 0x80000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000400, 0x00000000, 0x00000000, 0x00000000, 0x00000400, 0x00000000, 0x00000000, 0x00000000,
    0x00100000, 0x00000000, 0x00000000, 0x80000000, 0x00000000, 0x00000000, 0x00000000, 0x00000100, 0x00000400,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000080, 0x00000000, 0x00000000,
    0x00000000, 0x00000080, 0x00000000, 0x00000000, 0x00000000, 0x80000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000400, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000002, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000400, 0x00100000, 0x00000000, 0x00000000, 0x00000400, 0x00000000, 0x00000000,
    0x00000001, 0x00000000,
};

void Daytelop_Update(DaytelopContext* this, GameState* gameState) {
    static u8 D_80815FF0 = 0;
    s16 new_var;
    u8 temp_v0_2;

    this->transitionCountdown--;
    if (this->transitionCountdown == 0) {
        if (gSaveContext.save.day < 9) {
            gSaveContext.gameMode = 0;
        } else {
            gSaveContext.nextCutsceneIndex = 0xFFF6;
            gSaveContext.save.day = 1;
        }

        {
            GameState* state = &this->state;
            state->running = 0;
        }

        SET_NEXT_GAMESTATE(&this->state, Play_Init, GlobalContext);
        gSaveContext.save.time = CLOCK_TIME(6, 0);
        D_801BDBC8 = 0xFE;
    } else if (this->transitionCountdown == 90) {
        this->fadeInState = DAYTELOP_HOURSTEXT_FADEIN;
        this->alpha = 0;
        D_80815FF0 = 30;
    }

    if (this->fadeInState == DAYTELOP_HOURSTEXT_FADEIN) {
        this->alpha += (s16)(ABS_ALT(this->alpha - 0xFF) / D_80815FF0);

        D_80815FF0--;
        if (D_80815FF0 == 0) {
            this->fadeInState = DAYTELOP_HOURSTEXT_ON;
            this->alpha = 255;
        }
    }
}

TexturePtr sDayLeftTextures[] = {
    gDaytelopFirstDayLeftNESTex,
    gDaytelopSecondDayLeftNESTex,
    gDaytelopFinalDayLeftNESTex,

    // Last element is the new day
    gDaytelopNewDayLeftNESTex,
};

TexturePtr sDayRightTextures[] = {
    gDaytelopFirstDayRightNESTex,
    gDaytelopSecondDayRightNESTex,
    gDaytelopFinalDayRightNESTex,

    // Last element is the new day
    gDaytelopNewDayRightNESTex,
};

TexturePtr sHoursLeftTextures[] = {
    gDaytelop72HoursNESTex,
    gDaytelop48HoursNESTex,
    gDaytelop24HoursNESTex,
};

void Daytelop_Draw(DaytelopContext* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;

    OPEN_DISPS(gfxCtx);
    func_8012C628(this->state.gfxCtx);

    if (gSaveContext.save.day >= 9) {
        // Draw a white screen
        gDPSetRenderMode(POLY_OPA_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(POLY_OPA_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
        gDPFillRectangle(POLY_OPA_DISP++, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    func_8012C628(this->state.gfxCtx);

    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);

    if (gSaveContext.save.day >= 9) {
        gDPSetAlphaCompare(POLY_OPA_DISP++, G_AC_NONE);
    }

    // Draw the left side of the "Dawn of" texture
    if (gSaveContext.save.day < 9) {
        gDPLoadTextureBlock_4b(POLY_OPA_DISP++, sDayLeftTextures[CURRENT_DAY - 1], G_IM_FMT_I, 128, 64, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
    } else {
        gDPLoadTextureBlock_4b(POLY_OPA_DISP++, sDayLeftTextures[ARRAY_COUNT(sDayLeftTextures) - 1], G_IM_FMT_I, 128,
                               64, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
    }
    gSPTextureRectangle(POLY_OPA_DISP++, 32 << 2, 77 << 2, (32 + 128) << 2, (77 + 64) << 2, G_TX_RENDERTILE, 0, 0,
                        0x0400, 0x0400);

    // Draw the right side of the "Dawn of" texture
    if (gSaveContext.save.day < 9) {
        gDPLoadTextureBlock_4b(POLY_OPA_DISP++, sDayRightTextures[CURRENT_DAY - 1], G_IM_FMT_I, 128, 64, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
    } else {
        gDPLoadTextureBlock_4b(POLY_OPA_DISP++, sDayRightTextures[ARRAY_COUNT(sDayRightTextures) - 1], G_IM_FMT_I, 128,
                               64, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
    }
    gSPTextureRectangle(POLY_OPA_DISP++, 160 << 2, 77 << 2, (160 + 128) << 2, (77 + 64) << 2, G_TX_RENDERTILE, 0, 0,
                        0x0400, 0x0400);

    // Draw the "Hours left" texture
    if (gSaveContext.save.day < 9) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetRenderMode(POLY_OPA_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, this->alpha);
        gDPLoadTextureBlock_4b(POLY_OPA_DISP++, sHoursLeftTextures[CURRENT_DAY - 1], G_IM_FMT_I, 144, 32, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(POLY_OPA_DISP++, 88 << 2, 144 << 2, (88 + 144) << 2, (144 + 32) << 2, G_TX_RENDERTILE, 0, 0,
                            0x0400, 0x0400);
    }

    CLOSE_DISPS(this->state.gfxCtx);
}

void Daytelop_Main(GameState* thisx) {
    DaytelopContext* this = (DaytelopContext*)thisx;

    func_8012CF0C(this->state.gfxCtx, true, true, 0, 0, 0);

    OPEN_DISPS(this->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x09, this->daytelopStaticFile);
    gSPSegment(POLY_OPA_DISP++, 0x0C, this->gameoverStaticFile);
    CLOSE_DISPS(this->state.gfxCtx);

    Daytelop_Draw(this);
    Daytelop_Update(this, &this->state);
}

void Daytelop_Destroy(GameState* thisx) {
    ShrinkWindow_Destroy();
}

void Daytelop_nop80815770(DaytelopContext* this) {
}

void Daytelop_LoadGraphics(DaytelopContext* this) {
    size_t segmentSize = SEGMENT_ROM_SIZE(daytelop_static);

    this->daytelopStaticFile = THA_AllocEndAlign16(&this->state.heap, segmentSize);
    DmaMgr_SendRequest0(this->daytelopStaticFile, SEGMENT_ROM_START(daytelop_static), segmentSize);

    segmentSize = SEGMENT_ROM_SIZE(icon_item_gameover_static);
    this->gameoverStaticFile = THA_AllocEndAlign16(&this->state.heap, segmentSize);
    DmaMgr_SendRequest0(this->gameoverStaticFile, SEGMENT_ROM_START(icon_item_gameover_static), segmentSize);
}

void Daytelop_Init(GameState* thisx) {
    DaytelopContext* this = (DaytelopContext*)thisx;

    Game_SetFramerateDivisor(thisx, 1);
    Matrix_StateAlloc(thisx);
    ShrinkWindow_Destroy();
    View_Init(&this->view, thisx->gfxCtx);
    thisx->main = Daytelop_Main;
    thisx->destroy = Daytelop_Destroy;
    this->transitionCountdown = 140;
    this->fadeInState = DAYTELOP_HOURSTEXT_OFF;

    if (gSaveContext.save.day < 9) {
        if (gSaveContext.save.day == 0) {
            Sram_ClearFlagsAtDawnOfTheFirstDay();
        }
        Sram_IncrementDay();
    }

    Daytelop_nop80815770(this);
    Daytelop_LoadGraphics(this);
    play_sound(NA_SE_OC_TELOP_IMPACT);
}
