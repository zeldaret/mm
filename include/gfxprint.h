#ifndef GFXPRINT_H
#define GFXPRINT_H

#include "color.h"
#include "PR/gbi.h"
#include "PR/ultratypes.h"
#include "xstdio.h"

#define GFXP_UNUSED "\x8E"
#define GFXP_UNUSED_CHAR 0x8E
#define GFXP_HIRAGANA "\x8D"
#define GFXP_HIRAGANA_CHAR 0x8D
#define GFXP_KATAKANA "\x8C"
#define GFXP_KATAKANA_CHAR 0x8C
#define GFXP_RAINBOW_ON "\x8B"
#define GFXP_RAINBOW_ON_CHAR 0x8B
#define GFXP_RAINBOW_OFF "\x8A"
#define GFXP_RAINBOW_OFF_CHAR 0x8A

typedef struct GfxPrint {
    /* 0x00 */ PrintCallback callback;
    /* 0x04 */ Gfx* dList;
    /* 0x08 */ u16 posX;
    /* 0x0A */ u16 posY;
    /* 0x0C */ u16 baseX;
    /* 0x0E */ u8 baseY;
    /* 0x0F */ u8 flags;
    /* 0x10 */ Color_RGBA8_u32 color;
    /* 0x14 */ UNK_TYPE1 unk_14[0x1C]; // unused
} GfxPrint; // size = 0x30

void GfxPrint_Setup(GfxPrint* printer);
void GfxPrint_SetColor(GfxPrint* printer, u32 r, u32 g, u32 b, u32 a);
void GfxPrint_SetPosPx(GfxPrint* printer, s32 x, s32 y);
void GfxPrint_SetPos(GfxPrint* printer, s32 x, s32 y);
void GfxPrint_SetBasePosPx(GfxPrint* printer, s32 x, s32 y);
void GfxPrint_PrintCharImpl(GfxPrint* printer, u8 c);
void GfxPrint_PrintChar(GfxPrint* printer, u8 c);
void GfxPrint_PrintStringWithSize(GfxPrint* printer, const void* buffer, size_t charSize, size_t charCount);
void GfxPrint_PrintString(GfxPrint* printer, const char* str);
void* GfxPrint_Callback(void* arg, const char* str, size_t size);
void GfxPrint_Init(GfxPrint* printer);
void GfxPrint_Destroy(GfxPrint* printer);
void GfxPrint_Open(GfxPrint* printer, Gfx* dList);
Gfx* GfxPrint_Close(GfxPrint* printer);
s32 GfxPrint_VPrintf(GfxPrint* printer, const char* fmt, va_list args);
s32 GfxPrint_Printf(GfxPrint* printer, const char* fmt, ...);

#endif
