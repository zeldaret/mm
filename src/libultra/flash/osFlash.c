#include "ultra64.h"
#include "global.h"

static s32 D_801FD040[4];
static OSIoMesg D_801FD050;
static OSMesgQueue D_801FD068;
static OSPiHandle D_801FD080;
static OSMesg D_801FD0F4;
static s32 D_801FD0F8;
static char D_801FD0FC[0x14];

u32 osFlashGetAddr(u32 pageNum) {
    s32 temp = (D_801FD0F8 == 0) ? pageNum << 6 : pageNum << 7;

    return temp;
}

OSPiHandle* osFlashReInit(u8 latency, u8 pulse, u8 pageSize, u8 relDuration, u32 start) {
    D_801FD080.baseAddress = RDRAM_UNCACHED | start;
    D_801FD080.type++;
    D_801FD080.latency = latency;
    D_801FD080.pulse = pulse;
    D_801FD080.pageSize = pageSize;
    D_801FD080.relDuration = relDuration;
    D_801FD080.domain = 1;

    return &D_801FD080;
}

void osFlashChange(u32 flash_num) {
    D_801FD080.baseAddress = RDRAM_UNCACHED | (FRAM_STATUS_REGISTER + (flash_num << 17));
    D_801FD080.type = 8 + flash_num;
    return;
}

OSPiHandle* osFlashInit(void) {
    u32 flashType;
    u32 flashVendor;

    osCreateMesgQueue(&D_801FD068, &D_801FD0F4, 1);

    if (D_801FD080.baseAddress == (RDRAM_UNCACHED | FRAM_BASE_ADDRESS)) {
        return &D_801FD080;
    }

    D_801FD080.type = 8;
    D_801FD080.baseAddress = (RDRAM_UNCACHED | FRAM_BASE_ADDRESS);
    D_801FD080.latency = 0x5;
    D_801FD080.pulse = 0xC;
    D_801FD080.pageSize = 0xF;
    D_801FD080.relDuration = 0x2;
    D_801FD080.domain = 1;
    D_801FD080.speed = 0;
    bzero(&D_801FD080.transferInfo, 96);

    osEPiLinkHandle(&D_801FD080);
    osFlashReadId(&flashType, &flashVendor);

    if (flashVendor == 0x00C2001E || flashVendor == 0x00C20001 || flashVendor == 0x00C20000) {
        D_801FD0F8 = 0; // OLD FLASH
    } else {
        D_801FD0F8 = 1; // NEW FLASH
    }

    return &D_801FD080;
}

void osFlashReadStatus(u8* flashStatus) {
    u32 outFlashStatus;

    osEPiWriteIo(&D_801FD080, D_801FD080.baseAddress | FRAM_COMMAND_REGISTER, FRAM_COMMAND_EXECUTE);
    // read status using IO
    osEPiReadIo(&D_801FD080, D_801FD080.baseAddress, &outFlashStatus);

    // why twice ?
    osEPiWriteIo(&D_801FD080, D_801FD080.baseAddress | FRAM_COMMAND_REGISTER, FRAM_COMMAND_EXECUTE);
    osEPiReadIo(&D_801FD080, D_801FD080.baseAddress, &outFlashStatus);

    *flashStatus = outFlashStatus & 0xFF;

    return;
}

void osFlashReadId(u32* flashType, u32* flashVendor) {
    u8 flashStatus; // sp1F

    // why read status ?
    osFlashReadStatus(&flashStatus);

    // select silicon id read mode
    osEPiWriteIo(&D_801FD080, D_801FD080.baseAddress | FRAM_COMMAND_REGISTER, FRAM_COMMAND_SET_MODE_STATUS_AND_STATUS);

    // read silicon id using DMA
    D_801FD050.hdr.pri = 0;
    D_801FD050.hdr.retQueue = &D_801FD068;
    D_801FD050.dramAddr = D_801FD040;
    D_801FD050.devAddr = 0;
    D_801FD050.size = 8;

    osInvalDCache(D_801FD040, sizeof(D_801FD040));
    osEPiStartDma(&D_801FD080, &D_801FD050, 0);
    osRecvMesg(&D_801FD068, 0, 1);

    *flashType = D_801FD040[0];
    *flashVendor = D_801FD040[1];

    return;
}

void osFlashClearStatus(void) {
    // select status mode
    osEPiWriteIo(&D_801FD080, D_801FD080.baseAddress | FRAM_COMMAND_REGISTER, FRAM_COMMAND_EXECUTE);
    // clear status
    osEPiWriteIo(&D_801FD080, D_801FD080.baseAddress, 0x00000000);

    return;
}

s32 osFlashAllErase(void) {
    u32 status;     // sp6C
    OSTimer timer;  // sp48
    OSMesgQueue mq; // sp30
    OSMesg msg;     // sp2C

    // start chip erase operation
    osEPiWriteIo(&D_801FD080, D_801FD080.baseAddress | FRAM_COMMAND_REGISTER, FRAM_COMMAND_UNK_ERASE_OPERATION);
    osEPiWriteIo(&D_801FD080, D_801FD080.baseAddress | FRAM_COMMAND_REGISTER, FRAM_COMMAND_SET_MODE_ERASE_AND_STATUS);

    // wait for completion by polling erase-busy flag
    osCreateMesgQueue(&mq, &msg, 1);
    do {
        osSetTimer(&timer, 0xABA95ULL, 0ULL, &mq, &msg);
        osRecvMesg(&mq, &msg, 1);
        osEPiReadIo(&D_801FD080, D_801FD080.baseAddress, &status);
    } while ((status & 0x2) == 0x2);

    // check erase operation status, clear status
    osEPiReadIo(&D_801FD080, D_801FD080.baseAddress, &status);
    osFlashClearStatus();

    if (((status & 0xFF) == 0x08) || ((status & 0xFF) == 0x48) || ((status & 0x08) == 0x08)) {
        return 0;
    } else {
        return -1;
    }
}

void osFlashAllEraseThrough(void) {
    // start chip erase operation
    osEPiWriteIo(&D_801FD080, D_801FD080.baseAddress | FRAM_COMMAND_REGISTER, FRAM_COMMAND_UNK_ERASE_OPERATION);
    osEPiWriteIo(&D_801FD080, D_801FD080.baseAddress | FRAM_COMMAND_REGISTER, FRAM_COMMAND_SET_MODE_ERASE_AND_STATUS);
}

s32 osFlashCheckEraseEnd(void) {
    u8 status; // sp1F

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
    u32 status;     // sp6C
    OSTimer timer;  // sp48
    OSMesgQueue mq; // sp30
    OSMesg msg;     // sp2C

    // start sector erase operation
    osEPiWriteIo(&D_801FD080, D_801FD080.baseAddress | FRAM_COMMAND_REGISTER,
                 FRAM_COMMAND_SET_ERASE_SECTOR_OFFSET | pageNum);
    osEPiWriteIo(&D_801FD080, D_801FD080.baseAddress | FRAM_COMMAND_REGISTER, FRAM_COMMAND_SET_MODE_ERASE_AND_STATUS);

    // wait for completion by polling erase-busy flag
    osCreateMesgQueue(&mq, &msg, 1);
    do {
        osSetTimer(&timer, 0x8F0D1ULL, 0ULL, &mq, &msg);
        osRecvMesg(&mq, &msg, 1);
        osEPiReadIo(&D_801FD080, D_801FD080.baseAddress, &status);
    } while ((status & 0x2) == 0x02);

    // check erase operation status, clear status
    osEPiReadIo(&D_801FD080, D_801FD080.baseAddress, &status);
    osFlashClearStatus();

    if (((status & 0xFF) == 0x08) || ((status & 0xFF) == 0x48) || ((status & 0x08) == 0x08)) {
        return 0;
    } else {
        return -1;
    }
}

void osFlashSectorEraseThrough(u32 pageNum) {
    // start sector erase operation
    osEPiWriteIo(&D_801FD080, D_801FD080.baseAddress | FRAM_COMMAND_REGISTER,
                 FRAM_COMMAND_SET_ERASE_SECTOR_OFFSET | pageNum);
    osEPiWriteIo(&D_801FD080, D_801FD080.baseAddress | FRAM_COMMAND_REGISTER, FRAM_COMMAND_SET_MODE_ERASE_AND_STATUS);
}

s32 osFlashWriteBuffer(OSIoMesg* mb, s32 priority, void* dramAddr, OSMesgQueue* mq) {
    s32 ret;
    // select load page mode
    osEPiWriteIo(&D_801FD080, D_801FD080.baseAddress | FRAM_COMMAND_REGISTER, FRAM_COMMAND_SET_MODE_WRITE);

    // DMA 128-byte page
    mb->hdr.pri = priority;
    mb->hdr.retQueue = mq;
    mb->dramAddr = dramAddr;
    mb->devAddr = 0;
    mb->size = 0x80;

    ret = osEPiStartDma(&D_801FD080, mb, 1);

    return ret;
}

s32 osFlashWriteArray(u32 pageNum) {
    u32 status;     // sp6C
    OSTimer timer;  // sp48
    OSMesgQueue mq; // sp30
    OSMesg msg;     // sp2C

    // only needed for new flash ?
    if (D_801FD0F8 == 1) {
        osEPiWriteIo(&D_801FD080, D_801FD080.baseAddress | FRAM_COMMAND_REGISTER, FRAM_COMMAND_SET_MODE_WRITE);
    }

    // start program page operation
    osEPiWriteIo(&D_801FD080, D_801FD080.baseAddress | FRAM_COMMAND_REGISTER,
                 FRAM_COMMAND_SET_ERASE_SECTOR_OFFSET_AND_STATUS | pageNum);

    // wait for completion by polling write-busy flag
    osCreateMesgQueue(&mq, &msg, 1);
    do {
        osSetTimer(&timer, 0x249FULL, 0ULL, &mq, &msg);
        osRecvMesg(&mq, &msg, 1);
        osEPiReadIo(&D_801FD080, D_801FD080.baseAddress, &status);
    } while ((status & 0x01) == 0x01);

    // check program operation status, clear status
    osEPiReadIo(&D_801FD080, D_801FD080.baseAddress, &status);
    osFlashClearStatus();

    if (((status & 0xFF) == 0x04) || ((status & 0xFF) == 0x44) || ((status & 0x04) == 0x04)) {
        return 0;
    } else {
        return -1;
    }
}

s32 osFlashReadArray(OSIoMesg* mb, s32 priority, u32 pageNum, void* dramAddr, u32 pageCount, OSMesgQueue* mq) {
    s32 ret;
    u32 dummy;     // sp20
    u32 last_page; // sp1C
    u32 pages;     // sp18

    // select read array mode
    osEPiWriteIo(&D_801FD080, D_801FD080.baseAddress | FRAM_COMMAND_REGISTER, FRAM_COMMAND_SET_MODE_READ_AND_STATUS);

    // dummy read to initiate "fast-page" reads ?
    osEPiReadIo(&D_801FD080, D_801FD080.baseAddress, &dummy);

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
        osEPiStartDma(&D_801FD080, mb, 0);
        osRecvMesg(mq, 0, 1);
        pageNum = (pageNum + 256) & 0xF00;
        mb->dramAddr = (void*)((uintptr_t)mb->dramAddr + mb->size);
    }

    while (pageCount > 256) {
        pages = 256;
        pageCount -= 256;
        mb->size = pages << 7;
        mb->devAddr = osFlashGetAddr(pageNum);
        osEPiStartDma(&D_801FD080, mb, 0);
        osRecvMesg(mq, 0, 1);
        pageNum += 256;
        mb->dramAddr = (void*)((uintptr_t)mb->dramAddr + mb->size);
    }

    mb->size = pageCount << 7;
    mb->devAddr = osFlashGetAddr(pageNum);
    ret = osEPiStartDma(&D_801FD080, mb, 0);

    return ret;
}
