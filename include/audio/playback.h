#ifndef AUDIO_PLAYBACK_H
#define AUDIO_PLAYBACK_H

#include "synthesis.h"
#include "effects.h"
#include "list.h"
#include "PR/ultratypes.h"
#include "unk.h"

struct SequenceLayer;
struct Instrument;
struct TunedSample;
struct Drum;
struct SoundEffect;

#define AUDIO_ERROR(fontId, id, err) (((fontId << 8) + id) + (err << 24))

typedef enum AudioError {
    /* 0x01 */ AUDIO_ERROR_NO_INST = 1,
    /* 0x03 */ AUDIO_ERROR_INVALID_INST_ID = 3,
    /* 0x04 */ AUDIO_ERROR_INVALID_DRUM_SFX_ID,
    /* 0x05 */ AUDIO_ERROR_NO_DRUM_SFX,
    /* 0x10 */ AUDIO_ERROR_FONT_NOT_LOADED = 0x10
} AudioError;

typedef union {
    struct {
        /* 0x0 */ u8 unused : 2;
        /* 0x0 */ u8 type : 2;
        /* 0x0 */ u8 strongRight : 1;
        /* 0x0 */ u8 strongLeft : 1;
        /* 0x0 */ u8 strongReverbRight : 1;
        /* 0x0 */ u8 strongReverbLeft : 1;
    };
    /* 0x0 */ u8 asByte;
} StereoData; // size = 0x1

typedef struct NoteAttributes {
    /* 0x00 */ u8 targetReverbVol;
    /* 0x01 */ u8 gain; // Increases volume by a multiplicative scaling factor. Represented as a UQ4.4 number
    /* 0x02 */ u8 pan;
    /* 0x03 */ u8 surroundEffectIndex;
    /* 0x04 */ StereoData stereoData;
    /* 0x05 */ u8 combFilterSize;
    /* 0x06 */ u16 combFilterGain;
    /* 0x08 */ f32 freqScale;
    /* 0x0C */ f32 velocity;
    /* 0x10 */ s16* filter;
    /* 0x14 */ s16* filterBuf;
} NoteAttributes; // size = 0x18

typedef enum NotePlaybackStatus {
    /* 0 */ PLAYBACK_STATUS_0,
    /* 1 */ PLAYBACK_STATUS_1,
    /* 2 */ PLAYBACK_STATUS_2
} NotePlaybackStatus;

typedef struct NotePlaybackState {
    /* 0x00 */ u8 priority;
    /* 0x01 */ u8 waveId;
    /* 0x02 */ u8 harmonicIndex; // the harmonic index for the synthetic wave contained in gWaveSamples (also matches the base 2 logarithm of the harmonic order)
    /* 0x03 */ u8 fontId;
    /* 0x04 */ u8 status;
    /* 0x05 */ u8 stereoHeadsetEffects;
    /* 0x06 */ s16 adsrVolScaleUnused;
    /* 0x08 */ f32 portamentoFreqScale;
    /* 0x0C */ f32 vibratoFreqScale;
    /* 0x18 */ struct SequenceLayer* wantedParentLayer;
    /* 0x14 */ struct SequenceLayer* parentLayer;
    /* 0x10 */ struct SequenceLayer* prevParentLayer;
    /* 0x1C */ NoteAttributes attributes;
    /* 0x34 */ AdsrState adsr;
    /* 0x54 */ Portamento portamento;
    /* 0x60 */ VibratoState vibratoState;
    /* 0x7C */ UNK_TYPE1 pad7C[0x4];
    /* 0x80 */ u8 unk_80;
    /* 0x84 */ u32 startSamplePos;
    /* 0x88 */ UNK_TYPE1 unk_BC[0x1C]; 
} NotePlaybackState; // size = 0xA4

typedef struct NoteSampleState {
    struct {
        /* 0x00 */ vu8 enabled : 1;
        /* 0x00 */ u8 needsInit : 1;
        /* 0x00 */ u8 finished : 1;
        /* 0x00 */ u8 unused : 1;
        /* 0x00 */ u8 strongRight : 1;
        /* 0x00 */ u8 strongLeft : 1;
        /* 0x00 */ u8 strongReverbRight : 1;
        /* 0x00 */ u8 strongReverbLeft : 1;
    } bitField0;
    struct {
        /* 0x01 */ u8 reverbIndex : 3;
        /* 0x01 */ u8 bookOffset : 2;
        /* 0x01 */ u8 isSyntheticWave : 1;
        /* 0x01 */ u8 hasTwoParts : 1;
        /* 0x01 */ u8 useHaasEffect : 1;
    } bitField1;
    /* 0x02 */ u8 gain; // Increases volume by a multiplicative scaling factor. Represented as a UQ4.4 number
    /* 0x03 */ u8 haasEffectLeftDelaySize;
    /* 0x04 */ u8 haasEffectRightDelaySize;
    /* 0x05 */ u8 targetReverbVol;
    /* 0x06 */ u8 harmonicIndexCurAndPrev; // bits 3..2 store curHarmonicIndex, bits 1..0 store prevHarmonicIndex
    /* 0x07 */ u8 combFilterSize;
    /* 0x08 */ u16 targetVolLeft;
    /* 0x0A */ u16 targetVolRight;
    /* 0x0C */ u16 frequencyFixedPoint;
    /* 0x0E */ u16 combFilterGain;
    union {
        /* 0x10 */ TunedSample* tunedSample;
        /* 0x10 */ s16* waveSampleAddr; // used for synthetic waves
    };
    /* 0x14 */ s16* filter;
    /* 0x18 */ UNK_TYPE1 unk_18;
    /* 0x19 */ u8 surroundEffectIndex;
    /* 0x1A */ UNK_TYPE1 unk_1A[0x6];
} NoteSampleState; // size = 0x20

typedef struct Note {
    /* 0x00 */ AudioListItem listItem;
    /* 0x10 */ NoteSynthesisState synthesisState;
    /* 0x34 */ NotePlaybackState playbackState;
    /* 0xD8 */ NoteSampleState sampleState;
} Note; // size = 0xF8

void AudioPlayback_NoteDisable(Note* note);
void AudioPlayback_ProcessNotes(void);
struct TunedSample* AudioPlayback_GetInstrumentTunedSample(struct Instrument* instrument, s32 semitone);
struct Instrument* AudioPlayback_GetInstrumentInner(s32 fontId, s32 instId);
struct Drum* AudioPlayback_GetDrum(s32 fontId, s32 drumId);
struct SoundEffect* AudioPlayback_GetSoundEffect(s32 fontId, s32 sfxId);
s32 AudioPlayback_SetFontInstrument(s32 instrumentType, s32 fontId, s32 index, void* value);
void AudioPlayback_SeqLayerNoteDecay(struct SequenceLayer* layer);
void AudioPlayback_SeqLayerNoteRelease(struct SequenceLayer* layer);
void AudioPlayback_InitSyntheticWave(Note* note, struct SequenceLayer* layer);
Note* AudioPlayback_AllocNote(struct SequenceLayer* layer);
void AudioPlayback_NoteInitAll(void);

#endif
