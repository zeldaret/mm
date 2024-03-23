#include "z64voice.h"
#include "padmgr.h"

OSVoiceDictionary sVoiceDictionary = {
    {
        // "atonanjikan" -  "How many hours"
        { 'ア', 'ト', 'ナ', 'ン', 'ジ', 'カ', 'ン' },

        // "haichīzu" - "say cheese"
        { 'ハ', 'イ', 'チ', 'ー', 'ズ' },

        // "okirō" - "wake up"
        { 'オ', 'キ', 'ロ', 'ー' },

        // "osuwari" - "sit"
        { 'オ', 'ス', 'ワ', 'リ' },

        // "miruku" - "milk"
        { 'ミ', 'ル', 'ク' },

        // "haiyā" - "hiya!"
        { 'ハ', 'イ', 'ヤ', 'ー' },
    },

    VOICE_WORD_ID_MAX, // number of words
};

u8 D_801D8E3C = 0;
OSVoiceData* sVoiceData = NULL;
u16 sTopScoreWordId = VOICE_WORD_ID_NONE;
u8 D_801D8E48 = 0;

// Relation to voice initialization
void AudioVoice_Noop(void) {
}

void func_801A4EB8(void) {
    u8* voiceMaskPattern;
    OSMesgQueue* serialEventQueue;
    s32 index;
    u8 sp38[1];
    u8 i;

    if (D_801D8E3C != 0) {
        serialEventQueue = PadMgr_VoiceAcquireSerialEventQueue();
        osVoiceStopReadData(&gVoiceHandle);
        PadMgr_VoiceReleaseSerialEventQueue(serialEventQueue);
    }

    voiceMaskPattern = AudioVoice_GetVoiceMaskPattern();

    for (i = 0; i < 1; i++) {
        sp38[i] = voiceMaskPattern[i];
    }

    if (func_801A5228(&sVoiceDictionary) == 0) {
        for (i = 0; i < VOICE_WORD_ID_MAX; i++) {
            index = i / 8;
            if (((sp38[index] >> (i % 8)) & 1) == 1) {
                AudioVoice_InitWordImplAlt(i);
            }
        }

        func_801A53E8(800, 2, VOICE_WARN_TOO_SMALL, 500, 2000);
        D_801D8E3C = 1;
    }
}

void AudioVoice_ResetWord(void) {
    s32 errorCode;
    OSMesgQueue* serialEventQueue;

    AudioVoice_InitWordImplAlt(VOICE_WORD_ID_NONE);

    if (D_801D8E3C != 0) {
        serialEventQueue = PadMgr_VoiceAcquireSerialEventQueue();
        osVoiceStopReadData(&gVoiceHandle);
        PadMgr_VoiceReleaseSerialEventQueue(serialEventQueue);

        errorCode = func_801A5228(&sVoiceDictionary);
        AudioVoice_InitWordImplAlt(VOICE_WORD_ID_NONE);
        if (errorCode == 0) {
            func_801A53E8(800, 2, VOICE_WARN_TOO_SMALL, 500, 2000);
            D_801D8E3C = 1;
        }

        AudioVoice_InitWord(VOICE_WORD_ID_HIYA);
        AudioVoice_InitWord(VOICE_WORD_ID_CHEESE);
    }
}

void AudioVoice_InitWord(u16 wordId) {
    if ((D_801D8E3C != 0) && (wordId < VOICE_WORD_ID_MAX)) {
        AudioVoice_InitWordImpl(wordId);
    }
}

// Unused
void AudioVoice_InitWordAlt(u16 wordId) {
    if ((D_801D8E3C != 0) && (wordId < VOICE_WORD_ID_MAX)) {
        AudioVoice_InitWordImplAlt(wordId);
    }
}

u16 AudioVoice_GetWord(void) {
    return sTopScoreWordId;
}

// Unused
u8 func_801A510C(void) {
    return D_801D8E3C;
}

void AudioVoice_Update(void) {
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

        sVoiceData = func_801A5390();
        if (sVoiceData != 0) {
            sTopScoreWordId = sVoiceData->answer[0];
        } else {
            sTopScoreWordId = VOICE_WORD_ID_NONE;
        }
    }
}
