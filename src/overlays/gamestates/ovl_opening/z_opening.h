#ifndef _Z64_OPENING_H_
#define _Z64_OPENING_H_

#include "global.h"

void TitleSetup_Init(GameState* thisx);
void TitleSetup_Destroy(GameState* thisx);

typedef struct {
    /* 0x000 */ GameState state;
    /* 0x0A4 */ UNK_TYPE1 unk_A4[0x4];
    /* 0x0A8 */ View view;
} TitleSetupState; // size = 0x210

#endif
