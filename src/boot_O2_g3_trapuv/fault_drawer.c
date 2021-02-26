#include <ultra64.h>
#include <global.h>

FaultDrawer* sFaultDrawContext = &sFaultDrawerStruct;
FaultDrawer sFaultDrawerDefault = {
    (u16*)0x803DA800, // fb - TODO map out buffers in this region and avoid hard-coded pointer
    320,
    240, // w, h
    16,
    223, // yStart, yEnd
    22,
    297, // xStart, xEnd
    0xFFFF,
    0x0000, // foreColor, backColor
    22,
    16,                   // cursorX, cursorY
    (u32*)&faultDrawFont, // font
    8,
    8,
    0,
    0, // charW, charH, charWPad, charHPad
    {  // printColors
      0x0001, 0xF801, 0x07C1, 0xFFC1, 0x003F, 0xF83F, 0x07FF, 0xFFFF, 0x7BDF, 0xB5AD },
    0,    // escCode
    0,    // osSyncPrintfEnabled
    NULL, // inputCallback
};

void FaultDrawer_SetOsSyncPrintfEnabled(u32 enabled) {
    sFaultDrawContext->osSyncPrintfEnabled = enabled;
}

#ifdef NON_MATCHING
// This function needs a lot of work
void FaultDrawer_DrawRecImpl(s32 xstart, s32 ystart, s32 xend, s32 yend, u16 color) {
    s32 x;
    s32 y;
    u16* fb;
    if (sFaultDrawContext->w - xstart > 0 && sFaultDrawContext->h - ystart > 0) {
        for (y = 0; y < yend - ystart + 1; y++) {
            fb = &sFaultDrawContext->fb[sFaultDrawContext->w * y];
            for (x = 0; x < xend - xstart + 1; x++) {
                *fb++ = color;
            }
        }

        osWritebackDCacheAll();
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/fault_drawer/FaultDrawer_DrawRecImpl.asm")
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/fault_drawer/FaultDrawer_DrawChar.asm")

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
    FaultDrawer_SetForeColor((u16)(color | 1)); // force alpha to be set
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

#pragma GLOBAL_ASM("./asm/non_matchings/fault_drawer/FaultDrawer_FormatStringFunc.asm")

void FaultDrawer_VPrintf(char* str, char* args) { // va_list
    _Printf((printf_func)FaultDrawer_FormatStringFunc, sFaultDrawContext, str, args);
}

#pragma GLOBAL_ASM("./asm/non_matchings/fault_drawer/FaultDrawer_Printf.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/fault_drawer/FaultDrawer_DrawText.asm")

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
    _bcopy(&sFaultDrawerDefault, sFaultDrawContext, sizeof(FaultDrawer));
    sFaultDrawContext->fb = (u16*)((osMemSize | 0x80000000) - 0x25800);
}
