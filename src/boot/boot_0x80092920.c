#include <ultra64.h>
#include <global.h>

OSPiHandle* func_80092920(void) {
    u32 v0;
    u32 temp;
    u32 temp2;
    u32 temp3;
    u32 temp4;
    UNK_TYPE func_ret;

    func_8008C1E0();

    if (D_800980D0 == 0) {
        func_8008C224();
        return &D_8009E610;
    }

    D_800980D0 = 0; // TODO volatile?

    D_8009E610.type = 0;
    D_8009E610.baseAddress = 0xB0000000;
    D_8009E610.domain = 0;
    D_8009E610.speed = 0;

    func_80089630(&D_8009E624, 96);

    while ((*(vu32*)0xA4600010) & 0x3);

    temp = *(vu32*)0xA4600014;
    temp2 = *(vu32*)0xA460001C;
    temp3 = *(vu32*)0xA4600020;
    temp4 = *(vu32*)0xA4600018;

    *(vu32*)0xA4600014 = 255;
    *(vu32*)0xA460001C = 0;
    *(vu32*)0xA4600020 = 3;
    *(vu32*)0xA4600018 = 255;

    v0 = *(u32*)(D_8009E610.baseAddress | 0xA0000000);
    D_8009E610.pageSize = (v0 >> 16) & 0xF;
    D_8009E610.relDuration = (v0 >> 20) & 0xF;
    D_8009E610.pulse = v0 >> 8;
    D_8009E610.latency = v0;

    *(vu32*)0xA4600014 = temp;
    *(vu32*)0xA460001C = temp2;
    *(vu32*)0xA4600020 = temp3;
    *(vu32*)0xA4600018 = temp4;

    func_ret = func_80091A60();

    D_8009E610.next = osPiHandleListHead;
    osPiHandleListHead = &D_8009E610;

    func_80091AD0(func_ret);

    func_8008C224();

    return &D_8009E610;
}
