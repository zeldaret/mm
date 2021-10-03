#include "global.h"

s32 __osVoiceCheckResult(OSVoiceHandle* handle, u8* status) {
    s32 phi_v1;
    u8 sp20[2];

    if (phi_v1 = __osVoiceGetStatus(handle->mq, handle->port, status), phi_v1 == 0) {
        if (*status & 1) {
            phi_v1 = 0xF;
        } else if (phi_v1 = __osVoiceContRead2(handle->mq, handle->port, 0, sp20), phi_v1 == 0) {
            handle->status = sp20[0] & 7;

            if (sp20[0] & 0x40) {
                phi_v1 = 0xF;
            } else {
                phi_v1 = sp20[1] << 8;
            }
        }
    }
    return phi_v1;
}
