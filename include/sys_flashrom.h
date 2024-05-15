#ifndef SYS_FLASHROM_H
#define SYS_FLASHROM_H

#include "ultra64.h"

typedef struct FlashromRequest {
    /* 0x00 */ s32 requestType;
    /* 0x04 */ s32 response;
    /* 0x08 */ void* addr;
    /* 0x0C */ s32 pageNum;
    /* 0x10 */ s32 pageCount;
    /* 0x14 */ OSMesgQueue messageQueue;
} FlashromRequest; // size = 0x2C

#define FLASHROM_REQUEST_WRITE 1
#define FLASHROM_REQUEST_READ 2

#define FLASH_TYPE_MAGIC 0x11118001

s32 SysFlashrom_InitFlash(void);
s32 SysFlashrom_ReadData(void* addr, u32 pageNum, u32 pageCount);
void SysFlashrom_WriteDataAsync(u8* addr, u32 pageNum, u32 pageCount);
s32 SysFlashrom_IsBusy(void);
s32 SysFlashrom_AwaitResult(void);
void SysFlashrom_WriteDataSync(void* addr, u32 pageNum, u32 pageCount);

#endif
