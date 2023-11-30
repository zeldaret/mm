#include "z64effect_ss.h"

#include "tha.h"
#include "loadfragment.h"
#include "z64malloc.h"
#include "global.h"

void EffectSS_ResetEntry(EffectSs* particle);

EffectSsInfo sEffectSsInfo = { NULL, 0, 0 };

void EffectSS_Init(PlayState* play, s32 numEntries) {
    u32 i;
    EffectSs* effectsSs;
    EffectSsOverlay* overlay;

    sEffectSsInfo.dataTable = (EffectSs*)THA_AllocTailAlign16(&play->state.tha, numEntries * sizeof(EffectSs));
    sEffectSsInfo.searchIndex = 0;
    sEffectSsInfo.size = numEntries;

    for (effectsSs = &sEffectSsInfo.dataTable[0]; effectsSs < &sEffectSsInfo.dataTable[sEffectSsInfo.size];
         effectsSs++) {
        EffectSS_ResetEntry(effectsSs);
    }

    overlay = &gParticleOverlayTable[0];
    for (i = 0; i < EFFECT_SS_MAX; i++) {
        overlay->loadedRamAddr = NULL;
        overlay++;
    }
}

void EffectSS_Clear(PlayState* play) {
    u32 i;
    EffectSs* effectsSs;
    EffectSsOverlay* overlay;
    void* addr;

    sEffectSsInfo.dataTable = NULL;
    sEffectSsInfo.searchIndex = 0;
    sEffectSsInfo.size = 0;

    //! @bug: Effects left in the table are not properly deleted, as dataTable was just set to NULL and size to 0
    for (effectsSs = &sEffectSsInfo.dataTable[0]; effectsSs < &sEffectSsInfo.dataTable[sEffectSsInfo.size];
         effectsSs++) {
        EffectSS_Delete(effectsSs);
    }

    // Free memory from loaded particle overlays
    overlay = &gParticleOverlayTable[0];
    for (i = 0; i < EFFECT_SS_MAX; i++) {
        addr = overlay->loadedRamAddr;
        if (addr != NULL) {
            ZeldaArena_Free(addr);
        }

        overlay->loadedRamAddr = NULL;
        overlay++;
    }
}

EffectSs* EffectSS_GetTable() {
    return sEffectSsInfo.dataTable;
}

void EffectSS_Delete(EffectSs* effectSs) {
    if (effectSs->flags & 2) {
        AudioSfx_StopByPos(&effectSs->pos);
    }

    if (effectSs->flags & 4) {
        AudioSfx_StopByPos(&effectSs->vec);
    }

    EffectSS_ResetEntry(effectSs);
}

void EffectSS_ResetEntry(EffectSs* particle) {
    u32 i;

    particle->type = EFFECT_SS_MAX;
    particle->accel.x = particle->accel.y = particle->accel.z = 0;
    particle->velocity.x = particle->velocity.y = particle->velocity.z = 0;
    particle->vec.x = particle->vec.y = particle->vec.z = 0;
    particle->pos.x = particle->pos.y = particle->pos.z = 0;
    particle->life = -1;
    particle->flags = 0;
    particle->priority = 128;
    particle->draw = NULL;
    particle->update = NULL;
    particle->gfx = NULL;
    particle->actor = NULL;

    for (i = 0; i < ARRAY_COUNT(particle->regs); i++) {
        particle->regs[i] = 0;
    }
}

s32 EffectSS_FindFreeSpace(s32 priority, s32* tableEntry) {
    s32 foundFree;
    s32 i;

    if (sEffectSsInfo.searchIndex >= sEffectSsInfo.size) {
        sEffectSsInfo.searchIndex = 0;
    }

    // Search for a unused entry
    i = sEffectSsInfo.searchIndex;
    foundFree = false;
    while (true) {
        if (sEffectSsInfo.dataTable[i].life == -1) {
            foundFree = true;
            break;
        }

        i++;

        if (i >= sEffectSsInfo.size) {
            i = 0; // Loop around the whole table
        }

        // After a full loop, break out
        if (i == sEffectSsInfo.searchIndex) {
            break;
        }
    }

    if (foundFree == true) {
        *tableEntry = i;
        return false;
    }

    // If all slots are in use, search for a slot with a lower priority
    // Note that a lower priority is representend by a higher value
    i = sEffectSsInfo.searchIndex;
    while (true) {
        // Equal priority should only be considered "lower" if flag 0 is set
        if ((priority <= sEffectSsInfo.dataTable[i].priority) &&
            !((priority == sEffectSsInfo.dataTable[i].priority) && (sEffectSsInfo.dataTable[i].flags & 1))) {
            break;
        }

        i++;

        if (i >= sEffectSsInfo.size) {
            i = 0; // Loop around the whole table
        }

        // After a full loop, return 1 to indicate that we failed to find a suitable slot
        if (i == sEffectSsInfo.searchIndex) {
            return true;
        }
    }

    *tableEntry = i;
    return false;
}

void EffectSS_Copy(PlayState* play, EffectSs* effectsSs) {
    s32 index;

    if (FrameAdvance_IsEnabled(&play->state) != true) {
        if (EffectSS_FindFreeSpace(effectsSs->priority, &index) == 0) {
            sEffectSsInfo.searchIndex = index + 1;
            sEffectSsInfo.dataTable[index] = *effectsSs;
        }
    }
}

void EffectSs_Spawn(PlayState* play, s32 type, s32 priority, void* initData) {
    s32 index;
    u32 overlaySize;
    EffectSsOverlay* overlayEntry = &gParticleOverlayTable[type];
    EffectSsInit* initInfo;

    if (EffectSS_FindFreeSpace(priority, &index) != 0) {
        // Abort because we couldn't find a suitable slot to add this effect in
        return;
    }

    sEffectSsInfo.searchIndex = index + 1;
    overlaySize = (uintptr_t)overlayEntry->vramEnd - (uintptr_t)overlayEntry->vramStart;

    if (overlayEntry->vramStart == NULL) {
        initInfo = overlayEntry->initInfo;
    } else {
        if (overlayEntry->loadedRamAddr == NULL) {
            overlayEntry->loadedRamAddr = ZeldaArena_MallocR(overlaySize);

            if (overlayEntry->loadedRamAddr == NULL) {
                return;
            }

            Overlay_Load(overlayEntry->vromStart, overlayEntry->vromEnd, overlayEntry->vramStart, overlayEntry->vramEnd,
                         overlayEntry->loadedRamAddr);
        }

        initInfo = (void*)(uintptr_t)((overlayEntry->initInfo != NULL)
                                          ? (void*)((uintptr_t)overlayEntry->initInfo -
                                                    (intptr_t)((uintptr_t)overlayEntry->vramStart -
                                                               (uintptr_t)overlayEntry->loadedRamAddr))
                                          : NULL);
    }

    if (initInfo->init != NULL) {
        // Delete the previous effect in the slot, in case the slot wasn't free
        EffectSS_Delete(&sEffectSsInfo.dataTable[index]);

        sEffectSsInfo.dataTable[index].type = type;
        sEffectSsInfo.dataTable[index].priority = priority;

        if (initInfo->init(play, index, &sEffectSsInfo.dataTable[index], initData) == 0) {
            EffectSS_ResetEntry(&sEffectSsInfo.dataTable[index]);
        }
    }
}

void EffectSS_UpdateParticle(PlayState* play, s32 index) {
    EffectSs* particle = &sEffectSsInfo.dataTable[index];

    if (particle->update != NULL) {
        particle->velocity.x += particle->accel.x;
        particle->velocity.y += particle->accel.y;
        particle->velocity.z += particle->accel.z;

        particle->pos.x += particle->velocity.x;
        particle->pos.y += particle->velocity.y;
        particle->pos.z += particle->velocity.z;

        particle->update(play, index, particle);
    }
}

void EffectSS_UpdateAllParticles(PlayState* play) {
    s32 i;

    for (i = 0; i < sEffectSsInfo.size; i++) {
        if (sEffectSsInfo.dataTable[i].life > -1) {
            sEffectSsInfo.dataTable[i].life--;

            if (sEffectSsInfo.dataTable[i].life < 0) {
                EffectSS_Delete(&sEffectSsInfo.dataTable[i]);
            }
        }

        if (sEffectSsInfo.dataTable[i].life > -1) {
            EffectSS_UpdateParticle(play, i);
        }
    }
}

void EffectSS_DrawParticle(PlayState* play, s32 index) {
    EffectSs* entry = &sEffectSsInfo.dataTable[index];

    if (entry->draw != NULL) {
        entry->draw(play, index, entry);
    }
}

void EffectSS_DrawAllParticles(PlayState* play) {
    Lights* lights = LightContext_NewLights(&play->lightCtx, play->state.gfxCtx);
    s32 i;

    Lights_BindAll(lights, play->lightCtx.listHead, NULL, play);
    Lights_Draw(lights, play->state.gfxCtx);

    for (i = 0; i < sEffectSsInfo.size; i++) {
        if (sEffectSsInfo.dataTable[i].life > -1) {
            if ((sEffectSsInfo.dataTable[i].pos.x > BGCHECK_Y_MAX) ||
                (sEffectSsInfo.dataTable[i].pos.x < BGCHECK_Y_MIN) ||
                (sEffectSsInfo.dataTable[i].pos.y > BGCHECK_Y_MAX) ||
                (sEffectSsInfo.dataTable[i].pos.y < BGCHECK_Y_MIN) ||
                (sEffectSsInfo.dataTable[i].pos.z > BGCHECK_Y_MAX) ||
                (sEffectSsInfo.dataTable[i].pos.z < BGCHECK_Y_MIN)) {
                EffectSS_Delete(&sEffectSsInfo.dataTable[i]);
            } else {
                EffectSS_DrawParticle(play, i);
            }
        }
    }
}

s16 func_800B096C(s16 arg0, s16 arg1, s32 arg2) {
    s16 ret = (arg2 == 0) ? arg1 : arg0 + (s32)((arg1 - arg0) / (f32)arg2);

    return ret;
}

s16 func_800B09D0(s16 arg0, s16 arg1, f32 arg2) {
    return arg2 * (arg1 - arg0) + arg0;
}

u8 func_800B0A24(u8 arg0, u8 arg1, f32 arg2) {
    return arg2 * ((f32)arg1 - (f32)arg0) + arg0;
}
