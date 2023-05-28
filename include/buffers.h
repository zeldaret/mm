#ifndef BUFFERS_H
#define BUFFERS_H

#include "z64.h"
#include "macros.h"
#include "stack.h"


extern u8 gGfxSPTaskYieldBuffer[OS_YIELD_DATA_SIZE];
extern STACK(gGfxSPTaskStack, 0x400);
extern GfxPool gGfxPools[2];
extern u8 gAudioHeap[0x138000];
extern u8 gSystemHeap[];

extern u8 gPictoPhotoI8[PICTO_PHOTO_SIZE];
extern u8 D_80784600[0x56200];
extern u16 gFramebuffer0[SCREEN_HEIGHT][SCREEN_WIDTH];


#endif
