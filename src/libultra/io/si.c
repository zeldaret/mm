#include <ultra64.h>
#include <global.h>

int __osSiDeviceBusy() {
    register u32 status;
    status = *(u32*)0xA4800018;
    if (status & 3) {
        return 1;
    } else {
        return 0;
    }
}
