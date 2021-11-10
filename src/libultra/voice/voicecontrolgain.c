#include "global.h"

extern u8 D_80098180[];

// Adjusts the input gain of the Voice Recognition System
s32 osVoiceControlGain(OSVoiceHandle* hd, s32 analog, s32 digital) {
    s32 errorCode;
    u8 phi_a2;

    if (analog == 0) {
        phi_a2 = 0x18;
    } else {
        phi_a2 = 0x98;
    }

    errorCode = __osVoiceSetADConverter(hd->mq, hd->port, phi_a2);
    if (errorCode != 0) {
        return errorCode;
    }

    if (!((digital < 8) && (digital >= 0))) {
        goto dummy;
    }

    phi_a2 = D_80098180[digital] + 2;

    if (0) {
    dummy:
        return CONT_ERR_INVALID;
    }

    errorCode = __osVoiceSetADConverter(hd->mq, hd->port, phi_a2);
    if (errorCode != 0) {
        return errorCode;
    }

    return errorCode;
}
