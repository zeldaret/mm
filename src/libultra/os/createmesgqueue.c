#include <ultra64.h>
#include <global.h>

void osCreateMesgQueue(OSMesgQueue* mq, OSMesg* msq, s32 count) {
    mq->mtqueue = (OSThread*)&__osThreadTail;
    mq->fullqueue = (OSThread*)&__osThreadTail;
    mq->validCount = 0;
    mq->first = 0;
    mq->msgCount = count;
    mq->msg = msq;
}
