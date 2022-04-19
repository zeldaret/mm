#include "PR/ultratypes.h"
#include "ultra64/vi.h"

// This file is currently required to fix bss reordering in idle.c. It is not resolved by prevent_bss_reordering.h .
// Hopefully it will not be permanent.

OSViMode gViConfigMode;
u8 D_8009B290;
