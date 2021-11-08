#include "global.h"

// Gets voice recognition result from the Voice Recognition System
#ifdef NON_EQUIVALENT
s32 osVoiceGetReadData(OSVoiceHandle* hd, OSVoiceData* result) {
    s32 errorCode;
    u8 new_var;
    u8 temp_t9;
    u8 sp38[40];
    s32 i;

    switch (hd->mode) {
        case 1:
            errorCode = __osVoiceGetStatus(hd->mq, hd->port, &sp38[39]);
            if (errorCode != 0) {
                return errorCode;
            }

            if (sp38[39] & 1) {
                return CONT_ERR_NOT_READY;
            }

            errorCode = __osVoiceContRead2(hd->mq, hd->port, 0, sp38);
            if (errorCode != 0) {
                return errorCode;
            }

            temp_t9 = sp38[0] & 7;
            hd->status = temp_t9;
            D_8009CF60 = temp_t9;
            if ((temp_t9 != 0) && (temp_t9 != 7)) {
                return CONT_ERR_NOT_READY;
            }
        case 2:
            hd->mode = 2;

            errorCode = __osVoiceGetStatus(hd->mq, hd->port, &sp38[39]);
            if (errorCode != 0) {
                return errorCode;
            }

            if (0) {}
            if (sp38[39] & 2) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            sp38[0] = 0x600; // Not reading in correctly since 0x600 is out-of-range for u8
            errorCode = __osVoiceContWrite4(hd->mq, hd->port, 0, sp38);
            if (errorCode != 0) {
                return errorCode;
            }

        case 3:
            hd->mode = 3;

            errorCode = __osVoiceGetStatus(hd->mq, hd->port, &sp38[39]);
            if (errorCode != 0) {
                return errorCode;
            }

            if (sp38[39] & 1) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            errorCode = __osVoiceContRead36(hd->mq, hd->port, 0, sp38);
            if (errorCode != 0) {
                return errorCode;
            }

            result->warning = (sp38[5] << 8) + sp38[4];
            result->answer_num = sp38[6];
            result->voice_level = (sp38[9] << 8) + sp38[8];
            result->voice_sn = (sp38[11] << 8) + sp38[10];
            result->voice_time = (sp38[13] << 8) + sp38[12];

            new_var = 4;
            for (i = 0; i < 5; i++) {
                result->answer[i] = (sp38[15 + new_var*i] << 8) + sp38[14 + new_var*i];
                result->distance[i] = (sp38[17 + new_var*i] << 8) + sp38[16 + new_var*i];
            }

            if (result->answer[0] == 0x7FFF) {
                result->answer_num = 0;
            }

            hd->status = sp38[34] & 7;
            if ((D_8009CF60 == 0) || (hd->status == 0)) {
                break;
            }
        case 4:
            hd->mode = 4;

            errorCode = __osVoiceGetStatus(hd->mq, hd->port, &sp38[39]);
            if (errorCode != 0) {
                return errorCode;
            }

            if (sp38[39] & 1) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            errorCode = __osVoiceContRead2(hd->mq, hd->port, 0, sp38);
            if (errorCode != 0) {
                return errorCode;
            }

            hd->status = sp38[0] & 7;
            if ((sp38[0] & 7) != 0) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            break;
        default:
            return CONT_ERR_INVALID;
    }
    hd->mode = 0;
    return errorCode;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/boot/voicegetreaddata/osVoiceGetReadData.s")
#endif
