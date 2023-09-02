#include "global.h"
#include "PR/osint.h"

u32 __osPreNMI = 0;

__OSEventState __osEventStateTab[OS_NUM_EVENTS];

void osSetEventMesg(OSEvent e, OSMesgQueue* mq, OSMesg m) {
    register u32 saveMask;
    __OSEventState* es;

    saveMask = __osDisableInt();

    es = &__osEventStateTab[e];

    es->messageQueue = mq;
    es->message = m;

    if (e == 14) {
        if ((__osShutdown != 0) && (__osPreNMI == 0)) {
            osSendMesg(mq, m, OS_MESG_NOBLOCK);
        }
        __osPreNMI = 1;
    }

    __osRestoreInt(saveMask);
}
