#include "global.h"

void* AudioHeap_SearchRegularCaches(s32 tableType, s32 cache, s32 id);
void AudioHeap_InitSampleCaches(size_t persistentSampleCacheSize, size_t temporarySampleCacheSize);
SampleCacheEntry* AudioHeap_AllocTemporarySampleCacheEntry(size_t size);
void AudioHeap_DiscardSampleCacheEntry(SampleCacheEntry* entry);
void AudioHeap_UnapplySampleCache(SampleCacheEntry* entry, SoundFontSample* sample);
SampleCacheEntry* AudioHeap_AllocPersistentSampleCacheEntry(size_t size);
void AudioHeap_DiscardSampleCaches(void);
void AudioHeap_DiscardSampleBank(s32 sampleBankId);
void AudioHeap_ApplySampleBankCacheInternal(s32 apply, s32 sampleBankId);
void AudioHeap_DiscardSampleBanks(void);
void AudioHeap_InitReverb(s32 reverbIndex, ReverbSettings* settings, s32 flags);

#define gTatumsPerBeat (gAudioTatumInit[1])

f32 func_8018B0F0(f32 arg0) {
    return 256.0f * gAudioContext.audioBufferParameters.unkUpdatesPerFrameScaled / arg0;
}

void func_8018B10C(void) {
    s32 i;

    gAudioContext.unk_3520[255] = func_8018B0F0(0.25f);
    gAudioContext.unk_3520[254] = func_8018B0F0(0.33f);
    gAudioContext.unk_3520[253] = func_8018B0F0(0.5f);
    gAudioContext.unk_3520[252] = func_8018B0F0(0.66f);
    gAudioContext.unk_3520[251] = func_8018B0F0(0.75f);

    for (i = 128; i < 251; i++) {
        gAudioContext.unk_3520[i] = func_8018B0F0(251 - i);
    }

    for (i = 16; i < 128; i++) {
        gAudioContext.unk_3520[i] = func_8018B0F0(4 * (143 - i));
    }

    for (i = 1; i < 16; i++) {
        gAudioContext.unk_3520[i] = func_8018B0F0(60 * (23 - i));
    }

    gAudioContext.unk_3520[0] = 0.0f;
}

void AudioHeap_ResetLoadStatus(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gAudioContext.fontLoadStatus); i++) {
        if (gAudioContext.fontLoadStatus[i] != LOAD_STATUS_5) {
            gAudioContext.fontLoadStatus[i] = LOAD_STATUS_0;
        }
    }

    for (i = 0; i < ARRAY_COUNT(gAudioContext.sampleFontLoadStatus); i++) {
        if (gAudioContext.sampleFontLoadStatus[i] != LOAD_STATUS_5) {
            gAudioContext.sampleFontLoadStatus[i] = LOAD_STATUS_0;
        }
    }

    for (i = 0; i < ARRAY_COUNT(gAudioContext.seqLoadStatus); i++) {
        if (gAudioContext.seqLoadStatus[i] != LOAD_STATUS_5) {
            gAudioContext.seqLoadStatus[i] = LOAD_STATUS_0;
        }
    }
}

void AudioHeap_DiscardFont(s32 fontId) {
    s32 i;

    for (i = 0; i < gAudioContext.numNotes; i++) {
        Note* note = &gAudioContext.notes[i];

        if (note->playbackState.fontId == fontId) {
            if ((note->playbackState.unk_04 == 0) && (note->playbackState.priority != 0)) {
                note->playbackState.parentLayer->enabled = false;
                note->playbackState.parentLayer->finished = true;
            }

            AudioPlayback_NoteDisable(note);
            AudioPlayback_AudioListRemove(&note->listItem);
            AudioSeq_AudioListPushBack(&gAudioContext.noteFreeLists.disabled, &note->listItem);
        }
    }
}

void AudioHeap_ReleaseNotesForFont(s32 fontId) {
    s32 i;

    for (i = 0; i < gAudioContext.numNotes; i++) {
        Note* note = &gAudioContext.notes[i];
        NotePlaybackState* playbackState = &note->playbackState;

        if (playbackState->fontId == fontId) {
            if (playbackState->priority != 0) {
                playbackState->priority = 1;
                playbackState->adsr.fadeOutVel = gAudioContext.audioBufferParameters.updatesPerFrameInv;
                playbackState->adsr.action.s.release = true;
            }
        }
    }
}

void AudioHeap_DiscardSequence(s32 seqId) {
    s32 i;

    for (i = 0; i < gAudioContext.audioBufferParameters.numSequencePlayers; i++) {
        if (gAudioContext.seqPlayers[i].enabled && gAudioContext.seqPlayers[i].seqId == seqId) {
            AudioSeq_SequencePlayerDisable(&gAudioContext.seqPlayers[i]);
        }
    }
}

/**
 * Perform a writeback from the L1 data cache to the ram.
 */
void* AudioHeap_WritebackDCache(void* addr, size_t size) {
    Audio_WritebackDCache(addr, size);
    if (addr) {}

    // KSEG0 to KSEG1 (ensures data is written straight to ram instead of the data cache)
    return OS_PHYSICAL_TO_K1(OS_K0_TO_PHYSICAL(addr));
}

/**
 * Attempt to allocated space on an external device. If no external device is available,
 * then allocate space on the pool provided in the argument.
 * Afterwards, zero all data pool the new allocated space
 */
void* AudioHeap_AllocZeroedAttemptExternal(AudioAllocPool* pool, size_t size) {
    void* addr = NULL;

    if (gAudioContext.externalPool.startAddr != NULL) {
        addr = AudioHeap_AllocZeroed(&gAudioContext.externalPool, size);
    }

    if (addr == NULL) {
        addr = AudioHeap_AllocZeroed(pool, size);
    }

    return addr;
}

/**
 * Attempt to allocated space on an external device. If no external device is available,
 * then allocate space on the pool provided in the argument
 */
void* AudioHeap_AllocAttemptExternal(AudioAllocPool* pool, size_t size) {
    void* addr = NULL;

    if (gAudioContext.externalPool.startAddr != NULL) {
        addr = AudioHeap_Alloc(&gAudioContext.externalPool, size);
    }

    if (addr == NULL) {
        addr = AudioHeap_Alloc(pool, size);
    }

    return addr;
}

void* AudioHeap_AllocDmaMemory(AudioAllocPool* pool, size_t size) {
    void* addr = AudioHeap_Alloc(pool, size);

    if (addr != NULL) {
        addr = AudioHeap_WritebackDCache(addr, size);
    }

    return addr;
}

void* AudioHeap_AllocDmaMemoryZeroed(AudioAllocPool* pool, size_t size) {
    void* addr = AudioHeap_AllocZeroed(pool, size);

    if (addr != NULL) {
        addr = AudioHeap_WritebackDCache(addr, size);
    }

    return addr;
}

/**
 * Allocates space on a pool contained withing the heap and sets all the allocated space to 0
 */
void* AudioHeap_AllocZeroed(AudioAllocPool* pool, size_t size) {
    u8* addr = AudioHeap_Alloc(pool, size);
    u8* ptr;

    if (addr != NULL) {
        for (ptr = addr; ptr < pool->curAddr; ptr++) {
            *ptr = 0;
        }
    }

    return addr;
}

/**
 * Tests the pool to see if the requested allocation would fit without actually allocating space.
 * Returns NULL if there is not enough space on the pool.
 * Else, return the address that would have been allocated
 */
void* AudioHeap_TestAlloc(AudioAllocPool* pool, size_t size) {
    u8* oldAddr = pool->curAddr;
    void* addr = AudioHeap_Alloc(pool, size);

    // remove allocation from pool
    if (addr != NULL) {
        pool->curAddr = oldAddr;
        pool->count--;
    }

    return addr;
}

/**
 * Allocates space on the pool contained withing the heap. If there is not enough space on the pool, return NULL
 */
void* AudioHeap_Alloc(AudioAllocPool* pool, size_t size) {
    size_t alignedSize = ALIGN16(size);
    u8* curAddr = pool->curAddr;

    if ((pool->startAddr + pool->size) >= (pool->curAddr + alignedSize)) {
        pool->curAddr += alignedSize;
    } else {
        return NULL;
    }

    pool->count++;
    return curAddr;
}

/**
 * Initialize a pool at the requested address with the requested size.
 * Store the metadata of this pool in AudioAllocPool* pool
 */
void AudioHeap_AllocPoolInit(AudioAllocPool* pool, void* addr, size_t size) {
    pool->curAddr = pool->startAddr = (u8*)ALIGN16((uintptr_t)addr);
    pool->size = size - ((uintptr_t)addr & 0xF);
    pool->count = 0;
}

void AudioHeap_ClearPersistentCache(AudioPersistentCache* persistent) {
    persistent->pool.count = 0;
    persistent->numEntries = 0;
    persistent->pool.curAddr = persistent->pool.startAddr;
}

void AudioHeap_ClearTemporaryCache(AudioTemporaryCache* temporary) {
    temporary->pool.count = 0;
    temporary->pool.curAddr = temporary->pool.startAddr;
    temporary->nextSide = 0;
    temporary->entries[0].addr = temporary->pool.startAddr;
    temporary->entries[1].addr = temporary->pool.startAddr + temporary->pool.size;
    temporary->entries[0].id = -1;
    temporary->entries[1].id = -1;
}

void AudioHeap_ResetPool(AudioAllocPool* pool) {
    pool->count = 0;
    pool->curAddr = pool->startAddr;
}

void AudioHeap_PopCache(s32 tableType) {
    AudioCache* loadedCache;
    AudioAllocPool* persistentHeap;
    AudioPersistentCache* persistent;
    void* entryAddr;
    u8* loadStatus;

    switch (tableType) {
        case SEQUENCE_TABLE:
            loadedCache = &gAudioContext.seqCache;
            loadStatus = gAudioContext.seqLoadStatus;
            break;

        case FONT_TABLE:
            loadedCache = &gAudioContext.fontCache;
            loadStatus = gAudioContext.fontLoadStatus;
            break;

        case SAMPLE_TABLE:
            loadedCache = &gAudioContext.sampleBankCache;
            loadStatus = gAudioContext.sampleFontLoadStatus;
            break;
    }

    persistent = &loadedCache->persistent;
    persistentHeap = &persistent->pool;

    if (persistent->numEntries == 0) {
        return;
    }

    entryAddr = persistent->entries[persistent->numEntries - 1].addr;
    persistentHeap->curAddr = entryAddr;
    persistentHeap->count--;

    if (tableType == SAMPLE_TABLE) {
        AudioHeap_DiscardSampleBank(persistent->entries[persistent->numEntries - 1].id);
    }
    if (tableType == FONT_TABLE) {
        AudioHeap_DiscardFont(persistent->entries[persistent->numEntries - 1].id);
    }

    loadStatus[persistent->entries[persistent->numEntries - 1].id] = LOAD_STATUS_0;
    persistent->numEntries--;
}

void AudioHeap_InitMainPool(size_t mainPoolSplitSize) {
    AudioHeap_AllocPoolInit(&gAudioContext.audioInitPool, gAudioContext.audioHeap, mainPoolSplitSize);
    AudioHeap_AllocPoolInit(&gAudioContext.audioSessionPool, gAudioContext.audioHeap + mainPoolSplitSize,
                            gAudioContext.audioHeapSize - mainPoolSplitSize);

    gAudioContext.externalPool.startAddr = NULL;
}

void AudioHeap_InitSessionPool(AudioSessionPoolSplit* split) {
    gAudioContext.audioSessionPool.curAddr = gAudioContext.audioSessionPool.startAddr;

    AudioHeap_AllocPoolInit(&gAudioContext.miscPool,
                            AudioHeap_Alloc(&gAudioContext.audioSessionPool, split->miscPoolSize), split->miscPoolSize);
    AudioHeap_AllocPoolInit(&gAudioContext.cachePool,
                            AudioHeap_Alloc(&gAudioContext.audioSessionPool, split->cachePoolSize),
                            split->cachePoolSize);
}

void AudioHeap_InitCachePool(AudioCachePoolSplit* split) {
    gAudioContext.cachePool.curAddr = gAudioContext.cachePool.startAddr;

    AudioHeap_AllocPoolInit(&gAudioContext.persistentCommonPool,
                            AudioHeap_Alloc(&gAudioContext.cachePool, split->persistentCommonPoolSize),
                            split->persistentCommonPoolSize);
    AudioHeap_AllocPoolInit(&gAudioContext.temporaryCommonPool,
                            AudioHeap_Alloc(&gAudioContext.cachePool, split->temporaryCommonPoolSize),
                            split->temporaryCommonPoolSize);
}

void AudioHeap_InitPersistentCache(AudioCommonPoolSplit* split) {
    gAudioContext.persistentCommonPool.curAddr = gAudioContext.persistentCommonPool.startAddr;

    AudioHeap_AllocPoolInit(&gAudioContext.seqCache.persistent.pool,
                            AudioHeap_Alloc(&gAudioContext.persistentCommonPool, split->seqCacheSize),
                            split->seqCacheSize);
    AudioHeap_AllocPoolInit(&gAudioContext.fontCache.persistent.pool,
                            AudioHeap_Alloc(&gAudioContext.persistentCommonPool, split->fontCacheSize),
                            split->fontCacheSize);
    AudioHeap_AllocPoolInit(&gAudioContext.sampleBankCache.persistent.pool,
                            AudioHeap_Alloc(&gAudioContext.persistentCommonPool, split->sampleBankCacheSize),
                            split->sampleBankCacheSize);

    AudioHeap_ClearPersistentCache(&gAudioContext.seqCache.persistent);
    AudioHeap_ClearPersistentCache(&gAudioContext.fontCache.persistent);
    AudioHeap_ClearPersistentCache(&gAudioContext.sampleBankCache.persistent);
}

void AudioHeap_InitTemporaryCache(AudioCommonPoolSplit* split) {
    gAudioContext.temporaryCommonPool.curAddr = gAudioContext.temporaryCommonPool.startAddr;

    AudioHeap_AllocPoolInit(&gAudioContext.seqCache.temporary.pool,
                            AudioHeap_Alloc(&gAudioContext.temporaryCommonPool, split->seqCacheSize),
                            split->seqCacheSize);
    AudioHeap_AllocPoolInit(&gAudioContext.fontCache.temporary.pool,
                            AudioHeap_Alloc(&gAudioContext.temporaryCommonPool, split->fontCacheSize),
                            split->fontCacheSize);
    AudioHeap_AllocPoolInit(&gAudioContext.sampleBankCache.temporary.pool,
                            AudioHeap_Alloc(&gAudioContext.temporaryCommonPool, split->sampleBankCacheSize),
                            split->sampleBankCacheSize);

    AudioHeap_ClearTemporaryCache(&gAudioContext.seqCache.temporary);
    AudioHeap_ClearTemporaryCache(&gAudioContext.fontCache.temporary);
    AudioHeap_ClearTemporaryCache(&gAudioContext.sampleBankCache.temporary);
}

void* AudioHeap_AllocCached(s32 tableType, size_t size, s32 cache, s32 id) {
    AudioCache* loadedCache;
    AudioTemporaryCache* temporaryCache;
    AudioAllocPool* temporaryPool;
    void* persistentAddr;
    void* temporaryAddr;
    u8 loadStatusEntry0;
    u8 loadStatusEntry1;
    s32 i;
    u8* loadStatus;
    s32 side;

    switch (tableType) {
        case SEQUENCE_TABLE:
            loadedCache = &gAudioContext.seqCache;
            loadStatus = gAudioContext.seqLoadStatus;
            break;

        case FONT_TABLE:
            loadedCache = &gAudioContext.fontCache;
            loadStatus = gAudioContext.fontLoadStatus;
            break;

        case SAMPLE_TABLE:
            loadedCache = &gAudioContext.sampleBankCache;
            loadStatus = gAudioContext.sampleFontLoadStatus;
            break;
    }

    if (cache == CACHE_TEMPORARY) {
        temporaryCache = &loadedCache->temporary;
        temporaryPool = &temporaryCache->pool;

        if ((s32)temporaryPool->size < (s32)size) {
            return NULL;
        }

        loadStatusEntry0 =
            (temporaryCache->entries[0].id == -1) ? LOAD_STATUS_0 : loadStatus[temporaryCache->entries[0].id];
        loadStatusEntry1 =
            (temporaryCache->entries[1].id == -1) ? LOAD_STATUS_0 : loadStatus[temporaryCache->entries[1].id];

        if (tableType == FONT_TABLE) {
            if (loadStatusEntry0 == LOAD_STATUS_4) {
                for (i = 0; i < gAudioContext.numNotes; i++) {
                    if ((gAudioContext.notes[i].playbackState.fontId == temporaryCache->entries[0].id) &&
                        gAudioContext.notes[i].noteSubEu.bitField0.enabled) {
                        break;
                    }
                }

                if (i == gAudioContext.numNotes) {
                    AudioLoad_SetFontLoadStatus(temporaryCache->entries[0].id, LOAD_STATUS_3);
                    loadStatusEntry0 = LOAD_STATUS_3;
                }
            }

            if (loadStatusEntry1 == LOAD_STATUS_4) {
                for (i = 0; i < gAudioContext.numNotes; i++) {
                    if ((gAudioContext.notes[i].playbackState.fontId == temporaryCache->entries[1].id) &&
                        gAudioContext.notes[i].noteSubEu.bitField0.enabled) {
                        break;
                    }
                }

                if (i == gAudioContext.numNotes) {
                    AudioLoad_SetFontLoadStatus(temporaryCache->entries[1].id, LOAD_STATUS_3);
                    loadStatusEntry1 = LOAD_STATUS_3;
                }
            }
        }

        if (loadStatusEntry0 == LOAD_STATUS_0) {
            temporaryCache->nextSide = 0;
        } else if (loadStatusEntry1 == LOAD_STATUS_0) {
            temporaryCache->nextSide = 1;
        } else if ((loadStatusEntry0 == LOAD_STATUS_3) && (loadStatusEntry1 == LOAD_STATUS_3)) {
            // Use the opposite side from last time.
        } else if (loadStatusEntry0 == LOAD_STATUS_3) {
            temporaryCache->nextSide = 0;
        } else if (loadStatusEntry1 == LOAD_STATUS_3) {
            temporaryCache->nextSide = 1;
        } else {
            // Check if there is a side which isn't in active use, if so, evict that one.
            if (tableType == SEQUENCE_TABLE) {
                if (loadStatusEntry0 == LOAD_STATUS_2) {
                    for (i = 0; i < gAudioContext.audioBufferParameters.numSequencePlayers; i++) {
                        if (gAudioContext.seqPlayers[i].enabled &&
                            gAudioContext.seqPlayers[i].seqId == temporaryCache->entries[0].id) {
                            break;
                        }
                    }

                    if (i == gAudioContext.audioBufferParameters.numSequencePlayers) {
                        temporaryCache->nextSide = 0;
                        goto done;
                    }
                }

                if (loadStatusEntry1 == LOAD_STATUS_2) {
                    for (i = 0; i < gAudioContext.audioBufferParameters.numSequencePlayers; i++) {
                        if (gAudioContext.seqPlayers[i].enabled &&
                            gAudioContext.seqPlayers[i].seqId == temporaryCache->entries[1].id) {
                            break;
                        }
                    }

                    if (i == gAudioContext.audioBufferParameters.numSequencePlayers) {
                        temporaryCache->nextSide = 1;
                        goto done;
                    }
                }
            } else if (tableType == FONT_TABLE) {
                if (loadStatusEntry0 == LOAD_STATUS_2) {
                    for (i = 0; i < gAudioContext.numNotes; i++) {
                        if ((gAudioContext.notes[i].playbackState.fontId == temporaryCache->entries[0].id) &&
                            gAudioContext.notes[i].noteSubEu.bitField0.enabled) {
                            break;
                        }
                    }
                    if (i == gAudioContext.numNotes) {
                        temporaryCache->nextSide = 0;
                        goto done;
                    }
                }

                if (loadStatusEntry1 == LOAD_STATUS_2) {
                    for (i = 0; i < gAudioContext.numNotes; i++) {
                        if ((gAudioContext.notes[i].playbackState.fontId == temporaryCache->entries[1].id) &&
                            gAudioContext.notes[i].noteSubEu.bitField0.enabled) {
                            break;
                        }
                    }
                    if (i == gAudioContext.numNotes) {
                        temporaryCache->nextSide = 1;
                        goto done;
                    }
                }
            }

            // No such luck. Evict the side that wasn't chosen last time, except
            // if it is being loaded into.
            if (temporaryCache->nextSide == 0) {
                if (loadStatusEntry0 == LOAD_STATUS_1) {
                    if (loadStatusEntry1 == LOAD_STATUS_1) {
                        goto fail;
                    }
                    temporaryCache->nextSide = 1;
                }
            } else {
                if (loadStatusEntry1 == LOAD_STATUS_1) {
                    if (loadStatusEntry0 == LOAD_STATUS_1) {
                        goto fail;
                    }
                    temporaryCache->nextSide = 0;
                }
            }

            if (0) {
            fail:
                // Both sides are being loaded into.
                return NULL;
            }
        }
    done:

        side = temporaryCache->nextSide;

        if (temporaryCache->entries[side].id != -1) {
            if (tableType == SAMPLE_TABLE) {
                AudioHeap_DiscardSampleBank(temporaryCache->entries[side].id);
            }

            loadStatus[temporaryCache->entries[side].id] = LOAD_STATUS_0;

            if (tableType == FONT_TABLE) {
                AudioHeap_DiscardFont(temporaryCache->entries[side].id);
            }
        }

        switch (side) {
            case 0:
                temporaryCache->entries[0].addr = temporaryPool->startAddr;
                temporaryCache->entries[0].id = id;
                temporaryCache->entries[0].size = size;
                temporaryPool->curAddr = temporaryPool->startAddr + size;

                if ((temporaryCache->entries[1].id != -1) &&
                    (temporaryCache->entries[1].addr < temporaryPool->curAddr)) {
                    if (tableType == SAMPLE_TABLE) {
                        AudioHeap_DiscardSampleBank(temporaryCache->entries[1].id);
                    }

                    loadStatus[temporaryCache->entries[1].id] = LOAD_STATUS_0;

                    switch (tableType) {
                        case SEQUENCE_TABLE:
                            AudioHeap_DiscardSequence((s32)temporaryCache->entries[1].id);
                            break;

                        case FONT_TABLE:
                            AudioHeap_DiscardFont((s32)temporaryCache->entries[1].id);
                            break;
                    }

                    temporaryCache->entries[1].id = -1;
                    temporaryCache->entries[1].addr = temporaryPool->startAddr + temporaryPool->size;
                }

                temporaryAddr = temporaryCache->entries[0].addr;
                break;

            case 1:
                temporaryCache->entries[1].addr =
                    (u8*)((uintptr_t)(temporaryPool->startAddr + temporaryPool->size - size) & ~0xF);
                temporaryCache->entries[1].id = id;
                temporaryCache->entries[1].size = size;
                if ((temporaryCache->entries[0].id != -1) &&
                    (temporaryCache->entries[1].addr < temporaryPool->curAddr)) {
                    if (tableType == SAMPLE_TABLE) {
                        AudioHeap_DiscardSampleBank(temporaryCache->entries[0].id);
                    }

                    loadStatus[temporaryCache->entries[0].id] = LOAD_STATUS_0;

                    switch (tableType) {
                        case SEQUENCE_TABLE:
                            AudioHeap_DiscardSequence(temporaryCache->entries[0].id);
                            break;

                        case FONT_TABLE:
                            AudioHeap_DiscardFont(temporaryCache->entries[0].id);
                            break;
                    }

                    temporaryCache->entries[0].id = -1;
                    temporaryPool->curAddr = temporaryPool->startAddr;
                }

                temporaryAddr = temporaryCache->entries[1].addr;
                break;

            default:
                return NULL;
        }

        temporaryCache->nextSide ^= 1;
        return temporaryAddr;
    }

    persistentAddr = AudioHeap_Alloc(&loadedCache->persistent.pool, size);
    loadedCache->persistent.entries[loadedCache->persistent.numEntries].addr = persistentAddr;

    if (persistentAddr == NULL) {
        switch (cache) {
            case CACHE_EITHER:
                return AudioHeap_AllocCached(tableType, size, CACHE_TEMPORARY, id);

            case CACHE_TEMPORARY:
            case CACHE_PERSISTENT:
                return NULL;
        }
    }

    loadedCache->persistent.entries[loadedCache->persistent.numEntries].id = id;
    loadedCache->persistent.entries[loadedCache->persistent.numEntries].size = size;

    return loadedCache->persistent.entries[loadedCache->persistent.numEntries++].addr;
}

void* AudioHeap_SearchCaches(s32 tableType, s32 cache, s32 id) {
    void* addr;

    // Always search the permanent cache in addition to the regular ones.
    addr = AudioHeap_SearchPermanentCache(tableType, id);
    if (addr != NULL) {
        return addr;
    }
    if (cache == CACHE_PERMANENT) {
        return NULL;
    }
    return AudioHeap_SearchRegularCaches(tableType, cache, id);
}

void* AudioHeap_SearchRegularCaches(s32 tableType, s32 cache, s32 id) {
    u32 i;
    AudioCache* loadedCache;
    AudioTemporaryCache* temporary;
    AudioPersistentCache* persistent;

    switch (tableType) {
        case SEQUENCE_TABLE:
            loadedCache = &gAudioContext.seqCache;
            break;

        case FONT_TABLE:
            loadedCache = &gAudioContext.fontCache;
            break;

        case SAMPLE_TABLE:
            loadedCache = &gAudioContext.sampleBankCache;
            break;
    }

    temporary = &loadedCache->temporary;

    if (cache == CACHE_TEMPORARY) {
        if (temporary->entries[0].id == id) {
            temporary->nextSide = 1;
            return temporary->entries[0].addr;
        } else if (temporary->entries[1].id == id) {
            temporary->nextSide = 0;
            return temporary->entries[1].addr;
        } else {
            return NULL;
        }
    }

    persistent = &loadedCache->persistent;

    for (i = 0; i < persistent->numEntries; i++) {
        if (persistent->entries[i].id == id) {
            return persistent->entries[i].addr;
        }
    }

    if (cache == CACHE_EITHER) {
        return AudioHeap_SearchCaches(tableType, CACHE_TEMPORARY, id);
    }
    return NULL;
}

void func_8018C4E4(f32 p, f32 q, u16* out) {
    // With the bug below fixed, this mysterious unused function computes two recurrences
    // out[0..7] = a_i, out[8..15] = b_i, where
    // a_{-2} = b_{-1} = 262159 = 2^18 + 15
    // a_{-1} = b_{-2} = 0
    // a_i = q * a_{i-1} + p * a_{i-2}
    // b_i = q * b_{i-1} + p * b_{i-2}
    // These grow exponentially if p < -1 or p + |q| > 1.
    s32 i;
    f32 tmp[16];

    tmp[0] = (f32)(q * 262159.0f);
    tmp[8] = (f32)(p * 262159.0f);
    tmp[1] = (f32)((q * p) * 262159.0f);
    tmp[9] = (f32)(((p * p) + q) * 262159.0f);

    for (i = 2; i < 8; i++) {
        //! @bug value should be stored to tmp[i] and tmp[8 + i], otherwise we read
        //! garbage in later loop iterations.
        out[i] = q * tmp[i - 2] + p * tmp[i - 1];
        out[8 + i] = q * tmp[6 + i] + p * tmp[7 + i];
    }

    for (i = 0; i < 16; i++) {
        out[i] = tmp[i];
    }
}

void AudioHeap_ClearFilter(s16* filter) {
    s32 i;

    for (i = 0; i < 8; i++) {
        filter[i] = 0;
    }
}

void AudioHeap_LoadLowPassFilter(s16* filter, s32 cutoff) {
    s32 i;
    s16* ptr = &gLowPassFilterData[8 * cutoff];

    for (i = 0; i < 8; i++) {
        filter[i] = ptr[i];
    }
}

void AudioHeap_LoadHighPassFilter(s16* filter, s32 cutoff) {
    s32 i;
    s16* ptr = &gHighPassFilterData[8 * (cutoff - 1)];

    for (i = 0; i < 8; i++) {
        filter[i] = ptr[i];
    }
}

void AudioHeap_LoadFilter(s16* filter, s32 lowPassCutoff, s32 highPassCutoff) {
    s32 i;
    s32 j;
    s32 k;
    s32 cutOff;

    //! @bug filter is never set if (lowPassCutoff == highPassCutoff) and does not equal 0
    if (lowPassCutoff == 0 && highPassCutoff == 0) {
        // Identity filter
        AudioHeap_LoadLowPassFilter(filter, 0);
    } else if (highPassCutoff == 0) {
        AudioHeap_LoadLowPassFilter(filter, lowPassCutoff);
    } else if (lowPassCutoff == 0) {
        AudioHeap_LoadHighPassFilter(filter, highPassCutoff);
    } else {
        k = 0;
        j = 14;

        cutOff = lowPassCutoff;
        if (lowPassCutoff < highPassCutoff) {

            for (i = 1; i < cutOff; i++) {
                k += j;
                j--;
            }

            k += highPassCutoff - lowPassCutoff - 1;
            for (i = 0; i < 8; i++) {
                //! @bug should be gBandStopFilterData[8 * k + i];
                filter[i] = gBandStopFilterData[k + i];
            }
        } else if (highPassCutoff < lowPassCutoff) {

            cutOff = highPassCutoff;
            for (i = 1; i < cutOff; i++) {
                k += j;
                j--;
            }

            k += lowPassCutoff - highPassCutoff - 1;
            for (i = 0; i < 8; i++) {
                //! @bug should be gBandPassFilterData[8 * k + i];
                filter[i] = gBandPassFilterData[k + i];
            }
        }
    }
}

void AudioHeap_UpdateReverb(SynthesisReverb* reverb) {
}

void AudioHeap_UpdateReverbs(void) {
    s32 count;
    s32 i;
    s32 j;

    if (gAudioContext.audioBufferParameters.specUnk4 == 2) {
        count = 2;
    } else {
        count = 1;
    }

    for (i = 0; i < gAudioContext.numSynthesisReverbs; i++) {
        for (j = 0; j < count; j++) {
            AudioHeap_UpdateReverb(&gAudioContext.synthesisReverbs[i]);
        }
    }
}

/**
 * Clear the Audio Interface Buffers
 */
void AudioHeap_ClearAiBuffers(void) {
    s32 curAiBuffferIndex = gAudioContext.curAiBuffferIndex;
    s32 i;

    gAudioContext.aiBufLengths[curAiBuffferIndex] = gAudioContext.audioBufferParameters.minAiBufferLength;

    for (i = 0; i < AIBUF_LEN; i++) {
        gAudioContext.aiBuffers[curAiBuffferIndex][i] = 0;
    }
}

s32 AudioHeap_ResetStep(void) {
    s32 i;
    s32 j;
    s32 count;

    if (gAudioContext.audioBufferParameters.specUnk4 == 2) {
        count = 2;
    } else {
        count = 1;
    }

    switch (gAudioContext.resetStatus) {
        case 5:
            for (i = 0; i < gAudioContext.audioBufferParameters.numSequencePlayers; i++) {
                AudioSeq_SequencePlayerDisableAsFinished(&gAudioContext.seqPlayers[i]);
            }
            gAudioContext.audioResetFadeOutFramesLeft = 2 / count;
            gAudioContext.resetStatus--;
            break;

        case 4:
            if (gAudioContext.audioResetFadeOutFramesLeft != 0) {
                gAudioContext.audioResetFadeOutFramesLeft--;
                AudioHeap_UpdateReverbs();
            } else {
                for (i = 0; i < gAudioContext.numNotes; i++) {
                    if (gAudioContext.notes[i].noteSubEu.bitField0.enabled &&
                        gAudioContext.notes[i].playbackState.adsr.action.s.state != ADSR_STATE_DISABLED) {
                        gAudioContext.notes[i].playbackState.adsr.fadeOutVel =
                            gAudioContext.audioBufferParameters.updatesPerFrameInv;
                        gAudioContext.notes[i].playbackState.adsr.action.s.release = true;
                    }
                }
                gAudioContext.audioResetFadeOutFramesLeft = 8 / count;
                gAudioContext.resetStatus--;
            }
            break;

        case 3:
            if (gAudioContext.audioResetFadeOutFramesLeft != 0) {
                gAudioContext.audioResetFadeOutFramesLeft--;
                AudioHeap_UpdateReverbs();
            } else {
                gAudioContext.audioResetFadeOutFramesLeft = 2 / count;
                gAudioContext.resetStatus--;
            }
            break;

        case 2:
            AudioHeap_ClearAiBuffers();
            if (gAudioContext.audioResetFadeOutFramesLeft != 0) {
                gAudioContext.audioResetFadeOutFramesLeft--;
            } else {
                gAudioContext.resetStatus--;
                AudioHeap_DiscardSampleCaches();
                AudioHeap_DiscardSampleBanks();
            }
            break;

        case 1:
            AudioHeap_Init();
            gAudioContext.resetStatus = 0;
            for (i = 0; i < ARRAY_COUNT(gAudioContext.aiBufLengths); i++) {
                gAudioContext.aiBufLengths[i] = gAudioContext.audioBufferParameters.maxAiBufferLength;
                for (j = 0; j < AIBUF_LEN; j++) {
                    gAudioContext.aiBuffers[i][j] = 0;
                }
            }
            break;
    }

    if (gAudioContext.resetStatus < 3) {
        return false;
    }

    return true;
}

void AudioHeap_Init(void) {
    s32 pad1[4];
    s16* addr;
    size_t persistentSize;
    size_t temporarySize;
    size_t cachePoolSize;
    size_t miscPoolSize;
    u32 intMask;
    s32 i;
    s32 j;
    s32 pad2;
    AudioSpec* spec = &gAudioSpecs[gAudioContext.audioResetSpecIdToLoad]; // Audio Specifications

    gAudioContext.sampleDmaCount = 0;

    // audio buffer parameters
    gAudioContext.audioBufferParameters.samplingFreq = spec->samplingFreq;
    gAudioContext.audioBufferParameters.aiSamplingFreq =
        osAiSetFrequency(gAudioContext.audioBufferParameters.samplingFreq);

    gAudioContext.audioBufferParameters.samplesPerFrameTarget =
        ALIGN16(gAudioContext.audioBufferParameters.samplingFreq / gAudioContext.refreshRate);
    gAudioContext.audioBufferParameters.minAiBufferLength =
        gAudioContext.audioBufferParameters.samplesPerFrameTarget - 0x10;
    gAudioContext.audioBufferParameters.maxAiBufferLength =
        gAudioContext.audioBufferParameters.samplesPerFrameTarget + 0x10;
    gAudioContext.audioBufferParameters.updatesPerFrame =
        ((gAudioContext.audioBufferParameters.samplesPerFrameTarget + 0x10) / 0xD0) + 1;
    gAudioContext.audioBufferParameters.samplesPerUpdate = (gAudioContext.audioBufferParameters.samplesPerFrameTarget /
                                                            gAudioContext.audioBufferParameters.updatesPerFrame) &
                                                           ~7;
    gAudioContext.audioBufferParameters.samplesPerUpdateMax = gAudioContext.audioBufferParameters.samplesPerUpdate + 8;
    gAudioContext.audioBufferParameters.samplesPerUpdateMin = gAudioContext.audioBufferParameters.samplesPerUpdate - 8;
    gAudioContext.audioBufferParameters.resampleRate = 32000.0f / (s32)gAudioContext.audioBufferParameters.samplingFreq;
    gAudioContext.audioBufferParameters.unkUpdatesPerFrameScaled =
        (1.0f / 256.0f) / gAudioContext.audioBufferParameters.updatesPerFrame;
    gAudioContext.audioBufferParameters.unk_24 = gAudioContext.audioBufferParameters.updatesPerFrame * 0.25f;
    gAudioContext.audioBufferParameters.updatesPerFrameInv = 1.0f / gAudioContext.audioBufferParameters.updatesPerFrame;

    // sample dma size
    gAudioContext.sampleDmaBufSize1 = spec->sampleDmaBufSize1;
    gAudioContext.sampleDmaBufSize2 = spec->sampleDmaBufSize2;

    gAudioContext.numNotes = spec->numNotes;
    gAudioContext.audioBufferParameters.numSequencePlayers = spec->numSequencePlayers;

    if (gAudioContext.audioBufferParameters.numSequencePlayers > 5) {
        gAudioContext.audioBufferParameters.numSequencePlayers = 5;
    }

    gAudioContext.unk_29BC = 8;
    gAudioContext.unk_2 = spec->unk_14;
    gAudioContext.tempoInternalToExternal = (u32)(gAudioContext.audioBufferParameters.updatesPerFrame * 2880000.0f /
                                                  gTatumsPerBeat / gAudioContext.unk_2960);

    gAudioContext.unk_2870 = gAudioContext.refreshRate;
    gAudioContext.unk_2870 *= gAudioContext.audioBufferParameters.updatesPerFrame;
    gAudioContext.unk_2870 /= gAudioContext.audioBufferParameters.aiSamplingFreq;
    gAudioContext.unk_2870 /= gAudioContext.tempoInternalToExternal;

    gAudioContext.audioBufferParameters.specUnk4 = spec->unk_04;
    gAudioContext.audioBufferParameters.samplesPerFrameTarget *= gAudioContext.audioBufferParameters.specUnk4;
    gAudioContext.audioBufferParameters.maxAiBufferLength *= gAudioContext.audioBufferParameters.specUnk4;
    gAudioContext.audioBufferParameters.minAiBufferLength *= gAudioContext.audioBufferParameters.specUnk4;
    gAudioContext.audioBufferParameters.updatesPerFrame *= gAudioContext.audioBufferParameters.specUnk4;

    if (gAudioContext.audioBufferParameters.specUnk4 >= 2) {
        gAudioContext.audioBufferParameters.maxAiBufferLength -= 0x10;
    }

    // Determine the maximum allowable number of audio command list entries for the rsp microcode
    gAudioContext.maxAudioCmds =
        gAudioContext.numNotes * 20 * gAudioContext.audioBufferParameters.updatesPerFrame + spec->numReverbs * 30 + 800;

    // Calculate sizes for various caches on the audio heap
    persistentSize =
        spec->persistentSeqCacheSize + spec->persistentFontCacheSize + spec->persistentSampleBankCacheSize + 0x10;
    temporarySize =
        spec->temporarySeqCacheSize + spec->temporaryFontCacheSize + spec->temporarySampleBankCacheSize + 0x10;
    cachePoolSize = persistentSize + temporarySize;
    miscPoolSize = gAudioContext.audioSessionPool.size - cachePoolSize - 0x100;

    if (gAudioContext.externalPool.startAddr != NULL) {
        gAudioContext.externalPool.curAddr = gAudioContext.externalPool.startAddr;
    }

    // Session Pool Split (split into Cache and Misc heaps)
    gAudioContext.sessionPoolSplit.miscPoolSize = miscPoolSize;
    gAudioContext.sessionPoolSplit.cachePoolSize = cachePoolSize;
    AudioHeap_InitSessionPool(&gAudioContext.sessionPoolSplit);

    // Cache Pool Split (Split into Persistent and Temporary heaps)
    gAudioContext.cachePoolSplit.persistentCommonPoolSize = persistentSize;
    gAudioContext.cachePoolSplit.temporaryCommonPoolSize = temporarySize;
    AudioHeap_InitCachePool(&gAudioContext.cachePoolSplit);

    // Persistent Pool Split (Split into Sequences, SoundFonts, Samples)
    gAudioContext.persistentCommonPoolSplit.seqCacheSize = spec->persistentSeqCacheSize;
    gAudioContext.persistentCommonPoolSplit.fontCacheSize = spec->persistentFontCacheSize;
    gAudioContext.persistentCommonPoolSplit.sampleBankCacheSize = spec->persistentSampleBankCacheSize;
    AudioHeap_InitPersistentCache(&gAudioContext.persistentCommonPoolSplit);

    // Temporary Pool Split (Split into Sequences, SoundFonts, Samples)
    gAudioContext.temporaryCommonPoolSplit.seqCacheSize = spec->temporarySeqCacheSize;
    gAudioContext.temporaryCommonPoolSplit.fontCacheSize = spec->temporaryFontCacheSize;
    gAudioContext.temporaryCommonPoolSplit.sampleBankCacheSize = spec->temporarySampleBankCacheSize;
    AudioHeap_InitTemporaryCache(&gAudioContext.temporaryCommonPoolSplit);

    AudioHeap_ResetLoadStatus();

    // Initialize notes
    gAudioContext.notes = AudioHeap_AllocZeroed(&gAudioContext.miscPool, gAudioContext.numNotes * sizeof(Note));
    AudioPlayback_NoteInitAll();
    AudioPlayback_InitNoteFreeList();
    gAudioContext.noteSubsEu =
        AudioHeap_AllocZeroed(&gAudioContext.miscPool, gAudioContext.audioBufferParameters.updatesPerFrame *
                                                           gAudioContext.numNotes * sizeof(NoteSubEu));

    // Initialize audio binary interface command list buffer
    for (j = 0; j < ARRAY_COUNT(gAudioContext.abiCmdBufs); j++) {
        gAudioContext.abiCmdBufs[j] =
            AudioHeap_AllocDmaMemoryZeroed(&gAudioContext.miscPool, gAudioContext.maxAudioCmds * sizeof(u64));
    }

    // Initialize unk_3520 (fadeOutVelocities for ADSR)
    gAudioContext.unk_3520 = AudioHeap_Alloc(&gAudioContext.miscPool, 0x100 * sizeof(f32));
    func_8018B10C();

    // Initialize reverbs
    for (i = 0; i < ARRAY_COUNT(gAudioContext.synthesisReverbs); i++) {
        gAudioContext.synthesisReverbs[i].useReverb = 0;
    }

    gAudioContext.numSynthesisReverbs = spec->numReverbs;
    for (i = 0; i < gAudioContext.numSynthesisReverbs; i++) {
        AudioHeap_InitReverb(i, &spec->reverbSettings[i], 1);
    }

    // Initialize sequence players
    AudioSeq_InitSequencePlayers();
    for (j = 0; j < gAudioContext.audioBufferParameters.numSequencePlayers; j++) {
        AudioSeq_InitSequencePlayerChannels(j);
        AudioSeq_ResetSequencePlayer(&gAudioContext.seqPlayers[j]);
    }

    // Initialize two additional caches on the audio heap to store individual audio samples
    AudioHeap_InitSampleCaches(spec->persistentSampleCacheSize, spec->temporarySampleCacheSize);
    AudioLoad_InitSampleDmaBuffers(gAudioContext.numNotes);

    // Initalize Loads
    gAudioContext.preloadSampleStackTop = 0;
    AudioLoad_InitSlowLoads();
    AudioLoad_InitScriptLoads();
    AudioLoad_InitAsyncLoads();
    gAudioContext.unk_4 = 0x1000;
    AudioLoad_LoadPermanentSamples();

    intMask = osSetIntMask(1);
    osWritebackDCacheAll();
    osSetIntMask(intMask);
}

void* AudioHeap_SearchPermanentCache(s32 tableType, s32 id) {
    s32 i;

    for (i = 0; i < gAudioContext.permanentPool.count; i++) {
        if (gAudioContext.permanentEntries[i].tableType == tableType && gAudioContext.permanentEntries[i].id == id) {
            return gAudioContext.permanentEntries[i].addr;
        }
    }
    return NULL;
}

void* AudioHeap_AllocPermanent(s32 tableType, s32 id, size_t size) {
    void* addr;
    s32 index = gAudioContext.permanentPool.count;

    addr = AudioHeap_Alloc(&gAudioContext.permanentPool, size);
    gAudioContext.permanentEntries[index].addr = addr;

    if (addr == NULL) {
        return NULL;
    }

    gAudioContext.permanentEntries[index].tableType = tableType;
    gAudioContext.permanentEntries[index].id = id;
    gAudioContext.permanentEntries[index].size = size;
    //! @bug UB: missing return. "addr" is in v0 at this point, but doing an
    // explicit return uses an additional register.
    // return addr;
}

void* AudioHeap_AllocSampleCache(size_t size, s32 sampleBankId, void* sampleAddr, s8 medium, s32 cache) {
    SampleCacheEntry* entry;

    if (cache == CACHE_TEMPORARY) {
        entry = AudioHeap_AllocTemporarySampleCacheEntry(size);
    } else {
        entry = AudioHeap_AllocPersistentSampleCacheEntry(size);
    }

    if (entry != NULL) {
        entry->sampleBankId = sampleBankId;
        entry->sampleAddr = sampleAddr;
        entry->origMedium = medium;
        return entry->allocatedAddr;
    }
    return NULL;
}

/**
 * Initializes the persistent and temporary caches used for individual samples. Will attempt to use heap space available
 * on the external pool. If no external pool is provided, then default to using space on the misc heap.
 */
void AudioHeap_InitSampleCaches(size_t persistentSampleCacheSize, size_t temporarySampleCacheSize) {
    void* addr;

    addr = AudioHeap_AllocAttemptExternal(&gAudioContext.miscPool, persistentSampleCacheSize);
    if (addr == NULL) {
        gAudioContext.persistentSampleCache.pool.size = 0;
    } else {
        AudioHeap_AllocPoolInit(&gAudioContext.persistentSampleCache.pool, addr, persistentSampleCacheSize);
    }

    addr = AudioHeap_AllocAttemptExternal(&gAudioContext.miscPool, temporarySampleCacheSize);
    if (addr == NULL) {
        gAudioContext.temporarySampleCache.pool.size = 0;
    } else {
        AudioHeap_AllocPoolInit(&gAudioContext.temporarySampleCache.pool, addr, temporarySampleCacheSize);
    }

    gAudioContext.persistentSampleCache.numEntries = 0;
    gAudioContext.temporarySampleCache.numEntries = 0;
}

SampleCacheEntry* AudioHeap_AllocTemporarySampleCacheEntry(size_t size) {
    s32 pad2[2];
    void* addr;
    s32 pad3[2];
    u8* allocAfter;
    u8* allocBefore;
    s32 pad1;
    s32 index;
    s32 i;
    SampleCacheEntry* entry;
    AudioPreloadReq* preload;
    AudioSampleCache* cache;
    u8* startAddr;
    u8* endAddr;

    cache = &gAudioContext.temporarySampleCache;
    allocBefore = cache->pool.curAddr;
    addr = AudioHeap_Alloc(&cache->pool, size);
    if (addr == NULL) {
        // Reset the heap and try again. We still keep pointers to within the
        // heap, so we have to be careful to discard existing overlapping
        // allocations further down.
        u8* oldAddr = cache->pool.curAddr;

        cache->pool.curAddr = cache->pool.startAddr;
        addr = AudioHeap_Alloc(&cache->pool, size);
        if (addr == NULL) {
            cache->pool.curAddr = oldAddr;
            return NULL;
        }
        allocBefore = cache->pool.startAddr;
    }

    allocAfter = cache->pool.curAddr;

    index = -1;
    for (i = 0; i < gAudioContext.preloadSampleStackTop; i++) {
        preload = &gAudioContext.preloadSampleStack[i];
        if (preload->isFree == false) {
            startAddr = preload->ramAddr;
            endAddr = preload->ramAddr + preload->sample->size - 1;

            if ((endAddr < allocBefore) && (startAddr < allocBefore)) {
                continue;
            }
            if ((endAddr >= allocAfter) && (startAddr >= allocAfter)) {
                continue;
            }

            // Overlap, skip this preload.
            preload->isFree = true;
        }
    }

    for (i = 0; i < cache->numEntries; i++) {
        if (!cache->entries[i].inUse) {
            continue;
        }

        startAddr = cache->entries[i].allocatedAddr;
        endAddr = startAddr + cache->entries[i].size - 1;

        if ((endAddr < allocBefore) && (startAddr < allocBefore)) {
            continue;
        }
        if ((endAddr >= allocAfter) && (startAddr >= allocAfter)) {
            continue;
        }

        // Overlap, discard existing entry.
        AudioHeap_DiscardSampleCacheEntry(&cache->entries[i]);
        cache->entries[i].inUse = false;
        if (index == -1) {
            index = i;
        }
    }

    if (index == -1) {
        for (i = 0; i < cache->numEntries; i++) {
            if (!cache->entries[i].inUse) {
                break;
            }
        }

        index = i;
        if (index == cache->numEntries) {
            if (cache->numEntries == 128) {
                return NULL;
            }
            cache->numEntries++;
        }
    }

    entry = &cache->entries[index];
    entry->inUse = 1;
    entry->allocatedAddr = addr;
    entry->size = size;

    return entry;
}

void AudioHeap_UnapplySampleCacheForFont(SampleCacheEntry* entry, s32 fontId) {
    Drum* drum;
    Instrument* inst;
    SoundFontSound* sfx;
    s32 instId;
    s32 drumId;
    s32 sfxId;

    for (instId = 0; instId < gAudioContext.soundFonts[fontId].numInstruments; instId++) {
        inst = AudioPlayback_GetInstrumentInner(fontId, instId);
        if (inst != NULL) {
            if (inst->normalRangeLo != 0) {
                AudioHeap_UnapplySampleCache(entry, inst->lowNotesSound.sample);
            }
            if (inst->normalRangeHi != 0x7F) {
                AudioHeap_UnapplySampleCache(entry, inst->highNotesSound.sample);
            }
            AudioHeap_UnapplySampleCache(entry, inst->normalNotesSound.sample);
        }
    }

    for (drumId = 0; drumId < gAudioContext.soundFonts[fontId].numDrums; drumId++) {
        drum = AudioPlayback_GetDrum(fontId, drumId);
        if (drum != NULL) {
            AudioHeap_UnapplySampleCache(entry, drum->sound.sample);
        }
    }

    for (sfxId = 0; sfxId < gAudioContext.soundFonts[fontId].numSfx; sfxId++) {
        sfx = AudioPlayback_GetSfx(fontId, sfxId);
        if (sfx != NULL) {
            AudioHeap_UnapplySampleCache(entry, sfx->sample);
        }
    }
}

void AudioHeap_DiscardSampleCacheEntry(SampleCacheEntry* entry) {
    s32 numFonts;
    s32 sampleBankId1;
    s32 sampleBankId2;
    s32 fontId;

    numFonts = gAudioContext.soundFontTable->numEntries;
    for (fontId = 0; fontId < numFonts; fontId++) {
        sampleBankId1 = gAudioContext.soundFonts[fontId].sampleBankId1;
        sampleBankId2 = gAudioContext.soundFonts[fontId].sampleBankId2;
        if (((sampleBankId1 != 0xFF) && (entry->sampleBankId == sampleBankId1)) ||
            ((sampleBankId2 != 0xFF) && (entry->sampleBankId == sampleBankId2)) || entry->sampleBankId == 0 ||
            entry->sampleBankId == 0xFE) {
            if (AudioHeap_SearchCaches(FONT_TABLE, CACHE_EITHER, fontId) != NULL) {
                if (1) {}
                if (AudioLoad_IsFontLoadComplete(fontId) != 0) {
                    AudioHeap_UnapplySampleCacheForFont(entry, fontId);
                }
            }
        }
    }
}

void AudioHeap_UnapplySampleCache(SampleCacheEntry* entry, SoundFontSample* sample) {
    if (sample != NULL) {
        if (sample->sampleAddr == entry->allocatedAddr) {
            sample->sampleAddr = entry->sampleAddr;
            sample->medium = entry->origMedium;
        }
    }
}

SampleCacheEntry* AudioHeap_AllocPersistentSampleCacheEntry(size_t size) {
    AudioSampleCache* cache;
    SampleCacheEntry* entry;
    void* addr;

    cache = &gAudioContext.persistentSampleCache;
    addr = AudioHeap_Alloc(&cache->pool, size);
    if (addr == NULL) {
        return NULL;
    }

    if (cache->numEntries == 128) {
        return NULL;
    }

    entry = &cache->entries[cache->numEntries];
    entry->inUse = true;
    entry->allocatedAddr = addr;
    entry->size = size;
    cache->numEntries++;

    return entry;
}

void AudioHeap_DiscardSampleCacheForFont(SampleCacheEntry* entry, s32 sampleBankId1, s32 sampleBankId2, s32 fontId) {
    if ((entry->sampleBankId == sampleBankId1) || (entry->sampleBankId == sampleBankId2) ||
        (entry->sampleBankId == 0)) {
        AudioHeap_UnapplySampleCacheForFont(entry, fontId);
    }
}

void AudioHeap_DiscardSampleCaches(void) {
    s32 numFonts;
    s32 sampleBankId1;
    s32 sampleBankId2;
    s32 fontId;
    s32 j;

    numFonts = gAudioContext.soundFontTable->numEntries;
    for (fontId = 0; fontId < numFonts; fontId++) {
        sampleBankId1 = gAudioContext.soundFonts[fontId].sampleBankId1;
        sampleBankId2 = gAudioContext.soundFonts[fontId].sampleBankId2;
        if ((sampleBankId1 == 0xFF) && (sampleBankId2 == 0xFF)) {
            continue;
        }
        if (AudioHeap_SearchCaches(FONT_TABLE, CACHE_PERMANENT, fontId) == NULL ||
            !AudioLoad_IsFontLoadComplete(fontId)) {
            continue;
        }

        for (j = 0; j < gAudioContext.persistentSampleCache.numEntries; j++) {
            AudioHeap_DiscardSampleCacheForFont(&gAudioContext.persistentSampleCache.entries[j], sampleBankId1,
                                                sampleBankId2, fontId);
        }
        for (j = 0; j < gAudioContext.temporarySampleCache.numEntries; j++) {
            AudioHeap_DiscardSampleCacheForFont(&gAudioContext.temporarySampleCache.entries[j], sampleBankId1,
                                                sampleBankId2, fontId);
        }
    }
}

typedef struct {
    uintptr_t oldAddr;
    uintptr_t newAddr;
    size_t size;
    u8 newMedium;
} StorageChange;

void AudioHeap_ChangeStorage(StorageChange* change, SoundFontSample* sample) {
    if (sample != NULL && ((sample->medium == change->newMedium) || (D_801FD120 != 1)) &&
        ((sample->medium == MEDIUM_RAM) || (D_801FD120 != 0))) {
        uintptr_t startAddr = change->oldAddr;
        uintptr_t endAddr = change->oldAddr + change->size;

        if (startAddr <= (uintptr_t)sample->sampleAddr && (uintptr_t)sample->sampleAddr < endAddr) {
            sample->sampleAddr = sample->sampleAddr - startAddr + change->newAddr;
            if (D_801FD120 == 0) {
                sample->medium = change->newMedium;
            } else {
                sample->medium = MEDIUM_RAM;
            }
        }
    }
}

void AudioHeap_DiscardSampleBank(s32 sampleBankId) {
    D_801FD120 = 0;
    AudioHeap_ApplySampleBankCacheInternal(false, sampleBankId);
}

void AudioHeap_ApplySampleBankCache(s32 sampleBankId) {
    D_801FD120 = 1;
    AudioHeap_ApplySampleBankCacheInternal(true, sampleBankId);
}

void AudioHeap_ApplySampleBankCacheInternal(s32 apply, s32 sampleBankId) {
    AudioTable* sampleBankTable;
    AudioTableEntry* entry;
    s32 numFonts;
    s32 instId;
    s32 drumId;
    s32 sfxId;
    StorageChange change;
    s32 sampleBankId1;
    s32 sampleBankId2;
    s32 fontId;
    Drum* drum;
    Instrument* inst;
    SoundFontSound* sfx;
    uintptr_t* newAddr;
    s32 pad[4];

    sampleBankTable = gAudioContext.sampleBankTable;
    numFonts = gAudioContext.soundFontTable->numEntries;
    change.oldAddr = AudioHeap_SearchCaches(SAMPLE_TABLE, CACHE_EITHER, sampleBankId);
    if (change.oldAddr == 0) {
        return;
    }

    entry = &sampleBankTable->entries[sampleBankId];
    change.size = entry->size;
    change.newMedium = entry->medium;
    change.newAddr = entry->romAddr;

    newAddr = &change.oldAddr;
    if (apply && (apply == true)) {
        uintptr_t oldAddr;

        oldAddr = change.newAddr;

        change.newAddr = *newAddr;
        change.oldAddr = oldAddr;
    }

    for (fontId = 0; fontId < numFonts; fontId++) {
        sampleBankId1 = gAudioContext.soundFonts[fontId].sampleBankId1;
        sampleBankId2 = gAudioContext.soundFonts[fontId].sampleBankId2;
        if ((sampleBankId1 != 0xFF) || (sampleBankId2 != 0xFF)) {
            if (!AudioLoad_IsFontLoadComplete(fontId) ||
                AudioHeap_SearchCaches(FONT_TABLE, CACHE_EITHER, fontId) == NULL) {
                continue;
            }

            if (sampleBankId1 == sampleBankId) {
            } else if (sampleBankId2 == sampleBankId) {
            } else {
                continue;
            }

            for (instId = 0; instId < gAudioContext.soundFonts[fontId].numInstruments; instId++) {
                inst = AudioPlayback_GetInstrumentInner(fontId, instId);
                if (inst != NULL) {
                    if (inst->normalRangeLo != 0) {
                        AudioHeap_ChangeStorage(&change, inst->lowNotesSound.sample);
                    }
                    if (inst->normalRangeHi != 0x7F) {
                        AudioHeap_ChangeStorage(&change, inst->highNotesSound.sample);
                    }
                    AudioHeap_ChangeStorage(&change, inst->normalNotesSound.sample);
                }
            }

            for (drumId = 0; drumId < gAudioContext.soundFonts[fontId].numDrums; drumId++) {
                drum = AudioPlayback_GetDrum(fontId, drumId);
                if (drum != NULL) {
                    AudioHeap_ChangeStorage(&change, drum->sound.sample);
                }
            }

            for (sfxId = 0; sfxId < gAudioContext.soundFonts[fontId].numSfx; sfxId++) {
                sfx = AudioPlayback_GetSfx(fontId, sfxId);
                if (sfx != NULL) {
                    AudioHeap_ChangeStorage(&change, sfx->sample);
                }
            }
        }
    }
}

void AudioHeap_DiscardSampleBanks(void) {
    AudioCache* cache;
    AudioPersistentCache* persistent;
    AudioTemporaryCache* temporary;
    u32 i;

    cache = &gAudioContext.sampleBankCache;
    temporary = &cache->temporary;

    if (temporary->entries[0].id != -1) {
        AudioHeap_DiscardSampleBank(temporary->entries[0].id);
    }

    if (temporary->entries[1].id != -1) {
        AudioHeap_DiscardSampleBank(temporary->entries[1].id);
    }

    persistent = &cache->persistent;
    for (i = 0; i < persistent->numEntries; i++) {
        AudioHeap_DiscardSampleBank(persistent->entries[i].id);
    }
}

void AudioHeap_SetReverbData(s32 reverbIndex, u32 dataType, s32 data, s32 flags) {
    s32 windowSize;
    SynthesisReverb* reverb = &gAudioContext.synthesisReverbs[reverbIndex];

    switch (dataType) {
        case 0:
            AudioHeap_InitReverb(reverbIndex, (ReverbSettings*)data, 0);
            break;
        case 1:
            if (data < 4) {
                data = 4;
            }

            windowSize = data * 64;
            if (windowSize < 0x100) {
                windowSize = 0x100;
            }

            windowSize /= reverb->downsampleRate;

            if (flags == 0) {
                if (reverb->unk_1E >= (data / reverb->downsampleRate)) {
                    if ((reverb->nextRingBufPos >= windowSize) || (reverb->unk_24 >= windowSize)) {
                        reverb->nextRingBufPos = 0;
                        reverb->unk_24 = 0;
                    }
                } else {
                    break;
                }
            }

            reverb->windowSize = windowSize;

            if ((reverb->downsampleRate != 1) || reverb->unk_18) {
                reverb->unk_0E = 0x8000 / reverb->downsampleRate;
                if (reverb->unk_30 == NULL) {
                    reverb->unk_30 = AudioHeap_AllocZeroed(&gAudioContext.miscPool, 0x20);
                    reverb->unk_34 = AudioHeap_AllocZeroed(&gAudioContext.miscPool, 0x20);
                    reverb->unk_38 = AudioHeap_AllocZeroed(&gAudioContext.miscPool, 0x20);
                    reverb->unk_3C = AudioHeap_AllocZeroed(&gAudioContext.miscPool, 0x20);
                    if (reverb->unk_3C == NULL) {
                        reverb->downsampleRate = 1;
                    }
                }
            }
            break;
        case 2:
            gAudioContext.synthesisReverbs[reverbIndex].unk_0C = data;
            break;
        case 3:
            gAudioContext.synthesisReverbs[reverbIndex].unk_16 = data;
            break;
        case 4:
            gAudioContext.synthesisReverbs[reverbIndex].unk_0A = data;
            break;
        case 5:
            gAudioContext.synthesisReverbs[reverbIndex].leakRtl = data;
            break;
        case 6:
            gAudioContext.synthesisReverbs[reverbIndex].leakLtr = data;
            break;
        case 7:
            if (data != 0) {
                if ((flags != 0) || (reverb->unk_278 == 0)) {
                    reverb->filterLeftState = AudioHeap_AllocDmaMemoryZeroed(&gAudioContext.miscPool, 0x40);
                    reverb->unk_278 = AudioHeap_AllocDmaMemory(&gAudioContext.miscPool, 0x10);
                }

                reverb->filterLeft = reverb->unk_278;
                if (reverb->filterLeft != 0) {
                    AudioHeap_LoadLowPassFilter(reverb->filterLeft, data);
                }
            } else {
                reverb->filterLeft = 0;

                if (flags != 0) {
                    reverb->unk_278 = 0;
                }
            }

            break;
        case 8:
            if (data != 0) {
                if ((flags != 0) || (reverb->unk_27C == 0)) {
                    reverb->filterRightState = AudioHeap_AllocDmaMemoryZeroed(&gAudioContext.miscPool, 0x40);
                    reverb->unk_27C = AudioHeap_AllocDmaMemory(&gAudioContext.miscPool, 0x10);
                }
                reverb->filterRight = reverb->unk_27C;
                if (reverb->unk_27C != 0) {
                    AudioHeap_LoadLowPassFilter(reverb->unk_27C, data);
                }
            } else {
                reverb->filterRight = 0;
                if (flags != 0) {
                    reverb->unk_27C = 0;
                }
            }
            break;
        case 9:
            reverb->unk_19 = data;
            if (data == 0) {
                reverb->unk_18 = false;
            } else {
                reverb->unk_18 = true;
            }
            break;
        default:
            break;
    }
}

void AudioHeap_InitReverb(s32 reverbIndex, ReverbSettings* settings, s32 flags) {
    SynthesisReverb* reverb = &gAudioContext.synthesisReverbs[reverbIndex];

    if (flags != 0) {
        reverb->unk_1E = settings->windowSize / settings->downsampleRate;
        reverb->unk_30 = 0;
    } else if (reverb->unk_1E < (settings->windowSize / settings->downsampleRate)) {
        return;
    }

    reverb->downsampleRate = settings->downsampleRate;
    reverb->unk_18 = false;
    reverb->unk_19 = 0;
    reverb->unk_1A = 0;
    reverb->unk_1C = 0;
    AudioHeap_SetReverbData(reverbIndex, 1, settings->windowSize, flags);
    reverb->unk_0C = settings->unk_4;
    reverb->unk_0A = settings->unk_A;
    reverb->unk_14 = settings->unk_6 << 6;
    reverb->unk_16 = settings->unk_8;
    reverb->leakRtl = settings->leakRtl;
    reverb->leakLtr = settings->leakLtr;
    reverb->unk_05 = settings->unk_10;
    reverb->unk_08 = settings->unk_12;
    reverb->useReverb = 8;

    if (flags != 0) {
        reverb->leftRingBuf = AudioHeap_AllocZeroedAttemptExternal(&gAudioContext.miscPool, reverb->windowSize * 2);
        reverb->rightRingBuf = AudioHeap_AllocZeroedAttemptExternal(&gAudioContext.miscPool, reverb->windowSize * 2);
        reverb->resampleFlags = 1;
        reverb->nextRingBufPos = 0;
        reverb->unk_24 = 0;
        reverb->curFrame = 0;
        reverb->framesToIgnore = 2;
    }

    reverb->sound.sample = &reverb->sample;
    reverb->sample.loop = &reverb->loop;
    reverb->sound.tuning = 1.0f;
    reverb->sample.codec = CODEC_REVERB;
    reverb->sample.medium = MEDIUM_RAM;
    reverb->sample.size = reverb->windowSize * 2;
    reverb->sample.sampleAddr = (u8*)reverb->leftRingBuf;
    reverb->loop.start = 0;
    reverb->loop.count = 1;
    reverb->loop.end = reverb->windowSize;

    AudioHeap_SetReverbData(reverbIndex, 7, settings->lowPassFilterCutoffLeft, flags);
    AudioHeap_SetReverbData(reverbIndex, 8, settings->lowPassFilterCutoffRight, flags);
}
