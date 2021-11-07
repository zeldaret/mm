#include "global.h"

// Initializes Voice Recognition System word registration dictionary
s32 osVoiceClearDictionary(OSVoiceHandle* hd, u8 words) {
    u8* registration_word;
    u8 status;
    s32 sp24;
    s32 errorCode;

    errorCode = __osVoiceGetStatus(hd->mq, hd->port, &status);
    if (errorCode != 0) {
        return errorCode;
    }

    registration_word = &sp24;
    if (status & 2) {
        return 0xF;
    }

    sp24 = 0x2000000;
    registration_word[2] = words;

    errorCode = __osVoiceContWrite4(hd->mq, hd->port, 0, registration_word);
    if (errorCode != 0) {
        return errorCode;
    }

    errorCode = __osVoiceCheckResult(hd, &status);
    if ((errorCode & 0xFF00) != 0) {
        errorCode = 5;
    }

    return errorCode;
}
