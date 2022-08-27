#include "prevent_bss_reordering.h"
#include "global.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"

void (*sKaleidoScopeUpdateFunc)(PlayState* play);
void (*sKaleidoScopeDrawFunc)(PlayState* play);

extern void KaleidoScope_Update(PlayState* play);
extern void KaleidoScope_Draw(PlayState* play);

void KaleidoScopeCall_LoadPlayer() {
    KaleidoMgrOverlay* playerActorOvl = &gKaleidoMgrOverlayTable[KALEIDO_OVL_PLAYER_ACTOR];

    if (gKaleidoMgrCurOvl != playerActorOvl) {
        if (gKaleidoMgrCurOvl != NULL) {
            KaleidoManager_ClearOvl(gKaleidoMgrCurOvl);
        }

        KaleidoManager_LoadOvl(playerActorOvl);
    }
}

void KaleidoScopeCall_Init(PlayState* play) {
    sKaleidoScopeUpdateFunc = KaleidoManager_GetRamAddr(KaleidoScope_Update);
    sKaleidoScopeDrawFunc = KaleidoManager_GetRamAddr(KaleidoScope_Draw);
    KaleidoSetup_Init(play);
}

void KaleidoScopeCall_Destroy(PlayState* play) {
    KaleidoSetup_Destroy(play);
}

void KaleidoScopeCall_Update(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;
    KaleidoMgrOverlay* kaleidoScopeOvl = &gKaleidoMgrOverlayTable[KALEIDO_OVL_KALEIDO_SCOPE];

    if ((play->pauseCtx.state != PAUSE_STATE_0) || (play->pauseCtx.debugEditor != DEBUG_EDITOR_NONE)) {
        if ((pauseCtx->state == PAUSE_STATE_1) || (pauseCtx->state == PAUSE_STATE_13)) {
            if (ShrinkWindow_GetLetterboxMagnitude() == 0) {
                R_PAUSE_MENU_MODE = 1;
                pauseCtx->state6SubState = PAUSE_SUBSTATE6_0;
                pauseCtx->state7SubState = PAUSE_SUBSTATE7_0;
                pauseCtx->state = (pauseCtx->state & 0xFFFF) + 1;
            }
        } else if (pauseCtx->state == PAUSE_STATE_GAMEOVER_0) {
            R_PAUSE_MENU_MODE = 1;
            pauseCtx->state6SubState = PAUSE_SUBSTATE6_0;
            pauseCtx->state7SubState = PAUSE_SUBSTATE7_0;
            pauseCtx->state = (pauseCtx->state & 0xFFFF) + 1;
        } else if ((pauseCtx->state == PAUSE_STATE_2) || (pauseCtx->state == PAUSE_STATE_GAMEOVER_1) ||
                   (pauseCtx->state == PAUSE_STATE_14)) {
            if (R_PAUSE_MENU_MODE == 3) {
                pauseCtx->state++;
            }
        } else if (pauseCtx->state != PAUSE_STATE_0) {
            if (gKaleidoMgrCurOvl != kaleidoScopeOvl) {
                if (gKaleidoMgrCurOvl != NULL) {
                    KaleidoManager_ClearOvl(gKaleidoMgrCurOvl);
                }

                KaleidoManager_LoadOvl(kaleidoScopeOvl);
            }

            if (gKaleidoMgrCurOvl == kaleidoScopeOvl) {
                sKaleidoScopeUpdateFunc(play);

                if ((play->pauseCtx.state == PAUSE_STATE_0) && (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE)) {
                    KaleidoManager_ClearOvl(kaleidoScopeOvl);
                    KaleidoScopeCall_LoadPlayer();
                }
            }
        }
    }
}

void KaleidoScopeCall_Draw(PlayState* play) {
    KaleidoMgrOverlay* kaleidoScopeOvl = &gKaleidoMgrOverlayTable[KALEIDO_OVL_KALEIDO_SCOPE];

    if (R_PAUSE_MENU_MODE == 3) {
        if (((play->pauseCtx.state >= PAUSE_STATE_4) && (play->pauseCtx.state <= PAUSE_STATE_7)) ||
            ((play->pauseCtx.state >= PAUSE_STATE_GAMEOVER_3) && (play->pauseCtx.state <= PAUSE_STATE_1A))) {
            if (gKaleidoMgrCurOvl == kaleidoScopeOvl) {
                sKaleidoScopeDrawFunc(play);
            }
        }
    }
}
