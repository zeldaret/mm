#ifndef LIBU64_PAD_H
#define LIBU64_PAD_H

#include "PR/os_cont.h"


typedef struct Input {
    /* 0x00 */ OSContPad cur;
    /* 0x06 */ OSContPad prev;
    /* 0x0C */ OSContPad press; // X/Y store delta from last frame
    /* 0x12 */ OSContPad rel; // X/Y store adjusted
} Input; // size = 0x18


void PadUtils_UpdateRelXY(Input* input);

#endif
