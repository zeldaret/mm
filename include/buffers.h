#ifndef BUFFERS_H
#define BUFFERS_H

#include "z64.h"
#include "macros.h"
#include "stack.h"

// pre-boot variables
extern u16 gFramebuffer1[SCREEN_HEIGHT][SCREEN_WIDTH]; // at 0x80000500
extern u8 gPreBootBuffer[];


extern u8 gGfxSPTaskYieldBuffer[OS_YIELD_DATA_SIZE];
extern STACK(gGfxSPTaskStack, 0x400);
extern GfxPool gGfxPools[2];
extern u8 gAudioHeap[0x138000];
extern u8 gSystemHeap[];


/**
 * The following variables are part of the `framebuffers` segment
 */
extern u8 gPictoPhotoI8[PICTO_PHOTO_SIZE];
extern u8 D_80784600[0x56200];
extern u16 gFramebuffer0[SCREEN_HEIGHT][SCREEN_WIDTH];

/**
 * The system heap is an area of memory that covers all the RAM that is not
 * taken by compiled code/data.
 * It starts just after the end of compiled code/data (that is not an overlay)
 * and ends at a fixed location in RAM.
 * That fixed location in RAM is used by the framebuffers of the game and have
 * a fixed size.
 * This address is calculated by doing `0x80800000 - (size of framebuffers)`,
 * where 0x80800000 is the end of the Expansion Pak address range.
 * In the vanilla game this value expands to `0x80780000`.
 */
#ifndef SYSTEM_HEAP_END_ADDR
#define SYSTEM_HEAP_END_ADDR (PHYS_TO_K0(0x800000) - sizeof(gFramebuffer0) - sizeof(D_80784600) - sizeof(gPictoPhotoI8))
#endif


#endif
