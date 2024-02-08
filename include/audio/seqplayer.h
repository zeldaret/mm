#ifndef AUDIO_SEQPLAYER_H
#define AUDIO_SEQPLAYER_H

#include "effects.h"
#include "list.h"
#include "playback.h"
#include "PR/ultratypes.h"
#include "PR/abi.h"
#include "unk.h"

struct Sample;
struct Instrument;
struct TunedSample;

#define SEQ_NUM_CHANNELS 16

#define NO_LAYER ((SequenceLayer*)(-1))

#define TATUMS_PER_BEAT 48

#define IS_SEQUENCE_CHANNEL_VALID(ptr) ((uintptr_t)(ptr) != (uintptr_t)&gAudioCtx.sequenceChannelNone)
#define SEQ_IO_VAL_NONE -1

#define MUTE_FLAGS_STOP_SAMPLES (1 << 3) // prevent further noteSubEus from playing
#define MUTE_FLAGS_STOP_LAYER (1 << 4) // stop something in seqLayer scripts
#define MUTE_FLAGS_SOFTEN (1 << 5) // lower volume, by default to half
#define MUTE_FLAGS_STOP_NOTES (1 << 6) // prevent further notes from playing
#define MUTE_FLAGS_STOP_SCRIPT (1 << 7) // stop processing sequence/channel scripts

typedef struct SeqScriptState {
    /* 0x00 */ u8* pc; // program counter
    /* 0x04 */ u8* stack[4];
    /* 0x14 */ u8 remLoopIters[4]; // remaining loop iterations
    /* 0x18 */ u8 depth;
    /* 0x19 */ s8 value;
} SeqScriptState; // size = 0x1C

typedef enum SeqPlayerState {
    /* 0 */ SEQPLAYER_STATE_0,
    /* 1 */ SEQPLAYER_STATE_FADE_IN,
    /* 2 */ SEQPLAYER_STATE_FADE_OUT
} SeqPlayerState;

// Also known as a Group, according to debug strings.
typedef struct SequencePlayer {
    /* 0x000 */ u8 enabled : 1;
    /* 0x000 */ u8 finished : 1;
    /* 0x000 */ u8 muted : 1;
    /* 0x000 */ u8 seqDmaInProgress : 1;
    /* 0x000 */ u8 fontDmaInProgress : 1;
    /* 0x000 */ u8 recalculateVolume : 1;
    /* 0x000 */ u8 stopScript : 1;
    /* 0x000 */ u8 applyBend : 1;
    /* 0x001 */ u8 state;
    /* 0x002 */ u8 noteAllocPolicy;
    /* 0x003 */ u8 muteFlags;
    /* 0x004 */ u8 seqId;
    /* 0x005 */ u8 defaultFont;
    /* 0x006 */ u8 unk_06[1];
    /* 0x007 */ s8 playerIndex;
    /* 0x008 */ u16 tempo; // tatums per minute
    /* 0x00A */ u16 tempoAcc;
    /* 0x00C */ s16 tempoChange;
    /* 0x00E */ s16 transposition;
    /* 0x010 */ u16 delay;
    /* 0x012 */ u16 fadeTimer;
    /* 0x014 */ u16 storedFadeTimer;
    /* 0x016 */ u16 unk_16;
    /* 0x018 */ u8* seqData;
    /* 0x01C */ f32 fadeVolume;
    /* 0x020 */ f32 fadeVelocity;
    /* 0x024 */ f32 volume;
    /* 0x028 */ f32 muteVolumeScale;
    /* 0x02C */ f32 fadeVolumeScale;
    /* 0x030 */ f32 appliedFadeVolume;
    /* 0x034 */ f32 bend;
    /* 0x038 */ struct SequenceChannel* channels[16];
    /* 0x078 */ SeqScriptState scriptState;
    /* 0x094 */ u8* shortNoteVelocityTable;
    /* 0x098 */ u8* shortNoteGateTimeTable;
    /* 0x09C */ NotePool notePool;
    /* 0x0DC */ s32 skipTicks;
    /* 0x0E0 */ u32 scriptCounter;
    /* 0x0E4 */ UNK_TYPE1 unk_E4[0x74]; // unused struct members for sequence/sound font dma management, according to sm64 decomp
    /* 0x158 */ s8 seqScriptIO[8];
} SequencePlayer; // size = 0x160

// Also known as a SubTrack, according to sm64 debug strings.
typedef struct SequenceChannel {
    /* 0x00 */ u8 enabled : 1;
    /* 0x00 */ u8 finished : 1;
    /* 0x00 */ u8 stopScript : 1;
    /* 0x00 */ u8 muted : 1; // sets SequenceLayer.muted
    /* 0x00 */ u8 hasInstrument : 1;
    /* 0x00 */ u8 stereoHeadsetEffects : 1;
    /* 0x00 */ u8 largeNotes : 1; // notes specify duration and velocity
    /* 0x00 */ u8 unused : 1;
    union {
        struct {
            /* 0x01 */ u8 freqScale : 1;
            /* 0x01 */ u8 volume : 1;
            /* 0x01 */ u8 pan : 1;
        } s;
        /* 0x01 */ u8 asByte;
    } changes;
    /* 0x02 */ u8 noteAllocPolicy;
    /* 0x03 */ u8 muteFlags;
    /* 0x04 */ u8 targetReverbVol; // or dry/wet mix
    /* 0x05 */ u8 notePriority; // 0-3
    /* 0x06 */ u8 someOtherPriority;
    /* 0x07 */ u8 fontId;
    /* 0x08 */ u8 reverbIndex;
    /* 0x09 */ u8 bookOffset;
    /* 0x0A */ u8 newPan;
    /* 0x0B */ u8 panChannelWeight;  // proportion of pan that comes from the channel (0..128)
    /* 0x0C */ u8 gain; // Increases volume by a multiplicative scaling factor. Represented as a UQ4.4 number
    /* 0x0D */ u8 velocityRandomVariance;
    /* 0x0E */ u8 gateTimeRandomVariance;
    /* 0x0F */ u8 combFilterSize;
    /* 0x10 */ u8 surroundEffectIndex;
    /* 0x11 */ u8 channelIndex;
    /* 0x12 */ VibratoSubStruct vibrato;
    /* 0x20 */ u16 delay;
    /* 0x22 */ u16 combFilterGain;
    /* 0x24 */ u16 unk_22; // Used for indexing data
    /* 0x26 */ s16 instOrWave; // either 0 (none), instrument index + 1, or
                             // 0x80..0x83 for sawtooth/triangle/sine/square waves.
    /* 0x28 */ s16 transposition;
    /* 0x2C */ f32 volumeScale;
    /* 0x30 */ f32 volume;
    /* 0x34 */ s32 pan;
    /* 0x38 */ f32 appliedVolume;
    /* 0x3C */ f32 freqScale;
    /* 0x40 */ u8 (*dynTable)[][2];
    /* 0x44 */ Note* noteUnused;
    /* 0x48 */ struct SequenceLayer* layerUnused;
    /* 0x4C */ struct Instrument* instrument;
    /* 0x50 */ SequencePlayer* seqPlayer;
    /* 0x54 */ struct SequenceLayer* layers[4];
    /* 0x64 */ SeqScriptState scriptState;
    /* 0x80 */ AdsrSettings adsr;
    /* 0x88 */ NotePool notePool;
    /* 0xC8 */ s8 seqScriptIO[8]; // bridge between sound script and audio lib, "io ports"
    /* 0xD0 */ u8* sfxState; // SfxChannelState
    /* 0xD4 */ s16* filter;
    /* 0xD8 */ StereoData stereoData;
    /* 0xDC */ s32 startSamplePos;
    /* 0xE0 */ s32 unk_E0;
} SequenceChannel; // size = 0xE4

// Might also be known as a Track, according to sm64 debug strings (?).
typedef struct SequenceLayer {
    /* 0x00 */ u8 enabled : 1;
    /* 0x00 */ u8 finished : 1;
    /* 0x00 */ u8 muted : 1;
    /* 0x00 */ u8 continuousNotes : 1; // keep the same note for consecutive notes with the same sound
    /* 0x00 */ u8 bit3 : 1; // "loaded"?
    /* 0x00 */ u8 ignoreDrumPan : 1;
    /* 0x00 */ u8 bit1 : 1; // "has initialized continuous notes"?
    /* 0x00 */ u8 notePropertiesNeedInit : 1;
    /* 0x01 */ StereoData stereoData;
    /* 0x02 */ u8 instOrWave;
    /* 0x03 */ u8 gateTime;
    /* 0x04 */ u8 semitone;
    /* 0x05 */ u8 portamentoTargetNote;
    /* 0x06 */ u8 pan; // 0..128
    /* 0x07 */ u8 notePan;
    /* 0x08 */ u8 surroundEffectIndex;
    /* 0x09 */ u8 targetReverbVol;
    union {
        struct {
            /* 0x0A */ u16 bit_0 : 1;
            /* 0x0A */ u16 bit_1 : 1;
            /* 0x0A */ u16 bit_2 : 1;
            /* 0x0A */ u16 useVibrato : 1;
            /* 0x0A */ u16 bit_4 : 1;
            /* 0x0A */ u16 bit_5 : 1;
            /* 0x0A */ u16 bit_6 : 1;
            /* 0x0A */ u16 bit_7 : 1;
            /* 0x0A */ u16 bit_8 : 1;
            /* 0x0A */ u16 bit_9 : 1;
            /* 0x0A */ u16 bit_A : 1;
            /* 0x0A */ u16 bit_B : 1;
            /* 0x0A */ u16 bit_C : 1;
            /* 0x0A */ u16 bit_D : 1;
            /* 0x0A */ u16 bit_E : 1;
            /* 0x0A */ u16 bit_F : 1;
        } s;
        /* 0x0A */ u16 asByte;
    } unk_0A;
    /* 0x0C */ VibratoSubStruct vibrato;
    /* 0x1A */ s16 delay;
    /* 0x1C */ s16 gateDelay;
    /* 0x1E */ s16 delay2;
    /* 0x20 */ u16 portamentoTime;
    /* 0x22 */ s16 transposition; // #semitones added to play commands
                                  // (seq instruction encoding only allows referring to the limited range
                                  // 0..0x3F; this makes 0x40..0x7F accessible as well)
    /* 0x24 */ s16 shortNoteDefaultDelay;
    /* 0x26 */ s16 lastDelay;
    /* 0x28 */ AdsrSettings adsr;
    /* 0x30 */ Portamento portamento;
    /* 0x3C */ Note* note;
    /* 0x40 */ f32 freqScale;
    /* 0x44 */ f32 bend;
    /* 0x48 */ f32 velocitySquare2;
    /* 0x4C */ f32 velocitySquare; // not sure which one of those corresponds to the sm64 original
    /* 0x50 */ f32 noteVelocity;
    /* 0x54 */ f32 noteFreqScale;
    /* 0x58 */ struct Instrument* instrument;
    /* 0x5C */ struct TunedSample* tunedSample;
    /* 0x60 */ SequenceChannel* channel;
    /* 0x64 */ SeqScriptState scriptState;
    /* 0x80 */ AudioListItem listItem;
} SequenceLayer; // size = 0x90

void AudioScript_SequenceChannelDisable(SequenceChannel* channel);
void AudioScript_SequencePlayerDisableAsFinished(SequencePlayer* seqPlayer);
void AudioScript_SequencePlayerDisable(SequencePlayer* seqPlayer);
void AudioScript_ProcessSequences(s32 arg0);
void AudioScript_SkipForwardSequence(SequencePlayer* seqPlayer);
void AudioScript_ResetSequencePlayer(SequencePlayer* seqPlayer);
void AudioScript_InitSequencePlayerChannels(s32 seqPlayerIndex);
void AudioScript_InitSequencePlayers(void);

typedef enum AudioCustomFunctions {
    /* 0x00 */ AUDIO_CUSTOM_FUNCTION_SEQ_0,
    /* 0x01 */ AUDIO_CUSTOM_FUNCTION_SEQ_1,
    /* 0x02 */ AUDIO_CUSTOM_FUNCTION_SEQ_2,
    /* 0x03 */ AUDIO_CUSTOM_FUNCTION_SEQ_3,
    /* 0xFE */ AUDIO_CUSTOM_FUNCTION_SYNTH = 0xFE,
    /* 0xFF */ AUDIO_CUSTOM_FUNCTION_REVERB
} AudioCustomFunctions;

typedef void (*AudioCustomUpdateFunction)(void);
typedef u32 (*AudioCustomSeqFunction)(s8 value, SequenceChannel* channel);
typedef void* (*AudioCustomReverbFunction)(struct Sample*, s32, s8, s32);
typedef Acmd* (*AudioCustomSynthFunction)(Acmd*, s32, s32);

extern AudioCustomUpdateFunction gAudioCustomUpdateFunction;
extern AudioCustomSeqFunction gAudioCustomSeqFunction;
extern AudioCustomReverbFunction gAudioCustomReverbFunction;
extern AudioCustomSynthFunction gAudioCustomSynthFunction;

#endif
