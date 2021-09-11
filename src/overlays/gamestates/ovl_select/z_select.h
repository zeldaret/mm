#ifndef Z64_SELECT_H
#define Z64_SELECT_H

#include "global.h"

void Select_Init(GameState* thisx);
void Select_Destroy(GameState* thisx);

typedef struct {
    GameState state;
    char unk_A4[0x1DC];
} SelectContext; // size = 0x280

#endif
