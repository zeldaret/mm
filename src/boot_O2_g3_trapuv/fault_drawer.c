#include <ultra64.h>
#include <global.h>

FaultDrawer* sFaultDrawContext = &sFaultDrawerStruct;
FaultDrawer sFaultDrawerDefault = {
    (u16*)0x803DA800,                   // fb - TODO map out buffers in this region and avoid hard-coded pointer
    SCREEN_WIDTH,                       // w
    SCREEN_HEIGHT,                      // h
    16,                                 // yStart
    223,                                // yEnd
    22,                                 // xStart
    297,                                // xEnd
    GPACK_RGBA5551(255, 255, 255, 255), // foreColor
    GPACK_RGBA5551(0, 0, 0, 0),         // backColor
    22,                                 // cursorX
    16,                                 // cursorY
    (u32*)&sFaultDrawerFont,            // font
    8,                                  // charW
    8,                                  // charH
    0,                                  // charWPad
    0,                                  //  charHPad
    {
        // printColors
        GPACK_RGBA5551(0, 0, 0, 1),
        GPACK_RGBA5551(255, 0, 0, 1),
        GPACK_RGBA5551(0, 255, 0, 1),
        GPACK_RGBA5551(255, 255, 0, 1),
        GPACK_RGBA5551(0, 0, 255, 1),
        GPACK_RGBA5551(255, 0, 255, 1),
        GPACK_RGBA5551(0, 255, 255, 1),
        GPACK_RGBA5551(255, 255, 255, 1),
        GPACK_RGBA5551(120, 120, 120, 1),
        GPACK_RGBA5551(176, 176, 176, 1),
    },
    0,    // escCode
    0,    // osSyncPrintfEnabled
    NULL, // inputCallback
};

void FaultDrawer_SetOsSyncPrintfEnabled(u32 enabled) {
    sFaultDrawContext->osSyncPrintfEnabled = enabled;
}

void FaultDrawer_DrawRecImpl(s32 xStart, s32 yStart, s32 xEnd, s32 yEnd, u16 color) {
    u16* fb;
    s32 x, y;
    s32 xDiff = sFaultDrawContext->w - xStart;
    s32 yDiff = sFaultDrawContext->h - yStart;
    s32 xSize = xEnd - xStart + 1;
    s32 ySize = yEnd - yStart + 1;

    if (xDiff > 0 && yDiff > 0) {
        if (xDiff < xSize) {
            xSize = xDiff;
        }

        if (yDiff < ySize) {
            ySize = yDiff;
        }

        fb = sFaultDrawContext->fb + sFaultDrawContext->w * yStart + xStart;
        for (y = 0; y < ySize; y++) {
            for (x = 0; x < xSize; x++) {
                *fb++ = color;
            }
            fb += sFaultDrawContext->w - xSize;
        }

        osWritebackDCacheAll();
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/boot/fault_drawer/FaultDrawer_DrawChar.asm")

s32 FaultDrawer_ColorToPrintColor(u16 color) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (color == sFaultDrawContext->printColors[i]) {
            return i;
        }
    }
    return -1;
}

void FaultDrawer_UpdatePrintColor() {
    s32 idx;

    if (sFaultDrawContext->osSyncPrintfEnabled) {
        Fault_Log(D_80099050);
        idx = FaultDrawer_ColorToPrintColor(sFaultDrawContext->foreColor);
        if (idx >= 0 && idx < 8) {
            Fault_Log(D_80099054, idx);
        }
        idx = FaultDrawer_ColorToPrintColor(sFaultDrawContext->backColor);
        if (idx >= 0 && idx < 8) {
            Fault_Log(D_8009905C, idx);
        }
    }
}

void FaultDrawer_SetForeColor(u16 color) {
    sFaultDrawContext->foreColor = color;
    FaultDrawer_UpdatePrintColor();
}

void FaultDrawer_SetBackColor(u16 color) {
    sFaultDrawContext->backColor = color;
    FaultDrawer_UpdatePrintColor();
}

void FaultDrawer_SetFontColor(u16 color) {
    FaultDrawer_SetForeColor(color | 1); // force alpha to be set
}

void FaultDrawer_SetCharPad(s8 padW, s8 padH) {
    sFaultDrawContext->charWPad = padW;
    sFaultDrawContext->charHPad = padH;
}

void FaultDrawer_SetCursor(s32 x, s32 y) {
    if (sFaultDrawContext->osSyncPrintfEnabled) {
        Fault_Log(D_80099064,
                  (y - sFaultDrawContext->yStart) / (sFaultDrawContext->charH + sFaultDrawContext->charHPad),
                  (x - sFaultDrawContext->xStart) / (sFaultDrawContext->charW + sFaultDrawContext->charWPad));
    }
    sFaultDrawContext->cursorX = x;
    sFaultDrawContext->cursorY = y;
}

void FaultDrawer_FillScreen() {
    if (sFaultDrawContext->osSyncPrintfEnabled) {
        Fault_Log(D_80099070);
    }

    FaultDrawer_DrawRecImpl(sFaultDrawContext->xStart, sFaultDrawContext->yStart, sFaultDrawContext->xEnd,
                            sFaultDrawContext->yEnd, sFaultDrawContext->backColor | 1);
    FaultDrawer_SetCursor(sFaultDrawContext->xStart, sFaultDrawContext->yStart);
}

#pragma GLOBAL_ASM("./asm/non_matchings/boot/fault_drawer/FaultDrawer_FormatStringFunc.asm")

void FaultDrawer_VPrintf(const char* str, char* args) { // va_list
    _Printf((printf_func)FaultDrawer_FormatStringFunc, sFaultDrawContext, str, args);
}

void FaultDrawer_Printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    FaultDrawer_VPrintf(fmt, args);
}

void FaultDrawer_DrawText(s32 x, s32 y, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    FaultDrawer_SetCursor(x, y);
    FaultDrawer_VPrintf(fmt, args);
}

void FaultDrawer_SetDrawerFB(void* fb, u16 w, u16 h) {
    sFaultDrawContext->fb = (u16*)fb;
    sFaultDrawContext->w = w;
    sFaultDrawContext->h = h;
}

void FaultDrawer_SetInputCallback(void (*callback)()) {
    sFaultDrawContext->inputCallback = callback;
}

void FaultDrawer_Init() {
    sFaultDrawContext = &sFaultDrawerStruct;
    bcopy(&sFaultDrawerDefault, sFaultDrawContext, sizeof(FaultDrawer));
    sFaultDrawContext->fb = (u16*)((osMemSize | 0x80000000) - 0x25800);
}
