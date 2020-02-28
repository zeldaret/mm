#include <ultra64.h>
#include <global.h>

FaultDrawer* faultDrawContext = &faultDrawContextStruct;
FaultDrawer faultDrawContextInit = {
    (u16*)0x803DA800, // fb - TODO map out buffers in this region and avoid hard-coded pointer
    320, 240, // w, h
    16, 223, // yStart, yEnd
    22, 297,// xStart, xEnd
    0xFFFF, 0x0000, // foreColor, backColor
    22, 16, // cursorX, cursorY
    (u32*)&faultDrawFont, // font
    8, 8, 0, 0, // charW, charH, charWPad, charHPad
    { // printColors
        0x0001, 0xF801, 0x07C1, 0xFFC1,
        0x003F, 0xF83F, 0x07FF, 0xFFFF,
        0x7BDF, 0xB5AD
    },
    0, // escCode
    0, // osSyncPrintfEnabled
    NULL, // inputCallback
};

void FaultDrawer_SetOsSyncPrintfEnabled(u32 enabled) {
    faultDrawContext->osSyncPrintfEnabled = enabled;
}


#ifdef NON_MATCHING
//This function needs a lot of work
void FaultDrawer_DrawRecImpl(s32 xstart, s32 ystart, s32 xend, s32 yend, u16 color) {
    s32 x;
    s32 y;
    u16* fb;
    if (faultDrawContext->w - xstart > 0 && faultDrawContext->h - ystart > 0) {
        for (y = 0; y < yend - ystart + 1; y++) {
            fb = &faultDrawContext->fb[faultDrawContext->w * y];
            for (x = 0; x < xend - xstart + 1; x++) {
                *fb++ = color;
            }
        }

        osWritebackDCacheAll();
    }
}
#else
GLOBAL_ASM("./asm/non_matchings/fault_drawer/FaultDrawer_DrawRecImpl.asm")
#endif

GLOBAL_ASM("./asm/non_matchings/fault_drawer/FaultDrawer_DrawChar.asm")

s32 FaultDrawer_ColorToPrintColor(u16 color) {
    s32 i;
    for (i = 0; i < 10; i++) {
        if (color == faultDrawContext->printColors[i]) {
            return i;
        }
    }
    return -1;
}

void FaultDrawer_UpdatePrintColor() {
    s32 idx;
    if (faultDrawContext->osSyncPrintfEnabled) {
        Fault_Log(D_80099050);
        idx = FaultDrawer_ColorToPrintColor(faultDrawContext->foreColor);
        if (idx >= 0 && idx < 8) {
            Fault_Log(D_80099054, idx);
        }
        idx = FaultDrawer_ColorToPrintColor(faultDrawContext->backColor);
        if (idx >= 0 && idx < 8) {
            Fault_Log(D_8009905C, idx);
        }
    }
}

void FaultDrawer_SetForeColor(u16 color) {
    faultDrawContext->foreColor = color;
    FaultDrawer_UpdatePrintColor();
}

void FaultDrawer_SetBackColor(u16 color) {
    faultDrawContext->backColor = color;
    FaultDrawer_UpdatePrintColor();
}

void FaultDrawer_SetFontColor(u16 color) {
    FaultDrawer_SetForeColor((u16)(color | 1)); //force alpha to be set
}

void FaultDrawer_SetCharPad(s8 padW, s8 padH) {
    faultDrawContext->charWPad = padW;
    faultDrawContext->charHPad = padH;
}

void FaultDrawer_SetCursor(s32 x, s32 y) {
    if (faultDrawContext->osSyncPrintfEnabled) {
        Fault_Log(D_80099064, (y - faultDrawContext->yStart) / (faultDrawContext->charH + faultDrawContext->charHPad), (x - faultDrawContext->xStart) / (faultDrawContext->charW + faultDrawContext->charWPad));
    }
    faultDrawContext->cursorX = x;
    faultDrawContext->cursorY = y;
}

void FaultDrawer_FillScreen() {
    if (faultDrawContext->osSyncPrintfEnabled) {
        Fault_Log(D_80099070);
    }

    FaultDrawer_DrawRecImpl(faultDrawContext->xStart, faultDrawContext->yStart, faultDrawContext->xEnd, faultDrawContext->yEnd, faultDrawContext->backColor | 1);
    FaultDrawer_SetCursor(faultDrawContext->xStart, faultDrawContext->yStart);
}

GLOBAL_ASM("./asm/non_matchings/fault_drawer/FaultDrawer_FormatStringFunc.asm")

void FaultDrawer_VPrintf(char* str, char* args) { //va_list
    _Printf((printf_func)FaultDrawer_FormatStringFunc, faultDrawContext, str, args);
}

GLOBAL_ASM("./asm/non_matchings/fault_drawer/FaultDrawer_Printf.asm")

GLOBAL_ASM("./asm/non_matchings/fault_drawer/FaultDrawer_DrawText.asm")

void FaultDrawer_SetDrawerFB(void* fb, u16 w, u16 h) {
    faultDrawContext->fb = (u16*)fb;
    faultDrawContext->w = w;
    faultDrawContext->h = h;
}

void FaultDrawer_SetInputCallback(void(*callback)()) {
    faultDrawContext->inputCallback = callback;
}

void FaultDrawer_Init() {
    faultDrawContext = &faultDrawContextStruct;
    _bcopy(&faultDrawContextInit, faultDrawContext, sizeof(FaultDrawer));
    faultDrawContext->fb = (u16*)((osMemSize | 0x80000000) - 0x25800);
}

