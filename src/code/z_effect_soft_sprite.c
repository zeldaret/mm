#include <ultra64.h>
#include <global.h>

void EffectSS_Init(GlobalContext* globalCtx, s32 numEntries) {
    u32 i;
    EffectSs* effectsSs;
    ParticleOverlay* overlay;

    EffectSS2Info.data_table = (EffectSs*)THA_AllocEndAlign16(&globalCtx->state.heap, numEntries * sizeof(EffectSs));
    EffectSS2Info.searchIndex = 0;
    EffectSS2Info.size = numEntries;

    for (effectsSs = &EffectSS2Info.data_table[0]; effectsSs < &EffectSS2Info.data_table[EffectSS2Info.size];
         effectsSs++) {
        EffectSS_ResetEntry(effectsSs);
    }

    overlay = &particleOverlayTable[0];
    for (i = 0; i < EFFECT_SS2_TYPE_LAST_LABEL; i++) {
        overlay->loadedRamAddr = NULL;
        overlay++;
    }
}

void EffectSS_Clear(GlobalContext* globalCtx) {
    u32 i;
    EffectSs* effectsSs;
    ParticleOverlay* overlay;
    void* addr;

    EffectSS2Info.data_table = NULL;
    EffectSS2Info.searchIndex = 0;
    EffectSS2Info.size = 0;

    // This code is completely useless, as data_table was just set to NULL and size to 0
    for (effectsSs = EffectSS2Info.data_table; effectsSs < EffectSS2Info.data_table + EffectSS2Info.size; effectsSs++) {
        EffectSS_Delete(effectsSs);
    }

    // Free memory from loaded particle overlays
    overlay = &particleOverlayTable[0];
    for (i = 0; i < EFFECT_SS2_TYPE_LAST_LABEL; i++) {
        addr = overlay->loadedRamAddr;
        if (addr != NULL) {
            zelda_free(addr);
        }

        overlay->loadedRamAddr = 0;
        overlay++;
    }
}

EffectSs* EffectSS_GetTable() {
    return EffectSS2Info.data_table;
}

void EffectSS_Delete(EffectSs* effectSs) {
    if (effectSs->flags & 2) {
        func_801A72CC(&effectSs->pos);
    }

    if (effectSs->flags & 4) {
        func_801A72CC(&effectSs->vec);
    }

    EffectSS_ResetEntry(effectSs);
}

void EffectSS_ResetEntry(EffectSs* particle) {
    u32 i;

    particle->type = EFFECT_SS2_TYPE_LAST_LABEL;
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

    if (EffectSS2Info.searchIndex >= EffectSS2Info.size) {
        EffectSS2Info.searchIndex = 0;
    }

    // Search for a unused entry
    i = EffectSS2Info.searchIndex;
    foundFree = false;
    while (true) {
        if (EffectSS2Info.data_table[i].life == -1) {
            foundFree = true;
            break;
        }

        i++;

        if (i >= EffectSS2Info.size) {
            i = 0; // Loop around the whole table
        }

        // After a full loop, break out
        if (i == EffectSS2Info.searchIndex) {
            break;
        }
    }

    if (foundFree == true) {
        *tableEntry = i;
        return false;
    }

    // If all slots are in use, search for a slot with a lower priority
    // Note that a lower priority is representend by a higher value
    i = EffectSS2Info.searchIndex;
    while (true) {
        // Equal priority should only be considered "lower" if flag 0 is set
        if ((priority <= EffectSS2Info.data_table[i].priority) &&
            !((priority == EffectSS2Info.data_table[i].priority) && (EffectSS2Info.data_table[i].flags & 1))) {
            break;
        }

        i++;

        if (i >= EffectSS2Info.size) {
            i = 0; // Loop around the whole table
        }

        // After a full loop, return 1 to indicate that we failed to find a suitable slot
        if (i == EffectSS2Info.searchIndex) {
            return true;
        }
    }

    *tableEntry = i;
    return false;
}

void EffectSS_Copy(GlobalContext* globalCtx, EffectSs* effectsSs) {
    s32 index;

    if (FrameAdvance_IsEnabled(globalCtx) != true) {
        if (EffectSS_FindFreeSpace(effectsSs->priority, &index) == 0) {
            EffectSS2Info.searchIndex = index + 1;
            EffectSS2Info.data_table[index] = *effectsSs;
        }
    }
}

void EffectSs_Spawn(GlobalContext* globalCtx, s32 type, s32 priority, void* initData) {
    s32 index;
    u32 overlaySize;
    ParticleOverlay* entry = &particleOverlayTable[type];
    ParticleOverlayInfo* overlayInfo;

    if (EffectSS_FindFreeSpace(priority, &index) != 0) {
        // Abort because we couldn't find a suitable slot to add this effect in
        return;
    }

    EffectSS2Info.searchIndex = index + 1;
    overlaySize = (u32)entry->vramEnd - (u32)entry->vramStart;

    if (entry->vramStart == NULL) {
        overlayInfo = entry->overlayInfo;
    } else {
        if (entry->loadedRamAddr == NULL) {
            entry->loadedRamAddr = zelda_mallocR(overlaySize);

            if (entry->loadedRamAddr == NULL) {
                return;
            }

            Load2_LoadOverlay(entry->vromStart, entry->vromEnd, entry->vramStart, entry->vramEnd, entry->loadedRamAddr);
        }

        overlayInfo = (void*)(u32)(
            entry->overlayInfo != NULL
                ? (ParticleOverlayInfo*)(-((u32)entry->vramStart - (u32)entry->loadedRamAddr) + (u32)entry->overlayInfo)
                : NULL);
    }

    if (overlayInfo->init != NULL) {
        // Delete the previous effect in the slot, in case the slot wasn't free
        EffectSS_Delete(&EffectSS2Info.data_table[index]);

        EffectSS2Info.data_table[index].type = type;
        EffectSS2Info.data_table[index].priority = priority;

        if (overlayInfo->init(globalCtx, index, &EffectSS2Info.data_table[index], initData) == 0) {
            EffectSS_ResetEntry(&EffectSS2Info.data_table[index]);
        }
    }
}

void EffectSS_UpdateParticle(GlobalContext* globalCtx, s32 index) {
    EffectSs* particle = &EffectSS2Info.data_table[index];

    if (particle->update != NULL) {
        particle->velocity.x += particle->accel.x;
        particle->velocity.y += particle->accel.y;
        particle->velocity.z += particle->accel.z;

        particle->pos.x += particle->velocity.x;
        particle->pos.y += particle->velocity.y;
        particle->pos.z += particle->velocity.z;

        particle->update(globalCtx, index, particle);
    }
}

void EffectSS_UpdateAllParticles(GlobalContext* globalCtx) {
    s32 i;

    for (i = 0; i < EffectSS2Info.size; i++) {
        if (EffectSS2Info.data_table[i].life > -1) {
            EffectSS2Info.data_table[i].life--;

            if (EffectSS2Info.data_table[i].life < 0) {
                EffectSS_Delete(&EffectSS2Info.data_table[i]);
            }
        }

        if (EffectSS2Info.data_table[i].life > -1) {
            EffectSS_UpdateParticle(globalCtx, i);
        }
    }
}

void EffectSS_DrawParticle(GlobalContext* globalCtx, s32 index) {
    EffectSs* entry = &EffectSS2Info.data_table[index];

    if (entry->draw != NULL) {
        entry->draw(globalCtx, index, entry);
    }
}

void EffectSS_DrawAllParticles(GlobalContext* globalCtx) {
    Lights* lights = LightContext_NewLights(&globalCtx->lightCtx, globalCtx->state.gfxCtx);
    s32 i;

    Lights_BindAll(lights, globalCtx->lightCtx.listHead, NULL, globalCtx);
    Lights_Draw(lights, globalCtx->state.gfxCtx);

    for (i = 0; i < EffectSS2Info.size; i++) {
        if (EffectSS2Info.data_table[i].life > -1) {
            if ((EffectSS2Info.data_table[i].pos.x > 32000.0f) || (EffectSS2Info.data_table[i].pos.x < -32000.0f) ||
                (EffectSS2Info.data_table[i].pos.y > 32000.0f) || (EffectSS2Info.data_table[i].pos.y < -32000.0f) ||
                (EffectSS2Info.data_table[i].pos.z > 32000.0f) || (EffectSS2Info.data_table[i].pos.z < -32000.0f)) {
                EffectSS_Delete(&EffectSS2Info.data_table[i]);
            } else {
                EffectSS_DrawParticle(globalCtx, i);
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
