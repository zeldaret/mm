#ifndef PR_OS_FLASH_H
#define PR_OS_FLASH_H

#include "ultratypes.h"
#include "os_pi.h"


OSPiHandle* osFlashReInit(u8 latency, u8 pulse, u8 pageSize, u8 relDuration, u32 start);
OSPiHandle* osFlashInit(void);
void osFlashReadStatus(u8* flashStatus);
void osFlashReadId(u32* flashType, u32* flashVendor);
void osFlashClearStatus(void);
s32 osFlashAllErase(void);
s32 osFlashSectorErase(u32 pageNum);
s32 osFlashWriteBuffer(OSIoMesg* mb, s32 priority, void* dramAddr, OSMesgQueue* mq);
s32 osFlashWriteArray(u32 pageNum);
s32 osFlashReadArray(OSIoMesg* mb, s32 priority, u32 pageNum, void* dramAddr, u32 pageCount, OSMesgQueue* mq);
void osFlashChange(u32 flashNum);
void osFlashAllEraseThrough(void);
void osFlashSectorEraseThrough(u32 pageNum);
s32 osFlashCheckEraseEnd(void);

#endif
