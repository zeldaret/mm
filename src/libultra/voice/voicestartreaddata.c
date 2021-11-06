#include "global.h"

// Start voice recognition by the Voice Recognition System
s32 osVoiceStartReadData(OSVoiceHandle* hd) {
    s32 ret;
    u8 sp2B;
    s32 sp24;

    ret = __osVoiceGetStatus(hd->mq, hd->port, &sp2B);
    if (ret != 0) {
        return ret;
    }

    if ((sp2B & 2) != 0) {
        return 0xF;
    }

    if (hd->mode != 0) {
        return 5;
    }

    sp24 = 0x5000000;
    ret = __osVoiceContWrite4(hd->mq, hd->port, 0, &sp24);

    if (ret == 0) {
        ret = __osVoiceCheckResult(hd, &sp2B);
        
        if ((ret & 0xFF00) != 0) {
            ret = 5;
        } else {
            hd->mode = 1;
        }
    }

    return ret;
}
