#include "global.h"
#include "PR/osint.h"
#include "libc/stdbool.h"

u32 __osPreNMI = false;

__OSEventState __osEventStateTab[OS_NUM_EVENTS];

void osSetEventMesg(OSEvent e, OSMesgQueue* mq, OSMesg m) {
    register u32 saveMask;
    __OSEventState* es;

    saveMask = __osDisableInt();

    es = &__osEventStateTab[e];

    es->messageQueue = mq;
    es->message = m;

    if (e == 14) {
        if (__osShutdown && !__osPreNMI) {
            osSendMesg(mq, m, OS_MESG_NOBLOCK);
        }
        __osPreNMI = true;
    }

    __osRestoreInt(saveMask);
}
