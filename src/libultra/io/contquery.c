#include "global.h"

s32 osContStartQuery(OSMesgQueue* mq) {
    s32 ret;

    __osSiGetAccess();

    if (__osContLastCmd != 0) {
        __osPackRequestData(0);
        __osSiRawStartDma(OS_WRITE, &__osContPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    }

    ret = __osSiRawStartDma(OS_READ, &__osContPifRam);

    __osContLastCmd = 0;

    __osSiRelAccess();

    return ret;
}

void osContGetQuery(OSContStatus* data) {
    u8 pattern;

    __osContGetInitData(&pattern, data);
}
