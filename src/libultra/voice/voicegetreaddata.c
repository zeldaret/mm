#include "global.h"

// Gets voice recognition result from the Voice Recognition System
s32 osVoiceGetReadData(OSVoiceHandle* hd, OSVoiceData* result) {
    s32 errorCode;
    u8 temp_t9;
    u8 new_var2;
    union {
        u8 data[40];
        u32 data32[10];
    } u;
    s32 i;

    switch (hd->mode) {
        case 1:
            errorCode = __osVoiceGetStatus(hd->mq, hd->port, &u.data[39]);
            if (errorCode != 0) {
                return errorCode;
            }

            if (u.data[39] & 1) {
                return CONT_ERR_NOT_READY;
            }

            errorCode = __osVoiceContRead2(hd->mq, hd->port, 0, u.data);
            if (errorCode != 0) {
                return errorCode;
            }

            temp_t9 = u.data[0] & 7;
            hd->status = temp_t9;
            D_8009CF60 = temp_t9;
            if ((temp_t9 != 0) && (temp_t9 != 7)) {
                return CONT_ERR_NOT_READY;
            }
        case 2:
            hd->mode = 2;

            errorCode = __osVoiceGetStatus(hd->mq, hd->port, &u.data[39]);
            if (errorCode != 0) {
                return errorCode;
            }

            if (u.data[39] & 2) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            u.data32[0] = 0x600;
            errorCode = __osVoiceContWrite4(hd->mq, hd->port, 0, u.data);
            if (errorCode != 0) {
                return errorCode;
            }

        case 3:
            hd->mode = 3;

            errorCode = __osVoiceGetStatus(hd->mq, hd->port, &u.data[39]);
            if (errorCode != 0) {
                return errorCode;
            }

            if (u.data[39] & 1) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            errorCode = __osVoiceContRead36(hd->mq, hd->port, 0, u.data);
            if (errorCode != 0) {
                return errorCode;
            }

            result->warning = u.data[4] + (u.data[5] << 8);
            result->answerNum = u.data[6];
            result->voiceLevel = u.data[8] + (u.data[9] << 8);
            result->voiceRelLevel = u.data[10] + (u.data[11] << 8);
            result->voiceTime = u.data[12] + (u.data[13] << 8);

            for (i = 0; i < 5; i++) {
                result->answer[i] = u.data[14 + 4 * (i ^ 0)] + (u.data[15 + 4 * (i ^ 0)] << 8);
                result->distance[i] = u.data[16 + 4 * (i ^ 0)] + (u.data[17 + 4 * (i ^ 0)] << 8);
            }

            if (result->answer[0] == 0x7FFF) {
                result->answerNum = 0;
            }

            new_var2 = D_8009CF60;
            temp_t9 = u.data[34] ^ 0;
            hd->status = temp_t9 & 7;
            if ((new_var2 == 0) || (hd->status == 0)) {
                break;
            }
        case 4:
            hd->mode = 4;

            errorCode = __osVoiceGetStatus(hd->mq, hd->port, &u.data[39]);
            if (errorCode != 0) {
                return errorCode;
            }

            if (u.data[39] & 1) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            errorCode = __osVoiceContRead2(hd->mq, hd->port, 0, u.data);
            if (errorCode != 0) {
                return errorCode;
            }

            hd->status = u.data[0] & 7;
            if (u.data[0] & 7) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            break;
        default:
            return CONT_ERR_INVALID;
    }
    hd->mode = 0;
    return errorCode;
}
