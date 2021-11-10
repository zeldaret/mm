#include "global.h"

// Gets voice recognition result from the Voice Recognition System
#ifdef NON_EQUIVALENT
s32 osVoiceGetReadData(OSVoiceHandle* hd, OSVoiceData* result) {
    s32 errorCode;
    u8 new_var;
    u8 temp_t9;
    union {
        u8 sp38[40];
        u32 sp38_32[10];
    } u;
    s32 i;

    switch (hd->mode) {
        case 1:
            errorCode = __osVoiceGetStatus(hd->mq, hd->port, &u.sp38[39]);
            if (errorCode != 0) {
                return errorCode;
            }

            if (u.sp38[39] & 1) {
                return CONT_ERR_NOT_READY;
            }

            errorCode = __osVoiceContRead2(hd->mq, hd->port, 0, u.sp38);
            if (errorCode != 0) {
                return errorCode;
            }

            temp_t9 = u.sp38[0] & 7;
            hd->status = temp_t9;
            D_8009CF60 = temp_t9;
            if ((temp_t9 != 0) && (temp_t9 != 7)) {
                return CONT_ERR_NOT_READY;
            }
        case 2:
            hd->mode = 2;

            errorCode = __osVoiceGetStatus(hd->mq, hd->port, &u.sp38[39]);
            if (errorCode != 0) {
                return errorCode;
            }

            if (u.sp38[39] & 2) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            u.sp38_32[0] = 0x600;
            errorCode = __osVoiceContWrite4(hd->mq, hd->port, 0, u.sp38);
            if (errorCode != 0) {
                return errorCode;
            }

        case 3:
            hd->mode = 3;

            errorCode = __osVoiceGetStatus(hd->mq, hd->port, &u.sp38[39]);
            if (errorCode != 0) {
                return errorCode;
            }

            if (u.sp38[39] & 1) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            errorCode = __osVoiceContRead36(hd->mq, hd->port, 0, u.sp38);
            if (errorCode != 0) {
                return errorCode;
            }

            result->warning = u.sp38[4] + (u.sp38[5] << 8);
            result->answer_num = u.sp38[6];
            result->voice_level = u.sp38[8] + (u.sp38[9] << 8);
            result->voice_sn = u.sp38[10] + (u.sp38[11] << 8);
            result->voice_time = u.sp38[12] + (u.sp38[13] << 8);

            // Issue here with for-loop unrolling
            new_var = 4;
            for (i = 0; i < 5; i++) {
                result->answer[i] = u.sp38[14 + new_var*i] + (u.sp38[15 + new_var*i] << 8);
                result->distance[i] = u.sp38[16 + new_var*i] + (u.sp38[17 + new_var*i] << 8);
            }
            
            // result->answer[0]   = u.sp38[14] + (u.sp38[15] << 8);
            // result->distance[0] = u.sp38[16] + (u.sp38[17] << 8);
            // result->answer[1]   = u.sp38[18] + (u.sp38[19] << 8);
            // result->distance[1] = u.sp38[20] + (u.sp38[21] << 8);
            // result->answer[2]   = u.sp38[22] + (u.sp38[23] << 8);
            // result->distance[2] = u.sp38[24] + (u.sp38[25] << 8);
            // result->answer[3]   = u.sp38[26] + (u.sp38[27] << 8);
            // result->distance[3] = u.sp38[28] + (u.sp38[29] << 8);
            // result->answer[4]   = u.sp38[30] + (u.sp38[31] << 8);
            // result->distance[4] = u.sp38[32] + (u.sp38[33] << 8);

            if (result->answer[0] == 0x7FFF) {
                result->answer_num = 0;
            }

            // Issue here with regalloc
            hd->status = u.sp38[34] & 7;
            if ((D_8009CF60 == 0) || (hd->status == 0)) {
                break;
            }
        case 4:
            hd->mode = 4;

            errorCode = __osVoiceGetStatus(hd->mq, hd->port, &u.sp38[39]);
            if (errorCode != 0) {
                return errorCode;
            }

            if (u.sp38[39] & 1) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            errorCode = __osVoiceContRead2(hd->mq, hd->port, 0, u.sp38);
            if (errorCode != 0) {
                return errorCode;
            }

            hd->status = u.sp38[0] & 7;
            if (u.sp38[0] & 7) {
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
