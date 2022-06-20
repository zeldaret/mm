#ifndef SEQUENCE_H
#define SEQUENCE_H

#define NA_BGM_STOP 0x100000FF

#define NA_BGM_GENERAL_SFX 0x00             // General Sound Effects
#define NA_BGM_NATURE_AMBIENCE 0x01         // Ambient background noises
#define NA_BGM_TERMINA_FIELD 0x02           // Termina Field
#define NA_BGM_CHASE 0x03                   // Forest Chase
#define NA_BGM_MAJORAS_THEME 0x04           // Majora's Theme "STALKID"
#define NA_BGM_CLOCK_TOWER 0x05             // The Clock Tower
#define NA_BGM_STONE_TOWER_TEMPLE 0x06      // Stone Tower Temple
#define NA_BGM_INV_STONE_TOWER_TEMPLE 0x07  // Stone Tower Temple Inverted
#define NA_BGM_FAILURE_0 0x08               // Missed Event 1
#define NA_BGM_FAILURE_1 0x09               // Title
#define NA_BGM_HAPPY_MASK_SALESMAN 0x0A     // Mask Salesman "OMENYA"
#define NA_BGM_SONG_OF_HEALING 0x0B         // Song of Healing "DEMO_CURE"
#define NA_BGM_SWAMP_REGION 0x0C            // Southern Swamp and Woodfall "DAMP_AREA"
#define NA_BGM_ALIEN_INVASION 0x0D          // Ghost Attack "UFO"
#define NA_BGM_SWAMP_CRUISE 0x0E            // Mini Game "JUNGLE_CREWS"
#define NA_BGM_SHARPS_CURSE 0x0F            // Sharp's Curse
#define NA_BGM_GREAT_BAY_REGION 0x10        // Great Bay Coast "SEA_AREA"
#define NA_BGM_IKANA_REGION 0x11            // Ikana Valley
#define NA_BGM_DEKU_KING 0x12               // Court of the Deku King
#define NA_BGM_MOUNTAIN_REGION 0x13         // Mountain Village "SNOW_AREA"
#define NA_BGM_PIRATES_FORTRESS 0x14        // Pirates' Fortress "PIRATE_AREA"
#define NA_BGM_CLOCK_TOWN_DAY_1 0x15        // Clock Town Day 1 This song's filename is dummied out in MM3D "DUMMY_21"
#define NA_BGM_CLOCK_TOWN_DAY_2 0x16        // Clock Town Day 2 his song's filename is dummied out in MM3D "DUMMY_22"
#define NA_BGM_CLOCK_TOWN_DAY_3 0x17        // Clock Town Day 3 This song's filename is dummied out in MM3D "DUMMY_23"
#define NA_BGM_FILE_SELECT 0x18             // This song has no track name, as it's a duplicate of the Fairy's Fountain
#define NA_BGM_CLEAR_EVENT 0x19             // Event Clear
#define NA_BGM_ENEMY 0x1A                   // Battle
#define NA_BGM_BOSS 0x1B                    // Boss Battle
#define NA_BGM_WOODFALL_TEMPLE 0x1C         // Woodfall Temple "JUNGLE_DUNGEON"
#define NA_BGM_MARKET 0x1D                  // Clock Town Day 1		Duplicate of #15. Interesting filename in MM3D.	✘
#define NA_BGM_OPENING 0x1E                 // Forest Ambush
#define NA_BGM_INSIDE_A_HOUSE 0x1F          // House "LINK_HOUSE"
#define NA_BGM_GAME_OVER 0x20               // Game Over
#define NA_BGM_CLEAR_BOSS 0x21              // Boss Clear
#define NA_BGM_GET_ITEM 0x22                // Item Catch
#define NA_BGM_GATE_OPEN 0x23               // Clock Town Day 2 Duplicate of #16. In MM3D, it shares its filename with the Door of Time song from OoT
#define NA_BGM_GET_HEART 0x24               // Complete a Heart Piece
#define NA_BGM_MINI_GAME_2 0x25             // Playing Minigame
#define NA_BGM_GORON_RACE 0x26              // Goron Race
#define NA_BGM_MUSIC_BOX_HOUSE 0x27         // Music Box House "ORGEL_HOUSE"
#define NA_BGM_FAIRY_FOUNTAIN 0x28          // Fairy's Fountain In MM3D, it shares its filename with the Door of Time song from OoT "GODESS"
#define NA_BGM_ZELDAS_LULLABY 0x29          // Zelda's Lullaby "HIME"
#define NA_BGM_ROSA_SISTERS 0x2A            // Rosa Sisters' Dance "SISTER_DANCER"
#define NA_BGM_OPEN_CHEST 0x2B              // Open Chest "OPEN_TRE_BOX"
#define NA_BGM_MARINE_RESEARCH_LAB 0x2C     // Marine Research Laboratory "DRUGSTORE"
#define NA_BGM_GIANTS_THEME 0x2D            // The Four Giants "KYOJIN_ROOM"
#define NA_BGM_SONG_OF_STORMS 0x2E          // Guru-Guru's Song "FUSHA"
#define NA_BGM_ROMANI_RANCH 0x2F            // Romani Ranch "RONRON"
#define NA_BGM_GORON_VILLAGE 0x30           // Goron Village
#define NA_BGM_MAYORS_OFFICE 0x31           // Mayor Dotour "MEETING"
#define NA_BGM_OCA_EPONA 0x32               // Ocarina Epona's Song
#define NA_BGM_OCA_SUNS 0x33                // Ocarina Sun's Song
#define NA_BGM_OCA_TIME 0x34                // Ocarina Song of Time "TIME_NORMAL"
#define NA_BGM_OCA_STORM 0x35               // Ocarina Song of Storms
#define NA_BGM_ZORA_HALL 0x36               // Zora Hall
#define NA_BGM_GET_NEW_MASK 0x37            // A New Mask
#define NA_BGM_MINI_BOSS 0x38               // Mini Boss "MIDDLE_BOSS"
#define NA_BGM_GET_SMALL_ITEM 0x39          // Small Item Catch "S_ITEM_GET"
#define NA_BGM_ASTRAL_OBSERVATORY 0x3A      // Astral Observatory "TENMONDAI"
#define NA_BGM_CAVERN 0x3B                  // Clock Town Cavern "NORMAL_DUNGEON"
#define NA_BGM_MILK_BAR 0x3C                // Milk Bar Latte
#define NA_BGM_ZELDA_APPEAR 0x3D            // Meet Zelda (OoT)
#define NA_BGM_SARIAS_SONG 0x3E             // Saria's Theme Song from OoT "MAYOIMORI"
#define NA_BGM_GORON_GOAL 0x3F              // Goron Race Goal
#define NA_BGM_HORSE 0x40                   // Gorman Race
#define NA_BGM_HORSE_GOAL 0x41              // Race Finish
#define NA_BGM_INGO 0x42                    // Gorman Bros. "INGO"
#define NA_BGM_KOTAKE_POTION_SHOP 0x43      // Kotake's Potion Shop "KOTAKE_KOUME"
#define NA_BGM_SHOP 0x44                    // Store
#define NA_BGM_OWL 0x45                     // Gaebora's Theme
#define NA_BGM_MINI_GAME 0x46               // Target Practice
#define NA_BGM_OCA_SOARING 0x47             // Ocarina Song of Soaring "OCA_BIGWING"
#define NA_BGM_OCA_HEALING 0x48             // Ocarina Song of Healing "OCA_CURE"
#define NA_BGM_INVERTED_SONG_OF_TIME 0x49   // Inverted Song of Time "_SPEED"
#define NA_BGM_SONG_OF_DOUBLE_TIME 0x4A     // Song of Double Time "TIME_JUMP"
#define NA_BGM_SONATA_OF_AWAKENING 0x4B     // Sonata of Awakening "DEMO_AWAKING"
#define NA_BGM_GORON_LULLABY 0x4C           // Goron Lullaby "DEMO_LULLABY"
#define NA_BGM_NEW_WAVE_BOSSA_NOVA 0x4D     // New Wave Bossa Nova "DEMO_TIDE"
#define NA_BGM_ELEGY_OF_EMPTINESS 0x4E      // Elegy of Emptiness "DEMO_SHELL"
#define NA_BGM_OATH_TO_ORDER 0x4F           // Oath to Order "DEMO_PLEDGE"
#define NA_BGM_SWORD_TRAINING_HALL 0x50     // Sword Training "EXERCISE_HALL"
#define NA_BGM_GORON_LULLABY_INTRO 0x51     // Ocarina Goron Lullaby Intro "DEMO_LULLABY_HALF"
#define NA_BGM_OCA_FAIRY 0x52               // New Song "OCA_YOUSEI"
#define NA_BGM_BREMEN_MARCH 0x53            // Bremen March "FACEMASK"
#define NA_BGM_BALLAD_OF_THE_WIND_FISH 0x54 // Quartet performed in on the milk bar stage "QUARTET"
#define NA_BGM_SONG_OF_SOARING 0x55         // Song of Soaring "WING_WARP"
#define NA_BGM_MILK_BAR_DUPLICATE 0x56      // Milk Bar Latte		Duplicate. "MILK_BAR_DUMMY"
#define NA_BGM_FINAL_HOURS 0x57             // Final Hours "TIME_LIMIT"
#define NA_BGM_MIKAU_RIFF 0x58              // Mikau's Tale "MIKAU_LIFF"
#define NA_BGM_MIKAU_FINALE 0x59            // A single guitar chord. "MIKAU_FIN"
#define NA_BGM_FROG_SONG 0x5A               // Don Gero's Song
#define NA_BGM_OCA_SONATA 0x5B              // Ocarina Sonata of Awakening "OCA_AWAKING"
#define NA_BGM_OCA_LULLABY 0x5C             // Ocarina Goron Lullaby "OCA_LULLABY"
#define NA_BGM_OCA_NEW_WAVE 0x5D            // Ocarina New Wave Bossa Nova "OCA_TIDE"
#define NA_BGM_OCA_ELEGY 0x5E               // Ocarina Elegy of Emptiness "OCA_SHELL"
#define NA_BGM_OCA_OATH 0x5F                // Ocarina Oath to Order "OCA_PLEDGE"
#define NA_BGM_MAJORAS_LAIR 0x60            // "LAST_DUNGEON"
#define NA_BGM_OCA_LULLABY_INTRO 0x61       // "OCA_LULLABY_HALF"
#define NA_BGM_OCA_GUITAR_BASS_SESSION 0x62 // Bass and Guitar Session "OCA_SESSION"
#define NA_BGM_PIANO_SESSION 0x63           // Piano Solo "DEMO_SESSION"
#define NA_BGM_INDIGO_GO_SESSION 0x64       // The Indigo-Go's Rehearsal "ALLPART_SESSION"
#define NA_BGM_SNOWHEAD_TEMPLE 0x65         // Snowhead Temple "SILVER_DUNGEON"
#define NA_BGM_GREAT_BAY_TEMPLE 0x66        // Great Bay Temple "DEEPBLUE_DUNGEON"
#define NA_BGM_NEW_WAVE_SAXOPHONE 0x67      // "DEMO_TIDE_SAX"
#define NA_BGM_NEW_WAVE_VOCAL 0x68          // "DEMO_TIDE_VOCAL"
#define NA_BGM_MAJORAS_WRATH 0x69           // Majora's Wrath "MUJURA_1"
#define NA_BGM_MAJORAS_INCARNATION 0x6A     // Majora's Incarnation "MUJURA_2"
#define NA_BGM_MAJORAS_MASK 0x6B            // Majora's Mask Battle "MUJURA_3"
#define NA_BGM_BASS_PLAY 0x6C               // Bass Practice "BASS_PLAY"
#define NA_BGM_DRUMS_PLAY 0x6D              // Drums Practice "DRUMS_PLAY"
#define NA_BGM_PIANO_PLAY 0x6E              // Piano Practice "PIANO_PLAY"
#define NA_BGM_IKANA_CASTLE 0x6F            // Ikana Castle
#define NA_BGM_GATHERING_GIANTS 0x70        // Calling the Four Giants
#define NA_BGM_KAMARO_DANCE 0x71            // Kamaro's Dance "CAMARO_DANCE"
#define NA_BGM_CREMIA_CARRIAGE 0x72         // Cremia's Carriage "DONKEY_CART"
#define NA_BGM_KEATON_QUIZ 0x73             // Keaton "QUIZ"
#define NA_BGM_END_CREDITS_1 0x74           // The End/Credits I "END_DEMO"
#define NA_BGM_OPENING_LOOP 0x75            // Forest Ambush (?)		Duplicate.
#define NA_BGM_TITLE_THEME 0x76             // Title Screen
#define NA_BGM_DUNGEON_APPEAR 0x77          // Surfacing of Woodfall
#define NA_BGM_WOODFALL_CLEAR 0x78          // Woodfall Clear "PURIFICATION_0"
#define NA_BGM_SNOWHEAD_CLEAR 0x79          // Snowhead Clear "PURIFICATION_1"
#define NA_BGM_INTO_THE_MOON 0x7B           // To the Moon
#define NA_BGM_GOODBYE_GIANT 0x7C           //
#define NA_BGM_TATL_AND_TAEL 0x7D           // Tatl and Tael "CHAT"
#define NA_BGM_MOONS_DESTRUCTION 0x7E       // Moon's Destruction "MOON_VANISH"
#define NA_BGM_NO_MUSIC 0x7F                //
#define NA_BGM_END_CREDITS_2 0x82           // The End/Credits II "STAFFROLL2"
#define NA_BGM_DISABLED 0xFFFF

typedef enum {
    /* 0 */ SEQ_PLAYER_BGM_MAIN,
    /* 1 */ SEQ_PLAYER_FANFARE,
    /* 2 */ SEQ_PLAYER_SFX,
    /* 3 */ SEQ_PLAYER_BGM_SUB,
    /* 4 */ SEQ_PLAYER_NATURE
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
    /* 0x0 */ NATURE_CHANNEL_STREAM_0,
    /* 0x1 */ NATURE_CHANNEL_CRITTER_0,
    /* 0x2 */ NATURE_CHANNEL_CRITTER_1,
    /* 0x3 */ NATURE_CHANNEL_CRITTER_2,
    /* 0x4 */ NATURE_CHANNEL_CRITTER_3,
    /* 0x5 */ NATURE_CHANNEL_CRITTER_4,
    /* 0x6 */ NATURE_CHANNEL_CRITTER_5,
    /* 0x7 */ NATURE_CHANNEL_CRITTER_6,
    /* 0x8 */ NATURE_CHANNEL_CRITTER_7,
    /* 0xC */ NATURE_CHANNEL_STREAM_1 = 12,
    /* 0xD */ NATURE_CHANNEL_UNK,
    /* 0xE */ NATURE_CHANNEL_RAIN,
    /* 0xF */ NATURE_CHANNEL_LIGHTNING
} NatureChannelIdx; // playerIdx = 4

typedef enum {
    /* 0x00 */ NATURE_AMBIENCE_0,
    /* 0x01 */ NATURE_AMBIENCE_1,
    /* 0x02 */ NATURE_AMBIENCE_2,
    /* 0x03 */ NATURE_AMBIENCE_3,
    /* 0x04 */ NATURE_AMBIENCE_4,
    /* 0x05 */ NATURE_AMBIENCE_5,
    /* 0x06 */ NATURE_AMBIENCE_6,
    /* 0x07 */ NATURE_AMBIENCE_7,
    /* 0x08 */ NATURE_AMBIENCE_8,
    /* 0x09 */ NATURE_AMBIENCE_9,
    /* 0x0A */ NATURE_AMBIENCE_A,
    /* 0x0B */ NATURE_AMBIENCE_B,
    /* 0x0C */ NATURE_AMBIENCE_C,
    /* 0x0D */ NATURE_AMBIENCE_D,
    /* 0x0E */ NATURE_AMBIENCE_E,
    /* 0x0F */ NATURE_AMBIENCE_F,
    /* 0x10 */ NATURE_AMBIENCE_10,
    /* 0x11 */ NATURE_AMBIENCE_11,
    /* 0x12 */ NATURE_AMBIENCE_12,
    /* 0x13 */ NATURE_AMBIENCE_13
} NatureAmbienceId; // playerIdx = 4

typedef enum {
    /* 0x00 */ NATURE_STREAM_0,
    /* 0x01 */ NATURE_STREAM_1,
    /* 0x02 */ NATURE_STREAM_2,
    /* 0x03 */ NATURE_STREAM_3
} NatureStreamId;

typedef enum {
    /* 0x00 */ NATURE_CRITTER_00,
    /* 0x01 */ NATURE_CRITTER_01,
    /* 0x02 */ NATURE_CRITTER_02,
    /* 0x03 */ NATURE_CRITTER_03,
    /* 0x04 */ NATURE_CRITTER_04,
    /* 0x05 */ NATURE_CRITTER_05,
    /* 0x06 */ NATURE_CRITTER_06,
    /* 0x07 */ NATURE_CRITTER_07,
    /* 0x08 */ NATURE_CRITTER_08,
    /* 0x09 */ NATURE_CRITTER_09,
    /* 0x0A */ NATURE_CRITTER_10,
    /* 0x0B */ NATURE_CRITTER_11,
    /* 0x0C */ NATURE_CRITTER_12,
    /* 0x0D */ NATURE_CRITTER_13,
    /* 0x0E */ NATURE_CRITTER_14,
    /* 0x0F */ NATURE_CRITTER_15,
    /* 0x10 */ NATURE_CRITTER_16,
    /* 0x11 */ NATURE_CRITTER_17,
    /* 0x12 */ NATURE_CRITTER_18,
    /* 0x13 */ NATURE_CRITTER_19
} NatureAmimalId;

#define NATURE_IO_CRITTER_0_TYPE(type)        NATURE_CHANNEL_CRITTER_0, CHANNEL_IO_PORT_2, type
#define NATURE_IO_CRITTER_0_BEND_PITCH(bend)  NATURE_CHANNEL_CRITTER_0, CHANNEL_IO_PORT_3, bend
#define NATURE_IO_CRITTER_0_NUM_LAYERS(num)   NATURE_CHANNEL_CRITTER_0, CHANNEL_IO_PORT_4, num
#define NATURE_IO_CRITTER_0_PORT5(reverb)     NATURE_CHANNEL_CRITTER_0, CHANNEL_IO_PORT_5, reverb

#define NATURE_IO_CRITTER_1_TYPE(type)        NATURE_CHANNEL_CRITTER_1, CHANNEL_IO_PORT_2, type
#define NATURE_IO_CRITTER_1_BEND_PITCH(bend)  NATURE_CHANNEL_CRITTER_1, CHANNEL_IO_PORT_3, bend
#define NATURE_IO_CRITTER_1_NUM_LAYERS(num)   NATURE_CHANNEL_CRITTER_1, CHANNEL_IO_PORT_4, num
#define NATURE_IO_CRITTER_1_PORT5(reverb)     NATURE_CHANNEL_CRITTER_1, CHANNEL_IO_PORT_5, reverb

#define NATURE_IO_CRITTER_2_TYPE(type)        NATURE_CHANNEL_CRITTER_2, CHANNEL_IO_PORT_2, type
#define NATURE_IO_CRITTER_2_BEND_PITCH(bend)  NATURE_CHANNEL_CRITTER_2, CHANNEL_IO_PORT_3, bend
#define NATURE_IO_CRITTER_2_NUM_LAYERS(num)   NATURE_CHANNEL_CRITTER_2, CHANNEL_IO_PORT_4, num
#define NATURE_IO_CRITTER_2_PORT5(reverb)     NATURE_CHANNEL_CRITTER_2, CHANNEL_IO_PORT_5, reverb

#define NATURE_IO_CRITTER_3_TYPE(type)        NATURE_CHANNEL_CRITTER_3, CHANNEL_IO_PORT_2, type
#define NATURE_IO_CRITTER_3_BEND_PITCH(bend)  NATURE_CHANNEL_CRITTER_3, CHANNEL_IO_PORT_3, bend
#define NATURE_IO_CRITTER_3_NUM_LAYERS(num)   NATURE_CHANNEL_CRITTER_3, CHANNEL_IO_PORT_4, num
#define NATURE_IO_CRITTER_3_PORT5(reverb)     NATURE_CHANNEL_CRITTER_3, CHANNEL_IO_PORT_5, reverb

#define NATURE_IO_CRITTER_4_TYPE(type)        NATURE_CHANNEL_CRITTER_4, CHANNEL_IO_PORT_2, type
#define NATURE_IO_CRITTER_4_BEND_PITCH(bend)  NATURE_CHANNEL_CRITTER_4, CHANNEL_IO_PORT_3, bend
#define NATURE_IO_CRITTER_4_NUM_LAYERS(num)   NATURE_CHANNEL_CRITTER_4, CHANNEL_IO_PORT_4, num
#define NATURE_IO_CRITTER_4_PORT5(reverb)     NATURE_CHANNEL_CRITTER_4, CHANNEL_IO_PORT_5, reverb

#define NATURE_IO_CRITTER_5_TYPE(type)        NATURE_CHANNEL_CRITTER_5, CHANNEL_IO_PORT_2, type
#define NATURE_IO_CRITTER_5_BEND_PITCH(bend)  NATURE_CHANNEL_CRITTER_5, CHANNEL_IO_PORT_3, bend
#define NATURE_IO_CRITTER_5_NUM_LAYERS(num)   NATURE_CHANNEL_CRITTER_5, CHANNEL_IO_PORT_4, num
#define NATURE_IO_CRITTER_5_PORT5(reverb)     NATURE_CHANNEL_CRITTER_5, CHANNEL_IO_PORT_5, reverb

#define NATURE_IO_CRITTER_6_TYPE(type)        NATURE_CHANNEL_CRITTER_6, CHANNEL_IO_PORT_2, type
#define NATURE_IO_CRITTER_6_BEND_PITCH(bend)  NATURE_CHANNEL_CRITTER_6, CHANNEL_IO_PORT_3, bend
#define NATURE_IO_CRITTER_6_NUM_LAYERS(num)   NATURE_CHANNEL_CRITTER_6, CHANNEL_IO_PORT_4, num
#define NATURE_IO_CRITTER_6_PORT5(reverb)     NATURE_CHANNEL_CRITTER_6, CHANNEL_IO_PORT_5, reverb

#define NATURE_IO_STREAM_0_TYPE(type)         NATURE_CHANNEL_STREAM_0, CHANNEL_IO_PORT_2, type
#define NATURE_IO_STREAM_0_PORT3(data)        NATURE_CHANNEL_STREAM_0, CHANNEL_IO_PORT_3, data
#define NATURE_IO_STREAM_0_PORT4(data)        NATURE_CHANNEL_STREAM_0, CHANNEL_IO_PORT_4, data

#define NATURE_IO_STREAM_1_TYPE(type)         NATURE_CHANNEL_STREAM_1, CHANNEL_IO_PORT_2, type
#define NATURE_IO_STREAM_1_PORT3(data)        NATURE_CHANNEL_STREAM_1, CHANNEL_IO_PORT_3, data
#define NATURE_IO_STREAM_1_PORT4(data)        NATURE_CHANNEL_STREAM_1, CHANNEL_IO_PORT_4, data

#define NATURE_IO_RAIN_PORT4(data)            NATURE_CHANNEL_RAIN, CHANNEL_IO_PORT_4, data

#define NATURE_IO_ENTRIES_END 0xFF

#endif
