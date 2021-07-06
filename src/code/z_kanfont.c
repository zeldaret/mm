#include <ultra64.h>
#include <global.h>

// stubbed in NTSC-U
void Font_LoadChar(GlobalContext* globalCtx, u16 codePointIndex, s32 offset) {
}

void Font_LoadCharNES(GlobalContext* globalCtx, u8 codePointIndex, s32 offset) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    Font* font = &msgCtx->font;

    DmaMgr_SendRequest0(&font->charBuf[font->unk_11D88][offset],
                        &_nes_font_staticSegmentRomStart[(codePointIndex - ' ') * FONT_CHAR_TEX_SIZE],
                        FONT_CHAR_TEX_SIZE);
}

void Font_LoadMessageBoxEndIcon(Font* font, u16 icon) {
    DmaMgr_SendRequest0(&font->iconBuf, &_message_staticSegmentRomStart[5 * 0x1000 + icon * FONT_CHAR_TEX_SIZE],
                        FONT_CHAR_TEX_SIZE);
}

static char sFontOrdering[] = "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19"
                              "!\"#$%&\'()*+,-./0123456789:ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                              "\x00\x0D\x0E\x1A"
                              "afjmosvwxyz{|}~"
                              "\x7F\x80\x81\x84\x86\x87\x88\x89\x8A\x8B\x8C";

void Font_LoadOrderedFont(Font* font) {
    u32 loadOffset;
    s32 codePointIndex = 0;
    u8* writeLocation;

    while (1) {
        writeLocation = &font->fontBuf[codePointIndex * FONT_CHAR_TEX_SIZE];
        loadOffset = sFontOrdering[codePointIndex] * FONT_CHAR_TEX_SIZE;
        if (sFontOrdering[codePointIndex] == 0) {
            loadOffset = 0;
        }
        // UB to convert pointer to u32
        DmaMgr_SendRequest0(writeLocation, (u32)_nes_font_staticSegmentRomStart + loadOffset, FONT_CHAR_TEX_SIZE);
        if (sFontOrdering[codePointIndex] == 0x8C) {
            break;
        }
        codePointIndex++;
    }
}
