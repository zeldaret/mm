#include "global.h"

// Forcibly stops voice recognition processing by the Voice Recognition System
#ifdef NON_EQUIVALENT
s32 osVoiceStopReadData(OSVoiceHandle* hd) {
    s32 i;
    s32 errorCode;
    u8 sp3F;
    s32 sp38;

    errorCode = __osVoiceGetStatus(hd->mq, hd->port, &sp3F);
    if (errorCode != 0) {
        return errorCode;
    }

    if (sp3F & 2) {
        return CONT_ERR_VOICE_NO_RESPONSE;
    }

    if (hd->mode == 0) {
        return CONT_ERR_INVALID;
    }

    sp38 = 0x700;
    errorCode = __osVoiceContWrite4(hd->mq, hd->port, 0, &sp38);
    
    if (errorCode == 0) {
        for (i = 0; i < 20; i++) {
            errorCode = __osVoiceCheckResult(hd, &sp3F);
            if (errorCode & 0xFF00) {
                if (((errorCode & 7) == 0) || ((errorCode & 7) == 7)) {
                    if (hd) {}
                    errorCode = 0;
                    hd->mode = 0;
                } else {
                    errorCode = CONT_ERR_INVALID;
                }
            } else {
                hd->mode = 0;
            }

            if (errorCode != CONT_ERR_VOICE_NO_RESPONSE) {
                break;
            }
        }
    }

    return errorCode;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/boot/voicestopread/osVoiceStopReadData.s")
#endif
