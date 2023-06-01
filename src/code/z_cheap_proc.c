#include "global.h"

/**
 * Draws a display list to the opaque display buffer
 */
void Gfx_DrawDListOpa(PlayState* play, Gfx* dlist) {
    Gfx* dl;

    OPEN_DISPS(play->state.gfxCtx);

    dl = POLY_OPA_DISP;

    gSPDisplayList(&dl[0], gSetupDLs[SETUPDL_25]);
    gSPMatrix(&dl[1], Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(&dl[2], dlist);

    POLY_OPA_DISP = &dl[3];

    CLOSE_DISPS(play->state.gfxCtx);
}

/**
 * Draws a display list to the translucent display buffer
 */
void Gfx_DrawDListXlu(PlayState* play, Gfx* dlist) {
    Gfx* dl;

    OPEN_DISPS(play->state.gfxCtx);

    dl = POLY_XLU_DISP;

    gSPDisplayList(&dl[0], gSetupDLs[SETUPDL_25]);
    gSPMatrix(&dl[1], Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(&dl[2], dlist);

    POLY_XLU_DISP = &dl[3];

    CLOSE_DISPS(play->state.gfxCtx);
}
