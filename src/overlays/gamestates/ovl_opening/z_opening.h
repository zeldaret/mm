#ifndef _Z64_OPENING_H_
#define _Z64_OPENING_H_

#include "global.h"

void Opening_Init(GameState* thisx);
void Opening_Destroy(GameState* thisx);

typedef struct {
    /* 0x000 */ GameState state;
    /* 0x0A4 */ UNK_TYPE1 unk_A4[0x4];
    /* 0x0A8 */ View view;
} OpeningContext; // size = 0x210

#endif
