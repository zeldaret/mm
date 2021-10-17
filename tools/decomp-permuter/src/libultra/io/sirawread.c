#include <ultra64.h>
#include <global.h>

s32 __osSiRawReadIo(u32 devAddr, u32* data) {
    if (__osSiDeviceBusy()) {
        return -1;
    }
    *data = *(u32*)(devAddr | 0xA0000000);
    return 0;
}
