/**
 * @file audio_thread.c
 *
 * Top-level file that coordinates all audio code on the audio thread.
 */
#include "global.h"
#include "audio/effects.h"

AudioTask* AudioThread_UpdateImpl(void);
void AudioThread_SetFadeOutTimer(s32 seqPlayerIndex, s32 fadeTimer);
void AudioThread_SetFadeInTimer(s32 seqPlayerIndex, s32 fadeTimer);
void AudioThread_ProcessCmds(u32 msg);
void AudioThread_ProcessSeqPlayerCmd(SequencePlayer* seqPlayer, AudioCmd* cmd);
void AudioThread_ProcessChannelCmd(SequenceChannel* channel, AudioCmd* cmd);
s32 AudioThread_GetSamplePos(s32 seqPlayerIndex, s32 channelIndex, s32 layerIndex, s32* loopEnd, s32* samplePosInt);
s32 AudioThread_CountAndReleaseNotes(s32 flags);

AudioTask* AudioThread_Update(void) {
    return AudioThread_UpdateImpl();
}

AudioTask* AudioThread_UpdateImpl(void) {
    static AudioTask* sWaitingAudioTask = NULL;
    u32 numSamplesRemainingInAi;
    s32 numAbiCmds;
    s32 pad;
    s32 j;
    s32 dmaCount;
    s16* curAiBuffer;
    OSTask_t* task;
    s32 index;
    u32 msg;
    s32 validCount;
    s32 i;

    gAudioCtx.totalTaskCount++;
    if ((gAudioCtx.totalTaskCount % gAudioCtx.audioBufferParameters.specUnk4) != 0) {
        if (gAudioCustomUpdateFunction != NULL) {
            gAudioCustomUpdateFunction();
        }

        if (((gAudioCtx.totalTaskCount % gAudioCtx.audioBufferParameters.specUnk4) + 1) ==
            gAudioCtx.audioBufferParameters.specUnk4) {
            return sWaitingAudioTask;
        }

        return NULL;
    }

    osSendMesg(gAudioCtx.taskStartQueueP, (OSMesg)gAudioCtx.totalTaskCount, OS_MESG_NOBLOCK);
    gAudioCtx.rspTaskIndex ^= 1;
    gAudioCtx.curAiBufferIndex++;
    gAudioCtx.curAiBufferIndex %= 3;
    index = (gAudioCtx.curAiBufferIndex + 1) % 3;

    // Division converts size to numSamples: 2 channels (left/right) * 2 bytes per sample
    numSamplesRemainingInAi = osAiGetLength() / (2 * SAMPLE_SIZE);

    if (gAudioCtx.resetTimer < 16) {
        if (gAudioCtx.numSamplesPerFrame[index] != 0) {
            osAiSetNextBuffer(gAudioCtx.aiBuffers[index], 2 * gAudioCtx.numSamplesPerFrame[index] * (s32)SAMPLE_SIZE);
            if (gAudioCtx.aiBuffers[index]) {}
            if (gAudioCtx.numSamplesPerFrame[index]) {}
        }
    }

    if (gAudioCustomUpdateFunction != NULL) {
        gAudioCustomUpdateFunction();
    }

    dmaCount = gAudioCtx.curAudioFrameDmaCount;
    for (i = 0; i < gAudioCtx.curAudioFrameDmaCount; i++) {
        if (osRecvMesg(&gAudioCtx.curAudioFrameDmaQueue, NULL, OS_MESG_NOBLOCK) == 0) {
            dmaCount--;
        }
    }

    if (dmaCount != 0) {
        for (i = 0; i < dmaCount; i++) {
            osRecvMesg(&gAudioCtx.curAudioFrameDmaQueue, NULL, OS_MESG_BLOCK);
        }
    }

    validCount = gAudioCtx.curAudioFrameDmaQueue.validCount;
    if (validCount != 0) {
        for (i = 0; i < validCount; i++) {
            osRecvMesg(&gAudioCtx.curAudioFrameDmaQueue, NULL, OS_MESG_NOBLOCK);
        }
    }

    gAudioCtx.curAudioFrameDmaCount = 0;
    AudioLoad_DecreaseSampleDmaTtls();
    AudioLoad_ProcessLoads(gAudioCtx.resetStatus);
    AudioLoad_ProcessScriptLoads();

    if (gAudioCtx.resetStatus != 0) {
        if (AudioHeap_ResetStep() == 0) {
            if (gAudioCtx.resetStatus == 0) {
                osSendMesg(gAudioCtx.audioResetQueueP, (OSMesg)(uintptr_t)gAudioCtx.specId, OS_MESG_NOBLOCK);
            }

            sWaitingAudioTask = NULL;
            return NULL;
        }
    }

    if (gAudioCtx.resetTimer > 16) {
        return NULL;
    }
    if (gAudioCtx.resetTimer != 0) {
        gAudioCtx.resetTimer++;
    }

    gAudioCtx.curTask = &gAudioCtx.rspTask[gAudioCtx.rspTaskIndex];
    gAudioCtx.curAbiCmdBuf = gAudioCtx.abiCmdBufs[gAudioCtx.rspTaskIndex];

    index = gAudioCtx.curAiBufferIndex;
    curAiBuffer = gAudioCtx.aiBuffers[index];

    gAudioCtx.numSamplesPerFrame[index] =
        (s16)((((gAudioCtx.audioBufferParameters.numSamplesPerFrameTarget - numSamplesRemainingInAi) +
                (8 * SAMPLES_PER_FRAME)) &
               ~0xF) +
              (1 * SAMPLES_PER_FRAME));

    // Clamp numSamplesPerFrame between numSamplesPerFrameMin and numSamplesPerFrameMax
    if (gAudioCtx.numSamplesPerFrame[index] < gAudioCtx.audioBufferParameters.numSamplesPerFrameMin) {
        gAudioCtx.numSamplesPerFrame[index] = gAudioCtx.audioBufferParameters.numSamplesPerFrameMin;
    }
    if (gAudioCtx.numSamplesPerFrame[index] > gAudioCtx.audioBufferParameters.numSamplesPerFrameMax) {
        gAudioCtx.numSamplesPerFrame[index] = gAudioCtx.audioBufferParameters.numSamplesPerFrameMax;
    }

    j = 0;
    if (gAudioCtx.resetStatus == 0) {
        // msg = 0000RREE R = read pos, E = End Pos
        while (osRecvMesg(gAudioCtx.threadCmdProcQueueP, (OSMesg*)&msg, OS_MESG_NOBLOCK) != -1) {
            //! FAKE:
            if (1) {}
            AudioThread_ProcessCmds(msg);
            j++;
        }
        if ((j == 0) && gAudioCtx.threadCmdQueueFinished) {
            AudioThread_ScheduleProcessCmds();
        }
    }

    if (gAudioSPDataPtr == (u64*)gAudioCtx.curAbiCmdBuf) {
        return (void*)-1;
    }

    gAudioCtx.curAbiCmdBuf =
        AudioSynth_Update(gAudioCtx.curAbiCmdBuf, &numAbiCmds, curAiBuffer, gAudioCtx.numSamplesPerFrame[index]);

    // Update audioRandom to the next random number
    gAudioCtx.audioRandom = (gAudioCtx.audioRandom + gAudioCtx.totalTaskCount) * osGetCount();
    gAudioCtx.audioRandom = gAudioCtx.audioRandom + gAudioCtx.aiBuffers[index][gAudioCtx.totalTaskCount & 0xFF];

    // gWaveSamples[8] interprets compiled assembly code as s16 samples as a way to generate sound with noise.
    // Start with the address of AudioThread_Update(), and offset it by a random number between 0 - 0xFFF0
    // Use the resulting address as the starting address to interpret an array of samples i.e. `s16 samples[]`
    gWaveSamples[8] = (s16*)((u8*)AudioThread_Update + (gAudioCtx.audioRandom & 0xFFF0));

    index = gAudioCtx.rspTaskIndex;
    gAudioCtx.curTask->taskQueue = NULL;
    gAudioCtx.curTask->unk_44 = NULL;

    task = &gAudioCtx.curTask->task.t;
    task->type = M_AUDTASK;
    task->flags = 0;
    task->ucodeBoot = aspMainTextStart;
    task->ucodeBootSize = SP_UCODE_SIZE;
    task->ucodeDataSize = ((aspMainDataEnd - aspMainDataStart) * sizeof(u64)) - 1;
    task->ucode = aspMainTextStart;
    task->ucodeData = aspMainDataStart;
    task->ucodeSize = SP_UCODE_SIZE;
    task->dramStack = (u64*)D_801D6200;
    task->dramStackSize = 0;
    task->outputBuff = NULL;
    task->outputBuffSize = NULL;
    if (1) {}
    task->dataPtr = (u64*)gAudioCtx.abiCmdBufs[index];
    task->dataSize = numAbiCmds * sizeof(Acmd);
    task->yieldDataPtr = NULL;
    task->yieldDataSize = 0;

    if (gAudioCtx.numAbiCmdsMax < numAbiCmds) {
        gAudioCtx.numAbiCmdsMax = numAbiCmds;
    }

    if (gAudioCtx.audioBufferParameters.specUnk4 == 1) {
        return gAudioCtx.curTask;
    } else {
        sWaitingAudioTask = gAudioCtx.curTask;
        return NULL;
    }
}

void AudioThread_ProcessGlobalCmd(AudioCmd* cmd) {
    s32 i;
    s32 pad;

    switch (cmd->op) {
        case AUDIOCMD_OP_GLOBAL_SYNC_LOAD_SEQ_PARTS:
            AudioLoad_SyncLoadSeqParts(cmd->arg1, cmd->arg2, cmd->asInt, &gAudioCtx.externalLoadQueue);
            break;

        case AUDIOCMD_OP_GLOBAL_INIT_SEQPLAYER:
            AudioLoad_SyncInitSeqPlayer(cmd->arg0, cmd->arg1, cmd->arg2);
            AudioThread_SetFadeInTimer(cmd->arg0, cmd->asInt);
            break;

        case AUDIOCMD_OP_GLOBAL_INIT_SEQPLAYER_SKIP_TICKS:
            AudioLoad_SyncInitSeqPlayerSkipTicks(cmd->arg0, cmd->arg1, cmd->asInt);
            AudioThread_SetFadeInTimer(cmd->arg0, 500);
            AudioScript_SkipForwardSequence(&gAudioCtx.seqPlayers[cmd->arg0]);
            break;

        case AUDIOCMD_OP_GLOBAL_DISABLE_SEQPLAYER:
            if (gAudioCtx.seqPlayers[cmd->arg0].enabled) {
                if (cmd->asInt == 0) {
                    AudioScript_SequencePlayerDisableAsFinished(&gAudioCtx.seqPlayers[cmd->arg0]);
                } else {
                    AudioThread_SetFadeOutTimer(cmd->arg0, cmd->asInt);
                }
            }
            break;

        case AUDIOCMD_OP_GLOBAL_SET_SOUND_MODE:
            gAudioCtx.soundMode = cmd->asInt;
            break;

        case AUDIOCMD_OP_GLOBAL_MUTE:
            if (cmd->arg0 == AUDIOCMD_ALL_SEQPLAYERS) {
                for (i = 0; i < gAudioCtx.audioBufferParameters.numSequencePlayers; i++) {
                    gAudioCtx.seqPlayers[i].muted = true;
                    gAudioCtx.seqPlayers[i].recalculateVolume = true;
                }
            } else {
                gAudioCtx.seqPlayers[cmd->arg0].muted = true;
                gAudioCtx.seqPlayers[cmd->arg0].recalculateVolume = true;
            }
            break;

        case AUDIOCMD_OP_GLOBAL_UNMUTE:
            if (cmd->asInt == true) {
                for (i = 0; i < gAudioCtx.numNotes; i++) {
                    Note* note = &gAudioCtx.notes[i];
                    NoteSampleState* noteSampleState = &note->sampleState;

                    if (noteSampleState->bitField0.enabled && (note->playbackState.status == PLAYBACK_STATUS_0) &&
                        (note->playbackState.parentLayer->channel->muteFlags & MUTE_FLAGS_STOP_SAMPLES)) {
                        noteSampleState->bitField0.finished = true;
                    }
                }
            }

            if (cmd->arg0 == AUDIOCMD_ALL_SEQPLAYERS) {
                for (i = 0; i < gAudioCtx.audioBufferParameters.numSequencePlayers; i++) {
                    gAudioCtx.seqPlayers[i].muted = false;
                    gAudioCtx.seqPlayers[i].recalculateVolume = true;
                }
            } else {
                gAudioCtx.seqPlayers[cmd->arg0].muted = false;
                gAudioCtx.seqPlayers[cmd->arg0].recalculateVolume = true;
            }

            break;

        case AUDIOCMD_OP_GLOBAL_SYNC_LOAD_INSTRUMENT:
            AudioLoad_SyncLoadInstrument(cmd->arg0, cmd->arg1, cmd->arg2);
            break;

        case AUDIOCMD_OP_GLOBAL_ASYNC_LOAD_SAMPLE_BANK:
            AudioLoad_AsyncLoadSampleBank(cmd->arg0, cmd->arg1, cmd->arg2, &gAudioCtx.externalLoadQueue);
            break;

        case AUDIOCMD_OP_GLOBAL_ASYNC_LOAD_FONT:
            AudioLoad_AsyncLoadFont(cmd->arg0, cmd->arg1, cmd->arg2, &gAudioCtx.externalLoadQueue);
            break;

        case AUDIOCMD_OP_GLOBAL_ASYNC_LOAD_SEQ:
            AudioLoad_AsyncLoadSeq(cmd->arg0, cmd->arg1, cmd->arg2, &gAudioCtx.externalLoadQueue);
            break;

        case AUDIOCMD_OP_GLOBAL_DISCARD_SEQ_FONTS:
            AudioLoad_DiscardSeqFonts(cmd->arg1);
            break;

        case AUDIOCMD_OP_GLOBAL_SET_CHANNEL_MASK:
            gAudioCtx.threadCmdChannelMask[cmd->arg0] = cmd->asUShort;
            break;

        case AUDIOCMD_OP_GLOBAL_RESET_AUDIO_HEAP:
            gAudioCtx.resetStatus = 5;
            gAudioCtx.specId = cmd->asUInt;
            break;

        case AUDIOCMD_OP_GLOBAL_SET_CUSTOM_UPDATE_FUNCTION:
            gAudioCustomUpdateFunction = cmd->asPtr;
            break;

        case AUDIOCMD_OP_GLOBAL_SET_CUSTOM_FUNCTION:
            if (cmd->arg2 == AUDIO_CUSTOM_FUNCTION_REVERB) {
                gAudioCustomReverbFunction = cmd->asPtr;
            } else if (cmd->arg2 == AUDIO_CUSTOM_FUNCTION_SYNTH) {
                gAudioCustomSynthFunction = cmd->asPtr;
            } else {
                gAudioCtx.customSeqFunctions[cmd->arg2] = cmd->asPtr;
            }
            break;

        case AUDIOCMD_OP_GLOBAL_SET_DRUM_FONT:
        case AUDIOCMD_OP_GLOBAL_SET_SFX_FONT:
        case AUDIOCMD_OP_GLOBAL_SET_INSTRUMENT_FONT:
            if (AudioPlayback_SetFontInstrument(cmd->op - AUDIOCMD_OP_GLOBAL_SET_DRUM_FONT, cmd->arg1, cmd->arg2,
                                                cmd->asPtr)) {}
            break;

        case AUDIOCMD_OP_GLOBAL_DISABLE_ALL_SEQPLAYERS: {
            u32 flags = cmd->asUInt;

            if (flags == AUDIO_NOTE_RELEASE) {
                for (i = 0; i < gAudioCtx.audioBufferParameters.numSequencePlayers; i++) {
                    if (gAudioCtx.seqPlayers[i].enabled) {
                        AudioScript_SequencePlayerDisableAsFinished(&gAudioCtx.seqPlayers[i]);
                    }
                }
            }
            AudioThread_CountAndReleaseNotes(flags);
            break;
        }

        case AUDIOCMD_OP_GLOBAL_POP_PERSISTENT_CACHE:
            AudioHeap_PopPersistentCache(cmd->asInt);
            break;

        case AUDIOCMD_OP_GLOBAL_E5:
            func_8018FA60(cmd->arg0, cmd->arg1, cmd->arg2, cmd->asInt);
            break;

        case AUDIOCMD_OP_GLOBAL_SET_REVERB_DATA:
            AudioHeap_SetReverbData(cmd->arg1, cmd->arg0, cmd->asInt, false);
            break;

        default:
            break;
    }
}

void AudioThread_SetFadeOutTimer(s32 seqPlayerIndex, s32 fadeTimer) {
    SequencePlayer* seqPlayer = &gAudioCtx.seqPlayers[seqPlayerIndex];

    if (fadeTimer == 0) {
        fadeTimer = 1;
    }

    seqPlayer->fadeVelocity = -(seqPlayer->fadeVolume / fadeTimer);
    seqPlayer->state = SEQPLAYER_STATE_FADE_OUT;
    seqPlayer->fadeTimer = fadeTimer;
}

void AudioThread_SetFadeInTimer(s32 seqPlayerIndex, s32 fadeTimer) {
    SequencePlayer* seqPlayer;

    if (fadeTimer != 0) {
        seqPlayer = &gAudioCtx.seqPlayers[seqPlayerIndex];
        seqPlayer->state = SEQPLAYER_STATE_FADE_IN;
        seqPlayer->storedFadeTimer = fadeTimer;
        seqPlayer->fadeTimer = fadeTimer;
        seqPlayer->fadeVolume = 0.0f;
        seqPlayer->fadeVelocity = 0.0f;
    }
}

void AudioThread_InitMesgQueuesInternal(void) {
    gAudioCtx.threadCmdWritePos = 0;
    gAudioCtx.threadCmdReadPos = 0;
    gAudioCtx.threadCmdQueueFinished = false;

    gAudioCtx.taskStartQueueP = &gAudioCtx.taskStartQueue;
    gAudioCtx.threadCmdProcQueueP = &gAudioCtx.threadCmdProcQueue;
    gAudioCtx.audioResetQueueP = &gAudioCtx.audioResetQueue;

    osCreateMesgQueue(gAudioCtx.taskStartQueueP, gAudioCtx.taskStartMsgs, ARRAY_COUNT(gAudioCtx.taskStartMsgs));
    osCreateMesgQueue(gAudioCtx.threadCmdProcQueueP, gAudioCtx.threadCmdProcMsgBuf,
                      ARRAY_COUNT(gAudioCtx.threadCmdProcMsgBuf));
    osCreateMesgQueue(gAudioCtx.audioResetQueueP, gAudioCtx.audioResetMesgs, ARRAY_COUNT(gAudioCtx.audioResetMesgs));
}

void AudioThread_QueueCmd(u32 opArgs, void** data) {
    AudioCmd* cmd = &gAudioCtx.threadCmdBuf[gAudioCtx.threadCmdWritePos & 0xFF];

    cmd->opArgs = opArgs;
    cmd->data = *data;

    gAudioCtx.threadCmdWritePos++;

    if (gAudioCtx.threadCmdWritePos == gAudioCtx.threadCmdReadPos) {
        gAudioCtx.threadCmdWritePos--;
    }
}

void AudioThread_QueueCmdF32(u32 opArgs, f32 data) {
    AudioThread_QueueCmd(opArgs, (void**)&data);
}

void AudioThread_QueueCmdS32(u32 opArgs, s32 data) {
    AudioThread_QueueCmd(opArgs, (void**)&data);
}

void AudioThread_QueueCmdS8(u32 opArgs, s8 data) {
    u32 uData = data << 0x18;

    AudioThread_QueueCmd(opArgs, (void**)&uData);
}

void AudioThread_QueueCmdU16(u32 opArgs, u16 data) {
    u32 uData = data << 0x10;

    AudioThread_QueueCmd(opArgs, (void**)&uData);
}

s32 AudioThread_ScheduleProcessCmds(void) {
    static s32 sMaxWriteReadDiff = 0;
    s32 ret;

    if (sMaxWriteReadDiff < (u8)((gAudioCtx.threadCmdWritePos - gAudioCtx.threadCmdReadPos) + 0x100)) {
        sMaxWriteReadDiff = (u8)((gAudioCtx.threadCmdWritePos - gAudioCtx.threadCmdReadPos) + 0x100);
    }

    ret = osSendMesg(gAudioCtx.threadCmdProcQueueP,
                     (void*)(((gAudioCtx.threadCmdReadPos & 0xFF) << 8) | (gAudioCtx.threadCmdWritePos & 0xFF)),
                     OS_MESG_NOBLOCK);
    if (ret != -1) {
        gAudioCtx.threadCmdReadPos = gAudioCtx.threadCmdWritePos;
        ret = 0;
    } else {
        return -1;
    }

    return ret;
}

void AudioThread_ResetCmdQueue(void) {
    gAudioCtx.threadCmdQueueFinished = false;
    gAudioCtx.threadCmdReadPos = gAudioCtx.threadCmdWritePos;
}

void AudioThread_ProcessCmd(AudioCmd* cmd) {
    SequencePlayer* seqPlayer;
    u16 threadCmdChannelMask;
    s32 channelIndex;

    if ((cmd->op & 0xF0) >= 0xE0) {
        AudioThread_ProcessGlobalCmd(cmd);
        return;
    }

    if (cmd->arg0 < gAudioCtx.audioBufferParameters.numSequencePlayers) {
        seqPlayer = &gAudioCtx.seqPlayers[cmd->arg0];
        if (cmd->op & 0x80) {
            AudioThread_ProcessGlobalCmd(cmd);
            return;
        }

        if (cmd->op & 0x40) {
            AudioThread_ProcessSeqPlayerCmd(seqPlayer, cmd);
            return;
        }

        if (cmd->arg1 < SEQ_NUM_CHANNELS) {
            AudioThread_ProcessChannelCmd(seqPlayer->channels[cmd->arg1], cmd);
            return;
        }

        if (cmd->arg1 == AUDIOCMD_ALL_CHANNELS) {
            threadCmdChannelMask = gAudioCtx.threadCmdChannelMask[cmd->arg0];
            for (channelIndex = 0; channelIndex < SEQ_NUM_CHANNELS; channelIndex++) {
                if (threadCmdChannelMask & 1) {
                    AudioThread_ProcessChannelCmd(seqPlayer->channels[channelIndex], cmd);
                }
                threadCmdChannelMask = threadCmdChannelMask >> 1;
            }
        }
    }
}

void AudioThread_ProcessCmds(u32 msg) {
    static u8 sCurCmdRdPos = 0;
    AudioCmd* cmd;
    u8 endPos;

    if (!gAudioCtx.threadCmdQueueFinished) {
        sCurCmdRdPos = msg >> 8;
    }

    while (true) {
        endPos = msg & 0xFF;
        if (sCurCmdRdPos == endPos) {
            gAudioCtx.threadCmdQueueFinished = false;
            break;
        }

        cmd = &gAudioCtx.threadCmdBuf[sCurCmdRdPos++ & 0xFF];
        if (cmd->op == AUDIOCMD_OP_GLOBAL_STOP_AUDIOCMDS) {
            gAudioCtx.threadCmdQueueFinished = true;
            break;
        }

        AudioThread_ProcessCmd(cmd);
        cmd->op = AUDIOCMD_OP_NOOP;
    }
}

u32 AudioThread_GetExternalLoadQueueMsg(u32* retMsg) {
    u32 msg;

    if (osRecvMesg(&gAudioCtx.externalLoadQueue, (OSMesg*)&msg, OS_MESG_NOBLOCK) == -1) {
        *retMsg = 0;
        return 0;
    }

    *retMsg = msg & 0xFFFFFF;
    return msg >> 0x18;
}

u8* AudioThread_GetFontsForSequence(s32 seqId, u32* outNumFonts) {
    return AudioLoad_GetFontsForSequence(seqId, outNumFonts);
}

void AudioThread_GetSampleBankIdsOfFont(s32 fontId, u32* sampleBankId1, u32* sampleBankId2) {
    *sampleBankId1 = gAudioCtx.soundFontList[fontId].sampleBankId1;
    *sampleBankId2 = gAudioCtx.soundFontList[fontId].sampleBankId2;
}

s32 func_80193C5C(void) {
    s32 pad;
    s32 specId;

    if (osRecvMesg(gAudioCtx.audioResetQueueP, (OSMesg*)&specId, OS_MESG_NOBLOCK) == -1) {
        return 0;
    } else if (gAudioCtx.specId != specId) {
        return -1;
    } else {
        return 1;
    }
}

void AudioThread_WaitForAudioResetQueueP(void) {
    // macro?
    // clang-format off
    s32 chk = -1; s32 msg; do {} while (osRecvMesg(gAudioCtx.audioResetQueueP, (OSMesg*)&msg, OS_MESG_NOBLOCK) != chk);
    // clang-format on
}

s32 AudioThread_ResetAudioHeap(s32 specId) {
    s32 resetStatus;
    OSMesg msg;
    s32 pad;

    AudioThread_WaitForAudioResetQueueP();
    resetStatus = gAudioCtx.resetStatus;
    if (resetStatus != 0) {
        AudioThread_ResetCmdQueue();
        if (gAudioCtx.specId == specId) {
            return -2;
        } else if (resetStatus > 2) {
            gAudioCtx.specId = specId;
            return -3;
        } else {
            osRecvMesg(gAudioCtx.audioResetQueueP, &msg, OS_MESG_BLOCK);
        }
    }

    AudioThread_WaitForAudioResetQueueP();
    AUDIOCMD_GLOBAL_RESET_AUDIO_HEAP(specId);

    return AudioThread_ScheduleProcessCmds();
}

void AudioThread_PreNMIInternal(void) {
    gAudioCtx.resetTimer = 1;
    if (gAudioCtxInitalized) {
        AudioThread_ResetAudioHeap(0);
        gAudioCtx.resetStatus = 0;
    }
}

// Unused
s8 AudioThread_GetChannelIO(s32 seqPlayerIndex, s32 channelIndex, s32 ioPort) {
    SequencePlayer* seqPlayer = &gAudioCtx.seqPlayers[seqPlayerIndex];
    SequenceChannel* channel;

    if (seqPlayer->enabled) {
        channel = seqPlayer->channels[channelIndex];
        return channel->seqScriptIO[ioPort];
    } else {
        return SEQ_IO_VAL_NONE;
    }
}

// Unused
s8 AudioThread_GetSeqPlayerIO(s32 seqPlayerIndex, s32 ioPort) {
    return gAudioCtx.seqPlayers[seqPlayerIndex].seqScriptIO[ioPort];
}

// Unused
void AudioThread_InitExternalPool(void* addr, size_t size) {
    AudioHeap_InitPool(&gAudioCtx.externalPool, addr, size);
}

// Unused
void AudioThread_ResetExternalPool(void) {
    gAudioCtx.externalPool.startAddr = NULL;
}

void AudioThread_ProcessSeqPlayerCmd(SequencePlayer* seqPlayer, AudioCmd* cmd) {
    f32 fadeVolume;

    switch (cmd->op) {
        case AUDIOCMD_OP_SEQPLAYER_FADE_VOLUME_SCALE:
            if (seqPlayer->fadeVolumeScale != cmd->asFloat) {
                seqPlayer->fadeVolumeScale = cmd->asFloat;
                seqPlayer->recalculateVolume = true;
            }
            break;

        case AUDIOCMD_OP_SEQPLAYER_SET_TEMPO:
            seqPlayer->tempo = cmd->asInt * TATUMS_PER_BEAT;
            break;

        case AUDIOCMD_OP_SEQPLAYER_CHANGE_TEMPO:
            seqPlayer->tempoChange = cmd->asInt * TATUMS_PER_BEAT;
            break;

        case AUDIOCMD_OP_SEQPLAYER_CHANGE_TEMPO_TICKS:
            seqPlayer->tempoChange = cmd->asInt;
            break;

        case AUDIOCMD_OP_SEQPLAYER_SET_TRANSPOSITION:
            seqPlayer->transposition = cmd->asSbyte;
            break;

        case AUDIOCMD_OP_SEQPLAYER_SET_IO:
            seqPlayer->seqScriptIO[cmd->arg2] = cmd->asSbyte;
            break;

        case AUDIOCMD_OP_SEQPLAYER_FADE_TO_SET_VOLUME:
            fadeVolume = (s32)cmd->arg1 / 127.0f;
            goto apply_fade;

        case AUDIOCMD_OP_SEQPLAYER_FADE_TO_SCALED_VOLUME:
            fadeVolume = ((s32)cmd->arg1 / 100.0f) * seqPlayer->fadeVolume;
        apply_fade:
            if (seqPlayer->state != SEQPLAYER_STATE_FADE_OUT) {
                seqPlayer->volume = seqPlayer->fadeVolume;
                if (cmd->asInt == 0) {
                    seqPlayer->fadeVolume = fadeVolume;
                } else {
                    s32 fadeTimer = cmd->asInt;

                    seqPlayer->state = SEQPLAYER_STATE_0;
                    seqPlayer->fadeTimer = fadeTimer;
                    seqPlayer->fadeVelocity = (fadeVolume - seqPlayer->fadeVolume) / fadeTimer;
                }
            }
            break;

        case AUDIOCMD_OP_SEQPLAYER_RESET_VOLUME:
            if (seqPlayer->state != SEQPLAYER_STATE_FADE_OUT) {
                if (cmd->asInt == 0) {
                    seqPlayer->fadeVolume = seqPlayer->volume;
                } else {
                    s32 fadeTimer = cmd->asInt;

                    seqPlayer->state = SEQPLAYER_STATE_0;
                    seqPlayer->fadeTimer = fadeTimer;
                    seqPlayer->fadeVelocity = (seqPlayer->volume - seqPlayer->fadeVolume) / fadeTimer;
                }
            }
            break;

        case AUDIOCMD_OP_SEQPLAYER_SET_BEND:
            seqPlayer->bend = cmd->asFloat;
            if (seqPlayer->bend == 1.0f) {
                seqPlayer->applyBend = false;
            } else {
                seqPlayer->applyBend = true;
            }
            break;

        default:
            break;
    }
}

void AudioThread_ProcessChannelCmd(SequenceChannel* channel, AudioCmd* cmd) {
    u8 filterCutoff;

    switch (cmd->op) {
        case AUDIOCMD_OP_CHANNEL_SET_VOL_SCALE:
            if (channel->volumeScale != cmd->asFloat) {
                channel->volumeScale = cmd->asFloat;
                channel->changes.s.volume = true;
            }
            break;

        case AUDIOCMD_OP_CHANNEL_SET_VOL:
            if (channel->volume != cmd->asFloat) {
                channel->volume = cmd->asFloat;
                channel->changes.s.volume = true;
            }
            break;

        case AUDIOCMD_OP_CHANNEL_SET_PAN:
            if (channel->newPan != cmd->asSbyte) {
                channel->newPan = cmd->asSbyte;
                channel->changes.s.pan = true;
            }
            break;

        case AUDIOCMD_OP_CHANNEL_SET_PAN_WEIGHT:
            if (channel->newPan != cmd->asSbyte) {
                channel->panChannelWeight = cmd->asSbyte;
                channel->changes.s.pan = true;
            }
            break;

        case AUDIOCMD_OP_CHANNEL_SET_FREQ_SCALE:
            if (channel->freqScale != cmd->asFloat) {
                channel->freqScale = cmd->asFloat;
                channel->changes.s.freqScale = true;
            }
            break;

        case AUDIOCMD_OP_CHANNEL_SET_REVERB_VOLUME:
            if (channel->targetReverbVol != cmd->asSbyte) {
                channel->targetReverbVol = cmd->asSbyte;
            }
            break;

        case AUDIOCMD_OP_CHANNEL_SET_REVERB_INDEX:
            if (channel->reverbIndex != cmd->asSbyte) {
                channel->reverbIndex = cmd->asSbyte;
            }
            break;

        case AUDIOCMD_OP_CHANNEL_SET_SURROUND_EFFECT_INDEX:
            channel->surroundEffectIndex = cmd->asSbyte;
            break;

        case AUDIOCMD_OP_CHANNEL_SET_IO:
            if (cmd->arg2 < ARRAY_COUNT(channel->seqScriptIO)) {
                channel->seqScriptIO[cmd->arg2] = cmd->asSbyte;
            }
            break;

        case AUDIOCMD_OP_CHANNEL_SET_MUTE:
            channel->muted = cmd->asSbyte;
            break;

        case AUDIOCMD_OP_CHANNEL_SET_MUTE_FLAGS:
            channel->muteFlags = cmd->asSbyte;
            break;

        case AUDIOCMD_OP_CHANNEL_SET_VIBRATO_DEPTH:
            channel->vibrato.vibratoDepthTarget = cmd->asUbyte * 8;
            channel->vibrato.vibratoDepthChangeDelay = 1;
            break;

        case AUDIOCMD_OP_CHANNEL_SET_VIBRATO_RATE:
            channel->vibrato.vibratoRateTarget = cmd->asUbyte * 32;
            channel->vibrato.vibratoRateChangeDelay = 1;
            break;

        case AUDIOCMD_OP_CHANNEL_SET_COMB_FILTER_SIZE:
            channel->combFilterSize = cmd->asUbyte;
            break;

        case AUDIOCMD_OP_CHANNEL_SET_COMB_FILTER_GAIN:
            channel->combFilterGain = cmd->asUShort;
            break;

        case AUDIOCMD_OP_CHANNEL_SET_STEREO:
            channel->stereoData.asByte = cmd->asUbyte;
            break;

        case AUDIOCMD_OP_CHANNEL_SET_SET_START_POS:
            channel->startSamplePos = cmd->asInt;
            break;

        case AUDIOCMD_OP_CHANNEL_SET_SFX_STATE:
            channel->sfxState = cmd->asPtr;
            break;

        case AUDIOCMD_OP_CHANNEL_SET_FILTER:
            filterCutoff = cmd->arg2;
            if (cmd->asPtr != NULL) {
                channel->filter = cmd->asPtr;
            }
            if (channel->filter != NULL) {
                AudioHeap_LoadFilter(channel->filter, filterCutoff >> 4, filterCutoff & 0xF);
            }
            break;

        case AUDIOCMD_OP_CHANNEL_SET_GAIN:
            channel->gain = cmd->asUbyte;
            break;

        default:
            break;
    }
}

/**
 * Call an audio-thread command that has no code to process it. Unused.
 */
void AudioThread_Noop1Cmd(s32 arg0, s32 arg1, s32 arg2) {
    AUDIOCMD_GLOBAL_NOOP_1(arg0, arg1, arg2, 1);
}

/**
 * Call an audio-thread command that has no code to process it. Unused.
 */
void AudioThread_Noop1CmdZeroed(void) {
    AUDIOCMD_GLOBAL_NOOP_1(0, 0, 0, 0);
}

/**
 * Call an audio-thread command that has no code to process it. Unused.
 */
void AudioThread_Noop2Cmd(u32 arg0, s32 arg1) {
    AUDIOCMD_GLOBAL_NOOP_2(0, 0, arg1, arg0);
}

// Unused
void AudioThread_WaitForAudioTask(void) {
    osRecvMesg(gAudioCtx.taskStartQueueP, NULL, OS_MESG_NOBLOCK);
    osRecvMesg(gAudioCtx.taskStartQueueP, NULL, OS_MESG_BLOCK);
}

/**
 * Get the number of s16-samples from the start of the sample to the current sample position.
 * Unused
 */
s32 AudioThread_GetSamplePosFromStart(s32 seqPlayerIndex, s32 channelIndex, s32 layerIndex) {
    s32 pad;
    s32 loopEnd;
    s32 samplePosInt;

    if (!AudioThread_GetSamplePos(seqPlayerIndex, channelIndex, layerIndex, &loopEnd, &samplePosInt)) {
        return 0;
    }
    return samplePosInt;
}

/**
 * Get the number of s16-samples from the current sample position to the end of the sample.
 * Unused
 */
s32 AudioThread_GetSamplePosUntilEnd(s32 seqPlayerIndex, s32 channelIndex, s32 layerIndex) {
    s32 pad;
    s32 loopEnd;
    s32 samplePosInt;

    if (!AudioThread_GetSamplePos(seqPlayerIndex, channelIndex, layerIndex, &loopEnd, &samplePosInt)) {
        return 0;
    }
    return loopEnd - samplePosInt;
}

// Only used in unused functions
s32 AudioThread_GetSamplePos(s32 seqPlayerIndex, s32 channelIndex, s32 layerIndex, s32* loopEnd, s32* samplePosInt) {
    SequencePlayer* seqPlayer = &gAudioCtx.seqPlayers[seqPlayerIndex];
    SequenceLayer* layer;
    Note* note;
    TunedSample* tunedSample;

    if (seqPlayer->enabled && seqPlayer->channels[channelIndex]->enabled) {
        layer = seqPlayer->channels[channelIndex]->layers[layerIndex];
        if (layer == NULL) {
            return false;
        }

        if (layer->enabled) {
            if (layer->note == NULL) {
                return false;
            }

            if (!layer->bit3) {
                return false;
            }

            note = layer->note;
            if (layer == note->playbackState.parentLayer) {

                if (note->sampleState.bitField1.isSyntheticWave == true) {
                    return false;
                }

                tunedSample = note->sampleState.tunedSample;
                if (tunedSample == NULL) {
                    return false;
                }
                *loopEnd = tunedSample->sample->loop->loopEnd;
                *samplePosInt = note->synthesisState.samplePosInt;
                return true;
            }
            return false;
        }
    }
    return false;
}

s32 AudioThread_GetEnabledNotesCount(void) {
    return AudioThread_CountAndReleaseNotes(0);
}

s32 AudioThread_GetEnabledSampledNotesCount(void) {
    return AudioThread_CountAndReleaseNotes(AUDIO_NOTE_SAMPLE_NOTES);
}

/**
 * @param flags 0: count notes. 1: release all notes. 2: count sample notes 3: release sample notes
 * @return s32 number of notes
 */
s32 AudioThread_CountAndReleaseNotes(s32 flags) {
    s32 noteCount;
    NotePlaybackState* playbackState;
    NoteSampleState* noteSampleState;
    s32 i;
    Note* note;
    TunedSample* tunedSample;

    noteCount = 0;
    for (i = 0; i < gAudioCtx.numNotes; i++) {
        note = &gAudioCtx.notes[i];
        playbackState = &note->playbackState;
        if (note->sampleState.bitField0.enabled) {
            noteSampleState = &note->sampleState;
            if (playbackState->adsr.action.s.status != ADSR_STATUS_DISABLED) {
                if (flags >= AUDIO_NOTE_SAMPLE_NOTES) {
                    tunedSample = noteSampleState->tunedSample;
                    if ((tunedSample == NULL) || noteSampleState->bitField1.isSyntheticWave) {
                        continue;
                    }
                    if (tunedSample->sample->medium == MEDIUM_RAM) {
                        continue;
                    }
                }

                noteCount++;
                if ((flags & AUDIO_NOTE_RELEASE) == AUDIO_NOTE_RELEASE) {
                    playbackState->adsr.fadeOutVel = gAudioCtx.audioBufferParameters.updatesPerFrameInv;
                    playbackState->adsr.action.s.release = true;
                }
            }
        }
    }
    return noteCount;
}

u32 AudioThread_NextRandom(void) {
    static u32 sAudioRandom = 0x12345678;
    static u32 sAudioOsCount = 0x11111111;
    u32 count = osGetCount();

    sAudioRandom = (gAudioCtx.totalTaskCount + sAudioRandom + count) * (gAudioCtx.audioRandom + 0x1234567);
    sAudioRandom = (sAudioRandom & 1) + (sAudioRandom * 2) + sAudioOsCount;
    sAudioOsCount = count;

    return sAudioRandom;
}

void AudioThread_InitMesgQueues(void) {
    AudioThread_InitMesgQueuesInternal();
}
