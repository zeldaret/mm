#include "global.h"

s32 osJamMesg(OSMesgQueue* mq, OSMesg msg, s32 flag) {
    register u32 saveMask;

    saveMask = __osDisableInt();

    while (mq->validCount >= mq->msgCount) {
        if (flag == 1) {
            __osRunningThread->state = 8;
            __osEnqueueAndYield(&mq->fullQueue);
        } else {
            __osRestoreInt(saveMask);
            return -1;
        }
    }

    mq->first = (mq->first + mq->msgCount - 1) % mq->msgCount;

    mq->msg[mq->first] = msg;
    mq->validCount++;

    if (mq->mtQueue->next != NULL) {
        osStartThread(__osPopThread(&mq->mtQueue));
    }

    __osRestoreInt(saveMask);
    return 0;
}
