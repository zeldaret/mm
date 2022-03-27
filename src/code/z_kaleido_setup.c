#include "global.h"

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kaleido_setup/func_800F4A10.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kaleido_setup/func_800F4C0C.s")

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
