#include <osint.h>

void osSetThreadPri(OSThread* t, OSPri p) {
    register u32 saveMask;
	
    saveMask = __osDisableInt();
	
    if (t == NULL) {
        t = __osRunningThread;
    }
	
    if (t->priority != p) {
        t->priority = p;

        if (t != __osRunningThread && t->state != 1) {
            __osDequeueThread(t->queue, t);
            __osEnqueueThread(t->queue, t);
        }

        if (__osRunningThread->priority < __osRunQueue->priority) {
            __osRunningThread->state = 2;
            __osEnqueueAndYield(&__osRunQueue);
        }
    }
	
    __osRestoreInt(saveMask);
}
