#include <ultra64.h>
#include <global.h>

// Bit Flag array in which gBitFlags[n] is literally (1 << n)
u32 gBitFlags[] = {
    (1 << 0),  (1 << 1),  (1 << 2),  (1 << 3),  (1 << 4),  (1 << 5),  (1 << 6),  (1 << 7),
    (1 << 8),  (1 << 9),  (1 << 10), (1 << 11), (1 << 12), (1 << 13), (1 << 14), (1 << 15),
    (1 << 16), (1 << 17), (1 << 18), (1 << 19), (1 << 20), (1 << 21), (1 << 22), (1 << 23),
    (1 << 24), (1 << 25), (1 << 26), (1 << 27), (1 << 28), (1 << 29), (1 << 30), (1 << 31),
};

u16 gEquipMasks[] = { 0x000F, 0x00F0, 0x0F00, 0xF000 };
u16 gEquipNegMasks[] = { 0xFFF0, 0xFF0F, 0xF0FF, 0x0FFF };
u32 gUpgradeMasks[] = {
    0x00000007, 0x00000038, 0x000001C0, 0x00000E00, 0x00003000, 0x0001C000, 0x000E0000, 0x00700000,
};
u32 gUpgradeNegMasks[] = {
    0xFFFFFFF8, 0xFFFFFFC7, 0xFFFFFE3F, 0xFFFFF1FF, 0xFFFFCFFF, 0xFFFE3FFF, 0xFFF1FFFF, 0xFF8FFFFF,
};
u8 gEquipShifts[] = { 0, 4, 8, 12 };
u8 gUpgradeShifts[] = { 0, 3, 6, 9, 12, 14, 17, 20, 0, 0, 0, 30, 0, 40, 0, 50 };

u16 gUpgradeCapacities[][4] = {
    { 0, 20, 30, 40 },     // Bomb Bags
    { 0, 0, 0, 0 },        // Unused (Scale)
    { 0, 0, 0, 0 },        // Unused (Strength)
    { 99, 200, 500, 500 }, // Wallets
    { 0, 30, 40, 50 },     // Quivers
    { 0, 10, 20, 30 },     // Unused (Deku Stick)
    { 0, 20, 30, 40 },     // Unused (Deku Nut)
};

u32 gGsFlagsMask[] = { 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000 };
u32 gGsFlagsShift[] = { 0, 8, 16, 24 };

// TODO: use symbols for these icon textures once textures are properly in C
void* gItemIcons[] = {
    0x08000000, 0x08001000, 0x08002000, 0x08003000, 0x08004000, 0x08005000, 0x08006000, 0x08007000, 0x08008000,
    0x08009000, 0x0800A000, 0x0800B000, 0x0800C000, 0x0800D000, 0x0800E000, 0x0800F000, 0x08010000, 0x08011000,
    0x08012000, 0x08013000, 0x08014000, 0x08015000, 0x08016000, 0x08017000, 0x08018000, 0x08019000, 0x0801A000,
    0x0801B000, 0x0801C000, 0x0801D000, 0x0801E000, 0x0801F000, 0x08020000, 0x08021000, 0x08022000, 0x08023000,
    0x08024000, 0x08025000, 0x08026000, 0x08027000, 0x08028000, 0x08029000, 0x0802A000, 0x0802B000, 0x0802C000,
    0x0802D000, 0x0802E000, 0x0802F000, 0x08030000, 0x08031000, 0x08032000, 0x08033000, 0x08034000, 0x08035000,
    0x08036000, 0x08037000, 0x08038000, 0x08039000, 0x0803A000, 0x0803B000, 0x0803C000, 0x0803D000, 0x0803E000,
    0x0803F000, 0x08040000, 0x08041000, 0x08042000, 0x08043000, 0x08044000, 0x08045000, 0x08046000, 0x08047000,
    0x08048000, 0x08049000, 0x0804A000, 0x0804B000, 0x0804C000, 0x0804D000, 0x0804E000, 0x0804F000, 0x08050000,
    0x08051000, 0x08052000, 0x08053000, 0x08054000, 0x08055000, 0x08056000, 0x08057000, 0x08058000, 0x08059000,
    0x0805A000, 0x0805B000, 0x0805C000, 0x0805D000, 0x0805E000, 0x0805F000, 0x08060000, 0x08062000, 0x08062000,
    0x08062000, 0x08062000, 0x08062000, 0x08062000, 0x08062000, 0x08062000, 0x08062000, 0x08062000, 0x08062000,
    0x08062000, 0x08061000, 0x09000000, 0x09000900, 0x09001200, 0x08062000, 0x08062000, 0x08062000, 0x09003600,
    0x09004800, 0x09003F00, 0x09005100, 0x09005A00, 0x09006300, 0x09006C00, 0x08062180, 0x08062A80, 0x08063380,
    0x020028A0, 0x020025A0, 0x020027A0, 0x020026A0, 0x020024A0,
};

// Used to map item IDs to inventory slots
u8 gItemSlots[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12,
    0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x05, 0x05, 0x05, 0x05, 0x05, 0x0B, 0x0B, 0x11,
    0x11, 0x11, 0x1D, 0x23, 0x29, 0x2F, 0x28, 0x26, 0x19, 0x20, 0x1E, 0x2C, 0x24, 0x25, 0x18, 0x27,
    0x1C, 0x2B, 0x21, 0x2A, 0x2D, 0x1B, 0x1F, 0x1A, 0x22, 0x2E, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
};

u16 gItemPrices[] = {
    0, 0,  0,  0,  0,  0,   0,  0,  0,  0,   0, 0, 0,   0,  0, 0, 0, 0, 0, 20, 20, 20, 20, 0, 20,
    5, 20, 20, 50, 50, 200, 20, 20, 20, 200, 5, 0, 200, 20, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0, 0,
};

// Used to map scene indexes to their region in Termina
u16 gScenesPerRegion[11][27] = {
    // Great Bay
    {
        SCENE_30GYOSON,
        SCENE_LABO,
        SCENE_FISHERMAN,
        SCENE_SINKAI,
        SCENE_31MISAKI,
        SCENE_TORIDE,
        SCENE_KAIZOKU,
        SCENE_PIRATE,
        SCENE_35TAKI,
        SCENE_KINDAN2,
        -1,
    },
    // Zora Hall
    {
        SCENE_33ZORACITY,
        SCENE_BANDROOM,
        -1,
    },
    // Romani Ranch
    {
        SCENE_F01,
        SCENE_ROMANYMAE,
        SCENE_OMOYA,
        SCENE_F01C,
        SCENE_F01_B,
        SCENE_KOEPONARACE,
        -1,
    },
    // Deku Palace
    {
        SCENE_22DEKUCITY,
        SCENE_DEKU_KING,
        SCENE_26SARUNOMORI,
        SCENE_DANPEI,
        -1,
    },
    // Southern Swamp
    {
        SCENE_20SICHITAI,
        SCENE_20SICHITAI2,
        SCENE_MAP_SHOP,
        SCENE_WITCH_SHOP,
        SCENE_21MITURINMAE,
        SCENE_KINSTA1,
        -1,
    },
    // Clock Town
    {
        SCENE_00KEIKOKU,    SCENE_TENMON_DAI,   SCENE_13HUBUKINOMITI,
        SCENE_24KEMONOMITI, SCENE_SYATEKI_MORI, SCENE_IKANAMAE,
        SCENE_TOWN,         SCENE_SYATEKI_MIZU, SCENE_BOWLING,
        SCENE_TAKARAYA,     SCENE_YADOYA,       SCENE_SONCHONOIE,
        SCENE_MILK_BAR,     SCENE_ICHIBA,       SCENE_BOMYA,
        SCENE_AYASHIISHOP,  SCENE_8ITEMSHOP,    SCENE_DOUJOU,
        SCENE_POSTHOUSE,    SCENE_TAKARAKUJI,   SCENE_BACKTOWN,
        SCENE_CLOCKTOWER,   SCENE_INSIDETOWER,  SCENE_OKUJOU,
        SCENE_ALLEY,        SCENE_DEKUTES,      -1,
    },
    // Snowhead
    {
        SCENE_10YUKIYAMANOMURA,
        SCENE_10YUKIYAMANOMURA2,
        SCENE_KAJIYA,
        SCENE_12HAKUGINMAE,
        SCENE_14YUKIDAMANOMITI,
        SCENE_GORONRACE,
        SCENE_GORON_HAKA,
        SCENE_17SETUGEN,
        SCENE_17SETUGEN2,
        -1,
    },
    // Ikana Graveyard
    {
        SCENE_BOTI,
        SCENE_DANPEI2TEST,
        -1,
    },
    // Ikana Canyon
    {
        SCENE_CASTLE,
        SCENE_IKNINSIDE,
        SCENE_IKANA,
        SCENE_SECOM,
        SCENE_MUSICHOUSE,
        SCENE_RANDOM,
        SCENE_REDEAD,
        SCENE_TOUGITES,
        SCENE_HAKASHITA,
        -1,
    },
    // Goron Village
    {
        SCENE_11GORONNOSATO,
        SCENE_11GORONNOSATO2,
        SCENE_16GORON_HOUSE,
        SCENE_GORONSHOP,
        -1,
    },
    // Stone Tower
    {
        SCENE_F40,
        SCENE_F41,
        -1,
    },
};

s32 func_8012EC80(GlobalContext* globalCtx) {
    if (gSaveContext.buttonStatus[0] == BTN_DISABLED) {
        return 0xFF;
    } else if (gSaveContext.unk_1015 == 0xFF) {
        return 0xFF;
    } else if (gSaveContext.equips.buttonItems[((gSaveContext.playerForm == 4) ? 0 : gSaveContext.playerForm)][0] ==
               0xFF) {
        if (globalCtx->interfaceCtx.unk_21C != 0) {
            if (globalCtx->interfaceCtx.unk_21E != 0) {
                return globalCtx->interfaceCtx.unk_21E;
            }
        }
        return 0xFF;
    } else {
        return gSaveContext.equips.buttonItems[((gSaveContext.playerForm == 4) ? 0 : gSaveContext.playerForm)][0];
    }
}

void func_8012ED34(s16 equipment);
#pragma GLOBAL_ASM("./asm/non_matchings/code/code_0x8012EC80/func_8012ED34.asm")

u8 func_8012ED78(GlobalContext* globalCtx, s16 equipment);
#pragma GLOBAL_ASM("./asm/non_matchings/code/code_0x8012EC80/func_8012ED78.asm")

void func_8012EDE8(s16 arg0, u32 arg1);
#pragma GLOBAL_ASM("./asm/non_matchings/code/code_0x8012EC80/func_8012EDE8.asm")

s32 func_8012EE34(s16 arg0) {
    s16 num = 0;

    if (arg0 >= 0x20) {
        if (arg0 < 0x40) {
            num = 1;
        } else if (arg0 < 0x60) {
            num = 2;
        } else if (arg0 < 0x80) {
            num = 3;
        } else if (arg0 < 0xA0) {
            num = 4;
        } else if (arg0 < 0xC0) {
            num = 5;
        } else if (arg0 < 0xE0) {
            num = 6;
        }
    }

    if (gSaveContext.roomInf[125][num] & gBitFlags[arg0 - (num << 5)]) {
        return 1;
    }

    return 0;
}

/* static */ u16 D_801C2380[12][6] = {
    {
        SCENE_00KEIKOKU,
        SCENE_BOTI,
        SCENE_13HUBUKINOMITI,
        SCENE_24KEMONOMITI,
        SCENE_IKANAMAE,
        SCENE_TOWN,
    },
    {
        SCENE_ICHIBA,
        SCENE_BACKTOWN,
        SCENE_CLOCKTOWER,
        SCENE_ALLEY,
        -1,
    },
    {
        SCENE_20SICHITAI,
        SCENE_20SICHITAI2,
        SCENE_21MITURINMAE,
        SCENE_22DEKUCITY,
        SCENE_DEKU_KING,
        SCENE_KINSTA1,
    },
    { -1 },
    {
        SCENE_10YUKIYAMANOMURA,
        SCENE_10YUKIYAMANOMURA2,
        SCENE_11GORONNOSATO,
        SCENE_11GORONNOSATO2,
        SCENE_16GORON_HOUSE,
        SCENE_12HAKUGINMAE,
    },
    {
        SCENE_14YUKIDAMANOMITI,
        SCENE_GORONRACE,
        SCENE_17SETUGEN,
        SCENE_17SETUGEN2,
        -1,
    },
    {
        SCENE_F01,
        SCENE_ROMANYMAE,
        SCENE_OMOYA,
        SCENE_F01C,
        SCENE_F01_B,
        SCENE_KOEPONARACE,
    },
    { -1 },
    {
        SCENE_30GYOSON,
        SCENE_SINKAI,
        SCENE_31MISAKI,
        SCENE_TORIDE,
        SCENE_KAIZOKU,
        SCENE_33ZORACITY,
    },
    {
        SCENE_35TAKI,
        -1,
    },
    {
        SCENE_F40,
        SCENE_F41,
        SCENE_CASTLE,
        SCENE_IKANA,
        SCENE_REDEAD,
        -1,
    },
};

#ifdef NON_EQUIVALENT
// loop seems wrong?
void func_8012EF0C(s16 arg0) {
    s16 i;
    s16 num;
    s16 sceneIndex;

    if ((arg0 >= 0) && (arg0 < ARRAY_COUNT(D_801C2380))) {
        i = 0;
        num = 0;
        sceneIndex = D_801C2380[arg0][i];

        while (sceneIndex != 0xFFFF) {
            sceneIndex = D_801C2380[arg0][i];
            if (sceneIndex < 0x20) {
                num = 0;
            } else if (sceneIndex < 0x40) {
                num = 1;
            } else if (sceneIndex < 0x60) {
                num = 2;
            } else if (sceneIndex < 0x80) {
                num = 3;
            } else if (sceneIndex < 0xA0) {
                num = 4;
            } else if (sceneIndex < 0xC0) {
                num = 5;
            } else if (sceneIndex < 0xE0) {
                num = 6;
            }

            gSaveContext.roomInf[125][sceneIndex] |= gBitFlags[(-(num << 7)) + num];
            i++;
        }

        if (i == 0) {
            gSaveContext.unk_F60 |= 3;
        } else if (i == 1) {
            gSaveContext.unk_F60 |= 0x1C;
        } else if (i == 2) {
            gSaveContext.unk_F60 |= 0xE0;
        } else if (i == 3) {
            gSaveContext.unk_F60 |= 0x100;
        } else if (i == 4) {
            gSaveContext.unk_F60 |= 0x1E00;
        } else if (i == 5) {
            gSaveContext.unk_F60 |= 0x6000;
        }
    }

    dREG(82) = 0;
}
#else
void func_8012EF0C(s16 arg0);
#pragma GLOBAL_ASM("./asm/non_matchings/code/code_0x8012EC80/func_8012EF0C.asm")
#endif

void func_8012F0EC(s16 arg0);
#pragma GLOBAL_ASM("./asm/non_matchings/code/code_0x8012EC80/func_8012F0EC.asm")

#ifdef NON_MATCHING
// regalloc
void func_8012F1BC(s16 sceneIndex) {
    if (sceneIndex == SCENE_KINSTA1) {
        gSaveContext.roomInf[126][0] = ((((gSaveContext.roomInf[126][0] & 0xFFFF0000) >> 0x10) + 1) << 0x10) |
                                       (gSaveContext.roomInf[126][0] & 0xFFFF);
    } else {
        gSaveContext.roomInf[126][0] =
            ((gSaveContext.roomInf[126][0] + 1) & 0xFFFF) | (gSaveContext.roomInf[126][0] & 0xFFFF0000);
    }
}
#else
void func_8012F1BC(s16 arg0);
#pragma GLOBAL_ASM("./asm/non_matchings/code/code_0x8012EC80/func_8012F1BC.asm")
#endif

s16 func_8012F22C(s16 sceneIndex) {
    if (sceneIndex == SCENE_KINSTA1) {
        return (gSaveContext.roomInf[126][0] & 0xFFFF0000) >> 0x10;
    } else {
        return gSaveContext.roomInf[126][0] & 0xFFFF;
    }
}

void func_8012F278(GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/code/code_0x8012EC80/func_8012F278.asm")

u32 D_801C2410[] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000101, 0x01010101, 0x01010101, 0x01010101, 0x01010101,
    0x01010101, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000100, 0x00000000, 0x00000000, 0x00000101, 0x01000000, 0x01010101, 0x01010101, 0x01010101,
    0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x01000000, 0x00000000, 0x00000000, 0x00010100, 0x00000101, 0x01010101,
    0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000100, 0x00000000, 0x00000001, 0x00000001, 0x01000000,
    0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x01010101, 0x01010101, 0x01010101,
    0x00010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101,
    0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
