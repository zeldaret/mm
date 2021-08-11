#include "prevent_bss_reordering.h"
#include "global.h"

u8 gGfxSPTaskYieldBuffer[OS_YIELD_DATA_SIZE];

u8 gGfxSPTaskStack[0x400];

GfxPool gGfxPools[2];
