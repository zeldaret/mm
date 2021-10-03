#include "global.h"

// Initializes Voice Recognition System word registration dictionary
s32 osVoiceClearDictionary(OSVoiceHandle* hd, u8 words) {
    u8* registration_word;
    u8 status;
    s32 sp24;
    s32 temp_v0;

    temp_v0 = __osVoiceGetStatus(hd->mq, hd->port, &status);
    if (temp_v0 != 0) {
        return temp_v0;
    }

    registration_word = &sp24;
    if (status & 2) {
        return 0xF;
    }

    sp24 = 0x2000000;
    registration_word[2] = words;

    temp_v0 = __osVoiceContWrite4(hd->mq, hd->port, 0, registration_word);
    if (temp_v0 != 0) {
        return temp_v0;
    }

    temp_v0 = __osVoiceCheckResult(hd, &status);
    if ((temp_v0 & 0xFF00) != 0) {
        temp_v0 = 5;
    }
    return temp_v0;
}
