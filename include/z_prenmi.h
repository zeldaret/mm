#ifndef Z64_PRENMI_H
#define Z64_PRENMI_H

#include "global.h"

void PreNMI_Destroy(GameState* thisx);
void PreNMI_Init(GameState* thisx);

typedef struct {
    /* 0x00 */ GameState state;
    /* 0xA4 */ u32 timer;
    /* 0xA8 */ UNK_TYPE4 unkA8;
} PreNMIState; // size = 0xAC

#endif
