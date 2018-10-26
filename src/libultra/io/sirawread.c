#include <osint.h>
#include <assert.h>

s32 __osSiRawReadIo(u32 devAddr, u32* data) {
    if (__osSiDeviceBusy() != 0) {
        return -1;
    }
    
    *(u32*)(devAddr | 0xA0000000) = (u32)data;
    
    return 0;
}
