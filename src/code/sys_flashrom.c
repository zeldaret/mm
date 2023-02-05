#include "global.h"
#include "stack.h"
#include "stackcheck.h"
#include "system_malloc.h"

OSMesgQueue sFlashromMesgQueue;
OSMesg sFlashromMesg;
s32 D_801FBE2C;
s32 sFlashromVendor;

u8 sSysFlashromStack[0x1000];
StackEntry sSysFlashromStackEntry;
OSThread sSysFlashromThread;
s80185D40 D_801FD008;
OSMesg D_801FD034;

s32 func_801857C0(void) {
    return D_801FBE2C;
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

    if (func_801857C0() == 0) {
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
    osCreateMesgQueue(&sFlashromMesgQueue, &sFlashromMesg, 1);
    osFlashInit();
    D_801FBE2C = 1;
    if (SysFlashrom_CheckFlashType() != 0) {
        D_801FBE2C = 0;
        return -1;
    }
    return 0;
}

s32 SysFlashrom_ReadData(void* addr, s32 pageNum, s32 pageCount) {
    OSIoMesg msg;

    if (func_801857C0() == 0) {
        return -1;
    }
    osInvalDCache(addr, pageCount * 128);
    osFlashReadArray(&msg, 0, pageNum, addr, pageCount, &sFlashromMesgQueue);
    osRecvMesg(&sFlashromMesgQueue, NULL, OS_MESG_BLOCK);
    return 0;
}

s32 SysFlashrom_ErasePage(u32 page) {
    if (func_801857C0() == 0) {
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

    if (func_801857C0() == 0) {
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

    if (func_801857C0() == 0) {
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

    if (func_801857C0() == 0) {
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
void SysFlashrom_CreateRequest(u8* arg0, u32 arg1, u32 arg2) {
    if (func_801857C0() != 0) {
        D_801FD008.unk0 = 1;
        D_801FD008.addr = arg0;
        D_801FD008.pageNum = arg1;
        D_801FD008.pageCount = arg2;
        osCreateMesgQueue(&D_801FD008.messageQueue, &D_801FD034, 1);
        StackCheck_Init(&sSysFlashromStackEntry, sSysFlashromStack, sSysFlashromStack + sizeof(sSysFlashromStack), 0,
                        0x100, "sys_flashrom");
        osCreateThread(&sSysFlashromThread, 0xD, SysFlashrom_ThreadEntry, &D_801FD008,
                       sSysFlashromStack + sizeof(sSysFlashromStack), 0xD);
        osStartThread(&sSysFlashromThread);
    }
}
#else
void SysFlashrom_CreateRequest(u8* arg0, u32 arg1, u32 arg2);
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_flashrom/SysFlashrom_CreateRequest.s")
#endif

#ifdef NON_MATCHING
s32 func_80185EC4(void) {
    if (func_801857C0() == 0) {
        return -1;
    }
    return (D_801FD008.messageQueue.msgCount <= D_801FD008.messageQueue.validCount);
}
#else
s32 func_80185EC4(void);
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_flashrom/func_80185EC4.s")
#endif

s32 SysFlashrom_DestroyThread(void) {
    if (func_801857C0() == 0) {
        return -1;
    }
    osRecvMesg(&D_801FD008.messageQueue, NULL, OS_MESG_BLOCK);
    osDestroyThread(&sSysFlashromThread);
    StackCheck_Cleanup(&sSysFlashromStackEntry);
    return D_801FD008.unk4;
}

void func_80185F64(void* arg0, s32 arg1, s32 arg2) {
    SysFlashrom_CreateRequest(arg0, arg1, arg2);
    SysFlashrom_DestroyThread();
}
