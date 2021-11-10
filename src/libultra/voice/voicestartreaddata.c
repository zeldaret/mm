#include "global.h"

// Start voice recognition by the Voice Recognition System
s32 osVoiceStartReadData(OSVoiceHandle* hd) {
    s32 errorCode;
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

    if (hd->mode != 0) {
        return CONT_ERR_INVALID;
    }

    /**
     * data[0] = 5
     * data[1] = 0
     * data[2] = 0
     * data[3] = 0
     */
    u.data32 = 0x5000000;
    errorCode = __osVoiceContWrite4(hd->mq, hd->port, 0, u.data);

    if (errorCode == 0) {
        errorCode = __osVoiceCheckResult(hd, &status);

        if (errorCode & 0xFF00) {
            errorCode = CONT_ERR_INVALID;
        } else {
            hd->mode = 1;
        }
    }

    return errorCode;
}
