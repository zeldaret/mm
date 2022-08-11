#include "global.h"

typedef struct {
    /* 0x0 */ s8 x;
    /* 0x1 */ s8 y;
} OcarinaControlStick; // size = 0x2

typedef struct {
    /* 0x0 */ u16 playerIO;
    /* 0x2 */ u16 channelMask;
    /* 0x4 */ u8 channelIO[3 * 33 + 1];
} NatureAmbienceDataIO; // size = 0x68

typedef struct {
    /* 0x0 */ Vec3f* pos;
    /* 0x4 */ f32 freqScale;
    /* 0x8 */ s8 reverbAdd;
} SfxSettings; // size = 0x9

typedef struct {
    /* 0x0 */ f32 volume;
    /* 0x4 */ f32 freqScale;
    /* 0x8 */ s8 reverb;
    /* 0x9 */ s8 panSigned;
    /* 0xA */ s8 stereoBits;
    /* 0xB */ u8 filter;
    /* 0xC */ u8 combFilterGain;
    /* 0xD */ u8 zVolume;
} SfxChannelState; // size = 0xE

typedef enum {
    /* 0x0 */ SFX_CHANNEL_PLAYER0, // SfxPlayerBank
    /* 0x1 */ SFX_CHANNEL_PLAYER1,
    /* 0x2 */ SFX_CHANNEL_PLAYER2,
    /* 0x3 */ SFX_CHANNEL_ITEM0, // SfxItemBank
    /* 0x4 */ SFX_CHANNEL_ITEM1,
    /* 0x5 */ SFX_CHANNEL_ENV0, // SfxEnvironmentBank
    /* 0x6 */ SFX_CHANNEL_ENV1,
    /* 0x7 */ SFX_CHANNEL_ENV2,
    /* 0x8 */ SFX_CHANNEL_ENEMY0, // SfxEnemyBank
    /* 0x9 */ SFX_CHANNEL_ENEMY1,
    /* 0xA */ SFX_CHANNEL_ENEMY2,
    /* 0xB */ SFX_CHANNEL_SYSTEM0, // SfxSystemBank
    /* 0xC */ SFX_CHANNEL_SYSTEM1,
    /* 0xD */ SFX_CHANNEL_OCARINA, // SfxOcarinaBank
    /* 0xE */ SFX_CHANNEL_VOICE0,  // SfxVoiceBank
    /* 0xF */ SFX_CHANNEL_VOICE1
} SfxChannelIndex; // playerIndex = 2

// Global IO ports for sequences, 8 global ports per seqPlayer
typedef enum {
    /* 0x0 */ SEQ_PLAYER_IO_PORT_0,
    /* 0x1 */ SEQ_PLAYER_IO_PORT_1,
    /* 0x2 */ SEQ_PLAYER_IO_PORT_2,
    /* 0x3 */ SEQ_PLAYER_IO_PORT_3,
    /* 0x4 */ SEQ_PLAYER_IO_PORT_4,
    /* 0x5 */ SEQ_PLAYER_IO_PORT_5,
    /* 0x6 */ SEQ_PLAYER_IO_PORT_6,
    /* 0x7 */ SEQ_PLAYER_IO_PORT_7,
} SeqPlayerIOPort;

typedef struct {
    /* 0x0 */ f32 value;
    /* 0x4 */ f32 target;
    /* 0x8 */ f32 step;
    /* 0xC */ s32 remainingFrames;
} FreqLerp; // size = 0x10

s32 AudioOcarina_MemoryGameNextNote(void);
s32 Audio_SetGanonsTowerBgmVolume(u8 targetVolume);
void func_801A3238(s8 playerIndex, u16 seqId, u8 fadeTimer, s8 arg3, u8 arg4);

// Sfx bss
SfxSettings sSfxSettings[8];
u8 sSfxSettingsFlags;
f32 sTwoSemitonesLoweredFreq;
s8 sSfxIncreasedReverb;
f32 sSfxSyncedVolume;
f32 sSfxSyncedVolumeForMetalEffects;
f32 sSfxSyncedFreq;
FreqLerp sRiverFreqScaleLerp;
FreqLerp sWaterfallFreqScaleLerp;
f32 sSfxAdjustedFreq;
s8 sSfxCustomReverb;
u8 sRiverSoundMainBgmVol;
u8 sRiverSoundMainBgmCurrentVol;
u8 sRiverSoundMainBgmLower;
u8 sRiverSoundMainBgmRestore;
u8 sGanonsTowerVol;
f32* sSfxVolumeCur;
f32 sSfxVolumeTarget;
f32 sSfxVolumeRate;
u16 sSceneSeqId1;
SfxChannelState sSfxChannelState[16];

// Sequence bss
u8 D_801FD3A8;
u8 D_801FD3A9;
u8 sRiverSoundBgmTimer;
u8 sFanfareState;
u16 sFanfareSeqId;
u8 sMuteOnlySfxAndNatureSeq;
u8 sAllPlayersMutedExceptOcaAndSys;
u8 sAudioPauseState;
u8 sSpatialSeqIsActive[4];
u8 sSequenceFilter[8 * 4];
u8 sIsFinalHoursOrSoaring;
u8 sObjSoundFanfareSeqId;
u8 sObjSoundFanfareRequested;
Vec3f sObjSoundFanfarePos;
u8 sObjSoundPlayerIndex;
Vec3f sObjSoundPos;
s16 sObjSoundFlags;
f32 sObjSoundMinDist;
f32 sObjSoundMaxDist;
f32 sObjSoundMaxVol;
f32 sObjSoundMinVol;
Vec3f sSpatialSeqNoFilterPos;
Vec3f sSpatialSeqFilterPos;
f32 sSpatialSeqMaxDist;
u8 sSpatialSeqSeqId;
u8 sSpatialSeqFlags;
u8 D_801FD432;
u8 sSpatialSubBgmFadeTimer;
u8 D_801FD434;
u8 sSpatialSeqPlayerIndex;
u8 sSpatialSeqFadeTimer;
u16 D_801FD438;

// AudioOcarina bss
OcarinaStaff sPlayingStaff;
OcarinaStaff sPlaybackStaff;
OcarinaStaff sRecordingStaff;
u32 sOcarinaUpdateTaskStart;
OcarinaControlStick sOcarinaInputStickRel;
u32 sOcarinaInputButtonCur;
u32 sOcarinaInputButtonStart;
u32 sOcarinaInputButtonPrev;
s32 sOcarinaInputButtonPress;
u8 sOcarinaDisableTimer;
u8 sOcarinaUnused;
u8 sOcarinaHasStartedSong;
u8 sFirstOcarinaSongIndex;
u8 sLastOcarinaSongIndex;
u32 sOcarinaAvailableSongFlags;
u8 sOcarinaStaffPlayingPos;
u16 sMusicStaffPos[OCARINA_SONG_MAX];
u16 sMusicStaffCurHeldLength[OCARINA_SONG_MAX];
u16 sMusicStaffExpectedLength[OCARINA_SONG_MAX];
u8 sMusicStaffExpectedPitch[OCARINA_SONG_MAX]; // Next required pitch in song playback
u8 D_801FD518[OCARINA_SONG_MAX];
u32 D_801FD530[OCARINA_SONG_MAX];
OcarinaNote sScarecrowsLongSongSecondNote;
u16 sCustomSequencePc;

// Sfx Data
// If the Sfx Bank has more than 255 values (max value of u8)
u8 gIsLargeSfxBank[] = {
    true, false, true, true, false, false, true,
};
u8 D_801D6608[] = {
    true, true, true, true, true, false, true,
};
u8 gChannelsPerBank[4][7] = {
    { 3, 2, 3, 3, 2, 1, 2 },
    { 3, 2, 2, 2, 2, 2, 2 },
    { 3, 2, 2, 2, 2, 2, 2 },
    { 4, 1, 0, 0, 2, 2, 2 },
};
u8 gUsedChannelsPerBank[4][7] = {
    { 3, 2, 3, 2, 2, 1, 1 },
    { 3, 1, 1, 1, 2, 1, 1 },
    { 3, 1, 1, 1, 2, 1, 1 },
    { 2, 1, 0, 0, 1, 1, 1 },
};
f32 sGiantsMaskFreq = 0.89167805f; // Around 2 semitones down in pitch
s8 sGiantsMaskReverbAdd = 0x40;
f32 sWaterWheelVolume = 0.65f;
f32 gSfxVolume = 1.0f;
s8 sSfxTimer = 20;
s8 sSfxTimerLerpRange2 = 30;
s8 sSfxTimerLerpRange1 = 20;
f32 sBehindScreenZ[2] = { -15.0f, -65.0f }; // Unused Remnant of OoT
u8 sAudioIncreasingTranspose = 0;           // Remnant of OoT, only unsed in unused functions
u8 gMorphaTransposeTable[16] = { 0, 0, 0, 1, 1, 2, 4, 6, 8, 8, 8, 8, 8, 8, 8, 8 }; // Unused Remnant of OoT
u8 sPrevChargeLevel = 0;
f32 sChargeLevelsSfxFreq[] = { 1.0f, 1.12246f, 1.33484f, 1.33484f };
f32 sCurChargeLevelSfxFreq = 1.0f;
u8 sGanonsTowerLevelsVol[] = {
    127, 80, 75, 73, 70, 68, 65, 60 // volumes
};
u8 sEnterGanonsTowerTimer = 0;
u16 sSfxVolumeDuration = 0;

// System Data
s8 sSoundMode = SOUNDMODE_STEREO;
s8 sAudioIsWindowOpen = false;
s8 sAudioCutsceneFlag = false;
s8 sSpecReverb = 0;
s8 sAudioEnvReverb = 0;
s8 sAudioCodeReverb = 0;

// Sequence Data
u8 sPrevSeqMode = 0;
f32 sAudioEnemyDist = 0.0f;
s8 sAudioEnemyVol = 127;
u16 sPrevMainBgmSeqId = NA_BGM_DISABLED;
u8 sBgmPlayerIOPort7 = 0;
u8 sSceneSeqId2 = NA_BGM_GENERAL_SFX;
u32 sNumFramesStill = 0;
u32 sNumFramesMoving = 0;
u8 sAudioBaseFilter = 0;
u8 sAudioExtraFilter = 0;
u8 sAudioBaseFilter2 = 0;
u8 sAudioExtraFilter2 = 0;
s8 gUnderwaterSfxReverbAdd = 0;
Vec3f* sRiverSoundBgmPos = NULL;
f32 sRiverSoundXZDistToPlayer = 2000.0f;
u8 sObjSoundMainBgmSeqId = NA_BGM_GENERAL_SFX;
u8 sSeqFlags[] = {
    0x3,  // NA_BGM_GENERAL_SFX
    0x1,  // NA_BGM_NATURE_AMBIENCE
    0x1,  // NA_BGM_TERMINA_FIELD
    0x8,  // NA_BGM_CHASE
    0,    // NA_BGM_MAJORAS_THEME
    0,    // NA_BGM_CLOCK_TOWER
    0x1,  // NA_BGM_STONE_TOWER_TEMPLE
    0x1,  // NA_BGM_INV_STONE_TOWER_TEMPLE
    0x2,  // NA_BGM_FAILURE_0
    0x2,  // NA_BGM_FAILURE_1
    0,    // NA_BGM_HAPPY_MASK_SALESMAN
    0,    // NA_BGM_SONG_OF_HEALING
    0x1,  // NA_BGM_SWAMP_REGION
    0,    // NA_BGM_ALIEN_INVASION
    0x2,  // NA_BGM_SWAMP_CRUISE
    0,    // NA_BGM_SHARPS_CURSE
    0x1,  // NA_BGM_GREAT_BAY_REGION
    0x1,  // NA_BGM_IKANA_REGION
    0,    // NA_BGM_DEKU_KING
    0x1,  // NA_BGM_MOUNTAIN_REGION
    0,    // NA_BGM_PIRATES_FORTRESS
    0,    // NA_BGM_CLOCK_TOWN_DAY_1
    0,    // NA_BGM_CLOCK_TOWN_DAY_2
    0,    // NA_BGM_CLOCK_TOWN_DAY_3
    0x40, // NA_BGM_FILE_SELECT
    0x10, // NA_BGM_CLEAR_EVENT
    0,    // NA_BGM_ENEMY
    0x8,  // NA_BGM_BOSS
    0x1,  // NA_BGM_WOODFALL_TEMPLE
    0,    // NA_BGM_MARKET
    0,    // NA_BGM_OPENING
    0x20, // NA_BGM_INSIDE_A_HOUSE
    0x2,  // NA_BGM_GAME_OVER
    0,    // NA_BGM_CLEAR_BOSS
    0x2,  // NA_BGM_GET_ITEM
    0x2,  // NA_BGM_GATE_OPEN
    0x2,  // NA_BGM_GET_HEART
    0x8,  // NA_BGM_TIMED_MINI_GAME
    0,    // NA_BGM_GORON_RACE
    0,    // NA_BGM_MUSIC_BOX_HOUSE
    0,    // NA_BGM_FAIRY_FOUNTAIN
    0,    // NA_BGM_ZELDAS_LULLABY
    0,    // NA_BGM_ROSA_SISTERS
    0x2,  // NA_BGM_OPEN_CHEST
    0,    // NA_BGM_MARINE_RESEARCH_LAB
    0x40, // NA_BGM_GIANTS_THEME
    0,    // NA_BGM_SONG_OF_STORMS
    0,    // NA_BGM_ROMANI_RANCH
    0,    // NA_BGM_GORON_VILLAGE
    0,    // NA_BGM_MAYORS_OFFICE
    0x2,  // NA_BGM_OCA_EPONA
    0x2,  // NA_BGM_OCA_SUNS
    0x2,  // NA_BGM_OCA_TIME
    0x2,  // NA_BGM_OCA_STORM
    0x10, // NA_BGM_ZORA_HALL
    0x2,  // NA_BGM_GET_NEW_MASK
    0x8,  // NA_BGM_MINI_BOSS
    0x2,  // NA_BGM_GET_SMALL_ITEM
    0,    // NA_BGM_ASTRAL_OBSERVATORY
    0x1,  // NA_BGM_CAVERN
    0x11, // NA_BGM_MILK_BAR
    0x2,  // NA_BGM_ZELDA_APPEAR
    0,    // NA_BGM_SARIAS_SONG
    0,    // NA_BGM_GORON_GOAL
    0,    // NA_BGM_HORSE
    0,    // NA_BGM_HORSE_GOAL
    0,    // NA_BGM_INGO
    0,    // NA_BGM_KOTAKE_POTION_SHOP
    0x20, // NA_BGM_SHOP
    0x2,  // NA_BGM_OWL
    0x20, // NA_BGM_MINI_GAME
    0x2,  // NA_BGM_OCA_SOARING
    0x2,  // NA_BGM_OCA_HEALING
    0x2,  // NA_BGM_INVERTED_SONG_OF_TIME
    0x2,  // NA_BGM_SONG_OF_DOUBLE_TIME
    0x2,  // NA_BGM_SONATA_OF_AWAKENING
    0x2,  // NA_BGM_GORON_LULLABY
    0x2,  // NA_BGM_NEW_WAVE_BOSSA_NOVA
    0x2,  // NA_BGM_ELEGY_OF_EMPTINESS
    0x2,  // NA_BGM_OATH_TO_ORDER
    0,    // NA_BGM_SWORD_TRAINING_HALL
    0x2,  // NA_BGM_GORON_LULLABY_INTRO
    0x2,  // NA_BGM_OCA_FAIRY
    0x2,  // NA_BGM_BREMEN_MARCH
    0x2,  // NA_BGM_BALLAD_OF_THE_WIND_FISH
    0x8,  // NA_BGM_SONG_OF_SOARING
    0,    // NA_BGM_MILK_BAR_DUPLICATE
    0,    // NA_BGM_FINAL_HOURS
    0x2,  // NA_BGM_MIKAU_RIFF
    0x2,  // NA_BGM_MIKAU_FINALE
    0,    // NA_BGM_FROG_SONG
    0x2,  // NA_BGM_OCA_SONATA
    0x2,  // NA_BGM_OCA_LULLABY
    0x2,  // NA_BGM_OCA_NEW_WAVE
    0x2,  // NA_BGM_OCA_ELEGY
    0x2,  // NA_BGM_OCA_OATH
    0,    // NA_BGM_MAJORAS_LAIR
    0x2,  // NA_BGM_OCA_LULLABY_INTRO
    0x2,  // NA_BGM_OCA_GUITAR_BASS_SESSION
    0x2,  // NA_BGM_PIANO_SESSION
    0x2,  // NA_BGM_INDIGO_GO_SESSION
    0x1,  // NA_BGM_SNOWHEAD_TEMPLE
    0x1,  // NA_BGM_GREAT_BAY_TEMPLE
    0x2,  // NA_BGM_NEW_WAVE_SAXOPHONE
    0x2,  // NA_BGM_NEW_WAVE_VOCAL
    0,    // NA_BGM_MAJORAS_WRATH
    0,    // NA_BGM_MAJORAS_INCARNATION
    0,    // NA_BGM_MAJORAS_MASK
    0x2,  // NA_BGM_BASS_PLAY
    0x2,  // NA_BGM_DRUMS_PLAY
    0x2,  // NA_BGM_PIANO_PLAY
    0x1,  // NA_BGM_IKANA_CASTLE
    0,    // NA_BGM_GATHERING_GIANTS
    0x4,  // NA_BGM_KAMARO_DANCE
    0,    // NA_BGM_CREMIA_CARRIAGE
    0x2,  // NA_BGM_KEATON_QUIZ
    0,    // NA_BGM_END_CREDITS_1
    0,    // NA_BGM_OPENING_LOOP
    0,    // NA_BGM_TITLE_THEME
    0x2,  // NA_BGM_DUNGEON_APPEAR
    0x2,  // NA_BGM_WOODFALL_CLEAR
    0x2,  // NA_BGM_SNOWHEAD_CLEAR
    0,    //
    0,    // NA_BGM_INTO_THE_MOON
    0,    // NA_BGM_GOODBYE_GIANT
    0,    // NA_BGM_TATL_AND_TAEL
    0,    // NA_BGM_MOONS_DESTRUCTION
    0,    // NA_BGM_END_CREDITS_2
};

s8 sSpecReverbs[20] = {
    0, 0, 0, 0, 0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

NatureAmbienceDataIO sNatureAmbienceData[20] = {
    // natureSeqId: 0
    {
        0xC0FF, // PlayerIO Data
        0xC0FE, // Channel Mask
        {
            // Channel 0
            NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_0),
            NATURE_IO_STREAM_0_PORT3(0),

            // Channel 1
            NATURE_IO_CRITTER_0_TYPE(NATURE_CRITTER_09),
            NATURE_IO_CRITTER_0_BEND_PITCH(64),
            NATURE_IO_CRITTER_0_NUM_LAYERS(0),
            NATURE_IO_CRITTER_0_PORT5(32),

            // Channel 2
            NATURE_IO_CRITTER_1_TYPE(NATURE_CRITTER_04),
            NATURE_IO_CRITTER_1_BEND_PITCH(0),
            NATURE_IO_CRITTER_1_NUM_LAYERS(1),
            NATURE_IO_CRITTER_1_PORT5(16),

            // Channel 3
            NATURE_IO_CRITTER_2_TYPE(NATURE_CRITTER_10),
            NATURE_IO_CRITTER_2_BEND_PITCH(112),
            NATURE_IO_CRITTER_2_NUM_LAYERS(1),
            NATURE_IO_CRITTER_2_PORT5(48),

            // Channel 4
            NATURE_IO_CRITTER_3_TYPE(NATURE_CRITTER_03),
            NATURE_IO_CRITTER_3_BEND_PITCH(127),
            NATURE_IO_CRITTER_3_NUM_LAYERS(0),
            NATURE_IO_CRITTER_3_PORT5(16),

            // Channel 5
            NATURE_IO_CRITTER_4_TYPE(NATURE_CRITTER_00),
            NATURE_IO_CRITTER_4_BEND_PITCH(127),
            NATURE_IO_CRITTER_4_NUM_LAYERS(1),
            NATURE_IO_CRITTER_4_PORT5(16),

            // Channel 6
            NATURE_IO_CRITTER_5_TYPE(NATURE_CRITTER_01),
            NATURE_IO_CRITTER_5_BEND_PITCH(127),
            NATURE_IO_CRITTER_5_NUM_LAYERS(3),
            NATURE_IO_CRITTER_5_PORT5(16),

            // End
            NATURE_IO_ENTRIES_END,
        },
    },

    // natureSeqId: 1
    {
        0xC0FF, // PlayerIO Data
        0xC0FE, // Channel Mask
        {
            // Channel 0
            NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_0),
            NATURE_IO_STREAM_0_PORT3(0),

            // Channel 1
            NATURE_IO_CRITTER_0_TYPE(NATURE_CRITTER_04),
            NATURE_IO_CRITTER_0_BEND_PITCH(64),
            NATURE_IO_CRITTER_0_NUM_LAYERS(0),
            NATURE_IO_CRITTER_0_PORT5(32),

            // Channel 2
            NATURE_IO_CRITTER_1_TYPE(NATURE_CRITTER_16),
            NATURE_IO_CRITTER_1_BEND_PITCH(0),
            NATURE_IO_CRITTER_1_NUM_LAYERS(1),
            NATURE_IO_CRITTER_1_PORT5(16),

            // Channel 3
            NATURE_IO_CRITTER_2_TYPE(NATURE_CRITTER_12),
            NATURE_IO_CRITTER_2_BEND_PITCH(112),
            NATURE_IO_CRITTER_2_NUM_LAYERS(0),
            NATURE_IO_CRITTER_2_PORT5(48),

            // Channel 4
            NATURE_IO_CRITTER_3_TYPE(NATURE_CRITTER_15),
            NATURE_IO_CRITTER_3_BEND_PITCH(127),
            NATURE_IO_CRITTER_3_NUM_LAYERS(1),
            NATURE_IO_CRITTER_3_PORT5(16),

            // Channel 5
            NATURE_IO_CRITTER_4_TYPE(NATURE_CRITTER_06),
            NATURE_IO_CRITTER_4_BEND_PITCH(127),
            NATURE_IO_CRITTER_4_NUM_LAYERS(1),
            NATURE_IO_CRITTER_4_PORT5(16),

            // Channel 6
            NATURE_IO_CRITTER_5_TYPE(NATURE_CRITTER_01),
            NATURE_IO_CRITTER_5_BEND_PITCH(127),
            NATURE_IO_CRITTER_5_NUM_LAYERS(3),
            NATURE_IO_CRITTER_5_PORT5(16),

            // End
            NATURE_IO_ENTRIES_END,
        },
    },

    // natureSeqId: 2
    {
        0xC0FF, // PlayerIO Data
        0xC0FE, // Channel Mask
        {
            // Channel 0
            NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_0),
            NATURE_IO_STREAM_0_PORT3(0),

            // Channel 1
            NATURE_IO_CRITTER_0_TYPE(NATURE_CRITTER_04),
            NATURE_IO_CRITTER_0_BEND_PITCH(64),
            NATURE_IO_CRITTER_0_NUM_LAYERS(0),
            NATURE_IO_CRITTER_0_PORT5(48),

            // Channel 2
            NATURE_IO_CRITTER_1_TYPE(NATURE_CRITTER_10),
            NATURE_IO_CRITTER_1_BEND_PITCH(0),
            NATURE_IO_CRITTER_1_NUM_LAYERS(1),
            NATURE_IO_CRITTER_1_PORT5(16),

            // Channel 3
            NATURE_IO_CRITTER_2_TYPE(NATURE_CRITTER_04),
            NATURE_IO_CRITTER_2_BEND_PITCH(48),
            NATURE_IO_CRITTER_2_NUM_LAYERS(1),
            NATURE_IO_CRITTER_2_PORT5(32),

            // Channel 4
            NATURE_IO_CRITTER_3_TYPE(NATURE_CRITTER_03),
            NATURE_IO_CRITTER_3_BEND_PITCH(127),
            NATURE_IO_CRITTER_3_NUM_LAYERS(0),
            NATURE_IO_CRITTER_3_PORT5(16),

            // Channel 5
            NATURE_IO_CRITTER_4_TYPE(NATURE_CRITTER_01),
            NATURE_IO_CRITTER_4_BEND_PITCH(64),
            NATURE_IO_CRITTER_4_NUM_LAYERS(1),
            NATURE_IO_CRITTER_4_PORT5(0),

            // Channel 6
            NATURE_IO_CRITTER_5_TYPE(NATURE_CRITTER_04),
            NATURE_IO_CRITTER_5_BEND_PITCH(127),
            NATURE_IO_CRITTER_5_NUM_LAYERS(0),
            NATURE_IO_CRITTER_5_PORT5(63),

            // End
            NATURE_IO_ENTRIES_END,
        },
    },

    // natureSeqId: 3
    {
        0xC0FF, // PlayerIO Data
        0xC0FE, // Channel Mask
        {
            // Channel 0
            NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_0),
            NATURE_IO_STREAM_0_PORT3(0),

            // Channel 1
            NATURE_IO_CRITTER_0_TYPE(NATURE_CRITTER_09),
            NATURE_IO_CRITTER_0_BEND_PITCH(64),
            NATURE_IO_CRITTER_0_NUM_LAYERS(0),
            NATURE_IO_CRITTER_0_PORT5(32),

            // Channel 2
            NATURE_IO_CRITTER_1_TYPE(NATURE_CRITTER_04),
            NATURE_IO_CRITTER_1_BEND_PITCH(64),
            NATURE_IO_CRITTER_1_NUM_LAYERS(0),
            NATURE_IO_CRITTER_1_PORT5(48),

            // Channel 3
            NATURE_IO_CRITTER_2_TYPE(NATURE_CRITTER_10),
            NATURE_IO_CRITTER_2_BEND_PITCH(32),
            NATURE_IO_CRITTER_2_NUM_LAYERS(1),
            NATURE_IO_CRITTER_2_PORT5(32),

            // Channel 4
            NATURE_IO_CRITTER_3_TYPE(NATURE_CRITTER_14),
            NATURE_IO_CRITTER_3_BEND_PITCH(64),
            NATURE_IO_CRITTER_3_NUM_LAYERS(1),
            NATURE_IO_CRITTER_3_PORT5(16),

            // Channel 5
            NATURE_IO_CRITTER_4_TYPE(NATURE_CRITTER_00),
            NATURE_IO_CRITTER_4_BEND_PITCH(127),
            NATURE_IO_CRITTER_4_NUM_LAYERS(1),
            NATURE_IO_CRITTER_4_PORT5(16),

            // Channel 6
            NATURE_IO_CRITTER_5_TYPE(NATURE_CRITTER_01),
            NATURE_IO_CRITTER_5_BEND_PITCH(127),
            NATURE_IO_CRITTER_5_NUM_LAYERS(3),
            NATURE_IO_CRITTER_5_PORT5(16),

            // End
            NATURE_IO_ENTRIES_END,
        },
    },

    // natureSeqId: 4
    {
        0xC0FF, // PlayerIO Data
        0xC0FE, // Channel Mask
        {
            // Channel 0
            NATURE_IO_STREAM_0_TYPE(0),
            NATURE_IO_STREAM_0_PORT3(0),

            // Channel 1
            NATURE_IO_CRITTER_0_TYPE(NATURE_CRITTER_04),
            NATURE_IO_CRITTER_0_BEND_PITCH(64),
            NATURE_IO_CRITTER_0_NUM_LAYERS(0),
            NATURE_IO_CRITTER_0_PORT5(32),

            // Channel 2
            NATURE_IO_CRITTER_1_TYPE(NATURE_CRITTER_02),
            NATURE_IO_CRITTER_1_BEND_PITCH(64),
            NATURE_IO_CRITTER_1_NUM_LAYERS(1),
            NATURE_IO_CRITTER_1_PORT5(16),

            // Channel 3
            NATURE_IO_CRITTER_2_TYPE(NATURE_CRITTER_12),
            NATURE_IO_CRITTER_2_BEND_PITCH(112),
            NATURE_IO_CRITTER_2_NUM_LAYERS(1),
            NATURE_IO_CRITTER_2_PORT5(48),

            // Channel 4
            NATURE_IO_CRITTER_3_TYPE(NATURE_CRITTER_13),
            NATURE_IO_CRITTER_3_BEND_PITCH(64),
            NATURE_IO_CRITTER_3_NUM_LAYERS(1),
            NATURE_IO_CRITTER_3_PORT5(16),

            // Channel 5
            NATURE_IO_CRITTER_4_TYPE(NATURE_CRITTER_01),
            NATURE_IO_CRITTER_4_BEND_PITCH(64),
            NATURE_IO_CRITTER_4_NUM_LAYERS(1),
            NATURE_IO_CRITTER_4_PORT5(16),

            // Channel 6
            NATURE_IO_CRITTER_5_TYPE(NATURE_CRITTER_02),
            NATURE_IO_CRITTER_5_BEND_PITCH(112),
            NATURE_IO_CRITTER_5_NUM_LAYERS(0),
            NATURE_IO_CRITTER_5_PORT5(48),

            // Channel 14
            NATURE_IO_RAIN_PORT4(63),

            // End
            NATURE_IO_ENTRIES_END,

        },
    },

    // natureSeqId: 5
    {
        0xC0FF, // PlayerIO Data
        0xC0FE, // Channel Mask
        {
            // Channel 0
            NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_0),
            NATURE_IO_STREAM_0_PORT3(0),

            // Channel 1
            NATURE_IO_CRITTER_0_TYPE(NATURE_CRITTER_09),
            NATURE_IO_CRITTER_0_BEND_PITCH(64),
            NATURE_IO_CRITTER_0_NUM_LAYERS(0),
            NATURE_IO_CRITTER_0_PORT5(32),

            // Channel 2
            NATURE_IO_CRITTER_1_TYPE(NATURE_CRITTER_04),
            NATURE_IO_CRITTER_1_BEND_PITCH(0),
            NATURE_IO_CRITTER_1_NUM_LAYERS(1),
            NATURE_IO_CRITTER_1_PORT5(16),

            // Channel 3
            NATURE_IO_CRITTER_2_TYPE(NATURE_CRITTER_10),
            NATURE_IO_CRITTER_2_BEND_PITCH(112),
            NATURE_IO_CRITTER_2_NUM_LAYERS(1),
            NATURE_IO_CRITTER_2_PORT5(48),

            // Channel 4
            NATURE_IO_CRITTER_3_TYPE(NATURE_CRITTER_13),
            NATURE_IO_CRITTER_3_BEND_PITCH(127),
            NATURE_IO_CRITTER_3_NUM_LAYERS(0),
            NATURE_IO_CRITTER_3_PORT5(63),

            // Channel 5
            NATURE_IO_CRITTER_4_TYPE(NATURE_CRITTER_00),
            NATURE_IO_CRITTER_4_BEND_PITCH(127),
            NATURE_IO_CRITTER_4_NUM_LAYERS(1),
            NATURE_IO_CRITTER_4_PORT5(16),

            // Channel 6
            NATURE_IO_CRITTER_5_TYPE(NATURE_CRITTER_01),
            NATURE_IO_CRITTER_5_BEND_PITCH(127),
            NATURE_IO_CRITTER_5_NUM_LAYERS(3),
            NATURE_IO_CRITTER_5_PORT5(16),

            // End
            NATURE_IO_ENTRIES_END,
        },
    },

    // natureSeqId: 6
    {
        0xC0FF, // PlayerIO Data
        0xC0FE, // Channel Mask
        {
            // Channel 0
            NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_0),
            NATURE_IO_STREAM_0_PORT3(0),

            // Channel 1
            NATURE_IO_CRITTER_0_TYPE(NATURE_CRITTER_11),
            NATURE_IO_CRITTER_0_BEND_PITCH(112),
            NATURE_IO_CRITTER_0_NUM_LAYERS(0),
            NATURE_IO_CRITTER_0_PORT5(48),

            // Channel 2
            NATURE_IO_CRITTER_1_TYPE(NATURE_CRITTER_15),
            NATURE_IO_CRITTER_1_BEND_PITCH(112),
            NATURE_IO_CRITTER_1_NUM_LAYERS(0),
            NATURE_IO_CRITTER_1_PORT5(63),

            // Channel 3
            NATURE_IO_CRITTER_2_TYPE(NATURE_CRITTER_11),
            NATURE_IO_CRITTER_2_BEND_PITCH(48),
            NATURE_IO_CRITTER_2_NUM_LAYERS(1),
            NATURE_IO_CRITTER_2_PORT5(16),

            // Channel 4
            NATURE_IO_CRITTER_3_TYPE(NATURE_CRITTER_14),
            NATURE_IO_CRITTER_3_BEND_PITCH(48),
            NATURE_IO_CRITTER_3_NUM_LAYERS(1),
            NATURE_IO_CRITTER_3_PORT5(16),

            // Channel 5
            NATURE_IO_CRITTER_4_TYPE(NATURE_CRITTER_11),
            NATURE_IO_CRITTER_4_BEND_PITCH(127),
            NATURE_IO_CRITTER_4_NUM_LAYERS(0),
            NATURE_IO_CRITTER_4_PORT5(32),

            // Channel 6
            NATURE_IO_CRITTER_5_TYPE(NATURE_CRITTER_02),
            NATURE_IO_CRITTER_5_BEND_PITCH(127),
            NATURE_IO_CRITTER_5_NUM_LAYERS(0),
            NATURE_IO_CRITTER_5_PORT5(48),

            // End
            NATURE_IO_ENTRIES_END,
        },
    },

    // natureSeqId: 7
    {
        0xC001, // PlayerIO Data
        0xC000, // Channel Mask
        {
            // Channel 0
            NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_0),
            NATURE_IO_STREAM_0_PORT3(0),

            // End
            NATURE_IO_ENTRIES_END,
        },
    },

    // natureSeqId: 8
    {
        0xC003, // PlayerIO Data
        0xC000, // Channel Mask
        {
            // Channel 0
            NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_0),
            NATURE_IO_STREAM_0_PORT3(0),

            // Channel 1
            NATURE_IO_CRITTER_0_TYPE(NATURE_CRITTER_01),
            NATURE_IO_CRITTER_0_BEND_PITCH(127),
            NATURE_IO_CRITTER_0_NUM_LAYERS(3),
            NATURE_IO_CRITTER_0_PORT5(16),

            // End
            NATURE_IO_ENTRIES_END,
        },
    },

    // natureSeqId: 9
    {
        0xC00F, // PlayerIO Data
        0xC000, // Channel Mask
        {
            // Channel 0
            NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_0),
            NATURE_IO_STREAM_0_PORT3(0),

            // Channel 1
            NATURE_IO_CRITTER_0_TYPE(NATURE_CRITTER_16),
            NATURE_IO_CRITTER_0_BEND_PITCH(0),
            NATURE_IO_CRITTER_0_NUM_LAYERS(2),
            NATURE_IO_CRITTER_0_PORT5(16),

            // Channel 2
            NATURE_IO_CRITTER_1_TYPE(NATURE_CRITTER_12),
            NATURE_IO_CRITTER_1_BEND_PITCH(112),
            NATURE_IO_CRITTER_1_NUM_LAYERS(0),
            NATURE_IO_CRITTER_1_PORT5(48),

            // Channel 3
            NATURE_IO_CRITTER_2_TYPE(NATURE_CRITTER_15),
            NATURE_IO_CRITTER_2_BEND_PITCH(127),
            NATURE_IO_CRITTER_2_NUM_LAYERS(1),
            NATURE_IO_CRITTER_2_PORT5(16),

            // End
            NATURE_IO_ENTRIES_END,
        },
    },

    // natureSeqId: 10
    {
        0xC081, // PlayerIO Data
        0xC000, // Channel Mask
        {
            // Channel 0
            NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_1),
            NATURE_IO_STREAM_0_PORT3(8),

            // Channel 7
            NATURE_IO_CRITTER_6_TYPE(NATURE_CRITTER_11),
            NATURE_IO_CRITTER_6_BEND_PITCH(112),
            NATURE_IO_CRITTER_6_NUM_LAYERS(2),
            NATURE_IO_CRITTER_6_PORT5(32),

            // End
            NATURE_IO_ENTRIES_END,
        },
    },

    // natureSeqId: 11
    {
        0xC00F, // PlayerIO Data
        0xC000, // Channel Mask
        {
            // Channel 0
            NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_3),
            NATURE_IO_STREAM_0_PORT3(8),

            // Channel 1
            NATURE_IO_CRITTER_0_TYPE(NATURE_CRITTER_01),
            NATURE_IO_CRITTER_0_BEND_PITCH(127),
            NATURE_IO_CRITTER_0_NUM_LAYERS(3),
            NATURE_IO_CRITTER_0_PORT5(16),

            // Channel 2
            NATURE_IO_CRITTER_1_TYPE(NATURE_CRITTER_00),
            NATURE_IO_CRITTER_1_BEND_PITCH(127),
            NATURE_IO_CRITTER_1_NUM_LAYERS(2),
            NATURE_IO_CRITTER_1_PORT5(16),

            // Channel 3
            NATURE_IO_CRITTER_2_TYPE(NATURE_CRITTER_06),
            NATURE_IO_CRITTER_2_BEND_PITCH(127),
            NATURE_IO_CRITTER_2_NUM_LAYERS(1),
            NATURE_IO_CRITTER_2_PORT5(16),

            // End
            NATURE_IO_ENTRIES_END,
        },
    },

    // natureSeqId: 12
    {
        0xC007, // PlayerIO Data
        0xC000, // Channel Mask
        {
            // Channel 0
            NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_0),

            // Channel 1
            NATURE_IO_CRITTER_0_TYPE(NATURE_CRITTER_00),
            NATURE_IO_CRITTER_0_BEND_PITCH(127),
            NATURE_IO_CRITTER_0_NUM_LAYERS(1),
            NATURE_IO_CRITTER_0_PORT5(16),

            // Channel 2
            NATURE_IO_CRITTER_1_TYPE(NATURE_CRITTER_01),
            NATURE_IO_CRITTER_1_BEND_PITCH(127),
            NATURE_IO_CRITTER_1_NUM_LAYERS(3),
            NATURE_IO_CRITTER_1_PORT5(16),

            // End
            NATURE_IO_ENTRIES_END,
        },
    },

    // natureSeqId: 13
    {
        0xC003, // PlayerIO Data
        0xC000, // Channel Mask
        {
            // Channel 0
            NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_0),
            NATURE_IO_STREAM_0_PORT3(0),

            // Channel 1
            NATURE_IO_CRITTER_0_TYPE(NATURE_CRITTER_04),
            NATURE_IO_CRITTER_0_BEND_PITCH(0),
            NATURE_IO_CRITTER_0_NUM_LAYERS(1),
            NATURE_IO_CRITTER_0_PORT5(16),

            // End
            NATURE_IO_ENTRIES_END,
        },
    },

    // natureSeqId: 14
    {
        0xC003, // PlayerIO Data
        0xC000, // Channel Mask
        {
            // Channel 0
            NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_0),
            NATURE_IO_STREAM_0_PORT3(0),

            // Channel 1
            NATURE_IO_CRITTER_0_TYPE(NATURE_CRITTER_04),
            NATURE_IO_CRITTER_0_BEND_PITCH(0),
            NATURE_IO_CRITTER_0_NUM_LAYERS(1),
            NATURE_IO_CRITTER_0_PORT5(16),

            // End
            NATURE_IO_ENTRIES_END,
        },
    },

    // natureSeqId: 15
    {
        0xC003, // PlayerIO Data
        0xC000, // Channel Mask
        {
            // Channel 0
            NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_0),
            NATURE_IO_STREAM_0_PORT3(0),

            // Channel 1
            NATURE_IO_CRITTER_0_TYPE(NATURE_CRITTER_04),
            NATURE_IO_CRITTER_0_BEND_PITCH(0),
            NATURE_IO_CRITTER_0_NUM_LAYERS(1),
            NATURE_IO_CRITTER_0_PORT5(16),

            // End
            NATURE_IO_ENTRIES_END,
        },
    },

    // natureSeqId: 16
    {
        0xC003, // PlayerIO Data
        0xC000, // Channel Mask
        {
            // Channel 0
            NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_0),
            NATURE_IO_STREAM_0_PORT3(0),

            // Channel 1
            NATURE_IO_CRITTER_0_TYPE(NATURE_CRITTER_04),
            NATURE_IO_CRITTER_0_BEND_PITCH(0),
            NATURE_IO_CRITTER_0_NUM_LAYERS(1),
            NATURE_IO_CRITTER_0_PORT5(16),

            // End
            NATURE_IO_ENTRIES_END,
        },
    },

    // natureSeqId: 17
    {
        0xC003, // PlayerIO Data
        0xC000, // Channel Mask
        {
            // Channel 0
            NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_0),
            NATURE_IO_STREAM_0_PORT3(0),

            // Channel 1
            NATURE_IO_CRITTER_0_TYPE(NATURE_CRITTER_04),
            NATURE_IO_CRITTER_0_BEND_PITCH(0),
            NATURE_IO_CRITTER_0_NUM_LAYERS(1),
            NATURE_IO_CRITTER_0_PORT5(16),

            // End
            NATURE_IO_ENTRIES_END,
        },
    },

    // natureSeqId: 18
    {
        0xC000, // PlayerIO Data
        0xC000, // Channel Mask
        {
            // Channel 0
            NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_0),

            // End
            NATURE_IO_ENTRIES_END,
        },
    },

    // natureSeqId: 19
    {
        0xC003, // PlayerIO Data
        0xC000, // Channel Mask
        {
            NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_0),
            NATURE_IO_STREAM_0_PORT3(0),

            // Channel 1
            NATURE_IO_CRITTER_0_TYPE(NATURE_CRITTER_04),
            NATURE_IO_CRITTER_0_BEND_PITCH(0),
            NATURE_IO_CRITTER_0_NUM_LAYERS(1),
            NATURE_IO_CRITTER_0_PORT5(16),

            // End
            NATURE_IO_ENTRIES_END,

        },
    },
};

// AudioOcarina Data
u8 sIsOcarinaInputEnabled = false;
s8 sOcarinaInstrumentId = OCARINA_INSTRUMENT_OFF;
u8 sCurOcarinaPitch = OCARINA_PITCH_NONE;
u8 sPrevOcarinaPitch = OCARINA_PITCH_C4;
u8 sCurOcarinaButtonIndex = OCARINA_BTN_A;
u8 sMusicStaffPrevPitch = OCARINA_PITCH_C4;
f32 sCurOcarinaBendFreq = 1.0f;
f32 sDefaultOcarinaVolume = 87.0f / 127.0f;
s8 sCurOcarinaBendIndex = 0;
s8 sCurOcarinaVolume = 87;
s8 sCurOcarinaVibrato = 0;
u8 sPlaybackState = 0;
u8 sPlaybackStaffStopPos = 0xFF;
u8 sPlaybackStaffStartPos = 0xFF;
u32 sOcarinaFlags = 0;
s32 sPlaybackNoteTimer = 0;
u16 sPlaybackNotePos = 0;
u16 sPlaybackStaffPos = 0;
u32 sPrevOcarinaWithMusicStaffFlags = 0; // Stores sOcarinaFlags but never used
u8 sPlaybackPitch = OCARINA_PITCH_NONE;  // Pitch + PitchFlags
u8 sNotePlaybackVolume = 0;
u8 sNotePlaybackVibrato = 0;
s8 sNotePlaybackBend = 0;
f32 sRelativeNotePlaybackBend = 1.0f;
f32 sRelativeNotePlaybackVolume = 1.0f;
u32 sOcarinaPlaybackTaskStart = 0;
u32 sOcarinaWallCounter = 0;
u8 sCurOcarinaSongWithoutMusicStaff[8] = {
    OCARINA_PITCH_C4, OCARINA_PITCH_C4, OCARINA_PITCH_C4, OCARINA_PITCH_C4,
    OCARINA_PITCH_C4, OCARINA_PITCH_C4, OCARINA_PITCH_C4, OCARINA_PITCH_C4,
};
u8 sOcarinaWithoutMusicStaffPos = 0;
u8 sOcarinaSongStartingPos = 0;

u8 sButtonToPitchMap[5] = {
    OCARINA_PITCH_D4, // OCARINA_BTN_A
    OCARINA_PITCH_F4, // OCARINA_BTN_C_DOWN
    OCARINA_PITCH_A4, // OCARINA_BTN_C_RIGHT
    OCARINA_PITCH_B4, // OCARINA_BTN_C_LEFT
    OCARINA_PITCH_D5, // OCARINA_BTN_C_UP
};

u8 sOcarinaMemoryGameAppendPos = 0;
u8 sOcarinaMemoryGameEndPos = 0;
u8 sOcarinaMemoryGameNumNotes[] = { 5, 6, 8 };
OcarinaNote sOcarinaSongNotes[OCARINA_SONG_MAX][20] = {
    // OCARINA_SONG_SONATA
    {
        { OCARINA_PITCH_D5, 19, 92, 0, 0, 0 },
        { OCARINA_PITCH_B4, 19, 90, 0, 0, 0 },
        { OCARINA_PITCH_D5, 19, 90, 0, 0, 0 },
        { OCARINA_PITCH_B4, 38, 90, 0, 0, 0 },
        { OCARINA_PITCH_D4, 39, 92, 0, 0, 0 },
        { OCARINA_PITCH_A4, 76, 89, 0, 0, 0 },
        { OCARINA_PITCH_D4, 77, 82, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 86, 0, 0, 0 },
    },

    // OCARINA_SONG_GORON_LULLABY
    {
        { OCARINA_PITCH_D4, 41, 80, 0, 0, 0 },
        { OCARINA_PITCH_A4, 40, 72, 0, 0, 0 },
        { OCARINA_PITCH_B4, 39, 84, 0, 0, 0 },
        { OCARINA_PITCH_D4, 42, 76, 0, 0, 0 },
        { OCARINA_PITCH_A4, 40, 84, 0, 0, 0 },
        { OCARINA_PITCH_B4, 39, 76, 0, 0, 0 },
        { OCARINA_PITCH_A4, 41, 84, 0, 0, 0 },
        { OCARINA_PITCH_D4, 80, 76, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 40, 76, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 66, 0, 0, 0 },
    },

    // OCARINA_SONG_NEW_WAVE
    {
        { OCARINA_PITCH_B4, 64, 74, 0, 0, 0 },
        { OCARINA_PITCH_D5, 13, 88, 0, 0, 0 },
        { OCARINA_PITCH_B4, 12, 90, 0, 0, 0 },
        { OCARINA_PITCH_A4, 78, 88, 0, 0, 0 },
        { OCARINA_PITCH_F4, 12, 76, 0, 0, 0 },
        { OCARINA_PITCH_B4, 13, 76, 0, 0, 0 },
        { OCARINA_PITCH_A4, 114, 76, 6, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // OCARINA_SONG_ELEGY
    {
        { OCARINA_PITCH_A4, 85, 93, 0, 0, 0 },
        { OCARINA_PITCH_B4, 43, 91, 0, 0, 0 },
        { OCARINA_PITCH_A4, 43, 93, 0, 0, 0 },
        { OCARINA_PITCH_F4, 21, 88, 0, 0, 0 },
        { OCARINA_PITCH_A4, 21, 88, 0, 0, 0 },
        { OCARINA_PITCH_D5, 43, 101, 0, 0, 0 },
        { OCARINA_PITCH_B4, 85, 95, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 94, 0, 0, 0 },
    },

    // OCARINA_SONG_OATH
    {
        { OCARINA_PITCH_A4, 97, 104, 0, 0, 0 },
        { OCARINA_PITCH_F4, 48, 88, 0, 0, 0 },
        { OCARINA_PITCH_D4, 49, 78, 0, 0, 0 },
        { OCARINA_PITCH_F4, 49, 78, 0, 0, 0 },
        { OCARINA_PITCH_A4, 48, 94, 0, 0, 0 },
        { OCARINA_PITCH_D5, 97, 100, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 96, 0, 0, 0 },

    },

    // OCARINA_SONG_SARIAS
    {
        { OCARINA_PITCH_F4, 17, 84, 0, 0, 0 },
        { OCARINA_PITCH_A4, 17, 88, 0, 0, 0 },
        { OCARINA_PITCH_B4, 34, 80, 0, 0, 0 },
        { OCARINA_PITCH_F4, 17, 84, 0, 0, 0 },
        { OCARINA_PITCH_A4, 17, 88, 0, 0, 0 },
        { OCARINA_PITCH_B4, 136, 80, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // OCARINA_SONG_TIME
    {
        { OCARINA_PITCH_A4, 32, 84, 0, 0, 0 },
        { OCARINA_PITCH_D4, 65, 88, 0, 0, 0 },
        { OCARINA_PITCH_F4, 33, 80, 0, 0, 0 },
        { OCARINA_PITCH_A4, 32, 84, 0, 0, 0 },
        { OCARINA_PITCH_D4, 65, 88, 0, 0, 0 },
        { OCARINA_PITCH_F4, 99, 80, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // OCARINA_SONG_HEALING
    {
        { OCARINA_PITCH_B4, 32, 88, 0, 0, 0 },
        { OCARINA_PITCH_A4, 33, 88, 0, 0, 0 },
        { OCARINA_PITCH_F4, 33, 69, 0, 0, 0 },
        { OCARINA_PITCH_B4, 32, 94, 0, 0, 0 },
        { OCARINA_PITCH_A4, 33, 88, 0, 0, 0 },
        { OCARINA_PITCH_F4, 121, 86, 2, 0, 0 },
        { OCARINA_PITCH_NONE, 10, 84, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // OCARINA_SONG_EPONAS
    {
        { OCARINA_PITCH_D5, 18, 84, 0, 0, 0 },
        { OCARINA_PITCH_B4, 18, 88, 0, 0, 0 },
        { OCARINA_PITCH_A4, 72, 80, 0, 0, 0 },
        { OCARINA_PITCH_D5, 18, 84, 0, 0, 0 },
        { OCARINA_PITCH_B4, 18, 88, 0, 0, 0 },
        { OCARINA_PITCH_A4, 144, 80, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // OCARINA_SONG_SOARING
    {
        { OCARINA_PITCH_F4, 18, 84, 0, 0, 0 },
        { OCARINA_PITCH_B4, 18, 80, 0, 0, 0 },
        { OCARINA_PITCH_D5, 36, 94, 0, 0, 0 },
        { OCARINA_PITCH_F4, 18, 73, 0, 0, 0 },
        { OCARINA_PITCH_B4, 18, 76, 0, 0, 0 },
        { OCARINA_PITCH_D5, 108, 96, 2, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // OCARINA_SONG_STORMS
    {
        { OCARINA_PITCH_D4, 11, 84, 0, 0, 0 },
        { OCARINA_PITCH_F4, 11, 88, 0, 0, 0 },
        { OCARINA_PITCH_D5, 45, 80, 0, 0, 0 },
        { OCARINA_PITCH_D4, 11, 84, 0, 0, 0 },
        { OCARINA_PITCH_F4, 11, 88, 0, 0, 0 },
        { OCARINA_PITCH_D5, 90, 80, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // OCARINA_SONG_SUNS
    {
        { OCARINA_PITCH_A4, 12, 84, 0, 0, 0 },
        { OCARINA_PITCH_F4, 13, 88, 0, 0, 0 },
        { OCARINA_PITCH_D5, 29, 80, 2, 0, 0 },
        { OCARINA_PITCH_NONE, 9, 84, 0, 0, 0 },
        { OCARINA_PITCH_A4, 12, 84, 0, 0, 0 },
        { OCARINA_PITCH_F4, 13, 88, 0, 0, 0 },
        { OCARINA_PITCH_D5, 120, 80, 3, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // OCARINA_SONG_INVERTED_TIME
    {
        { OCARINA_PITCH_F4, 32, 84, 0, 0, 0 },
        { OCARINA_PITCH_D4, 65, 88, 0, 0, 0 },
        { OCARINA_PITCH_A4, 33, 80, 0, 0, 0 },
        { OCARINA_PITCH_F4, 32, 84, 0, 0, 0 },
        { OCARINA_PITCH_D4, 65, 88, 0, 0, 0 },
        { OCARINA_PITCH_A4, 99, 80, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // OCARINA_SONG_DOUBLE_TIME
    {
        { OCARINA_PITCH_A4, 29, 84, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 3, 84, 0, 0, 0 },
        { OCARINA_PITCH_A4, 30, 84, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 3, 84, 0, 0, 0 },
        { OCARINA_PITCH_D4, 29, 84, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 3, 84, 0, 0, 0 },
        { OCARINA_PITCH_D4, 30, 84, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 3, 84, 0, 0, 0 },
        { OCARINA_PITCH_F4, 29, 84, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 3, 84, 0, 0, 0 },
        { OCARINA_PITCH_F4, 99, 84, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 0, 0, 0, 0 },
    },

    // OCARINA_SONG_GORON_LULLABY_INTRO
    {
        { OCARINA_PITCH_D4, 32, 78, 0, 0, 0 },
        { OCARINA_PITCH_A4, 33, 90, 0, 0, 0 },
        { OCARINA_PITCH_B4, 33, 87, 0, 0, 0 },
        { OCARINA_PITCH_D4, 32, 92, 0, 0, 0 },
        { OCARINA_PITCH_A4, 33, 86, 0, 0, 0 },
        { OCARINA_PITCH_B4, 130, 80, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 66, 0, 0, 0 },
    },

    // OCARINA_SONG_WIND_FISH_HUMAN
    {
        { OCARINA_PITCH_D5, 89, 80, 0, 0, 0 },
        { OCARINA_PITCH_A4, 41, 72, 0, 0, 0 },
        { OCARINA_PITCH_B4, 22, 84, 0, 0, 0 },
        { OCARINA_PITCH_A4, 91, 76, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 30, 66, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 66, 0, 0, 0 },
    },

    // OCARINA_SONG_WIND_FISH_GORON
    {
        { OCARINA_PITCH_D4, 52, 80, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 3, 66, 0, 0, 0 },
        { OCARINA_PITCH_D4, 8, 72, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 3, 66, 0, 0, 0 },
        { OCARINA_PITCH_D4, 30, 84, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 3, 66, 0, 0, 0 },
        { OCARINA_PITCH_F4, 34, 76, 0, 0, 0 },
        { OCARINA_PITCH_D4, 52, 80, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 3, 66, 0, 0, 0 },
        { OCARINA_PITCH_D4, 8, 72, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 3, 66, 0, 0, 0 },
        { OCARINA_PITCH_D4, 30, 84, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 3, 66, 0, 0, 0 },
        { OCARINA_PITCH_A4, 34, 76, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 66, 0, 0, 0 },
    },

    // OCARINA_SONG_WIND_FISH_ZORA
    {
        { OCARINA_PITCH_D5, 11, 80, 0, 0, 0 },
        { OCARINA_PITCH_A4, 11, 72, 0, 0, 0 },
        { OCARINA_PITCH_F4, 11, 84, 0, 0, 0 },
        { OCARINA_PITCH_D4, 100, 76, 0, 0, 0 },
        { OCARINA_PITCH_D5, 11, 84, 0, 0, 0 },
        { OCARINA_PITCH_B4, 11, 76, 0, 0, 0 },
        { OCARINA_PITCH_A4, 11, 72, 0, 0, 0 },
        { OCARINA_PITCH_F4, 100, 84, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 66, 0, 0, 0 },
    },

    // OCARINA_SONG_WIND_FISH_DEKU
    {
        { OCARINA_PITCH_A4, 54, 80, 0, 0, 0 },
        { OCARINA_PITCH_D4, 77, 72, 0, 0, 0 },
        { OCARINA_PITCH_F4, 19, 84, 0, 0, 0 },
        { OCARINA_PITCH_B4, 20, 76, 0, 0, 0 },
        { OCARINA_PITCH_A4, 78, 84, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 66, 0, 0, 0 },
    },

    // OCARINA_SONG_EVAN_PART1
    {
        { OCARINA_PITCH_A4, 33, 100, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 3, 92, 0, 0, 0 },
        { OCARINA_PITCH_A4, 37, 104, 0, 0, 0 },
        { OCARINA_PITCH_F4, 24, 100, 0, 0, 0 },
        { OCARINA_PITCH_D4, 70, 97, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 3, 96, 0, 0, 0 },
        { OCARINA_PITCH_D4, 12, 93, 0, 0, 0 },
        { OCARINA_PITCH_F4, 12, 100, 0, 0, 0 },
        { OCARINA_PITCH_A4, 12, 62, 0, 0, 0 },
        { OCARINA_PITCH_D4, 170, 91, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 66, 0, 0, 0 },
    },

    // OCARINA_SONG_EVAN_PART2
    {
        { OCARINA_PITCH_B4, 33, 107, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 3, 100, 0, 0, 0 },
        { OCARINA_PITCH_B4, 37, 104, 0, 0, 0 },
        { OCARINA_PITCH_A4, 24, 97, 0, 0, 0 },
        { OCARINA_PITCH_F4, 70, 104, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 3, 104, 0, 0, 0 },
        { OCARINA_PITCH_F4, 12, 90, 0, 0, 0 },
        { OCARINA_PITCH_A4, 12, 96, 0, 0, 0 },
        { OCARINA_PITCH_B4, 12, 81, 0, 0, 0 },
        { OCARINA_PITCH_F4, 170, 66, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 66, 0, 0, 0 },
    },

    // OCARINA_SONG_ZELDAS_LULLABY
    {
        { OCARINA_PITCH_B4, 51, 84, 0, 0, 0 },
        { OCARINA_PITCH_D5, 25, 88, 0, 0, 0 },
        { OCARINA_PITCH_A4, 78, 80, 0, 0, 0 },
        { OCARINA_PITCH_B4, 51, 84, 0, 0, 0 },
        { OCARINA_PITCH_D5, 25, 88, 0, 0, 0 },
        { OCARINA_PITCH_A4, 100, 80, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // OCARINA_SONG_SCARECROW_SPAWN
    {
        { OCARINA_PITCH_D4, 3, 0, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 255, 0, 0, 0 },
    },

    // OCARINA_SONG_TERMINA_WALL
    {
        { OCARINA_PITCH_D4, 3, 0, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 255, 0, 0, 0 },
    },
};

OcarinaNote sOoTOcarinaSongNotes[9][20] = {
    // Minuet
    {
        { OCARINA_PITCH_D4, 18, 86, 0, 0, 0 },
        { OCARINA_PITCH_D5, 18, 92, 0, 0, 0 },
        { OCARINA_PITCH_B4, 72, 86, 0, 0, 0 },
        { OCARINA_PITCH_A4, 18, 80, 0, 0, 0 },
        { OCARINA_PITCH_B4, 18, 88, 0, 0, 0 },
        { OCARINA_PITCH_A4, 144, 86, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 86, 0, 0, 0 },
    },

    // Bolero
    {
        { OCARINA_PITCH_F4, 15, 80, 0, 0, 0 },
        { OCARINA_PITCH_D4, 15, 72, 0, 0, 0 },
        { OCARINA_PITCH_F4, 15, 84, 0, 0, 0 },
        { OCARINA_PITCH_D4, 15, 76, 0, 0, 0 },
        { OCARINA_PITCH_A4, 15, 84, 0, 0, 0 },
        { OCARINA_PITCH_F4, 15, 74, 0, 0, 0 },
        { OCARINA_PITCH_A4, 15, 78, 0, 0, 0 },
        { OCARINA_PITCH_F4, 135, 66, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 66, 0, 0, 0 },
    },

    // Serenade
    {
        { OCARINA_PITCH_D4, 36, 60, 0, 0, 0 },
        { OCARINA_PITCH_F4, 36, 78, 0, 0, 0 },
        { OCARINA_PITCH_A4, 33, 82, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 3, 82, 0, 0, 0 },
        { OCARINA_PITCH_A4, 36, 84, 0, 0, 0 },
        { OCARINA_PITCH_B4, 144, 90, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // Requiem
    {
        { OCARINA_PITCH_D4, 45, 88, 0, 0, 0 },
        { OCARINA_PITCH_F4, 23, 86, 0, 0, 0 },
        { OCARINA_PITCH_D4, 22, 84, 0, 0, 0 },
        { OCARINA_PITCH_A4, 45, 86, 0, 0, 0 },
        { OCARINA_PITCH_F4, 45, 94, 0, 0, 0 },
        { OCARINA_PITCH_D4, 180, 94, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 94, 0, 0, 0 },
    },

    // Nocturne
    {
        { OCARINA_PITCH_B4, 36, 88, 0, 0, 0 },
        { OCARINA_PITCH_A4, 33, 84, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 3, 84, 0, 0, 0 },
        { OCARINA_PITCH_A4, 18, 82, 0, 0, 0 },
        { OCARINA_PITCH_D4, 18, 60, 0, 0, 0 },
        { OCARINA_PITCH_B4, 18, 90, 0, 0, 0 },
        { OCARINA_PITCH_A4, 18, 88, 0, 0, 0 },
        { OCARINA_PITCH_F4, 144, 96, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 96, 0, 0, 0 },
    },

    // Prelude
    {
        { OCARINA_PITCH_D5, 15, 84, 0, 0, 0 },
        { OCARINA_PITCH_A4, 45, 88, 0, 0, 0 },
        { OCARINA_PITCH_D5, 15, 88, 0, 0, 0 },
        { OCARINA_PITCH_A4, 15, 82, 0, 0, 0 },
        { OCARINA_PITCH_B4, 15, 86, 0, 0, 0 },
        { OCARINA_PITCH_D5, 60, 90, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 75, 90, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // Sarias
    {
        { OCARINA_PITCH_F4, 17, 84, 0, 0, 0 },
        { OCARINA_PITCH_A4, 17, 88, 0, 0, 0 },
        { OCARINA_PITCH_B4, 34, 80, 0, 0, 0 },
        { OCARINA_PITCH_F4, 17, 84, 0, 0, 0 },
        { OCARINA_PITCH_A4, 17, 88, 0, 0, 0 },
        { OCARINA_PITCH_B4, 136, 80, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // Zeldas Lullaby
    {
        { OCARINA_PITCH_B4, 51, 84, 0, 0, 0 },
        { OCARINA_PITCH_D5, 25, 88, 0, 0, 0 },
        { OCARINA_PITCH_A4, 78, 80, 0, 0, 0 },
        { OCARINA_PITCH_B4, 51, 84, 0, 0, 0 },
        { OCARINA_PITCH_D5, 25, 88, 0, 0, 0 },
        { OCARINA_PITCH_A4, 100, 80, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // Suns Song
    {
        { OCARINA_PITCH_A4, 12, 84, 0, 0, 0 },
        { OCARINA_PITCH_F4, 13, 88, 0, 0, 0 },
        { OCARINA_PITCH_D5, 29, 80, 2, 0, 0 },
        { OCARINA_PITCH_NONE, 9, 84, 0, 0, 0 },
        { OCARINA_PITCH_A4, 12, 84, 0, 0, 0 },
        { OCARINA_PITCH_F4, 13, 88, 0, 0, 0 },
        { OCARINA_PITCH_D5, 120, 80, 3, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },
};

u8 sOoTOcarinaSongsNumNotes[] = {
    6, // Minuet
    8, // Bolero
    5, // Serenade
    6, // Requiem
    7, // Nocturne
    6, // Prelude
    6, // Sarias
    6, // Zeldas Lullaby
    6, // Suns Song
};

OcarinaNote* sPlaybackSong = sOcarinaSongNotes[0];
u8 sFrogsSongNotes[14] = {
    OCARINA_BTN_A,       OCARINA_BTN_C_LEFT,  OCARINA_BTN_C_RIGHT, OCARINA_BTN_C_DOWN, OCARINA_BTN_C_LEFT,
    OCARINA_BTN_C_RIGHT, OCARINA_BTN_C_DOWN,  OCARINA_BTN_A,       OCARINA_BTN_C_DOWN, OCARINA_BTN_A,
    OCARINA_BTN_C_DOWN,  OCARINA_BTN_C_RIGHT, OCARINA_BTN_C_LEFT,  OCARINA_BTN_A,
};
u8* gFrogsSongPtr = sFrogsSongNotes;
u8 sRecordingState = OCARINA_RECORD_OFF;
u8 sRecordSongPos = 0;
u32 sOcarinaRecordTaskStart = 0;
u8 sRecordOcarinaPitch = 0;
u8 sRecordOcarinaVolume = 0;
u8 sRecordOcarinaVibrato = 0;
s8 sRecordOcarinaBendIndex = 0;
u8 sRecordOcarinaButtonIndex = 0;
u8 sPlayedOcarinaSongIndexPlusOne = 0;
u8 sMusicStaffNumNotesPerTest = 0;
u8 D_801D8530 = false;
u32 D_801D8534 = 0;
u8 sOcarinaDropInputTimer = 0;

OcarinaNote sScarecrowsLongSongNotes[108] = {
    { OCARINA_PITCH_NONE, 0, 0, 0, 0, 0 },
    { OCARINA_PITCH_NONE, 0, 0, 0, 0, 0 },
};

OcarinaNote* gScarecrowLongSongPtr = sScarecrowsLongSongNotes;
u8* gScarecrowSpawnSongPtr = (u8*)&sOcarinaSongNotes[OCARINA_SONG_SCARECROW_SPAWN];
OcarinaNote* sTerminaWallSongPtr = sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL];

u8 sPitchToButtonMap[16] = {
    OCARINA_BTN_A,                 // OCARINA_PITCH_C4
    OCARINA_BTN_A,                 // OCARINA_PITCH_DFLAT4
    OCARINA_BTN_A,                 // OCARINA_PITCH_D4
    OCARINA_BTN_A,                 // OCARINA_PITCH_EFLAT4
    OCARINA_BTN_C_DOWN,            // OCARINA_PITCH_E4
    OCARINA_BTN_C_DOWN,            // OCARINA_PITCH_F4
    OCARINA_BTN_C_DOWN,            // OCARINA_PITCH_GFLAT4
    OCARINA_BTN_C_RIGHT,           // OCARINA_PITCH_G4
    OCARINA_BTN_C_RIGHT,           // OCARINA_PITCH_AFLAT4
    OCARINA_BTN_C_RIGHT,           // OCARINA_PITCH_A4
    OCARINA_BTN_C_RIGHT_OR_C_LEFT, // OCARINA_PITCH_BFLAT4: Interface/Overlap between C_RIGHT and C_LEFT
    OCARINA_BTN_C_LEFT,            // OCARINA_PITCH_B4
    OCARINA_BTN_C_LEFT,            // OCARINA_PITCH_C5
    OCARINA_BTN_C_UP,              // OCARINA_PITCH_DFLAT5
    OCARINA_BTN_C_UP,              // OCARINA_PITCH_D5
    OCARINA_BTN_C_UP,              // OCARINA_PITCH_EFLAT5
};

// seqData written in the music macro language
// Only used in unused functions
// clang-format off
u8 sCustomSequenceScript[400] = {
    /* 0 */ 0xFE, // delay1
    /* 1 */ 0xFE, // delay1
    /* 2 */ 0xD3, 0x20, // mutebhv 0x20
    /* 4 */ 0xD7, 0x00, 0x01, // initchan 0x0001
    /* 7 */ 0xCC, 0x00, // ldi 0
    /* 9 */ 0x70, // stio 0
    /* 10 */ 0x90, 0x00, 22, // ldchan 0, chan0
    /* 13 */ 0xDB, 100, // vol 100
    /* 15 */ 0xDD, 120, // tempo 120

    // .sequence seq_loop
    /* 17 */ 0xFE, // delay1
    /* 18 */ 0x00, // testchan 0
    /* 19 */ 0xF3, -4, // rbeqz seq_loop
    /* 21 */ 0xFF, // end

    // .channel chan0
    /* 22 */ 0xC3, // short
    /* 23 */ 0x88, 0x00, 41, // ldlayer 0, layer0
    /* 26 */ 0x89, 0x00, 43, // ldlayer 1, layer1
    /* 29 */ 0xDF, 127, // vol 127
    /* 31 */ 0xE9, 0x0F, // notepri 0x0F
    /* 33 */ 0xDD, 55, // pan 55
    /* 35 */ 0xD4, 64, // reverb 64
    /* 37 */ 0xC1, 82, // instr 82

    // .channel chan_loop
    /* 39 */ 0xFE, // delay1
    /* 40 */ 0x80, // testlayer 0

    // (no end or loop; channel script seems to run into the note layers?)
    
    // .layer layer0
    /* 41 */ 0xF3, -4, // rbeqz chan_loop

    // .layer layer1
    /* 43 */ 0xFF, // end

    // .layer layer2?
    /* 44 */ 0xC2, -5, // transpose -5
    /* 46 */ 0xC0, 0, // ldelay 0 
    /* 48 */ 0xC1, 87, // shortvel 87 
    /* 50 */ 0xC9, 0, // shortgate 0
    /* 52 */ 0, // empty until the end
};
// clang-format on

OcarinaSongButtons gOcarinaSongButtons[OCARINA_SONG_MAX] = {
    // OCARINA_SONG_SONATA
    {
        7,
        {
            OCARINA_BTN_C_UP,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_UP,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_A,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_A,
        },
    },

    // OCARINA_SONG_GORON_LULLABY
    {
        8,
        {
            OCARINA_BTN_A,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_A,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_A,
        },
    },

    // OCARINA_SONG_NEW_WAVE
    {
        7,
        {
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_UP,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_RIGHT,
        },
    },

    // OCARINA_SONG_ELEGY
    {
        7,
        {
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_UP,
            OCARINA_BTN_C_LEFT,
        },
    },

    // OCARINA_SONG_OATH
    {
        6,
        {
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_A,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_UP,
        },
    },

    // OCARINA_SONG_SARIAS
    {
        6,
        {
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_LEFT,
        },
    },

    // OCARINA_SONG_TIME
    {
        6,
        {
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_A,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_A,
            OCARINA_BTN_C_DOWN,
        },
    },

    // OCARINA_SONG_HEALING
    {
        6,
        {
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_DOWN,
        },
    },

    // OCARINA_SONG_EPONAS
    {
        6,
        {
            OCARINA_BTN_C_UP,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_UP,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_RIGHT,
        },
    },

    // OCARINA_SONG_SOARING
    {
        6,
        {
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_UP,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_UP,
        },
    },

    // OCARINA_SONG_STORMS
    {
        6,
        {
            OCARINA_BTN_A,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_C_UP,
            OCARINA_BTN_A,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_C_UP,
        },
    },

    // OCARINA_SONG_SUNS
    {
        6,
        {
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_C_UP,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_C_UP,
        },
    },

    // OCARINA_SONG_INVERTED_TIME
    {
        6,
        {
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_A,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_A,
            OCARINA_BTN_C_RIGHT,
        },
    },

    // OCARINA_SONG_DOUBLE_TIME
    {
        6,
        {
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_A,
            OCARINA_BTN_A,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_C_DOWN,
        },
    },

    // OCARINA_SONG_GORON_LULLABY_INTRO
    {
        6,
        {
            OCARINA_BTN_A,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_A,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_LEFT,
        },
    },

    // OCARINA_SONG_WIND_FISH_HUMAN
    {
        4,
        {
            OCARINA_BTN_C_UP,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_RIGHT,
        },
    },

    // OCARINA_SONG_WIND_FISH_GORON
    {
        8,
        {
            OCARINA_BTN_A,
            OCARINA_BTN_A,
            OCARINA_BTN_A,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_A,
            OCARINA_BTN_A,
            OCARINA_BTN_A,
            OCARINA_BTN_C_RIGHT,
        },
    },

    // OCARINA_SONG_WIND_FISH_ZORA
    {
        8,
        {
            OCARINA_BTN_C_UP,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_A,
            OCARINA_BTN_C_UP,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_DOWN,
        },
    },

    // OCARINA_SONG_WIND_FISH_DEKU
    {
        5,
        {
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_A,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_RIGHT,
        },
    },

    // OCARINA_SONG_EVAN_PART1
    {
        8,
        {
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_A,
            OCARINA_BTN_A,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_A,
        },
    },

    // OCARINA_SONG_EVAN_PART2
    {
        8,
        {
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_DOWN,
        },
    },

    // OCARINA_SONG_ZELDAS_LULLABY
    {
        6,
        {
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_UP,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_UP,
            OCARINA_BTN_C_RIGHT,
        },
    },

    // OCARINA_SONG_SCARECROW_SPAWN
    {
        8,
        {
            OCARINA_BTN_A,
            OCARINA_BTN_A,
            OCARINA_BTN_A,
            OCARINA_BTN_A,
            OCARINA_BTN_A,
            OCARINA_BTN_A,
            OCARINA_BTN_A,
            OCARINA_BTN_A,
        },
    },

    // OCARINA_SONG_TERMINA_WALL
    {
        8,
        {
            OCARINA_BTN_A,
            OCARINA_BTN_C_DOWN,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_UP,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_DOWN,
        },
    },
};

const u16 gAudioEnvironmentalSfx[] = {
    NA_SE_EV_RIVER_STREAM - SFX_FLAG,   NA_SE_EV_WAVE - SFX_FLAG,
    NA_SE_EV_WATER_WALL_BIG - SFX_FLAG, NA_SE_EV_WATER_WALL - SFX_FLAG,
    NA_SE_EV_MAGMA_LEVEL - SFX_FLAG,    NA_SE_EV_MAGMA_LEVEL_M - SFX_FLAG,
    NA_SE_EV_MAGMA_LEVEL_L - SFX_FLAG,  NA_SE_EV_TORCH - SFX_FLAG,
    NA_SE_EV_FOUNTAIN - SFX_FLAG,       NA_SE_EV_DRAIN - SFX_FLAG,
    NA_SE_EV_CROWD - SFX_FLAG,          NA_SE_EV_WATER_CONVECTION - SFX_FLAG,
    NA_SE_EV_GORON_CHEER - SFX_FLAG,    NA_SE_EV_WATER_WALL_BIG_SILENT - SFX_FLAG,
    NA_SE_EV_WATER_BUBBLE - SFX_FLAG,   NA_SE_EV_COW_CRY_LV - SFX_FLAG,
    NA_SE_EV_MAKE_TURRET - SFX_FLAG,    NA_SE_EV_BOILED_WATER_S - SFX_FLAG,
    NA_SE_EV_BOILED_WATER_L - SFX_FLAG, NA_SE_EV_WAVE_S - SFX_FLAG,
    NA_SE_EV_WAVE_S - SFX_FLAG,         NA_SE_EV_WAVE_S - SFX_FLAG,
};

const u8 sIsOcarinaSongReserved[OCARINA_SONG_MAX] = {
    true,  // OCARINA_SONG_SONATA
    true,  // OCARINA_SONG_GORON_LULLABY
    true,  // OCARINA_SONG_NEW_WAVE
    true,  // OCARINA_SONG_ELEGY
    true,  // OCARINA_SONG_OATH
    false, // OCARINA_SONG_SARIAS
    true,  // OCARINA_SONG_TIME
    true,  // OCARINA_SONG_HEALING
    true,  // OCARINA_SONG_EPONAS
    true,  // OCARINA_SONG_SOARING
    true,  // OCARINA_SONG_STORMS
    false, // OCARINA_SONG_SUNS
    true,  // OCARINA_SONG_INVERTED_TIME
    true,  // OCARINA_SONG_DOUBLE_TIME
    true,  // OCARINA_SONG_GORON_LULLABY_INTRO
    false, // OCARINA_SONG_WIND_FISH_HUMAN
    false, // OCARINA_SONG_WIND_FISH_GORON
    false, // OCARINA_SONG_WIND_FISH_ZORA
    false, // OCARINA_SONG_WIND_FISH_DEKU
    true,  // OCARINA_SONG_EVAN_PART1
    true,  // OCARINA_SONG_EVAN_PART2
    false, // OCARINA_SONG_ZELDAS_LULLABY
    true,  // OCARINA_SONG_SCARECROW_SPAWN
    false, // OCARINA_SONG_TERMINA_WALL
};

const char sAudioOcarinaUnusedText0[] = "key step is too long !!! %d:%d>%d\n";
const char sAudioOcarinaUnusedText1[] = "You played %d Melody !!! (last step:%d)\n";
const char sAudioOcarinaUnusedText2[] = "pass 0\n";
const char sAudioOcarinaUnusedText3[] = "pass 1\n";
const char sAudioOcarinaUnusedText4[] = "pass 2\n";
const char sAudioOcarinaUnusedText5[] = "last key is bad !!! %d %d %02X %02X\n";
const char sAudioOcarinaUnusedText6[] = "last key step is too short !!! %d:%d %d<%d\n";
const char sAudioOcarinaUnusedText7[] = "check is over!!! %d %d %d\n";

void AudioOcarina_ReadControllerInput(void) {
    Input inputs[4];
    Input* input = &inputs[0];
    u32 ocarinaInputButtonPrev = sOcarinaInputButtonCur;

    Padmgr_GetInput2(inputs, 0);
    sOcarinaInputButtonCur = input->cur.button;
    sOcarinaInputButtonPrev = ocarinaInputButtonPrev;
    sOcarinaInputStickRel.x = input->rel.stick_x;
    sOcarinaInputStickRel.y = input->rel.stick_y;
}

/**
 * Looks up the frequency to bend the pitch by.
 * The pitch will bend up to a maximum of 2 semitones
 * in each direction giving a total range of 4 semitones
 */
f32 AudioOcarina_BendPitchTwoSemitones(s8 bendIndex) {
    s8 adjBendIndex;
    f32 bendFreq;

    if (bendIndex > 64) {
        adjBendIndex = 127;
    } else if (bendIndex < -64) {
        adjBendIndex = -128;
    } else if (bendIndex >= 0) {
        adjBendIndex = (bendIndex * 127) / 64;
    } else {
        adjBendIndex = (bendIndex * 128) / 64;
    }

    /**
     * index 128 is in the middle of the table and
     * contains the value 1.0f i.e. no bend
     * absolute indices above 128 will bend the pitch 2 semitones upwards
     * absolute indices below 128 will bend the pitch 2 semitones downwards
     */
    bendFreq = gBendPitchTwoSemitonesFrequencies[adjBendIndex + 128];
    return bendFreq;
}

/**
 * If an available song has been played, then return that song index
 * If the ocarina is on, but no song has been played then return 0xFE
 * If the ocarina is off, return 0xFF
 */
u8 AudioOcarina_GetPlayingState(void) {
    u8 playedOcarinaSongIndex;

    if (sPlayedOcarinaSongIndexPlusOne != 0) {
        playedOcarinaSongIndex = sPlayedOcarinaSongIndexPlusOne - 1;
        sPlayedOcarinaSongIndexPlusOne = 0;
    } else if (sOcarinaFlags != 0) {
        playedOcarinaSongIndex = 0xFE;
    } else {
        playedOcarinaSongIndex = 0xFF;
    }

    return playedOcarinaSongIndex;
}

u8 AudioOcarina_MapPitchToButton(u8 pitchAndBFlatFlag) {
    u8 buttonIndex = sPitchToButtonMap[pitchAndBFlatFlag & 0x3F];

    /**
     * Special case for bFlat4:
     * CRIGHT and CLEFT are the only two pitches that are 2 semitones apart
     * which are pitches A4 and B4 respectively
     * bFlat4 is in the middle of those two and is the only pitch that can not
     * be resolved between the two buttons without external information.
     * That information is stored as flags in pitch with the mask:
     * (pitchAndBFlatFlag & 0xC0)
     */
    if (buttonIndex == OCARINA_BTN_C_RIGHT_OR_C_LEFT) {
        if (pitchAndBFlatFlag & OCARINA_BUTTON_FLAG_BFLAT_RAISE) {
            return OCARINA_BTN_C_RIGHT;
        }
        // OCARINA_BUTTON_FLAG_BFLAT_LOWER
        return OCARINA_BTN_C_LEFT;
    }

    return buttonIndex;
}

void AudioOcarina_MapSongFromPitchToButton(u8 noteSongIndex, u8 buttonSongIndex, u8 numButtons) {
    u8 buttonSongPos = 0;
    u8 noteSongPos = 0;
    u8 pitch;

    while ((buttonSongPos < numButtons) && (noteSongPos < 16)) {
        pitch = sOcarinaSongNotes[noteSongIndex][noteSongPos++].pitch;

        if (pitch != OCARINA_PITCH_NONE) {
            gOcarinaSongButtons[buttonSongIndex].buttonIndex[buttonSongPos++] = sPitchToButtonMap[pitch];
        }
    }

    gOcarinaSongButtons[buttonSongIndex].numButtons = numButtons;
}

/**
 * Ocarina flags:
 * bitmask 0x3FFF:
 *      - Ocarina song id
 * bitmask 0xC000:
 *      - 0x0000: Limits the notes to 8 notes at a time. Not playing a correct song after 8 notes will cause an ocarina
 * error
 *      - 0x4000: (Identical to 0xC000)
 *      - 0x8000: Limits the notes to 1 note at a time. A single incorrect note will cause an ocarina error
 *      - 0xC000: Free-play, no limitations to the number of notes to play
 * bitmask 0x7FFF0000:
 *      - ocarina action (only used to make flags != 0)
 * bitmask 0x80000000:
 *      - unused (only used to make flags != 0)
 */

// The ocarina songs that can be performed at any time = 0x3FFF
#define OCARINA_SONGS_PLAYABLE_FLAGS                                                                                \
    ((1 << OCARINA_SONG_SONATA) | (1 << OCARINA_SONG_GORON_LULLABY) | (1 << OCARINA_SONG_NEW_WAVE) |                \
     (1 << OCARINA_SONG_ELEGY) | (1 << OCARINA_SONG_OATH) | (1 << OCARINA_SONG_SARIAS) | (1 << OCARINA_SONG_TIME) | \
     (1 << OCARINA_SONG_HEALING) | (1 << OCARINA_SONG_EPONAS) | (1 << OCARINA_SONG_SOARING) |                       \
     (1 << OCARINA_SONG_STORMS) | (1 << OCARINA_SONG_SUNS) | (1 << OCARINA_SONG_INVERTED_TIME) |                    \
     (1 << OCARINA_SONG_DOUBLE_TIME))

void AudioOcarina_Start(u32 ocarinaFlags) {
    u8 songIndex;

    if ((sOcarinaSongNotes[OCARINA_SONG_SCARECROW_SPAWN][1].volume != 0xFF) &&
        ((ocarinaFlags & OCARINA_SONGS_PLAYABLE_FLAGS) == OCARINA_SONGS_PLAYABLE_FLAGS)) {
        ocarinaFlags |= (1 << OCARINA_SONG_SCARECROW_SPAWN);
    }

    if ((ocarinaFlags == (0xC0000000 | OCARINA_SONGS_PLAYABLE_FLAGS)) &&
        (sOcarinaSongNotes[OCARINA_SONG_SCARECROW_SPAWN][1].volume != 0xFF)) {
        ocarinaFlags = (0xC0000000 | OCARINA_SONGS_PLAYABLE_FLAGS);
    }

    if ((ocarinaFlags == OCARINA_SONGS_PLAYABLE_FLAGS) &&
        (sOcarinaSongNotes[OCARINA_SONG_SCARECROW_SPAWN][1].volume != 0xFF)) {
        ocarinaFlags = OCARINA_SONGS_PLAYABLE_FLAGS;
    }

    if (ocarinaFlags != 0xFFFF) {
        sOcarinaFlags = 0x80000000 + ocarinaFlags;
        sFirstOcarinaSongIndex = 0;
        sLastOcarinaSongIndex = OCARINA_SONG_MAX;
        sOcarinaAvailableSongFlags = ocarinaFlags & 0xFFFFFF;
        sMusicStaffNumNotesPerTest = 8; // Ocarina Check
        sOcarinaHasStartedSong = false;
        sPlayedOcarinaSongIndexPlusOne = 0;
        sOcarinaStaffPlayingPos = 0;
        sPlayingStaff.state = AudioOcarina_GetPlayingState();
        sIsOcarinaInputEnabled = true;
        sPrevOcarinaWithMusicStaffFlags = 0;

        // Reset music staff song check
        for (songIndex = OCARINA_SONG_SONATA; songIndex <= OCARINA_SONG_EVAN_PART2; songIndex++) {
            for (sMusicStaffPos[songIndex] = 0;
                 sOcarinaSongNotes[songIndex][sMusicStaffPos[songIndex]].pitch == OCARINA_PITCH_NONE;) {
                sMusicStaffPos[songIndex]++;
            }

            sMusicStaffCurHeldLength[songIndex] = 0;
            sMusicStaffExpectedLength[songIndex] = 0;
            sMusicStaffExpectedPitch[songIndex] = 0;

            if (D_801D8530) {
                if ((1 << songIndex) & ocarinaFlags) {
                    D_801FD518[songIndex] = 0;
                } else {
                    D_801FD518[songIndex] = 0xFF;
                }
            }
        }

        if (ocarinaFlags & 0x80000000) {
            sMusicStaffNumNotesPerTest = 0; // Ocarina Playback
        }

        if (ocarinaFlags & 0x40000000) {
            sOcarinaWithoutMusicStaffPos = 0;
        }

        if (ocarinaFlags & 0xC0400000) {
            AudioOcarina_MapSongFromPitchToButton(OCARINA_SONG_SCARECROW_SPAWN, OCARINA_SONG_SCARECROW_SPAWN, 8);
        }
    } else {
        sOcarinaFlags = 0;
        sIsOcarinaInputEnabled = false;
    }
}

#undef OCARINA_SONGS_PLAYABLE_FLAGS

void AudioOcarina_SetSongStartingPos(void) {
    sOcarinaSongStartingPos = sOcarinaWithoutMusicStaffPos;
}

void AudioOcarina_StartAtSongStartingPos(u32 ocarinaFlags) {
    D_801D8530 = false;
    AudioOcarina_Start(ocarinaFlags);
    if (sOcarinaSongStartingPos != 0) {
        sOcarinaWithoutMusicStaffPos = sOcarinaSongStartingPos;
        sOcarinaSongStartingPos = 0;
    }
}

void AudioOcarina_StartForSongCheck(u32 ocarinaFlags, u8 ocarinaStaffPlayingPosStart) {
    u8 songIndex;
    u8 j;

    AudioOcarina_Start(ocarinaFlags);
    sMusicStaffNumNotesPerTest = 8;
    sOcarinaStaffPlayingPos = ocarinaStaffPlayingPosStart;

    for (songIndex = 0; songIndex <= OCARINA_SONG_EVAN_PART2; songIndex++) {
        for (j = 0; j < ocarinaStaffPlayingPosStart;) {
            if (sOcarinaSongNotes[songIndex][sMusicStaffPos[songIndex]].pitch != OCARINA_PITCH_NONE) {
                j++;
            }
            sMusicStaffPos[songIndex]++;
        }

        if (sOcarinaSongNotes[songIndex][sMusicStaffPos[songIndex]].pitch == OCARINA_PITCH_NONE) {
            sMusicStaffPos[songIndex]++;
        }
    }
}

void AudioOcarina_StartWithSongNoteLengths(u32 ocarinaFlags) {
    u8 songIndex;

    for (songIndex = 0; songIndex < OCARINA_SONG_MAX; songIndex++) {
        if ((1 << songIndex) & ocarinaFlags) {
            D_801FD530[songIndex] = 0;
        } else {
            D_801FD530[songIndex] = 0xFF;
        }
    }

    D_801D8530 = true;
    D_801D8534 = ocarinaFlags;
    AudioOcarina_Start(ocarinaFlags);
}

void AudioOcarina_StartDefault(u32 ocarinaFlags) {
    D_801D8530 = false;
    AudioOcarina_Start(ocarinaFlags);
}

u8 func_8019B568(void) {
    u32 temp_v0 = D_801D8534;
    u8 songIndex;

    for (songIndex = OCARINA_SONG_SONATA; !((temp_v0 >> songIndex) & 1) && (songIndex < OCARINA_SONG_MAX);
         songIndex++) {}

    return songIndex;
}

u8 func_8019B5AC(void) {
    u8 songIndex = func_8019B568();

    if (songIndex < OCARINA_SONG_MAX) {
        return D_801FD518[songIndex];
    }

    return 0xFF;
}

u8 func_8019B5EC(void) {
    return D_801FD530[func_8019B568()];
}

void AudioOcarina_CheckIfStartedSong(void) {
    if ((sCurOcarinaPitch != OCARINA_PITCH_NONE) && !sOcarinaHasStartedSong) {
        sOcarinaHasStartedSong = true;
        sMusicStaffPrevPitch = OCARINA_PITCH_NONE;
    }
}

void AudioOcarina_UpdateCurOcarinaSong(void) {
    u8 i;

    if (sOcarinaWithoutMusicStaffPos == 8) {
        for (i = 0; i < ARRAY_COUNT(sCurOcarinaSongWithoutMusicStaff) - 1; i++) {
            sCurOcarinaSongWithoutMusicStaff[i] = sCurOcarinaSongWithoutMusicStaff[i + 1];
        }
    } else {
        sOcarinaWithoutMusicStaffPos++;
    }
}

/**
 * Checks for ocarina songs from user input with a music staff prompt
 * Type 1) Playback: tests note-by-note (ocarinaFlag & 0xC000 == 0x8000) eg:
 *      - learning a new song
 *      - playing the ocarina memory game
 * Type 2) Check: tests in 8-note chunks (ocarinaFlag & 0xC000 == 0x0000) eg:
 *      - validating scarecrow spawn song as adult
 *      - ocarina prompt for zelda's lullaby, saria's song, Storms, Song of Time, etc...
 */
void AudioOcarina_CheckSongsWithMusicStaff(void) {
    u32 curOcarinaSongFlag;
    s32 pad;
    u8 noNewValidInput = false;
    s16 pad2;
    s8 staffOcarinaPlayingPosOffset = 0;
    u8 songIndex;
    OcarinaNote* curNote;
    OcarinaNote* nextNote;

    AudioOcarina_CheckIfStartedSong();

    if (!sOcarinaHasStartedSong) {
        return;
    }

    if (ABS_ALT(sCurOcarinaBendIndex) > 20) {
        sOcarinaFlags = 0;
        for (songIndex = OCARINA_SONG_SONATA; songIndex < OCARINA_SONG_MAX; songIndex++) {
            D_801FD518[songIndex] = 4;
        }
        sIsOcarinaInputEnabled = false;
        return;
    }

    if ((sPrevOcarinaPitch == sCurOcarinaPitch) || (sCurOcarinaPitch == OCARINA_PITCH_NONE)) {
        noNewValidInput = true;
    } else {
        AudioOcarina_UpdateCurOcarinaSong();
        sCurOcarinaSongWithoutMusicStaff[sOcarinaWithoutMusicStaffPos - 1] = sCurOcarinaPitch;
    }

    for (songIndex = sFirstOcarinaSongIndex; songIndex < sLastOcarinaSongIndex; songIndex++) {
        curOcarinaSongFlag = 1 << songIndex;

        if (sOcarinaAvailableSongFlags & curOcarinaSongFlag) {
            if (D_801D8530) {
                sMusicStaffCurHeldLength[songIndex] += sOcarinaUpdateTaskStart - sOcarinaPlaybackTaskStart;
            } else {
                sMusicStaffCurHeldLength[songIndex] = sMusicStaffExpectedLength[songIndex] + 9;
            }

            if (noNewValidInput) {
                if ((sMusicStaffCurHeldLength[songIndex] > 8) &&
                    (sMusicStaffPrevPitch != sMusicStaffExpectedPitch[songIndex])) {
                    sOcarinaAvailableSongFlags ^= curOcarinaSongFlag;
                    if (D_801D8530) {
                        D_801FD518[songIndex] = 1;
                    }
                }

                if (D_801D8530 && ((sMusicStaffExpectedLength[songIndex] + 9) < sMusicStaffCurHeldLength[songIndex])) {
                    sOcarinaAvailableSongFlags ^= curOcarinaSongFlag;
                    D_801FD518[songIndex] = 3;
                } else if ((sMusicStaffCurHeldLength[songIndex] >= (sMusicStaffExpectedLength[songIndex] - 9)) &&
                           (sMusicStaffCurHeldLength[songIndex] >= sMusicStaffExpectedLength[songIndex]) &&
                           (sOcarinaSongNotes[songIndex][sMusicStaffPos[songIndex]].length == 0) &&
                           (sMusicStaffPrevPitch == sMusicStaffExpectedPitch[songIndex])) {
                    // This case is taken if the song is finished and successfully played
                    // (i.e. .length == 0 indicates that the song is at the end)
                    sPlayedOcarinaSongIndexPlusOne = songIndex + 1;
                    sIsOcarinaInputEnabled = false;
                    sOcarinaFlags = 0;
                    if (D_801D8530) {
                        D_801FD518[songIndex] = 5;
                    }
                }
            } else if (sMusicStaffCurHeldLength[songIndex] >= (sMusicStaffExpectedLength[songIndex] - 9)) {
                // This else-if statement always holds true, taken if a new note is played
                if (sMusicStaffPrevPitch != OCARINA_PITCH_NONE) {
                    // New note is played
                    if (sMusicStaffPrevPitch == sMusicStaffExpectedPitch[songIndex]) {
                        // Note is part of expected song
                        if (D_801D8530) {
                            D_801FD530[songIndex] +=
                                ABS_ALT(sMusicStaffExpectedLength[songIndex] - sMusicStaffCurHeldLength[songIndex]);
                        }
                        sMusicStaffCurHeldLength[songIndex] = 0;
                    } else {
                        // Note is not part of expected song, so this song is no longer available as an option in this
                        // playback
                        sOcarinaAvailableSongFlags ^= curOcarinaSongFlag;
                        if (D_801D8530) {
                            D_801FD518[songIndex] = 1;
                        }
                    }
                }

                curNote = &sOcarinaSongNotes[songIndex][sMusicStaffPos[songIndex]];
                nextNote = &sOcarinaSongNotes[songIndex][++sMusicStaffPos[songIndex]];
                sMusicStaffExpectedLength[songIndex] = curNote->length;
                sMusicStaffExpectedPitch[songIndex] = curNote->pitch;

                while ((curNote->pitch == nextNote->pitch) ||
                       ((nextNote->pitch == OCARINA_PITCH_NONE) && (nextNote->length != 0))) {
                    sMusicStaffExpectedLength[songIndex] += nextNote->length;
                    curNote = &sOcarinaSongNotes[songIndex][sMusicStaffPos[songIndex]];
                    nextNote = &sOcarinaSongNotes[songIndex][sMusicStaffPos[songIndex] + 1];
                    sMusicStaffPos[songIndex]++;
                }
            } else if (sMusicStaffCurHeldLength[songIndex] < 9) {
                // case never taken
                staffOcarinaPlayingPosOffset = -1;
                sMusicStaffCurHeldLength[songIndex] = 0;
                sMusicStaffPrevPitch = sCurOcarinaPitch;
            } else {
                // case never taken
                if (sOcarinaSongNotes[songIndex][sMusicStaffPos[songIndex]].length == 0) {
                    D_801FD518[songIndex] = 1;
                } else if (D_801D8530) {
                    D_801FD518[songIndex] = 2;
                }
                sOcarinaAvailableSongFlags ^= curOcarinaSongFlag;
            }
        }

        // if a note is played that doesn't match a song, the song bit in sAvailOcarinaSongFlags is turned off
        // if there are no more songs remaining that it could be and the maximum position has been exceeded, then
        if ((sOcarinaAvailableSongFlags == 0) && (sOcarinaStaffPlayingPos >= sMusicStaffNumNotesPerTest)) {
            sIsOcarinaInputEnabled = false;
            if (!D_801D8530) {
                if ((sOcarinaFlags & 0x40000000) && (sCurOcarinaPitch == sOcarinaSongNotes[songIndex][0].pitch)) {
                    // case never taken, this function is not called if (sOcarinaFlags & 0x40000000) is set
                    sPrevOcarinaWithMusicStaffFlags = sOcarinaFlags;
                }
            }
            sOcarinaFlags = 0;
            return;
        }
    }

    if (!noNewValidInput) {
        sMusicStaffPrevPitch = sCurOcarinaPitch;
        sOcarinaStaffPlayingPos += staffOcarinaPlayingPosOffset + 1;
    }
}

/**
 * Checks for ocarina songs from user input with no music staff prompt.
 * Includes ocarina actions such as free play, no warp
 */
void AudioOcarina_CheckSongsWithoutMusicStaff(void) {
    u32 pitch;
    u8 ocarinaStaffPlayingPosStart;
    u8 songIndex;
    u8 j;
    u8 k;

    if (CHECK_BTN_ANY(sOcarinaInputButtonCur, BTN_L) &&
        CHECK_BTN_ANY(sOcarinaInputButtonCur, BTN_A | BTN_CRIGHT | BTN_CLEFT | BTN_CDOWN | BTN_CUP)) {
        AudioOcarina_StartDefault(sOcarinaFlags);
        return;
    }

    AudioOcarina_CheckIfStartedSong();

    if (!sOcarinaHasStartedSong) {
        return;
    }

    ocarinaStaffPlayingPosStart = sOcarinaStaffPlayingPos;
    if ((sPrevOcarinaPitch != sCurOcarinaPitch) && (sCurOcarinaPitch != OCARINA_PITCH_NONE)) {
        sOcarinaStaffPlayingPos++;
        if (sOcarinaStaffPlayingPos > ARRAY_COUNT(sCurOcarinaSongWithoutMusicStaff)) {
            sOcarinaStaffPlayingPos = 1;
        }

        AudioOcarina_UpdateCurOcarinaSong();

        if ((ABS_ALT(sCurOcarinaBendIndex) > 20) && (ocarinaStaffPlayingPosStart != sOcarinaStaffPlayingPos)) {
            sCurOcarinaSongWithoutMusicStaff[sOcarinaWithoutMusicStaffPos - 1] = OCARINA_PITCH_NONE;
        } else {
            sCurOcarinaSongWithoutMusicStaff[sOcarinaWithoutMusicStaffPos - 1] = sCurOcarinaPitch;
        }

        // This nested for-loop tests to see if the notes from the ocarina are identical
        // to any of the songIndex from sFirstOcarinaSongIndex to sLastOcarinaSongIndex

        // Loop through each of the songs
        for (songIndex = sFirstOcarinaSongIndex; songIndex < sLastOcarinaSongIndex; songIndex++) {
            // Checks to see if the song is available to be played
            if ((u32)sOcarinaAvailableSongFlags & (1 << songIndex)) {
                // Loops through all possible starting indices?
                // Loops through the notes of the song?
                for (j = 0, k = 0; j < gOcarinaSongButtons[songIndex].numButtons && k == 0 &&
                                   sOcarinaWithoutMusicStaffPos >= gOcarinaSongButtons[songIndex].numButtons;) {

                    pitch = sCurOcarinaSongWithoutMusicStaff[(sOcarinaWithoutMusicStaffPos -
                                                              gOcarinaSongButtons[songIndex].numButtons) +
                                                             j];

                    if (pitch == sButtonToPitchMap[gOcarinaSongButtons[songIndex].buttonIndex[j]]) {
                        j++;
                    } else {
                        k++;
                    }
                }

                // This conditional is true if songIndex = i is detected
                if (j == gOcarinaSongButtons[songIndex].numButtons) {
                    sPlayedOcarinaSongIndexPlusOne = songIndex + 1;
                    sIsOcarinaInputEnabled = false;
                    sOcarinaFlags = 0;
                }
            }
        }
    }
}

void AudioOcarina_PlayControllerInput(u8 isOcarinaSfxSuppressedWhenCancelled) {
    u32 ocarinaBtnsHeld;

    // Prevents two different ocarina notes from being played on two consecutive frames
    if ((sOcarinaFlags != 0) && (sOcarinaDropInputTimer != 0)) {
        sOcarinaDropInputTimer--;
        return;
    }

    // Ensures the button pressed to start the ocarina does not also play an ocarina note
    if ((sOcarinaInputButtonStart == 0) ||
        ((sOcarinaInputButtonStart & (BTN_A | BTN_CRIGHT | BTN_CLEFT | BTN_CDOWN | BTN_CUP)) !=
         (sOcarinaInputButtonCur & (BTN_A | BTN_CRIGHT | BTN_CLEFT | BTN_CDOWN | BTN_CUP)))) {
        sOcarinaInputButtonStart = 0;
        if (1) {}
        sCurOcarinaPitch = OCARINA_PITCH_NONE;
        sCurOcarinaButtonIndex = OCARINA_BTN_INVALID;
        ocarinaBtnsHeld = (sOcarinaInputButtonCur & (BTN_A | BTN_CRIGHT | BTN_CLEFT | BTN_CDOWN | BTN_CUP)) &
                          (sOcarinaInputButtonPrev & (BTN_A | BTN_CRIGHT | BTN_CLEFT | BTN_CDOWN | BTN_CUP));

        if (!(sOcarinaInputButtonPress & ocarinaBtnsHeld) && (sOcarinaInputButtonCur != 0)) {
            sOcarinaInputButtonPress = sOcarinaInputButtonCur;
        } else {
            sOcarinaInputButtonPress &= ocarinaBtnsHeld;
        }

        // Interprets and transforms controller input into ocarina buttons and notes
        if (CHECK_BTN_ANY(sOcarinaInputButtonPress, BTN_A)) {
            sCurOcarinaPitch = OCARINA_PITCH_D4;
            sCurOcarinaButtonIndex = OCARINA_BTN_A;

        } else if (CHECK_BTN_ANY(sOcarinaInputButtonPress, BTN_CDOWN)) {
            sCurOcarinaPitch = OCARINA_PITCH_F4;
            sCurOcarinaButtonIndex = OCARINA_BTN_C_DOWN;

        } else if (CHECK_BTN_ANY(sOcarinaInputButtonPress, BTN_CRIGHT)) {
            sCurOcarinaPitch = OCARINA_PITCH_A4;
            sCurOcarinaButtonIndex = OCARINA_BTN_C_RIGHT;

        } else if (CHECK_BTN_ANY(sOcarinaInputButtonPress, BTN_CLEFT)) {
            sCurOcarinaPitch = OCARINA_PITCH_B4;
            sCurOcarinaButtonIndex = OCARINA_BTN_C_LEFT;

        } else if (CHECK_BTN_ANY(sOcarinaInputButtonPress, BTN_CUP)) {
            sCurOcarinaPitch = OCARINA_PITCH_D5;
            sCurOcarinaButtonIndex = OCARINA_BTN_C_UP;
        }

        if (sOcarinaInputButtonCur) {}

        // Pressing the R Button will raise the pitch by 1 semitone
        if ((sCurOcarinaPitch != OCARINA_PITCH_NONE) && CHECK_BTN_ANY(sOcarinaInputButtonCur, BTN_R) &&
            (sRecordingState != OCARINA_RECORD_SCARECROW_SPAWN)) {
            sCurOcarinaButtonIndex += OCARINA_BUTTON_FLAG_BFLAT_RAISE; // Flag to resolve B Flat 4
            sCurOcarinaPitch++;                                        // Raise the pitch by 1 semitone
        }

        // Pressing the Z Button will lower the pitch by 1 semitone
        if ((sCurOcarinaPitch != OCARINA_PITCH_NONE) && CHECK_BTN_ANY(sOcarinaInputButtonCur, BTN_Z) &&
            (sRecordingState != OCARINA_RECORD_SCARECROW_SPAWN)) {
            sCurOcarinaButtonIndex += OCARINA_BUTTON_FLAG_BFLAT_LOWER; // Flag to resolve B Flat 4
            sCurOcarinaPitch--;                                        // Lower the pitch by 1 semitone
        }

        if (sRecordingState != OCARINA_RECORD_SCARECROW_SPAWN) {
            // Bend the pitch of the note based on y control stick
            sCurOcarinaBendIndex = sOcarinaInputStickRel.y;
            sCurOcarinaBendFreq = AudioOcarina_BendPitchTwoSemitones(sCurOcarinaBendIndex);

            // Add vibrato of the ocarina note based on the x control stick
            sCurOcarinaVibrato = ABS_ALT(sOcarinaInputStickRel.x) >> 2;
            // Sets vibrato to io port 6
            AudioThread_QueueCmdS8(0x6 << 24 | SEQ_PLAYER_SFX << 16 | SFX_CHANNEL_OCARINA << 8 | 6, sCurOcarinaVibrato);
        } else {
            // no bending or vibrato for recording state OCARINA_RECORD_SCARECROW_SPAWN
            sCurOcarinaBendIndex = 0;
            sCurOcarinaVibrato = 0;
            sCurOcarinaBendFreq = 1.0f; // No bend
        }

        // Processes new and valid notes
        if ((sCurOcarinaPitch != OCARINA_PITCH_NONE) && (sPrevOcarinaPitch != sCurOcarinaPitch)) {
            // Sets ocarina instrument Id to io port 7, which is used
            // as an index in seq 0 to get the true instrument Id
            AudioThread_QueueCmdS8(0x6 << 24 | SEQ_PLAYER_SFX << 16 | SFX_CHANNEL_OCARINA << 8 | 7,
                                   sOcarinaInstrumentId - 1);
            // Sets pitch to io port 5
            AudioThread_QueueCmdS8(0x6 << 24 | SEQ_PLAYER_SFX << 16 | SFX_CHANNEL_OCARINA << 8 | 5, sCurOcarinaPitch);
            AudioSfx_PlaySfx(NA_SE_OC_OCARINA, &gSfxDefaultPos, 4, &sCurOcarinaBendFreq, &sDefaultOcarinaVolume,
                             &gSfxDefaultReverb);
        } else if ((sPrevOcarinaPitch != OCARINA_PITCH_NONE) && (sCurOcarinaPitch == OCARINA_PITCH_NONE) &&
                   !isOcarinaSfxSuppressedWhenCancelled) {
            // Stops ocarina sound when transitioning from playing to not playing a note
            AudioSfx_StopById(NA_SE_OC_OCARINA);
        }
    }
}

/**
 * Directly enable the ocarina to receive input without
 * properly resetting it based on an ocarina instrument id
 * Unused.
 */
void AudioOcarina_EnableInput(u8 inputEnabled) {
    sIsOcarinaInputEnabled = inputEnabled;
}

/**
 * Resets ocarina properties
 */
void AudioOcarina_ResetAndMute(void) {
    sOcarinaInputButtonCur = 0;
    sOcarinaInputButtonPrev = 0;
    sOcarinaInputButtonPress = 0;

    sOcarinaInputButtonStart = 0xFFFF;

    AudioOcarina_PlayControllerInput(false);
    AudioSfx_StopById(NA_SE_OC_OCARINA);

    if (gAudioSpecId != 12) {
        AudioSfx_MuteBanks(0);
    }

    sPlaybackState = 0;
    sPlaybackStaffPos = 0;
    sIsOcarinaInputEnabled = false;

    sOcarinaFlags = 0;

    // return to full volume for both bgm players after ocarina is finished
    AudioSfx_RestoreBgmVolume(SFX_CHANNEL_OCARINA);
    // return to full volume for all sfx channels except system & ocarina banks
    Audio_SetSfxVolumeExceptSystemAndOcarinaBanks(0x7F);
}

void AudioOcarina_ResetAndReadInput(void) {
    sOcarinaInputButtonCur = 0;
    sOcarinaInputButtonPrev = 0;
    sOcarinaInputButtonPress = 0;

    sOcarinaInputButtonStart = 0xFFFF;

    AudioOcarina_PlayControllerInput(true);

    sPlaybackState = 0;
    sPlaybackStaffPos = 0;
    sIsOcarinaInputEnabled = false;

    sOcarinaFlags = 0;

    sOcarinaInputButtonCur = 0;

    AudioOcarina_ReadControllerInput();
    sOcarinaInputButtonStart = sOcarinaInputButtonCur;
}

/**
 * Set a timer that will disable the ocarina once the timer reaches 0
 */
void AudioOcarina_SetOcarinaDisableTimer(u8 unused, u8 timer) {
    sOcarinaDisableTimer = timer;
    sOcarinaUnused = unused;
}

u32 AudioOcarina_SetInstrument(u8 ocarinaInstrumentId) {
    if ((sOcarinaInstrumentId != ocarinaInstrumentId) || (ocarinaInstrumentId == OCARINA_INSTRUMENT_DEFAULT)) {
        Audio_QueueSeqCmd(0x80000000 | ((u32)(SEQ_PLAYER_SFX) << 24) | ((u32)(1) << 16) |
                          ((u32)(SFX_CHANNEL_OCARINA) << 8) | (u32)(ocarinaInstrumentId));
        sOcarinaInstrumentId = ocarinaInstrumentId;

        if (ocarinaInstrumentId == OCARINA_INSTRUMENT_OFF) {
            AudioOcarina_ResetAndMute();
        } else {
            sOcarinaInputButtonCur = 0;
            AudioOcarina_ReadControllerInput();
            sOcarinaInputButtonStart = sOcarinaInputButtonCur;
            // lowers volume of all sfx channels except system & ocarina banks
            Audio_SetSfxVolumeExceptSystemAndOcarinaBanks(0x40);
            // lowers volume of bgm players while playing ocarina
            AudioSfx_LowerBgmVolume(SFX_CHANNEL_OCARINA);
        }
    }
}

void AudioOcarina_SetPlaybackSong(s8 songIndexPlusOne, u8 playbackState) {
    u8 i = 0;

    if (songIndexPlusOne == 0) {
        sPlaybackState = 0;
        AudioSfx_StopById(NA_SE_OC_OCARINA);
        return;
    }

    if (songIndexPlusOne < (OCARINA_SONG_MAX + 1)) {
        sPlaybackSong = sOcarinaSongNotes[songIndexPlusOne - 1];
    } else {
        sPlaybackSong = sScarecrowsLongSongNotes;
    }

    sPlaybackNotePos = 0;
    if (playbackState & 0x80) {
        sPlaybackState = 1;
        sPlaybackStaffStopPos = playbackState & 0xF;
        sPlaybackStaffStartPos = 0xFF;
    } else if (playbackState & 0x40) {
        sPlaybackState = 1;
        sPlaybackStaffStartPos = playbackState & 0xF;
        sPlaybackStaffStopPos = 0xFF;
        while (i < sPlaybackStaffStartPos) {
            if (sOcarinaSongNotes[songIndexPlusOne - 1][sPlaybackNotePos].pitch != OCARINA_PITCH_NONE) {
                i++;
            }
            sPlaybackNotePos++;
        }
    } else {
        sPlaybackState = playbackState;
        sPlaybackStaffStopPos = 0xFF;
        sPlaybackStaffStartPos = 0xFF;
    }

    sPlaybackNoteTimer = 0;
    sPlaybackPitch = OCARINA_PITCH_NONE;
    sPlaybackStaffPos = 0;

    if (sPlaybackStaffStartPos == 0xFF) {
        while ((sPlaybackSong[sPlaybackNotePos].pitch == OCARINA_PITCH_NONE) &&
               (songIndexPlusOne > (OCARINA_SONG_EVAN_PART2 + 1))) {
            sPlaybackNotePos++;
        }
    }
}

/**
 * Play a song with the ocarina to the user that is
 * based on OcarinaNote data and not user input
 */
void AudioOcarina_PlaybackSong(void) {
    s32 noteTimerStep;
    s32 nextNoteTimerStep;

    if (sPlaybackState == 0) {
        return;
    }

    if (sPlaybackStaffPos == 0) {
        noteTimerStep = 3;
    } else {
        noteTimerStep = sOcarinaUpdateTaskStart - sOcarinaPlaybackTaskStart;
    }

    if (noteTimerStep < sPlaybackNoteTimer) {
        sPlaybackNoteTimer -= noteTimerStep;
    } else {
        nextNoteTimerStep = noteTimerStep - sPlaybackNoteTimer;
        sPlaybackNoteTimer = 0;
    }

    if (sPlaybackNoteTimer == 0) {

        if (sPlaybackStaffPos == sPlaybackStaffStopPos) {
            sPlaybackState = 0;
            return;
        }

        sPlaybackNoteTimer = sPlaybackSong[sPlaybackNotePos].length;

        if (sPlaybackNotePos == 1) {
            sPlaybackNoteTimer++;
        }

        if (sPlaybackNoteTimer == 0) {
            sPlaybackState--;
            if (sPlaybackState != 0) {
                sPlaybackNotePos = 0;
                sPlaybackStaffPos = 0;
                sPlaybackPitch = OCARINA_PITCH_NONE;
            } else {
                AudioSfx_StopById(NA_SE_OC_OCARINA);
            }
            return;
        } else {
            sPlaybackNoteTimer -= nextNoteTimerStep;
        }

        // Update volume
        if (sNotePlaybackVolume != sPlaybackSong[sPlaybackNotePos].volume) {
            sNotePlaybackVolume = sPlaybackSong[sPlaybackNotePos].volume;
            sRelativeNotePlaybackVolume = sNotePlaybackVolume / 127.0f;
        }

        // Update vibrato
        sNotePlaybackVibrato = sPlaybackSong[sPlaybackNotePos].vibrato;
        // Sets vibrato to io port 6
        AudioThread_QueueCmdS8(0x6 << 24 | SEQ_PLAYER_SFX << 16 | SFX_CHANNEL_OCARINA << 8 | 6, sNotePlaybackVibrato);

        // Update bend
        if (sNotePlaybackBend != sPlaybackSong[sPlaybackNotePos].bend) {
            sNotePlaybackBend = sPlaybackSong[sPlaybackNotePos].bend;
            sRelativeNotePlaybackBend = AudioOcarina_BendPitchTwoSemitones(sNotePlaybackBend);
        }

        // No changes in volume, vibrato, or bend between notes
        if ((sPlaybackSong[sPlaybackNotePos].volume == sPlaybackSong[sPlaybackNotePos - 1].volume &&
             (sPlaybackSong[sPlaybackNotePos].vibrato == sPlaybackSong[sPlaybackNotePos - 1].vibrato) &&
             (sPlaybackSong[sPlaybackNotePos].bend == sPlaybackSong[sPlaybackNotePos - 1].bend))) {
            sPlaybackPitch = 0xFE;
        }

        if (sPlaybackPitch != sPlaybackSong[sPlaybackNotePos].pitch) {
            u8 pitch = sPlaybackSong[sPlaybackNotePos].pitch;

            // As bFlat4 is exactly in the middle of notes B & A, a flag is
            // added to the pitch to resolve which button to map Bflat4 to
            if (pitch == OCARINA_PITCH_BFLAT4) {
                sPlaybackPitch = pitch + sPlaybackSong[sPlaybackNotePos].bFlat4Flag;
            } else {
                sPlaybackPitch = pitch;
            }

            if (sPlaybackPitch != OCARINA_PITCH_NONE) {
                sPlaybackStaffPos++;
                // Sets ocarina instrument Id to io port 7, which is used
                // as an index in seq 0 to get the true instrument Id
                AudioThread_QueueCmdS8(0x6 << 24 | SEQ_PLAYER_SFX << 16 | SFX_CHANNEL_OCARINA << 8 | 7,
                                       sOcarinaInstrumentId - 1);
                AudioThread_QueueCmdS8(0x6 << 24 | SEQ_PLAYER_SFX << 16 | SFX_CHANNEL_OCARINA << 8 | 5,
                                       sPlaybackPitch & OCARINA_BUTTON_MASK_PITCH);
                AudioSfx_PlaySfx(NA_SE_OC_OCARINA, &gSfxDefaultPos, 4, &sRelativeNotePlaybackBend,
                                 &sRelativeNotePlaybackVolume, &gSfxDefaultReverb);
            } else {
                AudioSfx_StopById(NA_SE_OC_OCARINA);
            }
        }
        sPlaybackNotePos++;
    }
}

void AudioOcarina_SetRecordingSong(u8 isRecordingComplete) {
    u16 i;
    u16 i2;
    u16 pad;
    u8 pitch;
    OcarinaNote* note;
    u8 j;
    u8 k;
    s32 t;
    OcarinaNote* recordedSong;

    if (sRecordingState == OCARINA_RECORD_SCARECROW_LONG) {
        recordedSong = gScarecrowLongSongPtr;
    } else {
        /**
         * OCARINA_RECORD_SCARECROW_SPAWN
         *
         * The notes for scarecrows spawn song are first recorded into the ocarina termina
         * wall address to act as a buffer. That way, if a new scarecrow spawn song is
         * rejected, the previous scarecrow spawn song is not overwritten. If the scarecrow
         * spawn song is accepted, then the notes are copied over to the scarecrow spawn
         * song address
         */
        recordedSong = sTerminaWallSongPtr;
    }

    recordedSong[sRecordSongPos].pitch = sRecordOcarinaPitch;
    recordedSong[sRecordSongPos].length = sOcarinaUpdateTaskStart - sOcarinaRecordTaskStart;
    recordedSong[sRecordSongPos].volume = sRecordOcarinaVolume;
    recordedSong[sRecordSongPos].vibrato = sRecordOcarinaVibrato;
    recordedSong[sRecordSongPos].bend = sRecordOcarinaBendIndex;
    recordedSong[sRecordSongPos].bFlat4Flag = sRecordOcarinaButtonIndex & OCARINA_BUTTON_MASK_FLAG;

    sRecordOcarinaPitch = sCurOcarinaPitch;
    sRecordOcarinaVolume = sCurOcarinaVolume;
    sRecordOcarinaVibrato = sCurOcarinaVibrato;
    sRecordOcarinaBendIndex = sCurOcarinaBendIndex;
    sRecordOcarinaButtonIndex = sCurOcarinaButtonIndex;

    sRecordSongPos++;

    if ((sRecordSongPos != (ARRAY_COUNT(sScarecrowsLongSongNotes) - 1)) && !isRecordingComplete) {
        // Continue recording
        return;
    }

    // Recording is complete

    i = sRecordSongPos;
    pitch = OCARINA_PITCH_NONE;
    while (i != 0 && pitch == OCARINA_PITCH_NONE) {
        i--;
        pitch = recordedSong[i].pitch;
    }

    if (sRecordSongPos != (i + 1)) {
        sRecordSongPos = i + 2;
        recordedSong[sRecordSongPos - 1].length = 0;
    }

    recordedSong[sRecordSongPos].length = 0;

    if (sRecordingState == OCARINA_RECORD_SCARECROW_SPAWN) {
        if (sOcarinaStaffPlayingPos >= 8) {
            for (i = 0; i < sRecordSongPos; i++) {
                recordedSong[i] = recordedSong[i + 1];
            }

            // Copies Notes from buffer into scarecrows spawn buttons to be tested for acceptance or rejection
            AudioOcarina_MapSongFromPitchToButton(OCARINA_SONG_TERMINA_WALL, OCARINA_SONG_SCARECROW_SPAWN, 8);

            // Tests to see if the notes from the scarecrow song contain identical
            // notes within its song to any of the reserved songIndex from 0 to 21

            // Loop through each of the songs
            for (i = 0; i < OCARINA_SONG_SCARECROW_SPAWN; i++) {
                // Checks to see if the song is reserved
                if (sIsOcarinaSongReserved[i]) {
                    // Loops through all possible starting indices
                    for (j = 0; (j < 9 - gOcarinaSongButtons[i].numButtons); j++) {
                        // Loops through the notes of the song
                        for (k = 0; (k < gOcarinaSongButtons[i].numButtons) && (k + j < 8) &&
                                    (gOcarinaSongButtons[i].buttonIndex[k] ==
                                     gOcarinaSongButtons[OCARINA_SONG_SCARECROW_SPAWN].buttonIndex[k + j]);
                             k++) {
                            ;
                        }

                        // This conditional is true if the recorded song contains a reserved song
                        // recorded song is cancelled
                        if (k == gOcarinaSongButtons[i].numButtons) {
                            sRecordingState = OCARINA_RECORD_REJECTED;
                            sOcarinaSongNotes[OCARINA_SONG_SCARECROW_SPAWN][1].volume = 0xFF;
                            return;
                        }
                    }
                }
            }

            // Counts how many times a note is repeated
            i = 1;
            while (i < 8) {
                if (gOcarinaSongButtons[OCARINA_SONG_SCARECROW_SPAWN].buttonIndex[0] !=
                    gOcarinaSongButtons[OCARINA_SONG_SCARECROW_SPAWN].buttonIndex[i]) {
                    i = 9; // break
                } else {
                    i++;
                }
            }

            // This condition is true if all 8 notes are the same pitch
            if (i == 8) {
                sRecordingState = OCARINA_RECORD_REJECTED;
                sOcarinaSongNotes[OCARINA_SONG_SCARECROW_SPAWN][1].volume = 0xFF;
                return;
            }

            // The scarecrow spawn song is accepted and copied from the buffer to the scarecrow spawn notes
            for (i = 0; i < sRecordSongPos; i++) {
                sOcarinaSongNotes[OCARINA_SONG_SCARECROW_SPAWN][i] = sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][i];
            }

            sIsOcarinaInputEnabled = false;
        } else {
            sOcarinaSongNotes[OCARINA_SONG_SCARECROW_SPAWN][1].volume = 0xFF;
        }
    }

    sRecordingState = OCARINA_RECORD_OFF;
}

/**
 * recordingState = OCARINA_RECORD_OFF, end
 * recordingState = OCARINA_RECORD_SCARECROW_LONG, start long scarecrows song
 * recordingState = OCARINA_RECORD_SCARECROW_SPAWN, start spawn scarecrows song
 */
void AudioOcarina_SetRecordingState(u8 recordingState) {
    if ((u32)recordingState == sRecordingState) {
        return;
    }

    if (recordingState != OCARINA_RECORD_OFF) {
        sOcarinaRecordTaskStart = sOcarinaUpdateTaskStart;
        sRecordOcarinaPitch = OCARINA_PITCH_NONE;
        sRecordOcarinaVolume = 0x57;
        sRecordOcarinaVibrato = 0;
        sRecordOcarinaBendIndex = 0;
        sRecordOcarinaButtonIndex = 0;
        sRecordSongPos = 0;
        sIsOcarinaInputEnabled = true;
        sOcarinaStaffPlayingPos = 0;
        sScarecrowsLongSongSecondNote = sScarecrowsLongSongNotes[1];
    } else {
        if (sRecordSongPos == 0) {
            sScarecrowsLongSongNotes[1] = sScarecrowsLongSongSecondNote;
        } else {
            if (sRecordingState == OCARINA_RECORD_SCARECROW_SPAWN) {
                sOcarinaStaffPlayingPos = 1;
            }

            AudioOcarina_SetRecordingSong(true);
        }

        sIsOcarinaInputEnabled = false;
        sOcarinaStaffPlayingPos = 0;
    }

    sRecordingState = recordingState;
}

void AudioOcarina_UpdateRecordingStaff(void) {
    sRecordingStaff.state = sRecordingState;
    sRecordingStaff.pos = sOcarinaStaffPlayingPos;
    if (sRecordingState == OCARINA_RECORD_REJECTED) {
        sRecordingState = OCARINA_RECORD_OFF;
    }
}

void AudioOcarina_UpdatePlayingStaff(void) {
    if (sCurOcarinaButtonIndex != OCARINA_BTN_INVALID) {
        sPlayingStaff.buttonIndex = sCurOcarinaButtonIndex & OCARINA_BUTTON_MASK_PITCH;
    }
    sPlayingStaff.state = AudioOcarina_GetPlayingState();
    sPlayingStaff.pos = sOcarinaStaffPlayingPos;
}

void AudioOcarina_UpdatePlaybackStaff(void) {
    if ((sPlaybackPitch & OCARINA_BUTTON_MASK_PITCH) <= OCARINA_PITCH_EFLAT5) {
        sPlaybackStaff.buttonIndex = AudioOcarina_MapPitchToButton(sPlaybackPitch);
    }

    sPlaybackStaff.state = sPlaybackState;

    if (sPlaybackSong != sScarecrowsLongSongNotes) {
        sPlaybackStaff.pos = sPlaybackStaffPos;
    } else if (sPlaybackStaffPos == 0) {
        sPlaybackStaff.pos = 0;
    } else {
        sPlaybackStaff.pos = ((sPlaybackStaffPos - 1) % 8) + 1;
    }
}

OcarinaStaff* AudioOcarina_GetRecordingStaff(void) {
    return &sRecordingStaff;
}

OcarinaStaff* AudioOcarina_GetPlayingStaff(void) {
    if (sPlayingStaff.state < 0xFE) {
        sOcarinaFlags = 0;
    }

    return &sPlayingStaff;
}

OcarinaStaff* AudioOcarina_GetPlaybackStaff(void) {
    return &sPlaybackStaff;
}

void AudioOcarina_RecordSong(void) {
    s32 noteChanged;

    if ((sRecordingState != OCARINA_RECORD_OFF) && ((sOcarinaUpdateTaskStart - sOcarinaRecordTaskStart) >= 3)) {
        noteChanged = false;
        if (sRecordOcarinaPitch != sCurOcarinaPitch) {
            if (sCurOcarinaPitch != OCARINA_PITCH_NONE) {
                sRecordingStaff.buttonIndex = sCurOcarinaButtonIndex & OCARINA_BUTTON_MASK_PITCH;
                sOcarinaStaffPlayingPos++;
            } else if ((sRecordingState == OCARINA_RECORD_SCARECROW_SPAWN) && (sOcarinaStaffPlayingPos == 8)) {
                AudioOcarina_SetRecordingSong(true);
                return;
            }

            if (sOcarinaStaffPlayingPos > 8) {
                if (sRecordingState == OCARINA_RECORD_SCARECROW_SPAWN) {
                    // notes played are over 8 and in recording mode.
                    AudioOcarina_SetRecordingSong(true);
                    return;
                }
                sOcarinaStaffPlayingPos = 1;
            }
            noteChanged = true;
        } else if (sRecordOcarinaVolume != sCurOcarinaVolume) {
            noteChanged = true;
        } else if (sRecordOcarinaVibrato != sCurOcarinaVibrato) {
            if (sRecordingState != OCARINA_RECORD_SCARECROW_SPAWN) {
                noteChanged = true;
            }
        } else if ((sRecordOcarinaBendIndex != sCurOcarinaBendIndex) &&
                   (sRecordingState != OCARINA_RECORD_SCARECROW_SPAWN)) {
            noteChanged = true;
        }

        if (noteChanged) {
            AudioOcarina_SetRecordingSong(false);
            sOcarinaRecordTaskStart = sOcarinaUpdateTaskStart;
        }
    }
}

/**
 * Tests to see if the notes from songIndex contain identical notes
 * within its song to any of the reserved songIndex from 0 up to maxSongIndex
 */
s32 AudioOcarina_TerminaWallValidateNotes(u8 songIndex, u8 maxSongIndex) {
    u8 curSongIndex;
    u8 j;
    u8 k;

    // loop through all possible songs up to maxSongIndex
    for (curSongIndex = 0; curSongIndex < maxSongIndex; curSongIndex++) {
        // check to see if the song is reserved or not
        if (sIsOcarinaSongReserved[curSongIndex]) {
            // starting index to test the song
            for (j = 0; j < (9 - gOcarinaSongButtons[curSongIndex].numButtons); j++) {
                // loop through each note in the song
                for (k = 0; (k < gOcarinaSongButtons[curSongIndex].numButtons) && ((k + j) < 8) &&
                            (gOcarinaSongButtons[curSongIndex].buttonIndex[k] ==
                             gOcarinaSongButtons[songIndex].buttonIndex[(k + j)]);
                     k++) {
                    continue;
                }

                if (k == gOcarinaSongButtons[curSongIndex].numButtons) {
                    // failure: songIndex is identical to curSongIndex.
                    return -1;
                }
            }
        }
    }

    // success: notes are accepted and used
    return 0;
}

/**
 * Generates the notes displayed on the Termina Field wall of musical notes
 * Song generation loop alternates between 8 random notes and a random song from Ocarina of Time (OoT).
 * Will check to see that the notes are valid by ensuring no playable song is within the selected notes
 * All OoT songs are valid, so the outer loop will run a maxiumum of two times.
 * i.e. if random notes fails, then the next set of notes will be from a valid OoT song
 */
void AudioOcarina_TerminaWallGenerateNotes(void) {
    OcarinaNote* ocarinaNote;
    u8 randomButtonIndex;
    u8 i;
    u8 j;

    do {
        i = 0;
        if (sOcarinaWallCounter++ % 2) {
            j = 0;

            for (; i < 8; i++) {
                randomButtonIndex = AudioThread_NextRandom() % ARRAY_COUNT(sButtonToPitchMap);
                sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][j].pitch = sButtonToPitchMap[randomButtonIndex];
                sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][j].length = 19;
                sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][j].volume = 80;
                sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][j].vibrato = 0;
                sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][j].bend = 0;
                j++;
                sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][j].pitch = OCARINA_PITCH_NONE;
                sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][j].length = 3;
                sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][j].volume = 0;
                sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][j].vibrato = 0;
                sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][j].bend = 0;
                j++;
            }

            sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][j - 2].length = 90;
            sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][j - 1].length = 22;
            sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][j + 1].pitch = OCARINA_PITCH_NONE;
            sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][j + 1].length = 0;
            AudioOcarina_MapSongFromPitchToButton(OCARINA_SONG_TERMINA_WALL, OCARINA_SONG_TERMINA_WALL, 8);
        } else {
            j = AudioThread_NextRandom() % ARRAY_COUNT(sOoTOcarinaSongNotes);
            ocarinaNote = sOoTOcarinaSongNotes[j];

            for (; ocarinaNote[i].length != 0; i++) {
                sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][i] = ocarinaNote[i];
            }

            sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][i].pitch = OCARINA_PITCH_NONE;
            sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][i].length = 0;
            AudioOcarina_MapSongFromPitchToButton(OCARINA_SONG_TERMINA_WALL, OCARINA_SONG_TERMINA_WALL,
                                                  sOoTOcarinaSongsNumNotes[j]);
        }
    } while (AudioOcarina_TerminaWallValidateNotes(OCARINA_SONG_TERMINA_WALL, OCARINA_SONG_TERMINA_WALL) != 0);
}

/**
 * Unused remnant of OoT
 */
void AudioOcarina_MemoryGameInit(u8 minigameRound) {
    u8 i;

    if (minigameRound > 2) {
        minigameRound = 2;
    }

    sOcarinaMemoryGameAppendPos = 0;
    sOcarinaMemoryGameEndPos = sOcarinaMemoryGameNumNotes[minigameRound];

    for (i = 0; i < 3; i++) {
        AudioOcarina_MemoryGameNextNote();
    }
}

/**
 * Unused remnant of OoT, Id 14 now represent Goron Lullaby Intro instead of the OoT ocarina memory game
 * //! @bug calling this function in MM will overwrite Goron Lullaby Intro
 */
#define OCARINA_SONG_MEMORY_GAME 14
s32 AudioOcarina_MemoryGameNextNote(void) {
    u32 randomButtonIndex;
    u8 randomPitch;

    if (sOcarinaMemoryGameAppendPos == sOcarinaMemoryGameEndPos) {
        return true;
    }

    randomButtonIndex = AudioThread_NextRandom();
    randomPitch = sButtonToPitchMap[randomButtonIndex % ARRAY_COUNT(sButtonToPitchMap)];

    if (sOcarinaSongNotes[OCARINA_SONG_MEMORY_GAME][sOcarinaMemoryGameAppendPos - 1].pitch == randomPitch) {
        randomPitch = sButtonToPitchMap[(randomButtonIndex + 1) % ARRAY_COUNT(sButtonToPitchMap)];
    }

    sOcarinaSongNotes[OCARINA_SONG_MEMORY_GAME][sOcarinaMemoryGameAppendPos].pitch = randomPitch;
    sOcarinaSongNotes[OCARINA_SONG_MEMORY_GAME][sOcarinaMemoryGameAppendPos].length = 45;
    sOcarinaSongNotes[OCARINA_SONG_MEMORY_GAME][sOcarinaMemoryGameAppendPos].volume = 0x50;
    sOcarinaSongNotes[OCARINA_SONG_MEMORY_GAME][sOcarinaMemoryGameAppendPos].vibrato = 0;
    sOcarinaSongNotes[OCARINA_SONG_MEMORY_GAME][sOcarinaMemoryGameAppendPos].bend = 0;

    sOcarinaMemoryGameAppendPos++;

    sOcarinaSongNotes[OCARINA_SONG_MEMORY_GAME][sOcarinaMemoryGameAppendPos].pitch = OCARINA_PITCH_NONE;
    sOcarinaSongNotes[OCARINA_SONG_MEMORY_GAME][sOcarinaMemoryGameAppendPos].length = 0;
    sOcarinaSongNotes[OCARINA_SONG_MEMORY_GAME][sOcarinaMemoryGameAppendPos + 1].pitch = OCARINA_PITCH_NONE;
    sOcarinaSongNotes[OCARINA_SONG_MEMORY_GAME][sOcarinaMemoryGameAppendPos + 1].length = 0;
    if (1) {}
    return false;
}
#undef OCARINA_SONG_MEMORY_GAME

void AudioOcarina_Update(void) {
    sOcarinaUpdateTaskStart = gAudioContext.totalTaskCount;
    if (sOcarinaInstrumentId != OCARINA_INSTRUMENT_OFF) {
        if (sIsOcarinaInputEnabled == true) {
            AudioOcarina_ReadControllerInput();
        }

        if ((sPlaybackState == 0) && (sIsOcarinaInputEnabled == true)) {
            AudioOcarina_PlayControllerInput(false);
        }

        if (sOcarinaFlags != 0) {
            if (sOcarinaFlags & 0x40000000) {
                AudioOcarina_CheckSongsWithoutMusicStaff();
            } else {
                AudioOcarina_CheckSongsWithMusicStaff();
            }
        }

        AudioOcarina_PlaybackSong();
        sOcarinaPlaybackTaskStart = sOcarinaUpdateTaskStart;

        if (sPlaybackState == 0) {
            AudioOcarina_RecordSong();
        }

        if ((sOcarinaFlags != 0) && (sPrevOcarinaPitch != sCurOcarinaPitch)) {
            sOcarinaDropInputTimer = 1; // Drops ocarina input for 1 frame
        }

        sPrevOcarinaPitch = sCurOcarinaPitch;

        if (sOcarinaDisableTimer != 0) {
            sOcarinaDisableTimer--;
            if (sOcarinaDisableTimer == 0) {
                AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
            }
        }
    }

    AudioOcarina_UpdatePlayingStaff();
    AudioOcarina_UpdatePlaybackStaff();
    AudioOcarina_UpdateRecordingStaff();
}

#define OCARINA_INSTRUMENT_OOT_MAX 7

void AudioOcarina_PlayLongScarecrowAfterCredits(void) {
    static u8 sScarecrowAfterCreditsState = 0;
    static u8 sScarecrowAfterCreditsIntrumentId = OCARINA_INSTRUMENT_DEFAULT;
    static u16 sScarecrowAfterCreditsTimer = 1200;

    switch (sScarecrowAfterCreditsState) {
        case 0:
            if (sScarecrowAfterCreditsTimer-- == 0) {
                // OoT originally had 7 Ocarina instruments
                // MM has more so this does not go all the way to the max
                if (sScarecrowAfterCreditsIntrumentId < OCARINA_INSTRUMENT_OOT_MAX) {
                    // set next ocarina instrument and restart
                    sScarecrowAfterCreditsState++;
                } else {
                    // finished
                    sScarecrowAfterCreditsState = 3;
                    AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                }
                sScarecrowAfterCreditsTimer = 1200;
            }
            break;

        case 1:
            AudioSfx_MuteBanks(0);
            AudioOcarina_SetInstrument(sScarecrowAfterCreditsIntrumentId);
            AudioOcarina_SetPlaybackSong(OCARINA_SONG_SCARECROW_LONG + 1, 1);
            sScarecrowAfterCreditsIntrumentId++;
            sScarecrowAfterCreditsState++;
            break;

        case 2:
            if (AudioOcarina_GetPlaybackStaff()->state == 0) {
                sScarecrowAfterCreditsState = 0;
            }
            break;
    }
}

u8 sRequestCustomSequence = false;

void AudioOcarina_SetCustomSequence(void) {
    // Never passes true as sRequestCustomSequence is never set true
    if (sRequestCustomSequence && gAudioContext.seqPlayers[SEQ_PLAYER_FANFARE].enabled &&
        ((u8)gAudioContext.seqPlayers[SEQ_PLAYER_FANFARE].soundScriptIO[0] == 0xFF)) {
        gAudioContext.seqPlayers[SEQ_PLAYER_FANFARE].seqData = sCustomSequenceScript;
        sRequestCustomSequence = false;
    }
}

// Called by unused function
void AudioOcarina_PlayCustomSequence(void) {
    sRequestCustomSequence = true;
    Audio_QueueSeqCmd(0x00000000 | ((u32)(SEQ_PLAYER_FANFARE) << 24) | ((u32)(0) << 0x10) |
                      (u32)(NA_BGM_DUNGEON_APPEAR));
}

// Unused
// Regalloc Swap https://decomp.me/scratch/QEovr
#ifdef NON_MATCHING
s32 AudioOcarina_CreateCustomSequence(void) {
    OcarinaNote* prevNote;
    u16 i;
    u16 phi_s4;
    u16 temp_a0; // delay1
    u16 phi_a2;  // delay2
    u8 absPitch;
    s8 phi_a0;   // adjBendIndex
    s8 phi_s2;   // prevBend
    u8 phi_t1;   // vibrato
    u8 phi_t5;   // isLegato
    u16 temp_t4; // prevNoteLength

    phi_a2 = 0;
    phi_t1 = 0;
    phi_s2 = 0;
    phi_t5 = 0;
    phi_s4 = 0;

    sCustomSequencePc = 39; // .channel chan_loop

    prevNote = &sScarecrowsLongSongNotes[0];
    for (i = 1; ((prevNote->pitch == OCARINA_PITCH_NONE) && (prevNote->length != 0)); i++) {
        prevNote = &sScarecrowsLongSongNotes[i];
    }

    for (; (prevNote->length != 0) && (sCustomSequencePc < 394); i++) {

        temp_a0 = ((prevNote->length * 48) / 30);

        if (phi_t1 != prevNote->vibrato) {
            sCustomSequenceScript[sCustomSequencePc++] = 0xFD; // delay cmd

            if (phi_a2 >= 0x80) {
                // Store as compressed u16
                sCustomSequenceScript[sCustomSequencePc++] = (((phi_a2 >> 8) & 0xFF) & 0x7F) + 0x80; // delay arg
                sCustomSequenceScript[sCustomSequencePc++] = phi_a2 & 0xFF;                          // delay arg
            } else {
                // Store as u8
                sCustomSequenceScript[sCustomSequencePc++] = phi_a2; // delay arg
            }

            sCustomSequenceScript[sCustomSequencePc++] = 0xD8;              // vibdepth cmd
            sCustomSequenceScript[sCustomSequencePc++] = prevNote->vibrato; // vibdepth arg

            phi_a2 = temp_a0;
            phi_t1 = prevNote->vibrato;
        } else {
            phi_a2 += temp_a0;
        }

        prevNote = &sScarecrowsLongSongNotes[i];
    }

    if (phi_a2 != 0) {
        sCustomSequenceScript[sCustomSequencePc++] = 0xFD; // delay cmd
        if (phi_a2 >= 0x80) {
            // Store as compressed u16
            sCustomSequenceScript[sCustomSequencePc++] = (((phi_a2 >> 8) & 0xFF) & 0x7F) + 0x80; // delay arg
            sCustomSequenceScript[sCustomSequencePc++] = phi_a2 & 0xFF;                          // delay arg
        } else {
            // Store as u8
            sCustomSequenceScript[sCustomSequencePc++] = phi_a2; // delay arg
        }
    }

    sCustomSequenceScript[sCustomSequencePc++] = 0xFF; // end cmd

    // ldlayer 0, layer0
    sCustomSequenceScript[24] = sCustomSequencePc >> 8;
    sCustomSequenceScript[25] = sCustomSequencePc & 0xFF;

    // ldlayer 1, layer1
    sCustomSequenceScript[27] = (sCustomSequencePc + 4) >> 8;
    sCustomSequenceScript[28] = (sCustomSequencePc + 4) & 0xFF;

    sCustomSequenceScript[sCustomSequencePc++] = 0xC2; // transpose cmd
    sCustomSequenceScript[sCustomSequencePc++] = -5;   // transpose arg

    sCustomSequenceScript[sCustomSequencePc++] = 0xC0; // ldelay cmd
    sCustomSequenceScript[sCustomSequencePc++] = 8;    // ldelay arg

    sCustomSequenceScript[sCustomSequencePc++] = 0xC1; // shortvel cmd
    sCustomSequenceScript[sCustomSequencePc++] = 87;   // shortvel arg

    sCustomSequenceScript[sCustomSequencePc++] = 0xC9; // shortgate cmd
    sCustomSequenceScript[sCustomSequencePc++] = 0;    // shortgate arg

    if (1) {}
    if (1) {} // TODO: Needed?

    prevNote = &sScarecrowsLongSongNotes[0];

    for (i = 1; ((prevNote->pitch == OCARINA_PITCH_NONE) && (prevNote->length != 0)); i++) {
        prevNote = &sScarecrowsLongSongNotes[i];
    }

    for (; ((temp_t4 = prevNote->length) != 0) && (sCustomSequencePc < 394); i++) {

        if (prevNote->pitch == sScarecrowsLongSongNotes[i].pitch) {
            if ((sScarecrowsLongSongNotes[i].length != 0) && (phi_t5 == 0)) {
                sCustomSequenceScript[sCustomSequencePc++] = 0xC4; // legato cmd
                phi_t5 = 1;
            }
        } else if ((phi_t5 == 1) && (sScarecrowsLongSongNotes[i].pitch != OCARINA_PITCH_NONE) &&
                   (sScarecrowsLongSongNotes[i].pitch != OCARINA_PITCH_C4)) {
            sCustomSequenceScript[sCustomSequencePc++] = 0xC5; // nolegato cmd
            phi_t5 = 0;
        }

        if (phi_s2 != prevNote->bend) {
            sCustomSequenceScript[sCustomSequencePc++] = 0xCE; // bendfine cmd

            if (ABS_ALT(prevNote->bend) > 64) {
                phi_a0 = 127;
            } else if (prevNote->bend < 0) {
                phi_a0 = -prevNote->bend;
            } else {
                phi_a0 = ((prevNote->bend * 127) / 64);
            }

            if (prevNote->bend < 0) {
                phi_a0 *= -1;
            }

            sCustomSequenceScript[sCustomSequencePc++] = phi_a0; // bendfine arg

            phi_s2 = prevNote->bend;
        }

        absPitch = prevNote->pitch + 39; // convert ocarina pitch to absolute pitch, + PITCH_C4 (Middle C)
        if (prevNote->pitch != OCARINA_PITCH_NONE) {
            sCustomSequenceScript[sCustomSequencePc++] = absPitch; // shortdvg cmd, shortdvg arg
        } else {
            sCustomSequenceScript[sCustomSequencePc++] = 0xC0; // ldelay cmd
        }

        // delay/duration
        temp_a0 = ((temp_t4 * 48) + phi_s4) / 30;

        if (temp_a0 < 0x80) {
            // Store as u8
            sCustomSequenceScript[sCustomSequencePc++] = temp_a0; // shortdvg/ldelay arg
        } else {
            // Store as compressed u16
            sCustomSequenceScript[sCustomSequencePc++] = (((temp_a0 >> 8) & 0xFF) & 0x7F) + 0x80; // shortdvg/ldelay arg
            sCustomSequenceScript[sCustomSequencePc++] = temp_a0 & 0xFF;                          // shortdvg/ldelay arg
        }

        if (1) {}

        phi_s4 = ((temp_t4 * 48) + phi_s4) - (temp_a0 * 30);

        prevNote = &sScarecrowsLongSongNotes[i];
    }

    sCustomSequenceScript[sCustomSequencePc++] = 0xFF; // end cmd

    AudioOcarina_PlayCustomSequence();

    if (i >= 394) {
        return -1;
    }

    return 0;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/AudioOcarina_CreateCustomSequence.s")
#endif

void AudioOcarina_ResetInstrument(void) {
    if (sOcarinaInstrumentId != OCARINA_INSTRUMENT_OFF) {
        Audio_QueueSeqCmd(0x80000000 | ((u32)(SEQ_PLAYER_SFX) << 24) | ((u32)(1) << 16) |
                          ((u32)(SFX_CHANNEL_OCARINA) << 8) | (u32)(0));
        sOcarinaInstrumentId = OCARINA_INSTRUMENT_OFF;
        AudioOcarina_ResetAndMute();
    }
}

void AudioOcarina_ResetStaffs(void) {
    u8 songIndex;

    sPlayingStaff.buttonIndex = OCARINA_BTN_INVALID;
    sPlayingStaff.state = 0xFF;
    sPlayingStaff.pos = 0;

    sPlaybackStaff.buttonIndex = OCARINA_BTN_INVALID;
    sPlaybackStaff.state = 0;
    sPlaybackStaff.pos = 0;

    sRecordingStaff.buttonIndex = OCARINA_BTN_INVALID;
    sRecordingStaff.state = 0xFF;
    sRecordingStaff.pos = 0;

    sOcarinaDisableTimer = 0;
    sOcarinaDropInputTimer = 0;

    for (songIndex = OCARINA_SONG_SONATA; songIndex < OCARINA_SONG_MAX; songIndex++) {
        D_801FD518[songIndex] = 0xFF;
        D_801FD530[songIndex] = 0;
    }

    D_801D8534 = 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019DFF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019E000.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019E00C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019E014.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019E0FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019E104.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019E110.s")

f32 AudioSfx_ComputeVolume(u8 bankId, u8 entryIndex) {
    SfxBankEntry* bankEntry = &gSfxBanks[bankId][entryIndex];
    f32 minDist;
    f32 phi_f14;
    f32 baseDist;
    f32 phi_f12;
    f32 volume; // Also acts as intermediate volumeSquared
    s32 pad[3];

    if (bankEntry->sfxParams & SFX_FLAG_VOLUME_NO_DIST) {
        return 1.0f;
    }

    if (bankEntry->dist > 10000.0f) {
        volume = 0.0f;
    } else {
        if (bankEntry->sfxParams & SFX_PARAM_DIST_RANGE_MASK_UPPER) {
            phi_f12 = 0.35f;
            phi_f14 = 0.65f;
        } else {
            phi_f12 = 0.81f;
            phi_f14 = 0.19f;
        }

        switch (bankEntry->sfxParams & SFX_PARAM_DIST_RANGE_MASK) {
            case 0:
                baseDist = 500.0f;
                break;

            case 1:
                baseDist = 666.6667f;
                break;

            case 2:
                baseDist = 952.381f;
                break;

            case 3:
                baseDist = 3846.154f;
                break;

            case 4:
                baseDist = 1000.0f;
                break;

            case 5:
                baseDist = 666.6667f;
                break;

            case 6:
                baseDist = 500.0f;
                break;

            case 7:
                baseDist = 400.0f;
                break;
        }

        minDist = baseDist / 5.0f;

        if (bankEntry->dist < minDist) {
            volume = 1.0f;
        } else if (bankEntry->dist < baseDist) {
            volume =
                ((((baseDist - minDist) - (bankEntry->dist - minDist)) / (baseDist - minDist)) * phi_f14) + phi_f12;
        } else {
            volume = (1.0f - ((bankEntry->dist - baseDist) / (10000.0f - baseDist))) * phi_f12;
        }

        volume = SQ(volume);
    }

    return volume;
}

s8 AudioSfx_ComputeReverb(u8 bankId, u8 entryIndex, u8 channelIndex) {
    s8 distAdd = 0;
    s32 scriptAdd = 0;
    SfxBankEntry* entry = &gSfxBanks[bankId][entryIndex];
    s32 reverb;

    if (!(entry->sfxParams & SFX_FLAG_REVERB_NO_DIST)) {
        if (entry->dist < 2500.0f) {
            distAdd = *entry->posZ > 0.0f ? (entry->dist / 2500.0f) * 70.0f : (entry->dist / 2500.0f) * 91.0f;
        } else {
            distAdd = 70;
        }
    }

    if (IS_SEQUENCE_CHANNEL_VALID(gAudioContext.seqPlayers[SEQ_PLAYER_SFX].channels[channelIndex])) {
        scriptAdd = gAudioContext.seqPlayers[SEQ_PLAYER_SFX].channels[channelIndex]->soundScriptIO[1];
        if (gAudioContext.seqPlayers[SEQ_PLAYER_SFX].channels[channelIndex]->soundScriptIO[1] < 0) {
            scriptAdd = 0;
        }
    }

    reverb = (*entry->reverbAdd & 0x7F) + distAdd;

    if (entry->state != SFX_STATE_READY) {
        reverb += scriptAdd;
    }

    if ((bankId != BANK_OCARINA) || (SFX_INDEX(entry->sfxId) >= 2)) {
        reverb += sAudioEnvReverb + (sAudioCodeReverb & 0x3F) + sSpecReverb;
    }

    if (reverb > 0x7F) {
        reverb = 0x7F;
    }

    return reverb;
}

s8 AudioSfx_ComputePanSigned(f32 x, f32 z, u8 token) {
    f32 absX = ABS_ALT(x);
    f32 absZ = ABS_ALT(z);
    f32 pan;

    if (absX > 8000.0f) {
        absX = 8000.0f;
    }

    if (absZ > 8000.0f) {
        absZ = 8000.0f;
    }

    if ((x == 0.0f) && (z == 0.0f)) {
        pan = 0.5f;
    } else if (absZ <= absX) {
        pan = (16000.0f - absX) / (4.5f * (16000.0f - absZ));
        if (x >= 0.0f) {
            pan = 1.0f - pan;
        }
    } else {
        pan = (x / (3.6f * absZ)) + 0.5f;
    }

    if ((absZ < 50.0f) && (absX < 50.0f)) {
        pan = ((pan - 0.5f) * SQ(absX / 50.0f)) + 0.5f;
    }

    return (pan * 127.0f) + 0.5f;
}

f32 AudioSfx_ComputeFreqScale(u8 bankId, u8 entryIndex) {
    s32 applyRandScaling = false;
    SfxBankEntry* entry = &gSfxBanks[bankId][entryIndex];
    f32 dist;
    f32 freq = 1.0f;

    if (entry->sfxParams & SFX_PARAM_RAND_FREQ_LOWER) {
        freq = 1.0f - ((gAudioContext.audioRandom & 0xF) / 192.0f);
    }

    switch (bankId) {
        case BANK_VOICE:
            if (((entry->sfxId & 0xFF) < 0x40) && (sAudioBaseFilter2 != 0)) {
                applyRandScaling = true;
            } else if (((entry->sfxId & 0xFF) >= 0x40) && (sAudioExtraFilter2 != 0)) {
                applyRandScaling = true;
            }
            break;

        case BANK_PLAYER:
        case BANK_ITEM:
            if (sAudioBaseFilter2 != 0) {
                applyRandScaling = true;
            }
            break;

        case BANK_ENV:
        case BANK_ENEMY:
            if (((*entry->reverbAdd & 0x80) != 0) | (sAudioExtraFilter2 != 0)) {
                applyRandScaling = true;
            }
            break;

        case BANK_SYSTEM:
        case BANK_OCARINA:
            break;

        default:
            break;
    }

    if ((applyRandScaling == true) && !(entry->sfxParams & SFX_PARAM_RAND_FREQ_SCALE)) {
        freq *= 1.0293 - ((gAudioContext.audioRandom & 0xF) / 144.0f);
    }

    dist = entry->dist;
    if (!(entry->sfxParams & SFX_FLAG_VOLUME_NO_DIST) && !(entry->sfxParams & SFX_FLAG_FREQ_NO_DIST)) {
        if (dist >= 10000.0f) {
            freq += 0.2f;
        } else {
            freq += (0.2f * (dist / 10000.0f));
        }
    }

    if ((entry->sfxParams & SFX_PARAM_RAND_FREQ_RAISE_MASK) != (0 << SFX_PARAM_RAND_FREQ_RAISE_SHIFT)) {
        freq += (entry->randFreq / 192.0f);
    }

    return freq;
}

u8 AudioSfx_ComputeSurroundSoundFilter(f32 behindScreenZ, SfxBankEntry* entry, s8 panSigned) {
    u8 lowPassCutoff;
    u8 highPassCutoff;
    u16* sfxParams;
    f32 distParam;
    f32 dist;

    // Remnant of OoT
    if (*entry->posZ < behindScreenZ) {
        lowPassCutoff = 0;
    } else {
        lowPassCutoff = 0;
    }

    sfxParams = &entry->sfxParams;

    if (*sfxParams & SFX_FLAG_SURROUND_LOWPASS_FILTER) {
        lowPassCutoff = 0xF;
    }

    switch ((*sfxParams & SFX_PARAM_DIST_RANGE_MASK)) {
        case 0:
            distParam = 15.0f;
            break;

        case 1:
            distParam = 12.0f;
            break;

        case 2:
            distParam = 9.0f;
            break;

        case 3:
            distParam = 6.0f;
            break;

        case 4:
            distParam = 18.0f;
            break;

        case 5:
            distParam = 21.0f;
            break;

        case 6:
            distParam = 24.0f;
            break;

        case 7:
            distParam = 27.0f;
            break;

        default:
            break;
    }

    if (!(entry->sfxFlags & SFX_FLAG2_SURROUND_NO_HIGHPASS_FILTER)) {
        if (entry->dist > 1923.077f) {
            dist = 1923.077f;
        } else {
            dist = entry->dist;
        }

        highPassCutoff = (distParam * dist) / (2 * 1923.077f);
    } else {
        highPassCutoff = 0;
    }

    return (lowPassCutoff << 4) + highPassCutoff;
}

s8 AudioSfx_ComputeCombFilter(f32 posY, u16 sfxParams) {
    s8 combFilterGain;

    if (posY < 0.0f) {
        if (posY < -625.0f) {
            combFilterGain = -32;
        } else {
            combFilterGain = (s8)(((625.0f + posY) / 625.0f) * 31.0f) + 0xE0;
        }
    } else if (posY > 1250.0f) {
        combFilterGain = 127;
    } else {
        combFilterGain = (posY / 1250.0f) * 126.0f;
    }

    return combFilterGain | 1;
}

void AudioSfx_SetProperties(u8 bankId, u8 entryIndex, u8 channelIndex) {
    static s8 sZVolumes[] = {
        0,  2,  4,   6,   8,   10,  12,  14,  16,  18,  20,  22,  24,  25,  26,  27,  28,  29,  30, 31, 32, 33,
        34, 35, 36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52, 53, 54, 55,
        56, 56, 57,  57,  58,  58,  59,  59,  60,  60,  60,  61,  61,  61,  62,  62,  62,  63,  63, 63, 64, 64,
        64, 65, 65,  65,  66,  66,  66,  67,  67,  67,  68,  68,  69,  69,  70,  70,  71,  71,  72, 73, 74, 75,
        76, 77, 78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94, 95, 96, 97,
        98, 99, 100, 101, 102, 103, 105, 107, 109, 111, 113, 115, 117, 119, 121, 123, 125, 127,
    };
    f32 volume = 1.0f;
    s8 volumeS8;
    s8 reverb = 0;
    f32 freqScale = 1.0f;
    s8 panSigned = 0x40;
    u8 pad;
    u8 filter = 0;
    s8 combFilterGain = 0;
    s8 zVolume = -1;
    f32 behindScreenZ;
    u8 baseFilter = 0;
    SfxBankEntry* entry = &gSfxBanks[bankId][entryIndex];
    s32 pad2;

    switch (bankId) {
        case BANK_PLAYER:
        case BANK_ITEM:
        case BANK_ENV:
        case BANK_ENEMY:
        case BANK_VOICE:
            if (sSoundMode == SOUNDMODE_SURROUND) {
                combFilterGain = AudioSfx_ComputeCombFilter(*entry->posY, entry->sfxParams);
            }
            // fallthrough
        case BANK_OCARINA:
            entry->dist = sqrtf(entry->dist * 10.0f);
            volume = AudioSfx_ComputeVolume(bankId, entryIndex) * *entry->volume;
            reverb = AudioSfx_ComputeReverb(bankId, entryIndex, channelIndex);
            panSigned = AudioSfx_ComputePanSigned(*entry->posX, *entry->posZ, entry->token);
            freqScale = AudioSfx_ComputeFreqScale(bankId, entryIndex) * *entry->freqScale;

            if (sSoundMode == SOUNDMODE_SURROUND) {
                if (*entry->posZ >= 0.0f) {
                    if (*entry->posZ < 200.0f) {
                        zVolume = 32.0f - ((*entry->posZ / 300.0f) * 32.0f);
                    } else {
                        zVolume = 0;
                    }
                } else if (*entry->posZ < 0.0f) {
                    if (*entry->posZ > -300.0f) {
                        zVolume = 32.0f - ((*entry->posZ / 300.0f) * 95.0f);
                    } else {
                        zVolume = 127;
                    }
                }
                zVolume = sZVolumes[zVolume];
            }

            if (sAudioBaseFilter != 0) {
                if ((bankId == BANK_PLAYER) || (bankId == BANK_ITEM) ||
                    ((bankId == BANK_VOICE) && (((entry->sfxId & 0xFF) < 0x40) || ((entry->sfxId & 0xFF) >= 0x80)))) {
                    baseFilter = sAudioBaseFilter;
                    if (sAudioExtraFilter) {
                        reverb >>= 2;
                    }
                }
            }

            if (((*entry->reverbAdd & 0x80) | baseFilter | sAudioExtraFilter |
                 (entry->sfxFlags & SFX_FLAG2_APPLY_LOWPASS_FILTER)) != 0) {
                filter = ((((*entry->reverbAdd & 0x80) >> 2) | baseFilter | sAudioExtraFilter |
                           ((entry->sfxFlags & SFX_FLAG2_APPLY_LOWPASS_FILTER) >> 2)) *
                          2);
                filter &= 0xFF;
            } else if ((sSoundMode == SOUNDMODE_SURROUND) && !(entry->sfxParams & SFX_FLAG_VOLUME_NO_DIST)) {
                filter = AudioSfx_ComputeSurroundSoundFilter(behindScreenZ, entry, panSigned);
            }
            break;

        case BANK_SYSTEM:
            break;
    }

    if (sSfxChannelState[channelIndex].volume != volume) {
        volumeS8 = (u8)(volume * 127.0f);
        sSfxChannelState[channelIndex].volume = volume;
    } else {
        volumeS8 = -1;
    }

    //! FAKE:
    if (1) {}

    // CHAN_UPD_SCRIPT_IO (slot 2, sets volume)
    AudioThread_QueueCmdS8((0x6 << 24) | (SEQ_PLAYER_SFX << 16) | (channelIndex << 8) | 2, volumeS8);

    if (sSfxChannelState[channelIndex].reverb != reverb) {
        sSfxChannelState[channelIndex].reverb = reverb;
    }
    if (sSfxChannelState[channelIndex].freqScale != freqScale) {
        sSfxChannelState[channelIndex].freqScale = freqScale;
    }
    if (sSfxChannelState[channelIndex].stereoBits != 0) {
        sSfxChannelState[channelIndex].stereoBits = 0;
    }
    if (sSfxChannelState[channelIndex].filter != filter) {
        sSfxChannelState[channelIndex].filter = filter;
    }
    if (sSfxChannelState[channelIndex].combFilterGain != combFilterGain) {
        sSfxChannelState[channelIndex].combFilterGain = combFilterGain;
    }
    if (sSfxChannelState[channelIndex].zVolume != zVolume) {
        sSfxChannelState[channelIndex].zVolume = zVolume;
    }
    if (sSfxChannelState[channelIndex].panSigned != panSigned) {
        sSfxChannelState[channelIndex].panSigned = panSigned;
    }
}

u32 AudioSfx_SetFreqAndStereoBits(u8 seqScriptValIn, SequenceChannel* channel) {
    channel->stereo.asByte = sSfxChannelState[seqScriptValIn].stereoBits;
    channel->freqScale = sSfxChannelState[seqScriptValIn].freqScale;
    channel->changes.s.freqScale = true;

    return seqScriptValIn;
}

void AudioSfx_ResetSfxChannelState(void) {
    SfxChannelState* state;
    u8 i;

    for (i = 0; i < ARRAY_COUNT(sSfxChannelState); i++) {
        state = &sSfxChannelState[i];
        state->volume = 1.0f;
        state->freqScale = 1.0f;
        state->reverb = 0;
        state->panSigned = 0x40;
        state->stereoBits = 0;
        state->filter = 0xFF;
        state->combFilterGain = 0xFF;
        state->zVolume = 0xFF;
    }

    sSfxChannelState[SFX_CHANNEL_OCARINA].combFilterGain = 0;
    sPrevSeqMode = SEQ_MODE_DEFAULT;
    sAudioCodeReverb = 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/play_sound.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F128.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F170.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/Audio_PlaySfxAtPos.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F208.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F230.s")

SfxSettings* AudioSfx_AddSfxSetting(Vec3f* pos) {
    SfxSettings* sfxSettings;
    u8 i = 0;
    u8 sfxSettingIndex = 0xFF;

    for (; i < ARRAY_COUNT(sSfxSettings); i++) {
        sfxSettings = &sSfxSettings[i];

        if ((sfxSettings->pos == NULL) && (sfxSettingIndex == 0xFF)) {
            sfxSettingIndex = i;
        }

        if (sfxSettings->pos == pos) {
            return sfxSettings;
        }
    }

    if (sfxSettingIndex != 0xFF) {
        sSfxSettingsFlags |= 1 << sfxSettingIndex;
        sfxSettings = &sSfxSettings[sfxSettingIndex];
        sfxSettings->pos = pos;
        return sfxSettings;
    }

    return NULL;
}

void AudioSfx_ProcessSfxSettings(void) {
    SfxBankEntry* entry;
    u8 sfxSettingsFlags;
    u8 sfxSettingIndex = 0;
    u8 bankId;
    u8 entryIndex;
    s32 found;

    if (sSfxSettingsFlags != 0) {
        sfxSettingsFlags = sSfxSettingsFlags;

        while (sfxSettingsFlags != 0) {
            bankId = BANK_ENV;
            if ((sfxSettingsFlags & (1 << sfxSettingIndex))) {

                found = false;
                while ((bankId <= BANK_ENEMY) && !found) {
                    entryIndex = gSfxBanks[bankId]->next;

                    while (entryIndex != 0xFF) {
                        entry = &gSfxBanks[bankId][entryIndex];
                        entryIndex = 0xFF;
                        if (entry->posX == &sSfxSettings[sfxSettingIndex].pos->x) {
                            found = true;
                        } else {
                            entryIndex = entry->next;
                        }
                    }
                    bankId++;
                }

                if (!found) {
                    sSfxSettingsFlags ^= (1 << sfxSettingIndex);
                    sSfxSettings[sfxSettingIndex].pos = NULL;
                }

                sfxSettingsFlags ^= (1 << sfxSettingIndex);
            }
            sfxSettingIndex++;
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F420.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F4AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F540.s")

void AudioSfx_LowerSfxSettingsReverb(Vec3f* pos, s8 isReverbLowered) {
    SfxSettings* sfxSettings = AudioSfx_AddSfxSetting(pos);

    if (sfxSettings != NULL) {
        if (isReverbLowered) {
            sfxSettings->reverbAdd = -0x80;
        } else {
            sfxSettings->reverbAdd = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F5AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F638.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F780.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F7D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F830.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F88C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F900.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019FA18.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019FAD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019FB0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019FC20.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019FCB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019FD90.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019FDC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019FE1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019FE74.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019FEDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019FF38.s")

/**
 * Used for EnRiverSound
 */
void Audio_PlaySfxForRiver(Vec3f* pos, f32 freqScale) {
    if (!AudioSfx_IsPlaying(NA_SE_EV_RIVER_STREAM - SFX_FLAG)) {
        sRiverFreqScaleLerp.value = freqScale;
    } else if (freqScale != sRiverFreqScaleLerp.value) {
        sRiverFreqScaleLerp.target = freqScale;
        sRiverFreqScaleLerp.remainingFrames = 40;
        sRiverFreqScaleLerp.step = (sRiverFreqScaleLerp.target - sRiverFreqScaleLerp.value) / 40;
    }
    AudioSfx_PlaySfx(NA_SE_EV_RIVER_STREAM - SFX_FLAG, pos, 4, &sRiverFreqScaleLerp.value, &gSfxDefaultFreqAndVolScale,
                     &gSfxDefaultReverb);
}

/**
 * Unused remnant of OoT's EnRiverSound
 * Used for Zora's River Waterfall
 */
void Audio_PlaySfxForWaterfall(Vec3f* pos, f32 freqScale) {
    if (!AudioSfx_IsPlaying(NA_SE_EV_WATER_WALL_BIG - SFX_FLAG)) {
        sWaterfallFreqScaleLerp.value = freqScale;
    } else if (freqScale != sWaterfallFreqScaleLerp.value) {
        sWaterfallFreqScaleLerp.target = freqScale;
        sWaterfallFreqScaleLerp.remainingFrames = 40;
        sWaterfallFreqScaleLerp.step = (sWaterfallFreqScaleLerp.target - sWaterfallFreqScaleLerp.value) / 40;
    }
    AudioSfx_PlaySfx(NA_SE_EV_WATER_WALL_BIG - SFX_FLAG, pos, 4, &sWaterfallFreqScaleLerp.value,
                     &sWaterfallFreqScaleLerp.value, &gSfxDefaultReverb);
}

/**
 * Used for EnRiverSound variables
 */
void Audio_StepFreqLerp(FreqLerp* lerp) {
    if (lerp->remainingFrames != 0) {
        lerp->remainingFrames--;
        if (lerp->remainingFrames != 0) {
            lerp->value += lerp->step;
        } else {
            lerp->value = lerp->target;
        }
    }
}

f32 sBigBellsVolume[8] = {
    1.0f, 0.9f, 0.8f, 0.7f, 0.6f, 0.5f, 0.4f, 0.3f,
};
#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A0124.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A0184.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A01C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A0204.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A0238.s")

/**
 * Unused remnant from OoT's EnRiverSound
 * Was designed to incrementally increase volume of NA_BGM_GANON_TOWER for each new room during the climb of Ganon's
 * Tower
 */
void Audio_SetGanonsTowerBgmVolumeLevel(u8 ganonsTowerLevel) {
    u8 channelIndex;
    s8 pan = 0;

    // Ganondorfs's Lair
    if (ganonsTowerLevel == 0) {
        pan = 0x7F;
    }

    for (channelIndex = 0; channelIndex < 16; channelIndex++) {
        // CHAN_UPD_PAN_UNSIGNED
        AudioThread_QueueCmdS8(((u8)(u32)channelIndex << 8) | 0x7000000, pan);
    }

    // Lowest room in Ganon's Tower (Entrance Room)
    if (ganonsTowerLevel == 7) {
        // Adds a delay to setting the volume in the first room
        sEnterGanonsTowerTimer = 2;
    } else {
        Audio_SetGanonsTowerBgmVolume(sGanonsTowerLevelsVol[ganonsTowerLevel % ARRAY_COUNTU(sGanonsTowerLevelsVol)]);
    }
}

/**
 * Unused remnant from OoT's EnRiverSound
 * If a new volume is requested for ganon's tower, update the volume and
 * calculate a new low-pass filter cutoff and reverb based on the new volume
 */
s32 Audio_SetGanonsTowerBgmVolume(u8 targetVolume) {
    u8 lowPassFilterCutoff;
    u8 channelIndex;
    u16 reverb;

    if (sGanonsTowerVol != targetVolume) {
        // Sets the volume
        Audio_SetVolumeScale(SEQ_PLAYER_BGM_MAIN, 0, targetVolume, 2);

        // Sets the filter cutoff of the form (lowPassFilterCutoff << 4) | (highPassFilter & 0xF). highPassFilter is
        // always set to 0
        if (targetVolume < 0x40) {
            // Only the first room
            lowPassFilterCutoff = 0x10;
        } else {
            // Higher volume leads to a higher cut-off frequency in the low-pass filtering
            lowPassFilterCutoff = (((targetVolume - 0x40) >> 2) + 1) << 4;
        }

        Audio_QueueSeqCmd((8 << 28) | ((u8)(SEQ_PLAYER_BGM_MAIN) << 24) | ((u8)(4) << 16) | ((u8)(15) << 8) |
                          (u8)(lowPassFilterCutoff));

        // Sets the reverb
        for (channelIndex = 0; channelIndex < ARRAY_COUNT(gAudioContext.seqPlayers[SEQ_PLAYER_BGM_MAIN].channels);
             channelIndex++) {
            if (&gAudioContext.sequenceChannelNone !=
                gAudioContext.seqPlayers[SEQ_PLAYER_BGM_MAIN].channels[channelIndex]) {
                // soundScriptIO[5] was set to 0x40 in channels 0, 1, and 4 (BGM no longer in OoT)
                if ((u8)gAudioContext.seqPlayers[SEQ_PLAYER_BGM_MAIN].channels[channelIndex]->soundScriptIO[5] !=
                    0xFF) {
                    // Higher volume leads to lower reverb
                    reverb =
                        (((u16)gAudioContext.seqPlayers[SEQ_PLAYER_BGM_MAIN].channels[channelIndex]->soundScriptIO[5] -
                          targetVolume) +
                         0x7F);

                    if (reverb > 0x7F) {
                        reverb = 0x7F;
                    }

                    // CHAN_UPD_REVERB
                    AudioThread_QueueCmdS8(_SHIFTL(5, 24, 8) | _SHIFTL(SEQ_PLAYER_BGM_MAIN, 16, 8) |
                                               _SHIFTL(channelIndex, 8, 8),
                                           (u8)reverb);
                }
            }
        }

        sGanonsTowerVol = targetVolume;
    }
    return -1;
}

/**
 * Unused remnant from OoT's EnRiverSound
 * Responsible for lowering market bgm in Child Market Entrance and Child Market Back Alley
 * Only lowers volume for 1 frame, so must be called every frame to maintain lower volume
 */
void Audio_LowerMainBgmVolume(u8 volume) {
    sRiverSoundMainBgmVol = volume;
    sRiverSoundMainBgmLower = true;
}

/**
 * Unused remnant from OoT's EnRiverSound
 * Still called by Audio_Update every frame, but none of these processes get initialized
 */
void Audio_UpdateRiverSoundVolumes(void) {
    // Updates Main Bgm Volume (RiverSound of type RS_LOWER_MAIN_BGM_VOLUME)
    if (sRiverSoundMainBgmLower == true) {
        if (sRiverSoundMainBgmCurrentVol != sRiverSoundMainBgmVol) {
            // lowers the volume for 1 frame
            Audio_SetVolumeScale(SEQ_PLAYER_BGM_MAIN, 0, sRiverSoundMainBgmVol, 10);
            sRiverSoundMainBgmCurrentVol = sRiverSoundMainBgmVol;
            sRiverSoundMainBgmRestore = true;
        }
        sRiverSoundMainBgmLower = false;
    } else if ((sRiverSoundMainBgmRestore == true) && !sAudioIsWindowOpen) {
        // restores the volume every frame
        Audio_SetVolumeScale(SEQ_PLAYER_BGM_MAIN, 0, 0x7F, 10);
        sRiverSoundMainBgmCurrentVol = 0x7F;
        sRiverSoundMainBgmRestore = false;
    }

    // Update Ganon's Tower Volume (RiverSound of type RS_GANON_TOWER_7)
    if (sEnterGanonsTowerTimer != 0) {
        sEnterGanonsTowerTimer--;
        if (sEnterGanonsTowerTimer == 0) {
            Audio_SetGanonsTowerBgmVolume(sGanonsTowerLevelsVol[7]);
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A0554.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A05E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A05F0.s")

void AudioSfx_SetChannelIO(Vec3f* pos, u16 sfxId, u8 ioData) {
    u8 channelIndex = 0;
    u8 bankId = SFX_BANK_SHIFT(sfxId);
    u8 entryIndex;
    u8 i;

    for (i = 0; i < bankId; i++) {
        channelIndex += gChannelsPerBank[gSfxChannelLayout][i];
    }

    for (i = 0; i < gChannelsPerBank[gSfxChannelLayout][bankId]; i++) {
        entryIndex = gActiveSfx[bankId][i].entryIndex;

        if (entryIndex != 0xFF) {
            if ((sfxId == gSfxBanks[bankId][entryIndex].sfxId) && (&pos->x == gSfxBanks[bankId][entryIndex].posX)) {
                AudioThread_QueueCmdS8(_SHIFTL(6, 24, 8) | _SHIFTL(SEQ_PLAYER_SFX, 16, 8) |
                                           _SHIFTL(channelIndex, 8, 8) | _SHIFTL(6, 0, 8),
                                       ioData);
            }
        }
        channelIndex++;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A0810.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A0868.s")

/**
 * Unused remnant of OoT's EnRiverSound (func_800F4E30)
 */
void func_801A09D4(Vec3f* pos, f32 xzDistToPlayer) {
    f32 volumeRel;
    s8 pan;
    u8 channelIndex;

    if (sRiverSoundBgmPos == NULL) {
        sRiverSoundBgmPos = pos;
        sRiverSoundXZDistToPlayer = xzDistToPlayer;
    } else if (sRiverSoundBgmPos != pos) {
        if (sRiverSoundXZDistToPlayer > xzDistToPlayer) {
            sRiverSoundBgmPos = pos;
            sRiverSoundXZDistToPlayer = xzDistToPlayer;
        }
    } else {
        sRiverSoundXZDistToPlayer = xzDistToPlayer;
    }

    if (sRiverSoundBgmPos->x > 100.0f) {
        pan = 0x7F;
    } else if (sRiverSoundBgmPos->x < -100.0f) {
        pan = 0;
    } else {
        pan = ((sRiverSoundBgmPos->x / 100.0f) * 64.0f) + 64.0f;
    }

    if (sRiverSoundXZDistToPlayer > 400.0f) {
        volumeRel = 0.1f;
    } else if (sRiverSoundXZDistToPlayer < 120.0f) {
        volumeRel = 1.0f;
    } else {
        volumeRel = ((1.0f - ((sRiverSoundXZDistToPlayer - 120.0f) / 280.0f)) * 0.9f) + 0.1f;
    }

    for (channelIndex = 0; channelIndex < 16; channelIndex++) {
        if (channelIndex != 9) {
            Audio_QueueSeqCmd(((u32)(6) << 28) | ((u32)(SEQ_PLAYER_BGM_MAIN) << 24) | ((u32)(2) << 16) |
                              ((u32)(channelIndex) << 8) | ((u8)(127.0f * volumeRel)));
            AudioThread_QueueCmdS8(0x03000000 | ((u8)((u32)channelIndex) << 8), pan);
        }
    }
}

/**
 * Unused remnant of OoT's EnRiverSound
 */
void Audio_ClearSariaBgm(void) {
    if (sRiverSoundBgmPos != NULL) {
        sRiverSoundBgmPos = NULL;
    }
}

/**
 * Unused remnant of OoT's EnRiverSound
 */
void Audio_ClearSariaBgmAtPos(Vec3f* pos) {
    if (sRiverSoundBgmPos == pos) {
        sRiverSoundBgmPos = NULL;
    }
}

u8 sBgmPlayers[2] = { SEQ_PLAYER_BGM_MAIN, SEQ_PLAYER_BGM_SUB };
void Audio_SplitBgmChannels(s8 volumeSplit);
#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/Audio_SplitBgmChannels.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A0E44.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A1290.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A1348.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A13BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A153C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A17F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A1904.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A1A10.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A1A8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A1D44.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A1DB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A1E0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A1F00.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A1F88.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A1FB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A2090.s")

/**
 * Unused remnant of OoT's EnRiverSound
 */
void Audio_PlaySariaBgm(Vec3f* pos, u16 seqId, u16 distMax) {
    f32 absY;
    f32 dist;
    u8 targetVolume;
    f32 prevDist;

    if (sRiverSoundBgmTimer != 0) {
        sRiverSoundBgmTimer--;
        return;
    }

    dist = sqrtf(SQ(pos->z) + (SQ(pos->x) + SQ(pos->y)));

    if (sRiverSoundBgmPos == NULL) {
        sRiverSoundBgmPos = pos;
        func_801A3238(SEQ_PLAYER_BGM_SUB, seqId, 0, 7, 2);
    } else {
        prevDist = sqrtf(SQ(sRiverSoundBgmPos->z) + SQ(sRiverSoundBgmPos->x));
        if (dist < prevDist) {
            sRiverSoundBgmPos = pos;
        } else {
            dist = prevDist;
        }
    }

    absY = ABS_ALT(pos->y);

    if ((distMax / 15.0f) < absY) {
        targetVolume = 0;
    } else if (dist < distMax) {
        targetVolume = (1.0f - (dist / distMax)) * 127.0f;
    } else {
        targetVolume = 0;
    }

    if (seqId != NA_BGM_FAIRY_FOUNTAIN) {
        Audio_SplitBgmChannels(targetVolume);
    }

    Audio_SetVolumeScale(SEQ_PLAYER_BGM_SUB, 3, targetVolume, 0);
    Audio_SetVolumeScale(SEQ_PLAYER_BGM_MAIN, 3, 0x7F - targetVolume, 0);
}

/**
 * Unused remnant of OoT's EnRiverSound
 */
void Audio_ClearSariaBgm2(void) {
    sRiverSoundBgmPos = NULL;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A246C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A2544.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A257C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A25E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A2670.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A2778.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A27E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A281C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A29D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A2BB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A2C20.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A2C44.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A2C88.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A2D54.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/Audio_IsSequencePlaying.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A2E54.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A2ED8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A2F88.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A2FC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3000.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3038.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3098.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A312C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A31EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3238.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A32CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3590.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A36F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3950.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A39F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3A7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3AC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3AEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3B48.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3B90.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3CD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3CF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3D54.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3D98.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3E38.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/Audio_SetCutsceneFlag.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3F6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3FB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A3FFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/audio_setBGM.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4058.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A41C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A41F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A429C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A42C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4324.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4348.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/Audio_SetSfxVolumeExceptSystemAndOcarinaBanks.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4428.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/Audio_PreNMI.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A44C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A44D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A46F8.s")

f32 sSfxOriginalPos[] = { 0.0f, 0.0f, 0.0f };
#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4748.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A479C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A47DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A48E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4A28.s")

u32 Audio_SetNatureAmbienceRandomBend(u8 seqScriptValIn, SequenceChannel* channel);
#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/Audio_SetNatureAmbienceRandomBend.s")

void Audio_Init(void) {
    AudioLoad_Init(NULL, 0);
}

void AudioSfx_Init(u16 fadeTimer) {
    u8 channelIndex;

    AudioThread_ScheduleProcessCmds();
    Audio_StartSequence(SEQ_PLAYER_SFX, NA_BGM_GENERAL_SFX, 0x70, fadeTimer);

    for (channelIndex = 0; channelIndex < ARRAY_COUNT(sSfxChannelState); channelIndex++) {
        AudioThread_QueueCmdS32(0x10 << 24 | SEQ_PLAYER_SFX << 16 | ((u8)(u32)channelIndex << 8),
                                &sSfxChannelState[channelIndex]);
    }

    AudioThread_QueueCmdS32(0xE4000000, AudioSfx_SetFreqAndStereoBits);
    AudioThread_QueueCmdS32(0xE4000001, Audio_SetNatureAmbienceRandomBend);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4D00.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4D50.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4DF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4E64.s")
