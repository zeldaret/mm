#include "global.h"

// Registers words to the Voice Recognition System dictionary
s32 osVoiceSetWord(OSVoiceHandle* hd, u8* word) {
    s32 i;
    s32 sp50;
    s32 errorCode;
    u8 status;
    u8 data[40];

    errorCode = __osVoiceGetStatus(hd->mq, hd->port, &status);
    if (errorCode != 0) {
        return errorCode;
    }

    if (status & 2) {
        return CONT_ERR_VOICE_NO_RESPONSE;
    }

    sp50 = 0;

    while (word[sp50] != 0) {
        sp50 += 2;
    }

    bzero(&data, 40);

    for (i = 0; i < sp50; i += 2) {
        data[39 - sp50 + i] = word[i];
        data[39 - sp50 + i - 1] = word[i + 1];
    }

    data[39 - i - 5] = 3;

    if (sp50 >= 0xF) {
        errorCode = __osVoiceContWrite20(hd->mq, hd->port, 0, &data[0]);
        if (errorCode != 0) {
            return errorCode;
        }
    } 

    errorCode = __osVoiceContWrite20(hd->mq, hd->port, 0, &data[20]);
    if (errorCode != 0) {
        return errorCode;
    }

    errorCode = __osVoiceCheckResult(hd, &status);

    if (errorCode != 0) {
        if (errorCode & 0x100) {
            errorCode = CONT_ERR_VOICE_MEMORY;
        } else if (errorCode & 0x200) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (errorCode & 0xFF00) {
            errorCode = CONT_ERR_INVALID;
        }
    }

    return errorCode;
}
