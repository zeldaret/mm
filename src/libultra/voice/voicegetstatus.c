#include "global.h"
#include "io/controller.h"

s32 __osVoiceGetStatus(OSMesgQueue* mq, s32 port, u8* status) {
    __OSContRequestHeaderAligned header;
    s32 ret = 0;
    s32 i;
    u8* ptr = (u8*)&__osContPifRam;
    s32 var = 2;

    __osSiGetAccess();

    do {
        if (ret != CONT_ERR_CONTRFAIL) {
            __osContPifRam.status = CONT_CMD_READ_BUTTON;

            for (i = 0; i < port; i++, *ptr++ = 0) {
                ;
            }

            *ptr++ = 1;
            *ptr++ = 3;
            *ptr = CONT_CMD_REQUEST_STATUS;
            ptr += 4;
            *ptr = CONT_CMD_END;

            __osContLastPoll = CONT_CMD_END;
            ret = __osSiRawStartDma(OS_WRITE, &__osContPifRam);
            osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        }
        ret = __osSiRawStartDma(OS_READ, &__osContPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        ptr = (u8*)&__osContPifRam + port;

        header = *((__OSContRequestHeaderAligned*)ptr);

        ret = (u8)((header.rxsize & 0xC0) >> 4);
        *status = header.status;

        if (ret == 0) {
            if (header.typeh == 0 && header.typel == 1) {
                if (header.status & 4) {
                    ret = CONT_ERR_CONTRFAIL;
                }
            } else {
                ret = CONT_ERR_DEVICE;
            }
        } else if (ret & CONT_NO_RESPONSE_ERROR) {
            ret = CONT_ERR_NO_CONTROLLER;
        } else {
            ret = CONT_ERR_CONTRFAIL;
        }
    } while ((ret == CONT_ERR_CONTRFAIL) && (var-- >= 0));

    __osSiRelAccess();
    return (ret);
}
