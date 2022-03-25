#include "global.h"

void AudioPlayback_NoteSetResamplingRate(NoteSubEu* noteSubEu, f32 resamplingRateInput);
void AudioPlayback_AudioListPushFront(AudioListItem* list, AudioListItem* item);
void AudioPlayback_NoteInitForLayer(Note* note, SequenceLayer* layer);

void AudioPlayback_InitNoteSub(Note* note, NoteSubEu* sub, NoteSubAttributes* attrs) {
    f32 volRight, volLeft;
    s32 smallPanIndex;
    u64 pad;
    u8 strongLeft;
    u8 strongRight;
    f32 vel;
    u8 pan;
    u8 reverbVol;
    StereoData stereoData;
    s32 stereoHeadsetEffects = note->playbackState.stereoHeadsetEffects;

    vel = attrs->velocity;
    pan = attrs->pan;
    reverbVol = attrs->reverbVol;
    stereoData = attrs->stereo.s;

    sub->bitField0 = note->noteSubEu.bitField0;
    sub->bitField1 = note->noteSubEu.bitField1;
    sub->sound.samples = note->noteSubEu.sound.samples;
    sub->unk_06 = note->noteSubEu.unk_06;

    AudioPlayback_NoteSetResamplingRate(sub, attrs->frequency);

    pan &= 0x7F;

    sub->bitField0.stereoStrongRight = false;
    sub->bitField0.stereoStrongLeft = false;
    sub->bitField0.stereoHeadsetEffects = stereoData.stereoHeadsetEffects;
    sub->bitField0.usesHeadsetPanEffects = stereoData.usesHeadsetPanEffects;
    if (stereoHeadsetEffects && gAudioContext.soundMode == AUDIO_MODE_HEADSET) {
        smallPanIndex = pan >> 1;
        if (smallPanIndex > 0x3F) {
            smallPanIndex = 0x3F;
        }

        sub->headsetPanLeft = gHeadsetPanQuantization[smallPanIndex];
        sub->headsetPanRight = gHeadsetPanQuantization[0x3F - smallPanIndex];
        sub->bitField1.usesHeadsetPanEffects2 = true;

        volLeft = gHeadsetPanVolume[pan];
        volRight = gHeadsetPanVolume[0x7F - pan];
    } else if (stereoHeadsetEffects && gAudioContext.soundMode == AUDIO_MODE_STEREO) {
        strongLeft = strongRight = false;
        sub->headsetPanRight = 0;
        sub->headsetPanLeft = 0;
        sub->bitField1.usesHeadsetPanEffects2 = false;

        volLeft = gStereoPanVolume[pan];
        volRight = gStereoPanVolume[0x7F - pan];
        if (pan < 0x20) {
            strongLeft = true;
        } else if (pan > 0x60) {
            strongRight = true;
        }

        sub->bitField0.stereoStrongRight = strongRight;
        sub->bitField0.stereoStrongLeft = strongLeft;

        switch (stereoData.bit2) {
            case 0:
                break;
            case 1:
                sub->bitField0.stereoStrongRight = stereoData.strongRight;
                sub->bitField0.stereoStrongLeft = stereoData.strongLeft;
                break;
            case 2:
                sub->bitField0.stereoStrongRight = stereoData.strongRight | strongRight;
                sub->bitField0.stereoStrongLeft = stereoData.strongLeft | strongLeft;
                break;
            case 3:
                sub->bitField0.stereoStrongRight = stereoData.strongRight ^ strongRight;
                sub->bitField0.stereoStrongLeft = stereoData.strongLeft ^ strongLeft;
                break;
        }

    } else if (gAudioContext.soundMode == AUDIO_MODE_MONO) {
        sub->bitField0.stereoHeadsetEffects = false;
        sub->bitField0.usesHeadsetPanEffects = false;
        volLeft = 0.707f; // approx 1/sqrt(2)
        volRight = 0.707f;
    } else {
        sub->bitField0.stereoStrongRight = stereoData.strongRight;
        sub->bitField0.stereoStrongLeft = stereoData.strongLeft;
        volLeft = gDefaultPanVolume[pan];
        volRight = gDefaultPanVolume[0x7F - pan];
    }

    vel = 0.0f > vel ? 0.0f : vel;
    vel = 1.0f < vel ? 1.0f : vel;

    sub->targetVolLeft = (s32)((vel * volLeft) * (0x1000 - 0.001f));
    sub->targetVolRight = (s32)((vel * volRight) * (0x1000 - 0.001f));

    sub->unk_2 = attrs->unk_1;
    sub->filter = attrs->filter;
    sub->unk_07 = attrs->unk_14;
    sub->unk_0E = attrs->unk_16;
    sub->reverbVol = reverbVol;
    sub->unk_19 = attrs->unk_3;
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
    if (note->playbackState.parentLayer->adsr.releaseRate == 0) {
        AudioEffects_AdsrInit(&note->playbackState.adsr, note->playbackState.parentLayer->channel->adsr.envelope,
                              &note->playbackState.adsrVolScaleUnused);
    } else {
        AudioEffects_AdsrInit(&note->playbackState.adsr, note->playbackState.parentLayer->adsr.envelope,
                              &note->playbackState.adsrVolScaleUnused);
    }

    note->playbackState.unk_04 = 0;
    note->playbackState.adsr.action.s.state = ADSR_STATE_INITIAL;
    note->noteSubEu = gDefaultNoteSub;
}

void AudioPlayback_NoteDisable(Note* note) {
    if (note->noteSubEu.bitField0.needsInit == true) {
        note->noteSubEu.bitField0.needsInit = false;
    }
    note->playbackState.priority = 0;
    note->noteSubEu.bitField0.enabled = false;
    note->playbackState.unk_04 = 0;
    note->noteSubEu.bitField0.finished = false;
    note->playbackState.parentLayer = NO_LAYER;
    note->playbackState.prevParentLayer = NO_LAYER;
    note->playbackState.adsr.action.s.state = ADSR_STATE_DISABLED;
    note->playbackState.adsr.current = 0;
}

void AudioPlayback_ProcessNotes(void) {
    s32 pad;
    s32 unk_04;
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

            if (note != playbackState->parentLayer->note && playbackState->unk_04 == 0) {
                playbackState->adsr.action.s.release = true;
                playbackState->adsr.fadeOutVel = gAudioContext.audioBufferParameters.updatesPerFrameInv;
                playbackState->priority = 1;
                playbackState->unk_04 = 2;
                goto out;
            } else if (!playbackState->parentLayer->enabled && playbackState->unk_04 == 0 &&
                       playbackState->priority >= 1) {
                // do nothing
            } else if (playbackState->parentLayer->channel->seqPlayer == NULL) {
                AudioSeq_SequenceChannelDisable(playbackState->parentLayer->channel);
                playbackState->priority = 1;
                playbackState->unk_04 = 1;
                continue;
            } else if (playbackState->parentLayer->channel->seqPlayer->muted &&
                       (playbackState->parentLayer->channel->muteBehavior & 0x40)) {
                // do nothing
            } else {
                goto out;
            }

            AudioPlayback_SeqLayerNoteRelease(playbackState->parentLayer);
            AudioPlayback_AudioListRemove(&note->listItem);
            AudioPlayback_AudioListPushFront(&note->listItem.pool->decaying, &note->listItem);
            playbackState->priority = 1;
            playbackState->unk_04 = 2;
        } else if (playbackState->unk_04 == 0 && playbackState->priority >= 1) {
            continue;
        }

    out:
        if (playbackState->priority != 0) {
            if (1) {}
            noteSubEu = &note->noteSubEu;
            if (playbackState->unk_04 >= 1 || noteSubEu->bitField0.finished) {
                if (playbackState->adsr.action.s.state == ADSR_STATE_DISABLED || noteSubEu->bitField0.finished) {
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
            unk_04 = playbackState->unk_04;
            attrs = &playbackState->attributes;
            if (unk_04 == 1 || unk_04 == 2) {
                subAttrs.frequency = attrs->freqScale;
                subAttrs.velocity = attrs->velocity;
                subAttrs.pan = attrs->pan;
                subAttrs.reverbVol = attrs->reverb;
                subAttrs.stereo = attrs->stereo;
                subAttrs.unk_1 = attrs->unk_1;
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
                    subAttrs.unk_1 = channel->unk_0C;
                } else {
                    subAttrs.unk_1 = 0;
                    if (1) {}
                }

                subAttrs.filter = channel->filter;
                subAttrs.unk_14 = channel->unk_0F;
                subAttrs.unk_16 = channel->unk_20;
                bookOffset = channel->bookOffset & 0x7;

                if (channel->seqPlayer->muted && (channel->muteBehavior & 8)) {
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

SoundFontSound* AudioPlayback_InstrumentGetSound(Instrument* instrument, s32 semitone) {
    SoundFontSound* sound;

    if (semitone < instrument->normalRangeLo) {
        sound = &instrument->lowNotesSound;
    } else if (semitone <= instrument->normalRangeHi) {
        sound = &instrument->normalNotesSound;
    } else {
        sound = &instrument->highNotesSound;
    }
    return sound;
}

Instrument* AudioPlayback_GetInstrumentInner(s32 fontId, s32 instId) {
    Instrument* inst;

    if (fontId == 0xFF) {
        return NULL;
    }

    if (!AudioLoad_IsFontLoadComplete(fontId)) {
        gAudioContext.audioErrorFlags = fontId + 0x10000000;
        return NULL;
    }

    if (instId >= gAudioContext.soundFonts[fontId].numInstruments) {
        gAudioContext.audioErrorFlags = ((fontId << 8) + instId) + 0x3000000;
        return NULL;
    }

    inst = gAudioContext.soundFonts[fontId].instruments[instId];
    if (inst == NULL) {
        gAudioContext.audioErrorFlags = ((fontId << 8) + instId) + 0x1000000;
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
        gAudioContext.audioErrorFlags = fontId + 0x10000000;
        return NULL;
    }

    if (drumId >= gAudioContext.soundFonts[fontId].numDrums) {
        gAudioContext.audioErrorFlags = ((fontId << 8) + drumId) + 0x4000000;
        return NULL;
    }
    if ((u32)gAudioContext.soundFonts[fontId].drums < 0x80000000) {
        return NULL;
    }
    drum = gAudioContext.soundFonts[fontId].drums[drumId];

    if (drum == NULL) {
        gAudioContext.audioErrorFlags = ((fontId << 8) + drumId) + 0x5000000;
    }

    return drum;
}

SoundFontSound* AudioPlayback_GetSfx(s32 fontId, s32 sfxId) {
    SoundFontSound* sfx;

    if (fontId == 0xFF) {
        return NULL;
    }

    if (!AudioLoad_IsFontLoadComplete(fontId)) {
        gAudioContext.audioErrorFlags = fontId + 0x10000000;
        return NULL;
    }

    if (sfxId >= gAudioContext.soundFonts[fontId].numSfx) {
        gAudioContext.audioErrorFlags = ((fontId << 8) + sfxId) + 0x4000000;
        return NULL;
    }

    if ((u32)gAudioContext.soundFonts[fontId].soundEffects < 0x80000000) {
        return NULL;
    }

    sfx = &gAudioContext.soundFonts[fontId].soundEffects[sfxId];

    if (sfx == NULL) {
        gAudioContext.audioErrorFlags = ((fontId << 8) + sfxId) + 0x5000000;
    }

    if (sfx->sample == NULL) {
        return NULL;
    }

    return sfx;
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
            if (index >= gAudioContext.soundFonts[fontId].numDrums) {
                return -3;
            }
            gAudioContext.soundFonts[fontId].drums[index] = value;
            break;

        case 1:
            if (index >= gAudioContext.soundFonts[fontId].numSfx) {
                return -3;
            }
            gAudioContext.soundFonts[fontId].soundEffects[index] = *(SoundFontSound*)value;
            break;

        default:
            if (index >= gAudioContext.soundFonts[fontId].numInstruments) {
                return -3;
            }
            gAudioContext.soundFonts[fontId].instruments[index] = value;
            break;
    }

    return 0;
}

void AudioPlayback_SeqLayerDecayRelease(SequenceLayer* layer, s32 target) {
    Note* note;
    NoteAttributes* attrs;
    SequenceChannel* chan;
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
            chan = layer->channel;

            if (layer->unk_0A.s.bit_2 == 1) {
                attrs->reverb = chan->reverb;
            } else {
                attrs->reverb = layer->unk_09;
            }

            if (layer->unk_08 == 0x80) {
                attrs->unk_3 = chan->unk_10;
            } else {
                attrs->unk_3 = layer->unk_08;
            }

            if (layer->unk_0A.s.bit_9 == 1) {
                attrs->unk_1 = chan->unk_0C;
            } else {
                attrs->unk_1 = 0;
            }

            attrs->filter = chan->filter;

            if (attrs->filter != NULL) {
                for (i = 0; i < 8; i++) {
                    attrs->filterBuf[i] = attrs->filter[i];
                }
                attrs->filter = attrs->filterBuf;
            }

            attrs->unk_6 = chan->unk_20;
            attrs->unk_4 = chan->unk_0F;
            if (chan->seqPlayer->muted && (chan->muteBehavior & 8)) {
                note->noteSubEu.bitField0.finished = true;
            }

            if (layer->stereo.asByte == 0) {
                attrs->stereo = chan->stereo;
            } else {
                attrs->stereo = layer->stereo;
            }
            note->playbackState.priority = chan->someOtherPriority;
        } else {
            attrs->stereo = layer->stereo;
            note->playbackState.priority = 1;
        }

        note->playbackState.prevParentLayer = note->playbackState.parentLayer;
        note->playbackState.parentLayer = NO_LAYER;
        if (target == ADSR_STATE_RELEASE) {
            note->playbackState.adsr.fadeOutVel = gAudioContext.audioBufferParameters.updatesPerFrameInv;
            note->playbackState.adsr.action.s.release = true;
            note->playbackState.unk_04 = 2;
        } else {
            note->playbackState.unk_04 = 1;
            note->playbackState.adsr.action.s.decay = true;
            if (layer->adsr.releaseRate == 0) {
                note->playbackState.adsr.fadeOutVel = gAudioContext.unk_3520[layer->channel->adsr.releaseRate];
            } else {
                note->playbackState.adsr.fadeOutVel = gAudioContext.unk_3520[layer->adsr.releaseRate];
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

s32 AudioPlayback_BuildSyntheticWave(Note* note, SequenceLayer* layer, s32 waveId) {
    f32 freqScale;
    f32 ratio;
    u8 sampleCountIndex;

    if (waveId < 128) {
        waveId = 128;
    }

    freqScale = layer->freqScale;
    if (layer->portamento.mode != 0 && 0.0f < layer->portamento.extent) {
        freqScale *= (layer->portamento.extent + 1.0f);
    }
    if (freqScale < 0.99999f) {
        sampleCountIndex = 0;
        ratio = 1.0465f;
    } else if (freqScale < 1.99999f) {
        sampleCountIndex = 1;
        ratio = 0.52325f;
    } else if (freqScale < 3.99999f) {
        sampleCountIndex = 2;
        ratio = 0.26263f;
    } else {
        sampleCountIndex = 3;
        ratio = 0.13081f;
    }
    layer->freqScale *= ratio;
    note->playbackState.waveId = waveId;
    note->playbackState.sampleCountIndex = sampleCountIndex;

    note->noteSubEu.sound.samples = &gWaveSamples[waveId - 128][sampleCountIndex * 64];

    return sampleCountIndex;
}

void AudioPlayback_InitSyntheticWave(Note* note, SequenceLayer* layer) {
    s32 sampleCountIndex;
    s32 waveSampleCountIndex;
    s32 waveId = layer->instOrWave;

    if (waveId == 0xFF) {
        waveId = layer->channel->instOrWave;
    }

    sampleCountIndex = note->playbackState.sampleCountIndex;
    waveSampleCountIndex = AudioPlayback_BuildSyntheticWave(note, layer, waveId);

    if (waveSampleCountIndex != sampleCountIndex) {
        note->noteSubEu.unk_06 = waveSampleCountIndex * 4 + sampleCountIndex;
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
    noteSubEu->sound.soundFontSound = layer->sound;

    if (instId >= 0x80 && instId < 0xC0) {
        noteSubEu->bitField1.isSyntheticWave = true;
    } else {
        noteSubEu->bitField1.isSyntheticWave = false;
    }

    if (noteSubEu->bitField1.isSyntheticWave) {
        AudioPlayback_BuildSyntheticWave(note, layer, instId);
    } else if (channel->unk_DC == 1) {
        playbackState->unk_84 = noteSubEu->sound.soundFontSound->sample->loop->start;
    } else {
        playbackState->unk_84 = channel->unk_DC;
        if (playbackState->unk_84 >= noteSubEu->sound.soundFontSound->sample->loop->end) {
            playbackState->unk_84 = 0;
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
        note->playbackState.unk_04 = 0;
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
        note->playbackState.unk_84 = 0;
        note->synthesisState.synthesisBuffers = AudioHeap_AllocDmaMemory(&gAudioContext.miscPool, 0x2E0);
        note->playbackState.attributes.filterBuf = AudioHeap_AllocDmaMemory(&gAudioContext.miscPool, 0x10);
    }
}
