#include "regs.h"
#include "system_malloc.h"

RegEditor* gRegEditor;

void Regs_Init(void) {
    s32 i;

    gRegEditor = SystemArena_Malloc(sizeof(RegEditor));
    if (1) {}
    gRegEditor->unk_00 = 0;
    gRegEditor->unk_01 = 0;
    gRegEditor->unk_02 = 0;
    gRegEditor->unk_04 = 0;
    gRegEditor->unk_03 = 0;

    for (i = 0; i < ARRAY_COUNT(gRegEditor->data); i++) {
        gRegEditor->data[i] = 0;
    }
}
