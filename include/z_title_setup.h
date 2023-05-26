#ifndef Z64TITLE_SETUP_H
#define Z64TITLE_SETUP_H

#include "global.h"

void Setup_Destroy(GameState* gameState);
void Setup_Init(GameState* thisx);

typedef struct {
    /* 0x00 */ GameState state;
} SetupState; // size = 0xA4

#endif
