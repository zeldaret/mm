#include "global.h"

void func_801A5080(u16 arg0);
s32 func_801A5228(OSVoiceDictionary* dict);
void func_801A53E8(u16 distance, u16 answerNum, u16 warning, u16 voiceLevel, u16 voiceRelLevel);
s32 func_801A5808(void);
OSVoiceData* func_801A5390(void);
s32 func_801A5680(u16 wordId);
s32 func_801A54D0(u16 wordId);
u8* func_801A54C4(void);

extern OSVoiceHandle sVoiceHandle;

OSVoiceDictionary D_801D8BE0 = {
    {
        // "アトナンジカン" - "atonanjikan" -  "How many hours"
        { 0x83, 0x41, 0x83, 0x67, 0x83, 0x69, 0x83, 0x93, 0x83, 0x57, 0x83, 0x4A, 0x83, 0x93 },

        // "ハイチーズ" - "haichīzu" - "say cheese"
        { 0x83, 0x6E, 0x83, 0x43, 0x83, 0x60, 0x81, 0x5B, 0x83, 0x59 },

        // "オキロー" - "okirō" - "wake up"
        { 0x83, 0x49, 0x83, 0x4C, 0x83, 0x8D, 0x81, 0x5B },

        // "オスワリ" - "osuwari" - "sit"
        { 0x83, 0x49, 0x83, 0x58, 0x83, 0x8F, 0x83, 0x8A },

        // "ミルク" - "miruku" - "milk"
        { 0x83, 0x7E, 0x83, 0x8B, 0x83, 0x4E },

        // "ハイヤー" - "haiyā" - "hiya!"
        { 0x83, 0x6E, 0x83, 0x43, 0x83, 0x84, 0x81, 0x5B },
    },

    VOICE_WORD_ID_MAX, // number of words
};

u8 D_801D8E3C = 0;
OSVoiceData* D_801D8E40 = NULL;
u16 sTopScoreWordId = VOICE_WORD_ID_NONE;
u8 D_801D8E48 = 0;

void func_801A4EB0(void) {
}

void func_801A4EB8(void) {
    u8* new_var;
    OSMesgQueue* msgQ;
    s32 index;
    u8 sp38[1];
    u8 i;

    if (D_801D8E3C != 0) {
        msgQ = PadMgr_LockSerialMesgQueue();
        osVoiceStopReadData(&sVoiceHandle);
        PadMgr_UnlockSerialMesgQueue(msgQ);
    }

    new_var = func_801A54C4();

    for (i = 0; i < 1; i++) {
        sp38[i] = new_var[i];
    }

    if (func_801A5228(&D_801D8BE0) == 0) {
        for (i = 0; i < VOICE_WORD_ID_MAX; i++) {
            index = i / 8;
            if (((sp38[index] >> (i % 8)) & 1) == 1) {
                func_801A54D0(i);
            }
        }

        func_801A53E8(800, 2, VOICE_WARN_TOO_SMALL, 500, 2000);
        D_801D8E3C = 1;
    }
}

// Used externally in code_8019AF00
void func_801A4FD8(void) {
    s32 errorCode;
    OSMesgQueue* msgQ;

    func_801A54D0(VOICE_WORD_ID_NONE);
    if (D_801D8E3C != 0) {
        msgQ = PadMgr_LockSerialMesgQueue();
        osVoiceStopReadData(&sVoiceHandle);
        PadMgr_UnlockSerialMesgQueue(msgQ);

        errorCode = func_801A5228(&D_801D8BE0);
        func_801A54D0(VOICE_WORD_ID_NONE);
        if (errorCode == 0) {
            func_801A53E8(800, 2, VOICE_WARN_TOO_SMALL, 500, 2000);
            D_801D8E3C = 1;
        }

        func_801A5080(5);
        func_801A5080(1);
    }
}

void func_801A5080(u16 wordId) {
    if ((D_801D8E3C != 0) && (wordId < VOICE_WORD_ID_MAX)) {
        func_801A5680(wordId);
    }
}

// Unused
void func_801A50C0(u16 wordId) {
    if ((D_801D8E3C != 0) && (wordId < VOICE_WORD_ID_MAX)) {
        func_801A54D0(wordId);
    }
}

// Used externally in many files
u16 func_801A5100(void) {
    return sTopScoreWordId;
}

// Unused
u8 func_801A510C(void) {
    return D_801D8E3C;
}

// Used externally in Audio_Update (code_8019AF00)
void func_801A5118(void) {
    if (D_801D8E3C & 2) {
        D_801D8E3C &= 1;
        func_801A4EB8();
    }

    if (D_801D8E3C != 0) {
        if (func_801A5808() != 0) {
            D_801D8E48++;
            if (D_801D8E48 == 10) {
                D_801D8E3C = 0;
                sTopScoreWordId = VOICE_WORD_ID_NONE;
                return;
            }
        } else {
            D_801D8E48 = 0;
        }

        D_801D8E40 = func_801A5390();
        if (D_801D8E40 != 0) {
            sTopScoreWordId = D_801D8E40->answer[0];
        } else {
            sTopScoreWordId = VOICE_WORD_ID_NONE;
        }
    }
}
