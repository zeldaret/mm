#ifndef Z64OCARINA_H
#define Z64OCARINA_H

#include "ultra64.h"

typedef enum {
    /*  0 */ OCARINA_SONG_SONATA,
    /*  1 */ OCARINA_SONG_GORON_LULLABY,
    /*  2 */ OCARINA_SONG_NEW_WAVE,
    /*  3 */ OCARINA_SONG_ELEGY,
    /*  4 */ OCARINA_SONG_OATH,
    /*  5 */ OCARINA_SONG_SARIAS,
    /*  6 */ OCARINA_SONG_TIME,
    /*  7 */ OCARINA_SONG_HEALING,
    /*  8 */ OCARINA_SONG_EPONAS,
    /*  9 */ OCARINA_SONG_SOARING,
    /* 10 */ OCARINA_SONG_STORMS,
    /* 11 */ OCARINA_SONG_SUNS,
    /* 12 */ OCARINA_SONG_INVERTED_TIME,
    /* 13 */ OCARINA_SONG_DOUBLE_TIME,
    /* 14 */ OCARINA_SONG_GORON_LULLABY_INTRO,
    /* 15 */ OCARINA_SONG_WIND_FISH_HUMAN, // "Ballad of the Wind Fish"
    /* 16 */ OCARINA_SONG_WIND_FISH_GORON,
    /* 17 */ OCARINA_SONG_WIND_FISH_ZORA,
    /* 18 */ OCARINA_SONG_WIND_FISH_DEKU,
    /* 19 */ OCARINA_SONG_EVAN_PART1,
    /* 20 */ OCARINA_SONG_EVAN_PART2,
    /* 21 */ OCARINA_SONG_ZELDAS_LULLABY,
    /* 22 */ OCARINA_SONG_SCARECROW,
    /* 23 */ OCARINA_SONG_TERMINA_WALL,
    /* 24 */ OCARINA_SONG_MAX,
    /* 24 */ OCARINA_SONG_SCARECROW_LONG = OCARINA_SONG_MAX
} OcarinaSongId;

typedef enum {
    /*  0 */ OCARINA_BTN_A,
    /*  1 */ OCARINA_BTN_C_DOWN,
    /*  2 */ OCARINA_BTN_C_RIGHT,
    /*  3 */ OCARINA_BTN_C_LEFT,
    /*  4 */ OCARINA_BTN_C_UP,
    /* -1 */ OCARINA_BTN_INVALID = 0xFF
} OcarinaButtonIndex;

// Uses scientific pitch notation relative to middle C
// https://en.wikipedia.org/wiki/Scientific_pitch_notation
typedef enum {
    /* 0x0 */ OCARINA_PITCH_C4,
    /* 0x1 */ OCARINA_PITCH_DFLAT4,
    /* 0x2 */ OCARINA_PITCH_D4,
    /* 0x3 */ OCARINA_PITCH_EFLAT4,
    /* 0x4 */ OCARINA_PITCH_E4,
    /* 0x5 */ OCARINA_PITCH_F4,
    /* 0x6 */ OCARINA_PITCH_GFLAT4,
    /* 0x7 */ OCARINA_PITCH_G4,
    /* 0x8 */ OCARINA_PITCH_AFLAT4,
    /* 0x9 */ OCARINA_PITCH_A4,
    /* 0xA */ OCARINA_PITCH_BFLAT4,
    /* 0xB */ OCARINA_PITCH_B4,
    /* 0xC */ OCARINA_PITCH_C5,
    /* 0xD */ OCARINA_PITCH_DFLAT5,
    /* 0xE */ OCARINA_PITCH_D5,
    /* 0xF */ OCARINA_PITCH_EFLAT5,
    /* -1  */ OCARINA_PITCH_NONE = 0xFF
} OcarinaPitch;

// Mainly set by func_80152CAC in z_message.c
typedef enum {
    /* 0  */ OCARINA_INSTRUMENT_OFF,
    /* 1  */ OCARINA_INSTRUMENT_DEFAULT,
    /* 2  */ OCARINA_INSTRUMENT_FEMALE_VOICE,
    /* 3  */ OCARINA_INSTRUMENT_WHISTLING_FLUTE,
    /* 4  */ OCARINA_INSTRUMENT_HARP,
    /* 5  */ OCARINA_INSTRUMENT_IKANA_KING,
    /* 6  */ OCARINA_INSTRUMENT_TATL,
    /* 7  */ OCARINA_INSTRUMENT_GORON_DRUMS,
    /* 8  */ OCARINA_INSTRUMENT_ZORA_GUITAR,
    /* 9  */ OCARINA_INSTRUMENT_DEKU_PIPES,
    /* 10 */ OCARINA_INSTRUMENT_MONKEY,
    /* 11 */ OCARINA_INSTRUMENT_DEKU_TRUMPET, // Pull out ocarina for captured monkey
    /* 12 */ OCARINA_INSTRUMENT_ELDER_GORON_DRUMS,
    /* 13 */ OCARINA_INSTRUMENT_PIANO,
    /* 14 */ OCARINA_INSTRUMENT_BASS_GUITAR,
    /* 15 */ OCARINA_INSTRUMENT_BABY_SINGING,
    /* 16 */ OCARINA_INSTRUMENT_AMPLIFIED_GUITAR, // Related to (gSaveContext.weekEventReg[41] & 0x20)
} OcarinaInstrumentId;

typedef enum {
    /* 0  */ OCARINA_RECORD_OFF,
    /* 1  */ OCARINA_RECORD_SCARECROW_LONG,
    /* 2  */ OCARINA_RECORD_SCARECROW_SPAWN,
    /* -1 */ OCARINA_RECORD_REJECTED = 0xFF
} OcarinaRecordingState;

/**
 * BFlat4Flag Note:
 * Flag for resolving whether (pitch = OCARINA_PITCH_BFLAT4) 
 * gets mapped to either C_RIGHT and C_LEFT
 * 
 * This is required as C_RIGHT and C_LEFT are the only notes
 * that map to two semitones apart (NOTE_A4 and NOTE_B4)
 *      0x40 - BTN_Z is pressed to lower note by a semitone
 *      0x80 - BTN_R is pressed to raise note by a semitone
 */ 

typedef struct {
    /* 0x0 */ u8 pitch; // number of semitones above middle C
    /* 0x2 */ u16 length; // number of frames the note is sustained
    /* 0x4 */ u8 volume;
    /* 0x5 */ u8 vibrato;
    /* 0x6 */ s8 bend; // frequency multiplicative offset from the pitch defined by pitch
    /* 0x7 */ u8 BFlat4Flag; // See note above
} OcarinaNote;  // size = 0x8

typedef struct {
    /* 0x0 */ u8 numButtons;
    /* 0x1 */ u8 buttonIndex[8];
} OcarinaSongButtons; // size = 0x9

typedef struct {
    /* 0x0 */ u8 buttonIndex;
    /* 0x1 */ u8 state;   // original name: "status"
    /* 0x2 */ u8 pos;     // original name: "locate"
} OcarinaStaff; // size = 0x3

#endif
