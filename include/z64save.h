#ifndef _Z64SAVE_H_
#define _Z64SAVE_H_

#include "ultra64.h"
#include "z64math.h"
#include "os.h"

typedef struct {
    /* 0x00 */ u8 buttonItems[4][4];
    /* 0x10 */ u8 cButtonSlots[4][4];
    /* 0x20 */ u16 equipment;
} ItemEquips; // size = 0x22

typedef struct {
    /* 0x00 */ u8 items[24];
    /* 0x18 */ u8 masks[24];
    /* 0x30 */ s8 ammo[24];
    /* 0x48 */ u32 upgrades;                     // some bits are wallet upgrades
    /* 0x4C */ u32 questItems;
    /* 0x50 */ u8 dungeonItems[10];
    /* 0x5A */ s8 dungeonKeys[10];
    /* 0x64 */ s8 strayFairies[10];              // original name: orange_fairy
    /* 0x6E */ u8 unk_6E[8][3];                  // original name: degnuts_memory_name
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
    /* 0x0000 */ char newf[6];                   // original name: newf"               Will always be "ZELDA3 for a valid save
    /* 0x0006 */ u16 deaths;                     // original name: savect
    /* 0x0008 */ char playerName[8];             // original name: player_name
    /* 0x0010 */ s16 healthCapacity;             // original name: max_life
    /* 0x0012 */ s16 health;                     // original name: now_life
    /* 0x0014 */ s8 magicLevel;                  // original name: magic_max
    /* 0x0015 */ s8 magic;                       // original name: magic_now
    /* 0x0016 */ s16 rupees;                     // original name: lupy_count
    /* 0x0018 */ u16 swordHealth;                // original name: long_sword_hp
    /* 0x001A */ u16 tatlTimer;                  // original name: navi_timer
    /* 0x001C */ u8 magicAcquired;               // original name: magic_mode
    /* 0x001D */ u8 doubleMagic;                 // original name: magic_ability
    /* 0x001E */ u8 doubleDefense;               // original name: life_ability
    /* 0x001F */ u8 unk_1F;                      // original name: ocarina_round
    /* 0x0020 */ u8 unk_20;                      // original name: first_memory
    /* 0x0022 */ u16 owlActivationFlags;         // original name: memory_warp_point
    /* 0x0024 */ u8 unk_24;                      // original name: last_warp_pt
    /* 0x0026 */ s16 savedSceneNum;              // original name: scene_data_ID
} SavePlayerData; // size = 0x28

typedef struct {
    /* 0x0000 */ u32 entranceIndex;              // original name: scene_no
    /* 0x0004 */ u8 equippedMask;                // original name: player_mask
    /* 0x0005 */ u8 firstCycleFlag;              // original name: opening_flag
    /* 0x0006 */ u8 unk_06;
    /* 0x0007 */ u8 linkAge;                     // original name: link_age
    /* 0x0008 */ s32 cutscene;                   // original name: day_time
    /* 0x000C */ u16 time;                       // original name: zelda_time
    /* 0x000E */ u16 owlSaveLocation;
    /* 0x0010 */ s32 isNight;                    // original name: asahiru_fg
    /* 0x0014 */ u32 daySpeed;                   // original name: change_zelda_time
    /* 0x0018 */ s32 day;                        // original name: totalday
    /* 0x001C */ u32 daysElapsed;                // original name: eventday
    /* 0x0020 */ u8 playerForm;                  // original name: player_character
    /* 0x0021 */ u8 snowheadCleared;             // original name: spring_flag
    /* 0x0022 */ u8 hasTatl;                     // original name: bell_flag
    /* 0x0023 */ u8 isOwlSave;
    /* 0x0024 */ SavePlayerData playerData;
    /* 0x004C */ ItemEquips equips;
    /* 0x0070 */ Inventory inventory;
    /* 0x00F8 */ u32 roomInf[128][7];
    /* 0x0EF8 */ u8 weekEventReg[100];           // original name: week_event_reg
    /* 0x0F5C */ u32 mapsVisited;                // original name: area_arrival
    /* 0x0F60 */ u32 mapsVisible;                // original name: cloud_clear
    /* 0x0F64 */ u8 unk_F64;                     // original name: oca_rec_flag                   has scarecrows song
    /* 0x0F65 */ u8 unk_F65;                     // original name: oca_rec_flag8                  scarecrows song set?
    /* 0x0F66 */ u8 scarecrowsSong[128];         // original name: oca_rec_buff8
    /* 0x0FE6 */ s8 bombersCaughtNum;            // original name: aikotoba_index
    /* 0x0FE7 */ s8 bombersCaughtOrder[5];       // original name: aikotoba_table
    /* 0x0FEC */ s8 lotteryCodes[3][3];          // original name: numbers_table
    /* 0x0FF5 */ s8 spiderHouseMaskOrder[6];     // original name: kinsta_color_table
    /* 0x0FFB */ s8 bomberCode[5];               // original name: bombers_aikotoba_table
    /* 0x1000 */ HorseData horseData;
    /* 0x100A */ u16 checksum;                   // original name: check_sum
} Save; // size = 0x100C

typedef struct {
    /* 0x0000 */ Save save;
    /* 0x100C */ u8 eventInf[8];
    /* 0x1014 */ u8 unk_1014;                    // original name: stone_set_flag
    /* 0x1015 */ u8 unk_1015;
    /* 0x1016 */ u16 jinxTimer;
    /* 0x1018 */ s16 rupeeAccumulator;           // original name: lupy_udct
    /* 0x101A */ u8 unk_101A[6];                 // original name: bottle_status, one entry for each bottle
    /* 0x1020 */ OSTime unk_1020[6];             // original name: bottle_ostime, one entry for each bottle
    /* 0x1050 */ OSTime unk_1050[6];             // original name: bottle_sub, one entry for each bottle
    /* 0x1080 */ OSTime unk_1080[6];             // original name: bottle_time, one entry for each bottle
    /* 0x10B0 */ OSTime unk_10B0[6];             // original name: bottle_stop_time, one entry for each bottle
    /* 0x10E0 */ u64 pictoPhoto[1400];           // buffer containing the pictograph photo
    /* 0x3CA0 */ s32 fileNum;                    // original name: file_no
    /* 0x3CA4 */ s16 powderKegTimer;             // original name: big_bom_timer
    /* 0x3CA6 */ u8 unk_3CA6;
    /* 0x3CA7 */ u8 unk_3CA7;                    // original name: day_night_flag
    /* 0x3CA8 */ s32 gameMode;                   // original name: mode
    /* 0x3CAC */ s32 sceneSetupIndex;            // original name: counter
    /* 0x3CB0 */ s32 respawnFlag;                // original name: restart_flag
    /* 0x3CB4 */ RespawnData respawn[8];         // original name: restart_data
    /* 0x3DB4 */ f32 entranceSpeed;              // original name: player_wipe_speedF
    /* 0x3DB8 */ u16 entranceSound;              // original name: player_wipe_door_SE
    /* 0x3DBA */ u8 unk_3DBA;                    // original name: player_wipe_item
    /* 0x3DBB */ u8 unk_3DBB;                    // original name: next_walk
    /* 0x3DBC */ u16 dogParams;                  // original name: dog_flag
    /* 0x3DBE */ u8 textTriggerFlags;            // original name: guide_status
    /* 0x3DBF */ u8 showTitleCard;               // original name: name_display
    /* 0x3DC0 */ s16 unk_3DC0;                   // original name: shield_magic_timer
    /* 0x3DC2 */ u8 unk_3DC2;                    // original name: pad1
    /* 0x3DC8 */ OSTime unk_3DC8;                // original name: get_time
    /* 0x3DD0 */ u8 unk_3DD0[7];                 // original name: event_fg
    /* 0x3DD7 */ u8 unk_3DD7[7];                 // original name: calc_flag
    /* 0x3DE0 */ OSTime unk_3DE0[7];             // original name: event_ostime
    /* 0x3E18 */ OSTime unk_3E18[7];             // original name: event_sub
    /* 0x3E50 */ OSTime unk_3E50[7];             // original name: func_time
    /* 0x3E88 */ OSTime unk_3E88[7];             // original name: func_end_time
    /* 0x3EC0 */ OSTime unk_3EC0[7];             // original name: func_stop_time
    /* 0x3EF8 */ s16 timerX[7];                  // original name: event_xp
    /* 0x3F06 */ s16 timerY[7];                  // original name: event_yp
    /* 0x3F14 */ s16 unk_3F14;                   // original name: character_change
    /* 0x3F16 */ u8 seqIndex;                    // original name: old_bgm
    /* 0x3F17 */ u8 nightSeqIndex;               // original name: old_env
    /* 0x3F18 */ u8 buttonStatus[6];             // original name: button_item
    /* 0x3F1E */ u8 unk_3F1E;                    // original name: ck_fg
    /* 0x3F20 */ u16 unk_3F20;                   // original name: alpha_type
    /* 0x3F22 */ u16 unk_3F22;                   // original name: prev_alpha_type
    /* 0x3F24 */ u16 unk_3F24;                   // original name: alpha_count
    /* 0x3F26 */ u16 unk_3F26;                   // original name: last_time_type
    /* 0x3F28 */ s16 unk_3F28;                   // original name: magic_flag
    /* 0x3F2A */ s16 unk_3F2A;                   // original name: recovery_magic_flag
    /* 0x3F2C */ s16 unk_3F2C;                   // original name: keep_magic_flag
    /* 0x3F2E */ s16 unk_3F2E;                   // original name: magic_now_max
    /* 0x3F30 */ s16 unk_3F30;                   // original name: magic_now_now
    /* 0x3F32 */ s16 unk_3F32;                   // original name: magic_used
    /* 0x3F34 */ s16 unk_3F34;                   // original name: magic_recovery
    /* 0x3F36 */ u16 mapIndex;                   // original name: scene_ID
    /* 0x3F38 */ u16 minigameState;              // original name: yabusame_mode
    /* 0x3F3A */ u16 minigameScore;              // original name: yabusame_total
    /* 0x3F3C */ u16 unk_3F3C;                   // original name: yabusame_out_ct
    /* 0x3F3E */ u8 unk_3F3E;                    // original name: no_save
    /* 0x3F3F */ u8 unk_3F3F;                    // original name: flash_flag
    /* 0x3F40 */ u16 optionId;                   // original name: option_id
    /* 0x3F42 */ u8 language;                    // original name: j_n
    /* 0x3F43 */ s8 audioSetting;                // original name: s_sound
    /* 0x3F44 */ u8 languageSetting;             // original name: language
    /* 0x3F45 */ u8 zTargetSetting;              // 0: Switch; 1: Hold
    /* 0x3F46 */ u16 unk_3F46;                   // original name: NottoriBgm
    /* 0x3F48 */ u8 unk_3F48;                    // original name: fade_go
    /* 0x3F4A */ u16 nextCutsceneIndex;          // original name: next_daytime
    /* 0x3F4C */ u8 cutsceneTrigger;             // original name: doukidemo
    /* 0x3F4D */ u8 unk_3F4D;                    // original name: Kenjya_no
    /* 0x3F4E */ u16 nextDayTime;                // original name: next_zelda_time
    /* 0x3F50 */ u8 fadeDuration;                // original name: fade_speed
    /* 0x3F51 */ u8 fadeSpeed;                   // original name: wipe_speed           transition related
    /* 0x3F52 */ u16 environmentTime;            // original name: kankyo_time
    /* 0x3F54 */ u8 dogIsLost;                   // original name: dog_event_flag
    /* 0x3F55 */ u8 nextTransition;              // original name: next_wipe
    /* 0x3F56 */ s16 worldMapArea;               // original name: area_type
    /* 0x3F58 */ s16 unk_3F58;                   // original name: sunmoon_flag         sun's song related
    /* 0x3F5A */ s16 healthAccumulator;          // original name: life_mode
    /* 0x3F5C */ s32 unk_3F5C;                   // original name: bet_rupees
    /* 0x3F60 */ u8 screenScaleFlag;             // original name: framescale_flag
    /* 0x3F64 */ f32 screenScale;                // original name: framescale_scale
    /* 0x3F68 */ u32 cycleSceneFlags[120][5];
    /* 0x48C8 */ u16 unk_48C8;                   // original name: scene_id_mix
    /* 0x48CA */ u8 maskMaskBit[3];              // original name: mask_mask_bit
    /* 0x48CD */ u8 unk_48CD[24];
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
    /* 0x07 */ RESPAWN_MODE_UNK_8
} RespawnMode;

typedef enum {
    /* 0x00 */ BTN_ENABLED,
    /* 0xFF */ BTN_DISABLED = 0xFF
} ButtonStatus;

typedef struct FileChooseContext FileChooseContext;

#endif
