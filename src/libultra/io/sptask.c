#include <ultra64.h>
#include <global.h>

OSTask* _VirtualToPhysicalTask(OSTask* intp) {
    OSTask* tp = &tmp_task;
    bcopy((void*)intp, (void*)tp, sizeof(OSTask));
    if (tp->t.ucode) {
        tp->t.ucode = (u64*)osVirtualToPhysical(tp->t.ucode);
    }
    if (tp->t.ucode_data) {
        tp->t.ucode_data = (u64*)osVirtualToPhysical(tp->t.ucode_data);
    }
    if (tp->t.dram_stack) {
        tp->t.dram_stack = (u64*)osVirtualToPhysical(tp->t.dram_stack);
    }
    if (tp->t.output_buff) {
        tp->t.output_buff = (u64*)osVirtualToPhysical(tp->t.output_buff);
    }
    if (tp->t.output_buff_size) {
        tp->t.output_buff_size = (u64*)osVirtualToPhysical(tp->t.output_buff_size);
    }
    if (tp->t.data_ptr) {
        tp->t.data_ptr = (u64*)osVirtualToPhysical(tp->t.data_ptr);
    }
    if (tp->t.yield_data_ptr) {
        tp->t.yield_data_ptr = (u64*)osVirtualToPhysical(tp->t.yield_data_ptr);
    }

    return &tmp_task;
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
