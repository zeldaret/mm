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
    /* 0x0 */ f32 vol;
    /* 0x4 */ f32 freqScale;
    /* 0x8 */ s8 reverb;
    /* 0x9 */ s8 panSigned;
    /* 0xA */ s8 stereoBits;
    /* 0xB */ u8 filter;
    /* 0xC */ u8 unk_0C;
    /* 0xD */ u8 unk_0D;
} SfxPlayerState; // size = 0xE

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

s32 AudioOcarina_MemoryGameGenerateNotes(void);
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
SfxPlayerState sSfxChannelState[16];

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
u32 sOcarinaUpdateTaskCurrent;
OcarinaControlStick sOcarinaInputStickRel;
u32 sOcarinaInputButtonCur;
u32 sOcarinaInputButtonStart;
u32 sOcarinaInputButtonPrev;
s32 sOcaInputBtnPress;
u8 sOcarinaResetDelay;
u8 sOcarinaResetUnused;
u8 sOcarinaHasStartedSong;
u8 sFirstOcarinaSongIndex;
u8 sLastOcarinaSongIndex;
u32 sOcarinaAvailSongs;
u8 sOcarinaStaffPlayingPos;
u16 sMusicStaffPos[OCARINA_SONG_MAX];
u16 sMusicStaffCurHeldLength[OCARINA_SONG_MAX];
u16 sMusicStaffExpectedLength[OCARINA_SONG_MAX];
u8 sMusicStaffExpectedPitch[OCARINA_SONG_MAX]; // Next required pitch in song playback
u8 D_801FD518[OCARINA_SONG_MAX];
u32 D_801FD530[OCARINA_SONG_MAX];
OcarinaNote sRecordingSongNote;
u16 sCustomSequencePc;

// Sfx Data
u8 D_801D6600[] = {
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
s8 sAudioFileSelectSetting = AUDIO_FS_STEREO;
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
u8 sPrevOcarinaPitch = 0;
u8 sCurOcarinaButtonIndex = 0;
u8 sMusicStaffPrevPitch = 0;
f32 sCurOcarinaBendFreq = 1.0f;
f32 sDefaultOcarinaVolume = 0.68503935f;
s8 sCurOcarinaBendIndex = 0;
s8 sCurOcarinaVolume = 0x57;
s8 sCurOcarinaVibrato = 0;
u8 sPlaybackState = 0;
u8 D_801D6FE4 = 0xFF;
u8 D_801D6FE8 = 0xFF;
u32 sOcarinaFlags = 0;
s32 sPlaybackNoteTimer = 0;
u16 sPlaybackNotePos = 0;
u16 sPlaybackStaffPos = 0;
u32 sPrevOcarinaSongFlags = 0; // Stores sOcarinaFlags but never used
u8 sPlaybackNoteValue = OCARINA_PITCH_NONE;
u8 sNotePlaybackVolume = 0;
u8 sNotePlaybackVibrato = 0;
s8 sNotePlaybackBend = 0;
f32 sNormalizedNotePlaybackTone = 1.0f;
f32 sNormalizedNotePlaybackVolume = 1.0f;
u32 sOcarinaPlaybackTaskStart = 0;
u32 sOcarinaWallCounter = 0;
u8 sCurOcarinaSong[8] = {
    OCARINA_PITCH_C4, OCARINA_PITCH_C4, OCARINA_PITCH_C4, OCARINA_PITCH_C4,
    OCARINA_PITCH_C4, OCARINA_PITCH_C4, OCARINA_PITCH_C4, OCARINA_PITCH_C4,
};
u8 sOcarinaSongAppendPos = 0;
u8 sOcarinaSongStartingPos = 0;

u8 sButtonToPitchMap[5] = {
    OCARINA_PITCH_D4, // OCARINA_BTN_A
    OCARINA_PITCH_F4, // OCARINA_BTN_C_DOWN
    OCARINA_PITCH_A4, // OCARINA_BTN_C_RIGHT
    OCARINA_PITCH_B4, // OCARINA_BTN_C_LEFT
    OCARINA_PITCH_D5, // OCARINA_BTN_C_UP
};

u8 sOcarinaMemoryGameAppendPos = 0;
u8 sOcaMemoryGameEndPos = 0;
u8 sOcaMemoryGameNumNotes[] = { 5, 6, 8 };
OcarinaNote sOcarinaSongNotes[OCARINA_SONG_MAX][20] = {
    // 0: Sonata of Awakening
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

    // 1: Goron Lullaby
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

    // 2: New Wave Bossa Nova
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

    // 3: Elegy of Emptyness
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

    // 4: Oath to Order
    {
        { OCARINA_PITCH_A4, 97, 104, 0, 0, 0 },
        { OCARINA_PITCH_F4, 48, 88, 0, 0, 0 },
        { OCARINA_PITCH_D4, 49, 78, 0, 0, 0 },
        { OCARINA_PITCH_F4, 49, 78, 0, 0, 0 },
        { OCARINA_PITCH_A4, 48, 94, 0, 0, 0 },
        { OCARINA_PITCH_D5, 97, 100, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 96, 0, 0, 0 },

    },

    // 5: Sarias Song
    {
        { OCARINA_PITCH_F4, 17, 84, 0, 0, 0 },
        { OCARINA_PITCH_A4, 17, 88, 0, 0, 0 },
        { OCARINA_PITCH_B4, 34, 80, 0, 0, 0 },
        { OCARINA_PITCH_F4, 17, 84, 0, 0, 0 },
        { OCARINA_PITCH_A4, 17, 88, 0, 0, 0 },
        { OCARINA_PITCH_B4, 136, 80, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // 6: Song of Time
    {
        { OCARINA_PITCH_A4, 32, 84, 0, 0, 0 },
        { OCARINA_PITCH_D4, 65, 88, 0, 0, 0 },
        { OCARINA_PITCH_F4, 33, 80, 0, 0, 0 },
        { OCARINA_PITCH_A4, 32, 84, 0, 0, 0 },
        { OCARINA_PITCH_D4, 65, 88, 0, 0, 0 },
        { OCARINA_PITCH_F4, 99, 80, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // 7: Song of Healing
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

    // 8: Eponas Song
    {
        { OCARINA_PITCH_D5, 18, 84, 0, 0, 0 },
        { OCARINA_PITCH_B4, 18, 88, 0, 0, 0 },
        { OCARINA_PITCH_A4, 72, 80, 0, 0, 0 },
        { OCARINA_PITCH_D5, 18, 84, 0, 0, 0 },
        { OCARINA_PITCH_B4, 18, 88, 0, 0, 0 },
        { OCARINA_PITCH_A4, 144, 80, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // 9: Song of Soaring
    {
        { OCARINA_PITCH_F4, 18, 84, 0, 0, 0 },
        { OCARINA_PITCH_B4, 18, 80, 0, 0, 0 },
        { OCARINA_PITCH_D5, 36, 94, 0, 0, 0 },
        { OCARINA_PITCH_F4, 18, 73, 0, 0, 0 },
        { OCARINA_PITCH_B4, 18, 76, 0, 0, 0 },
        { OCARINA_PITCH_D5, 108, 96, 2, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // 10: Song of Storms
    {
        { OCARINA_PITCH_D4, 11, 84, 0, 0, 0 },
        { OCARINA_PITCH_F4, 11, 88, 0, 0, 0 },
        { OCARINA_PITCH_D5, 45, 80, 0, 0, 0 },
        { OCARINA_PITCH_D4, 11, 84, 0, 0, 0 },
        { OCARINA_PITCH_F4, 11, 88, 0, 0, 0 },
        { OCARINA_PITCH_D5, 90, 80, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // 11: Suns Song
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

    // 12: Inverted Song of Time
    {
        { OCARINA_PITCH_F4, 32, 84, 0, 0, 0 },
        { OCARINA_PITCH_D4, 65, 88, 0, 0, 0 },
        { OCARINA_PITCH_A4, 33, 80, 0, 0, 0 },
        { OCARINA_PITCH_F4, 32, 84, 0, 0, 0 },
        { OCARINA_PITCH_D4, 65, 88, 0, 0, 0 },
        { OCARINA_PITCH_A4, 99, 80, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // 13: Song of Double Time
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

    // 14: Goron Lullaby Intro
    {
        { OCARINA_PITCH_D4, 32, 78, 0, 0, 0 },
        { OCARINA_PITCH_A4, 33, 90, 0, 0, 0 },
        { OCARINA_PITCH_B4, 33, 87, 0, 0, 0 },
        { OCARINA_PITCH_D4, 32, 92, 0, 0, 0 },
        { OCARINA_PITCH_A4, 33, 86, 0, 0, 0 },
        { OCARINA_PITCH_B4, 130, 80, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 66, 0, 0, 0 },
    },

    // 15: Milk Bar Jam "Ballad of the Wind Fish" Human
    {
        { OCARINA_PITCH_D5, 89, 80, 0, 0, 0 },
        { OCARINA_PITCH_A4, 41, 72, 0, 0, 0 },
        { OCARINA_PITCH_B4, 22, 84, 0, 0, 0 },
        { OCARINA_PITCH_A4, 91, 76, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 30, 66, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 66, 0, 0, 0 },
    },

    // 16: Milk Bar Jam "Ballad of the Wind Fish" Goron
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

    // 17: Milk Bar Jam "Ballad of the Wind Fish" Zora
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

    // 18: Milk Bar Jam "Ballad of the Wind Fish" Deku
    {
        { OCARINA_PITCH_A4, 54, 80, 0, 0, 0 },
        { OCARINA_PITCH_D4, 77, 72, 0, 0, 0 },
        { OCARINA_PITCH_F4, 19, 84, 0, 0, 0 },
        { OCARINA_PITCH_B4, 20, 76, 0, 0, 0 },
        { OCARINA_PITCH_A4, 78, 84, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 66, 0, 0, 0 },
    },

    // 19: Evan HP (Zora Band Leader) Song Part 1
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

    // 20: Evan HP (Zora Band Leader) Song Part 2
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

    // 21: Zeldas Lullaby
    {
        { OCARINA_PITCH_B4, 51, 84, 0, 0, 0 },
        { OCARINA_PITCH_D5, 25, 88, 0, 0, 0 },
        { OCARINA_PITCH_A4, 78, 80, 0, 0, 0 },
        { OCARINA_PITCH_B4, 51, 84, 0, 0, 0 },
        { OCARINA_PITCH_D5, 25, 88, 0, 0, 0 },
        { OCARINA_PITCH_A4, 100, 80, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 90, 0, 0, 0 },
    },

    // 22: Scarecrow
    {
        { OCARINA_PITCH_D4, 3, 0, 0, 0, 0 },
        { OCARINA_PITCH_NONE, 0, 255, 0, 0, 0 },
    },

    // 23: Termina Field 2D Song Buttons Appearing on Wall (In OoT, this is Ocarina Memory Game)
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

OcarinaNote* sPlaybackSong = sOcarinaSongNotes[OCARINA_SONG_SONATA];
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
u8 sIsOcarinaNoteChanged = false;

OcarinaNote sScarecrowsLongSongNotes[108] = {
    { OCARINA_PITCH_NONE, 0, 0, 0, 0, 0 },
    { OCARINA_PITCH_NONE, 0, 0, 0, 0, 0 },
};

OcarinaNote* gScarecrowLongSongPtr = sScarecrowsLongSongNotes;
u8* gScarecrowSpawnSongPtr = (u8*)&sOcarinaSongNotes[OCARINA_SONG_SCARECROW];
OcarinaNote* sTerminaWallSongPtr = sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL];

u8 sPitchToButtonMap[16] = {
    OCARINA_BTN_A,                            // OCARINA_PITCH_C4
    OCARINA_BTN_A,                            // OCARINA_PITCH_DFLAT4
    OCARINA_BTN_A,                            // OCARINA_PITCH_D4
    OCARINA_BTN_A,                            // OCARINA_PITCH_EFLAT4
    OCARINA_BTN_C_DOWN,                       // OCARINA_PITCH_E4
    OCARINA_BTN_C_DOWN,                       // OCARINA_PITCH_F4
    OCARINA_BTN_C_DOWN,                       // OCARINA_PITCH_GFLAT4
    OCARINA_BTN_C_RIGHT,                      // OCARINA_PITCH_G4
    OCARINA_BTN_C_RIGHT,                      // OCARINA_PITCH_AFLAT4
    OCARINA_BTN_C_RIGHT,                      // OCARINA_PITCH_A4
    OCARINA_BTN_C_RIGHT + OCARINA_BTN_C_LEFT, // OCARINA_PITCH_BFLAT4: Interface/Overlap between C_RIGHT and C_LEFT
    OCARINA_BTN_C_LEFT,                       // OCARINA_PITCH_B4
    OCARINA_BTN_C_LEFT,                       // OCARINA_PITCH_C5
    OCARINA_BTN_C_UP,                         // OCARINA_PITCH_DFLAT5
    OCARINA_BTN_C_UP,                         // OCARINA_PITCH_D5
    OCARINA_BTN_C_UP,                         // OCARINA_PITCH_EFLAT5
};

// seqData written in the music macro language
// Only used in unused functions
u8 sCustomSequenceScript[400] = {
    0xFE, 0xFE, 0xD3, 0x20, 0xD7, 0x00, 0x01, 0xCC, 0x00, 0x70, 0x90, 0x00, 0x16, 0xDB, 0x64, 0xDD, 0x78,
    0xFE, 0x00, 0xF3, 0xFC, 0xFF, 0xC3, 0x88, 0x00, 0x29, 0x89, 0x00, 0x2B, 0xDF, 0x7F, 0xE9, 0x0F, 0xDD,
    0x37, 0xD4, 0x40, 0xC1, 0x52, 0xFE, 0x80, 0xF3, 0xFC, 0xFF, 0xC2, 0xFB, 0xC0, 0x00, 0xC1, 0x57, 0xC9,
};

OcarinaSongButtons gOcarinaSongButtons[OCARINA_SONG_MAX] = {
    // 0: Sonata of Awakening
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

    // 1: Goron Lullaby
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

    // 2: New Wave Bossa Nova
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

    // 3: Elegy of Emptyness
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

    // 4: Oath to Order
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

    // 5; Sarias Song
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

    // 6: Song of Time
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

    // 7: Song of Healing
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

    // 8: Eponas Song
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

    // 9: Song of Soaring
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

    // 10: Song of Storms
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

    // 11: Suns Song
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

    // 12: Inverted Song of Time
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

    // 13; Song of Double Time
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

    // 14: Goron Lullaby Intro
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

    // 15: Milk Bar Jam "Ballad of the Wind Fish" Human
    {
        4,
        {
            OCARINA_BTN_C_UP,
            OCARINA_BTN_C_RIGHT,
            OCARINA_BTN_C_LEFT,
            OCARINA_BTN_C_RIGHT,
        },
    },

    // 16: Milk Bar Jam "Ballad of the Wind Fish" Goron
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

    // 17: Milk Bar Jam "Ballad of the Wind Fish" Zora
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

    // 18: Milk Bar Jam "Ballad of the Wind Fish" Deku
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

    // 19: Evan HP (Zora Band Leader) Song Part 1
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

    // 20: Evan HP (Zora Band Leader) Song Part 2
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

    // 21: Zeldas Lullaby
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

    // 22: Scarecrow
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

    // 23: Termina Field 2D Song Buttons Appearing on Wall (In OoT, this is Ocarina Memory Game)
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

// Static In-Function Data
u8 sScarecrowAfterCreditsState = 0;
u8 sScarecrowAfterCreditsIntrumentId = OCARINA_INSTRUMENT_DEFAULT;
u16 sScarecrowAfterCreditsTimer = 1200;
u8 sRequestCustomSequence = false;
s8 D_801D8B30[] = {
    0,  2,  4,   6,   8,   10,  12,  14,  16,  18,  20,  22,  24,  25,  26,  27,  28,  29,  30, 31, 32, 33,
    34, 35, 36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52, 53, 54, 55,
    56, 56, 57,  57,  58,  58,  59,  59,  60,  60,  60,  61,  61,  61,  62,  62,  62,  63,  63, 63, 64, 64,
    64, 65, 65,  65,  66,  66,  66,  67,  67,  67,  68,  68,  69,  69,  70,  70,  71,  71,  72, 73, 74, 75,
    76, 77, 78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94, 95, 96, 97,
    98, 99, 100, 101, 102, 103, 105, 107, 109, 111, 113, 115, 117, 119, 121, 123, 125, 127,
};
f32 sBigBellsVolume[8] = {
    1.0f, 0.9f, 0.8f, 0.7f, 0.6f, 0.5f, 0.4f, 0.3f,
};
u8 sBgmPlayers[2] = { SEQ_PLAYER_BGM_MAIN, SEQ_PLAYER_BGM_SUB };
f32 sSfxOriginalPos[] = { 0.0f, 0.0f, 0.0f };

// OoT's soundEffects from EnRiverSound
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

extern const u8 sIsOcarinaSongReserved[OCARINA_SONG_MAX];
/**
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
    true,  // OCARINA_SONG_SCARECROW
    false, // OCARINA_SONG_TERMINA_WALL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019AF00.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019AF58.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019AFE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019B02C.s")

void AudioOcarina_MapSongFromNotesToButtons(u8 noteSongIndex, u8 buttonSongIndex, u8 numButtons);
#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/AudioOcarina_MapSongFromNotesToButtons.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019B144.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019B378.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019B38C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019B3D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019B4B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/AudioOcarina_StartDefault.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019B568.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019B5AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019B5EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019B618.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019B654.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019B6B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019BC44.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019BE98.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019C1C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019C1D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019C268.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019C2E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/AudioOcarina_SetInstrumentId.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019C398.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019C5A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019C8D8.s")

const char sAudioOcarinaUnusedText0[] = "key step is too long !!! %d:%d>%d\n";
const char sAudioOcarinaUnusedText1[] = "You played %d Melody !!! (last step:%d)\n";
const char sAudioOcarinaUnusedText2[] = "pass 0\n";
const char sAudioOcarinaUnusedText3[] = "pass 1\n";
const char sAudioOcarinaUnusedText4[] = "pass 2\n";
const char sAudioOcarinaUnusedText5[] = "last key is bad !!! %d %d %02X %02X\n";
const char sAudioOcarinaUnusedText6[] = "last key step is too short !!! %d:%d %d<%d\n";
const char sAudioOcarinaUnusedText7[] = "check is over!!! %d %d %d\n";

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019CD08.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019CE34.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019CE6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019CEBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019CF6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019CF78.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/AudioOcarina_GetPlaybackStaff.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019CFA8.s")

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
    u8 randButtonIndex;
    u8 i;
    u8 j;

    do {
        i = 0;
        if (sOcarinaWallCounter++ % 2) {
            j = 0;

            for (; i < 8; i++) {
                randButtonIndex = Audio_NextRandom() % ARRAY_COUNT(sButtonToPitchMap);
                sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][j].pitch = sButtonToPitchMap[randButtonIndex];
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
            AudioOcarina_MapSongFromNotesToButtons(OCARINA_SONG_TERMINA_WALL, OCARINA_SONG_TERMINA_WALL, 8);
        } else {
            j = Audio_NextRandom() % ARRAY_COUNT(sOoTOcarinaSongNotes);
            ocarinaNote = sOoTOcarinaSongNotes[j];

            for (; ocarinaNote[i].length != 0; i++) {
                sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][i] = ocarinaNote[i];
            }

            sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][i].pitch = OCARINA_PITCH_NONE;
            sOcarinaSongNotes[OCARINA_SONG_TERMINA_WALL][i].length = 0;
            AudioOcarina_MapSongFromNotesToButtons(OCARINA_SONG_TERMINA_WALL, OCARINA_SONG_TERMINA_WALL,
                                                   sOoTOcarinaSongsNumNotes[j]);
        }
    } while (AudioOcarina_TerminaWallValidateNotes(OCARINA_SONG_TERMINA_WALL, OCARINA_SONG_TERMINA_WALL) != 0);
}

/**
 * Unused remnant of OoT
 */
void AudioOcarina_MemoryGameSetNumNotes(u8 minigameRound) {
    u8 i;

    if (minigameRound > 2) {
        minigameRound = 2;
    }

    sOcarinaMemoryGameAppendPos = 0;
    sOcaMemoryGameEndPos = sOcaMemoryGameNumNotes[minigameRound];

    for (i = 0; i < 3; i++) {
        AudioOcarina_MemoryGameGenerateNotes();
    }
}

/**
 * Unused remnant of OoT, Id 14 now represent Goron Lullaby Intro instead of the OoT ocarina memory game
 * //! @bug calling this function in MM will overwrite Goron Lullaby Intro
 */
#define OCARINA_SONG_MEMORYGAME 14
s32 AudioOcarina_MemoryGameGenerateNotes(void) {
    u32 randButtonIndex;
    u8 randPitch;

    if (sOcarinaMemoryGameAppendPos == sOcaMemoryGameEndPos) {
        return true;
    }

    randButtonIndex = Audio_NextRandom();
    randPitch = sButtonToPitchMap[randButtonIndex % ARRAY_COUNT(sButtonToPitchMap)];

    if (sOcarinaSongNotes[OCARINA_SONG_MEMORYGAME][sOcarinaMemoryGameAppendPos - 1].pitch == randPitch) {
        randPitch = sButtonToPitchMap[(randButtonIndex + 1) % ARRAY_COUNT(sButtonToPitchMap)];
    }

    sOcarinaSongNotes[OCARINA_SONG_MEMORYGAME][sOcarinaMemoryGameAppendPos].pitch = randPitch;
    sOcarinaSongNotes[OCARINA_SONG_MEMORYGAME][sOcarinaMemoryGameAppendPos].length = 45;
    sOcarinaSongNotes[OCARINA_SONG_MEMORYGAME][sOcarinaMemoryGameAppendPos].volume = 0x50;
    sOcarinaSongNotes[OCARINA_SONG_MEMORYGAME][sOcarinaMemoryGameAppendPos].vibrato = 0;
    sOcarinaSongNotes[OCARINA_SONG_MEMORYGAME][sOcarinaMemoryGameAppendPos].bend = 0;

    sOcarinaMemoryGameAppendPos++;

    sOcarinaSongNotes[OCARINA_SONG_MEMORYGAME][sOcarinaMemoryGameAppendPos].pitch = OCARINA_PITCH_NONE;
    sOcarinaSongNotes[OCARINA_SONG_MEMORYGAME][sOcarinaMemoryGameAppendPos].length = 0;
    sOcarinaSongNotes[OCARINA_SONG_MEMORYGAME][sOcarinaMemoryGameAppendPos + 1].pitch = OCARINA_PITCH_NONE;
    sOcarinaSongNotes[OCARINA_SONG_MEMORYGAME][sOcarinaMemoryGameAppendPos + 1].length = 0;
    if (1) {}
    return false;
}
#undef OCARINA_SONG_MEMORYGAME

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019D600.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019D758.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019D864.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019D8B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019D8E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019DF28.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019DF64.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019DFF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019E000.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019E00C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019E014.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019E0FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019E104.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019E110.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019E14C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019E324.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019E4B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019E634.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019E864.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019EA40.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019EB2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F024.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F05C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/play_sound.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F128.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F170.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/Audio_PlaySfxAtPos.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F208.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F230.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F258.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F300.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F420.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F4AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F540.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_8019F570.s")

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
    if (!Audio_IsSfxPlaying(NA_SE_EV_RIVER_STREAM - SFX_FLAG)) {
        sRiverFreqScaleLerp.value = freqScale;
    } else if (freqScale != sRiverFreqScaleLerp.value) {
        sRiverFreqScaleLerp.target = freqScale;
        sRiverFreqScaleLerp.remainingFrames = 40;
        sRiverFreqScaleLerp.step = (sRiverFreqScaleLerp.target - sRiverFreqScaleLerp.value) / 40;
    }
    Audio_PlaySfxGeneral(NA_SE_EV_RIVER_STREAM - SFX_FLAG, pos, 4, &sRiverFreqScaleLerp.value, &D_801DB4B0,
                         &D_801DB4B8);
}

/**
 * Unused remnant of OoT's EnRiverSound
 * Used for Zora's River Waterfall
 */
void Audio_PlaySfxForWaterfall(Vec3f* pos, f32 freqScale) {
    if (!Audio_IsSfxPlaying(NA_SE_EV_WATER_WALL_BIG - SFX_FLAG)) {
        sWaterfallFreqScaleLerp.value = freqScale;
    } else if (freqScale != sWaterfallFreqScaleLerp.value) {
        sWaterfallFreqScaleLerp.target = freqScale;
        sWaterfallFreqScaleLerp.remainingFrames = 40;
        sWaterfallFreqScaleLerp.step = (sWaterfallFreqScaleLerp.target - sWaterfallFreqScaleLerp.value) / 40;
    }
    Audio_PlaySfxGeneral(NA_SE_EV_WATER_WALL_BIG - SFX_FLAG, pos, 4, &sWaterfallFreqScaleLerp.value,
                         &sWaterfallFreqScaleLerp.value, &D_801DB4B8);
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
        Audio_QueueCmdS8(((u8)(u32)channelIndex << 8) | 0x7000000, pan);
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
                    Audio_QueueCmdS8(_SHIFTL(5, 24, 8) | _SHIFTL(SEQ_PLAYER_BGM_MAIN, 16, 8) |
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

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A0654.s")

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
            Audio_QueueCmdS8(0x03000000 | ((u8)((u32)channelIndex) << 8), pan);
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

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4380.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4428.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/Audio_PreNMI.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A44C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A44D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A46F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4748.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A479C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A47DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A48E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4A28.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4B80.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4C30.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4C54.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4D00.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4D50.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4DF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_8019AF00/func_801A4E64.s")
