/**
 * File: z_shrink_window.c
 * Description: Draws black top/bottom/side borders on the viewing window (e.g. Z-targeting, talking to NPC)
 */
#include "prevent_bss_reordering.h"
#include "global.h"

ShrinkWindowContext gShrinkWindowContext;
ShrinkWindowContext* gShrinkWindowContextPtr;

void ShrinkWindow_SetLetterboxTarget(s32 target) {
    gShrinkWindowContextPtr->letterboxTarget = target;
}

s32 ShrinkWindow_GetLetterboxTarget(void) {
    return gShrinkWindowContextPtr->letterboxTarget;
}

void ShrinkWindow_SetLetterboxMagnitude(s32 magnitude) {
    gShrinkWindowContextPtr->letterboxMagnitude = magnitude;
}

s32 ShrinkWindow_GetLetterboxMagnitude(void) {
    return gShrinkWindowContextPtr->letterboxMagnitude;
}

void ShrinkWindow_SetPillarboxTarget(s32 target) {
    gShrinkWindowContextPtr->pillarboxTarget = target;
}

s32 ShrinkWindow_GetPillarboxTarget(void) {
    return gShrinkWindowContextPtr->pillarboxTarget;
}

void ShrinkWindow_SetPillarboxMagnitude(s32 magnitude) {
    gShrinkWindowContextPtr->pillarboxMagnitude = magnitude;
}

s32 ShrinkWindow_GetPillarboxMagnitude(void) {
    return gShrinkWindowContextPtr->pillarboxMagnitude;
}

void ShrinkWindow_Init(void) {
    gShrinkWindowContextPtr = &gShrinkWindowContext;
    bzero(gShrinkWindowContextPtr, sizeof(gShrinkWindowContext));
}

void ShrinkWindow_Destroy(void) {
    gShrinkWindowContextPtr = NULL;
}

void ShrinkWindow_Update(s32 framerateDivisor) {
    s32 step = ((framerateDivisor == 3) ? 10 : 30 / framerateDivisor);
    s32 nextMagnitude;

    nextMagnitude = gShrinkWindowContextPtr->letterboxMagnitude;
    Math_StepToIGet(&nextMagnitude, gShrinkWindowContextPtr->letterboxTarget, step);
    gShrinkWindowContextPtr->letterboxMagnitude = nextMagnitude;

    nextMagnitude = gShrinkWindowContextPtr->pillarboxMagnitude;
    Math_StepToIGet(&nextMagnitude, gShrinkWindowContextPtr->pillarboxTarget, step);
    gShrinkWindowContextPtr->pillarboxMagnitude = nextMagnitude;
}

void ShrinkWindow_Draw(GraphicsContext* gfxCtx) {
    Gfx* gfx;
    s8 letterboxMagnitude = gShrinkWindowContextPtr->letterboxMagnitude;
    s8 pillarboxMagnitude = gShrinkWindowContextPtr->pillarboxMagnitude;

    if (letterboxMagnitude > 0) {
        OPEN_DISPS(gfxCtx);

        gfx = OVERLAY_DISP;

        gDPPipeSync(gfx++);
        gDPSetCycleType(gfx++, G_CYC_FILL);
        gDPSetRenderMode(gfx++, G_RM_NOOP, G_RM_NOOP2);
        gDPSetFillColor(gfx++, (GPACK_RGBA5551(0, 0, 0, 1) << 16) | GPACK_RGBA5551(0, 0, 0, 1));
        gDPFillRectangle(gfx++, 0, 0, gScreenWidth - 1, letterboxMagnitude - 1);
        gDPFillRectangle(gfx++, 0, gScreenHeight - letterboxMagnitude, gScreenWidth - 1, gScreenHeight - 1);

        gDPPipeSync(gfx++);
        gDPSetCycleType(gfx++, G_CYC_1CYCLE);
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 0);
        gDPFillRectangle(gfx++, 0, letterboxMagnitude, gScreenWidth, letterboxMagnitude + 1);
        gDPFillRectangle(gfx++, 0, gScreenHeight - letterboxMagnitude - 1, gScreenWidth,
                         gScreenHeight - letterboxMagnitude);

        gDPPipeSync(gfx++);
        OVERLAY_DISP = gfx++;

        CLOSE_DISPS(gfxCtx);
    }
    if (pillarboxMagnitude > 0) {
        OPEN_DISPS(gfxCtx);

        gfx = OVERLAY_DISP;

        gDPPipeSync(gfx++);
        gDPSetCycleType(gfx++, G_CYC_FILL);
        gDPSetRenderMode(gfx++, G_RM_NOOP, G_RM_NOOP2);
        gDPSetFillColor(gfx++, (GPACK_RGBA5551(0, 0, 0, 1) << 16) | GPACK_RGBA5551(0, 0, 0, 1));

        gDPFillRectangle(gfx++, 0, 0, pillarboxMagnitude - 1, gScreenHeight - 1);
        gDPFillRectangle(gfx++, gScreenWidth - pillarboxMagnitude, 0, gScreenWidth - 1, gScreenHeight - 1);

        gDPPipeSync(gfx++);
        gDPSetCycleType(gfx++, G_CYC_1CYCLE);
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 0);

        gDPFillRectangle(gfx++, pillarboxMagnitude, 0, pillarboxMagnitude + 2, gScreenHeight);
        gDPFillRectangle(gfx++, gScreenWidth - pillarboxMagnitude - 2, 0, gScreenWidth - pillarboxMagnitude,
                         gScreenHeight);

        gDPPipeSync(gfx++);
        OVERLAY_DISP = gfx++;

        CLOSE_DISPS(gfxCtx);
    }
}
