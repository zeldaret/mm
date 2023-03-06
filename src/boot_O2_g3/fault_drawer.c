/**
 * @file fault_drawer.c
 *
 * Implements routines for drawing text with a fixed font directly to a framebuffer, used in displaying
 * the crash screen implemented by fault.c
 */

#include "fault.h"
#include "fault_internal.h"
#include "global.h"
#include "vt.h"

typedef struct {
    /* 0x00 */ u16* fb;
    /* 0x04 */ u16 w;
    /* 0x06 */ u16 h;
    /* 0x08 */ u16 yStart;
    /* 0x0A */ u16 yEnd;
    /* 0x0C */ u16 xStart;
    /* 0x0E */ u16 xEnd;
    /* 0x10 */ u16 foreColor;
    /* 0x12 */ u16 backColor;
    /* 0x14 */ u16 cursorX;
    /* 0x16 */ u16 cursorY;
    /* 0x18 */ const u32* fontData;
    /* 0x1C */ u8 charW;
    /* 0x1D */ u8 charH;
    /* 0x1E */ s8 charWPad;
    /* 0x1F */ s8 charHPad;
    /* 0x20 */ u16 printColors[10];
    /* 0x34 */ u8 escCode; // bool
    /* 0x35 */ u8 osSyncPrintfEnabled;
    /* 0x38 */ FaultDrawerCallback inputCallback;
} FaultDrawer; // size = 0x3C

extern const u32 sFaultDrawerFont[];

FaultDrawer sFaultDrawer;

FaultDrawer* sFaultDrawerRef = &sFaultDrawer;

#define FAULT_DRAWER_CURSOR_X 22
#define FAULT_DRAWER_CURSOR_Y 16

FaultDrawer sFaultDrawerDefault = {
    FAULT_FB_ADDRESS,                          // fb
    SCREEN_WIDTH,                              // w
    SCREEN_HEIGHT,                             // h
    FAULT_DRAWER_CURSOR_Y,                     // yStart
    SCREEN_HEIGHT - FAULT_DRAWER_CURSOR_Y - 1, // yEnd
    FAULT_DRAWER_CURSOR_X,                     // xStart
    SCREEN_WIDTH - FAULT_DRAWER_CURSOR_X - 1,  // xEnd
    GPACK_RGBA5551(255, 255, 255, 255),        // foreColor
    GPACK_RGBA5551(0, 0, 0, 0),                // backColor
    FAULT_DRAWER_CURSOR_X,                     // cursorX
    FAULT_DRAWER_CURSOR_Y,                     // cursorY
    sFaultDrawerFont,                          // fontData
    8,                                         // charW
    8,                                         // charH
    0,                                         // charWPad
    0,                                         // charHPad
    {
        // printColors
        GPACK_RGBA5551(0, 0, 0, 1),       // BLACK
        GPACK_RGBA5551(255, 0, 0, 1),     // RED
        GPACK_RGBA5551(0, 255, 0, 1),     // GREEN
        GPACK_RGBA5551(255, 255, 0, 1),   // YELLOW
        GPACK_RGBA5551(0, 0, 255, 1),     // BLUE
        GPACK_RGBA5551(255, 0, 255, 1),   // MAGENTA
        GPACK_RGBA5551(0, 255, 255, 1),   // CYAN
        GPACK_RGBA5551(255, 255, 255, 1), // WHITE
        GPACK_RGBA5551(120, 120, 120, 1), // DARK GRAY
        GPACK_RGBA5551(176, 176, 176, 1), // LIGHT GRAY
    },
    false, // escCode
    false, // osSyncPrintfEnabled
    NULL,  // inputCallback
};

//! TODO: Needs to be extracted
#pragma GLOBAL_ASM("asm/non_matchings/boot/fault_drawer/sFaultDrawerFont.s")

void FaultDrawer_SetOsSyncPrintfEnabled(u32 enabled) {
    sFaultDrawerRef->osSyncPrintfEnabled = enabled;
}

void FaultDrawer_DrawRecImpl(s32 xStart, s32 yStart, s32 xEnd, s32 yEnd, u16 color) {
    u16* fb;
    s32 x;
    s32 y;
    s32 xDiff = sFaultDrawerRef->w - xStart;
    s32 yDiff = sFaultDrawerRef->h - yStart;
    s32 xSize = xEnd - xStart + 1;
    s32 ySize = yEnd - yStart + 1;

    if (xDiff > 0 && yDiff > 0) {
        if (xDiff < xSize) {
            xSize = xDiff;
        }

        if (yDiff < ySize) {
            ySize = yDiff;
        }

        fb = sFaultDrawerRef->fb + sFaultDrawerRef->w * yStart + xStart;
        for (y = 0; y < ySize; y++) {
            for (x = 0; x < xSize; x++) {
                *fb++ = color;
            }
            fb += sFaultDrawerRef->w - xSize;
        }

        osWritebackDCacheAll();
    }
}

void FaultDrawer_DrawChar(char c) {
    s32 x;
    s32 y;
    u32 data;
    s32 cursorX = sFaultDrawerRef->cursorX;
    s32 cursorY = sFaultDrawerRef->cursorY;
    s32 shift = c % 4;
    const u32* dataPtr = &sFaultDrawerRef->fontData[(((c / 8) * 16) + ((c & 4) >> 2))];
    u16* fb = sFaultDrawerRef->fb + (sFaultDrawerRef->w * cursorY) + cursorX;

    if ((sFaultDrawerRef->xStart <= cursorX) && ((sFaultDrawerRef->charW + cursorX - 1) <= sFaultDrawerRef->xEnd) &&
        (sFaultDrawerRef->yStart <= cursorY) && ((sFaultDrawerRef->charH + cursorY - 1) <= sFaultDrawerRef->yEnd)) {
        for (y = 0; y < sFaultDrawerRef->charH; y++) {
            u32 mask = 0x10000000 << shift;

            data = *dataPtr;
            for (x = 0; x < sFaultDrawerRef->charW; x++) {
                if (mask & data) {
                    fb[x] = sFaultDrawerRef->foreColor;
                } else if (sFaultDrawerRef->backColor & 1) {
                    fb[x] = sFaultDrawerRef->backColor;
                }
                mask >>= 4;
            }
            fb += sFaultDrawerRef->w;
            dataPtr += 2;
        }
    }
}

s32 FaultDrawer_ColorToPrintColor(u16 color) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sFaultDrawerRef->printColors); i++) {
        if (color == sFaultDrawerRef->printColors[i]) {
            return i;
        }
    }
    return -1;
}

void FaultDrawer_UpdatePrintColor(void) {
    s32 idx;

    if (sFaultDrawerRef->osSyncPrintfEnabled) {
        osSyncPrintf(VT_RST);

        idx = FaultDrawer_ColorToPrintColor(sFaultDrawerRef->foreColor);
        if (idx >= 0 && idx < 8) {
            osSyncPrintf(VT_SGR("3%d"), idx);
        }

        idx = FaultDrawer_ColorToPrintColor(sFaultDrawerRef->backColor);
        if (idx >= 0 && idx < 8) {
            osSyncPrintf(VT_SGR("4%d"), idx);
        }
    }
}

void FaultDrawer_SetForeColor(u16 color) {
    sFaultDrawerRef->foreColor = color;
    FaultDrawer_UpdatePrintColor();
}

void FaultDrawer_SetBackColor(u16 color) {
    sFaultDrawerRef->backColor = color;
    FaultDrawer_UpdatePrintColor();
}

void FaultDrawer_SetFontColor(u16 color) {
    FaultDrawer_SetForeColor(color | 1); // force alpha to be set
}

void FaultDrawer_SetCharPad(s8 padW, s8 padH) {
    sFaultDrawerRef->charWPad = padW;
    sFaultDrawerRef->charHPad = padH;
}

void FaultDrawer_SetCursor(s32 x, s32 y) {
    if (sFaultDrawerRef->osSyncPrintfEnabled) {
        osSyncPrintf(VT_CUP("%d", "%d"),
                     (y - sFaultDrawerRef->yStart) / (sFaultDrawerRef->charH + sFaultDrawerRef->charHPad),
                     (x - sFaultDrawerRef->xStart) / (sFaultDrawerRef->charW + sFaultDrawerRef->charWPad));
    }
    sFaultDrawerRef->cursorX = x;
    sFaultDrawerRef->cursorY = y;
}

void FaultDrawer_FillScreen() {
    if (sFaultDrawerRef->osSyncPrintfEnabled) {
        osSyncPrintf(VT_CLS);
    }

    FaultDrawer_DrawRecImpl(sFaultDrawerRef->xStart, sFaultDrawerRef->yStart, sFaultDrawerRef->xEnd,
                            sFaultDrawerRef->yEnd, sFaultDrawerRef->backColor | 1);
    FaultDrawer_SetCursor(sFaultDrawerRef->xStart, sFaultDrawerRef->yStart);
}

void* FaultDrawer_FormatStringFunc(void* arg, const char* str, size_t count) {
    for (; count != 0; count--, str++) {
        if (sFaultDrawerRef->escCode) {
            sFaultDrawerRef->escCode = false;
            if (*str >= '1' && *str <= '9') {
                FaultDrawer_SetForeColor(sFaultDrawerRef->printColors[*str - '0']);
            }
        } else {
            switch (*str) {
                case '\n':
                    if (sFaultDrawerRef->osSyncPrintfEnabled) {
                        osSyncPrintf("\n");
                    }

                    sFaultDrawerRef->cursorX = sFaultDrawerRef->w;
                    break;

                case FAULT_ESC:
                    sFaultDrawerRef->escCode = true;
                    break;

                default:
                    if (sFaultDrawerRef->osSyncPrintfEnabled) {
                        osSyncPrintf("%c", *str);
                    }

                    FaultDrawer_DrawChar(*str);
                    sFaultDrawerRef->cursorX += sFaultDrawerRef->charW + sFaultDrawerRef->charWPad;
            }
        }

        if (sFaultDrawerRef->cursorX >= (sFaultDrawerRef->xEnd - sFaultDrawerRef->charW)) {
            sFaultDrawerRef->cursorX = sFaultDrawerRef->xStart;
            sFaultDrawerRef->cursorY += sFaultDrawerRef->charH + sFaultDrawerRef->charHPad;
            if (sFaultDrawerRef->yEnd - sFaultDrawerRef->charH <= sFaultDrawerRef->cursorY) {
                if (sFaultDrawerRef->inputCallback != NULL) {
                    sFaultDrawerRef->inputCallback();
                    FaultDrawer_FillScreen();
                }
                sFaultDrawerRef->cursorY = sFaultDrawerRef->yStart;
            }
        }
    }

    osWritebackDCacheAll();

    return arg;
}

const char D_80099080[] = "(null)";

s32 FaultDrawer_VPrintf(const char* fmt, va_list ap) {
    return _Printf(FaultDrawer_FormatStringFunc, sFaultDrawerRef, fmt, ap);
}

s32 FaultDrawer_Printf(const char* fmt, ...) {
    s32 ret;
    va_list args;

    va_start(args, fmt);

    ret = FaultDrawer_VPrintf(fmt, args);

    va_end(args);

    return ret;
}

void FaultDrawer_DrawText(s32 x, s32 y, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    FaultDrawer_SetCursor(x, y);
    FaultDrawer_VPrintf(fmt, args);

    va_end(args);
}

void FaultDrawer_SetDrawerFB(void* fb, u16 w, u16 h) {
    sFaultDrawerRef->fb = fb;
    sFaultDrawerRef->w = w;
    sFaultDrawerRef->h = h;
}

void FaultDrawer_SetInputCallback(FaultDrawerCallback callback) {
    sFaultDrawerRef->inputCallback = callback;
}

void FaultDrawer_Init() {
    sFaultDrawerRef = &sFaultDrawer;
    bcopy(&sFaultDrawerDefault, sFaultDrawerRef, sizeof(FaultDrawer));
    sFaultDrawerRef->fb = (u16*)(PHYS_TO_K0(osMemSize) - SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(u16));
}
