#include "global.h"

s32 __osVoiceCheckResult(OSVoiceHandle* hd, u8* status) {
    s32 errorCode;
    u8 data[2];

    if (errorCode = __osVoiceGetStatus(hd->mq, hd->port, status), errorCode == 0) {
        if (*status & 1) {
            errorCode = CONT_ERR_VOICE_NO_RESPONSE;
        } else if (errorCode = __osVoiceContRead2(hd->mq, hd->port, 0, data), errorCode == 0) {
            hd->status = data[0] & 7;

            if (data[0] & 0x40) {
                errorCode = CONT_ERR_VOICE_NO_RESPONSE;
            } else {
                errorCode = data[1] << 8;
            }
        }
    }
    return errorCode;
}
