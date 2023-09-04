#include "global.h"

void func_80084940(void) {
    u32 spStatus = __osSpGetStatus();
    u32 dpStatus = osDpGetStatus();

    if (spStatus && dpStatus) {} // stubbed debug prints
}

void func_80084968(void) {
    func_80084940();
    osDpSetStatus(0x28);
    __osSpSetStatus(0x4082);
    func_80084940();
}
