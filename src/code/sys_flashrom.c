#include "global.h"
#include "stack.h"
#include "stackcheck.h"
#include "system_malloc.h"

#include "prevent_bss_reordering.h"

OSMesgQueue sFlashromMesgQueue;
OSMesg sFlashromMesg[1];
s32 sFlashromFlashIsGood;
s32 sFlashromVendor;

u8 sSysFlashromStack[0x1000];
StackEntry sSysFlashromStackInfo;
OSThread sSysFlashromThread;
s80185D40 sFlashromRequest;
OSMesg D_801FD034[1];

s32 SysFlashrom_FlashIsGood(void) {
    return sFlashromFlashIsGood;
}

const char* SysFlashrom_GetVendorStr(void) {
    switch (sFlashromVendor) {
        case FLASH_VERSION_MX_PROTO_A:
            return "PROTO A";
        case FLASH_VERSION_MX_A:
            return "A";
        case FLASH_VERSION_MX_C:
            return "C";
        case FLASH_VERSION_MEI:
            return "D(NEW)";
        case FLASH_VERSION_MX_B_AND_D:
            return "B or D";
        default:
            return "UNKNOWN";
    }
}

s32 SysFlashrom_CheckFlashType(void) {
    u32 flashType;
    u32 flashVendor;

    if (!SysFlashrom_FlashIsGood()) {
        return -1;
    }
    osFlashReadId(&flashType, &flashVendor);
    sFlashromVendor = flashVendor;
    if (flashType == 0x11118001) {
        if ((flashVendor == FLASH_VERSION_MX_PROTO_A) || (flashVendor == FLASH_VERSION_MX_A) || (flashVendor == FLASH_VERSION_MX_C) ||
            (flashVendor == FLASH_VERSION_MEI) || (flashVendor == FLASH_VERSION_MX_B_AND_D)) {
            return 0;
        } else {
            return -1;
        }
    }
    return -1;
}

s32 SysFlashrom_InitFlash(void) {
    osCreateMesgQueue(&sFlashromMesgQueue, sFlashromMesg, ARRAY_COUNT(sFlashromMesg));
    osFlashInit();
    sFlashromFlashIsGood = true;
    if (SysFlashrom_CheckFlashType()) {
        sFlashromFlashIsGood = false;
        return -1;
    }
    return 0;
}

s32 SysFlashrom_ReadData(void* addr, s32 pageNum, s32 pageCount) {
    OSIoMesg msg;

    if (!SysFlashrom_FlashIsGood()) {
        return -1;
    }
    osInvalDCache(addr, pageCount * 128);
    osFlashReadArray(&msg, 0, pageNum, addr, pageCount, &sFlashromMesgQueue);
    osRecvMesg(&sFlashromMesgQueue, NULL, OS_MESG_BLOCK);
    return 0;
}

s32 SysFlashrom_ErasePage(u32 page) {
    if (!SysFlashrom_FlashIsGood()) {
        return -1;
    }
    return osFlashSectorErase(page);
}

#ifdef NON_MATCHING
// Stack, Regalloc, reorderings
s32 SysFlashrom_WriteData(u8* addr, u32 pageNum, s32 pageCount) {
    OSIoMesg sp40;
    s32 temp_v0;
    s32 i;

    if (!SysFlashrom_FlashIsGood()) {
        return -1;
    }
    if (pageNum & 0x7F) {
        Fault_AddHungupAndCrash("../sys_flashrom.c", 275);
    }
    osWritebackDCache(addr, pageCount * 128);
    for (i = 0; i != pageCount; i++, pageNum++) {
        osFlashWriteBuffer(&sp40, 0, addr + i * 128, &sFlashromMesgQueue);
        osRecvMesg(&sFlashromMesgQueue, NULL, OS_MESG_BLOCK);
        if (pageNum) {}
        temp_v0 = osFlashWriteArray(pageNum);
        if (temp_v0 != 0) {
            return temp_v0;
        }
    }
    return 0;
}
#else
s32 SysFlashrom_WriteData(u8* addr, u32 pageNum, s32 pageCount);
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_flashrom/SysFlashrom_WriteData.s")
#endif

// TODO Remove Goto
s32 SysFlashrom_AttemptWrite(void* addr, s32 pageNum, s32 pageCount) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 i;

    if (!SysFlashrom_FlashIsGood()) {
        return -1;
    }
    osWritebackDCache(addr, pageCount * 128);
    i = 0;
loop_3:
    /*while(1)*/ {
        temp_v0 = SysFlashrom_ErasePage(pageNum);
        if (temp_v0 != 0) {
            if (i < 3) {
                i += 1;
                goto loop_3;
            }
            return temp_v0;
        }
        temp_v0_2 = SysFlashrom_WriteData(addr, pageNum, pageCount);
        if (temp_v0_2 != 0) {
            if (i < 3) {
                i += 1;
                goto loop_3;
            }
            return temp_v0_2;
        }
    }
    return 0;
}

s32 func_80185BE4(void* data, void* addr, u32 pageCount) {
    u32 size;
    u32 i;

    for (i = 0; i < pageCount * 128; i += 4) {
        if ((*(s32*)data & *(s32*)addr) != *(s32*)addr) {
            return 0;
        }
    }
    return 1;
}

s32 func_80185C24(void* addr, u32 pageNum, u32 pageCount) {
    void* data;
    size_t size;
    s32 ret;

    if (!SysFlashrom_FlashIsGood()) {
        return -1;
    }
    size = pageCount * 128;
    data = SystemArena_Malloc(size);
    if (data == 0) {
        ret = SysFlashrom_AttemptWrite(addr, pageNum, pageCount);
    } else {
        SysFlashrom_ReadData(data, pageNum, pageCount);
        if (bcmp(data, addr, size) == 0) {
            ret = 0;
        } else {
            if (func_80185BE4(data, addr, pageCount) != 0) {
                ret = SysFlashrom_AttemptWrite(addr, pageNum, pageCount);
            } else {
                ret = SysFlashrom_AttemptWrite(addr, pageNum, pageCount);
            }
            if (ret == 0) {
                SysFlashrom_ReadData(data, pageNum, pageCount);
                if (bcmp(data, addr, size) == 0) {
                    ret = 0;
                } else {
                    ret = -1;
                }
            }
        }
        SystemArena_Free(data);
    }
    return ret;
}

void SysFlashrom_ThreadEntry(void* arg) {
    s80185D40* param_1 = (s80185D40*)arg;
    switch (param_1->unk0) {
        case 1:
            param_1->unk4 = func_80185C24(param_1->addr, param_1->pageNum, param_1->pageCount);
            osSendMesg(&param_1->messageQueue, param_1->unk4, 1);
            break;
        case 2:
            param_1->unk4 = SysFlashrom_ReadData(param_1->addr, param_1->pageNum, param_1->pageCount);
            osSendMesg(&param_1->messageQueue, param_1->unk4, 1);
            break;
    }
}

#ifdef NON_MATCHING
// Data ordering
void SysFlashrom_CreateRequest(u8* addr, u32 pageNum, u32 pageCount) {
    if (SysFlashrom_FlashIsGood() != 0) {
        sFlashromRequest.unk0 = 1;
        sFlashromRequest.addr = addr;
        sFlashromRequest.pageNum = pageNum;
        sFlashromRequest.pageCount = pageCount;
        osCreateMesgQueue(&sFlashromRequest.messageQueue, D_801FD034, ARRAY_COUNT(D_801FD034));
        StackCheck_Init(&sSysFlashromStackInfo, sSysFlashromStack, sSysFlashromStack + sizeof(sSysFlashromStack), 0,
                        0x100, "sys_flashrom");
        osCreateThread(&sSysFlashromThread, 0xD, SysFlashrom_ThreadEntry, &sFlashromRequest,
                       sSysFlashromStack + sizeof(sSysFlashromStack), 0xD);
        osStartThread(&sSysFlashromThread);
    }
}
#else
void SysFlashrom_CreateRequest(u8* addr, u32 pageNum, u32 pageCount);
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_flashrom/SysFlashrom_CreateRequest.s")
#endif

s32 func_80185EC4(void) {
    OSMesgQueue* queue = &sFlashromRequest.messageQueue;
    
    if (!SysFlashrom_FlashIsGood()) {
        return -1;
    }
    return (queue->msgCount <= queue->validCount);
}

s32 SysFlashrom_DestroyThread(void) {
    if (!SysFlashrom_FlashIsGood()) {
        return -1;
    }
    osRecvMesg(&sFlashromRequest.messageQueue, NULL, OS_MESG_BLOCK);
    osDestroyThread(&sSysFlashromThread);
    StackCheck_Cleanup(&sSysFlashromStackInfo);
    return sFlashromRequest.unk4;
}

void func_80185F64(void* addr, u32 pageNum, u32 pageCount) {
    SysFlashrom_CreateRequest(addr, pageNum, pageCount);
    SysFlashrom_DestroyThread();
}

