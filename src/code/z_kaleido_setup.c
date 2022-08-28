#include "global.h"
#include "z64rumble.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"

s16 D_801BDB00[] = { PAUSE_MAP, PAUSE_QUEST, PAUSE_MASK, PAUSE_ITEM };
f32 sKaleidoSetupEyeX[] = { -64.0f, 0.0f, 64.0f, 0.0f };
f32 sKaleidoSetupEyeZ[] = { 0.0f, -64.0f, 0.0f, 64.0f };

void func_800F4A10(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 i;

    Rumble_StateReset();

    pauseCtx->unk_206 = 0;
    pauseCtx->actionState = PAUSE_ACTIONSTATE_1;
    pauseCtx->eye.x = sKaleidoSetupEyeX[pauseCtx->pageIndex];
    pauseCtx->eye.z = sKaleidoSetupEyeZ[pauseCtx->pageIndex];
    pauseCtx->pageIndex = D_801BDB00[pauseCtx->pageIndex];
    pauseCtx->infoPanelOffsetY = -40;

    for (i = 0; i < ARRAY_COUNT(pauseCtx->worldMapPoints); i++) {
        pauseCtx->worldMapPoints[i] = false;
    }

    if (pauseCtx->state == PAUSE_STATE_1) {
        for (i = 0; i < 11; i++) {
            if ((gSaveContext.save.mapsVisited >> i) & 1) {
                pauseCtx->worldMapPoints[i] = true;
            }
        }
    } else {
        for (i = 9; i >= 0; i--) {
            if ((gSaveContext.save.playerData.owlActivationFlags >> i) & 1) {
                pauseCtx->worldMapPoints[i] = true;
                pauseCtx->cursorPoint[PAUSE_WORLD_MAP] = i;
            }
        }

        if ((gSaveContext.save.playerData.owlActivationFlags >> 4) & 1) {
            pauseCtx->cursorPoint[PAUSE_WORLD_MAP] = 4;
        }
    }

    YREG(11) = -200;
    YREG(12) = -14400;
    YREG(13) = 10000;
    YREG(14) = 10000;
    YREG(15) = 10000;
    YREG(16) = -190;
    YREG(17) = -1750;
    YREG(18) = -2960;
    YREG(19) = 1760;
    YREG(20) = 0;
    YREG(21) = -1570;
    YREG(22) = -3140;
    YREG(23) = 1570;
    YREG(24) = -1570;
    YREG(25) = -90;
    YREG(26) = -14400;
}

void KaleidoSetup_Update(PlayState* play) {
    Input* input = CONTROLLER1(&play->state);
    MessageContext* msgCtx = &play->msgCtx;
    Player* player = GET_PLAYER(play);
    PauseContext* pauseCtx = &play->pauseCtx;

    if (CHECK_BTN_ALL(input->cur.button, BTN_R)) {
        if (msgCtx && msgCtx) {}
    }

    if ((pauseCtx->state == PAUSE_STATE_0) && (pauseCtx->debugEditor == DEBUG_EDITOR_NONE) &&
        (play->gameOverCtx.state == GAMEOVER_INACTIVE)) {
        if ((play->transitionTrigger == TRANS_TRIGGER_OFF) && (play->transitionMode == TRANS_MODE_OFF)) {
            if ((gSaveContext.save.cutscene < 0xFFF0) && (gSaveContext.nextCutsceneIndex < 0xFFF0)) {
                if (!Play_InCsMode(play) || ((msgCtx->msgMode != 0) && (msgCtx->currentTextId == 0xFF))) {
                    if ((play->unk_1887C < 2) && (gSaveContext.unk_3F28 != 8) && (gSaveContext.unk_3F28 != 9)) {
                        if (!(gSaveContext.eventInf[1] & 0x80) && !(player->stateFlags1 & 0x20)) {
                            if (!(play->actorCtx.unk5 & 2) && !(play->actorCtx.unk5 & 4)) {
                                if ((play->actorCtx.unk268 == 0) && CHECK_BTN_ALL(input->press.button, BTN_START)) {
                                    gSaveContext.unk_3F26 = gSaveContext.unk_3F22;
                                    pauseCtx->itemDescriptionOn = false;
                                    pauseCtx->state = PAUSE_STATE_1;
                                    func_800F4A10(play);
                                    pauseCtx->mode = pauseCtx->pageIndex * 2 + 1;
                                    func_801A3A7C(1);
                                }

                                if (pauseCtx->state == PAUSE_STATE_1) {
                                    Game_SetFramerateDivisor(&play->state, 2);
                                    if (ShrinkWindow_GetLetterboxTarget() != 0) {
                                        ShrinkWindow_SetLetterboxTarget(0);
                                    }
                                    func_801A3AEC(1);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void KaleidoSetup_Init(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;
    s32 pad[2];

    bzero(pauseCtx, sizeof(PauseContext));

    pauseCtx->pageIndex = PAUSE_ITEM;

    pauseCtx->MaskPageRoll = 160.0f;
    pauseCtx->QuestPageRoll = 160.0f;
    pauseCtx->MapPageRoll = 160.0f;
    pauseCtx->itemPageRoll = 160.0f;

    pauseCtx->eye.x = -64.0f;
    pauseCtx->unk_20C = 936.0f;
    pauseCtx->unk_220 = -314.0f;

    pauseCtx->cursorPoint[PAUSE_MAP] = XREG(94) + 3;

    pauseCtx->cursorSpecialPos = PAUSE_CURSOR_PAGE_RIGHT;
    pauseCtx->pageSwitchTimer = 0;

    pauseCtx->cursorItem[PAUSE_ITEM] = PAUSE_ITEM_NONE;
    pauseCtx->cursorItem[PAUSE_MAP] = XREG(94) + 3;
    pauseCtx->cursorItem[PAUSE_QUEST] = PAUSE_ITEM_NONE;
    pauseCtx->cursorItem[PAUSE_MASK] = PAUSE_ITEM_NONE;

    pauseCtx->cursorSlot[PAUSE_ITEM] = 0;
    pauseCtx->cursorSlot[PAUSE_MAP] = XREG(94) + 3;

    pauseCtx->cursorColorSet = 2;
    pauseCtx->ocarinaSongIndex = -1;
    pauseCtx->equipAnimScale = 320;
    pauseCtx->equipAnimShrinkRate = 40;
    pauseCtx->promptAlpha = 100;

    View_Init(&pauseCtx->view, play->state.gfxCtx);
}

void KaleidoSetup_Destroy(PlayState* play) {
}
