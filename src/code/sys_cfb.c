#include "global.h"

OSViMode sNotebookViMode;
void* gFramebuffers[2];
OSViMode* gActiveViMode;
u16* gZBufferPtr;
void* gWorkBuffer;
u64* gGfxSPTaskOutputBufferPtr;
void* gGfxSPTaskOutputBufferSize; // Actually points to the end of the task buffer

void* sCfbLoRes1;
void* sCfbLoRes0;
u16 (*gZBufferLoRes)[SCREEN_WIDTH * SCREEN_HEIGHT];
u16 (*gWorkBufferLoRes)[SCREEN_WIDTH * SCREEN_HEIGHT];
u64 (*gGfxSPTaskOutputBufferLoRes)[0x3000];
void* gGfxSPTaskOutputBufferSizeLoRes; // Actually points to the end of the task buffer

void* sCfbHiRes1;
void* sCfbHiRes0;
u16 (*gZBufferHiRes)[SCREEN_WIDTH_NOTEBOOK * SCREEN_HEIGHT_NOTEBOOK];
u16 (*gWorkBufferHiRes)[SCREEN_WIDTH_NOTEBOOK * SCREEN_HEIGHT_NOTEBOOK];
u64 (*gGfxSPTaskOutputBufferHiRes)[0x3000];
void* gGfxSPTaskOutputBufferSizeHiRes; // Actually points to the end of the task buffer

s16 gCfbWidth;
s16 gCfbHeight;
s16 gCfbLeftAdjust;
s16 gCfbUpperAdjust;

u8 gSysCfbHiResEnabled;

void SysCfb_SetLoResMode(void) {
    gFramebuffers[1] = sCfbLoRes1;
    gFramebuffers[0] = sCfbLoRes0;
    gZBufferPtr = *gZBufferLoRes;
    gWorkBuffer = gWorkBufferLoRes;
    gGfxSPTaskOutputBufferPtr = *gGfxSPTaskOutputBufferLoRes;
    gGfxSPTaskOutputBufferSize = gGfxSPTaskOutputBufferSizeLoRes;
    gCfbWidth = SCREEN_WIDTH;
    gCfbHeight = SCREEN_HEIGHT;
    gCfbLeftAdjust = 0;
    gCfbUpperAdjust = 0;
    gSysCfbHiResEnabled = false;
    gScreenWidth = gCfbWidth;
    gScreenHeight = gCfbHeight;
    gActiveViMode = &osViModeNtscLan1;
}

void SysCfb_SetHiResMode(void) {
    gFramebuffers[1] = sCfbHiRes1;
    gFramebuffers[0] = sCfbHiRes0;
    gZBufferPtr = *gZBufferHiRes;
    gWorkBuffer = gWorkBufferHiRes;
    gGfxSPTaskOutputBufferPtr = *gGfxSPTaskOutputBufferHiRes;
    gGfxSPTaskOutputBufferSize = gGfxSPTaskOutputBufferSizeHiRes;
    if (1) {}
    gCfbWidth = SCREEN_WIDTH_NOTEBOOK;
    gCfbHeight = SCREEN_HEIGHT_NOTEBOOK;
    gCfbLeftAdjust = 30;
    gCfbUpperAdjust = 10;
    gScreenWidth = gCfbWidth;
    gScreenHeight = gCfbHeight;
    if ((gCfbWidth == SCREEN_WIDTH_HIRES) && (gCfbHeight == SCREEN_HEIGHT_HIRES)) {
        gActiveViMode = &osViModeNtscHpf1;
    } else {
        s32 rightAdjust;
        s32 lowerAdjust;

    //! FAKE:
    l1:
        rightAdjust = gCfbWidth - 610;
        lowerAdjust = gCfbHeight - 470;
        ViMode_Configure(&sNotebookViMode, -1, osTvType, 0, 1, 0, 1, gCfbWidth, gCfbHeight, 30, rightAdjust, 10,
                         lowerAdjust);
        gActiveViMode = &sNotebookViMode;
    }
    gSysCfbHiResEnabled = true;
}

//! FAKE:
extern u16 gFramebuffer1_[SCREEN_WIDTH_NOTEBOOK][SCREEN_HEIGHT_NOTEBOOK];
void SysCfb_Init(void) {
    sCfbLoRes1 = gFramebuffer1;
    sCfbLoRes0 = gFramebuffer0;
    sCfbHiRes1 = gFramebuffer1_;
    sCfbHiRes0 = D_80780000;
    SysCfb_SetLoResMode();
}

// Unused
void SysCfb_Reset(void) {
    gFramebuffers[0] = NULL;
    gFramebuffers[1] = NULL;
}

void* SysCfb_GetFramebuffer(s32 index) {
    if (index < 2) {
        return gFramebuffers[index];
    }
    return NULL;
}

u16* SysCfb_GetZBuffer(void) {
    return gZBufferPtr;
}

void* SysCfb_GetWorkBuffer(void) {
    return gWorkBuffer;
}

u16 SysCfb_GetZBufferPixel(s32 x, s32 y) {
    u16* zBuff = SysCfb_GetZBuffer();
    u16 val;

    if (zBuff != NULL) {
        val = (&zBuff[x])[y * gCfbWidth];
    } else {
        val = 0;
    }
    return val;
}

s32 SysCfb_GetZBufferInt(s32 x, s32 y) {
    return Environment_ZBufValToFixedPoint(SysCfb_GetZBufferPixel(x, y) << 2) >> 3;
}
