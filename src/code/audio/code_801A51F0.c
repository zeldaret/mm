#include "global.h"

// internal voice functions
u8* func_801A5A1C(s8* arg0);

typedef struct {
    /* 0x00 */ u8* unk_00;
    /* 0x04 */ s8 unk_04;
    /* 0x08 */ OSVoiceData* unk_08;
    /* 0x0C */ u16 unk_0C;
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ u16 unk_10;
    /* 0x12 */ u16 unk_12;
    /* 0x14 */ u16 unk_14;
} OSVoiceUnk; // size = 0x18

extern OSVoiceUnk D_801FD5A0;
extern OSVoiceHandle D_801FD5B8;
extern OSVoiceData D_801FD5C8;
extern OSVoiceData D_801FD5E8;
extern u8 D_801FD610[];
extern s8 D_801FD5A4;
extern u8 D_801FD5C4;

s8 D_801D8E50[] =
    "aa\0AA\0ii\0II\0uu\0UU\0ee\0EE\0oo\0OO\0KA\0GA\0KI\0GI\0KU\0GU\0KE\0GE\0KO\0GO\0SA\0ZA\0SI\0ZI\0SU\0ZU\0SE\0ZE\0SO"
    "\0ZO\0TA\0DA\0TI\0DI\0tu\0TU\0DU\0TE\0DE\0TO\0DO\0NA\0NI\0NU\0NE\0NO\0HA\0BA\0PA\0HI\0BI\0PI\0HU\0BU\0PU\0HE\0BE\0"
    "PE\0HO\0BO\0PO\0MA\0MI\0MU\0ME\0MO\0ya\0YA\0yu\0YU\0yo\0YO\0RA\0RI\0RU\0RE\0RO\0wa\0WA\0WI\0WE\0WO\0NN\0VU\0ka\0ke"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

s8 D_801D8F70[] = "aa\0AA\0ii\0II\0uu\0UU\0ee\0EE\0oo\0OO\0KA\0GA\0KI\0GI\0KU\0GU\0KE\0GE\0KO\0GO\0SA\0ZA\0SI\0ZI\0SU"
                    "\0ZU\0SE\0ZE\0SO\0ZO\0TA\0DA\0TI\0DI\0tu\0TU\0DU\0TE\0DE\0TO\0DO\0NA\0NI\0NU\0NE\0NO\0HA\0BA\0PA\0"
                    "HI\0BI\0PI\0HU\0BU\0PU\0HE\0BE\0PE\0HO\0BO\0PO\0MA\0MI\0  "
                    "\0MU\0ME\0MO\0ya\0YA\0yu\0YU\0yo\0YO\0RA\0RI\0RU\0RE\0RO\0wa\0WA\0WI\0WE\0WO\0NN\0VU\0ka\0ke\0\0\0"
                    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

/*
char D_801E0EC0[] = "Error %d\n"
char D_801E0ECC[] = "NAI_VRS:osVoiceClearDictionary %d\n"
char D_801E0EF0[] = "NAI_VRS:dict error! (%d-%d %s)\n"
char D_801E0F10[] = "NAI_VRS:Ina_SetVruGain Error!\n"
char D_801E0F30[] = "NAI_VRS:mask on  %d\n"
char D_801E0F48[] = "NAI_VRS:mask off %d\n"
char D_801E0F60[] = "NAI_VRS:answer No.:%d Dist:%d Warn:%04X Level:%5d SN:%5d (Num:%d)\n"
char D_801E0FA4[] = "NAI_VRS:error !! (ANS_MAX:%d DIST:%d WARNING:%04X LEVEL:%5d SN:%5d)\n"
*/
#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/D_801E0EC0.s")

s32 func_801A51F0(s32 errorCode) {
    switch (errorCode) {
        case CONT_ERR_NO_CONTROLLER:
        case CONT_ERR_CONTRFAIL:
        case CONT_ERR_INVALID:
        case CONT_ERR_DEVICE:
        case CONT_ERR_VOICE_MEMORY:
        case CONT_ERR_VOICE_WORD:
        case CONT_ERR_VOICE_NO_RESPONSE:
            return -1;
        default:
            return 0;
    }
}

s32 func_801A5228(u8* arg0) {
    OSMesgQueue* msgQ;
    s32 errorCode;
    u8 temp_s1;
    u8 i;
    u32 indexTemp;
    s32 index;

    D_801FD5A0.unk_04 = 0;
    D_801FD5A0.unk_08 = NULL;
    D_801FD5A0.unk_0C = 1000;
    D_801FD5A0.unk_0E = 5;
    D_801FD5A0.unk_10 = 0;
    D_801FD5A0.unk_00 = arg0;
    
    temp_s1 = arg0[600];

    msgQ = PadMgr_LockSerialMesgQueue();
    errorCode = osVoiceClearDictionary(&D_801FD5B8, temp_s1);
    PadMgr_UnlockSerialMesgQueue(msgQ);

    if (errorCode != 0) {
        return errorCode;
    } 

    for (i = 0; i < (((temp_s1 - 1) / 8) + 1); i++) {
        D_801FD608[i] = 0;

    }

    for (i = 0; i < temp_s1; i++) {

        msgQ = PadMgr_LockSerialMesgQueue();
        indexTemp = i;
        index = indexTemp * 30;
        errorCode = osVoiceSetWord(&D_801FD5B8, &arg0[index]);
        PadMgr_UnlockSerialMesgQueue(msgQ);
        
        if (func_801A51F0(errorCode) != 0) {
            func_801A5A1C(&arg0[index]);
        }
    }

    return errorCode;
}

OSVoiceData* func_801A5390(void) {
    OSVoiceData* temp_t6;
    OSMesgQueue* msgQ;

    temp_t6 = D_801FD5A0.unk_08;
    D_801FD5A0.unk_08 = NULL;

    msgQ = PadMgr_LockSerialMesgQueue();
    osVoiceStartReadData(&D_801FD5B8);
    PadMgr_UnlockSerialMesgQueue(msgQ);

    return temp_t6;
}

s32 func_801A53DC(void) {
    return D_801FD5A0.unk_00;
}

void func_801A53E8(u16 arg0, u16 arg1, u16 arg2, u16 arg3, u16 arg4) {
    D_801FD5A0.unk_0C = arg0;
    D_801FD5A0.unk_0E = arg1;
    D_801FD5A0.unk_10 = arg2;
    D_801FD5A0.unk_12 = arg3;
    D_801FD5A0.unk_14 = arg4;
}

void func_801A541C(s32 analog, s32 digital) {
    s32 sp1C;
    OSMesgQueue* msgQ;

    if (D_801FD5A0.unk_00 != 0) {

        msgQ = PadMgr_LockSerialMesgQueue();
        sp1C = osVoiceControlGain(&D_801FD5B8, analog, digital);
        PadMgr_UnlockSerialMesgQueue(msgQ);

        if (sp1C != 0) {
            func_801A51F0(sp1C);
        }
    }
}

s32 func_801A5488(u8* word) {
    s32 sp1C;
    OSMesgQueue* msgQ;
    s32 temp_v0;

    msgQ = PadMgr_LockSerialMesgQueue();
    sp1C = osVoiceCheckWord(word);
    PadMgr_UnlockSerialMesgQueue(msgQ);

    return sp1C;
}

u8* func_801A54C4(void) {
    return D_801FD608;
}

s32 func_801A54D0(u16 arg0) {
    s32 errorCode;
    u8 phi_t0;
    u8 sp22;
    u8 i;
    OSMesgQueue* msgQ;
    
    phi_t0 = true;
    if (D_801FD5A0.unk_00 != 0) {
        sp22 = D_801FD5A0.unk_00[600];
    } else {
        sp22 = 20;
        phi_t0 = false;
    }

    if (arg0 == 0xFFFF) {
        for (i = 0; i < sp22; i++) {
            D_801FD608[i / 8] |= 1 << (i % 8);
        }
    } else {
        if (D_801FD608[arg0 / 8] & (1 << (arg0 % 8))) {
            phi_t0 = false;
        } else {
            D_801FD608[arg0 / 8] |= (1 << (arg0 % 8));
        }
    }
    
    if (phi_t0) {
        msgQ = PadMgr_LockSerialMesgQueue();
        errorCode = osVoiceStopReadData(&D_801FD5B8);
        PadMgr_UnlockSerialMesgQueue(msgQ);

        if ((errorCode == 0) || (D_801FD5A4 == 0)) {
            msgQ = PadMgr_LockSerialMesgQueue();
            errorCode = osVoiceMaskDictionary(&D_801FD5B8, D_801FD608, ((sp22 - 1) / 8) + 1);
            PadMgr_UnlockSerialMesgQueue(msgQ);
        }

        D_801FD5A4 = 0;
    }
    
    return errorCode;
}

s32 func_801A5680(u16 arg0) {
    s32 errorCode;
    u8 phi_a3;
    u8 sp22;
    u8 i;
    OSMesgQueue* msgQ;
    
    phi_a3 = true;
    if (D_801FD5A0.unk_00 != 0) {
        sp22 = D_801FD5A0.unk_00[600];
    } else {
        sp22 = 20;
        phi_a3 = false;
    }

    if (arg0 == 0xFFFF) {
        for (i = 0; i < (((sp22 - 1) / 8) + 1); i++) {
            D_801FD608[i] = 0;
        }
    } else {
        if (!(D_801FD608[arg0 / 8] & (1 << (arg0 % 8)))) {
            phi_a3 = false;
        } else {
            D_801FD608[arg0 / 8] &= (1 << (arg0 % 8)) ^ 0xFF;
        }
    }
    
    if (phi_a3) {
        msgQ = PadMgr_LockSerialMesgQueue();
        errorCode = osVoiceStopReadData(&D_801FD5B8);
        PadMgr_UnlockSerialMesgQueue(msgQ);

        if ((errorCode == 0) || (D_801FD5A4 == 0)) {
            msgQ = PadMgr_LockSerialMesgQueue();
            errorCode = osVoiceMaskDictionary(&D_801FD5B8, D_801FD608, ((sp22 - 1) / 8) + 1);
            PadMgr_UnlockSerialMesgQueue(msgQ);
        }

        D_801FD5A4 = 0;
    }
    
    return errorCode;
}

s32 func_801A5808(void) {
    s32 errorCode = 0;
    s32 ret;
    OSMesgQueue* msgQ;

    switch (D_801FD5A0.unk_04) {
        case 0:
            msgQ = PadMgr_LockSerialMesgQueue();
            errorCode = osVoiceStartReadData(&D_801FD5B8);
            PadMgr_UnlockSerialMesgQueue(msgQ);

            D_801FD5A4 = 1;
            break;
        case 1:
            msgQ = PadMgr_LockSerialMesgQueue();
            errorCode = osVoiceGetReadData(&D_801FD5B8, &D_801FD5C8);
            PadMgr_UnlockSerialMesgQueue(msgQ);

            if (func_801A51F0(errorCode) == 0) {
                switch (D_801FD5C4) {
                    case 0:
                        D_801FD5A4 = 2;
                        break;
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        break;
                    case 7:
                        D_801FD5A4 = 2;
                        break;
                }
            }
            break;
        case 2:
            if (((D_801FD5C8.warning & D_801FD5A0.unk_10) == 0) && (D_801FD5A0.unk_0E >= D_801FD5C8.answer_num) && (D_801FD5A0.unk_0C >= D_801FD5C8.distance[0]) && (D_801FD5C8.voice_level >= D_801FD5A0.unk_12) && (D_801FD5C8.voice_sn >= D_801FD5A0.unk_14)) {
                D_801FD5E8 = D_801FD5C8;
                D_801FD5A0.unk_08 = &D_801FD5E8;
            }

            msgQ = PadMgr_LockSerialMesgQueue();
            osVoiceStopReadData(&D_801FD5B8);
            PadMgr_UnlockSerialMesgQueue(msgQ);
            
            msgQ = PadMgr_LockSerialMesgQueue();
            errorCode = osVoiceStartReadData(&D_801FD5B8);
            PadMgr_UnlockSerialMesgQueue(msgQ);

            D_801FD5A4 = 1;
            break;
    }

    return func_801A51F0(errorCode);
}

void func_801A5A10(void) {
    D_801FD5A0.unk_00 = 0;
}

u8* func_801A5A1C(s8* arg0) {
    u8* indexTemp1;
    u8 i;
    u8 j;
    u8 temp_t6;
    u8 temp_t8;
    u8* index;
    u8 len = strlen(arg0);

    for (j = 0, i = 0; i < len; i += 2) {

        temp_t8 = arg0[i];
        temp_t6 = arg0[i + 1];
        
        indexTemp1 = &temp_t8;
        index = &temp_t6;

        if (temp_t8 == 0x83) {
            D_801FD610[j++] = D_801D8F70[3 * (temp_t6 - 0x40)];
            D_801FD610[j++] = D_801D8F70[3 * (temp_t6 - 0x40) + 1];
        } else if (temp_t8 == 0x82) {
            D_801FD610[j++] = D_801D8E50[3 * (temp_t6 - 0x9F)];
            D_801FD610[j++] = D_801D8E50[3 * (temp_t6 - 0x9F) + 1];
        } else if (temp_t8 == 0x81 && temp_t6 == 0x5B) {
            D_801FD610[j++] = 0x2D;
            D_801FD610[j++] = 0x2D;
        } else {
            D_801FD610[j++] = 0x20;
            D_801FD610[j++] = 0x20;
        }
    }
    
    D_801FD610[i] = 0;

    return D_801FD610;
  
}

