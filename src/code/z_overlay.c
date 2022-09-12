#include "global.h"
#include "z64load.h"

// Overlay_VramToLoaded
void* func_801651B0(TransitionOverlay* overlayEntry, void* vramAddr) {
    void* loadedRamAddr = Lib_PhysicalToVirtualNull(overlayEntry->loadedRamAddr);

    if ((loadedRamAddr != NULL) && (vramAddr >= overlayEntry->vramStart) && (vramAddr < overlayEntry->vramEnd)) {
        return ((uintptr_t)loadedRamAddr - (uintptr_t)overlayEntry->vramStart) + (uintptr_t)vramAddr;
    }
    return vramAddr;
}

// Overlay_VramToLoadedArray
void func_80165224(TransitionOverlay* overlayEntry, void** vramAddrs, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        vramAddrs[i] = func_801651B0(overlayEntry, vramAddrs[i]);
    }
}

// Overlay_LoadOverlay
s32 func_80165288(TransitionOverlay* overlayEntry) {
    s32 count;
    void* loadedRamAddr;

    if (overlayEntry->vromStart == 0) {
        return 3;
    }
    if (Lib_PhysicalToVirtualNull(overlayEntry->loadedRamAddr) == NULL) {
        loadedRamAddr = ZeldaArena_Malloc(VRAM_PTR_SIZE(overlayEntry));

        if (loadedRamAddr == NULL) {
            return -1;
        }
        Load2_LoadOverlay(overlayEntry->vromStart, overlayEntry->vromEnd, overlayEntry->vramStart,
                          overlayEntry->vramEnd, loadedRamAddr);
        overlayEntry->loadedRamAddr = Lib_PhysicalToVirtual(loadedRamAddr);
        overlayEntry->count = 1;
        return 0;
    }
    count = overlayEntry->count;
    if (count != 0) {
        count++;
        overlayEntry->count = count;
        if (count == 0) {
            return 2;
        } else {
            return 1;
        }
    } else {
        return 2;
    }
}

// Overlay_FreeOverlay
s32 func_8016537C(TransitionOverlay* overlayEntry) {
    s32 count;
    void* loadedRamAddr;

    if (overlayEntry->vromStart == 0) {
        return 3;
    }
    loadedRamAddr = Lib_PhysicalToVirtualNull(overlayEntry->loadedRamAddr);
    if (loadedRamAddr != NULL) {
        count = overlayEntry->count;
        if (count != 0) {
            count--;
            overlayEntry->count = count;
            if (count == 0) {
                ZeldaArena_Free(loadedRamAddr);
                overlayEntry->loadedRamAddr = Lib_PhysicalToVirtual(NULL);
                return 0;
            }
            return 1;
        }
        return 2;
    }
    return -1;
}

// Overlay_ClearLoadInfo
void func_80165438(TransitionOverlay* overlayEntry) {
    overlayEntry->loadInfo = 0;
}

// Overlay_SetSegment
void func_80165444(TransitionOverlay* overlayEntry, void* vramStart, void* vramEnd, u32 vromStart, u32 vromEnd) {
    overlayEntry->vramStart = vramStart;
    overlayEntry->vramEnd = vramEnd;
    overlayEntry->vromStart = vromStart;
    overlayEntry->vromEnd = vromEnd;
}
