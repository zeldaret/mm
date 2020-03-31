#include <ultra64.h>
#include <global.h>

#ifdef NON_MATCHING
u32 osFlashGetAddr(u32 page_num)
{
    return (D_801FD0F8 == 0)
        ? page_num << 6
        : page_num << 7;
}
#else
GLOBAL_ASM("asm/non_matchings/code_0x80186A70/osFlashGetAddr.asm")
#endif

#ifdef NON_MATCHING
OSPiHandle* osFlashReInit(u8 latency, u8 pulse, u8 page_size, u8 rel_duration, u32 start)
{
    D_801FD080.baseAddress = 0xA0000000 | start;
    ++D_801FD080.type;
    D_801FD080.latency = latency;
    D_801FD080.pulse = pulse;
    D_801FD080.pageSize = page_size;
    D_801FD080.relDuration = rel_duration;
    D_801FD080.domain = 1;

    return &D_801FD080;
}
#else
GLOBAL_ASM("asm/non_matchings/code_0x80186A70/osFlashReInit.asm")
#endif

#ifdef NON_MATCHING
void osFlashChange(u32 flash_num)
{
    D_801FD080.baseAddress = 0xA0000000 | (0x08000000 + (flash_num << 17));
    D_801FD080.type = 8 + flash_num;
}
#else
GLOBAL_ASM("asm/non_matchings/code_0x80186A70/osFlashChange.asm")
#endif

#ifdef NON_MATCHING
OSPiHandle* osFlashInit(void)
{
    u32 flash_maker; // sp18
    u32 flash_type; // sp1C

    osCreateMesgQueue(&D_801FD068, &D_801FD0F4, 1);

    if (D_801FD080.baseAddress == 0xA8000000) { return &D_801FD080; }

    D_801FD080.type = 8;
    D_801FD080.baseAddress = 0xA8000000;
    D_801FD080.latency = 0x5;
    D_801FD080.pulse = 0xC;
    D_801FD080.pageSize = 0xF;
    D_801FD080.relDuration = 0x2;
    D_801FD080.domain = 1;
    D_801FD080.speed = 0;
    bzero(&D_801FD080.transferInfo, 96);

    osEPiLinkHandle(&D_801FD080);
    osFlashReadId(&flash_type, &flash_maker);

    if (flash_maker == 0x00C2001E
     || flash_maker == 0x00C20001
     || flash_maker == 0x00C20000)
    {
        D_801FD0F8 = 0; // OLD FLASH
    }
    else {
        D_801FD0F8 = 1; // NEW FLASH
    }

    return &D_801FD080;
}
#else
GLOBAL_ASM("asm/non_matchings/code_0x80186A70/osFlashInit.asm")
#endif

#ifdef NON_MATCHING
void osFlashReadStatus(u8* flash_status)
{
    u32 sp1C;

    // select status mode
    func_80093BB0(&D_801FD080, D_801FD080.baseAddress | 0x10000, 0xD2000000);
    // read status using IO
    func_800920B0(&D_801FD080, D_801FD080.baseAddress, &sp1C);

    // why twice ?
    func_80093BB0(&D_801FD080, D_801FD080.baseAddress | 0x10000, 0xD2000000);
    func_800920B0(&D_801FD080, D_801FD080.baseAddress, &sp1C);

    *flash_status = (sp1C & 0xff);
}
#else
GLOBAL_ASM("asm/non_matchings/code_0x80186A70/osFlashReadStatus.asm")
#endif

#ifdef NON_MATCHING
void osFlashReadId(u32 *flash_type, u32 *flash_maker)
{
    // why read status ?
    u8 flash_status; // sp1F
    osFlashReadStatus(&flash_status);

    // select silicon id read mode
    func_80093BB0(&D_801FD080, D_801FD080.baseAddress | 0x10000, 0xE1000000);

    // read silicon id using DMA
    D_801FD050.hdr.pri = 0;
    D_801FD050.hdr.retQueue = &D_801FD068;
    D_801FD050.dramAddr = &D_801FD040;
    D_801FD050.devAddr = 0;
    D_801FD050.size = 8;

    osInvalDCache(&D_801FD040, 16);
    osEPiStartDma(&D_801FD080, &D_801FD050, 0);
    osRecvMesg(&D_801FD068, 0, 1);

    *flash_type = D_801FD040;
    *flash_maker = D_801FD040+0x4;
}
#else
GLOBAL_ASM("asm/non_matchings/code_0x80186A70/osFlashReadId.asm")
#endif

#ifdef NON_MATCHING
void osFlashClearStatus(void)
{
    // select status mode
    func_80093BB0(&D_801FD080, D_801FD080.baseAddress | 0x10000, 0xD2000000);
    // clear status
    func_80093BB0(&D_801FD080, D_801FD080.baseAddress, 0x00000000);
}
#else
GLOBAL_ASM("asm/non_matchings/code_0x80186A70/osFlashClearStatus.asm")
#endif

#ifdef NON_MATCHING
s32 osFlashAllErase(void)
{
    OSMesg msg; // sp2C
    OSMesgQueue mq; // sp30
    OSTimer timer; // sp48
    u32 status; // sp6C

    // start chip erase operation
    func_80093BB0(&D_801FD080, D_801FD080.baseAddress | 0x10000, 0x3C000000);
    func_80093BB0(&D_801FD080, D_801FD080.baseAddress | 0x10000, 0x78000000);

    // wait for completion by polling erase-busy flag
    osCreateMesgQueue(&mq, &msg, 1);
    do
    {
        osSetTimer(&timer, 0xABA95ULL, 0ULL, &mq, &msg);
        osRecvMesg(&mq, &msg, 1);
        func_800920B0(&D_801FD080, D_801FD080.baseAddress, &status);
    } while((status & 0x2) == 0x2);

    // check erase operation status, clear status
    func_800920B0(&D_801FD080, D_801FD080.baseAddress, &status);
    osFlashClearStatus();

    if ((status & 0xff) == 0x08) { return 0; }
    if ((status & 0xff) == 0x48) { return 0; }
    if ((status & 0x08) == 0x08) { return 0; }

    return -1;
}
#else
GLOBAL_ASM("asm/non_matchings/code_0x80186A70/osFlashAllErase.asm")
#endif

#ifdef NON_MATCHING
void osFlashAllEraseThrough(void)
{
    // start chip erase operation
    func_80093BB0(&D_801FD080, D_801FD080.baseAddress | 0x10000, 0x3C000000);
    func_80093BB0(&D_801FD080, D_801FD080.baseAddress | 0x10000, 0x78000000);
}
#else
GLOBAL_ASM("asm/non_matchings/code_0x80186A70/osFlashAllEraseThrough.asm")
#endif

#ifdef NON_MATCHING
s32 osFlashCheckEraseEnd(void)
{
    u8 status; // sp1F

    // check if erase operation is completed
    osFlashReadStatus(&status);
    if ((status & 0x02) == 0x2) {
        return 2; // busy
    }

    // check erase operation status, clear status
    osFlashReadStatus(&status);
    osFlashClearStatus();

    if ((status & 0xff) == 0x08) { return 0; }
    if ((status & 0xff) == 0x48) { return 0; }
    if ((status & 0x08) == 0x08) { return 0; }

    return -1;
}
#else
GLOBAL_ASM("asm/non_matchings/code_0x80186A70/osFlashCheckEraseEnd.asm")
#endif

#ifdef NON_MATCHING
s32 osFlashSectorErase(u32 page_num)
{
    OSMesg msg; // sp2C
    OSMesgQueue mq; // sp30
    OSTimer timer; // sp48
    u32 status; // sp6C

    // start sector erase operation
    func_80093BB0(&D_801FD080, D_801FD080.baseAddress | 0x10000, 0x4B000000 | page_num);
    func_80093BB0(&D_801FD080, D_801FD080.baseAddress | 0x10000, 0x78000000);

    // wait for completion by polling erase-busy flag
    osCreateMesgQueue(&mq, &msg, 1);
    do
    {
        osSetTimer(&timer, 0x8F0D1ULL, 0ULL, &mq, &msg);
        osRecvMesg(&mq, &msg, 1);
        func_800920B0(&D_801FD080, D_801FD080.baseAddress, &status);
    } while((status & 0x2) == 0x2);

    // check erase operation status, clear status
    func_800920B0(&D_801FD080, D_801FD080.baseAddress, &status);
    osFlashClearStatus();

    if ((status & 0xff) == 0x08) { return 0; }
    if ((status & 0xff) == 0x48) { return 0; }
    if ((status & 0x08) == 0x08) { return 0; }

    return -1;
}
#else
GLOBAL_ASM("asm/non_matchings/code_0x80186A70/osFlashSectorErase.asm")
#endif

#ifdef NON_MATCHING
void osFlashSectorEraseThrough(u32 page_num)
{
    // start sector erase operation
    func_80093BB0(&D_801FD080, D_801FD080.baseAddress | 0x10000, 0x4B000000 | page_num);
    func_80093BB0(&D_801FD080, D_801FD080.baseAddress | 0x10000, 0x78000000);
}
#else
GLOBAL_ASM("asm/non_matchings/code_0x80186A70/osFlashSectorEraseThrough.asm")
#endif

#ifdef NON_MATCHING
s32 osFlashWriteBuffer(OSIoMesg *mb, s32 priority, void *dramAddr, OSMesgQueue *mq)
{
    // select load page mode
    func_80093BB0(&D_801FD080, D_801FD080.baseAddress | 0x10000, 0xB4000000);

    // DMA 128-byte page
    mb->hdr.pri = priority;
    mb->hdr.retQueue = mq;
    mb->dramAddr = dramAddr;
    mb->devAddr = 0;
    mb->size = 0x80;

    return osEPiStartDma(&D_801FD080, mb, 1);
}
#else
GLOBAL_ASM("asm/non_matchings/code_0x80186A70/osFlashWriteBuffer.asm")
#endif

#ifdef NON_MATCHING
s32 osFlashWriteArray(u32 page_num)
{
    OSMesg msg; // sp2C
    OSMesgQueue mq; // sp30
    OSTimer timer; // sp48
    u32 status; // sp6C

    // only needed for new flash ?
    if (D_801FD0F8 == 1) {
        func_80093BB0(&D_801FD080, D_801FD080.baseAddress | 0x10000, 0xB4000000);
    }

    // start program page operation
    func_80093BB0(&D_801FD080, D_801FD080.baseAddress | 0x10000, 0xA5000000 | page_num);

    // wait for completion by polling write-busy flag
    osCreateMesgQueue(&mq, &msg, 1);
    do
    {
        osSetTimer(&timer, 0x249FULL, 0ULL, &mq, &msg);
        osRecvMesg(&mq, &msg, 1);
        func_800920B0(&D_801FD080, D_801FD080.baseAddress, &status);
    } while((status & 0x1) == 0x1);

    // check program operation status, clear status
    func_800920B0(&D_801FD080, D_801FD080.baseAddress, &status);
    osFlashClearStatus();

    if ((status & 0xff) == 0x04) { return 0; }
    if ((status & 0xff) == 0x44) { return 0; }
    if ((status & 0x04) == 0x04) { return 0; }

    return -1;
}
#else
GLOBAL_ASM("asm/non_matchings/code_0x80186A70/osFlashWriteArray.asm")
#endif

#ifdef NON_MATCHING
s32 osFlashReadArray(OSIoMesg *mb, s32 priority, u32 page_num, void *dramAddr, u32 n_pages, OSMesgQueue *mq)
{
    u32 pages; // sp18
    u32 last_page; // sp1C
    u32 dummy; // sp20

    // select read array mode
    func_80093BB0(&D_801FD080, D_801FD080.baseAddress | 0x10000, 0xF0000000);

    // dummy read to initiate "fast-page" reads ?
    func_800920B0(&D_801FD080, D_801FD080.baseAddress, &dummy);

    // DMA requested pages
    mb->hdr.pri = priority;
    mb->hdr.retQueue = mq;
    mb->dramAddr = dramAddr;

    last_page = page_num + n_pages - 1;

    if ((last_page & 0xF00) != (page_num & 0xF00)) {

        pages = 256 - (page_num & 0xFF);
        n_pages -= pages;
        mb->size = pages << 7;
        mb->devAddr = osFlashGetAddr(page_num);
        osEPiStartDma(&D_801FD080, mb, 0);
        osRecvMesg(mq, 0, 1);
        page_num = (page_num + 256) & 0xF00;
        (char*)mb->dramAddr += mb->size;
    }

    if (n_pages >= 257) {
        do {
            pages = 256;
            n_pages -= 256;
            mb->size = pages << 7;
            mb->devAddr = osFlashGetAddr(page_num);
            osEPiStartDma(&D_801FD080, mb, 0);
            osRecvMesg(mq, 0, 1);
            page_num += 256;
            (char*)mb->dramAddr += mb->size;
        } while(n_pages >= 257);
    }

    mb->size = n_pages << 7;
    mb->devAddr = osFlashGetAddr(page_num);
    return osEPiStartDma(&D_801FD080, mb, 0);
}
#else
GLOBAL_ASM("asm/non_matchings/code_0x80186A70/osFlashReadArray.asm")
#endif
