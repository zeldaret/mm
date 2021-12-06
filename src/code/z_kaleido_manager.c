#include "global.h"

#define KALEIDO_OVERLAY(name)                                                                                \
    {                                                                                                        \
        NULL, (u32)_ovl_##name##SegmentRomStart, (u32)_ovl_##name##SegmentRomEnd, _ovl_##name##SegmentStart, \
            _ovl_##name##SegmentEnd, 0, #name,                                                               \
    }

KaleidoMgrOverlay gKaleidoMgrOverlayTable[] = {
    KALEIDO_OVERLAY(kaleido_scope),
    KALEIDO_OVERLAY(player_actor),
};

void* sKaleidoAreaPtr = NULL;
KaleidoMgrOverlay* gKaleidoMgrCurOvl = NULL;
FaultAddrConvClient sKaleidoAreaFaultClient;

void* KaleidoManager_FaultAddrConvFunc(void* address, void* param) {
    u8* ptr = address;
    KaleidoMgrOverlay* ovl = &gKaleidoMgrCurOvl[0];
    u8* ramStart;
    u8* ramEnd;
    size_t size;
    u32 offset;

    if (ovl != NULL) {
        size = (u8*)ovl->vramEnd - (u8*)ovl->vramStart;
        ramStart = ovl->loadedRamAddr;
        ramEnd = ramStart + size;
        offset = (u8*)ovl->vramStart - ramStart;
        if (ramStart != NULL) {
            if (ptr >= ramStart && ptr < ramEnd) {
                return ptr + offset;
            }
        }
    }
    return NULL;
}

void KaleidoManager_LoadOvl(KaleidoMgrOverlay* ovl) {
    ovl->loadedRamAddr = sKaleidoAreaPtr;
    Load2_LoadOverlay(ovl->vromStart, ovl->vromEnd, ovl->vramStart, ovl->vramEnd, ovl->loadedRamAddr);
    ovl->offset = (u32)ovl->loadedRamAddr - (u32)ovl->vramStart;
    gKaleidoMgrCurOvl = ovl;
}

void KaleidoManager_ClearOvl(KaleidoMgrOverlay* ovl) {
    if (ovl->loadedRamAddr != NULL) {
        ovl->offset = 0;
        bzero(ovl->loadedRamAddr, (u32)ovl->vramEnd - (u32)ovl->vramStart);
        ovl->loadedRamAddr = NULL;
        gKaleidoMgrCurOvl = NULL;
    }
}

void KaleidoManager_Init(GlobalContext* globalCtx) {
    s32 largestSize = 0;
    s32 size;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(gKaleidoMgrOverlayTable); i++) {
        size = (u32)gKaleidoMgrOverlayTable[i].vramEnd - (u32)gKaleidoMgrOverlayTable[i].vramStart;
        if (size > largestSize) {
            largestSize = size;
        }
    }

    sKaleidoAreaPtr = THA_AllocEndAlign16(&globalCtx->state.heap, largestSize);
    gKaleidoMgrCurOvl = NULL;
    Fault_AddAddrConvClient(&sKaleidoAreaFaultClient, KaleidoManager_FaultAddrConvFunc, NULL);
}

void KaleidoManager_Destroy() {
    Fault_RemoveAddrConvClient(&sKaleidoAreaFaultClient);

    if (gKaleidoMgrCurOvl != NULL) {
        KaleidoManager_ClearOvl(gKaleidoMgrCurOvl);
        gKaleidoMgrCurOvl = NULL;
    }

    sKaleidoAreaPtr = NULL;
}

void* KaleidoManager_GetRamAddr(void* vram) {
    if (gKaleidoMgrCurOvl == NULL) {
        s32 pad[2];
        KaleidoMgrOverlay* ovl = &gKaleidoMgrOverlayTable[0];

        do {
            if (((u32)vram >= (u32)ovl->vramStart) && ((u32)ovl->vramEnd >= (u32)vram)) {
                KaleidoManager_LoadOvl(ovl);
                return (void*)((u32)vram + ovl->offset);
            }
            ovl++;
        } while (ovl != (KaleidoMgrOverlay*)&sKaleidoAreaPtr);

        return NULL;
    } else if (((u32)vram < (u32)gKaleidoMgrCurOvl->vramStart) || ((u32)vram >= (u32)gKaleidoMgrCurOvl->vramEnd)) {
        return NULL;
    }

    return (void*)((u32)vram + gKaleidoMgrCurOvl->offset);
}
