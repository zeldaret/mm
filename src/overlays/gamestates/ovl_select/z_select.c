/*
 * File: z_select.c
 * Overlay: ovl_select
 * Description: Debug Map Select Menu
 */

#include "z_select.h"
#include "libc/alloca.h"
#include "overlays/gamestates/ovl_title/z_title.h"

void MapSelect_LoadTitle(MapSelectState* this) {
    {
        GameState* gameState = &this->state;
        gameState->running = false;
    }

    SET_NEXT_GAMESTATE(&this->state, Title_Init, TitleContext);
}

void MapSelect_LoadGame(MapSelectState* this, u32 entranceIndex, s32 opt) {
    if (gSaveContext.fileNum == 0xFF) {
        Sram_InitDebugSave();
    }

    gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_ENABLED;
    gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_ENABLED;
    gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_ENABLED;
    gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_ENABLED;
    gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_ENABLED;
    gSaveContext.unk_3F1E = 0;
    gSaveContext.unk_3F20 = 0;
    gSaveContext.unk_3F22 = 0;
    gSaveContext.unk_3F24 = 0;

    Audio_QueueSeqCmd(NA_BGM_STOP);
    gSaveContext.save.entranceIndex = entranceIndex;

    if (opt != 0) {
        gSaveContext.save.entranceIndex =
            Entrance_CreateIndex((s32)gSaveContext.save.entranceIndex >> 9, opt, gSaveContext.save.entranceIndex & 0xF);
    }
    if (gSaveContext.save.entranceIndex == 0xC000) {
        gSaveContext.save.day = 0;
        gSaveContext.save.time = CLOCK_TIME(6, 0) - 1;
    }

    gSaveContext.respawn[RESPAWN_MODE_DOWN].entranceIndex = 0xFFFF;
    gSaveContext.seqIndex = (u8)NA_BGM_DISABLED;
    gSaveContext.nightSeqIndex = 0xFF;
    gSaveContext.showTitleCard = true;
    gSaveContext.respawnFlag = 0;
    gSaveContext.respawn[RESPAWN_MODE_GORON].entranceIndex = 0xFF;
    gSaveContext.respawn[RESPAWN_MODE_ZORA].entranceIndex = 0xFF;
    gSaveContext.respawn[RESPAWN_MODE_DEKU].entranceIndex = 0xFF;
    gSaveContext.respawn[RESPAWN_MODE_HUMAN].entranceIndex = 0xFF;
    gWeatherMode = 0;

    do {
        GameState* gameState = &this->state;
        gameState->running = false;
    } while (0);
    SET_NEXT_GAMESTATE(&this->state, Play_Init, PlayState);
}

// "Translation" (Actual name)
static SceneSelectEntry sScenes[] = {
    // "0: OP Woods for Cutscene Use" (Forest Opening Scene)
    { "  0:OP" GFXP_KATAKANA "ﾃﾞﾓ" GFXP_HIRAGANA "ﾖｳ ｼﾝﾘﾝ", MapSelect_LoadGame, 0x1C00 },

    // "0-0: Lost Woods" (Lost Woods)
    { "  0-0:" GFXP_HIRAGANA "ﾏﾖｲ ﾉ ﾓﾘ", MapSelect_LoadGame, 0xC400 },

    // "1: Town Outskirts" (Termina Field)
    { "  1:" GFXP_KATAKANA "ﾀｳﾝ " GFXP_HIRAGANA "ｺｳｶﾞｲ", MapSelect_LoadGame, 0x5400 },

    // "1-0: Astral Observatory" (Astral Observatory)
    { "  1-0:" GFXP_HIRAGANA "ﾃﾝﾓﾝｶﾝｿｸｼﾞｮ", MapSelect_LoadGame, 0x4C00 },

    // "1-1: Astral Observatory Telescope" (Astral Observatory - Telescope)
    { "  1-1:" GFXP_HIRAGANA "ﾃﾝﾓﾝｶﾝｿｸｼﾞｮ ﾃﾞ ﾎﾞｳｴﾝｷｮｳ", MapSelect_LoadGame, 0x54A0 },

    // "1-2: Ikana Graveyard" (Ikana Canyon Graveyard)
    { "  1-2:" GFXP_KATAKANA "ｲｶｰﾅ " GFXP_HIRAGANA "ﾉ ﾊｶﾊﾞ", MapSelect_LoadGame, 0x8000 },

    // "2: Romani Ranch" (Romani Ranch)
    { "  2:" GFXP_KATAKANA "ﾛﾏﾆｰ " GFXP_HIRAGANA "ﾎﾞｸｼﾞｮｳ", MapSelect_LoadGame, 0x6400 },

    // "3: Milk Road" (Milk Road)
    { "  3:" GFXP_KATAKANA "ﾐﾙｸﾛｰﾄﾞ", MapSelect_LoadGame, 0x3E00 },

    // "4: Main Building" ("Ranch House)
    { "  4:" GFXP_HIRAGANA "ｵﾓﾔ", MapSelect_LoadGame, 0x610 },

    // "5: Cow Shed" (Cow Shed)
    { "  5:" GFXP_HIRAGANA "ｳｼｺﾞﾔ", MapSelect_LoadGame, 0x600 },

    // "6: Cucco Shed" (Cucco Shed)
    { "  6:" GFXP_KATAKANA "ｺｯｺ " GFXP_HIRAGANA "ｺﾞﾔ", MapSelect_LoadGame, 0x7E00 },

    // "7: Dog Racing Area" (Doggy Racetrack)
    { "  7:" GFXP_KATAKANA "ﾄﾞｯｸﾞﾚｰｽ" GFXP_HIRAGANA "ｼﾞｮｳ", MapSelect_LoadGame, 0x7C00 },

    // "8: Gorman Track" (Gorman Track)
    { "  8:" GFXP_KATAKANA "ｺﾞｰﾏﾝ ﾄﾗｯｸ", MapSelect_LoadGame, 0xCE00 },

    // "10: Mountain Village -Winter-" (Mountain Village - Winter)
    { " 10:" GFXP_HIRAGANA "ﾔﾏｻﾞﾄ -ﾌﾕ-", MapSelect_LoadGame, 0x9A00 },

    // "10-0: Mountain Village -Spring-" (Mountain Village - Spring)
    { " 10-0:" GFXP_HIRAGANA "ﾔﾏｻﾞﾄ -ﾊﾙ-", MapSelect_LoadGame, 0xAE00 },

    // "10-1: Mountain Village Blacksmith" (Mountain Smithy)
    { " 10-1:" GFXP_HIRAGANA "ﾔﾏｻﾞﾄ ﾉ ｶｼﾞﾔ", MapSelect_LoadGame, 0x5200 },

    // "11: Goron Village -Winter-" (Goron Village - Winter)
    { " 11:" GFXP_KATAKANA "ｺﾞﾛﾝ" GFXP_HIRAGANA " ﾉ ｻﾄ -ﾌﾕ-", MapSelect_LoadGame, 0x9400 },

    // "11-0: Goron Village -Spring-" (Goron Village - Spring)
    { " 11-0:" GFXP_KATAKANA "ｺﾞﾛﾝ" GFXP_HIRAGANA " ﾉ ｻﾄ -ﾊﾙ-", MapSelect_LoadGame, 0x8A00 },

    // "11-1: Goron Shrine" (Goron Shrine)
    { " 11-1:" GFXP_KATAKANA "ｺﾞﾛﾝ" GFXP_HIRAGANA " ﾉ ﾎｺﾗ", MapSelect_LoadGame, 0x5E00 },

    // "11-2: Lone Peak Shrine" (Lone Peak Shrine)
    { " 11-2:" GFXP_HIRAGANA "ﾊﾅﾚﾔﾏ ﾉ ﾎｺﾗ", MapSelect_LoadGame, 0x1500 },

    // "11-3: Goron Shop" (Goron Shop)
    { " 11-3:" GFXP_KATAKANA "ｺﾞﾛﾝ " GFXP_HIRAGANA "ﾉ ﾐｾ", MapSelect_LoadGame, 0x7400 },

    // "12: Snowhead" (Snowhead)
    { " 12:" GFXP_KATAKANA "ｽﾉｰﾍｯﾄﾞ", MapSelect_LoadGame, 0xB200 },

    // "13: Blizzard Path" (Path to Goron Village - Part 1)
    { " 13:" GFXP_HIRAGANA "ﾌﾌﾞｷ ﾉ ﾐﾁ", MapSelect_LoadGame, 0x3200 },

    // "14: Snowball Path" (Path to Goron Village - Part 2)
    { " 14:" GFXP_HIRAGANA "ﾕｷﾀﾞﾏ ﾉ ﾐﾁ", MapSelect_LoadGame, 0xB000 },

    // "15: Goron Racetrack" (Goron Racetrack)
    { " 15:" GFXP_KATAKANA "ｺﾞﾛﾝﾚｰｽ " GFXP_HIRAGANA "ｼﾞｮｳ", MapSelect_LoadGame, 0xD000 },

    // "16: Goron Grave" (Darmani's Grave)
    { " 16:" GFXP_KATAKANA "ｺﾞﾛﾝ " GFXP_HIRAGANA "ﾉ ﾊｶ", MapSelect_LoadGame, 0x9600 },

    // "17: Snow Field Battle -Winter-" (Path to Goron Village - Winter)
    { " 17:" GFXP_HIRAGANA "ｾﾂｹﾞﾝ " GFXP_KATAKANA "ﾊﾞﾄﾙ " GFXP_HIRAGANA "-ﾌﾕ-", MapSelect_LoadGame, 0xB400 },

    // "17-0: Snow Field Battle -Spring-" (Path to Goron Village - Spring)
    { " 17-0:" GFXP_HIRAGANA "ｾﾂｹﾞﾝ " GFXP_KATAKANA "ﾊﾞﾄﾙ " GFXP_HIRAGANA "-ﾊﾙ-", MapSelect_LoadGame, 0xB600 },

    // "20: Swampland" (Southern Swamp)
    { " 20:" GFXP_HIRAGANA "ﾇﾏﾁ", MapSelect_LoadGame, 0x8400 },

    // "20-0: Swampland - Afterwards" (Southern Swamp - After Odolwa)
    { " 20-0:" GFXP_HIRAGANA "ﾇﾏﾁ ｿﾉｺﾞ", MapSelect_LoadGame, 0xC00 },

    // "20-1: Swamp Tourist Information" (Tourist Information)
    { " 20-1:" GFXP_HIRAGANA "ﾇﾏ ﾉ ｶﾝｺｳｱﾝﾅｲ", MapSelect_LoadGame, 0xA800 },

    // "20-2: Magic Hags' Potion Shop" (Magic Hags' Potion Shop)
    { " 20-2:" GFXP_HIRAGANA "ﾏﾎｳｵﾊﾞﾊﾞ ﾉ ｸｽﾘﾔ", MapSelect_LoadGame, 0x400 },

    // "21: Wood Mountain" (Woodfall)
    { " 21:" GFXP_KATAKANA "ｳｯﾄﾞﾏｳﾝﾃﾝ", MapSelect_LoadGame, 0x8600 },

    // "21-0: Deku Princess's Prison" (Deku Princess's Prison Cutscene: Tatl Apologizes)
    { " 21-0:" GFXP_KATAKANA "ﾃﾞｸ" GFXP_HIRAGANA "ﾋﾒ ﾉ ﾛｳﾔ", MapSelect_LoadGame, 0x3010 },

    // "22: Deku Castle" (Deku Palace)
    { " 22:" GFXP_KATAKANA "ﾃﾞｸﾅｯﾂ " GFXP_HIRAGANA "ﾉ ｼﾛ", MapSelect_LoadGame, 0x5000 },

    // "22-0: Boe Hole 0" (Deku Palace Grotto 0 - Deku Baba & Butterflies, Entrance 1)
    { " 22-0:" GFXP_KATAKANA "ｸﾛｽｹ " GFXP_HIRAGANA "ﾉ ｱﾅ0", MapSelect_LoadGame, 0x1460 },

    // "22-1: Boe Hole 1" (Deku Palace Grotto 1 - Deku Baba & Butterflies, Entrance 2)
    { " 22-1:" GFXP_KATAKANA "ｸﾛｽｹ " GFXP_HIRAGANA "ﾉ ｱﾅ1", MapSelect_LoadGame, 0x14E0 },

    // "22-2: Boe Hole 2" (Deku Palace Grotto 2 - Skullwalltula Wall, Lower Entrance)
    { " 22-2:" GFXP_KATAKANA "ｸﾛｽｹ " GFXP_HIRAGANA "ﾉ ｱﾅ2", MapSelect_LoadGame, 0x1480 },

    // "22-3: Boe Hole 3" (Deku Palace Grotto 3 - Skullwalltula Wall, Upper Entrance)
    { " 22-3:" GFXP_KATAKANA "ｸﾛｽｹ " GFXP_HIRAGANA "ﾉ ｱﾅ3", MapSelect_LoadGame, 0x14F0 },

    // "22-4: Boe Hole 4" (Deku Palace Grotto 4 - Bean Seller)
    { " 22-4:" GFXP_KATAKANA "ｸﾛｽｹ " GFXP_HIRAGANA "ﾉ ｱﾅ4", MapSelect_LoadGame, 0x14C0 },

    // "24: Beast Path" (Road to Swamp)
    { " 24:" GFXP_HIRAGANA "ｹﾓﾉﾐﾁ", MapSelect_LoadGame, 0x7A00 },

    // "24-0: Forest Shooting Gallery" (Swamp Shooting Gallery)
    { " 24-0:" GFXP_HIRAGANA "ﾓﾘ ﾉ ｼｬﾃｷｼﾞｮｳ", MapSelect_LoadGame, 0x4200 },

    // "25: Deku King's Chamber" (Deku Palace Throne Room)
    { " 25:" GFXP_KATAKANA "ﾃﾞｸ" GFXP_HIRAGANA "ｵｳ ﾉ ﾏ", MapSelect_LoadGame, 0x7600 },

    // "26: Woods of Mystery" (Woods of Mystery)
    { " 26:" GFXP_HIRAGANA "ﾌｼｷﾞ ﾉ ﾓﾘ", MapSelect_LoadGame, 0xC200 },

    // "30: Great Bay Coast" (Great Bay Coast - Entrance Area)
    { " 30:" GFXP_KATAKANA "ｸﾞﾚｰﾄﾍﾞｲ" GFXP_HIRAGANA " ﾉ ｶｲｶﾞﾝ", MapSelect_LoadGame, 0x6800 },

    // "30-0: Ocean Laboratory" (Marine Research Lab)
    { " 30-0:" GFXP_HIRAGANA "ｶｲﾖｳ ｹﾝｷｭｳｼﾞｮ", MapSelect_LoadGame, 0x5800 },

    // "30-1: Fisherman's House" (Fisherman's Hut)
    { " 30-1:" GFXP_HIRAGANA "ﾘｮｳｼ ﾉ ｲｴ", MapSelect_LoadGame, 0x7200 },

    // "30-2: Pointed Rock" (Twin Pillars)
    { " 30-2:" GFXP_HIRAGANA "ﾄﾝｶﾞﾘ ｲﾜ", MapSelect_LoadGame, 0x4400 },

    // "31: Cape" (Great Bay Coast - River Area)
    { " 31:" GFXP_HIRAGANA "ﾐｻｷ", MapSelect_LoadGame, 0x6A00 },

    // "32: Outside of Pirates' Fortress" (Pirates' Fortress - Exterior)
    { " 32:" GFXP_HIRAGANA "ｶｲｿﾞｸﾉﾄﾘﾃﾞﾏｴ", MapSelect_LoadGame, 0x7000 },

    // "32-0: Pirates' Fortress" (Pirates' Fortress - Courtyard)
    { " 32-0:" GFXP_HIRAGANA "ｶｲｿﾞｸﾉﾄﾘﾃﾞ", MapSelect_LoadGame, 0x2200 },

    // "32-1: Pirates' Fortress - Telescope" (Pirates' Fortress - Secret Entrance, Looking Through Telescope)
    { " 32-1:" GFXP_HIRAGANA "ｶｲｿﾞｸﾉﾄﾘﾃﾞ ﾎﾞｳｴﾝｷｮｳ", MapSelect_LoadGame, 0x22A0 },

    // "32-2: Pirates' Fortress - Interior 0" (Pirates' Fortress - Throne Room)
    { " 32-2:" GFXP_HIRAGANA "ｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ0", MapSelect_LoadGame, 0x4000 },

    // "32-3: Pirates' Fortress - Interior 1" (Pirates' Fortress - View of Throne Room, Wasp Nest)
    { " 32-3:" GFXP_HIRAGANA "ｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ1", MapSelect_LoadGame, 0x4010 },

    // "32-4: Pirates' Fortress - Interior 2" (Pirates' Fortress - Tempting Treasure Chest, Leading to 32-5)
    { " 32-4:" GFXP_HIRAGANA "ｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ2", MapSelect_LoadGame, 0x4020 },

    // "32-5: Pirates' Fortress - Interior 3" (Pirates' Fortress - Zora Egg Room, One Shell Blade)
    { " 32-5:" GFXP_HIRAGANA "ｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ3", MapSelect_LoadGame, 0x4030 },

    // "32-6: Pirates' Fortress - Interior 4" (Pirates' Fortress - Oil Drum Room, Leading to 32-7)
    { " 32-6:" GFXP_HIRAGANA "ｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ4", MapSelect_LoadGame, 0x4040 },

    // "32-7: Pirates' Fortress - Interior 5" (Pirates' Fortress - Zora Egg Room, One Shell Blade)
    { " 32-7:" GFXP_HIRAGANA "ｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ5", MapSelect_LoadGame, 0x4050 },

    // "32-8: Pirates' Fortress - Interior 6" (Pirates' Fortress - Fenced Indoor Walkway, Leading to 32-9)
    { " 32-8:" GFXP_HIRAGANA "ｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ6", MapSelect_LoadGame, 0x4060 },

    // "32-9: Pirates' Fortress - Interior 7" (Pirates' Fortress - Zora Egg Room, One Desbreko & Treasure Chest)
    { " 32-9:" GFXP_HIRAGANA "ｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ7", MapSelect_LoadGame, 0x4070 },

    // "32-10: Pirates' Fortress - Interior 8" (Pirates' Fortress - End of Secret Entrance: Telescope Room)
    { " 32-10:" GFXP_HIRAGANA "ｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ8", MapSelect_LoadGame, 0x4080 },

    // "32-11: Pirates' Fortress - Interior 9" (Pirates' Fortress - Start of Secret Entrance)
    { " 32-11:" GFXP_HIRAGANA "ｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ9", MapSelect_LoadGame, 0x4090 },

    // "33: Zora Shrine" (Zora Hall)
    { " 33:" GFXP_KATAKANA "ｿﾞｰﾗ " GFXP_HIRAGANA "ﾉ ﾎｺﾗ", MapSelect_LoadGame, 0x6000 },

    // "33-0: Zora Shop" (Zora Shop)
    { " 33-0:" GFXP_KATAKANA "ｿﾞｰﾗ " GFXP_HIRAGANA "ﾉ ﾐｾ", MapSelect_LoadGame, 0x9250 },

    // "33-1: Zora Waiting Room" (Mikau & Tijo's Room)
    { " 33-1:" GFXP_KATAKANA "ｿﾞｰﾗ " GFXP_HIRAGANA "ﾉ ﾋｶｴｼﾂ", MapSelect_LoadGame, 0x9200 },

    // "34: Great Bay" (Great Bay Cutscene: Pirates Approach Temple)
    { " 34:" GFXP_KATAKANA "ｸﾞﾚｰﾄﾍﾞｲ", MapSelect_LoadGame, 0xBE00 },

    // "35: Mountain Stream Above Falls" (Waterfall Rapids)
    { " 35:" GFXP_HIRAGANA "ﾀｷｳｴ ﾉ ｹｲﾘｭｳ", MapSelect_LoadGame, 0x8E00 },

    // "40: Rock Building Shaft" (Stone Tower)
    { " 40:" GFXP_KATAKANA "ﾛｯｸﾋﾞﾙ" GFXP_HIRAGANA " ﾉ ﾀﾃｱﾅ", MapSelect_LoadGame, 0xAA00 },

    // "40-0: Heaven & Earth Are Overturned" (Stone Tower Cutscene: Tower is Flipped)
    { " 40-0:" GFXP_HIRAGANA "ﾃﾝﾁ ｷﾞｬｸﾃﾝ", MapSelect_LoadGame, 0xAC00 },

    // "41: Road to Ikana" (Road to Ikana)
    { " 41:" GFXP_KATAKANA "ｲｶｰﾅ " GFXP_HIRAGANA "ﾍﾉ ﾐﾁ", MapSelect_LoadGame, 0xA000 },

    // "42: Ancient Castle of Ikana" (Ancient Castle of Ikana)
    { " 42:" GFXP_KATAKANA "ｲｶｰﾅ" GFXP_HIRAGANA " ｺｼﾞｮｳ", MapSelect_LoadGame, 0x3400 },

    // "42-0: Ancient Castle of Ikana - Interior" (Ancient Castle of Ikana - Interior)
    { " 42-0:" GFXP_KATAKANA "ｲｶｰﾅ" GFXP_HIRAGANA " ﾉ ｺｼﾞｮｳ ﾅｲﾌﾞ", MapSelect_LoadGame, 0x3430 },

    // "42-B: Ancient Castle of Ikana - Boss Room" (Ikana King's Throne)
    { " 42-B:" GFXP_KATAKANA "ｲｶｰﾅ" GFXP_HIRAGANA " ﾉ ｺｼﾞｮｳ " GFXP_KATAKANA "ﾎﾞｽ" GFXP_HIRAGANA "ﾍﾞﾔ",
      MapSelect_LoadGame, 0xA600 },

    // "43: Ikana Canyon" (Ikana Canyon)
    { " 43:" GFXP_KATAKANA "ｲｶｰﾅ " GFXP_HIRAGANA "ｹｲｺｸ", MapSelect_LoadGame, 0x2000 },

    // "43-0: Ikana Canyon Cave" (Sharp's Cave)
    { " 43-0:" GFXP_KATAKANA "ｲｶｰﾅ " GFXP_HIRAGANA "ｹｲｺｸ ﾄﾞｳｸﾂ", MapSelect_LoadGame, 0x20E0 },

    // "43-1: Secom's House" (Sakon's Hideout)
    { " 43-1:" GFXP_KATAKANA "ｾｺﾑ " GFXP_HIRAGANA "ﾉ ｲｴ", MapSelect_LoadGame, 0x9800 },

    // "43-2: Music Box House" (Music Box House)
    { " 43-2:" GFXP_KATAKANA "ｵﾙｺﾞｰﾙ ﾊｳｽ", MapSelect_LoadGame, 0xA400 },

    // "50: Clock Town -East-" (East Clock Town)
    { " 50:" GFXP_KATAKANA "ｸﾛｯｸﾀｳﾝ " GFXP_HIRAGANA "-ﾋｶﾞｼ-", MapSelect_LoadGame, 0xD200 },

    // "50-0: Town Target Range" (Shooting Gallery)
    { " 50-0:" GFXP_HIRAGANA "ﾏﾁ ﾉ ｼｬﾃｷｼﾞｮｳ", MapSelect_LoadGame, 0x3A00 },

    // "50-1: Honey and Darling's Shop" (Honey & Darling's Shop)
    { " 50-1:" GFXP_KATAKANA "ﾊﾆｰ ｱﾝﾄﾞ ﾀﾞｰﾘﾝ " GFXP_HIRAGANA "ﾉ ﾐｾ", MapSelect_LoadGame, 0x800 },

    // "50-2: Treasure Chest Shop" (Treasure Chest Shop)
    { " 50-2:" GFXP_HIRAGANA "ﾀｶﾗﾊﾞｺﾔ", MapSelect_LoadGame, 0x2800 },

    // "50-3: Pots 'n' Pans Inn" (Stockpot Inn)
    { " 50-3:" GFXP_KATAKANA "ﾅﾍﾞ" GFXP_HIRAGANA "ｶﾏ ﾃｲ", MapSelect_LoadGame, 0xBC00 },

    // "50-4: Mayor's House" (The Mayor's Residence)
    { " 50-4:" GFXP_HIRAGANA "ﾁｮｳﾁｮｳ ﾉ ｲｴ", MapSelect_LoadGame, 0 },

    // "50-5: Milk Bar" (Milk Bar)
    { " 50-5:" GFXP_KATAKANA "ﾐﾙｸﾊﾞｰ", MapSelect_LoadGame, 0x2400 },

    // "51: Clock Town -West-" (West Clock Town)
    { " 51:" GFXP_KATAKANA "ｸﾛｯｸﾀｳﾝ " GFXP_HIRAGANA "-ﾆｼ-", MapSelect_LoadGame, 0xD400 },

    // "51-0: Bomb Shop" (Bomb Shop)
    { " 51-0:" GFXP_HIRAGANA "ﾊﾞｸﾀﾞﾝ ﾔ", MapSelect_LoadGame, 0xCA00 },

    // "51-1: Maniac Mart" (Curiosity Shop)
    { " 51-1:" GFXP_KATAKANA "ﾏﾆ" GFXP_HIRAGANA "ﾔ", MapSelect_LoadGame, 0xE00 },

    // "51-2: General Store" (Trading Post)
    { " 51-2:" GFXP_HIRAGANA "ｻﾞｯｶ ﾔ", MapSelect_LoadGame, 0x6200 },

    // "51-3: Sword Dojo" (Swordsman's School)
    { " 51-3:" GFXP_HIRAGANA "ｹﾝﾄﾞｳｼﾞｮｳ", MapSelect_LoadGame, 0xA200 },

    // "51-4: Post House" (Post Office)
    { " 51-4:" GFXP_HIRAGANA "ﾎﾟｽﾄﾊｳｽ", MapSelect_LoadGame, 0x5600 },

    // "51-5: Lottery Shop" (Lottery Shop)
    { " 51-5:" GFXP_HIRAGANA "ﾀｶﾗｸｼﾞﾔ", MapSelect_LoadGame, 0x6C00 },

    // "52: Clock Town -North-" (North Clock Town)
    { " 52:" GFXP_KATAKANA "ｸﾛｯｸﾀｳﾝ " GFXP_HIRAGANA "-ｷﾀ-", MapSelect_LoadGame, 0xD600 },

    // "53: Clocktown -South-" (South Clock Town)
    { " 53:" GFXP_KATAKANA "ｸﾛｯｸﾀｳﾝ " GFXP_HIRAGANA "-ﾐﾅﾐ-", MapSelect_LoadGame, 0xD800 },

    // "53-0: Clock Tower Interior" (Clock Tower Interior)
    { " 53-0:" GFXP_HIRAGANA "ﾄｹｲﾄｳﾅｲﾌﾞ", MapSelect_LoadGame, 0xC000 },

    // "54: Clock Tower Rooftop" (Clock Tower Rooftop)
    { " 54:" GFXP_HIRAGANA "ﾄｹｲﾄｳ ｵｸｼﾞｮｳ", MapSelect_LoadGame, 0x2C00 },

    // "55: Laundry Area" (Laundry Pool)
    { " 55:" GFXP_HIRAGANA "ｾﾝﾀｸｼﾞｮｳ", MapSelect_LoadGame, 0xDA00 },

    // "55-0: Maniac Mart - Rear Entrance" (Curiosity Shop - Back Room)
    { " 55-0:" GFXP_KATAKANA "ﾏﾆ" GFXP_HIRAGANA "ﾔ ﾉ ｳﾗｸﾞﾁ", MapSelect_LoadGame, 0xE10 },

    // "55-1: Maniac Mart - Peephole" (Curiosity Shop Back Room - Peephole)
    { " 55-1:" GFXP_KATAKANA "ﾏﾆ" GFXP_HIRAGANA "ﾔ ﾉ ﾉｿﾞｷｱﾅ", MapSelect_LoadGame, 0xE20 },

    // "100: Wood Mountain Temple" (Woodfall Temple)
    { "100:" GFXP_KATAKANA "ｳｯﾄﾞﾏｳﾝﾃﾝ " GFXP_HIRAGANA "ﾉ ｼﾝﾃﾞﾝ", MapSelect_LoadGame, 0x3000 },

    // "100-B: Wood Mountain Temple - Boss" (Odolwa's Lair)
    { "100-B:" GFXP_KATAKANA "ｳｯﾄﾞﾏｳﾝﾃﾝ " GFXP_HIRAGANA "ﾉ ｼﾝﾃﾞﾝ" GFXP_KATAKANA "-ﾎﾞｽ-", MapSelect_LoadGame, 0x3800 },

    // "101: Snowhead Temple" (Snowhead Temple)
    { "101:" GFXP_KATAKANA "ｽﾉｰﾍｯﾄﾞ " GFXP_HIRAGANA "ﾉ ｼﾝﾃﾞﾝ", MapSelect_LoadGame, 0x3C00 },

    // "101-B: Snowhead Temple - Boss" (Goht's Lair)
    { "101-B:" GFXP_KATAKANA "ｽﾉｰﾍｯﾄﾞ " GFXP_HIRAGANA "ﾉ ｼﾝﾃﾞﾝ" GFXP_KATAKANA "-ﾎﾞｽ-", MapSelect_LoadGame, 0x8200 },

    // "102: Great Bay Temple" (Great Bay Temple)
    { "102:" GFXP_KATAKANA "ｸﾞﾚｰﾄﾍﾞｲ " GFXP_HIRAGANA "ﾉ ｼﾝﾃﾞﾝ", MapSelect_LoadGame, 0x8C00 },

    // "102-B: Great Bay Temple - Boss" (Gyorg's Lair)
    { "102-B:" GFXP_KATAKANA "ｸﾞﾚｰﾄﾍﾞｲ " GFXP_HIRAGANA "ﾉ ｼﾝﾃﾞﾝ" GFXP_KATAKANA "-ﾎﾞｽ-", MapSelect_LoadGame, 0xB800 },

    // "103: Rock Building Temple -Top Side-" (Stone Tower Temple)
    { "103:" GFXP_KATAKANA "ﾛｯｸﾋﾞﾙ " GFXP_HIRAGANA "ﾉ ｼﾝﾃﾞﾝ-ｵﾓﾃｰ", MapSelect_LoadGame, 0x2600 },

    // "103-0: Rock Building Temple -Underside-" (Stone Tower Temple - Flipped)
    { "103-0:" GFXP_KATAKANA "ﾛｯｸﾋﾞﾙ " GFXP_HIRAGANA "ﾉ ｼﾝﾃﾞﾝ-ｳﾗｰ", MapSelect_LoadGame, 0x2A00 },

    // "103-B: Rock Building Temple - Boss" (Twinmold's Lair)
    { "103-B:" GFXP_KATAKANA "ﾛｯｸﾋﾞﾙ " GFXP_HIRAGANA "ﾉ ｼﾝﾃﾞﾝ" GFXP_KATAKANA "-ﾎﾞｽ-", MapSelect_LoadGame, 0x6600 },

    // "104: Steppe" (On the Moon)
    { "104:" GFXP_KATAKANA "ｿｳｹﾞﾝ", MapSelect_LoadGame, 0xC800 },

    // "104-0: Last Deku Dungeon" (Deku Trial)
    { "104-0:" GFXP_KATAKANA "ﾗｽﾄ ﾃﾞｸ ﾀﾞﾝｼﾞｮﾝ", MapSelect_LoadGame, 0x4E00 },

    // "104-1: Last Goron Dungeon" (Goron Trial)
    { "104-1:" GFXP_KATAKANA "ﾗｽﾄ ｺﾞﾛﾝ ﾀﾞﾝｼﾞｮﾝ", MapSelect_LoadGame, 0x7800 },

    // "104-2: Last Zora Dungeon" (Zora Trial)
    { "104-2:" GFXP_KATAKANA "ﾗｽﾄ ｿﾞｰﾗ ﾀﾞﾝｼﾞｮﾝ", MapSelect_LoadGame, 0x8800 },

    // "104-3: Last Link Dungeon" (Link Trial)
    { "104-3:" GFXP_KATAKANA "ﾗｽﾄ ﾘﾝｸ ﾀﾞﾝｼﾞｮﾝ", MapSelect_LoadGame, 0xC600 },

    // "104-B: Last Dungeon -Boss-" (Majora's Lair)
    { "104-B:" GFXP_KATAKANA "ﾗｽﾄﾀﾞﾝｼﾞｮﾝ -ﾎﾞｽ-", MapSelect_LoadGame, 0x200 },

    // "119: Deku Shrine" (Deku Shrine)
    { "119:" GFXP_KATAKANA "ﾃﾞｸﾅｯﾂ " GFXP_HIRAGANA "ﾉ ﾎｺﾗ", MapSelect_LoadGame, 0x9E00 },

    // "121: Secret Shrine" (Secret Shrine)
    { "121:" GFXP_HIRAGANA "ﾋﾐﾂ ﾉ ﾎｺﾗ", MapSelect_LoadGame, 0xBA00 },

    // "122: Opening Dungeon" (Pond Area Cutscene: Falling of the Cliff)
    { "122:" GFXP_KATAKANA "ｵｰﾌﾟﾆﾝｸﾞ ﾀﾞﾝｼﾞｮﾝ", MapSelect_LoadGame, 0x2E00 },

    // "123: Giants' Chamber" (Giants' Chamber)
    { "123:" GFXP_HIRAGANA "ｷｮｼﾞﾝ ﾉ ﾏ", MapSelect_LoadGame, 0xCC00 },

    // "126: Deku Minigame" (Deku Rupee Minigame)
    { "126:" GFXP_KATAKANA "ﾃﾞｸﾅｯﾂ ﾐﾆｹﾞｰﾑ", MapSelect_LoadGame, 0x3600 },

    // "127-0: Fairy Fountain 0" (Fairy Fountain - Clock Town)
    { "127-0:" GFXP_HIRAGANA "ﾖｳｾｲ ﾉ ｲｽﾞﾐ 0", MapSelect_LoadGame, 0x4600 },

    // "127-1: Fairy Fountain 1" (Fairy Fountain - Woodfall)
    { "127-1:" GFXP_HIRAGANA "ﾖｳｾｲ ﾉ ｲｽﾞﾐ 1", MapSelect_LoadGame, 0x4610 },

    // "127-2: Fairy Fountain 2" (Fairy Fountain - Snowhead)
    { "127-2:" GFXP_HIRAGANA "ﾖｳｾｲ ﾉ ｲｽﾞﾐ 2", MapSelect_LoadGame, 0x4620 },

    // "127-3: Fairy Fountain 3" (Fairy Fountain - Great Bay Coast)
    { "127-3:" GFXP_HIRAGANA "ﾖｳｾｲ ﾉ ｲｽﾞﾐ 3", MapSelect_LoadGame, 0x4630 },

    // "127-4: Fairy Fountain 4" (Fairy Fountain - Ikana Canyon)
    { "127-4:" GFXP_HIRAGANA "ﾖｳｾｲ ﾉ ｲｽﾞﾐ 4", MapSelect_LoadGame, 0x4640 },

    // "128: Swamp Spider Manor" (Swamp Spider House)
    { "128:" GFXP_HIRAGANA "ﾇﾏ ﾉ ｸﾓﾔｶﾀ", MapSelect_LoadGame, 0x4800 },

    // "129: Ocean Spider Manor" (Oceanside Spider House)
    { "129:" GFXP_HIRAGANA "ｳﾐ ﾉ ｸﾓﾔｶﾀ", MapSelect_LoadGame, 0x4A00 },

    // "130: Beneath the Graves - Dampe" (Beneath the Graveyard)
    { "130:" GFXP_HIRAGANA "ﾊｶ ﾉ ｼﾀ-" GFXP_KATAKANA "ﾀﾞﾝﾍﾟｲ-", MapSelect_LoadGame, 0x5A00 },

    // "131: Beneath the Well" (Beneath the Well)
    { "131:" GFXP_HIRAGANA "ｲﾄﾞ ﾉ ｼﾀ", MapSelect_LoadGame, 0x9000 },

    // "132: Ghost Hut" (Ghost Hut)
    { "132:" GFXP_HIRAGANA "ﾕｳﾚｲｺﾞﾔ", MapSelect_LoadGame, 0x9C00 },

    // "133-0: Beneath the Graves 0" (Beneath the Graveyard - Part 1)
    { "133-0:" GFXP_HIRAGANA "ﾊｶ ﾉ ｼﾀ0", MapSelect_LoadGame, 0xA00 },

    // "133-1: Beneath the Graves 1" (Beneath the Graveyard - Part 2)
    { "133-1:" GFXP_HIRAGANA "ﾊｶ ﾉ ｼﾀ1", MapSelect_LoadGame, 0xA10 },

    // "134-0: Secret Grotto 0" (Secret Grotto - Four Gossip Stones)
    { "134-0:" GFXP_HIRAGANA "ｶｸｼｱﾅ 0", MapSelect_LoadGame, 0x1400 },

    // "134-1: Secret Grotto 1" (Secret Grotto - Four Gossip Stones, Skulltula)
    { "134-1:" GFXP_HIRAGANA "ｶｸｼｱﾅ 1", MapSelect_LoadGame, 0x1410 },

    // "134-2: Secret Grotto 2" (Secret Grotto - Four Gossip Stones, Water Puddles)
    { "134-2:" GFXP_HIRAGANA "ｶｸｼｱﾅ 2", MapSelect_LoadGame, 0x1420 },

    // "134-3: Secret Grotto 3" (Secret Grotto - Four Gossip Stones, Water Puddle With Bugs)
    { "134-3:" GFXP_HIRAGANA "ｶｸｼｱﾅ 3", MapSelect_LoadGame, 0x1430 },

    // "134-4: Secret Grotto 4" (Secret Grotto - Chest with Blue Rupee, Deku Babas)
    { "134-4:" GFXP_HIRAGANA "ｶｸｼｱﾅ 4", MapSelect_LoadGame, 0x1440 },

    // "134-5: Secret Grotto 5" (Secret Grotto - Hot Spring, Deku Babas, Large Stones)
    { "134-5:" GFXP_HIRAGANA "ｶｸｼｱﾅ5", MapSelect_LoadGame, 0x1450 },

    // "134-7: Secret Grotto 7" (Secret Grotto - Two Dondogos)
    { "134-7:" GFXP_HIRAGANA "ｶｸｼｱﾅ 7", MapSelect_LoadGame, 0x1470 },

    // "134-9: Secret Grotto 9" (Secret Grotto - Tall Grass With Box, Pot, Bugs)
    { "134-9:" GFXP_HIRAGANA "ｶｸｼｱﾅ 9", MapSelect_LoadGame, 0x1490 },

    // "134-10: Secret Grotto 10" (Secret Grotto - Two Cows Surrounded by Grass)
    { "134-10:" GFXP_HIRAGANA "ｶｸｼｱﾅ10", MapSelect_LoadGame, 0x14A0 },

    // "134-11: Secret Grotto 11" (Secret Grotto - Watery Hole Filled with Underwater Babas, Fish)
    { "134-11:" GFXP_HIRAGANA "ｶｸｼｱﾅ11", MapSelect_LoadGame, 0x14B0 },

    // "134-13: Secret Grotto 13" (Secret Grotto - Peahat in Center)
    { "134-13:" GFXP_HIRAGANA "ｶｸｼｱﾅ13", MapSelect_LoadGame, 0x14D0 },

    // "X 1: SPOT00" (Opening Cutscene)
    { "X 1:SPOT00", MapSelect_LoadGame, 0x1C00 },

    // "Title" (Title Screen)
    { "title", (void*)MapSelect_LoadTitle, 0x0000 },
};

void MapSelect_UpdateMenu(MapSelectState* this) {
    s32 playerForm;
    Input* controller1 = CONTROLLER1(&this->state);
    s32 stickY;
    s32 pad[2];
    s16 i;
    s32 updateRate;

    if (this->verticalInputAccumulator == 0) {
        if (CHECK_BTN_ALL(controller1->press.button, BTN_A) || CHECK_BTN_ALL(controller1->press.button, BTN_START)) {
            for (i = 0; i < ARRAY_COUNT(gSaveContext.unk_3EC0); i++) {
                gSaveContext.unk_3DD0[i] = 0;
                gSaveContext.unk_3DE0[i] = 0;
                gSaveContext.unk_3E18[i] = 0;
                gSaveContext.unk_3E50[i] = 0;
                gSaveContext.unk_3E88[i] = 0;
                gSaveContext.unk_3EC0[i] = 0;
            }
            gSaveContext.minigameState = 0;

            if (this->scenes[this->currentScene].loadFunc != NULL) {
                this->scenes[this->currentScene].loadFunc(this, this->scenes[this->currentScene].entranceIndex,
                                                          this->opt);
            }
        }

        if (CHECK_BTN_ALL(controller1->press.button, BTN_B)) {
            playerForm = gSaveContext.save.playerForm - 1;
            if (playerForm < PLAYER_FORM_FIERCE_DEITY) {
                playerForm = PLAYER_FORM_HUMAN;
            }
            gSaveContext.save.playerForm = playerForm;
        }

        if (CHECK_BTN_ALL(controller1->press.button, BTN_Z)) {
            if (gSaveContext.save.cutscene == 0x8000) {
                gSaveContext.save.cutscene = 0;
            } else if (gSaveContext.save.cutscene == 0) {
                gSaveContext.save.cutscene = 0x8800;
            } else if (gSaveContext.save.cutscene == 0x8800) {
                gSaveContext.save.cutscene = 0xFFF0;
            } else if (gSaveContext.save.cutscene == 0xFFF0) {
                gSaveContext.save.cutscene = 0xFFF1;
            } else if (gSaveContext.save.cutscene == 0xFFF1) {
                gSaveContext.save.cutscene = 0xFFF2;
            } else if (gSaveContext.save.cutscene == 0xFFF2) {
                gSaveContext.save.cutscene = 0xFFF3;
            } else if (gSaveContext.save.cutscene == 0xFFF3) {
                gSaveContext.save.cutscene = 0xFFF4;
            } else if (gSaveContext.save.cutscene == 0xFFF4) {
                gSaveContext.save.cutscene = 0xFFF5;
            } else if (gSaveContext.save.cutscene == 0xFFF5) {
                gSaveContext.save.cutscene = 0xFFF6;
            } else if (gSaveContext.save.cutscene == 0xFFF6) {
                gSaveContext.save.cutscene = 0xFFF7;
            } else if (gSaveContext.save.cutscene == 0xFFF7) {
                gSaveContext.save.cutscene = 0xFFF8;
            } else if (gSaveContext.save.cutscene == 0xFFF8) {
                gSaveContext.save.cutscene = 0xFFF9;
            } else if (gSaveContext.save.cutscene == 0xFFF9) {
                gSaveContext.save.cutscene = 0xFFFA;
            } else if (gSaveContext.save.cutscene == 0xFFFA) {
                gSaveContext.save.cutscene = 0x8000;
            }
        } else if (CHECK_BTN_ALL(controller1->press.button, BTN_R)) {
            if (gSaveContext.save.cutscene == 0x8000) {
                gSaveContext.save.cutscene = 0xFFFA;
            } else if (gSaveContext.save.cutscene == 0) {
                gSaveContext.save.cutscene = 0x8000;
            } else if (gSaveContext.save.cutscene == 0x8800) {
                gSaveContext.save.cutscene = 0;
            } else if (gSaveContext.save.cutscene == 0xFFF0) {
                gSaveContext.save.cutscene = 0x8800;
            } else if (gSaveContext.save.cutscene == 0xFFF1) {
                gSaveContext.save.cutscene = 0xFFF0;
            } else if (gSaveContext.save.cutscene == 0xFFF2) {
                gSaveContext.save.cutscene = 0xFFF1;
            } else if (gSaveContext.save.cutscene == 0xFFF3) {
                gSaveContext.save.cutscene = 0xFFF2;
            } else if (gSaveContext.save.cutscene == 0xFFF4) {
                gSaveContext.save.cutscene = 0xFFF3;
            } else if (gSaveContext.save.cutscene == 0xFFF5) {
                gSaveContext.save.cutscene = 0xFFF4;
            } else if (gSaveContext.save.cutscene == 0xFFF6) {
                gSaveContext.save.cutscene = 0xFFF5;
            } else if (gSaveContext.save.cutscene == 0xFFF7) {
                gSaveContext.save.cutscene = 0xFFF6;
            } else if (gSaveContext.save.cutscene == 0xFFF8) {
                gSaveContext.save.cutscene = 0xFFF7;
            } else if (gSaveContext.save.cutscene == 0xFFF9) {
                gSaveContext.save.cutscene = 0xFFF8;
            } else if (gSaveContext.save.cutscene == 0xFFFA) {
                gSaveContext.save.cutscene = 0xFFF9;
            }
        }

        gSaveContext.save.isNight = false;
        if (gSaveContext.save.cutscene == 0x8800) {
            gSaveContext.save.isNight = true;
        }

        if (CHECK_BTN_ALL(controller1->press.button, BTN_CUP)) {
            this->opt--;
        }
        if (CHECK_BTN_ALL(controller1->press.button, BTN_CDOWN)) {
            this->opt++;
        }

        if (CHECK_BTN_ALL(controller1->press.button, BTN_CLEFT)) {
            if (gSaveContext.save.day > 1) {
                gSaveContext.save.day--;
            }
        }

        if (CHECK_BTN_ALL(controller1->press.button, BTN_CRIGHT)) {
            if (gSaveContext.save.day < 4) {
                gSaveContext.save.day++;
            }
        }

        updateRate = R_UPDATE_RATE;
        stickY = controller1->rel.stick_y;
        if (stickY != 0) {
            this->verticalInput = (updateRate * stickY) / 7;
        } else {
            if (CHECK_BTN_ALL(controller1->press.button, BTN_DUP)) {
                if (this->lockUp == true) {
                    this->timerUp = 0;
                }
                if (this->timerUp == 0) {
                    this->timerUp = 20;
                    this->lockUp = true;

                    play_sound(NA_SE_IT_SWORD_IMPACT);
                    this->verticalInput = updateRate;
                }
            }

            if (CHECK_BTN_ALL(controller1->cur.button, BTN_DUP) && (this->timerUp == 0)) {
                play_sound(NA_SE_IT_SWORD_IMPACT);
                this->verticalInput = updateRate * 3;
            }

            if (CHECK_BTN_ALL(controller1->press.button, BTN_DDOWN)) {
                if (this->lockDown == true) {
                    this->timerDown = 0;
                }
                if (this->timerDown == 0) {
                    this->timerDown = 20;
                    this->lockDown = true;
                    play_sound(NA_SE_IT_SWORD_IMPACT);
                    this->verticalInput = -updateRate;
                }
            }
            if (CHECK_BTN_ALL(controller1->cur.button, BTN_DDOWN) && (this->timerDown == 0)) {
                play_sound(NA_SE_IT_SWORD_IMPACT);
                this->verticalInput = -updateRate * 3;
            }

            if (CHECK_BTN_ALL(controller1->press.button, BTN_DLEFT) ||
                CHECK_BTN_ALL(controller1->cur.button, BTN_DLEFT)) {
                play_sound(NA_SE_IT_SWORD_IMPACT);
                this->verticalInput = updateRate;
            }

            if (CHECK_BTN_ALL(controller1->press.button, BTN_DRIGHT) ||
                CHECK_BTN_ALL(controller1->cur.button, BTN_DRIGHT)) {
                play_sound(NA_SE_IT_SWORD_IMPACT);
                this->verticalInput = -updateRate;
            }
        }
    }

    if (CHECK_BTN_ALL(controller1->press.button, BTN_L)) {
        this->pageDownIndex++;
        this->pageDownIndex =
            (this->pageDownIndex + ARRAY_COUNT(this->pageDownStops)) % ARRAY_COUNT(this->pageDownStops);
        this->currentScene = this->topDisplayedScene = this->pageDownStops[this->pageDownIndex];
    }

    this->verticalInputAccumulator += this->verticalInput;

    if (this->verticalInputAccumulator < -7) {
        this->verticalInput = 0;
        this->verticalInputAccumulator = 0;

        this->currentScene++;
        this->currentScene = (this->currentScene + this->count) % this->count;

        if (this->currentScene == ((this->topDisplayedScene + this->count + 19) % this->count)) {
            this->topDisplayedScene++;
            this->topDisplayedScene = (this->topDisplayedScene + this->count) % this->count;
        }
    }

    if (this->verticalInputAccumulator > 7) {
        this->verticalInput = 0;
        this->verticalInputAccumulator = 0;

        if (this->currentScene == this->topDisplayedScene) {
            this->topDisplayedScene -= 2;
            this->topDisplayedScene = (this->topDisplayedScene + this->count) % this->count;
        }

        this->currentScene--;
        this->currentScene = (this->currentScene + this->count) % this->count;

        if (this->currentScene == ((this->topDisplayedScene + this->count) % this->count)) {
            this->topDisplayedScene--;
            this->topDisplayedScene = (this->topDisplayedScene + this->count) % this->count;
        }
    }

    this->currentScene = (this->currentScene + this->count) % this->count;
    this->topDisplayedScene = (this->topDisplayedScene + this->count) % this->count;

    dREG(80) = this->currentScene;
    dREG(81) = this->topDisplayedScene;
    dREG(82) = this->pageDownIndex;

    if (this->timerUp != 0) {
        this->timerUp--;
    }

    if (this->timerUp == 0) {
        this->lockUp = false;
    }

    if (this->timerDown != 0) {
        this->timerDown--;
    }

    if (this->timerDown == 0) {
        this->lockDown = false;
    }
}

void MapSelect_PrintMenu(MapSelectState* this, GfxPrint* printer) {
    s32 i;

    GfxPrint_SetColor(printer, 255, 155, 150, 255);
    GfxPrint_SetPos(printer, 12, 2);
    GfxPrint_Printf(printer, "ZELDA MAP SELECT");
    GfxPrint_SetColor(printer, 255, 255, 255, 255);

    for (i = 0; i < 20; i++) {
        s32 sceneIndex;
        char* sceneName;

        GfxPrint_SetPos(printer, 9, i + 4);
        sceneIndex = (this->topDisplayedScene + i + this->count) % this->count;
        if (sceneIndex == this->currentScene) {
            GfxPrint_SetColor(printer, 255, 20, 20, 255);
        } else {
            GfxPrint_SetColor(printer, 200, 200, 55, 255);
        }

        sceneName = this->scenes[sceneIndex].name;
        if (sceneName == NULL) {
            sceneName = "**Null**";
        }
        GfxPrint_Printf(printer, "%s", sceneName);
    }

    GfxPrint_SetColor(printer, 155, 55, 150, 255);
    GfxPrint_SetPos(printer, 20, 26);
    GfxPrint_Printf(printer, "OPT=%d", this->opt);
}

static const char* sLoadingMessages[] = {
    // "Please wait a minute"
    GFXP_HIRAGANA "ｼﾊﾞﾗｸｵﾏﾁｸﾀﾞｻｲ",
    // "Hold on a sec"
    GFXP_HIRAGANA "ﾁｮｯﾄ ﾏｯﾃﾈ",
    // "Wait a moment"
    GFXP_KATAKANA "ｳｪｲﾄ ｱ ﾓｰﾒﾝﾄ",
    // "Loading"
    GFXP_KATAKANA "ﾛｰﾄﾞ" GFXP_HIRAGANA "ﾁｭｳ",
    // "Now working"
    GFXP_HIRAGANA "ﾅｳ ﾜｰｷﾝｸﾞ",
    // "Now creating"
    GFXP_HIRAGANA "ｲﾏ ﾂｸｯﾃﾏｽ",
    // "It's not broken"
    GFXP_HIRAGANA "ｺｼｮｳｼﾞｬﾅｲﾖ",
    // "Coffee Break"
    GFXP_KATAKANA "ｺｰﾋｰ ﾌﾞﾚｲｸ",
    // "Please set B side"
    GFXP_KATAKANA "Bﾒﾝｦｾｯﾄｼﾃｸﾀﾞｻｲ",
    // "Be patient, now"
    GFXP_HIRAGANA "ｼﾞｯﾄ" GFXP_KATAKANA "ｶﾞﾏﾝ" GFXP_HIRAGANA "ﾉ" GFXP_KATAKANA "ｺ" GFXP_HIRAGANA "ﾃﾞｱｯﾀ",
    // "Please wait just a minute"
    GFXP_HIRAGANA "ｲﾏｼﾊﾞﾗｸｵﾏﾁｸﾀﾞｻｲ",
    // "Don't worry, don't worry. Take a break, take a break."
    GFXP_HIRAGANA "ｱﾜﾃﾅｲｱﾜﾃﾅｲ｡ﾋﾄﾔｽﾐﾋﾄﾔｽﾐ｡",
};

void MapSelect_PrintLoadingMessage(MapSelectState* this, GfxPrint* printer) {
    s32 randomMsg;

    GfxPrint_SetPos(printer, 10, 15);
    GfxPrint_SetColor(printer, 255, 255, 255, 255);

    randomMsg = Rand_ZeroOne() * ARRAY_COUNT(sLoadingMessages);
    GfxPrint_Printf(printer, "%s", sLoadingMessages[randomMsg]);
}

// Second column is unused
static const char* sFormLabel[][2] = {
    // "17 (Adult)" // 17 (Daitetsujin)
    { GFXP_HIRAGANA "17(ｵﾄﾅ)", GFXP_HIRAGANA "17(ﾀﾞｲﾃﾂｼﾞﾝ)" },
    // "30 (Goron)" // 30 (Ice Cream -1)
    { GFXP_KATAKANA "30(ｺﾞﾛﾝ)", GFXP_KATAKANA "30(ｱｲｽｸﾘｰﾑ-1)" },
    // "78 (Zora)" // 78 (Carmen +1)
    { GFXP_KATAKANA "78(ｿﾞｰﾗ)", GFXP_KATAKANA "78(ｶﾙﾒﾝ+1)" },
    // "12 (Deku)" // 12 (Majestic)
    { GFXP_KATAKANA "12(ﾃﾞｸﾅｯﾂ)", GFXP_KATAKANA "12(ﾏｼﾞｪｽﾃｨｯｸ)" },
    // "5 (Child)" // 5 (NTT Kodomo)
    { GFXP_HIRAGANA "5(ｺﾄﾞﾓ)", GFXP_KATAKANA "5(NTTｺﾄﾞﾓ)" },
};

void MapSelect_PrintAgeSetting(MapSelectState* this, GfxPrint* printer, s32 playerForm) {
    s32 pad;
    const char* age;
    const char*(*ageTemp)[2];
    const char*(*phi_v1)[2];
    s32 phi_v0;

    if ((playerForm >= PLAYER_FORM_FIERCE_DEITY) && (playerForm < PLAYER_FORM_MAX)) {
        ageTemp = &sFormLabel[playerForm];
        phi_v1 = ageTemp + 1;

        // This loop doesn't do anything
        for (phi_v0 = 8; phi_v0 >= 0; phi_v0 -= 8) {
            if (phi_v1 != 0) {
                break;
            }
            phi_v1--;
        }
        if (phi_v1) {}

        age = (*ageTemp)[0];
    } else {
        age = NULL;
    }

    GfxPrint_SetPos(printer, 4, 26);
    GfxPrint_SetColor(printer, 255, 255, 55, 255);
    if (age != NULL) {
        GfxPrint_Printf(printer, "Age:%s", age);
    } else {
        // clang-format off
        GfxPrint_Printf(printer, "Age:???" "(%d)", playerForm);
        // clang-format on
    }
}

void MapSelect_PrintCutsceneSetting(MapSelectState* this, GfxPrint* printer, u16 csIndex) {
    const char* stage;
    const char* day;

    GfxPrint_SetPos(printer, 4, 25);
    GfxPrint_SetColor(printer, 255, 255, 55, 255);

    // "-jara" used in these strings is a Kokiri speech quirk word
    switch (csIndex) {
        case 0:
            // clang-format off
            // "Afternoon-jara"
            gSaveContext.save.time = CLOCK_TIME(12, 0); stage = GFXP_HIRAGANA "ｵﾋﾙ" GFXP_KATAKANA "ｼﾞｬﾗ";
            // clang-format on
            break;

        case 0x8000:
            // clang-format off
            // "Morning-jara"
            gSaveContext.save.time = CLOCK_TIME(6, 0) + 1; stage = GFXP_HIRAGANA "ｱｻ " GFXP_KATAKANA "ｼﾞｬﾗ";
            // clang-format on
            break;

        case 0x8800:
            gSaveContext.save.time = CLOCK_TIME(18, 1);
            // "Night-jara"
            stage = GFXP_HIRAGANA "ﾖﾙ " GFXP_KATAKANA "ｼﾞｬﾗ";
            break;

        case 0xFFF0:
            // clang-format off
            // "Cutscene 00"
            gSaveContext.save.time = CLOCK_TIME(12, 0); stage = "ﾃﾞﾓ00";
            // clang-format on
            break;

        case 0xFFF1:
            // "Cutscene 01"
            stage = "ﾃﾞﾓ01";
            break;

        case 0xFFF2:
            // "Cutscene 02"
            stage = "ﾃﾞﾓ02";
            break;

        case 0xFFF3:
            // "Cutscene 03"
            stage = "ﾃﾞﾓ03";
            break;

        case 0xFFF4:
            // "Cutscene 04"
            stage = "ﾃﾞﾓ04";
            break;

        case 0xFFF5:
            // "Cutscene 05"
            stage = "ﾃﾞﾓ05";
            break;

        case 0xFFF6:
            // "Cutscene 06"
            stage = "ﾃﾞﾓ06";
            break;

        case 0xFFF7:
            // "Cutscene 07"
            stage = "ﾃﾞﾓ07";
            break;

        case 0xFFF8:
            // "Cutscene 08"
            stage = "ﾃﾞﾓ08";
            break;

        case 0xFFF9:
            // "Cutscene 09"
            stage = "ﾃﾞﾓ09";
            break;

        case 0xFFFA:
            // "Cutscene 0A"
            stage = "ﾃﾞﾓ0A";
            break;

        default:
            stage = "???";
            break;
    }
    gSaveContext.skyboxTime = gSaveContext.save.time;
    GfxPrint_Printf(printer, "Stage:" GFXP_KATAKANA "%s", stage);

    GfxPrint_SetPos(printer, 23, 25);
    GfxPrint_SetColor(printer, 255, 255, 55, 255);

    switch (gSaveContext.save.day) {
        case 1:
            // "The First Day"
            day = GFXP_HIRAGANA "ｻｲｼｮﾉﾋ";
            break;

        case 2:
            // "The Next Day"
            day = GFXP_HIRAGANA "ﾂｷﾞﾉﾋ";
            break;

        case 3:
            // "The Final Day"
            day = GFXP_HIRAGANA "ｻｲｺﾞﾉﾋ";
            break;

        case 4:
            // "Clear Day"
            day = GFXP_HIRAGANA "ｸﾘｱｰﾉﾋ";
            break;

        default:
            gSaveContext.save.day = 1;
            // "The First Day"
            day = GFXP_HIRAGANA "ｻｲｼｮﾉﾋ";
            break;
    }

    GfxPrint_Printf(printer, "Day:" GFXP_HIRAGANA "%s", day);
}

void MapSelect_DrawMenu(MapSelectState* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;
    GfxPrint* printer;

    OPEN_DISPS(gfxCtx);

    func_8012C4C0(gfxCtx);

    printer = alloca(sizeof(GfxPrint));
    GfxPrint_Init(printer);
    GfxPrint_Open(printer, POLY_OPA_DISP);

    MapSelect_PrintMenu(this, printer);
    MapSelect_PrintAgeSetting(this, printer, ((void)0, gSaveContext.save.playerForm));
    MapSelect_PrintCutsceneSetting(this, printer, ((void)0, gSaveContext.save.cutscene));

    POLY_OPA_DISP = GfxPrint_Close(printer);
    GfxPrint_Destroy(printer);

    CLOSE_DISPS(gfxCtx);
}

void MapSelect_DrawLoadingScreen(MapSelectState* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;
    GfxPrint printer;

    OPEN_DISPS(gfxCtx);

    func_8012C4C0(gfxCtx);

    GfxPrint_Init(&printer);
    GfxPrint_Open(&printer, POLY_OPA_DISP);

    MapSelect_PrintLoadingMessage(this, &printer);

    POLY_OPA_DISP = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);

    CLOSE_DISPS(gfxCtx);
}

void MapSelect_Draw(MapSelectState* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;

    func_8012CF0C(gfxCtx, true, true, 0, 0, 0);

    SET_FULLSCREEN_VIEWPORT(&this->view);
    View_RenderView(&this->view, 0xF);
    if (!this->state.running) {
        MapSelect_DrawLoadingScreen(this);
    } else {
        MapSelect_DrawMenu(this);
    }
}

void MapSelect_Main(GameState* thisx) {
    MapSelectState* this = (MapSelectState*)thisx;

    MapSelect_UpdateMenu(this);
    MapSelect_Draw(this);
}

void MapSelect_Destroy(GameState* thisx) {
    ShrinkWindow_Destroy();
}

void MapSelect_Init(GameState* thisx) {
    MapSelectState* this = (MapSelectState*)thisx;

    this->state.main = MapSelect_Main;
    this->state.destroy = MapSelect_Destroy;

    this->scenes = sScenes;
    this->topDisplayedScene = 0;
    this->currentScene = 0;
    this->pageDownStops[0] = 0;
    this->pageDownStops[1] = 19;
    this->pageDownStops[2] = 37;
    this->pageDownStops[3] = 51;
    this->pageDownStops[4] = 59;
    this->pageDownStops[5] = 73;
    this->pageDownStops[6] = 91;
    this->pageDownIndex = 0;
    this->opt = 0;
    this->count = ARRAY_COUNT(sScenes);

    ShrinkWindow_Init();
    View_Init(&this->view, this->state.gfxCtx);
    this->view.flags = (0x08 | 0x02);
    this->verticalInputAccumulator = 0;
    this->verticalInput = 0;
    this->timerUp = 0;
    this->timerDown = 0;
    this->lockUp = false;
    this->lockDown = false;
    this->unk_274 = 0;

    if ((dREG(80) >= 0) && (dREG(80) < this->count)) {
        this->currentScene = dREG(80);
        this->topDisplayedScene = dREG(81);
        this->pageDownIndex = dREG(82);
    }

    Game_SetFramerateDivisor(&this->state, 1);
    gSaveContext.save.cutscene = 0;
    gSaveContext.save.playerForm = PLAYER_FORM_HUMAN;
    gSaveContext.save.linkAge = 0;
}
