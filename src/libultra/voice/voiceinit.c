#include "global.h"

extern u8 D_80097FA0;
extern u8 D_80097FA5;

// Initializes Voice Recognition System control structure and hardware
s32 osVoiceInit(OSMesgQueue* siMessageQ, OSVoiceHandle* hd, s32 channel) {
    s32 errorCode;
    u8* phi_s0;
    u8 status = 0;
    union {
        s32 data32;
        u8 data[4];
    } u;
    s32 pad;

    hd->port = channel;
    hd->mq = siMessageQ;
    hd->mode = 0;
    
    errorCode = __osVoiceGetStatus(siMessageQ, channel, &status);
    if (errorCode != 0) {
        return errorCode;
    }

    if (__osContChannelReset(siMessageQ, channel) != 0) {
        return CONT_ERR_CONTRFAIL;
    }

    for (phi_s0 = &D_80097FA0;;) {
        errorCode = __osVoiceSetADConverter(siMessageQ, channel, *phi_s0);

        phi_s0++;
        if (errorCode != 0) {
            return errorCode;
        }

        if (phi_s0 == &D_80097FA5) {
            errorCode = __osVoiceGetStatus(siMessageQ, channel, &status);
            if (errorCode != 0) {
                return errorCode;
            }
            if (status & 2) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            /**
             * data[0] = 0
             * data[1] = 0
             * data[2] = 1
             * data[3] = 0
             */
            u.data32 = 0x100;
            errorCode = __osVoiceContWrite4(siMessageQ, channel, 0, u.data);
            if (errorCode != 0) {
                return errorCode;
            }
            
            errorCode = __osVoiceCheckResult(hd, &status);
            if (errorCode & 0xFF00) {
                errorCode = CONT_ERR_INVALID;
            }
            
            return errorCode;
        }
    }
}

