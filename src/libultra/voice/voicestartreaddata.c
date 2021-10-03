#include "global.h"

// Start voice recognition by the Voice Recognition System
s32 osVoiceStartReadData(OSVoiceHandle* hd) {
    s32 temp_v0;
    u8 sp2B;
    s32 sp24;

    temp_v0 = __osVoiceGetStatus(hd->mq, hd->port, &sp2B);
    if (temp_v0 != 0) {
        return temp_v0;
    }

    if ((sp2B & 2) != 0) {
        return 0xF;
    }

    if (hd->mode != 0) {
        return 5;
    }

    sp24 = 0x5000000;
    temp_v0 = __osVoiceContWrite4(hd->mq, hd->port, 0, &sp24);

    if (temp_v0 == 0) {
        temp_v0 = __osVoiceCheckResult(hd, &sp2B);
        if ((temp_v0 & 0xFF00) != 0) {
            temp_v0 = 5;
        } else {
            hd->mode = 1;
        }
    }

    return temp_v0;
}
