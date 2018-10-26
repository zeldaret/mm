#include <PR/ultratypes.h>
#include <osint.h>

void osCreateThread(OSThread* t, OSId id, void(*entry)(void*), void* arg, void* sp, OSPri p) {
    register u32 saveMask;
    OSIntMask mask;
    
    t->id = id;
    t->priority = p;
    t->next = NULL;
    t->queue = NULL;
    t->context.pc = (u32)entry;
    t->context.a0 = (u64)arg;
    t->context.sp = (u64)sp - 16;
    t->context.ra = (u64)__osCleanupThread;
    
    mask = 0x3FFF01;
    t->context.sr = 0xFF03;
    t->context.rcp = (mask & 0x3F0000) >> 16;
    t->context.fpcsr = 0x01000800;
    t->fp = 0;
    t->state = 1;
    t->flags = 0;
    
    saveMask = __osDisableInt();
    t->tlnext = __osActiveQueue;
    __osActiveQueue = t;
    __osRestoreInt(saveMask);
}
