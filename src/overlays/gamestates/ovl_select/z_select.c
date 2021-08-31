/*
 * File: z_select.c
 * Overlay: ovl_select
 * Description:
 */

#include "z_select.h"
#include "alloca.h"
#include "overlays/gamestates/ovl_title/z_title.h"

void func_80800930(SelectContext* this, u32, s32);
void func_80800910(SelectContext* this);

SceneSelectEntry D_80801C80[] = {
    { "  0:OP\x8Cﾃﾞﾓ\x8Dﾖｳ ｼﾝﾘﾝ", func_80800930, 0x1C00 },
    { "  0-0:\x8Dﾏﾖｲ ﾉ ﾓﾘ", func_80800930, 0xC400 },
    { "  1:\x8Cﾀｳﾝ \x8Dｺｳｶﾞｲ", func_80800930, 0x5400 },
    { "  1-0:\x8Dﾃﾝﾓﾝｶﾝｿｸｼﾞｮ", func_80800930, 0x4C00 },
    { "  1-1:\x8Dﾃﾝﾓﾝｶﾝｿｸｼﾞｮ ﾃﾞ ﾎﾞｳｴﾝｷｮｳ", func_80800930, 0x54A0 },
    { "  1-2:\x8Cｲｶｰﾅ \x8Dﾉ ﾊｶﾊﾞ", func_80800930, 0x8000 },
    { "  2:\x8Cﾛﾏﾆｰ \x8Dﾎﾞｸｼﾞｮｳ", func_80800930, 0x6400 },
    { "  3:\x8Cﾐﾙｸﾛｰﾄﾞ", func_80800930, 0x3E00 },
    { "  4:\x8Dｵﾓﾔ", func_80800930, 0x610 },
    { "  5:\x8Dｳｼｺﾞﾔ", func_80800930, 0x600 },
    { "  6:\x8Cｺｯｺ \x8Dｺﾞﾔ", func_80800930, 0x7E00 },
    { "  7:\x8Cﾄﾞｯｸﾞﾚｰｽ\x8Dｼﾞｮｳ", func_80800930, 0x7C00 },
    { "  8:\x8Cｺﾞｰﾏﾝ ﾄﾗｯｸ", func_80800930, 0xCE00 },
    { " 10:\x8Dﾔﾏｻﾞﾄ -ﾌﾕ-", func_80800930, 0x9A00 },
    { " 10-0:\x8Dﾔﾏｻﾞﾄ -ﾊﾙ-", func_80800930, 0xAE00 },
    { " 10-1:\x8Dﾔﾏｻﾞﾄ ﾉ ｶｼﾞﾔ", func_80800930, 0x5200 },
    { " 11:\x8Cｺﾞﾛﾝ\x8D ﾉ ｻﾄ -ﾌﾕ-", func_80800930, 0x9400 },
    { " 11-0:\x8Cｺﾞﾛﾝ\x8D ﾉ ｻﾄ -ﾊﾙ-", func_80800930, 0x8A00 },
    { " 11-1:\x8Cｺﾞﾛﾝ\x8D ﾉ ﾎｺﾗ", func_80800930, 0x5E00 },
    { " 11-2:\x8Dﾊﾅﾚﾔﾏ ﾉ ﾎｺﾗ", func_80800930, 0x1500 },
    { " 11-3:\x8Cｺﾞﾛﾝ \x8Dﾉ ﾐｾ", func_80800930, 0x7400 },
    { " 12:\x8Cｽﾉｰﾍｯﾄﾞ", func_80800930, 0xB200 },
    { " 13:\x8Dﾌﾌﾞｷ ﾉ ﾐﾁ", func_80800930, 0x3200 },
    { " 14:\x8Dﾕｷﾀﾞﾏ ﾉ ﾐﾁ", func_80800930, 0xB000 },
    { " 15:\x8Cｺﾞﾛﾝﾚｰｽ \x8Dｼﾞｮｳ", func_80800930, 0xD000 },
    { " 16:\x8Cｺﾞﾛﾝ \x8Dﾉ ﾊｶ", func_80800930, 0x9600 },
    { " 17:\x8Dｾﾂｹﾞﾝ \x8Cﾊﾞﾄﾙ \x8D-ﾌﾕ-", func_80800930, 0xB400 },
    { " 17-0:\x8Dｾﾂｹﾞﾝ \x8Cﾊﾞﾄﾙ \x8D-ﾊﾙ-", func_80800930, 0xB600 },
    { " 20:\x8Dﾇﾏﾁ", func_80800930, 0x8400 },
    { " 20-0:\x8Dﾇﾏﾁ ｿﾉｺﾞ", func_80800930, 0xC00 },
    { " 20-1:\x8Dﾇﾏ ﾉ ｶﾝｺｳｱﾝﾅｲ", func_80800930, 0xA800 },
    { " 20-2:\x8Dﾏﾎｳｵﾊﾞﾊﾞ ﾉ ｸｽﾘﾔ", func_80800930, 0x400 },
    { " 21:\x8Cｳｯﾄﾞﾏｳﾝﾃﾝ", func_80800930, 0x8600 },
    { " 21-0:\x8Cﾃﾞｸ\x8Dﾋﾒ ﾉ ﾛｳﾔ", func_80800930, 0x3010 },
    { " 22:\x8Cﾃﾞｸﾅｯﾂ \x8Dﾉ ｼﾛ", func_80800930, 0x5000 },
    { " 22-0:\x8Cｸﾛｽｹ \x8Dﾉ ｱﾅ0", func_80800930, 0x1460 },
    { " 22-1:\x8Cｸﾛｽｹ \x8Dﾉ ｱﾅ1", func_80800930, 0x14E0 },
    { " 22-2:\x8Cｸﾛｽｹ \x8Dﾉ ｱﾅ2", func_80800930, 0x1480 },
    { " 22-3:\x8Cｸﾛｽｹ \x8Dﾉ ｱﾅ3", func_80800930, 0x14F0 },
    { " 22-4:\x8Cｸﾛｽｹ \x8Dﾉ ｱﾅ4", func_80800930, 0x14C0 },
    { " 24:\x8Dｹﾓﾉﾐﾁ", func_80800930, 0x7A00 },
    { " 24-0:\x8Dﾓﾘ ﾉ ｼｬﾃｷｼﾞｮｳ", func_80800930, 0x4200 },
    { " 25:\x8Cﾃﾞｸ\x8Dｵｳ ﾉ ﾏ", func_80800930, 0x7600 },
    { " 26:\x8Dﾌｼｷﾞ ﾉ ﾓﾘ", func_80800930, 0xC200 },
    { " 30:\x8Cｸﾞﾚｰﾄﾍﾞｲ\x8D ﾉ ｶｲｶﾞﾝ", func_80800930, 0x6800 },
    { " 30-0:\x8Dｶｲﾖｳ ｹﾝｷｭｳｼﾞｮ", func_80800930, 0x5800 },
    { " 30-1:\x8Dﾘｮｳｼ ﾉ ｲｴ", func_80800930, 0x7200 },
    { " 30-2:\x8Dﾄﾝｶﾞﾘ ｲﾜ", func_80800930, 0x4400 },
    { " 31:\x8Dﾐｻｷ", func_80800930, 0x6A00 },
    { " 32:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾏｴ", func_80800930, 0x7000 },
    { " 32-0:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞ", func_80800930, 0x2200 },
    { " 32-1:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞ ﾎﾞｳｴﾝｷｮｳ", func_80800930, 0x22A0 },
    { " 32-2:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ0", func_80800930, 0x4000 },
    { " 32-3:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ1", func_80800930, 0x4010 },
    { " 32-4:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ2", func_80800930, 0x4020 },
    { " 32-5:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ3", func_80800930, 0x4030 },
    { " 32-6:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ4", func_80800930, 0x4040 },
    { " 32-7:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ5", func_80800930, 0x4050 },
    { " 32-8:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ6", func_80800930, 0x4060 },
    { " 32-9:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ7", func_80800930, 0x4070 },
    { " 32-10:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ8", func_80800930, 0x4080 },
    { " 32-11:\x8Dｶｲｿﾞｸﾉﾄﾘﾃﾞﾅｲﾌﾞ9", func_80800930, 0x4090 },
    { " 33:\x8Cｿﾞｰﾗ \x8Dﾉ ﾎｺﾗ", func_80800930, 0x6000 },
    { " 33-0:\x8Cｿﾞｰﾗ \x8Dﾉ ﾐｾ", func_80800930, 0x9250 },
    { " 33-1:\x8Cｿﾞｰﾗ \x8Dﾉ ﾋｶｴｼﾂ", func_80800930, 0x9200 },
    { " 34:\x8Cｸﾞﾚｰﾄﾍﾞｲ", func_80800930, 0xBE00 },
    { " 35:\x8Dﾀｷｳｴ ﾉ ｹｲﾘｭｳ", func_80800930, 0x8E00 },
    { " 40:\x8Cﾛｯｸﾋﾞﾙ\x8D ﾉ ﾀﾃｱﾅ", func_80800930, 0xAA00 },
    { " 40-0:\x8Dﾃﾝﾁ ｷﾞｬｸﾃﾝ", func_80800930, 0xAC00 },
    { " 41:\x8Cｲｶｰﾅ \x8Dﾍﾉ ﾐﾁ", func_80800930, 0xA000 },
    { " 42:\x8Cｲｶｰﾅ\x8D ｺｼﾞｮｳ", func_80800930, 0x3400 },
    { " 42-0:\x8Cｲｶｰﾅ\x8D ﾉ ｺｼﾞｮｳ ﾅｲﾌﾞ", func_80800930, 0x3430 },
    { " 42-B:\x8Cｲｶｰﾅ\x8D ﾉ ｺｼﾞｮｳ \x8Cﾎﾞｽ\x8Dﾍﾞﾔ", func_80800930, 0xA600 },
    { " 43:\x8Cｲｶｰﾅ \x8Dｹｲｺｸ", func_80800930, 0x2000 },
    { " 43-0:\x8Cｲｶｰﾅ \x8Dｹｲｺｸ ﾄﾞｳｸﾂ", func_80800930, 0x20E0 },
    { " 43-1:\x8Cｾｺﾑ \x8Dﾉ ｲｴ", func_80800930, 0x9800 },
    { " 43-2:\x8Cｵﾙｺﾞｰﾙ ﾊｳｽ", func_80800930, 0xA400 },
    { " 50:\x8Cｸﾛｯｸﾀｳﾝ \x8D-ﾋｶﾞｼ-", func_80800930, 0xD200 },
    { " 50-0:\x8Dﾏﾁ ﾉ ｼｬﾃｷｼﾞｮｳ", func_80800930, 0x3A00 },
    { " 50-1:\x8Cﾊﾆｰ ｱﾝﾄﾞ ﾀﾞｰﾘﾝ \x8Dﾉ ﾐｾ", func_80800930, 0x800 },
    { " 50-2:\x8Dﾀｶﾗﾊﾞｺﾔ", func_80800930, 0x2800 },
    { " 50-3:\x8Cﾅﾍﾞ\x8Dｶﾏ ﾃｲ", func_80800930, 0xBC00 },
    { " 50-4:\x8Dﾁｮｳﾁｮｳ ﾉ ｲｴ", func_80800930, 0 },
    { " 50-5:\x8Cﾐﾙｸﾊﾞｰ", func_80800930, 0x2400 },
    { " 51:\x8Cｸﾛｯｸﾀｳﾝ \x8D-ﾆｼ-", func_80800930, 0xD400 },
    { " 51-0:\x8Dﾊﾞｸﾀﾞﾝ ﾔ", func_80800930, 0xCA00 },
    { " 51-1:\x8Cﾏﾆ\x8Dﾔ", func_80800930, 0xE00 },
    { " 51-2:\x8Dｻﾞｯｶ ﾔ", func_80800930, 0x6200 },
    { " 51-3:\x8Dｹﾝﾄﾞｳｼﾞｮｳ", func_80800930, 0xA200 },
    { " 51-4:\x8Dﾎﾟｽﾄﾊｳｽ", func_80800930, 0x5600 },
    { " 51-5:\x8Dﾀｶﾗｸｼﾞﾔ", func_80800930, 0x6C00 },
    { " 52:\x8Cｸﾛｯｸﾀｳﾝ \x8D-ｷﾀ-", func_80800930, 0xD600 },
    { " 53:\x8Cｸﾛｯｸﾀｳﾝ \x8D-ﾐﾅﾐ-", func_80800930, 0xD800 },
    { " 53-0:\x8Dﾄｹｲﾄｳﾅｲﾌﾞ", func_80800930, 0xC000 },
    { " 54:\x8Dﾄｹｲﾄｳ ｵｸｼﾞｮｳ", func_80800930, 0x2C00 },
    { " 55:\x8Dｾﾝﾀｸｼﾞｮｳ", func_80800930, 0xDA00 },
    { " 55-0:\x8Cﾏﾆ\x8Dﾔ ﾉ ｳﾗｸﾞﾁ", func_80800930, 0xE10 },
    { " 55-1:\x8Cﾏﾆ\x8Dﾔ ﾉ ﾉｿﾞｷｱﾅ", func_80800930, 0xE20 },
    { "100:\x8Cｳｯﾄﾞﾏｳﾝﾃﾝ \x8Dﾉ ｼﾝﾃﾞﾝ", func_80800930, 0x3000 },
    { "100-B:\x8Cｳｯﾄﾞﾏｳﾝﾃﾝ \x8Dﾉ ｼﾝﾃﾞﾝ\x8C-ﾎﾞｽ-", func_80800930, 0x3800 },
    { "101:\x8Cｽﾉｰﾍｯﾄﾞ \x8Dﾉ ｼﾝﾃﾞﾝ", func_80800930, 0x3C00 },
    { "101-B:\x8Cｽﾉｰﾍｯﾄﾞ \x8Dﾉ ｼﾝﾃﾞﾝ\x8C-ﾎﾞｽ-", func_80800930, 0x8200 },
    { "102:\x8Cｸﾞﾚｰﾄﾍﾞｲ \x8Dﾉ ｼﾝﾃﾞﾝ", func_80800930, 0x8C00 },
    { "102-B:\x8Cｸﾞﾚｰﾄﾍﾞｲ \x8Dﾉ ｼﾝﾃﾞﾝ\x8C-ﾎﾞｽ-", func_80800930, 0xB800 },
    { "103:\x8Cﾛｯｸﾋﾞﾙ \x8Dﾉ ｼﾝﾃﾞﾝ-ｵﾓﾃｰ", func_80800930, 0x2600 },
    { "103-0:\x8Cﾛｯｸﾋﾞﾙ \x8Dﾉ ｼﾝﾃﾞﾝ-ｳﾗｰ", func_80800930, 0x2A00 },
    { "103-B:\x8Cﾛｯｸﾋﾞﾙ \x8Dﾉ ｼﾝﾃﾞﾝ\x8C-ﾎﾞｽ-", func_80800930, 0x6600 },
    { "104:\x8Cｿｳｹﾞﾝ", func_80800930, 0xC800 },
    { "104-0:\x8Cﾗｽﾄ ﾃﾞｸ ﾀﾞﾝｼﾞｮﾝ", func_80800930, 0x4E00 },
    { "104-1:\x8Cﾗｽﾄ ｺﾞﾛﾝ ﾀﾞﾝｼﾞｮﾝ", func_80800930, 0x7800 },
    { "104-2:\x8Cﾗｽﾄ ｿﾞｰﾗ ﾀﾞﾝｼﾞｮﾝ", func_80800930, 0x8800 },
    { "104-3:\x8Cﾗｽﾄ ﾘﾝｸ ﾀﾞﾝｼﾞｮﾝ", func_80800930, 0xC600 },
    { "104-B:\x8Cﾗｽﾄﾀﾞﾝｼﾞｮﾝ -ﾎﾞｽ-", func_80800930, 0x200 },
    { "119:\x8Cﾃﾞｸﾅｯﾂ \x8Dﾉ ﾎｺﾗ", func_80800930, 0x9E00 },
    { "121:\x8Dﾋﾐﾂ ﾉ ﾎｺﾗ", func_80800930, 0xBA00 },
    { "122:\x8Cｵｰﾌﾟﾆﾝｸﾞ ﾀﾞﾝｼﾞｮﾝ", func_80800930, 0x2E00 },
    { "123:\x8Dｷｮｼﾞﾝ ﾉ ﾏ", func_80800930, 0xCC00 },
    { "126:\x8Cﾃﾞｸﾅｯﾂ ﾐﾆｹﾞｰﾑ", func_80800930, 0x3600 },
    { "127-0:\x8Dﾖｳｾｲ ﾉ ｲｽﾞﾐ 0", func_80800930, 0x4600 },
    { "127-1:\x8Dﾖｳｾｲ ﾉ ｲｽﾞﾐ 1", func_80800930, 0x4610 },
    { "127-2:\x8Dﾖｳｾｲ ﾉ ｲｽﾞﾐ 2", func_80800930, 0x4620 },
    { "127-3:\x8Dﾖｳｾｲ ﾉ ｲｽﾞﾐ 3", func_80800930, 0x4630 },
    { "127-4:\x8Dﾖｳｾｲ ﾉ ｲｽﾞﾐ 4", func_80800930, 0x4640 },
    { "128:\x8Dﾇﾏ ﾉ ｸﾓﾔｶﾀ", func_80800930, 0x4800 },
    { "129:\x8Dｳﾐ ﾉ ｸﾓﾔｶﾀ", func_80800930, 0x4A00 },
    { "130:\x8Dﾊｶ ﾉ ｼﾀ-\x8Cﾀﾞﾝﾍﾟｲ-", func_80800930, 0x5A00 },
    { "131:\x8Dｲﾄﾞ ﾉ ｼﾀ", func_80800930, 0x9000 },
    { "132:\x8Dﾕｳﾚｲｺﾞﾔ", func_80800930, 0x9C00 },
    { "133-0:\x8Dﾊｶ ﾉ ｼﾀ0", func_80800930, 0xA00 },
    { "133-1:\x8Dﾊｶ ﾉ ｼﾀ1", func_80800930, 0xA10 },
    { "134-0:\x8Dｶｸｼｱﾅ 0", func_80800930, 0x1400 },
    { "134-1:\x8Dｶｸｼｱﾅ 1", func_80800930, 0x1410 },
    { "134-2:\x8Dｶｸｼｱﾅ 2", func_80800930, 0x1420 },
    { "134-3:\x8Dｶｸｼｱﾅ 3", func_80800930, 0x1430 },
    { "134-4:\x8Dｶｸｼｱﾅ 4", func_80800930, 0x1440 },
    { "134-5:\x8Dｶｸｼｱﾅ5", func_80800930, 0x1450 },
    { "134-7:\x8Dｶｸｼｱﾅ 7", func_80800930, 0x1470 },
    { "134-9:\x8Dｶｸｼｱﾅ 9", func_80800930, 0x1490 },
    { "134-10:\x8Dｶｸｼｱﾅ10", func_80800930, 0x14A0 },
    { "134-11:\x8Dｶｸｼｱﾅ11", func_80800930, 0x14B0 },
    { "134-13:\x8Dｶｸｼｱﾅ13", func_80800930, 0x14D0 },
    { "X 1:SPOT00", func_80800930, 0x1C00 },
    { "title", (void*)func_80800910, 0x0000 },
};

void func_80800910(SelectContext* this) {
    {
        GameState* state = &this->state;
        state->running = false;
    }

    SET_NEXT_GAMESTATE(&this->state, Title_Init, TitleContext);
}

extern s8 D_801BDBB0;

#ifdef NON_EQUIVALENT
void func_80800930(SelectContext* this, u32 arg1, s32 arg2) {
    gSaveContext.fileNum;

    if (gSaveContext.fileNum == 0xFF) {
        func_80144968();
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

    // NA_BGM_STOP: 0x100000FF
    func_801A89A8(0x100000FF);
    gSaveContext.entranceIndex = arg1;

    if (arg2 != 0) {
        gSaveContext.entranceIndex = Entrance_CreateIndex((s32)arg1 >> 9, arg2, arg1 & 0xF);
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

    {
        GameState* state = &this->state;
        state->running = false;
    }
    SET_NEXT_GAMESTATE(&this->state, Play_Init, GlobalContext);
}
#else
void func_80800930(SelectContext* this, u32, s32);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_select/func_80800930.s")
#endif

#ifdef NON_EQUIVALENT
void func_80800A44(SelectContext* this) {
    s32 pad[5];
    Input* controller1; // sp24?

    controller1 = CONTROLLER1(this);

    if (this->unk_25C == 0) {
        if (CHECK_BTN_ALL(controller1->press.button, BTN_A) || CHECK_BTN_ALL(controller1->press.button, BTN_START)) {
            s16 phi_v1;

            for (phi_v1 = 0; phi_v1 < ARRAY_COUNT(gSaveContext.unk_3EC0); phi_v1++) {
                gSaveContext.unk_3DD0[phi_v1] = 0;
                gSaveContext.unk_3DE0[phi_v1] = 0;
                gSaveContext.unk_3E18[phi_v1] = 0;
                gSaveContext.unk_3E50[phi_v1] = 0;
                gSaveContext.unk_3E88[phi_v1] = 0;
                gSaveContext.unk_3EC0[phi_v1] = 0;
            }

            gSaveContext.minigameState = 0;
            if (this->scenes[this->unk_218].loadFunc != NULL) {
                this->scenes[this->unk_218].loadFunc(this, this->scenes[this->unk_218].entranceIndex, this->unk_248);
            }
        }
        if (CHECK_BTN_ALL(controller1->press.button, BTN_B)) {
    s32 phi_v1_2;
            phi_v1_2 = gSaveContext.playerForm - 1;
            if (phi_v1_2 < 0) {
                phi_v1_2 = 4U;
            }
            gSaveContext.playerForm = phi_v1_2;
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

            if (gSaveContext.cutscene ==  0x8000) {
                gSaveContext.cutscene = 0xFFFA;
            } else if (gSaveContext.cutscene ==  0) {
                gSaveContext.cutscene = 0x8000;
            } else if (gSaveContext.cutscene ==  0x8800) {
                gSaveContext.cutscene = 0;
            } else if (gSaveContext.cutscene ==  0xFFF0) {
                gSaveContext.cutscene = 0x8800;
            } else if (gSaveContext.cutscene ==  0xFFF1) {
                gSaveContext.cutscene = 0xFFF0;
            } else if (gSaveContext.cutscene ==  0xFFF2) {
                gSaveContext.cutscene = 0xFFF1;
            } else if (gSaveContext.cutscene ==  0xFFF3) {
                gSaveContext.cutscene = 0xFFF2;
            } else if (gSaveContext.cutscene ==  0xFFF4) {
                gSaveContext.cutscene = 0xFFF3;
            } else if (gSaveContext.cutscene ==  0xFFF5) {
                gSaveContext.cutscene = 0xFFF4;
            } else if (gSaveContext.cutscene ==  0xFFF6) {
                gSaveContext.cutscene = 0xFFF5;
            } else if (gSaveContext.cutscene ==  0xFFF7) {
                gSaveContext.cutscene = 0xFFF6;
            } else if (gSaveContext.cutscene ==  0xFFF8) {
                gSaveContext.cutscene = 0xFFF7;
            } else if (gSaveContext.cutscene ==  0xFFF9) {
                gSaveContext.cutscene = 0xFFF8;
            } else if (gSaveContext.cutscene ==  0xFFFA) {
                gSaveContext.cutscene = 0xFFF9;
            }

        }
        gSaveContext.isNight = 0;
        if (gSaveContext.cutscene == 0x8800) {
            gSaveContext.isNight = 1;
        }
        if (CHECK_BTN_ALL(controller1->press.button, BTN_CUP)) {
            this->unk_248 += -1;
        }
        if (CHECK_BTN_ALL(controller1->press.button, BTN_CDOWN)) {
            this->unk_248 += 1;
        }
        if (CHECK_BTN_ALL(controller1->press.button, BTN_CLEFT)) {
            if (gSaveContext.day >= 2) {
                gSaveContext.day--;
            }
        }
        if (CHECK_BTN_ALL(controller1->cur.button, BTN_CRIGHT)) {
            if (gSaveContext.day < 4) {
                gSaveContext.day++;
            }
        }
        if (controller1->rel.stick_y != 0) {
            this->unk_260 = (gGameInfo->data[126] * controller1->rel.stick_y) / 7;
        } else {
            if (CHECK_BTN_ALL(controller1->press.button, BTN_DUP)) {
                if (this->unk_26C == 1) {
                    this->unk_264 = 0;
                }
                if (this->unk_264 == 0) {
                    this->unk_264 = 0x14;
                    this->unk_26C = 1;
                    play_sound(0x1800);
                    this->unk_260 = gGameInfo->data[126];
                }
            }
            if (CHECK_BTN_ALL(controller1->cur.button, BTN_DUP) && (this->unk_264 == 0)) {
                play_sound(0x1800);
                this->unk_260 = gGameInfo->data[126] * 3;
            }
            if (CHECK_BTN_ALL(controller1->press.button, BTN_DDOWN)) {
                if (1 == this->unk_270) {
                    this->unk_268 = 0;
                }
                if (this->unk_268 == 0) {
                    this->unk_268 = 0x14;
                    this->unk_270 = 1;
                    play_sound(0x1800);
                    this->unk_260 = - gGameInfo->data[126];
                }
            }
            if (CHECK_BTN_ALL(controller1->cur.button, BTN_DDOWN) && (this->unk_268 == 0)) {
                play_sound(0x1800);
                this->unk_260 = gGameInfo->data[126] * 3;
            }
            if (CHECK_BTN_ALL(controller1->press.button, BTN_DLEFT) || CHECK_BTN_ALL(controller1->cur.button, BTN_DLEFT)) {
                play_sound(0x1800);
                this->unk_260 = gGameInfo->data[126];
            }
            if (CHECK_BTN_ALL(controller1->press.button, BTN_DRIGHT) || CHECK_BTN_ALL(controller1->cur.button, BTN_DRIGHT)) {
                play_sound(0x1800);
                this->unk_260 = gGameInfo->data[126];
            }
        }
    }
    if (CHECK_BTN_ALL(controller1->press.button, BTN_L)) {
        this->unk_21C++;
        this->unk_21C = (this->unk_21C + 7) % 7;
        this->unk_24C = this->unk_220[this->unk_21C];
        this->unk_218 = this->unk_220[this->unk_21C];
    }
    this->unk_25C = this->unk_25C + this->unk_260;
    if (this->unk_25C < -7) {
        this->unk_260 = 0;
        this->unk_218++;
        this->unk_218 = (this->unk_218 + this->unk_210) % this->unk_210;
        this->unk_25C = 0;
        if (((this->unk_24C + this->unk_210 + 0x13) % this->unk_210) == this->unk_218) {
            this->unk_24C++;
            this->unk_24C = (this->unk_24C + this->unk_210) % this->unk_210;
        }
    }

    if (this->unk_25C >= 8) {
        this->unk_260 = 0;
        this->unk_25C = 0;
        if (this->unk_24C == this->unk_218) {
            this->unk_24C -= 2;
            this->unk_24C = (this->unk_24C + this->unk_210) % this->unk_210;
        }

        this->unk_218--;
        this->unk_218 = (this->unk_218 + this->unk_210) % this->unk_210;
        if (((this->unk_24C + this->unk_210) % this->unk_210) == this->unk_218) {
            this->unk_24C--;
            this->unk_24C = (this->unk_24C + this->unk_210) % this->unk_210;
        }
    }

    this->unk_218 = (this->unk_218 + this->unk_210) % this->unk_210;
    this->unk_24C = (this->unk_24C + this->unk_210) % this->unk_210;
    gGameInfo->data[2576] = this->unk_218;
    gGameInfo->data[2577] = this->unk_24C;
    gGameInfo->data[2578] = this->unk_21C;
    
    if (this->unk_264 != 0) {
        this->unk_264 = this->unk_264 - 1;
        this->unk_264 = this->unk_264 - 1;
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
#else
void func_80800A44(SelectContext* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_select/func_80800A44.s")
#endif

// Select_PrintMenu
void func_808013B8(SelectContext* this, GfxPrint* printer) {
    s32 i;

    GfxPrint_SetColor(printer, 255, 155, 150, 255);
    GfxPrint_SetPos(printer, 12, 2);
    GfxPrint_Printf(printer, "ZELDA MAP SELECT");

    GfxPrint_SetColor(printer, 255, 255, 255, 255);
    for (i = 0; i < 20; i++) {
        s32 sceneIndex;
        char* sceneName;

        GfxPrint_SetPos(printer, 9, i + 4);
        sceneIndex = (this->unk_24C + i + this->unk_210) % this->unk_210;
        if (sceneIndex == this->unk_218) {
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
    GfxPrint_Printf(printer, "OPT=%d", this->unk_248);
}

// clang-format off
const char* D_80802334[12] = {
    "\x8Dｼﾊﾞﾗｸｵﾏﾁｸﾀﾞｻｲ",
    "\x8Dﾁｮｯﾄ ﾏｯﾃﾈ",
    "\x8Cｳｪｲﾄ ｱ ﾓｰﾒﾝﾄ",
    "\x8Cﾛｰﾄﾞ\x8Dﾁｭｳ",
    "\x8Dﾅｳ ﾜｰｷﾝｸﾞ",
    "\x8Dｲﾏ ﾂｸｯﾃﾏｽ",
    "\x8Dｺｼｮｳｼﾞｬﾅｲﾖ",
    "\x8Cｺｰﾋｰ ﾌﾞﾚｲｸ",
    "\x8C" "Bﾒﾝｦｾｯﾄｼﾃｸﾀﾞｻｲ",
    "\x8Dｼﾞｯﾄ\x8Cｶﾞﾏﾝ\x8Dﾉ\x8Cｺ\x8Dﾃﾞｱｯﾀ",
    "\x8Dｲﾏｼﾊﾞﾗｸｵﾏﾁｸﾀﾞｻｲ",
    "\x8Dｱﾜﾃﾅｲｱﾜﾃﾅｲ｡ﾋﾄﾔｽﾐﾋﾄﾔｽﾐ｡",
};
// clang-format on

void func_80801594(SelectContext* this, GfxPrint* printer) {
    GfxPrint_SetPos(printer, 10, 15);
    GfxPrint_SetColor(printer, 255, 255, 255, 255);
    GfxPrint_Printf(printer, "%s", D_80802334[(s32)(Rand_ZeroOne() * ARRAY_COUNT(D_80802334))]);
}

// clang-format off
char* D_80802364[][2] = {
    {"\x8D""17(ｵﾄﾅ)",    "\x8D""17(ﾀﾞｲﾃﾂｼﾞﾝ)"},
    {"\x8C""30(ｺﾞﾛﾝ)",   "\x8C""30(ｱｲｽｸﾘｰﾑ-1)"},
    {"\x8C""78(ｿﾞｰﾗ)",   "\x8C""78(ｶﾙﾒﾝ+1)"},
    {"\x8C""12(ﾃﾞｸﾅｯﾂ)", "\x8C""12(ﾏｼﾞｪｽﾃｨｯｸ)"},
    {"\x8D""5(ｺﾄﾞﾓ)",    "\x8C""5(NTTｺﾄﾞﾓ)"},
};
// clang-format on

#ifdef NON_MATCHING
void func_80801620(SelectContext* this, GfxPrint* printer, s32 arg2) {
    s32 sp20;
    char*(*temp_a0)[2];
    s32 temp_v0;
    char*(*phi_v1)[2];
    s32 phi_v0;

    if ((arg2 >= 0) && (arg2 < 5)) {
        temp_a0 = &D_80802364[arg2];
        phi_v1 = temp_a0 + 8;
        phi_v0 = 8;
    loop_3:
        temp_v0 = phi_v0 - 8;
        phi_v0 = temp_v0;
        if (phi_v1 == 0) {
            phi_v1 += -8;
            if (temp_v0 >= 0) {
                goto loop_3;
            }
        }
        sp20 = *temp_a0;
    } else {
        sp20 = 0;
    }
    GfxPrint_SetPos(printer, 4, 0x1A);
    GfxPrint_SetColor(printer, 0xFFU, 0xFFU, 0x37U, 0xFFU);
    if (sp20 != 0) {
        GfxPrint_Printf(printer, "Age:%s", sp20);
        return;
    }

    // clang-format off
    GfxPrint_Printf(printer, "Age:" "???" "(%d)", arg2);
    // clang-format on
}
#else
void func_80801620(SelectContext* this, GfxPrint* printer, s32 arg2);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_select/func_80801620.s")
#endif

void func_808016E8(SelectContext* this, GfxPrint* printer, u16 arg2) {
    const char* phi_a2;
    const char* phi_a2_2;

    GfxPrint_SetPos(printer, 4, 25);
    GfxPrint_SetColor(printer, 255, 255, 55, 255);
    switch (arg2) {
        case 0:
            // clang-format off
            gSaveContext.time = CLOCK_TIME(12, 0); phi_a2 = "\x8Dｵﾋﾙ\x8Cｼﾞｬﾗ";
            // clang-format on
            break;

        case 0x8000:
            // clang-format off
            gSaveContext.time = CLOCK_TIME(6, 0) + 1; phi_a2 = "\x8Dｱｻ \x8Cｼﾞｬﾗ";
            // clang-format on
            break;

        case 0x8800:
            gSaveContext.time = CLOCK_TIME(18, 1);
            phi_a2 = "\x8Dﾖﾙ \x8Cｼﾞｬﾗ";
            break;

        case 0xFFF0:
            // clang-format off
            gSaveContext.time = CLOCK_TIME(12, 0); phi_a2 = "ﾃﾞﾓ00";
            // clang-format on
            break;
        case 0xFFF1:
            phi_a2 = "ﾃﾞﾓ01";
            break;
        case 0xFFF2:
            phi_a2 = "ﾃﾞﾓ02";
            break;
        case 0xFFF3:
            phi_a2 = "ﾃﾞﾓ03";
            break;
        case 0xFFF4:
            phi_a2 = "ﾃﾞﾓ04";
            break;
        case 0xFFF5:
            phi_a2 = "ﾃﾞﾓ05";
            break;
        case 0xFFF6:
            phi_a2 = "ﾃﾞﾓ06";
            break;
        case 0xFFF7:
            phi_a2 = "ﾃﾞﾓ07";
            break;
        case 0xFFF8:
            phi_a2 = "ﾃﾞﾓ08";
            break;
        case 0xFFF9:
            phi_a2 = "ﾃﾞﾓ09";
            break;
        case 0xFFFA:
            phi_a2 = "ﾃﾞﾓ0A";
            break;

        default:
            phi_a2 = "???";
            break;
    }
    gSaveContext.environmentTime = gSaveContext.time;
    GfxPrint_Printf(printer, "Stage:\x8C%s", phi_a2);

    GfxPrint_SetPos(printer, 23, 25);
    GfxPrint_SetColor(printer, 255, 255, 55, 255);

    switch (gSaveContext.day) {
        case 1:
            phi_a2_2 = "\x8Dｻｲｼｮﾉﾋ";
            break;
        case 2:
            phi_a2_2 = "\x8Dﾂｷﾞﾉﾋ";
            break;
        case 3:
            phi_a2_2 = "\x8Dｻｲｺﾞﾉﾋ";
            break;
        case 4:
            phi_a2_2 = "\x8Dｸﾘｱｰﾉﾋ";
            break;
        default:
            gSaveContext.day = 1;
            phi_a2_2 = "\x8Dｻｲｼｮﾉﾋ";
            break;
    }
    GfxPrint_Printf(printer, "Day:\x8D%s", phi_a2_2);
}

void func_8080194C(SelectContext* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;
    GfxPrint* printer;

    OPEN_DISPS(gfxCtx);

    func_8012C4C0(gfxCtx);

    printer = alloca(sizeof(GfxPrint));
    GfxPrint_Init(printer);
    GfxPrint_Open(printer, POLY_OPA_DISP);

    func_808013B8(this, printer);
    func_80801620(this, printer, ((void)0, gSaveContext.playerForm));
    func_808016E8(this, printer, ((void)0, gSaveContext.cutscene));

    POLY_OPA_DISP = GfxPrint_Close(printer);
    GfxPrint_Destroy(printer);

    CLOSE_DISPS(gfxCtx);
}

void func_808019FC(SelectContext* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;
    GfxPrint printer;

    OPEN_DISPS(gfxCtx);

    func_8012C4C0(gfxCtx);

    GfxPrint_Init(&printer);
    GfxPrint_Open(&printer, POLY_OPA_DISP);
    func_80801594(this, &printer);
    POLY_OPA_DISP = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);

    CLOSE_DISPS(gfxCtx);
}

void func_80801A64(SelectContext* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;

    func_8012CF0C(gfxCtx, 1, 1, 0, 0, 0);

    SET_FULLSCREEN_VIEWPORT(&this->view);
    View_RenderView(&this->view, 0xF);
    if (!this->state.running) {
        func_808019FC(this);
    } else {
        func_8080194C(this);
    }
}

void Select_Main(GameState* thisx) {
    SelectContext* this = (SelectContext*)thisx;

    func_80800A44(this);
    func_80801A64(this);
}

void Select_Destroy(GameState* thisx) {
    ShrinkWindow_Fini();
}

extern SceneSelectEntry D_80801C80[];

void Select_Init(GameState* thisx) {
    SelectContext* this = (SelectContext*)thisx;

    this->state.main = Select_Main;
    this->state.destroy = Select_Destroy;

    this->scenes = D_80801C80;
    this->unk_24C = 0;
    this->unk_218 = 0;
    this->unk_220[0] = 0;
    this->unk_220[1] = 0x13;
    this->unk_220[2] = 0x25;
    this->unk_220[3] = 0x33;
    this->unk_220[4] = 0x3B;
    this->unk_220[5] = 0x49;
    this->unk_220[6] = 0x5B;
    this->unk_21C = 0;
    this->unk_248 = 0;
    this->unk_210 = 0x8F;

    ShrinkWindow_Init();
    View_Init(&this->view, this->state.gfxCtx);
    this->view.flags = 0xA;
    this->unk_25C = 0;
    this->unk_260 = 0;
    this->unk_264 = 0;
    this->unk_268 = 0;
    this->unk_26C = 0;
    this->unk_270 = 0;
    this->unk_274 = 0;

    if ((dREG(80) >= 0) && (dREG(80) < this->unk_210)) {
        this->unk_218 = dREG(80);
        this->unk_24C = dREG(81);
        this->unk_21C = dREG(82);
    }

    Game_SetFramerateDivisor(&this->state, 1);
    gSaveContext.cutscene = 0;
    gSaveContext.playerForm = PLAYER_FORM_HUMAN;
    gSaveContext.linkAge = 0;
}
