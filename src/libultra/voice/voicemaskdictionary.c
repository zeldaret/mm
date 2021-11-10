#include "global.h"

// Mask words registered in the voice recognition system
s32 osVoiceMaskDictionary(OSVoiceHandle* hd, u8* maskPattern, s32 size) {
    s32 errorCode;
    s32 i;
    s32 sp3C;
    u8 status;
    u8 data[20];

    errorCode = __osVoiceGetStatus(hd->mq, hd->port, &status);
    if (errorCode != 0) {
        return errorCode;
    }

    if (status & 2) {
        return CONT_ERR_VOICE_NO_RESPONSE;
    }

    if (size & 1) {
        sp3C = size + 1;
    } else {
        sp3C = size;
    }

    bzero(&data, 20);

    data[18 - sp3C] = 4;

    for (i = 0; i < sp3C; i += 2) {
        data[i + 20 - sp3C] = maskPattern[i];
        data[i + 21 - sp3C] = maskPattern[i+1];
    }

    if (size & 1) {
        data[19] = 0;
    }

    errorCode = __osVoiceContWrite20(hd->mq, hd->port, 0, &data);
    if (errorCode == 0) {
        errorCode = __osVoiceCheckResult(hd, &status);
        if (errorCode & 0xFF00) {
            errorCode = CONT_ERR_INVALID;
        }
    }

    return errorCode;
}

