#ifndef Z64_OPENING_H
#define Z64_OPENING_H

#include "global.h"

void Opening_Init(GameState* thisx);
void Opening_Destroy(GameState* thisx);

typedef struct {
    /* 0x000 */ GameState common;
    /* 0x0A4 */ UNK_TYPE1 padA4[0x4];
    /* 0x0A8 */ View view;
} OpeningContext; // size = 0x210

#endif
