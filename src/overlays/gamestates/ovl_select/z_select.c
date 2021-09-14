/*
 * File: z_select.c
 * Overlay: ovl_select
 * Description: Debug map select
 */

#include "z_select.h"
#include "alloca.h"
#include "overlays/gamestates/ovl_title/z_title.h"

void Select_LoadTitle(SelectContext* this) {
    {
        GameState* state = &this->state;
        state->running = false;
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
    gSaveContext.entranceIndex = entranceIndex;

    if (opt != 0) {
        gSaveContext.entranceIndex = Entrance_CreateIndex((s32)gSaveContext.entranceIndex >> 9, opt, gSaveContext.entranceIndex & 0xF);
    }
    if (gSaveContext.entranceIndex == 0xC000) {
        gSaveContext.day = 0;
        gSaveContext.time = CLOCK_TIME(6, 0) - 1;
    }

    gSaveContext.respawn[0].entranceIndex = 0xFFFF;
    gSaveContext.seqIndex = 0xFF;
    gSaveContext.nightSeqIndex = 0xFF;
    gSaveContext.showTitleCard = true;
    gSaveContext.respawnFlag = 0;
    gSaveContext.respawn[4].entranceIndex = 0xFF;
    gSaveContext.respawn[5].entranceIndex = 0xFF;
    gSaveContext.respawn[6].entranceIndex = 0xFF;
    gSaveContext.respawn[7].entranceIndex = 0xFF;
    D_801BDBB0 = 0;

    do {
        GameState* state = &this->state;
        state->running = false;
    } while(0);
    SET_NEXT_GAMESTATE(&this->state, Play_Init, GlobalContext);
}

SceneSelectEntry D_80801C80[] = {
    { "  0:OP\x8Cﾃﾞﾓ\x8Dﾖｳ ｼﾝﾘﾝ", Select_LoadGame, 0x1C00 },
    { "  0-0:\x8Dﾏﾖｲ ﾉ ﾓﾘ", Select_LoadGame, 0xC400 },
    { "  1:\x8Cﾀｳﾝ \x8Dｺｳｶﾞｲ", Select_LoadGame, 0x5400 },
    { "  1-0:\x8Dﾃﾝﾓﾝｶﾝｿｸｼﾞｮ", Select_LoadGame, 0x4C00 },
    { "  1-1:\x8Dﾃﾝﾓﾝｶﾝｿｸｼﾞｮ ﾃﾞ ﾎﾞｳｴﾝｷｮｳ", Select_LoadGame, 0x54A0 },
    { "  1-2:\x8Cｲｶｰﾅ \x8Dﾉ ﾊｶﾊﾞ", Select_LoadGame, 0x8000 },
    { "  2:\x8Cﾛﾏﾆｰ \x8Dﾎﾞｸｼﾞｮｳ", Select_LoadGame, 0x6400 },
    { "  3:\x8Cﾐﾙｸﾛｰﾄﾞ", Select_LoadGame, 0x3E00 },
    { "  4:\x8Dｵﾓﾔ", Select_LoadGame, 0x610 },
    { "  5:\x8Dｳｼｺﾞﾔ", Select_LoadGame, 0x600 },
    { "  6:\x8Cｺｯｺ \x8Dｺﾞﾔ", Select_LoadGame, 0x7E00 },
    { "  7:\x8Cﾄﾞｯｸﾞﾚｰｽ\x8Dｼﾞｮｳ", Select_LoadGame, 0x7C00 },
    { "  8:\x8Cｺﾞｰﾏﾝ ﾄﾗｯｸ", Select_LoadGame, 0xCE00 },
    { " 10:\x8Dﾔﾏｻﾞﾄ -ﾌﾕ-", Select_LoadGame, 0x9A00 },
    { " 10-0:\x8Dﾔﾏｻﾞﾄ -ﾊﾙ-", Select_LoadGame, 0xAE00 },
    { " 10-1:\x8Dﾔﾏｻﾞﾄ ﾉ ｶｼﾞﾔ", Select_LoadGame, 0x5200 },
    { " 11:\x8Cｺﾞﾛﾝ\x8D ﾉ ｻﾄ -ﾌﾕ-", Select_LoadGame, 0x9400 },
    { " 11-0:\x8Cｺﾞﾛﾝ\x8D ﾉ ｻﾄ -ﾊﾙ-", Select_LoadGame, 0x8A00 },
    { " 11-1:\x8Cｺﾞﾛﾝ\x8D ﾉ ﾎｺﾗ", Select_LoadGame, 0x5E00 },
    { " 11-2:\x8Dﾊﾅﾚﾔﾏ ﾉ ﾎｺﾗ", Select_LoadGame, 0x1500 },
    { " 11-3:\x8Cｺﾞﾛﾝ \x8Dﾉ ﾐｾ", Select_LoadGame, 0x7400 },
    { " 12:\x8Cｽﾉｰﾍｯﾄﾞ", Select_LoadGame, 0xB200 },
    { " 13:\x8Dﾌﾌﾞｷ ﾉ ﾐﾁ", Select_LoadGame, 0x3200 },
    { " 14:\x8Dﾕｷﾀﾞﾏ ﾉ ﾐﾁ", Select_LoadGame, 0xB000 },
    { " 15:\x8Cｺﾞﾛﾝﾚｰｽ \x8Dｼﾞｮｳ", Select_LoadGame, 0xD000 },
    { " 16:\x8Cｺﾞﾛﾝ \x8Dﾉ ﾊｶ", Select_LoadGame, 0x9600 },
    { " 17:\x8Dｾﾂｹﾞﾝ \x8Cﾊﾞﾄﾙ \x8D-ﾌﾕ-", Select_LoadGame, 0xB400 },
    { " 17-0:\x8Dｾﾂｹﾞﾝ \x8Cﾊﾞﾄﾙ \x8D-ﾊﾙ-", Select_LoadGame, 0xB600 },
    { " 20:\x8Dﾇﾏﾁ", Select_LoadGame, 0x8400 },
    { " 20-0:\x8Dﾇﾏﾁ ｿﾉｺﾞ", Select_LoadGame, 0xC00 },
    { " 20-1:\x8Dﾇﾏ ﾉ ｶﾝｺｳｱﾝﾅｲ", Select_LoadGame, 0xA800 },
    { " 20-2:\x8Dﾏﾎｳｵﾊﾞﾊﾞ ﾉ ｸｽﾘﾔ", Select_LoadGame, 0x400 },
    { " 21:\x8Cｳｯﾄﾞﾏｳﾝﾃﾝ", Select_LoadGame, 0x8600 },
    { " 21-0:\x8Cﾃﾞｸ\x8Dﾋﾒ ﾉ ﾛｳﾔ", Select_LoadGame, 0x3010 },
    { " 22:\x8Cﾃﾞｸﾅｯﾂ \x8Dﾉ ｼﾛ", Select_LoadGame, 0x5000 },
    { " 22-0:\x8Cｸﾛｽｹ \x8Dﾉ ｱﾅ0", Select_LoadGame, 0x1460 },
    { " 22-1:\x8Cｸﾛｽｹ \x8Dﾉ ｱﾅ1", Select_LoadGame, 0x14E0 },
    { " 22-2:\x8Cｸﾛｽｹ \x8Dﾉ ｱﾅ2", Select_LoadGame, 0x1480 },
    { " 22-3:\x8Cｸﾛｽｹ \x8Dﾉ ｱﾅ3", Select_LoadGame, 0x14F0 },
    { " 22-4:\x8Cｸﾛｽｹ \x8Dﾉ ｱﾅ4", Select_LoadGame, 0x14C0 },
    { " 24:\x8Dｹﾓﾉﾐﾁ", Select_LoadGame, 0x7A00 },
    { " 24-0:\x8Dﾓﾘ ﾉ ｼｬﾃｷｼﾞｮｳ", Select_LoadGame, 0x4200 },
    { " 25:\x8Cﾃﾞｸ\x8Dｵｳ ﾉ ﾏ", Select_LoadGame, 0x7600 },
    { " 26:\x8Dﾌｼｷﾞ ﾉ ﾓﾘ", Select_LoadGame, 0xC200 },
    { " 30:\x8Cｸﾞﾚｰﾄﾍﾞｲ\x8D ﾉ ｶｲｶﾞﾝ", Select_LoadGame, 0x6800 },
    { " 30-0:\x8Dｶｲﾖｳ ｹﾝｷｭｳｼﾞｮ", Select_LoadGame, 0x5800 },
    { " 30-1:\x8Dﾘｮｳｼ ﾉ ｲｴ", Select_LoadGame, 0x7200 },
    { " 30-2:\x8Dﾄﾝｶﾞﾘ ｲﾜ", Select_LoadGame, 0x4400 },
    { " 31:\x8Dﾐｻｷ", Select_LoadGame, 0x6A00 },
    { " 32:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾏｴ", Select_LoadGame, 0x7000 },
    { " 32-0:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞ", Select_LoadGame, 0x2200 },
    { " 32-1:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞ ﾎﾞｳｴﾝｷｮｳ", Select_LoadGame, 0x22A0 },
    { " 32-2:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ0", Select_LoadGame, 0x4000 },
    { " 32-3:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ1", Select_LoadGame, 0x4010 },
    { " 32-4:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ2", Select_LoadGame, 0x4020 },
    { " 32-5:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ3", Select_LoadGame, 0x4030 },
    { " 32-6:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ4", Select_LoadGame, 0x4040 },
    { " 32-7:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ5", Select_LoadGame, 0x4050 },
    { " 32-8:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ6", Select_LoadGame, 0x4060 },
    { " 32-9:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ7", Select_LoadGame, 0x4070 },
    { " 32-10:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ8", Select_LoadGame, 0x4080 },
    { " 32-11:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ9", Select_LoadGame, 0x4090 },
    { " 33:\x8Cｿﾞｰﾗ \x8Dﾉ ﾎｺﾗ", Select_LoadGame, 0x6000 },
    { " 33-0:\x8Cｿﾞｰﾗ \x8Dﾉ ﾐｾ", Select_LoadGame, 0x9250 },
    { " 33-1:\x8Cｿﾞｰﾗ \x8Dﾉ ﾋｶｴｼﾂ", Select_LoadGame, 0x9200 },
    { " 34:\x8Cｸﾞﾚｰﾄﾍﾞｲ", Select_LoadGame, 0xBE00 },
    { " 35:\x8Dﾀｷｳｴ ﾉ ｹｲﾘｭｳ", Select_LoadGame, 0x8E00 },
    { " 40:\x8Cﾛｯｸﾋﾞﾙ\x8D ﾉ ﾀﾃｱﾅ", Select_LoadGame, 0xAA00 },
    { " 40-0:\x8Dﾃﾝﾁ ｷﾞｬｸﾃﾝ", Select_LoadGame, 0xAC00 },
    { " 41:\x8Cｲｶｰﾅ \x8Dﾍﾉ ﾐﾁ", Select_LoadGame, 0xA000 },
    { " 42:\x8Cｲｶｰﾅ\x8D ｺｼﾞｮｳ", Select_LoadGame, 0x3400 },
    { " 42-0:\x8Cｲｶｰﾅ\x8D ﾉ ｺｼﾞｮｳ ﾅｲﾌﾞ", Select_LoadGame, 0x3430 },
    { " 42-B:\x8Cｲｶｰﾅ\x8D ﾉ ｺｼﾞｮｳ \x8Cﾎﾞｽ\x8Dﾍﾞﾔ", Select_LoadGame, 0xA600 },
    { " 43:\x8Cｲｶｰﾅ \x8Dｹｲｺｸ", Select_LoadGame, 0x2000 },
    { " 43-0:\x8Cｲｶｰﾅ \x8Dｹｲｺｸ ﾄﾞｳｸﾂ", Select_LoadGame, 0x20E0 },
    { " 43-1:\x8Cｾｺﾑ \x8Dﾉ ｲｴ", Select_LoadGame, 0x9800 },
    { " 43-2:\x8Cｵﾙｺﾞｰﾙ ﾊｳｽ", Select_LoadGame, 0xA400 },
    { " 50:\x8Cｸﾛｯｸﾀｳﾝ \x8D-ﾋｶﾞｼ-", Select_LoadGame, 0xD200 },
    { " 50-0:\x8Dﾏﾁ ﾉ ｼｬﾃｷｼﾞｮｳ", Select_LoadGame, 0x3A00 },
    { " 50-1:\x8Cﾊﾆｰ ｱﾝﾄﾞ ﾀﾞｰﾘﾝ \x8Dﾉ ﾐｾ", Select_LoadGame, 0x800 },
    { " 50-2:\x8Dﾀｶﾗﾊﾞｺﾔ", Select_LoadGame, 0x2800 },
    { " 50-3:\x8Cﾅﾍﾞ\x8Dｶﾏ ﾃｲ", Select_LoadGame, 0xBC00 },
    { " 50-4:\x8Dﾁｮｳﾁｮｳ ﾉ ｲｴ", Select_LoadGame, 0 },
    { " 50-5:\x8Cﾐﾙｸﾊﾞｰ", Select_LoadGame, 0x2400 },
    { " 51:\x8Cｸﾛｯｸﾀｳﾝ \x8D-ﾆｼ-", Select_LoadGame, 0xD400 },
    { " 51-0:\x8Dﾊﾞｸﾀﾞﾝ ﾔ", Select_LoadGame, 0xCA00 },
    { " 51-1:\x8Cﾏﾆ\x8Dﾔ", Select_LoadGame, 0xE00 },
    { " 51-2:\x8Dｻﾞｯｶ ﾔ", Select_LoadGame, 0x6200 },
    { " 51-3:\x8Dｹﾝﾄﾞｳｼﾞｮｳ", Select_LoadGame, 0xA200 },
    { " 51-4:\x8Dﾎﾟｽﾄﾊｳｽ", Select_LoadGame, 0x5600 },
    { " 51-5:\x8Dﾀｶﾗｸｼﾞﾔ", Select_LoadGame, 0x6C00 },
    { " 52:\x8Cｸﾛｯｸﾀｳﾝ \x8D-ｷﾀ-", Select_LoadGame, 0xD600 },
    { " 53:\x8Cｸﾛｯｸﾀｳﾝ \x8D-ﾐﾅﾐ-", Select_LoadGame, 0xD800 },
    { " 53-0:\x8Dﾄｹｲﾄｳﾅｲﾌﾞ", Select_LoadGame, 0xC000 },
    { " 54:\x8Dﾄｹｲﾄｳ ｵｸｼﾞｮｳ", Select_LoadGame, 0x2C00 },
    { " 55:\x8Dｾﾝﾀｸｼﾞｮｳ", Select_LoadGame, 0xDA00 },
    { " 55-0:\x8Cﾏﾆ\x8Dﾔ ﾉ ｳﾗｸﾞﾁ", Select_LoadGame, 0xE10 },
    { " 55-1:\x8Cﾏﾆ\x8Dﾔ ﾉ ﾉｿﾞｷｱﾅ", Select_LoadGame, 0xE20 },
    { "100:\x8Cｳｯﾄﾞﾏｳﾝﾃﾝ \x8Dﾉ ｼﾝﾃﾞﾝ", Select_LoadGame, 0x3000 },
    { "100-B:\x8Cｳｯﾄﾞﾏｳﾝﾃﾝ \x8Dﾉ ｼﾝﾃﾞﾝ\x8C-ﾎﾞｽ-", Select_LoadGame, 0x3800 },
    { "101:\x8Cｽﾉｰﾍｯﾄﾞ \x8Dﾉ ｼﾝﾃﾞﾝ", Select_LoadGame, 0x3C00 },
    { "101-B:\x8Cｽﾉｰﾍｯﾄﾞ \x8Dﾉ ｼﾝﾃﾞﾝ\x8C-ﾎﾞｽ-", Select_LoadGame, 0x8200 },
    { "102:\x8Cｸﾞﾚｰﾄﾍﾞｲ \x8Dﾉ ｼﾝﾃﾞﾝ", Select_LoadGame, 0x8C00 },
    { "102-B:\x8Cｸﾞﾚｰﾄﾍﾞｲ \x8Dﾉ ｼﾝﾃﾞﾝ\x8C-ﾎﾞｽ-", Select_LoadGame, 0xB800 },
    { "103:\x8Cﾛｯｸﾋﾞﾙ \x8Dﾉ ｼﾝﾃﾞﾝ-ｵﾓﾃｰ", Select_LoadGame, 0x2600 },
    { "103-0:\x8Cﾛｯｸﾋﾞﾙ \x8Dﾉ ｼﾝﾃﾞﾝ-ｳﾗｰ", Select_LoadGame, 0x2A00 },
    { "103-B:\x8Cﾛｯｸﾋﾞﾙ \x8Dﾉ ｼﾝﾃﾞﾝ\x8C-ﾎﾞｽ-", Select_LoadGame, 0x6600 },
    { "104:\x8Cｿｳｹﾞﾝ", Select_LoadGame, 0xC800 },
    { "104-0:\x8Cﾗｽﾄ ﾃﾞｸ ﾀﾞﾝｼﾞｮﾝ", Select_LoadGame, 0x4E00 },
    { "104-1:\x8Cﾗｽﾄ ｺﾞﾛﾝ ﾀﾞﾝｼﾞｮﾝ", Select_LoadGame, 0x7800 },
    { "104-2:\x8Cﾗｽﾄ ｿﾞｰﾗ ﾀﾞﾝｼﾞｮﾝ", Select_LoadGame, 0x8800 },
    { "104-3:\x8Cﾗｽﾄ ﾘﾝｸ ﾀﾞﾝｼﾞｮﾝ", Select_LoadGame, 0xC600 },
    { "104-B:\x8Cﾗｽﾄﾀﾞﾝｼﾞｮﾝ -ﾎﾞｽ-", Select_LoadGame, 0x200 },
    { "119:\x8Cﾃﾞｸﾅｯﾂ \x8Dﾉ ﾎｺﾗ", Select_LoadGame, 0x9E00 },
    { "121:\x8Dﾋﾐﾂ ﾉ ﾎｺﾗ", Select_LoadGame, 0xBA00 },
    { "122:\x8Cｵｰﾌﾟﾆﾝｸﾞ ﾀﾞﾝｼﾞｮﾝ", Select_LoadGame, 0x2E00 },
    { "123:\x8Dｷｮｼﾞﾝ ﾉ ﾏ", Select_LoadGame, 0xCC00 },
    { "126:\x8Cﾃﾞｸﾅｯﾂ ﾐﾆｹﾞｰﾑ", Select_LoadGame, 0x3600 },
    { "127-0:\x8Dﾖｳｾｲ ﾉ ｲｽﾞﾐ 0", Select_LoadGame, 0x4600 },
    { "127-1:\x8Dﾖｳｾｲ ﾉ ｲｽﾞﾐ 1", Select_LoadGame, 0x4610 },
    { "127-2:\x8Dﾖｳｾｲ ﾉ ｲｽﾞﾐ 2", Select_LoadGame, 0x4620 },
    { "127-3:\x8Dﾖｳｾｲ ﾉ ｲｽﾞﾐ 3", Select_LoadGame, 0x4630 },
    { "127-4:\x8Dﾖｳｾｲ ﾉ ｲｽﾞﾐ 4", Select_LoadGame, 0x4640 },
    { "128:\x8Dﾇﾏ ﾉ ｸﾓﾔｶﾀ", Select_LoadGame, 0x4800 },
    { "129:\x8Dｳﾐ ﾉ ｸﾓﾔｶﾀ", Select_LoadGame, 0x4A00 },
    { "130:\x8Dﾊｶ ﾉ ｼﾀ-\x8Cﾀﾞﾝﾍﾟｲ-", Select_LoadGame, 0x5A00 },
    { "131:\x8Dｲﾄﾞ ﾉ ｼﾀ", Select_LoadGame, 0x9000 },
    { "132:\x8Dﾕｳﾚｲｺﾞﾔ", Select_LoadGame, 0x9C00 },
    { "133-0:\x8Dﾊｶ ﾉ ｼﾀ0", Select_LoadGame, 0xA00 },
    { "133-1:\x8Dﾊｶ ﾉ ｼﾀ1", Select_LoadGame, 0xA10 },
    { "134-0:\x8Dｶｸｼｱﾅ 0", Select_LoadGame, 0x1400 },
    { "134-1:\x8Dｶｸｼｱﾅ 1", Select_LoadGame, 0x1410 },
    { "134-2:\x8Dｶｸｼｱﾅ 2", Select_LoadGame, 0x1420 },
    { "134-3:\x8Dｶｸｼｱﾅ 3", Select_LoadGame, 0x1430 },
    { "134-4:\x8Dｶｸｼｱﾅ 4", Select_LoadGame, 0x1440 },
    { "134-5:\x8Dｶｸｼｱﾅ5", Select_LoadGame, 0x1450 },
    { "134-7:\x8Dｶｸｼｱﾅ 7", Select_LoadGame, 0x1470 },
    { "134-9:\x8Dｶｸｼｱﾅ 9", Select_LoadGame, 0x1490 },
    { "134-10:\x8Dｶｸｼｱﾅ10", Select_LoadGame, 0x14A0 },
    { "134-11:\x8Dｶｸｼｱﾅ11", Select_LoadGame, 0x14B0 },
    { "134-13:\x8Dｶｸｼｱﾅ13", Select_LoadGame, 0x14D0 },
    { "X 1:SPOT00", Select_LoadGame, 0x1C00 },
    { "title", (void*)Select_LoadTitle, 0x0000 },
};

void Select_UpdateMenu(SelectContext* this) {
    s32 playerForm;
    Input* controller1 = CONTROLLER1(this);
    s32 stick_y;
    s32 pad[2];
    s16 phi_v1;
    s32 updateRate;

    if (this->unk_25C == 0) {
        if (CHECK_BTN_ALL(controller1->press.button, BTN_A) || CHECK_BTN_ALL(controller1->press.button, BTN_START)) {
            for (phi_v1 = 0; phi_v1 < ARRAY_COUNT(gSaveContext.unk_3EC0); phi_v1++) {
                gSaveContext.unk_3DD0[phi_v1] = 0;
                gSaveContext.unk_3DE0[phi_v1] = 0;
                gSaveContext.unk_3E18[phi_v1] = 0;
                gSaveContext.unk_3E50[phi_v1] = 0;
                gSaveContext.unk_3E88[phi_v1] = 0;
                gSaveContext.unk_3EC0[phi_v1] = 0;
            }
            gSaveContext.minigameState = 0;

            if (this->scenes[this->currentScene].loadFunc != NULL) {
                this->scenes[this->currentScene].loadFunc(this, this->scenes[this->currentScene].entranceIndex, this->opt);
            }
        }

        if (CHECK_BTN_ALL(controller1->press.button, BTN_B)) {
            playerForm = gSaveContext.playerForm - 1;
            if (playerForm < PLAYER_FORM_FIERCE_DEITY) {
                playerForm = PLAYER_FORM_HUMAN;
            }
            gSaveContext.playerForm = playerForm;
        }

        if (CHECK_BTN_ALL(controller1->press.button, BTN_Z)) {
            if (gSaveContext.cutscene == 0x8000) {
                gSaveContext.cutscene = 0;
            } else if (gSaveContext.cutscene == 0) {
                gSaveContext.cutscene = 0x8800;
            } else if (gSaveContext.cutscene == 0x8800) {
                gSaveContext.cutscene = 0xFFF0;
            } else if (gSaveContext.cutscene == 0xFFF0) {
                gSaveContext.cutscene = 0xFFF1;
            } else if (gSaveContext.cutscene == 0xFFF1) {
                gSaveContext.cutscene = 0xFFF2;
            } else if (gSaveContext.cutscene == 0xFFF2) {
                gSaveContext.cutscene = 0xFFF3;
            } else if (gSaveContext.cutscene == 0xFFF3) {
                gSaveContext.cutscene = 0xFFF4;
            } else if (gSaveContext.cutscene == 0xFFF4) {
                gSaveContext.cutscene = 0xFFF5;
            } else if (gSaveContext.cutscene == 0xFFF5) {
                gSaveContext.cutscene = 0xFFF6;
            } else if (gSaveContext.cutscene == 0xFFF6) {
                gSaveContext.cutscene = 0xFFF7;
            } else if (gSaveContext.cutscene == 0xFFF7) {
                gSaveContext.cutscene = 0xFFF8;
            } else if (gSaveContext.cutscene == 0xFFF8) {
                gSaveContext.cutscene = 0xFFF9;
            } else if (gSaveContext.cutscene == 0xFFF9) {
                gSaveContext.cutscene = 0xFFFA;
            } else if (gSaveContext.cutscene == 0xFFFA) {
                gSaveContext.cutscene = 0x8000;
            }
        } else if (CHECK_BTN_ALL(controller1->press.button, BTN_R)) {
            if (gSaveContext.cutscene == 0x8000) {
                gSaveContext.cutscene = 0xFFFA;
            } else if (gSaveContext.cutscene == 0) {
                gSaveContext.cutscene = 0x8000;
            } else if (gSaveContext.cutscene == 0x8800) {
                gSaveContext.cutscene = 0;
            } else if (gSaveContext.cutscene == 0xFFF0) {
                gSaveContext.cutscene = 0x8800;
            } else if (gSaveContext.cutscene == 0xFFF1) {
                gSaveContext.cutscene = 0xFFF0;
            } else if (gSaveContext.cutscene == 0xFFF2) {
                gSaveContext.cutscene = 0xFFF1;
            } else if (gSaveContext.cutscene == 0xFFF3) {
                gSaveContext.cutscene = 0xFFF2;
            } else if (gSaveContext.cutscene == 0xFFF4) {
                gSaveContext.cutscene = 0xFFF3;
            } else if (gSaveContext.cutscene == 0xFFF5) {
                gSaveContext.cutscene = 0xFFF4;
            } else if (gSaveContext.cutscene == 0xFFF6) {
                gSaveContext.cutscene = 0xFFF5;
            } else if (gSaveContext.cutscene == 0xFFF7) {
                gSaveContext.cutscene = 0xFFF6;
            } else if (gSaveContext.cutscene == 0xFFF8) {
                gSaveContext.cutscene = 0xFFF7;
            } else if (gSaveContext.cutscene == 0xFFF9) {
                gSaveContext.cutscene = 0xFFF8;
            } else if (gSaveContext.cutscene == 0xFFFA) {
                gSaveContext.cutscene = 0xFFF9;
            }
        }

        gSaveContext.isNight = false;
        if (gSaveContext.cutscene == 0x8800) {
            gSaveContext.isNight = true;
        }

        // user can change "opt", but it doesn't do anything
        if (CHECK_BTN_ALL(controller1->press.button, BTN_CUP)) {
            this->opt--;
        }
        if (CHECK_BTN_ALL(controller1->press.button, BTN_CDOWN)) {
            this->opt++;
        }

        if (CHECK_BTN_ALL(controller1->press.button, BTN_CLEFT)) {
            if (gSaveContext.day > 1) {
                gSaveContext.day--;
            }
        }

        if (CHECK_BTN_ALL(controller1->press.button, BTN_CRIGHT)) {
            if (gSaveContext.day < 4) {
                gSaveContext.day++;
            }
        }

        updateRate = R_UPDATE_RATE;
        stick_y = controller1->rel.stick_y;
        if (stick_y != 0) {
            this->cursorVelocity = (updateRate * stick_y) / 7;
        } else {
            if (CHECK_BTN_ALL(controller1->press.button, BTN_DUP)) {
                if (this->unk_26C == 1) {
                    this->unk_264 = 0;
                }
                if (this->unk_264 == 0) {
                    this->unk_264 = 20;
                    this->unk_26C = 1;

                    play_sound(NA_SE_IT_SWORD_IMPACT);
                    this->cursorVelocity = updateRate;
                }
            }

            if (CHECK_BTN_ALL(controller1->cur.button, BTN_DUP) && (this->unk_264 == 0)) {
                play_sound(NA_SE_IT_SWORD_IMPACT);
                this->cursorVelocity = updateRate * 3;
            }

            if (CHECK_BTN_ALL(controller1->press.button, BTN_DDOWN)) {
                if (this->unk_270 == 1) {
                    this->unk_268 = 0;
                }
                if (this->unk_268 == 0) {
                    this->unk_268 = 20;
                    this->unk_270 = 1;
                    play_sound(NA_SE_IT_SWORD_IMPACT);
                    this->cursorVelocity = -updateRate;
                }
            }
            if (CHECK_BTN_ALL(controller1->cur.button, BTN_DDOWN) && (this->unk_268 == 0)) {
                play_sound(NA_SE_IT_SWORD_IMPACT);
                this->cursorVelocity = -updateRate * 3;
            }

            if (CHECK_BTN_ALL(controller1->press.button, BTN_DLEFT) || CHECK_BTN_ALL(controller1->cur.button, BTN_DLEFT)) {
                play_sound(NA_SE_IT_SWORD_IMPACT);
                this->cursorVelocity = updateRate;
            }

            if (CHECK_BTN_ALL(controller1->press.button, BTN_DRIGHT) || CHECK_BTN_ALL(controller1->cur.button, BTN_DRIGHT)) {
                play_sound(NA_SE_IT_SWORD_IMPACT);
                this->cursorVelocity = -updateRate;
            }
        }
    }

    if (CHECK_BTN_ALL(controller1->press.button, BTN_L)) {
        this->unk_21C++;
        this->unk_21C = (this->unk_21C + ARRAY_COUNT(this->unk_220)) % ARRAY_COUNT(this->unk_220);
        this->currentScene = this->cursorPos = this->unk_220[this->unk_21C];
    }

    this->unk_25C += this->cursorVelocity;

    if (this->unk_25C < -7) {
        this->cursorVelocity = 0;
        this->unk_25C = 0;

        this->currentScene++;
        this->currentScene = (this->currentScene + this->count) % this->count;

        if (this->currentScene == ((this->cursorPos + this->count + 19) % this->count)) {
            this->cursorPos++;
            this->cursorPos = (this->cursorPos + this->count) % this->count;
        }
    }

    if (this->unk_25C > 7) {
        this->cursorVelocity = 0;
        this->unk_25C = 0;
        if (this->currentScene == this->cursorPos) {
            this->cursorPos -= 2;
            this->cursorPos = (this->cursorPos + this->count) % this->count;
        }

        this->currentScene--;
        this->currentScene = (this->currentScene + this->count) % this->count;
        if (this->currentScene == ((this->cursorPos + this->count) % this->count)) {
            this->cursorPos--;
            this->cursorPos = (this->cursorPos + this->count) % this->count;
        }
    }

    this->currentScene = (this->currentScene + this->count) % this->count;
    this->cursorPos = (this->cursorPos + this->count) % this->count;

    dREG(80) = this->currentScene;
    dREG(81) = this->cursorPos;
    dREG(82) = this->unk_21C;

    if (this->unk_264 != 0) {
        this->unk_264--;
    }
    if (this->unk_264 == 0) {
        this->unk_26C = 0;
    }

    if (this->unk_268 != 0) {
        this->unk_268--;
    }
    if (this->unk_268 == 0) {
        this->unk_270 = 0;
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
        sceneIndex = (this->cursorPos + i + this->count) % this->count;
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
const char* sLoadingMessages[] = {
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
const char* D_80802364[][2] = {
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
    const char* (*temp_a0)[2];
    const char* (*phi_v1)[2];
    s32 phi_v0;

    if ((playerForm >= PLAYER_FORM_FIERCE_DEITY) && (playerForm < PLAYER_FORM_MAX)) {
        temp_a0 = &D_80802364[playerForm];
        phi_v1 = temp_a0 + 1;

        // This loop doesn't do anything
        for (phi_v0 = 8; phi_v0 >= 0; phi_v0 -= 8) {
            if (phi_v1 != 0) {
                break;
            }
            phi_v1--;
        }
        if (phi_v1) {}

        age = (*temp_a0)[0];
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

    switch (csIndex) {
        case 0:
            // clang-format off
            gSaveContext.time = CLOCK_TIME(12, 0); stage = "\x8Dｵﾋﾙ\x8Cｼﾞｬﾗ";
            // clang-format on
            break;

        case 0x8000:
            // clang-format off
            gSaveContext.time = CLOCK_TIME(6, 0) + 1; stage = "\x8Dｱｻ \x8Cｼﾞｬﾗ";
            // clang-format on
            break;

        case 0x8800:
            gSaveContext.time = CLOCK_TIME(18, 1);
            stage = "\x8Dﾖﾙ \x8Cｼﾞｬﾗ";
            break;

        case 0xFFF0:
            // clang-format off
            gSaveContext.time = CLOCK_TIME(12, 0); stage = "ﾃﾞﾓ00";
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
    gSaveContext.environmentTime = gSaveContext.time;
    GfxPrint_Printf(printer, "Stage:\x8C%s", stage);

    GfxPrint_SetPos(printer, 23, 25);
    GfxPrint_SetColor(printer, 255, 255, 55, 255);

    switch (gSaveContext.day) {
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
            gSaveContext.day = 1;
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
    Select_PrintAgeSetting(this, printer, ((void)0, gSaveContext.playerForm));
    Select_PrintCutsceneSetting(this, printer, ((void)0, gSaveContext.cutscene));

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

    func_8012CF0C(gfxCtx, 1, 1, 0, 0, 0);

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
    ShrinkWindow_Fini();
}

void Select_Init(GameState* thisx) {
    SelectContext* this = (SelectContext*)thisx;

    this->state.main = Select_Main;
    this->state.destroy = Select_Destroy;

    this->scenes = D_80801C80;
    this->cursorPos = 0;
    this->currentScene = 0;
    this->unk_220[0] = 0;
    this->unk_220[1] = 19;
    this->unk_220[2] = 37;
    this->unk_220[3] = 51;
    this->unk_220[4] = 59;
    this->unk_220[5] = 73;
    this->unk_220[6] = 91;
    this->unk_21C = 0;
    this->opt = 0;
    this->count = ARRAY_COUNT(D_80801C80);

    ShrinkWindow_Init();
    View_Init(&this->view, this->state.gfxCtx);
    this->view.flags = (0x08 | 0x02);
    this->unk_25C = 0;
    this->cursorVelocity = 0;
    this->unk_264 = 0;
    this->unk_268 = 0;
    this->unk_26C = 0;
    this->unk_270 = 0;
    this->unk_274 = 0;

    if ((dREG(80) >= 0) && (dREG(80) < this->count)) {
        this->currentScene = dREG(80);
        this->cursorPos = dREG(81);
        this->unk_21C = dREG(82);
    }

    Game_SetFramerateDivisor(&this->state, 1);
    gSaveContext.cutscene = 0;
    gSaveContext.playerForm = PLAYER_FORM_HUMAN;
    gSaveContext.linkAge = 0;
}
