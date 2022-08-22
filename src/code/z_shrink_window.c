/**
 * File: z_shrink_window.c
 * Description: Draws black top/bottom/side borders on the viewing window (e.g. Z-targeting, talking to NPC)
 */
#include "prevent_bss_reordering.h"
#include "global.h"

typedef struct {
    /* 0x0 */ s8 letterboxTarget;
    /* 0x1 */ s8 letterboxSize;
    /* 0x2 */ s8 pillarboxTarget;
    /* 0x3 */ s8 pillarboxSize;
} ShrinkWindowContext; // size = 0x4

ShrinkWindowContext gShrinkWindowContext;
ShrinkWindowContext* gShrinkWindowContextPtr;

void Letterbox_SetSizeTarget(s32 target) {
    gShrinkWindowContextPtr->letterboxTarget = target;
}

s32 Letterbox_GetSizeTarget(void) {
    return gShrinkWindowContextPtr->letterboxTarget;
}

void Letterbox_SetSize(s32 size) {
    gShrinkWindowContextPtr->letterboxSize = size;
}

s32 Letterbox_GetSize(void) {
    return gShrinkWindowContextPtr->letterboxSize;
}

void Pillarbox_SetSizeTarget(s32 target) {
    gShrinkWindowContextPtr->pillarboxTarget = target;
}

s32 Pillarbox_GetSizeTarget(void) {
    return gShrinkWindowContextPtr->pillarboxTarget;
}

void Pillarbox_SetSize(s32 size) {
    gShrinkWindowContextPtr->pillarboxSize = size;
}

s32 Pillarbox_GetSize(void) {
    return gShrinkWindowContextPtr->pillarboxSize;
}

void ShrinkWindow_Init(void) {
    gShrinkWindowContextPtr = &gShrinkWindowContext;
    bzero(gShrinkWindowContextPtr, sizeof(gShrinkWindowContext));
}

void ShrinkWindow_Destroy(void) {
    gShrinkWindowContextPtr = NULL;
}

void ShrinkWindow_Update(s32 framerateDivisor) {
    s32 step = (framerateDivisor == 3) ? 10 : (30 / framerateDivisor);
    s32 nextSize;

    nextSize = gShrinkWindowContextPtr->letterboxSize;
    Math_StepToIGet(&nextSize, gShrinkWindowContextPtr->letterboxTarget, step);
    gShrinkWindowContextPtr->letterboxSize = nextSize;

    nextSize = gShrinkWindowContextPtr->pillarboxSize;
    Math_StepToIGet(&nextSize, gShrinkWindowContextPtr->pillarboxTarget, step);
    gShrinkWindowContextPtr->pillarboxSize = nextSize;
}

void ShrinkWindow_Draw(GraphicsContext* gfxCtx) {
    Gfx* gfx;
    s8 letterboxSize = gShrinkWindowContextPtr->letterboxSize;
    s8 pillarboxSize = gShrinkWindowContextPtr->pillarboxSize;

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
