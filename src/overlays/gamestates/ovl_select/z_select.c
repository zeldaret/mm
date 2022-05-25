/*
 * File: z_select.c
 * Overlay: ovl_select
 * Description: Debug map select
 */

#include "z_select.h"
#include "libc/alloca.h"
#include "overlays/gamestates/ovl_title/z_title.h"

void Select_LoadTitle(SelectContext* this) {
    {
        GameState* gameState = &this->state;
        gameState->running = false;
    }

    SET_NEXT_GAMESTATE(&this->state, Title_Init, TitleContext);
}

void Select_LoadGame(SelectContext* this, u32 entranceIndex, s32 opt) {
    if (gSaveContext.fileNum == 0xFF) {
        Sram_InitDebugSave();
    }

    gSaveContext.buttonStatus[0] = BTN_ENABLED;
    gSaveContext.buttonStatus[1] = BTN_ENABLED;
    gSaveContext.buttonStatus[2] = BTN_ENABLED;
    gSaveContext.buttonStatus[3] = BTN_ENABLED;
    gSaveContext.buttonStatus[4] = BTN_ENABLED;
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

    gSaveContext.respawn[RESTART_MODE_DOWN].entranceIndex = 0xFFFF;
    gSaveContext.seqIndex = (u8)NA_BGM_DISABLED;
    gSaveContext.nightSeqIndex = 0xFF;
    gSaveContext.showTitleCard = true;
    gSaveContext.respawnFlag = 0;
    gSaveContext.respawn[RESPAWN_MODE_GORON].entranceIndex = 0xFF;
    gSaveContext.respawn[RESPAWN_MODE_ZORA].entranceIndex = 0xFF;
    gSaveContext.respawn[RESPAWN_MODE_DEKU].entranceIndex = 0xFF;
    gSaveContext.respawn[RESPAWN_MODE_HUMAN].entranceIndex = 0xFF;
    D_801BDBB0 = 0;

    do {
        GameState* gameState = &this->state;
        gameState->running = false;
    } while (0);
    SET_NEXT_GAMESTATE(&this->state, Play_Init, GlobalContext);
}

// "Translation" ("Actual name")
static SceneSelectEntry sScenes[] = {
    // "  0: OP Woods for Cutscene Use" ("  0: Forest Opening Scene")
    { "  0:OP\x8Cﾃﾞﾓ\x8Dﾖｳ ｼﾝﾘﾝ", Select_LoadGame, 0x1C00 },
    // "  0-0: Lost Woods" ("  0-0: Lost Woods")
    { "  0-0:\x8Dﾏﾖｲ ﾉ ﾓﾘ", Select_LoadGame, 0xC400 },
    // "  1: Town Outskirts" ("  1: Termina Field")
    { "  1:\x8Cﾀｳﾝ \x8Dｺｳｶﾞｲ", Select_LoadGame, 0x5400 },
    // "  1-0: Astral Observatory" ("  1-0: Astral Observatory")
    { "  1-0:\x8Dﾃﾝﾓﾝｶﾝｿｸｼﾞｮ", Select_LoadGame, 0x4C00 },
    // "  1 - 1: Astral Observatory Telescope" ("  1 - 1: Astral Observatory - Telescope")
    { "  1-1:\x8Dﾃﾝﾓﾝｶﾝｿｸｼﾞｮ ﾃﾞ ﾎﾞｳｴﾝｷｮｳ", Select_LoadGame, 0x54A0 },
    // "  1 - 2: Ikana Graveyard" ("  1 - 2: Ikana Canyon Graveyard")
    { "  1-2:\x8Cｲｶｰﾅ \x8Dﾉ ﾊｶﾊﾞ", Select_LoadGame, 0x8000 },
    // "  2: Romani Ranch" ("  2: Romani Ranch")
    { "  2:\x8Cﾛﾏﾆｰ \x8Dﾎﾞｸｼﾞｮｳ", Select_LoadGame, 0x6400 },
    // "  3: Milk Road" ("  3: Milk Road")
    { "  3:\x8Cﾐﾙｸﾛｰﾄﾞ", Select_LoadGame, 0x3E00 },
    // "  4: Main Building" ("  4: Ranch House")
    { "  4:\x8Dｵﾓﾔ", Select_LoadGame, 0x610 },
    // "  5: Cow Shed" ("  5: Cow Shed")
    { "  5:\x8Dｳｼｺﾞﾔ", Select_LoadGame, 0x600 },
    // "  6: Cucco Shed" ("  6: Cucco Shed")
    { "  6:\x8Cｺｯｺ \x8Dｺﾞﾔ", Select_LoadGame, 0x7E00 },
    // "  7: Dog Racing Area" ("  7: Doggy Racetrack")
    { "  7:\x8Cﾄﾞｯｸﾞﾚｰｽ\x8Dｼﾞｮｳ", Select_LoadGame, 0x7C00 },
    // "  8: Gorman Track" ("  8: Gorman Track")
    { "  8:\x8Cｺﾞｰﾏﾝ ﾄﾗｯｸ", Select_LoadGame, 0xCE00 },
    // " 10: Mountain Village -Winter-" (" 10: Mountain Village - Winter")
    { " 10:\x8Dﾔﾏｻﾞﾄ -ﾌﾕ-", Select_LoadGame, 0x9A00 },
    // " 10 - 0: Mountain Village -Spring-" (" 10 - 0: Mountain Village - Spring")
    { " 10-0:\x8Dﾔﾏｻﾞﾄ -ﾊﾙ-", Select_LoadGame, 0xAE00 },
    // " 10 - 1: Mountain Village Blacksmith" (" 10 - 1: Mountain Smithy")
    { " 10-1:\x8Dﾔﾏｻﾞﾄ ﾉ ｶｼﾞﾔ", Select_LoadGame, 0x5200 },
    // " 11: Goron Village -Winter-" (" 11: Goron Village - Winter")
    { " 11:\x8Cｺﾞﾛﾝ\x8D ﾉ ｻﾄ -ﾌﾕ-", Select_LoadGame, 0x9400 },
    // " 11-0: Goron Village -Spring-" (" 11-0: Goron Village - Spring")
    { " 11-0:\x8Cｺﾞﾛﾝ\x8D ﾉ ｻﾄ -ﾊﾙ-", Select_LoadGame, 0x8A00 },
    // " 11-1: Goron Shrine" (" 11-1: Goron Shrine")
    { " 11-1:\x8Cｺﾞﾛﾝ\x8D ﾉ ﾎｺﾗ", Select_LoadGame, 0x5E00 },
    // " 11-2: Lone Peak Shrine" (" 11-2: Lone Peak Shrine")
    { " 11-2:\x8Dﾊﾅﾚﾔﾏ ﾉ ﾎｺﾗ", Select_LoadGame, 0x1500 },
    // " 11-3: Goron Shop" (" 11-3: Goron Shop")
    { " 11-3:\x8Cｺﾞﾛﾝ \x8Dﾉ ﾐｾ", Select_LoadGame, 0x7400 },
    // " 12: Snowhead" (" 12: Snowhead")
    { " 12:\x8Cｽﾉｰﾍｯﾄﾞ", Select_LoadGame, 0xB200 },
    // " 13: Blizzard Path" (" 13: Path to Goron Village - Part 1")
    { " 13:\x8Dﾌﾌﾞｷ ﾉ ﾐﾁ", Select_LoadGame, 0x3200 },
    // " 14: Snowball Path" (" 14: Path to Goron Village - Part 2")
    { " 14:\x8Dﾕｷﾀﾞﾏ ﾉ ﾐﾁ", Select_LoadGame, 0xB000 },
    // " 15: Goron Racetrack" (" 15: Goron Racetrack")
    { " 15:\x8Cｺﾞﾛﾝﾚｰｽ \x8Dｼﾞｮｳ", Select_LoadGame, 0xD000 },
    // " 16: Goron Grave" (" 16: Darmani's Grave")
    { " 16:\x8Cｺﾞﾛﾝ \x8Dﾉ ﾊｶ", Select_LoadGame, 0x9600 },
    // " 17: Snow Field Battle -Winter-" (" 17: Path to Goron Village - Winter")
    { " 17:\x8Dｾﾂｹﾞﾝ \x8Cﾊﾞﾄﾙ \x8D-ﾌﾕ-", Select_LoadGame, 0xB400 },
    // " 17-0: Snow Field Battle -Spring-" (" 17-0: Path to Goron Village - Spring")
    { " 17-0:\x8Dｾﾂｹﾞﾝ \x8Cﾊﾞﾄﾙ \x8D-ﾊﾙ-", Select_LoadGame, 0xB600 },
    // " 20: Swampland" (" 20: Southern Swamp")
    { " 20:\x8Dﾇﾏﾁ", Select_LoadGame, 0x8400 },
    // " 20-0: Swampland - Afterwards" (" 20-0: Southern Swamp - After Odolwa")
    { " 20-0:\x8Dﾇﾏﾁ ｿﾉｺﾞ", Select_LoadGame, 0xC00 },
    // " 20-1: Swamp Tourist Information" (" 20-1: Tourist Information")
    { " 20-1:\x8Dﾇﾏ ﾉ ｶﾝｺｳｱﾝﾅｲ", Select_LoadGame, 0xA800 },
    // " 20-2: Magic Hags' Potion Shop" (" 20-2: Magic Hags' Potion Shop")
    { " 20-2:\x8Dﾏﾎｳｵﾊﾞﾊﾞ ﾉ ｸｽﾘﾔ", Select_LoadGame, 0x400 },
    // " 21: Wood Mountain" (" 21: Woodfall")
    { " 21:\x8Cｳｯﾄﾞﾏｳﾝﾃﾝ", Select_LoadGame, 0x8600 },
    // " 21-0: Deku Princess's Prison" (" 21-0: Deku Princess's Prison [Cutscene: Tatl Apologizes]")
    { " 21-0:\x8Cﾃﾞｸ\x8Dﾋﾒ ﾉ ﾛｳﾔ", Select_LoadGame, 0x3010 },
    // " 22: Deku Castle" (" 22: Deku Palace")
    { " 22:\x8Cﾃﾞｸﾅｯﾂ \x8Dﾉ ｼﾛ", Select_LoadGame, 0x5000 },
    // " 22-0: Boe Hole 0" (" 22-0: Deku Palace Grotto 0 - Deku Baba & Butterflies, Entrance 1")
    { " 22-0:\x8Cｸﾛｽｹ \x8Dﾉ ｱﾅ0", Select_LoadGame, 0x1460 },
    // " 22-1: Boe Hole 1" (" 22-1: Deku Palace Grotto 1 - Deku Baba & Butterflies, Entrance 2")
    { " 22-1:\x8Cｸﾛｽｹ \x8Dﾉ ｱﾅ1", Select_LoadGame, 0x14E0 },
    // " 22-2: Boe Hole 2" (" 22-2: Deku Palace Grotto 2 - Skullwalltula Wall, Lower Entrance")
    { " 22-2:\x8Cｸﾛｽｹ \x8Dﾉ ｱﾅ2", Select_LoadGame, 0x1480 },
    // " 22-3: Boe Hole 3" (" 22-3: Deku Palace Grotto 3 - Skullwalltula Wall, Upper Entrance")
    { " 22-3:\x8Cｸﾛｽｹ \x8Dﾉ ｱﾅ3", Select_LoadGame, 0x14F0 },
    // " 22-4: Boe Hole 4" (" 22-4: Deku Palace Grotto 4 - Bean Seller")
    { " 22-4:\x8Cｸﾛｽｹ \x8Dﾉ ｱﾅ4", Select_LoadGame, 0x14C0 },
    // " 24: Beast Path" (" 24: Road to Swamp")
    { " 24:\x8Dｹﾓﾉﾐﾁ", Select_LoadGame, 0x7A00 },
    // " 24-0: Forest Shooting Gallery" (" 24-0: Swamp Shooting Gallery")
    { " 24-0:\x8Dﾓﾘ ﾉ ｼｬﾃｷｼﾞｮｳ", Select_LoadGame, 0x4200 },
    // " 25: Deku King's Chamber" (" 25: Deku Palace Throne Room")
    { " 25:\x8Cﾃﾞｸ\x8Dｵｳ ﾉ ﾏ", Select_LoadGame, 0x7600 },
    // " 26: Woods of Mystery" (" 26: Woods of Mystery")
    { " 26:\x8Dﾌｼｷﾞ ﾉ ﾓﾘ", Select_LoadGame, 0xC200 },
    // " 30: Great Bay Coast" (" 30: Great Bay Coast - Entrance Area")
    { " 30:\x8Cｸﾞﾚｰﾄﾍﾞｲ\x8D ﾉ ｶｲｶﾞﾝ", Select_LoadGame, 0x6800 },
    // " 30-0: Ocean Laboratory" (" 30-0: Marine Research Lab")
    { " 30-0:\x8Dｶｲﾖｳ ｹﾝｷｭｳｼﾞｮ", Select_LoadGame, 0x5800 },
    // " 30-1: Fisherman's House" (" 30-1: Fisherman's Hut")
    { " 30-1:\x8Dﾘｮｳｼ ﾉ ｲｴ", Select_LoadGame, 0x7200 },
    // " 30-2: Pointed Rock" (" 30-2: Twin Pillars")
    { " 30-2:\x8Dﾄﾝｶﾞﾘ ｲﾜ", Select_LoadGame, 0x4400 },
    // " 31: Cape" (" 31: Great Bay Coast - River Area")
    { " 31:\x8Dﾐｻｷ", Select_LoadGame, 0x6A00 },
    // " 32: Outside of Pirates' Fortress" (" 32: Pirates' Fortress - Exterior")
    { " 32:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾏｴ", Select_LoadGame, 0x7000 },
    // " 32-0: Pirates' Fortress" (" 32-0: Pirates' Fortress - Courtyard")
    { " 32-0:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞ", Select_LoadGame, 0x2200 },
    // " 32-1: Pirates' Fortress - Telescope" (" 32-1: Pirates' Fortress - Secret Entrance (Looking Through
    // Telescope)")
    { " 32-1:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞ ﾎﾞｳｴﾝｷｮｳ", Select_LoadGame, 0x22A0 },
    // " 32-2: Pirates' Fortress - Interior 0" (" 32-2: Pirates' Fortress - Throne Room")
    { " 32-2:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ0", Select_LoadGame, 0x4000 },
    // " 32-3: Pirates' Fortress - Interior 1" (" 32-3: Pirates' Fortress - View of Throne Room, Wasp Nest")
    { " 32-3:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ1", Select_LoadGame, 0x4010 },
    // " 32-4: Pirates' Fortress - Interior 2" (" 32-4: Pirates' Fortress - Tempting Treasure Chest, Leading to 32-5")
    { " 32-4:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ2", Select_LoadGame, 0x4020 },
    // " 32-5: Pirates' Fortress - Interior 3" (" 32-5: Pirates' Fortress - Zora Egg Room, One Shell Blade")
    { " 32-5:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ3", Select_LoadGame, 0x4030 },
    // " 32-6: Pirates' Fortress - Interior 4" (" 32-6: Pirates' Fortress - Oil Drum Room, Leading to 32-7")
    { " 32-6:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ4", Select_LoadGame, 0x4040 },
    // " 32-7: Pirates' Fortress - Interior 5" (" 32-7: Pirates' Fortress - Zora Egg Room, One Shell Blade")
    { " 32-7:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ5", Select_LoadGame, 0x4050 },
    // " 32-8: Pirates' Fortress - Interior 6" (" 32-8: Pirates' Fortress - Fenced Indoor Walkway, Leading to 32-9")
    { " 32-8:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ6", Select_LoadGame, 0x4060 },
    // " 32-9: Pirates' Fortress - Interior 7" (" 32-9: Pirates' Fortress - Zora Egg Room, One Desbreko & Treasure
    // Chest")
    { " 32-9:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ7", Select_LoadGame, 0x4070 },
    // " 32-10: Pirates' Fortress - Interior 8" (" 32-10: Pirates' Fortress - End of Secret Entrance (Telescope
    // Room)")
    { " 32-10:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ8", Select_LoadGame, 0x4080 },
    // " 32-11: Pirates' Fortress - Interior 9" (" 32-11: Pirates' Fortress - Start of Secret Entrance")
    { " 32-11:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ9", Select_LoadGame, 0x4090 },
    // " 33: Zora Shrine" (" 33: Zora Hall")
    { " 33:\x8Cｿﾞｰﾗ \x8Dﾉ ﾎｺﾗ", Select_LoadGame, 0x6000 },
    // " 33-0: Zora Shop" (" 33-0: Zora Shop")
    { " 33-0:\x8Cｿﾞｰﾗ \x8Dﾉ ﾐｾ", Select_LoadGame, 0x9250 },
    // " 33-1: Zora Waiting Room" (" 33-1: Mikau & Tijo's Room")
    { " 33-1:\x8Cｿﾞｰﾗ \x8Dﾉ ﾋｶｴｼﾂ", Select_LoadGame, 0x9200 },
    // " 34: Great Bay" (" 34: Great Bay [Cutscene: Pirates Approach Temple]")
    { " 34:\x8Cｸﾞﾚｰﾄﾍﾞｲ", Select_LoadGame, 0xBE00 },
    // " 35: Mountain Stream Above Falls" (" 35: Waterfall Rapids")
    { " 35:\x8Dﾀｷｳｴ ﾉ ｹｲﾘｭｳ", Select_LoadGame, 0x8E00 },
    // " 40: Rock Building Shaft" (" 40: Stone Tower")
    { " 40:\x8Cﾛｯｸﾋﾞﾙ\x8D ﾉ ﾀﾃｱﾅ", Select_LoadGame, 0xAA00 },
    // " 40-0: Heaven & Earth Are Overturned" (" 40-0: Stone Tower [Cutscene: Tower is Flipped]")
    { " 40-0:\x8Dﾃﾝﾁ ｷﾞｬｸﾃﾝ", Select_LoadGame, 0xAC00 },
    // " 41: Road to Ikana" (" 41: Road to Ikana")
    { " 41:\x8Cｲｶｰﾅ \x8Dﾍﾉ ﾐﾁ", Select_LoadGame, 0xA000 },
    // " 42: Ancient Castle of Ikana" (" 42: Ancient Castle of Ikana")
    { " 42:\x8Cｲｶｰﾅ\x8D ｺｼﾞｮｳ", Select_LoadGame, 0x3400 },
    // " 42-0: Ancient Castle of Ikana - Interior" (" 42-0: Ancient Castle of Ikana - Interior")
    { " 42-0:\x8Cｲｶｰﾅ\x8D ﾉ ｺｼﾞｮｳ ﾅｲﾌﾞ", Select_LoadGame, 0x3430 },
    // " 42-B: Ancient Castle of Ikana - Boss Room" (" 42-B: Ikana King's Throne")
    { " 42-B:\x8Cｲｶｰﾅ\x8D ﾉ ｺｼﾞｮｳ \x8Cﾎﾞｽ\x8Dﾍﾞﾔ", Select_LoadGame, 0xA600 },
    // " 43: Ikana Canyon" (" 43: Ikana Canyon")
    { " 43:\x8Cｲｶｰﾅ \x8Dｹｲｺｸ", Select_LoadGame, 0x2000 },
    // " 43-0: Ikana Canyon Cave" (" 43-0: Sharp's Cave")
    { " 43-0:\x8Cｲｶｰﾅ \x8Dｹｲｺｸ ﾄﾞｳｸﾂ", Select_LoadGame, 0x20E0 },
    // " 43-1: Secom's House" (" 43-1: Sakon's Hideout")
    { " 43-1:\x8Cｾｺﾑ \x8Dﾉ ｲｴ", Select_LoadGame, 0x9800 },
    // " 43-2: Music Box House" (" 43-2: Music Box House")
    { " 43-2:\x8Cｵﾙｺﾞｰﾙ ﾊｳｽ", Select_LoadGame, 0xA400 },
    // " 50: Clock Town -East-" (" 50: East Clock Town")
    { " 50:\x8Cｸﾛｯｸﾀｳﾝ \x8D-ﾋｶﾞｼ-", Select_LoadGame, 0xD200 },
    // " 50-0: Town Target Range" (" 50-0: Shooting Gallery")
    { " 50-0:\x8Dﾏﾁ ﾉ ｼｬﾃｷｼﾞｮｳ", Select_LoadGame, 0x3A00 },
    // " 50-1: Honey and Darling's Shop" (" 50-1: Honey & Darling's Shop")
    { " 50-1:\x8Cﾊﾆｰ ｱﾝﾄﾞ ﾀﾞｰﾘﾝ \x8Dﾉ ﾐｾ", Select_LoadGame, 0x800 },
    // " 50-2: Treasure Chest Shop" (" 50-2: Treasure Chest Shop")
    { " 50-2:\x8Dﾀｶﾗﾊﾞｺﾔ", Select_LoadGame, 0x2800 },
    // " 50-3: Pots 'n' Pans Inn" (" 50-3: Stockpot Inn")
    { " 50-3:\x8Cﾅﾍﾞ\x8Dｶﾏ ﾃｲ", Select_LoadGame, 0xBC00 },
    // " 50-4: Mayor's House" (" 50-4: The Mayor's Residence")
    { " 50-4:\x8Dﾁｮｳﾁｮｳ ﾉ ｲｴ", Select_LoadGame, 0 },
    // " 50-5: Milk Bar" (" 50-5: Milk Bar")
    { " 50-5:\x8Cﾐﾙｸﾊﾞｰ", Select_LoadGame, 0x2400 },
    // " 51: Clock Town -West-" (" 51: West Clock Town")
    { " 51:\x8Cｸﾛｯｸﾀｳﾝ \x8D-ﾆｼ-", Select_LoadGame, 0xD400 },
    // " 51-0: Bomb Shop" (" 51-0: Bomb Shop")
    { " 51-0:\x8Dﾊﾞｸﾀﾞﾝ ﾔ", Select_LoadGame, 0xCA00 },
    // " 51-1: Maniac Mart" (" 51-1: Curiosity Shop")
    { " 51-1:\x8Cﾏﾆ\x8Dﾔ", Select_LoadGame, 0xE00 },
    // " 51-2: General Store" (" 51-2: Trading Post")
    { " 51-2:\x8Dｻﾞｯｶ ﾔ", Select_LoadGame, 0x6200 },
    // " 51-3: Sword Dojo" (" 51-3: Swordsman's School")
    { " 51-3:\x8Dｹﾝﾄﾞｳｼﾞｮｳ", Select_LoadGame, 0xA200 },
    // " 51-4: Post House" (" 51-4: Post Office")
    { " 51-4:\x8Dﾎﾟｽﾄﾊｳｽ", Select_LoadGame, 0x5600 },
    // " 51-5: Lottery Shop" (" 51-5: Lottery Shop")
    { " 51-5:\x8Dﾀｶﾗｸｼﾞﾔ", Select_LoadGame, 0x6C00 },
    // " 52: Clock Town -North-" (" 52: North Clock Town")
    { " 52:\x8Cｸﾛｯｸﾀｳﾝ \x8D-ｷﾀ-", Select_LoadGame, 0xD600 },
    // " 53: Clocktown -South-" (" 53: South Clock Town")
    { " 53:\x8Cｸﾛｯｸﾀｳﾝ \x8D-ﾐﾅﾐ-", Select_LoadGame, 0xD800 },
    // " 53-0: Clock Tower Interior" (" 53-0: Clock Tower Interior")
    { " 53-0:\x8Dﾄｹｲﾄｳﾅｲﾌﾞ", Select_LoadGame, 0xC000 },
    // " 54: Clock Tower Rooftop" (" 54: Clock Tower Rooftop")
    { " 54:\x8Dﾄｹｲﾄｳ ｵｸｼﾞｮｳ", Select_LoadGame, 0x2C00 },
    // " 55: Laundry Area" (" 55: Laundry Pool")
    { " 55:\x8Dｾﾝﾀｸｼﾞｮｳ", Select_LoadGame, 0xDA00 },
    // " 55-0: Maniac Mart - Rear Entrance" (" 55-0: Curiosity Shop - Back Room")
    { " 55-0:\x8Cﾏﾆ\x8Dﾔ ﾉ ｳﾗｸﾞﾁ", Select_LoadGame, 0xE10 },
    // " 55-1: Maniac Mart - Peephole" (" 55-1: Curiosity Shop Back Room - Peephole")
    { " 55-1:\x8Cﾏﾆ\x8Dﾔ ﾉ ﾉｿﾞｷｱﾅ", Select_LoadGame, 0xE20 },
    // "100: Wood Mountain Temple" ("100: Woodfall Temple")
    { "100:\x8Cｳｯﾄﾞﾏｳﾝﾃﾝ \x8Dﾉ ｼﾝﾃﾞﾝ", Select_LoadGame, 0x3000 },
    // "100-B: Wood Mountain Temple - Boss" ("100-B: Odolwa's Lair")
    { "100-B:\x8Cｳｯﾄﾞﾏｳﾝﾃﾝ \x8Dﾉ ｼﾝﾃﾞﾝ\x8C-ﾎﾞｽ-", Select_LoadGame, 0x3800 },
    // "101: Snowhead Temple" ("101: Snowhead Temple")
    { "101:\x8Cｽﾉｰﾍｯﾄﾞ \x8Dﾉ ｼﾝﾃﾞﾝ", Select_LoadGame, 0x3C00 },
    // "101-B: Snowhead Temple - Boss" ("101-B: Goht's Lair")
    { "101-B:\x8Cｽﾉｰﾍｯﾄﾞ \x8Dﾉ ｼﾝﾃﾞﾝ\x8C-ﾎﾞｽ-", Select_LoadGame, 0x8200 },
    // "102: Great Bay Temple" ("102: Great Bay Temple")
    { "102:\x8Cｸﾞﾚｰﾄﾍﾞｲ \x8Dﾉ ｼﾝﾃﾞﾝ", Select_LoadGame, 0x8C00 },
    // "102-B: Great Bay Temple - Boss" ("102-B: Gyorg's Lair")
    { "102-B:\x8Cｸﾞﾚｰﾄﾍﾞｲ \x8Dﾉ ｼﾝﾃﾞﾝ\x8C-ﾎﾞｽ-", Select_LoadGame, 0xB800 },
    // "103: Rock Building Temple -Top Side-" ("103: Stone Tower Temple")
    { "103:\x8Cﾛｯｸﾋﾞﾙ \x8Dﾉ ｼﾝﾃﾞﾝ-ｵﾓﾃｰ", Select_LoadGame, 0x2600 },
    // "103-0: Rock Building Temple -Underside-" ("103-0: Stone Tower Temple - Flipped")
    { "103-0:\x8Cﾛｯｸﾋﾞﾙ \x8Dﾉ ｼﾝﾃﾞﾝ-ｳﾗｰ", Select_LoadGame, 0x2A00 },
    // "103-B: Rock Building Temple - Boss" ("103-B: Twinmold's Lair")
    { "103-B:\x8Cﾛｯｸﾋﾞﾙ \x8Dﾉ ｼﾝﾃﾞﾝ\x8C-ﾎﾞｽ-", Select_LoadGame, 0x6600 },
    // "104: Steppe" ("104: On the Moon")
    { "104:\x8Cｿｳｹﾞﾝ", Select_LoadGame, 0xC800 },
    // "104-0: Last Deku Dungeon" ("104-0: Deku Trial")
    { "104-0:\x8Cﾗｽﾄ ﾃﾞｸ ﾀﾞﾝｼﾞｮﾝ", Select_LoadGame, 0x4E00 },
    // "104-1: Last Goron Dungeon" ("104-1: Goron Trial")
    { "104-1:\x8Cﾗｽﾄ ｺﾞﾛﾝ ﾀﾞﾝｼﾞｮﾝ", Select_LoadGame, 0x7800 },
    // "104-2: Last Zora Dungeon" ("104-2: Zora Trial")
    { "104-2:\x8Cﾗｽﾄ ｿﾞｰﾗ ﾀﾞﾝｼﾞｮﾝ", Select_LoadGame, 0x8800 },
    // "104-3: Last Link Dungeon" ("104-3: Link Trial")
    { "104-3:\x8Cﾗｽﾄ ﾘﾝｸ ﾀﾞﾝｼﾞｮﾝ", Select_LoadGame, 0xC600 },
    // "104-B: Last Dungeon -Boss-" ("104-B: Majora's Lair")
    { "104-B:\x8Cﾗｽﾄﾀﾞﾝｼﾞｮﾝ -ﾎﾞｽ-", Select_LoadGame, 0x200 },
    // "119: Deku Shrine" ("119: Deku Shrine")
    { "119:\x8Cﾃﾞｸﾅｯﾂ \x8Dﾉ ﾎｺﾗ", Select_LoadGame, 0x9E00 },
    // "121: Secret Shrine" ("121: Secret Shrine")
    { "121:\x8Dﾋﾐﾂ ﾉ ﾎｺﾗ", Select_LoadGame, 0xBA00 },
    // "122: Opening Dungeon" ("122: Pond Area [Cutscene: Falling of the Cliff]")
    { "122:\x8Cｵｰﾌﾟﾆﾝｸﾞ ﾀﾞﾝｼﾞｮﾝ", Select_LoadGame, 0x2E00 },
    // "123: Giants' Chamber" ("123: Giants' Chamber")
    { "123:\x8Dｷｮｼﾞﾝ ﾉ ﾏ", Select_LoadGame, 0xCC00 },
    // "126: Deku Minigame" ("126: Deku Rupee Minigame")
    { "126:\x8Cﾃﾞｸﾅｯﾂ ﾐﾆｹﾞｰﾑ", Select_LoadGame, 0x3600 },
    // "127-0: Fairy Fountain 0" ("127-0: Fairy Fountain - Clock Town")
    { "127-0:\x8Dﾖｳｾｲ ﾉ ｲｽﾞﾐ 0", Select_LoadGame, 0x4600 },
    // "127-1: Fairy Fountain 1" ("127-1: Fairy Fountain - Woodfall")
    { "127-1:\x8Dﾖｳｾｲ ﾉ ｲｽﾞﾐ 1", Select_LoadGame, 0x4610 },
    // "127-2: Fairy Fountain 2" ("127-2: Fairy Fountain - Snowhead")
    { "127-2:\x8Dﾖｳｾｲ ﾉ ｲｽﾞﾐ 2", Select_LoadGame, 0x4620 },
    // "127-3: Fairy Fountain 3" ("127-3: Fairy Fountain - Great Bay Coast")
    { "127-3:\x8Dﾖｳｾｲ ﾉ ｲｽﾞﾐ 3", Select_LoadGame, 0x4630 },
    // "127-4: Fairy Fountain 4" ("127-4: Fairy Fountain - Ikana Canyon")
    { "127-4:\x8Dﾖｳｾｲ ﾉ ｲｽﾞﾐ 4", Select_LoadGame, 0x4640 },
    // "128: Swamp Spider Manor" ("128: Swamp Spider House")
    { "128:\x8Dﾇﾏ ﾉ ｸﾓﾔｶﾀ", Select_LoadGame, 0x4800 },
    // "129: Ocean Spider Manor" ("129: Oceanside Spider House")
    { "129:\x8Dｳﾐ ﾉ ｸﾓﾔｶﾀ", Select_LoadGame, 0x4A00 },
    // "130: Beneath the Graves - Dampe" ("130: Beneath the Graveyard")
    { "130:\x8Dﾊｶ ﾉ ｼﾀ-\x8Cﾀﾞﾝﾍﾟｲ-", Select_LoadGame, 0x5A00 },
    // "131: Beneath the Well" ("131: Beneath the Well")
    { "131:\x8Dｲﾄﾞ ﾉ ｼﾀ", Select_LoadGame, 0x9000 },
    // "132: Ghost Hut" (" 132: Ghost Hut")
    { "132:\x8Dﾕｳﾚｲｺﾞﾔ", Select_LoadGame, 0x9C00 },
    // "133-0: Beneath the Graves 0" ("133-0: Beneath the Graveyard - Part 1")
    { "133-0:\x8Dﾊｶ ﾉ ｼﾀ0", Select_LoadGame, 0xA00 },
    // "133-1: Beneath the Graves 1" ("133-1: Beneath the Graveyard - Part 2")
    { "133-1:\x8Dﾊｶ ﾉ ｼﾀ1", Select_LoadGame, 0xA10 },
    // "134-0: Secret Grotto 0" ("134-0: Secret Grotto - Four Gossip Stones")
    { "134-0:\x8Dｶｸｼｱﾅ 0", Select_LoadGame, 0x1400 },
    // "134-1: Secret Grotto 1" ("134-1: Secret Grotto - Four Gossip Stones, Skulltula")
    { "134-1:\x8Dｶｸｼｱﾅ 1", Select_LoadGame, 0x1410 },
    // "134-2: Secret Grotto 2" ("134-2: Secret Grotto - Four Gossip Stones, Water Puddles")
    { "134-2:\x8Dｶｸｼｱﾅ 2", Select_LoadGame, 0x1420 },
    // "134-3: Secret Grotto 3" ("134-3: Secret Grotto - Four Gossip Stones, Water Puddle With Bugs")
    { "134-3:\x8Dｶｸｼｱﾅ 3", Select_LoadGame, 0x1430 },
    // "134-4: Secret Grotto 4" ("134-4: Secret Grotto - Chest with Blue Rupee, Deku Babas")
    { "134-4:\x8Dｶｸｼｱﾅ 4", Select_LoadGame, 0x1440 },
    // "134-5: Secret Grotto 5" ("134-5: Secret Grotto - Hot Spring, Deku Babas, Large Stones")
    { "134-5:\x8Dｶｸｼｱﾅ5", Select_LoadGame, 0x1450 },
    // "134-7: Secret Grotto 7" ("134-7: Secret Grotto - Two Dondogos")
    { "134-7:\x8Dｶｸｼｱﾅ 7", Select_LoadGame, 0x1470 },
    // "134-9: Secret Grotto 9" ("134-9: Secret Grotto - Tall Grass With Box, Pot, Bugs")
    { "134-9:\x8Dｶｸｼｱﾅ 9", Select_LoadGame, 0x1490 },
    // "134-10: Secret Grotto 10" ("134-10: Secret Grotto - Two Cows Surrounded by Grass")
    { "134-10:\x8Dｶｸｼｱﾅ10", Select_LoadGame, 0x14A0 },
    // "134-11: Secret Grotto 11" ("134-11: Secret Grotto - Watery Hole Filled with Underwater Babas, Fish")
    { "134-11:\x8Dｶｸｼｱﾅ11", Select_LoadGame, 0x14B0 },
    // "134-13: Secret Grotto 13" ("134-13: Secret Grotto - Peahat in Center")
    { "134-13:\x8Dｶｸｼｱﾅ13", Select_LoadGame, 0x14D0 },
    // "X 1: SPOT00" ("X 1: Opening [Cutscene: Opening Cutscene]")
    { "X 1:SPOT00", Select_LoadGame, 0x1C00 },
    // "Title" ("Title Screen")
    { "title", (void*)Select_LoadTitle, 0x0000 },
};

void Select_UpdateMenu(SelectContext* this) {
    s32 playerForm;
    Input* controller1 = CONTROLLER1(this);
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

        if (this->currentScene == ((this->topDisplayedScene + 19 + this->count) % this->count)) {
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

void Select_PrintMenu(SelectContext* this, GfxPrint* printer) {
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

// clang-format off
static const char* sLoadingMessages[] = {
    // "Please wait a minute",
    "\x8Dｼﾊﾞﾗｸｵﾏﾁｸﾀﾞｻｲ",
    // "Hold on a sec",
    "\x8Dﾁｮｯﾄ ﾏｯﾃﾈ",
    // "Wait a moment",
    "\x8Cｳｪｲﾄ ｱ ﾓｰﾒﾝﾄ",
    // "Loading",
    "\x8Cﾛｰﾄﾞ\x8Dﾁｭｳ",
    // "Now working",
    "\x8Dﾅｳ ﾜｰｷﾝｸﾞ",
    // "Now creating",
    "\x8Dｲﾏ ﾂｸｯﾃﾏｽ",
    // "It's not broken",
    "\x8Dｺｼｮｳｼﾞｬﾅｲﾖ",
    // "Coffee Break",
    "\x8Cｺｰﾋｰ ﾌﾞﾚｲｸ",
    // "Please set B side",
    "\x8C" "Bﾒﾝｦｾｯﾄｼﾃｸﾀﾞｻｲ",
    // "Be patient, now",
    "\x8Dｼﾞｯﾄ\x8Cｶﾞﾏﾝ\x8Dﾉ\x8Cｺ\x8Dﾃﾞｱｯﾀ",
    // "Please wait just a minute",
    "\x8Dｲﾏｼﾊﾞﾗｸｵﾏﾁｸﾀﾞｻｲ",
    // "Don't worry, don't worry. Take a break, take a break",
    "\x8Dｱﾜﾃﾅｲｱﾜﾃﾅｲ｡ﾋﾄﾔｽﾐﾋﾄﾔｽﾐ｡",
};
// clang-format on

void Select_PrintLoadingMessage(SelectContext* this, GfxPrint* printer) {
    s32 index;

    GfxPrint_SetPos(printer, 10, 15);
    GfxPrint_SetColor(printer, 255, 255, 255, 255);

    index = Rand_ZeroOne() * ARRAY_COUNT(sLoadingMessages);
    GfxPrint_Printf(printer, "%s", sLoadingMessages[index]);
}

// clang-format off
// Second column is unused
static const char* sFormLabel[][2] = {
    // "17 (Adult)" // 17 (Daitetsujin)
    {"\x8D""17(ｵﾄﾅ)",    "\x8D""17(ﾀﾞｲﾃﾂｼﾞﾝ)"},
    // "30 (Goron)" // 30 (Ice Cream -1)
    {"\x8C""30(ｺﾞﾛﾝ)",   "\x8C""30(ｱｲｽｸﾘｰﾑ-1)"},
    // "78 (Zora)" // 78 (Carmen +1)
    {"\x8C""78(ｿﾞｰﾗ)",   "\x8C""78(ｶﾙﾒﾝ+1)"},
    // "12 (Deku)" // 12 (Majestic)
    {"\x8C""12(ﾃﾞｸﾅｯﾂ)", "\x8C""12(ﾏｼﾞｪｽﾃｨｯｸ)"},
    // "5 (Child)" // 5 (NTT Kodomo)
    {"\x8D""5(ｺﾄﾞﾓ)",    "\x8C""5(NTTｺﾄﾞﾓ)"},
};
// clang-format on

void Select_PrintAgeSetting(SelectContext* this, GfxPrint* printer, s32 playerForm) {
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
        GfxPrint_Printf(printer, "Age:" "???" "(%d)", playerForm);
        // clang-format on
    }
}

void Select_PrintCutsceneSetting(SelectContext* this, GfxPrint* printer, u16 csIndex) {
    const char* stage;
    const char* day;

    GfxPrint_SetPos(printer, 4, 25);
    GfxPrint_SetColor(printer, 255, 255, 55, 255);

    // "-jara" used in these strings is a Kokiri speech quirk word
    switch (csIndex) {
        case 0:
            // clang-format off
            // "Afternoon-jara"
            gSaveContext.save.time = CLOCK_TIME(12, 0); stage = "\x8Dｵﾋﾙ\x8Cｼﾞｬﾗ";
            // clang-format on
            break;

        case 0x8000:
            // clang-format off
            // "Morning-jara"
            gSaveContext.save.time = CLOCK_TIME(6, 0) + 1; stage = "\x8Dｱｻ \x8Cｼﾞｬﾗ";
            // clang-format on
            break;

        case 0x8800:
            gSaveContext.save.time = CLOCK_TIME(18, 1);
            // "Night-jara"
            stage = "\x8Dﾖﾙ \x8Cｼﾞｬﾗ";
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
    gSaveContext.environmentTime = gSaveContext.save.time;
    GfxPrint_Printf(printer, "Stage:\x8C%s", stage);

    GfxPrint_SetPos(printer, 23, 25);
    GfxPrint_SetColor(printer, 255, 255, 55, 255);

    switch (gSaveContext.save.day) {
        case 1:
            // "The First Day"
            day = "\x8Dｻｲｼｮﾉﾋ";
            break;
        case 2:
            // "The Next Day"
            day = "\x8Dﾂｷﾞﾉﾋ";
            break;
        case 3:
            // "The Final Day"
            day = "\x8Dｻｲｺﾞﾉﾋ";
            break;
        case 4:
            // "Clear Day"
            day = "\x8Dｸﾘｱｰﾉﾋ";
            break;
        default:
            gSaveContext.save.day = 1;
            // "The First Day"
            day = "\x8Dｻｲｼｮﾉﾋ";
            break;
    }

    GfxPrint_Printf(printer, "Day:\x8D%s", day);
}

void Select_DrawMenu(SelectContext* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;
    GfxPrint* printer;

    OPEN_DISPS(gfxCtx);

    func_8012C4C0(gfxCtx);

    printer = alloca(sizeof(GfxPrint));
    GfxPrint_Init(printer);
    GfxPrint_Open(printer, POLY_OPA_DISP);

    Select_PrintMenu(this, printer);
    Select_PrintAgeSetting(this, printer, ((void)0, gSaveContext.save.playerForm));
    Select_PrintCutsceneSetting(this, printer, ((void)0, gSaveContext.save.cutscene));

    POLY_OPA_DISP = GfxPrint_Close(printer);
    GfxPrint_Destroy(printer);

    CLOSE_DISPS(gfxCtx);
}

void Select_DrawLoadingScreen(SelectContext* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;
    GfxPrint printer;

    OPEN_DISPS(gfxCtx);

    func_8012C4C0(gfxCtx);

    GfxPrint_Init(&printer);
    GfxPrint_Open(&printer, POLY_OPA_DISP);

    Select_PrintLoadingMessage(this, &printer);

    POLY_OPA_DISP = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);

    CLOSE_DISPS(gfxCtx);
}

void Select_Draw(SelectContext* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;

    func_8012CF0C(gfxCtx, true, true, 0, 0, 0);

    SET_FULLSCREEN_VIEWPORT(&this->view);
    View_RenderView(&this->view, 0xF);
    if (!this->state.running) {
        Select_DrawLoadingScreen(this);
    } else {
        Select_DrawMenu(this);
    }
}

void Select_Main(GameState* thisx) {
    SelectContext* this = (SelectContext*)thisx;

    Select_UpdateMenu(this);
    Select_Draw(this);
}

void Select_Destroy(GameState* thisx) {
    ShrinkWindow_Destroy();
}

void Select_Init(GameState* thisx) {
    SelectContext* this = (SelectContext*)thisx;

    this->state.main = Select_Main;
    this->state.destroy = Select_Destroy;

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
