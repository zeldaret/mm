#include "global.h"
#include "io/controller.h"

s32 __osVoiceGetStatus(OSMesgQueue* mq, s32 port, u8* status) {
    __OSContRequestHeaderAligned header;
    s32 errorCode = 0;
    s32 i;
    u8* ptr = (u8*)&__osContPifRam;
    s32 retryCount = 2;

    __osSiGetAccess();

    do {
        if (errorCode != CONT_ERR_CONTRFAIL) {
            __osContPifRam.pifstatus = CONT_CMD_READ_BUTTON;

            for (i = 0; i < port; i++, *ptr++ = 0) {
                ;
            }

            *ptr++ = 1;
            *ptr++ = 3;
            *ptr = CONT_CMD_REQUEST_STATUS;
            ptr += 4;
            *ptr = CONT_CMD_END;

            __osContLastCmd = CONT_CMD_END;
            errorCode = __osSiRawStartDma(OS_WRITE, &__osContPifRam);
            osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        }
        errorCode = __osSiRawStartDma(OS_READ, &__osContPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        ptr = (u8*)&__osContPifRam + port;

        header = *((__OSContRequestHeaderAligned*)ptr);

        errorCode = (u8)((header.rxsize & 0xC0) >> 4);
        *status = header.status;

        if (errorCode == 0) {
            if (header.typeh == 0 && header.typel == 1) {
                if (header.status & 4) {
                    errorCode = CONT_ERR_CONTRFAIL;
                }
            } else {
                errorCode = CONT_ERR_DEVICE;
            }
        } else if (errorCode & CONT_NO_RESPONSE_ERROR) {
            errorCode = CONT_ERR_NO_CONTROLLER;
        } else {
            errorCode = CONT_ERR_CONTRFAIL;
        }
    } while ((errorCode == CONT_ERR_CONTRFAIL) && (retryCount-- >= 0));

    __osSiRelAccess();
    
    return errorCode;
}
