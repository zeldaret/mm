#ifndef CONTROLLER_VOICE_H
#define CONTROLLER_VOICE_H

#include "PR/ultratypes.h"
#include "ultra64/message.h"
#include "libc/stddef.h"

typedef enum OsVoiceHandleMode {
    /* 0 */ VOICE_HANDLE_MODE_0,
    /* 1 */ VOICE_HANDLE_MODE_1,
    /* 2 */ VOICE_HANDLE_MODE_2,
    /* 3 */ VOICE_HANDLE_MODE_3,
    /* 4 */ VOICE_HANDLE_MODE_4
} OsVoiceHandleMode;

typedef struct {
    /* 0x0 */ OSMesgQueue* mq;
    /* 0x4 */ s32 channel; /* Controller port */
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

typedef struct {
    /* 0x0 */ u8 dummy;
    /* 0x1 */ u8 txsize;
    /* 0x2 */ u8 rxsize;
    /* 0x3 */ u8 cmd;
    /* 0x4 */ u8 addrh;
    /* 0x5 */ u8 addrl;
    /* 0x6 */ u8 data[2];
    /* 0x8 */ u8 datacrc;
} __OSVoiceRead2Format; // size = 0x9

typedef struct {
    /* 0x00 */ u8 dummy;
    /* 0x01 */ u8 txsize;
    /* 0x02 */ u8 rxsize;
    /* 0x03 */ u8 cmd;
    /* 0x04 */ u8 addrh;
    /* 0x05 */ u8 addrl;
    /* 0x06 */ u8 data[36];
    /* 0x2A */ u8 datacrc;
} __OSVoiceRead36Format; // siez = 0x2B

typedef struct {
    /* 0x0 */ u8 dummy;
    /* 0x1 */ u8 txsize;
    /* 0x2 */ u8 rxsize;
    /* 0x3 */ u8 cmd;
    /* 0x4 */ u8 addrh;
    /* 0x5 */ u8 addrl;
    /* 0x6 */ u8 data[4];
    /* 0xA */ u8 datacrc;
} __OSVoiceWrite4Format; // size = 0xB

typedef struct {
    /* 0x00 */ u8 dummy;
    /* 0x01 */ u8 txsize;
    /* 0x02 */ u8 rxsize;
    /* 0x03 */ u8 cmd;
    /* 0x04 */ u8 addrh;
    /* 0x05 */ u8 addrl;
    /* 0x06 */ u8 data[20];
    /* 0x1A */ u8 datacrc;
} __OSVoiceWrite20Format; // size = 0x1B

typedef struct {
    /* 0x0 */ u8 txsize;
    /* 0x1 */ u8 rxsize;
    /* 0x2 */ u8 cmd;
    /* 0x3 */ u8 data;
    /* 0x4 */ u8 scrc;
    /* 0x5 */ u8 datacrc;
} __OSVoiceSWriteFormat; // size = 0x6

s32 osVoiceInit(OSMesgQueue* mq, OSVoiceHandle* hd, s32 channel);
s32 osVoiceSetWord(OSVoiceHandle* hd, u8* word);
s32 osVoiceCheckWord(u8* word);
s32 osVoiceStartReadData(OSVoiceHandle* hd);
s32 osVoiceStopReadData(OSVoiceHandle* hd);
s32 osVoiceGetReadData(OSVoiceHandle* hd, OSVoiceData* result);
s32 osVoiceClearDictionary(OSVoiceHandle* hd, u8 numWords);
s32 osVoiceMaskDictionary(OSVoiceHandle* hd, u8* maskPattern, s32 size);
s32 osVoiceControlGain(OSVoiceHandle* hd, s32 analog, s32 digital);

s32 __osVoiceContRead2(OSMesgQueue* mq, s32 channel, u16 address, u8 dst[2]);
s32 __osVoiceContRead36(OSMesgQueue* mq, s32 channel, u16 address, u8 dst[36]);
s32 __osVoiceContWrite4(OSMesgQueue* mq, s32 channel, u16 address, u8 dst[4]);
s32 __osVoiceContWrite20(OSMesgQueue* mq, s32 channel, u16 address, u8 dst[20]);
s32 __osVoiceCheckResult(OSVoiceHandle* hd, u8* status);
s32 __osVoiceGetStatus(OSMesgQueue* mq, s32 channel, u8* status);
s32 __osVoiceSetADConverter(OSMesgQueue* mq, s32 channel, u8 data);
u8 __osVoiceContDataCrc(u8* data, size_t numBytes);

extern OSVoiceHandle gVoiceHandle;

#endif
