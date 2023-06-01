#ifndef OS_VOICE_H
#define OS_VOICE_H

#include "PR/ultratypes.h"
#include "ultra64/message.h"

typedef enum OsVoiceHandleMode {
    /* 0 */ VOICE_HANDLE_MODE_0,
    /* 1 */ VOICE_HANDLE_MODE_1,
    /* 2 */ VOICE_HANDLE_MODE_2,
    /* 3 */ VOICE_HANDLE_MODE_3,
    /* 4 */ VOICE_HANDLE_MODE_4
} OsVoiceHandleMode;

typedef struct {
    /* 0x0 */ OSMesgQueue* mq;
    /* 0x4 */ s32 channel; // Controller port
    /* 0x8 */ OsVoiceHandleMode mode;
    /* 0xC */ u8 status;
} OSVoiceHandle; // size = 0x10

typedef struct {
    /* 0x00 */ u16 warning;       // Warning
    /* 0x02 */ u16 answerNum;     // Candidate number (0~5)
    /* 0x04 */ u16 voiceLevel;    // Voice input level
    /* 0x06 */ u16 voiceRelLevel; // Relative voice level "voice_sn"
    /* 0x08 */ u16 voiceTime;     // Voice input time
    /* 0x0A */ u16 answer[5];     // Candidate word number
    /* 0x14 */ u16 distance[5];   // Distance value
} OSVoiceData; // size = 0x20

s32 osVoiceInit(OSMesgQueue* mq, OSVoiceHandle* hd, s32 channel);
s32 osVoiceSetWord(OSVoiceHandle* hd, u8* word);
s32 osVoiceCheckWord(u8* word);
s32 osVoiceStartReadData(OSVoiceHandle* hd);
s32 osVoiceStopReadData(OSVoiceHandle* hd);
s32 osVoiceGetReadData(OSVoiceHandle* hd, OSVoiceData* result);
s32 osVoiceClearDictionary(OSVoiceHandle* hd, u8 numWords);
s32 osVoiceMaskDictionary(OSVoiceHandle* hd, u8* maskPattern, s32 size);
s32 osVoiceControlGain(OSVoiceHandle* hd, s32 analog, s32 digital);

#endif
