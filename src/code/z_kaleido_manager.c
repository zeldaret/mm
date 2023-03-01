#include "global.h"
#include "z64load.h"

#define KALEIDO_OVERLAY(name)                                                                        \
    {                                                                                                \
        NULL, SEGMENT_ROM_START(ovl_##name), SEGMENT_ROM_END(ovl_##name), SEGMENT_START(ovl_##name), \
            SEGMENT_END(ovl_##name), 0, #name,                                                       \
    }

KaleidoMgrOverlay gKaleidoMgrOverlayTable[] = {
    KALEIDO_OVERLAY(kaleido_scope),
    KALEIDO_OVERLAY(player_actor),
};

void* sKaleidoAreaPtr = NULL;
KaleidoMgrOverlay* gKaleidoMgrCurOvl = NULL;
FaultAddrConvClient sKaleidoMgrFaultAddrConvClient;

void* KaleidoManager_FaultAddrConv(void* address, void* param) {
    uintptr_t addr = address;
    KaleidoMgrOverlay* kaleidoMgrOvl = gKaleidoMgrCurOvl;
    uintptr_t ramConv;
    void* ramStart;
    uintptr_t diff;
    s32 i;

    if (kaleidoMgrOvl != NULL) {
        diff = VRAM_PTR_SIZE(kaleidoMgrOvl);
        ramStart = kaleidoMgrOvl->loadedRamAddr;
        ramConv = (uintptr_t)kaleidoMgrOvl->vramStart - (uintptr_t)ramStart;

        if (ramStart != NULL) {
            if (addr >= (uintptr_t)ramStart && addr < (uintptr_t)ramStart + diff) {
                return addr + ramConv;
            }
        }
    }
    return NULL;
}

void KaleidoManager_LoadOvl(KaleidoMgrOverlay* ovl) {
    ovl->loadedRamAddr = sKaleidoAreaPtr;
    Load2_LoadOverlay(ovl->vromStart, ovl->vromEnd, ovl->vramStart, ovl->vramEnd, ovl->loadedRamAddr);
    ovl->offset = (uintptr_t)ovl->loadedRamAddr - (uintptr_t)ovl->vramStart;
    gKaleidoMgrCurOvl = ovl;
}

void KaleidoManager_ClearOvl(KaleidoMgrOverlay* ovl) {
    if (ovl->loadedRamAddr != NULL) {
        ovl->offset = 0;
        bzero(ovl->loadedRamAddr, VRAM_PTR_SIZE(ovl));
        ovl->loadedRamAddr = NULL;
        gKaleidoMgrCurOvl = NULL;
    }
}

void KaleidoManager_Init(PlayState* play) {
    s32 largestSize = 0;
    s32 size;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(gKaleidoMgrOverlayTable); i++) {
        size = VRAM_PTR_SIZE(&gKaleidoMgrOverlayTable[i]);
        if (size > largestSize) {
            largestSize = size;
        }
    }

    sKaleidoAreaPtr = THA_AllocEndAlign16(&play->state.heap, largestSize);
    gKaleidoMgrCurOvl = NULL;
    Fault_AddAddrConvClient(&sKaleidoMgrFaultAddrConvClient, KaleidoManager_FaultAddrConv, NULL);
}

void KaleidoManager_Destroy() {
    Fault_RemoveAddrConvClient(&sKaleidoMgrFaultAddrConvClient);

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
            if (((uintptr_t)vram >= (uintptr_t)ovl->vramStart) && ((uintptr_t)ovl->vramEnd >= (uintptr_t)vram)) {
                KaleidoManager_LoadOvl(ovl);
                return (void*)((uintptr_t)vram + ovl->offset);
            }
            ovl++;
        } while (ovl != (KaleidoMgrOverlay*)&sKaleidoAreaPtr);

        return NULL;
    } else if (((uintptr_t)vram < (uintptr_t)gKaleidoMgrCurOvl->vramStart) ||
               ((uintptr_t)vram >= (uintptr_t)gKaleidoMgrCurOvl->vramEnd)) {
        return NULL;
    }

    return (void*)((uintptr_t)vram + gKaleidoMgrCurOvl->offset);
}
