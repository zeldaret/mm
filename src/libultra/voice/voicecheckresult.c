#include "global.h"

s32 __osVoiceCheckResult(OSVoiceHandle* hd, u8* status) {
    s32 errorCode;
    u8 sp20[2];

    if (errorCode = __osVoiceGetStatus(hd->mq, hd->port, status), errorCode == 0) {
        if (*status & 1) {
            errorCode = 0xF;
        } else if (errorCode = __osVoiceContRead2(hd->mq, hd->port, 0, sp20), errorCode == 0) {
            hd->status = sp20[0] & 7;

            if (sp20[0] & 0x40) {
                errorCode = 0xF;
            } else {
                errorCode = sp20[1] << 8;
            }
        }
    }
    return errorCode;
}
