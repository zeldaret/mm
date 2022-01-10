#include "global.h"

/**
 * Draws a display list to the opaque display buffer
 */
void Gfx_DrawDListOpa(GlobalContext* globalCtx, Gfx* dlist) {
    Gfx* dl;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    dl = POLY_OPA_DISP;

    gSPDisplayList(&dl[0], &sSetupDL[6 * 0x19]);
    gSPMatrix(&dl[1], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(&dl[2], dlist);

    POLY_OPA_DISP = &dl[3];

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * Draws a display list to the translucent display buffer
 */
void Gfx_DrawDListXlu(GlobalContext* globalCtx, Gfx* dlist) {
    Gfx* dl;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    dl = POLY_XLU_DISP;

    gSPDisplayList(&dl[0], &sSetupDL[6 * 0x19]);
    gSPMatrix(&dl[1], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(&dl[2], dlist);

    POLY_XLU_DISP = &dl[3];

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
