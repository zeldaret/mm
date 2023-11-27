#include "regs.h"
#include "libc64/malloc.h"
#include "macros.h"

RegEditor* gRegEditor;

void Regs_Init(void) {
    s32 i;

    gRegEditor = malloc(sizeof(RegEditor));
    if (1) {}
    gRegEditor->regPage = 0;
    gRegEditor->regGroup = 0;
    gRegEditor->regCur = 0;
    gRegEditor->inputRepeatTimer = 0;
    gRegEditor->dPadInputPrev = 0;

    for (i = 0; i < ARRAY_COUNT(gRegEditor->data); i++) {
        gRegEditor->data[i] = 0;
    }
}
