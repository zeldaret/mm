#include <ultra64.h>
#include <global.h>

#define SCENE_ENTRY(name, textId, config) \
    { (u32) _##name##SegmentRomStart, (u32)_##name##SegmentRomEnd, textId, 0, config }

#define SCENE_ENTRY_NONE() \
    { 0, 0, 0, 0, 0 }

SceneTableEntry gSceneTable[] = {
    SCENE_ENTRY(Z2_20SICHITAI2, 0x0116, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY_NONE(),
    SCENE_ENTRY_NONE(),
    SCENE_ENTRY_NONE(),
    SCENE_ENTRY_NONE(),
    SCENE_ENTRY_NONE(),
    SCENE_ENTRY_NONE(),
    SCENE_ENTRY(KAKUSIANA, 0x0000, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(SPOT00, 0x0000, SCENE_DRAW_CFG_NOTHING),
    SCENE_ENTRY_NONE(),
    SCENE_ENTRY(Z2_WITCH_SHOP, 0x011A, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_LAST_BS, 0x0000, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_HAKASHITA, 0x0113, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_AYASHIISHOP, 0x010E, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY_NONE(),
    SCENE_ENTRY_NONE(),
    SCENE_ENTRY(Z2_OMOYA, 0x0132, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_BOWLING, 0x0108, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_SONCHONOIE, 0x010B, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_IKANA, 0x0141, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_KAIZOKU, 0x0000, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_MILK_BAR, 0x010C, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_INISIE_N, 0x0144, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_TAKARAYA, 0x0109, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_INISIE_R, 0x0144, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_OKUJOU, 0x0000, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_OPENINGDAN, 0x0000, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_MITURIN, 0x011F, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_13HUBUKINOMITI, 0x0000, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_CASTLE, 0x0142, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_DEKUTES, 0x0000, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_MITURIN_BS, 0x0000, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_SYATEKI_MIZU, 0x0107, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_HAKUGIN, 0x012B, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_ROMANYMAE, 0x0149, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_PIRATE, 0x0000, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_SYATEKI_MORI, 0x011B, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_SINKAI, 0x0135, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_YOUSEI_IZUMI, 0x013E, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_KINSTA1, 0x011E, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_KINDAN2, 0x013F, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_TENMON_DAI, 0x0114, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_LAST_DEKU, 0x0000, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_22DEKUCITY, 0x0118, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_KAJIYA, 0x0127, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_00KEIKOKU, 0x0100, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_POSTHOUSE, 0x0111, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_LABO, 0x013A, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_DANPEI2TEST, 0x0113, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY_NONE(),
    SCENE_ENTRY(Z2_16GORON_HOUSE, 0x0124, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_33ZORACITY, 0x0136, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_8ITEMSHOP, 0x010F, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_F01, 0x012E, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_INISIE_BS, 0x0000, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_30GYOSON, 0x0134, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_31MISAKI, 0x0134, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_TAKARAKUJI, 0x0112, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY_NONE(),
    SCENE_ENTRY(Z2_TORIDE, 0x0138, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_FISHERMAN, 0x013B, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_GORONSHOP, 0x0129, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_DEKU_KING, 0x011C, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_LAST_GORON, 0x0000, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_24KEMONOMITI, 0x0000, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_F01_B, 0x0130, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_F01C, 0x012F, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_BOTI, 0x0106, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_HAKUGIN_BS, 0x0000, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_20SICHITAI, 0x0116, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_21MITURINMAE, 0x0117, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_LAST_ZORA, 0x0000, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_11GORONNOSATO2, 0x0123, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_SEA, 0x013D, SCENE_DRAW_CFG_GREAT_BAY_TEMPLE),
    SCENE_ENTRY(Z2_35TAKI, 0x0137, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_REDEAD, 0x0145, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_BANDROOM, 0x0000, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_11GORONNOSATO, 0x0123, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_GORON_HAKA, 0x012A, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_SECOM, 0x0143, SCENE_DRAW_CFG_MAT_ANIM_MANUAL_STEP),
    SCENE_ENTRY(Z2_10YUKIYAMANOMURA, 0x0122, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_TOUGITES, 0x0146, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_DANPEI, 0x0120, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_IKANAMAE, 0x0000, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_DOUJOU, 0x0110, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_MUSICHOUSE, 0x0147, SCENE_DRAW_CFG_MAT_ANIM_MANUAL_STEP),
    SCENE_ENTRY(Z2_IKNINSIDE, 0x0142, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_MAP_SHOP, 0x0119, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_F40, 0x0140, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_F41, 0x0000, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_10YUKIYAMANOMURA2, 0x0122, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_14YUKIDAMANOMITI, 0x0000, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_12HAKUGINMAE, 0x0125, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_17SETUGEN, 0x0000, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_17SETUGEN2, 0x0000, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_SEA_BS, 0x0000, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_RANDOM, 0x012C, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_YADOYA, 0x010A, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_KONPEKI_ENT, 0x0139, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_INSIDETOWER, 0x0000, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_26SARUNOMORI, 0x011D, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_LOST_WOODS, 0x0000, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_LAST_LINK, 0x0000, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_SOUGEN, 0x0000, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_BOMYA, 0x010D, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_KYOJINNOMA, 0x0000, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_KOEPONARACE, 0x0131, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_GORONRACE, 0x0126, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_TOWN, 0x0101, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_ICHIBA, 0x0102, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_BACKTOWN, 0x0103, SCENE_DRAW_CFG_DEFAULT),
    SCENE_ENTRY(Z2_CLOCKTOWER, 0x0104, SCENE_DRAW_CFG_MAT_ANIM),
    SCENE_ENTRY(Z2_ALLEY, 0x0105, SCENE_DRAW_CFG_MAT_ANIM),
};

static EntranceTableEntry sMayorsResidenceEntrance0[] = {
    { 0x12, 0x00, 0x4102 },
};

static EntranceTableEntry sMayorsResidenceEntrance1[] = {
    { 0x12, 0x01, 0x4102 },
};

static EntranceTableEntry sMayorsResidenceEntrance2[] = {
    { 0x12, 0x02, 0x4102 },
};

static EntranceTableEntry* sMayorsResidenceEntranceTable[] = {
    sMayorsResidenceEntrance0,
    sMayorsResidenceEntrance1,
    sMayorsResidenceEntrance2,
};

static EntranceTableEntry sMajorasLairEntrance0[] = {
    { 0xF5, 0x00, 0x0387 },
};

static EntranceTableEntry* sMajorasLairEntranceTable[] = {
    sMajorasLairEntrance0,
};

static EntranceTableEntry sMagicHagsPotionShopEntrance0[] = {
    { 0x0A, 0x00, 0x4102 },
};

static EntranceTableEntry* sMagicHagsPotionShopEntranceTable[] = {
    sMagicHagsPotionShopEntrance0,
};

static EntranceTableEntry sRanchHouseEntrance0[] = {
    { 0x10, 0x00, 0x0102 },
};

static EntranceTableEntry sRanchHouseEntrance1[] = {
    { 0x10, 0x01, 0x4102 },
};

static EntranceTableEntry* sRanchHouseEntranceTable[] = {
    sRanchHouseEntrance0,
    sRanchHouseEntrance1,
};

static EntranceTableEntry sHoneyAndDarlingsShopEntrance0[] = {
    { 0x11, 0x00, 0x4102 },
};

static EntranceTableEntry* sHoneyAndDarlingsShopEntranceTable[] = {
    sHoneyAndDarlingsShopEntrance0,
};

static EntranceTableEntry sBeneathTheGraveryardEntrance0[] = {
    { 0xF4, 0x00, 0x4102 },
};

static EntranceTableEntry sBeneathTheGraveryardEntrance1[] = {
    { 0xF4, 0x01, 0x4102 },
};

static EntranceTableEntry* sBeneathTheGraveryardEntranceTable[] = {
    sBeneathTheGraveryardEntrance0,
    sBeneathTheGraveryardEntrance1,
};

static EntranceTableEntry sSouthernSwampClearedEntrance0[] = {
    { 0x00, 0x00, 0xCA14 },
};

static EntranceTableEntry sSouthernSwampClearedEntrance1[] = {
    { 0x00, 0x01, 0x4102 },
};

static EntranceTableEntry sSouthernSwampClearedEntrance2[] = {
    { 0x00, 0x02, 0xC102 },
};

static EntranceTableEntry sSouthernSwampClearedEntrance3[] = {
    { 0x00, 0x03, 0x4102 },
};

static EntranceTableEntry sSouthernSwampClearedEntrance4[] = {
    { 0x00, 0x04, 0x4102 },
};

static EntranceTableEntry sSouthernSwampClearedEntrance5[] = {
    { 0x00, 0x05, 0x4102 },
};

static EntranceTableEntry sSouthernSwampClearedEntrance6[] = {
    { 0x00, 0x06, 0x0102 },
};

static EntranceTableEntry sSouthernSwampClearedEntrance7[] = {
    { 0x00, 0x07, 0x4102 },
};

static EntranceTableEntry sSouthernSwampClearedEntrance8[] = {
    { 0x00, 0x08, 0x4102 },
};

static EntranceTableEntry sSouthernSwampClearedEntrance9[] = {
    { 0x00, 0x09, 0x4A14 },
};

static EntranceTableEntry sSouthernSwampClearedEntrance10[] = {
    { 0x00, 0x0A, 0x4A14 },
};

static EntranceTableEntry* sSouthernSwampClearedEntranceTable[] = {
    sSouthernSwampClearedEntrance0, sSouthernSwampClearedEntrance1,  sSouthernSwampClearedEntrance2,
    sSouthernSwampClearedEntrance3, sSouthernSwampClearedEntrance4,  sSouthernSwampClearedEntrance5,
    sSouthernSwampClearedEntrance6, sSouthernSwampClearedEntrance7,  sSouthernSwampClearedEntrance8,
    sSouthernSwampClearedEntrance9, sSouthernSwampClearedEntrance10,
};

static EntranceTableEntry sCuriosityShopEntrance0[] = {
    { 0x0D, 0x00, 0x4102 },
};

static EntranceTableEntry sCuriosityShopEntrance1[] = {
    { 0x0D, 0x01, 0x0102 },
};

static EntranceTableEntry sCuriosityShopEntrance2[] = {
    { 0x0D, 0x02, 0x8A95 },
};

static EntranceTableEntry sCuriosityShopEntrance3[] = {
    { 0x0D, 0x03, 0x8102 },
};

static EntranceTableEntry* sCuriosityShopEntranceTable[] = {
    sCuriosityShopEntrance0,
    sCuriosityShopEntrance1,
    sCuriosityShopEntrance2,
    sCuriosityShopEntrance3,
};

static EntranceTableEntry sIkanaCanyonEntrance0[] = {
    { 0x13, 0x00, 0xCA14 }, { 0x13, 0x00, 0x8A14 }, { 0x13, 0x00, 0x0A14 },
    { 0x13, 0x00, 0x4A14 }, { 0x13, 0x00, 0x8102 },
};

static EntranceTableEntry sIkanaCanyonEntrance1[] = {
    { 0x13, 0x01, 0x4102 },
    { 0x13, 0x01, 0x4102 },
    { 0x13, 0x01, 0xCA14 },
    { 0x13, 0x01, 0x4102 },
};

static EntranceTableEntry sIkanaCanyonEntrance2[] = {
    { 0x13, 0x02, 0x4102 },
    { 0x13, 0x02, 0x4102 },
    { 0x13, 0x02, 0x4102 },
    { 0x13, 0x02, 0x4102 },
};

static EntranceTableEntry sIkanaCanyonEntrance3[] = {
    { 0x13, 0x03, 0x4102 },
    { 0x13, 0x03, 0x4102 },
    { 0x13, 0x03, 0x4102 },
    { 0x13, 0x03, 0x4102 },
};

static EntranceTableEntry sIkanaCanyonEntrance4[] = {
    { 0x13, 0x04, 0x4A14 },
    { 0x13, 0x04, 0x4A14 },
    { 0x13, 0x04, 0x4A14 },
    { 0x13, 0x04, 0x4A14 },
};

static EntranceTableEntry sIkanaCanyonEntrance5[] = {
    { 0x13, 0x05, 0x4102 },
    { 0x13, 0x05, 0x4102 },
    { 0x13, 0x05, 0x4102 },
    { 0x13, 0x05, 0x4102 },
};

static EntranceTableEntry sIkanaCanyonEntrance6[] = {
    { 0x13, 0x06, 0x4102 },
    { 0x13, 0x06, 0x4102 },
    { 0x13, 0x06, 0x4102 },
    { 0x13, 0x06, 0x4102 },
};

static EntranceTableEntry sIkanaCanyonEntrance7[] = {
    { 0x13, 0x07, 0x4A14 },
    { 0x13, 0x07, 0x4A14 },
    { 0x13, 0x07, 0x4A14 },
    { 0x13, 0x07, 0x4A14 },
};

static EntranceTableEntry sIkanaCanyonEntrance8[] = {
    { 0x13, 0x08, 0x4102 },
    { 0x13, 0x08, 0x4102 },
    { 0x13, 0x08, 0x4102 },
    { 0x13, 0x08, 0x4102 },
};

static EntranceTableEntry sIkanaCanyonEntrance9[] = {
    { 0x13, 0x09, 0x4A14 },
    { 0x13, 0x09, 0x4A14 },
    { 0x13, 0x09, 0x4A14 },
    { 0x13, 0x09, 0x4A14 },
};

static EntranceTableEntry sIkanaCanyonEntrance10[] = {
    { 0x13, 0x0A, 0x4A14 },
    { 0x13, 0x0A, 0x4A14 },
    { 0x13, 0x0A, 0x4A14 },
    { 0x13, 0x0A, 0x4A14 },
};

static EntranceTableEntry sIkanaCanyonEntrance11[] = {
    { 0x13, 0x0B, 0x4102 },
    { 0x13, 0x0B, 0x4102 },
    { 0x13, 0x0B, 0x4102 },
    { 0x13, 0x0B, 0x4102 },
};

static EntranceTableEntry sIkanaCanyonEntrance12[] = {
    { 0x13, 0x0C, 0x4102 },
    { 0x13, 0x0C, 0x4102 },
    { 0x13, 0x0C, 0x4102 },
    { 0x13, 0x0C, 0x4102 },
};

static EntranceTableEntry sIkanaCanyonEntrance13[] = {
    { 0x13, 0x0D, 0x8102 },
    { 0x13, 0x0D, 0x8102 },
    { 0x13, 0x0D, 0x8102 },
    { 0x13, 0x0D, 0x8102 },
};

static EntranceTableEntry sIkanaCanyonEntrance14[] = {
    { 0x13, 0x0E, 0x8102 },
    { 0x13, 0x0E, 0x8102 },
    { 0x13, 0x0E, 0x8102 },
    { 0x13, 0x0E, 0x8102 },
};

static EntranceTableEntry sIkanaCanyonEntrance15[] = {
    { 0x13, 0x0F, 0x8102 },
    { 0x13, 0x0F, 0x8102 },
    { 0x13, 0x0F, 0x8102 },
    { 0x13, 0x0F, 0x0183 },
};

static EntranceTableEntry* sIkanaCanyonEntranceTable[] = {
    sIkanaCanyonEntrance0,  sIkanaCanyonEntrance1,  sIkanaCanyonEntrance2,  sIkanaCanyonEntrance3,
    sIkanaCanyonEntrance4,  sIkanaCanyonEntrance5,  sIkanaCanyonEntrance6,  sIkanaCanyonEntrance7,
    sIkanaCanyonEntrance8,  sIkanaCanyonEntrance9,  sIkanaCanyonEntrance10, sIkanaCanyonEntrance11,
    sIkanaCanyonEntrance12, sIkanaCanyonEntrance13, sIkanaCanyonEntrance14, sIkanaCanyonEntrance15,
};

static EntranceTableEntry sPiratesFortressEntrance0[] = {
    { 0x14, 0x00, 0x8102 },
    { 0x14, 0x00, 0x8102 },
    { 0x14, 0x00, 0x8102 },
};

static EntranceTableEntry sPiratesFortressEntrance1[] = {
    { 0x14, 0x01, 0x8102 },
    { 0x14, 0x01, 0x8102 },
};

static EntranceTableEntry sPiratesFortressEntrance2[] = {
    { 0x14, 0x02, 0x8102 },
};

static EntranceTableEntry sPiratesFortressEntrance3[] = {
    { 0x14, 0x03, 0x8102 },
};

static EntranceTableEntry sPiratesFortressEntrance4[] = {
    { 0x14, 0x04, 0x8102 },
};

static EntranceTableEntry sPiratesFortressEntrance5[] = {
    { 0x14, 0x05, 0x8102 },
};

static EntranceTableEntry sPiratesFortressEntrance6[] = {
    { 0x14, 0x06, 0x8102 },
};

static EntranceTableEntry sPiratesFortressEntrance7[] = {
    { 0x14, 0x07, 0x8102 },
};

static EntranceTableEntry sPiratesFortressEntrance8[] = {
    { 0x14, 0x08, 0x8102 },
};

static EntranceTableEntry sPiratesFortressEntrance9[] = {
    { 0x14, 0x09, 0x8102 },
};

static EntranceTableEntry sPiratesFortressEntrance10[] = {
    { 0x14, 0x0A, 0x8A95 },
};

static EntranceTableEntry sPiratesFortressEntrance11[] = {
    { 0x14, 0x0B, 0x8102 },
};

static EntranceTableEntry sPiratesFortressEntrance12[] = {
    { 0x14, 0x0C, 0x8102 },
};

static EntranceTableEntry sPiratesFortressEntrance13[] = {
    { 0x14, 0x0D, 0x8102 },
};

static EntranceTableEntry sPiratesFortressEntrance14[] = {
    { 0x14, 0x0E, 0x8102 },
};

static EntranceTableEntry* sPiratesFortressEntranceTable[] = {
    sPiratesFortressEntrance0,  sPiratesFortressEntrance1,  sPiratesFortressEntrance2,  sPiratesFortressEntrance3,
    sPiratesFortressEntrance4,  sPiratesFortressEntrance5,  sPiratesFortressEntrance6,  sPiratesFortressEntrance7,
    sPiratesFortressEntrance8,  sPiratesFortressEntrance9,  sPiratesFortressEntrance10, sPiratesFortressEntrance11,
    sPiratesFortressEntrance12, sPiratesFortressEntrance13, sPiratesFortressEntrance14,
};

static EntranceTableEntry sMilkBarEntrance0[] = {
    { 0x15, 0x00, 0x4102 }, { 0x15, 0x00, 0x8102 }, { 0x15, 0x00, 0x8102 },
    { 0x15, 0x00, 0x8102 }, { 0x15, 0x00, 0x8102 },
};

static EntranceTableEntry* sMilkBarEntranceTable[] = {
    sMilkBarEntrance0,
};

static EntranceTableEntry sStoneTowerTempleEntrance0[] = {
    { 0xEA, 0x00, 0xC102 },
};

static EntranceTableEntry sStoneTowerTempleEntrance1[] = {
    { 0xEA, 0x01, 0x4102 },
};

static EntranceTableEntry* sStoneTowerTempleEntranceTable[] = {
    sStoneTowerTempleEntrance0,
    sStoneTowerTempleEntrance1,
};

static EntranceTableEntry sTreasureChestShopEntrance0[] = {
    { 0x17, 0x00, 0x4102 },
};

static EntranceTableEntry sTreasureChestShopEntrance1[] = {
    { 0x17, 0x01, 0x0102 },
};

static EntranceTableEntry* sTreasureChestShopEntranceTable[] = {
    sTreasureChestShopEntrance0,
    sTreasureChestShopEntrance1,
};

static EntranceTableEntry sStoneTowerTempleReversedEntrance0[] = {
    { 0xE8, 0x00, 0xC102 },
};

static EntranceTableEntry sStoneTowerTempleReversedEntrance1[] = {
    { 0xE8, 0x01, 0x8102 },
};

static EntranceTableEntry sStoneTowerTempleReversedEntrance2[] = {
    { 0xE8, 0x02, 0x8102 },
};

static EntranceTableEntry* sStoneTowerTempleReversedEntranceTable[] = {
    sStoneTowerTempleReversedEntrance0,
    sStoneTowerTempleReversedEntrance1,
    sStoneTowerTempleReversedEntrance2,
};

static EntranceTableEntry sClockTowerRooftopEntrance0[] = {
    { 0xE7, 0x00, 0x0102 },
    { 0xE7, 0x00, 0x8102 },
    { 0xE7, 0x00, 0x0102 },
    { 0xE7, 0x00, 0x0102 },
};

static EntranceTableEntry sClockTowerRooftopEntrance1[] = {
    { 0xE7, 0x01, 0x0102 },
    { 0xE7, 0x01, 0x0102 },
    { 0xE7, 0x01, 0x0102 },
};

static EntranceTableEntry sClockTowerRooftopEntrance2[] = {
    { 0xE7, 0x02, 0x858B },
    { 0xE7, 0x02, 0x858B },
    { 0xE7, 0x02, 0x8102 },
};

static EntranceTableEntry* sClockTowerRooftopEntranceTable[] = {
    sClockTowerRooftopEntrance0,
    sClockTowerRooftopEntrance1,
    sClockTowerRooftopEntrance2,
};

static EntranceTableEntry sOpeningDungeonEntrance0[] = {
    { 0xE6, 0x00, 0x0102 },
    { 0xE6, 0x00, 0x8102 },
};

static EntranceTableEntry sOpeningDungeonEntrance1[] = {
    { 0xE6, 0x01, 0x0102 },
};

static EntranceTableEntry sOpeningDungeonEntrance2[] = {
    { 0xE6, 0x02, 0x0102 },
};

static EntranceTableEntry sOpeningDungeonEntrance3[] = {
    { 0xE6, 0x03, 0x0102 },
};

static EntranceTableEntry sOpeningDungeonEntrance4[] = {
    { 0xE6, 0x04, 0x058B },
};

static EntranceTableEntry* sOpeningDungeonEntranceTable[] = {
    sOpeningDungeonEntrance0, sOpeningDungeonEntrance1, sOpeningDungeonEntrance2,
    sOpeningDungeonEntrance3, sOpeningDungeonEntrance4,
};

static EntranceTableEntry sWoodfallTempleEntrance0[] = {
    { 0xE5, 0x00, 0x4102 },
};

static EntranceTableEntry sWoodfallTempleEntrance1[] = {
    { 0xE5, 0x01, 0x0102 },
};

static EntranceTableEntry sWoodfallTempleEntrance2[] = {
    { 0xE5, 0x02, 0x0102 },
};

static EntranceTableEntry* sWoodfallTempleEntranceTable[] = {
    sWoodfallTempleEntrance0,
    sWoodfallTempleEntrance1,
    sWoodfallTempleEntrance2,
};

static EntranceTableEntry sPathToMountainVillageEntrance0[] = {
    { 0x1C, 0x00, 0x8A14 },
    { 0x1C, 0x00, 0x8A14 },
};

static EntranceTableEntry sPathToMountainVillageEntrance1[] = {
    { 0x1C, 0x01, 0x8A14 },
    { 0x1C, 0x01, 0x8A14 },
};

static EntranceTableEntry* sPathToMountainVillageEntranceTable[] = {
    sPathToMountainVillageEntrance0,
    sPathToMountainVillageEntrance1,
};

static EntranceTableEntry sIkanaCastleEntrance0[] = {
    { 0xE3, 0x00, 0x4102 },
};

static EntranceTableEntry sIkanaCastleEntrance1[] = {
    { 0xE3, 0x01, 0x4102 },
};

static EntranceTableEntry sIkanaCastleEntrance2[] = {
    { 0xE3, 0x02, 0x8102 },
};

static EntranceTableEntry sIkanaCastleEntrance3[] = {
    { 0xE3, 0x03, 0x8102 },
};

static EntranceTableEntry sIkanaCastleEntrance4[] = {
    { 0xE3, 0x04, 0x8102 },
};

static EntranceTableEntry sIkanaCastleEntrance5[] = {
    { 0xE3, 0x05, 0x8102 },
};

static EntranceTableEntry sIkanaCastleEntrance6[] = {
    { 0xE3, 0x06, 0x8102 },
};

static EntranceTableEntry* sIkanaCastleEntranceTable[] = {
    sIkanaCastleEntrance0, sIkanaCastleEntrance1, sIkanaCastleEntrance2, sIkanaCastleEntrance3,
    sIkanaCastleEntrance4, sIkanaCastleEntrance5, sIkanaCastleEntrance6,
};

static EntranceTableEntry sDekuScrubPlaygroundEntrance0[] = {
    { 0x1E, 0x00, 0x0102 },
};

static EntranceTableEntry sDekuScrubPlaygroundEntrance1[] = {
    { 0x1E, 0x01, 0x0102 },
};

static EntranceTableEntry* sDekuScrubPlaygroundEntranceTable[] = {
    sDekuScrubPlaygroundEntrance0,
    sDekuScrubPlaygroundEntrance1,
};

static EntranceTableEntry sOdolwasLairEntrance0[] = {
    { 0xE1, 0x00, 0x8102 },
};

static EntranceTableEntry* sOdolwasLairEntranceTable[] = {
    sOdolwasLairEntrance0,
};

static EntranceTableEntry sTownShootingGalleryEntrance0[] = {
    { 0x20, 0x00, 0x4102 },
};

static EntranceTableEntry sTownShootingGalleryEntrance1[] = {
    { 0x20, 0x01, 0x0102 },
};

static EntranceTableEntry* sTownShootingGalleryEntranceTable[] = {
    sTownShootingGalleryEntrance0,
    sTownShootingGalleryEntrance1,
};

static EntranceTableEntry sSnowheadTempleEntrance0[] = {
    { 0xDF, 0x00, 0x4102 },
};

static EntranceTableEntry sSnowheadTempleEntrance1[] = {
    { 0xDF, 0x01, 0x4102 },
};

static EntranceTableEntry* sSnowheadTempleEntranceTable[] = {
    sSnowheadTempleEntrance0,
    sSnowheadTempleEntrance1,
};

static EntranceTableEntry sMilkRoadEntrance0[] = {
    { 0x22, 0x00, 0xCA14 },
};

static EntranceTableEntry sMilkRoadEntrance1[] = {
    { 0x22, 0x01, 0x4A14 },
};

static EntranceTableEntry sMilkRoadEntrance2[] = {
    { 0x22, 0x02, 0x4A14 },
};

static EntranceTableEntry sMilkRoadEntrance3[] = {
    { 0x22, 0x03, 0x4A14 },
};

static EntranceTableEntry sMilkRoadEntrance4[] = {
    { 0x22, 0x04, 0x4A14 },
};

static EntranceTableEntry sMilkRoadEntrance5[] = {
    { 0x22, 0x05, 0x0102 },
};

static EntranceTableEntry sMilkRoadEntrance6[] = {
    { 0x22, 0x06, 0x0102 },
};

static EntranceTableEntry* sMilkRoadEntranceTable[] = {
    sMilkRoadEntrance0, sMilkRoadEntrance1, sMilkRoadEntrance2, sMilkRoadEntrance3,
    sMilkRoadEntrance4, sMilkRoadEntrance5, sMilkRoadEntrance6,
};

static EntranceTableEntry sPiratesFortressInteriorEntrance0[] = {
    { 0x23, 0x00, 0x8102 },
};

static EntranceTableEntry sPiratesFortressInteriorEntrance1[] = {
    { 0x23, 0x01, 0x8102 },
};

static EntranceTableEntry sPiratesFortressInteriorEntrance2[] = {
    { 0x23, 0x02, 0x8102 },
};

static EntranceTableEntry sPiratesFortressInteriorEntrance3[] = {
    { 0x23, 0x03, 0x8102 },
};

static EntranceTableEntry sPiratesFortressInteriorEntrance4[] = {
    { 0x23, 0x04, 0x8102 },
};

static EntranceTableEntry sPiratesFortressInteriorEntrance5[] = {
    { 0x23, 0x05, 0x8102 },
};

static EntranceTableEntry sPiratesFortressInteriorEntrance6[] = {
    { 0x23, 0x06, 0x8102 },
};

static EntranceTableEntry sPiratesFortressInteriorEntrance7[] = {
    { 0x23, 0x07, 0x8102 },
};

static EntranceTableEntry sPiratesFortressInteriorEntrance8[] = {
    { 0x23, 0x08, 0x8102 },
};

static EntranceTableEntry sPiratesFortressInteriorEntrance9[] = {
    { 0x23, 0x09, 0x8993 },
};

static EntranceTableEntry sPiratesFortressInteriorEntrance10[] = {
    { 0x23, 0x0A, 0x8102 },
};

static EntranceTableEntry sPiratesFortressInteriorEntrance11[] = {
    { 0x23, 0x0B, 0x8102 },
};

static EntranceTableEntry sPiratesFortressInteriorEntrance12[] = {
    { 0x23, 0x0C, 0x8102 },
};

static EntranceTableEntry sPiratesFortressInteriorEntrance13[] = {
    { 0x23, 0x0D, 0x8102 },
};

static EntranceTableEntry sPiratesFortressInteriorEntrance14[] = {
    { 0x23, 0x0E, 0x8102 },
};

static EntranceTableEntry sPiratesFortressInteriorEntrance15[] = {
    { 0x23, 0x0F, 0x8102 },
};

static EntranceTableEntry* sPiratesFortressInteriorEntranceTable[] = {
    sPiratesFortressInteriorEntrance0,  sPiratesFortressInteriorEntrance1,  sPiratesFortressInteriorEntrance2,
    sPiratesFortressInteriorEntrance3,  sPiratesFortressInteriorEntrance4,  sPiratesFortressInteriorEntrance5,
    sPiratesFortressInteriorEntrance6,  sPiratesFortressInteriorEntrance7,  sPiratesFortressInteriorEntrance8,
    sPiratesFortressInteriorEntrance9,  sPiratesFortressInteriorEntrance10, sPiratesFortressInteriorEntrance11,
    sPiratesFortressInteriorEntrance12, sPiratesFortressInteriorEntrance13, sPiratesFortressInteriorEntrance14,
    sPiratesFortressInteriorEntrance15,
};

static EntranceTableEntry sSwampShootingGalleryEntrance0[] = {
    { 0x24, 0x00, 0x4102 },
};

static EntranceTableEntry* sSwampShootingGalleryEntranceTable[] = {
    sSwampShootingGalleryEntrance0,
};

static EntranceTableEntry sPinaccleRockEntrance0[] = {
    { 0x25, 0x00, 0x4A14 },
};

static EntranceTableEntry sPinaccleRockEntrance1[] = {
    { 0x25, 0x01, 0x0A14 },
};

static EntranceTableEntry* sPinaccleRockEntranceTable[] = {
    sPinaccleRockEntrance0,
    sPinaccleRockEntrance1,
};

static EntranceTableEntry sFairyFountainEntrance0[] = {
    { 0x26, 0x00, 0x4102 },
    { 0x26, 0x00, 0x8102 },
};

static EntranceTableEntry sFairyFountainEntrance1[] = {
    { 0x26, 0x01, 0x4102 },
};

static EntranceTableEntry sFairyFountainEntrance2[] = {
    { 0x26, 0x02, 0x4102 },
};

static EntranceTableEntry sFairyFountainEntrance3[] = {
    { 0x26, 0x03, 0x4102 },
};

static EntranceTableEntry sFairyFountainEntrance4[] = {
    { 0x26, 0x04, 0x4102 },
};

static EntranceTableEntry sFairyFountainEntrance5[] = {
    { 0x26, 0x05, 0x8183 },
};

static EntranceTableEntry sFairyFountainEntrance6[] = {
    { 0x26, 0x06, 0x858B },
};

static EntranceTableEntry sFairyFountainEntrance7[] = {
    { 0x26, 0x07, 0x858B },
};

static EntranceTableEntry sFairyFountainEntrance8[] = {
    { 0x26, 0x08, 0x858B },
};

static EntranceTableEntry sFairyFountainEntrance9[] = {
    { 0x26, 0x09, 0x858B },
};

static EntranceTableEntry* sFairyFountainEntranceTable[] = {
    sFairyFountainEntrance0, sFairyFountainEntrance1, sFairyFountainEntrance2, sFairyFountainEntrance3,
    sFairyFountainEntrance4, sFairyFountainEntrance5, sFairyFountainEntrance6, sFairyFountainEntrance7,
    sFairyFountainEntrance8, sFairyFountainEntrance9,
};

static EntranceTableEntry sSwampSpiderHouseEntrance0[] = {
    { 0xD9, 0x00, 0x4102 },
};

static EntranceTableEntry* sSwampSpiderHouseEntranceTable[] = {
    sSwampSpiderHouseEntrance0,
};

static EntranceTableEntry sOceansideSpiderHouseEntrance0[] = {
    { 0xD8, 0x00, 0x4102 },
};

static EntranceTableEntry* sOceansideSpiderHouseEntranceTable[] = {
    sOceansideSpiderHouseEntrance0,
};

static EntranceTableEntry sAstralObservatoryEntrance0[] = {
    { 0x29, 0x00, 0x0102 },
};

static EntranceTableEntry sAstralObservatoryEntrance1[] = {
    { 0x29, 0x01, 0x4102 },
};

static EntranceTableEntry sAstralObservatoryEntrance2[] = {
    { 0x29, 0x02, 0x8115 },
};

static EntranceTableEntry* sAstralObservatoryEntranceTable[] = {
    sAstralObservatoryEntrance0,
    sAstralObservatoryEntrance1,
    sAstralObservatoryEntrance2,
};

static EntranceTableEntry sMoonDekuTrialEntrance0[] = {
    { 0xD6, 0x00, 0x0387 },
};

static EntranceTableEntry* sMoonDekuTrialEntranceTable[] = {
    sMoonDekuTrialEntrance0,
};

static EntranceTableEntry sDekuPalaceEntrance0[] = {
    { 0x2B, 0x00, 0x4102 },
};

static EntranceTableEntry sDekuPalaceEntrance1[] = {
    { 0x2B, 0x01, 0x8A14 },
};

static EntranceTableEntry sDekuPalaceEntrance2[] = {
    { 0x2B, 0x02, 0xC102 },
};

static EntranceTableEntry sDekuPalaceEntrance3[] = {
    { 0x2B, 0x03, 0xC102 },
};

static EntranceTableEntry sDekuPalaceEntrance4[] = {
    { 0x2B, 0x04, 0x4102 },
};

static EntranceTableEntry sDekuPalaceEntrance5[] = {
    { 0x2B, 0x05, 0x4102 },
};

static EntranceTableEntry sDekuPalaceEntrance6[] = {
    { 0x2B, 0x06, 0x4102 },
};

static EntranceTableEntry sDekuPalaceEntrance7[] = {
    { 0x2B, 0x07, 0x4102 },
};

static EntranceTableEntry sDekuPalaceEntrance8[] = {
    { 0x2B, 0x08, 0x4102 },
};

static EntranceTableEntry sDekuPalaceEntrance9[] = {
    { 0x2B, 0x09, 0x4102 },
};

static EntranceTableEntry sDekuPalaceEntrance10[] = {
    { 0x2B, 0x0A, 0x4102 },
};

static EntranceTableEntry* sDekuPalaceEntranceTable[] = {
    sDekuPalaceEntrance0, sDekuPalaceEntrance1, sDekuPalaceEntrance2,  sDekuPalaceEntrance3,
    sDekuPalaceEntrance4, sDekuPalaceEntrance5, sDekuPalaceEntrance6,  sDekuPalaceEntrance7,
    sDekuPalaceEntrance8, sDekuPalaceEntrance9, sDekuPalaceEntrance10,
};

static EntranceTableEntry sMountainSmithyEntrance0[] = {
    { 0x2C, 0x00, 0x4102 },
};

static EntranceTableEntry* sMountainSmithyEntranceTable[] = {
    sMountainSmithyEntrance0,
};

static EntranceTableEntry sTerminaFieldEntrance0[] = {
    { 0x2D, 0x00, 0x4102 }, { 0xD3, 0x00, 0x0A14 }, { 0xD3, 0x00, 0x0A14 }, { 0xD3, 0x00, 0x058B },
    { 0x2D, 0x00, 0x0A14 }, { 0x2D, 0x00, 0x0A14 }, { 0x2D, 0x00, 0x058B }, { 0x2D, 0x00, 0x8102 },
    { 0x2D, 0x00, 0x0102 }, { 0x2D, 0x00, 0x8102 },
};

static EntranceTableEntry sTerminaFieldEntrance1[] = {
    { 0x2D, 0x01, 0xCA14 }, { 0x2D, 0x01, 0x0A14 }, { 0x2D, 0x01, 0x058B }, { 0xD3, 0x01, 0x858B },
    { 0x2D, 0x01, 0x0A14 }, { 0x2D, 0x01, 0x0A14 }, { 0x2D, 0x01, 0x058B }, { 0x2D, 0x01, 0x858B },
    { 0x2D, 0x01, 0x0102 }, { 0x2D, 0x01, 0x8102 },
};

static EntranceTableEntry sTerminaFieldEntrance2[] = {
    { 0x2D, 0x02, 0xCA14 }, { 0xD3, 0x02, 0x0A14 }, { 0xD3, 0x02, 0x0A14 },
    { 0xD3, 0x02, 0x058B }, { 0x2D, 0x02, 0x0A14 }, { 0x2D, 0x02, 0x0A14 },
};

static EntranceTableEntry sTerminaFieldEntrance3[] = {
    { 0x2D, 0x03, 0xCA14 }, { 0xD3, 0x03, 0x0A14 }, { 0xD3, 0x03, 0x0A14 },
    { 0xD3, 0x03, 0x058B }, { 0x2D, 0x03, 0x0A14 }, { 0x2D, 0x03, 0x0A14 },
};

static EntranceTableEntry sTerminaFieldEntrance4[] = {
    { 0x2D, 0x04, 0xCA14 }, { 0xD3, 0x04, 0x0A14 }, { 0xD3, 0x04, 0x0A14 },
    { 0xD3, 0x04, 0x058B }, { 0x2D, 0x04, 0x0A14 }, { 0x2D, 0x04, 0x0A14 },
};

static EntranceTableEntry sTerminaFieldEntrance5[] = {
    { 0x2D, 0x05, 0xCA14 }, { 0xD3, 0x05, 0x0A14 }, { 0xD3, 0x05, 0x0A14 },
    { 0xD3, 0x05, 0x858B }, { 0x2D, 0x05, 0x0A14 }, { 0x2D, 0x05, 0x0A14 },
};

static EntranceTableEntry sTerminaFieldEntrance6[] = {
    { 0x2D, 0x06, 0x4102 }, { 0xD3, 0x06, 0x0A14 }, { 0xD3, 0x06, 0x0A14 },
    { 0xD3, 0x06, 0x858B }, { 0x2D, 0x06, 0x0A14 }, { 0x2D, 0x06, 0x0A14 },
};

static EntranceTableEntry sTerminaFieldEntrance7[] = {
    { 0x2D, 0x07, 0x4102 }, { 0xD3, 0x07, 0x0A14 }, { 0xD3, 0x07, 0x0A14 },
    { 0xD3, 0x07, 0x858B }, { 0x2D, 0x07, 0x0A14 }, { 0x2D, 0x07, 0x0A14 },
};

static EntranceTableEntry sTerminaFieldEntrance8[] = {
    { 0x2D, 0x08, 0x4102 }, { 0xD3, 0x08, 0x0A14 }, { 0xD3, 0x08, 0x0A14 },
    { 0xD3, 0x08, 0x058B }, { 0x2D, 0x08, 0x0A14 }, { 0x2D, 0x08, 0x0A14 },
};

static EntranceTableEntry sTerminaFieldEntrance9[] = {
    { 0x2D, 0x09, 0x4102 }, { 0xD3, 0x09, 0x0A14 }, { 0xD3, 0x09, 0x0A14 },
    { 0xD3, 0x09, 0x058B }, { 0x2D, 0x09, 0x0A14 }, { 0x2D, 0x09, 0x0A14 },
};

static EntranceTableEntry sTerminaFieldEntrance10[] = {
    { 0x2D, 0x0A, 0x8A95 }, { 0xD3, 0x0A, 0x0A14 }, { 0xD3, 0x0A, 0x0A14 },
    { 0xD3, 0x0A, 0x058B }, { 0x2D, 0x0A, 0x0A14 }, { 0x2D, 0x0A, 0x0A95 },
};

static EntranceTableEntry sTerminaFieldEntrance11[] = {
    { 0x2D, 0x0B, 0x4A14 }, { 0xD3, 0x0B, 0x0A14 }, { 0xD3, 0x0B, 0x0A14 },
    { 0xD3, 0x0B, 0x058B }, { 0x2D, 0x0B, 0x0A14 }, { 0x2D, 0x0B, 0x0A14 },
};

static EntranceTableEntry sTerminaFieldEntrance12[] = {
    { 0x2D, 0x0C, 0x0A14 }, { 0xD3, 0x0C, 0x0A14 }, { 0xD3, 0x0C, 0x0A14 },
    { 0xD3, 0x0C, 0x058B }, { 0x2D, 0x0C, 0x0A14 }, { 0x2D, 0x0C, 0x0A14 },
};

static EntranceTableEntry sTerminaFieldEntrance13[] = {
    { 0x2D, 0x0D, 0x0A14 }, { 0xD3, 0x0D, 0x0A14 }, { 0xD3, 0x0D, 0x0A14 },
    { 0xD3, 0x0D, 0x058B }, { 0x2D, 0x0D, 0x0A14 }, { 0x2D, 0x0D, 0x0A14 },
};

static EntranceTableEntry sTerminaFieldEntrance14[] = {
    { 0x2D, 0x0E, 0x858B },
};

static EntranceTableEntry* sTerminaFieldEntranceTable[] = {
    sTerminaFieldEntrance0,  sTerminaFieldEntrance1,  sTerminaFieldEntrance2,  sTerminaFieldEntrance3,
    sTerminaFieldEntrance4,  sTerminaFieldEntrance5,  sTerminaFieldEntrance6,  sTerminaFieldEntrance7,
    sTerminaFieldEntrance8,  sTerminaFieldEntrance9,  sTerminaFieldEntrance10, sTerminaFieldEntrance11,
    sTerminaFieldEntrance12, sTerminaFieldEntrance13, sTerminaFieldEntrance14,
};

static EntranceTableEntry sPostOfficeEntrance0[] = {
    { 0x2E, 0x00, 0x4102 },
};

static EntranceTableEntry* sPostOfficeEntranceTable[] = {
    sPostOfficeEntrance0,
};

static EntranceTableEntry sMarineResearchLabEntrance0[] = {
    { 0x2F, 0x00, 0x4102 },
};

static EntranceTableEntry* sMarineResearchLabEntranceTable[] = {
    sMarineResearchLabEntrance0,
};

static EntranceTableEntry sDampesHouseEntrance0[] = {
    { 0x30, 0x00, 0x4102 },
};

static EntranceTableEntry sDampesHouseEntrance1[] = {
    { 0x30, 0x01, 0x0102 },
};

static EntranceTableEntry* sDampesHouseEntranceTable[] = {
    sDampesHouseEntrance0,
    sDampesHouseEntrance1,
};

static EntranceTableEntry sGoronShrineEntrance0[] = {
    { 0x32, 0x00, 0x4102 },
    { 0x32, 0x00, 0x4102 },
};

static EntranceTableEntry sGoronShrineEntrance1[] = {
    { 0x32, 0x01, 0x0102 },
    { 0x32, 0x01, 0x0102 },
};

static EntranceTableEntry sGoronShrineEntrance2[] = {
    { 0x32, 0x02, 0x058B },
    { 0x32, 0x02, 0x058B },
};

static EntranceTableEntry sGoronShrineEntrance3[] = {
    { 0x32, 0x03, 0x0102 },
    { 0x32, 0x03, 0x0102 },
};

static EntranceTableEntry* sGoronShrineEntranceTable[] = {
    sGoronShrineEntrance0,
    sGoronShrineEntrance1,
    sGoronShrineEntrance2,
    sGoronShrineEntrance3,
};

static EntranceTableEntry sZoraHallEntrance0[] = {
    { 0x33, 0x00, 0x4993 },
    { 0x33, 0x00, 0x8102 },
};

static EntranceTableEntry sZoraHallEntrance1[] = {
    { 0x33, 0x01, 0x4102 },
};

static EntranceTableEntry sZoraHallEntrance2[] = {
    { 0x33, 0x02, 0x4102 },
};

static EntranceTableEntry sZoraHallEntrance3[] = {
    { 0x33, 0x03, 0x4102 },
};

static EntranceTableEntry sZoraHallEntrance4[] = {
    { 0x33, 0x04, 0x4102 },
};

static EntranceTableEntry sZoraHallEntrance5[] = {
    { 0x33, 0x05, 0x4102 },
};

static EntranceTableEntry sZoraHallEntrance6[] = {
    { 0x33, 0x06, 0x4102 },
};

static EntranceTableEntry sZoraHallEntrance7[] = {
    { 0x33, 0x07, 0x058B },
};

static EntranceTableEntry sZoraHallEntrance8[] = {
    { 0x33, 0x08, 0x8183 },
};

static EntranceTableEntry* sZoraHallEntranceTable[] = {
    sZoraHallEntrance0, sZoraHallEntrance1, sZoraHallEntrance2, sZoraHallEntrance3, sZoraHallEntrance4,
    sZoraHallEntrance5, sZoraHallEntrance6, sZoraHallEntrance7, sZoraHallEntrance8,
};

static EntranceTableEntry sTradingPostEntrance0[] = {
    { 0x34, 0x00, 0x4102 },
};

static EntranceTableEntry sTradingPostEntrance1[] = {
    { 0x34, 0x01, 0x0102 },
};

static EntranceTableEntry* sTradingPostEntranceTable[] = {
    sTradingPostEntrance0,
    sTradingPostEntrance1,
};

static EntranceTableEntry sRomaniRanchEntrance0[] = {
    { 0x35, 0x00, 0x4A14 }, { 0x35, 0x00, 0x0A14 }, { 0x35, 0x00, 0x8102 }, { 0x35, 0x00, 0x858B },
    { 0x35, 0x00, 0x858B }, { 0x35, 0x00, 0x0102 }, { 0x35, 0x00, 0x8102 },
};

static EntranceTableEntry sRomaniRanchEntrance1[] = {
    { 0x35, 0x01, 0x0A14 },
};

static EntranceTableEntry sRomaniRanchEntrance2[] = {
    { 0x35, 0x02, 0x0102 },
};

static EntranceTableEntry sRomaniRanchEntrance3[] = {
    { 0x35, 0x03, 0x0102 },
};

static EntranceTableEntry sRomaniRanchEntrance4[] = {
    { 0x35, 0x04, 0x8102 },
};

static EntranceTableEntry sRomaniRanchEntrance5[] = {
    { 0x35, 0x05, 0x8102 },
};

static EntranceTableEntry sRomaniRanchEntrance6[] = {
    { 0x35, 0x06, 0x0A14 },
};

static EntranceTableEntry sRomaniRanchEntrance7[] = {
    { 0x35, 0x07, 0x0A14 },
};

static EntranceTableEntry sRomaniRanchEntrance8[] = {
    { 0x35, 0x08, 0x0A14 },
};

static EntranceTableEntry sRomaniRanchEntrance9[] = {
    { 0x35, 0x09, 0x0102 },
};

static EntranceTableEntry sRomaniRanchEntrance10[] = {
    { 0x35, 0x0A, 0x0102 },
};

static EntranceTableEntry sRomaniRanchEntrance11[] = {
    { 0x35, 0x0B, 0x0102 },
};

static EntranceTableEntry* sRomaniRanchEntranceTable[] = {
    sRomaniRanchEntrance0, sRomaniRanchEntrance1, sRomaniRanchEntrance2,  sRomaniRanchEntrance3,
    sRomaniRanchEntrance4, sRomaniRanchEntrance5, sRomaniRanchEntrance6,  sRomaniRanchEntrance7,
    sRomaniRanchEntrance8, sRomaniRanchEntrance9, sRomaniRanchEntrance10, sRomaniRanchEntrance11,
};

static EntranceTableEntry sTwinmoldsLairEntrance0[] = {
    { 0xCA, 0x00, 0x0102 },
};

static EntranceTableEntry sTwinmoldsLairEntrance1[] = {
    { 0xCA, 0x01, 0x0102 },
};

static EntranceTableEntry sTwinmoldsLairEntrance2[] = {
    { 0xCA, 0x02, 0x0102 },
};

static EntranceTableEntry sTwinmoldsLairEntrance3[] = {
    { 0xCA, 0x03, 0x0102 },
};

static EntranceTableEntry sTwinmoldsLairEntrance4[] = {
    { 0xCA, 0x04, 0x0102 },
};

static EntranceTableEntry* sTwinmoldsLairEntranceTable[] = {
    sTwinmoldsLairEntrance0, sTwinmoldsLairEntrance1, sTwinmoldsLairEntrance2,
    sTwinmoldsLairEntrance3, sTwinmoldsLairEntrance4,
};

static EntranceTableEntry sGreatBayCoastEntrance0[] = {
    { 0x37, 0x00, 0xCA14 },
    { 0x37, 0x00, 0xCA14 },
    { 0x37, 0x00, 0x8102 },
};

static EntranceTableEntry sGreatBayCoastEntrance1[] = {
    { 0x37, 0x01, 0xCA14 },
    { 0x37, 0x01, 0xCA14 },
};

static EntranceTableEntry sGreatBayCoastEntrance2[] = {
    { 0x37, 0x02, 0x4993 },
    { 0x37, 0x02, 0x4993 },
};

static EntranceTableEntry sGreatBayCoastEntrance3[] = {
    { 0x37, 0x03, 0x4A14 },
    { 0x37, 0x03, 0x4A14 },
};

static EntranceTableEntry sGreatBayCoastEntrance4[] = {
    { 0x37, 0x04, 0x4102 },
    { 0x37, 0x04, 0x4102 },
};

static EntranceTableEntry sGreatBayCoastEntrance5[] = {
    { 0x37, 0x05, 0x4993 },
    { 0x37, 0x05, 0x4993 },
};

static EntranceTableEntry sGreatBayCoastEntrance6[] = {
    { 0x37, 0x06, 0x4993 },
    { 0x37, 0x06, 0x4993 },
};

static EntranceTableEntry sGreatBayCoastEntrance7[] = {
    { 0x37, 0x07, 0x4102 },
    { 0x37, 0x07, 0x4102 },
};

static EntranceTableEntry sGreatBayCoastEntrance8[] = {
    { 0x37, 0x08, 0x4102 },
    { 0x37, 0x08, 0x4102 },
};

static EntranceTableEntry sGreatBayCoastEntrance9[] = {
    { 0x37, 0x09, 0x058B },
    { 0x37, 0x09, 0x058B },
};

static EntranceTableEntry sGreatBayCoastEntrance10[] = {
    { 0x37, 0x0A, 0x858B },
    { 0x37, 0x0A, 0x858B },
};

static EntranceTableEntry sGreatBayCoastEntrance11[] = {
    { 0x37, 0x0B, 0x0A14 },
    { 0x37, 0x0B, 0x0A14 },
};

static EntranceTableEntry sGreatBayCoastEntrance12[] = {
    { 0x37, 0x0C, 0x0A14 },
    { 0x37, 0x0C, 0x0A14 },
};

static EntranceTableEntry sGreatBayCoastEntrance13[] = {
    { 0x37, 0x0D, 0x0A14 },
    { 0x37, 0x0D, 0x0A14 },
};

static EntranceTableEntry* sGreatBayCoastEntranceTable[] = {
    sGreatBayCoastEntrance0,  sGreatBayCoastEntrance1,  sGreatBayCoastEntrance2,  sGreatBayCoastEntrance3,
    sGreatBayCoastEntrance4,  sGreatBayCoastEntrance5,  sGreatBayCoastEntrance6,  sGreatBayCoastEntrance7,
    sGreatBayCoastEntrance8,  sGreatBayCoastEntrance9,  sGreatBayCoastEntrance10, sGreatBayCoastEntrance11,
    sGreatBayCoastEntrance12, sGreatBayCoastEntrance13,
};

static EntranceTableEntry sZoraCapeEntrance0[] = {
    { 0x38, 0x00, 0x8A14 },
    { 0x38, 0x00, 0x8A14 },
};

static EntranceTableEntry sZoraCapeEntrance1[] = {
    { 0x38, 0x01, 0x4993 },
    { 0x38, 0x01, 0x4993 },
};

static EntranceTableEntry sZoraCapeEntrance2[] = {
    { 0x38, 0x02, 0x4102 },
    { 0x38, 0x02, 0x4102 },
};

static EntranceTableEntry sZoraCapeEntrance3[] = {
    { 0x38, 0x03, 0x0993 },
    { 0x38, 0x03, 0x0993 },
};

static EntranceTableEntry sZoraCapeEntrance4[] = {
    { 0x38, 0x04, 0x4102 },
    { 0x38, 0x04, 0x4102 },
};

static EntranceTableEntry sZoraCapeEntrance5[] = {
    { 0x38, 0x05, 0x0102 },
    { 0x38, 0x05, 0x0102 },
};

static EntranceTableEntry sZoraCapeEntrance6[] = {
    { 0x38, 0x06, 0x0A14 },
    { 0x38, 0x06, 0x0A14 },
};

static EntranceTableEntry sZoraCapeEntrance7[] = {
    { 0x38, 0x07, 0x0A14 },
    { 0x38, 0x07, 0x0A14 },
};

static EntranceTableEntry sZoraCapeEntrance8[] = {
    { 0x38, 0x08, 0x0A14 },
    { 0x38, 0x08, 0x0A14 },
};

static EntranceTableEntry sZoraCapeEntrance9[] = {
    { 0x38, 0x09, 0x0A14 },
    { 0x38, 0x09, 0x0A14 },
};

static EntranceTableEntry* sZoraCapeEntranceTable[] = {
    sZoraCapeEntrance0, sZoraCapeEntrance1, sZoraCapeEntrance2, sZoraCapeEntrance3, sZoraCapeEntrance4,
    sZoraCapeEntrance5, sZoraCapeEntrance6, sZoraCapeEntrance7, sZoraCapeEntrance8, sZoraCapeEntrance9,
};

static EntranceTableEntry sLotteryShopEntrance0[] = {
    { 0x39, 0x00, 0x4102 },
};

static EntranceTableEntry* sLotteryShopEntranceTable[] = {
    sLotteryShopEntrance0,
};

static EntranceTableEntry sPiratesFortressExteriorEntrance0[] = {
    { 0x3B, 0x00, 0x4993 },
};

static EntranceTableEntry sPiratesFortressExteriorEntrance1[] = {
    { 0x3B, 0x01, 0x8102 },
};

static EntranceTableEntry sPiratesFortressExteriorEntrance2[] = {
    { 0x3B, 0x02, 0x8993 },
};

static EntranceTableEntry sPiratesFortressExteriorEntrance3[] = {
    { 0x3B, 0x03, 0x8993 },
};

static EntranceTableEntry sPiratesFortressExteriorEntrance4[] = {
    { 0x3B, 0x04, 0x8102 },
};

static EntranceTableEntry sPiratesFortressExteriorEntrance5[] = {
    { 0x3B, 0x05, 0x8102 },
};

static EntranceTableEntry sPiratesFortressExteriorEntrance6[] = {
    { 0x3B, 0x06, 0x8102 },
};

static EntranceTableEntry* sPiratesFortressExteriorEntranceTable[] = {
    sPiratesFortressExteriorEntrance0, sPiratesFortressExteriorEntrance1, sPiratesFortressExteriorEntrance2,
    sPiratesFortressExteriorEntrance3, sPiratesFortressExteriorEntrance4, sPiratesFortressExteriorEntrance5,
    sPiratesFortressExteriorEntrance6,
};

static EntranceTableEntry sFishermansHutEntrance0[] = {
    { 0x3C, 0x00, 0x4102 },
};

static EntranceTableEntry* sFishermansHutEntranceTable[] = {
    sFishermansHutEntrance0,
};

static EntranceTableEntry sGoronShopEntrance0[] = {
    { 0x3D, 0x00, 0x4102 },
};

static EntranceTableEntry* sGoronShopEntranceTable[] = {
    sGoronShopEntrance0,
};

static EntranceTableEntry sDekuKingsChamberEntrance0[] = {
    { 0xC2, 0x00, 0xC102 },
    { 0xC2, 0x00, 0x8102 },
};

static EntranceTableEntry sDekuKingsChamberEntrance1[] = {
    { 0xC2, 0x01, 0xC102 },
};

static EntranceTableEntry sDekuKingsChamberEntrance2[] = {
    { 0xC2, 0x02, 0x858B },
};

static EntranceTableEntry sDekuKingsChamberEntrance3[] = {
    { 0xC2, 0x03, 0x0102 },
};

static EntranceTableEntry* sDekuKingsChamberEntranceTable[] = {
    sDekuKingsChamberEntrance0,
    sDekuKingsChamberEntrance1,
    sDekuKingsChamberEntrance2,
    sDekuKingsChamberEntrance3,
};

static EntranceTableEntry sMoonGoronTrialEntrance0[] = {
    { 0xC1, 0x00, 0x0387 },
};

static EntranceTableEntry* sMoonGoronTrialEntranceTable[] = {
    sMoonGoronTrialEntrance0,
};

static EntranceTableEntry sRoadToSouthernSwampEntrance0[] = {
    { 0x40, 0x00, 0x8A14 },
};

static EntranceTableEntry sRoadToSouthernSwampEntrance1[] = {
    { 0x40, 0x01, 0x8A14 },
};

static EntranceTableEntry sRoadToSouthernSwampEntrance2[] = {
    { 0x40, 0x02, 0x0102 },
};

static EntranceTableEntry* sRoadToSouthernSwampEntranceTable[] = {
    sRoadToSouthernSwampEntrance0,
    sRoadToSouthernSwampEntrance1,
    sRoadToSouthernSwampEntrance2,
};

static EntranceTableEntry sDoggyRacetrackEntrance0[] = {
    { 0x41, 0x00, 0xC102 },
};

static EntranceTableEntry sDoggyRacetrackEntrance1[] = {
    { 0x41, 0x01, 0x0A14 },
};

static EntranceTableEntry* sDoggyRacetrackEntranceTable[] = {
    sDoggyRacetrackEntrance0,
    sDoggyRacetrackEntrance1,
};

static EntranceTableEntry sCuccoShackEntrance0[] = {
    { 0x42, 0x00, 0xC102 },
    { 0x42, 0x00, 0x8102 },
};

static EntranceTableEntry sCuccoShackEntrance1[] = {
    { 0x42, 0x01, 0x0A14 },
};

static EntranceTableEntry* sCuccoShackEntranceTable[] = {
    sCuccoShackEntrance0,
    sCuccoShackEntrance1,
};

static EntranceTableEntry sIkanaGraveyardEntrance0[] = {
    { 0x43, 0x00, 0x4A14 },
    { 0x43, 0x00, 0x8102 },
};

static EntranceTableEntry sIkanaGraveyardEntrance1[] = {
    { 0x43, 0x01, 0x4102 },
};

static EntranceTableEntry sIkanaGraveyardEntrance2[] = {
    { 0x43, 0x02, 0x4102 },
};

static EntranceTableEntry sIkanaGraveyardEntrance3[] = {
    { 0x43, 0x03, 0x4102 },
};

static EntranceTableEntry sIkanaGraveyardEntrance4[] = {
    { 0x43, 0x04, 0x4102 },
};

static EntranceTableEntry sIkanaGraveyardEntrance5[] = {
    { 0x43, 0x05, 0x058B },
};

static EntranceTableEntry* sIkanaGraveyardEntranceTable[] = {
    sIkanaGraveyardEntrance0, sIkanaGraveyardEntrance1, sIkanaGraveyardEntrance2,
    sIkanaGraveyardEntrance3, sIkanaGraveyardEntrance4, sIkanaGraveyardEntrance5,
};

static EntranceTableEntry sGohtsLairEntrance0[] = {
    { 0xBC, 0x00, 0x8102 },
};

static EntranceTableEntry* sGohtsLairEntranceTable[] = {
    sGohtsLairEntrance0,
};

static EntranceTableEntry sSouthernSwampPoisonedEntrance0[] = {
    { 0x45, 0x00, 0xCA14 },
};

static EntranceTableEntry sSouthernSwampPoisonedEntrance1[] = {
    { 0x45, 0x01, 0x4102 },
};

static EntranceTableEntry sSouthernSwampPoisonedEntrance2[] = {
    { 0x45, 0x02, 0xC102 },
};

static EntranceTableEntry sSouthernSwampPoisonedEntrance3[] = {
    { 0x45, 0x03, 0x4102 },
};

static EntranceTableEntry sSouthernSwampPoisonedEntrance4[] = {
    { 0x45, 0x04, 0x4102 },
};

static EntranceTableEntry sSouthernSwampPoisonedEntrance5[] = {
    { 0x45, 0x05, 0x4102 },
};

static EntranceTableEntry sSouthernSwampPoisonedEntrance6[] = {
    { 0x45, 0x06, 0x0102 },
};

static EntranceTableEntry sSouthernSwampPoisonedEntrance7[] = {
    { 0x45, 0x07, 0x4102 },
};

static EntranceTableEntry sSouthernSwampPoisonedEntrance8[] = {
    { 0x45, 0x08, 0x4102 },
};

static EntranceTableEntry sSouthernSwampPoisonedEntrance9[] = {
    { 0x45, 0x09, 0x4A14 },
};

static EntranceTableEntry sSouthernSwampPoisonedEntrance10[] = {
    { 0x45, 0x0A, 0x4A14 },
};

static EntranceTableEntry* sSouthernSwampPoisonedEntranceTable[] = {
    sSouthernSwampPoisonedEntrance0, sSouthernSwampPoisonedEntrance1,  sSouthernSwampPoisonedEntrance2,
    sSouthernSwampPoisonedEntrance3, sSouthernSwampPoisonedEntrance4,  sSouthernSwampPoisonedEntrance5,
    sSouthernSwampPoisonedEntrance6, sSouthernSwampPoisonedEntrance7,  sSouthernSwampPoisonedEntrance8,
    sSouthernSwampPoisonedEntrance9, sSouthernSwampPoisonedEntrance10,
};

static EntranceTableEntry sWoodfallEntrance0[] = {
    { 0x46, 0x00, 0xC102 },
    { 0x46, 0x00, 0x0183 },
    { 0x46, 0x00, 0xC102 },
};

static EntranceTableEntry sWoodfallEntrance1[] = {
    { 0x46, 0x01, 0x4102 },
    { 0x46, 0x01, 0x0183 },
    { 0x46, 0x01, 0x4102 },
};

static EntranceTableEntry sWoodfallEntrance2[] = {
    { 0x46, 0x02, 0x4102 },
    { 0x46, 0x02, 0x0183 },
    { 0x46, 0x02, 0x4102 },
};

static EntranceTableEntry sWoodfallEntrance3[] = {
    { 0x46, 0x03, 0x4102 },
    { 0x46, 0x03, 0x0183 },
    { 0x46, 0x03, 0x4102 },
};

static EntranceTableEntry sWoodfallEntrance4[] = {
    { 0x46, 0x04, 0x4102 },
    { 0x46, 0x04, 0x0183 },
    { 0x46, 0x04, 0x4102 },
};

static EntranceTableEntry* sWoodfallEntranceTable[] = {
    sWoodfallEntrance0, sWoodfallEntrance1, sWoodfallEntrance2, sWoodfallEntrance3, sWoodfallEntrance4,
};

static EntranceTableEntry sMoonZoraTrialEntrance0[] = {
    { 0xB9, 0x00, 0x0387 },
};

static EntranceTableEntry sMoonZoraTrialEntrance1[] = {
    { 0xB9, 0x01, 0x0102 },
};

static EntranceTableEntry* sMoonZoraTrialEntranceTable[] = {
    sMoonZoraTrialEntrance0,
    sMoonZoraTrialEntrance1,
};

static EntranceTableEntry sGoronVillageSpringEntrance0[] = {
    { 0x48, 0x00, 0xC102 },
    { 0x48, 0x00, 0x8102 },
};

static EntranceTableEntry sGoronVillageSpringEntrance1[] = {
    { 0x48, 0x01, 0x4102 },
};

static EntranceTableEntry sGoronVillageSpringEntrance2[] = {
    { 0x48, 0x02, 0x4102 },
};

static EntranceTableEntry sGoronVillageSpringEntrance3[] = {
    { 0x48, 0x03, 0x4102 },
};

static EntranceTableEntry sGoronVillageSpringEntrance4[] = {
    { 0x48, 0x04, 0x0A14 },
};

static EntranceTableEntry* sGoronVillageSpringEntranceTable[] = {
    sGoronVillageSpringEntrance0, sGoronVillageSpringEntrance1, sGoronVillageSpringEntrance2,
    sGoronVillageSpringEntrance3, sGoronVillageSpringEntrance4,
};

static EntranceTableEntry sGreatBayTempleEntrance0[] = {
    { 0xB7, 0x00, 0x4102 },
};

static EntranceTableEntry sGreatBayTempleEntrance1[] = {
    { 0xB7, 0x01, 0x0102 },
};

static EntranceTableEntry sGreatBayTempleEntrance2[] = {
    { 0xB7, 0x02, 0x0102 },
};

static EntranceTableEntry* sGreatBayTempleEntranceTable[] = {
    sGreatBayTempleEntrance0,
    sGreatBayTempleEntrance1,
    sGreatBayTempleEntrance2,
};

static EntranceTableEntry sWaterfallRapidsEntrance0[] = {
    { 0x4A, 0x00, 0x4102 },
};

static EntranceTableEntry sWaterfallRapidsEntrance1[] = {
    { 0x4A, 0x01, 0x0A14 },
};

static EntranceTableEntry sWaterfallRapidsEntrance2[] = {
    { 0x4A, 0x02, 0x0A14 },
};

static EntranceTableEntry sWaterfallRapidsEntrance3[] = {
    { 0x4A, 0x03, 0x0A14 },
};

static EntranceTableEntry* sWaterfallRapidsEntranceTable[] = {
    sWaterfallRapidsEntrance0,
    sWaterfallRapidsEntrance1,
    sWaterfallRapidsEntrance2,
    sWaterfallRapidsEntrance3,
};

static EntranceTableEntry sBeneathTheWellEntrance0[] = {
    { 0xB5, 0x00, 0x4102 },
};

static EntranceTableEntry sBeneathTheWellEntrance1[] = {
    { 0xB5, 0x01, 0x4102 },
};

static EntranceTableEntry* sBeneathTheWellEntranceTable[] = {
    sBeneathTheWellEntrance0,
    sBeneathTheWellEntrance1,
};

static EntranceTableEntry sZoraHallRoomsEntrance0[] = {
    { 0x4C, 0x00, 0x0102 },
};

static EntranceTableEntry sZoraHallRoomsEntrance1[] = {
    { 0x4C, 0x01, 0x0102 },
};

static EntranceTableEntry sZoraHallRoomsEntrance2[] = {
    { 0x4C, 0x02, 0x0102 },
};

static EntranceTableEntry sZoraHallRoomsEntrance3[] = {
    { 0x4C, 0x03, 0x0102 },
};

static EntranceTableEntry sZoraHallRoomsEntrance4[] = {
    { 0x4C, 0x04, 0x858B },
};

static EntranceTableEntry sZoraHallRoomsEntrance5[] = {
    { 0x4C, 0x05, 0x0102 },
};

static EntranceTableEntry sZoraHallRoomsEntrance6[] = {
    { 0x4C, 0x06, 0x0102 },
};

static EntranceTableEntry* sZoraHallRoomsEntranceTable[] = {
    sZoraHallRoomsEntrance0, sZoraHallRoomsEntrance1, sZoraHallRoomsEntrance2, sZoraHallRoomsEntrance3,
    sZoraHallRoomsEntrance4, sZoraHallRoomsEntrance5, sZoraHallRoomsEntrance6,
};

static EntranceTableEntry sGoronVillageWinterEntrance0[] = {
    { 0x4D, 0x00, 0xC102 },
};

static EntranceTableEntry sGoronVillageWinterEntrance1[] = {
    { 0x4D, 0x01, 0x4102 },
};

static EntranceTableEntry sGoronVillageWinterEntrance2[] = {
    { 0x4D, 0x02, 0x4102 },
};

static EntranceTableEntry sGoronVillageWinterEntrance3[] = {
    { 0x4D, 0x03, 0x4102 },
};

static EntranceTableEntry sGoronVillageWinterEntrance4[] = {
    { 0x4D, 0x04, 0x0A14 },
};

static EntranceTableEntry* sGoronVillageWinterEntranceTable[] = {
    sGoronVillageWinterEntrance0, sGoronVillageWinterEntrance1, sGoronVillageWinterEntrance2,
    sGoronVillageWinterEntrance3, sGoronVillageWinterEntrance4,
};

static EntranceTableEntry sGoronGraveryardEntrance0[] = {
    { 0x4E, 0x00, 0x4102 },
};

static EntranceTableEntry sGoronGraveryardEntrance1[] = {
    { 0x4E, 0x01, 0x058B },
};

static EntranceTableEntry* sGoronGraveryardEntranceTable[] = {
    sGoronGraveryardEntrance0,
    sGoronGraveryardEntrance1,
};

static EntranceTableEntry sSakonsHideoutEntrance0[] = {
    { 0x4F, 0x00, 0x4102 },
};

static EntranceTableEntry* sSakonsHideoutEntranceTable[] = {
    sSakonsHideoutEntrance0,
};

static EntranceTableEntry sMountainVillageWinterEntrance0[] = {
    { 0x50, 0x00, 0x4A14 },
};

static EntranceTableEntry sMountainVillageWinterEntrance1[] = {
    { 0x50, 0x01, 0x4102 },
};

static EntranceTableEntry sMountainVillageWinterEntrance2[] = {
    { 0x50, 0x02, 0xCA14 },
};

static EntranceTableEntry sMountainVillageWinterEntrance3[] = {
    { 0x50, 0x03, 0x4102 },
};

static EntranceTableEntry sMountainVillageWinterEntrance4[] = {
    { 0x50, 0x04, 0xCA14 },
};

static EntranceTableEntry sMountainVillageWinterEntrance5[] = {
    { 0x50, 0x05, 0x4102 },
};

static EntranceTableEntry sMountainVillageWinterEntrance6[] = {
    { 0x50, 0x06, 0x4A14 },
};

static EntranceTableEntry sMountainVillageWinterEntrance7[] = {
    { 0x50, 0x07, 0x4A14 },
};

static EntranceTableEntry sMountainVillageWinterEntrance8[] = {
    { 0x50, 0x08, 0x4A14 },
};

static EntranceTableEntry* sMountainVillageWinterEntranceTable[] = {
    sMountainVillageWinterEntrance0, sMountainVillageWinterEntrance1, sMountainVillageWinterEntrance2,
    sMountainVillageWinterEntrance3, sMountainVillageWinterEntrance4, sMountainVillageWinterEntrance5,
    sMountainVillageWinterEntrance6, sMountainVillageWinterEntrance7, sMountainVillageWinterEntrance8,
};

static EntranceTableEntry sGhostHutEntrance0[] = {
    { 0x51, 0x00, 0x4102 },
};

static EntranceTableEntry sGhostHutEntrance1[] = {
    { 0x51, 0x01, 0x0102 },
};

static EntranceTableEntry sGhostHutEntrance2[] = {
    { 0x51, 0x02, 0x0102 },
};

static EntranceTableEntry* sGhostHutEntranceTable[] = {
    sGhostHutEntrance0,
    sGhostHutEntrance1,
    sGhostHutEntrance2,
};

static EntranceTableEntry sDekuShrineEntrance0[] = {
    { 0x52, 0x00, 0x4102 },
};

static EntranceTableEntry sDekuShrineEntrance1[] = {
    { 0x52, 0x01, 0x0102 },
};

static EntranceTableEntry sDekuShrineEntrance2[] = {
    { 0x52, 0x02, 0x0102 },
};

static EntranceTableEntry* sDekuShrineEntranceTable[] = {
    sDekuShrineEntrance0,
    sDekuShrineEntrance1,
    sDekuShrineEntrance2,
};

static EntranceTableEntry sRoadToIkanaEntrance0[] = {
    { 0x53, 0x00, 0x8A14 },
};

static EntranceTableEntry sRoadToIkanaEntrance1[] = {
    { 0x53, 0x01, 0x8A14 },
};

static EntranceTableEntry sRoadToIkanaEntrance2[] = {
    { 0x53, 0x02, 0x0A14 },
};

static EntranceTableEntry* sRoadToIkanaEntranceTable[] = {
    sRoadToIkanaEntrance0,
    sRoadToIkanaEntrance1,
    sRoadToIkanaEntrance2,
};

static EntranceTableEntry sMusicBoxHouseEntrance0[] = {
    { 0x55, 0x00, 0x4102 },
};

static EntranceTableEntry* sMusicBoxHouseEntranceTable[] = {
    sMusicBoxHouseEntrance0,
};

static EntranceTableEntry sIgosDuIkanasLairEntrance0[] = {
    { 0xAA, 0x00, 0x8102 },
    { 0xAA, 0x00, 0x8102 },
};

static EntranceTableEntry* sIgosDuIkanasLairEntranceTable[] = {
    sIgosDuIkanasLairEntrance0,
};

static EntranceTableEntry sSwordmansSchoolEntrance0[] = {
    { 0x54, 0x00, 0x4102 },
};

static EntranceTableEntry* sSwordmansSchoolEntranceTable[] = {
    sSwordmansSchoolEntrance0,
};

static EntranceTableEntry sTouristInformationEntrance0[] = {
    { 0x57, 0x00, 0x4102 },
};

static EntranceTableEntry sTouristInformationEntrance1[] = {
    { 0x57, 0x01, 0x0102 },
};

static EntranceTableEntry sTouristInformationEntrance2[] = {
    { 0x57, 0x02, 0x0102 },
};

static EntranceTableEntry* sTouristInformationEntranceTable[] = {
    sTouristInformationEntrance0,
    sTouristInformationEntrance1,
    sTouristInformationEntrance2,
};

static EntranceTableEntry sStoneTowerEntrance0[] = {
    { 0x58, 0x00, 0x4102 },
};

static EntranceTableEntry sStoneTowerEntrance1[] = {
    { 0x58, 0x01, 0xCA14 },
};

static EntranceTableEntry sStoneTowerEntrance2[] = {
    { 0x58, 0x02, 0xC102 },
};

static EntranceTableEntry sStoneTowerEntrance3[] = {
    { 0x58, 0x03, 0x4A14 },
};

static EntranceTableEntry* sStoneTowerEntranceTable[] = {
    sStoneTowerEntrance0,
    sStoneTowerEntrance1,
    sStoneTowerEntrance2,
    sStoneTowerEntrance3,
};

static EntranceTableEntry sStoneTowerInvertedEntrance0[] = {
    { 0x59, 0x00, 0x4A14 },
};

static EntranceTableEntry sStoneTowerInvertedEntrance1[] = {
    { 0x59, 0x01, 0xC102 },
};

static EntranceTableEntry* sStoneTowerInvertedEntranceTable[] = {
    sStoneTowerInvertedEntrance0,
    sStoneTowerInvertedEntrance1,
};

static EntranceTableEntry sMountainVillageSpringEntrance0[] = {
    { 0x5A, 0x00, 0x4A14 },
    { 0x5A, 0x00, 0x4A14 },
};

static EntranceTableEntry sMountainVillageSpringEntrance1[] = {
    { 0x5A, 0x01, 0x4102 },
};

static EntranceTableEntry sMountainVillageSpringEntrance2[] = {
    { 0x5A, 0x02, 0xCA14 },
};

static EntranceTableEntry sMountainVillageSpringEntrance3[] = {
    { 0x5A, 0x03, 0x4102 },
};

static EntranceTableEntry sMountainVillageSpringEntrance4[] = {
    { 0x5A, 0x04, 0xCA14 },
};

static EntranceTableEntry sMountainVillageSpringEntrance5[] = {
    { 0x5A, 0x05, 0x4102 },
};

static EntranceTableEntry sMountainVillageSpringEntrance6[] = {
    { 0x5A, 0x06, 0xCA14 },
};

static EntranceTableEntry sMountainVillageSpringEntrance7[] = {
    { 0x5A, 0x07, 0x458B },
};

static EntranceTableEntry sMountainVillageSpringEntrance8[] = {
    { 0x5A, 0x08, 0x4A14 },
};

static EntranceTableEntry* sMountainVillageSpringEntranceTable[] = {
    sMountainVillageSpringEntrance0, sMountainVillageSpringEntrance1, sMountainVillageSpringEntrance2,
    sMountainVillageSpringEntrance3, sMountainVillageSpringEntrance4, sMountainVillageSpringEntrance5,
    sMountainVillageSpringEntrance6, sMountainVillageSpringEntrance7, sMountainVillageSpringEntrance8,
};

static EntranceTableEntry sPathToSnowheadEntrance0[] = {
    { 0x5B, 0x00, 0xCA14 },
    { 0x5B, 0x00, 0xCA14 },
};

static EntranceTableEntry sPathToSnowheadEntrance1[] = {
    { 0x5B, 0x01, 0xCA14 },
    { 0x5B, 0x01, 0xCA14 },
};

static EntranceTableEntry* sPathToSnowheadEntranceTable[] = {
    sPathToSnowheadEntrance0,
    sPathToSnowheadEntrance1,
};

static EntranceTableEntry sSnowheadEntrance0[] = {
    { 0x5C, 0x00, 0xCA14 },
    { 0x5C, 0x00, 0xCA14 },
};

static EntranceTableEntry sSnowheadEntrance1[] = {
    { 0x5C, 0x01, 0x4102 },
    { 0x5C, 0x01, 0x4102 },
};

static EntranceTableEntry sSnowheadEntrance2[] = {
    { 0x5C, 0x02, 0x4102 },
    { 0x5C, 0x02, 0x4102 },
};

static EntranceTableEntry sSnowheadEntrance3[] = {
    { 0x5C, 0x03, 0x4102 },
    { 0x5C, 0x03, 0x4102 },
};

static EntranceTableEntry* sSnowheadEntranceTable[] = {
    sSnowheadEntrance0,
    sSnowheadEntrance1,
    sSnowheadEntrance2,
    sSnowheadEntrance3,
};

static EntranceTableEntry sPathToGoronVillageWinterEntrance0[] = {
    { 0x5D, 0x00, 0x8A14 },
};

static EntranceTableEntry sPathToGoronVillageWinterEntrance1[] = {
    { 0x5D, 0x01, 0x8102 },
};

static EntranceTableEntry sPathToGoronVillageWinterEntrance2[] = {
    { 0x5D, 0x02, 0x0102 },
};

static EntranceTableEntry* sPathToGoronVillageWinterEntranceTable[] = {
    sPathToGoronVillageWinterEntrance0,
    sPathToGoronVillageWinterEntrance1,
    sPathToGoronVillageWinterEntrance2,
};

static EntranceTableEntry sPathToGoronVillageSpringEntrance0[] = {
    { 0x5E, 0x00, 0x8A14 },
};

static EntranceTableEntry sPathToGoronVillageSpringEntrance1[] = {
    { 0x5E, 0x01, 0x8102 },
};

static EntranceTableEntry sPathToGoronVillageSpringEntrance2[] = {
    { 0x5E, 0x02, 0x0102 },
};

static EntranceTableEntry* sPathToGoronVillageSpringEntranceTable[] = {
    sPathToGoronVillageSpringEntrance0,
    sPathToGoronVillageSpringEntrance1,
    sPathToGoronVillageSpringEntrance2,
};

static EntranceTableEntry sGyorgsLairEntrance0[] = {
    { 0xA1, 0x00, 0x8102 },
};

static EntranceTableEntry sGyorgsLairEntrance1[] = {
    { 0xA1, 0x01, 0x8102 },
};

static EntranceTableEntry* sGyorgsLairEntranceTable[] = {
    sGyorgsLairEntrance0,
    sGyorgsLairEntrance1,
};

static EntranceTableEntry sSecretShrineEntrance0[] = {
    { 0xA0, 0x00, 0x4102 },
};

static EntranceTableEntry* sSecretShrineEntranceTable[] = {
    sSecretShrineEntrance0,
};

static EntranceTableEntry sStockPotInnEntrance0[] = {
    { 0x61, 0x00, 0x4102 },
    { 0x61, 0x00, 0x8102 },
};

static EntranceTableEntry sStockPotInnEntrance1[] = {
    { 0x61, 0x01, 0x4102 },
};

static EntranceTableEntry sStockPotInnEntrance2[] = {
    { 0x61, 0x02, 0x0102 },
};

static EntranceTableEntry sStockPotInnEntrance3[] = {
    { 0x61, 0x03, 0x0102 },
};

static EntranceTableEntry sStockPotInnEntrance4[] = {
    { 0x61, 0x04, 0x0102 },
};

static EntranceTableEntry sStockPotInnEntrance5[] = {
    { 0x61, 0x05, 0x0102 },
};

static EntranceTableEntry* sStockPotInnEntranceTable[] = {
    sStockPotInnEntrance0, sStockPotInnEntrance1, sStockPotInnEntrance2,
    sStockPotInnEntrance3, sStockPotInnEntrance4, sStockPotInnEntrance5,
};

static EntranceTableEntry sGreatBayCutsceneEntrance0[] = {
    { 0x62, 0x00, 0x4102 },
};

static EntranceTableEntry* sGreatBayCutsceneEntranceTable[] = {
    sGreatBayCutsceneEntrance0,
};

static EntranceTableEntry sClockTowerInteriorEntrance0[] = {
    { 0x63, 0x00, 0x0102 },
};

static EntranceTableEntry sClockTowerInteriorEntrance1[] = {
    { 0x63, 0x01, 0x0102 },
};

static EntranceTableEntry sClockTowerInteriorEntrance2[] = {
    { 0x63, 0x02, 0x058B },
};

static EntranceTableEntry sClockTowerInteriorEntrance3[] = {
    { 0x63, 0x03, 0x0102 },
};

static EntranceTableEntry sClockTowerInteriorEntrance4[] = {
    { 0x63, 0x04, 0x058B },
};

static EntranceTableEntry sClockTowerInteriorEntrance5[] = {
    { 0x63, 0x05, 0x0102 },
};

static EntranceTableEntry sClockTowerInteriorEntrance6[] = {
    { 0x63, 0x06, 0x858B },
};

static EntranceTableEntry* sClockTowerInteriorEntranceTable[] = {
    sClockTowerInteriorEntrance0, sClockTowerInteriorEntrance1, sClockTowerInteriorEntrance2,
    sClockTowerInteriorEntrance3, sClockTowerInteriorEntrance4, sClockTowerInteriorEntrance5,
    sClockTowerInteriorEntrance6,
};

static EntranceTableEntry sWoodsOfMysteryEntrance0[] = {
    { 0x64, 0x00, 0x4102 },
};

static EntranceTableEntry* sWoodsOfMysteryEntranceTable[] = {
    sWoodsOfMysteryEntrance0,
};

static EntranceTableEntry sLostWoodsEntrance0[] = {
    { 0x9B, 0x00, 0x858B },
    { 0x9B, 0x00, 0x8183 },
    { 0x9B, 0x00, 0x858B },
    { 0x9B, 0x00, 0x8102 },
};

static EntranceTableEntry sLostWoodsEntrance1[] = {
    { 0x9B, 0x01, 0x058B },
    { 0x9B, 0x01, 0x058B },
    { 0x9B, 0x01, 0x058B },
    { 0x9B, 0x01, 0x058B },
};

static EntranceTableEntry sLostWoodsEntrance2[] = {
    { 0x9B, 0x02, 0x058B },
    { 0x9B, 0x02, 0x058B },
    { 0x9B, 0x02, 0x058B },
    { 0x9B, 0x02, 0x058B },
};

static EntranceTableEntry* sLostWoodsEntranceTable[] = {
    sLostWoodsEntrance0,
    sLostWoodsEntrance1,
    sLostWoodsEntrance2,
};

static EntranceTableEntry sMoonLinkTrialEntrance0[] = {
    { 0x66, 0x00, 0x0387 },
};

static EntranceTableEntry* sMoonLinkTrialEntranceTable[] = {
    sMoonLinkTrialEntrance0,
};

static EntranceTableEntry sTheMoonEntrance0[] = {
    { 0x67, 0x00, 0x0387 },
};

static EntranceTableEntry* sTheMoonEntranceTable[] = {
    sTheMoonEntrance0,
};

static EntranceTableEntry sBombShopEntrance0[] = {
    { 0x68, 0x00, 0x4102 },
};

static EntranceTableEntry sBombShopEntrance1[] = {
    { 0x68, 0x01, 0x0102 },
};

static EntranceTableEntry* sBombShopEntranceTable[] = {
    sBombShopEntrance0,
    sBombShopEntrance1,
};

static EntranceTableEntry sGiantsChamberEntrance0[] = {
    { 0x69, 0x00, 0x0102 }, { 0x69, 0x00, 0x0102 }, { 0x69, 0x00, 0x0102 }, { 0x69, 0x00, 0x0102 },
    { 0x69, 0x00, 0x0102 }, { 0x69, 0x00, 0x0102 }, { 0x69, 0x00, 0x0102 }, { 0x69, 0x00, 0x0102 },
    { 0x69, 0x00, 0x0102 }, { 0x69, 0x00, 0x0102 }, { 0x69, 0x00, 0x0102 },
};

static EntranceTableEntry* sGiantsChamberEntranceTable[] = {
    sGiantsChamberEntrance0,
};

static EntranceTableEntry sGormanTrackEntrance0[] = {
    { 0x6A, 0x00, 0x4A14 },
};

static EntranceTableEntry sGormanTrackEntrance1[] = {
    { 0x6A, 0x01, 0x4A14 },
};

static EntranceTableEntry sGormanTrackEntrance2[] = {
    { 0x6A, 0x02, 0x4A14 },
};

static EntranceTableEntry sGormanTrackEntrance3[] = {
    { 0x6A, 0x03, 0x4A14 },
};

static EntranceTableEntry sGormanTrackEntrance4[] = {
    { 0x6A, 0x04, 0x0102 },
};

static EntranceTableEntry sGormanTrackEntrance5[] = {
    { 0x6A, 0x05, 0x0A14 },
};

static EntranceTableEntry* sGormanTrackEntranceTable[] = {
    sGormanTrackEntrance0, sGormanTrackEntrance1, sGormanTrackEntrance2,
    sGormanTrackEntrance3, sGormanTrackEntrance4, sGormanTrackEntrance5,
};

static EntranceTableEntry sGoronRacetrackEntrance0[] = {
    { 0x6B, 0x00, 0x4102 },
    { 0x6B, 0x00, 0x4102 },
};

static EntranceTableEntry sGoronRacetrackEntrance1[] = {
    { 0x6B, 0x01, 0x8A14 },
    { 0x6B, 0x01, 0x8A14 },
};

static EntranceTableEntry sGoronRacetrackEntrance2[] = {
    { 0x6B, 0x02, 0x0A14 },
    { 0x6B, 0x02, 0x0A14 },
};

static EntranceTableEntry* sGoronRacetrackEntranceTable[] = {
    sGoronRacetrackEntrance0,
    sGoronRacetrackEntrance1,
    sGoronRacetrackEntrance2,
};

static EntranceTableEntry sEastClockTownEntrance0[] = {
    { 0x6C, 0x00, 0x4102 },
    { 0x6C, 0x00, 0x8102 },
    { 0x6C, 0x00, 0x058B },
};

static EntranceTableEntry sEastClockTownEntrance1[] = {
    { 0x6C, 0x01, 0xCA14 },
};

static EntranceTableEntry sEastClockTownEntrance2[] = {
    { 0x6C, 0x02, 0x4102 },
};

static EntranceTableEntry sEastClockTownEntrance3[] = {
    { 0x6C, 0x03, 0xC102 },
};

static EntranceTableEntry sEastClockTownEntrance4[] = {
    { 0x6C, 0x04, 0x4102 },
};

static EntranceTableEntry sEastClockTownEntrance5[] = {
    { 0x6C, 0x05, 0xC102 },
};

static EntranceTableEntry sEastClockTownEntrance6[] = {
    { 0x6C, 0x06, 0x4102 },
};

static EntranceTableEntry sEastClockTownEntrance7[] = {
    { 0x6C, 0x07, 0x4102 },
};

static EntranceTableEntry sEastClockTownEntrance8[] = {
    { 0x6C, 0x08, 0x4102 },
};

static EntranceTableEntry sEastClockTownEntrance9[] = {
    { 0x6C, 0x09, 0x4102 },
};

static EntranceTableEntry sEastClockTownEntrance10[] = {
    { 0x6C, 0x0A, 0x4102 },
};

static EntranceTableEntry sEastClockTownEntrance11[] = {
    { 0x6C, 0x0B, 0x4102 },
};

static EntranceTableEntry sEastClockTownEntrance12[] = {
    { 0x6C, 0x0C, 0x4102 },
};

static EntranceTableEntry* sEastClockTownEntranceTable[] = {
    sEastClockTownEntrance0,  sEastClockTownEntrance1, sEastClockTownEntrance2,  sEastClockTownEntrance3,
    sEastClockTownEntrance4,  sEastClockTownEntrance5, sEastClockTownEntrance6,  sEastClockTownEntrance7,
    sEastClockTownEntrance8,  sEastClockTownEntrance9, sEastClockTownEntrance10, sEastClockTownEntrance11,
    sEastClockTownEntrance12,
};

static EntranceTableEntry sWestClockTownEntrance0[] = {
    { 0x6D, 0x00, 0x4102 },
    { 0x6D, 0x00, 0x8102 },
};

static EntranceTableEntry sWestClockTownEntrance1[] = {
    { 0x6D, 0x01, 0xC102 },
};

static EntranceTableEntry sWestClockTownEntrance2[] = {
    { 0x6D, 0x02, 0xCA14 },
};

static EntranceTableEntry sWestClockTownEntrance3[] = {
    { 0x6D, 0x03, 0x4102 },
};

static EntranceTableEntry sWestClockTownEntrance4[] = {
    { 0x6D, 0x04, 0x4102 },
};

static EntranceTableEntry sWestClockTownEntrance5[] = {
    { 0x6D, 0x05, 0x4102 },
};

static EntranceTableEntry sWestClockTownEntrance6[] = {
    { 0x6D, 0x06, 0x4102 },
};

static EntranceTableEntry sWestClockTownEntrance7[] = {
    { 0x6D, 0x07, 0x4102 },
};

static EntranceTableEntry sWestClockTownEntrance8[] = {
    { 0x6D, 0x08, 0x4102 },
};

static EntranceTableEntry sWestClockTownEntrance9[] = {
    { 0x6D, 0x09, 0x4A14 },
};

static EntranceTableEntry* sWestClockTownEntranceTable[] = {
    sWestClockTownEntrance0, sWestClockTownEntrance1, sWestClockTownEntrance2, sWestClockTownEntrance3,
    sWestClockTownEntrance4, sWestClockTownEntrance5, sWestClockTownEntrance6, sWestClockTownEntrance7,
    sWestClockTownEntrance8, sWestClockTownEntrance9,
};

static EntranceTableEntry sNorthClockTownEntrance0[] = {
    { 0x6E, 0x00, 0x4102 },
    { 0x6E, 0x00, 0x458B },
};

static EntranceTableEntry sNorthClockTownEntrance1[] = {
    { 0x6E, 0x01, 0xC102 },
};

static EntranceTableEntry sNorthClockTownEntrance2[] = {
    { 0x6E, 0x02, 0xC102 },
};

static EntranceTableEntry sNorthClockTownEntrance3[] = {
    { 0x6E, 0x03, 0x4102 },
};

static EntranceTableEntry sNorthClockTownEntrance4[] = {
    { 0x6E, 0x04, 0x4102 },
};

static EntranceTableEntry sNorthClockTownEntrance5[] = {
    { 0x6E, 0x05, 0x8A14 },
};

static EntranceTableEntry sNorthClockTownEntrance6[] = {
    { 0x6E, 0x06, 0x8A14 },
};

static EntranceTableEntry sNorthClockTownEntrance7[] = {
    { 0x6E, 0x07, 0x8A14 },
};

static EntranceTableEntry* sNorthClockTownEntranceTable[] = {
    sNorthClockTownEntrance0, sNorthClockTownEntrance1, sNorthClockTownEntrance2, sNorthClockTownEntrance3,
    sNorthClockTownEntrance4, sNorthClockTownEntrance5, sNorthClockTownEntrance6, sNorthClockTownEntrance7,
};

static EntranceTableEntry sSouthClockTownEntrance0[] = {
    { 0x6F, 0x00, 0x4102 },
    { 0x6F, 0x00, 0x8102 },
    { 0x6F, 0x00, 0x0A14 },
    { 0x6F, 0x00, 0x0102 },
};

static EntranceTableEntry sSouthClockTownEntrance1[] = {
    { 0x6F, 0x01, 0x4102 },
    { 0x6F, 0x01, 0x8102 },
};

static EntranceTableEntry sSouthClockTownEntrance2[] = {
    { 0x6F, 0x02, 0xC102 },
};

static EntranceTableEntry sSouthClockTownEntrance3[] = {
    { 0x6F, 0x03, 0xCA14 },
};

static EntranceTableEntry sSouthClockTownEntrance4[] = {
    { 0x6F, 0x04, 0xC102 },
};

static EntranceTableEntry sSouthClockTownEntrance5[] = {
    { 0x6F, 0x05, 0xC102 },
};

static EntranceTableEntry sSouthClockTownEntrance6[] = {
    { 0x6F, 0x06, 0xCA14 },
};

static EntranceTableEntry sSouthClockTownEntrance7[] = {
    { 0x6F, 0x07, 0xCA14 },
};

static EntranceTableEntry sSouthClockTownEntrance8[] = {
    { 0x6F, 0x08, 0x4A14 },
};

static EntranceTableEntry sSouthClockTownEntrance9[] = {
    { 0x6F, 0x09, 0x4A14 },
};

static EntranceTableEntry sSouthClockTownEntrance10[] = {
    { 0x6F, 0x0A, 0x058B },
};

static EntranceTableEntry* sSouthClockTownEntranceTable[] = {
    sSouthClockTownEntrance0, sSouthClockTownEntrance1, sSouthClockTownEntrance2,  sSouthClockTownEntrance3,
    sSouthClockTownEntrance4, sSouthClockTownEntrance5, sSouthClockTownEntrance6,  sSouthClockTownEntrance7,
    sSouthClockTownEntrance8, sSouthClockTownEntrance9, sSouthClockTownEntrance10,
};

static EntranceTableEntry sLaundryPoolEntrance0[] = {
    { 0x70, 0x00, 0xCA14 },
};

static EntranceTableEntry sLaundryPoolEntrance1[] = {
    { 0x70, 0x01, 0x4A14 },
};

static EntranceTableEntry sLaundryPoolEntrance2[] = {
    { 0x70, 0x02, 0x4102 },
};

static EntranceTableEntry* sLaundryPoolEntranceTable[] = {
    sLaundryPoolEntrance0,
    sLaundryPoolEntrance1,
    sLaundryPoolEntrance2,
};

static EntranceTableEntry sGrottosEntrance0[] = {
    { 0x07, 0x00, 0x0102 },
};

static EntranceTableEntry sGrottosEntrance1[] = {
    { 0x07, 0x01, 0x0102 },
};

static EntranceTableEntry sGrottosEntrance2[] = {
    { 0x07, 0x02, 0x0102 },
};

static EntranceTableEntry sGrottosEntrance3[] = {
    { 0x07, 0x03, 0x0102 },
};

static EntranceTableEntry sGrottosEntrance4[] = {
    { 0x07, 0x04, 0x0102 },
};

static EntranceTableEntry sGrottosEntrance5[] = {
    { 0x07, 0x05, 0x0102 },
};

static EntranceTableEntry sGrottosEntrance6[] = {
    { 0x07, 0x06, 0x0102 },
};

static EntranceTableEntry sGrottosEntrance7[] = {
    { 0x07, 0x07, 0x0102 },
};

static EntranceTableEntry sGrottosEntrance8[] = {
    { 0x07, 0x08, 0x0102 },
};

static EntranceTableEntry sGrottosEntrance9[] = {
    { 0x07, 0x09, 0x0102 },
};

static EntranceTableEntry sGrottosEntrance10[] = {
    { 0x07, 0x0A, 0x0102 },
};

static EntranceTableEntry sGrottosEntrance11[] = {
    { 0x07, 0x0B, 0x0102 },
};

static EntranceTableEntry sGrottosEntrance12[] = {
    { 0x07, 0x0C, 0x0102 },
};

static EntranceTableEntry sGrottosEntrance13[] = {
    { 0x07, 0x0D, 0x0102 },
};

static EntranceTableEntry sGrottosEntrance14[] = {
    { 0x07, 0x0E, 0x0102 },
};

static EntranceTableEntry sGrottosEntrance15[] = {
    { 0x07, 0x0F, 0x0102 },
};

static EntranceTableEntry sGrottosEntrance16[] = {
    { 0x07, 0x10, 0x0102 },
};

static EntranceTableEntry* sGrottosEntranceTable[] = {
    sGrottosEntrance0,  sGrottosEntrance1,  sGrottosEntrance2,  sGrottosEntrance3,  sGrottosEntrance4,
    sGrottosEntrance5,  sGrottosEntrance6,  sGrottosEntrance7,  sGrottosEntrance8,  sGrottosEntrance9,
    sGrottosEntrance10, sGrottosEntrance11, sGrottosEntrance12, sGrottosEntrance13, sGrottosEntrance14,
    sGrottosEntrance15, sGrottosEntrance16,
};

static EntranceTableEntry sCutsceneEntrance0[] = {
    { 0xF8, 0x00, 0x0102 }, { 0xF8, 0x00, 0x0102 }, { 0xF8, 0x00, 0x8102 }, { 0xF8, 0x00, 0x0102 },
    { 0xF8, 0x00, 0x058B }, { 0xF8, 0x00, 0x058B }, { 0xF8, 0x00, 0x058B }, { 0xF8, 0x00, 0x058B },
    { 0xF8, 0x00, 0x0183 }, { 0xF8, 0x00, 0x0183 }, { 0xF8, 0x00, 0x8102 }, { 0xF8, 0x00, 0x0102 },
};

static EntranceTableEntry sCutsceneEntrance1[] = {
    { 0xF8, 0x01, 0x0183 }, { 0xF8, 0x01, 0x0102 }, { 0xF8, 0x01, 0x8102 }, { 0xF8, 0x01, 0x0102 },
    { 0xF8, 0x01, 0x8102 }, { 0xF8, 0x01, 0x058B }, { 0xF8, 0x01, 0x058B }, { 0xF8, 0x01, 0x058B },
    { 0xF8, 0x01, 0x058B }, { 0xF8, 0x01, 0x8102 }, { 0xF8, 0x01, 0x8102 }, { 0xF8, 0x01, 0x0102 },
};

static EntranceTableEntry sCutsceneEntrance2[] = {
    { 0xF8, 0x02, 0x0183 }, { 0xF8, 0x02, 0x0102 }, { 0xF8, 0x02, 0x8102 }, { 0xF8, 0x02, 0x0102 },
    { 0xF8, 0x02, 0x8102 }, { 0xF8, 0x02, 0x058B }, { 0xF8, 0x02, 0x058B }, { 0xF8, 0x02, 0x058B },
    { 0xF8, 0x02, 0x058B }, { 0xF8, 0x02, 0x858B }, { 0xF8, 0x02, 0x8102 },
};

static EntranceTableEntry sCutsceneEntrance3[] = {
    { 0xF8, 0x03, 0x0183 }, { 0xF8, 0x03, 0x0102 }, { 0xF8, 0x03, 0x8102 }, { 0xF8, 0x03, 0x0102 },
    { 0xF8, 0x03, 0x058B }, { 0xF8, 0x03, 0x058B }, { 0xF8, 0x03, 0x058B }, { 0xF8, 0x03, 0x058B },
    { 0xF8, 0x03, 0x058B }, { 0xF8, 0x03, 0x058B }, { 0xF8, 0x03, 0x8102 },
};

static EntranceTableEntry sCutsceneEntrance4[] = {
    { 0xF8, 0x04, 0x0183 }, { 0xF8, 0x04, 0x0102 }, { 0xF8, 0x04, 0x8102 }, { 0xF8, 0x04, 0x0102 },
    { 0xF8, 0x04, 0x058B }, { 0xF8, 0x04, 0x058B }, { 0xF8, 0x04, 0x058B }, { 0xF8, 0x04, 0x058B },
    { 0xF8, 0x04, 0x058B }, { 0xF8, 0x04, 0x058B }, { 0xF8, 0x04, 0x8102 },
};

static EntranceTableEntry sCutsceneEntrance5[] = {
    { 0xF8, 0x05, 0x0183 }, { 0xF8, 0x05, 0x0102 }, { 0xF8, 0x05, 0x8102 }, { 0xF8, 0x05, 0x0102 },
    { 0xF8, 0x05, 0x058B }, { 0xF8, 0x05, 0x058B }, { 0xF8, 0x05, 0x058B }, { 0xF8, 0x05, 0x058B },
    { 0xF8, 0x05, 0x058B }, { 0xF8, 0x05, 0x858B }, { 0xF8, 0x05, 0x8102 },
};

static EntranceTableEntry sCutsceneEntrance6[] = {
    { 0xF8, 0x06, 0x0183 }, { 0xF8, 0x06, 0x0102 }, { 0xF8, 0x06, 0x8102 }, { 0xF8, 0x06, 0x0102 },
    { 0xF8, 0x06, 0x058B }, { 0xF8, 0x06, 0x058B }, { 0xF8, 0x06, 0x058B }, { 0xF8, 0x06, 0x058B },
    { 0xF8, 0x06, 0x058B }, { 0xF8, 0x06, 0x858B }, { 0xF8, 0x06, 0x8102 },
};

static EntranceTableEntry sCutsceneEntrance7[] = {
    { 0xF8, 0x07, 0x0183 }, { 0xF8, 0x07, 0x0102 }, { 0xF8, 0x07, 0x8102 }, { 0xF8, 0x07, 0x0102 },
    { 0xF8, 0x07, 0x058B }, { 0xF8, 0x07, 0x058B }, { 0xF8, 0x07, 0x058B }, { 0xF8, 0x07, 0x058B },
    { 0xF8, 0x07, 0x058B }, { 0xF8, 0x07, 0x858B }, { 0xF8, 0x07, 0x8102 },
};

static EntranceTableEntry sCutsceneEntrance8[] = {
    { 0xF8, 0x08, 0x0183 }, { 0xF8, 0x08, 0x0102 }, { 0xF8, 0x08, 0x8102 }, { 0xF8, 0x08, 0x0102 },
    { 0xF8, 0x08, 0x058B }, { 0xF8, 0x08, 0x058B }, { 0xF8, 0x08, 0x058B }, { 0xF8, 0x08, 0x058B },
    { 0xF8, 0x08, 0x058B }, { 0xF8, 0x08, 0x858B }, { 0xF8, 0x08, 0x8102 },
};

static EntranceTableEntry sCutsceneEntrance9[] = {
    { 0xF8, 0x09, 0x0183 }, { 0xF8, 0x09, 0x0102 }, { 0xF8, 0x09, 0x8102 }, { 0xF8, 0x09, 0x0102 },
    { 0xF8, 0x09, 0x058B }, { 0xF8, 0x09, 0x058B }, { 0xF8, 0x09, 0x058B }, { 0xF8, 0x09, 0x058B },
    { 0xF8, 0x09, 0x058B }, { 0xF8, 0x09, 0x858B }, { 0xF8, 0x09, 0x8102 },
};

static EntranceTableEntry* sCutsceneEntranceTable[] = {
    sCutsceneEntrance0, sCutsceneEntrance1, sCutsceneEntrance2, sCutsceneEntrance3, sCutsceneEntrance4,
    sCutsceneEntrance5, sCutsceneEntrance6, sCutsceneEntrance7, sCutsceneEntrance8, sCutsceneEntrance9,
};

#define SCENE_ENTRANCE(entranceTable, name) \
    { ARRAY_COUNT(entranceTable), entranceTable, name }

#define SCENE_ENTRANCE_NONE() \
    { 0, NULL, NULL }

static SceneEntranceTableEntry sSceneEntranceTable[] = {
    SCENE_ENTRANCE(sMayorsResidenceEntranceTable, "Z2_SONCHONOIE"),
    SCENE_ENTRANCE(sMajorasLairEntranceTable, "Z2_LAST_BS"),
    SCENE_ENTRANCE(sMagicHagsPotionShopEntranceTable, "Z2_WITCH_SHOP"),
    SCENE_ENTRANCE(sRanchHouseEntranceTable, "Z2_OMOYA"),
    SCENE_ENTRANCE(sHoneyAndDarlingsShopEntranceTable, "Z2_BOWLING"),
    SCENE_ENTRANCE(sBeneathTheGraveryardEntranceTable, "Z2_HAKASHITA"),
    SCENE_ENTRANCE(sSouthernSwampClearedEntranceTable, "Z2_20SICHITAI2"),
    SCENE_ENTRANCE(sCuriosityShopEntranceTable, "Z2_AYASHIISHOP"),
    SCENE_ENTRANCE_NONE(),
    SCENE_ENTRANCE_NONE(),
    SCENE_ENTRANCE(sGrottosEntranceTable, "KAKUSIANA"),
    SCENE_ENTRANCE_NONE(),
    SCENE_ENTRANCE_NONE(),
    SCENE_ENTRANCE_NONE(),
    SCENE_ENTRANCE(sCutsceneEntranceTable, "SPOT00"),
    SCENE_ENTRANCE_NONE(),
    SCENE_ENTRANCE(sIkanaCanyonEntranceTable, "Z2_IKANA"),
    SCENE_ENTRANCE(sPiratesFortressEntranceTable, "Z2_KAIZOKU"),
    SCENE_ENTRANCE(sMilkBarEntranceTable, "Z2_MILK_BAR"),
    SCENE_ENTRANCE(sStoneTowerTempleEntranceTable, "Z2_INISIE_N"),
    SCENE_ENTRANCE(sTreasureChestShopEntranceTable, "Z2_TAKARAYA"),
    SCENE_ENTRANCE(sStoneTowerTempleReversedEntranceTable, "Z2_INISIE_R"),
    SCENE_ENTRANCE(sClockTowerRooftopEntranceTable, "Z2_OKUJOU"),
    SCENE_ENTRANCE(sOpeningDungeonEntranceTable, "Z2_OPENINGDAN"),
    SCENE_ENTRANCE(sWoodfallTempleEntranceTable, "Z2_MITURIN"),
    SCENE_ENTRANCE(sPathToMountainVillageEntranceTable, "Z2_13HUBUKINOMITI"),
    SCENE_ENTRANCE(sIkanaCastleEntranceTable, "Z2_CASTLE"),
    SCENE_ENTRANCE(sDekuScrubPlaygroundEntranceTable, "Z2_DEKUTES"),
    SCENE_ENTRANCE(sOdolwasLairEntranceTable, "Z2_MITURIN_BS"),
    SCENE_ENTRANCE(sTownShootingGalleryEntranceTable, "Z2_SYATEKI_MIZU"),
    SCENE_ENTRANCE(sSnowheadTempleEntranceTable, "Z2_HAKUGIN"),
    SCENE_ENTRANCE(sMilkRoadEntranceTable, "Z2_ROMANYMAE"),
    SCENE_ENTRANCE(sPiratesFortressInteriorEntranceTable, "Z2_PIRATE"),
    SCENE_ENTRANCE(sSwampShootingGalleryEntranceTable, "Z2_SYATEKI_MORI"),
    SCENE_ENTRANCE(sPinaccleRockEntranceTable, "Z2_SINKAI"),
    SCENE_ENTRANCE(sFairyFountainEntranceTable, "Z2_YOUSEI_IZUMI"),
    SCENE_ENTRANCE(sSwampSpiderHouseEntranceTable, "Z2_KINSTA1"),
    SCENE_ENTRANCE(sOceansideSpiderHouseEntranceTable, "Z2_KINDAN2"),
    SCENE_ENTRANCE(sAstralObservatoryEntranceTable, "Z2_TENMON_DAI"),
    SCENE_ENTRANCE(sMoonDekuTrialEntranceTable, "Z2_LAST_DEKU"),
    SCENE_ENTRANCE(sDekuPalaceEntranceTable, "Z2_22DEKUCITY"),
    SCENE_ENTRANCE(sMountainSmithyEntranceTable, "Z2_KAJIYA"),
    SCENE_ENTRANCE(sTerminaFieldEntranceTable, "Z2_00KEIKOKU"),
    SCENE_ENTRANCE(sPostOfficeEntranceTable, "Z2_POSTHOUSE"),
    SCENE_ENTRANCE(sMarineResearchLabEntranceTable, "Z2_LABO"),
    SCENE_ENTRANCE(sDampesHouseEntranceTable, "Z2_DANPEI2TEST"),
    SCENE_ENTRANCE_NONE(),
    SCENE_ENTRANCE(sGoronShrineEntranceTable, "Z2_16GORON_HOUSE"),
    SCENE_ENTRANCE(sZoraHallEntranceTable, "Z2_33ZORACITY"),
    SCENE_ENTRANCE(sTradingPostEntranceTable, "Z2_8ITEMSHOP"),
    SCENE_ENTRANCE(sRomaniRanchEntranceTable, "Z2_F01"),
    SCENE_ENTRANCE(sTwinmoldsLairEntranceTable, "Z2_INISIE_BS"),
    SCENE_ENTRANCE(sGreatBayCoastEntranceTable, "Z2_30GYOSON"),
    SCENE_ENTRANCE(sZoraCapeEntranceTable, "Z2_31MISAKI"),
    SCENE_ENTRANCE(sLotteryShopEntranceTable, "Z2_TAKARAKUJI"),
    SCENE_ENTRANCE_NONE(),
    SCENE_ENTRANCE(sPiratesFortressExteriorEntranceTable, "Z2_TORIDE"),
    SCENE_ENTRANCE(sFishermansHutEntranceTable, "Z2_FISHERMAN"),
    SCENE_ENTRANCE(sGoronShopEntranceTable, "Z2_GORONSHOP"),
    SCENE_ENTRANCE(sDekuKingsChamberEntranceTable, "Z2_DEKU_KING"),
    SCENE_ENTRANCE(sMoonGoronTrialEntranceTable, "Z2_LAST_GORON"),
    SCENE_ENTRANCE(sRoadToSouthernSwampEntranceTable, "Z2_24KEMONOMITI"),
    SCENE_ENTRANCE(sDoggyRacetrackEntranceTable, "Z2_F01_B"),
    SCENE_ENTRANCE(sCuccoShackEntranceTable, "Z2_F01C"),
    SCENE_ENTRANCE(sIkanaGraveyardEntranceTable, "Z2_BOTI"),
    SCENE_ENTRANCE(sGohtsLairEntranceTable, "Z2_HAKUGIN_BS"),
    SCENE_ENTRANCE(sSouthernSwampPoisonedEntranceTable, "Z2_20SICHITAI"),
    SCENE_ENTRANCE(sWoodfallEntranceTable, "Z2_21MITURINMAE"),
    SCENE_ENTRANCE(sMoonZoraTrialEntranceTable, "Z2_LAST_ZORA"),
    SCENE_ENTRANCE(sGoronVillageSpringEntranceTable, "Z2_11GORONNOSATO2"),
    SCENE_ENTRANCE(sGreatBayTempleEntranceTable, "Z2_SEA"),
    SCENE_ENTRANCE(sWaterfallRapidsEntranceTable, "Z2_35TAKI"),
    SCENE_ENTRANCE(sBeneathTheWellEntranceTable, "Z2_REDEAD"),
    SCENE_ENTRANCE(sZoraHallRoomsEntranceTable, "Z2_BANDROOM"),
    SCENE_ENTRANCE(sGoronVillageWinterEntranceTable, "Z2_11GORONNOSATO"),
    SCENE_ENTRANCE(sGoronGraveryardEntranceTable, "Z2_GORON_HAKA"),
    SCENE_ENTRANCE(sSakonsHideoutEntranceTable, "Z2_SECOM"),
    SCENE_ENTRANCE(sMountainVillageWinterEntranceTable, "Z2_10YUKIYAMANOMURA"),
    SCENE_ENTRANCE(sGhostHutEntranceTable, "Z2_TOUGITES"),
    SCENE_ENTRANCE(sDekuShrineEntranceTable, "Z2_DANPEI"),
    SCENE_ENTRANCE(sRoadToIkanaEntranceTable, "Z2_IKANAMAE"),
    SCENE_ENTRANCE(sSwordmansSchoolEntranceTable, "Z2_DOUJOU"),
    SCENE_ENTRANCE(sMusicBoxHouseEntranceTable, "Z2_MUSICHOUSE"),
    SCENE_ENTRANCE(sIgosDuIkanasLairEntranceTable, "Z2_IKNINSIDE"),
    SCENE_ENTRANCE(sTouristInformationEntranceTable, "Z2_MAP_SHOP"),
    SCENE_ENTRANCE(sStoneTowerEntranceTable, "Z2_F40"),
    SCENE_ENTRANCE(sStoneTowerInvertedEntranceTable, "Z2_F41"),
    SCENE_ENTRANCE(sMountainVillageSpringEntranceTable, "Z2_10YUKIYAMANOMURA2"),
    SCENE_ENTRANCE(sPathToSnowheadEntranceTable, "Z2_14YUKIDAMANOMITI"),
    SCENE_ENTRANCE(sSnowheadEntranceTable, "Z2_12HAKUGINMAE"),
    SCENE_ENTRANCE(sPathToGoronVillageWinterEntranceTable, "Z2_17SETUGEN"),
    SCENE_ENTRANCE(sPathToGoronVillageSpringEntranceTable, "Z2_17SETUGEN2"),
    SCENE_ENTRANCE(sGyorgsLairEntranceTable, "Z2_SEA_BS"),
    SCENE_ENTRANCE(sSecretShrineEntranceTable, "Z2_RANDOM"),
    SCENE_ENTRANCE(sStockPotInnEntranceTable, "Z2_YADOYA"),
    SCENE_ENTRANCE(sGreatBayCutsceneEntranceTable, "Z2_KONPEKI_ENT"),
    SCENE_ENTRANCE(sClockTowerInteriorEntranceTable, "Z2_INSIDETOWER"),
    SCENE_ENTRANCE(sWoodsOfMysteryEntranceTable, "Z2_26SARUNOMORI"),
    SCENE_ENTRANCE(sLostWoodsEntranceTable, "Z2_LOST_WOODS"),
    SCENE_ENTRANCE(sMoonLinkTrialEntranceTable, "Z2_LAST_LINK"),
    SCENE_ENTRANCE(sTheMoonEntranceTable, "Z2_SOUGEN"),
    SCENE_ENTRANCE(sBombShopEntranceTable, "Z2_BOMYA"),
    SCENE_ENTRANCE(sGiantsChamberEntranceTable, "Z2_KYOJINNOMA"),
    SCENE_ENTRANCE(sGormanTrackEntranceTable, "Z2_KOEPONARACE"),
    SCENE_ENTRANCE(sGoronRacetrackEntranceTable, "Z2_GORONRACE"),
    SCENE_ENTRANCE(sEastClockTownEntranceTable, "Z2_TOWN"),
    SCENE_ENTRANCE(sWestClockTownEntranceTable, "Z2_ICHIBA"),
    SCENE_ENTRANCE(sNorthClockTownEntranceTable, "Z2_BACKTOWN"),
    SCENE_ENTRANCE(sSouthClockTownEntranceTable, "Z2_CLOCKTOWER"),
    SCENE_ENTRANCE(sLaundryPoolEntranceTable, "Z2_ALLEY"),
};

/**
 * Returns a pointer to an entrance table from a given entrance index.
 */
EntranceTableEntry* Entrance_GetTableEntry(u16 entranceIndex) {
    u32 entranceIndex2 = entranceIndex;
    EntranceTableEntry** tableEntryP = sSceneEntranceTable[entranceIndex2 >> 9].table;
    EntranceTableEntry* tableEntry = tableEntryP[(entranceIndex2 >> 4) & 0x1F];

    return &tableEntry[entranceIndex2 & 0xF];
}

/**
 * Returns the scene index from a given entrance index.
 */
s32 Entrance_GetSceneNum(u16 entranceIndex) {
    EntranceTableEntry* tableEntry = Entrance_GetTableEntry(entranceIndex);

    return tableEntry->sceneNum;
}

/**
 * Returns the absolute value scene index (since for some reason some of them are negative) from a given entrance index.
 */
s32 Entrance_GetSceneNumAbsolute(u16 entranceIndex) {
    EntranceTableEntry* tableEntry = Entrance_GetTableEntry(entranceIndex);

    return ABS_ALT(tableEntry->sceneNum);
}

/**
 * Returns the spawn index from a given entrance index.
 */
s32 Entrance_GetSpawnNum(u16 entranceIndex) {
    EntranceTableEntry* tableEntry = Entrance_GetTableEntry(entranceIndex);

    return tableEntry->spawnNum;
}

/**
 * Returns the transition effect flags from a given entrance index.
 */
s32 Entrance_GetTransitionFlags(u16 entranceIndex) {
    EntranceTableEntry* tableEntry = Entrance_GetTableEntry(entranceIndex);

    return tableEntry->flags;
}
