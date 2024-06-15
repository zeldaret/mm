#ifndef Z64DMA_H
#define Z64DMA_H

#include "ultra64.h"

#include "stdint.h"

#include "romfile.h"
#include "unk.h"

typedef struct {
    /* 0x00 */ uintptr_t vromAddr; // VROM address (source)
    /* 0x04 */ void* dramAddr;     // DRAM address (destination)
    /* 0x08 */ size_t size;        // File Transfer size
    /* 0x0C */ char* filename;     // Filename for debugging
    /* 0x10 */ s32 line;           // Line for debugging
    /* 0x14 */ s32 unk14;
    /* 0x18 */ OSMesgQueue* notifyQueue; // Message queue for the notification message
    /* 0x1C */ OSMesg notifyMsg;         // Completion notification message
} DmaRequest; // size = 0x20

typedef struct {
    /* 0x0 */ RomFile file;
    /* 0x8 */ uintptr_t romStart;
    /* 0xC */ uintptr_t romEnd;
} DmaEntry; // size = 0x10

#define DMAMGR_DEFAULT_BUFSIZE ALIGN16(0x2000)

extern DmaEntry gDmaDataTable[];
extern size_t gDmaMgrDmaBuffSize;

// Standard DMA Requests
s32 DmaMgr_RequestAsync(DmaRequest* req, void* ram, uintptr_t vrom, size_t size, UNK_TYPE unused, OSMesgQueue* queue, void* msg);
s32 DmaMgr_RequestSync(void* ram, uintptr_t vrom, size_t size);

// Special-purpose DMA Requests

s32 DmaMgr_DmaRomToRam(uintptr_t rom, void* ram, size_t size);
s32 DmaMgr_TranslateVromToRom(uintptr_t vrom);
s32 DmaMgr_AudioDmaHandler(OSPiHandle* pihandle, OSIoMesg* mb, s32 direction);
const char* func_800809F4(uintptr_t vrom);

// Thread Management

void DmaMgr_Init(void);
void DmaMgr_Stop(void);

#endif
