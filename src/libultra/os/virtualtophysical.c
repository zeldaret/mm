#include "PR/ultratypes.h"
#include "osint.h"
#include "stdint.h"
#include "global.h"

uintptr_t osVirtualToPhysical(void* virtualAddress) {
    if (((uintptr_t)virtualAddress >= 0x80000000) && ((uintptr_t)virtualAddress < 0xA0000000)) {
        return (uintptr_t)virtualAddress & 0x1FFFFFFF;
    } else if (((uintptr_t)virtualAddress >= 0xA0000000) && ((uintptr_t)virtualAddress < 0xC0000000)) {
        return (uintptr_t)virtualAddress & 0x1FFFFFFF;
    } else {
        return __osProbeTLB(virtualAddress);
    }
}
