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
    /* 0x64 */ s8 strayFairies[10];
    /* 0x6E */ u8 unk_6E[8][3];
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
    /* 0x0000 */ u32 entranceIndex;
    /* 0x0004 */ u8 equippedMask;
    /* 0x0005 */ u8 unk_05;
    /* 0x0006 */ u8 unk_06;
    /* 0x0007 */ u8 linkAge;
    /* 0x0008 */ s32 cutscene;
    /* 0x000C */ u16 time;
    /* 0x000E */ u16 owlSaveLocation;
    /* 0x0010 */ u32 isNight;
    /* 0x0014 */ u32 unk_14;
    /* 0x0018 */ u32 day;
    /* 0x001C */ u32 daysElapsed;
    /* 0x0020 */ u8 playerForm; // transformation mask ID
    /* 0x0021 */ u8 snowheadCleared;
    /* 0x0022 */ u8 unk_22;
    /* 0x0023 */ u8 owlSave;
    /* 0x0024 */ char newf[6]; // Will always be "ZELDA3" for a valid save
    /* 0x002B */ u16 deaths;
    /* 0x002C */ char playerName[8];
    /* 0x0034 */ s16 healthCapacity;
    /* 0x0036 */ s16 health;
    /* 0x0038 */ s8 magicLevel;
    /* 0x0039 */ s8 magic;
    /* 0x003A */ s16 rupees;
    /* 0x003C */ u16 swordHealth;
    /* 0x003E */ u16 naviTimer;
    /* 0x0040 */ u8 magicAcquired;
    /* 0x0041 */ u8 doubleMagic;
    /* 0x0042 */ u8 doubleDefense;
    /* 0x0043 */ u8 unk_43;
    /* 0x0044 */ u8 unk_44;
    /* 0x0046 */ u16 unk_46;
    /* 0x0048 */ u8 unk_48;
    /* 0x004A */ s16 savedSceneNum;
    /* 0x004C */ ItemEquips equips;
    /* 0x0070 */ Inventory inventory;
    /* 0x00F8 */ u32 roomInf[128][7];
    /* 0x0EF8 */ u8 weekEventReg[100];
    /* 0x0F5C */ u32 mapsVisited;
    /* 0x0F60 */ u32 unk_F60;
    /* 0x0F64 */ u8 unk_F64;
    /* 0x0F65 */ u8 unk_F65;
    /* 0x0F66 */ u8 unk_F66[128];
    /* 0x0FE6 */ s8 unk_FE6;
    /* 0x0FE7 */ s8 unk_FE7[5];
    /* 0x0FEC */ s8 lotteryCodes[3][3];
    /* 0x0FF5 */ s8 spiderHouseMaskOrder[6];
    /* 0x0FFB */ s8 bomberCode[5];
    /* 0x1000 */ HorseData horseData;
    /* 0x100A */ u16 checksum;
    /* 0x100C */ u8 eventInf[8];
    /* 0x1014 */ u8 unk_1014;
    /* 0x1015 */ u8 unk_1015;
    /* 0x1016 */ u16 unk_1016;
    /* 0x1018 */ s16 rupeeAccumulator;
    /* 0x101A */ u8 unk_101A[6];       // One entry for each bottle
    /* 0x1020 */ OSTime unk_1020[6];   // One entry for each bottle
    /* 0x1050 */ OSTime unk_1050[6];   // One entry for each bottle
    /* 0x1080 */ OSTime unk_1080[6];   // One entry for each bottle
    /* 0x10B0 */ OSTime unk_10B0[6];   // One entry for each bottle
    /* 0x10E0 */ u64 pictoPhoto[1400]; // buffer containing the pictograph photo
    /* 0x3CA0 */ s32 fileNum;
    /* 0x3CA4 */ s16 powderKegTimer;
    /* 0x3CA6 */ u8 unk_3CA6;
    /* 0x3CA7 */ u8 unk_3CA7;
    /* 0x3CA8 */ s32 gameMode;
    /* 0x3CAC */ s32 sceneSetupIndex;
    /* 0x3CB0 */ s32 respawnFlag;
    /* 0x3CB4 */ RespawnData respawn[8];
    /* 0x3DB4 */ f32 entranceSpeed;
    /* 0x3DB8 */ u16 entranceSound;
    /* 0x3DBA */ u8 unk_3DBA;
    /* 0x3DBB */ u8 unk_3DBB;
    /* 0x3DBC */ u16 dogParams;
    /* 0x3DBE */ u8 textTriggerFlags;
    /* 0x3DBF */ u8 showTitleCard;
    /* 0x3DC0 */ s16 unk_3DC0;
    /* 0x3DC2 */ u8 unk_3DC2;
    /* 0x3DC8 */ OSTime unk_3DC8;
    /* 0x3DD0 */ u8 unk_3DD0[7];
    /* 0x3DD7 */ u8 unk_3DD7[7];
    /* 0x3DE0 */ OSTime unk_3DE0[7];
    /* 0x3E18 */ OSTime unk_3E18[7];
    /* 0x3E50 */ OSTime unk_3E50[7];
    /* 0x3E88 */ OSTime unk_3E88[7];
    /* 0x3EC0 */ OSTime unk_3EC0[7];
    /* 0x3EF8 */ s16 timerX[7];
    /* 0x3F06 */ s16 timerY[7];
    /* 0x3F14 */ s16 unk_3F14; // transformation mask related?
    /* 0x3F16 */ u8 seqIndex;
    /* 0x3F17 */ u8 nightSeqIndex;
    /* 0x3F18 */ u8 buttonStatus[6];
    /* 0x3F1E */ u8 unk_3F1E;
    /* 0x3F20 */ u16 unk_3F20;
    /* 0x3F22 */ u16 unk_3F22;
    /* 0x3F24 */ u16 unk_3F24;
    /* 0x3F26 */ u16 unk_3F26;
    /* 0x3F28 */ s16 unk_3F28;
    /* 0x3F2A */ s16 unk_3F2A;
    /* 0x3F2C */ s16 unk_3F2C;
    /* 0x3F2E */ s16 unk_3F2E;
    /* 0x3F30 */ s16 unk_3F30;
    /* 0x3F32 */ s16 unk_3F32;
    /* 0x3F34 */ s16 unk_3F34;
    /* 0x3F36 */ u16 mapIndex; // map/minimap index
    /* 0x3F38 */ u16 minigameState;
    /* 0x3F3A */ u16 minigameScore;
    /* 0x3F3C */ u16 unk_3F3C; // minigame related
    /* 0x3F3E */ u8 unk_3F3E;
    /* 0x3F3F */ u8 unk_3F3F;
    /* 0x3F40 */ u16 option_id;
    /* 0x3F42 */ u8 language;
    /* 0x3F43 */ u8 audioSetting;
    /* 0x3F44 */ u8 unk_3F44;
    /* 0x3F45 */ u8 zTargetSetting; // 0: Switch; 1: Hold
    /* 0x3F46 */ u16 unk_3F46;      // bgm related
    /* 0x3F48 */ u8 unk_3F48;       // transition related
    /* 0x3F4A */ u16 unk_3F4A;      // transition related
    /* 0x3F4C */ u8 cutsceneTrigger;
    /* 0x3F4D */ u8 unk_3F4D;
    /* 0x3F4E */ u16 nextDayTime;
    /* 0x3F50 */ u8 fadeDuration;
    /* 0x3F51 */ u8 unk_3F51; // transition related
    /* 0x3F52 */ u16 environmentTime;
    /* 0x3F54 */ u8 dogIsLost;
    /* 0x3F55 */ u8 nextTransition;
    /* 0x3F56 */ s16 worldMapArea;
    /* 0x3F58 */ s16 unk_3F58;
    /* 0x3F5A */ s16 healthAccumulator;
    /* 0x3F5C */ s32 unk_3F5C;
    /* 0x3F60 */ u8 unk_3F60;
    /* 0x3F64 */ f32 unk_3F64;
    /* 0x3F68 */ u32 unk_3F68[5][120];
    /* 0x48C8 */ u16 unk_48C8;
    /* 0x48CA */ u8 unk_48CA[27];
} SaveContext; // size = 0x48C8

typedef enum {
    /* 0x00 */ RESPAWN_MODE_DOWN,   /* Normal Void Outs */
    /* 0x01 */ RESPAWN_MODE_RETURN, /* Grotto Returnpoints */
    /* 0x02 */ RESPAWN_MODE_TOP     /* Farore's Wind */
} RespawnMode;

typedef enum {
    /* 0x00 */ BTN_ENABLED,
    /* 0xFF */ BTN_DISABLED = 0xFF
} ButtonStatus;

#endif
