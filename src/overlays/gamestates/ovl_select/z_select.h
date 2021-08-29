#ifndef _Z64_SELECT_H_
#define _Z64_SELECT_H_

#include "global.h"

void Select_Init(GameState* thisx);
void Select_Destroy(GameState* thisx);

typedef struct {
    /* 0x000 */ GameState state;
    /* 0x0A4 */ char unk_0A4[0x4];
    /* 0x0A8 */ View view;
    /* 0x210 */ UNK_TYPE4 unk_210;
    /* 0x214 */ UNK_TYPE4 unk_214;
    /* 0x218 */ UNK_TYPE4 unk_218;
    /* 0x21C */ UNK_TYPE4 unk_21C;
    /* 0x220 */ UNK_TYPE4 unk_220;
    /* 0x224 */ UNK_TYPE4 unk_224;
    /* 0x228 */ UNK_TYPE4 unk_228;
    /* 0x22C */ UNK_TYPE4 unk_22C;
    /* 0x230 */ UNK_TYPE4 unk_230;
    /* 0x234 */ UNK_TYPE4 unk_234;
    /* 0x238 */ UNK_TYPE4 unk_238;
    /* 0x23C */ UNK_TYPE4 unk_23C;
    /* 0x240 */ UNK_TYPE4 unk_240;
    /* 0x244 */ UNK_TYPE4 unk_244;
    /* 0x248 */ UNK_TYPE4 unk_248;
    /* 0x24C */ UNK_TYPE4 unk_24C;
    /* 0x250 */ UNK_TYPE4 unk_250;
    /* 0x254 */ UNK_TYPE4 unk_254;
    /* 0x258 */ UNK_TYPE4 unk_258;
    /* 0x25C */ UNK_TYPE4 unk_25C;
    /* 0x260 */ UNK_TYPE4 unk_260;
    /* 0x264 */ UNK_TYPE4 unk_264;
    /* 0x268 */ UNK_TYPE4 unk_268;
    /* 0x26C */ UNK_TYPE4 unk_26C;
    /* 0x270 */ UNK_TYPE4 unk_270;
    /* 0x274 */ UNK_TYPE4 unk_274;
    /* 0x278 */ UNK_TYPE4 unk_278;
    /* 0x27C */ UNK_TYPE4 unk_27C;
} SelectContext; // size = 0x280

#endif
