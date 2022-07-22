#include "global.h"

// Forcibly stops voice recognition processing by the Voice Recognition System
s32 osVoiceStopReadData(OSVoiceHandle* hd) {
    s32 errorCode;
    s32 i;
    u8 status;
    union {
        u32 data32;
        u8 data[4];
    } u;

    errorCode = __osVoiceGetStatus(hd->mq, hd->port, &status);
    if (errorCode != 0) {
        return errorCode;
    }

    if (status & 2) {
        return CONT_ERR_VOICE_NO_RESPONSE;
    }

    if (hd->mode == 0) {
        return CONT_ERR_INVALID;
    }

    /**
     * data[0] = 0
     * data[1] = 0
     * data[2] = 7
     * data[3] = 0
     */
    u.data32 = 0x700;
    errorCode = __osVoiceContWrite4(hd->mq, hd->port, 0, u.data);

    if (errorCode == 0) {
        i = 0;
        do {
            errorCode = __osVoiceCheckResult(hd, &status);
            if (errorCode & 0xFF00) {
                if (((errorCode & 7) == 0) || ((errorCode & 7) == 7)) {
                    errorCode = 0;
                    hd->mode = 0;
                } else {
                    errorCode = CONT_ERR_INVALID;
                }
            } else {
                hd->mode = 0;
            }
            i++;
        } while ((errorCode == CONT_ERR_VOICE_NO_RESPONSE) && (i < 20));
    }

    if (i) {}

    return errorCode;
}
