#include "global.h"

s32 __osVoiceSetADConverter(OSMesgQueue* mq, s32 port, u8 arg2) {
    s32 errorCode;
    u8* ptr;
    s32 retryCount = 2;
    u8 status;
    u16 sp48;
    s32 i;

    __osSiGetAccess();

    sp48 = arg2 * 8;

    do {

        ptr = (u8*)&__osPfsPifRam;

        if ((__osContLastCmd != 0xD) || (port != D_80097FB0)) {
            __osContLastCmd = 0xD;
            D_80097FB0 = port;

            for (i = 0; i < port; i++, *ptr++ = 0) {
                ;
            }

            __osPfsPifRam.pifstatus = CONT_CMD_READ_BUTTON;

            ptr[0] = 3;
            ptr[1] = 1;
            ptr[2] = 0xD;
            ptr[5] = 0;
            ptr[6] = 0xFE;
        } else {
            ptr = (u8*)&__osPfsPifRam + port;
        }

        ptr[3] = arg2;
        ptr[4] = __osContAddressCrc(sp48);

        __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        errorCode = (ptr[1] & 0xC0) >> 4;

        if (errorCode == 0) {
            if (ptr[5] & 1) {
                errorCode = __osVoiceGetStatus(mq, port, &status);
                if (errorCode != 0) {
                    break;
                }

                errorCode = CONT_ERR_CONTRFAIL;
            }
        } else {
            errorCode = CONT_ERR_NO_CONTROLLER;
        }

    } while ((errorCode == CONT_ERR_CONTRFAIL) && (retryCount-- >= 0));

    __osSiRelAccess();

    return errorCode;
}
