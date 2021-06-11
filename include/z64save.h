#ifndef _Z64SAVE_H_
#define _Z64SAVE_H_

#include "ultra64.h"
#include "z64math.h"
#include <os.h>

typedef struct {
    /* 0x00 */ u8 buttonItems[4][4];
    /* 0x10 */ u8 cButtonSlots[4][4];
    /* 0x20 */ u16 equipment;
} ItemEquips; // size = 0x0A

typedef struct {
    /* 0x00 */ u8 items[24];
    /* 0x18 */ u8 masks[24];
    /* 0x30 */ s8 ammo[24];
    /* 0x48 */ u32 upgrades; // some bits are wallet upgrades
    /* 0x4C */ u32 questItems;
    /* 0x50 */ u8 dungeonItems[10];
    /* 0x5A */ s8 dungeonKeys[10];
    /* 0x64 */ s8 strayFairies[10]; // "orange_fairy"
    /* 0x6E */ u8 unk_6E[8][3]; // "degnuts_memory_name"
} Inventory; // size = 0x88

typedef struct {
    /* 0x00 */ s16 scene;
    /* 0x02 */ Vec3s pos;
    /* 0x08 */ s16 angle;
} HorseData; // size = 0x0A

typedef struct {
    /* 0x0 */ Vec3f pos;
    /* 0xC */ s16 yaw;
    /* 0xE */ s16 playerParams;
    /* 0x10 */ u16 entranceIndex;
    /* 0x12 */ u8 roomIndex;
    /* 0x13 */ s8 data;
    /* 0x14 */ u32 tempSwchFlags;
    /* 0x18 */ u32 unk_18;
    /* 0x1C */ u32 tempCollectFlags;
} RespawnData; // size = 0x20

typedef struct {
    /* 0x0000 */ u32 entranceIndex; // "scene_no"
    /* 0x0004 */ u8 equippedMask;   // "player_mask"
    /* 0x0005 */ u8 unk_05;         // "opening_flag"
    /* 0x0006 */ u8 unk_06;
    /* 0x0007 */ u8 linkAge;   // "link_age"
    /* 0x0008 */ s32 cutscene; // "day_time"
    /* 0x000C */ u16 time;     // "zelda_time"
    /* 0x000E */ u16 owlSaveLocation;
    /* 0x0010 */ s32 isNight;        // "asahiru_fg"
    /* 0x0014 */ u16 unk_14;         // "change_zelda_time"
    /* 0x0016 */ u16 unk_16;
    /* 0x0018 */ s32 day;            // "totalday"
    /* 0x001C */ u32 daysElapsed;    // "eventday"
    /* 0x0020 */ u8 playerForm;      // "player_character"
    /* 0x0021 */ u8 snowheadCleared; // "spring_flag"
    /* 0x0022 */ u8 hasTatl;         // "bell_flag"
    /* 0x0023 */ u8 isOwlSave;
    /* 0x0024 */ char newf[6];       // Will always be "ZELDA3" for a valid save
    /* 0x002B */ u16 deaths;         // "savect"
    /* 0x002C */ char playerName[8]; // "player_name"
    /* 0x0034 */ s16 healthCapacity; // "max_life"
    /* 0x0036 */ s16 health;         // "now_life"
    /* 0x0038 */ s8 magicLevel;      // "magic_max"
    /* 0x0039 */ s8 magic;           // "magic_now"
    /* 0x003A */ s16 rupees;         // "lupy_count"
    /* 0x003C */ u16 swordHealth;    // "long_sword_hp"
    /* 0x003E */ u16 naviTimer;      // "navi_timer"
    /* 0x0040 */ u8 magicAcquired;   // "magic_mode"
    /* 0x0041 */ u8 doubleMagic;     // "magic_ability"
    /* 0x0042 */ u8 doubleDefense;   // "life_ability"
    /* 0x0043 */ u8 unk_43;          // "ocarina_round"
    /* 0x0044 */ u8 unk_44;          // "first_memory"
    /* 0x0046 */ u16 unk_46;         // "memory_warp_point"
    /* 0x0048 */ u8 unk_48;          // "last_warp_pt"
    /* 0x004A */ s16 savedSceneNum;  // "scene_data_ID"
    /* 0x004C */ ItemEquips equips;
    /* 0x0070 */ Inventory inventory;
    /* 0x00F8 */ u32 roomInf[128][7];
    /* 0x0EF8 */ u8 weekEventReg[100];       // "week_event_reg"
    /* 0x0F5C */ u32 mapsVisited;            // "area_arrival"
    /* 0x0F60 */ u32 unk_F60;                // "cloud_clear"
    /* 0x0F64 */ u8 unk_F64;                 // "oca_rec_flag"
    /* 0x0F65 */ u8 unk_F65;                 // "oca_rec_flag8"
    /* 0x0F66 */ u8 unk_F66[128];            // "oca_rec_buff8"
    /* 0x0FE6 */ s8 unk_FE6;                 // "aikotoba_index"
    /* 0x0FE7 */ s8 unk_FE7[5];              // "aikotoba_table"
    /* 0x0FEC */ s8 lotteryCodes[3][3];      // "numbers_table"
    /* 0x0FF5 */ s8 spiderHouseMaskOrder[6]; // "kinsta_color_table"
    /* 0x0FFB */ s8 bomberCode[5];           // "bombers_aikotoba_table"
    /* 0x1000 */ HorseData horseData;
    /* 0x100A */ u16 checksum; // "check_sum"
    /* 0x100C */ u8 eventInf[8];
    /* 0x1014 */ u8 unk_1014; // "stone_set_flag"
    /* 0x1015 */ u8 unk_1015;
    /* 0x1016 */ u16 unk_1016;
    /* 0x1018 */ s16 rupeeAccumulator; // "lupy_udct"
    /* 0x101A */ u8 unk_101A[6];       // "bottle_status", one entry for each bottle
    /* 0x1020 */ OSTime unk_1020[6];   // "bottle_ostime", one entry for each bottle
    /* 0x1050 */ OSTime unk_1050[6];   // "bottle_sub", one entry for each bottle
    /* 0x1080 */ OSTime unk_1080[6];   // "bottle_time", one entry for each bottle
    /* 0x10B0 */ OSTime unk_10B0[6];   // "bottle_stop_time", one entry for each bottle
    /* 0x10E0 */ u64 pictoPhoto[1400]; // buffer containing the pictograph photo
    /* 0x3CA0 */ s32 fileNum;          // "file_no"
    /* 0x3CA4 */ s16 powderKegTimer;   // "big_bom_timer"
    /* 0x3CA6 */ u8 unk_3CA6;
    /* 0x3CA7 */ u8 unk_3CA7;            // "day_night_flag"
    /* 0x3CA8 */ s32 gameMode;           // "mode"
    /* 0x3CAC */ s32 sceneSetupIndex;    // "counter"
    /* 0x3CB0 */ s32 respawnFlag;        // "restart_flag"
    /* 0x3CB4 */ RespawnData respawn[8]; // "restart_data"
    /* 0x3DB4 */ f32 entranceSpeed;      // "player_wipe_speedF"
    /* 0x3DB8 */ u16 entranceSound;      // "player_wipe_door_SE"
    /* 0x3DBA */ u8 unk_3DBA;            // "player_wipe_item"
    /* 0x3DBB */ u8 unk_3DBB;            // "next_walk"
    /* 0x3DBC */ u16 dogParams;          // "dog_flag"
    /* 0x3DBE */ u8 textTriggerFlags;    // "guide_status"
    /* 0x3DBF */ u8 showTitleCard;       // "name_display"
    /* 0x3DC0 */ s16 unk_3DC0;           // "shield_magic_timer"
    /* 0x3DC2 */ u8 unk_3DC2;            // "pad1"
    /* 0x3DC8 */ OSTime unk_3DC8;        // "get_time"
    /* 0x3DD0 */ u8 unk_3DD0[7];         // "event_fg"
    /* 0x3DD7 */ u8 unk_3DD7[7];         // "calc_flag"
    /* 0x3DE0 */ OSTime unk_3DE0[7];     // "event_ostime"
    /* 0x3E18 */ OSTime unk_3E18[7];     // "event_sub"
    /* 0x3E50 */ OSTime unk_3E50[7];     // "func_time"
    /* 0x3E88 */ OSTime unk_3E88[7];     // "func_end_time"
    /* 0x3EC0 */ OSTime unk_3EC0[7];     // "func_stop_time"
    /* 0x3EF8 */ s16 timerX[7];          // "event_xp"
    /* 0x3F06 */ s16 timerY[7];          // "event_yp"
    /* 0x3F14 */ s16 unk_3F14;           // "character_change"
    /* 0x3F16 */ u8 seqIndex;            // "old_bgm"
    /* 0x3F17 */ u8 nightSeqIndex;       // "old_env"
    /* 0x3F18 */ u8 buttonStatus[6];     // "button_item"
    /* 0x3F1E */ u8 unk_3F1E;            // "ck_fg"
    /* 0x3F20 */ u16 unk_3F20;           // "alpha_type"
    /* 0x3F22 */ u16 unk_3F22;           // "prev_alpha_type"
    /* 0x3F24 */ u16 unk_3F24;           // "alpha_count"
    /* 0x3F26 */ u16 unk_3F26;           // "last_time_type"
    /* 0x3F28 */ s16 unk_3F28;           // "magic_flag"
    /* 0x3F2A */ s16 unk_3F2A;           // "recovery_magic_flag"
    /* 0x3F2C */ s16 unk_3F2C;           // "keep_magic_flag"
    /* 0x3F2E */ s16 unk_3F2E;           // "magic_now_max"
    /* 0x3F30 */ s16 unk_3F30;           // "magic_now_now"
    /* 0x3F32 */ s16 unk_3F32;           // "magic_used"
    /* 0x3F34 */ s16 unk_3F34;           // "magic_recovery"
    /* 0x3F36 */ u16 mapIndex;           // "scene_ID"
    /* 0x3F38 */ u16 minigameState;      // "yabusame_mode"
    /* 0x3F3A */ u16 minigameScore;      // "yabusame_total"
    /* 0x3F3C */ u16 unk_3F3C;           // "yabusame_out_ct"
    /* 0x3F3E */ u8 unk_3F3E;            // "no_save"
    /* 0x3F3F */ u8 unk_3F3F;            // "flash_flag"
    /* 0x3F40 */ u16 option_id;          // "option_id"
    /* 0x3F42 */ u8 language;            // "j_n"
    /* 0x3F43 */ u8 audioSetting;        // "s_sound"
    /* 0x3F44 */ u8 unk_3F44;            // "language"
    /* 0x3F45 */ u8 zTargetSetting;      // 0: Switch; 1: Hold
    /* 0x3F46 */ u16 unk_3F46;           // "NottoriBgm"
    /* 0x3F48 */ u8 unk_3F48;            // "fade_go"
    /* 0x3F4A */ u16 unk_3F4A;           // "next_daytime"
    /* 0x3F4C */ u8 cutsceneTrigger;     // "doukidemo"
    /* 0x3F4D */ u8 unk_3F4D;            // "Kenjya_no"
    /* 0x3F4E */ u16 nextDayTime;        // "next_zelda_time"
    /* 0x3F50 */ u8 fadeDuration;        // "fade_speed"
    /* 0x3F51 */ u8 unk_3F51;            // "wipe_speed"
    /* 0x3F52 */ u16 environmentTime;    // "kankyo_time"
    /* 0x3F54 */ u8 dogIsLost;           // "dog_event_flag"
    /* 0x3F55 */ u8 nextTransition;      // "next_wipe"
    /* 0x3F56 */ s16 worldMapArea;       // "area_type"
    /* 0x3F58 */ s16 unk_3F58;           // "sunmoon_flag"
    /* 0x3F5A */ s16 healthAccumulator;  // "life_mode"
    /* 0x3F5C */ s32 unk_3F5C;           // "bet_rupees"
    /* 0x3F60 */ u8 unk_3F60;            // "framescale_flag"
    /* 0x3F64 */ f32 unk_3F64;           // "framescale_scale"
    /* 0x3F68 */ u32 unk_3F68[5][120];
    /* 0x48C8 */ u16 unk_48C8; // "scene_id_mix"
    /* 0x48CA */ u8 unk_48CA[27];
} SaveContext; // size = 0x48C8

typedef enum {
    /* 0x00 */ RESPAWN_MODE_VOID_OUT,
    /* 0x01 */ RESPAWN_MODE_GROTTO,       // Exiting a grotto
    /* 0x02 */ RESPAWN_MODE_FARORES_WIND, // Unused in MM
    /* 0x03 */ RESPAWN_MODE_GORON,
    /* 0x04 */ RESPAWN_MODE_ZORA,
    /* 0x05 */ RESPAWN_MODE_DEKU,
    /* 0x06 */ RESPAWN_MODE_CHILD_LINK,
    /* 0x07 */ RESPAWN_MODE_UNK_7,
    /* 0x07 */ RESPAWN_MODE_UNK_8,
} RespawnMode;

typedef enum {
    /* 0x00 */ BTN_ENABLED,
    /* 0xFF */ BTN_DISABLED = 0xFF
} ButtonStatus;

#endif
