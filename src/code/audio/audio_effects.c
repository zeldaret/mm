#include "global.h"

void AudioEffects_SequenceChannelProcessSound(SequenceChannel* channel, s32 recalculateVolume, s32 applyBend) {
    f32 channelVolume;
    f32 chanFreqScale;
    s32 i;

    if (channel->changes.s.volume || recalculateVolume) {
        channelVolume = channel->volume * channel->volumeScale * channel->seqPlayer->appliedFadeVolume;
        if (channel->seqPlayer->muted && (channel->muteBehavior & 0x20)) {
            channelVolume = channel->seqPlayer->muteVolumeScale * channelVolume;
        }
        channel->appliedVolume = channelVolume * channelVolume;
    }

    if (channel->changes.s.pan) {
        channel->pan = channel->newPan * channel->panChannelWeight;
    }

    chanFreqScale = channel->freqScale;
    if (applyBend) {
        chanFreqScale *= channel->seqPlayer->bend;
        channel->changes.s.freqScale = true;
    }

    for (i = 0; i < ARRAY_COUNT(channel->layers); i++) {
        SequenceLayer* layer = channel->layers[i];

        if (layer != NULL && layer->enabled && layer->note != NULL) {
            if (layer->notePropertiesNeedInit) {
                layer->noteFreqScale = layer->freqScale * chanFreqScale;
                layer->noteVelocity = layer->velocitySquare2 * channel->appliedVolume;
                layer->notePan = (channel->pan + layer->pan * (0x80 - channel->panChannelWeight)) >> 7;
                layer->notePropertiesNeedInit = false;
            } else {
                if (channel->changes.s.freqScale) {
                    layer->noteFreqScale = layer->freqScale * chanFreqScale;
                }
                if (channel->changes.s.volume || recalculateVolume) {
                    layer->noteVelocity = layer->velocitySquare2 * channel->appliedVolume;
                }
                if (channel->changes.s.pan) {
                    layer->notePan = (channel->pan + layer->pan * (0x80 - channel->panChannelWeight)) >> 7;
                }
            }
        }
    }
    channel->changes.asByte = 0;
}

void AudioEffects_SequencePlayerProcessSound(SequencePlayer* seqPlayer) {
    s32 i;

    if ((seqPlayer->fadeTimer != 0) && (seqPlayer->skipTicks == 0)) {
        seqPlayer->fadeVolume += seqPlayer->fadeVelocity;
        seqPlayer->recalculateVolume = true;

        if (seqPlayer->fadeVolume > 1.0f) {
            seqPlayer->fadeVolume = 1.0f;
        }
        if (seqPlayer->fadeVolume < 0.0f) {
            seqPlayer->fadeVolume = 0.0f;
        }

        seqPlayer->fadeTimer--;
        if (seqPlayer->fadeTimer == 0 && seqPlayer->state == 2) {
            AudioSeq_SequencePlayerDisable(seqPlayer);
            return;
        }
    }

    if (seqPlayer->recalculateVolume) {
        seqPlayer->appliedFadeVolume = seqPlayer->fadeVolume * seqPlayer->fadeVolumeScale;
    }

    for (i = 0; i < ARRAY_COUNT(seqPlayer->channels); i++) {
        if (seqPlayer->channels[i]->enabled == true) {
            AudioEffects_SequenceChannelProcessSound(seqPlayer->channels[i], seqPlayer->recalculateVolume,
                                                     seqPlayer->applyBend);
        }
    }

    seqPlayer->recalculateVolume = false;
}

f32 AudioEffects_GetPortamentoFreqScale(Portamento* portamento) {
    u32 loResCur;
    f32 portamentoFreq;

    portamento->cur += portamento->speed;
    loResCur = (portamento->cur >> 8) & 0xFF;

    if (loResCur >= 127) {
        loResCur = 127;
        portamento->mode = 0;
    }

    portamentoFreq = AUDIO_LERPIMP(1.0f, gBendPitchOneOctaveFrequencies[loResCur + 128], portamento->extent);

    return portamentoFreq;
}

s16 AudioEffects_GetVibratoPitchChange(VibratoState* vib) {
    s32 index;

    vib->time += (s32)vib->rate;
    index = (vib->time >> 10) & 0x3F;
    return vib->curve[index];
}

f32 AudioEffects_GetVibratoFreqScale(VibratoState* vib) {
    static f32 activeVibratoFreqScaleSum = 0.0f;
    static s32 activeVibratoCount = 0;
    f32 pitchChange;
    f32 extent;
    f32 invExtent;
    f32 result;
    f32 scaledExtent;
    VibratoSubStruct* subVib = vib->vibSubStruct;

    if (vib->delay != 0) {
        vib->delay--;
        return 1.0f;
    }

    if (subVib != NULL) {
        if (vib->extentChangeTimer) {
            if (vib->extentChangeTimer == 1) {
                vib->extent = (s32)subVib->vibratoExtentTarget;
            } else {
                vib->extent += ((s32)subVib->vibratoExtentTarget - vib->extent) / (s32)vib->extentChangeTimer;
            }

            vib->extentChangeTimer--;
        } else if (subVib->vibratoExtentTarget != (s32)vib->extent) {
            if ((vib->extentChangeTimer = subVib->vibratoExtentChangeDelay) == 0) {
                vib->extent = (s32)subVib->vibratoExtentTarget;
            }
        }

        if (vib->rateChangeTimer) {
            if (vib->rateChangeTimer == 1) {
                vib->rate = (s32)subVib->vibratoRateTarget;
            } else {
                vib->rate += ((s32)subVib->vibratoRateTarget - vib->rate) / (s32)vib->rateChangeTimer;
            }

            vib->rateChangeTimer--;
        } else if (subVib->vibratoRateTarget != (s32)vib->rate) {
            if ((vib->rateChangeTimer = subVib->vibratoRateChangeDelay) == 0) {
                vib->rate = (s32)subVib->vibratoRateTarget;
            }
        }
    }

    if (vib->extent == 0.0f) {
        return 1.0f;
    }

    pitchChange = AudioEffects_GetVibratoPitchChange(vib) + 32768.0f;
    scaledExtent = vib->extent / 4096.0f;
    extent = scaledExtent + 1.0f;
    invExtent = 1.0f / extent;

    // inverse linear interpolation
    result = 1.0f / ((extent - invExtent) * pitchChange / 65536.0f + invExtent);

    activeVibratoFreqScaleSum += result;
    activeVibratoCount++;

    return result;
}

void AudioEffects_NoteVibratoUpdate(Note* note) {
    if (note->playbackState.portamento.mode != 0) {
        note->playbackState.portamentoFreqScale = AudioEffects_GetPortamentoFreqScale(&note->playbackState.portamento);
    }
    if (note->playbackState.vibratoState.active) {
        note->playbackState.vibratoFreqScale = AudioEffects_GetVibratoFreqScale(&note->playbackState.vibratoState);
    }
}

void AudioEffects_NoteVibratoInit(Note* note) {
    NotePlaybackState* playbackState = &note->playbackState;
    VibratoState* vib = &playbackState->vibratoState;
    VibratoSubStruct* subVib;

    vib->active = true;
    vib->curve = gWaveSamples[2];

    if (playbackState->parentLayer->unk_0A.s.bit_3 == 1) {
        vib->vibSubStruct = &playbackState->parentLayer->channel->vibrato;
    } else {
        vib->vibSubStruct = &playbackState->parentLayer->vibrato;
    }

    subVib = vib->vibSubStruct;

    if ((vib->extentChangeTimer = subVib->vibratoExtentChangeDelay) == 0) {
        vib->extent = (s32)subVib->vibratoExtentTarget;
    } else {
        vib->extent = (s32)subVib->vibratoExtentStart;
    }

    if ((vib->rateChangeTimer = subVib->vibratoRateChangeDelay) == 0) {
        vib->rate = (s32)subVib->vibratoRateTarget;
    } else {
        vib->rate = (s32)subVib->vibratoRateStart;
    }

    playbackState->vibratoFreqScale = 1.0f;
    vib->time = 0;
    vib->delay = subVib->vibratoDelay;
}

void AudioEffects_NotePortamentoInit(Note* note) {
    note->playbackState.portamentoFreqScale = 1.0f;
    note->playbackState.portamento = note->playbackState.parentLayer->portamento;
}

void AudioEffects_AdsrInit(AdsrState* adsr, AdsrEnvelope* envelope, s16* volOut) {
    adsr->action.asByte = 0;
    adsr->delay = 0;
    adsr->envelope = envelope;
    adsr->sustain = 0.0f;
    adsr->current = 0.0f;
    adsr->velocity = 0.0f;
    // (An older versions of the audio engine used in Super Mario 64 did
    // adsr->volOut = volOut. That line and associated struct member were
    // removed, but the function parameter was forgotten and remains.)
}

f32 AudioEffects_AdsrUpdate(AdsrState* adsr) {
    u8 state = adsr->action.s.state;

    switch (state) {
        case ADSR_STATE_DISABLED:
            return 0.0f;

        case ADSR_STATE_INITIAL:
            if (adsr->action.s.hang) {
                adsr->action.s.state = ADSR_STATE_HANG;
                break;
            }
            // fallthrough

        case ADSR_STATE_START_LOOP:
            adsr->envIndex = 0;
            adsr->action.s.state = ADSR_STATE_LOOP;
            // fallthrough

        retry:
        case ADSR_STATE_LOOP:
            adsr->delay = adsr->envelope[adsr->envIndex].delay;
            switch (adsr->delay) {
                case ADSR_DISABLE:
                    adsr->action.s.state = ADSR_STATE_DISABLED;
                    break;
                case ADSR_HANG:
                    adsr->action.s.state = ADSR_STATE_HANG;
                    break;
                case ADSR_GOTO:
                    adsr->envIndex = adsr->envelope[adsr->envIndex].arg;
                    goto retry;
                case ADSR_RESTART:
                    adsr->action.s.state = ADSR_STATE_INITIAL;
                    break;

                default:
                    adsr->delay *= gAudioContext.audioBufferParameters.unk_24;
                    if (adsr->delay == 0) {
                        adsr->delay = 1;
                    }
                    adsr->target = adsr->envelope[adsr->envIndex].arg / 32767.0f;
                    adsr->target = adsr->target * adsr->target;
                    adsr->velocity = (adsr->target - adsr->current) / adsr->delay;
                    adsr->action.s.state = ADSR_STATE_FADE;
                    adsr->envIndex++;
                    break;
            }
            if (adsr->action.s.state != ADSR_STATE_FADE) {
                break;
            }
            // fallthrough

        case ADSR_STATE_FADE:
            adsr->current += adsr->velocity;
            if (--adsr->delay <= 0) {
                adsr->action.s.state = ADSR_STATE_LOOP;
            }
            // fallthrough

        case ADSR_STATE_HANG:
            break;

        case ADSR_STATE_DECAY:
        case ADSR_STATE_RELEASE:
            adsr->current -= adsr->fadeOutVel;
            if (adsr->sustain != 0.0f && state == ADSR_STATE_DECAY) {
                if (adsr->current < adsr->sustain) {
                    adsr->current = adsr->sustain;
                    adsr->delay = 128;
                    adsr->action.s.state = ADSR_STATE_SUSTAIN;
                }
                break;
            }

            if (adsr->current < 0.00001f) {
                adsr->current = 0.0f;
                adsr->action.s.state = ADSR_STATE_DISABLED;
            }
            break;

        case ADSR_STATE_SUSTAIN:
            adsr->delay--;
            if (adsr->delay == 0) {
                adsr->action.s.state = ADSR_STATE_RELEASE;
            }
            break;
    }

    if (adsr->action.s.decay) {
        adsr->action.s.state = ADSR_STATE_DECAY;
        adsr->action.s.decay = false;
    }

    if (adsr->action.s.release) {
        adsr->action.s.state = ADSR_STATE_RELEASE;
        adsr->action.s.release = false;
    }

    if (adsr->current < 0.0f) {
        return 0.0f;
    }

    if (adsr->current > 1.0f) {
        return 1.0f;
    }

    return adsr->current;
}
