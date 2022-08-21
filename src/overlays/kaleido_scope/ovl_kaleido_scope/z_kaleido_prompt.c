/*
 * File: z_kaleido_prompt.c
 * Overlay: ovl_kaleido_scope
 * Description: Pause Menu - Save Prompt
 */

#include "z_kaleido_scope.h"

s16 sSavePromptAlphaTargets[] = { 100, 255 };

// Unused remnant of OoT
void KaleidoScope_UpdateSavePrompt(PlayState* play) {
    static s16 sSavePromptAlphaTargetIndex = 0;
    static s16 sSavePromptAlphaTimer = 10;
    PauseContext* pauseCtx = &play->pauseCtx;
    Input* input = CONTROLLER1(&play->state);
    s8 relStickX = input->rel.stick_x;
    s16 alphaStep;

    if (((play->pauseCtx.state == 7) && (pauseCtx->unk_208 == 1)) || (pauseCtx->state == 0xE) ||
        (pauseCtx->state == 0x11)) {
        if ((pauseCtx->savePromptChoice == PAUSE_SAVE_PROMPT_YES) && (relStickX >= 30)) {
            play_sound(NA_SE_SY_CURSOR);
            pauseCtx->savePromptChoice = PAUSE_SAVE_PROMPT_NO;
        } else if ((pauseCtx->savePromptChoice != PAUSE_SAVE_PROMPT_YES) && (relStickX <= -30)) {
            play_sound(NA_SE_SY_CURSOR);
            pauseCtx->savePromptChoice = PAUSE_SAVE_PROMPT_YES;
        }

        alphaStep = ABS_ALT(pauseCtx->savePromptAlpha - sSavePromptAlphaTargets[sSavePromptAlphaTargetIndex]) /
                    sSavePromptAlphaTimer;

        if (pauseCtx->savePromptAlpha >= sSavePromptAlphaTargets[sSavePromptAlphaTargetIndex]) {
            pauseCtx->savePromptAlpha -= alphaStep;
        } else {
            pauseCtx->savePromptAlpha += alphaStep;
        }

        sSavePromptAlphaTimer--;
        if (sSavePromptAlphaTimer == 0) {
            pauseCtx->savePromptAlpha = sSavePromptAlphaTargets[sSavePromptAlphaTargetIndex];
            sSavePromptAlphaTimer = sSavePromptAlphaTargetIndex + 20;
            sSavePromptAlphaTargetIndex ^= 1;
        }
    }
}
