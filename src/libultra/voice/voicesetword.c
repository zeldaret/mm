#include "global.h"

// Registers words to the Voice Recognition System dictionary
s32 osVoiceSetWord(OSVoiceHandle* hd, u8* word) {
    s32 i;
    s32 sp50;
    s32 errorCode;
    u8 sp4B;
    u8 sp20[0x28];

    errorCode = __osVoiceGetStatus(hd->mq, hd->port, &sp4B);
    if (errorCode != 0) {
        return errorCode;
    }

    if (sp4B & 2) {
        return 0xF;
    }

    sp50 = 0;

    while (word[sp50] != 0) {
        sp50 += 2;
    }

    bzero(&sp20, 0x28);

    for (i = 0; i < sp50; i += 2) {
        sp20[0x27 - sp50 + i] = word[i];
        sp20[0x27 - sp50 + i - 1] = word[i + 1];
    }

    sp20[0x27 - i - 5] = 3;

    if (sp50 >= 0xF) {
        errorCode = __osVoiceContWrite20(hd->mq, hd->port, 0, &sp20);
        if (errorCode != 0) {
            return errorCode;
        }
    } 

    errorCode = __osVoiceContWrite20(hd->mq, hd->port, 0, &sp20[0x14]);
    if (errorCode != 0) {
        return errorCode;
    }

    errorCode = __osVoiceCheckResult(hd, &sp4B);

    if (errorCode != 0) {
        if (errorCode & 0x100) {
            errorCode = 0xD;
        } else if (errorCode & 0x200) {
            errorCode = 0xE;
        } else if (errorCode & 0xFF00) {
            errorCode = 5;
        }
    }

    return errorCode;
}
