#include "global.h"

extern u8 D_80097FA0;
extern u8 D_80097FA5;

// Initializes Voice Recognition System control structure and hardware
s32 osVoiceInit(OSMesgQueue* siMessageQ, OSVoiceHandle* hd, s32 channel) {
    s32 errorCode;
    u8* phi_s0;
    u8 sp37 = 0;
    s32 sp30;
    s32 pad;

    hd->port = channel;
    hd->mq = siMessageQ;
    hd->mode = 0;
    
    errorCode = __osVoiceGetStatus(siMessageQ, channel, &sp37);
    if (errorCode != 0) {
        return errorCode;
    }

    if (__osContChannelReset(siMessageQ, channel) != 0) {
        return 4;
    }

    for (phi_s0 = &D_80097FA0;;) {
        errorCode = __osVoiceSetADConverter(siMessageQ, channel, *phi_s0);

        phi_s0++;
        if (errorCode != 0) {
            return errorCode;
        }

        if (phi_s0 == &D_80097FA5) {
            errorCode = __osVoiceGetStatus(siMessageQ, channel, &sp37);
            if (errorCode != 0) {
                return errorCode;
            }
            if (sp37 & 2) {
                return 0xF;
            }

            sp30 = 0x100;
            errorCode = __osVoiceContWrite4(siMessageQ, channel, 0, &sp30);
            if (errorCode != 0) {
                return errorCode;
            }
            
            errorCode = __osVoiceCheckResult(hd, &sp37);
            if (errorCode & 0xFF00) {
                errorCode = 5;
            }
            
            return errorCode;
        }
    }
}

