#include <PR/ultratypes.h>
#include <osint.h>

u32 osVirtualToPhysical(void* virtualAddress) {
    if (((u32)virtualAddress >= 0x80000000) && ((u32)virtualAddress < 0xA0000000)) {
        return (u32)virtualAddress & 0x1FFFFFFF;
    } else if (((u32)virtualAddress >= 0xA0000000) && ((u32)virtualAddress < 0xC0000000)) {
        return (u32)virtualAddress & 0x1FFFFFFF;
    } else {
        return __osProbeTLB(virtualAddress);
    }
}
