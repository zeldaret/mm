#ifndef _Z64_DAYTELOP_H_
#define _Z64_DAYTELOP_H_

#include "global.h"

void Daytelop_Init(GameState* thisx);
void Daytelop_Destroy(GameState* thisx);

typedef struct {
    /* 0x000 */ GameState common;
    /* 0x0A4 */ void* daytelopStaticFile;
    /* 0x0A8 */ void* gameoverStaticFile;
    /* 0x0AC */ UNK_TYPE1 padAC[0x4];
    /* 0x0B0 */ View view;
    /* 0x218 */ UNK_TYPE1 pad218[0x28];
    /* 0x240 */ s16 transitionCountdown;
    /* 0x242 */ s16 unk_242; // state?
    /* 0x244 */ s16 alpha;
} DaytelopContext; // size = 0x248

#endif
