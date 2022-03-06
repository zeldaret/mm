#include "prevent_bss_reordering.h"
#include "global.h"

void (*sKaleidoScopeUpdateFunc)(GlobalContext* globalCtx);
void (*sKaleidoScopeDrawFunc)(GlobalContext* globalCtx);

extern void KaleidoScope_Update(GlobalContext* globalCtx);
extern void KaleidoScope_Draw(GlobalContext* globalCtx);

void KaleidoScopeCall_LoadPlayer() {
    KaleidoMgrOverlay* playerActorOvl = &gKaleidoMgrOverlayTable[KALEIDO_OVL_PLAYER_ACTOR];

    if (gKaleidoMgrCurOvl != playerActorOvl) {
        if (gKaleidoMgrCurOvl != NULL) {
            KaleidoManager_ClearOvl(gKaleidoMgrCurOvl);
        }

        KaleidoManager_LoadOvl(playerActorOvl);
    }
}

void KaleidoScopeCall_Init(GlobalContext* globalCtx) {
    sKaleidoScopeUpdateFunc = KaleidoManager_GetRamAddr(KaleidoScope_Update);
    sKaleidoScopeDrawFunc = KaleidoManager_GetRamAddr(KaleidoScope_Draw);
    KaleidoSetup_Init(globalCtx);
}

void KaleidoScopeCall_Destroy(GlobalContext* globalCtx) {
    KaleidoSetup_Destroy(globalCtx);
}

void KaleidoScopeCall_Update(GlobalContext* globalCtx) {
    PauseContext* pauseCtx = &globalCtx->pauseCtx;
    KaleidoMgrOverlay* kaleidoScopeOvl = &gKaleidoMgrOverlayTable[KALEIDO_OVL_KALEIDO_SCOPE];

    if ((globalCtx->pauseCtx.state != 0) || (globalCtx->pauseCtx.debugState != 0)) {
        if (pauseCtx->state == 1 || pauseCtx->state == 19) {
            if (ShrinkWindow_GetLetterboxMagnitude() == 0) {
                R_PAUSE_MENU_MODE = 1;
                pauseCtx->unk_200 = 0;
                pauseCtx->unk_208 = 0;
                pauseCtx->state = (pauseCtx->state & 0xFFFF) + 1;
            }
        } else if (pauseCtx->state == 8) {
            R_PAUSE_MENU_MODE = 1;
            pauseCtx->unk_200 = 0;
            pauseCtx->unk_208 = 0;
            pauseCtx->state = (pauseCtx->state & 0xFFFF) + 1;
        } else if ((pauseCtx->state == 2) || (pauseCtx->state == 9) || (pauseCtx->state == 20)) {
            if (R_PAUSE_MENU_MODE == 3) {
                pauseCtx->state++;
            }
        } else if (pauseCtx->state != 0) {
            if (gKaleidoMgrCurOvl != kaleidoScopeOvl) {
                if (gKaleidoMgrCurOvl != NULL) {
                    KaleidoManager_ClearOvl(gKaleidoMgrCurOvl);
                }

                KaleidoManager_LoadOvl(kaleidoScopeOvl);
            }

            if (gKaleidoMgrCurOvl == kaleidoScopeOvl) {
                sKaleidoScopeUpdateFunc(globalCtx);

                if ((globalCtx->pauseCtx.state == 0) && (globalCtx->pauseCtx.debugState == 0)) {
                    KaleidoManager_ClearOvl(kaleidoScopeOvl);
                    KaleidoScopeCall_LoadPlayer();
                }
            }
        }
    }
}

void KaleidoScopeCall_Draw(GlobalContext* globalCtx) {
    KaleidoMgrOverlay* kaleidoScopeOvl = &gKaleidoMgrOverlayTable[KALEIDO_OVL_KALEIDO_SCOPE];

    if (R_PAUSE_MENU_MODE == 3) {
        if (((globalCtx->pauseCtx.state >= 4) && (globalCtx->pauseCtx.state <= 7)) ||
            ((globalCtx->pauseCtx.state >= 11) && (globalCtx->pauseCtx.state <= 26))) {
            if (gKaleidoMgrCurOvl == kaleidoScopeOvl) {
                sKaleidoScopeDrawFunc(globalCtx);
            }
        }
    }
}
