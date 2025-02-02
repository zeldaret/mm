#include "buffers.h"

u64 gGfxSPTaskYieldBuffer[OS_YIELD_DATA_SIZE / sizeof(u64)] ALIGNED(16);

STACK(gGfxSPTaskStack, SP_DRAM_STACK_SIZE8) ALIGNED(16);

GfxPool gGfxPools[2] ALIGNED(16);
