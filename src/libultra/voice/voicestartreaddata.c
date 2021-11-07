#include "global.h"

// Start voice recognition by the Voice Recognition System
s32 osVoiceStartReadData(OSVoiceHandle* hd) {
    s32 errorCode;
    u8 status;
    s32 sp24;

    errorCode = __osVoiceGetStatus(hd->mq, hd->port, &status);
    if (errorCode != 0) {
        return errorCode;
    }

    if (status & 2) {
        return 0xF;
    }

    if (hd->mode != 0) {
        return 5;
    }

    sp24 = 0x5000000;
    errorCode = __osVoiceContWrite4(hd->mq, hd->port, 0, &sp24);

    if (errorCode == 0) {
        errorCode = __osVoiceCheckResult(hd, &status);
        
        if (errorCode & 0xFF00) {
            errorCode = 5;
        } else {
            hd->mode = 1;
        }
    }

    return errorCode;
}
