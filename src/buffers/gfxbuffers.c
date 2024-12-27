#include "prevent_bss_reordering.h"
#include "buffers.h"

u64 gGfxSPTaskYieldBuffer[OS_YIELD_DATA_SIZE / sizeof(u64)] ALIGNED(16);

STACK(gGfxSPTaskStack, 0x400) ALIGNED(16);

GfxPool gGfxPools[2] ALIGNED(16);
