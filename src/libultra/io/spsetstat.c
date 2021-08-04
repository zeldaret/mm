#include "osint.h"
#include "assert.h"

void __osSpSetStatus(u32 data) {
    *(vu32*)0xA4040010 = data;
}
