#ifndef PR_OS_FLASH_H
#define PR_OS_FLASH_H

#include "ultratypes.h"
#include "os_pi.h"

#define FRAM_BASE_ADDRESS 0x08000000           // FRAM Base Address in Cart Memory
#define FRAM_STATUS_REGISTER FRAM_BASE_ADDRESS // FRAM Base Address in Cart Memory

#define FLASH_VERSION_MX_PROTO_A 0x00C20000
#define FLASH_VERSION_MX_A       0x00C20001
#define FLASH_VERSION_MX_C       0x00C2001E
#define FLASH_VERSION_MX_B_AND_D 0x00C2001D
#define FLASH_VERSION_MEI        0x003200F1


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
