/*
 * File: z_kaleido_scope_NES.c
 * Overlay: ovl_kaleido_scope
 * Description: Pause Menu
 */

#include "prevent_bss_reordering.h"
#include "z_kaleido_scope.h"
#include "overlays/gamestates/ovl_opening/z_opening.h"
#include "z64view.h"
#include "overlays/gamestates/ovl_opening/z_opening.h"
#include "interface/icon_item_gameover_static/icon_item_gameover_static.h"
#include "interface/icon_item_jpn_static/icon_item_jpn_static.h"
#include "interface/icon_item_vtx_static/icon_item_vtx_static.h"

// iconItemSegment
extern TexturePtr D_08064340; // gPauseMenuCursorTex
extern TexturePtr D_08064440;
extern TexturePtr D_0806E440;
extern TexturePtr D_08077A40;
extern TexturePtr D_08081040;
extern TexturePtr D_0808A640;
extern TexturePtr D_0806EE40;
extern TexturePtr D_08078440;
extern TexturePtr D_08081A40;
extern TexturePtr D_0808B040;
extern TexturePtr D_08065840;
extern TexturePtr D_0806F840;
extern TexturePtr D_08078E40;
extern TexturePtr D_08082440;
extern TexturePtr D_0808BA40;
extern TexturePtr D_08070240;
extern TexturePtr D_08079840;
extern TexturePtr D_08082E40;
extern TexturePtr D_0808C440;
extern TexturePtr D_08070C40;
extern TexturePtr D_0807A240;
extern TexturePtr D_08083840;
extern TexturePtr D_0808CE40;
extern TexturePtr D_08071640;
extern TexturePtr D_0807AC40;
extern TexturePtr D_08084240;
extern TexturePtr D_0808D840;
extern TexturePtr D_08068040;
extern TexturePtr D_08072040;
extern TexturePtr D_0807B640;
extern TexturePtr D_08084C40;
extern TexturePtr D_0808E240;
extern TexturePtr D_08072A40;
extern TexturePtr D_0807C040;
extern TexturePtr D_08085640;
extern TexturePtr D_0808EC40;
extern TexturePtr D_08069440;
extern TexturePtr D_08073440;
extern TexturePtr D_0807CA40;
extern TexturePtr D_08086040;
extern TexturePtr D_0808F640;
extern TexturePtr D_08073E40;
extern TexturePtr D_0807D440;
extern TexturePtr D_08086A40;
extern TexturePtr D_08090040;
extern TexturePtr D_08074840;
extern TexturePtr D_0807DE40;
extern TexturePtr D_08087440;
extern TexturePtr D_08090A40;
extern TexturePtr D_08075240;
extern TexturePtr D_0807E840;
extern TexturePtr D_08087E40;
extern TexturePtr D_08091440;

// Page Textures (Background of Page):
// Broken up into multiple textures.
// Numbered by column/row.
TexturePtr sSelectMaskTextures[] = {
    // Column 0
    &D_08064440, // gPauseMasks00Tex
    &D_0806E440, // gPauseMasks01Tex
    &D_08077A40, // gPauseMasks02Tex
    &D_08081040, // gPauseMasks03Tex
    &D_0808A640, // gPauseMasks04Tex
    // Column 1
    gPauseMasks10ENGTex,
    &D_0806EE40, // gPauseMasks11Tex
    &D_08078440, // gPauseMasks12Tex
    &D_08081A40, // gPauseMasks13Tex
    &D_0808B040, // gPauseMasks14Tex
    // Column 2
    &D_08065840, // gPauseMasks20Tex
    &D_0806F840, // gPauseMasks21Tex
    &D_08078E40, // gPauseMasks22Tex
    &D_08082440, // gPauseMasks23Tex
    &D_0808BA40, // gPauseMasks24Tex
};
TexturePtr sSelectItemTextures[] = {
    // Column 0
    gPauseSelectItem00ENGTex,
    &D_08070240, // gPauseSelectItem01Tex
    &D_08079840, // gPauseSelectItem02Tex
    &D_08082E40, // gPauseSelectItem03Tex
    &D_0808C440, // gPauseSelectItem04Tex
    // Column 1
    gPauseSelectItem10ENGTex,
    &D_08070C40, // gPauseSelectItem11Tex
    &D_0807A240, // gPauseSelectItem12Tex
    &D_08083840, // gPauseSelectItem13Tex
    &D_0808CE40, // gPauseSelectItem14Tex
    // Column 2
    gPauseSelectItem20ENGTex,
    &D_08071640, // gPauseSelectItem21Tex
    &D_0807AC40, // gPauseSelectItem22Tex
    &D_08084240, // gPauseSelectItem23Tex
    &D_0808D840, // gPauseSelectItem24Tex
};
TexturePtr sMapTextures[] = {
    // Column 0
    &D_08068040, // gPauseMap00Tex
    &D_08072040, // gPauseMap01Tex
    &D_0807B640, // gPauseMap02Tex
    &D_08084C40, // gPauseMap03Tex
    &D_0808E240, // gPauseMap04Tex
    // Column 1
    gPauseMap10ENGTex,
    &D_08072A40, // gPauseMap11Tex
    &D_0807C040, // gPauseMap12Tex
    &D_08085640, // gPauseMap13Tex
    &D_0808EC40, // gPauseMap14Tex
    // Column 2
    &D_08069440, // gPauseMap20Tex
    &D_08073440, // gPauseMap21Tex
    &D_0807CA40, // gPauseMap22Tex
    &D_08086040, // gPauseMap23Tex
    &D_0808F640, // gPauseMap24Tex
};
TexturePtr sQuestStatusTextures[] = {
    // Column 0
    gPauseQuestStatus00ENGTex,
    &D_08073E40, // gPauseQuestStatus01Tex
    &D_0807D440, // gPauseQuestStatus02Tex
    &D_08086A40, // gPauseQuestStatus03Tex
    &D_08090040, // gPauseQuestStatus04Tex
    // Column 1
    gPauseQuestStatus10ENGTex,
    &D_08074840, // gPauseQuestStatus11Tex
    &D_0807DE40, // gPauseQuestStatus12Tex
    &D_08087440, // gPauseQuestStatus13Tex
    &D_08090A40, // gPauseQuestStatus14Tex
    // Column 2
    gPauseQuestStatus20ENGTex,
    &D_08075240, // gPauseQuestStatus21Tex
    &D_0807E840, // gPauseQuestStatus22Tex
    &D_08087E40, // gPauseQuestStatus23Tex
    &D_08091440, // gPauseQuestStatus24Tex
};

s16 D_8082B7F0[] = {
    80, 64, 64, 64, 16, 64, 112, 112, 48, 64, 64, 64, 64, 48, 64, 8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,   8,   24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
};
s16 D_8082B838[] = {
    40, 31, 53, 53, 53, 52, 35, 35, 32, 64, 64, 64, 64, 82, 61, 8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,  12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
};

s16 sGameOverPrimR = 0;
s16 sGameOverPrimG = 0;
s16 sGameOverPrimB = 0;
s16 sGameOverPrimAlpha = 255;
s16 sCursorPrimR = 0;
s16 sCursorPrimG = 0;
s16 sCursorPrimB = 0;
s16 sCursorEnvR = 0;
s16 sCursorEnvG = 0;
s16 sCursorEnvB = 0;
s16 sGameOverEnvR = 255;
s16 sGameOverEnvG = 0;
s16 sGameOverEnvB = 0;

s16 sInDungeonScene = false;

f32 sPageSwitchEyeDx[] = {
    -PAUSE_EYE_DIST * (PAUSE_MAP_X - PAUSE_ITEM_X) / 16, // From PAUSE_ITEM to PAUSE_MAP (switching right)
    -PAUSE_EYE_DIST*(PAUSE_MASK_X - PAUSE_ITEM_X) / 16,  // From PAUSE_ITEM to PAUSE_MASK (switching left)
    -PAUSE_EYE_DIST*(PAUSE_QUEST_X - PAUSE_MAP_X) / 16,  // From PAUSE_MAP to PAUSE_QUEST (switching right)
    -PAUSE_EYE_DIST*(PAUSE_ITEM_X - PAUSE_MAP_X) / 16,   // From PAUSE_MAP to PAUSE_ITEM (switching left)
    -PAUSE_EYE_DIST*(PAUSE_MASK_X - PAUSE_QUEST_X) / 16, // From PAUSE_QUEST to PAUSE_MASK (switching right)
    -PAUSE_EYE_DIST*(PAUSE_MAP_X - PAUSE_QUEST_X) / 16,  // From PAUSE_QUEST to PAUSE_MAP (switching left)
    -PAUSE_EYE_DIST*(PAUSE_ITEM_X - PAUSE_MASK_X) / 16,  // From PAUSE_MASK to PAUSE_ITEM (switching right)
    -PAUSE_EYE_DIST*(PAUSE_QUEST_X - PAUSE_MASK_X) / 16, // From PAUSE_MASK to PAUSE_QUEST (switching left)
};

f32 sPageSwitchEyeDz[] = {
    -PAUSE_EYE_DIST * (PAUSE_MAP_Z - PAUSE_ITEM_Z) / 16, // From PAUSE_ITEM to PAUSE_MAP (switching right)
    -PAUSE_EYE_DIST*(PAUSE_MASK_Z - PAUSE_ITEM_Z) / 16,  // From PAUSE_ITEM to PAUSE_MASK (switching left)
    -PAUSE_EYE_DIST*(PAUSE_QUEST_Z - PAUSE_MAP_Z) / 16,  // From PAUSE_MAP to PAUSE_QUEST (switching right)
    -PAUSE_EYE_DIST*(PAUSE_ITEM_Z - PAUSE_MAP_Z) / 16,   // From PAUSE_MAP to PAUSE_ITEM (switching left)
    -PAUSE_EYE_DIST*(PAUSE_MASK_Z - PAUSE_QUEST_Z) / 16, // From PAUSE_QUEST to PAUSE_MASK (switching right)
    -PAUSE_EYE_DIST*(PAUSE_MAP_Z - PAUSE_QUEST_Z) / 16,  // From PAUSE_QUEST to PAUSE_MAP (switching left)
    -PAUSE_EYE_DIST*(PAUSE_ITEM_Z - PAUSE_MASK_Z) / 16,  // From PAUSE_MASK to PAUSE_ITEM (switching right)
    -PAUSE_EYE_DIST*(PAUSE_QUEST_Z - PAUSE_MASK_Z) / 16, // From PAUSE_MASK to PAUSE_QUEST (switching left)
};

u16 sPageSwitchNextPageIndex[] = {
    PAUSE_MAP,   // From PAUSE_ITEM (switching right)
    PAUSE_MASK,  // From PAUSE_ITEM (switching left)
    PAUSE_QUEST, // From PAUSE_MAP (switching right)
    PAUSE_ITEM,  // From PAUSE_MAP (switching left)
    PAUSE_MASK,  // From PAUSE_QUEST (switching right)
    PAUSE_MAP,   // From PAUSE_QUEST (switching left)
    PAUSE_ITEM,  // From PAUSE_MASK (switching right)
    PAUSE_QUEST, // From PAUSE_MASK (switching left)
};

f32 sPauseMenuVerticalOffset = 0.0f;
f32 D_8082B90C = 0.0f;
f32 sPauseCursorLeftMoveOffsetX = 40.0f;
f32 sPauseCursorRightMoveOffsetX = -40.0f;

s16 sPauseCursorLeftX = 0;
s16 sPauseCursorRightX = 0;
s16 D_8082B920 = 10;

s16 D_8082B924[] = { 20, 4, 20, 10 };

// Unused remnant of OoT
u8 gAreaGsFlags[] = {
    0x0F, 0x1F, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x07, 0x07, 0x03, 0x0F,
    0x07, 0x0F, 0x0F, 0xFF, 0xFF, 0xFF, 0x1F, 0x0F, 0x03, 0x0F, 0x00, 0x00,
};

// TODO: Also applies to owl warps
s16 sGameOverRectPosY = 66;

void func_80821900(void* segment, u32 texIndex) {
    func_80178E3C(SEGMENT_ROM_START(map_name_static), texIndex, segment, 0x400);
}

void func_8082192C(void* segment, u32 texIndex) {
    func_80178E3C(SEGMENT_ROM_START(map_name_static), texIndex, segment, 0xA00);
}

void func_80821958(void* segment, u32 texIndex) {
    func_80178E3C(SEGMENT_ROM_START(item_name_static), texIndex, segment, 0x400);
}

void KaleidoScope_MoveCursorToSpecialPos(PlayState* play, s16 cursorSpecialPos) {
    PauseContext* pauseCtx = &play->pauseCtx;

    pauseCtx->cursorSlot[pauseCtx->pageIndex] = 0;
    pauseCtx->cursorSpecialPos = cursorSpecialPos;
    pauseCtx->pageSwitchInputTimer = 0;

    play_sound(NA_SE_SY_DECIDE);

    gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_ENABLED;
    gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_DISABLED;
    gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_DISABLED;
    gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_DISABLED;
    gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_DISABLED;

    gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
    Interface_SetHudVisibility(HUD_VISIBILITY_ALL);
}

void func_80821A04(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;

    pauseCtx->nameDisplayTimer = 0;
    pauseCtx->cursorSpecialPos = 0;

    play_sound(NA_SE_SY_CURSOR);

    pauseCtx->cursorShrinkRate = 4.0f;

    // TODO: indexing of D_801C6A98 is likely wrong
    gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_ENABLED;
    gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = D_801C6A98[pauseCtx->pageIndex + 1][1];
    gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = D_801C6A98[pauseCtx->pageIndex + 1][1];
    gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = D_801C6A98[pauseCtx->pageIndex + 1][1];
    gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_ENABLED;

    gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;

    Interface_SetHudVisibility(HUD_VISIBILITY_ALL);
}

void KaleidoScope_DrawTexQuadRGBA32(GraphicsContext* gfxCtx, TexturePtr texture, u16 width, u16 height, u16 point) {
    OPEN_DISPS(gfxCtx);

    gDPLoadTextureBlock(POLY_OPA_DISP++, texture, G_IM_FMT_RGBA, G_IM_SIZ_32b, width, height, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSP1Quadrangle(POLY_OPA_DISP++, point, point + 2, point + 3, point + 1, 0);

    CLOSE_DISPS(gfxCtx);
}

#define SWITCH_PAGE_LEFT 0
#define SWITCH_PAGE_RIGHT 2

void KaleidoScope_SwitchPage(PauseContext* pauseCtx, u8 direction) {
    pauseCtx->cursorSlot[pauseCtx->pageIndex] = 0;
    pauseCtx->mainState = PAUSE_MAIN_STATE_SWITCHING_PAGE;
    pauseCtx->switchPageTimer = 0;

    if (direction == SWITCH_PAGE_LEFT) {
        pauseCtx->nextPageMode = pauseCtx->pageIndex * 2 + 1;
        play_sound(NA_SE_SY_WIN_SCROLL_LEFT);
        pauseCtx->cursorSpecialPos = PAUSE_CURSOR_PAGE_RIGHT;
    } else { // SWITCH_PAGE_RIGHT
        pauseCtx->nextPageMode = pauseCtx->pageIndex * 2;
        play_sound(NA_SE_SY_WIN_SCROLL_RIGHT);
        pauseCtx->cursorSpecialPos = PAUSE_CURSOR_PAGE_LEFT;
    }

    gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_ENABLED;
    gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_DISABLED;
    gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_DISABLED;
    gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_DISABLED;
    gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_DISABLED;

    gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
    Interface_SetHudVisibility(HUD_VISIBILITY_ALL);
}

/**
 * Process inputs to decide whether to switch pages
 */
void KaleidoScope_HandlePageToggles(PlayState* play, Input* input) {
    PauseContext* pauseCtx = &play->pauseCtx;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;

    //! FAKE
    if (1) {}

    if ((pauseCtx->debugEditor == DEBUG_EDITOR_NONE) && !pauseCtx->itemDescriptionOn) {
        if (CHECK_BTN_ALL(input->cur.button, BTN_DRIGHT) || CHECK_BTN_ALL(input->press.button, BTN_R)) {
            // Switch the page to the right regardless of where the cursor is
            if (interfaceCtx->unk_212 == 6) {
                func_8011552C(play, 0x15);
            }
            KaleidoScope_SwitchPage(pauseCtx, SWITCH_PAGE_RIGHT);
        } else if (CHECK_BTN_ALL(input->cur.button, BTN_DLEFT) || CHECK_BTN_ALL(input->press.button, BTN_Z)) {
            // Switch the page to the left regardless of where the cursor is
            if (interfaceCtx->unk_212 == 6) {
                func_8011552C(play, 0x15);
            }
            KaleidoScope_SwitchPage(pauseCtx, SWITCH_PAGE_LEFT);
        } else if (pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_LEFT) {
            //
            if (pauseCtx->stickAdjX < -30) {
                pauseCtx->pageSwitchInputTimer++;
                // Switch the page to the left after a certain number of frames with held input or after a second press
                if ((pauseCtx->pageSwitchInputTimer >= 10) || (pauseCtx->pageSwitchInputTimer == 0)) {
                    KaleidoScope_SwitchPage(pauseCtx, SWITCH_PAGE_LEFT);
                }
            } else {
                // stickAdjX is no longer held, so that the next input to the left will immediately switch pages
                pauseCtx->pageSwitchInputTimer = -1;
            }
        } else if (pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_RIGHT) {
            if (pauseCtx->stickAdjX > 30) {
                pauseCtx->pageSwitchInputTimer++;
                // Switch the page to the right after a certain number of frames with held input or after a second press
                if ((pauseCtx->pageSwitchInputTimer >= 10) || (pauseCtx->pageSwitchInputTimer == 0)) {
                    KaleidoScope_SwitchPage(pauseCtx, SWITCH_PAGE_RIGHT);
                }
            } else {
                // stickAdjY is no longer held, so that the next input to the right will immediately switch pages
                pauseCtx->pageSwitchInputTimer = -1;
            }
        }
    }
}

Gfx* KaleidoScope_DrawPageSections(Gfx* gfx, Vtx* vertices, void** textures) {
    s32 i;
    s32 j;

    gSPVertex(gfx++, vertices, 32, 0);

    i = 0;
    j = 0;
    while (j < 32) {
        gDPPipeSync(gfx++);
        gDPLoadTextureBlock(gfx++, textures[i], G_IM_FMT_IA, G_IM_SIZ_8b, 80, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSP1Quadrangle(gfx++, j, j + 2, j + 3, j + 1, 0);

        j += 4;
        i++;
    }

    gSPVertex(gfx++, vertices + 32, 28, 0);

    j = 0;
    while (j < 28) {
        gDPPipeSync(gfx++);
        gDPLoadTextureBlock(gfx++, textures[i], G_IM_FMT_IA, G_IM_SIZ_8b, 80, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSP1Quadrangle(gfx++, j, j + 2, j + 3, j + 1, 0);

        j += 4;
        i++;
    }

    return gfx;
}

s16 sCursorPrimColorTarget[][3] = {
    { 255, 255, 255 }, { 255, 255, 255 }, { 255, 255, 0 }, { 255, 255, 0 }, { 100, 150, 255 }, { 100, 255, 255 },
};
s16 sCursorEnvColorTarget[][3] = {
    { 0, 0, 0 }, { 170, 170, 170 }, { 0, 0, 0 }, { 255, 160, 0 }, { 0, 0, 100 }, { 0, 150, 255 },
};
void KaleidoScope_DrawPages(PlayState* play, GraphicsContext* gfxCtx) {
    static s16 sCursorColorTimer = 10;
    static s16 sCursorColorTargetIndex = 0;
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 stepR;
    s16 stepG;
    s16 stepB;

    OPEN_DISPS(gfxCtx);

    if (!IS_PAUSE_STATE_GAMEOVER) {
        if (pauseCtx->state != PAUSE_STATE_SAVEPROMPT) {

            stepR =
                ABS_ALT(sCursorPrimR - sCursorPrimColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][0]) /
                sCursorColorTimer;
            stepG =
                ABS_ALT(sCursorPrimG - sCursorPrimColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][1]) /
                sCursorColorTimer;
            stepB =
                ABS_ALT(sCursorPrimB - sCursorPrimColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][2]) /
                sCursorColorTimer;

            if (sCursorPrimR >= sCursorPrimColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][0]) {
                sCursorPrimR -= stepR;
            } else {
                sCursorPrimR += stepR;
            }

            if (sCursorPrimG >= sCursorPrimColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][1]) {
                sCursorPrimG -= stepG;
            } else {
                sCursorPrimG += stepG;
            }

            if (sCursorPrimB >= sCursorPrimColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][2]) {
                sCursorPrimB -= stepB;
            } else {
                sCursorPrimB += stepB;
            }

            stepR =
                ABS_ALT(sCursorEnvR - sCursorEnvColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][0]) /
                sCursorColorTimer;
            stepG =
                ABS_ALT(sCursorEnvG - sCursorEnvColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][1]) /
                sCursorColorTimer;
            stepB =
                ABS_ALT(sCursorEnvB - sCursorEnvColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][2]) /
                sCursorColorTimer;

            if (sCursorEnvR >= sCursorEnvColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][0]) {
                sCursorEnvR -= stepR;
            } else {
                sCursorEnvR += stepR;
            }

            if (sCursorEnvG >= sCursorEnvColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][1]) {
                sCursorEnvG -= stepG;
            } else {
                sCursorEnvG += stepG;
            }

            if (sCursorEnvB >= sCursorEnvColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][2]) {
                sCursorEnvB -= stepB;
            } else {
                sCursorEnvB += stepB;
            }

            sCursorColorTimer--;
            if (sCursorColorTimer == 0) {
                sCursorPrimR = sCursorPrimColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][0];
                sCursorPrimG = sCursorPrimColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][1];
                sCursorPrimB = sCursorPrimColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][2];
                sCursorEnvR = sCursorEnvColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][0];
                sCursorEnvG = sCursorEnvColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][1];
                sCursorEnvB = sCursorEnvColorTarget[pauseCtx->cursorColorSet + sCursorColorTargetIndex][2];
                sCursorColorTargetIndex ^= 1;
                sCursorColorTimer = 10;
            }
        }

        if ((pauseCtx->pageIndex != PAUSE_ITEM) && (pauseCtx->pageIndex != PAUSE_QUEST)) {
            gDPPipeSync(POLY_OPA_DISP++);

            gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0,
                              TEXEL0, 0, SHADE, 0);

            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);

            Matrix_RotateYF(0.0f, MTXMODE_NEW);
            Matrix_Translate(0.0f, sPauseMenuVerticalOffset / 100.0f, -93.0f, MTXMODE_APPLY);
            Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
            Matrix_RotateXFApply(-pauseCtx->itemPageRoll / 100.0f);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->itemPageVtx, sSelectItemTextures);

            KaleidoScope_DrawItemSelect(play);
        }

        if ((pauseCtx->pageIndex != PAUSE_MAP) && (pauseCtx->pageIndex != PAUSE_MASK)) {
            gDPPipeSync(POLY_OPA_DISP++);

            gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0,
                              TEXEL0, 0, SHADE, 0);

            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);

            Matrix_RotateYF(-1.57f, MTXMODE_NEW);
            Matrix_Translate(0.0f, sPauseMenuVerticalOffset / 100.0f, -93.0f, MTXMODE_APPLY);
            Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
            Matrix_RotateXFApply(-pauseCtx->mapPageRoll / 100.0f);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->mapPageVtx, sMapTextures);

            if (sInDungeonScene) {
                KaleidoScope_DrawDungeonMap(play);
                func_8012C8AC(gfxCtx);
                gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                func_801091F0(play);
            } else {
                KaleidoScope_DrawWorldMap(play);
            }
        }

        if ((pauseCtx->pageIndex != PAUSE_QUEST) && (pauseCtx->pageIndex != PAUSE_ITEM)) {
            gDPPipeSync(POLY_OPA_DISP++);

            gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_BILERP);

            gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0,
                              TEXEL0, 0, SHADE, 0);

            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);

            Matrix_RotateYF(-3.14f, MTXMODE_NEW);
            Matrix_Translate(0.0f, sPauseMenuVerticalOffset / 100.0f, -93.0f, MTXMODE_APPLY);
            Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
            Matrix_RotateXFApply(-pauseCtx->questPageRoll / 100.0f);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->questPageVtx, sQuestStatusTextures);

            KaleidoScope_DrawQuestStatus(play);
        }

        if ((pauseCtx->pageIndex != PAUSE_MASK) && (pauseCtx->pageIndex != PAUSE_MAP)) {
            gDPPipeSync(POLY_OPA_DISP++);

            gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_BILERP);

            gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0,
                              TEXEL0, 0, SHADE, 0);

            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);

            Matrix_RotateYF(1.57f, MTXMODE_NEW);
            Matrix_Translate(0.0f, sPauseMenuVerticalOffset / 100.0f, -93.0f, MTXMODE_APPLY);
            Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
            Matrix_RotateXFApply(-pauseCtx->maskPageRoll / 100.0f);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->maskPageVtx, sSelectMaskTextures);

            KaleidoScope_DrawMaskSelect(play);
        }

        switch (pauseCtx->pageIndex) {
            case PAUSE_ITEM:
                if (pauseCtx->mainState <= PAUSE_MAIN_STATE_EQUIP_MASK) {
                    gDPPipeSync(POLY_OPA_DISP++);

                    gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0,
                                      PRIMITIVE, 0, TEXEL0, 0, SHADE, 0);

                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);

                    Matrix_RotateYF(0.0f, MTXMODE_NEW);
                    Matrix_Translate(0.0f, sPauseMenuVerticalOffset / 100.0f, -93.0f, MTXMODE_APPLY);
                    Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
                    Matrix_RotateXFApply(-pauseCtx->itemPageRoll / 100.0f);

                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    POLY_OPA_DISP =
                        KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->itemPageVtx, sSelectItemTextures);

                    KaleidoScope_DrawItemSelect(play);
                }
                break;

            case PAUSE_MAP:
                gDPPipeSync(POLY_OPA_DISP++);

                gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE,
                                  0, TEXEL0, 0, SHADE, 0);

                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);

                Matrix_RotateYF(-1.57f, MTXMODE_NEW);
                Matrix_Translate(0.0f, sPauseMenuVerticalOffset / 100.0f, -93.0f, MTXMODE_APPLY);
                Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
                Matrix_RotateXFApply(-pauseCtx->mapPageRoll / 100.0f);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->mapPageVtx, sMapTextures);

                if (sInDungeonScene) {
                    KaleidoScope_DrawDungeonMap(play);
                    func_8012C8AC(gfxCtx);

                    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

                    func_801091F0(play);
                } else {
                    Matrix_RotateYF(R_PAUSE_WORLD_MAP_YAW / 1000.0f, MTXMODE_NEW);

                    if ((pauseCtx->state == PAUSE_STATE_OPENING_3) || (pauseCtx->state == PAUSE_STATE_OWLWARP_3) ||
                        (pauseCtx->state >= PAUSE_STATE_OWLWARP_6) ||
                        ((pauseCtx->state == PAUSE_STATE_SAVEPROMPT) &&
                         ((pauseCtx->savePromptState == PAUSE_SAVEPROMPT_STATE_3) ||
                          (pauseCtx->savePromptState == PAUSE_SAVEPROMPT_STATE_7)))) {
                        Matrix_Translate(0.0f, (R_PAUSE_WORLD_MAP_Y_OFFSET - 8000) / 100.0f,
                                         R_PAUSE_WORLD_MAP_DEPTH / 100.0f, MTXMODE_APPLY);
                    } else {
                        Matrix_Translate(0.0f, R_PAUSE_WORLD_MAP_Y_OFFSET / 100.0f, R_PAUSE_WORLD_MAP_DEPTH / 100.0f,
                                         MTXMODE_APPLY);
                    }

                    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
                    Matrix_RotateXFApply(-pauseCtx->mapPageRoll / 100.0f);

                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    KaleidoScope_DrawWorldMap(play);
                }
                break;

            case PAUSE_QUEST:
                gDPPipeSync(POLY_OPA_DISP++);

                gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE,
                                  0, TEXEL0, 0, SHADE, 0);

                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);

                gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_BILERP);

                Matrix_RotateYF(-3.14f, MTXMODE_NEW);
                Matrix_Translate(0.0f, sPauseMenuVerticalOffset / 100.0f, -93.0f, MTXMODE_APPLY);
                Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
                Matrix_RotateXFApply(-pauseCtx->questPageRoll / 100.0f);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                POLY_OPA_DISP =
                    KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->questPageVtx, sQuestStatusTextures);

                KaleidoScope_DrawQuestStatus(play);
                break;

            case PAUSE_MASK:
                gDPPipeSync(POLY_OPA_DISP++);

                gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE,
                                  0, TEXEL0, 0, SHADE, 0);

                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);

                Matrix_RotateYF(1.57f, MTXMODE_NEW);
                Matrix_Translate(0.0f, sPauseMenuVerticalOffset / 100.0f, -93.0f, MTXMODE_APPLY);
                Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
                Matrix_RotateXFApply(-pauseCtx->maskPageRoll / 100.0f);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                POLY_OPA_DISP =
                    KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->maskPageVtx, sSelectMaskTextures);

                KaleidoScope_DrawMaskSelect(play);
                break;
        }
    }

    CLOSE_DISPS(gfxCtx);
}

TexturePtr D_8082B998[] = {
    gPauseToMasksENGTex,
    gPauseToSelectItemENGTex,
    gPauseToMapENGTex,
    gPauseToQuestStatusENGTex,
};
TexturePtr D_8082B9A8[] = {
    gPauseToMapENGTex,
    gPauseToQuestStatusENGTex,
    gPauseToMasksENGTex,
    gPauseToSelectItemENGTex,
};
void KaleidoScope_DrawInfoPanel(PlayState* play) {
    static s16 sPauseLRCursorColorTargets[][4] = {
        { 180, 210, 255, 220 },
        { 100, 100, 150, 220 },
    };
    static s16 sPauseLRCursorColorTimer = 20;
    static s16 sPauseLRCursorColorIndex = 0;
    static s16 sPauseLRCursorRed;
    static s16 sPauseLRCursorGreen;
    static s16 sPauseLRCursorBlue;
    static s16 sPauseLRCursorAlpha;
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 stepR;
    s16 stepG;
    s16 stepB;
    s16 stepA;
    s16 y;
    s16 i;
    s16 j;

    OPEN_DISPS(play->state.gfxCtx);

    stepR =
        ABS_ALT(sPauseLRCursorRed - sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][0]) / sPauseLRCursorColorTimer;
    stepG = ABS_ALT(sPauseLRCursorGreen - sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][1]) /
            sPauseLRCursorColorTimer;
    stepB = ABS_ALT(sPauseLRCursorBlue - sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][2]) /
            sPauseLRCursorColorTimer;
    stepA = ABS_ALT(sPauseLRCursorAlpha - sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][3]) /
            sPauseLRCursorColorTimer;

    if (sPauseLRCursorRed >= sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][0]) {
        sPauseLRCursorRed -= stepR;
    } else {
        sPauseLRCursorRed += stepR;
    }

    if (sPauseLRCursorGreen >= sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][1]) {
        sPauseLRCursorGreen -= stepG;
    } else {
        sPauseLRCursorGreen += stepG;
    }

    if (sPauseLRCursorBlue >= sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][2]) {
        sPauseLRCursorBlue -= stepB;
    } else {
        sPauseLRCursorBlue += stepB;
    }

    if (sPauseLRCursorAlpha >= sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][3]) {
        sPauseLRCursorAlpha -= stepA;
    } else {
        sPauseLRCursorAlpha += stepA;
    }

    sPauseLRCursorColorTimer--;
    if (sPauseLRCursorColorTimer == 0) {
        sPauseLRCursorRed = sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][0];
        sPauseLRCursorGreen = sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][1];
        sPauseLRCursorBlue = sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][2];
        sPauseLRCursorAlpha = sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][3];
        sPauseLRCursorColorTimer = D_8082B924[0];
        sPauseLRCursorColorIndex ^= 1;
    }

    y = pauseCtx->infoPanelOffsetY - 76;
    for (j = 0, i = 0; i < 7; i++, j += 4) {
        pauseCtx->infoPanelVtx[j + 0].v.ob[0] = pauseCtx->infoPanelVtx[j + 2].v.ob[0] = -72;

        pauseCtx->infoPanelVtx[j + 1].v.ob[0] = pauseCtx->infoPanelVtx[j + 3].v.ob[0] = 0;

        pauseCtx->infoPanelVtx[j + 0].v.ob[1] = pauseCtx->infoPanelVtx[j + 1].v.ob[1] = y;

        pauseCtx->infoPanelVtx[j + 2].v.ob[1] = pauseCtx->infoPanelVtx[j + 3].v.ob[1] = y - 24;

        pauseCtx->infoPanelVtx[j + 0].v.ob[2] = pauseCtx->infoPanelVtx[j + 1].v.ob[2] =
            pauseCtx->infoPanelVtx[j + 2].v.ob[2] = pauseCtx->infoPanelVtx[j + 3].v.ob[2] = 0;

        pauseCtx->infoPanelVtx[j + 0].v.flag = pauseCtx->infoPanelVtx[j + 1].v.flag =
            pauseCtx->infoPanelVtx[j + 2].v.flag = pauseCtx->infoPanelVtx[j + 3].v.flag = 0;

        pauseCtx->infoPanelVtx[j + 0].v.tc[0] = pauseCtx->infoPanelVtx[j + 0].v.tc[1] =
            pauseCtx->infoPanelVtx[j + 1].v.tc[1] = pauseCtx->infoPanelVtx[j + 2].v.tc[0] = 0;

        pauseCtx->infoPanelVtx[j + 1].v.tc[0] = pauseCtx->infoPanelVtx[j + 3].v.tc[0] = 72 * (1 << 5);

        pauseCtx->infoPanelVtx[j + 2].v.tc[1] = pauseCtx->infoPanelVtx[j + 3].v.tc[1] = 24 * (1 << 5);

        pauseCtx->infoPanelVtx[j + 0].v.cn[0] = pauseCtx->infoPanelVtx[j + 2].v.cn[0] =
            pauseCtx->infoPanelVtx[j + 0].v.cn[1] = pauseCtx->infoPanelVtx[j + 2].v.cn[1] =
                pauseCtx->infoPanelVtx[j + 0].v.cn[2] = pauseCtx->infoPanelVtx[j + 2].v.cn[2] =
                    pauseCtx->infoPanelVtx[j + 1].v.cn[0] = pauseCtx->infoPanelVtx[j + 3].v.cn[0] =
                        pauseCtx->infoPanelVtx[j + 1].v.cn[1] = pauseCtx->infoPanelVtx[j + 3].v.cn[1] =
                            pauseCtx->infoPanelVtx[j + 1].v.cn[2] = pauseCtx->infoPanelVtx[j + 3].v.cn[2] = 200;

        pauseCtx->infoPanelVtx[j + 0].v.cn[3] = pauseCtx->infoPanelVtx[j + 2].v.cn[3] =
            pauseCtx->infoPanelVtx[j + 1].v.cn[3] = pauseCtx->infoPanelVtx[j + 3].v.cn[3] = pauseCtx->alpha;
    }

    pauseCtx->infoPanelVtx[4].v.ob[0] = pauseCtx->infoPanelVtx[6].v.ob[0] = pauseCtx->infoPanelVtx[0].v.ob[0] + 72;

    pauseCtx->infoPanelVtx[5].v.ob[0] = pauseCtx->infoPanelVtx[7].v.ob[0] = pauseCtx->infoPanelVtx[4].v.ob[0] + 72;

    if ((pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_LEFT) && (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE)) {
        pauseCtx->infoPanelVtx[8].v.ob[0] = pauseCtx->infoPanelVtx[10].v.ob[0] = sPauseCursorLeftX;

        pauseCtx->infoPanelVtx[9].v.ob[0] = pauseCtx->infoPanelVtx[11].v.ob[0] = pauseCtx->infoPanelVtx[8].v.ob[0] + 24;

        pauseCtx->infoPanelVtx[8].v.ob[1] = pauseCtx->infoPanelVtx[9].v.ob[1] = D_8082B920;

        pauseCtx->infoPanelVtx[10].v.ob[1] = pauseCtx->infoPanelVtx[11].v.ob[1] =
            pauseCtx->infoPanelVtx[8].v.ob[1] - 32;
    } else {
        pauseCtx->infoPanelVtx[8].v.ob[0] = pauseCtx->infoPanelVtx[10].v.ob[0] = sPauseCursorLeftX + 3;

        pauseCtx->infoPanelVtx[9].v.ob[0] = pauseCtx->infoPanelVtx[11].v.ob[0] = pauseCtx->infoPanelVtx[8].v.ob[0] + 18;

        pauseCtx->infoPanelVtx[8].v.ob[1] = pauseCtx->infoPanelVtx[9].v.ob[1] = D_8082B920 - 3;

        pauseCtx->infoPanelVtx[10].v.ob[1] = pauseCtx->infoPanelVtx[11].v.ob[1] =
            pauseCtx->infoPanelVtx[8].v.ob[1] - 26;
    }

    if ((pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_RIGHT) && (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE)) {
        pauseCtx->infoPanelVtx[12].v.ob[0] = pauseCtx->infoPanelVtx[14].v.ob[0] = sPauseCursorRightX;

        pauseCtx->infoPanelVtx[13].v.ob[0] = pauseCtx->infoPanelVtx[15].v.ob[0] =
            pauseCtx->infoPanelVtx[12].v.ob[0] + 24;

        pauseCtx->infoPanelVtx[12].v.ob[1] = pauseCtx->infoPanelVtx[13].v.ob[1] = D_8082B920;

        pauseCtx->infoPanelVtx[14].v.ob[1] = pauseCtx->infoPanelVtx[15].v.ob[1] =
            pauseCtx->infoPanelVtx[12].v.ob[1] - 32;
    } else {
        pauseCtx->infoPanelVtx[12].v.ob[0] = pauseCtx->infoPanelVtx[14].v.ob[0] = sPauseCursorRightX + 3;

        pauseCtx->infoPanelVtx[13].v.ob[0] = pauseCtx->infoPanelVtx[15].v.ob[0] =
            pauseCtx->infoPanelVtx[12].v.ob[0] + 18;

        pauseCtx->infoPanelVtx[12].v.ob[1] = pauseCtx->infoPanelVtx[13].v.ob[1] = D_8082B920 - 3;

        pauseCtx->infoPanelVtx[14].v.ob[1] = pauseCtx->infoPanelVtx[15].v.ob[1] =
            pauseCtx->infoPanelVtx[12].v.ob[1] - 26;
    }

    pauseCtx->infoPanelVtx[9].v.tc[0] = pauseCtx->infoPanelVtx[11].v.tc[0] = pauseCtx->infoPanelVtx[13].v.tc[0] =
        pauseCtx->infoPanelVtx[15].v.tc[0] = 24 * (1 << 5);

    pauseCtx->infoPanelVtx[10].v.tc[1] = pauseCtx->infoPanelVtx[11].v.tc[1] = pauseCtx->infoPanelVtx[14].v.tc[1] =
        pauseCtx->infoPanelVtx[15].v.tc[1] = 32 * (1 << 5);

    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    Matrix_Translate(0.0f, 0.0f, -144.0f, MTXMODE_NEW);
    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 150, 140, 90, 255);
    gSPVertex(POLY_OPA_DISP++, &pauseCtx->infoPanelVtx[0], 16, 0);

    gSPDisplayList(POLY_OPA_DISP++, gItemNamePanelDL);

    if ((pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_LEFT) &&
        (!pauseCtx->mainState || (pauseCtx->mainState == PAUSE_MAIN_STATE_UNK))) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 150, 140, 90, sPauseLRCursorAlpha);
    }

    gSPDisplayList(POLY_OPA_DISP++, gLButtonIconDL);

    if ((pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_RIGHT) &&
        (!pauseCtx->mainState || (pauseCtx->mainState == PAUSE_MAIN_STATE_UNK))) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 150, 140, 90, sPauseLRCursorAlpha);
    }

    gSPDisplayList(POLY_OPA_DISP++, gRButtonIconDL);

    if (pauseCtx->cursorSpecialPos != 0) {
        j = (pauseCtx->cursorSpecialPos * 4) - 32;
        pauseCtx->cursorVtx[0].v.ob[0] = pauseCtx->infoPanelVtx[j].v.ob[0];
        pauseCtx->cursorVtx[0].v.ob[1] = pauseCtx->infoPanelVtx[j].v.ob[1];
    }

    y = pauseCtx->infoPanelOffsetY - 80;
    pauseCtx->infoPanelVtx[16].v.ob[1] = pauseCtx->infoPanelVtx[17].v.ob[1] = y;

    pauseCtx->infoPanelVtx[18].v.ob[1] = pauseCtx->infoPanelVtx[19].v.ob[1] = pauseCtx->infoPanelVtx[16].v.ob[1] - 16;

    pauseCtx->infoPanelVtx[18].v.tc[1] = pauseCtx->infoPanelVtx[19].v.tc[1] = 16 * (1 << 5);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetEnvColor(POLY_OPA_DISP++, 20, 30, 40, 0);

    if (pauseCtx->itemDescriptionOn ||
        ((pauseCtx->state == PAUSE_STATE_MAIN) && (pauseCtx->namedItem != PAUSE_ITEM_NONE) &&
         (pauseCtx->nameDisplayTimer < 40) &&
         (!pauseCtx->mainState || (pauseCtx->mainState == PAUSE_MAIN_STATE_SONG_PLAYBACK) ||
          (pauseCtx->mainState == PAUSE_MAIN_STATE_UNK) ||
          ((pauseCtx->mainState >= PAUSE_MAIN_STATE_SONG_PROMPT_INIT) &&
           (pauseCtx->mainState <= PAUSE_MAIN_STATE_SONG_PROMPT_UNUSED)) ||
          (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG)) &&
         (pauseCtx->cursorSpecialPos == 0))) {
        if (!pauseCtx->mainState || (pauseCtx->mainState == PAUSE_MAIN_STATE_SONG_PLAYBACK) ||
            (pauseCtx->mainState == PAUSE_MAIN_STATE_UNK) ||
            ((pauseCtx->mainState >= PAUSE_MAIN_STATE_SONG_PROMPT_INIT) &&
             (pauseCtx->mainState <= PAUSE_MAIN_STATE_SONG_PROMPT_UNUSED)) ||
            (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG)) {

            pauseCtx->infoPanelVtx[16].v.ob[0] = pauseCtx->infoPanelVtx[18].v.ob[0] = -63;

            pauseCtx->infoPanelVtx[17].v.ob[0] = pauseCtx->infoPanelVtx[19].v.ob[0] =
                pauseCtx->infoPanelVtx[16].v.ob[0] + 128;

            pauseCtx->infoPanelVtx[17].v.tc[0] = pauseCtx->infoPanelVtx[19].v.tc[0] = 128 * (1 << 5);

            gSPVertex(POLY_OPA_DISP++, &pauseCtx->infoPanelVtx[16], 4, 0);

            if (pauseCtx->nameColorSet == 1) {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 70, 70, 70, 255);
            } else {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
            }

            POLY_OPA_DISP = Gfx_DrawTexQuad4b(POLY_OPA_DISP, pauseCtx->nameSegment, G_IM_FMT_IA, 128, 16, 0);
        }
    } else if ((pauseCtx->mainState <= PAUSE_MAIN_STATE_SONG_PLAYBACK) ||
               (pauseCtx->mainState == PAUSE_MAIN_STATE_SONG_PROMPT_UNUSED) ||
               (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG) ||
               (pauseCtx->mainState == PAUSE_MAIN_STATE_UNK)) {
        pauseCtx->infoPanelVtx[20].v.ob[1] = pauseCtx->infoPanelVtx[21].v.ob[1] = y;

        pauseCtx->infoPanelVtx[22].v.ob[1] = pauseCtx->infoPanelVtx[23].v.ob[1] =
            pauseCtx->infoPanelVtx[20].v.ob[1] - 16;

        pauseCtx->infoPanelVtx[22].v.tc[1] = pauseCtx->infoPanelVtx[23].v.tc[1] = 16 * (1 << 5);

        gSPVertex(POLY_OPA_DISP++, &pauseCtx->infoPanelVtx[16], 8, 0);

        if (pauseCtx->state == PAUSE_STATE_SAVEPROMPT) {
            pauseCtx->infoPanelVtx[16].v.ob[0] = pauseCtx->infoPanelVtx[18].v.ob[0] = -33;

            pauseCtx->infoPanelVtx[17].v.ob[0] = pauseCtx->infoPanelVtx[19].v.ob[0] =
                pauseCtx->infoPanelVtx[16].v.ob[0] + 24;

            pauseCtx->infoPanelVtx[20].v.ob[0] = pauseCtx->infoPanelVtx[22].v.ob[0] =
                pauseCtx->infoPanelVtx[16].v.ob[0] + 0x10;

            pauseCtx->infoPanelVtx[21].v.ob[0] = pauseCtx->infoPanelVtx[23].v.ob[0] =
                pauseCtx->infoPanelVtx[20].v.ob[0] + 0x30;

            pauseCtx->infoPanelVtx[17].v.tc[0] = pauseCtx->infoPanelVtx[19].v.tc[0] = 24 * (1 << 5);

            pauseCtx->infoPanelVtx[21].v.tc[0] = pauseCtx->infoPanelVtx[23].v.tc[0] = 48 * (1 << 5);

            gSPDisplayList(POLY_OPA_DISP++, gAButtonIconDL);
            gDPPipeSync(POLY_OPA_DISP++);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);

            //! @bug: Incorrect dimensions. Should be 64x16
            POLY_OPA_DISP = Gfx_DrawTexQuad4b(POLY_OPA_DISP, gPauseToDecideENGTex, G_IM_FMT_IA, 48, 16, 4);

        } else if (pauseCtx->cursorSpecialPos != 0) {
            if ((pauseCtx->state == PAUSE_STATE_MAIN) && (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE)) {

                pauseCtx->infoPanelVtx[16].v.ob[0] = pauseCtx->infoPanelVtx[18].v.ob[0] = -63;

                pauseCtx->infoPanelVtx[17].v.ob[0] = pauseCtx->infoPanelVtx[19].v.ob[0] =
                    pauseCtx->infoPanelVtx[16].v.ob[0] + 128;

                pauseCtx->infoPanelVtx[17].v.tc[0] = pauseCtx->infoPanelVtx[19].v.tc[0] = 128 * (1 << 5);

                gDPPipeSync(POLY_OPA_DISP++);
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 200, 0, 255);

                if (pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_LEFT) {
                    POLY_OPA_DISP =
                        Gfx_DrawTexQuad4b(POLY_OPA_DISP, D_8082B998[pauseCtx->pageIndex], G_IM_FMT_IA, 128, 16, 0);
                } else {
                    POLY_OPA_DISP =
                        Gfx_DrawTexQuad4b(POLY_OPA_DISP, D_8082B9A8[pauseCtx->pageIndex], G_IM_FMT_IA, 128, 16, 0);
                }
            }
        } else if ((!pauseCtx->pageIndex || (pauseCtx->pageIndex == PAUSE_MASK)) &&
                   (pauseCtx->namedItem != PAUSE_ITEM_NONE)) {
            pauseCtx->infoPanelVtx[16].v.ob[0] = pauseCtx->infoPanelVtx[18].v.ob[0] = -49;

            pauseCtx->infoPanelVtx[17].v.ob[0] = pauseCtx->infoPanelVtx[19].v.ob[0] =
                pauseCtx->infoPanelVtx[16].v.ob[0] + 48;

            pauseCtx->infoPanelVtx[20].v.ob[0] = pauseCtx->infoPanelVtx[22].v.ob[0] =
                pauseCtx->infoPanelVtx[16].v.ob[0] + 47;

            pauseCtx->infoPanelVtx[21].v.ob[0] = pauseCtx->infoPanelVtx[23].v.ob[0] =
                pauseCtx->infoPanelVtx[20].v.ob[0] + 64;

            pauseCtx->infoPanelVtx[17].v.tc[0] = pauseCtx->infoPanelVtx[19].v.tc[0] = 48 * (1 << 5);

            pauseCtx->infoPanelVtx[21].v.tc[0] = pauseCtx->infoPanelVtx[23].v.tc[0] = 64 * (1 << 5);

            gSPDisplayList(POLY_OPA_DISP++, gCButtonIconsDL);

            gDPPipeSync(POLY_OPA_DISP++);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);

            POLY_OPA_DISP = Gfx_DrawTexQuad4b(POLY_OPA_DISP, gPauseToEquipENGTex, G_IM_FMT_IA, 64, 16, 4);
        } else if ((pauseCtx->pageIndex == PAUSE_MAP) && sInDungeonScene) {
            // No code in this case
        } else if ((pauseCtx->pageIndex == PAUSE_QUEST) &&
                   (pauseCtx->cursorSlot[PAUSE_QUEST] == QUEST_BOMBERS_NOTEBOOK)) {
            if (pauseCtx->namedItem != PAUSE_ITEM_NONE) {
                // The cursor is on the bombers notebook
                pauseCtx->infoPanelVtx[16].v.ob[0] = pauseCtx->infoPanelVtx[18].v.ob[0] = -58;

                pauseCtx->infoPanelVtx[17].v.ob[0] = pauseCtx->infoPanelVtx[19].v.ob[0] =
                    pauseCtx->infoPanelVtx[16].v.ob[0] + 24;

                pauseCtx->infoPanelVtx[20].v.ob[0] = pauseCtx->infoPanelVtx[22].v.ob[0] =
                    pauseCtx->infoPanelVtx[16].v.ob[0] + 0x14;

                pauseCtx->infoPanelVtx[21].v.ob[0] = pauseCtx->infoPanelVtx[23].v.ob[0] =
                    pauseCtx->infoPanelVtx[20].v.ob[0] + 0x60;

                pauseCtx->infoPanelVtx[17].v.tc[0] = pauseCtx->infoPanelVtx[19].v.tc[0] = 24 * (1 << 5);

                pauseCtx->infoPanelVtx[21].v.tc[0] = pauseCtx->infoPanelVtx[23].v.tc[0] = 96 * (1 << 5);

                gSPDisplayList(POLY_OPA_DISP++, gAButtonIconDL);

                gDPPipeSync(POLY_OPA_DISP++);
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);

                POLY_OPA_DISP = Gfx_DrawTexQuad4b(POLY_OPA_DISP, gPauseToViewNotebookENGTex, G_IM_FMT_IA, 96, 16, 4);
            }
        } else if ((pauseCtx->pageIndex == PAUSE_QUEST) && (pauseCtx->cursorSlot[PAUSE_QUEST] >= QUEST_SONG_SONATA) &&
                   (pauseCtx->cursorSlot[PAUSE_QUEST] <= QUEST_SONG_SUN) && (pauseCtx->namedItem != PAUSE_ITEM_NONE)) {
            // The cursor is on a learned song
            pauseCtx->infoPanelVtx[16].v.ob[0] = pauseCtx->infoPanelVtx[18].v.ob[0] = -55;

            pauseCtx->infoPanelVtx[17].v.ob[0] = pauseCtx->infoPanelVtx[19].v.ob[0] =
                pauseCtx->infoPanelVtx[16].v.ob[0] + 24;

            pauseCtx->infoPanelVtx[20].v.ob[0] = pauseCtx->infoPanelVtx[22].v.ob[0] =
                pauseCtx->infoPanelVtx[16].v.ob[0] + 20;

            pauseCtx->infoPanelVtx[21].v.ob[0] = pauseCtx->infoPanelVtx[23].v.ob[0] =
                pauseCtx->infoPanelVtx[20].v.ob[0] + 96;

            pauseCtx->infoPanelVtx[17].v.tc[0] = pauseCtx->infoPanelVtx[19].v.tc[0] = 24 * (1 << 5);

            pauseCtx->infoPanelVtx[21].v.tc[0] = pauseCtx->infoPanelVtx[23].v.tc[0] = 96 * (1 << 5);

            gSPDisplayList(POLY_OPA_DISP++, gAButtonIconDL);

            gDPPipeSync(POLY_OPA_DISP++);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);

            POLY_OPA_DISP = Gfx_DrawTexQuad4b(POLY_OPA_DISP, gPauseToPlayMelodyENGTex, G_IM_FMT_IA, 96, 16, 4);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

u8 sUnpausedButtonStatus[5];
f32 sCursorCirclesX[4];
f32 sCursorCirclesY[4];

void KaleidoScope_UpdateNamePanel(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;
    u16 namedItem;

    if ((pauseCtx->namedItem != pauseCtx->cursorItem[pauseCtx->pageIndex]) ||
        ((pauseCtx->pageIndex == PAUSE_MAP) && (pauseCtx->cursorSpecialPos != 0))) {

        pauseCtx->namedItem = pauseCtx->cursorItem[pauseCtx->pageIndex];
        namedItem = pauseCtx->namedItem;

        osCreateMesgQueue(&pauseCtx->loadQueue, &pauseCtx->loadMsg, 1);

        if (pauseCtx->namedItem != PAUSE_ITEM_NONE) {
            if ((pauseCtx->pageIndex == PAUSE_MAP) && !sInDungeonScene) {
                func_80821900(pauseCtx->nameSegment, namedItem);
            } else {
                func_80821958(pauseCtx->nameSegment, namedItem);
            }
            pauseCtx->nameDisplayTimer = 0;
        }
    } else if (pauseCtx->nameColorSet == 0) {
        if (((pauseCtx->pageIndex == PAUSE_QUEST) && (pauseCtx->cursorSlot[PAUSE_QUEST] >= QUEST_SONG_SONATA) &&
             (pauseCtx->cursorSlot[PAUSE_QUEST] <= QUEST_SONG_SUN) &&
             (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG)) ||
            ((pauseCtx->pageIndex == PAUSE_QUEST) && (pauseCtx->cursorSlot[PAUSE_QUEST] == QUEST_BOMBERS_NOTEBOOK)) ||
            (pauseCtx->pageIndex == PAUSE_ITEM) || (pauseCtx->pageIndex == PAUSE_MASK)) {

            pauseCtx->nameDisplayTimer++;
            if (pauseCtx->nameDisplayTimer > 70) {
                pauseCtx->nameDisplayTimer = 0;
            }
        } else {
            pauseCtx->nameDisplayTimer = 0;
        }
    } else {
        pauseCtx->nameDisplayTimer = 0;
    }
}

void KaleidoScope_DrawOwlWarpMapPage(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;

    OPEN_DISPS(play->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);

    gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0,
                      SHADE, 0);

    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);

    Matrix_RotateYF(-1.57f, MTXMODE_NEW); // (-M_PI / 2)
    Matrix_Translate(0.0f, sPauseMenuVerticalOffset / 100.0f, -93.0f, MTXMODE_APPLY);
    Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
    Matrix_RotateXFApply(-pauseCtx->mapPageRoll / 100.0f);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->mapPageVtx, sMapTextures);

    Matrix_RotateYF(R_PAUSE_WORLD_MAP_YAW / 1000.0f, MTXMODE_NEW);

    if ((pauseCtx->state == PAUSE_STATE_OPENING_3) || (pauseCtx->state == PAUSE_STATE_OWLWARP_3) ||
        (pauseCtx->state >= PAUSE_STATE_OWLWARP_6) ||
        ((pauseCtx->state == PAUSE_STATE_SAVEPROMPT) && ((pauseCtx->savePromptState == PAUSE_SAVEPROMPT_STATE_3) ||
                                                         (pauseCtx->savePromptState == PAUSE_SAVEPROMPT_STATE_7)))) {
        Matrix_Translate(0.0f, (R_PAUSE_WORLD_MAP_Y_OFFSET - 8000) / 100.0f, R_PAUSE_WORLD_MAP_DEPTH / 100.0f,
                         MTXMODE_APPLY);
    } else {
        Matrix_Translate(0.0f, R_PAUSE_WORLD_MAP_Y_OFFSET / 100.0f, R_PAUSE_WORLD_MAP_DEPTH / 100.0f, MTXMODE_APPLY);
    }

    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
    Matrix_RotateXFApply(-pauseCtx->mapPageRoll / 100.0f);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    KaleidoScope_DrawWorldMap(play);

    CLOSE_DISPS(play->state.gfxCtx);
}

void KaleidoScope_DrawOwlWarpInfoPanel(PlayState* play) {
    static s16 sPauseLRCursorColorTargets[][4] = {
        { 180, 210, 255, 220 },
        { 100, 100, 150, 220 },
    };
    static s16 sPauseLRCursorColorTimer = 20;
    static s16 sPauseLRCursorColorIndex = 0;
    static s16 sPauseLRCursorRed;
    static s16 sPauseLRCursorGreen;
    static s16 sPauseLRCursorBlue;
    static s16 sPauseLRCursorAlpha;
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 stepR;
    s16 stepG;
    s16 stepB;
    s16 stepA;
    s16 y;
    s16 i;
    s16 j;

    OPEN_DISPS(play->state.gfxCtx);

    stepR =
        ABS_ALT(sPauseLRCursorRed - sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][0]) / sPauseLRCursorColorTimer;
    stepG = ABS_ALT(sPauseLRCursorGreen - sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][1]) /
            sPauseLRCursorColorTimer;
    stepB = ABS_ALT(sPauseLRCursorBlue - sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][2]) /
            sPauseLRCursorColorTimer;
    stepA = ABS_ALT(sPauseLRCursorAlpha - sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][3]) /
            sPauseLRCursorColorTimer;

    if (sPauseLRCursorRed >= sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][0]) {
        sPauseLRCursorRed -= stepR;
    } else {
        sPauseLRCursorRed += stepR;
    }

    if (sPauseLRCursorGreen >= sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][1]) {
        sPauseLRCursorGreen -= stepG;
    } else {
        sPauseLRCursorGreen += stepG;
    }

    if (sPauseLRCursorBlue >= sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][2]) {
        sPauseLRCursorBlue -= stepB;
    } else {
        sPauseLRCursorBlue += stepB;
    }

    if (sPauseLRCursorAlpha >= sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][3]) {
        sPauseLRCursorAlpha -= stepA;
    } else {
        sPauseLRCursorAlpha += stepA;
    }

    sPauseLRCursorColorTimer--;
    if (sPauseLRCursorColorTimer == 0) {
        sPauseLRCursorRed = sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][0];
        sPauseLRCursorGreen = sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][1];
        sPauseLRCursorBlue = sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][2];
        sPauseLRCursorAlpha = sPauseLRCursorColorTargets[sPauseLRCursorColorIndex][3];
        sPauseLRCursorColorTimer = D_8082B924[0];
        sPauseLRCursorColorIndex ^= 1;
    }

    y = pauseCtx->infoPanelOffsetY - 76;
    for (j = 0, i = 0; i < 7; i++, j += 4) {
        pauseCtx->infoPanelVtx[j + 0].v.ob[0] = pauseCtx->infoPanelVtx[j + 2].v.ob[0] = -72;

        pauseCtx->infoPanelVtx[j + 1].v.ob[0] = pauseCtx->infoPanelVtx[j + 3].v.ob[0] = 0;

        pauseCtx->infoPanelVtx[j + 0].v.ob[1] = pauseCtx->infoPanelVtx[j + 1].v.ob[1] = y;

        pauseCtx->infoPanelVtx[j + 2].v.ob[1] = pauseCtx->infoPanelVtx[j + 3].v.ob[1] = y - 24;

        pauseCtx->infoPanelVtx[j + 0].v.ob[2] = pauseCtx->infoPanelVtx[j + 1].v.ob[2] =
            pauseCtx->infoPanelVtx[j + 2].v.ob[2] = pauseCtx->infoPanelVtx[j + 3].v.ob[2] = 0;

        pauseCtx->infoPanelVtx[j + 0].v.flag = pauseCtx->infoPanelVtx[j + 1].v.flag =
            pauseCtx->infoPanelVtx[j + 2].v.flag = pauseCtx->infoPanelVtx[j + 3].v.flag = 0;

        pauseCtx->infoPanelVtx[j + 0].v.tc[0] = pauseCtx->infoPanelVtx[j + 0].v.tc[1] =
            pauseCtx->infoPanelVtx[j + 1].v.tc[1] = pauseCtx->infoPanelVtx[j + 2].v.tc[0] = 0;

        pauseCtx->infoPanelVtx[j + 1].v.tc[0] = pauseCtx->infoPanelVtx[j + 3].v.tc[0] = 72 * (1 << 5);

        pauseCtx->infoPanelVtx[j + 2].v.tc[1] = pauseCtx->infoPanelVtx[j + 3].v.tc[1] = 24 * (1 << 5);

        pauseCtx->infoPanelVtx[j + 0].v.cn[0] = pauseCtx->infoPanelVtx[j + 2].v.cn[0] =
            pauseCtx->infoPanelVtx[j + 0].v.cn[1] = pauseCtx->infoPanelVtx[j + 2].v.cn[1] =
                pauseCtx->infoPanelVtx[j + 0].v.cn[2] = pauseCtx->infoPanelVtx[j + 2].v.cn[2] =
                    pauseCtx->infoPanelVtx[j + 1].v.cn[0] = pauseCtx->infoPanelVtx[j + 3].v.cn[0] =
                        pauseCtx->infoPanelVtx[j + 1].v.cn[1] = pauseCtx->infoPanelVtx[j + 3].v.cn[1] =
                            pauseCtx->infoPanelVtx[j + 1].v.cn[2] = pauseCtx->infoPanelVtx[j + 3].v.cn[2] = 200;

        pauseCtx->infoPanelVtx[j + 0].v.cn[3] = pauseCtx->infoPanelVtx[j + 2].v.cn[3] =
            pauseCtx->infoPanelVtx[j + 1].v.cn[3] = pauseCtx->infoPanelVtx[j + 3].v.cn[3] = pauseCtx->alpha;
    }

    pauseCtx->infoPanelVtx[4].v.ob[0] = pauseCtx->infoPanelVtx[6].v.ob[0] = pauseCtx->infoPanelVtx[0].v.ob[0] + 72;

    pauseCtx->infoPanelVtx[5].v.ob[0] = pauseCtx->infoPanelVtx[7].v.ob[0] = pauseCtx->infoPanelVtx[4].v.ob[0] + 72;

    if ((pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_LEFT) && (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE)) {
        pauseCtx->infoPanelVtx[8].v.ob[0] = pauseCtx->infoPanelVtx[10].v.ob[0] = sPauseCursorLeftX;

        pauseCtx->infoPanelVtx[9].v.ob[0] = pauseCtx->infoPanelVtx[11].v.ob[0] = pauseCtx->infoPanelVtx[8].v.ob[0] + 24;

        pauseCtx->infoPanelVtx[8].v.ob[1] = pauseCtx->infoPanelVtx[9].v.ob[1] = D_8082B920;

        pauseCtx->infoPanelVtx[10].v.ob[1] = pauseCtx->infoPanelVtx[11].v.ob[1] =
            pauseCtx->infoPanelVtx[8].v.ob[1] - 32;
    } else {
        pauseCtx->infoPanelVtx[8].v.ob[0] = pauseCtx->infoPanelVtx[10].v.ob[0] = sPauseCursorLeftX + 3;

        pauseCtx->infoPanelVtx[9].v.ob[0] = pauseCtx->infoPanelVtx[11].v.ob[0] = pauseCtx->infoPanelVtx[8].v.ob[0] + 18;

        pauseCtx->infoPanelVtx[8].v.ob[1] = pauseCtx->infoPanelVtx[9].v.ob[1] = D_8082B920 - 3;

        pauseCtx->infoPanelVtx[10].v.ob[1] = pauseCtx->infoPanelVtx[11].v.ob[1] =
            pauseCtx->infoPanelVtx[8].v.ob[1] - 26;
    }

    if ((pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_RIGHT) && (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE)) {
        pauseCtx->infoPanelVtx[12].v.ob[0] = pauseCtx->infoPanelVtx[14].v.ob[0] = sPauseCursorRightX;

        pauseCtx->infoPanelVtx[13].v.ob[0] = pauseCtx->infoPanelVtx[15].v.ob[0] =
            pauseCtx->infoPanelVtx[12].v.ob[0] + 24;

        pauseCtx->infoPanelVtx[12].v.ob[1] = pauseCtx->infoPanelVtx[13].v.ob[1] = D_8082B920;

        pauseCtx->infoPanelVtx[14].v.ob[1] = pauseCtx->infoPanelVtx[15].v.ob[1] =
            pauseCtx->infoPanelVtx[12].v.ob[1] - 32;
    } else {
        pauseCtx->infoPanelVtx[12].v.ob[0] = pauseCtx->infoPanelVtx[14].v.ob[0] = sPauseCursorRightX + 3;

        pauseCtx->infoPanelVtx[13].v.ob[0] = pauseCtx->infoPanelVtx[15].v.ob[0] =
            pauseCtx->infoPanelVtx[12].v.ob[0] + 18;

        pauseCtx->infoPanelVtx[12].v.ob[1] = pauseCtx->infoPanelVtx[13].v.ob[1] = D_8082B920 - 3;

        pauseCtx->infoPanelVtx[14].v.ob[1] = pauseCtx->infoPanelVtx[15].v.ob[1] =
            pauseCtx->infoPanelVtx[12].v.ob[1] - 26;
    }

    pauseCtx->infoPanelVtx[9].v.tc[0] = pauseCtx->infoPanelVtx[11].v.tc[0] = pauseCtx->infoPanelVtx[13].v.tc[0] =
        pauseCtx->infoPanelVtx[15].v.tc[0] = 24 * (1 << 5);

    pauseCtx->infoPanelVtx[10].v.tc[1] = pauseCtx->infoPanelVtx[11].v.tc[1] = pauseCtx->infoPanelVtx[14].v.tc[1] =
        pauseCtx->infoPanelVtx[15].v.tc[1] = 32 * (1 << 5);

    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    Matrix_Translate(0.0f, 0.0f, -144.0f, MTXMODE_NEW);
    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 150, 140, 90, 255);
    gSPVertex(POLY_OPA_DISP++, &pauseCtx->infoPanelVtx[0], 16, 0);

    gSPDisplayList(POLY_OPA_DISP++, gItemNamePanelDL);

    if (pauseCtx->cursorSpecialPos != 0) {
        j = (pauseCtx->cursorSpecialPos * 4) - 32;
        pauseCtx->cursorVtx[0].v.ob[0] = pauseCtx->infoPanelVtx[j].v.ob[0];
        pauseCtx->cursorVtx[0].v.ob[1] = pauseCtx->infoPanelVtx[j].v.ob[1];
    }

    y = pauseCtx->infoPanelOffsetY - 80;
    pauseCtx->infoPanelVtx[16].v.ob[1] = pauseCtx->infoPanelVtx[17].v.ob[1] = y;

    pauseCtx->infoPanelVtx[18].v.ob[1] = pauseCtx->infoPanelVtx[19].v.ob[1] = pauseCtx->infoPanelVtx[16].v.ob[1] - 16;

    pauseCtx->infoPanelVtx[18].v.tc[1] = pauseCtx->infoPanelVtx[19].v.tc[1] = 16 * (1 << 5);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetEnvColor(POLY_OPA_DISP++, 20, 30, 40, 0);

    if ((pauseCtx->state == PAUSE_STATE_OWLWARP_SELECT) && (pauseCtx->namedItem != PAUSE_ITEM_NONE) &&
        (pauseCtx->nameDisplayTimer < 40)) {
        pauseCtx->infoPanelVtx[16].v.ob[0] = pauseCtx->infoPanelVtx[18].v.ob[0] = -63;

        pauseCtx->infoPanelVtx[17].v.ob[0] = pauseCtx->infoPanelVtx[19].v.ob[0] =
            pauseCtx->infoPanelVtx[16].v.ob[0] + 128;

        pauseCtx->infoPanelVtx[17].v.tc[0] = pauseCtx->infoPanelVtx[19].v.tc[0] = 128 * (1 << 5);

        gSPVertex(POLY_OPA_DISP++, &pauseCtx->infoPanelVtx[16], 4, 0);

        if (pauseCtx->nameColorSet == 1) {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 70, 70, 70, 255);
        } else {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
        }

        POLY_OPA_DISP = Gfx_DrawTexQuad4b(POLY_OPA_DISP, pauseCtx->nameSegment, G_IM_FMT_IA, 128, 16, 0);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void KaleidoScope_UpdateOwlWarpNamePanel(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;
    u16 texIndex;

    if ((pauseCtx->namedItem != pauseCtx->cursorItem[pauseCtx->pageIndex]) ||
        ((pauseCtx->pageIndex == PAUSE_MAP) && (pauseCtx->cursorSpecialPos != 0))) {

        pauseCtx->namedItem = pauseCtx->cursorItem[pauseCtx->pageIndex];
        texIndex = pauseCtx->namedItem;

        osCreateMesgQueue(&pauseCtx->loadQueue, &pauseCtx->loadMsg, 1);

        if (pauseCtx->namedItem != PAUSE_ITEM_NONE) {
            if ((pauseCtx->pageIndex == PAUSE_MAP) && !sInDungeonScene) {
                func_80821900(pauseCtx->nameSegment, texIndex);
            } else {
                func_80821958(pauseCtx->nameSegment, texIndex);
            }
            pauseCtx->nameDisplayTimer = 0;
        }
    } else if (pauseCtx->nameColorSet == 0) {
        if (((pauseCtx->pageIndex == PAUSE_QUEST) && (pauseCtx->cursorSlot[PAUSE_QUEST] >= QUEST_SONG_SONATA) &&
             (pauseCtx->cursorSlot[PAUSE_QUEST] <= QUEST_SONG_SUN) &&
             (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG)) ||
            (pauseCtx->pageIndex == PAUSE_ITEM)) {

            pauseCtx->nameDisplayTimer++;
            if (pauseCtx->nameDisplayTimer > 70) {
                pauseCtx->nameDisplayTimer = 0;
            }
        } else {
            pauseCtx->nameDisplayTimer = 0;
        }
    } else {
        pauseCtx->nameDisplayTimer = 0;
    }
}

void KaleidoScope_UpdateSwitchPage(PlayState* play, Input* input) {
    PauseContext* pauseCtx = &play->pauseCtx;

    if (1) {
        pauseCtx->eye.x += sPageSwitchEyeDx[pauseCtx->nextPageMode] * 2.0f;
        pauseCtx->eye.z += sPageSwitchEyeDz[pauseCtx->nextPageMode] * 2.0f;

        if (pauseCtx->switchPageTimer < 32) {
            sPauseCursorLeftX -= (s16)(sPauseCursorLeftMoveOffsetX / 4);
            sPauseCursorRightX -= (s16)(sPauseCursorRightMoveOffsetX / 4);
        } else {
            sPauseCursorLeftX += (s16)(sPauseCursorLeftMoveOffsetX / 4);
            sPauseCursorRightX += (s16)(sPauseCursorRightMoveOffsetX / 4);
        }

        pauseCtx->switchPageTimer += 8;

        if (pauseCtx->switchPageTimer == 64) {
            pauseCtx->switchPageTimer = 0;
            pauseCtx->pageIndex = sPageSwitchNextPageIndex[pauseCtx->nextPageMode];
            pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;

            KaleidoScope_HandlePageToggles(play, input);
        }
    }
}

void KaleidoScope_SetView(PauseContext* pauseCtx, f32 eyeX, f32 eyeY, f32 eyeZ) {
    Vec3f eye;
    Vec3f at;
    Vec3f up;

    eye.x = eyeX;
    eye.y = eyeY;
    eye.z = eyeZ;
    at.x = at.y = at.z = 0.0f;
    up.x = up.z = 0.0f;
    up.y = 1.0f;

    View_LookAt(&pauseCtx->view, &eye, &at, &up);
    View_Apply(&pauseCtx->view,
               VIEW_ALL | VIEW_FORCE_VIEWING | VIEW_FORCE_VIEWPORT | VIEW_FORCE_PROJECTION_PERSPECTIVE);
}

s16 D_8082B9E8[] = { 0, 0 };
s16 D_8082B9EC[] = { 0, 0 };
s16 D_8082B9F0[] = { -21, -104, -76, -48, -104, -40 };
s16 D_8082B9FC[] = { 0, 0 };
s16 D_8082BA00[] = {
    -41, 9, 43, -21, -37, 43, -69, -69, -32, -109, -45, -109, -45, 59,  -5, -70, -52, -11,
    -2,  8, 2,  1,   43,  52, 54,  62,  -80, -64,  -9,  -3,   -7,  -16, -1, 23,  44,  54,
};
s16 D_8082BA48[] = {
    -76, -58, 10, -58, 10, 0,
};
s16 D_8082BA54[] = { 0, 0 };
s16 D_8082BA58[] = { 0, 0 };
s16 D_8082BA5C[] = {
    128, 24, 24, 24, 32, 24,
};
s16 D_8082BA68[] = { 0, 0 };
s16 D_8082BA6C[] = {
    152, 48, 48, 48, 48, 0,
};
s16 D_8082BA78[] = { 0, 0 };
s16 D_8082BA7C[] = { 0, 0 };

s16 D_8082BA80[] = {
    54, -42, -42, -42, -24, 50,
};
s16 D_8082BA8C[] = { 0, 0 };
s16 D_8082BA90[] = {
    11,  22,  -16, -16, -16, 59, 24, 59, -11, -5,  -5, 59, 59, 39, 31,  -10, -36, -19,
    -53, -27, -2,  41,  11,  -3, 45, 18, -8,  -38, 39, 26, 1,  -7, -28, -27, -1,  24,
};
s16 D_8082BAD8[] = {
    36, 10, 10, -6, -6, 0,
};
s16 D_8082BAE4[] = { 0, 0 };
s16 D_8082BAE8[] = { 0, 0 };
s16 D_8082BAEC[] = {
    16, 24, 24, 24, 24, 24,
};
s16 D_8082BAF8[] = { 0, 0 };
s16 D_8082BAFC[] = {
    16, 48, 48, 16, 16, 0,
};
s16* D_8082BB08[] = {
    D_8082B9E8, D_8082B9EC, D_8082B9F0, D_8082B9FC, D_8082BA00, D_8082BA48,
};

s16* D_8082BB20[] = {
    D_8082BA54, D_8082BA58, D_8082BA5C, D_8082BA68, D_8082B7F0, D_8082BA6C,
};

s16* D_8082BB38[] = {
    D_8082BA78, D_8082BA7C, D_8082BA80, D_8082BA8C, D_8082BA90, D_8082BAD8,
};

s16* D_8082BB50[] = {
    D_8082BAE4, D_8082BAE8, D_8082BAEC, D_8082BAF8, D_8082B838, D_8082BAFC,
};
s16 D_8082BB68[] = {
    14, -2, -2, -18, -18, 0,
};
s16 func_80825A50(PlayState* play, Vtx* vtx, s16 arg2, s16 arg3) {
    PauseContext* pauseCtx = &play->pauseCtx;
    GameOverContext* gameOverCtx = &play->gameOverCtx;
    s16* ptr1;
    s16* ptr2;
    s16* ptr3;
    s16* ptr4;
    s16 var_a2;
    s16 var_t3;
    s16 i;
    s16 j;
    s16 k;

    var_t3 = -200;

    for (k = 0, i = 0; i < 3; i++) {
        var_t3 += 80;

        for (var_a2 = 80, j = 0; j < 5; j++, k += 4, var_a2 -= 32) {
            vtx[k + 0].v.ob[0] = vtx[k + 2].v.ob[0] = var_t3;
            vtx[k + 1].v.ob[0] = vtx[k + 3].v.ob[0] = vtx[k + 0].v.ob[0] + 80;

            vtx[k + 0].v.ob[1] = vtx[k + 1].v.ob[1] = var_a2 + pauseCtx->offsetY;
            vtx[k + 2].v.ob[1] = vtx[k + 3].v.ob[1] = vtx[k + 0].v.ob[1] - 32;

            vtx[k + 0].v.ob[2] = vtx[k + 1].v.ob[2] = vtx[k + 2].v.ob[2] = vtx[k + 3].v.ob[2] = 0;

            vtx[k + 0].v.flag = vtx[k + 1].v.flag = vtx[k + 2].v.flag = vtx[k + 3].v.flag = 0;

            vtx[k + 0].v.tc[0] = vtx[k + 0].v.tc[1] = 0;
            vtx[k + 1].v.tc[1] = vtx[k + 2].v.tc[0] = 0;
            vtx[k + 1].v.tc[0] = vtx[k + 3].v.tc[0] = 80 * (1 << 5);
            vtx[k + 2].v.tc[1] = vtx[k + 3].v.tc[1] = 32 * (1 << 5);

            vtx[k + 0].v.cn[0] = vtx[k + 2].v.cn[0] = vtx[k + 0].v.cn[1] = vtx[k + 2].v.cn[1] = vtx[k + 0].v.cn[2] =
                vtx[k + 2].v.cn[2] = 0;

            vtx[k + 1].v.cn[0] = vtx[k + 3].v.cn[0] = vtx[k + 1].v.cn[1] = vtx[k + 3].v.cn[1] = vtx[k + 1].v.cn[2] =
                vtx[k + 3].v.cn[2] = 0;

            vtx[k + 0].v.cn[3] = vtx[k + 2].v.cn[3] = vtx[k + 1].v.cn[3] = vtx[k + 3].v.cn[3] = pauseCtx->alpha;
        }
    }

    if (arg3 != 0) {
        ptr1 = D_8082BB08[arg2];
        ptr2 = D_8082BB20[arg2];
        ptr3 = D_8082BB38[arg2];
        ptr4 = D_8082BB50[arg2];

        for (i = 0; i < arg3; i++, k += 4) {
            vtx[k + 2].v.ob[0] = vtx[k + 0].v.ob[0] = ptr1[i];

            vtx[k + 1].v.ob[0] = vtx[k + 3].v.ob[0] = vtx[k + 0].v.ob[0] + ptr2[i];

            if (!IS_PAUSE_STATE_GAMEOVER) {
                vtx[k + 0].v.ob[1] = vtx[k + 1].v.ob[1] = ptr3[i] + pauseCtx->offsetY;
            } else if (gameOverCtx->state == GAMEOVER_INACTIVE) {
                vtx[k + 0].v.ob[1] = vtx[k + 1].v.ob[1] = ptr3[i] + pauseCtx->offsetY;
            } else {
                vtx[k + 0].v.ob[1] = vtx[k + 1].v.ob[1] = D_8082BB68[i] + pauseCtx->offsetY;
            }

            vtx[k + 2].v.ob[1] = vtx[k + 3].v.ob[1] = vtx[k + 0].v.ob[1] - ptr4[i];

            vtx[k + 0].v.ob[2] = vtx[k + 1].v.ob[2] = vtx[k + 2].v.ob[2] = vtx[k + 3].v.ob[2] = 0;

            vtx[k + 0].v.flag = vtx[k + 1].v.flag = vtx[k + 2].v.flag = vtx[k + 3].v.flag = 0;

            vtx[k + 0].v.tc[0] = vtx[k + 0].v.tc[1] = vtx[k + 1].v.tc[1] = vtx[k + 2].v.tc[0] = 0;
            vtx[k + 1].v.tc[0] = vtx[k + 3].v.tc[0] = ptr2[i] << 5;
            vtx[k + 2].v.tc[1] = vtx[k + 3].v.tc[1] = ptr4[i] << 5;

            vtx[k + 0].v.cn[0] = vtx[k + 2].v.cn[0] = vtx[k + 0].v.cn[1] = vtx[k + 2].v.cn[1] = vtx[k + 0].v.cn[2] =
                vtx[k + 2].v.cn[2] = 255;

            vtx[k + 1].v.cn[0] = vtx[k + 3].v.cn[0] = vtx[k + 1].v.cn[1] = vtx[k + 3].v.cn[1] = vtx[k + 1].v.cn[2] =
                vtx[k + 3].v.cn[2] = 255;

            vtx[k + 0].v.cn[3] = vtx[k + 2].v.cn[3] = vtx[k + 1].v.cn[3] = vtx[k + 3].v.cn[3] = pauseCtx->alpha;
        }
    }
    return k;
}

s16 sQuestVtxRectLeft[] = {
    45,   // QUEST_REMAINS_ODOLWA
    78,   // QUEST_REMAINS_GOHT
    10,   // QUEST_REMAINS_GYORG
    45,   // QUEST_REMAINS_TWINMOLD
    80,   // QUEST_SHIELD
    11,   // QUEST_SWORD
    -109, // QUEST_SONG_SONATA
    -87,  // QUEST_SONG_LULLABY
    -65,  // QUEST_SONG_BOSSA_NOVA
    -41,  // QUEST_SONG_ELEGY
    -19,  // QUEST_SONG_OATH
    -18,  // QUEST_SONG_SARIA
    -109, // QUEST_SONG_TIME
    -87,  // QUEST_SONG_HEALING
    -65,  // QUEST_SONG_EPONA
    -41,  // QUEST_SONG_SOARING
    -19,  // QUEST_SONG_STORMS
    -18,  // QUEST_SONG_SUN
    -103, // QUEST_BOMBERS_NOTEBOOK
    7,    // QUEST_QUIVER
    82,   // QUEST_BOMB_BAG
    -110, // QUEST_SKULL_TOKEN (unused)
    -54,  // QUEST_HEART_PIECE
    -98,  // ocarina song button index 0
    -86,  // ocarina song button index 1
    -74,  // ocarina song button index 2
    -62,  // ocarina song button index 3
    -50,  // ocarina song button index 4
    -38,  // ocarina song button index 5
    -26,  // ocarina song button index 6
    -14,  // ocarina song button index 7
    -98,  // ocarina input button index 0
    -86,  // ocarina input button index 1
    -74,  // ocarina input button index 2
    -62,  // ocarina input button index 3
    -50,  // ocarina input button index 4
    -38,  // ocarina input button index 5
    -26,  // ocarina input button index 6
    -14,  // ocarina input button index 7
};

s16 sQuestVtxRectTop[] = {
    62,  // QUEST_REMAINS_ODOLWA
    42,  // QUEST_REMAINS_GOHT
    42,  // QUEST_REMAINS_GYORG
    20,  // QUEST_REMAINS_TWINMOLD
    -9,  // QUEST_SHIELD
    -9,  // QUEST_SWORD
    -20, // QUEST_SONG_SONATA
    -20, // QUEST_SONG_LULLABY
    -20, // QUEST_SONG_BOSSA_NOVA
    -20, // QUEST_SONG_ELEGY
    -20, // QUEST_SONG_OATH
    -20, // QUEST_SONG_SARIA
    2,   // QUEST_SONG_TIME
    2,   // QUEST_SONG_HEALING
    2,   // QUEST_SONG_EPONA
    2,   // QUEST_SONG_SOARING
    2,   // QUEST_SONG_STORMS
    2,   // QUEST_SONG_SUN
    54,  // QUEST_BOMBERS_NOTEBOOK
    -44, // QUEST_QUIVER
    -44, // QUEST_BOMB_BAG
    34,  // QUEST_SKULL_TOKEN (unused)
    58,  // QUEST_HEART_PIECE
    -52, // ocarina song button index 0
    -52, // ocarina song button index 1
    -52, // ocarina song button index 2
    -52, // ocarina song button index 3
    -52, // ocarina song button index 4
    -52, // ocarina song button index 5
    -52, // ocarina song button index 6
    -52, // ocarina song button index 7
    -52, // ocarina input button index 0
    -52, // ocarina input button index 1
    -52, // ocarina input button index 2
    -52, // ocarina input button index 3
    -52, // ocarina input button index 4
    -52, // ocarina input button index 5
    -52, // ocarina input button index 6
    -52, // ocarina input button index 7
};

s16 sQuestVtxWidths[] = {
    32, // QUEST_REMAINS_ODOLWA
    32, // QUEST_REMAINS_GOHT
    32, // QUEST_REMAINS_GYORG
    32, // QUEST_REMAINS_TWINMOLD
    32, // QUEST_SHIELD
    32, // QUEST_SWORD
    16, // QUEST_SONG_SONATA
    16, // QUEST_SONG_LULLABY
    16, // QUEST_SONG_BOSSA_NOVA
    16, // QUEST_SONG_ELEGY
    16, // QUEST_SONG_OATH
    16, // QUEST_SONG_SARIA
    16, // QUEST_SONG_TIME
    16, // QUEST_SONG_HEALING
    16, // QUEST_SONG_EPONA
    16, // QUEST_SONG_SOARING
    16, // QUEST_SONG_STORMS
    16, // QUEST_SONG_SUN
    32, // QUEST_BOMBERS_NOTEBOOK
    32, // QUEST_QUIVER
    32, // QUEST_BOMB_BAG
    24, // QUEST_SKULL_TOKEN (unused)
    48, // QUEST_HEART_PIECE
    16, // ocarina song button index 0
    16, // ocarina song button index 1
    16, // ocarina song button index 2
    16, // ocarina song button index 3
    16, // ocarina song button index 4
    16, // ocarina song button index 5
    16, // ocarina song button index 6
    16, // ocarina song button index 7
    16, // ocarina input button index 0
    16, // ocarina input button index 1
    16, // ocarina input button index 2
    16, // ocarina input button index 3
    16, // ocarina input button index 4
    16, // ocarina input button index 5
    16, // ocarina input button index 6
    16, // ocarina input button index 7
};

s16 sQuestVtxHeights[] = {
    32, // QUEST_REMAINS_ODOLWA
    32, // QUEST_REMAINS_GOHT
    32, // QUEST_REMAINS_GYORG
    32, // QUEST_REMAINS_TWINMOLD
    32, // QUEST_SHIELD
    32, // QUEST_SWORD
    24, // QUEST_SONG_SONATA
    24, // QUEST_SONG_LULLABY
    24, // QUEST_SONG_BOSSA_NOVA
    24, // QUEST_SONG_ELEGY
    24, // QUEST_SONG_OATH
    24, // QUEST_SONG_SARIA
    24, // QUEST_SONG_TIME
    24, // QUEST_SONG_HEALING
    24, // QUEST_SONG_EPONA
    24, // QUEST_SONG_SOARING
    24, // QUEST_SONG_STORMS
    24, // QUEST_SONG_SUN
    32, // QUEST_BOMBERS_NOTEBOOK
    32, // QUEST_QUIVER
    32, // QUEST_BOMB_BAG
    24, // QUEST_SKULL_TOKEN (unused)
    48, // QUEST_HEART_PIECE
    16, // ocarina song button index 0
    16, // ocarina song button index 1
    16, // ocarina song button index 2
    16, // ocarina song button index 3
    16, // ocarina song button index 4
    16, // ocarina song button index 5
    16, // ocarina song button index 6
    16, // ocarina song button index 7
    16, // ocarina input button index 0
    16, // ocarina input button index 1
    16, // ocarina input button index 2
    16, // ocarina input button index 3
    16, // ocarina input button index 4
    16, // ocarina input button index 5
    16, // ocarina input button index 6
    16, // ocarina input button index 7
};

void KaleidoScope_InitVertices(PlayState* play, GraphicsContext* gfxCtx) {
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 i;
    s16 j;
    s16 k;
    s16 var_a3;
    s16 var_t3;

    pauseCtx->offsetY = 0;

    if ((pauseCtx->state == PAUSE_STATE_OPENING_3) || (pauseCtx->state == PAUSE_STATE_OWLWARP_3) ||
        (pauseCtx->state >= PAUSE_STATE_OWLWARP_6) ||
        ((pauseCtx->state == PAUSE_STATE_SAVEPROMPT) && ((pauseCtx->savePromptState == PAUSE_SAVEPROMPT_STATE_3) ||
                                                         (pauseCtx->savePromptState == PAUSE_SAVEPROMPT_STATE_7)))) {
        pauseCtx->offsetY = 80;
    }

    if (pauseCtx->pageIndex != PAUSE_QUEST) {
        pauseCtx->itemPageVtx = GRAPH_ALLOC(gfxCtx, 60 * sizeof(Vtx));
        func_80825A50(play, pauseCtx->itemPageVtx, 1, 0);

        pauseCtx->itemVtx = GRAPH_ALLOC(gfxCtx, 108 * sizeof(Vtx));

        for (k = 0, i = 0, var_t3 = 58; k < 4; k++, var_t3 -= 32) {
            for (var_a3 = -96, j = 0; j < 6; j++, i += 4, var_a3 += 32) {
                pauseCtx->itemVtx[i + 0].v.ob[0] = pauseCtx->itemVtx[i + 2].v.ob[0] = var_a3 + 2;
                pauseCtx->itemVtx[i + 1].v.ob[0] = pauseCtx->itemVtx[i + 3].v.ob[0] =
                    pauseCtx->itemVtx[i + 0].v.ob[0] + 28;

                pauseCtx->itemVtx[i + 0].v.ob[1] = pauseCtx->itemVtx[i + 1].v.ob[1] = var_t3 + pauseCtx->offsetY - 2;
                pauseCtx->itemVtx[i + 2].v.ob[1] = pauseCtx->itemVtx[i + 3].v.ob[1] =
                    pauseCtx->itemVtx[i + 0].v.ob[1] - 28;

                pauseCtx->itemVtx[i + 0].v.ob[2] = pauseCtx->itemVtx[i + 1].v.ob[2] = pauseCtx->itemVtx[i + 2].v.ob[2] =
                    pauseCtx->itemVtx[i + 3].v.ob[2] = 0;

                pauseCtx->itemVtx[i + 0].v.flag = pauseCtx->itemVtx[i + 1].v.flag = pauseCtx->itemVtx[i + 2].v.flag =
                    pauseCtx->itemVtx[i + 3].v.flag = 0;

                pauseCtx->itemVtx[i + 0].v.tc[0] = pauseCtx->itemVtx[i + 0].v.tc[1] = pauseCtx->itemVtx[i + 1].v.tc[1] =
                    pauseCtx->itemVtx[i + 2].v.tc[0] = 0;

                pauseCtx->itemVtx[i + 1].v.tc[0] = pauseCtx->itemVtx[i + 2].v.tc[1] = pauseCtx->itemVtx[i + 3].v.tc[0] =
                    pauseCtx->itemVtx[i + 3].v.tc[1] = 32 * (1 << 5);

                pauseCtx->itemVtx[i + 0].v.cn[0] = pauseCtx->itemVtx[i + 1].v.cn[0] = pauseCtx->itemVtx[i + 2].v.cn[0] =
                    pauseCtx->itemVtx[i + 3].v.cn[0] = pauseCtx->itemVtx[i + 0].v.cn[1] =
                        pauseCtx->itemVtx[i + 1].v.cn[1] = pauseCtx->itemVtx[i + 2].v.cn[1] =
                            pauseCtx->itemVtx[i + 3].v.cn[1] = pauseCtx->itemVtx[i + 0].v.cn[2] =
                                pauseCtx->itemVtx[i + 1].v.cn[2] = pauseCtx->itemVtx[i + 2].v.cn[2] =
                                    pauseCtx->itemVtx[i + 3].v.cn[2] = 255;

                pauseCtx->itemVtx[i + 0].v.cn[3] = pauseCtx->itemVtx[i + 1].v.cn[3] = pauseCtx->itemVtx[i + 2].v.cn[3] =
                    pauseCtx->itemVtx[i + 3].v.cn[3] = 255;
            }
        }

        for (j = 1; j < 4; j++, i += 4) {
            if (GET_CUR_FORM_BTN_SLOT(j) != ITEM_NONE) {
                k = GET_CUR_FORM_BTN_SLOT(j) << 2;

                pauseCtx->itemVtx[i + 0].v.ob[0] = pauseCtx->itemVtx[i + 2].v.ob[0] = pauseCtx->itemVtx[k].v.ob[0] - 2;

                pauseCtx->itemVtx[i + 1].v.ob[0] = pauseCtx->itemVtx[i + 3].v.ob[0] =
                    pauseCtx->itemVtx[i + 0].v.ob[0] + 32;

                pauseCtx->itemVtx[i + 0].v.ob[1] = pauseCtx->itemVtx[i + 1].v.ob[1] = pauseCtx->itemVtx[k].v.ob[1] + 2;

                pauseCtx->itemVtx[i + 2].v.ob[1] = pauseCtx->itemVtx[i + 3].v.ob[1] =
                    pauseCtx->itemVtx[i + 0].v.ob[1] - 32;

                pauseCtx->itemVtx[i + 0].v.ob[2] = pauseCtx->itemVtx[i + 1].v.ob[2] = pauseCtx->itemVtx[i + 2].v.ob[2] =
                    pauseCtx->itemVtx[i + 3].v.ob[2] = 0;

                pauseCtx->itemVtx[i + 0].v.flag = pauseCtx->itemVtx[i + 1].v.flag = pauseCtx->itemVtx[i + 2].v.flag =
                    pauseCtx->itemVtx[i + 3].v.flag = 0;

                pauseCtx->itemVtx[i + 0].v.tc[0] = pauseCtx->itemVtx[i + 0].v.tc[1] = pauseCtx->itemVtx[i + 1].v.tc[1] =
                    pauseCtx->itemVtx[i + 2].v.tc[0] = 0;

                pauseCtx->itemVtx[i + 1].v.tc[0] = pauseCtx->itemVtx[i + 2].v.tc[1] = pauseCtx->itemVtx[i + 3].v.tc[0] =
                    pauseCtx->itemVtx[i + 3].v.tc[1] = 32 * (1 << 5);

                pauseCtx->itemVtx[i + 0].v.cn[0] = pauseCtx->itemVtx[i + 1].v.cn[0] = pauseCtx->itemVtx[i + 2].v.cn[0] =
                    pauseCtx->itemVtx[i + 3].v.cn[0] = pauseCtx->itemVtx[i + 0].v.cn[1] =
                        pauseCtx->itemVtx[i + 1].v.cn[1] = pauseCtx->itemVtx[i + 2].v.cn[1] =
                            pauseCtx->itemVtx[i + 3].v.cn[1] = pauseCtx->itemVtx[i + 0].v.cn[2] =
                                pauseCtx->itemVtx[i + 1].v.cn[2] = pauseCtx->itemVtx[i + 2].v.cn[2] =
                                    pauseCtx->itemVtx[i + 3].v.cn[2] = 255;

                pauseCtx->itemVtx[i + 0].v.cn[3] = pauseCtx->itemVtx[i + 1].v.cn[3] = pauseCtx->itemVtx[i + 2].v.cn[3] =
                    pauseCtx->itemVtx[i + 3].v.cn[3] = pauseCtx->alpha;
            } else {
                pauseCtx->itemVtx[i + 2].v.ob[0] = -300;
                pauseCtx->itemVtx[i + 0].v.ob[0] = pauseCtx->itemVtx[i + 2].v.ob[0];

                pauseCtx->itemVtx[i + 1].v.ob[0] = pauseCtx->itemVtx[i + 3].v.ob[0] =
                    pauseCtx->itemVtx[i + 0].v.ob[0] + 32;

                pauseCtx->itemVtx[i + 0].v.ob[1] = pauseCtx->itemVtx[i + 1].v.ob[1] = 300;
                pauseCtx->itemVtx[i + 2].v.ob[1] = pauseCtx->itemVtx[i + 3].v.ob[1] =
                    pauseCtx->itemVtx[i + 0].v.ob[1] - 32;
            }
        }
    }

    if (pauseCtx->pageIndex != PAUSE_MASK) {
        if (!sInDungeonScene) {
            pauseCtx->mapPageVtx = GRAPH_ALLOC(gfxCtx, 264 * sizeof(Vtx));
            j = func_80825A50(play, pauseCtx->mapPageVtx, 4, 36);

            for (i = 0, var_t3 = 59; i < 15; i++, j += 4, var_t3 -= 9) {
                pauseCtx->mapPageVtx[j + 2].v.ob[0] = -109;
                pauseCtx->mapPageVtx[j + 0].v.ob[0] = pauseCtx->mapPageVtx[j + 2].v.ob[0];

                pauseCtx->mapPageVtx[j + 1].v.ob[0] = pauseCtx->mapPageVtx[j + 3].v.ob[0] =
                    pauseCtx->mapPageVtx[j + 0].v.ob[0] + 216;

                pauseCtx->mapPageVtx[j + 0].v.ob[1] = pauseCtx->mapPageVtx[j + 1].v.ob[1] = var_t3 + pauseCtx->offsetY;

                pauseCtx->mapPageVtx[j + 2].v.ob[1] = pauseCtx->mapPageVtx[j + 3].v.ob[1] =
                    pauseCtx->mapPageVtx[j + 0].v.ob[1] - 9;

                pauseCtx->mapPageVtx[j + 0].v.ob[2] = pauseCtx->mapPageVtx[j + 1].v.ob[2] =
                    pauseCtx->mapPageVtx[j + 2].v.ob[2] = pauseCtx->mapPageVtx[j + 3].v.ob[2] = 0;

                pauseCtx->mapPageVtx[j + 0].v.flag = pauseCtx->mapPageVtx[j + 1].v.flag =
                    pauseCtx->mapPageVtx[j + 2].v.flag = pauseCtx->mapPageVtx[j + 3].v.flag = 0;

                pauseCtx->mapPageVtx[j + 0].v.tc[0] = pauseCtx->mapPageVtx[j + 0].v.tc[1] =
                    pauseCtx->mapPageVtx[j + 1].v.tc[1] = pauseCtx->mapPageVtx[j + 2].v.tc[0] = 0;

                pauseCtx->mapPageVtx[j + 1].v.tc[0] = pauseCtx->mapPageVtx[j + 3].v.tc[0] = 216 * (1 << 5);
                pauseCtx->mapPageVtx[j + 2].v.tc[1] = pauseCtx->mapPageVtx[j + 3].v.tc[1] = 9 * (1 << 5);

                pauseCtx->mapPageVtx[j + 0].v.cn[0] = pauseCtx->mapPageVtx[j + 2].v.cn[0] =
                    pauseCtx->mapPageVtx[j + 0].v.cn[1] = pauseCtx->mapPageVtx[j + 2].v.cn[1] =
                        pauseCtx->mapPageVtx[j + 0].v.cn[2] = pauseCtx->mapPageVtx[j + 2].v.cn[2] =
                            pauseCtx->mapPageVtx[j + 1].v.cn[0] = pauseCtx->mapPageVtx[j + 3].v.cn[0] =
                                pauseCtx->mapPageVtx[j + 1].v.cn[1] = pauseCtx->mapPageVtx[j + 3].v.cn[1] =
                                    pauseCtx->mapPageVtx[j + 1].v.cn[2] = pauseCtx->mapPageVtx[j + 3].v.cn[2] =
                                        pauseCtx->mapPageVtx[j + 0].v.cn[3] = pauseCtx->mapPageVtx[j + 2].v.cn[3] =
                                            pauseCtx->mapPageVtx[j + 1].v.cn[3] = pauseCtx->mapPageVtx[j + 3].v.cn[3] =
                                                pauseCtx->alpha;
            }

            pauseCtx->mapPageVtx[j - 2].v.ob[1] = pauseCtx->mapPageVtx[j - 1].v.ob[1] =
                pauseCtx->mapPageVtx[j - 4].v.ob[1] - 2;

            pauseCtx->mapPageVtx[j - 2].v.tc[1] = pauseCtx->mapPageVtx[j - 1].v.tc[1] = 2 * (1 << 5);

        } else {
            pauseCtx->mapPageVtx = GRAPH_ALLOC(gfxCtx, 84 * sizeof(Vtx));
            func_80825A50(play, pauseCtx->mapPageVtx, 2, 6);
        }
    }

    if (pauseCtx->pageIndex != PAUSE_ITEM) {
        pauseCtx->questPageVtx = GRAPH_ALLOC(gfxCtx, 60 * sizeof(Vtx));
        func_80825A50(play, pauseCtx->questPageVtx, 3, 0);

        pauseCtx->questVtx = GRAPH_ALLOC(gfxCtx, 156 * sizeof(Vtx));

        for (k = 0, j = 0; j < 39; j++, k += 4) {
            if (j <= QUEST_SWORD) {
                pauseCtx->questVtx[k + 0].v.ob[0] = pauseCtx->questVtx[k + 2].v.ob[0] = sQuestVtxRectLeft[j];

                pauseCtx->questVtx[k + 1].v.ob[0] = pauseCtx->questVtx[k + 3].v.ob[0] =
                    pauseCtx->questVtx[k + 0].v.ob[0] + sQuestVtxWidths[j];

                pauseCtx->questVtx[k + 0].v.ob[1] = pauseCtx->questVtx[k + 1].v.ob[1] =
                    sQuestVtxRectTop[j] + pauseCtx->offsetY;

                pauseCtx->questVtx[k + 2].v.ob[1] = pauseCtx->questVtx[k + 3].v.ob[1] =
                    pauseCtx->questVtx[k + 0].v.ob[1] - sQuestVtxHeights[j];
            } else {
                pauseCtx->questVtx[k + 0].v.ob[0] = pauseCtx->questVtx[k + 2].v.ob[0] = sQuestVtxRectLeft[j] + 2;

                pauseCtx->questVtx[k + 1].v.ob[0] = pauseCtx->questVtx[k + 3].v.ob[0] =
                    pauseCtx->questVtx[k + 0].v.ob[0] + sQuestVtxWidths[j] - 4;

                pauseCtx->questVtx[k + 0].v.ob[1] = pauseCtx->questVtx[k + 1].v.ob[1] =
                    sQuestVtxRectTop[j] + pauseCtx->offsetY - 2;

                pauseCtx->questVtx[k + 2].v.ob[1] = pauseCtx->questVtx[k + 3].v.ob[1] =
                    pauseCtx->questVtx[k + 0].v.ob[1] - sQuestVtxHeights[j] + 4;
            }

            pauseCtx->questVtx[k + 0].v.ob[2] = pauseCtx->questVtx[k + 1].v.ob[2] = pauseCtx->questVtx[k + 2].v.ob[2] =
                pauseCtx->questVtx[k + 3].v.ob[2] = 0;

            pauseCtx->questVtx[k + 0].v.flag = pauseCtx->questVtx[k + 1].v.flag = pauseCtx->questVtx[k + 2].v.flag =
                pauseCtx->questVtx[k + 3].v.flag = 0;

            pauseCtx->questVtx[k + 0].v.tc[0] = pauseCtx->questVtx[k + 0].v.tc[1] = pauseCtx->questVtx[k + 1].v.tc[1] =
                pauseCtx->questVtx[k + 2].v.tc[0] = 0;

            pauseCtx->questVtx[k + 1].v.tc[0] = pauseCtx->questVtx[k + 3].v.tc[0] = sQuestVtxWidths[j] << 5;
            pauseCtx->questVtx[k + 2].v.tc[1] = pauseCtx->questVtx[k + 3].v.tc[1] = sQuestVtxHeights[j] << 5;

            pauseCtx->questVtx[k + 0].v.cn[0] = pauseCtx->questVtx[k + 1].v.cn[0] = pauseCtx->questVtx[k + 2].v.cn[0] =
                pauseCtx->questVtx[k + 3].v.cn[0] = pauseCtx->questVtx[k + 0].v.cn[1] =
                    pauseCtx->questVtx[k + 1].v.cn[1] = pauseCtx->questVtx[k + 2].v.cn[1] =
                        pauseCtx->questVtx[k + 3].v.cn[1] = pauseCtx->questVtx[k + 0].v.cn[2] =
                            pauseCtx->questVtx[k + 1].v.cn[2] = pauseCtx->questVtx[k + 2].v.cn[2] =
                                pauseCtx->questVtx[k + 3].v.cn[2] = 255;

            pauseCtx->questVtx[k + 0].v.cn[3] = pauseCtx->questVtx[k + 1].v.cn[3] = pauseCtx->questVtx[k + 2].v.cn[3] =
                pauseCtx->questVtx[k + 3].v.cn[3] = pauseCtx->alpha;
        }
    }

    if (pauseCtx->pageIndex != PAUSE_MAP) {
        pauseCtx->maskPageVtx = GRAPH_ALLOC(gfxCtx, 60 * sizeof(Vtx));
        func_80825A50(play, pauseCtx->maskPageVtx, 0, 0);

        pauseCtx->maskVtx = GRAPH_ALLOC(gfxCtx, 108 * sizeof(Vtx));

        for (k = 0, i = 0, var_t3 = 58; k < 4; k++, var_t3 -= 32) {
            for (var_a3 = -96, j = 0; j < 6; j++, i += 4, var_a3 += 32) {
                pauseCtx->maskVtx[i + 0].v.ob[0] = pauseCtx->maskVtx[i + 2].v.ob[0] = var_a3 + 2;
                pauseCtx->maskVtx[i + 1].v.ob[0] = pauseCtx->maskVtx[i + 3].v.ob[0] =
                    pauseCtx->maskVtx[i + 0].v.ob[0] + 28;

                pauseCtx->maskVtx[i + 0].v.ob[1] = pauseCtx->maskVtx[i + 1].v.ob[1] = var_t3 + pauseCtx->offsetY - 2;
                pauseCtx->maskVtx[i + 2].v.ob[1] = pauseCtx->maskVtx[i + 3].v.ob[1] =
                    pauseCtx->maskVtx[i + 0].v.ob[1] - 28;

                pauseCtx->maskVtx[i + 0].v.ob[2] = pauseCtx->maskVtx[i + 1].v.ob[2] = pauseCtx->maskVtx[i + 2].v.ob[2] =
                    pauseCtx->maskVtx[i + 3].v.ob[2] = 0;

                pauseCtx->maskVtx[i + 0].v.flag = pauseCtx->maskVtx[i + 1].v.flag = pauseCtx->maskVtx[i + 2].v.flag =
                    pauseCtx->maskVtx[i + 3].v.flag = 0;

                pauseCtx->maskVtx[i + 0].v.tc[0] = pauseCtx->maskVtx[i + 0].v.tc[1] = pauseCtx->maskVtx[i + 1].v.tc[1] =
                    pauseCtx->maskVtx[i + 2].v.tc[0] = 0;

                pauseCtx->maskVtx[i + 1].v.tc[0] = pauseCtx->maskVtx[i + 2].v.tc[1] = pauseCtx->maskVtx[i + 3].v.tc[0] =
                    pauseCtx->maskVtx[i + 3].v.tc[1] = 32 * (1 << 5);

                pauseCtx->maskVtx[i + 0].v.cn[0] = pauseCtx->maskVtx[i + 1].v.cn[0] = pauseCtx->maskVtx[i + 2].v.cn[0] =
                    pauseCtx->maskVtx[i + 3].v.cn[0] = pauseCtx->maskVtx[i + 0].v.cn[1] =
                        pauseCtx->maskVtx[i + 1].v.cn[1] = pauseCtx->maskVtx[i + 2].v.cn[1] =
                            pauseCtx->maskVtx[i + 3].v.cn[1] = pauseCtx->maskVtx[i + 0].v.cn[2] =
                                pauseCtx->maskVtx[i + 1].v.cn[2] = pauseCtx->maskVtx[i + 2].v.cn[2] =
                                    pauseCtx->maskVtx[i + 3].v.cn[2] = 255;

                pauseCtx->maskVtx[i + 0].v.cn[3] = pauseCtx->maskVtx[i + 1].v.cn[3] = pauseCtx->maskVtx[i + 2].v.cn[3] =
                    pauseCtx->maskVtx[i + 3].v.cn[3] = 255;
            }
        }

        for (j = 1; j < 4; j++, i += 4) {
            if (GET_CUR_FORM_BTN_SLOT(j) != ITEM_NONE) {
                k = (GET_CUR_FORM_BTN_SLOT(j) << 2) - 0x60;

                pauseCtx->maskVtx[i + 0].v.ob[0] = pauseCtx->maskVtx[i + 2].v.ob[0] = pauseCtx->maskVtx[k].v.ob[0] - 2;

                pauseCtx->maskVtx[i + 1].v.ob[0] = pauseCtx->maskVtx[i + 3].v.ob[0] =
                    pauseCtx->maskVtx[i + 0].v.ob[0] + 32;

                pauseCtx->maskVtx[i + 0].v.ob[1] = pauseCtx->maskVtx[i + 1].v.ob[1] = pauseCtx->maskVtx[k].v.ob[1] + 2;

                pauseCtx->maskVtx[i + 2].v.ob[1] = pauseCtx->maskVtx[i + 3].v.ob[1] =
                    pauseCtx->maskVtx[i + 0].v.ob[1] - 32;

                pauseCtx->maskVtx[i + 0].v.ob[2] = pauseCtx->maskVtx[i + 1].v.ob[2] = pauseCtx->maskVtx[i + 2].v.ob[2] =
                    pauseCtx->maskVtx[i + 3].v.ob[2] = 0;

                pauseCtx->maskVtx[i + 0].v.flag = pauseCtx->maskVtx[i + 1].v.flag = pauseCtx->maskVtx[i + 2].v.flag =
                    pauseCtx->maskVtx[i + 3].v.flag = 0;

                pauseCtx->maskVtx[i + 0].v.tc[0] = pauseCtx->maskVtx[i + 0].v.tc[1] = pauseCtx->maskVtx[i + 1].v.tc[1] =
                    pauseCtx->maskVtx[i + 2].v.tc[0] = 0;

                pauseCtx->maskVtx[i + 1].v.tc[0] = pauseCtx->maskVtx[i + 2].v.tc[1] = pauseCtx->maskVtx[i + 3].v.tc[0] =
                    pauseCtx->maskVtx[i + 3].v.tc[1] = 32 * (1 << 5);

                pauseCtx->maskVtx[i + 0].v.cn[0] = pauseCtx->maskVtx[i + 1].v.cn[0] = pauseCtx->maskVtx[i + 2].v.cn[0] =
                    pauseCtx->maskVtx[i + 3].v.cn[0] = pauseCtx->maskVtx[i + 0].v.cn[1] =
                        pauseCtx->maskVtx[i + 1].v.cn[1] = pauseCtx->maskVtx[i + 2].v.cn[1] =
                            pauseCtx->maskVtx[i + 3].v.cn[1] = pauseCtx->maskVtx[i + 0].v.cn[2] =
                                pauseCtx->maskVtx[i + 1].v.cn[2] = pauseCtx->maskVtx[i + 2].v.cn[2] =
                                    pauseCtx->maskVtx[i + 3].v.cn[2] = 255;

                pauseCtx->maskVtx[i + 0].v.cn[3] = pauseCtx->maskVtx[i + 1].v.cn[3] = pauseCtx->maskVtx[i + 2].v.cn[3] =
                    pauseCtx->maskVtx[i + 3].v.cn[3] = pauseCtx->alpha;
            } else {
                pauseCtx->maskVtx[i + 2].v.ob[0] = -300;
                pauseCtx->maskVtx[i + 0].v.ob[0] = pauseCtx->maskVtx[i + 2].v.ob[0];

                pauseCtx->maskVtx[i + 1].v.ob[0] = pauseCtx->maskVtx[i + 3].v.ob[0] =
                    pauseCtx->maskVtx[i + 0].v.ob[0] + 32;

                pauseCtx->maskVtx[i + 0].v.ob[1] = pauseCtx->maskVtx[i + 1].v.ob[1] = 300;
                pauseCtx->maskVtx[i + 2].v.ob[1] = pauseCtx->maskVtx[i + 3].v.ob[1] =
                    pauseCtx->maskVtx[i + 0].v.ob[1] - 32;
            }
        }
    }

    pauseCtx->cursorVtx = GRAPH_ALLOC(play->state.gfxCtx, 20 * sizeof(Vtx));

    for (i = 0; i < 20; i++) {
        pauseCtx->cursorVtx[i].v.ob[0] = pauseCtx->cursorVtx[i].v.ob[1] = pauseCtx->cursorVtx[i].v.ob[2] = 0;

        pauseCtx->cursorVtx[i].v.flag = 0;

        pauseCtx->cursorVtx[i].v.tc[0] = pauseCtx->cursorVtx[i].v.tc[1] = 0;

        pauseCtx->cursorVtx[i].v.cn[0] = pauseCtx->cursorVtx[i].v.cn[1] = pauseCtx->cursorVtx[i].v.cn[2] =
            pauseCtx->cursorVtx[i].v.cn[3] = 255;
    }

    pauseCtx->cursorVtx[1].v.tc[0] = pauseCtx->cursorVtx[2].v.tc[1] = pauseCtx->cursorVtx[3].v.tc[0] =
        pauseCtx->cursorVtx[3].v.tc[1] = pauseCtx->cursorVtx[5].v.tc[0] = pauseCtx->cursorVtx[6].v.tc[1] =
            pauseCtx->cursorVtx[7].v.tc[0] = pauseCtx->cursorVtx[7].v.tc[1] = pauseCtx->cursorVtx[9].v.tc[0] =
                pauseCtx->cursorVtx[10].v.tc[1] = pauseCtx->cursorVtx[11].v.tc[0] = pauseCtx->cursorVtx[11].v.tc[1] =
                    pauseCtx->cursorVtx[13].v.tc[0] = pauseCtx->cursorVtx[14].v.tc[1] =
                        pauseCtx->cursorVtx[15].v.tc[0] = pauseCtx->cursorVtx[15].v.tc[1] = 16 * (1 << 5);

    pauseCtx->cursorVtx[17].v.tc[0] = pauseCtx->cursorVtx[18].v.tc[1] = pauseCtx->cursorVtx[19].v.tc[0] =
        pauseCtx->cursorVtx[19].v.tc[1] = 32 * (1 << 5);

    pauseCtx->infoPanelVtx = GRAPH_ALLOC(gfxCtx, 28 * sizeof(Vtx));

    if ((pauseCtx->state == PAUSE_STATE_SAVEPROMPT) || IS_PAUSE_STATE_GAMEOVER) {
        pauseCtx->saveVtx = GRAPH_ALLOC(gfxCtx, 80 * sizeof(Vtx));
        func_80825A50(play, pauseCtx->saveVtx, 5, 5);
    }
}

f32 sItemMaskCursorsX[] = {
    -62.0f, // Column 1
    -36.0f, // Column 2
    -10.0f, // Column 3
    16.0f,  // Column 4
    42.0f,  // Column 5
    68.0f,  // Column 6
};
f32 sItemMaskCursorsY[] = {
    31.0f,  // Row 1
    5.0f,   // Row 2
    -21.0f, // Row 3
    -47.0f, // Row 4
};
f32 sWorldMapCursorsX[REGION_MAX] = {
    -49.0f, // REGION_GREAT_BAY
    -35.0f, // REGION_ZORA_HALL
    -3.0f,  // REGION_ROMANI_RANCH
    4.0f,   // REGION_DEKU_PALACE
    12.0f,  // REGION_WOODFALL
    8.0f,   // REGION_CLOCK_TOWN
    7.0f,   // REGION_SNOWHEAD
    40.0f,  // REGION_IKANA_GRAVEYARD
    47.0f,  // REGION_IKANA_CANYON
    49.0f,  // REGION_GORON_VILLAGE
    55.0f,  // REGION_STONE_TOWER
};
f32 sWorldMapCursorsY[REGION_MAX] = {
    -15.0f, // REGION_GREAT_BAY
    -36.0f, // REGION_ZORA_HALL
    -23.0f, // REGION_ROMANI_RANCH
    -49.0f, // REGION_DEKU_PALACE
    -29.0f, // REGION_WOODFALL
    -8.0f,  // REGION_CLOCK_TOWN
    25.0f,  // REGION_SNOWHEAD
    2.0f,   // REGION_IKANA_GRAVEYARD
    -9.0f,  // REGION_IKANA_CANYON
    28.0f,  // REGION_GORON_VILLAGE
    7.0f,   // REGION_STONE_TOWER
};
f32 sOwlWarpWorldMapCursorsX[OWL_WARP_MAX - 1] = {
    -50.0f, // OWL_WARP_GREAT_BAY_COAST
    -38.0f, // OWL_WARP_ZORA_CAPE
    6.0f,   // OWL_WARP_SNOWHEAD
    11.0f,  // OWL_WARP_MOUNTAIN_VILLAGE
    8.0f,   // OWL_WARP_CLOCK_TOWN
    0.0f,   // OWL_WARP_MILK_ROAD
    12.0f,  // OWL_WARP_WOODFALL
    31.0f,  // OWL_WARP_SOUTHERN_SWAMP
    48.0f,  // OWL_WARP_IKANA_CANYON
    56.0f,  // OWL_WARP_STONE_TOWER
};
f32 sOwlWarpWorldMapCursorsY[OWL_WARP_MAX - 1] = {
    -14.0f, // OWL_WARP_GREAT_BAY_COAST
    -39.0f, // OWL_WARP_ZORA_CAPE
    23.0f,  // OWL_WARP_SNOWHEAD
    11.0f,  // OWL_WARP_MOUNTAIN_VILLAGE
    -8.0f,  // OWL_WARP_CLOCK_TOWN
    -15.0f, // OWL_WARP_MILK_ROAD
    -31.0f, // OWL_WARP_WOODFALL
    -30.0f, // OWL_WARP_SOUTHERN_SWAMP
    -10.0f, // OWL_WARP_IKANA_CANYON
    11.0f,  // OWL_WARP_STONE_TOWER
};
f32 sDungeonMapCursorsX[] = {
    -72.0f, // DUNGEON_BOSS_KEY
    -47.0f, // DUNGEON_COMPASS
    -26.0f, // DUNGEON_MAP
    -50.0f, // DUNGEON_STRAY_FAIRIES
    -48.0f, // DUNGEON_FLOOR_INDEX_4 (top floor)
    -48.0f, // DUNGEON_FLOOR_INDEX_3
    -48.0f, // DUNGEON_FLOOR_INDEX_2
    -48.0f, // DUNGEON_FLOOR_INDEX_1
    -48.0f, // DUNGEON_FLOOR_INDEX_0 (bottom floor)
};
f32 sDungeonMapCursorsY[] = {
    -47.0f, // DUNGEON_BOSS_KEY
    -47.0f, // DUNGEON_COMPASS
    -47.0f, // DUNGEON_MAP
    -30.0f, // DUNGEON_STRAY_FAIRIES
    33.0f,  // DUNGEON_FLOOR_INDEX_4 (top floor)
    22.0f,  // DUNGEON_FLOOR_INDEX_3
    11.0f,  // DUNGEON_FLOOR_INDEX_2
    -2.0f,  // DUNGEON_FLOOR_INDEX_1
    -13.0f, // DUNGEON_FLOOR_INDEX_0 (bottom floor)
};
f32 sQuestStatusCursorsX[] = {
    52.0f,  // QUEST_REMAINS_ODOLWA
    80.0f,  // QUEST_REMAINS_GOHT
    24.0f,  // QUEST_REMAINS_GYORG
    52.0f,  // QUEST_REMAINS_TWINMOLD
    81.0f,  // QUEST_SHIELD
    24.0f,  // QUEST_SWORD
    -78.0f, // QUEST_SONG_SONATA
    -61.0f, // QUEST_SONG_LULLABY
    -44.0f, // QUEST_SONG_BOSSA_NOVA
    -24.0f, // QUEST_SONG_ELEGY
    -6.0f,  // QUEST_SONG_OATH
    -3.0f,  // QUEST_SONG_SARIA
    -78.0f, // QUEST_SONG_TIME
    -61.0f, // QUEST_SONG_HEALING
    -44.0f, // QUEST_SONG_EPONA
    -24.0f, // QUEST_SONG_SOARING
    -6.0f,  // QUEST_SONG_STORMS
    -3.0f,  // QUEST_SONG_SUN
    -68.0f, // QUEST_BOMBERS_NOTEBOOK
    22.0f,  // QUEST_QUIVER
    83.0f,  // QUEST_BOMB_BAG
    -67.0f, // QUEST_SKULL_TOKEN
    -21.0f, // QUEST_HEART_PIECE
};
f32 sQuestStatusCursorsY[] = {
    33.0f,  // QUEST_REMAINS_ODOLWA
    18.0f,  // QUEST_REMAINS_GOHT
    18.0f,  // QUEST_REMAINS_GYORG
    0.0f,   // QUEST_REMAINS_TWINMOLD
    -23.0f, // QUEST_SHIELD
    -23.0f, // QUEST_SWORD
    -29.0f, // QUEST_SONG_SONATA
    -29.0f, // QUEST_SONG_LULLABY
    -29.0f, // QUEST_SONG_BOSSA_NOVA
    -29.0f, // QUEST_SONG_ELEGY
    -29.0f, // QUEST_SONG_OATH
    -29.0f, // QUEST_SONG_SARIA
    -11.0f, // QUEST_SONG_TIME
    -11.0f, // QUEST_SONG_HEALING
    -11.0f, // QUEST_SONG_EPONA
    -11.0f, // QUEST_SONG_SOARING
    -11.0f, // QUEST_SONG_STORMS
    -11.0f, // QUEST_SONG_SUN
    27.0f,  // QUEST_BOMBERS_NOTEBOOK
    -53.0f, // QUEST_QUIVER
    -53.0f, // QUEST_BOMB_BAG
    14.0f,  // QUEST_SKULL_TOKEN
    26.0f,  // QUEST_HEART_PIECE
};
void KaleidoScope_UpdateCursorSize(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 index;

    pauseCtx->cursorVtx[0].v.ob[0] = pauseCtx->cursorVtx[2].v.ob[0] = -8;
    pauseCtx->cursorVtx[1].v.ob[0] = pauseCtx->cursorVtx[3].v.ob[0] = pauseCtx->cursorVtx[0].v.ob[0] + 16;

    pauseCtx->cursorVtx[0].v.ob[1] = pauseCtx->cursorVtx[1].v.ob[1] = 8;
    pauseCtx->cursorVtx[2].v.ob[1] = pauseCtx->cursorVtx[3].v.ob[1] = pauseCtx->cursorVtx[0].v.ob[1] - 16;

    if (pauseCtx->cursorSpecialPos == 0) {
        switch (pauseCtx->pageIndex) {
            case PAUSE_ITEM:
                pauseCtx->cursorX = sItemMaskCursorsX[pauseCtx->cursorXIndex[PAUSE_ITEM]];
                pauseCtx->cursorY = sItemMaskCursorsY[pauseCtx->cursorYIndex[PAUSE_ITEM]];
                pauseCtx->cursorWidth = 15.0f;
                pauseCtx->cursorHeight = 15.0f;
                break;

            case PAUSE_MAP:
                if (!sInDungeonScene) {
                    if (IS_PAUSE_STATE_OWLWARP) {
                        pauseCtx->cursorX = sOwlWarpWorldMapCursorsX[pauseCtx->cursorPoint[PAUSE_WORLD_MAP]];
                        pauseCtx->cursorY = sOwlWarpWorldMapCursorsY[pauseCtx->cursorPoint[PAUSE_WORLD_MAP]];
                    } else {
                        pauseCtx->cursorX = sWorldMapCursorsX[pauseCtx->cursorPoint[PAUSE_WORLD_MAP]];
                        pauseCtx->cursorY = sWorldMapCursorsY[pauseCtx->cursorPoint[PAUSE_WORLD_MAP]];
                    }
                    if (!IS_PAUSE_STATE_OWLWARP) {
                        pauseCtx->cursorHeight = 10.0f;
                        pauseCtx->cursorWidth = 10.0f;
                    } else {
                        pauseCtx->cursorHeight = 15.0f;
                        pauseCtx->cursorWidth = 15.0f;
                    }
                } else {
                    pauseCtx->cursorX = sDungeonMapCursorsX[pauseCtx->cursorPoint[PAUSE_MAP]];
                    pauseCtx->cursorY = sDungeonMapCursorsY[pauseCtx->cursorPoint[PAUSE_MAP]];
                    if (pauseCtx->cursorSlot[pauseCtx->pageIndex] >= 4) {
                        pauseCtx->cursorWidth = 18.0f;
                        pauseCtx->cursorHeight = 12.0f;
                    } else if (pauseCtx->cursorSlot[pauseCtx->pageIndex] == 3) {
                        pauseCtx->cursorHeight = 12.0f;
                        pauseCtx->cursorWidth = 40.0f;
                    } else {
                        pauseCtx->cursorHeight = 15.0f;
                        pauseCtx->cursorWidth = 15.0f;
                    }
                }
                break;

            case PAUSE_QUEST:
                if (!R_PAUSE_DBG_QUEST_CURSOR_ON) {
                    pauseCtx->cursorX = sQuestStatusCursorsX[pauseCtx->cursorPoint[PAUSE_QUEST]];
                    pauseCtx->cursorY = sQuestStatusCursorsY[pauseCtx->cursorPoint[PAUSE_QUEST]];
                } else {
                    pauseCtx->cursorX = R_PAUSE_DBG_QUEST_CURSOR_X;
                    pauseCtx->cursorY = R_PAUSE_DBG_QUEST_CURSOR_Y;
                }
                pauseCtx->cursorHeight = 17.0f;
                pauseCtx->cursorWidth = 17.0f;
                if (pauseCtx->cursorSlot[pauseCtx->pageIndex] == QUEST_17) {
                    pauseCtx->cursorHeight = 25.0f;
                    pauseCtx->cursorWidth = 25.0f;
                } else if (pauseCtx->cursorSlot[pauseCtx->pageIndex] <= QUEST_SWORD) {
                    pauseCtx->cursorHeight = 18.0f;
                    pauseCtx->cursorWidth = 18.0f;
                } else if ((pauseCtx->cursorSlot[pauseCtx->pageIndex] >= QUEST_SONG_SONATA) &&
                           (pauseCtx->cursorSlot[pauseCtx->pageIndex] <= QUEST_SONG_SUN)) {
                    pauseCtx->cursorHeight = 12.0f;
                    pauseCtx->cursorWidth = 12.0f;
                }
                break;

            case PAUSE_MASK:
                pauseCtx->cursorX = sItemMaskCursorsX[pauseCtx->cursorXIndex[PAUSE_MASK]];
                pauseCtx->cursorY = sItemMaskCursorsY[pauseCtx->cursorYIndex[PAUSE_MASK]];
                pauseCtx->cursorWidth = 15.0f;
                pauseCtx->cursorHeight = 15.0f;
                break;
        }

        pauseCtx->cursorSpinPhase += 0x300;
    } else {
        if (pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_LEFT) {
            pauseCtx->cursorX = -93.0f;
        } else { // PAUSE_CURSOR_PAGE_RIGHT
            pauseCtx->cursorX = 101.0f;
        }
        pauseCtx->cursorSpinPhase += 0x300;
        pauseCtx->cursorHeight = 16.0f;
        pauseCtx->cursorWidth = 16.0f;
        pauseCtx->cursorY = -4.0f;
    }

    if (pauseCtx->cursorWidth < pauseCtx->cursorShrinkRate) {
        pauseCtx->cursorWidth = 0;
    } else {
        pauseCtx->cursorWidth -= pauseCtx->cursorShrinkRate;
    }

    if (pauseCtx->cursorHeight < pauseCtx->cursorShrinkRate) {
        pauseCtx->cursorHeight = 0.0f;
    } else {
        pauseCtx->cursorHeight -= pauseCtx->cursorShrinkRate;
    }

    if (pauseCtx->cursorShrinkRate != 0.0f) {
        pauseCtx->cursorShrinkRate -= 1.0f;
    }

    sCursorCirclesX[0] = Math_SinS(pauseCtx->cursorSpinPhase) * pauseCtx->cursorWidth;
    sCursorCirclesX[1] = Math_SinS(pauseCtx->cursorSpinPhase + 0x4000) * pauseCtx->cursorWidth;
    sCursorCirclesX[2] = Math_SinS(pauseCtx->cursorSpinPhase + 0x8000) * pauseCtx->cursorWidth;
    sCursorCirclesX[3] = Math_SinS(pauseCtx->cursorSpinPhase + 0xC000) * pauseCtx->cursorWidth;
    sCursorCirclesY[0] = Math_CosS(pauseCtx->cursorSpinPhase) * pauseCtx->cursorHeight;
    sCursorCirclesY[1] = Math_CosS(pauseCtx->cursorSpinPhase + 0x4000) * pauseCtx->cursorHeight;
    sCursorCirclesY[2] = Math_CosS(pauseCtx->cursorSpinPhase + 0x8000) * pauseCtx->cursorHeight;
    sCursorCirclesY[3] = Math_CosS(pauseCtx->cursorSpinPhase + 0xC000) * pauseCtx->cursorHeight;
}

void KaleidoScope_DrawCursor(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 i;

    OPEN_DISPS(play->state.gfxCtx);

    if ((pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE) ||
        (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG) ||
        ((pauseCtx->pageIndex == PAUSE_QUEST) && ((pauseCtx->mainState <= PAUSE_MAIN_STATE_SONG_PLAYBACK) ||
                                                  (pauseCtx->mainState == PAUSE_MAIN_STATE_SONG_PROMPT) ||
                                                  (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG)))) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                          PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, sCursorPrimR, sCursorPrimG, sCursorPrimB, 255);
        gDPSetEnvColor(POLY_OPA_DISP++, sCursorEnvR, sCursorEnvG, sCursorEnvB, 255);

        Matrix_Translate(pauseCtx->cursorX, pauseCtx->cursorY, -50.0f, MTXMODE_NEW);
        Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);

        for (i = 0; i < 4; i++) {
            Matrix_Push();
            Matrix_Translate(sCursorCirclesX[i], sCursorCirclesY[i], -50.0f, MTXMODE_APPLY);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPPipeSync(POLY_OPA_DISP++);
            gDPLoadTextureBlock(POLY_OPA_DISP++, &D_08064340, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gSPVertex(POLY_OPA_DISP++, pauseCtx->cursorVtx, 4, 0);
            gSP1Quadrangle(POLY_OPA_DISP++, 0, 2, 3, 1, 0);
            Matrix_Pop();
        }

        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void KaleidoScope_DrawGameOver(PlayState* play) {
    static s16 D_8082BE84 = 0;
    GraphicsContext* gfxCtx = play->state.gfxCtx;

    OPEN_DISPS(gfxCtx);

    func_8012C628(gfxCtx);

    gDPSetCycleType(POLY_OPA_DISP++, G_CYC_2CYCLE);
    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_PASS, G_RM_XLU_SURF2);
    gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT,
                      COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0);

    gDPSetPrimColor(POLY_OPA_DISP++, 0, 80, sGameOverPrimR, sGameOverPrimG, sGameOverPrimB, sGameOverPrimAlpha);
    gDPSetEnvColor(POLY_OPA_DISP++, sGameOverEnvR, sGameOverEnvG, sGameOverEnvB, 255);

    D_8082BE84 -= 2;

    gDPLoadTextureBlock(POLY_OPA_DISP++, gGameOverP1Tex, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gDPLoadMultiBlock(POLY_OPA_DISP++, gGameOverMaskTex, 256, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, 0,
                      G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, 5, G_TX_NOLOD, G_TX_NOLOD);

    gDPSetTileSize(POLY_OPA_DISP++, 1, 0, D_8082BE84 & 0x7F, 252, (D_8082BE84 & 0x7F) + 0x7C);

    gSPTextureRectangle(POLY_OPA_DISP++, 0x100, sGameOverRectPosY << 2, 0x200, (sGameOverRectPosY + 32) << 2,
                        G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

    gDPLoadTextureBlock(POLY_OPA_DISP++, gGameOverP2Tex, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    gSPTextureRectangle(POLY_OPA_DISP++, 0x200, sGameOverRectPosY << 2, 0x300, (sGameOverRectPosY + 32) << 2,
                        G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

    gDPLoadTextureBlock(POLY_OPA_DISP++, gGameOverP3Tex, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    gSPTextureRectangle(POLY_OPA_DISP++, 0x300, sGameOverRectPosY << 2, 0x400, (sGameOverRectPosY + 32) << 2,
                        G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

    CLOSE_DISPS(gfxCtx);
}

void KaleidoScope_Draw(PlayState* play) {
    s32 pad;
    PauseContext* pauseCtx = &play->pauseCtx;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;

    OPEN_DISPS(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x02, interfaceCtx->parameterSegment);
    gSPSegment(POLY_OPA_DISP++, 0x08, pauseCtx->iconItemSegment);
    gSPSegment(POLY_OPA_DISP++, 0x09, pauseCtx->iconItem24Segment);
    gSPSegment(POLY_OPA_DISP++, 0x0A, pauseCtx->nameSegment);
    gSPSegment(POLY_OPA_DISP++, 0x0C, pauseCtx->iconItemAltSegment);
    gSPSegment(POLY_OPA_DISP++, 0x0D, pauseCtx->iconItemLangSegment);
    gSPSegment(POLY_OPA_DISP++, 0x0B, pauseCtx->iconItemVtxSegment);

    if (pauseCtx->debugEditor == DEBUG_EDITOR_NONE) {
        KaleidoScope_SetView(pauseCtx, pauseCtx->eye.x, pauseCtx->eye.y, pauseCtx->eye.z);
        func_8012C8AC(play->state.gfxCtx);

        if (!IS_PAUSE_STATE_OWLWARP) {
            // Draw Default or Game Over Menus
            KaleidoScope_InitVertices(play, play->state.gfxCtx);
            KaleidoScope_DrawPages(play, play->state.gfxCtx);

            func_8012C8AC(play->state.gfxCtx);
            gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                              PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);

            KaleidoScope_SetView(pauseCtx, 0.0f, 0.0f, 64.0f);

            if (!IS_PAUSE_STATE_GAMEOVER) {
                KaleidoScope_DrawInfoPanel(play);
            }

            KaleidoScope_UpdateCursorSize(play);

            if (pauseCtx->state == PAUSE_STATE_MAIN) {
                KaleidoScope_DrawCursor(play);
            }

            if ((pauseCtx->state >= PAUSE_STATE_GAMEOVER_3) && (pauseCtx->state <= PAUSE_STATE_GAMEOVER_10) &&
                (play->gameOverCtx.state != GAMEOVER_INACTIVE)) {
                KaleidoScope_DrawGameOver(play);
            }
        } else {
            // Draw Owl Warp Menu
            KaleidoScope_InitVertices(play, play->state.gfxCtx);
            KaleidoScope_DrawPages(play, play->state.gfxCtx);
            KaleidoScope_DrawOwlWarpMapPage(play);

            func_8012C8AC(play->state.gfxCtx);
            gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                              PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);

            KaleidoScope_SetView(pauseCtx, 0.0f, 0.0f, 64.0f);
            KaleidoScope_DrawOwlWarpInfoPanel(play);
            KaleidoScope_UpdateCursorSize(play);

            if (pauseCtx->state == PAUSE_STATE_OWLWARP_SELECT) {
                KaleidoScope_DrawCursor(play);
            }
        }
    }

    if ((pauseCtx->debugEditor == DEBUG_EDITOR_INVENTORY_INIT) || (pauseCtx->debugEditor == DEBUG_EDITOR_INVENTORY)) {
        KaleidoScope_DrawInventoryEditor(play);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void KaleidoScope_GrayOutTextureRGBA32(u32* texture, u16 pixelCount) {
    u32 rgb;
    u32 gray;
    u16 i;
    s32 j;

    //! FAKE
    if (texture == NULL) {}

    for (i = 0; i < pixelCount; i++) {
        j = i;
        if ((texture[j] & 0xFFFFFF00) != 0) {
            rgb = texture[j] >> 8;
            gray = ((((rgb & 0xFF0000) >> 16) + ((rgb & 0xFF00) >> 7) + (rgb & 0xFF)) / 7) & 0xFF;

            rgb = gray;
            rgb <<= 8;
            rgb |= gray;
            rgb <<= 8;
            rgb |= gray;

            texture[j] = (rgb << 8) | (texture[j] & 0xFF);
        }
    }
}

void KaleidoScope_UpdateOpening(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;

    pauseCtx->eye.x += sPageSwitchEyeDx[pauseCtx->nextPageMode] * 2.0f;
    pauseCtx->eye.z += sPageSwitchEyeDz[pauseCtx->nextPageMode] * 2.0f;
    pauseCtx->switchPageTimer += 8;

    if (pauseCtx->switchPageTimer == 64) {
        // Finished opening
        func_80112C0C(play, 1);

        if (pauseCtx->cursorSpecialPos == 0) {
            gSaveContext.buttonStatus[EQUIP_SLOT_B] = D_801C6A98[pauseCtx->pageIndex][0];
            gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = D_801C6A98[pauseCtx->pageIndex][1];
            gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = D_801C6A98[pauseCtx->pageIndex][1];
            gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = D_801C6A98[pauseCtx->pageIndex][1];
            gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_ENABLED;
        } else {
            gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_ENABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_DISABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_DISABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_DISABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_DISABLED;
        }

        pauseCtx->pageIndex = sPageSwitchNextPageIndex[pauseCtx->nextPageMode];
        pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
        pauseCtx->state++; // PAUSE_STATE_MAIN
        pauseCtx->alpha = 255;
        func_80115844(play, 3);
    } else if (pauseCtx->switchPageTimer == 64) {
        pauseCtx->pageIndex = sPageSwitchNextPageIndex[pauseCtx->nextPageMode];
        pauseCtx->nextPageMode = (pauseCtx->pageIndex * 2) + 1;
    }
}

void KaleidoScope_Update(PlayState* play) {
    static u16 sCursorPointsToOcarinaModes[] = {
        28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
    };
    static s16 sUnpausedHudVisibility = HUD_VISIBILITY_IDLE;
    static s16 sNextMainState = PAUSE_MAIN_STATE_IDLE;
    static s16 sDelayTimer = 10;
    static s16 sGameOverColorTimer = 0;
    static s16 sStickXRepeatTimer = 0;
    static s16 sStickYRepeatTimer = 0;
    static s16 sStickXRepeatState = 0;
    static s16 sStickYRepeatState = 0;
    PauseContext* pauseCtx = &play->pauseCtx;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    MessageContext* msgCtx = &play->msgCtx;
    GameOverContext* gameOverCtx = &play->gameOverCtx;
    SramContext* sramCtx = &play->sramCtx;
    Input* input = CONTROLLER1(&play->state);
    size_t size0;
    size_t size1;
    size_t size2;
    u16 itemId;
    u16 worldMapCursorPoint;
    void* iconItemLangSegment;
    s16 stepR;
    s16 stepG;
    s16 stepB;
    s16 stepA;
    s16 stickAdjX = input->rel.stick_x;

    func_80109428(play);

    pauseCtx->stickAdjX = input->rel.stick_x;
    pauseCtx->stickAdjY = input->rel.stick_y;

    switch (pauseCtx->state) {
        case PAUSE_STATE_OPENING_2:
            sUnpausedHudVisibility = gSaveContext.hudVisibility;
            sPauseMenuVerticalOffset = -6240.0f;

            sUnpausedButtonStatus[EQUIP_SLOT_B] = gSaveContext.buttonStatus[EQUIP_SLOT_B];
            sUnpausedButtonStatus[EQUIP_SLOT_C_LEFT] = gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT];
            sUnpausedButtonStatus[EQUIP_SLOT_C_DOWN] = gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN];
            sUnpausedButtonStatus[EQUIP_SLOT_C_RIGHT] = gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT];
            sUnpausedButtonStatus[EQUIP_SLOT_A] = gSaveContext.buttonStatus[EQUIP_SLOT_A];

            pauseCtx->cursorXIndex[PAUSE_MAP] = 0;
            pauseCtx->cursorSlot[PAUSE_MAP] = R_REVERSE_FLOOR_INDEX + DUNGEON_FLOOR_INDEX_4;
            pauseCtx->cursorPoint[PAUSE_MAP] = pauseCtx->unk_256 = R_REVERSE_FLOOR_INDEX + DUNGEON_FLOOR_INDEX_4;

            sPauseCursorLeftX = -175;
            sPauseCursorRightX = 155;
            pauseCtx->roll = -314.0f;

            pauseCtx->iconItemSegment = (void*)ALIGN16((uintptr_t)play->objectCtx.spaceStart);
            size0 = SEGMENT_ROM_SIZE(icon_item_static_old);
            func_80178E7C((uintptr_t)SEGMENT_ROM_START(icon_item_static_test), pauseCtx->iconItemSegment, size0);

            gSegments[0x08] = PHYSICAL_TO_VIRTUAL(pauseCtx->iconItemSegment);

            for (itemId = 0; itemId <= ITEM_BOW_ARROW_FIRE; itemId++) {
                if (!gPlayerFormItemRestrictions[(void)0, gSaveContext.save.playerForm][(s32)itemId]) {
                    KaleidoScope_GrayOutTextureRGBA32(Lib_SegmentedToVirtual(gItemIcons[(s32)itemId]), 0x400);
                }
            }

            pauseCtx->iconItem24Segment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItemSegment + size0);
            size1 = SEGMENT_ROM_SIZE(icon_item_24_static_old);
            func_80178E7C((uintptr_t)SEGMENT_ROM_START(icon_item_24_static_test), pauseCtx->iconItem24Segment, size1);

            pauseCtx->iconItemAltSegment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItem24Segment + size1);
            if (func_8010A0A4(play)) {
                size_t size = SEGMENT_ROM_SIZE(icon_item_dungeon_static);

                DmaMgr_SendRequest0(pauseCtx->iconItemAltSegment, SEGMENT_ROM_START(icon_item_dungeon_static), size);
                iconItemLangSegment =
                    func_801068FC(play, (void*)ALIGN16((uintptr_t)pauseCtx->iconItemAltSegment + size), size);
                sInDungeonScene = true;
            } else {
                size_t size;

                sInDungeonScene = false;
                size = SEGMENT_ROM_SIZE(icon_item_field_static);
                DmaMgr_SendRequest0(pauseCtx->iconItemAltSegment, _icon_item_field_staticSegmentRomStart, size);
                iconItemLangSegment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItemAltSegment + size);
            }

            pauseCtx->iconItemLangSegment = iconItemLangSegment;
            size2 = SEGMENT_ROM_SIZE(icon_item_jpn_static);
            DmaMgr_SendRequest0(pauseCtx->iconItemLangSegment, SEGMENT_ROM_START(icon_item_jpn_static), size2);

            pauseCtx->nameSegment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItemLangSegment + size2);
            func_8011552C(play, 0x15);
            if (((void)0, gSaveContext.worldMapArea) < 0x16) {
                func_8082192C(pauseCtx->nameSegment + 0x400, ((void)0, gSaveContext.worldMapArea));
            }

            pauseCtx->iconItemVtxSegment = (void*)ALIGN16((uintptr_t)pauseCtx->nameSegment + 0xA00);
            DmaMgr_SendRequest0(pauseCtx->iconItemVtxSegment, SEGMENT_ROM_START(icon_item_vtx_static),
                                SEGMENT_ROM_SIZE(icon_item_vtx_static));

            pauseCtx->unk_2B6 = 255;
            pauseCtx->unk_2B7 = 255;
            pauseCtx->unk_2B8 = 255;
            pauseCtx->state = PAUSE_STATE_OPENING_3;
            break;

        case PAUSE_STATE_OPENING_3:
            pauseCtx->infoPanelOffsetY += 10;
            pauseCtx->itemPageRoll = pauseCtx->mapPageRoll = pauseCtx->questPageRoll = pauseCtx->maskPageRoll -= 40.0f;

            interfaceCtx->startAlpha += 63;
            sPauseCursorLeftX += (s16)(sPauseCursorLeftMoveOffsetX / 4);
            sPauseCursorRightX += (s16)(sPauseCursorRightMoveOffsetX / 4);
            pauseCtx->alpha += 31;
            if (pauseCtx->itemPageRoll == 0) {
                interfaceCtx->startAlpha = 255;
                sPauseMenuVerticalOffset = 0.0f;
                pauseCtx->state = PAUSE_STATE_OPENING_4;
            }

            KaleidoScope_UpdateOpening(play);
            break;

        case PAUSE_STATE_OPENING_4:
            pauseCtx->alpha += 31;
            KaleidoScope_UpdateOpening(play);

            if (pauseCtx->state == PAUSE_STATE_MAIN) {
                KaleidoScope_UpdateNamePanel(play);
            }
            break;

        case PAUSE_STATE_MAIN:
            switch (pauseCtx->mainState) {
                case PAUSE_MAIN_STATE_IDLE:
                    if (!pauseCtx->itemDescriptionOn &&
                        (CHECK_BTN_ALL(input->press.button, BTN_START) || CHECK_BTN_ALL(input->press.button, BTN_B))) {
                        func_8011552C(play, 0xA);
                        pauseCtx->state = PAUSE_STATE_UNPAUSE_SETUP;
                        sPauseMenuVerticalOffset = -6240.0f;
                        func_801A3AEC(0);
                    }
                    break;

                case PAUSE_MAIN_STATE_SWITCHING_PAGE:
                    KaleidoScope_UpdateSwitchPage(play, input);
                    break;

                case PAUSE_MAIN_STATE_SONG_PLAYBACK:
                    // Song is in playback
                    pauseCtx->ocarinaStaff = AudioOcarina_GetPlaybackStaff();
                    if (pauseCtx->ocarinaStaff->state == 0) {
                        // Song playback is finished, give song prompt to player
                        pauseCtx->mainState = PAUSE_MAIN_STATE_SONG_PROMPT_INIT;
                        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                    }
                    break;

                case PAUSE_MAIN_STATE_EQUIP_ITEM:
                    KaleidoScope_UpdateItemEquip(play);
                    break;

                case PAUSE_MAIN_STATE_SONG_PROMPT_INIT:
                    break;

                case PAUSE_MAIN_STATE_SONG_PROMPT:
                    pauseCtx->ocarinaStaff = AudioOcarina_GetPlayingStaff();

                    if (CHECK_BTN_ALL(input->press.button, BTN_START) || CHECK_BTN_ALL(input->press.button, BTN_B)) {
                        // Abort having the player play the song and close the pause menu
                        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                        func_8011552C(play, 0xA);
                        pauseCtx->state = PAUSE_STATE_UNPAUSE_SETUP;
                        sPauseMenuVerticalOffset = -6240.0f;
                        func_801A3AEC(0);
                        pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
                    } else if (pauseCtx->ocarinaStaff->state == pauseCtx->ocarinaSongIndex) {
                        // The player successfully played the song
                        play_sound(NA_SE_SY_TRE_BOX_APPEAR);
                        sNextMainState = PAUSE_MAIN_STATE_IDLE;
                        sDelayTimer = 30;
                        pauseCtx->mainState = PAUSE_MAIN_STATE_SONG_PROMPT_DONE;
                    } else if (pauseCtx->ocarinaStaff->state == 0xFF) {
                        // The player failed to play the song
                        play_sound(NA_SE_SY_OCARINA_ERROR);
                        sNextMainState = PAUSE_MAIN_STATE_SONG_PROMPT_INIT;
                        sDelayTimer = 20;
                        pauseCtx->mainState = PAUSE_MAIN_STATE_SONG_PROMPT_DONE;
                    }
                    break;

                case PAUSE_MAIN_STATE_SONG_PROMPT_DONE:
                    sDelayTimer--;
                    if (sDelayTimer == 0) {
                        pauseCtx->mainState = sNextMainState;
                        if (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE) {
                            AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                        }
                    }
                    break;

                case PAUSE_MAIN_STATE_SONG_PROMPT_UNUSED:
                    break;

                case PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG:
                    if (CHECK_BTN_ALL(input->press.button, BTN_START) || CHECK_BTN_ALL(input->press.button, BTN_B)) {
                        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                        func_8011552C(play, 0xA);
                        pauseCtx->state = PAUSE_STATE_UNPAUSE_SETUP;
                        sPauseMenuVerticalOffset = -6240.0f;
                        func_801A3AEC(0);
                        pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
                    }
                    break;

                case PAUSE_MAIN_STATE_SONG_PLAYBACK_INIT:
                    break;

                case PAUSE_MAIN_STATE_EQUIP_MASK:
                    KaleidoScope_UpdateMaskEquip(play);
                    break;

                case PAUSE_MAIN_STATE_BOMBERS_NOTEBOOK_OPEN:
                    if (!play->pauseCtx.bombersNotebookOpen) {
                        pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
                    }
                    break;

                default:
                    pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
                    break;
            }
            break;

        case PAUSE_STATE_SAVEPROMPT:
            switch (pauseCtx->savePromptState) {
                case PAUSE_SAVEPROMPT_STATE_0:
                    pauseCtx->roll -= 78.5f;
                    sPauseCursorLeftX -= (s16)(sPauseCursorLeftMoveOffsetX / 4);
                    sPauseCursorRightX -= (s16)(sPauseCursorRightMoveOffsetX / 4);
                    if (pauseCtx->roll <= -628.0f) {
                        pauseCtx->roll = -628.0f;
                        pauseCtx->savePromptState = PAUSE_SAVEPROMPT_STATE_1;
                    }
                    break;

                case PAUSE_SAVEPROMPT_STATE_1:
                    if (CHECK_BTN_ALL(input->press.button, BTN_A) || CHECK_BTN_ALL(input->press.button, BTN_CUP)) {
                        if (pauseCtx->promptChoice != PAUSE_PROMPT_YES) {
                            func_8011552C(play, 0xA);
                            pauseCtx->savePromptState = PAUSE_SAVEPROMPT_STATE_2;
                        } else {
                            play_sound(NA_SE_SY_PIECE_OF_HEART);
                            Play_SaveCycleSceneFlags(&play->state);
                            gSaveContext.save.playerData.savedSceneId = play->sceneId;
                            func_8014546C(sramCtx);
                            if (gSaveContext.unk_3F3F == 0) {
                                pauseCtx->savePromptState = PAUSE_SAVEPROMPT_STATE_5;
                            } else {
                                func_80147008(sramCtx, D_801C67C8[gSaveContext.fileNum],
                                              D_801C67F0[gSaveContext.fileNum]);
                                func_80147020(sramCtx);
                                pauseCtx->savePromptState = PAUSE_SAVEPROMPT_STATE_4;
                            }
                            sDelayTimer = 90;
                        }
                    } else if (CHECK_BTN_ALL(input->press.button, BTN_START)) {
                        func_8011552C(play, 0xA);
                        pauseCtx->savePromptState = PAUSE_SAVEPROMPT_STATE_3;
                        sPauseMenuVerticalOffset = -6240.0f;
                        D_8082B90C = pauseCtx->roll;
                        func_801A3AEC(0);
                    } else if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
                        func_8011552C(play, 0xA);
                        pauseCtx->savePromptState = PAUSE_SAVEPROMPT_STATE_2;
                        D_8082B90C = pauseCtx->roll;
                    }
                    break;

                case PAUSE_SAVEPROMPT_STATE_4:
                    if (sramCtx->status == 0) {
                        pauseCtx->savePromptState = PAUSE_SAVEPROMPT_STATE_5;
                    }
                    break;

                case PAUSE_SAVEPROMPT_STATE_5:
                    if (CHECK_BTN_ALL(input->press.button, BTN_B) || CHECK_BTN_ALL(input->press.button, BTN_A) ||
                        CHECK_BTN_ALL(input->press.button, BTN_START) || (--sDelayTimer == 0)) {
                        func_8011552C(play, 0xA);
                        pauseCtx->savePromptState = PAUSE_SAVEPROMPT_STATE_3;
                        sPauseMenuVerticalOffset = -6240.0f;
                        D_8082B90C = pauseCtx->roll;
                        func_801A3AEC(0);
                    }
                    break;

                case PAUSE_SAVEPROMPT_STATE_3:
                case PAUSE_SAVEPROMPT_STATE_7:
                    if (pauseCtx->roll != (D_8082B90C + 160.0f)) {
                        pauseCtx->itemPageRoll = pauseCtx->mapPageRoll = pauseCtx->questPageRoll =
                            pauseCtx->maskPageRoll += 40.0f;
                        pauseCtx->roll += 40.0f;
                        pauseCtx->infoPanelOffsetY -= 10;
                        sPauseCursorLeftX -= (s16)(sPauseCursorLeftMoveOffsetX / 4);
                        sPauseCursorRightX -= (s16)(sPauseCursorRightMoveOffsetX / 4);
                        pauseCtx->alpha -= 63;
                        if (pauseCtx->roll == (D_8082B90C + 160.0f)) {
                            pauseCtx->alpha = 0;
                        }
                    } else {
                        pauseCtx->debugEditor = DEBUG_EDITOR_NONE;
                        pauseCtx->state = PAUSE_STATE_UNPAUSE_CLOSE;
                        pauseCtx->itemPageRoll = pauseCtx->mapPageRoll = pauseCtx->questPageRoll =
                            pauseCtx->maskPageRoll = 160.0f;
                        pauseCtx->roll = -434.0f;
                        pauseCtx->namedItem = PAUSE_ITEM_NONE;
                        pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
                    }
                    break;

                case PAUSE_SAVEPROMPT_STATE_2:
                    pauseCtx->roll += 78.5f;
                    sPauseCursorLeftX += (s16)(sPauseCursorLeftMoveOffsetX / 4);
                    sPauseCursorRightX += (s16)(sPauseCursorRightMoveOffsetX / 4);
                    if (pauseCtx->roll >= -314.0f) {
                        pauseCtx->state = PAUSE_STATE_MAIN;
                        pauseCtx->savePromptState = PAUSE_SAVEPROMPT_STATE_0;
                        pauseCtx->roll = -314.0f;
                        pauseCtx->itemPageRoll = pauseCtx->mapPageRoll = pauseCtx->questPageRoll =
                            pauseCtx->maskPageRoll = 0.0f;
                        func_8011552C(play, 0x15);
                        gSaveContext.buttonStatus[EQUIP_SLOT_B] = D_801C6A98[pauseCtx->pageIndex + 1][0];
                        gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = D_801C6A98[pauseCtx->pageIndex + 1][1];
                        gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = D_801C6A98[pauseCtx->pageIndex + 1][1];
                        gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = D_801C6A98[pauseCtx->pageIndex + 1][1];
                        if ((pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_LEFT) ||
                            (pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_RIGHT)) {
                            KaleidoScope_MoveCursorToSpecialPos(play, pauseCtx->cursorSpecialPos);
                        } else {
                            func_80821A04(play);
                        }
                    }
                    break;

                case PAUSE_SAVEPROMPT_STATE_6:
                    if (interfaceCtx->unk_264 != 255) {
                        interfaceCtx->unk_264 += 10;
                        if (interfaceCtx->unk_264 >= 255) {
                            interfaceCtx->unk_264 = 255;
                            pauseCtx->state = PAUSE_STATE_OFF;
                            Game_SetFramerateDivisor(&play->state, 3);
                            R_PAUSE_BG_PRERENDER_STATE = PAUSE_BG_PRERENDER_UNK4;
                            Object_LoadAll(&play->objectCtx);
                            BgCheck_InitCollisionHeaders(&play->colCtx, play);
                            STOP_GAMESTATE(&play->state);
                            SET_NEXT_GAMESTATE(&play->state, TitleSetup_Init, sizeof(TitleSetupState));
                            func_801A4058(0x14);
                            gSaveContext.seqId = (u8)NA_BGM_DISABLED;
                            gSaveContext.ambienceId = AMBIENCE_ID_DISABLED;
                        }
                    }
                    break;
            }
            break;

        case PAUSE_STATE_GAMEOVER_2:
            pauseCtx->cursorSlot[PAUSE_MAP] = R_REVERSE_FLOOR_INDEX + DUNGEON_FLOOR_INDEX_4;
            pauseCtx->cursorPoint[PAUSE_MAP] = R_REVERSE_FLOOR_INDEX + DUNGEON_FLOOR_INDEX_4;
            sPauseCursorLeftX = -175;
            sPauseCursorRightX = 155;
            pauseCtx->roll = -434.0f;
            Interface_SetHudVisibility(HUD_VISIBILITY_NONE);

            pauseCtx->iconItemSegment =
                (void*)(((uintptr_t)play->objectCtx.spaceStart + 0x30) & ~0x3F); // Messed up ALIGN64
            size0 = SEGMENT_ROM_SIZE(icon_item_static_old);
            func_80178E7C(SEGMENT_ROM_START(icon_item_static_test), pauseCtx->iconItemSegment, size0);

            pauseCtx->iconItem24Segment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItemSegment + size0);
            size1 = SEGMENT_ROM_SIZE(icon_item_24_static_old);
            func_80178E7C(SEGMENT_ROM_START(icon_item_24_static_test), pauseCtx->iconItem24Segment, size1);

            pauseCtx->iconItemAltSegment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItem24Segment + size1);
            size2 = SEGMENT_ROM_SIZE(icon_item_gameover_static);
            DmaMgr_SendRequest0(pauseCtx->iconItemAltSegment, SEGMENT_ROM_START(icon_item_gameover_static), size2);

            pauseCtx->iconItemLangSegment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItemAltSegment + size2);
            DmaMgr_SendRequest0(pauseCtx->iconItemLangSegment, SEGMENT_ROM_START(icon_item_jpn_static),
                                SEGMENT_ROM_SIZE(icon_item_jpn_static));

            gSaveContext.timerStates[TIMER_ID_MOON_CRASH] = TIMER_STATE_OFF;

            sGameOverPrimR = 255;
            sGameOverPrimG = 130;
            sGameOverPrimB = 0;
            sGameOverPrimAlpha = 0;
            sGameOverEnvR = 30;
            sGameOverEnvG = 0;
            sGameOverEnvB = 0;
            sGameOverRectPosY = 98;
            sGameOverColorTimer = 30;

            pauseCtx->promptChoice = PAUSE_PROMPT_YES;
            pauseCtx->state++;
            if (gameOverCtx->state == GAMEOVER_INACTIVE) {
                pauseCtx->state++;
            }
            break;

        case PAUSE_STATE_GAMEOVER_3:
            stepR = ABS_ALT(sGameOverPrimR - 30) / sGameOverColorTimer;
            stepG = ABS_ALT(sGameOverPrimG - 0) / sGameOverColorTimer;
            stepB = ABS_ALT(sGameOverPrimB - 0) / sGameOverColorTimer;
            stepA = ABS_ALT(sGameOverPrimAlpha - 255) / sGameOverColorTimer;
            if (sGameOverPrimR >= 30) {
                sGameOverPrimR -= stepR;
            } else {
                sGameOverPrimR += stepR;
            }
            if (sGameOverPrimG >= 0) {
                sGameOverPrimG -= stepG;
            } else {
                sGameOverPrimG += stepG;
            }
            if (sGameOverPrimB >= 0) {
                sGameOverPrimB -= stepB;
            } else {
                sGameOverPrimB += stepB;
            }
            if (sGameOverPrimAlpha >= 255) {
                sGameOverPrimAlpha -= stepA;
            } else {
                sGameOverPrimAlpha += stepA;
            }

            stepR = ABS_ALT(sGameOverEnvR - 255) / sGameOverColorTimer;
            stepG = ABS_ALT(sGameOverEnvG - 130) / sGameOverColorTimer;
            stepB = ABS_ALT(sGameOverEnvB - 0) / sGameOverColorTimer;
            if (sGameOverEnvR >= 255) {
                sGameOverEnvR -= stepR;
            } else {
                sGameOverEnvR += stepR;
            }
            if (sGameOverEnvG >= 130) {
                sGameOverEnvG -= stepG;
            } else {
                sGameOverEnvG += stepG;
            }
            if (sGameOverEnvB >= 0) {
                sGameOverEnvB -= stepB;
            } else {
                sGameOverEnvB += stepB;
            }

            sGameOverColorTimer--;
            if (sGameOverColorTimer == 0) {
                sGameOverPrimR = 30;
                sGameOverPrimG = 0;
                sGameOverPrimB = 0;
                sGameOverPrimAlpha = 255;

                sGameOverEnvR = 255;
                sGameOverEnvG = 130;
                sGameOverEnvB = 0;

                sGameOverColorTimer = 40;
                pauseCtx->state++;
            }
            break;

        case PAUSE_STATE_GAMEOVER_4:
            sGameOverColorTimer--;
            if (sGameOverColorTimer == 0) {
                pauseCtx->state = PAUSE_STATE_GAMEOVER_5;
            }
            break;

        case PAUSE_STATE_GAMEOVER_5:
            pauseCtx->infoPanelOffsetY += 10;
            pauseCtx->roll -= 40.0f;
            pauseCtx->itemPageRoll = pauseCtx->mapPageRoll = pauseCtx->questPageRoll = pauseCtx->maskPageRoll =
                pauseCtx->roll;
            interfaceCtx->startAlpha += 63;
            sGameOverRectPosY -= 3;
            sPauseCursorLeftX += (s16)(sPauseCursorLeftMoveOffsetX / 4);
            sPauseCursorRightX += (s16)(sPauseCursorRightMoveOffsetX / 4);
            pauseCtx->alpha += 31;
            if (pauseCtx->roll < -628.0f) {
                pauseCtx->roll = -628.0f;
                interfaceCtx->startAlpha = 255;
                sGameOverRectPosY = 66;
                sPauseMenuVerticalOffset = 0.0f;
                pauseCtx->alpha = 255;
                if (gameOverCtx->state == GAMEOVER_INACTIVE) {
                    pauseCtx->state = PAUSE_STATE_GAMEOVER_SAVE_PROMPT;
                } else {
                    pauseCtx->state = PAUSE_STATE_GAMEOVER_CONTINUE_PROMPT;
                }
            }
            break;

        case PAUSE_STATE_GAMEOVER_SAVE_PROMPT:
            if (CHECK_BTN_ALL(input->press.button, BTN_A)) {
                if (pauseCtx->promptChoice != PAUSE_PROMPT_YES) {
                    pauseCtx->promptChoice = PAUSE_PROMPT_YES;
                    play_sound(NA_SE_SY_DECIDE);
                    pauseCtx->state = PAUSE_STATE_OFF;
                    Game_SetFramerateDivisor(&play->state, 3);
                    R_PAUSE_BG_PRERENDER_STATE = PAUSE_BG_PRERENDER_UNK4;
                    Object_LoadAll(&play->objectCtx);
                    BgCheck_InitCollisionHeaders(&play->colCtx, play);
                } else {
                    play_sound(NA_SE_SY_PIECE_OF_HEART);
                    pauseCtx->promptChoice = PAUSE_PROMPT_YES;
                    Play_SaveCycleSceneFlags(&play->state);
                    gSaveContext.save.playerData.savedSceneId = play->sceneId;
                    gSaveContext.save.playerData.health = 0x30;
                    func_8014546C(sramCtx);
                    if (gSaveContext.unk_3F3F == 0) {
                        pauseCtx->state = PAUSE_STATE_GAMEOVER_8;
                    } else {
                        func_80147008(sramCtx, D_801C67C8[gSaveContext.fileNum], D_801C67F0[gSaveContext.fileNum]);
                        func_80147020(sramCtx);
                        pauseCtx->state = PAUSE_STATE_GAMEOVER_7;
                    }
                    sDelayTimer = 90;
                }
            } else if ((pauseCtx->promptChoice == PAUSE_PROMPT_YES) && (stickAdjX >= 30)) {
                play_sound(NA_SE_SY_CURSOR);
                pauseCtx->promptChoice = PAUSE_PROMPT_NO;
            } else if ((pauseCtx->promptChoice != PAUSE_PROMPT_YES) && (stickAdjX <= -30)) {
                play_sound(NA_SE_SY_CURSOR);
                pauseCtx->promptChoice = PAUSE_PROMPT_YES;
            }
            break;

        case PAUSE_STATE_GAMEOVER_7:
            if (sramCtx->status == 0) {
                pauseCtx->state = PAUSE_STATE_OFF;
                Game_SetFramerateDivisor(&play->state, 3);
                R_PAUSE_BG_PRERENDER_STATE = PAUSE_BG_PRERENDER_UNK4;
                Object_LoadAll(&play->objectCtx);
                BgCheck_InitCollisionHeaders(&play->colCtx, play);
            }
            break;

        case PAUSE_STATE_GAMEOVER_8:
            sDelayTimer--;
            if (sDelayTimer == 0) {
                pauseCtx->state = PAUSE_STATE_GAMEOVER_CONTINUE_PROMPT;
                gameOverCtx->state++;
            } else if ((sDelayTimer <= 80) &&
                       (CHECK_BTN_ALL(input->press.button, BTN_A) || CHECK_BTN_ALL(input->press.button, BTN_START))) {
                pauseCtx->state = PAUSE_STATE_GAMEOVER_CONTINUE_PROMPT;
                gameOverCtx->state++;
                func_801A3AEC(0);
            }
            break;

        case PAUSE_STATE_GAMEOVER_CONTINUE_PROMPT:
            if (CHECK_BTN_ALL(input->press.button, BTN_A) || CHECK_BTN_ALL(input->press.button, BTN_START)) {
                if (pauseCtx->promptChoice == PAUSE_PROMPT_YES) {
                    play_sound(NA_SE_SY_PIECE_OF_HEART);
                    Play_SaveCycleSceneFlags(&play->state);
                    if (gSaveContext.save.entrance == ENTRANCE(UNSET_0D, 0)) {}
                } else { // PAUSE_PROMPT_NO
                    play_sound(NA_SE_SY_DECIDE);
                }
                pauseCtx->state = PAUSE_STATE_GAMEOVER_10;
            }
            break;

        case PAUSE_STATE_GAMEOVER_10:
            if (interfaceCtx->unk_264 != 255) {
                interfaceCtx->unk_264 += 10;
                if (interfaceCtx->unk_264 >= 255) {
                    interfaceCtx->unk_264 = 255;

                    pauseCtx->state = PAUSE_STATE_OFF;
                    Game_SetFramerateDivisor(&play->state, 3);
                    R_PAUSE_BG_PRERENDER_STATE = PAUSE_BG_PRERENDER_UNK4;
                    Object_LoadAll(&play->objectCtx);
                    BgCheck_InitCollisionHeaders(&play->colCtx, play);

                    if (pauseCtx->promptChoice == PAUSE_PROMPT_YES) {
                        func_80169FDC(&play->state);
                        gSaveContext.respawnFlag = -2;
                        gSaveContext.nextTransitionType = TRANS_TYPE_02;
                        gSaveContext.save.playerData.health = 0x30;
                        Audio_SetSpec(0xA);
                        gSaveContext.healthAccumulator = 0;
                        gSaveContext.magicState = MAGIC_STATE_IDLE;
                        gSaveContext.magicFlag = 0;
                        gSaveContext.magicCapacity = 0;
                        gSaveContext.magicFillTarget = gSaveContext.save.playerData.magic;
                        gSaveContext.save.playerData.magicLevel = 0;
                        gSaveContext.save.playerData.magic = 0;
                    } else { // PAUSE_PROMPT_NO
                        STOP_GAMESTATE(&play->state);
                        SET_NEXT_GAMESTATE(&play->state, TitleSetup_Init, sizeof(TitleSetupState));
                    }
                }
            }
            break;

        case PAUSE_STATE_OWLWARP_2:
            sPauseMenuVerticalOffset = -6240.0f;

            sUnpausedButtonStatus[EQUIP_SLOT_B] = gSaveContext.buttonStatus[EQUIP_SLOT_B];
            sUnpausedButtonStatus[EQUIP_SLOT_C_LEFT] = gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT];
            sUnpausedButtonStatus[EQUIP_SLOT_C_DOWN] = gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN];
            sUnpausedButtonStatus[EQUIP_SLOT_C_RIGHT] = gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT];
            sUnpausedButtonStatus[EQUIP_SLOT_A] = gSaveContext.buttonStatus[EQUIP_SLOT_A];

            pauseCtx->cursorXIndex[PAUSE_MAP] = 0;
            pauseCtx->cursorSlot[PAUSE_MAP] = R_REVERSE_FLOOR_INDEX + DUNGEON_FLOOR_INDEX_4;
            pauseCtx->cursorPoint[PAUSE_MAP] = pauseCtx->unk_256 = R_REVERSE_FLOOR_INDEX + DUNGEON_FLOOR_INDEX_4;

            sPauseCursorLeftX = -175;
            sPauseCursorRightX = 155;

            pauseCtx->iconItemSegment = (void*)ALIGN16((uintptr_t)play->objectCtx.spaceStart);
            size0 = SEGMENT_ROM_SIZE(icon_item_static_old);
            func_80178E7C(SEGMENT_ROM_START(icon_item_static_test), pauseCtx->iconItemSegment, size0);

            pauseCtx->iconItemAltSegment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItemSegment + size0);
            sInDungeonScene = false;
            size1 = SEGMENT_ROM_SIZE(icon_item_field_static);
            DmaMgr_SendRequest0(pauseCtx->iconItemAltSegment, SEGMENT_ROM_START(icon_item_field_static), size1);

            pauseCtx->iconItemLangSegment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItemAltSegment + size1);
            size2 = SEGMENT_ROM_SIZE(icon_item_jpn_static);
            DmaMgr_SendRequest0(pauseCtx->iconItemLangSegment, SEGMENT_ROM_START(icon_item_jpn_static), size2);

            pauseCtx->nameSegment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItemLangSegment + size2);
            func_8011552C(play, 0x16);
            worldMapCursorPoint = pauseCtx->cursorPoint[PAUSE_WORLD_MAP];
            func_80821900(pauseCtx->nameSegment, worldMapCursorPoint);

            pauseCtx->iconItemVtxSegment = (void*)ALIGN16((uintptr_t)pauseCtx->nameSegment + 0xA00);
            DmaMgr_SendRequest0(pauseCtx->iconItemVtxSegment, SEGMENT_ROM_START(icon_item_vtx_static),
                                SEGMENT_ROM_SIZE(icon_item_vtx_static));

            pauseCtx->state = PAUSE_STATE_OWLWARP_3;
            sGameOverRectPosY = 98;
            pauseCtx->promptChoice = PAUSE_PROMPT_YES;
            break;

        case PAUSE_STATE_OWLWARP_3:
            R_PAUSE_OWLWARP_ALPHA += 20;
            pauseCtx->infoPanelOffsetY += 10;
            pauseCtx->mapPageRoll -= 40.0f;
            interfaceCtx->startAlpha += 63;
            sGameOverRectPosY -= 3;
            sPauseCursorLeftX += (s16)(sPauseCursorLeftMoveOffsetX / 4);
            sPauseCursorRightX += (s16)(sPauseCursorRightMoveOffsetX / 4);
            pauseCtx->alpha += 31;

            if (pauseCtx->mapPageRoll == 0) {
                interfaceCtx->startAlpha = 255;
                sPauseMenuVerticalOffset = 0.0f;
                pauseCtx->alpha = 255;
                pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
                pauseCtx->cursorSpecialPos = 0;
                pauseCtx->state = PAUSE_STATE_OWLWARP_SELECT;
                R_PAUSE_OWLWARP_ALPHA = 120;
            }
            break;

        case PAUSE_STATE_OWLWARP_SELECT:
            if (CHECK_BTN_ALL(input->press.button, BTN_START) || CHECK_BTN_ALL(input->press.button, BTN_B)) {
                func_8011552C(play, 0xA);
                pauseCtx->state = PAUSE_STATE_OWLWARP_6;
                sPauseMenuVerticalOffset = -6240.0f;
                func_801A3AEC(0);
                play->msgCtx.ocarinaMode = 4;
                gSaveContext.prevHudVisibility = HUD_VISIBILITY_ALL;
            } else if (CHECK_BTN_ALL(input->press.button, BTN_A)) {
                play_sound(NA_SE_SY_DECIDE);
                Message_StartTextbox(play, 0x1B93, NULL);
                pauseCtx->state = PAUSE_STATE_OWLWARP_CONFIRM;
            } else {
                KaleidoScope_UpdateOwlWarpNamePanel(play);
            }
            break;

        case PAUSE_STATE_OWLWARP_CONFIRM:
            if (CHECK_BTN_ALL(input->press.button, BTN_A)) {
                msgCtx->msgLength = 0;
                msgCtx->msgMode = 0;
                if (msgCtx->choiceIndex == 0) {
                    func_8011552C(play, 0xA);
                    pauseCtx->state = PAUSE_STATE_OWLWARP_6;
                    sPauseMenuVerticalOffset = -6240.0f;
                    func_801A3AEC(0);
                    play->msgCtx.ocarinaMode = sCursorPointsToOcarinaModes[pauseCtx->cursorPoint[PAUSE_WORLD_MAP]];
                    play_sound(NA_SE_SY_DECIDE);
                } else {
                    pauseCtx->state = PAUSE_STATE_OWLWARP_SELECT;
                    func_8011552C(play, 0x16);
                    play_sound(NA_SE_SY_MESSAGE_PASS);
                }
            } else if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
                msgCtx->msgLength = 0;
                msgCtx->msgMode = 0;
                pauseCtx->state = PAUSE_STATE_OWLWARP_SELECT;
                play_sound(NA_SE_SY_MESSAGE_PASS);
            } else if (CHECK_BTN_ALL(input->press.button, BTN_START)) {
                msgCtx->msgLength = 0;
                msgCtx->msgMode = 0;
                func_8011552C(play, 0xA);
                pauseCtx->state = PAUSE_STATE_OWLWARP_6;
                sPauseMenuVerticalOffset = -6240.0f;
                func_801A3AEC(0);
                play->msgCtx.ocarinaMode = 4;
                gSaveContext.prevHudVisibility = HUD_VISIBILITY_ALL;
            }
            break;

        case PAUSE_STATE_OWLWARP_6:
            if (pauseCtx->mapPageRoll != 160.0f) {
                R_PAUSE_OWLWARP_ALPHA -= 60;
                if (R_PAUSE_OWLWARP_ALPHA <= 0) {
                    R_PAUSE_OWLWARP_ALPHA = 0;
                }
                pauseCtx->infoPanelOffsetY -= 10;
                pauseCtx->mapPageRoll += 40.0f;
                interfaceCtx->startAlpha -= 63;
                sPauseCursorLeftX -= (s16)(sPauseCursorLeftMoveOffsetX / 4);
                sPauseCursorRightX -= (s16)(sPauseCursorRightMoveOffsetX / 4);
                pauseCtx->alpha -= 63;
                if (pauseCtx->mapPageRoll == 160.0f) {
                    pauseCtx->alpha = 0;
                }
            } else {
                pauseCtx->debugEditor = DEBUG_EDITOR_NONE;
                pauseCtx->state = PAUSE_STATE_UNPAUSE_CLOSE;
                pauseCtx->itemPageRoll = pauseCtx->mapPageRoll = pauseCtx->questPageRoll = pauseCtx->maskPageRoll =
                    160.0f;
                pauseCtx->namedItem = PAUSE_ITEM_NONE;
                interfaceCtx->startAlpha = 0;
                pauseCtx->pageIndex = pauseCtx->unk_2C8;
                pauseCtx->cursorPoint[PAUSE_WORLD_MAP] = pauseCtx->unk_2CA;
            }
            break;

        case PAUSE_STATE_UNPAUSE_SETUP:
            if (pauseCtx->itemPageRoll != 160.0f) {
                pauseCtx->infoPanelOffsetY -= 10;
                pauseCtx->itemPageRoll = pauseCtx->mapPageRoll = pauseCtx->questPageRoll = pauseCtx->maskPageRoll +=
                    40.0f;
                interfaceCtx->startAlpha -= 63;
                sPauseCursorLeftX -= (s16)(sPauseCursorLeftMoveOffsetX / 4);
                sPauseCursorRightX -= (s16)(sPauseCursorRightMoveOffsetX / 4);
                pauseCtx->alpha -= 63;
                if (pauseCtx->itemPageRoll == 160.0f) {
                    pauseCtx->alpha = 0;
                }
            } else {
                pauseCtx->debugEditor = DEBUG_EDITOR_NONE;
                pauseCtx->state = PAUSE_STATE_UNPAUSE_CLOSE;
                pauseCtx->maskPageRoll = 160.0f;
                pauseCtx->questPageRoll = 160.0f;
                pauseCtx->mapPageRoll = 160.0f;
                pauseCtx->itemPageRoll = 160.0f;
                pauseCtx->namedItem = PAUSE_ITEM_NONE;
                interfaceCtx->startAlpha = 0;
            }
            break;

        case PAUSE_STATE_UNPAUSE_CLOSE:
            pauseCtx->state = PAUSE_STATE_OFF;
            Game_SetFramerateDivisor(&play->state, 3);
            R_PAUSE_BG_PRERENDER_STATE = PAUSE_BG_PRERENDER_UNK4;
            Object_LoadAll(&play->objectCtx);
            BgCheck_InitCollisionHeaders(&play->colCtx, play);

            gSaveContext.buttonStatus[EQUIP_SLOT_B] = sUnpausedButtonStatus[EQUIP_SLOT_B];
            gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = sUnpausedButtonStatus[EQUIP_SLOT_C_LEFT];
            gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = sUnpausedButtonStatus[EQUIP_SLOT_C_DOWN];
            gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = sUnpausedButtonStatus[EQUIP_SLOT_C_RIGHT];
            gSaveContext.buttonStatus[EQUIP_SLOT_A] = sUnpausedButtonStatus[EQUIP_SLOT_A];

            func_80110038(play);
            gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
            Interface_SetHudVisibility(HUD_VISIBILITY_ALL);
            MsgEvent_SendNullTask();
            func_80143324(play, &play->skyboxCtx, play->skyboxId);

            if ((msgCtx->msgMode != 0) && (msgCtx->currentTextId == 0xFF)) {
                func_80115844(play, 0x12);
                func_8011552C(play, 0x12);
                Interface_SetHudVisibility(HUD_VISIBILITY_A_B_C);
            } else {
                interfaceCtx->unk_222 = interfaceCtx->unk_224 = 0;
            }
            gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
            Interface_SetHudVisibility(sUnpausedHudVisibility);
            func_801A3A7C(0);
            break;
    }

    // If stickAdj is held, set a delay to allow the cursor to read the next input.
    // The first delay is given a longer time than all subsequent delays.
    if (!IS_PAUSE_STATE_GAMEOVER && (pauseCtx->state != PAUSE_STATE_SAVEPROMPT)) {
        if (pauseCtx->stickAdjX < -30) {
            if (sStickXRepeatState == -1) {
                sStickXRepeatTimer--;
                if (sStickXRepeatTimer < 0) {
                    // Allow the input to register and apply the delay for all subsequent repeated inputs
                    sStickXRepeatTimer = 2;
                } else {
                    // Cancel the current input
                    pauseCtx->stickAdjX = 0;
                }
            } else {
                // Allow the input to register and apply the delay for the first repeated input
                sStickXRepeatTimer = 10;
                sStickXRepeatState = -1;
            }
        } else if (pauseCtx->stickAdjX > 30) {
            if (sStickXRepeatState == 1) {
                sStickXRepeatTimer--;
                if (sStickXRepeatTimer < 0) {
                    // Allow the input to register and apply the delay for all subsequent repeated inputs
                    sStickXRepeatTimer = 2;
                } else {
                    // Cancel the current input
                    pauseCtx->stickAdjX = 0;
                }
            } else {
                // Allow the input to register and apply the delay for the first repeated input
                sStickXRepeatTimer = 10;
                sStickXRepeatState = 1;
            }
        } else {
            sStickXRepeatState = 0;
        }

        if (pauseCtx->stickAdjY < -30) {
            if (sStickYRepeatState == -1) {
                sStickYRepeatTimer--;
                if (sStickYRepeatTimer < 0) {
                    // Allow the input to register and apply the delay for all subsequent repeated inputs
                    sStickYRepeatTimer = 2;
                } else {
                    // Cancel the current input
                    pauseCtx->stickAdjY = 0;
                }
            } else {
                // Allow the input to register and apply the delay for the first repeated input
                sStickYRepeatTimer = 10;
                sStickYRepeatState = -1;
            }
        } else if (pauseCtx->stickAdjY > 30) {
            if (sStickYRepeatState == 1) {
                sStickYRepeatTimer--;
                if (sStickYRepeatTimer < 0) {
                    // Allow the input to register and apply the delay for all subsequent repeated inputs
                    sStickYRepeatTimer = 2;
                } else {
                    // Cancel the current input
                    pauseCtx->stickAdjY = 0;
                }
            } else {
                // Allow the input to register and apply the delay for the first repeated input
                sStickYRepeatTimer = 10;
                sStickYRepeatState = 1;
            }
        } else {
            sStickYRepeatState = 0;
        }
    }

    // Process the Cursor input
    if ((R_PAUSE_BG_PRERENDER_STATE == PAUSE_BG_PRERENDER_DONE) && (pauseCtx->debugEditor == DEBUG_EDITOR_NONE) &&
        !IS_PAUSE_STATE_OWLWARP &&
        (((pauseCtx->state >= PAUSE_STATE_OPENING_3) && (pauseCtx->state <= PAUSE_STATE_SAVEPROMPT)) ||
         ((pauseCtx->state >= PAUSE_STATE_GAMEOVER_2) && (pauseCtx->state <= PAUSE_STATE_UNPAUSE_SETUP)))) {
        if (!IS_PAUSE_STATE_GAMEOVER) {
            switch (pauseCtx->pageIndex) {
                case PAUSE_ITEM:
                    KaleidoScope_UpdateItemCursor(play);
                    break;

                case PAUSE_MAP:
                    if (sInDungeonScene) {
                        KaleidoScope_UpdateDungeonCursor(play);
                    } else {
                        KaleidoScope_UpdateWorldMapCursor(play);
                    }
                    break;

                case PAUSE_QUEST:
                    KaleidoScope_UpdateQuestCursor(play);
                    break;

                case PAUSE_MASK:
                    KaleidoScope_UpdateMaskCursor(play);
                    break;
            }

            if ((pauseCtx->state == PAUSE_STATE_MAIN) &&
                ((pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE) ||
                 (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG))) {
                KaleidoScope_HandlePageToggles(play, input);
            }
        }
        if (pauseCtx->state == PAUSE_STATE_MAIN) {
            KaleidoScope_UpdateNamePanel(play);
        }
    } else if (pauseCtx->state == PAUSE_STATE_OWLWARP_SELECT) {
        KaleidoScope_UpdateWorldMapCursor(play);
        KaleidoScope_UpdateNamePanel(play);
    }

    // Update the inventory editor
    if ((pauseCtx->debugEditor == DEBUG_EDITOR_INVENTORY_INIT) || (pauseCtx->debugEditor == DEBUG_EDITOR_INVENTORY)) {
        KaleidoScope_UpdateInventoryEditor(play);
    }
}
