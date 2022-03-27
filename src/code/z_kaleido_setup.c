#include "global.h"

extern s16 D_801BDB00[4]/* = { 1, 2, 3, 0 }*/;
extern f32 D_801BDB08[4]/* = { -64.0f, 0.0f, 64.0f, 0.0f }*/;
extern f32 D_801BDB18[6]/* = { 0.0f, -64.0f, 0.0f, 64.0f, 0.0f, 0.0f }*/;



#ifdef NON_EQUIVALENT
void func_800F4A10(GlobalContext* globalCtx) {
    PauseContext* pauseCtx;
    s16 i;

    func_8013EE24();

    pauseCtx = &globalCtx->pauseCtx;

    pauseCtx->unk_206 = 0;
    pauseCtx->unk_200 = 1;
    pauseCtx->eye.x = D_801BDB08[pauseCtx->pageIndex];
    pauseCtx->eye.z = D_801BDB18[pauseCtx->pageIndex];
    pauseCtx->unk_27E = -0x0028;
    pauseCtx->pageIndex = D_801BDB00[pauseCtx->pageIndex];

    for (i = 0; i < ARRAY_COUNT(pauseCtx->worldMapPoints); i++) {
        pauseCtx->worldMapPoints[i] = 0;
    }

    if (pauseCtx->state == 1) {
        for (i = 0; i < 11; i++) {
            if (((gSaveContext.save.mapsVisited >> i) & 1) != 0) {
                pauseCtx->worldMapPoints[i] = 1;
            }
        }
    } else {
        for (i = 9; i >= 0; i--) {
            if (((gSaveContext.save.playerData.owlActivationFlags >> i) & 1) != 0) {
                pauseCtx->worldMapPoints[i] = (u8) 1U;
                pauseCtx->unk_238[4] = i;
            }
        }

        if (((gSaveContext.save.playerData.owlActivationFlags >> 4) & 1) != 0) {
            pauseCtx->unk_238[4] = 4;
        }
    }

    gGameInfo->data[0x24B] = -0x00C8;
    gGameInfo->data[0x24C] = -0x3840;
    gGameInfo->data[0x24D] = 0x2710;
    gGameInfo->data[0x24E] = 0x2710;
    gGameInfo->data[0x24F] = 0x2710;
    gGameInfo->data[0x250] = -0x00BE;
    gGameInfo->data[0x251] = -0x06D6;
    gGameInfo->data[0x252] = -0x0B90;
    gGameInfo->data[0x253] = 0x06E0;
    gGameInfo->data[0x254] = 0;
    gGameInfo->data[0x255] = -0x0622;
    gGameInfo->data[0x256] = -0x0C44;
    gGameInfo->data[0x257] = 0x0622;
    gGameInfo->data[0x258] = -0x0622;
    gGameInfo->data[0x259] = -0x005A;
    gGameInfo->data[0x25A] = -0x3840;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_kaleido_setup/func_800F4A10.s")
#endif

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
            if ((globalCtx->gameOverCtx.state == 0) && (globalCtx->sceneLoadFlag == 0) && (globalCtx->unk_18B4A == 0) && (gSaveContext.save.cutscene < 0xFFF0)) {
                if (gSaveContext.nextCutsceneIndex < 0xFFF0) {
                    if ((func_801690CC(globalCtx) == 0) || (( (msgCtx->msgMode != 0)) && (msgCtx->currentTextId == 0xFF))) {
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
