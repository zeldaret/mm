/**
 * File: voicegetreaddata.c
 *
 * Gets voice recognition result from the Voice Recognition System
 */

#include "PR/controller_voice.h"
#include "PR/os_voice.h"
#include "PR/controller.h"
#include "attributes.h"

s32 osVoiceGetReadData(OSVoiceHandle* hd, OSVoiceData* result) {
    static u8 sHandleStatus;
    s32 errorCode;
    s32 i;
    u8 status;
    u8 data[36];

    switch (hd->__mode) {
        case VOICE_HANDLE_MODE_1:
            errorCode = __osVoiceGetStatus(hd->__mq, hd->__channel, &status);
            if (errorCode != 0) {
                return errorCode;
            }

            if (status & 1) {
                return CONT_ERR_NOT_READY;
            }

            errorCode = __osVoiceContRead2(hd->__mq, hd->__channel, 0, data);
            if (errorCode != 0) {
                return errorCode;
            }

            sHandleStatus = data[0] & 7;
            hd->cmd_status = sHandleStatus;
            if ((sHandleStatus != VOICE_STATUS_READY) && (sHandleStatus != VOICE_STATUS_END)) {
                return CONT_ERR_NOT_READY;
            }
            FALLTHROUGH;
        case VOICE_HANDLE_MODE_2:
            hd->__mode = VOICE_HANDLE_MODE_2;

            errorCode = __osVoiceGetStatus(hd->__mq, hd->__channel, &status);
            if (errorCode != 0) {
                return errorCode;
            }

            if (status & 2) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            *(u32*)data = 0x600;
            errorCode = __osVoiceContWrite4(hd->__mq, hd->__channel, 0, data);
            if (errorCode != 0) {
                return errorCode;
            }
            FALLTHROUGH;
        case VOICE_HANDLE_MODE_3:
            hd->__mode = VOICE_HANDLE_MODE_3;

            errorCode = __osVoiceGetStatus(hd->__mq, hd->__channel, &status);
            if (errorCode != 0) {
                return errorCode;
            }

            if (status & 1) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            errorCode = __osVoiceContRead36(hd->__mq, hd->__channel, 0, data);
            if (errorCode != 0) {
                return errorCode;
            }

            result->warning = data[4] + (data[5] << 8);
            result->answer_num = data[6];
            result->voice_level = data[8] + (data[9] << 8);
            result->voice_sn = data[10] + (data[11] << 8);
            result->voice_time = data[12] + (data[13] << 8);

            for (i = 0; i < 5; i++) {
                result->answer[i] = data[14 + (i << 2)] + (data[15 + (i << 2)] << 8);
                result->distance[i] = data[16 + (i << 2)] + (data[17 + (i << 2)] << 8);
            }

            if (result->answer[0] == 0x7FFF) {
                result->answer_num = 0;
            }

            hd->cmd_status = data[34] & 7;
            if ((sHandleStatus == VOICE_STATUS_READY) || (hd->cmd_status == VOICE_STATUS_READY)) {
                break;
            }
            FALLTHROUGH;
        case VOICE_HANDLE_MODE_4:
            hd->__mode = VOICE_HANDLE_MODE_4;

            errorCode = __osVoiceGetStatus(hd->__mq, hd->__channel, &status);
            if (errorCode != 0) {
                return errorCode;
            }

            if (status & 1) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            errorCode = __osVoiceContRead2(hd->__mq, hd->__channel, 0, data);
            if (errorCode != 0) {
                return errorCode;
            }

            hd->cmd_status = data[0] & 7;
            if (data[0] & 7) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            break;

        default:
            return CONT_ERR_INVALID;
    }

    hd->__mode = VOICE_HANDLE_MODE_0;
    return errorCode;
}
