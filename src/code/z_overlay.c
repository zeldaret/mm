/**
 * @file z_overlay.c
 *
 * Functions for handling transition overlays in memory
 *
 * Status codes returned from TransitionOverlay_Load and TransitionOverlay_Free:
 *
 * -1 : failed allocation or null reference
 *  0 : successfully loaded/freed overlay
 *  1 : successfully added/removed instance
 *  2 : overlay is loaded but has no instances (?) TODO: Figure out why this exists
 *  3 : internal overlay, so always loaded
 */

#include "global.h"
#include "loadfragment.h"

void* TransitionOverlay_VramToRam(TransitionOverlay* overlayEntry, void* vramAddr) {
    void* loadedRamAddr = Lib_PhysicalToVirtual(overlayEntry->loadInfo.addr);

    if ((loadedRamAddr != NULL) && (vramAddr >= overlayEntry->vramStart) && (vramAddr < overlayEntry->vramEnd)) {
        return (void*)(((uintptr_t)loadedRamAddr - (uintptr_t)overlayEntry->vramStart) + (uintptr_t)vramAddr);
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
    if (Lib_PhysicalToVirtual(overlayEntry->loadInfo.addr) == NULL) {
        loadedRamAddr = ZeldaArena_Malloc((uintptr_t)overlayEntry->vramEnd - (uintptr_t)overlayEntry->vramStart);

        if (loadedRamAddr == NULL) {
            return -1;
        }
        Overlay_Load(overlayEntry->vromStart, overlayEntry->vromEnd, overlayEntry->vramStart, overlayEntry->vramEnd,
                     loadedRamAddr);
        overlayEntry->loadInfo.addr = Lib_VirtualToPhysical(loadedRamAddr);
        overlayEntry->loadInfo.count = 1;
        return 0;
    } else {
        count = overlayEntry->loadInfo.count;
        if (count != 0) {
            count++;
            overlayEntry->loadInfo.count = count;
            if (count == 0) {
                return 2;
            } else {
                return 1;
            }
        }
        return 2;
    }
}

s32 TransitionOverlay_Free(TransitionOverlay* overlayEntry) {
    s32 count;
    void* loadedRamAddr;

    if (overlayEntry->vromStart == 0) {
        return 3;
    }
    loadedRamAddr = Lib_PhysicalToVirtual(overlayEntry->loadInfo.addr);
    if (loadedRamAddr != NULL) {
        count = overlayEntry->loadInfo.count;
        if (count != 0) {
            count--;
            overlayEntry->loadInfo.count = count;
            if (count == 0) {
                ZeldaArena_Free(loadedRamAddr);
                overlayEntry->loadInfo.addr = Lib_VirtualToPhysical(NULL);
                return 0;
            }
            return 1;
        }
        return 2;
    }
    return -1;
}

void TransitionOverlay_ClearLoadInfo(TransitionOverlay* overlayEntry) {
    overlayEntry->loadInfo.word = 0; // Equivalent to overlayEntry->loadInfo.count = 0, overlayEntry->loadInfo.addr = 0;
}

void TransitionOverlay_SetSegment(TransitionOverlay* overlayEntry, void* vramStart, void* vramEnd, uintptr_t vromStart,
                                  uintptr_t vromEnd) {
    overlayEntry->vramStart = vramStart;
    overlayEntry->vramEnd = vramEnd;
    overlayEntry->vromStart = vromStart;
    overlayEntry->vromEnd = vromEnd;
}
