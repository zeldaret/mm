#ifndef ULTRA64_OS_VOICE_H
#define ULTRA64_OS_VOICE_H

#include "ultratypes.h"
#include "os_message.h"


typedef struct OSVoiceHandle {
    /* 0x0 */ OSMesgQueue* mq;
    /* 0x4 */ s32 port; /* Controller port */
    /* 0x8 */ s32 mode;
    /* 0xC */ u8 status;
} OSVoiceHandle; // size = 0x10

typedef struct OSVoiceData {
    /* 0x00 */ u16 warning;
    /* 0x02 */ u16 answer_num;
    /* 0x04 */ u16 voice_level;
    /* 0x06 */ u16 voice_sn;
    /* 0x08 */ u16 voice_time;
    /* 0x0A */ u16 answer[5];
    /* 0x14 */ u16 distance[5];
} OSVoiceData; // size = 0x1E


s32 osVoiceInit(OSMesgQueue *, OSVoiceHandle *, int);
s32 osVoiceCheckWord(u8 *data);
s32 osVoiceClearDictionary(OSVoiceHandle *, u8);
s32 osVoiceControlGain(OSVoiceHandle *, s32, s32);
s32 osVoiceSetWord(OSVoiceHandle *, u8 *);
s32 osVoiceStartReadData(OSVoiceHandle *);
s32 osVoiceStopReadData(OSVoiceHandle *);
s32 osVoiceGetReadData(OSVoiceHandle *, OSVoiceData *);
s32 osVoiceMaskDictionary(OSVoiceHandle *, u8 *, int);
void osVoiceCountSyllables(u8 *, u32 *);

// internal
u8 __osVoiceContDataCrc(u8* data, u32 length);
s32 __osVoiceCheckResult(OSVoiceHandle* hd, u8* stat);
s32 __osVoiceContRead2(OSMesgQueue* mq, int channel, u16 address, u8* buffer);
s32 __osVoiceContRead36(OSMesgQueue* mq, s32 channel, u16 address, u8* buffer);
s32 __osVoiceSetADConverter(OSMesgQueue* mq, s32 channel, u8 data);
s32 __osVoiceContWrite20(OSMesgQueue* mq, int channel, u16 address, u8* buffer);
s32 __osVoiceGetStatus(OSMesgQueue* mq, s32 port, u8* status);
s32 __osVoiceContWrite4(OSMesgQueue* mq, int channel, u16 address, u8 dst[4]);

#endif
