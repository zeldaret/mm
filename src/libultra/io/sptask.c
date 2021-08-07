#include "global.h"

#define _osVirtualToPhysical(ptr)              \
    if (ptr != NULL) {                         \
        ptr = (void*)osVirtualToPhysical(ptr); \
    }


static OSTask sTmpTask;

OSTask* _VirtualToPhysicalTask(OSTask* intp) {
    OSTask* tp = &sTmpTask;

    bcopy(intp, tp, sizeof(OSTask));

    _osVirtualToPhysical(tp->t.ucode);
    _osVirtualToPhysical(tp->t.ucode_data);
    _osVirtualToPhysical(tp->t.dram_stack);
    _osVirtualToPhysical(tp->t.output_buff);
    _osVirtualToPhysical(tp->t.output_buff_size);
    _osVirtualToPhysical(tp->t.data_ptr);
    _osVirtualToPhysical(tp->t.yield_data_ptr);

    return tp;
}


void osSpTaskLoad(OSTask* intp) {
    OSTask* tp;

    tp = _VirtualToPhysicalTask(intp);

    if ((tp->t.flags & 0x1) != 0) {
        tp->t.ucode_data = tp->t.yield_data_ptr;
        tp->t.ucode_data_size = tp->t.yield_data_size;

        intp->t.flags = intp->t.flags & 0xFFFFFFFE;

        if ((tp->t.flags & 0x4) != 0) {
            tp->t.ucode = *(u64**)(((u32)intp->t.yield_data_ptr + 3068) | 0xA0000000);
        }
    }

    osWritebackDCache((void*)tp, sizeof(OSTask));

    __osSpSetStatus(11008);

    while (__osSpSetPc(0x04001000) == -1) {
        ;
    }
    while (__osSpRawStartDma(1, 0x04000FC0, (void*)tp, sizeof(OSTask)) == -1) {
        ;
    }
    while (__osSpDeviceBusy()) {
        ;
    }
    while (__osSpRawStartDma(1, 0x04001000, (void*)tp->t.ucode_boot, tp->t.ucode_boot_size) == -1) {
        ;
    }
}

void osSpTaskStartGo(OSTask* tp) {
    while (__osSpDeviceBusy()) {
        ;
    }

    __osSpSetStatus(293);
}
