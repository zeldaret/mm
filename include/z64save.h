#ifndef Z64SAVE_H
#define Z64SAVE_H

#include "ultra64.h"
#include "z64math.h"
#include "os.h"

struct GameState;
struct GlobalContext;
struct FileChooseContext;

// TODO: properly name DOWN, RETURN and TOP
typedef enum RespawnMode {
    /* 0 */ RESTART_MODE_DOWN,                          // "RESTART_MODE_DOWN"
    /* 1 */ RESTART_MODE_RETURN,                        // "RESTART_MODE_RETURN"
    /* 2 */ RESTART_MODE_TOP,                           // "RESTART_MODE_TOP"
    /* 3 */ RESPAWN_MODE_UNK_3,                         // Maybe related to grottos
    /* 4 */ RESPAWN_MODE_GORON,                         // "RESTART_MODE_GORON"
    /* 5 */ RESPAWN_MODE_ZORA,                          // "RESTART_MODE_ZORA"
    /* 6 */ RESPAWN_MODE_DEKU,                          // "RESTART_MODE_NUTS"
    /* 7 */ RESPAWN_MODE_HUMAN,                         // "RESTART_MODE_CHILD"
    /* 8 */ RESPAWN_MODE_MAX
} RespawnMode;

#define SAVE_BUFFER_SIZE 0x4000

typedef struct SramContext {
    /* 0x00 */ u8* readBuff;
    /* 0x04 */ u8 *saveBuf;
    /* 0x08 */ char unk_08[4];
    /* 0x0C */ s16 status;
    /* 0x10 */ u32 curPage;
    /* 0x14 */ u32 numPages;
    /* 0x18 */ OSTime unk_18;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ s16 unk_24;
} SramContext; // size = 0x28

typedef struct ItemEquips {
    /* 0x00 */ u8 buttonItems[4][4];                    // "register_item"
    /* 0x10 */ u8 cButtonSlots[4][4];                   // "register_item_pt"
    /* 0x20 */ u16 equipment;
} ItemEquips; // size = 0x22

typedef struct Inventory {
    /* 0x00 */ u8 items[48];                            // "item_register", first 24 elements are normal items and the other 24 are masks
    /* 0x30 */ s8 ammo[24];                             // "item_count"
    /* 0x48 */ u32 upgrades;                            // "non_equip_register" some bits are wallet upgrades
    /* 0x4C */ u32 questItems;                          // "collect_register"
    /* 0x50 */ u8 dungeonItems[10];                     // "key_compass_map"
    /* 0x5A */ s8 dungeonKeys[10];                      // "key_register"
    /* 0x64 */ s8 strayFairies[10];                     // "orange_fairy"
    /* 0x6E */ char dekuPlaygroundPlayerName[3][8];     // "degnuts_memory_name" Stores playerName (8 char) over (3 days) when getting a new high score
} Inventory; // size = 0x88

typedef struct HorseData {
    /* 0x00 */ s16 scene;                               // "spot_no"
    /* 0x02 */ Vec3s pos;                               // "horse_x", "horse_y" and "horse_z"
    /* 0x08 */ s16 yaw;                                 // "horse_a"
} HorseData; // size = 0x0A

typedef struct RespawnData {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ s16 yaw;
    /* 0x0E */ s16 playerParams;
    /* 0x10 */ u16 entranceIndex;
    /* 0x12 */ u8 roomIndex;
    /* 0x13 */ s8 data;
    /* 0x14 */ u32 tempSwitchFlags;
    /* 0x18 */ u32 unk_18;
    /* 0x1C */ u32 tempCollectFlags;
} RespawnData; // size = 0x20

typedef struct PermanentSceneFlags {
    /* 0x00 */ u32 chest;
    /* 0x04 */ u32 switch0;
    /* 0x08 */ u32 switch1;
    /* 0x0C */ u32 clearedRoom;
    /* 0x10 */ u32 collectible;
    /* 0x14 */ u32 unk_14;
    /* 0x18 */ u32 unk_18;
} PermanentSceneFlags; // size = 0x1C

typedef struct CycleSceneFlags {
    /* 0x00 */ u32 chest;
    /* 0x04 */ u32 switch0;
    /* 0x08 */ u32 switch1;
    /* 0x0C */ u32 clearedRoom;
    /* 0x10 */ u32 collectible;
} CycleSceneFlags; // size = 0x14

typedef struct SaveOptions {
    /* 0x00 */ u16 optionId;                            // "option_id"
    /* 0x02 */ u8 language;                             // "j_n"
    /* 0x03 */ s8 audioSetting;                         // "s_sound"
    /* 0x04 */ u8 languageSetting;                      // "language"
    /* 0x05 */ u8 zTargetSetting;                       // "z_attention", 0: Switch; 1: Hold
} SaveOptions; // size = 0x06

typedef struct SavePlayerData {
    /* 0x0000 */ char newf[6];                          // "newf"               Will always be "ZELDA3 for a valid save
    /* 0x0006 */ u16 deaths;                            // "savect"
    /* 0x0008 */ char playerName[8];                    // "player_name"
    /* 0x0010 */ s16 healthCapacity;                    // "max_life"
    /* 0x0012 */ s16 health;                            // "now_life"
    /* 0x0014 */ s8 magicLevel;                         // "magic_max"
    /* 0x0015 */ s8 magic;                              // "magic_now"
    /* 0x0016 */ s16 rupees;                            // "lupy_count"
    /* 0x0018 */ u16 swordHealth;                       // "long_sword_hp"
    /* 0x001A */ u16 tatlTimer;                         // "navi_timer"
    /* 0x001C */ u8 magicAcquired;                      // "magic_mode"
    /* 0x001D */ u8 doubleMagic;                        // "magic_ability"
    /* 0x001E */ u8 doubleDefense;                      // "life_ability"
    /* 0x001F */ u8 unk_1F;                             // "ocarina_round"
    /* 0x0020 */ u8 unk_20;                             // "first_memory"
    /* 0x0022 */ u16 owlActivationFlags;                // "memory_warp_point"
    /* 0x0024 */ u8 unk_24;                             // "last_warp_pt"
    /* 0x0026 */ s16 savedSceneNum;                     // "scene_data_ID"
} SavePlayerData; // size = 0x28

typedef struct Save {
    /* 0x0000 */ u32 entranceIndex;                     // "scene_no"
    /* 0x0004 */ u8 equippedMask;                       // "player_mask"
    /* 0x0005 */ u8 isFirstCycle;                       // "opening_flag"
    /* 0x0006 */ u8 unk_06;
    /* 0x0007 */ u8 linkAge;                            // "link_age"
    /* 0x0008 */ s32 cutscene;                          // "day_time"
    /* 0x000C */ u16 time;                              // "zelda_time"
    /* 0x000E */ u16 owlSaveLocation;
    /* 0x0010 */ s32 isNight;                           // "asahiru_fg"
    /* 0x0014 */ u32 daySpeed;                          // "change_zelda_time"
    /* 0x0018 */ s32 day;                               // "totalday"
    /* 0x001C */ u32 daysElapsed;                       // "eventday"
    /* 0x0020 */ u8 playerForm;                         // "player_character"
    /* 0x0021 */ u8 snowheadCleared;                    // "spring_flag"
    /* 0x0022 */ u8 hasTatl;                            // "bell_flag"
    /* 0x0023 */ u8 isOwlSave;
    /* 0x0024 */ SavePlayerData playerData;
    /* 0x004C */ ItemEquips equips;
    /* 0x0070 */ Inventory inventory;
    /* 0x00F8 */ PermanentSceneFlags permanentSceneFlags[120];
    /* 0x0E18 */ u8 unk_E18[0x54];
    /* 0x0E6C */ u32 dekuPlaygroundHighScores[3];
    /* 0x0E78 */ u32 pictoFlags0;
    /* 0x0E7C */ u32 pictoFlags1;
    /* 0x0E80 */ u32 unk_E80;
    /* 0x0E84 */ u32 unk_E84;
    /* 0x0E88 */ u32 unk_E88[7];                        // Invadepoh flags
    /* 0x0EA4 */ u32 scenesVisible[7];                  // tingle maps and clouded regions on pause map. Stores scenes bitwise for up to 224 scenes even though there are not that many scenes
    /* 0x0EC0 */ u32 skullTokenCount;                   // upper 16 bits store Swamp skulls, lower 16 bits store Ocean skulls
    /* 0x0EC4 */ u32 unk_EC4;                           // Gossic stone heart piece flags
    /* 0x0EC8 */ u32 unk_EC8;
    /* 0x0ECC */ u32 unk_ECC[2];                        // Related to blue warps
    /* 0x0ED4 */ u32 stolenItems;                       // Items stolen by Takkuri and given to Curiosity Shop Man
    /* 0x0ED8 */ u32 unk_DD8;
    /* 0x0EDC */ u32 bankRupees;
    /* 0x0EE0 */ u32 unk_EE0;
    /* 0x0EE4 */ u32 unk_EE4;                           // Fishing flags
    /* 0x0EE8 */ u32 unk_EE8;
    /* 0x0EEC */ u32 horseBackBalloonHighScore;
    /* 0x0EF0 */ u32 lotteryCodeGuess;                  // Lottery code chosen by player (only uses lower three hex digits)
    /* 0x0EF4 */ u32 unk_EF4;                           // Shooting Gallery Man Flags
    /* 0x0EF8 */ u8 weekEventReg[100];                  // "week_event_reg"
    /* 0x0F5C */ u32 mapsVisited;                       // "area_arrival"
    /* 0x0F60 */ u32 mapsVisible;                       // "cloud_clear"
    /* 0x0F64 */ u8 unk_F64;                            // "oca_rec_flag"                   has scarecrows song
    /* 0x0F65 */ u8 unk_F65;                            // "oca_rec_flag8"                  scarecrows song set?
    /* 0x0F66 */ u8 scarecrowsSong[128];
    /* 0x0FE6 */ s8 bombersCaughtNum;                   // "aikotoba_index"
    /* 0x0FE7 */ s8 bombersCaughtOrder[5];              // "aikotoba_table"
    /* 0x0FEC */ s8 lotteryCodes[3][3];                 // "numbers_table", Preset lottery codes
    /* 0x0FF5 */ s8 spiderHouseMaskOrder[6];            // "kinsta_color_table"
    /* 0x0FFB */ s8 bomberCode[5];                      // "bombers_aikotoba_table"
    /* 0x1000 */ HorseData horseData;
    /* 0x100A */ u16 checksum;                          // "check_sum"
} Save; // size = 0x100C

typedef struct SaveContext {
    /* 0x0000 */ Save save;
    /* 0x100C */ u8 eventInf[8];                        // "event_inf"
    /* 0x1014 */ u8 unk_1014;                           // "stone_set_flag"
    /* 0x1015 */ u8 unk_1015;
    /* 0x1016 */ u16 jinxTimer;
    /* 0x1018 */ s16 rupeeAccumulator;                  // "lupy_udct"
    /* 0x101A */ u8 unk_101A[6];                        // "bottle_status", one entry for each bottle
    /* 0x1020 */ OSTime unk_1020[6];                    // "bottle_ostime", one entry for each bottle
    /* 0x1050 */ OSTime unk_1050[6];                    // "bottle_sub", one entry for each bottle
    /* 0x1080 */ OSTime unk_1080[6];                    // "bottle_time", one entry for each bottle
    /* 0x10B0 */ OSTime unk_10B0[6];                    // "bottle_stop_time", one entry for each bottle
    /* 0x10E0 */ u64 pictoPhoto[1400];                  // buffer containing the pictograph photo
    /* 0x3CA0 */ s32 fileNum;                           // "file_no"
    /* 0x3CA4 */ s16 powderKegTimer;                    // "big_bom_timer"
    /* 0x3CA6 */ u8 unk_3CA6;
    /* 0x3CA7 */ u8 unk_3CA7;                           // "day_night_flag"
    /* 0x3CA8 */ s32 gameMode;                          // "mode"
    /* 0x3CAC */ s32 sceneSetupIndex;                   // "counter"
    /* 0x3CB0 */ s32 respawnFlag;                       // "restart_flag"
    /* 0x3CB4 */ RespawnData respawn[RESPAWN_MODE_MAX]; // "restart_data"
    /* 0x3DB4 */ f32 entranceSpeed;                     // "player_wipe_speedF"
    /* 0x3DB8 */ u16 entranceSound;                     // "player_wipe_door_SE"
    /* 0x3DBA */ u8 unk_3DBA;                           // "player_wipe_item"
    /* 0x3DBB */ u8 unk_3DBB;                           // "next_walk"
    /* 0x3DBC */ u16 dogParams;                         // "dog_flag"
    /* 0x3DBE */ u8 textTriggerFlags;                   // "guide_status"
    /* 0x3DBF */ u8 showTitleCard;                      // "name_display"
    /* 0x3DC0 */ s16 unk_3DC0;                          // "shield_magic_timer"
    /* 0x3DC2 */ u8 unk_3DC2;                           // "pad1"
    /* 0x3DC8 */ OSTime unk_3DC8;                       // "get_time"
    /* 0x3DD0 */ u8 unk_3DD0[7];                        // "event_fg"
    /* 0x3DD7 */ u8 unk_3DD7[7];                        // "calc_flag"
    /* 0x3DE0 */ OSTime unk_3DE0[7];                    // "event_ostime"
    /* 0x3E18 */ OSTime unk_3E18[7];                    // "event_sub"
    /* 0x3E50 */ OSTime unk_3E50[7];                    // "func_time"
    /* 0x3E88 */ OSTime unk_3E88[7];                    // "func_end_time"
    /* 0x3EC0 */ OSTime unk_3EC0[7];                    // "func_stop_time"
    /* 0x3EF8 */ s16 timerX[7];                         // "event_xp"
    /* 0x3F06 */ s16 timerY[7];                         // "event_yp"
    /* 0x3F14 */ s16 unk_3F14;                          // "character_change"
    /* 0x3F16 */ u8 seqIndex;                           // "old_bgm"
    /* 0x3F17 */ u8 nightSeqIndex;                      // "old_env"
    /* 0x3F18 */ u8 buttonStatus[6];                    // "button_item"
    /* 0x3F1E */ u8 unk_3F1E;                           // "ck_fg"
    /* 0x3F20 */ u16 unk_3F20;                          // "alpha_type"
    /* 0x3F22 */ u16 unk_3F22;                          // "prev_alpha_type"
    /* 0x3F24 */ u16 unk_3F24;                          // "alpha_count"
    /* 0x3F26 */ u16 unk_3F26;                          // "last_time_type"
    /* 0x3F28 */ s16 unk_3F28;                          // "magic_flag"
    /* 0x3F2A */ s16 unk_3F2A;                          // "recovery_magic_flag"
    /* 0x3F2C */ s16 unk_3F2C;                          // "keep_magic_flag"
    /* 0x3F2E */ s16 unk_3F2E;                          // "magic_now_max"
    /* 0x3F30 */ s16 unk_3F30;                          // "magic_now_now"
    /* 0x3F32 */ s16 unk_3F32;                          // "magic_used"
    /* 0x3F34 */ s16 unk_3F34;                          // "magic_recovery"
    /* 0x3F36 */ u16 mapIndex;                          // "scene_ID"
    /* 0x3F38 */ u16 minigameState;                     // "yabusame_mode"
    /* 0x3F3A */ u16 minigameScore;                     // "yabusame_total"
    /* 0x3F3C */ u16 unk_3F3C;                          // "yabusame_out_ct"
    /* 0x3F3E */ u8 unk_3F3E;                           // "no_save"
    /* 0x3F3F */ u8 unk_3F3F;                           // "flash_flag"
    /* 0x3F40 */ SaveOptions options;
    /* 0x3F46 */ u16 unk_3F46;                          // "NottoriBgm"
    /* 0x3F48 */ u8 unk_3F48;                           // "fade_go"
    /* 0x3F4A */ u16 nextCutsceneIndex;                 // "next_daytime"
    /* 0x3F4C */ u8 cutsceneTrigger;                    // "doukidemo"
    /* 0x3F4D */ u8 unk_3F4D;                           // "Kenjya_no"
    /* 0x3F4E */ u16 nextDayTime;                       // "next_zelda_time"
    /* 0x3F50 */ u8 fadeDuration;                       // "fade_speed"
    /* 0x3F51 */ u8 fadeSpeed;                          // "wipe_speed"           transition related
    /* 0x3F52 */ u16 environmentTime;                   // "kankyo_time"
    /* 0x3F54 */ u8 dogIsLost;                          // "dog_event_flag"
    /* 0x3F55 */ u8 nextTransition;                     // "next_wipe"
    /* 0x3F56 */ s16 worldMapArea;                      // "area_type"
    /* 0x3F58 */ s16 sunsSongState;                     // "sunmoon_flag"
    /* 0x3F5A */ s16 healthAccumulator;                 // "life_mode"
    /* 0x3F5C */ s32 unk_3F5C;                          // "bet_rupees"
    /* 0x3F60 */ u8 screenScaleFlag;                    // "framescale_flag"
    /* 0x3F64 */ f32 screenScale;                       // "framescale_scale"
    /* 0x3F68 */ CycleSceneFlags cycleSceneFlags[120];  // Scene flags that are temporarily stored over the duration of a single 3-day cycle
    /* 0x48C8 */ u16 unk_48C8;                          // "scene_id_mix"
    /* 0x48CA */ u8 maskMaskBit[27];                    // "mask_mask_bit", masks given away on the Moon
} SaveContext; // size = 0x48C8

typedef enum ButtonStatus {
    /* 0x00 */ BTN_ENABLED,
    /* 0xFF */ BTN_DISABLED = 0xFF
} ButtonStatus;

typedef enum SunsSongState {
    /* 0 */ SUNSSONG_INACTIVE,
    /* 1 */ SUNSSONG_START, // the suns ocarina effect signals that the song has finished playing
    /* 2 */ SUNSSONG_SPEED_TIME, // suns was played where time passes, speed up the advancement of time
    /* 3 */ SUNSSONG_SPECIAL // time does not advance, but signals the song was played. used for freezing redeads
} SunsSongState;

void Sram_ActivateOwl(u8 owlId);
void Sram_ClearFlagsAtDawnOfTheFirstDay(void);
void Sram_SaveEndOfCycle(struct GlobalContext* globalCtx);
void Sram_IncrementDay(void);
u16 Sram_CalcChecksum(void* data, size_t count);
void Sram_InitNewSave(void);
void Sram_InitDebugSave(void);
void func_80144A94(SramContext* sramCtx);
void Sram_OpenSave(struct FileChooseContext* fileChooseCtx, SramContext* sramCtx);
void func_8014546C(SramContext* sramCtx);
void func_801457CC(struct FileChooseContext* fileChooseCtx, SramContext* sramCtx);
void func_80146580(struct FileChooseContext* fileChooseCtx, SramContext* sramCtx, s32 fileNum);
void func_80146628(struct FileChooseContext* fileChooseCtx, SramContext* sramCtx);
void Sram_InitSave(struct FileChooseContext* fileChooseCtx, SramContext* sramCtx);
void func_80146DF8(SramContext* sramCtx);
void Sram_InitSram(struct GameState* gameState, SramContext* sramCtx);
void Sram_Alloc(struct GameState* gamestate, SramContext* sramCtx);
void Sram_SaveSpecialEnterClockTown(struct GlobalContext* globalCtx);
void Sram_SaveSpecialNewDay(struct GlobalContext* globalCtx);
void func_80147008(SramContext* sramCtx, u32 curPage, u32 numPages);
void func_80147020(SramContext* sramCtx);
void func_80147068(SramContext* sramCtx);
void func_80147138(SramContext* sramCtx, s32 curPage, s32 numPages);
void func_80147150(SramContext* sramCtx);
void func_80147198(SramContext* sramCtx);

extern s32 D_801C6798[];
extern u8 D_801C67B0[24];
extern s32 D_801C67C8[];
extern s32 D_801C67E8[];
extern s32 D_801C67F0[];
extern s32 D_801C6818[];
extern s32 D_801C6838[];
extern s32 D_801C6840[];
extern s32 D_801C6850[];

#endif
