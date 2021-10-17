#include <ultra64.h>
#include <global.h>

u32 osDpGetStatus(void) {
    return *(u32*)0xA410000C;
}
