#include "global.h"

void osCreateThread(OSThread* thread, OSId id, void* entry, void* arg, void* sp, OSPri p) {
    register u32 saveMask;
    OSIntMask mask;

    thread->id = id;
    thread->priority = p;
    thread->next = NULL;
    thread->queue = NULL;
    thread->context.pc = (u32)entry;
    thread->context.a0 = arg;
    thread->context.sp = (u64)(s32)sp - 16;
    thread->context.ra = __osCleanupThread;

    mask = 0x3FFF01;
    thread->context.sr = 0xFF03;
    thread->context.rcp = (mask & 0x3F0000) >> 16;
    thread->context.fpcsr = 0x01000800;
    thread->fp = 0;
    thread->state = 1;
    thread->flags = 0;

    saveMask = __osDisableInt();
    thread->tlnext = __osActiveQueue;
    __osActiveQueue = thread;
    __osRestoreInt(saveMask);
}
