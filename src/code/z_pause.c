#include "global.h"

void FrameAdvance_Init(FrameAdvanceContext* frameAdvCtx) {
    frameAdvCtx->timer = 0;
    frameAdvCtx->enabled = false;
}

s32 FrameAdvance_Update(FrameAdvanceContext* frameAdvCtx, Input* input) {
    if (!frameAdvCtx->enabled || (CHECK_BTN_ALL(input->cur.button, BTN_Z) &&
                                  (CHECK_BTN_ALL(input->press.button, BTN_R) ||
                                   (CHECK_BTN_ALL(input->cur.button, BTN_R) && (++frameAdvCtx->timer >= 9))))) {
        frameAdvCtx->timer = 0;
        return true;
    }
    return false;
}
