#include <ultra64.h>
#include <global.h>

u32 sDmaMgrDmaBuffSize = 0x2000;

s32 DmaMgr_DMARomToRam(u32 rom, void* ram, u32 size) {
    OSIoMesg ioMsg;
    OSMesgQueue queue;
    OSMesg msg[1];
    s32 ret;
    u32 buffSize = sDmaMgrDmaBuffSize;

    osInvalDCache(ram, size);
    osCreateMesgQueue(&queue, msg, ARRAY_COUNT(msg));

    if (buffSize != 0) {
        while (buffSize < size) {
            ioMsg.hdr.pri = 0;
            ioMsg.hdr.retQueue = &queue;
            ioMsg.devAddr = (u32)rom;
            ioMsg.dramAddr = ram;
            ioMsg.size = buffSize;
            ret = osEPiStartDma(gCartHandle, &ioMsg, 0);
            if (ret) {
                goto END;
            }

            osRecvMesg(&queue, NULL, 1);
            size -= buffSize;
            rom = rom + buffSize;
            ram = (u8*)ram + buffSize;
        }
    }
    ioMsg.hdr.pri = 0;
    ioMsg.hdr.retQueue = &queue;
    ioMsg.devAddr = (u32)rom;
    ioMsg.dramAddr = ram;
    ioMsg.size = (u32)size;
    ret = osEPiStartDma(gCartHandle, &ioMsg, 0);
    if (ret) {
        goto END;
    }

    osRecvMesg(&queue, NULL, 1);

    osInvalDCache(ram, size);

END:
    return ret;
}

void DmaMgr_DmaCallback0(OSPiHandle* pihandle, OSIoMesg* mb, s32 direction) {
    osEPiStartDma(pihandle, mb, direction);
}

DmaEntry* DmaMgr_FindDmaEntry(u32 vrom) {
    DmaEntry* curr;

    for (curr = dmadata; curr->vromEnd != 0; curr++) {
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

u32 DmaMgr_TranslateVromToRom(u32 vrom) {
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

s32 DmaMgr_FindDmaIndex(u32 vrom) {
    DmaEntry* entry = DmaMgr_FindDmaEntry(vrom);

    if (entry != NULL) {
        return entry - dmadata;
    }

    return -1;
}

const char* func_800809F4(u32 a0) {
    return "??";
}

void DmaMgr_ProcessMsg(DmaRequest* req) {
    u32 vrom;
    void* ram;
    u32 size;
    u32 romStart;
    u32 romSize;
    DmaEntry* dmaEntry;
    s32 index;

    vrom = req->vromAddr;
    ram = req->dramAddr;
    size = req->size;

    index = DmaMgr_FindDmaIndex(vrom);

    if ((index >= 0) && (index < numDmaEntries)) {
        dmaEntry = &dmadata[index];
        if (dmaEntry->romEnd == 0) {
            if (dmaEntry->vromEnd < (vrom + size)) {
                Fault_AddHungupAndCrash("../z_std_dma.c", 499);
            }
            DmaMgr_DMARomToRam((dmaEntry->romStart + vrom) - dmaEntry->vromStart, (u8*)ram, size);
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

        osSetThreadPri(NULL, 10);
        Yaz0_Decompress(romStart, ram, romSize);
        osSetThreadPri(NULL, 17);
    } else {
        Fault_AddHungupAndCrash("../z_std_dma.c", 558);
    }
}

void DmaMgr_ThreadEntry(void* a0) {
    OSMesg msg;
    DmaRequest* req;

    while (1) {
        osRecvMesg(&sDmaMgrMsgQueue, &msg, OS_MESG_BLOCK);

        if (msg == NULL) {
            break;
        }

        req = (DmaRequest*)msg;

        DmaMgr_ProcessMsg(req);
        if (req->notifyQueue) {
            osSendMesg(req->notifyQueue, req->notifyMsg, OS_MESG_NOBLOCK);
        }
    }
}

s32 DmaMgr_SendRequestImpl(DmaRequest* request, void* vramStart, u32 vromStart, u32 size, UNK_TYPE4 unused,
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

s32 DmaMgr_SendRequest0(void* vramStart, u32 vromStart, u32 size) {
    DmaRequest req;
    OSMesgQueue queue;
    OSMesg msg[1];
    s32 ret;

    osCreateMesgQueue(&queue, msg, ARRAY_COUNT(msg));

    ret = DmaMgr_SendRequestImpl(&req, vramStart, vromStart, size, 0, &queue, NULL);

    if (ret == -1) {
        return ret;
    } else {
        osRecvMesg(&queue, NULL, OS_MESG_BLOCK);
    }

    return 0;
}

const char dmamgrThreadName[] = "dmamgr";

#ifdef NON_MATCHING
// TODO missing a useless move initializing v0, and some reorderings
void DmaMgr_Start() {
    DmaEntry* iter;
    u32 idx;

    DmaMgr_DMARomToRam((u32)_dmadataSegmentRomStart, dmadata, (u32)(_dmadataSegmentRomEnd - _dmadataSegmentRomStart));

    for (iter = dmadata, idx = 0; iter->vromEnd != 0; iter++, idx++) {
        ;
    }

    numDmaEntries = idx;

    osCreateMesgQueue(&sDmaMgrMsgQueue, sDmaMgrMsgs, ARRAY_COUNT(sDmaMgrMsgs));
    StackCheck_Init(&sDmaMgrStackInfo, sDmaMgrStack, sDmaMgrStack + sizeof(sDmaMgrStack), 0, 256, dmamgrThreadName);
    osCreateThread(&sDmaMgrThread, Z_THREAD_ID_DMAMGR, DmaMgr_ThreadEntry, NULL, sDmaMgrStack + sizeof(sDmaMgrStack),
                   Z_PRIORITY_DMAMGR);
    osStartThread(&sDmaMgrThread);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/boot/z_std_dma/DmaMgr_Start.asm")
#endif

void DmaMgr_Stop() {
    osSendMesg(&sDmaMgrMsgQueue, NULL, OS_MESG_BLOCK);
}
