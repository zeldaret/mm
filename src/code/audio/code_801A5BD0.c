#include "global.h"

typedef struct {
    /* 0x00 */ u16 sfxId;
    /* 0x02 */ u8 token;
    /* 0x04 */ s8* reverbAdd;
    /* 0x08 */ Vec3f* pos;
    /* 0x0C */ f32* freqScale;
    /* 0x10 */ f32* vol;
} SfxRequest; // size = 0x14

typedef struct {
    /* 0x0 */ f32 value;
    /* 0x4 */ f32 target;
    /* 0x8 */ f32 step;
    /* 0xC */ u16 remainingFrames;
} SfxBankLerp; // size = 0x10

extern u8 D_801D6600[7];
extern u8 D_801D6608[7];
extern u8 gChannelsPerBank[4][7];
extern u8 gUsedChannelsPerBank[4][7];

// bss
SfxBankEntry sSfxPlayerBank[9];
SfxBankEntry sSfxItemBank[12];
SfxBankEntry sSfxEnvironmentBank[32];
SfxBankEntry sSfxEnemyBank[20];
SfxBankEntry sSfxSystemBank[8];
SfxBankEntry sSfxOcarinaBank[3];
SfxBankEntry sSfxVoiceBank[5];
SfxRequest sSfxRequests[0x100];
u8 sSfxBankListEnd[7];
u8 sSfxBankFreeListStart[7];
u8 sSfxBankUnused[7];
ActiveSfx gActiveSfxs[7][3];
u8 sCurSfxPlayerChannelIdx;
u8 gSfxBankMuted[7];
SfxBankLerp sSfxBankLerp[7];

// data

// sSfxRequests ring buffer endpoints. read index <= write index, wrapping around mod 256.
u8 sSfxRequestWriteIndex = 0;
u8 sSfxRequestReadIndex = 0;

/**
 * Array of pointers to arrays of SfxBankEntry of sizes: 9, 12, 32, 20, 8, 3, 5
 *
 * 0 : Player Bank          size 9
 * 1 : Item Bank            size 12
 * 2 : Environment Bank     size 32
 * 3 : Enemy Bank           size 20
 * 4 : System Bank          size 8
 * 5 : Ocarina Bank         size 3
 * 6 : Voice Bank           size 5
 */
SfxBankEntry* gSfxBanks[7] = {
    sSfxPlayerBank, sSfxItemBank, sSfxEnvironmentBank, sSfxEnemyBank, sSfxSystemBank, sSfxOcarinaBank, sSfxVoiceBank,
};

u8 sBankSizes[ARRAY_COUNT(gSfxBanks)] = {
    ARRAY_COUNT(sSfxPlayerBank), ARRAY_COUNT(sSfxItemBank),   ARRAY_COUNT(sSfxEnvironmentBank),
    ARRAY_COUNT(sSfxEnemyBank),  ARRAY_COUNT(sSfxSystemBank), ARRAY_COUNT(sSfxOcarinaBank),
    ARRAY_COUNT(sSfxVoiceBank),
};

u8 gSfxChannelLayout = 0;
u16 sSfxChannelLowVolumeFlag = 0;

// The center of the screen in projected coordinates.
// Gives the impression that the sfx has no specific location
Vec3f gSfxDefaultPos = { 0.0f, 0.0f, 0.0f };

// Reused as either frequency or volume multiplicative scaling factor
// Does not alter or change frequency or volume
f32 gSfxDefaultFreqAndVolScale = 1.0f;
s32 D_801DB4B4 = 0; // unused

// Adds no reverb to the existing reverb
s8 gSfxDefaultReverb = 0;
s32 D_801DB4BC = 0; // unused

void Audio_SetSfxBanksMute(u16 muteMask) {
    u8 bankId;

    for (bankId = 0; bankId < ARRAY_COUNT(gSfxBanks); bankId++) {
        if (muteMask & 1) {
            gSfxBankMuted[bankId] = true;
        } else {
            gSfxBankMuted[bankId] = false;
        }
        muteMask = muteMask >> 1;
    }
}

/**
 * Lowers volumes of players 0 and 3 so that sfx can be more pronounced
 * Each sfx channel stores its own bit to lower the volume
 * Only a single channel needs to request this to lower the volume
 */
void Audio_SetFlagForBgmVolumeLow(u8 channelIdx) {
    sSfxChannelLowVolumeFlag |= (1 << channelIdx);

    Audio_SetVolumeScale(SEQ_PLAYER_BGM_MAIN, 2, 0x40, 0xF);
    Audio_SetVolumeScale(SEQ_PLAYER_BGM_SUB, 2, 0x40, 0xF);
}

/**
 * Clears the flag for the specific channel to lower volume
 * If all flags are cleared, then players 0 and 3 return to full volume
 */
void Audio_ClearFlagForBgmVolumeLow(u8 channelIdx) {
    sSfxChannelLowVolumeFlag &= ((1 << channelIdx) ^ 0xFFFF);

    if (sSfxChannelLowVolumeFlag == 0) {
        Audio_SetVolumeScale(SEQ_PLAYER_BGM_MAIN, 2, 0x7F, 0xF);
        Audio_SetVolumeScale(SEQ_PLAYER_BGM_SUB, 2, 0x7F, 0xF);
    }
}

void Audio_PlaySfxGeneral(u16 sfxId, Vec3f* pos, u8 token, f32* freqScale, f32* vol, s8* reverbAdd) {
    u8 i;
    SfxRequest* reqWrite;
    SfxRequest* reqRead;

    if (!gSfxBankMuted[SFX_BANK_SHIFT(sfxId)]) {
        reqWrite = &sSfxRequests[sSfxRequestWriteIndex];

        for (i = sSfxRequestReadIndex; sSfxRequestWriteIndex != i; i++) {
            reqRead = &sSfxRequests[i];
            if (reqRead->pos == pos && reqRead->sfxId == sfxId) {
                return;
            }
        }

        reqWrite->sfxId = sfxId;
        reqWrite->pos = pos;
        reqWrite->token = token;
        reqWrite->freqScale = freqScale;
        reqWrite->vol = vol;
        reqWrite->reverbAdd = reverbAdd;
        sSfxRequestWriteIndex++;
    }
}

void Audio_RemoveMatchingSfxRequests(u8 aspect, SfxBankEntry* entry) {
    SfxRequest* req;
    s32 remove;
    u8 i = sSfxRequestReadIndex;

    for (; i != sSfxRequestWriteIndex; i++) {
        remove = false;
        req = &sSfxRequests[i];

        switch (aspect) {
            case 0:
                if (SFX_BANK_MASK(req->sfxId) == SFX_BANK_MASK(entry->sfxId)) {
                    remove = true;
                }
                break;
            case 1:
                if ((SFX_BANK_MASK(req->sfxId) == SFX_BANK_MASK(entry->sfxId)) && (&req->pos->x == entry->posX)) {
                    remove = true;
                }
                break;
            case 2:
                if (&req->pos->x == entry->posX) {
                    remove = true;
                }
                break;
            case 3:
                if ((&req->pos->x == entry->posX) && (req->sfxId == entry->sfxId)) {
                    remove = true;
                }
                break;
            case 4:
                if ((req->token == entry->token) && (req->sfxId == entry->sfxId)) {
                    remove = true;
                }
                break;
            case 5:
                if (req->sfxId == entry->sfxId) {
                    remove = true;
                }
                break;
        }

        if (remove) {
            req->sfxId = 0;
        }
    }
}

void Audio_ProcessSfxRequest(void) {
    u16 sfxId;
    u8 count;
    u8 index;
    SfxRequest* req = &sSfxRequests[sSfxRequestReadIndex];
    SfxBankEntry* entry;
    SfxParams* sfxParams;
    s32 bankId;
    u8 evictImportance;
    u8 evictIndex = 0x80;

    if (req->sfxId == 0) {
        return;
    }

    bankId = SFX_BANK(req->sfxId);
    count = 0;
    index = gSfxBanks[bankId][0].next;

    while (index != 0xFF && index != 0) {
        if (gSfxBanks[bankId][index].posX == &req->pos->x) {
            if ((gSfxParams[SFX_BANK_SHIFT(req->sfxId)][SFX_INDEX(req->sfxId)].params & 0x20) &&
                (gSfxParams[SFX_BANK_SHIFT(req->sfxId)][SFX_INDEX(req->sfxId)].importance ==
                 gSfxBanks[bankId][index].sfxImportance)) {
                return;
            }

            if (gSfxBanks[bankId][index].sfxId == req->sfxId) {
                count = gUsedChannelsPerBank[gSfxChannelLayout][bankId];
            } else {
                if (count == 0) {
                    evictIndex = index;
                    sfxId = gSfxBanks[bankId][index].sfxId & 0xFFFF;
                    evictImportance = gSfxParams[SFX_BANK_SHIFT(sfxId)][SFX_INDEX(sfxId)].importance;
                } else if (gSfxBanks[bankId][index].sfxImportance < evictImportance) {
                    evictIndex = index;
                    sfxId = gSfxBanks[bankId][index].sfxId & 0xFFFF;
                    evictImportance = gSfxParams[SFX_BANK_SHIFT(sfxId)][SFX_INDEX(sfxId)].importance;
                }

                count++;
                if (count == gUsedChannelsPerBank[gSfxChannelLayout][bankId]) {
                    if (gSfxParams[SFX_BANK_SHIFT(req->sfxId)][SFX_INDEX(req->sfxId)].importance >= evictImportance) {
                        index = evictIndex;
                    } else {
                        index = 0;
                    }
                }
            }

            if (count == gUsedChannelsPerBank[gSfxChannelLayout][bankId]) {
                sfxParams = &gSfxParams[SFX_BANK_SHIFT(req->sfxId)][SFX_INDEX(req->sfxId)];

                if ((req->sfxId & 0xC00) || (sfxParams->flags & 1) || (index == evictIndex)) {
                    if ((gSfxBanks[bankId][index].sfxParams & 8) &&
                        (gSfxBanks[bankId][index].state != SFX_STATE_QUEUED)) {
                        Audio_ClearFlagForBgmVolumeLow(gSfxBanks[bankId][index].channelIdx);
                    }

                    gSfxBanks[bankId][index].token = req->token;
                    gSfxBanks[bankId][index].sfxId = req->sfxId;
                    gSfxBanks[bankId][index].state = SFX_STATE_QUEUED;
                    gSfxBanks[bankId][index].freshness = 2;
                    gSfxBanks[bankId][index].freqScale = req->freqScale;
                    gSfxBanks[bankId][index].vol = req->vol;
                    gSfxBanks[bankId][index].reverbAdd = req->reverbAdd;
                    gSfxBanks[bankId][index].sfxParams = sfxParams->params;
                    gSfxBanks[bankId][index].sfxFlags = sfxParams->flags;
                    gSfxBanks[bankId][index].sfxImportance = sfxParams->importance;
                } else if (gSfxBanks[bankId][index].state == SFX_STATE_PLAYING_2) {
                    gSfxBanks[bankId][index].state = SFX_STATE_PLAYING_1;
                }

                index = 0;
            }
        }

        if (index != 0) {
            index = gSfxBanks[bankId][index].next;
        }
    }

    if ((gSfxBanks[bankId][sSfxBankFreeListStart[bankId]].next != 0xFF) && (index != 0)) {
        index = sSfxBankFreeListStart[bankId];

        entry = &gSfxBanks[bankId][index];
        entry->posX = &req->pos->x;
        entry->posY = &req->pos->y;
        entry->posZ = &req->pos->z;
        entry->token = req->token;
        entry->freqScale = req->freqScale;
        entry->vol = req->vol;
        entry->reverbAdd = req->reverbAdd;

        sfxParams = &gSfxParams[SFX_BANK_SHIFT(req->sfxId)][SFX_INDEX(req->sfxId)];
        entry->sfxParams = sfxParams->params;
        entry->sfxFlags = sfxParams->flags;
        entry->sfxImportance = sfxParams->importance;
        entry->sfxId = req->sfxId;
        entry->state = SFX_STATE_QUEUED;
        entry->freshness = 2;
        entry->prev = sSfxBankListEnd[bankId];

        gSfxBanks[bankId][sSfxBankListEnd[bankId]].next = sSfxBankFreeListStart[bankId];
        sSfxBankListEnd[bankId] = sSfxBankFreeListStart[bankId];
        sSfxBankFreeListStart[bankId] = gSfxBanks[bankId][sSfxBankFreeListStart[bankId]].next;
        gSfxBanks[bankId][sSfxBankFreeListStart[bankId]].prev = 0xFF;
        entry->next = 0xFF;
    }
}

void Audio_RemoveSfxBankEntry(u8 bankId, u8 entryIndex) {
    SfxBankEntry* entry = &gSfxBanks[bankId][entryIndex];
    u8 i;

    if (entry->sfxParams & 8) {
        Audio_ClearFlagForBgmVolumeLow(entry->channelIdx);
    }

    if (entryIndex == sSfxBankListEnd[bankId]) {
        sSfxBankListEnd[bankId] = entry->prev;
    } else {
        gSfxBanks[bankId][entry->next].prev = entry->prev;
    }

    gSfxBanks[bankId][entry->prev].next = entry->next;
    entry->next = sSfxBankFreeListStart[bankId];
    entry->prev = 0xFF;
    gSfxBanks[bankId][sSfxBankFreeListStart[bankId]].prev = entryIndex;
    sSfxBankFreeListStart[bankId] = entryIndex;
    entry->state = SFX_STATE_EMPTY;

    for (i = 0; i < gChannelsPerBank[gSfxChannelLayout][bankId]; i++) {
        if (gActiveSfxs[bankId][i].entryIndex == entryIndex) {
            gActiveSfxs[bankId][i].entryIndex = 0xFF;
            i = gChannelsPerBank[gSfxChannelLayout][bankId];
        }
    }
}

void Audio_ChooseActiveSfxs(u8 bankId) {
    u8 numChosenSfxs;
    u8 numChannels;
    u8 entryIndex;
    u8 i;
    u8 j;
    u8 k;
    u8 sfxImportance;
    u8 needNewSfx;
    u8 chosenEntryIndex;
    s32 pad;
    SfxBankEntry* entry;
    ActiveSfx chosenSfxs[MAX_CHANNELS_PER_BANK];
    ActiveSfx* activeSfx;
    f32 entryPosY;
    f32 entryPosX;

    numChosenSfxs = 0;
    for (i = 0; i < MAX_CHANNELS_PER_BANK; i++) {
        chosenSfxs[i].priority = 0x7FFFFFFF;
        chosenSfxs[i].entryIndex = 0xFF;
    }

    entryIndex = gSfxBanks[bankId][0].next;
    k = 0;
    while (entryIndex != 0xFF) {
        if ((gSfxBanks[bankId][entryIndex].state == SFX_STATE_QUEUED) &&
            (gSfxBanks[bankId][entryIndex].sfxId & 0xC00)) {
            gSfxBanks[bankId][entryIndex].freshness--;
        } else if (!(gSfxBanks[bankId][entryIndex].sfxId & 0xC00) &&
                   (gSfxBanks[bankId][entryIndex].state == SFX_STATE_PLAYING_2)) {
            Audio_QueueCmdS8((gSfxBanks[bankId][entryIndex].channelIdx << 8) | 0x6020000, 0);
            Audio_RemoveSfxBankEntry(bankId, entryIndex);
        }
        if (gSfxBanks[bankId][entryIndex].freshness == 0) {
            Audio_RemoveSfxBankEntry(bankId, entryIndex);
        } else if (gSfxBanks[bankId][entryIndex].state != SFX_STATE_EMPTY) {
            entry = &gSfxBanks[bankId][entryIndex];

            if (&gSfxDefaultPos.x == entry[0].posX) {
                entry->dist = 0.0f;
            } else {
                entryPosY = *entry->posY * 1;
                entryPosX = *entry->posX * 0.5f;
                entry->dist = (SQ(entryPosX) + SQ(entryPosY) + SQ(*entry->posZ)) / 10.0f;
            }

            sfxImportance = entry->sfxImportance;

            if (entry->sfxParams & 0x10) {
                entry->priority = SQ(0xFF - sfxImportance) * SQ(76);
            } else {
                if (entry->dist > 0x7FFFFFD0) {
                    entry->dist = 0x70000008;
                }
                entry->priority = (u32)entry->dist + (SQ(0xFF - sfxImportance) * SQ(76));
                if (*entry->posZ < 0.0f) {
                    entry->priority += (s32)(-*entry->posZ * 6.0f);
                }
            }

            if (entry->dist > SQ(1e5f)) {
                if (entry->state == SFX_STATE_PLAYING_1) {
                    Audio_QueueCmdS8((entry->channelIdx << 8) | 0x6020000, 0);
                    if (entry->sfxId & 0xC00) {
                        Audio_RemoveSfxBankEntry(bankId, entryIndex);
                        entryIndex = k;
                    }
                }
            } else {
                numChannels = gChannelsPerBank[gSfxChannelLayout][bankId];

                for (i = 0; i < numChannels; i++) {
                    if (chosenSfxs[i].priority >= entry->priority) {
                        if (numChosenSfxs < gChannelsPerBank[gSfxChannelLayout][bankId]) {
                            numChosenSfxs++;
                        }

                        for (j = numChannels - 1; j > i; j--) {
                            chosenSfxs[j].priority = chosenSfxs[j - 1].priority;
                            chosenSfxs[j].entryIndex = chosenSfxs[j - 1].entryIndex;
                        }

                        chosenSfxs[i].priority = entry->priority;
                        chosenSfxs[i].entryIndex = entryIndex;
                        i = numChannels; // make this the last pass through the loop, here equivalent to "break"
                    }
                }
            }

            k = entryIndex;
        }

        entryIndex = gSfxBanks[bankId][k].next;
    }

    for (i = 0; i < numChosenSfxs; i++) {
        entry = &gSfxBanks[bankId][chosenSfxs[i].entryIndex];

        if (entry->state == SFX_STATE_QUEUED) {
            entry->state = SFX_STATE_READY;
        } else if (entry->state == SFX_STATE_PLAYING_1) {
            entry->state = SFX_STATE_PLAYING_REFRESH;
        }
    }

    // Pick something to play for all channels.
    numChannels = gChannelsPerBank[gSfxChannelLayout][bankId];
    for (i = 0; i < numChannels; i++) {
        needNewSfx = false;
        activeSfx = &gActiveSfxs[bankId][i];

        if (activeSfx->entryIndex == 0xFF) {
            needNewSfx = true;
        } else {
            entry = &gSfxBanks[bankId][activeSfx[0].entryIndex];
            if (entry->state == SFX_STATE_PLAYING_1) {
                if (entry->sfxId & 0xC00) {
                    Audio_RemoveSfxBankEntry(bankId, activeSfx->entryIndex);
                } else {
                    entry->state = SFX_STATE_QUEUED;
                    entry->freshness = 0x80;
                }
                needNewSfx = true;
            } else if (entry->state == SFX_STATE_EMPTY) {
                activeSfx->entryIndex = 0xFF;
                needNewSfx = true;
            } else {
                // Sfx is already playing as it should, nothing to do.
                for (j = 0; j < numChannels; j++) {
                    if (activeSfx->entryIndex == chosenSfxs[j].entryIndex) {
                        chosenSfxs[j].entryIndex = 0xFF;
                        j = numChannels;
                    }
                }

                numChosenSfxs--;
            }
        }

        if (needNewSfx == true) {
            for (j = 0; j < numChannels; j++) {
                chosenEntryIndex = chosenSfxs[j].entryIndex;
                if ((chosenEntryIndex != 0xFF) &&
                    (gSfxBanks[bankId][chosenEntryIndex].state != SFX_STATE_PLAYING_REFRESH)) {
                    for (k = 0; k < numChannels; k++) {
                        if (chosenEntryIndex == gActiveSfxs[bankId][k].entryIndex) {
                            needNewSfx = false;
                            k = numChannels; // "break; i.e. force for-loop to end"
                        }
                    }

                    if (needNewSfx == true) {
                        activeSfx->entryIndex = chosenEntryIndex;
                        chosenSfxs[j].entryIndex = 0xFF;
                        j = numChannels + 1;
                        numChosenSfxs--;
                    }
                }
            }
            if (j == numChannels) {
                // nothing found
                activeSfx->entryIndex = 0xFF;
            }
        }
    }
}

void Audio_PlayActiveSfxs(u8 bankId) {
    u8 entryIndex;
    SequenceChannel* channel;
    SfxBankEntry* entry;
    u8 i;
    u8 ioPort5Data;

    for (i = 0; i < gChannelsPerBank[gSfxChannelLayout][bankId]; i++) {
        entryIndex = gActiveSfxs[bankId][i].entryIndex;
        if (entryIndex != 0xFF) {
            entry = &gSfxBanks[bankId][entryIndex];
            channel = gAudioContext.seqPlayers[SEQ_PLAYER_SFX].channels[sCurSfxPlayerChannelIdx];
            if (entry->state == SFX_STATE_READY) {
                entry->channelIdx = sCurSfxPlayerChannelIdx;
                if (entry->sfxParams & 8) {
                    Audio_SetFlagForBgmVolumeLow(sCurSfxPlayerChannelIdx);
                }

                if (entry->sfxParams & 0xC0) {
                    switch (entry->sfxParams & 0xC0) {
                        case 0x40:
                            entry->unk_2F = Audio_NextRandom() & 0xF;
                            break;
                        case 0x80:
                            entry->unk_2F = Audio_NextRandom() & 0x1F;
                            break;
                        case 0xC0:
                            entry->unk_2F = Audio_NextRandom() & 0x3F;
                            break;
                        default:
                            entry->unk_2F = 0;
                            break;
                    }
                }

                Audio_SetSfxProperties(bankId, entryIndex, sCurSfxPlayerChannelIdx);
                Audio_QueueCmdS8(0x06020000 | ((sCurSfxPlayerChannelIdx & 0xFF) << 8), 1);
                Audio_QueueCmdS8(0x06020000 | ((sCurSfxPlayerChannelIdx & 0xFF) << 8) | 4, entry->sfxId & 0xFF);

                if (D_801D6600[bankId]) {
                    ioPort5Data = ((u8)((entry->sfxId & 0x300) >> 7) + (u8)((entry->sfxId & 0xFF) >> 7));
                } else {
                    ioPort5Data = 0;
                }

                if ((entry->sfxParams & 0x100) && (entry->freshness == 0x80)) {
                    ioPort5Data += 0x80;
                }

                if (D_801D6608[bankId]) {
                    Audio_QueueCmdS8(0x06020000 | ((sCurSfxPlayerChannelIdx & 0xFF) << 8) | 5, ioPort5Data);
                }

                if (entry->sfxId & 0xC00) {
                    entry->state = SFX_STATE_PLAYING_1;
                } else {
                    entry->state = SFX_STATE_PLAYING_2;
                }
            } else if ((u8)channel->soundScriptIO[1] == 0xFF) {
                Audio_RemoveSfxBankEntry(bankId, entryIndex);
            } else if (entry->state == SFX_STATE_PLAYING_REFRESH) {
                Audio_SetSfxProperties(bankId, entryIndex, sCurSfxPlayerChannelIdx);
                if (entry->sfxId & 0xC00) {
                    entry->state = SFX_STATE_PLAYING_1;
                } else {
                    entry->state = SFX_STATE_PLAYING_2;
                }
            }
        }

        sCurSfxPlayerChannelIdx++;
    }
}

void Audio_StopSfxByBank(u8 bankId) {
    SfxBankEntry* entry;
    s32 pad;
    SfxBankEntry entryToRemove;
    u8 entryIndex = gSfxBanks[bankId][0].next;

    while (entryIndex != 0xFF) {
        entry = &gSfxBanks[bankId][entryIndex];
        if (entry->state >= SFX_STATE_PLAYING_REFRESH) {
            Audio_QueueCmdS8(0x06020000 | ((entry->channelIdx & 0xFF) << 8), 0);
        }

        if (entry->state != SFX_STATE_EMPTY) {
            Audio_RemoveSfxBankEntry(bankId, entryIndex);
        }
        entryIndex = gSfxBanks[bankId][0].next;
    }

    entryToRemove.sfxId = bankId << 12;
    Audio_RemoveMatchingSfxRequests(0, &entryToRemove);
}

void func_801A7168(u8 bankId, Vec3f* pos) {
    SfxBankEntry* entry;
    u8 entryIndex = gSfxBanks[bankId][0].next;
    u8 prevEntryIndex = 0;

    while (entryIndex != 0xFF) {
        entry = &gSfxBanks[bankId][entryIndex];
        if (entry->posX == &pos->x) {
            if (entry->state >= SFX_STATE_PLAYING_REFRESH) {
                Audio_QueueCmdS8(0x06020000 | ((entry->channelIdx & 0xFF) << 8), 0);
            }

            if (entry->state != SFX_STATE_EMPTY) {
                Audio_RemoveSfxBankEntry(bankId, entryIndex);
            }
        } else {
            prevEntryIndex = entryIndex;
        }

        entryIndex = gSfxBanks[bankId][prevEntryIndex].next;
    }
}

void Audio_StopSfxByPosAndBank(u8 bankId, Vec3f* pos) {
    SfxBankEntry entryToRemove;

    func_801A7168(bankId, pos);
    entryToRemove.sfxId = bankId << 12;
    entryToRemove.posX = &pos->x;
    Audio_RemoveMatchingSfxRequests(1, &entryToRemove);
}

void Audio_StopSfxByPos(Vec3f* pos) {
    u8 bankId;
    SfxBankEntry entryToRemove;

    for (bankId = 0; bankId < ARRAY_COUNT(gSfxBanks); bankId++) {
        func_801A7168(bankId, pos);
    }

    entryToRemove.posX = &pos->x;
    Audio_RemoveMatchingSfxRequests(2, &entryToRemove);
}

void Audio_StopSfxByPosAndId(Vec3f* pos, u16 sfxId) {
    SfxBankEntry* entry;
    u8 entryIndex = gSfxBanks[SFX_BANK(sfxId)][0].next;
    u8 prevEntryIndex = 0;
    SfxBankEntry entryToRemove;

    while (entryIndex != 0xFF) {
        entry = &gSfxBanks[SFX_BANK(sfxId)][entryIndex];
        if (entry->posX == &pos->x && entry->sfxId == sfxId) {
            if (entry->state >= SFX_STATE_PLAYING_REFRESH) {
                Audio_QueueCmdS8(0x06020000 | ((entry->channelIdx & 0xFF) << 8), 0);
            }

            if (entry->state != SFX_STATE_EMPTY) {
                Audio_RemoveSfxBankEntry(SFX_BANK(sfxId), entryIndex);
            }
            entryIndex = 0xFF;
        } else {
            prevEntryIndex = entryIndex;
        }

        if (entryIndex != 0xFF) {
            entryIndex = gSfxBanks[SFX_BANK(sfxId)][prevEntryIndex].next;
        }
    }

    entryToRemove.posX = &pos->x;
    entryToRemove.sfxId = sfxId;
    Audio_RemoveMatchingSfxRequests(3, &entryToRemove);
}

void Audio_StopSfxByTokenAndId(u8 token, u16 sfxId) {
    SfxBankEntry* entry;
    u8 entryIndex = gSfxBanks[SFX_BANK(sfxId)][0].next;
    u8 prevEntryIndex = 0;
    SfxBankEntry entryToRemove;

    while (entryIndex != 0xFF) {
        entry = &gSfxBanks[SFX_BANK(sfxId)][entryIndex];
        if ((entry->token == token) && (entry->sfxId == sfxId)) {
            if (entry->state >= SFX_STATE_PLAYING_REFRESH) {
                Audio_QueueCmdS8(0x06020000 | ((entry->channelIdx & 0xFF) << 8), 0);
            }

            if (entry->state != SFX_STATE_EMPTY) {
                Audio_RemoveSfxBankEntry(SFX_BANK(sfxId), entryIndex);
            }
        } else {
            prevEntryIndex = entryIndex;
        }

        if (entryIndex != 0xFF) {
            entryIndex = gSfxBanks[SFX_BANK(sfxId)][prevEntryIndex].next;
        }
    }

    entryToRemove.token = token;
    entryToRemove.sfxId = sfxId;
    Audio_RemoveMatchingSfxRequests(4, &entryToRemove);
}

void Audio_StopSfxById(u32 sfxId) {
    SfxBankEntry* entry;
    u8 entryIndex = gSfxBanks[SFX_BANK(sfxId)][0].next;
    u8 prevEntryIndex = 0;
    SfxBankEntry entryToRemove;

    while (entryIndex != 0xFF) {
        entry = &gSfxBanks[SFX_BANK(sfxId)][entryIndex];
        if (entry->sfxId == sfxId) {
            if (entry->state >= SFX_STATE_PLAYING_REFRESH) {
                Audio_QueueCmdS8(0x06020000 | ((entry->channelIdx & 0xFF) << 8), 0);
            }
            if (entry->state != SFX_STATE_EMPTY) {
                Audio_RemoveSfxBankEntry(SFX_BANK(sfxId), entryIndex);
            }
        } else {
            prevEntryIndex = entryIndex;
        }

        entryIndex = gSfxBanks[SFX_BANK(sfxId)][prevEntryIndex].next;
    }

    entryToRemove.sfxId = sfxId;
    Audio_RemoveMatchingSfxRequests(5, &entryToRemove);
}

void Audio_ProcessSfxRequests(void) {
    if (gAudioContext.seqPlayers[SEQ_PLAYER_SFX].enabled) {
        while (sSfxRequestWriteIndex != sSfxRequestReadIndex) {
            Audio_ProcessSfxRequest();
            sSfxRequestReadIndex++;
        }
    }
}

/**
 * Unused
 */
void Audio_SetSfxBankLerp(u8 bankId, u8 target, u16 delay) {
    if (delay == 0) {
        delay++;
    }

    sSfxBankLerp[bankId].target = target / 127.0f;
    sSfxBankLerp[bankId].remainingFrames = delay;
    sSfxBankLerp[bankId].step = ((sSfxBankLerp[bankId].value - sSfxBankLerp[bankId].target) / delay);
}

/**
 * Unused
 */
void Audio_StepSfxBankLerp(u8 bankId) {
    if (sSfxBankLerp[bankId].remainingFrames != 0) {
        sSfxBankLerp[bankId].remainingFrames--;

        if (sSfxBankLerp[bankId].remainingFrames != 0) {
            sSfxBankLerp[bankId].value -= sSfxBankLerp[bankId].step;
        } else {
            sSfxBankLerp[bankId].value = sSfxBankLerp[bankId].target;
        }
    }
}

void Audio_ProcessActiveSfxs(void) {
    u8 bankId;

    if (gAudioContext.seqPlayers[SEQ_PLAYER_SFX].enabled) {
        sCurSfxPlayerChannelIdx = 0;

        for (bankId = 0; bankId < ARRAY_COUNT(gSfxBanks); bankId++) {
            Audio_ChooseActiveSfxs(bankId);
            Audio_PlayActiveSfxs(bankId);
            Audio_StepSfxBankLerp(bankId);
        }
    }
}

u8 Audio_IsSfxPlaying(u32 sfxId) {
    SfxBankEntry* entry;
    u8 entryIndex = gSfxBanks[SFX_BANK(sfxId)][0].next;

    while (entryIndex != 0xFF) {
        entry = &gSfxBanks[SFX_BANK(sfxId)][entryIndex];
        if (entry->sfxId == sfxId) {
            return true;
        }
        entryIndex = entry->next;
    }

    return false;
}

void Audio_ResetSfxs(void) {
    u8 bankId;
    u8 i;
    u8 entryIndex;

    sSfxRequestWriteIndex = 0;
    sSfxRequestReadIndex = 0;
    sSfxChannelLowVolumeFlag = 0;

    for (bankId = 0; bankId < ARRAY_COUNT(gSfxBanks); bankId++) {
        sSfxBankListEnd[bankId] = 0;
        sSfxBankFreeListStart[bankId] = 1;
        sSfxBankUnused[bankId] = 0;
        gSfxBankMuted[bankId] = false;
        sSfxBankLerp[bankId].value = 1.0f;
        sSfxBankLerp[bankId].remainingFrames = 0;
    }

    for (bankId = 0; bankId < ARRAY_COUNT(gSfxBanks); bankId++) {
        for (i = 0; i < MAX_CHANNELS_PER_BANK; i++) {
            gActiveSfxs[bankId][i].entryIndex = 0xFF;
        }
    }

    for (bankId = 0; bankId < ARRAY_COUNT(gSfxBanks); bankId++) {
        gSfxBanks[bankId][0].prev = 0xFF;
        gSfxBanks[bankId][0].next = 0xFF;

        for (i = 1; i < sBankSizes[bankId] - 1; i++) {
            gSfxBanks[bankId][i].prev = i - 1;
            gSfxBanks[bankId][i].next = i + 1;
        }

        gSfxBanks[bankId][i].prev = i - 1;
        gSfxBanks[bankId][i].next = 0xFF;
    }
}
