#include "global.h"

s32 __osVoiceContWrite4(OSMesgQueue* mq, s32 port, u16 arg2, u8* dst[4]) {
    s32 errorCode;
    u8 status;
    u8* ptr;
    s32 retryCount = 2;
    s32 i;
    u8 temp_s2;

    __osSiGetAccess();

    do {

        ptr = (u8*)&__osPfsPifRam;

        if ((__osContLastCmd != 0xC) || (port != D_80097FB0)) {
            __osContLastCmd = 0xC;
            D_80097FB0 = port;

            for (i = 0; i < port; i++, *ptr++ = 0) {
                ;
            }

            __osPfsPifRam.pifstatus = CONT_CMD_READ_BUTTON;

            ptr[0] = 0xFF;
            ptr[1] = 7;
            ptr[2] = 1;
            ptr[3] = 0xC;
            ptr[0xA] = 0xFF;
            ptr[0xB] = 0xFE;
        } else {
            ptr = (u8*)&__osPfsPifRam + port;
        }

        ptr[4] = arg2 >> 3;
        ptr[5] = __osContAddressCrc(arg2) | (arg2 << 5);

        bcopy(dst, &ptr[6], 4);
        
        __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
        temp_s2 = __osVoiceContDataCrc(dst, 4);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        errorCode = (ptr[2] & 0xC0) >> 4;

        if (errorCode == 0) {
            if (ptr[0xA] != (0, temp_s2)) {
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
