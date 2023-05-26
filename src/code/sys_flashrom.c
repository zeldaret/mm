#include "global.h"
#include "stack.h"
#include "stackcheck.h"
#include "system_malloc.h"

//#include "prevent_bss_reordering.h"

OSMesgQueue sFlashromMesgQueue;
OSMesg sFlashromMesg[1];
s32 sFlashromFlashIsGood;
s32 sFlashromVendor;

STACK(sSysFlashromStack, 0x1000);
StackEntry sSysFlashromStackInfo;
OSThread sSysFlashromThread;
FlashromRequest sFlashromRequest;
OSMesg sSysFlashromMsgBuf[1];

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
        if ((flashVendor == FLASH_VERSION_MX_PROTO_A) || (flashVendor == FLASH_VERSION_MX_A) ||
            (flashVendor == FLASH_VERSION_MX_C) || (flashVendor == FLASH_VERSION_MEI) ||
            (flashVendor == FLASH_VERSION_MX_B_AND_D)) {
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

s32 SysFlashrom_WriteData(u8* addr, u32 pageNum, u32 pageCount) {
    OSIoMesg msg;
    s32 result;
    u32 i;

    if (!SysFlashrom_FlashIsGood()) {
        return -1;
    }
    if (pageNum & 0x7F) {
        Fault_AddHungupAndCrash("../sys_flashrom.c", 275);
    }
    osWritebackDCache(addr, pageCount * 128);
    for (i = 0; i != pageCount; i++) {
        osFlashWriteBuffer(&msg, 0, addr + i * 128, &sFlashromMesgQueue);
        osRecvMesg(&sFlashromMesgQueue, NULL, OS_MESG_BLOCK);
        result = osFlashWriteArray(i + pageNum);
        if (result != 0) {
            return result;
        }
    }
    return 0;
}

s32 SysFlashrom_AttemptWrite(void* addr, s32 pageNum, s32 pageCount) {
    s32 result;
    s32 i;

    if (!SysFlashrom_FlashIsGood()) {
        return -1;
    }
    osWritebackDCache(addr, pageCount * 128);
    i = 0;
failRetry:
    result = SysFlashrom_ErasePage(pageNum);
    if (result != 0) {
        if (i < 3) {
            i++;
            goto failRetry;
        }
        return result;
    }
    result = SysFlashrom_WriteData(addr, pageNum, pageCount);
    if (result != 0) {
        if (i < 3) {
            i++;
            goto failRetry;
        }
        return result;
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

s32 SysFlashrom_WriteData2(void* addr, u32 pageNum, u32 pageCount) {
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
            //! @bug Will attempt to write regardless of the result of the function call.
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
    FlashromRequest* req = (FlashromRequest*)arg;
    switch (req->requestType) {
        case 1:
            req->response = SysFlashrom_WriteData2(req->addr, req->pageNum, req->pageCount);
            osSendMesg(&req->messageQueue, req->response, OS_MESG_BLOCK);
            break;
        case 2:
            req->response = SysFlashrom_ReadData(req->addr, req->pageNum, req->pageCount);
            osSendMesg(&req->messageQueue, req->response, OS_MESG_BLOCK);
            break;
    }
}

void SysFlashrom_CreateRequest(u8* addr, u32 pageNum, u32 pageCount) {
    FlashromRequest* req = &sFlashromRequest;
    if (SysFlashrom_FlashIsGood() != 0) {
        req->requestType = 1;
        req->addr = addr;
        req->pageNum = pageNum;
        req->pageCount = pageCount;
        osCreateMesgQueue(&req->messageQueue, sSysFlashromMsgBuf, ARRAY_COUNT(sSysFlashromMsgBuf));
        StackCheck_Init(&sSysFlashromStackInfo, sSysFlashromStack, STACK_TOP(sSysFlashromStack), 0,
                        0x100, "sys_flashrom");
        osCreateThread(&sSysFlashromThread, Z_THREAD_ID_FLASHROM, SysFlashrom_ThreadEntry, req,
                       STACK_TOP(sSysFlashromStack), Z_PRIORITY_FLASHROM);
        osStartThread(&sSysFlashromThread);
    }
}

s32 SysFlashrom_IsQueueFull(void) {
    OSMesgQueue* queue = &sFlashromRequest.messageQueue;

    if (!SysFlashrom_FlashIsGood()) {
        return -1;
    }
    return MQ_IS_FULL(queue); //queue->msgCount <= queue->validCount;
}

s32 SysFlashrom_DestroyThread(void) {
    if (!SysFlashrom_FlashIsGood()) {
        return -1;
    }
    osRecvMesg(&sFlashromRequest.messageQueue, NULL, OS_MESG_BLOCK);
    osDestroyThread(&sSysFlashromThread);
    StackCheck_Cleanup(&sSysFlashromStackInfo);
    return sFlashromRequest.response;
}

void func_80185F64(void* addr, u32 pageNum, u32 pageCount) {
    SysFlashrom_CreateRequest(addr, pageNum, pageCount);
    SysFlashrom_DestroyThread();
}
