#ifndef Z64FONT_H
#define Z64FONT_H

#include "PR/ultratypes.h"
#include "stdint.h"

struct PlayState;

#define FONT_CHAR_TEX_WIDTH 16
#define FONT_CHAR_TEX_HEIGHT 16
//! TODO: Make this use `sizeof(AnyFontTextureSymbol)`
#define FONT_CHAR_TEX_SIZE ((16 * 16) / 2) // 16x16 I4 texture

// Font textures are loaded into here
typedef struct Font {
    /* 0x00000 */ union {
        u8 charBuf[2][FONT_CHAR_TEX_SIZE * 120];
        u64 force_structure_alignment_charTex;
    };
    /* 0x07800 */ union {
        u8 iconBuf[FONT_CHAR_TEX_SIZE];
        u64 force_structure_alignment_icon;
    };
    /* 0x07880 */ union {
        u8 fontBuf[FONT_CHAR_TEX_SIZE * 320];
        u64 force_structure_alignment_font;
    };
    /* 0x11880 */ union {
        char schar[1280]; // msgBuf
        u16 wchar[640];   // msgBufWide
        u64 force_structure_alignment_msg;
    } msgBuf;
    /* 0x11D80 */ uintptr_t messageStart;
    /* 0x11D84 */ uintptr_t messageEnd;
    /* 0x11D88 */ u8 unk_11D88; // current Char Buffer ?
} Font; // size = 0x11D90

void Font_LoadChar(struct PlayState* play, u16 codePointIndex, s32 offset);
void Font_LoadCharNES(struct PlayState* play, u8 codePointIndex, s32 offset);
void Font_LoadMessageBoxEndIcon(Font* font, u16 icon);
void Font_LoadOrderedFont(Font* font);

#endif
