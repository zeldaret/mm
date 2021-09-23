#include "global.h"

GameInfo* gGameInfo;

// #pragma GLOBAL_ASM("asm/non_matchings/code/z_debug/static_context_init.s")
void static_context_init(void) {
    s32 i;
    gGameInfo = (GameInfo*)SystemArena_Malloc(sizeof(GameInfo));
    if (1) {}
    gGameInfo->unk_00 = 0;
    gGameInfo->unk_01 = 0;
    gGameInfo->unk_02 = 0;
    gGameInfo->unk_04 = 0;
    gGameInfo->unk_03 = 0;
    
    for (i = 0; i < ARRAY_COUNT(gGameInfo->data); i++) {
        gGameInfo->data[i] = 0;
    }
}
