#ifndef Z64_OPENING_H
#define Z64_OPENING_H

#include "z64game.h"
#include "z64view.h"


typedef struct {
    /* 0x000 */ GameState state;
    /* 0x0A4 */ UNK_TYPE1 unk_A4[0x4];
    /* 0x0A8 */ View view;
} TitleSetupState; // size = 0x210

void TitleSetup_Init(GameState* thisx);
void TitleSetup_Destroy(GameState* thisx);

#endif
