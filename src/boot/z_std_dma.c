#include "z64dma.h"

#include "carthandle.h"
#include "fault.h"
#include "macros.h"
#include "segment_symbols.h"
#include "stack.h"
#include "stackcheck.h"
#include "yaz0.h"
#include "z64thread.h"

size_t gDmaMgrDmaBuffSize = DMAMGR_DEFAULT_BUFSIZE;

StackEntry sDmaMgrStackInfo;
u16 sNumDmaEntries;
OSMesgQueue sDmaMgrMsgQueue;
OSMesg sDmaMgrMsgs[32];
OSThread sDmaMgrThread;
STACK(sDmaMgrStack, 0x500);

s32 DmaMgr_DmaRomToRam(uintptr_t rom, void* ram, size_t size) {
    OSIoMesg ioMsg;
    OSMesgQueue queue;
    OSMesg msg[1];
    s32 ret;
    size_t buffSize = gDmaMgrDmaBuffSize;

    osInvalDCache(ram, size);
    osCreateMesgQueue(&queue, msg, ARRAY_COUNT(msg));

    if (buffSize != 0) {
        while (buffSize < size) {
            ioMsg.hdr.pri = OS_MESG_PRI_NORMAL;
            ioMsg.hdr.retQueue = &queue;
            ioMsg.devAddr = rom;
            ioMsg.dramAddr = ram;
            ioMsg.size = buffSize;
            ret = osEPiStartDma(gCartHandle, &ioMsg, OS_READ);
            if (ret != 0) {
                goto end;
            }

            osRecvMesg(&queue, NULL, OS_MESG_BLOCK);
            size -= buffSize;
            rom += buffSize;
            ram = (u8*)ram + buffSize;
        }
    }
    ioMsg.hdr.pri = OS_MESG_PRI_NORMAL;
    ioMsg.hdr.retQueue = &queue;
    ioMsg.devAddr = rom;
    ioMsg.dramAddr = ram;
    ioMsg.size = size;
    ret = osEPiStartDma(gCartHandle, &ioMsg, OS_READ);
    if (ret != 0) {
        goto end;
    }

    osRecvMesg(&queue, NULL, OS_MESG_BLOCK);

    osInvalDCache(ram, size);

end:
    return ret;
}

s32 DmaMgr_AudioDmaHandler(OSPiHandle* pihandle, OSIoMesg* mb, s32 direction) {
    return osEPiStartDma(pihandle, mb, direction);
}

DmaEntry* DmaMgr_FindDmaEntry(uintptr_t vrom) {
    DmaEntry* curr;

    for (curr = gDmaDataTable; curr->vromEnd != 0; curr++) {
        if (vrom < curr->vromStart) {
            continue;
        }
        if (vrom >= curr->vromEnd) {
            continue;
        }

        return curr;
    }

    return NULL;
}

u32 DmaMgr_TranslateVromToRom(uintptr_t vrom) {
    DmaEntry* entry = DmaMgr_FindDmaEntry(vrom);

    if (entry != NULL) {
        if (entry->romEnd == 0) {
            return vrom + entry->romStart - entry->vromStart;
        }

        if (vrom == entry->vromStart) {
            return entry->romStart;
        }

        return -1;
    }

    return -1;
}

s32 DmaMgr_FindDmaIndex(uintptr_t vrom) {
    DmaEntry* entry = DmaMgr_FindDmaEntry(vrom);

    if (entry != NULL) {
        return entry - gDmaDataTable;
    }

    return -1;
}

const char* func_800809F4(uintptr_t vrom) {
    return "??";
}

void DmaMgr_ProcessRequest(DmaRequest* req) {
    uintptr_t vrom = req->vromAddr;
    void* ram = req->dramAddr;
    size_t size = req->size;
    uintptr_t romStart;
    size_t romSize;
    DmaEntry* dmaEntry;
    s32 index = DmaMgr_FindDmaIndex(vrom);

    if ((index >= 0) && (index < sNumDmaEntries)) {
        dmaEntry = &gDmaDataTable[index];
        if (dmaEntry->romEnd == 0) {
            if (dmaEntry->vromEnd < (vrom + size)) {
                Fault_AddHungupAndCrash("../z_std_dma.c", 499);
            }
            DmaMgr_DmaRomToRam((dmaEntry->romStart + vrom) - dmaEntry->vromStart, ram, size);
            return;
        }

        romSize = dmaEntry->romEnd - dmaEntry->romStart;
        romStart = dmaEntry->romStart;

        if (vrom != dmaEntry->vromStart) {
            Fault_AddHungupAndCrash("../z_std_dma.c", 518);
        }

        if (size != (dmaEntry->vromEnd - dmaEntry->vromStart)) {
            Fault_AddHungupAndCrash("../z_std_dma.c", 525);
        }

        osSetThreadPri(NULL, Z_PRIORITY_DMAMGR_LOW);
        Yaz0_Decompress(romStart, ram, romSize);
        osSetThreadPri(NULL, Z_PRIORITY_DMAMGR);
    } else {
        Fault_AddHungupAndCrash("../z_std_dma.c", 558);
    }
}

void DmaMgr_ThreadEntry(void* arg) {
    OSMesg msg;
    DmaRequest* req;

    while (true) {
        osRecvMesg(&sDmaMgrMsgQueue, &msg, OS_MESG_BLOCK);

        if (msg == NULL) {
            break;
        }

        req = (DmaRequest*)msg;

        DmaMgr_ProcessRequest(req);
        if (req->notifyQueue) {
            osSendMesg(req->notifyQueue, req->notifyMsg, OS_MESG_NOBLOCK);
        }
    }
}

s32 DmaMgr_SendRequest(DmaRequest* request, void* vramStart, uintptr_t vromStart, size_t size, UNK_TYPE4 unused,
                       OSMesgQueue* queue, OSMesg msg) {
    if (gIrqMgrResetStatus >= 2) {
        return -2;
    }

    request->vromAddr = vromStart;
    request->dramAddr = vramStart;
    request->size = size;
    request->unk14 = 0;
    request->notifyQueue = queue;
    request->notifyMsg = msg;

    osSendMesg(&sDmaMgrMsgQueue, request, OS_MESG_BLOCK);

    return 0;
}

s32 DmaMgr_RequestSync(void* vramStart, uintptr_t vromStart, size_t size) {
    DmaRequest req;
    OSMesgQueue queue;
    OSMesg msg[1];
    s32 ret;

    osCreateMesgQueue(&queue, msg, ARRAY_COUNT(msg));

    ret = DmaMgr_SendRequest(&req, vramStart, vromStart, size, 0, &queue, NULL);
    if (ret == -1) {
        return ret;
    }

    osRecvMesg(&queue, NULL, OS_MESG_BLOCK);

    return 0;
}

void DmaMgr_Init(void) {
    DmaMgr_DmaRomToRam(SEGMENT_ROM_START(dmadata), gDmaDataTable, SEGMENT_ROM_SIZE(dmadata));

    {
        DmaEntry* iter = gDmaDataTable;
        s32 index = 0;

        while (iter->vromEnd != 0) {
            iter++;
            index++;
        }

        sNumDmaEntries = index;
    }

    osCreateMesgQueue(&sDmaMgrMsgQueue, sDmaMgrMsgs, ARRAY_COUNT(sDmaMgrMsgs));
    StackCheck_Init(&sDmaMgrStackInfo, sDmaMgrStack, STACK_TOP(sDmaMgrStack), 0, 0x100, "dmamgr");
    osCreateThread(&sDmaMgrThread, Z_THREAD_ID_DMAMGR, DmaMgr_ThreadEntry, NULL, STACK_TOP(sDmaMgrStack),
                   Z_PRIORITY_DMAMGR);

    osStartThread(&sDmaMgrThread);
}

void DmaMgr_Destroy(void) {
    osSendMesg(&sDmaMgrMsgQueue, NULL, OS_MESG_BLOCK);
}
