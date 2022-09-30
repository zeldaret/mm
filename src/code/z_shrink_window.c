/**
 * File: z_shrink_window.c
 * Description: Draws black top/bottom/side borders on the viewing window (e.g. Z-targeting, talking to NPC)
 */
#include "prevent_bss_reordering.h"
#include "global.h"
#include "z64shrink_window.h"

typedef struct {
    /* 0x0 */ s8 letterboxTarget;
    /* 0x1 */ s8 letterboxSize;
    /* 0x2 */ s8 pillarboxTarget;
    /* 0x3 */ s8 pillarboxSize;
} ShrinkWindow; // size = 0x4

ShrinkWindow gShrinkWindow;
ShrinkWindow* gShrinkWindowPtr;

void ShrinkWindow_Letterbox_SetSizeTarget(s32 target) {
    gShrinkWindowPtr->letterboxTarget = target;
}

s32 ShrinkWindow_Letterbox_GetSizeTarget(void) {
    return gShrinkWindowPtr->letterboxTarget;
}

void ShrinkWindow_Letterbox_SetSize(s32 size) {
    gShrinkWindowPtr->letterboxSize = size;
}

s32 ShrinkWindow_Letterbox_GetSize(void) {
    return gShrinkWindowPtr->letterboxSize;
}

void ShrinkWindow_Pillarbox_SetSizeTarget(s32 target) {
    gShrinkWindowPtr->pillarboxTarget = target;
}

s32 ShrinkWindow_Pillarbox_GetSizeTarget(void) {
    return gShrinkWindowPtr->pillarboxTarget;
}

void ShrinkWindow_Pillarbox_SetSize(s32 size) {
    gShrinkWindowPtr->pillarboxSize = size;
}

s32 ShrinkWindow_Pillarbox_GetSize(void) {
    return gShrinkWindowPtr->pillarboxSize;
}

void ShrinkWindow_Init(void) {
    gShrinkWindowPtr = &gShrinkWindow;
    bzero(gShrinkWindowPtr, sizeof(gShrinkWindow));
}

void ShrinkWindow_Destroy(void) {
    gShrinkWindowPtr = NULL;
}

void ShrinkWindow_Update(s32 framerateDivisor) {
    s32 step = (framerateDivisor == 3) ? 10 : (30 / framerateDivisor);
    s32 nextSize;

    nextSize = gShrinkWindowPtr->letterboxSize;
    Math_StepToIGet(&nextSize, gShrinkWindowPtr->letterboxTarget, step);
    gShrinkWindowPtr->letterboxSize = nextSize;

    nextSize = gShrinkWindowPtr->pillarboxSize;
    Math_StepToIGet(&nextSize, gShrinkWindowPtr->pillarboxTarget, step);
    gShrinkWindowPtr->pillarboxSize = nextSize;
}

void ShrinkWindow_Draw(GraphicsContext* gfxCtx) {
    Gfx* gfx;
    s8 letterboxSize = gShrinkWindowPtr->letterboxSize;
    s8 pillarboxSize = gShrinkWindowPtr->pillarboxSize;

    if (letterboxSize > 0) {
        OPEN_DISPS(gfxCtx);

        gfx = OVERLAY_DISP;

        gDPPipeSync(gfx++);
        gDPSetCycleType(gfx++, G_CYC_FILL);
        gDPSetRenderMode(gfx++, G_RM_NOOP, G_RM_NOOP2);
        gDPSetFillColor(gfx++, (GPACK_RGBA5551(0, 0, 0, 1) << 16) | GPACK_RGBA5551(0, 0, 0, 1));
        gDPFillRectangle(gfx++, 0, 0, gScreenWidth - 1, letterboxSize - 1);
        gDPFillRectangle(gfx++, 0, gScreenHeight - letterboxSize, gScreenWidth - 1, gScreenHeight - 1);

        gDPPipeSync(gfx++);
        gDPSetCycleType(gfx++, G_CYC_1CYCLE);
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 0);
        gDPFillRectangle(gfx++, 0, letterboxSize, gScreenWidth, letterboxSize + 1);
        gDPFillRectangle(gfx++, 0, gScreenHeight - letterboxSize - 1, gScreenWidth, gScreenHeight - letterboxSize);

        gDPPipeSync(gfx++);
        OVERLAY_DISP = gfx++;

        CLOSE_DISPS(gfxCtx);
    }

    if (pillarboxSize > 0) {
        OPEN_DISPS(gfxCtx);

        gfx = OVERLAY_DISP;

        gDPPipeSync(gfx++);
        gDPSetCycleType(gfx++, G_CYC_FILL);
        gDPSetRenderMode(gfx++, G_RM_NOOP, G_RM_NOOP2);
        gDPSetFillColor(gfx++, (GPACK_RGBA5551(0, 0, 0, 1) << 16) | GPACK_RGBA5551(0, 0, 0, 1));

        gDPFillRectangle(gfx++, 0, 0, pillarboxSize - 1, gScreenHeight - 1);
        gDPFillRectangle(gfx++, gScreenWidth - pillarboxSize, 0, gScreenWidth - 1, gScreenHeight - 1);

        gDPPipeSync(gfx++);
        gDPSetCycleType(gfx++, G_CYC_1CYCLE);
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 0);

        gDPFillRectangle(gfx++, pillarboxSize, 0, pillarboxSize + 2, gScreenHeight);
        gDPFillRectangle(gfx++, gScreenWidth - pillarboxSize - 2, 0, gScreenWidth - pillarboxSize, gScreenHeight);

        gDPPipeSync(gfx++);
        OVERLAY_DISP = gfx++;

        CLOSE_DISPS(gfxCtx);
    }
}
