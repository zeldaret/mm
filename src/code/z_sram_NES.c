#include "global.h"
#include "overlays/gamestates/ovl_file_choose/z_file_choose.h"

void func_80146EBC(SramContext* sramCtx, s32 curPage, s32 numPages);
void func_80147314(SramContext* sramCtx, s32 fileNum);
void func_80147414(SramContext* sramCtx, s32 fileNum, s32 arg2);

#define CHECK_NEWF(newf)                                                                                 \
    ((newf)[0] != 'Z' || (newf)[1] != 'E' || (newf)[2] != 'L' || (newf)[3] != 'D' || (newf)[4] != 'A' || \
     (newf)[5] != '3')

// default scene flags (?)
// indices of subarray:
// - 0: switch0
// - 1: switch1
// - 2: chest
// - 3: collectible
u32 D_801C5FC0[SCENE_MAX][4] = {
    { 0xC00, 0, 0, 0x40000000 },    // SCENE_20SICHITAI2
    { 0, 0, 0, 0 },                 // SCENE_UNSET_1
    { 0, 0, 0, 0 },                 // SCENE_UNSET_2
    { 0, 0, 0, 0 },                 // SCENE_UNSET_3
    { 0, 0, 0, 0 },                 // SCENE_UNSET_4
    { 0, 0, 0, 0 },                 // SCENE_UNSET_5
    { 0, 0, 0, 0 },                 // SCENE_UNSET_6
    { 0, 0, 0, 0xC04 },             // SCENE_KAKUSIANA
    { 0, 0, 0, 0 },                 // SCENE_SPOT00
    { 0, 0, 0, 0 },                 // SCENE_UNSET_9
    { 0, 0, 0, 0 },                 // SCENE_WITCH_SHOP
    { 0, 0, 0, 0x80000000 },        // SCENE_LAST_BS
    { 0, 0, 0, 0x80000000 },        // SCENE_HAKASHITA
    { 0, 0, 0, 0 },                 // SCENE_AYASHIISHOP
    { 0, 0, 0, 0 },                 // SCENE_UNSET_E
    { 0, 0, 0, 0 },                 // SCENE_UNSET_F
    { 0, 0, 0, 0 },                 // SCENE_OMOYA
    { 0, 0, 0, 0 },                 // SCENE_BOWLING
    { 0, 0, 0, 0 },                 // SCENE_SONCHONOIE
    { 0x100000, 0, 0, 0x40000002 }, // SCENE_IKANA
    { 0, 0, 0, 0 },                 // SCENE_KAIZOKU
    { 0, 0, 0, 0 },                 // SCENE_MILK_BAR
    { 0x4000000, 0, 0, 0 },         // SCENE_INISIE_N
    { 2, 0, 0, 0 },                 // SCENE_TAKARAYA
    { 0x4000000, 0, 0, 0 },         // SCENE_INISIE_R
    { 0, 0, 0, 0 },                 // SCENE_OKUJOU
    { 0xF, 0, 0, 0 },               // SCENE_OPENINGDAN
    { 0x70B000, 0, 0, 0 },          // SCENE_MITURIN
    { 0, 0, 0, 0 },                 // SCENE_13HUBUKINOMITI
    { 0, 0x80000000, 0, 0x400 },    // SCENE_CASTLE
    { 0, 0, 0, 0 },                 // SCENE_DEKUTES
    { 0, 0, 0, 0x80000000 },        // SCENE_MITURIN_BS
    { 0, 0, 0, 0 },                 // SCENE_SYATEKI_MIZU
    { 0x1A00020, 0, 0, 0 },         // SCENE_HAKUGIN
    { 0x400, 0, 0, 0 },             // SCENE_ROMANYMAE
    { 0, 0, 0, 0x1000 },            // SCENE_PIRATE
    { 0, 0, 0, 0 },                 // SCENE_SYATEKI_MORI
    { 0, 0, 0, 2 },                 // SCENE_SINKAI
    { 0x400, 0, 0, 0 },             // SCENE_YOUSEI_IZUMI
    { 0, 0, 0, 0 },                 // SCENE_KINSTA1
    { 0, 0, 0, 0x80000000 },        // SCENE_KINDAN2
    { 0, 0, 0, 0 },                 // SCENE_TENMON_DAI
    { 0, 0, 0, 2 },                 // SCENE_LAST_DEKU
    { 0, 0, 0, 0x40000000 },        // SCENE_22DEKUCITY
    { 0, 0, 0, 0 },                 // SCENE_KAJIYA
    { 0x10, 0, 0, 0 },              // SCENE_00KEIKOKU
    { 3, 0, 0, 0 },                 // SCENE_POSTHOUSE
    { 0, 0, 0, 0 },                 // SCENE_LABO
    { 0, 0, 0, 0x80000000 },        // SCENE_DANPEI2TEST
    { 0, 0, 0, 0 },                 // SCENE_UNSET_31
    { 0, 0, 0, 0 },                 // SCENE_16GORON_HOUSE
    { 0, 0, 0, 0 },                 // SCENE_33ZORACITY
    { 0, 0, 0, 0 },                 // SCENE_8ITEMSHOP
    { 0, 0, 0, 0 },                 // SCENE_F01
    { 0, 0, 0, 0x80000000 },        // SCENE_INISIE_BS
    { 0x100400, 0, 0, 0x22 },       // SCENE_30GYOSON
    { 0x400, 0, 0, 0x80 },          // SCENE_31MISAKI
    { 0, 0, 0, 0 },                 // SCENE_TAKARAKUJI
    { 0, 0, 0, 0 },                 // SCENE_UNSET_3A
    { 0x400, 0, 0, 0 },             // SCENE_TORIDE
    { 0, 0, 0, 0 },                 // SCENE_FISHERMAN
    { 0, 0, 0, 0 },                 // SCENE_GORONSHOP
    { 0, 0, 0, 0 },                 // SCENE_DEKU_KING
    { 0, 0, 0, 2 },                 // SCENE_LAST_GORON
    { 0, 0, 0, 0x80000002 },        // SCENE_24KEMONOMITI
    { 0, 0, 0, 0 },                 // SCENE_F01_B
    { 0, 0, 0, 0 },                 // SCENE_F01C
    { 0, 0, 0, 0 },                 // SCENE_BOTI
    { 0, 0, 0, 0x80000000 },        // SCENE_HAKUGIN_BS
    { 0xC00, 0, 0, 0x40000000 },    // SCENE_20SICHITAI
    { 0x102, 0, 0, 0x400 },         // SCENE_21MITURINMAE
    { 0, 0, 0, 2 },                 // SCENE_LAST_ZORA
    { 0, 0, 0, 0x40000000 },        // SCENE_11GORONNOSATO2
    { 0x70, 0, 0, 0 },              // SCENE_SEA
    { 0, 0, 0, 0 },                 // SCENE_35TAKI
    { 0, 0, 0, 0 },                 // SCENE_REDEAD
    { 0, 0, 0, 0x40000000 },        // SCENE_BANDROOM
    { 0, 0, 0, 0x40000000 },        // SCENE_11GORONNOSATO
    { 0, 0, 0, 0 },                 // SCENE_GORON_HAKA
    { 0, 0, 0, 0 },                 // SCENE_SECOM
    { 0x100000, 0, 0, 0x80000000 }, // SCENE_10YUKIYAMANOMURA
    { 0, 0, 0, 0 },                 // SCENE_TOUGITES
    { 0, 0, 0, 0 },                 // SCENE_DANPEI
    { 0, 0, 0, 0 },                 // SCENE_IKANAMAE
    { 0, 0, 0, 0 },                 // SCENE_DOUJOU
    { 0, 0, 0, 0 },                 // SCENE_MUSICHOUSE
    { 0, 0, 0, 0 },                 // SCENE_IKNINSIDE
    { 0, 0, 0, 0 },                 // SCENE_MAP_SHOP
    { 0x400, 0, 0, 0 },             // SCENE_F40
    { 0x400, 0, 0, 0 },             // SCENE_F41
    { 0x100000, 0, 0, 0x80000000 }, // SCENE_10YUKIYAMANOMURA2
    { 0, 0, 0, 0x100 },             // SCENE_14YUKIDAMANOMITI
    { 0x400, 0, 0, 0 },             // SCENE_12HAKUGINMAE
    { 0, 0, 0, 0x80 },              // SCENE_17SETUGEN
    { 0, 0, 0, 0x80 },              // SCENE_17SETUGEN2
    { 0, 0, 0, 0x80000000 },        // SCENE_SEA_BS
    { 0, 0, 0, 0x400 },             // SCENE_RANDOM
    { 0, 0, 0, 0 },                 // SCENE_YADOYA
    { 0, 0, 0, 0 },                 // SCENE_KONPEKI_ENT
    { 1, 0, 0, 0 },                 // SCENE_INSIDETOWER
    { 0, 0, 0, 0 },                 // SCENE_26SARUNOMORI
    { 0, 0, 0, 0 },                 // SCENE_LOST_WOODS
    { 0, 0, 0, 2 },                 // SCENE_LAST_LINK
    { 0, 0, 0, 0 },                 // SCENE_SOUGEN
    { 0, 0, 0, 0 },                 // SCENE_BOMYA
    { 0, 0, 0, 0 },                 // SCENE_KYOJINNOMA
    { 0, 0, 0, 0 },                 // SCENE_KOEPONARACE
    { 0, 0, 0, 0 },                 // SCENE_GORONRACE
    { 1, 0, 0, 0 },                 // SCENE_TOWN
    { 0, 0, 0, 0 },                 // SCENE_ICHIBA
    { 0, 0, 0, 0x400 },             // SCENE_BACKTOWN
    { 0x100000, 0, 0, 0x400 },      // SCENE_CLOCKTOWER
    { 0, 0, 1, 0 },                 // SCENE_ALLEY
};

// TODO: figure out a way to use the WEEKEVENTREG defines here
// weekEventReg flags which will be not be cleared on a cycle reset
u16 D_801C66D0[ARRAY_COUNT(gSaveContext.save.weekEventReg)] = {
    /*  0 */ 0xFFFC,
    /*  1 */ 0xFFFF,
    /*  2 */ 0xFFFF,
    /*  3 */ 0xFFFF,
    /*  4 */ 0,
    /*  5 */ 0,
    /*  6 */ 0,
    /*  7 */ 0xC000,
    /*  8 */ 0xC00,
    /*  9 */ 0,
    /* 10 */ 0xC0,
    /* 11 */ 0,
    /* 12 */ 0x300,
    /* 13 */ 0x3000,
    /* 14 */ 0xC000,
    /* 15 */ 0xC00,
    /* 16 */ 0,
    /* 17 */ 0,
    /* 18 */ 0,
    /* 19 */ 0,
    /* 20 */ 0,
    /* 21 */ 0,
    /* 22 */ 0xC00C,
    /* 23 */ 0xC00C,
    /* 24 */ 0xC008,
    /* 25 */ 3,
    /* 26 */ 0x3000,
    /* 27 */ 0,
    /* 28 */ 0,
    /* 29 */ 0,
    /* 30 */ 0xFF00,
    /* 31 */ 0xC3F,
    /* 32 */ 0x3F,
    /* 33 */ 0,
    /* 34 */ 0,
    /* 35 */ 0xCFFF,
    /* 36 */ 0,
    /* 37 */ 0,
    /* 38 */ 0xC00,
    /* 39 */ 0xC00,
    /* 40 */ 0,
    /* 41 */ 0xC0,
    /* 42 */ 0,
    /* 43 */ 0,
    /* 44 */ 0,
    /* 45 */ 0,
    /* 46 */ 0,
    /* 47 */ 0,
    /* 48 */ 0,
    /* 49 */ 0,
    /* 50 */ 0x3C,
    /* 51 */ 0x20,
    /* 52 */ 0,
    /* 53 */ 0x300C,
    /* 54 */ 0x3000,
    /* 55 */ 0,
    /* 56 */ 0xC,
    /* 57 */ 0xC0,
    /* 58 */ 0,
    /* 59 */ 0xFF0,
    /* 60 */ 0x300,
    /* 61 */ 0,
    /* 62 */ 0,
    /* 63 */ 0xC00,
    /* 64 */ 0,
    /* 65 */ 0,
    /* 66 */ 0xFFFF,
    /* 67 */ 0xFFFF,
    /* 68 */ 0xFFFF,
    /* 69 */ 0xFFFF,
    /* 70 */ 0xFFFF,
    /* 71 */ 0xFFFF,
    /* 72 */ 0xFFFF,
    /* 73 */ 0xC0,
    /* 74 */ 0,
    /* 75 */ 0xC000,
    /* 76 */ 0,
    /* 77 */ 3,
    /* 78 */ 0,
    /* 79 */ 0xC000,
    /* 80 */ 0,
    /* 81 */ 0xC0,
    /* 82 */ 0x300,
    /* 83 */ 0,
    /* 84 */ 0,
    /* 85 */ 0,
    /* 86 */ 0xC000,
    /* 87 */ 0xFFF0,
    /* 88 */ 0,
    /* 89 */ 0,
    /* 90 */ 0x300,
    /* 91 */ 0,
    /* 92 */ 0xC000,
    /* 93 */ 0xF0,
    /* 94 */ 0,
    /* 95 */ 0,
    /* 96 */ 0,
    /* 97 */ 0,
    /* 98 */ 0,
    /* 99 */ 0,
};

// used in other files
s32 D_801C6798[] = {
    0x00000020, 0x00001470, 0x000028C0, 0x00003D10, 0x00005160, 0x000065B0,
};

u8 gAmmoItems[] = {
    ITEM_NONE,        // SLOT_OCARINA
    ITEM_BOW,         // SLOT_BOW
    ITEM_NONE,        // SLOT_ARROW_FIRE
    ITEM_NONE,        // SLOT_ARROW_ICE
    ITEM_NONE,        // SLOT_ARROW_LIGHT
    ITEM_NONE,        // SLOT_TRADE_DEED
    ITEM_BOMB,        // SLOT_BOMB
    ITEM_BOMBCHU,     // SLOT_BOMBCHU
    ITEM_STICK,       // SLOT_STICK
    ITEM_NUT,         // SLOT_NUT
    ITEM_MAGIC_BEANS, // SLOT_MAGIC_BEANS
    ITEM_NONE,        // SLOT_TRADE_KEY_MAMA
    ITEM_POWDER_KEG,  // SLOT_POWDER_KEG
    ITEM_PICTO_BOX,   // SLOT_PICTO_BOX
    ITEM_NONE,        // SLOT_LENS
    ITEM_NONE,        // SLOT_HOOKSHOT
    ITEM_NONE,        // SLOT_SWORD_GREAT_FAIRY
    ITEM_NONE,        // SLOT_TRADE_COUPLE
    ITEM_NONE,        // SLOT_BOTTLE_1
    ITEM_NONE,        // SLOT_BOTTLE_2
    ITEM_NONE,        // SLOT_BOTTLE_3
    ITEM_NONE,        // SLOT_BOTTLE_4
    ITEM_NONE,        // SLOT_BOTTLE_5
    ITEM_NONE,        // SLOT_BOTTLE_6
};

s32 D_801C67C8[] = { 0, 0x40, 0x80, 0xC0, 0x100, 0x180, 0x200, 0x280 };

s32 D_801C67E8[] = { 0x300, 0x380 };

s32 D_801C67F0[] = { 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80 };

s32 D_801C6810[] = { 1, 1 };

s32 D_801C6818[] = { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 };

s32 D_801C6838[] = { 1, 1 };

s32 D_801C6840[] = { 0x100, 0x180, 0x200, 0x280 };

s32 D_801C6850[] = { 0x80, 0x80, 0x80, 0x80, 0x300, 0x380, 1, 1 };

s32 D_801C6870[] = {
    sizeof(Save),
    sizeof(Save),
    sizeof(Save),
    sizeof(Save),
    offsetof(SaveContext, fileNum),
    offsetof(SaveContext, fileNum),
    offsetof(SaveContext, fileNum),
    offsetof(SaveContext, fileNum),
};

u8 D_801C6890[8] = { 1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80 };

u16 D_801F6AF0;
u8 D_801F6AF2;

void Sram_ActivateOwl(u8 owlId) {
    gSaveContext.save.playerData.owlActivationFlags =
        ((void)0, gSaveContext.save.playerData.owlActivationFlags) | (u16)gBitFlags[owlId];

    if (gSaveContext.save.playerData.unk_20 == 0xFF) {
        gSaveContext.save.playerData.unk_20 = owlId;
    }
}

void Sram_ClearHighscores(void) {
    gSaveContext.save.unk_EE8 = (gSaveContext.save.unk_EE8 & 0xFFFF) | 0x130000;
    gSaveContext.save.unk_EE8 = (gSaveContext.save.unk_EE8 & 0xFFFF0000) | 0xA;
    gSaveContext.save.horseBackBalloonHighScore = SECONDS_TO_TIMER(60);
    SET_TOWN_SHOOTING_GALLERY_HIGH_SCORE(39);
    SET_SWAMP_SHOOTING_GALLERY_HIGH_SCORE(10);

    gSaveContext.save.dekuPlaygroundHighScores[0] = SECONDS_TO_TIMER(75);
    gSaveContext.save.dekuPlaygroundHighScores[1] = SECONDS_TO_TIMER(75);
    gSaveContext.save.dekuPlaygroundHighScores[2] = SECONDS_TO_TIMER(76);
}

/**
 * Clears specific weekEventReg flags. Used by the "Dawn of the First Day" message
 */
void Sram_ClearFlagsAtDawnOfTheFirstDay(void) {
    CLEAR_WEEKEVENTREG(WEEKEVENTREG_55_02);
    CLEAR_WEEKEVENTREG(WEEKEVENTREG_90_01);
    CLEAR_WEEKEVENTREG(WEEKEVENTREG_89_40);
    CLEAR_WEEKEVENTREG(WEEKEVENTREG_89_08);
    CLEAR_WEEKEVENTREG(WEEKEVENTREG_85_80);
}

/**
 * Used by Song of Time (when clicking "Yes") and (indirectly) by the "Dawn of the New Day" cutscene
 */
void Sram_SaveEndOfCycle(PlayState* play) {
    s16 sceneId;
    s32 j;
    s32 i;
    u8 slot;
    u8 item;

    gSaveContext.save.timeSpeedOffset = 0;
    gSaveContext.save.daysElapsed = 0;
    gSaveContext.save.day = 0;
    gSaveContext.save.time = CLOCK_TIME(6, 0) - 1;

    gSaveContext.save.playerData.deaths++;
    if (gSaveContext.save.playerData.deaths > 999) {
        gSaveContext.save.playerData.deaths = 999;
    }

    sceneId = Play_GetOriginalSceneId(play->sceneId);
    Play_SaveCycleSceneFlags(&play->state);

    play->actorCtx.sceneFlags.chest &= D_801C5FC0[sceneId][2];
    play->actorCtx.sceneFlags.switches[0] &= D_801C5FC0[sceneId][0];
    play->actorCtx.sceneFlags.switches[1] &= D_801C5FC0[sceneId][1];
    play->actorCtx.sceneFlags.collectible[0] &= D_801C5FC0[sceneId][3];
    play->actorCtx.sceneFlags.clearedRoom = 0;

    for (i = 0; i < SCENE_MAX; i++) {
        gSaveContext.cycleSceneFlags[i].switch0 = ((void)0, gSaveContext.cycleSceneFlags[i].switch0) & D_801C5FC0[i][0];
        gSaveContext.cycleSceneFlags[i].switch1 = ((void)0, gSaveContext.cycleSceneFlags[i].switch1) & D_801C5FC0[i][1];
        gSaveContext.cycleSceneFlags[i].chest = ((void)0, gSaveContext.cycleSceneFlags[i].chest) & D_801C5FC0[i][2];
        gSaveContext.cycleSceneFlags[i].collectible =
            ((void)0, gSaveContext.cycleSceneFlags[i].collectible) & D_801C5FC0[i][3];
        gSaveContext.cycleSceneFlags[i].clearedRoom = 0;
        gSaveContext.save.permanentSceneFlags[i].unk_14 = 0;
        gSaveContext.save.permanentSceneFlags[i].rooms = 0;
    }

    for (; i < ARRAY_COUNT(gSaveContext.cycleSceneFlags); i++) {
        gSaveContext.cycleSceneFlags[i].chest = 0;
        gSaveContext.cycleSceneFlags[i].switch0 = 0;
        gSaveContext.cycleSceneFlags[i].switch1 = 0;
        gSaveContext.cycleSceneFlags[i].clearedRoom = 0;
        gSaveContext.cycleSceneFlags[i].collectible = 0;
    }

    for (i = 0; i < ARRAY_COUNT(gSaveContext.masksGivenOnMoon); i++) {
        gSaveContext.masksGivenOnMoon[i] = 0;
    }

    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_84_20)) {
        Inventory_DeleteItem(ITEM_MASK_FIERCE_DEITY, SLOT(ITEM_MASK_FIERCE_DEITY));
    }

    for (i = 0; i < ARRAY_COUNT(D_801C66D0); i++) {
        u16 phi_v1_3 = D_801C66D0[i];

        for (j = 0; j < ARRAY_COUNT(D_801C6890); j++) {
            if ((phi_v1_3 & 3) == 0) {
                gSaveContext.save.weekEventReg[i] =
                    ((void)0, gSaveContext.save.weekEventReg[i]) & (0xFF ^ D_801C6890[j]);
            }
            phi_v1_3 >>= 2;
        }
    }

    for (i = 0; i < ARRAY_COUNT(gSaveContext.eventInf); i++) {
        gSaveContext.eventInf[i] = 0;
    }

    CLEAR_EVENTINF(EVENTINF_70);
    CLEAR_EVENTINF(EVENTINF_71);
    CLEAR_EVENTINF(EVENTINF_72);
    CLEAR_EVENTINF(EVENTINF_73);
    CLEAR_EVENTINF(EVENTINF_74);

    if (gSaveContext.save.playerData.rupees != 0) {
        SET_EVENTINF(EVENTINF_70);
    }

    if (INV_CONTENT(ITEM_BOMB) == ITEM_BOMB) {
        item = INV_CONTENT(ITEM_BOMB);
        if (AMMO(item) != 0) {
            SET_EVENTINF(EVENTINF_71);
        }
    }
    if (INV_CONTENT(ITEM_NUT) == ITEM_NUT) {
        item = INV_CONTENT(ITEM_NUT);
        if (AMMO(item) != 0) {
            SET_EVENTINF(EVENTINF_72);
        }
    }
    if (INV_CONTENT(ITEM_STICK) == ITEM_STICK) {
        item = INV_CONTENT(ITEM_STICK);
        if (AMMO(item) != 0) {
            SET_EVENTINF(EVENTINF_73);
        }
    }
    if (INV_CONTENT(ITEM_BOW) == ITEM_BOW) {
        item = INV_CONTENT(ITEM_BOW);
        if (AMMO(item) != 0) {
            SET_EVENTINF(EVENTINF_74);
        }
    }

    for (i = 0; i < ARRAY_COUNT(gAmmoItems); i++) {
        if (gAmmoItems[i] != ITEM_NONE) {
            if ((gSaveContext.save.inventory.items[i] != ITEM_NONE) && (i != SLOT_PICTO_BOX)) {
                item = gSaveContext.save.inventory.items[i];
                AMMO(item) = 0;
            }
        }
    }

    for (i = SLOT_BOTTLE_1; i <= SLOT_BOTTLE_6; i++) {
        // Check for all bottled items
        if (gSaveContext.save.inventory.items[i] >= ITEM_POTION_RED) {
            if (gSaveContext.save.inventory.items[i] <= ITEM_OBABA_DRINK) {
                for (j = EQUIP_SLOT_C_LEFT; j <= EQUIP_SLOT_C_RIGHT; j++) {
                    if (GET_CUR_FORM_BTN_ITEM(j) == gSaveContext.save.inventory.items[i]) {
                        SET_CUR_FORM_BTN_ITEM(j, ITEM_BOTTLE);
                        Interface_LoadItemIconImpl(play, j);
                    }
                }
                gSaveContext.save.inventory.items[i] = ITEM_BOTTLE;
            }
        }
    }

    REMOVE_QUEST_ITEM(QUEST_PICTOGRAPH);

    if (gSaveContext.save.playerData.health < 0x30) {
        gSaveContext.save.playerData.health = 0x30;
    }

    if (GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD) <= EQUIP_VALUE_SWORD_RAZOR) {
        SET_EQUIP_VALUE(EQUIP_TYPE_SWORD, EQUIP_VALUE_SWORD_KOKIRI);

        if (CUR_FORM == 0) {
            if ((STOLEN_ITEM_1 >= ITEM_SWORD_GILDED) || (STOLEN_ITEM_2 >= ITEM_SWORD_GILDED)) {
                BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = ITEM_SWORD_GILDED;
                SET_EQUIP_VALUE(EQUIP_TYPE_SWORD, EQUIP_VALUE_SWORD_GILDED);
            } else {
                BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = ITEM_SWORD_KOKIRI;
            }
        } else {
            if ((STOLEN_ITEM_1 >= ITEM_SWORD_GILDED) || (STOLEN_ITEM_2 >= ITEM_SWORD_GILDED)) {
                BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B) = ITEM_SWORD_GILDED;
                SET_EQUIP_VALUE(EQUIP_TYPE_SWORD, EQUIP_VALUE_SWORD_GILDED);
            } else {
                BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B) = ITEM_SWORD_KOKIRI;
            }
        }
    }

    if ((STOLEN_ITEM_1 == ITEM_SWORD_GREAT_FAIRY) || (STOLEN_ITEM_2 == ITEM_SWORD_GREAT_FAIRY)) {
        INV_CONTENT(ITEM_SWORD_GREAT_FAIRY) = ITEM_SWORD_GREAT_FAIRY;
    }

    if (STOLEN_ITEM_1 == ITEM_BOTTLE) {
        slot = SLOT(ITEM_BOTTLE);
        for (i = BOTTLE_FIRST; i < BOTTLE_MAX; i++) {
            if (gSaveContext.save.inventory.items[slot + i] == ITEM_NONE) {
                gSaveContext.save.inventory.items[slot + i] = ITEM_BOTTLE;
                break;
            }
        }
    }

    if (STOLEN_ITEM_2 == ITEM_BOTTLE) {
        slot = SLOT(ITEM_BOTTLE);
        for (i = BOTTLE_FIRST; i < BOTTLE_MAX; i++) {
            if (gSaveContext.save.inventory.items[slot + i] == ITEM_NONE) {
                gSaveContext.save.inventory.items[slot + i] = ITEM_BOTTLE;
                break;
            }
        }
    }

    SET_STOLEN_ITEM_1(STOLEN_ITEM_NONE);
    SET_STOLEN_ITEM_2(STOLEN_ITEM_NONE);

    Inventory_DeleteItem(ITEM_OCARINA_FAIRY, SLOT_TRADE_DEED);
    Inventory_DeleteItem(ITEM_SLINGSHOT, SLOT_TRADE_KEY_MAMA);
    Inventory_DeleteItem(ITEM_LONGSHOT, SLOT_TRADE_COUPLE);

    for (j = EQUIP_SLOT_C_LEFT; j <= EQUIP_SLOT_C_RIGHT; j++) {
        if (GET_CUR_FORM_BTN_ITEM(j) >= ITEM_MOON_TEAR && GET_CUR_FORM_BTN_ITEM(j) <= ITEM_PENDANT_OF_MEMORIES) {
            SET_CUR_FORM_BTN_ITEM(j, ITEM_NONE);
            Interface_LoadItemIconImpl(play, j);
        }
    }

    gSaveContext.save.skullTokenCount &= ~0xFFFF0000;
    gSaveContext.save.skullTokenCount &= ~0x0000FFFF;
    gSaveContext.save.unk_EC4 = 0;

    gSaveContext.save.unk_E88[0] = 0;
    gSaveContext.save.unk_E88[1] = 0;
    gSaveContext.save.unk_E88[2] = 0;
    gSaveContext.save.unk_E88[3] = 0;
    gSaveContext.save.unk_E88[4] = 0;
    gSaveContext.save.unk_E88[5] = 0;
    gSaveContext.save.unk_E88[6] = 0;

    Sram_ClearHighscores();

    for (i = 0; i < 8; i++) {
        gSaveContext.save.inventory.dungeonItems[i] &= (u8)~1; // remove boss key
        DUNGEON_KEY_COUNT(i) = 0;
        gSaveContext.save.inventory.strayFairies[i] = 0;
    }

    gSaveContext.save.playerData.rupees = 0;
    gSaveContext.save.unk_F65 = 0;
    gSaveContext.powderKegTimer = 0;
    gSaveContext.unk_1014 = 0;
    gSaveContext.jinxTimer = 0;
    gSaveContext.rupeeAccumulator = 0;

    func_800F3B2C(play);
}

void Sram_IncrementDay(void) {
    if (CURRENT_DAY <= 3) {
        gSaveContext.save.day++;
        gSaveContext.save.daysElapsed++;
    }

    gSaveContext.save.bombersCaughtNum = 0;
    gSaveContext.save.bombersCaughtOrder[0] = 0;
    gSaveContext.save.bombersCaughtOrder[1] = 0;
    gSaveContext.save.bombersCaughtOrder[2] = 0;
    gSaveContext.save.bombersCaughtOrder[3] = 0;
    gSaveContext.save.bombersCaughtOrder[4] = 0;

    CLEAR_WEEKEVENTREG(WEEKEVENTREG_73_10);
    CLEAR_WEEKEVENTREG(WEEKEVENTREG_85_02);
}

u16 Sram_CalcChecksum(void* data, size_t count) {
    u8* dataPtr = data;
    u16 chkSum = 0;

    while (count-- > 0) {
        chkSum += *dataPtr;
        dataPtr++;
    }
    return chkSum;
}

// Resets `Save` substruct
void Sram_ResetSave(void) {
    gSaveContext.save.entrance = ENTRANCE(CUTSCENE, 0);
    gSaveContext.save.equippedMask = 0;
    gSaveContext.save.isFirstCycle = false;
    gSaveContext.save.unk_06 = 0;
    gSaveContext.save.linkAge = 0;
    gSaveContext.save.isNight = false;
    gSaveContext.save.timeSpeedOffset = 0;
    gSaveContext.save.snowheadCleared = 0;
    gSaveContext.save.hasTatl = false;
    gSaveContext.save.isOwlSave = false;

    // Instead of bloating all save context accesses with an extra sub-struct, the size of the would-be sub-struct
    // is calculated manually
    bzero(&gSaveContext.save.playerData, sizeof(Save) - offsetof(Save, playerData));
}

/**
 * Initializes with random values the following fields:
 * - lotteryCodes
 * - spiderHouseMaskOrder
 * - bomberCode
 */
void Sram_GenerateRandomSaveFields(void) {
    s32 randBombers;
    s16 sp2A;
    s16 pad;
    s16 i;
    s16 j;
    s32 k;
    s16 randSpiderHouse;

    Sram_ClearHighscores();

    gSaveContext.save.lotteryCodes[0][0] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[0][1] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[0][2] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[1][0] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[1][1] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[1][2] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[2][0] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[2][1] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[2][2] = Rand_S16Offset(0, 10);

    // Needed to match...
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {}
    }

    i = 0;
    sp2A = Rand_S16Offset(0, 16) & 3;
    k = 6;
    while (i != k) {
        randSpiderHouse = Rand_S16Offset(0, 16) & 3;
        if (sp2A != randSpiderHouse) {
            gSaveContext.save.spiderHouseMaskOrder[i] = randSpiderHouse;
            i++;
            sp2A = randSpiderHouse;
        }
    }

    do {
        randBombers = Rand_S16Offset(0, 6);
    } while (randBombers <= 0 || randBombers >= 6);

    gSaveContext.save.bomberCode[0] = randBombers;

    i = 1;
    while (i != 5) {
        k = false;

        do {
            randBombers = Rand_S16Offset(0, 6);
        } while (randBombers <= 0 || randBombers >= 6);

        sp2A = 0;
        do {
            if (randBombers == gSaveContext.save.bomberCode[sp2A]) {
                k = true;
            }
            sp2A++;
        } while (sp2A < i);

        if (k == false) {
            gSaveContext.save.bomberCode[i] = randBombers;
            i++;
        }
    }
}

SavePlayerData sSaveDefaultPlayerData = {
    { '\0', '\0', '\0', '\0', '\0', '\0' },             // newf
    0,                                                  // deaths
    { 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E }, // playerName "        "
    0x30,                                               // healthCapacity
    0x30,                                               // health
    0,                                                  // magicLevel
    MAGIC_NORMAL_METER,                                 // magic
    0,                                                  // rupees
    0,                                                  // swordHealth
    0,                                                  // tatlTimer
    false,                                              // isMagicAcquired
    false,                                              // isDoubleMagicAcquired
    0,                                                  // doubleDefense
    0,                                                  // unk_1F
    0xFF,                                               // unk_20
    0x0000,                                             // owlActivationFlags
    0xFF,                                               // unk_24
    SCENE_SPOT00,                                       // savedSceneId
};

ItemEquips sSaveDefaultItemEquips = {
    {
        { ITEM_SWORD_KOKIRI, ITEM_NONE, ITEM_NONE, ITEM_NONE },
        { ITEM_SWORD_KOKIRI, ITEM_NONE, ITEM_NONE, ITEM_NONE },
        { ITEM_SWORD_KOKIRI, ITEM_NONE, ITEM_NONE, ITEM_NONE },
        { ITEM_FD, ITEM_NONE, ITEM_NONE, ITEM_NONE },
    },
    {
        { SLOT_OCARINA, SLOT_NONE, SLOT_NONE, SLOT_NONE },
        { SLOT_NONE, SLOT_NONE, SLOT_NONE, SLOT_NONE },
        { SLOT_NONE, SLOT_NONE, SLOT_NONE, SLOT_NONE },
        { SLOT_NONE, SLOT_NONE, SLOT_NONE, SLOT_NONE },
    },
    0x11,
};

Inventory sSaveDefaultInventory = {
    // items
    {
        ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE,
        ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE,
        ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE,
        ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE,
        ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE, ITEM_NONE,
    },
    // ammo
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    // upgrades
    0x120000,
    // questItems
    0,
    // dungeonItems
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    // dungeonKeys
    { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
    // defenseHearts
    0,
    // strayFairies
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    // dekuPlaygroundPlayerName
    {
        // "LINK    "
        { 0x15, 0x12, 0x17, 0x14, 0x3E, 0x3E, 0x3E, 0x3E },
        // "LINK    "
        { 0x15, 0x12, 0x17, 0x14, 0x3E, 0x3E, 0x3E, 0x3E },
        // "LINK    "
        { 0x15, 0x12, 0x17, 0x14, 0x3E, 0x3E, 0x3E, 0x3E },
    },
};

u16 sSaveDefaultChecksum = 0;

/**
 *  Initialize new save.
 *  This save has an empty inventory with 3 hearts, sword and shield.
 */
void Sram_InitNewSave(void) {
    gSaveContext.save.playerForm = PLAYER_FORM_HUMAN;
    gSaveContext.save.daysElapsed = 0;
    gSaveContext.save.day = 0;
    gSaveContext.save.time = CLOCK_TIME(6, 0) - 1;
    Sram_ResetSave();

    Lib_MemCpy(&gSaveContext.save.playerData, &sSaveDefaultPlayerData, sizeof(SavePlayerData));
    Lib_MemCpy(&gSaveContext.save.equips, &sSaveDefaultItemEquips, sizeof(ItemEquips));
    Lib_MemCpy(&gSaveContext.save.inventory, &sSaveDefaultInventory, sizeof(Inventory));
    Lib_MemCpy(&gSaveContext.save.checksum, &sSaveDefaultChecksum, sizeof(gSaveContext.save.checksum));

    gSaveContext.save.horseData.sceneId = SCENE_F01;
    gSaveContext.save.horseData.pos.x = -1420;
    gSaveContext.save.horseData.pos.y = 257;
    gSaveContext.save.horseData.pos.z = -1285;
    gSaveContext.save.horseData.yaw = -0x7554;

    gSaveContext.nextCutsceneIndex = 0;
    gSaveContext.save.playerData.magicLevel = 0;
    Sram_GenerateRandomSaveFields();
}

SavePlayerData sSaveDebugPlayerData = {
    { 'Z', 'E', 'L', 'D', 'A', '3' },                   // newf
    0x0000,                                             // deaths
    { 0x15, 0x12, 0x17, 0x14, 0x3E, 0x3E, 0x3E, 0x3E }, // playerName "LINK    "
    0x80,                                               // healthCapacity
    0x80,                                               // health
    0,                                                  // magicLevel
    MAGIC_NORMAL_METER,                                 // magic
    50,                                                 // rupees
    100,                                                // swordHealth
    0,                                                  // tatlTimer
    true,                                               // isMagicAcquired
    false,                                              // isDoubleMagicAcquired
    0,                                                  // doubleDefense
    0,                                                  // unk_1F
    0xFF,                                               // unk_20
    0,                                                  // owlActivationFlags
    0xFF,                                               // unk_24
    SCENE_SPOT00,                                       // savedSceneId
};

ItemEquips sSaveDebugItemEquips = {
    {
        { ITEM_SWORD_KOKIRI, ITEM_BOW, ITEM_POTION_RED, ITEM_OCARINA },
        { ITEM_SWORD_KOKIRI, ITEM_BOW, ITEM_MASK_GORON, ITEM_OCARINA },
        { ITEM_SWORD_KOKIRI, ITEM_BOW, ITEM_MASK_ZORA, ITEM_OCARINA },
        { ITEM_NUT, ITEM_NUT, ITEM_MASK_DEKU, ITEM_OCARINA },
    },
    {
        { SLOT_OCARINA, SLOT_BOW, SLOT_BOTTLE_2, SLOT_OCARINA },
        { SLOT_OCARINA, SLOT_MAGIC_BEANS, SLOT_MASK_GORON, SLOT_BOMBCHU },
        { SLOT_OCARINA, SLOT_POWDER_KEG, SLOT_MASK_ZORA, SLOT_BOMBCHU },
        { SLOT_OCARINA, SLOT_BOW, SLOT_MASK_DEKU, SLOT_BOMBCHU },
    },
    0x11,
};

Inventory sSaveDebugInventory = {
    // items
    {
        ITEM_OCARINA,
        ITEM_BOW,
        ITEM_ARROW_FIRE,
        ITEM_ARROW_ICE,
        ITEM_ARROW_LIGHT,
        ITEM_MOON_TEAR,
        ITEM_BOMB,
        ITEM_BOMBCHU,
        ITEM_STICK,
        ITEM_NUT,
        ITEM_MAGIC_BEANS,
        ITEM_ROOM_KEY,
        ITEM_POWDER_KEG,
        ITEM_PICTO_BOX,
        ITEM_LENS,
        ITEM_HOOKSHOT,
        ITEM_SWORD_GREAT_FAIRY,
        ITEM_LETTER_TO_KAFEI,
        ITEM_BOTTLE,
        ITEM_POTION_RED,
        ITEM_POTION_GREEN,
        ITEM_POTION_BLUE,
        ITEM_NONE,
        ITEM_NONE,
        ITEM_MASK_POSTMAN,
        ITEM_MASK_ALL_NIGHT,
        ITEM_MASK_BLAST,
        ITEM_MASK_STONE,
        ITEM_MASK_GREAT_FAIRY,
        ITEM_MASK_DEKU,
        ITEM_MASK_KEATON,
        ITEM_MASK_BREMEN,
        ITEM_MASK_BUNNY,
        ITEM_MASK_DON_GERO,
        ITEM_MASK_SCENTS,
        ITEM_MASK_GORON,
        ITEM_MASK_ROMANI,
        ITEM_MASK_CIRCUS_LEADER,
        ITEM_MASK_KAFEIS_MASK,
        ITEM_MASK_COUPLE,
        ITEM_MASK_TRUTH,
        ITEM_MASK_ZORA,
        ITEM_MASK_KAMARO,
        ITEM_MASK_GIBDO,
        ITEM_MASK_GARO,
        ITEM_MASK_CAPTAIN,
        ITEM_MASK_GIANT,
        ITEM_MASK_FIERCE_DEITY,
    },
    // ammo
    { 1, 30, 1, 1, 1, 1, 30, 30, 30, 30, 1, 1, 1, 1, 30, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
    // upgrades
    0x120009,
    // questItems
    (1 << QUEST_SONG_SONATA) | (1 << QUEST_SONG_LULLABY) | (1 << QUEST_SONG_BOSSA_NOVA) | (1 << QUEST_SONG_ELEGY) |
        (1 << QUEST_SONG_OATH) | (1 << QUEST_SONG_TIME) | (1 << QUEST_SONG_HEALING) | (1 << QUEST_SONG_EPONA) |
        (1 << QUEST_SONG_SOARING) | (1 << QUEST_SONG_STORMS) | (1 << QUEST_BOMBERS_NOTEBOOK) |
        (1 << QUEST_SONG_LULLABY_INTRO),
    // dungeonItems
    { 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 },
    // dungeonKeys
    { 8, 8, 8, 8, 8, 8, 8, 8, 8 },
    // defenseHearts
    0,
    // strayFairies
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    // dekuPlaygroundPlayerName
    {
        // "LINK    "
        { 0x15, 0x12, 0x17, 0x14, 0x3E, 0x3E, 0x3E, 0x3E },
        // "LINK    "
        { 0x15, 0x12, 0x17, 0x14, 0x3E, 0x3E, 0x3E, 0x3E },
        // "LINK    "
        { 0x15, 0x12, 0x17, 0x14, 0x3E, 0x3E, 0x3E, 0x3E },
    },
};

u16 sSaveDebugChecksum = 0;

u8 D_801C6A48[] = {
    ITEM_MASK_FIERCE_DEITY, ITEM_MASK_GORON, ITEM_MASK_ZORA, ITEM_MASK_DEKU, ITEM_MASK_FIERCE_DEITY,
};

u8 D_801C6A50[] = {
    SLOT_MASK_FIERCE_DEITY, SLOT_MASK_GORON, SLOT_MASK_ZORA, SLOT_MASK_DEKU, SLOT_MASK_FIERCE_DEITY,
};

/**
 *  Initialize debug save. This is also used on the Title Screen
 *  This save has a mostly full inventory, every mask and 10 hearts.
 *
 *  Some noteable flags that are set:
 *  TODO: Investigate the flags
 */
void Sram_InitDebugSave(void) {
    Sram_ResetSave();

    Lib_MemCpy(&gSaveContext.save.playerData, &sSaveDebugPlayerData, sizeof(SavePlayerData));
    Lib_MemCpy(&gSaveContext.save.equips, &sSaveDebugItemEquips, sizeof(ItemEquips));
    Lib_MemCpy(&gSaveContext.save.inventory, &sSaveDebugInventory, sizeof(Inventory));
    Lib_MemCpy(&gSaveContext.save.checksum, &sSaveDebugChecksum, sizeof(gSaveContext.save.checksum));

    if (GET_PLAYER_FORM != PLAYER_FORM_HUMAN) {
        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN) = D_801C6A48[GET_PLAYER_FORM];
        C_SLOT_EQUIP(0, EQUIP_SLOT_C_DOWN) = D_801C6A50[GET_PLAYER_FORM];
    }

    gSaveContext.save.hasTatl = true;

    gSaveContext.save.horseData.sceneId = SCENE_F01;
    gSaveContext.save.horseData.pos.x = -1420;
    gSaveContext.save.horseData.pos.y = 257;
    gSaveContext.save.horseData.pos.z = -1285;
    gSaveContext.save.horseData.yaw = -0x7554;

    gSaveContext.save.entrance = ENTRANCE(CUTSCENE, 0);
    gSaveContext.save.isFirstCycle = true;

    SET_WEEKEVENTREG(WEEKEVENTREG_15_20);
    SET_WEEKEVENTREG(WEEKEVENTREG_59_04);
    SET_WEEKEVENTREG(WEEKEVENTREG_31_04);

    gSaveContext.cycleSceneFlags[SCENE_INSIDETOWER].switch0 = 1;
    gSaveContext.save.permanentSceneFlags[SCENE_INSIDETOWER].switch0 = 1;
    gSaveContext.save.playerData.magicLevel = 0;

    Sram_GenerateRandomSaveFields();
}

// Unused
void func_80144A94(SramContext* sramCtx) {
    s32 i;
    s32 cutscene = gSaveContext.save.cutscene;

    bzero(sramCtx->saveBuf, SAVE_BUFFER_SIZE);

    if (func_80185968(sramCtx->saveBuf, D_801C67C8[gSaveContext.fileNum * 2], D_801C67F0[gSaveContext.fileNum * 2]) !=
        0) {
        func_80185968(sramCtx->saveBuf, D_801C67C8[gSaveContext.fileNum * 2 + 1],
                      D_801C67F0[gSaveContext.fileNum * 2 + 1]);
    }
    Lib_MemCpy(&gSaveContext.save, sramCtx->saveBuf, sizeof(Save));
    if (CHECK_NEWF(gSaveContext.save.playerData.newf)) {
        func_80185968(sramCtx->saveBuf, D_801C67C8[gSaveContext.fileNum * 2 + 1],
                      D_801C67F0[gSaveContext.fileNum * 2 + 1]);
        Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, sizeof(Save));
    }
    gSaveContext.save.cutscene = cutscene;

    for (i = 0; i < ARRAY_COUNT(gSaveContext.eventInf); i++) {
        gSaveContext.eventInf[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNT(gSaveContext.cycleSceneFlags); i++) {
        gSaveContext.cycleSceneFlags[i].chest = gSaveContext.save.permanentSceneFlags[i].chest;
        gSaveContext.cycleSceneFlags[i].switch0 = gSaveContext.save.permanentSceneFlags[i].switch0;
        gSaveContext.cycleSceneFlags[i].switch1 = gSaveContext.save.permanentSceneFlags[i].switch1;
        gSaveContext.cycleSceneFlags[i].clearedRoom = gSaveContext.save.permanentSceneFlags[i].clearedRoom;
        gSaveContext.cycleSceneFlags[i].collectible = gSaveContext.save.permanentSceneFlags[i].collectible;
    }

    for (i = 0; i < TIMER_ID_MAX; i++) {
        gSaveContext.timerStates[i] = TIMER_STATE_OFF;
        gSaveContext.timerCurTimes[i] = SECONDS_TO_TIMER(0);
        gSaveContext.timerTimeLimits[i] = SECONDS_TO_TIMER(0);
        gSaveContext.timerStartOsTimes[i] = 0;
        gSaveContext.timerStopTimes[i] = SECONDS_TO_TIMER(0);
        gSaveContext.timerPausedOsTimes[i] = 0;
    }

    D_801BDAA0 = 1;
    D_801BDA9C = 0;
    gSaveContext.powderKegTimer = 0;
    gSaveContext.unk_1014 = 0;
    gSaveContext.jinxTimer = 0;
}

u16 D_801C6A58[] = {
    ENTRANCE(GREAT_BAY_COAST, 11), ENTRANCE(ZORA_CAPE, 6),
    ENTRANCE(SNOWHEAD, 3),         ENTRANCE(MOUNTAIN_VILLAGE_WINTER, 8),
    ENTRANCE(SOUTH_CLOCK_TOWN, 9), ENTRANCE(MILK_ROAD, 4),
    ENTRANCE(WOODFALL, 4),         ENTRANCE(SOUTHERN_SWAMP_POISONED, 10),
    ENTRANCE(IKANA_CANYON, 4),     ENTRANCE(STONE_TOWER, 3),
};

void Sram_OpenSave(FileSelectState* fileSelect, SramContext* sramCtx) {
    s32 i;
    s32 pad;
    s32 phi_t1;
    s32 pad1;
    s32 fileNum;

    if (gSaveContext.unk_3F3F) {
        bzero(sramCtx->saveBuf, SAVE_BUFFER_SIZE);

        if (gSaveContext.fileNum == 0xFF) {
            func_80185968(sramCtx->saveBuf, D_801C67C8[0], D_801C67F0[0]);
        } else if (fileSelect->unk_2446A[gSaveContext.fileNum] != 0) {
            phi_t1 = gSaveContext.fileNum + 2;
            phi_t1 *= 2;

            if (func_80185968(sramCtx->saveBuf, D_801C67C8[phi_t1], D_801C67F0[phi_t1]) != 0) {
                func_80185968(sramCtx->saveBuf, D_801C67C8[phi_t1 + 1], D_801C67F0[phi_t1 + 1]);
            }
        } else {
            phi_t1 = gSaveContext.fileNum;
            phi_t1 *= 2;

            if (func_80185968(sramCtx->saveBuf, D_801C67C8[phi_t1], D_801C67F0[phi_t1]) != 0) {
                func_80185968(sramCtx->saveBuf, D_801C67C8[phi_t1 + 1], D_801C67F0[phi_t1 + 1]);
            }
        }

        Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, D_801C6870[phi_t1]);

        if (CHECK_NEWF(gSaveContext.save.playerData.newf)) {
            func_80185968(sramCtx->saveBuf, D_801C67C8[phi_t1 + 1], D_801C67F0[phi_t1 + 1]);
            Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, D_801C6870[phi_t1]);
        }
    }

    gSaveContext.save.playerData.magicLevel = 0;

    if (!gSaveContext.save.isOwlSave) {
        for (i = 0; i < ARRAY_COUNT(gSaveContext.eventInf); i++) {
            gSaveContext.eventInf[i] = 0;
        }

        for (i = 0; i < ARRAY_COUNT(gSaveContext.cycleSceneFlags); i++) {
            gSaveContext.cycleSceneFlags[i].chest = gSaveContext.save.permanentSceneFlags[i].chest;
            gSaveContext.cycleSceneFlags[i].switch0 = gSaveContext.save.permanentSceneFlags[i].switch0;
            gSaveContext.cycleSceneFlags[i].switch1 = gSaveContext.save.permanentSceneFlags[i].switch1;
            gSaveContext.cycleSceneFlags[i].clearedRoom = gSaveContext.save.permanentSceneFlags[i].clearedRoom;
            gSaveContext.cycleSceneFlags[i].collectible = gSaveContext.save.permanentSceneFlags[i].collectible;
        }

        for (i = 0; i < TIMER_ID_MAX; i++) {
            gSaveContext.timerStates[i] = TIMER_STATE_OFF;
            gSaveContext.timerCurTimes[i] = SECONDS_TO_TIMER(0);
            gSaveContext.timerTimeLimits[i] = SECONDS_TO_TIMER(0);
            gSaveContext.timerStartOsTimes[i] = 0;
            gSaveContext.timerStopTimes[i] = SECONDS_TO_TIMER(0);
            gSaveContext.timerPausedOsTimes[i] = 0;
        }

        if (gSaveContext.save.isFirstCycle) {
            gSaveContext.save.entrance = ENTRANCE(SOUTH_CLOCK_TOWN, 0);
            gSaveContext.save.day = 0;
            gSaveContext.save.time = 0x3FFF;
        } else {
            gSaveContext.save.entrance = ENTRANCE(CUTSCENE, 0);
            gSaveContext.nextCutsceneIndex = 0;
            gSaveContext.save.playerForm = PLAYER_FORM_HUMAN;
        }
    } else {
        gSaveContext.save.entrance = D_801C6A58[(void)0, gSaveContext.save.owlSaveLocation];
        if ((gSaveContext.save.entrance == ENTRANCE(SOUTHERN_SWAMP_POISONED, 10)) &&
            CHECK_WEEKEVENTREG(WEEKEVENTREG_20_02)) {
            gSaveContext.save.entrance = ENTRANCE(SOUTHERN_SWAMP_CLEARED, 10);
        } else if ((gSaveContext.save.entrance == ENTRANCE(MOUNTAIN_VILLAGE_WINTER, 8)) &&
                   CHECK_WEEKEVENTREG(WEEKEVENTREG_33_80)) {
            gSaveContext.save.entrance = ENTRANCE(MOUNTAIN_VILLAGE_SPRING, 8);
        }

        for (i = 0; i < ARRAY_COUNT(gSaveContext.cycleSceneFlags); i++) {
            gSaveContext.cycleSceneFlags[i].chest = gSaveContext.save.permanentSceneFlags[i].chest;
            gSaveContext.cycleSceneFlags[i].switch0 = gSaveContext.save.permanentSceneFlags[i].switch0;
            gSaveContext.cycleSceneFlags[i].switch1 = gSaveContext.save.permanentSceneFlags[i].switch1;
            gSaveContext.cycleSceneFlags[i].clearedRoom = gSaveContext.save.permanentSceneFlags[i].clearedRoom;
            gSaveContext.cycleSceneFlags[i].collectible = gSaveContext.save.permanentSceneFlags[i].collectible;
        }

        if (gSaveContext.save.unk_F65) {
            Lib_MemCpy(gScarecrowSpawnSongPtr, gSaveContext.save.scarecrowSpawnSong,
                       sizeof(gSaveContext.save.scarecrowSpawnSong));

            for (i = 0; i != ARRAY_COUNT(gSaveContext.save.scarecrowSpawnSong); i++) {}
        }

        fileNum = gSaveContext.fileNum;
        func_80147314(sramCtx, fileNum);
    }
}

// Similar to func_80145698, but accounts for owl saves?
void func_8014546C(SramContext* sramCtx) {
    s32 i;

    if (gSaveContext.save.isOwlSave) {
        for (i = 0; i < ARRAY_COUNT(gSaveContext.cycleSceneFlags); i++) {
            gSaveContext.save.permanentSceneFlags[i].chest = gSaveContext.cycleSceneFlags[i].chest;
            gSaveContext.save.permanentSceneFlags[i].switch0 = gSaveContext.cycleSceneFlags[i].switch0;
            gSaveContext.save.permanentSceneFlags[i].switch1 = gSaveContext.cycleSceneFlags[i].switch1;
            gSaveContext.save.permanentSceneFlags[i].clearedRoom = gSaveContext.cycleSceneFlags[i].clearedRoom;
            gSaveContext.save.permanentSceneFlags[i].collectible = gSaveContext.cycleSceneFlags[i].collectible;
        }

        gSaveContext.save.checksum = 0;
        gSaveContext.save.checksum = Sram_CalcChecksum(&gSaveContext, offsetof(SaveContext, fileNum));

        Lib_MemCpy(sramCtx->saveBuf, &gSaveContext, offsetof(SaveContext, fileNum));
    } else {
        for (i = 0; i < ARRAY_COUNT(gSaveContext.cycleSceneFlags); i++) {
            gSaveContext.save.permanentSceneFlags[i].chest = gSaveContext.cycleSceneFlags[i].chest;
            gSaveContext.save.permanentSceneFlags[i].switch0 = gSaveContext.cycleSceneFlags[i].switch0;
            gSaveContext.save.permanentSceneFlags[i].switch1 = gSaveContext.cycleSceneFlags[i].switch1;
            gSaveContext.save.permanentSceneFlags[i].clearedRoom = gSaveContext.cycleSceneFlags[i].clearedRoom;
            gSaveContext.save.permanentSceneFlags[i].collectible = gSaveContext.cycleSceneFlags[i].collectible;
        }

        gSaveContext.save.checksum = 0;
        gSaveContext.save.checksum = Sram_CalcChecksum(&gSaveContext.save, sizeof(Save));

        if (gSaveContext.unk_3F3F) {
            Lib_MemCpy(sramCtx->saveBuf, &gSaveContext, sizeof(Save));
            Lib_MemCpy(&sramCtx->saveBuf[0x2000], &gSaveContext.save, sizeof(Save));
        }
    }
}

/**
 * Save permanent scene flags, calculate checksum, copy save context to the save buffer
 */
void func_80145698(SramContext* sramCtx) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gSaveContext.cycleSceneFlags); i++) {
        gSaveContext.save.permanentSceneFlags[i].chest = gSaveContext.cycleSceneFlags[i].chest;
        gSaveContext.save.permanentSceneFlags[i].switch0 = gSaveContext.cycleSceneFlags[i].switch0;
        gSaveContext.save.permanentSceneFlags[i].switch1 = gSaveContext.cycleSceneFlags[i].switch1;
        gSaveContext.save.permanentSceneFlags[i].clearedRoom = gSaveContext.cycleSceneFlags[i].clearedRoom;
        gSaveContext.save.permanentSceneFlags[i].collectible = gSaveContext.cycleSceneFlags[i].collectible;
    }

    gSaveContext.save.checksum = 0;
    gSaveContext.save.checksum = Sram_CalcChecksum(&gSaveContext.save, sizeof(Save));
    if (gSaveContext.unk_3F3F) {
        Lib_MemCpy(sramCtx->saveBuf, &gSaveContext, sizeof(Save));
        Lib_MemCpy(&sramCtx->saveBuf[0x2000], &gSaveContext.save, sizeof(Save));
    }
}

// Verifies save and use backup if corrupted?
#ifdef NON_EQUIVALENT
void func_801457CC(FileSelectState* fileSelect2, SramContext* sramCtx) {
    FileSelectState* fileSelect = fileSelect2;
    u16 sp7A;
    // u16 sp78;
    u16 sp76;
    // u16 sp74;
    u16 sp6E; //!
    // s32 sp68;
    // u16 sp66;
    u16 phi_s2; //!
    u16 sp64;
    // s32 sp60;
    // s32 sp5C;
    // s32 sp58;
    // u32 new_var;
    u16 phi_s2_3;
    // s16 fakevar;

    u16 temp_s2;
    u16 temp_v0_2;
    u16 phi_a0; // maskCount

    if (gSaveContext.unk_3F3F) {
        D_801F6AF0 = gSaveContext.save.time;
        D_801F6AF2 = gSaveContext.unk_3F3F;
        sp64 = 0;

        for (sp76 = 0; sp76 < 5; sp76++, sp64 += 2) {
            bzero(sramCtx->saveBuf, SAVE_BUFFER_SIZE);

            phi_s2 = false;
            sp6E = 0;
            if (func_80185968(sramCtx->saveBuf, D_801C67C8[sp64], D_801C67F0[sp64])) {
                sp6E = 1;
                if (func_80185968(sramCtx->saveBuf, D_801C67C8[sp64 + 1], D_801C67F0[sp64 + 1])) {
                    phi_s2 = true;
                }
            }

            if (sp76 < 2) {
                fileSelect->unk_24468[sp76] = 0;
                if (phi_s2) {
                    bzero(sramCtx->saveBuf, SAVE_BUFFER_SIZE);
                    Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, D_801C6870[sp64]);
                } else {
                    // Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, D_801C6870[sp64]);
                    Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, D_801C6870[sp64]);
                    temp_s2 = gSaveContext.save.checksum;
                    gSaveContext.save.checksum = 0;
                    temp_v0_2 = Sram_CalcChecksum(&gSaveContext, D_801C6870[sp64]);
                    gSaveContext.save.checksum = temp_s2;

                    if (CHECK_NEWF(gSaveContext.save.playerData.newf) || (temp_s2 != temp_v0_2)) {
                        sp6E = 1;
                        if (CHECK_NEWF2(gSaveContext.save.playerData.newf)) {}

                        phi_s2 = false;
                        if (func_80185968(sramCtx->saveBuf, D_801C67C8[sp64 + 1], D_801C67F0[sp64 + 1])) {
                            phi_s2 = true;
                        }

                        Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, D_801C6870[sp64]);
                        temp_s2 = gSaveContext.save.checksum;
                        gSaveContext.save.checksum = 0;
                        if (phi_s2 || CHECK_NEWF(gSaveContext.save.playerData.newf) ||
                            (temp_s2 != Sram_CalcChecksum(&gSaveContext, D_801C6870[sp64]))) {
                            bzero(sramCtx->saveBuf, SAVE_BUFFER_SIZE);
                            Lib_MemCpy(&gSaveContext.save, sramCtx->saveBuf, sizeof(Save));
                            sp6E = 999;
                        }
                    }
                }

                gSaveContext.save.checksum = 0;
                gSaveContext.save.checksum =
                    Sram_CalcChecksum(&gSaveContext, D_801C6870[sp64 & 0xFFFFFFFF]); // TODO: Needed?

                for (sp7A = 0; sp7A < ARRAY_COUNT(gSaveContext.save.playerData.newf); sp7A++) {
                    fileSelect->newf[sp76][sp7A] = gSaveContext.save.playerData.newf[sp7A];
                }

                if (!CHECK_NEWF(fileSelect->newf[sp76])) {
                    fileSelect->unk_2440C[sp76] = gSaveContext.save.playerData.deaths;

                    for (sp7A = 0; sp7A < ARRAY_COUNT(gSaveContext.save.playerData.playerName); sp7A++) {
                        fileSelect->unk_24414[sp76][sp7A] = gSaveContext.save.playerData.playerName[sp7A];
                    }

                    fileSelect->healthCapacity[sp76] = gSaveContext.save.playerData.healthCapacity;
                    fileSelect->health[sp76] = gSaveContext.save.playerData.health;
                    fileSelect->unk_24454[sp76] = gSaveContext.save.inventory.defenseHearts;
                    fileSelect->unk_24444[sp76] = gSaveContext.save.inventory.questItems;
                    fileSelect->unk_24458[sp76] = gSaveContext.save.time;
                    fileSelect->unk_24460[sp76] = gSaveContext.save.day;
                    fileSelect->unk_24468[sp76] = gSaveContext.save.isOwlSave;
                    fileSelect->rupees[sp76] = gSaveContext.save.playerData.rupees;
                    fileSelect->unk_24474[sp76] = CUR_UPG_VALUE(4);

                    for (sp7A = 0, phi_a0 = 0; sp7A < 24; sp7A++) {
                        if (gSaveContext.save.inventory.items[sp7A + 24] != 0xFF) {
                            phi_a0++;
                        }
                    }
                    fileSelect->maskCount[sp76] = phi_a0;
                    fileSelect->heartPieceCount[sp76] = ((gSaveContext.save.inventory.questItems & 0xF0000000) >> 0x1C);
                }

                if (sp6E == 1) {
                    Lib_MemCpy(&sramCtx->saveBuf[0x2000], &gSaveContext.save, sizeof(Save));
                    func_80146EBC(sramCtx, D_801C67C8[sp64], D_801C6818[sp64]);
                } else if (sp6E == 0) { // TODO: == 0?
                    temp_s2 = gSaveContext.save.checksum;
                    if (func_80185968(sramCtx->saveBuf, D_801C67C8[sp64 + 1], D_801C67F0[sp64 + 1])) {
                        phi_s2_3 = 1;
                    } else {
                        Lib_MemCpy(&gSaveContext.save, sramCtx->saveBuf, sizeof(Save));
                        phi_s2_3 = gSaveContext.save.checksum;
                        gSaveContext.save.checksum = 0;
                        sp7A = Sram_CalcChecksum(&gSaveContext.save, sizeof(Save));
                    }

                    if (CHECK_NEWF(gSaveContext.save.playerData.newf) || (phi_s2_3 != sp7A) || (phi_s2_3 != temp_s2)) {
                        func_80185968(sramCtx->saveBuf, D_801C67C8[sp64], D_801C67F0[sp64]);
                        Lib_MemCpy(&gSaveContext.save, sramCtx->saveBuf, sizeof(Save));
                        Lib_MemCpy(&sramCtx->saveBuf[0x2000], &gSaveContext.save, sizeof(Save));
                        func_80146EBC(sramCtx, D_801C67C8[sp64], D_801C6818[sp64]);
                    }
                }
            } else if (sp76 < 4) {
                fileSelect->unk_24468[sp76] = 0;

                if (!CHECK_NEWF(fileSelect->newf2[(s32)sp76])) { // TODO: Needed?
                    if (phi_s2) {
                        bzero(sramCtx->saveBuf, SAVE_BUFFER_SIZE);
                        Lib_MemCpy(&gSaveContext, sramCtx->saveBuf,
                                   D_801C6870[sp64]); // TODO: Needed?
                    } else {
                        Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, D_801C6870[sp64]);
                        temp_s2 = gSaveContext.save.checksum;

                        gSaveContext.save.checksum = 0;
                        temp_v0_2 = Sram_CalcChecksum(&gSaveContext, D_801C6870[sp64]);
                        gSaveContext.save.checksum = temp_s2;
                        if (CHECK_NEWF(gSaveContext.save.playerData.newf) || (temp_s2 != temp_v0_2)) {
                            sp6E = 1;
                            if ((gSaveContext.save.playerData.newf[0] == 'Z') &&
                                (gSaveContext.save.playerData.newf[1] == 'E')) {
                                phi_s2 = false;
                            }

                            if (func_80185968(sramCtx->saveBuf, D_801C67C8[sp64 + 1], D_801C67F0[sp64 + 1])) {
                                phi_s2 = true;
                            }

                            Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, D_801C6870[sp64]);
                            temp_s2 = gSaveContext.save.checksum;
                            gSaveContext.save.checksum = 0;
                            if (phi_s2 || CHECK_NEWF(gSaveContext.save.playerData.newf) ||
                                (temp_s2 != Sram_CalcChecksum(&gSaveContext, D_801C6870[sp64]))) {
                                bzero(sramCtx->saveBuf, SAVE_BUFFER_SIZE);
                                Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, D_801C6870[sp64]);
                                sp6E = 999;
                            }
                        }
                    }

                    gSaveContext.save.checksum = 0;
                    gSaveContext.save.checksum =
                        Sram_CalcChecksum(&gSaveContext, D_801C6870[sp64 & 0xFFFFFFFF]); // TODO: Needed?

                    for (sp7A = 0; sp7A < ARRAY_COUNT(gSaveContext.save.playerData.newf); sp7A++) {
                        fileSelect->newf[sp76][sp7A] = gSaveContext.save.playerData.newf[sp7A];
                    }

                    if (!CHECK_NEWF(fileSelect->newf[sp76])) {
                        fileSelect->unk_2440C[sp76] = gSaveContext.save.playerData.deaths;

                        for (sp7A = 0; sp7A < ARRAY_COUNT(gSaveContext.save.playerData.playerName); sp7A++) {
                            phi_s2 += 0; // TODO: Needed?
                            fileSelect->unk_24414[sp76][sp7A] = gSaveContext.save.playerData.playerName[sp7A];
                        }

                        fileSelect->healthCapacity[sp76] = gSaveContext.save.playerData.healthCapacity;
                        fileSelect->health[sp76] = gSaveContext.save.playerData.health;
                        fileSelect->unk_24454[sp76] = gSaveContext.save.inventory.defenseHearts;
                        fileSelect->unk_24444[sp76] = gSaveContext.save.inventory.questItems;
                        fileSelect->unk_24458[sp76] = gSaveContext.save.time;
                        fileSelect->unk_24460[sp76] = gSaveContext.save.day;
                        fileSelect->unk_24468[sp76] = gSaveContext.save.isOwlSave;
                        fileSelect->rupees[sp76] = gSaveContext.save.playerData.rupees;
                        fileSelect->unk_24474[sp76] = CUR_UPG_VALUE(4);

                        for (sp7A = 0, phi_a0 = 0; sp7A < 24; sp7A++) {
                            if (gSaveContext.save.inventory.items[sp7A + 24] != 0xFF) {
                                phi_a0++;
                            }
                        }
                        fileSelect->maskCount[sp76] = phi_a0;
                        fileSelect->heartPieceCount[sp76] =
                            ((gSaveContext.save.inventory.questItems & 0xF0000000) >> 0x1C);
                    }

                    if (sp6E == 1) {
                        func_80146EBC(sramCtx, D_801C67C8[sp64], D_801C67F0[sp64]);
                        func_80146EBC(sramCtx, D_801C67C8[sp64 + 1], D_801C67F0[sp64 + 1]);
                    } else if (!sp6E) { // TODO: == 0?
                        temp_s2 = gSaveContext.save.checksum;
                        if (func_80185968(sramCtx->saveBuf, D_801C67C8[sp64 + 1], D_801C67F0[sp64 + 1])) {
                            phi_s2_3 = 1;
                        } else {
                            Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, D_801C6870[sp64]);
                            phi_s2_3 = gSaveContext.save.checksum;
                            gSaveContext.save.checksum = 0;
                            // phi_s2_3 = gSaveContext.save.checksum;
                            sp7A = Sram_CalcChecksum(&gSaveContext, D_801C6870[sp64]);
                        }

                        if (CHECK_NEWF(gSaveContext.save.playerData.newf) || (phi_s2_3 != sp7A) ||
                            (phi_s2_3 != temp_s2)) {
                            func_80185968(sramCtx->saveBuf, D_801C67C8[sp64], D_801C67F0[sp64]);
                            Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, D_801C6870[sp64]);
                            func_80146EBC(sramCtx, D_801C67C8[sp64], D_801C67F0[sp64]);
                            func_80146EBC(sramCtx, D_801C67C8[sp64 + 1], D_801C67F0[sp64 + 1]);
                        }
                    }
                } else {
                    bzero(sramCtx->saveBuf, SAVE_BUFFER_SIZE);
                    Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, D_801C6870[sp64]);
                    func_80146EBC(sramCtx, D_801C67C8[sp64], D_801C67F0[sp64]);
                    func_80146EBC(sramCtx, D_801C67C8[sp64 + 1], D_801C67F0[sp64 + 1]);
                }
            } else {
                if (phi_s2) {
                    gSaveContext.options.optionId = 0xA51D;
                    gSaveContext.options.language = 1;
                    gSaveContext.options.audioSetting = 0;
                    gSaveContext.options.languageSetting = 0;
                    gSaveContext.options.zTargetSetting = 0;
                } else {
                    Lib_MemCpy(&gSaveContext.options, sramCtx->saveBuf, sizeof(SaveOptions));
                    if (gSaveContext.options.optionId != 0xA51D) {
                        gSaveContext.options.optionId = 0xA51D;
                        gSaveContext.options.language = 1;
                        gSaveContext.options.audioSetting = 0;
                        gSaveContext.options.languageSetting = 0;
                        gSaveContext.options.zTargetSetting = 0;
                    }
                }
                func_801A3D98(gSaveContext.options.audioSetting);
            }
        }

        gSaveContext.save.time = D_801F6AF0;
        gSaveContext.unk_3F3F = D_801F6AF2;
    }

    gSaveContext.options.language = 1;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_801457CC.s")
#endif

void func_80146580(FileSelectState* fileSelect2, SramContext* sramCtx, s32 fileNum) {
    FileSelectState* fileSelect = fileSelect2;
    s32 pad;

    if (gSaveContext.unk_3F3F) {
        if (fileSelect->unk_2446A[fileNum]) {
            func_80147314(sramCtx, fileNum);
            fileSelect->unk_2446A[fileNum] = 0;
        }
        bzero(sramCtx->saveBuf, SAVE_BUFFER_SIZE);
        Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, sizeof(Save));
    }

    gSaveContext.save.time = D_801F6AF0;
    gSaveContext.unk_3F3F = D_801F6AF2;
}

#ifdef NON_MATCHING
// v0/v1
void func_80146628(FileSelectState* fileSelect2, SramContext* sramCtx) {
    FileSelectState* fileSelect = fileSelect2;
    u16 i;
    s16 maskCount;

    if (gSaveContext.unk_3F3F) {
        if (fileSelect->unk_2446A[fileSelect->unk_2448E]) {
            func_80147414(sramCtx, fileSelect->unk_2448E, fileSelect->fileNum);
            fileSelect->unk_24410[fileSelect->fileNum] = gSaveContext.save.playerData.deaths;

            for (i = 0; i < ARRAY_COUNT(gSaveContext.save.playerData.playerName); i++) {
                fileSelect->unk_24424[fileSelect->fileNum][i] = gSaveContext.save.playerData.playerName[i];
            }

            fileSelect->unk_24438[fileSelect->fileNum] = gSaveContext.save.playerData.healthCapacity;
            fileSelect->unk_24440[fileSelect->fileNum] = gSaveContext.save.playerData.health;
            fileSelect->unk_24456[fileSelect->fileNum] = gSaveContext.save.inventory.defenseHearts;
            fileSelect->unk_2444C[fileSelect->fileNum] = gSaveContext.save.inventory.questItems;
            fileSelect->unk_2445C[fileSelect->fileNum] = gSaveContext.save.time;
            fileSelect->unk_24464[fileSelect->fileNum] = gSaveContext.save.day;
            fileSelect->unk_2446A[fileSelect->fileNum] = gSaveContext.save.isOwlSave;
            fileSelect->unk_24470[fileSelect->fileNum] = gSaveContext.save.playerData.rupees;
            // = CUR_UPG_VALUE(UPG_WALLET);
            fileSelect->unk_24476[fileSelect->fileNum] =
                (gSaveContext.save.inventory.upgrades & gUpgradeMasks[4]) >> gUpgradeShifts[4];

            for (i = 0, maskCount = 0; i < 24; i++) {
                if (gSaveContext.save.inventory.items[i + 24] != ITEM_NONE) {
                    maskCount++;
                }
            }

            fileSelect->unk_2447A[fileSelect->fileNum] = maskCount;
            fileSelect->unk_2447E[fileSelect->fileNum] = (gSaveContext.save.inventory.questItems & 0xF0000000) >> 0x1C;
        }

        // clear buffer
        bzero(sramCtx->saveBuf, SAVE_BUFFER_SIZE);
        // read to buffer
        func_80185968(sramCtx->saveBuf, D_801C67C8[fileSelect->unk_2448E * 2], D_801C67F0[fileSelect->unk_2448E * 2]);

        if (1) {}
        func_80185968(&sramCtx->saveBuf[0x2000], D_801C67C8[fileSelect->unk_2448E * 2 + 1],
                      D_801C67F0[fileSelect->unk_2448E * 2 + 1]);
        if (1) {}

        // copy buffer to save context
        Lib_MemCpy(&gSaveContext.save, sramCtx->saveBuf, sizeof(Save));

        fileSelect->unk_2440C[fileSelect->fileNum] = gSaveContext.save.playerData.deaths;

        for (i = 0; i < ARRAY_COUNT(gSaveContext.save.playerData.playerName); i++) {
            fileSelect->unk_24414[fileSelect->fileNum][i] = gSaveContext.save.playerData.playerName[i];
        }

        fileSelect->healthCapacity[fileSelect->fileNum] = gSaveContext.save.playerData.healthCapacity;
        fileSelect->health[fileSelect->fileNum] = gSaveContext.save.playerData.health;
        fileSelect->unk_24454[fileSelect->fileNum] = gSaveContext.save.inventory.defenseHearts;
        fileSelect->unk_24444[fileSelect->fileNum] = gSaveContext.save.inventory.questItems;
        fileSelect->unk_24458[fileSelect->fileNum] = gSaveContext.save.time;
        fileSelect->unk_24460[fileSelect->fileNum] = gSaveContext.save.day;
        fileSelect->unk_24468[fileSelect->fileNum] = gSaveContext.save.isOwlSave;
        fileSelect->rupees[fileSelect->fileNum] = gSaveContext.save.playerData.rupees;
        // = CUR_UPG_VALUE(UPG_WALLET);
        fileSelect->unk_24474[fileSelect->fileNum] =
            (gSaveContext.save.inventory.upgrades & gUpgradeMasks[4]) >> gUpgradeShifts[4];

        for (i = 0, maskCount = 0; i < 24; i++) {
            if (gSaveContext.save.inventory.items[i + 24] != ITEM_NONE) {
                maskCount++;
            }
        }

        fileSelect->maskCount[fileSelect->fileNum] = maskCount;
        fileSelect->heartPieceCount[fileSelect->fileNum] =
            (gSaveContext.save.inventory.questItems & 0xF0000000) >> 0x1C;
    }

    gSaveContext.save.time = D_801F6AF0;
    gSaveContext.unk_3F3F = D_801F6AF2;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80146628.s")
#endif

void Sram_InitSave(FileSelectState* fileSelect2, SramContext* sramCtx) {
    s32 phi_v0;
    u16 i;
    FileSelectState* fileSelect = fileSelect2;
    s16 maskCount;

    if (gSaveContext.unk_3F3F) {
        Sram_InitNewSave();
        if (fileSelect->unk_24480 == 0) {
            gSaveContext.save.cutscene = 0xFFF0;
        }

        for (phi_v0 = 0; phi_v0 < ARRAY_COUNT(gSaveContext.save.playerData.playerName); phi_v0++) {
            gSaveContext.save.playerData.playerName[phi_v0] = fileSelect->unk_24414[fileSelect->unk_24480][phi_v0];
        }

        gSaveContext.save.playerData.newf[0] = 'Z';
        gSaveContext.save.playerData.newf[1] = 'E';
        gSaveContext.save.playerData.newf[2] = 'L';
        gSaveContext.save.playerData.newf[3] = 'D';
        gSaveContext.save.playerData.newf[4] = 'A';
        gSaveContext.save.playerData.newf[5] = '3';

        gSaveContext.save.checksum = Sram_CalcChecksum(&gSaveContext.save, sizeof(Save));

        Lib_MemCpy(sramCtx->saveBuf, &gSaveContext.save, sizeof(Save));
        Lib_MemCpy(&sramCtx->saveBuf[0x2000], &gSaveContext.save, sizeof(Save));

        for (i = 0; i < ARRAY_COUNT(gSaveContext.save.playerData.newf); i++) {
            fileSelect->newf[fileSelect->unk_24480][i] = gSaveContext.save.playerData.newf[i];
        }

        fileSelect->unk_2440C[fileSelect->unk_24480] = gSaveContext.save.playerData.deaths;

        for (i = 0; i < ARRAY_COUNT(gSaveContext.save.playerData.playerName); i++) {
            fileSelect->unk_24414[fileSelect->unk_24480][i] = gSaveContext.save.playerData.playerName[i];
        }

        fileSelect->healthCapacity[fileSelect->unk_24480] = gSaveContext.save.playerData.healthCapacity;
        fileSelect->health[fileSelect->unk_24480] = gSaveContext.save.playerData.health;
        fileSelect->unk_24454[fileSelect->unk_24480] = gSaveContext.save.inventory.defenseHearts;
        fileSelect->unk_24444[fileSelect->unk_24480] = gSaveContext.save.inventory.questItems;
        fileSelect->unk_24458[fileSelect->unk_24480] = gSaveContext.save.time;
        fileSelect->unk_24460[fileSelect->unk_24480] = gSaveContext.save.day;
        fileSelect->unk_24468[fileSelect->unk_24480] = gSaveContext.save.isOwlSave;
        fileSelect->rupees[fileSelect->unk_24480] = gSaveContext.save.playerData.rupees;
        fileSelect->unk_24474[fileSelect->unk_24480] = CUR_UPG_VALUE(UPG_WALLET);

        for (i = 0, maskCount = 0; i < 24; i++) {
            if (gSaveContext.save.inventory.items[i + 24] != ITEM_NONE) {
                maskCount++;
            }
        }

        fileSelect->maskCount[fileSelect->unk_24480] = maskCount;
        fileSelect->heartPieceCount[fileSelect->unk_24480] =
            (gSaveContext.save.inventory.questItems & 0xF0000000) >> 0x1C;
    }

    gSaveContext.save.time = D_801F6AF0;
    gSaveContext.unk_3F3F = D_801F6AF2;
}

void func_80146DF8(SramContext* sramCtx) {
    if (gSaveContext.unk_3F3F) {
        // TODO: macros for languages
        gSaveContext.options.language = 1;
        Lib_MemCpy(sramCtx->saveBuf, &gSaveContext.options, sizeof(SaveOptions));
    }
}

void Sram_InitSram(GameState* gameState, SramContext* sramCtx) {
    if (gSaveContext.save.entrance) {} // Required to match

    func_801A3D98(gSaveContext.options.audioSetting);
}

void Sram_Alloc(GameState* gameState, SramContext* sramCtx) {
    if (gSaveContext.unk_3F3F) {
        sramCtx->saveBuf = THA_AllocEndAlign16(&gameState->heap, SAVE_BUFFER_SIZE);
        sramCtx->status = 0;
    }
}

/**
 * Synchronous flash write
 */
void func_80146EBC(SramContext* sramCtx, s32 curPage, s32 numPages) {
    sramCtx->curPage = curPage;
    sramCtx->numPages = numPages;
    func_80185F64(sramCtx->saveBuf, curPage, numPages);
}

/**
 * Saves the game on the very first time Player enters South Clock Town from the Clock Tower
 */
void Sram_SaveSpecialEnterClockTown(PlayState* play) {
    s32 pad[2];
    SramContext* sramCtx = &play->sramCtx;

    gSaveContext.save.isFirstCycle = true;
    gSaveContext.save.isOwlSave = false;
    func_80145698(sramCtx);
    func_80185F64(sramCtx->saveBuf, D_801C67C8[gSaveContext.fileNum * 2], D_801C6818[gSaveContext.fileNum * 2]);
}

/**
 * Saves when beating the game, after showing the "Dawn of the New Day" message
 */
void Sram_SaveSpecialNewDay(PlayState* play) {
    s32 cutscene = gSaveContext.save.cutscene;
    s32 day;
    u16 time = gSaveContext.save.time;

    day = gSaveContext.save.day;

    CLEAR_WEEKEVENTREG(WEEKEVENTREG_84_20);

    Sram_SaveEndOfCycle(play);
    func_8014546C(&play->sramCtx);

    gSaveContext.save.day = day;
    gSaveContext.save.time = time;
    gSaveContext.save.cutscene = cutscene;
    func_80185F64(play->sramCtx.saveBuf, D_801C67C8[gSaveContext.fileNum * 2], D_801C67F0[gSaveContext.fileNum * 2]);
}

void func_80147008(SramContext* sramCtx, u32 curPage, u32 numPages) {
    sramCtx->curPage = curPage;
    sramCtx->numPages = numPages;
    sramCtx->status = 1;
}

void func_80147020(SramContext* sramCtx) {
    // async flash write
    func_80185DDC(sramCtx->saveBuf, sramCtx->curPage, sramCtx->numPages);

    sramCtx->unk_18 = osGetTime();
    sramCtx->status = 2;
}

void func_80147068(SramContext* sramCtx) {
    if (sramCtx->status == 2) {
        if (func_80185EC4() != 0) {     // if task running
            if (func_80185F04() == 0) { // wait for task done
                // task success
                sramCtx->status = 4;
            } else {
                // task failure
                sramCtx->status = 4;
            }
        }
    } else if (OSTIME_TO_TIMER(osGetTime() - sramCtx->unk_18) >= SECONDS_TO_TIMER(2)) {
        sramCtx->status = 0;
    }
}

void func_80147138(SramContext* sramCtx, s32 curPage, s32 numPages) {
    sramCtx->curPage = curPage;
    sramCtx->numPages = numPages;
    sramCtx->status = 6;
}

void func_80147150(SramContext* sramCtx) {
    func_80185DDC(sramCtx->saveBuf, sramCtx->curPage, sramCtx->numPages);

    sramCtx->unk_18 = osGetTime();
    sramCtx->status = 7;
}

void func_80147198(SramContext* sramCtx) {
    if (sramCtx->status == 7) {
        if (func_80185EC4() != 0) {     // Is task running
            if (func_80185F04() == 0) { // Wait for task done
                func_80185DDC(sramCtx->saveBuf, sramCtx->curPage + 0x80, sramCtx->numPages);
                sramCtx->status = 8;
            } else {
                func_80185DDC(sramCtx->saveBuf, sramCtx->curPage + 0x80, sramCtx->numPages);
                sramCtx->status = 8;
            }
        }
    } else if (sramCtx->status == 8) {
        if (func_80185EC4() != 0) {     // Is task running
            if (func_80185F04() == 0) { // Wait for task done
                sramCtx->status = 4;
            } else {
                sramCtx->status = 4;
            }
        }
    } else if (OSTIME_TO_TIMER(osGetTime() - sramCtx->unk_18) >= SECONDS_TO_TIMER(2)) {
        sramCtx->status = 0;
        bzero(sramCtx->saveBuf, SAVE_BUFFER_SIZE);
        gSaveContext.save.isOwlSave = false;
        gSaveContext.save.checksum = 0;
        // flash read to buffer then copy to save context
        func_80185968(sramCtx->saveBuf, sramCtx->curPage, sramCtx->numPages);
        Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, offsetof(SaveContext, fileNum));
    }
}

void func_80147314(SramContext* sramCtx, s32 fileNum) {
    s32 pad;

    gSaveContext.save.isOwlSave = false;

    gSaveContext.save.playerData.newf[0] = '\0';
    gSaveContext.save.playerData.newf[1] = '\0';
    gSaveContext.save.playerData.newf[2] = '\0';
    gSaveContext.save.playerData.newf[3] = '\0';
    gSaveContext.save.playerData.newf[4] = '\0';
    gSaveContext.save.playerData.newf[5] = '\0';

    gSaveContext.save.checksum = 0;
    gSaveContext.save.checksum = Sram_CalcChecksum(&gSaveContext, offsetof(SaveContext, fileNum));

    Lib_MemCpy(sramCtx->saveBuf, &gSaveContext, offsetof(SaveContext, fileNum));
    func_80146EBC(sramCtx, D_801C6840[fileNum * 2], D_801C6850[fileNum * 2]);
    func_80146EBC(sramCtx, D_801C6840[fileNum * 2 + 1], D_801C6850[fileNum * 2]);

    gSaveContext.save.isOwlSave = true;

    gSaveContext.save.playerData.newf[0] = 'Z';
    gSaveContext.save.playerData.newf[1] = 'E';
    gSaveContext.save.playerData.newf[2] = 'L';
    gSaveContext.save.playerData.newf[3] = 'D';
    gSaveContext.save.playerData.newf[4] = 'A';
    gSaveContext.save.playerData.newf[5] = '3';
}

void func_80147414(SramContext* sramCtx, s32 fileNum, s32 arg2) {
    s32 pad;

    // Clear save buffer
    bzero(sramCtx->saveBuf, SAVE_BUFFER_SIZE);

    // Read save file
    if (func_80185968(sramCtx->saveBuf, D_801C6840[fileNum * 2], D_801C6850[fileNum * 2]) != 0) {
        // If failed, read backup save file
        func_80185968(sramCtx->saveBuf, D_801C6840[fileNum * 2 + 1], D_801C6850[fileNum * 2 + 1]);
    }

    // Copy buffer to save context
    Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, offsetof(SaveContext, fileNum));

    func_80146EBC(sramCtx, D_801C6840[arg2 * 2], D_801C6850[arg2 * 2]);
    func_80146EBC(sramCtx, D_801C6840[arg2 * 2 + 1], D_801C6850[arg2 * 2]);
}

void Sram_nop8014750C(UNK_TYPE4 arg0) {
}
