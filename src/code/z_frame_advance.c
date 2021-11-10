#include "global.h"

void FrameAdvance_Init(FrameAdvanceContext* frameAdvCtx) {
    frameAdvCtx->timer = 0;
    frameAdvCtx->enabled = false;
}

/**
 * Frame advance allows you to advance through the game one frame at a time on command.
 * To advance a frame, hold Z and press R on the spceified controller.
 * Holding Z and R will advance a frame every half second.
 *
 * This function returns true when frame advance is not active (game will run normally)
 *
 * Note: There is no way to enable it
 */
s32 FrameAdvance_Update(FrameAdvanceContext* frameAdvCtx, Input* input) {
    if (!frameAdvCtx->enabled || (CHECK_BTN_ALL(input->cur.button, BTN_Z) &&
                                  (CHECK_BTN_ALL(input->press.button, BTN_R) ||
                                   (CHECK_BTN_ALL(input->cur.button, BTN_R) && (++frameAdvCtx->timer >= 9))))) {
        frameAdvCtx->timer = 0;
        return true;
    }
    return false;
}
