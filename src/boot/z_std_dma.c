/**
 * @file z_std_dma.c
 *
 * This file implements a system for structuring the ROM image and retrieving data. It is designed to have the same
 * external interface regardless of whether the ROM segments are compressed or not.
 *
 * The ROM image is partitioned into regions that are entered into the DMA data table `gDmaDataTable`. External code
 * does not directly address locations on the ROM image directly, instead a "Virtual ROM" addressing is used. Virtual
 * ROM is defined to be the ROM address of a segment in a totally uncompressed ROM. For uncompressed ROMs, "physical"
 * ROM and VROM addresses coincide. The DMA data table converts VROM to ROM addresses so that code may exclusively use
 * VROM addresses even if the ROM is compressed.
 *
 * External code typically submits requests to the DMA Manager asking for a transfer in terms of Virtual ROM; the DMA
 * Manager translates this to the physical ROM address, performs the transfer to RAM and decompresses the data if
 * required.
 * Requests are processed in the order they are received and may be submitted both synchronously and asynchronously.
 *
 * There are some additional provisions to ensure that audio DMA is particularly high-speed, the audio data is assumed
 * to be uncompressed and the request queue and address translation is skipped.
 */
#include "prevent_bss_reordering.h"
#include "z64dma.h"

#include "carthandle.h"
#include "fault.h"
#include "macros.h"
#include "segment_symbols.h"
#include "stack.h"
#include "libu64/stackcheck.h"
#include "yaz0.h"
#include "z64thread.h"

size_t gDmaMgrDmaBuffSize = DMAMGR_DEFAULT_BUFSIZE;

StackEntry sDmaMgrStackInfo;
u16 sNumDmaEntries;
OSMesgQueue sDmaMgrMsgQueue;
OSMesg sDmaMgrMsgBuf[32];
OSThread sDmaMgrThread;
STACK(sDmaMgrStack, 0x500);

/**
 * Transfer `size` bytes from physical ROM address `rom` to `ram`.
 *
 * This function is intended for internal use only, however it is possible to use this function externally in which
 * case it behaves as a synchronous transfer, data is available as soon as this function returns.
 *
 * Transfers are divided into chunks based on the current value of `gDmaMgrDmaBuffSize` to avoid congestion of the PI
 * so that higher priority transfers can still be carried out in a timely manner. The transfers are sent in a queue to
 * the OS PI Manager which performs the transfer.
 *
 * @return 0 if successful, -1 if the DMA could not be queued with the PI Manager.
 */
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

/**
 * Callback function to facilitate audio DMA. Audio DMA does not use the request queue as audio data is often needed
 * very soon after the request is sent, requiring a higher priority method for enqueueing a DMA on the OS PI command
 * queue.
 *
 * @param pihandle Cartridge ROM PI Handle.
 * @param mb IO Message describing the transfer.
 * @param direction Read or write.
 * @return 0 if the IO Message was successfully put on the OS PI command queue, < 0 otherwise
 */
s32 DmaMgr_AudioDmaHandler(OSPiHandle* pihandle, OSIoMesg* mb, s32 direction) {
    return osEPiStartDma(pihandle, mb, direction);
}

DmaEntry* DmaMgr_FindDmaEntry(uintptr_t vrom) {
    DmaEntry* entry;

    for (entry = gDmaDataTable; entry->file.vromEnd != 0; entry++) {
        if ((vrom >= entry->file.vromStart) && (vrom < entry->file.vromEnd)) {
            return entry;
        }
    }

    return NULL;
}

s32 DmaMgr_TranslateVromToRom(uintptr_t vrom) {
    DmaEntry* entry = DmaMgr_FindDmaEntry(vrom);

    if (entry != NULL) {
        if (entry->romEnd == 0) {
            return vrom + entry->romStart - entry->file.vromStart;
        }

        if (vrom == entry->file.vromStart) {
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
    DmaEntry* entry;
    s32 index = DmaMgr_FindDmaIndex(vrom);

    if ((index >= 0) && (index < sNumDmaEntries)) {
        entry = &gDmaDataTable[index];
        if (entry->romEnd == 0) {
            // romEnd of 0 indicates that the file is uncompressed. Files that are stored uncompressed can have
            // only part of their content loaded into RAM, so DMA only the requested region.
            if (entry->file.vromEnd < (vrom + size)) {
                // Error, vrom + size ends up in a different file than it started in
                Fault_AddHungupAndCrash("../z_std_dma.c", 499);
            }
            DmaMgr_DmaRomToRam((entry->romStart + vrom) - entry->file.vromStart, ram, size);
        } else {
            // File is compressed. Files that are stored compressed must be loaded into RAM all at once.

            romSize = entry->romEnd - entry->romStart;
            romStart = entry->romStart;

            if (vrom != entry->file.vromStart) {
                // Error, requested vrom is not the start of a file
                Fault_AddHungupAndCrash("../z_std_dma.c", 518);
            }

            if (size != (entry->file.vromEnd - entry->file.vromStart)) {
                // Error, only part of the file was requested
                Fault_AddHungupAndCrash("../z_std_dma.c", 525);
            }

            // Reduce the thread priority and decompress the file, the decompression routine handles the DMA
            // in chunks. Restores the thread priority when done.
            osSetThreadPri(NULL, Z_PRIORITY_DMAMGR_LOW);
            Yaz0_Decompress(romStart, ram, romSize);
            osSetThreadPri(NULL, Z_PRIORITY_DMAMGR);
        }
    } else {
        // Error, invalid index
        Fault_AddHungupAndCrash("../z_std_dma.c", 558);
    }
}

void DmaMgr_ThreadEntry(void* arg) {
    OSMesg msg;
    DmaRequest* req;

    while (true) {
        // Wait for DMA Requests to arrive from other threads
        osRecvMesg(&sDmaMgrMsgQueue, &msg, OS_MESG_BLOCK);

        if (msg == NULL) {
            break;
        }

        req = (DmaRequest*)msg;

        DmaMgr_ProcessRequest(req);

        // Notify the sender that the request has been processed
        if (req->notifyQueue != NULL) {
            osSendMesg(req->notifyQueue, req->notifyMsg, OS_MESG_NOBLOCK);
        }
    }
}

/**
 * Submit an asynchronous DMA request. Unlike other DMA requests, this will not block the
 * current thread. Data arrival is not immediate however, ensure that the request has completed by awaiting a message
 * sent to `queue` when the DMA operation has completed.
 *
 * @param req DMA request, filled out internally.
 * @param ram Location in DRAM for data to be written.
 * @param vrom Virtual ROM location for data to be read.
 * @param size Transfer size.
 * @param queue Message queue to notify with `msg` once the transfer is complete.
 * @param msg Message to send to `queue` once the transfer is complete.
 * @return -2 if Irq is in NMI reset state, 0 otherwise
 */
s32 DmaMgr_RequestAsync(DmaRequest* req, void* ram, uintptr_t vrom, size_t size, UNK_TYPE4 unused, OSMesgQueue* queue,
                        OSMesg msg) {
    if (gIrqMgrResetStatus >= IRQ_RESET_STATUS_NMI) {
        return -2;
    }

    req->vromAddr = vrom;
    req->dramAddr = ram;
    req->size = size;
    req->unk14 = 0;
    req->notifyQueue = queue;
    req->notifyMsg = msg;

    osSendMesg(&sDmaMgrMsgQueue, (OSMesg)req, OS_MESG_BLOCK);

    return 0;
}

/**
 * Submit a synchronous DMA request. This will block the current thread until the requested transfer is complete. Data
 * is immediately available as soon as this function returns.
 *
 * @param ram Location in DRAM for data to be written.
 * @param vrom Virtual ROM location for data to be read.
 * @param size Transfer size.
 * @return 0
 */
s32 DmaMgr_RequestSync(void* ram, uintptr_t vrom, size_t size) {
    DmaRequest req;
    OSMesgQueue queue;
    OSMesg msg[1];
    s32 ret;

    osCreateMesgQueue(&queue, msg, ARRAY_COUNT(msg));

    ret = DmaMgr_RequestAsync(&req, ram, vrom, size, 0, &queue, NULL);
    if (ret == -1) { // DmaMgr_RequestAsync does not return -1
        return ret;
    }

    osRecvMesg(&queue, NULL, OS_MESG_BLOCK);

    return 0;
}

void DmaMgr_Init(void) {
    DmaMgr_DmaRomToRam(SEGMENT_ROM_START(dmadata), gDmaDataTable, SEGMENT_ROM_SIZE(dmadata));

    {
        DmaEntry* entry = gDmaDataTable;
        s32 index = 0;

        while (entry->file.vromEnd != 0) {
            entry++;
            index++;
        }

        sNumDmaEntries = index;
    }

    osCreateMesgQueue(&sDmaMgrMsgQueue, sDmaMgrMsgBuf, ARRAY_COUNT(sDmaMgrMsgBuf));
    StackCheck_Init(&sDmaMgrStackInfo, sDmaMgrStack, STACK_TOP(sDmaMgrStack), 0, 0x100, "dmamgr");
    osCreateThread(&sDmaMgrThread, Z_THREAD_ID_DMAMGR, DmaMgr_ThreadEntry, NULL, STACK_TOP(sDmaMgrStack),
                   Z_PRIORITY_DMAMGR);

    osStartThread(&sDmaMgrThread);
}

void DmaMgr_Stop(void) {
    osSendMesg(&sDmaMgrMsgQueue, NULL, OS_MESG_BLOCK);
}
