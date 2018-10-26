#include <osint.h>

s32 osSendMesg(OSMesgQueue* mq, OSMesg msg, s32 flags) {
    register u32 saveMask;
    register s32 last;
    
    saveMask = __osDisableInt();
    
    while (mq->validCount >= mq->msgCount) {
        if (flags == 1) {
            __osRunningThread->state = 8;
            __osEnqueueAndYield(&mq->fullqueue);
        } else {
            __osRestoreInt(saveMask);
            return -1;
        }
    }
    
    last = (mq->first + mq->validCount) % mq->msgCount;
    
    mq->msg[last] = msg;
    mq->validCount++;
    
    if (mq->mtqueue->next != NULL) {
        osStartThread(__osPopThread(&mq->mtqueue));
    }
    
    __osRestoreInt(saveMask);
    return 0;
}
