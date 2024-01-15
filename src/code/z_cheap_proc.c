#include "global.h"

/**
 * Draws a display list to the opaque display buffer
 */
void Gfx_DrawDListOpa(PlayState* play, Gfx* dList) {
    Gfx* gfx;

    OPEN_DISPS(play->state.gfxCtx);

    gfx = POLY_OPA_DISP;

    gSPDisplayList(&gfx[0], gSetupDLs[SETUPDL_25]);
    gSPMatrix(&gfx[1], Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(&gfx[2], dList);

    POLY_OPA_DISP = &gfx[3];

    CLOSE_DISPS(play->state.gfxCtx);
}

/**
 * Draws a display list to the translucent display buffer
 */
void Gfx_DrawDListXlu(PlayState* play, Gfx* dList) {
    Gfx* gfx;

    OPEN_DISPS(play->state.gfxCtx);

    gfx = POLY_XLU_DISP;

    gSPDisplayList(&gfx[0], gSetupDLs[SETUPDL_25]);
    gSPMatrix(&gfx[1], Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(&gfx[2], dList);

    POLY_XLU_DISP = &gfx[3];

    CLOSE_DISPS(play->state.gfxCtx);
}
