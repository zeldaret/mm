#include "ultra64.h"
#include "global.h"

s32 framDeviceInfo[4];
OSIoMesg framDeviceInfoQuery;
OSMesgQueue __osFlashMessageQ;
OSPiHandle __osFlashHandler;
OSMesg __osFlashMsgBuf;
s32 __osFlashVersion;
UNK_TYPE1 D_801FD0FC[0x14];

typedef enum {
    FLASH_OLD,
    FLASH_NEW,
} FlashVersion;

u32 osFlashGetAddr(u32 pageNum) {
    s32 addr = (__osFlashVersion == FLASH_OLD) ? pageNum << 6 : pageNum << 7;

    return addr;
}

OSPiHandle* osFlashReInit(u8 latency, u8 pulse, u8 pageSize, u8 relDuration, u32 start) {
    __osFlashHandler.baseAddress = RDRAM_UNCACHED | start;
    __osFlashHandler.type++;
    __osFlashHandler.latency = latency;
    __osFlashHandler.pulse = pulse;
    __osFlashHandler.pageSize = pageSize;
    __osFlashHandler.relDuration = relDuration;
    __osFlashHandler.domain = 1;

    return &__osFlashHandler;
}

void osFlashChange(u32 flash_num) {
    __osFlashHandler.baseAddress = RDRAM_UNCACHED | (FRAM_STATUS_REGISTER + (flash_num << 17));
    __osFlashHandler.type = 8 + flash_num;

    return;
}

OSPiHandle* osFlashInit(void) {
    u32 flashType;
    u32 flashVendor;

    osCreateMesgQueue(&__osFlashMessageQ, &__osFlashMsgBuf, 1);

    if (__osFlashHandler.baseAddress == (RDRAM_UNCACHED | FRAM_BASE_ADDRESS)) {
        return &__osFlashHandler;
    }

    __osFlashHandler.type = 8;
    __osFlashHandler.baseAddress = (RDRAM_UNCACHED | FRAM_BASE_ADDRESS);
    __osFlashHandler.latency = 5;
    __osFlashHandler.pulse = 12;
    __osFlashHandler.pageSize = 15;
    __osFlashHandler.relDuration = 2;
    __osFlashHandler.domain = 1;
    __osFlashHandler.speed = 0;
    bzero(&__osFlashHandler.transferInfo, sizeof(__OSTranxInfo));

    osEPiLinkHandle(&__osFlashHandler);
    osFlashReadId(&flashType, &flashVendor);

    if (flashVendor == 0x00C2001E || flashVendor == 0x00C20001 || flashVendor == 0x00C20000) {
        __osFlashVersion = FLASH_OLD;
    } else {
        __osFlashVersion = FLASH_NEW;
    }

    return &__osFlashHandler;
}

void osFlashReadStatus(u8* flashStatus) {
    u32 outFlashStatus;

    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FRAM_COMMAND_REGISTER, FRAM_COMMAND_EXECUTE);
    // read status using IO
    osEPiReadIo(&__osFlashHandler, __osFlashHandler.baseAddress, &outFlashStatus);

    // why twice ?
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FRAM_COMMAND_REGISTER, FRAM_COMMAND_EXECUTE);
    osEPiReadIo(&__osFlashHandler, __osFlashHandler.baseAddress, &outFlashStatus);

    *flashStatus = outFlashStatus & 0xFF;

    return;
}

void osFlashReadId(u32* flashType, u32* flashVendor) {
    u8 flashStatus;

    // why read status?
    osFlashReadStatus(&flashStatus);

    // select silicon id read mode
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FRAM_COMMAND_REGISTER,
                 FRAM_COMMAND_SET_MODE_STATUS_AND_STATUS);

    // read silicon id using DMA
    framDeviceInfoQuery.hdr.pri = 0;
    framDeviceInfoQuery.hdr.retQueue = &__osFlashMessageQ;
    framDeviceInfoQuery.dramAddr = framDeviceInfo;
    framDeviceInfoQuery.devAddr = 0;
    framDeviceInfoQuery.size = 8;

    osInvalDCache(framDeviceInfo, sizeof(framDeviceInfo));
    osEPiStartDma(&__osFlashHandler, &framDeviceInfoQuery, OS_READ);
    osRecvMesg(&__osFlashMessageQ, NULL, OS_MESG_BLOCK);

    *flashType = framDeviceInfo[0];
    *flashVendor = framDeviceInfo[1];

    return;
}

void osFlashClearStatus(void) {
    // select status mode
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FRAM_COMMAND_REGISTER, FRAM_COMMAND_EXECUTE);
    // clear status
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress, 0);

    return;
}

s32 osFlashAllErase(void) {
    u32 status;
    OSTimer timer;
    OSMesgQueue mq;
    OSMesg msg;

    // start chip erase operation
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FRAM_COMMAND_REGISTER,
                 FRAM_COMMAND_UNK_ERASE_OPERATION);
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FRAM_COMMAND_REGISTER,
                 FRAM_COMMAND_SET_MODE_ERASE_AND_STATUS);

    // wait for completion by polling erase-busy flag
    osCreateMesgQueue(&mq, &msg, 1);
    do {
        osSetTimer(&timer, OS_USEC_TO_CYCLES(15000), 0, &mq, &msg);
        osRecvMesg(&mq, &msg, OS_MESG_BLOCK);
        osEPiReadIo(&__osFlashHandler, __osFlashHandler.baseAddress, &status);
    } while ((status & 2) == 2);

    // check erase operation status, clear status
    osEPiReadIo(&__osFlashHandler, __osFlashHandler.baseAddress, &status);
    osFlashClearStatus();

    if (((status & 0xFF) == 0x08) || ((status & 0xFF) == 0x48) || ((status & 0x08) == 0x08)) {
        return 0;
    } else {
        return -1;
    }
}

void osFlashAllEraseThrough(void) {
    // start chip erase operation
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FRAM_COMMAND_REGISTER,
                 FRAM_COMMAND_UNK_ERASE_OPERATION);
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FRAM_COMMAND_REGISTER,
                 FRAM_COMMAND_SET_MODE_ERASE_AND_STATUS);
}

s32 osFlashCheckEraseEnd(void) {
    u8 status;

    // check if erase operation is completed
    osFlashReadStatus(&status);
    if ((status & 0x02) == 0x02) {
        return 2; // busy
    } else {
        // check erase operation status, clear status
        osFlashReadStatus(&status);
    }
    osFlashClearStatus();

    if (((status & 0xFF) == 0x08) || ((status & 0xFF) == 0x48) || ((status & 0x08) == 0x08)) {
        return 0;
    } else {
        return -1;
    }
}

s32 osFlashSectorErase(u32 pageNum) {
    u32 status;
    OSTimer timer;
    OSMesgQueue mq;
    OSMesg msg;

    // start sector erase operation
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FRAM_COMMAND_REGISTER,
                 FRAM_COMMAND_SET_ERASE_SECTOR_OFFSET | pageNum);
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FRAM_COMMAND_REGISTER,
                 FRAM_COMMAND_SET_MODE_ERASE_AND_STATUS);

    // wait for completion by polling erase-busy flag
    osCreateMesgQueue(&mq, &msg, 1);
    do {
        osSetTimer(&timer, OS_USEC_TO_CYCLES(12500), 0, &mq, &msg);
        osRecvMesg(&mq, &msg, OS_MESG_BLOCK);
        osEPiReadIo(&__osFlashHandler, __osFlashHandler.baseAddress, &status);
    } while ((status & 2) == 2);

    // check erase operation status, clear status
    osEPiReadIo(&__osFlashHandler, __osFlashHandler.baseAddress, &status);
    osFlashClearStatus();

    if (((status & 0xFF) == 0x08) || ((status & 0xFF) == 0x48) || ((status & 0x08) == 0x08)) {
        return 0;
    } else {
        return -1;
    }
}

void osFlashSectorEraseThrough(u32 pageNum) {
    // start sector erase operation
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FRAM_COMMAND_REGISTER,
                 FRAM_COMMAND_SET_ERASE_SECTOR_OFFSET | pageNum);
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FRAM_COMMAND_REGISTER,
                 FRAM_COMMAND_SET_MODE_ERASE_AND_STATUS);
}

s32 osFlashWriteBuffer(OSIoMesg* mb, s32 priority, void* dramAddr, OSMesgQueue* mq) {
    s32 ret;

    // select load page mode
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FRAM_COMMAND_REGISTER, FRAM_COMMAND_SET_MODE_WRITE);

    // DMA 128-byte page
    mb->hdr.pri = priority;
    mb->hdr.retQueue = mq;
    mb->dramAddr = dramAddr;
    mb->devAddr = 0;
    mb->size = 0x80;

    ret = osEPiStartDma(&__osFlashHandler, mb, OS_WRITE);

    return ret;
}

s32 osFlashWriteArray(u32 pageNum) {
    u32 status;
    OSTimer timer;
    OSMesgQueue mq;
    OSMesg msg;

    // only needed for new flash ?
    if (__osFlashVersion == FLASH_NEW) {
        osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FRAM_COMMAND_REGISTER,
                     FRAM_COMMAND_SET_MODE_WRITE);
    }

    // start program page operation
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FRAM_COMMAND_REGISTER,
                 FRAM_COMMAND_SET_ERASE_SECTOR_OFFSET_AND_STATUS | pageNum);

    // wait for completion by polling write-busy flag
    osCreateMesgQueue(&mq, &msg, 1);
    do {
        osSetTimer(&timer, OS_USEC_TO_CYCLES(200), 0, &mq, &msg);
        osRecvMesg(&mq, &msg, OS_MESG_BLOCK);
        osEPiReadIo(&__osFlashHandler, __osFlashHandler.baseAddress, &status);
    } while ((status & 0x01) == 0x01);

    // check program operation status, clear status
    osEPiReadIo(&__osFlashHandler, __osFlashHandler.baseAddress, &status);
    osFlashClearStatus();

    if (((status & 0xFF) == 0x04) || ((status & 0xFF) == 0x44) || ((status & 0x04) == 0x04)) {
        return 0;
    } else {
        return -1;
    }
}

s32 osFlashReadArray(OSIoMesg* mb, s32 priority, u32 pageNum, void* dramAddr, u32 pageCount, OSMesgQueue* mq) {
    s32 ret;
    u32 dummy;
    u32 last_page;
    u32 pages;

    // select read array mode
    osEPiWriteIo(&__osFlashHandler, __osFlashHandler.baseAddress | FRAM_COMMAND_REGISTER,
                 FRAM_COMMAND_SET_MODE_READ_AND_STATUS);

    // dummy read to initiate "fast-page" reads ?
    osEPiReadIo(&__osFlashHandler, __osFlashHandler.baseAddress, &dummy);

    // DMA requested pages
    mb->hdr.pri = priority;
    mb->hdr.retQueue = mq;
    mb->dramAddr = dramAddr;

    last_page = pageNum + pageCount - 1;

    if ((last_page & 0xF00) != (pageNum & 0xF00)) {

        pages = 256 - (pageNum & 0xFF);
        pageCount -= pages;
        mb->size = pages << 7;
        mb->devAddr = osFlashGetAddr(pageNum);
        osEPiStartDma(&__osFlashHandler, mb, OS_READ);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        pageNum = (pageNum + 256) & 0xF00;
        mb->dramAddr = (void*)((uintptr_t)mb->dramAddr + mb->size);
    }

    while (pageCount > 256) {
        pages = 256;
        pageCount -= 256;
        mb->size = pages << 7;
        mb->devAddr = osFlashGetAddr(pageNum);
        osEPiStartDma(&__osFlashHandler, mb, OS_READ);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        pageNum += 256;
        mb->dramAddr = (void*)((uintptr_t)mb->dramAddr + mb->size);
    }

    mb->size = pageCount << 7;
    mb->devAddr = osFlashGetAddr(pageNum);
    ret = osEPiStartDma(&__osFlashHandler, mb, OS_READ);

    return ret;
}
