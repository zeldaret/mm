#include "global.h"

// Forcibly stops voice recognition processing by the Voice Recognition System
s32 osVoiceStopReadData(OSVoiceHandle* hd) {
    s32 errorCode;
    s32 i;
    u8 sp3F;
    s32 sp38;

    errorCode = __osVoiceGetStatus(hd->mq, hd->port, &sp3F);
    if (errorCode != 0) {
        return errorCode;
    }

    if (sp3F & 2) {
        return CONT_ERR_VOICE_NO_RESPONSE;
    }

    if (hd->mode == 0) {
        return CONT_ERR_INVALID;
    }

    sp38 = 0x700;
    errorCode = __osVoiceContWrite4(hd->mq, hd->port, 0, &sp38);
    
    if (errorCode == 0) {
        i = 0;
        do {
            errorCode = __osVoiceCheckResult(hd, &sp3F);
            if (errorCode & 0xFF00) {
                if (((errorCode & 7) == 0) || ((errorCode & 7) == 7)) {
                    errorCode = 0;
                    hd->mode = 0;
                } else {
                    errorCode = 5;
                }
            } else {
                hd->mode = 0;
            }
            i++;
        } while ((errorCode == 15) && (i < 20));
    }

    if (i) {}

    return errorCode;
}
