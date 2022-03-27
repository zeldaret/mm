#include "global.h"

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kaleido_setup/func_800F4A10.s")

void func_800F4C0C(GlobalContext* globalCtx) {
    Input* input;
    MessageContext* msgCtx; // sp24
    Player* player;
    PauseContext* pauseCtx; // sp1C


    player = GET_PLAYER(globalCtx);


    input = CONTROLLER1(globalCtx);
    msgCtx = &globalCtx->msgCtx;
    pauseCtx = &globalCtx->pauseCtx;

    if (~(input->cur.button | ~0x10) == 0) {
        if (msgCtx && msgCtx) {}
    }

    if (pauseCtx->state == 0) {
        if (pauseCtx->debugState == 0) {
            if ((globalCtx->gameOverCtx.state == 0) && (globalCtx->sceneLoadFlag == 0) && (globalCtx->unk_18B4A == 0) && (gSaveContext.cutscene < 0xFFF0)) {
                if (gSaveContext.nextCutsceneIndex < 0xFFF0) {
                    if ((func_801690CC(globalCtx) == 0) || (( (msgCtx->msgMode != 0)) && (msgCtx->unk11F04 == 0xFF))) {
                        if ((globalCtx->unk_1887C < 2)) {
                            if ((gSaveContext.unk_3F28 != 8) && (gSaveContext.unk_3F28 != 9)) {
                                if (((gSaveContext.eventInf[1] & 0x80) == 0) && ((player->stateFlags1 & 0x20) == 0)) {
                                    if (((globalCtx->actorCtx.unk5 & 2) == 0) && ((globalCtx->actorCtx.unk5 & 4) == 0)) {
                                        if ((globalCtx->actorCtx.unk268 == 0) && (~(input->press.button | ~0x1000) == 0)) {
                                            gSaveContext.unk_3F26 = gSaveContext.unk_3F22;
                                            pauseCtx->unk_2B9 = 0;
                                            pauseCtx->state = 1;
                                            func_800F4A10(globalCtx);
                                            pauseCtx->mode = (pauseCtx->pageIndex * 2) + 1;
                                            func_801A3A7C(1);
                                        }
                                        if (pauseCtx->state == 1) {
                                            Game_SetFramerateDivisor(&globalCtx->state, 2);
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
    }
}


void KaleidoSetup_Init(GlobalContext* globalCtx) {
    PauseContext* pauseCtx = &globalCtx->pauseCtx;
    s32 pad[2];

    bzero(pauseCtx, sizeof(PauseContext));

    pauseCtx->pageIndex = 0;

    pauseCtx->unk_21C = 160.0f;
    pauseCtx->unk_218 = 160.0f;
    pauseCtx->unk_214 = 160.0f;
    pauseCtx->unk_210 = 160.0f;

    pauseCtx->eye.x = -64.0f;
    pauseCtx->unk_20C = 936.0f;
    pauseCtx->unk_220 = -314.0f;

    pauseCtx->unk_238[1] = XREG(94) + 3;

    pauseCtx->unk_258 = 11;
    pauseCtx->unk_25A = 0;

    pauseCtx->unk_25E[0] = 999;
    pauseCtx->unk_25E[1] = XREG(94) + 3;
    pauseCtx->unk_25E[2] = 999;
    pauseCtx->unk_25E[3] = 999;

    pauseCtx->unk_268[0] = 0;
    pauseCtx->unk_268[1] = XREG(94) + 3;

    pauseCtx->unk_284 = 2;
    pauseCtx->unk_2A0 = -1;
    pauseCtx->unk_2BA = 320;
    pauseCtx->unk_2BC = 40;
    pauseCtx->unk_29E = 100;

    View_Init(&pauseCtx->view, globalCtx->state.gfxCtx);
}

void KaleidoSetup_Destroy(GlobalContext* globalCtx) {

}
