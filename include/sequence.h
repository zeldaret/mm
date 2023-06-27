#ifndef SEQUENCE_H
#define SEQUENCE_H

#define NA_BGM_GENERAL_SFX 0x00             // General Sound Effects
#define NA_BGM_AMBIENCE 0x01                // Ambient background noises
#define NA_BGM_TERMINA_FIELD 0x02           // Termina Field ("FIELD")
#define NA_BGM_CHASE 0x03                   // Forest Chase ("CHASE")
#define NA_BGM_MAJORAS_THEME 0x04           // Majora's Theme ("STALKID")
#define NA_BGM_CLOCK_TOWER 0x05             // The Clock Tower ("CLOCK_TOWER")
#define NA_BGM_STONE_TOWER_TEMPLE 0x06      // Stone Tower Temple ("RUIN_DUNGEON_FRONT")
#define NA_BGM_INV_STONE_TOWER_TEMPLE 0x07  // Stone Tower Temple Inverted ("RUIN_DUNGEON_REVERSE")
#define NA_BGM_FAILURE_0 0x08               // Missed Event 1 ("FAILURE_0")
#define NA_BGM_FAILURE_1 0x09               // Failed Milk Run ("FAILURE_1")
#define NA_BGM_HAPPY_MASK_SALESMAN 0x0A     // Happy Mask Salesman ("OMENYA")
#define NA_BGM_SONG_OF_HEALING 0x0B         // Song of Healing ("DEMO_CURE")
#define NA_BGM_SWAMP_REGION 0x0C            // Southern Swamp and Woodfall ("DAMP_AREA")
#define NA_BGM_ALIEN_INVASION 0x0D          // Ghost Attack ("UFO")
#define NA_BGM_SWAMP_CRUISE 0x0E            // Swamp Cruise ("JUNGLE_CREWS")
#define NA_BGM_SHARPS_CURSE 0x0F            // Sharp's Curse ("SHARP")
#define NA_BGM_GREAT_BAY_REGION 0x10        // Great Bay Coast ("SEA_AREA")
#define NA_BGM_IKANA_REGION 0x11            // Ikana Canyon ("IKANA_AREA")
#define NA_BGM_DEKU_PALACE 0x12             // Deku Palace ("DEKU_KING")
#define NA_BGM_MOUNTAIN_REGION 0x13         // Mountain Village ("SNOW_AREA")
#define NA_BGM_PIRATES_FORTRESS 0x14        // Pirates' Fortress ("PIRATE_AREA")
#define NA_BGM_CLOCK_TOWN_DAY_1 0x15        // Clock Town Day 1. This song's filename is dummied out in MM3D ("DUMMY_21")
#define NA_BGM_CLOCK_TOWN_DAY_2 0x16        // Clock Town Day 2. This song's filename is dummied out in MM3D ("DUMMY_22")
#define NA_BGM_CLOCK_TOWN_DAY_3 0x17        // Clock Town Day 3. This song's filename is dummied out in MM3D ("DUMMY_23")
#define NA_BGM_FILE_SELECT 0x18             // File Select ("FILE_SELECT")
#define NA_BGM_CLEAR_EVENT 0x19             // Event Clear ("EVENT_CLEAR")
#define NA_BGM_ENEMY 0x1A                   // Battle ("ENEMY")
#define NA_BGM_BOSS 0x1B                    // Boss Battle ("BOSS00")
#define NA_BGM_WOODFALL_TEMPLE 0x1C         // Woodfall Temple ("JUNGLE_DUNGEON")
#define NA_BGM_MARKET 0x1D                  // Clock Town Day 1. Duplicate of #15. Name comes from MM3D. ("MARKET")
#define NA_BGM_OPENING 0x1E                 // Forest Ambush ("OPENING")
#define NA_BGM_INSIDE_A_HOUSE 0x1F          // House ("LINK_HOUSE")
#define NA_BGM_GAME_OVER 0x20               // Game Over ("GAME_OVER")
#define NA_BGM_CLEAR_BOSS 0x21              // Boss Clear ("BOSS_CLEAR")
#define NA_BGM_GET_ITEM 0x22                // Item Obtained ("ITEM_GET")
#define NA_BGM_GATE_OPEN 0x23               // Clock Town Day 2. Duplicate of #16. In MM3D, it shares its filename with the Door of Time song from OoT ("GATE_OPEN")
#define NA_BGM_GET_HEART 0x24               // Complete a Heart Piece ("HEART_GET")
#define NA_BGM_TIMED_MINI_GAME 0x25         // Playing a timed Minigame ("MINI_GAME_2")
#define NA_BGM_GORON_RACE 0x26              // Goron Race ("GORON_RACE")
#define NA_BGM_MUSIC_BOX_HOUSE 0x27         // Music Box House ("ORGEL_HOUSE")
#define NA_BGM_FAIRY_FOUNTAIN 0x28          // Fairy's Fountain. ("GODESS")
#define NA_BGM_ZELDAS_LULLABY 0x29          // Zelda's Lullaby ("HIME")
#define NA_BGM_ROSA_SISTERS 0x2A            // Rosa Sisters' Dance ("SISTER_DANCER")
#define NA_BGM_OPEN_CHEST 0x2B              // Open Chest ("OPEN_TRE_BOX")
#define NA_BGM_MARINE_RESEARCH_LAB 0x2C     // Marine Research Laboratory ("DRUGSTORE")
#define NA_BGM_GIANTS_THEME 0x2D            // The Four Giants ("KYOJIN_ROOM")
#define NA_BGM_SONG_OF_STORMS 0x2E          // Guru-Guru's Song ("FUSHA")
#define NA_BGM_ROMANI_RANCH 0x2F            // Romani Ranch ("RONRON")
#define NA_BGM_GORON_VILLAGE 0x30           // Goron Village ("GORON")
#define NA_BGM_MAYORS_OFFICE 0x31           // Mayor Dotour ("MEETING")
#define NA_BGM_OCA_EPONA 0x32               // Ocarina Epona's Song ("OCA_EPONA")
#define NA_BGM_OCA_SUNS 0x33                // Ocarina Sun's Song ("OCA_SUNS")
#define NA_BGM_OCA_TIME 0x34                // Ocarina Song of Time ("TIME_NORMAL")
#define NA_BGM_OCA_STORM 0x35               // Ocarina Song of Storms ("OCA_STORM")
#define NA_BGM_ZORA_HALL 0x36               // Zora Hall ("ZORA")
#define NA_BGM_GET_NEW_MASK 0x37            // A New Mask ("MASK_GET")
#define NA_BGM_MINI_BOSS 0x38               // Mini Boss ("MIDDLE_BOSS")
#define NA_BGM_GET_SMALL_ITEM 0x39          // Small Item Obtained ("S_ITEM_GET")
#define NA_BGM_ASTRAL_OBSERVATORY 0x3A      // Astral Observatory ("TENMONDAI")
#define NA_BGM_CAVERN 0x3B                  // Clock Town Cavern ("NORMAL_DUNGEON")
#define NA_BGM_MILK_BAR 0x3C                // Milk Bar Latte ("MILK_BAR")
#define NA_BGM_ZELDA_APPEAR 0x3D            // Meet Zelda (OoT) ("APPEAR")
#define NA_BGM_WOODS_OF_MYSTERY 0x3E        // Woods of Mystery ("MAYOIMORI")
#define NA_BGM_GORON_GOAL 0x3F              // Goron Race Goal ("GORON_GOAL")
#define NA_BGM_HORSE 0x40                   // Gorman Race ("HORSE")
#define NA_BGM_HORSE_GOAL 0x41              // Race Finish ("HORSE_GOAL")
#define NA_BGM_INGO 0x42                    // Gorman Bros. ("INGO")
#define NA_BGM_KOTAKE_POTION_SHOP 0x43      // Kotake's Potion Shop ("KOTAKE_KOUME")
#define NA_BGM_SHOP 0x44                    // Store ("SHOP")
#define NA_BGM_OWL 0x45                     // Gaebora's Theme ("OWL")
#define NA_BGM_MINI_GAME 0x46               // Shooting Gallery Theme ("MINI_GAME")
#define NA_BGM_OCA_SOARING 0x47             // Ocarina Song of Soaring ("OCA_BIGWING")
#define NA_BGM_OCA_HEALING 0x48             // Ocarina Song of Healing ("OCA_CURE")
#define NA_BGM_INVERTED_SONG_OF_TIME 0x49   // Inverted Song of Time ("TIME_SPEED")
#define NA_BGM_SONG_OF_DOUBLE_TIME 0x4A     // Song of Double Time ("TIME_JUMP")
#define NA_BGM_SONATA_OF_AWAKENING 0x4B     // Sonata of Awakening ("DEMO_AWAKING")
#define NA_BGM_GORON_LULLABY 0x4C           // Goron Lullaby ("DEMO_LULLABY")
#define NA_BGM_NEW_WAVE_BOSSA_NOVA 0x4D     // New Wave Bossa Nova ("DEMO_TIDE")
#define NA_BGM_ELEGY_OF_EMPTINESS 0x4E      // Elegy of Emptiness ("DEMO_SHELL")
#define NA_BGM_OATH_TO_ORDER 0x4F           // Oath to Order ("DEMO_PLEDGE")
#define NA_BGM_SWORD_TRAINING_HALL 0x50     // Sword Training ("EXERCISE_HALL")
#define NA_BGM_GORON_LULLABY_INTRO 0x51     // Goron Lullaby Intro ("DEMO_LULLABY_HALF")
#define NA_BGM_LEARNED_NEW_SONG 0x52        // New Song ("OCA_YOUSEI")
#define NA_BGM_BREMEN_MARCH 0x53            // Bremen March ("FACEMASK")
#define NA_BGM_BALLAD_OF_THE_WIND_FISH 0x54 // Quartet performed in on the Milk Bar stage ("QUARTET")
#define NA_BGM_SONG_OF_SOARING 0x55         // Song of Soaring ("WING_WARP")
#define NA_BGM_MILK_BAR_DUPLICATE 0x56      // Milk Bar Latte. Duplicate of #60. ("MILK_BAR_DUMMY")
#define NA_BGM_FINAL_HOURS 0x57             // Final Hours ("TIME_LIMIT")
#define NA_BGM_MIKAU_RIFF 0x58              // Mikau's Tale ("MIKAU_LIFF")
#define NA_BGM_MIKAU_FINALE 0x59            // A single guitar chord. ("MIKAU_FIN")
#define NA_BGM_FROG_SONG 0x5A               // Don Gero's Song ("FROG_SONG")
#define NA_BGM_OCA_SONATA 0x5B              // Ocarina Sonata of Awakening ("OCA_AWAKING")
#define NA_BGM_OCA_LULLABY 0x5C             // Ocarina Goron Lullaby ("OCA_LULLABY")
#define NA_BGM_OCA_NEW_WAVE 0x5D            // Ocarina New Wave Bossa Nova ("OCA_TIDE")
#define NA_BGM_OCA_ELEGY 0x5E               // Ocarina Elegy of Emptiness ("OCA_SHELL")
#define NA_BGM_OCA_OATH 0x5F                // Ocarina Oath to Order ("OCA_PLEDGE")
#define NA_BGM_MAJORAS_LAIR 0x60            // Majora Boss Room. Duplicate of #87 ("LAST_DUNGEON")
#define NA_BGM_OCA_LULLABY_INTRO 0x61       // Ocarina Goron Lullaby Intro ("OCA_LULLABY_HALF")
#define NA_BGM_OCA_GUITAR_BASS_SESSION 0x62 // Bass and Guitar Session ("OCA_SESSION")
#define NA_BGM_PIANO_SESSION 0x63           // Piano Solo ("DEMO_SESSION")
#define NA_BGM_INDIGO_GO_SESSION 0x64       // The Indigo-Go's Rehearsal ("ALLPART_SESSION")
#define NA_BGM_SNOWHEAD_TEMPLE 0x65         // Snowhead Temple ("SILVER_DUNGEON")
#define NA_BGM_GREAT_BAY_TEMPLE 0x66        // Great Bay Temple ("DEEPBLUE_DUNGEON")
#define NA_BGM_NEW_WAVE_SAXOPHONE 0x67      // ("DEMO_TIDE_SAX")
#define NA_BGM_NEW_WAVE_VOCAL 0x68          // ("DEMO_TIDE_VOCAL")
#define NA_BGM_MAJORAS_WRATH 0x69           // Majora's Wrath ("MUJURA_1")
#define NA_BGM_MAJORAS_INCARNATION 0x6A     // Majora's Incarnation ("MUJURA_2")
#define NA_BGM_MAJORAS_MASK 0x6B            // Majora's Mask Battle ("MUJURA_3")
#define NA_BGM_BASS_PLAY 0x6C               // Bass Practice ("BASS_PLAY")
#define NA_BGM_DRUMS_PLAY 0x6D              // Drums Practice ("DRUMS_PLAY")
#define NA_BGM_PIANO_PLAY 0x6E              // Piano Practice ("PIANO_PLAY")
#define NA_BGM_IKANA_CASTLE 0x6F            // Ikana Castle ("IKANA_CASTLE")
#define NA_BGM_GATHERING_GIANTS 0x70        // Calling the Four Giants ("GATHERING")
#define NA_BGM_KAMARO_DANCE 0x71            // Kamaro's Dance ("CAMARO_DANCE")
#define NA_BGM_CREMIA_CARRIAGE 0x72         // Cremia's Carriage ("DONKEY_CART")
#define NA_BGM_KEATON_QUIZ 0x73             // Keaton ("QUIZ")
#define NA_BGM_END_CREDITS_1 0x74           // The End/Credits ("END_DEMO")
#define NA_BGM_OPENING_LOOP 0x75            // Similar to #30, but the part where Tatl and Tael attack never happens ("OPENING_LOOP")
#define NA_BGM_TITLE_THEME 0x76             // Title Screen ("TITLE")
#define NA_BGM_DUNGEON_APPEAR 0x77          // Surfacing of Woodfall ("DUNGEON_APPEAR")
#define NA_BGM_WOODFALL_CLEAR 0x78          // Woodfall Clear ("PURIFICATION_0")
#define NA_BGM_SNOWHEAD_CLEAR 0x79          // Snowhead Clear ("PURIFICATION_1")
#define NA_BGM_INTO_THE_MOON 0x7B           // To the Moon ("INTO_THE_MOON")
#define NA_BGM_GOODBYE_GIANT 0x7C           // The Giants departing during the ending ("GOODBYE_GIANT")
#define NA_BGM_TATL_AND_TAEL 0x7D           // Tatl and Tael ("CHAT")
#define NA_BGM_MOONS_DESTRUCTION 0x7E       // Moon's disappearance ("MOON_VANISH")
#define NA_BGM_NO_MUSIC 0x7F
#define NA_BGM_DISABLED 0xFFFF

#define SEQ_FLAG_ASYNC 0x8000

typedef enum {
    /*    0 */ SEQ_PLAYER_BGM_MAIN,
    /*    1 */ SEQ_PLAYER_FANFARE,
    /*    2 */ SEQ_PLAYER_SFX,
    /*    3 */ SEQ_PLAYER_BGM_SUB,
    /*    4 */ SEQ_PLAYER_AMBIENCE,
    /*    5 */ SEQ_PLAYER_MAX,
    /* 0xFF */ SEQ_PLAYER_INVALID = 0xFF
} SequencePlayerId;

typedef enum {
    /* 0 */ SEQ_MODE_DEFAULT,
    /* 1 */ SEQ_MODE_ENEMY,
    /* 2 */ SEQ_MODE_STILL, // Not moving or first-person view
    /* 3 */ SEQ_MODE_IGNORE
} SequenceMode;

typedef enum {
    /* 0x0 */ CHANNEL_IO_PORT_0,
    /* 0x1 */ CHANNEL_IO_PORT_1,
    /* 0x2 */ CHANNEL_IO_PORT_2,
    /* 0x3 */ CHANNEL_IO_PORT_3,
    /* 0x4 */ CHANNEL_IO_PORT_4,
    /* 0x5 */ CHANNEL_IO_PORT_5,
    /* 0x6 */ CHANNEL_IO_PORT_6,
    /* 0x7 */ CHANNEL_IO_PORT_7
} ChannelIOPort;

typedef enum {
    /* 0 */ VOL_SCALE_INDEX_BGM_MAIN,
    /* 1 */ VOL_SCALE_INDEX_FANFARE,
    /* 2 */ VOL_SCALE_INDEX_SFX,
    /* 3 */ VOL_SCALE_INDEX_BGM_SUB,
    /* 4 */ VOL_SCALE_INDEX_MAX
} VolumeScaleIndex; // May be worth using SequencePlayerId instead

typedef enum {
    /* 0x0 */ AMBIENCE_CHANNEL_STREAM_0,
    /* 0x1 */ AMBIENCE_CHANNEL_CRITTER_0,
    /* 0x2 */ AMBIENCE_CHANNEL_CRITTER_1,
    /* 0x3 */ AMBIENCE_CHANNEL_CRITTER_2,
    /* 0x4 */ AMBIENCE_CHANNEL_CRITTER_3,
    /* 0x5 */ AMBIENCE_CHANNEL_CRITTER_4,
    /* 0x6 */ AMBIENCE_CHANNEL_CRITTER_5,
    /* 0x7 */ AMBIENCE_CHANNEL_CRITTER_6,
    /* 0x8 */ AMBIENCE_CHANNEL_CRITTER_7,
    /* 0xC */ AMBIENCE_CHANNEL_STREAM_1 = 12,
    /* 0xD */ AMBIENCE_CHANNEL_SOUND_MODE,
    /* 0xE */ AMBIENCE_CHANNEL_RAIN,
    /* 0xF */ AMBIENCE_CHANNEL_LIGHTNING
} AmbienceChannelIndex; // seqPlayerIndex = SEQ_PLAYER_AMBIENCE

typedef enum {
    /* 0x00 */ AMBIENCE_ID_00,
    /* 0x01 */ AMBIENCE_ID_01,
    /* 0x02 */ AMBIENCE_ID_02,
    /* 0x03 */ AMBIENCE_ID_03,
    /* 0x04 */ AMBIENCE_ID_04,
    /* 0x05 */ AMBIENCE_ID_05,
    /* 0x06 */ AMBIENCE_ID_06,
    /* 0x07 */ AMBIENCE_ID_07,
    /* 0x08 */ AMBIENCE_ID_08,
    /* 0x09 */ AMBIENCE_ID_09,
    /* 0x0A */ AMBIENCE_ID_0A,
    /* 0x0B */ AMBIENCE_ID_0B,
    /* 0x0C */ AMBIENCE_ID_0C,
    /* 0x0D */ AMBIENCE_ID_0D,
    /* 0x0E */ AMBIENCE_ID_0E,
    /* 0x0F */ AMBIENCE_ID_0F,
    /* 0x10 */ AMBIENCE_ID_10,
    /* 0x11 */ AMBIENCE_ID_11,
    /* 0x12 */ AMBIENCE_ID_12,
    /* 0x13 */ AMBIENCE_ID_13,
    /* 0xFF */ AMBIENCE_ID_DISABLED = 0xFF
} AmbienceId; // seqPlayerIndex = SEQ_PLAYER_AMBIENCE

typedef enum {
    /* 0x00 */ AMBIENCE_STREAM_0,
    /* 0x01 */ AMBIENCE_STREAM_1,
    /* 0x02 */ AMBIENCE_STREAM_2,
    /* 0x03 */ AMBIENCE_STREAM_3
} AmbienceStreamId;

typedef enum {
    /* 0x00 */ AMBIENCE_CRITTER_00,
    /* 0x01 */ AMBIENCE_CRITTER_01,
    /* 0x02 */ AMBIENCE_CRITTER_02,
    /* 0x03 */ AMBIENCE_CRITTER_03,
    /* 0x04 */ AMBIENCE_CRITTER_04,
    /* 0x05 */ AMBIENCE_CRITTER_05,
    /* 0x06 */ AMBIENCE_CRITTER_06,
    /* 0x07 */ AMBIENCE_CRITTER_07,
    /* 0x08 */ AMBIENCE_CRITTER_08,
    /* 0x09 */ AMBIENCE_CRITTER_09,
    /* 0x0A */ AMBIENCE_CRITTER_10,
    /* 0x0B */ AMBIENCE_CRITTER_11,
    /* 0x0C */ AMBIENCE_CRITTER_12,
    /* 0x0D */ AMBIENCE_CRITTER_13,
    /* 0x0E */ AMBIENCE_CRITTER_14,
    /* 0x0F */ AMBIENCE_CRITTER_15,
    /* 0x10 */ AMBIENCE_CRITTER_16,
    /* 0x11 */ AMBIENCE_CRITTER_17,
    /* 0x12 */ AMBIENCE_CRITTER_18,
    /* 0x13 */ AMBIENCE_CRITTER_19
} AmbienceCritterId;

#define AMBIENCE_IO_CRITTER_0_TYPE(type)        AMBIENCE_CHANNEL_CRITTER_0, CHANNEL_IO_PORT_2, type
#define AMBIENCE_IO_CRITTER_0_BEND_PITCH(bend)  AMBIENCE_CHANNEL_CRITTER_0, CHANNEL_IO_PORT_3, bend
#define AMBIENCE_IO_CRITTER_0_NUM_LAYERS(num)   AMBIENCE_CHANNEL_CRITTER_0, CHANNEL_IO_PORT_4, num
#define AMBIENCE_IO_CRITTER_0_PORT5(reverb)     AMBIENCE_CHANNEL_CRITTER_0, CHANNEL_IO_PORT_5, reverb

#define AMBIENCE_IO_CRITTER_1_TYPE(type)        AMBIENCE_CHANNEL_CRITTER_1, CHANNEL_IO_PORT_2, type
#define AMBIENCE_IO_CRITTER_1_BEND_PITCH(bend)  AMBIENCE_CHANNEL_CRITTER_1, CHANNEL_IO_PORT_3, bend
#define AMBIENCE_IO_CRITTER_1_NUM_LAYERS(num)   AMBIENCE_CHANNEL_CRITTER_1, CHANNEL_IO_PORT_4, num
#define AMBIENCE_IO_CRITTER_1_PORT5(reverb)     AMBIENCE_CHANNEL_CRITTER_1, CHANNEL_IO_PORT_5, reverb

#define AMBIENCE_IO_CRITTER_2_TYPE(type)        AMBIENCE_CHANNEL_CRITTER_2, CHANNEL_IO_PORT_2, type
#define AMBIENCE_IO_CRITTER_2_BEND_PITCH(bend)  AMBIENCE_CHANNEL_CRITTER_2, CHANNEL_IO_PORT_3, bend
#define AMBIENCE_IO_CRITTER_2_NUM_LAYERS(num)   AMBIENCE_CHANNEL_CRITTER_2, CHANNEL_IO_PORT_4, num
#define AMBIENCE_IO_CRITTER_2_PORT5(reverb)     AMBIENCE_CHANNEL_CRITTER_2, CHANNEL_IO_PORT_5, reverb

#define AMBIENCE_IO_CRITTER_3_TYPE(type)        AMBIENCE_CHANNEL_CRITTER_3, CHANNEL_IO_PORT_2, type
#define AMBIENCE_IO_CRITTER_3_BEND_PITCH(bend)  AMBIENCE_CHANNEL_CRITTER_3, CHANNEL_IO_PORT_3, bend
#define AMBIENCE_IO_CRITTER_3_NUM_LAYERS(num)   AMBIENCE_CHANNEL_CRITTER_3, CHANNEL_IO_PORT_4, num
#define AMBIENCE_IO_CRITTER_3_PORT5(reverb)     AMBIENCE_CHANNEL_CRITTER_3, CHANNEL_IO_PORT_5, reverb

#define AMBIENCE_IO_CRITTER_4_TYPE(type)        AMBIENCE_CHANNEL_CRITTER_4, CHANNEL_IO_PORT_2, type
#define AMBIENCE_IO_CRITTER_4_BEND_PITCH(bend)  AMBIENCE_CHANNEL_CRITTER_4, CHANNEL_IO_PORT_3, bend
#define AMBIENCE_IO_CRITTER_4_NUM_LAYERS(num)   AMBIENCE_CHANNEL_CRITTER_4, CHANNEL_IO_PORT_4, num
#define AMBIENCE_IO_CRITTER_4_PORT5(reverb)     AMBIENCE_CHANNEL_CRITTER_4, CHANNEL_IO_PORT_5, reverb

#define AMBIENCE_IO_CRITTER_5_TYPE(type)        AMBIENCE_CHANNEL_CRITTER_5, CHANNEL_IO_PORT_2, type
#define AMBIENCE_IO_CRITTER_5_BEND_PITCH(bend)  AMBIENCE_CHANNEL_CRITTER_5, CHANNEL_IO_PORT_3, bend
#define AMBIENCE_IO_CRITTER_5_NUM_LAYERS(num)   AMBIENCE_CHANNEL_CRITTER_5, CHANNEL_IO_PORT_4, num
#define AMBIENCE_IO_CRITTER_5_PORT5(reverb)     AMBIENCE_CHANNEL_CRITTER_5, CHANNEL_IO_PORT_5, reverb

#define AMBIENCE_IO_CRITTER_6_TYPE(type)        AMBIENCE_CHANNEL_CRITTER_6, CHANNEL_IO_PORT_2, type
#define AMBIENCE_IO_CRITTER_6_BEND_PITCH(bend)  AMBIENCE_CHANNEL_CRITTER_6, CHANNEL_IO_PORT_3, bend
#define AMBIENCE_IO_CRITTER_6_NUM_LAYERS(num)   AMBIENCE_CHANNEL_CRITTER_6, CHANNEL_IO_PORT_4, num
#define AMBIENCE_IO_CRITTER_6_PORT5(reverb)     AMBIENCE_CHANNEL_CRITTER_6, CHANNEL_IO_PORT_5, reverb

#define AMBIENCE_IO_STREAM_0_TYPE(type)         AMBIENCE_CHANNEL_STREAM_0, CHANNEL_IO_PORT_2, type
#define AMBIENCE_IO_STREAM_0_PORT3(data)        AMBIENCE_CHANNEL_STREAM_0, CHANNEL_IO_PORT_3, data
#define AMBIENCE_IO_STREAM_0_PORT4(data)        AMBIENCE_CHANNEL_STREAM_0, CHANNEL_IO_PORT_4, data

#define AMBIENCE_IO_STREAM_1_TYPE(type)         AMBIENCE_CHANNEL_STREAM_1, CHANNEL_IO_PORT_2, type
#define AMBIENCE_IO_STREAM_1_PORT3(data)        AMBIENCE_CHANNEL_STREAM_1, CHANNEL_IO_PORT_3, data
#define AMBIENCE_IO_STREAM_1_PORT4(data)        AMBIENCE_CHANNEL_STREAM_1, CHANNEL_IO_PORT_4, data

#define AMBIENCE_IO_RAIN_PORT4(data)            AMBIENCE_CHANNEL_RAIN, CHANNEL_IO_PORT_4, data

#define AMBIENCE_IO_ENTRIES_END 0xFF

#endif
