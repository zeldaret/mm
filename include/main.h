#ifndef MAIN_H
#define MAIN_H

#include "ultra64.h"

extern s32 gScreenWidth;
extern s32 gScreenHeight;
extern size_t gSystemHeapSize;

extern OSThread gGraphThread;

void Main(void* arg);

#endif
