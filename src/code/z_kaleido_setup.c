#include "global.h"
#include "z64rumble.h"
#include "overlays/gamestates/ovl_file_choose/z_file_choose.h"

s16 D_801BDB00[] = { PAUSE_1, PAUSE_2, PAUSE_3, PAUSE_0 };
f32 sKaleidoSetupEyeX[] = { -64.0f, 0.0f, 64.0f, 0.0f };
f32 sKaleidoSetupEyeZ[] = { 0.0f, -64.0f, 0.0f, 64.0f };

void func_800F4A10(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 i;

    Rumble_StateReset();

    pauseCtx->unk_206 = 0;
    pauseCtx->unk_200 = 1;
    pauseCtx->eye.x = sKaleidoSetupEyeX[pauseCtx->pageIndex];
    pauseCtx->eye.z = sKaleidoSetupEyeZ[pauseCtx->pageIndex];
    pauseCtx->pageIndex = D_801BDB00[pauseCtx->pageIndex];
    pauseCtx->unk_27E = -40;

    for (i = 0; i < ARRAY_COUNT(pauseCtx->worldMapPoints); i++) {
        pauseCtx->worldMapPoints[i] = 0;
    }

    if (pauseCtx->state == 1) {
        for (i = 0; i < 11; i++) {
            if ((gSaveContext.save.mapsVisited >> i) & 1) {
                pauseCtx->worldMapPoints[i] = 1;
            }
        }
    } else {
        for (i = 9; i >= 0; i--) {
            if ((gSaveContext.save.playerData.owlActivationFlags >> i) & 1) {
                pauseCtx->worldMapPoints[i] = 1;
                pauseCtx->unk_238[4] = i;
            }
        }

        if ((gSaveContext.save.playerData.owlActivationFlags >> 4) & 1) {
            pauseCtx->unk_238[4] = 4;
        }
    }

    YREG(11) = -0x00C8;
    YREG(12) = -0x3840;
    YREG(13) = 0x2710;
    YREG(14) = 0x2710;
    YREG(15) = 0x2710;
    YREG(16) = -0x00BE;
    YREG(17) = -0x06D6;
    YREG(18) = -0x0B90;
    YREG(19) = 0x06E0;
    YREG(20) = 0;
    YREG(21) = -0x0622;
    YREG(22) = -0x0C44;
    YREG(23) = 0x0622;
    YREG(24) = -0x0622;
    YREG(25) = -0x005A;
    YREG(26) = -0x3840;
}

void KaleidoSetup_Update(PlayState* play) {
    Input* input = CONTROLLER1(&play->state);
    MessageContext* msgCtx = &play->msgCtx;
    Player* player = GET_PLAYER(play);
    PauseContext* pauseCtx = &play->pauseCtx;

    if (CHECK_BTN_ALL(input->cur.button, BTN_R)) {
        if (msgCtx && msgCtx) {}
    }

    if ((pauseCtx->state == 0) && (pauseCtx->debugState == 0) && (play->gameOverCtx.state == GAMEOVER_INACTIVE)) {
        if ((play->transitionTrigger == TRANS_TRIGGER_OFF) && (play->transitionMode == TRANS_MODE_OFF)) {
            if ((gSaveContext.save.cutscene < 0xFFF0) && (gSaveContext.nextCutsceneIndex < 0xFFF0)) {
                if (!Play_InCsMode(play) || ((msgCtx->msgMode != 0) && (msgCtx->currentTextId == 0xFF))) {
                    if ((play->unk_1887C < 2) && (gSaveContext.unk_3F28 != 8) && (gSaveContext.unk_3F28 != 9)) {
                        if (!(gSaveContext.eventInf[1] & 0x80) && !(player->stateFlags1 & 0x20)) {
                            if (!(play->actorCtx.unk5 & 2) && !(play->actorCtx.unk5 & 4)) {
                                if ((play->actorCtx.unk268 == 0) && CHECK_BTN_ALL(input->press.button, BTN_START)) {
                                    gSaveContext.unk_3F26 = gSaveContext.unk_3F22;
                                    pauseCtx->unk_2B9 = 0;
                                    pauseCtx->state = 1;
                                    func_800F4A10(play);
                                    pauseCtx->mode = pauseCtx->pageIndex * 2 + 1;
                                    func_801A3A7C(1);
                                }

                                if (pauseCtx->state == 1) {
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

    pauseCtx->pageIndex = PAUSE_0;

    pauseCtx->unk_21C = 160.0f;
    pauseCtx->unk_218 = 160.0f;
    pauseCtx->unk_214 = 160.0f;
    pauseCtx->unk_210 = 160.0f;

    pauseCtx->eye.x = -64.0f;
    pauseCtx->unk_20C = 936.0f;
    pauseCtx->unk_220 = -314.0f;

    pauseCtx->unk_238[PAUSE_1] = XREG(94) + 3;

    pauseCtx->unk_258 = 11;
    pauseCtx->unk_25A = 0;

    pauseCtx->cursorItem[PAUSE_0] = 999;
    pauseCtx->cursorItem[PAUSE_1] = XREG(94) + 3;
    pauseCtx->cursorItem[PAUSE_2] = 999;
    pauseCtx->cursorItem[PAUSE_3] = 999;

    pauseCtx->unk_268[PAUSE_0] = 0;
    pauseCtx->unk_268[PAUSE_1] = XREG(94) + 3;

    pauseCtx->unk_284 = 2;
    pauseCtx->unk_2A0 = -1;
    pauseCtx->unk_2BA = 320;
    pauseCtx->unk_2BC = 40;
    pauseCtx->unk_29E = 100;

    View_Init(&pauseCtx->view, play->state.gfxCtx);
}

void KaleidoSetup_Destroy(PlayState* play) {
}
