#include "ultra64.h"
#include "global.h"

void osDpSetStatus(u32 data) {
    *(u32*)0xA410000C = data;
}
