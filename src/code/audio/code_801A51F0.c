#include "global.h"

// internal voice functions
u8* func_801A5A1C(s8* word);

// BSS
OSVoiceUnk D_801FD5A0;
OSVoiceHandle sVoiceHandle;
OSVoiceData D_801FD5C8; // Intermediate Voice Data during processsing?
OSVoiceData D_801FD5E8; // Best Match Voice Data?
u8 sVoiceMaskPattern[8];

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

s32 func_801A5228(OSVoiceDictionary* dict) {
    OSMesgQueue* msgQ;
    s32 errorCode;
    u8 numWords;
    u8 i;

    D_801FD5A0.mode = 0;
    D_801FD5A0.data = NULL;
    D_801FD5A0.distance = 1000;
    D_801FD5A0.answerNum = 5;
    D_801FD5A0.warning = 0;
    D_801FD5A0.dict = dict;

    numWords = dict->numWords;

    msgQ = PadMgr_LockSerialMesgQueue();
    errorCode = osVoiceClearDictionary(&sVoiceHandle, numWords);
    PadMgr_UnlockSerialMesgQueue(msgQ);

    if (errorCode != 0) {
        return errorCode;
    }

    for (i = 0; i < (((numWords - 1) / 8) + 1); i++) {
        sVoiceMaskPattern[i] = 0;
    }

    for (i = 0; i < numWords; i++) {
        msgQ = PadMgr_LockSerialMesgQueue();
        errorCode = osVoiceSetWord(&sVoiceHandle, &dict->words[i]);
        PadMgr_UnlockSerialMesgQueue(msgQ);

        if (func_801A51F0(errorCode) != 0) {
            func_801A5A1C(&dict->words[i]);
        }
    }

    return errorCode;
}

OSVoiceData* func_801A5390(void) {
    OSVoiceData* voiceData;
    OSMesgQueue* msgQ;

    voiceData = D_801FD5A0.data;
    D_801FD5A0.data = NULL;

    msgQ = PadMgr_LockSerialMesgQueue();
    osVoiceStartReadData(&sVoiceHandle);
    PadMgr_UnlockSerialMesgQueue(msgQ);

    return voiceData;
}

// Unused
OSVoiceDictionary* func_801A53DC(void) {
    return D_801FD5A0.dict;
}

void func_801A53E8(u16 distance, u16 answerNum, u16 warning, u16 voiceLevel, u16 voiceRelLevel) {
    D_801FD5A0.distance = distance;
    D_801FD5A0.answerNum = answerNum;
    D_801FD5A0.warning = warning;
    D_801FD5A0.voiceLevel = voiceLevel;
    D_801FD5A0.voiceRelLevel = voiceRelLevel;
}

// Unused
// Could have a return? or be void return?
s32 func_801A541C(s32 analog, s32 digital) {
    s32 errorCode;
    OSMesgQueue* msgQ;

    if (D_801FD5A0.dict != NULL) {
        msgQ = PadMgr_LockSerialMesgQueue();
        errorCode = osVoiceControlGain(&sVoiceHandle, analog, digital);
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
    return sVoiceMaskPattern;
}

s32 func_801A54D0(u16 arg0) {
    s32 errorCode;
    u8 phi_t0 = true;
    u8 numWords;
    u8 i;
    OSMesgQueue* msgQ;

    if (D_801FD5A0.dict != NULL) {
        numWords = D_801FD5A0.dict->numWords;
    } else {
        numWords = 20;
        phi_t0 = false;
    }

    if (arg0 == 0xFFFF) {
        for (i = 0; i < numWords; i++) {
            sVoiceMaskPattern[i / 8] |= 1 << (i % 8);
        }
    } else {
        if (sVoiceMaskPattern[arg0 / 8] & (1 << (arg0 % 8))) {
            phi_t0 = false;
        } else {
            sVoiceMaskPattern[arg0 / 8] |= (1 << (arg0 % 8));
        }
    }

    if (phi_t0) {
        msgQ = PadMgr_LockSerialMesgQueue();
        errorCode = osVoiceStopReadData(&sVoiceHandle);
        PadMgr_UnlockSerialMesgQueue(msgQ);

        if ((errorCode == 0) || (D_801FD5A0.mode == 0)) {
            msgQ = PadMgr_LockSerialMesgQueue();
            errorCode = osVoiceMaskDictionary(&sVoiceHandle, sVoiceMaskPattern, ((numWords - 1) / 8) + 1);
            PadMgr_UnlockSerialMesgQueue(msgQ);
        }

        D_801FD5A0.mode = 0;
    }

    return errorCode;
}

s32 func_801A5680(u16 arg0) {
    s32 errorCode;
    u8 phi_a3 = true;
    u8 numWords;
    u8 i;
    OSMesgQueue* msgQ;

    if (D_801FD5A0.dict != NULL) {
        numWords = D_801FD5A0.dict->numWords;
    } else {
        numWords = 20;
        phi_a3 = false;
    }

    if (arg0 == 0xFFFF) {
        for (i = 0; i < (((numWords - 1) / 8) + 1); i++) {
            sVoiceMaskPattern[i] = 0;
        }
    } else {
        if (!(sVoiceMaskPattern[arg0 / 8] & (1 << (arg0 % 8)))) {
            phi_a3 = false;
        } else {
            sVoiceMaskPattern[arg0 / 8] &= (1 << (arg0 % 8)) ^ 0xFF;
        }
    }

    if (phi_a3) {
        msgQ = PadMgr_LockSerialMesgQueue();
        errorCode = osVoiceStopReadData(&sVoiceHandle);
        PadMgr_UnlockSerialMesgQueue(msgQ);

        if ((errorCode == 0) || (D_801FD5A0.mode == 0)) {
            msgQ = PadMgr_LockSerialMesgQueue();
            errorCode = osVoiceMaskDictionary(&sVoiceHandle, sVoiceMaskPattern, ((numWords - 1) / 8) + 1);
            PadMgr_UnlockSerialMesgQueue(msgQ);
        }

        D_801FD5A0.mode = 0;
    }

    return errorCode;
}

s32 func_801A5808(void) {
    s32 errorCode = 0;
    s32 ret;
    OSMesgQueue* msgQ;

    if (1) {}

    switch (D_801FD5A0.mode) {
        case 0:
            msgQ = PadMgr_LockSerialMesgQueue();
            errorCode = osVoiceStartReadData(&sVoiceHandle);
            PadMgr_UnlockSerialMesgQueue(msgQ);

            D_801FD5A0.mode = 1;
            break;
        case 1:
            msgQ = PadMgr_LockSerialMesgQueue();
            errorCode = osVoiceGetReadData(&sVoiceHandle, &D_801FD5C8);
            PadMgr_UnlockSerialMesgQueue(msgQ);

            if (func_801A51F0(errorCode) == 0) {
                switch (sVoiceHandle.status) {
                    case VOICE_STATUS_READY:
                        D_801FD5A0.mode = 2;
                        break;
                    case VOICE_STATUS_START:
                    case 2:
                    case VOICE_STATUS_CANCEL:
                    case 4:
                    case VOICE_STATUS_BUSY:
                    case 6:
                        break;
                    case VOICE_STATUS_END:
                        D_801FD5A0.mode = 2;
                        break;
                }
            }
            break;
        case 2:
            if (((D_801FD5C8.warning & D_801FD5A0.warning) == 0) && (D_801FD5A0.answerNum >= D_801FD5C8.answerNum) &&
                (D_801FD5A0.distance >= D_801FD5C8.distance[0]) && (D_801FD5C8.voiceLevel >= D_801FD5A0.voiceLevel) &&
                (D_801FD5C8.voiceRelLevel >= D_801FD5A0.voiceRelLevel)) {
                D_801FD5E8 = D_801FD5C8;
                D_801FD5A0.data = &D_801FD5E8;
            }

            msgQ = PadMgr_LockSerialMesgQueue();
            osVoiceStopReadData(&sVoiceHandle);
            PadMgr_UnlockSerialMesgQueue(msgQ);

            msgQ = PadMgr_LockSerialMesgQueue();
            errorCode = osVoiceStartReadData(&sVoiceHandle);
            PadMgr_UnlockSerialMesgQueue(msgQ);

            D_801FD5A0.mode = 1;
            break;
    }

    ret = func_801A51F0(errorCode);

    return ret;
}

// Unused
void func_801A5A10(void) {
    D_801FD5A0.dict = NULL;
}

u8* func_801A5A1C(s8* word) {
    u8 i;
    u8 j;
    u8 numSyllables = strlen(word); // technically twice the num of syllables
    u8 syllable[2];

    for (j = 0, i = 0; i < numSyllables; i += 2) {
        syllable[0] = word[i];
        syllable[1] = word[i + 1];

        if (syllable[0] == 0x83) {
            D_801FD610[j++] = D_801D8F70[syllable[1] - 0x40][0];
            D_801FD610[j++] = D_801D8F70[syllable[1] - 0x40][1];
        } else if (syllable[0] == 0x82) {
            D_801FD610[j++] = D_801D8E50[syllable[1] - 0x9F][0];
            D_801FD610[j++] = D_801D8E50[syllable[1] - 0x9F][1];
        } else if (syllable[0] == 0x81 && syllable[1] == 0x5B) {
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
