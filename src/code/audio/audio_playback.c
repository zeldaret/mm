#include "global.h"

void AudioPlayback_NoteSetResamplingRate(NoteSubEu* noteSubEu, f32 resamplingRateInput);
void AudioPlayback_AudioListPushFront(AudioListItem* list, AudioListItem* item);
void AudioPlayback_NoteInitForLayer(Note* note, SequenceLayer* layer);

void AudioPlayback_InitNoteSub(Note* note, NoteSubEu* noteSubEu, NoteSubAttributes* subAttrs) {
    f32 volLeft;
    f32 volRight;
    s32 halfPanIndex;
    u64 pad;
    u8 strongLeft;
    u8 strongRight;
    f32 vel;
    u8 pan;
    u8 reverbVol;
    StereoData stereoData;
    s32 stereoHeadsetEffects = note->playbackState.stereoHeadsetEffects;

    vel = subAttrs->velocity;
    pan = subAttrs->pan;
    reverbVol = subAttrs->reverbVol;
    stereoData = subAttrs->stereo.s;

    noteSubEu->bitField0 = note->noteSubEu.bitField0;
    noteSubEu->bitField1 = note->noteSubEu.bitField1;
    noteSubEu->waveSampleAddr = note->noteSubEu.waveSampleAddr;
    noteSubEu->harmonicIndexCurAndPrev = note->noteSubEu.harmonicIndexCurAndPrev;

    AudioPlayback_NoteSetResamplingRate(noteSubEu, subAttrs->frequency);

    pan &= 0x7F;

    noteSubEu->bitField0.stereoStrongRight = false;
    noteSubEu->bitField0.stereoStrongLeft = false;
    noteSubEu->bitField0.stereoHeadsetEffects = stereoData.stereoHeadsetEffects;
    noteSubEu->bitField0.usesHeadsetPanEffects = stereoData.usesHeadsetPanEffects;
    if (stereoHeadsetEffects && (gAudioContext.soundMode == SOUNDMODE_HEADSET)) {
        halfPanIndex = pan >> 1;
        if (halfPanIndex > 0x3F) {
            halfPanIndex = 0x3F;
        }

        noteSubEu->headsetPanLeft = gHeadsetPanQuantization[halfPanIndex];
        noteSubEu->headsetPanRight = gHeadsetPanQuantization[0x3F - halfPanIndex];
        noteSubEu->bitField1.usesHeadsetPanEffects2 = true;

        volLeft = gHeadsetPanVolume[pan];
        volRight = gHeadsetPanVolume[0x7F - pan];
    } else if (stereoHeadsetEffects && (gAudioContext.soundMode == SOUNDMODE_STEREO)) {
        strongLeft = strongRight = false;
        noteSubEu->headsetPanRight = 0;
        noteSubEu->headsetPanLeft = 0;
        noteSubEu->bitField1.usesHeadsetPanEffects2 = false;

        volLeft = gStereoPanVolume[pan];
        volRight = gStereoPanVolume[0x7F - pan];
        if (pan < 0x20) {
            strongLeft = true;
        } else if (pan > 0x60) {
            strongRight = true;
        }

        // case 0:
        noteSubEu->bitField0.stereoStrongRight = strongRight;
        noteSubEu->bitField0.stereoStrongLeft = strongLeft;

        switch (stereoData.bit2) {
            case 0:
                break;

            case 1:
                noteSubEu->bitField0.stereoStrongRight = stereoData.strongRight;
                noteSubEu->bitField0.stereoStrongLeft = stereoData.strongLeft;
                break;

            case 2:
                noteSubEu->bitField0.stereoStrongRight = stereoData.strongRight | strongRight;
                noteSubEu->bitField0.stereoStrongLeft = stereoData.strongLeft | strongLeft;
                break;

            case 3:
                noteSubEu->bitField0.stereoStrongRight = stereoData.strongRight ^ strongRight;
                noteSubEu->bitField0.stereoStrongLeft = stereoData.strongLeft ^ strongLeft;
                break;
        }

    } else if (gAudioContext.soundMode == SOUNDMODE_MONO) {
        noteSubEu->bitField0.stereoHeadsetEffects = false;
        noteSubEu->bitField0.usesHeadsetPanEffects = false;
        volLeft = 0.707f; // approx 1/sqrt(2)
        volRight = 0.707f;
    } else {
        noteSubEu->bitField0.stereoStrongRight = stereoData.strongRight;
        noteSubEu->bitField0.stereoStrongLeft = stereoData.strongLeft;
        volLeft = gDefaultPanVolume[pan];
        volRight = gDefaultPanVolume[0x7F - pan];
    }

    vel = 0.0f > vel ? 0.0f : vel;
    vel = 1.0f < vel ? 1.0f : vel;

    noteSubEu->targetVolLeft = (s32)((vel * volLeft) * (0x1000 - 0.001f));
    noteSubEu->targetVolRight = (s32)((vel * volRight) * (0x1000 - 0.001f));

    noteSubEu->gain = subAttrs->gain;
    noteSubEu->filter = subAttrs->filter;
    noteSubEu->unk_07 = subAttrs->unk_14;
    noteSubEu->unk_0E = subAttrs->unk_16;
    noteSubEu->reverbVol = reverbVol;
    noteSubEu->unk_19 = subAttrs->unk_3;
}

void AudioPlayback_NoteSetResamplingRate(NoteSubEu* noteSubEu, f32 resamplingRateInput) {
    f32 resamplingRate = 0.0f;

    if (resamplingRateInput < 2.0f) {
        noteSubEu->bitField1.hasTwoParts = false;
        resamplingRate = CLAMP_MAX(resamplingRateInput, 1.99998f);

    } else {
        noteSubEu->bitField1.hasTwoParts = true;
        if (resamplingRateInput > 3.99996f) {
            resamplingRate = 1.99998f;
        } else {
            resamplingRate = resamplingRateInput * 0.5f;
        }
    }
    noteSubEu->resamplingRateFixedPoint = (s32)(resamplingRate * 32768.0f);
}

void AudioPlayback_NoteInit(Note* note) {
    if (note->playbackState.parentLayer->adsr.decayIndex == 0) {
        AudioEffects_AdsrInit(&note->playbackState.adsr, note->playbackState.parentLayer->channel->adsr.envelope,
                              &note->playbackState.adsrVolScaleUnused);
    } else {
        AudioEffects_AdsrInit(&note->playbackState.adsr, note->playbackState.parentLayer->adsr.envelope,
                              &note->playbackState.adsrVolScaleUnused);
    }

    note->playbackState.status = PLAYBACK_STATUS_0;
    note->playbackState.adsr.action.s.state = ADSR_STATE_INITIAL;
    note->noteSubEu = gDefaultNoteSub;
}

void AudioPlayback_NoteDisable(Note* note) {
    if (note->noteSubEu.bitField0.needsInit == true) {
        note->noteSubEu.bitField0.needsInit = false;
    }
    note->playbackState.priority = 0;
    note->noteSubEu.bitField0.enabled = false;
    note->playbackState.status = PLAYBACK_STATUS_0;
    note->noteSubEu.bitField0.finished = false;
    note->playbackState.parentLayer = NO_LAYER;
    note->playbackState.prevParentLayer = NO_LAYER;
    note->playbackState.adsr.action.s.state = ADSR_STATE_DISABLED;
    note->playbackState.adsr.current = 0;
}

void AudioPlayback_ProcessNotes(void) {
    s32 pad;
    s32 playbackStatus;
    NoteAttributes* attrs;
    NoteSubEu* noteSubEu2;
    NoteSubEu* noteSubEu;
    Note* note;
    NotePlaybackState* playbackState;
    NoteSubAttributes subAttrs;
    u8 bookOffset;
    f32 scale;
    s32 i;

    for (i = 0; i < gAudioContext.numNotes; i++) {
        note = &gAudioContext.notes[i];
        noteSubEu2 = &gAudioContext.noteSubsEu[gAudioContext.noteSubEuOffset + i];
        playbackState = &note->playbackState;
        if (playbackState->parentLayer != NO_LAYER) {
            if ((u32)playbackState->parentLayer < 0x7FFFFFFF) {
                continue;
            }

            if ((note != playbackState->parentLayer->note) && (playbackState->status == PLAYBACK_STATUS_0)) {
                playbackState->adsr.action.s.release = true;
                playbackState->adsr.fadeOutVel = gAudioContext.audioBufferParameters.updatesPerFrameInv;
                playbackState->priority = 1;
                playbackState->status = PLAYBACK_STATUS_2;
                goto out;
            } else if (!playbackState->parentLayer->enabled && (playbackState->status == PLAYBACK_STATUS_0) &&
                       (playbackState->priority >= 1)) {
                // do nothing
            } else if (playbackState->parentLayer->channel->seqPlayer == NULL) {
                AudioSeq_SequenceChannelDisable(playbackState->parentLayer->channel);
                playbackState->priority = 1;
                playbackState->status = PLAYBACK_STATUS_1;
                continue;
            } else if (playbackState->parentLayer->channel->seqPlayer->muted &&
                       (playbackState->parentLayer->channel->muteFlags & MUTE_FLAGS_STOP_NOTES)) {
                // do nothing
            } else {
                goto out;
            }

            AudioPlayback_SeqLayerNoteRelease(playbackState->parentLayer);
            AudioPlayback_AudioListRemove(&note->listItem);
            AudioPlayback_AudioListPushFront(&note->listItem.pool->decaying, &note->listItem);
            playbackState->priority = 1;
            playbackState->status = PLAYBACK_STATUS_2;
        } else if ((playbackState->status == PLAYBACK_STATUS_0) && (playbackState->priority >= 1)) {
            continue;
        }

    out:
        if (playbackState->priority != 0) {
            if (1) {}
            noteSubEu = &note->noteSubEu;
            if ((playbackState->status >= 1) || noteSubEu->bitField0.finished) {
                if ((playbackState->adsr.action.s.state == ADSR_STATE_DISABLED) || noteSubEu->bitField0.finished) {
                    if (playbackState->wantedParentLayer != NO_LAYER) {
                        AudioPlayback_NoteDisable(note);
                        if (playbackState->wantedParentLayer->channel != NULL) {
                            AudioPlayback_NoteInitForLayer(note, playbackState->wantedParentLayer);
                            AudioEffects_NoteVibratoInit(note);
                            AudioEffects_NotePortamentoInit(note);
                            AudioPlayback_AudioListRemove(&note->listItem);
                            AudioSeq_AudioListPushBack(&note->listItem.pool->active, &note->listItem);
                            playbackState->wantedParentLayer = NO_LAYER;
                            // don't skip
                        } else {
                            AudioPlayback_NoteDisable(note);
                            AudioPlayback_AudioListRemove(&note->listItem);
                            AudioSeq_AudioListPushBack(&note->listItem.pool->disabled, &note->listItem);
                            playbackState->wantedParentLayer = NO_LAYER;
                            goto skip;
                        }
                    } else {
                        if (playbackState->parentLayer != NO_LAYER) {
                            playbackState->parentLayer->bit1 = true;
                        }
                        AudioPlayback_NoteDisable(note);
                        AudioPlayback_AudioListRemove(&note->listItem);
                        AudioSeq_AudioListPushBack(&note->listItem.pool->disabled, &note->listItem);
                        continue;
                    }
                }
            } else if (playbackState->adsr.action.s.state == ADSR_STATE_DISABLED) {
                if (playbackState->parentLayer != NO_LAYER) {
                    playbackState->parentLayer->bit1 = true;
                }
                AudioPlayback_NoteDisable(note);
                AudioPlayback_AudioListRemove(&note->listItem);
                AudioSeq_AudioListPushBack(&note->listItem.pool->disabled, &note->listItem);
                continue;
            }

            scale = AudioEffects_AdsrUpdate(&playbackState->adsr);
            AudioEffects_NoteVibratoUpdate(note);
            playbackStatus = playbackState->status;
            attrs = &playbackState->attributes;
            if ((playbackStatus == PLAYBACK_STATUS_1) || (playbackStatus == PLAYBACK_STATUS_2)) {
                subAttrs.frequency = attrs->freqScale;
                subAttrs.velocity = attrs->velocity;
                subAttrs.pan = attrs->pan;
                subAttrs.reverbVol = attrs->reverb;
                subAttrs.stereo = attrs->stereo;
                subAttrs.gain = attrs->gain;
                subAttrs.filter = attrs->filter;
                subAttrs.unk_14 = attrs->unk_4;
                subAttrs.unk_16 = attrs->unk_6;
                subAttrs.unk_3 = attrs->unk_3;
                bookOffset = noteSubEu->bitField1.bookOffset;
            } else {
                SequenceLayer* layer = playbackState->parentLayer;
                SequenceChannel* channel = playbackState->parentLayer->channel;

                subAttrs.frequency = layer->noteFreqScale;
                subAttrs.velocity = layer->noteVelocity;
                subAttrs.pan = layer->notePan;

                if (layer->unk_08 == 0x80) {
                    subAttrs.unk_3 = channel->unk_10;
                } else {
                    subAttrs.unk_3 = layer->unk_08;
                }

                if (layer->stereo.s.bit2 == 0) {
                    subAttrs.stereo = channel->stereo;
                } else {
                    subAttrs.stereo = layer->stereo;
                }

                if (layer->unk_0A.s.bit_2 == 1) {
                    subAttrs.reverbVol = channel->reverb;
                } else {
                    subAttrs.reverbVol = layer->unk_09;
                }

                if (layer->unk_0A.s.bit_9 == 1) {
                    subAttrs.gain = channel->gain;
                } else {
                    subAttrs.gain = 0;
                    if (1) {}
                }

                subAttrs.filter = channel->filter;
                subAttrs.unk_14 = channel->unk_0F;
                subAttrs.unk_16 = channel->unk_20;
                bookOffset = channel->bookOffset & 0x7;

                if (channel->seqPlayer->muted && (channel->muteFlags & MUTE_FLAGS_3)) {
                    subAttrs.frequency = 0.0f;
                    subAttrs.velocity = 0.0f;
                }
            }

            subAttrs.frequency *= playbackState->vibratoFreqScale * playbackState->portamentoFreqScale;
            subAttrs.frequency *= gAudioContext.audioBufferParameters.resampleRate;
            subAttrs.velocity *= scale;
            AudioPlayback_InitNoteSub(note, noteSubEu2, &subAttrs);
            noteSubEu->bitField1.bookOffset = bookOffset;
        skip:;
        }
    }
}

TunedSample* AudioPlayback_GetInstrumentTunedSample(Instrument* instrument, s32 semitone) {
    TunedSample* tunedSample;

    if (semitone < instrument->normalRangeLo) {
        tunedSample = &instrument->lowPitchTunedSample;
    } else if (semitone <= instrument->normalRangeHi) {
        tunedSample = &instrument->normalPitchTunedSample;
    } else {
        tunedSample = &instrument->highPitchTunedSample;
    }

    return tunedSample;
}

Instrument* AudioPlayback_GetInstrumentInner(s32 fontId, s32 instId) {
    Instrument* inst;

    if (fontId == 0xFF) {
        return NULL;
    }

    if (!AudioLoad_IsFontLoadComplete(fontId)) {
        gAudioContext.audioErrorFlags = AUDIO_ERROR(0, fontId, AUDIO_ERROR_FONT_NOT_LOADED);
        return NULL;
    }

    if (instId >= gAudioContext.soundFontList[fontId].numInstruments) {
        gAudioContext.audioErrorFlags = AUDIO_ERROR(fontId, instId, AUDIO_ERROR_INVALID_INST_ID);
        return NULL;
    }

    inst = gAudioContext.soundFontList[fontId].instruments[instId];
    if (inst == NULL) {
        gAudioContext.audioErrorFlags = AUDIO_ERROR(fontId, instId, AUDIO_ERROR_NO_INST);
        return inst;
    }

    return inst;
}

Drum* AudioPlayback_GetDrum(s32 fontId, s32 drumId) {
    Drum* drum;

    if (fontId == 0xFF) {
        return NULL;
    }

    if (!AudioLoad_IsFontLoadComplete(fontId)) {
        gAudioContext.audioErrorFlags = AUDIO_ERROR(0, fontId, AUDIO_ERROR_FONT_NOT_LOADED);
        return NULL;
    }

    if (drumId >= gAudioContext.soundFontList[fontId].numDrums) {
        gAudioContext.audioErrorFlags = AUDIO_ERROR(fontId, drumId, AUDIO_ERROR_INVALID_DRUM_SFX_ID);
        return NULL;
    }
    if ((u32)gAudioContext.soundFontList[fontId].drums < AUDIO_RELOCATED_ADDRESS_START) {
        return NULL;
    }
    drum = gAudioContext.soundFontList[fontId].drums[drumId];

    if (drum == NULL) {
        gAudioContext.audioErrorFlags = AUDIO_ERROR(fontId, drumId, AUDIO_ERROR_NO_DRUM_SFX);
    }

    return drum;
}

SoundEffect* AudioPlayback_GetSoundEffect(s32 fontId, s32 sfxId) {
    SoundEffect* soundEffect;

    if (fontId == 0xFF) {
        return NULL;
    }

    if (!AudioLoad_IsFontLoadComplete(fontId)) {
        gAudioContext.audioErrorFlags = AUDIO_ERROR(0, fontId, AUDIO_ERROR_FONT_NOT_LOADED);
        return NULL;
    }

    if (sfxId >= gAudioContext.soundFontList[fontId].numSfx) {
        gAudioContext.audioErrorFlags = AUDIO_ERROR(fontId, sfxId, AUDIO_ERROR_INVALID_DRUM_SFX_ID);
        return NULL;
    }

    if ((u32)gAudioContext.soundFontList[fontId].soundEffects < AUDIO_RELOCATED_ADDRESS_START) {
        return NULL;
    }

    soundEffect = &gAudioContext.soundFontList[fontId].soundEffects[sfxId];

    if (soundEffect == NULL) {
        gAudioContext.audioErrorFlags = AUDIO_ERROR(fontId, sfxId, AUDIO_ERROR_NO_DRUM_SFX);
    }

    if (soundEffect->tunedSample.sample == NULL) {
        return NULL;
    }

    return soundEffect;
}

s32 AudioPlayback_SetFontInstrument(s32 instrumentType, s32 fontId, s32 index, void* value) {
    if (fontId == 0xFF) {
        return -1;
    }

    if (!AudioLoad_IsFontLoadComplete(fontId)) {
        return -2;
    }

    switch (instrumentType) {
        case 0:
            if (index >= gAudioContext.soundFontList[fontId].numDrums) {
                return -3;
            }
            gAudioContext.soundFontList[fontId].drums[index] = value;
            break;

        case 1:
            if (index >= gAudioContext.soundFontList[fontId].numSfx) {
                return -3;
            }
            gAudioContext.soundFontList[fontId].soundEffects[index] = *(SoundEffect*)value;
            break;

        default:
            if (index >= gAudioContext.soundFontList[fontId].numInstruments) {
                return -3;
            }
            gAudioContext.soundFontList[fontId].instruments[index] = value;
            break;
    }

    return 0;
}

void AudioPlayback_SeqLayerDecayRelease(SequenceLayer* layer, s32 target) {
    Note* note;
    NoteAttributes* attrs;
    SequenceChannel* channel;
    s32 i;

    if (layer == NO_LAYER) {
        return;
    }

    layer->bit3 = false;

    if (layer->note == NULL) {
        return;
    }

    note = layer->note;
    attrs = &note->playbackState.attributes;

    if (note->playbackState.wantedParentLayer == layer) {
        note->playbackState.wantedParentLayer = NO_LAYER;
    }

    if (note->playbackState.parentLayer != layer) {
        if (note->playbackState.parentLayer == NO_LAYER && note->playbackState.wantedParentLayer == NO_LAYER &&
            note->playbackState.prevParentLayer == layer && target != ADSR_STATE_DECAY) {
            note->playbackState.adsr.fadeOutVel = gAudioContext.audioBufferParameters.updatesPerFrameInv;
            note->playbackState.adsr.action.s.release = true;
        }
        return;
    }

    if (note->playbackState.adsr.action.s.state != ADSR_STATE_DECAY) {
        attrs->freqScale = layer->noteFreqScale;
        attrs->velocity = layer->noteVelocity;
        attrs->pan = layer->notePan;

        if (layer->channel != NULL) {
            channel = layer->channel;

            if (layer->unk_0A.s.bit_2 == 1) {
                attrs->reverb = channel->reverb;
            } else {
                attrs->reverb = layer->unk_09;
            }

            if (layer->unk_08 == 0x80) {
                attrs->unk_3 = channel->unk_10;
            } else {
                attrs->unk_3 = layer->unk_08;
            }

            if (layer->unk_0A.s.bit_9 == 1) {
                attrs->gain = channel->gain;
            } else {
                attrs->gain = 0;
            }

            attrs->filter = channel->filter;

            if (attrs->filter != NULL) {
                for (i = 0; i < 8; i++) {
                    attrs->filterBuf[i] = attrs->filter[i];
                }
                attrs->filter = attrs->filterBuf;
            }

            attrs->unk_6 = channel->unk_20;
            attrs->unk_4 = channel->unk_0F;
            if (channel->seqPlayer->muted && (channel->muteFlags & MUTE_FLAGS_3)) {
                note->noteSubEu.bitField0.finished = true;
            }

            if (layer->stereo.asByte == 0) {
                attrs->stereo = channel->stereo;
            } else {
                attrs->stereo = layer->stereo;
            }
            note->playbackState.priority = channel->someOtherPriority;
        } else {
            attrs->stereo = layer->stereo;
            note->playbackState.priority = 1;
        }

        note->playbackState.prevParentLayer = note->playbackState.parentLayer;
        note->playbackState.parentLayer = NO_LAYER;
        if (target == ADSR_STATE_RELEASE) {
            note->playbackState.adsr.fadeOutVel = gAudioContext.audioBufferParameters.updatesPerFrameInv;
            note->playbackState.adsr.action.s.release = true;
            note->playbackState.status = PLAYBACK_STATUS_2;
        } else {
            note->playbackState.status = PLAYBACK_STATUS_1;
            note->playbackState.adsr.action.s.decay = true;
            if (layer->adsr.decayIndex == 0) {
                note->playbackState.adsr.fadeOutVel = gAudioContext.adsrDecayTable[layer->channel->adsr.decayIndex];
            } else {
                note->playbackState.adsr.fadeOutVel = gAudioContext.adsrDecayTable[layer->adsr.decayIndex];
            }
            note->playbackState.adsr.sustain =
                ((f32)(s32)(layer->channel->adsr.sustain) * note->playbackState.adsr.current) / 256.0f;
        }
    }

    if (target == ADSR_STATE_DECAY) {
        AudioPlayback_AudioListRemove(&note->listItem);
        AudioPlayback_AudioListPushFront(&note->listItem.pool->decaying, &note->listItem);
    }
}

void AudioPlayback_SeqLayerNoteDecay(SequenceLayer* layer) {
    AudioPlayback_SeqLayerDecayRelease(layer, ADSR_STATE_DECAY);
}

void AudioPlayback_SeqLayerNoteRelease(SequenceLayer* layer) {
    AudioPlayback_SeqLayerDecayRelease(layer, ADSR_STATE_RELEASE);
}

/**
 * Extract the synthetic wave to use from gWaveSamples and update corresponding frequencies
 *
 * @param note
 * @param layer
 * @param waveId the index of the type of synthetic wave to use, offset by 128
 * @return harmonicIndex, the index of the harmonic for the synthetic wave contained in gWaveSamples
 */
s32 AudioPlayback_BuildSyntheticWave(Note* note, SequenceLayer* layer, s32 waveId) {
    f32 freqScale;
    f32 freqRatio;
    u8 harmonicIndex;

    if (waveId < 128) {
        waveId = 128;
    }

    freqScale = layer->freqScale;
    if (layer->portamento.mode != 0 && 0.0f < layer->portamento.extent) {
        freqScale *= (layer->portamento.extent + 1.0f);
    }

    // Map frequency to the harmonic to use from gWaveSamples
    if (freqScale < 0.99999f) {
        harmonicIndex = 0;
        freqRatio = 1.0465f;
    } else if (freqScale < 1.99999f) {
        harmonicIndex = 1;
        freqRatio = 1.0465f / 2;
    } else if (freqScale < 3.99999f) {
        harmonicIndex = 2;
        freqRatio = 1.0465f / 4 + 1.005E-3;
    } else {
        harmonicIndex = 3;
        freqRatio = 1.0465f / 8 - 2.5E-6;
    }

    // Update results
    layer->freqScale *= freqRatio;
    note->playbackState.waveId = waveId;
    note->playbackState.harmonicIndex = harmonicIndex;

    // Save the pointer to the synthethic wave
    // waveId index starts at 128, there are WAVE_SAMPLE_COUNT samples to read from
    note->noteSubEu.waveSampleAddr = &gWaveSamples[waveId - 128][harmonicIndex * WAVE_SAMPLE_COUNT];

    return harmonicIndex;
}

void AudioPlayback_InitSyntheticWave(Note* note, SequenceLayer* layer) {
    s32 prevHarmonicIndex;
    s32 curHarmonicIndex;
    s32 waveId = layer->instOrWave;

    if (waveId == 0xFF) {
        waveId = layer->channel->instOrWave;
    }

    prevHarmonicIndex = note->playbackState.harmonicIndex;
    curHarmonicIndex = AudioPlayback_BuildSyntheticWave(note, layer, waveId);

    if (curHarmonicIndex != prevHarmonicIndex) {
        note->noteSubEu.harmonicIndexCurAndPrev = (curHarmonicIndex << 2) + prevHarmonicIndex;
    }
}

void AudioPlayback_InitNoteList(AudioListItem* list) {
    list->prev = list;
    list->next = list;
    list->u.count = 0;
}

void AudioPlayback_InitNoteLists(NotePool* pool) {
    AudioPlayback_InitNoteList(&pool->disabled);
    AudioPlayback_InitNoteList(&pool->decaying);
    AudioPlayback_InitNoteList(&pool->releasing);
    AudioPlayback_InitNoteList(&pool->active);
    pool->disabled.pool = pool;
    pool->decaying.pool = pool;
    pool->releasing.pool = pool;
    pool->active.pool = pool;
}

void AudioPlayback_InitNoteFreeList(void) {
    s32 i;

    AudioPlayback_InitNoteLists(&gAudioContext.noteFreeLists);
    for (i = 0; i < gAudioContext.numNotes; i++) {
        gAudioContext.notes[i].listItem.u.value = &gAudioContext.notes[i];
        gAudioContext.notes[i].listItem.prev = NULL;
        AudioSeq_AudioListPushBack(&gAudioContext.noteFreeLists.disabled, &gAudioContext.notes[i].listItem);
    }
}

void AudioPlayback_NotePoolClear(NotePool* pool) {
    s32 i;
    AudioListItem* source;
    AudioListItem* cur;
    AudioListItem* dest;

    for (i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                source = &pool->disabled;
                dest = &gAudioContext.noteFreeLists.disabled;
                break;

            case 1:
                source = &pool->decaying;
                dest = &gAudioContext.noteFreeLists.decaying;
                break;

            case 2:
                source = &pool->releasing;
                dest = &gAudioContext.noteFreeLists.releasing;
                break;

            case 3:
                source = &pool->active;
                dest = &gAudioContext.noteFreeLists.active;
                break;
        }

        for (;;) {
            cur = source->next;
            if (cur == source || cur == NULL) {
                break;
            }
            AudioPlayback_AudioListRemove(cur);
            AudioSeq_AudioListPushBack(dest, cur);
        }
    }
}

void AudioPlayback_NotePoolFill(NotePool* pool, s32 count) {
    s32 i;
    s32 j;
    Note* note;
    AudioListItem* source;
    AudioListItem* dest;

    AudioPlayback_NotePoolClear(pool);

    for (i = 0, j = 0; j < count; i++) {
        if (i == 4) {
            return;
        }

        switch (i) {
            case 0:
                source = &gAudioContext.noteFreeLists.disabled;
                dest = &pool->disabled;
                break;

            case 1:
                source = &gAudioContext.noteFreeLists.decaying;
                dest = &pool->decaying;
                break;

            case 2:
                source = &gAudioContext.noteFreeLists.releasing;
                dest = &pool->releasing;
                break;

            case 3:
                source = &gAudioContext.noteFreeLists.active;
                dest = &pool->active;
                break;
        }

        while (j < count) {
            note = AudioSeq_AudioListPopBack(source);
            if (note == NULL) {
                break;
            }
            AudioSeq_AudioListPushBack(dest, &note->listItem);
            j++;
        }
    }
}

void AudioPlayback_AudioListPushFront(AudioListItem* list, AudioListItem* item) {
    // add 'item' to the front of the list given by 'list', if it's not in any list
    if (item->prev == NULL) {
        item->prev = list;
        item->next = list->next;
        list->next->prev = item;
        list->next = item;
        list->u.count++;
        item->pool = list->pool;
    }
}

void AudioPlayback_AudioListRemove(AudioListItem* item) {
    // remove 'item' from the list it's in, if any
    if (item->prev != NULL) {
        item->prev->next = item->next;
        item->next->prev = item->prev;
        item->prev = NULL;
    }
}

Note* AudioPlayback_FindNodeWithPrioLessThan(AudioListItem* list, s32 limit) {
    AudioListItem* cur = list->next;
    AudioListItem* best;

    if (cur == list) {
        return NULL;
    }

    for (best = cur; cur != list; cur = cur->next) {
        if (((Note*)best->u.value)->playbackState.priority >= ((Note*)cur->u.value)->playbackState.priority) {
            best = cur;
        }
    }

    if (best == NULL) {
        return NULL;
    }

    if (limit <= ((Note*)best->u.value)->playbackState.priority) {
        return NULL;
    }

    return best->u.value;
}

void AudioPlayback_NoteInitForLayer(Note* note, SequenceLayer* layer) {
    s32 pad[3];
    s16 instId;
    SequenceChannel* channel = layer->channel;
    NotePlaybackState* playbackState = &note->playbackState;
    NoteSubEu* noteSubEu = &note->noteSubEu;

    playbackState->prevParentLayer = NO_LAYER;
    playbackState->parentLayer = layer;
    playbackState->priority = channel->notePriority;
    layer->notePropertiesNeedInit = true;
    layer->bit3 = true;
    layer->note = note;
    channel->noteUnused = note;
    channel->layerUnused = layer;
    layer->noteVelocity = 0.0f;
    AudioPlayback_NoteInit(note);
    instId = layer->instOrWave;

    if (instId == 0xFF) {
        instId = channel->instOrWave;
    }
    noteSubEu->tunedSample = layer->tunedSample;

    if (instId >= 0x80 && instId < 0xC0) {
        noteSubEu->bitField1.isSyntheticWave = true;
    } else {
        noteSubEu->bitField1.isSyntheticWave = false;
    }

    if (noteSubEu->bitField1.isSyntheticWave) {
        AudioPlayback_BuildSyntheticWave(note, layer, instId);
    } else if (channel->startSamplePos == 1) {
        playbackState->startSamplePos = noteSubEu->tunedSample->sample->loop->start;
    } else {
        playbackState->startSamplePos = channel->startSamplePos;
        if (playbackState->startSamplePos >= noteSubEu->tunedSample->sample->loop->end) {
            playbackState->startSamplePos = 0;
        }
    }

    playbackState->fontId = channel->fontId;
    playbackState->stereoHeadsetEffects = channel->stereoHeadsetEffects;
    noteSubEu->bitField1.reverbIndex = channel->reverbIndex & 3;
}

void func_801963E8(Note* note, SequenceLayer* layer) {
    // similar to Audio_NoteReleaseAndTakeOwnership, hard to say what the difference is
    AudioPlayback_SeqLayerNoteRelease(note->playbackState.parentLayer);
    note->playbackState.wantedParentLayer = layer;
}

void AudioPlayback_NoteReleaseAndTakeOwnership(Note* note, SequenceLayer* layer) {
    note->playbackState.wantedParentLayer = layer;
    note->playbackState.priority = layer->channel->notePriority;

    note->playbackState.adsr.fadeOutVel = gAudioContext.audioBufferParameters.updatesPerFrameInv;
    note->playbackState.adsr.action.s.release = true;
}

Note* AudioPlayback_AllocNoteFromDisabled(NotePool* pool, SequenceLayer* layer) {
    Note* note = AudioSeq_AudioListPopBack(&pool->disabled);
    if (note != NULL) {
        AudioPlayback_NoteInitForLayer(note, layer);
        AudioPlayback_AudioListPushFront(&pool->active, &note->listItem);
    }
    return note;
}

Note* AudioPlayback_AllocNoteFromDecaying(NotePool* pool, SequenceLayer* layer) {
    Note* note = AudioPlayback_FindNodeWithPrioLessThan(&pool->decaying, layer->channel->notePriority);

    if (note != NULL) {
        AudioPlayback_NoteReleaseAndTakeOwnership(note, layer);
        AudioPlayback_AudioListRemove(&note->listItem);
        AudioSeq_AudioListPushBack(&pool->releasing, &note->listItem);
    }
    return note;
}

Note* AudioPlayback_AllocNoteFromActive(NotePool* pool, SequenceLayer* layer) {
    Note* rNote;
    Note* aNote;
    s32 rPriority;
    s32 aPriority;

    rPriority = aPriority = 0x10;
    rNote = AudioPlayback_FindNodeWithPrioLessThan(&pool->releasing, layer->channel->notePriority);

    if (rNote != NULL) {
        rPriority = rNote->playbackState.priority;
    }

    aNote = AudioPlayback_FindNodeWithPrioLessThan(&pool->active, layer->channel->notePriority);

    if (aNote != NULL) {
        aPriority = aNote->playbackState.priority;
    }

    if (rNote == NULL && aNote == NULL) {
        return NULL;
    }

    if (aPriority < rPriority) {
        AudioPlayback_AudioListRemove(&aNote->listItem);
        func_801963E8(aNote, layer);
        AudioSeq_AudioListPushBack(&pool->releasing, &aNote->listItem);
        aNote->playbackState.priority = layer->channel->notePriority;
        return aNote;
    }
    rNote->playbackState.wantedParentLayer = layer;
    rNote->playbackState.priority = layer->channel->notePriority;
    return rNote;
}

Note* AudioPlayback_AllocNote(SequenceLayer* layer) {
    Note* note;
    u32 policy = layer->channel->noteAllocPolicy;

    if (policy & 1) {
        note = layer->note;
        if (note != NULL && note->playbackState.prevParentLayer == layer &&
            note->playbackState.wantedParentLayer == NO_LAYER) {
            AudioPlayback_NoteReleaseAndTakeOwnership(note, layer);
            AudioPlayback_AudioListRemove(&note->listItem);
            AudioSeq_AudioListPushBack(&note->listItem.pool->releasing, &note->listItem);
            return note;
        }
    }

    if (policy & 2) {
        if (!(note = AudioPlayback_AllocNoteFromDisabled(&layer->channel->notePool, layer)) &&
            !(note = AudioPlayback_AllocNoteFromDecaying(&layer->channel->notePool, layer)) &&
            !(note = AudioPlayback_AllocNoteFromActive(&layer->channel->notePool, layer))) {
            goto null_return;
        }
        return note;
    }

    if (policy & 4) {
        if (!(note = AudioPlayback_AllocNoteFromDisabled(&layer->channel->notePool, layer)) &&
            !(note = AudioPlayback_AllocNoteFromDisabled(&layer->channel->seqPlayer->notePool, layer)) &&
            !(note = AudioPlayback_AllocNoteFromDecaying(&layer->channel->notePool, layer)) &&
            !(note = AudioPlayback_AllocNoteFromDecaying(&layer->channel->seqPlayer->notePool, layer)) &&
            !(note = AudioPlayback_AllocNoteFromActive(&layer->channel->notePool, layer)) &&
            !(note = AudioPlayback_AllocNoteFromActive(&layer->channel->seqPlayer->notePool, layer))) {
            goto null_return;
        }
        return note;
    }

    if (policy & 8) {
        if (!(note = AudioPlayback_AllocNoteFromDisabled(&gAudioContext.noteFreeLists, layer)) &&
            !(note = AudioPlayback_AllocNoteFromDecaying(&gAudioContext.noteFreeLists, layer)) &&
            !(note = AudioPlayback_AllocNoteFromActive(&gAudioContext.noteFreeLists, layer))) {
            goto null_return;
        }
        return note;
    }

    if (!(note = AudioPlayback_AllocNoteFromDisabled(&layer->channel->notePool, layer)) &&
        !(note = AudioPlayback_AllocNoteFromDisabled(&layer->channel->seqPlayer->notePool, layer)) &&
        !(note = AudioPlayback_AllocNoteFromDisabled(&gAudioContext.noteFreeLists, layer)) &&
        !(note = AudioPlayback_AllocNoteFromDecaying(&layer->channel->notePool, layer)) &&
        !(note = AudioPlayback_AllocNoteFromDecaying(&layer->channel->seqPlayer->notePool, layer)) &&
        !(note = AudioPlayback_AllocNoteFromDecaying(&gAudioContext.noteFreeLists, layer)) &&
        !(note = AudioPlayback_AllocNoteFromActive(&layer->channel->notePool, layer)) &&
        !(note = AudioPlayback_AllocNoteFromActive(&layer->channel->seqPlayer->notePool, layer)) &&
        !(note = AudioPlayback_AllocNoteFromActive(&gAudioContext.noteFreeLists, layer))) {
        goto null_return;
    }
    return note;

null_return:
    layer->bit3 = true;
    return NULL;
}

void AudioPlayback_NoteInitAll(void) {
    Note* note;
    s32 i;

    for (i = 0; i < gAudioContext.numNotes; i++) {
        note = &gAudioContext.notes[i];
        note->noteSubEu = gZeroNoteSub;
        note->playbackState.priority = 0;
        note->playbackState.status = PLAYBACK_STATUS_0;
        note->playbackState.parentLayer = NO_LAYER;
        note->playbackState.wantedParentLayer = NO_LAYER;
        note->playbackState.prevParentLayer = NO_LAYER;
        note->playbackState.waveId = 0;
        note->playbackState.attributes.velocity = 0.0f;
        note->playbackState.adsrVolScaleUnused = 0;
        note->playbackState.adsr.action.asByte = 0;
        note->playbackState.vibratoState.active = false;
        note->playbackState.portamento.cur = 0;
        note->playbackState.portamento.speed = 0;
        note->playbackState.stereoHeadsetEffects = false;
        note->playbackState.startSamplePos = 0;
        note->synthesisState.synthesisBuffers = AudioHeap_AllocDmaMemory(&gAudioContext.miscPool, 0x2E0);
        note->playbackState.attributes.filterBuf = AudioHeap_AllocDmaMemory(&gAudioContext.miscPool, 0x10);
    }
}
