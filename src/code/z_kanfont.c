#include <ultra64.h>
#include <global.h>

void Kanfont_Nop800F4F40(GlobalContext* ctxt, UNK_TYPE param_2, UNK_TYPE param_3) {}

void Kanfont_LoadAsciiChar(GlobalContext* ctxt, u8 character, s32 iParm3) {
    // UB to convert pointer to u32
    DmaMgr_SendRequest0((void*)((u32)&ctxt->msgCtx.font.unk0[(ctxt->msgCtx).unk11EF0] + iParm3),
        (u32)_nes_font_staticSegmentRomStart + character * 0x80 - 0x1000,
        0x80);
}

void Kanfont_LoadMessageBoxEnd(Font* font, u16 type) {
    // UB to convert pointer to u32
    DmaMgr_SendRequest0(&font->unk7800[0][0], type * 0x80 + (u32)_message_staticSegmentRomStart + 0x5000, 0x80);
}

void Kanfont_LoadOrderedFont(Font* font) {
    u32 loadOffset;
    s32 codePointIndex = 0;
    void* writeLocation;

    while (1) {
        writeLocation = &font->unk7800[codePointIndex + 1];
        loadOffset = kanfontOrdering[codePointIndex] * 128;
        if (kanfontOrdering[codePointIndex] == 0) {
            loadOffset = 0;
        }
        // UB to convert pointer to u32
        DmaMgr_SendRequest0(writeLocation, (u32)_nes_font_staticSegmentRomStart + loadOffset, 0x80);
        if (kanfontOrdering[codePointIndex] == 140) break;
        codePointIndex++;
    }
}
