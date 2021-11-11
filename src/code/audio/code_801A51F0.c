#include "global.h"

// internal voice functions
u8* func_801A5A1C(s8* arg0);

// BSS
OSVoiceUnk D_801FD5A0;
OSVoiceHandle D_801FD5B8;
OSVoiceData D_801FD5C8;
OSVoiceData D_801FD5E8;
u8 D_801FD608[8];

// Maybe all the same?
// u8 D_801FD610[0x11B0];
char D_801FD610[0x100];
u8 D_801FD710[0x1B0];
u8 D_801FD8C0[0x240];
u8 D_801FDB00[0x600];
u8 D_801FE100[0x3C0];
u8 D_801FE4C0[0x180];
u8 D_801FE640[0x90];
u8 D_801FE6D0[0xF0];

// Data
s8 D_801D8E50[96][3] = {
    "aa", "AA", "ii", "II", "uu", "UU", "ee", "EE", "oo", "OO", "KA", "GA", "KI", "GI", "KU", "GU",
    "KE", "GE", "KO", "GO", "SA", "ZA", "SI", "ZI", "SU", "ZU", "SE", "ZE", "SO", "ZO", "TA", "DA",
    "TI", "DI", "tu", "TU", "DU", "TE", "DE", "TO", "DO", "NA", "NI", "NU", "NE", "NO", "HA", "BA",
    "PA", "HI", "BI", "PI", "HU", "BU", "PU", "HE", "BE", "PE", "HO", "BO", "PO", "MA", "MI", "MU",
    "ME", "MO", "ya", "YA", "yu", "YU", "yo", "YO", "RA", "RI", "RU", "RE", "RO", "wa", "WA", "WI",
    "WE", "WO", "NN", "VU", "ka", "ke", "",   "",   "",   "",   "",   "",   "",   "",   "",   "",
};

s8 D_801D8F70[96][3] = {
    "aa", "AA", "ii", "II", "uu", "UU", "ee", "EE", "oo", "OO", "KA", "GA", "KI", "GI", "KU", "GU",
    "KE", "GE", "KO", "GO", "SA", "ZA", "SI", "ZI", "SU", "ZU", "SE", "ZE", "SO", "ZO", "TA", "DA",
    "TI", "DI", "tu", "TU", "DU", "TE", "DE", "TO", "DO", "NA", "NI", "NU", "NE", "NO", "HA", "BA",
    "PA", "HI", "BI", "PI", "HU", "BU", "PU", "HE", "BE", "PE", "HO", "BO", "PO", "MA", "MI", "  ",
    "MU", "ME", "MO", "ya", "YA", "yu", "YU", "yo", "YO", "RA", "RI", "RU", "RE", "RO", "wa", "WA",
    "WI", "WE", "WO", "NN", "VU", "ka", "ke", "",   "",   "",   "",   "",   "",   "",   "",   "",
};

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

// Unused
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

// Unused
// Could have a return? or be void return?
s32 func_801A541C(s32 analog, s32 digital) {
    s32 errorCode;
    OSMesgQueue* msgQ;

    if (D_801FD5A0.unk_00 != NULL) {
        msgQ = PadMgr_LockSerialMesgQueue();
        errorCode = osVoiceControlGain(&D_801FD5B8, analog, digital);
        PadMgr_UnlockSerialMesgQueue(msgQ);

        if (errorCode != 0) {
            func_801A51F0(errorCode);
        }
    }
}

// Unused
s32 func_801A5488(u8* word) {
    s32 errorCode;
    OSMesgQueue* msgQ;

    msgQ = PadMgr_LockSerialMesgQueue();
    errorCode = osVoiceCheckWord(word);
    PadMgr_UnlockSerialMesgQueue(msgQ);

    return errorCode;
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
    if (D_801FD5A0.unk_00 != NULL) {
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

        if ((errorCode == 0) || (D_801FD5A0.unk_04 == 0)) {
            msgQ = PadMgr_LockSerialMesgQueue();
            errorCode = osVoiceMaskDictionary(&D_801FD5B8, D_801FD608, ((sp22 - 1) / 8) + 1);
            PadMgr_UnlockSerialMesgQueue(msgQ);
        }

        D_801FD5A0.unk_04 = 0;
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
    if (D_801FD5A0.unk_00 != NULL) {
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

        if ((errorCode == 0) || (D_801FD5A0.unk_04 == 0)) {
            msgQ = PadMgr_LockSerialMesgQueue();
            errorCode = osVoiceMaskDictionary(&D_801FD5B8, D_801FD608, ((sp22 - 1) / 8) + 1);
            PadMgr_UnlockSerialMesgQueue(msgQ);
        }

        D_801FD5A0.unk_04 = 0;
    }

    return errorCode;
}

s32 func_801A5808(void) {
    s32 errorCode = 0;
    s32 ret;
    OSMesgQueue* msgQ;

    if (1) {}

    switch (D_801FD5A0.unk_04) {
        case 0:
            msgQ = PadMgr_LockSerialMesgQueue();
            errorCode = osVoiceStartReadData(&D_801FD5B8);
            PadMgr_UnlockSerialMesgQueue(msgQ);

            D_801FD5A0.unk_04 = 1;
            break;
        case 1:
            msgQ = PadMgr_LockSerialMesgQueue();
            errorCode = osVoiceGetReadData(&D_801FD5B8, &D_801FD5C8);
            PadMgr_UnlockSerialMesgQueue(msgQ);

            if (func_801A51F0(errorCode) == 0) {
                switch (D_801FD5B8.status) {
                    case VOICE_STATUS_READY:
                        D_801FD5A0.unk_04 = 2;
                        break;
                    case VOICE_STATUS_START:
                    case 2:
                    case VOICE_STATUS_CANCEL:
                    case 4:
                    case VOICE_STATUS_BUSY:
                    case 6:
                        break;
                    case VOICE_STATUS_END:
                        D_801FD5A0.unk_04 = 2;
                        break;
                }
            }
            break;
        case 2:
            if (((D_801FD5C8.warning & D_801FD5A0.unk_10) == 0) && (D_801FD5A0.unk_0E >= D_801FD5C8.answer_num) &&
                (D_801FD5A0.unk_0C >= D_801FD5C8.distance[0]) && (D_801FD5C8.voice_level >= D_801FD5A0.unk_12) &&
                (D_801FD5C8.voice_sn >= D_801FD5A0.unk_14)) {
                D_801FD5E8 = D_801FD5C8;
                D_801FD5A0.unk_08 = &D_801FD5E8;
            }

            msgQ = PadMgr_LockSerialMesgQueue();
            osVoiceStopReadData(&D_801FD5B8);
            PadMgr_UnlockSerialMesgQueue(msgQ);

            msgQ = PadMgr_LockSerialMesgQueue();
            errorCode = osVoiceStartReadData(&D_801FD5B8);
            PadMgr_UnlockSerialMesgQueue(msgQ);

            D_801FD5A0.unk_04 = 1;
            break;
    }

    ret = func_801A51F0(errorCode);

    return ret;
}

// Unused
void func_801A5A10(void) {
    D_801FD5A0.unk_00 = NULL;
}

u8* func_801A5A1C(s8* arg0) {
    u8 i;
    u8 j;
    u8 len = strlen(arg0);
    u8 temp_t8[2];

    for (j = 0, i = 0; i < len; i += 2) {
        temp_t8[0] = arg0[i];
        temp_t8[1] = arg0[i + 1];

        if (temp_t8[0] == 0x83) {
            D_801FD610[j++] = D_801D8F70[temp_t8[1] - 0x40][0];
            D_801FD610[j++] = D_801D8F70[temp_t8[1] - 0x40][1];
        } else if (temp_t8[0] == 0x82) {
            D_801FD610[j++] = D_801D8E50[temp_t8[1] - 0x9F][0];
            D_801FD610[j++] = D_801D8E50[temp_t8[1] - 0x9F][1];
        } else if (temp_t8[0] == 0x81 && temp_t8[1] == 0x5B) {
            D_801FD610[j++] = '-';
            D_801FD610[j++] = '-';
        } else {
            D_801FD610[j++] = ' ';
            D_801FD610[j++] = ' ';
        }
    }

    D_801FD610[i] = '\0';

    return D_801FD610;
}
