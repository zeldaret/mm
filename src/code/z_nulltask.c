#include "scheduler.h"

#include "macros.h"

/**
 * Blocks the current thread until all queued scheduler tasks have completed.
 */
void Sched_FlushTaskQueue(void) {
    OSScTask task;
    OSMesgQueue queue;
    OSMesg msg[1];

    // Prepare a "NULL" task
    task.next = NULL;
    task.flags = OS_SC_NEEDS_RDP | OS_SC_NEEDS_RSP;
    task.msgQ = &queue;
    task.msg = NULL;
    task.framebuffer = NULL;
    task.list.t.type = M_NULTASK;
    osCreateMesgQueue(task.msgQ, msg, ARRAY_COUNT(msg));

    // Send it to and wake up the scheduler
    osSendMesg(&gScheduler.cmdQueue, (OSMesg)&task, OS_MESG_BLOCK);
    Sched_SendNotifyMsg(&gScheduler);

    // Wait until the task has been processed, indicating that no task is
    // running and the task queue is now empty.
    osRecvMesg(&queue, NULL, OS_MESG_BLOCK);
}
