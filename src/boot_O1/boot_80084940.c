#include "global.h"

void func_80084940(void) {
    u32 sp;
    sp = __osSpGetStatus();
    osDpGetStatus();
}

void func_80084968(void) {
    func_80084940();
    osDpSetStatus(0x28);
    __osSpSetStatus(0x4082);
    func_80084940();
}
