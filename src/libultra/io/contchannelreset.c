#include "global.h"

s32 __osContChannelReset(OSMesgQueue* mq, s32 count) {
    s32 i;
    s32 ret;
    u8* bufptr = (u8*)&__osPfsPifRam;

    __osSiGetAccess();

    __osPfsPifRam.pifstatus = 1;

    for (i = 0; i < count; i++) {
        *bufptr++ = 0;
    }

    *bufptr++ = 0xFD;
    *bufptr = CONT_CMD_END;

    __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    __osSiRelAccess();

    return ret;
}
