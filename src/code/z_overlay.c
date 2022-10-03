#include "global.h"
#include "z64load.h"

void* TransitionOverlay_VramToRam(TransitionOverlay* overlayEntry, void* vramAddr) {
    void* loadedRamAddr = Lib_PhysicalToVirtual(overlayEntry->load.addr);

    if ((loadedRamAddr != NULL) && (vramAddr >= overlayEntry->vramStart) && (vramAddr < overlayEntry->vramEnd)) {
        return ((uintptr_t)loadedRamAddr - (uintptr_t)overlayEntry->vramStart) + (uintptr_t)vramAddr;
    }
    return vramAddr;
}

void TransitionOverlay_VramToRamArray(TransitionOverlay* overlayEntry, void** vramAddrs, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        vramAddrs[i] = TransitionOverlay_VramToRam(overlayEntry, vramAddrs[i]);
    }
}

s32 TransitionOverlay_Load(TransitionOverlay* overlayEntry) {
    s32 count;
    void* loadedRamAddr;

    if (overlayEntry->vromStart == 0) {
        return 3;
    }
    if (Lib_PhysicalToVirtual(overlayEntry->load.addr) == NULL) {
        loadedRamAddr = ZeldaArena_Malloc(VRAM_PTR_SIZE(overlayEntry));

        if (loadedRamAddr == NULL) {
            return -1;
        }
        Load2_LoadOverlay(overlayEntry->vromStart, overlayEntry->vromEnd, overlayEntry->vramStart,
                          overlayEntry->vramEnd, loadedRamAddr);
        overlayEntry->load.addr = Lib_VirtualToPhysical(loadedRamAddr);
        overlayEntry->load.count = 1;
        return 0;
    }
    count = overlayEntry->load.count;
    if (count != 0) {
        count++;
        overlayEntry->load.count = count;
        if (count == 0) {
            return 2;
        } else {
            return 1;
        }
    } else {
        return 2;
    }
}

s32 TransitionOverlay_Free(TransitionOverlay* overlayEntry) {
    s32 count;
    void* loadedRamAddr;

    if (overlayEntry->vromStart == 0) {
        return 3;
    }
    loadedRamAddr = Lib_PhysicalToVirtual(overlayEntry->load.addr);
    if (loadedRamAddr != NULL) {
        count = overlayEntry->load.count;
        if (count != 0) {
            count--;
            overlayEntry->load.count = count;
            if (count == 0) {
                ZeldaArena_Free(loadedRamAddr);
                overlayEntry->load.addr = Lib_VirtualToPhysical(NULL);
                return 0;
            }
            return 1;
        }
        return 2;
    }
    return -1;
}

void TransitionOverlay_ClearLoadInfo(TransitionOverlay* overlayEntry) {
    overlayEntry->loadInfo = 0; // load.count = 0, load.addr = 0
}

void TransitionOverlay_SetSegment(TransitionOverlay* overlayEntry, void* vramStart, void* vramEnd, uintptr_t vromStart,
                                  uintptr_t vromEnd) {
    overlayEntry->vramStart = vramStart;
    overlayEntry->vramEnd = vramEnd;
    overlayEntry->vromStart = vromStart;
    overlayEntry->vromEnd = vromEnd;
}
