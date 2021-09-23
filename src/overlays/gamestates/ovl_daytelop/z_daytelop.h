#ifndef Z64_DAYTELOP_H
#define Z64_DAYTELOP_H

#include "global.h"

void Daytelop_Init(GameState* thisx);
void Daytelop_Destroy(GameState* thisx);

typedef struct {
    /* 0x000 */ GameState state;
    /* 0x0A4 */ void* daytelopStaticFile;
    /* 0x0A8 */ void* gameoverStaticFile;
    /* 0x0AC */ UNK_TYPE1 unk_AC[0x4];
    /* 0x0B0 */ View view;
    /* 0x218 */ UNK_TYPE1 unk_218[0x28];
    /* 0x240 */ s16 transitionCountdown;
    /* 0x242 */ s16 fadeInState;
    /* 0x244 */ s16 alpha;
} DaytelopContext; // size = 0x248

typedef enum {
    /* 0 */ DAYTELOP_HOURSTEXT_OFF,
    /* 1 */ DAYTELOP_HOURSTEXT_FADEIN,
    /* 2 */ DAYTELOP_HOURSTEXT_ON
} Daytelop_FadeState;

#endif
