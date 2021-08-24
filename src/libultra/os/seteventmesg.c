#include "global.h"

UNK_TYPE4 D_80097F10 = 0;

__OSEventState __osEventStateTab[16];

void osSetEventMesg(OSEvent e, OSMesgQueue* mq, OSMesg m) {
    register u32 saveMask;
    __OSEventState* es;

    saveMask = __osDisableInt();

    es = &__osEventStateTab[e];

    es->messageQueue = mq;
    es->message = m;

    if (e == 14) {
        if (__osShutdown != 0 && D_80097F10 == 0) {
            osSendMesg(mq, m, 0);
        }
        D_80097F10 = 1;
    }

    __osRestoreInt(saveMask);
}
