/*
 * File: z_kaleido_prompt.c
 * Overlay: ovl_kaleido_scope
 * Description: Pause Menu - Prompt
 */

#include "z_kaleido_scope.h"

s16 D_8082B6F0[] = { 100, 255 };
void KaleidoScope_UpdatePrompt(PlayState* play) {
    static s16 D_8082B6F4 = 0;
    static s16 D_8082B6F8 = 10;
    PauseContext* pauseCtx = &play->pauseCtx;
    Input* input = &play->state.input[0];
    s8 relStickX = input->rel.stick_x;
    s16 step;

    if (((play->pauseCtx.state == 7) && (pauseCtx->unk_208 == 1)) || (pauseCtx->state == 0xE) ||
        (pauseCtx->state == 0x11)) {
        if ((pauseCtx->promptChoice == 0) && (relStickX >= 30)) {
            play_sound(NA_SE_SY_CURSOR);
            pauseCtx->promptChoice = 4;
        } else if ((pauseCtx->promptChoice != 0) && (relStickX <= -30)) {
            play_sound(NA_SE_SY_CURSOR);
            pauseCtx->promptChoice = 0;
        }

        step = ABS_ALT(pauseCtx->unk_29E - D_8082B6F0[D_8082B6F4]) / D_8082B6F8;

        if (pauseCtx->unk_29E >= D_8082B6F0[D_8082B6F4]) {
            pauseCtx->unk_29E -= step;
        } else {
            pauseCtx->unk_29E += step;
        }

        D_8082B6F8--;
        if (D_8082B6F8 == 0) {
            pauseCtx->unk_29E = D_8082B6F0[D_8082B6F4];
            D_8082B6F8 = D_8082B6F4 + 20;
            D_8082B6F4 ^= 1;
        }
    }
}