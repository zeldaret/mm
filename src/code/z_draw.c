#include "global.h"
#include "assets/objects/object_gi_arrow/object_gi_arrow.h"
#include "assets/objects/object_gi_arrowcase/object_gi_arrowcase.h"
#include "assets/objects/object_gi_bean/object_gi_bean.h"
#include "assets/objects/object_gi_bigbomb/object_gi_bigbomb.h"
#include "assets/objects/object_gi_bomb_1/object_gi_bomb_1.h"
#include "assets/objects/object_gi_bomb_2/object_gi_bomb_2.h"
#include "assets/objects/object_gi_bombpouch/object_gi_bombpouch.h"
#include "assets/objects/object_gi_bosskey/object_gi_bosskey.h"
#include "assets/objects/object_gi_bottle_04/object_gi_bottle_04.h"
#include "assets/objects/object_gi_bottle_15/object_gi_bottle_15.h"
#include "assets/objects/object_gi_bottle_16/object_gi_bottle_16.h"
#include "assets/objects/object_gi_bottle_21/object_gi_bottle_21.h"
#include "assets/objects/object_gi_bottle_22/object_gi_bottle_22.h"
#include "assets/objects/object_gi_bottle_red/object_gi_bottle_red.h"
#include "assets/objects/object_gi_bottle/object_gi_bottle.h"
#include "assets/objects/object_gi_bow/object_gi_bow.h"
#include "assets/objects/object_gi_camera/object_gi_camera.h"
#include "assets/objects/object_gi_compass/object_gi_compass.h"
#include "assets/objects/object_gi_fieldmap/object_gi_fieldmap.h"
#include "assets/objects/object_gi_fish/object_gi_fish.h"
#include "assets/objects/object_gi_ghost/object_gi_ghost.h"
#include "assets/objects/object_gi_glasses/object_gi_glasses.h"
#include "assets/objects/object_gi_gold_dust/object_gi_gold_dust.h"
#include "assets/objects/object_gi_golonmask/object_gi_golonmask.h"
#include "assets/objects/object_gi_heart/object_gi_heart.h"
#include "assets/objects/object_gi_hearts/object_gi_hearts.h"
#include "assets/objects/object_gi_hookshot/object_gi_hookshot.h"
#include "assets/objects/object_gi_insect/object_gi_insect.h"
#include "assets/objects/object_gi_key/object_gi_key.h"
#include "assets/objects/object_gi_ki_tan_mask/object_gi_ki_tan_mask.h"
#include "assets/objects/object_gi_liquid/object_gi_liquid.h"
#include "assets/objects/object_gi_loach/object_gi_loach.h"
#include "assets/objects/object_gi_longsword/object_gi_longsword.h"
#include "assets/objects/object_gi_m_arrow/object_gi_m_arrow.h"
#include "assets/objects/object_gi_magicmushroom/object_gi_magicmushroom.h"
#include "assets/objects/object_gi_magicpot/object_gi_magicpot.h"
#include "assets/objects/object_gi_map/object_gi_map.h"
#include "assets/objects/object_gi_mask03/object_gi_mask03.h"
#include "assets/objects/object_gi_mask05/object_gi_mask05.h"
#include "assets/objects/object_gi_mask06/object_gi_mask06.h"
#include "assets/objects/object_gi_mask09/object_gi_mask09.h"
#include "assets/objects/object_gi_mask10/object_gi_mask10.h"
#include "assets/objects/object_gi_mask11/object_gi_mask11.h"
#include "assets/objects/object_gi_mask12/object_gi_mask12.h"
#include "assets/objects/object_gi_mask13/object_gi_mask13.h"
#include "assets/objects/object_gi_mask14/object_gi_mask14.h"
#include "assets/objects/object_gi_mask15/object_gi_mask15.h"
#include "assets/objects/object_gi_mask16/object_gi_mask16.h"
#include "assets/objects/object_gi_mask17/object_gi_mask17.h"
#include "assets/objects/object_gi_mask18/object_gi_mask18.h"
#include "assets/objects/object_gi_mask20/object_gi_mask20.h"
#include "assets/objects/object_gi_mask21/object_gi_mask21.h"
#include "assets/objects/object_gi_mask22/object_gi_mask22.h"
#include "assets/objects/object_gi_mask23/object_gi_mask23.h"
#include "assets/objects/object_gi_melody/object_gi_melody.h"
#include "assets/objects/object_gi_milk/object_gi_milk.h"
#include "assets/objects/object_gi_mssa/object_gi_mssa.h"
#include "assets/objects/object_gi_nuts/object_gi_nuts.h"
#include "assets/objects/object_gi_nutsmask/object_gi_nutsmask.h"
#include "assets/objects/object_gi_ocarina/object_gi_ocarina.h"
#include "assets/objects/object_gi_purse/object_gi_purse.h"
#include "assets/objects/object_gi_rabit_mask/object_gi_rabit_mask.h"
#include "assets/objects/object_gi_reserve_b_00/object_gi_reserve_b_00.h"
#include "assets/objects/object_gi_reserve_b_01/object_gi_reserve_b_01.h"
#include "assets/objects/object_gi_reserve_c_00/object_gi_reserve_c_00.h"
#include "assets/objects/object_gi_reserve_c_01/object_gi_reserve_c_01.h"
#include "assets/objects/object_gi_reserve00/object_gi_reserve00.h"
#include "assets/objects/object_gi_reserve01/object_gi_reserve01.h"
#include "assets/objects/object_gi_rupy/object_gi_rupy.h"
#include "assets/objects/object_gi_schedule/object_gi_schedule.h"
#include "assets/objects/object_gi_seahorse/object_gi_seahorse.h"
#include "assets/objects/object_gi_shield_2/object_gi_shield_2.h"
#include "assets/objects/object_gi_shield_3/object_gi_shield_3.h"
#include "assets/objects/object_gi_soldout/object_gi_soldout.h"
#include "assets/objects/object_gi_soul/object_gi_soul.h"
#include "assets/objects/object_gi_stick/object_gi_stick.h"
#include "assets/objects/object_gi_stonemask/object_gi_stonemask.h"
#include "assets/objects/object_gi_sutaru/object_gi_sutaru.h"
#include "assets/objects/object_gi_sword_1/object_gi_sword_1.h"
#include "assets/objects/object_gi_sword_2/object_gi_sword_2.h"
#include "assets/objects/object_gi_sword_3/object_gi_sword_3.h"
#include "assets/objects/object_gi_sword_4/object_gi_sword_4.h"
#include "assets/objects/object_gi_truth_mask/object_gi_truth_mask.h"
#include "assets/objects/object_gi_zoramask/object_gi_zoramask.h"
#include "assets/objects/object_bsmask/object_bsmask.h"
#include "assets/objects/object_st/object_st.h"

extern UNK_TYPE D_06001254;
extern UNK_TYPE D_06001C60;

void GetItem_DrawBombchu(PlayState* play, s16 drawId);
void GetItem_DrawPoes(PlayState* play, s16 drawId);
void GetItem_DrawFairy2(PlayState* play, s16 drawId);
void GetItem_DrawSkullToken(PlayState* play, s16 drawId);
void GetItem_DrawCompass(PlayState* play, s16 drawId);
void GetItem_DrawPotion(PlayState* play, s16 drawId);
void GetItem_DrawGoronSword(PlayState* play, s16 drawId);
void GetItem_DrawDekuNuts(PlayState* play, s16 drawId);
void GetItem_DrawRecoveryHeart(PlayState* play, s16 drawId);
void GetItem_DrawFish(PlayState* play, s16 drawId);
void func_800EF054(PlayState* play, s16 drawId);
void func_800EF0F0(PlayState* play, s16 drawId);
void func_800EF1F4(PlayState* play, s16 drawId);
void func_800EF2AC(PlayState* play, s16 drawId);
void GetItem_DrawSeaHorseCaught(PlayState* play, s16 drawId);
void GetItem_DrawFairy(PlayState* play, s16 drawId);
void GetItem_DrawMoonsTear(PlayState* play, s16 drawId);
void GetItem_DrawMagicArrow(PlayState* play, s16 drawId);
void GetItem_DrawUpgrades(PlayState* play, s16 drawId);
void GetItem_DrawRupee(PlayState* play, s16 drawId);
void GetItem_DrawSmallRupee(PlayState* play, s16 drawId);
void GetItem_DrawWallet(PlayState* play, s16 drawId);
void GetItem_DrawRemains(PlayState* play, s16 drawId);

static DrawItemTableEntry sDrawItemTable[] = {
    // GID_BOTTLE, OBJECT_GI_BOTTLE
    { func_800EF0F0, { gGiBottleStopperDL, gGiBottleDL } },
    // GID_KEY_SMALL, OBJECT_GI_KEY
    { func_800EF054, { gGiSmallKeyDL } },
    // GID_MASK_KAMARO, OBJECT_GI_MASK17
    { func_800EF1F4, { object_gi_mask17_DL_000FD8, object_gi_mask17_DL_000FD0 } },
    // GID_MASK_COUPLE, OBJECT_GI_MASK13
    { func_800EF0F0, { object_gi_mask13_DL_0006A0, object_gi_mask13_DL_0005A0 } },
    // GID_04, OBJECT_GI_MELODY
    { func_800EF2AC, { object_gi_melody_DL_000AA0, object_gi_melody_DL_000AE0 } },
    // GID_05, OBJECT_GI_MELODY
    { func_800EF2AC, { object_gi_melody_DL_000AB0, object_gi_melody_DL_000AE0 } },
    // GID_06, OBJECT_GI_MELODY
    { func_800EF2AC, { object_gi_melody_DL_000AC0, object_gi_melody_DL_000AE0 } },
    // GID_07, OBJECT_GI_MELODY
    { func_800EF2AC, { object_gi_melody_DL_000AD0, object_gi_melody_DL_000AE0 } },
    // GID_HEART, OBJECT_GI_HEART
    { GetItem_DrawRecoveryHeart, { gGiRecoveryHeartDL } },
    // GID_KEY_BOSS, OBJECT_GI_KEY_BOSS
    { func_800EF0F0, { gGiBossKeyDL, gGiBossKeyGemDL } },
    // GID_COMPASS, OBJECT_GI_COMPASS
    { GetItem_DrawCompass, { gGiCompassDL, gGiCompassGlassDL } },
    // GID_BOMBERS_NOTEBOOK, OBJECT_GI_SCHEDULE
    { func_800EF0F0, { object_gi_schedule_DL_000B78, object_gi_schedule_DL_0006C0 } },
    // GID_MASK_STONE, OBJECT_GI_STONEMASK
    { func_800EF0F0, { object_gi_stonemask_DL_000E48, object_gi_stonemask_DL_000A10 } },
    // GID_MASK_KAFEIS_MASK, OBJECT_GI_MASK05
    { func_800EF1F4, { object_gi_mask05_DL_001048, object_gi_mask05_DL_001040 } },
    // GID_MASK_CIRCUS_LEADER, OBJECT_GI_MASK11
    { func_800EF0F0, { object_gi_mask11_DL_000C00, object_gi_mask11_DL_000B50 } },
    // GID_MASK_BREMEN, OBJECT_GI_MASK20
    { func_800EF1F4, { object_gi_mask20_DL_000808, object_gi_mask20_DL_000800 } },
    // GID_MASK_ALL_NIGHT, OBJECT_GI_MASK06
    { func_800EF0F0, { object_gi_mask06_DL_000968, object_gi_mask06_DL_0006F0 } },
    // GID_NUTS, OBJECT_GI_NUTS
    { GetItem_DrawDekuNuts, { gGiNutDL } },
    // GID_HEART_CONTAINER, OBJECT_GI_HEARTS
    { func_800EF2AC, { gGiHeartBorderDL, gGiHeartContainerDL } },
    // GID_HEART_PIECE, OBJECT_GI_HEARTS
    { func_800EF2AC, { gGiHeartBorderDL, gGiHeartPieceDL } },
    // GID_QUIVER_30, OBJECT_GI_ARROWCASE
    { GetItem_DrawUpgrades, { gGiQuiverInnerDL, gGiQuiver30InnerColorDL, gGiQuiver30OuterColorDL, gGiQuiverOuterDL } },
    // GID_QUIVER_40, OBJECT_GI_ARROWCASE
    { GetItem_DrawUpgrades, { gGiQuiverInnerDL, gGiQuiver40InnerColorDL, gGiQuiver40OuterColorDL, gGiQuiverOuterDL } },
    // GID_QUIVER_50, OBJECT_GI_ARROWCASE
    { GetItem_DrawUpgrades, { gGiQuiverInnerDL, gGiQuiver50InnerColorDL, gGiQuiver50OuterColorDL, gGiQuiverOuterDL } },
    // GID_BOMB_BAG_20, OBJECT_GI_BOMBPOUCH
    { GetItem_DrawUpgrades, { gGiBombBagDL, gGiBombBag20BagColorDL, gGiBombBag20RingColorDL, gGiBombBagRingDL } },
    // GID_BOMB_BAG_30, OBJECT_GI_BOMBPOUCH
    { GetItem_DrawUpgrades, { gGiBombBagDL, gGiBombBag30BagColorDL, gGiBombBag30RingColorDL, gGiBombBagRingDL } },
    // GID_BOMB_BAG_40, OBJECT_GI_BOMBPOUCH
    { GetItem_DrawUpgrades, { gGiBombBagDL, gGiBombBag40BagColorDL, gGiBombBag40RingColorDL, gGiBombBagRingDL } },
    // GID_STICK, OBJECT_GI_STICK
    { func_800EF054, { gGiStickDL } },
    // GID_DUNGEON_MAP, OBJECT_GI_MAP
    { func_800EF054, { gGiDungeonMapDL } },
    // GID_MAGIC_SMALL, OBJECT_GI_MAGICPOT
    { func_800EF054, { gGiMagicJarSmallDL } },
    // GID_MAGIC_LARGE, OBJECT_GI_MAGICPOT
    { func_800EF054, { gGiMagicJarLargeDL } },
    // GID_BOMB, OBJECT_GI_BOMB_1
    { func_800EF054, { gGiBombDL } },
    // GID_STONE_OF_AGONY, OBJECT_GI_MAP
    { func_800EF054, { gGiStoneOfAgonyDL } },
    // GID_WALLET_ADULT, OBJECT_GI_PURSE
    { GetItem_DrawWallet,
      { gGiWalletDL, gGiAdultWalletColorDL, gGiAdultWalletRupeeOuterColorDL, gGiWalletRupeeOuterDL,
        gGiAdultWalletStringColorDL, gGiWalletStringDL, gGiAdultWalletRupeeInnerColorDL, gGiWalletRupeeInnerDL } },
    // GID_WALLET_GIANT, OBJECT_GI_PURSE
    { GetItem_DrawWallet,
      { gGiWalletDL, gGiGiantsWalletColorDL, gGiGiantsWalletRupeeOuterColorDL, gGiWalletRupeeOuterDL,
        gGiGiantsWalletStringColorDL, gGiWalletStringDL, gGiGiantsWalletRupeeInnerColorDL, gGiWalletRupeeInnerDL } },
    // GID_MASK_DON_GERO, OBJECT_GI_MASK16
    { func_800EF0F0, { object_gi_mask16_DL_001438, object_gi_mask16_DL_001040 } },
    // GID_ARROWS_SMALL, OBJECT_GI_ARROW
    { func_800EF054, { gGiArrowSmallDL } },
    // GID_ARROWS_MEDIUM, OBJECT_GI_ARROW
    { func_800EF054, { gGiArrowMediumDL } },
    // GID_ARROWS_LARGE, OBJECT_GI_ARROW
    { func_800EF054, { gGiArrowLargeDL } },
    // GID_BOMBCHU, OBJECT_GI_BOMB_2
    { GetItem_DrawBombchu, { gGiBombchuDL } },
    // GID_SHIELD_HERO, OBJECT_GI_SHIELD_2
    { func_800EF0F0, { object_gi_shield_2_DL_000D28, object_gi_shield_2_DL_0009F0 } },
    // GID_HOOKSHOT, OBJECT_GI_HOOKSHOT
    { func_800EF1F4, { object_gi_hookshot_DL_000E48, object_gi_hookshot_DL_000A10 } },
    // GID_29, OBJECT_GI_HOOKSHOT
    { func_800EF1F4, { object_gi_hookshot_DL_000E48, object_gi_hookshot_DL_000A10 } },
    // GID_OCARINA, OBJECT_GI_OCARINA
    { func_800EF0F0, { gGiOcarinaTimeDL, gGiOcarinaTimeHolesDL } },
    // GID_MILK, OBJECT_GI_MILK
    { func_800EF0F0, { gGiMilkBottleContentsDL, gGiMilkBottleDL } },
    // GID_MASK_KEATON, OBJECT_GI_KI_TAN_MASK
    { func_800EF0F0, { gGiKeatonMaskDL, gGiKeatonMaskEyesDL } },
    // GID_TINGLE_MAP, OBJECT_GI_FIELDMAP
    { func_800EF1F4, { object_gi_fieldmap_DL_0006E8, object_gi_fieldmap_DL_0006E0 } },
    // GID_BOW, OBJECT_GI_BOW
    { func_800EF1F4, { object_gi_bow_DL_000C80, object_gi_bow_DL_000F40 } },
    // GID_LENS, OBJECT_GI_GLASSES
    { func_800EF0F0, { gGiLensDL, gGiLensGlassDL } },
    // GID_POTION_GREEN, OBJECT_GI_LIQUID
    { GetItem_DrawPotion,
      { gGiPotionPotDL, gGiGreenPotColorDL, gGiGreenLiquidColorDL, gGiPotionLiquidDL, gGiGreenPatternColorDL,
        gGiPotionPatternDL } },
    // GID_POTION_RED, OBJECT_GI_LIQUID
    { GetItem_DrawPotion,
      { gGiPotionPotDL, gGiRedPotColorDL, gGiRedLiquidColorDL, gGiPotionLiquidDL, gGiRedPatternColorDL,
        gGiPotionPatternDL } },
    // GID_POTION_BLUE, OBJECT_GI_LIQUID
    { GetItem_DrawPotion,
      { gGiPotionPotDL, gGiBluePotColorDL, gGiBlueLiquidColorDL, gGiPotionLiquidDL, gGiBluePatternColorDL,
        gGiPotionPatternDL } },
    // GID_SHIELD_MIRROR, OBJECT_GI_SHIELD_3
    { func_800EF0F0, { object_gi_shield_3_DL_000BF8, object_gi_shield_3_DL_000770 } },
    // GID_MAGIC_BEANS, OBJECT_GI_BEAN
    { func_800EF054, { gGiBeanDL } },
    // GID_FISH, OBJECT_GI_FISH
    { GetItem_DrawFish, { gGiFishDL } },
    // GID_LETTER_MAMA, OBJECT_GI_RESERVE_B_01
    { func_800EF0F0, { object_gi_reserve_b_01_DL_000948, object_gi_reserve_b_01_DL_000820 } },
    // GID_37
    { func_800EF054, { NULL } },
    // GID_SWORD_BGS, OBJECT_GI_LONGSWORD
    { GetItem_DrawGoronSword, { gGiBiggoronSwordDL } },
    // GID_39, OBJECT_GI_MSSA
    { func_800EF0F0, { object_gi_mssa_DL_000DF0, object_gi_mssa_DL_000C00 } },
    // GID_MASK_BLAST, OBJECT_GI_MASK21
    { func_800EF0F0, { object_gi_mask21_DL_000AA8, object_gi_mask21_DL_000830 } },
    // GID_FAIRY, OBJECT_GI_BOTTLE_04
    { GetItem_DrawFairy,
      { object_gi_bottle_04_DL_000B10, object_gi_bottle_04_DL_0008B8, object_gi_bottle_04_DL_0007F0,
        (Gfx*)0x060007B0 } },
    // GID_MASK_SCENTS, OBJECT_GI_MASK22
    { func_800EF1F4, { object_gi_mask22_DL_000918, object_gi_mask22_DL_000880 } },
    // GID_MASK_CAPTAIN, OBJECT_GI_MASK18
    { func_800EF1F4, { object_gi_mask18_DL_000FA0, object_gi_mask18_DL_000CF0 } },
    // GID_MASK_BUNNY, OBJECT_GI_RABIT_MASK
    { func_800EF0F0, { gGiBunnyHoodDL, gGiBunnyHoodEyesDL } },
    // GID_MASK_TRUTH, OBJECT_GI_TRUTH_MASK
    { func_800EF0F0, { gGiMaskOfTruthDL, gGiMaskOfTruthAccentsDL } },
    // GID_DEED_SWAMP, OBJECT_GI_RESERVE01
    { func_800EF1F4, { object_gi_reserve01_DL_000A08, object_gi_reserve01_DL_000990 } },
    // GID_DEED_MOUNTAIN, OBJECT_GI_RESERVE01
    { func_800EF1F4, { object_gi_reserve01_DL_000A08, object_gi_reserve01_DL_0009B8 } },
    // GID_42, OBJECT_GI_RUPY
    { GetItem_DrawRupee,
      { object_gi_rupy_DL_000620, object_gi_rupy_DL_000540, object_gi_rupy_DL_000730, object_gi_rupy_DL_000600 } },
    // GID_DEED_OCEAN, OBJECT_GI_RESERVE01
    { func_800EF1F4, { object_gi_reserve01_DL_000A08, object_gi_reserve01_DL_0009E0 } },
    // GID_MASK_GORON, OBJECT_GI_GOLONMASK
    { func_800EF0F0, { object_gi_golonmask_DL_0010D0, object_gi_golonmask_DL_000BA0 } },
    // GID_MASK_ZORA, OBJECT_GI_ZORAMASK
    { func_800EF1F4, { object_gi_zoramask_DL_000C10, object_gi_zoramask_DL_0007D0 } },
    // GID_46
    { GetItem_DrawBombchu, { NULL } },
    // GID_ARROW_FIRE, OBJECT_GI_M_ARROW
    { GetItem_DrawMagicArrow, { gGiMagicArrowDL, gGiFireArrowColorDL, gGiArrowMagicDL } },
    // GID_ARROW_ICE, OBJECT_GI_M_ARROW
    { GetItem_DrawMagicArrow, { gGiMagicArrowDL, gGiIceArrowColorDL, gGiArrowMagicDL } },
    // GID_ARROW_LIGHT, OBJECT_GI_M_ARROW
    { GetItem_DrawMagicArrow, { gGiMagicArrowDL, gGiLightArrowColorDL, gGiArrowMagicDL } },
    // GID_SKULL_TOKEN, OBJECT_GI_SUTARU
    { GetItem_DrawSkullToken, { gGiSkulltulaTokenDL, gGiSkulltulaTokenFlameDL } },
    // GID_BUG, OBJECT_GI_INSECT
    { func_800EF0F0, { gGiBugsContainerDL, gGiBugsGlassDL } },
    // GID_4C
    { func_800EF0F0, { NULL } },
    // GID_POE, OBJECT_GI_GHOST
    { GetItem_DrawPoes, { gGiGhostContainerLidDL, gGiGhostContainerGlassDL, gGiGhostContainerContentsDL, gGiPoeColorDL } },
    // GID_FAIRY_2, OBJECT_GI_SOUL
    { GetItem_DrawFairy2, { gGiFairyContainerBaseCapDL, gGiFairyContainerGlassDL, gGiFairyContainerContentsDL } },
    // GID_4F, OBJECT_GI_RUPY
    { GetItem_DrawSmallRupee,
      { object_gi_rupy_DL_000620, object_gi_rupy_DL_0004A0, object_gi_rupy_DL_000730, object_gi_rupy_DL_000560 } },
    // GID_50, OBJECT_GI_RUPY
    { GetItem_DrawSmallRupee,
      { object_gi_rupy_DL_000620, object_gi_rupy_DL_0004C0, object_gi_rupy_DL_000730, object_gi_rupy_DL_000580 } },
    // GID_51, OBJECT_GI_RUPY
    { GetItem_DrawSmallRupee,
      { object_gi_rupy_DL_000620, object_gi_rupy_DL_0004E0, object_gi_rupy_DL_000730, object_gi_rupy_DL_0005A0 } },
    // GID_BIG_POE, OBJECT_GI_GHOST
    { GetItem_DrawPoes,
      { gGiGhostContainerLidDL, gGiGhostContainerGlassDL, gGiGhostContainerContentsDL, gGiBigPoeColorDL } },
    // GID_53, OBJECT_GI_RUPY
    { GetItem_DrawRupee,
      { object_gi_rupy_DL_000620, object_gi_rupy_DL_000500, object_gi_rupy_DL_000730, object_gi_rupy_DL_0005C0 } },
    // GID_54, OBJECT_GI_RUPY
    { GetItem_DrawRupee,
      { object_gi_rupy_DL_000620, object_gi_rupy_DL_000520, object_gi_rupy_DL_000730, object_gi_rupy_DL_0005E0 } },
    // GID_SWORD_KOKIRI, OBJECT_GI_SWORD_1
    { func_800EF1F4, { object_gi_sword_1_DL_000998, object_gi_sword_1_DL_000850 } },
    // GID_SKULL_TOKEN_2, OBJECT_ST
    { GetItem_DrawSkullToken, { object_st_DL_004DB0, object_st_DL_004EB8 } },
    // GID_ZORA_EGG, OBJECT_GI_BOTTLE_RED
    { func_800EF0F0, { object_gi_bottle_red_DL_000CC0, object_gi_bottle_red_DL_0009B0 } },
    // GID_58, OBJECT_GI_BOTTLE_15
    { func_800EF0F0, { object_gi_bottle_15_DL_001010, object_gi_bottle_15_DL_000CF0 } },
    // GID_MOON_TEAR, OBJECT_GI_RESERVE00
    { GetItem_DrawMoonsTear, { object_gi_reserve00_DL_000D78, object_gi_reserve00_DL_000C80 } },
    // GID_DEED_LAND, OBJECT_GI_RESERVE01
    { func_800EF1F4, { object_gi_reserve01_DL_000A08, object_gi_reserve01_DL_000968 } },
    // GID_MASK_DEKU, OBJECT_GI_NUTSMASK
    { func_800EF0F0, { object_gi_nutsmask_DL_000F20, object_gi_nutsmask_DL_000B50 } },
    // GID_REMAINS_ODOLWA, OBJECT_BSMASK
    { GetItem_DrawRemains, { object_bsmask_DL_000690, object_bsmask_DL_000690 } },
    // GID_POWDER_KEG, OBJECT_GI_BIGBOMB
    { func_800EF0F0, { object_gi_bigbomb_DL_000DA0, object_gi_bigbomb_DL_000BC0 } },
    // GID_GOLD_DUST, OBJECT_GI_GOLD_DUST
    { func_800EF1F4, { object_gi_gold_dust_DL_000888, object_gi_gold_dust_DL_000880 } },
    // GID_SEA_HORSE, OBJECT_GI_BOTTLE_16
    { func_800EF0F0, { object_gi_bottle_16_DL_000D18, object_gi_bottle_16_DL_0009A0 } },
    // GID_60, OBJECT_GI_BOTTLE_22
    { func_800EF0F0, { object_gi_bottle_22_DL_000FB8, object_gi_bottle_22_DL_000C90 } },
    // GID_HYLIAN_LOACH, OBJECT_GI_LOACH
    { func_800EF0F0, { object_gi_loach_DL_000D30, object_gi_loach_DL_0007F0 } },
    // GID_SEA_HORSE_CAUGHT, OBJECT_GI_SEAHORSE
    { GetItem_DrawSeaHorseCaught,
      { object_gi_seahorse_DL_000F08, object_gi_seahorse_DL_000B20, object_gi_seahorse_DL_000A90, (Gfx*)0x06000A50 } },
    // GID_REMAINS_GOHT, OBJECT_BSMASK
    { GetItem_DrawRemains, { object_bsmask_DL_003AD0, object_bsmask_DL_003AD0 } },
    // GID_REMAINS_GYORG, OBJECT_BSMASK
    { GetItem_DrawRemains, { object_bsmask_DL_001D80, object_bsmask_DL_001D80 } },
    // GID_REMAINS_TWINMOLD, OBJECT_BSMASK
    { GetItem_DrawRemains, { object_bsmask_DL_005020, object_bsmask_DL_005020 } },
    // GID_SWORD_RAZOR, OBJECT_GI_SWORD_2
    { func_800EF1F4, { object_gi_sword_2_DL_000C08, object_gi_sword_2_DL_000C00 } },
    // GID_SWORD_GILDED, OBJECT_GI_SWORD_3
    { func_800EF1F4, { object_gi_sword_3_DL_0009E8, object_gi_sword_3_DL_0009E0 } },
    // GID_SWORD_GREAT_FAIRY, OBJECT_GI_SWORD_4
    { func_800EF0F0, { object_gi_sword_4_DL_000AD8, object_gi_sword_4_DL_000940 } },
    // GID_MASK_GARO, OBJECT_GI_MASK09
    { func_800EF0F0, { object_gi_mask09_DL_0008F0, object_gi_mask09_DL_0007A0 } },
    // GID_MASK_GREAT_FAIRY, OBJECT_GI_MASK14
    { func_800EF0F0, { object_gi_mask14_DL_001000, object_gi_mask14_DL_000ED0 } },
    // GID_MASK_GIBDO, OBJECT_GI_MASK15
    { func_800EF0F0, { object_gi_mask15_DL_000F58, object_gi_mask15_DL_000B30 } },
    // GID_ROOM_KEY, OBJECT_GI_RESERVE_B_00
    { func_800EF0F0, { object_gi_reserve_b_00_DL_000C20, object_gi_reserve_b_00_DL_0007D0 } },
    // GID_LETTER_TO_KAFEI, OBJECT_GI_RESERVE_C_00
    { func_800EF0F0, { object_gi_reserve_c_00_DL_0005F0, object_gi_reserve_c_00_DL_0004A0 } },
    // GID_PENDANT_MEMORIES, OBJECT_GI_RESERVE_C_01
    { func_800EF0F0, { object_gi_reserve_c_01_DL_000C78, object_gi_reserve_c_01_DL_000750 } },
    // GID_MUSHROOM, OBJECT_GI_MAGICMUSHROOM
    { func_800EF0F0, { object_gi_magicmushroom_DL_000958, object_gi_magicmushroom_DL_000640 } },
    // GID_MASK_ROMANI, OBJECT_GI_MASK10
    { func_800EF0F0, { object_gi_mask10_DL_000B60, object_gi_mask10_DL_000A30 } },
    // GID_MASK_POSTMAN, OBJECT_GI_MASK12
    { func_800EF0F0, { object_gi_mask12_DL_000608, object_gi_mask12_DL_000570 } },
    // GID_MASK_GIANT, OBJECT_GI_MASK23
    { func_800EF1F4, { object_gi_mask23_DL_000C00, object_gi_mask23_DL_0008C0 } },
    // GID_CHATEAU, OBJECT_GI_BOTTLE_21
    { func_800EF0F0, { object_gi_bottle_21_DL_000E90, object_gi_bottle_21_DL_000A50 } },
    // GID_PICTO_BOX, OBJECT_GI_CAMERA
    { func_800EF0F0, { object_gi_camera_DL_000EC8, object_gi_camera_DL_000BC0 } },
    // GID_MASK_FIERCE_DEITY, OBJECT_GI_MASK03
    { func_800EF1F4, { object_gi_mask03_DL_000B90, object_gi_mask03_DL_0009B0 } },
};

/**
 * Draw "Get Item" Model
 * Calls the corresponding draw function for the given draw ID
 */
void GetItem_Draw(PlayState* play, s16 drawId) {
    sDrawItemTable[drawId].drawFunc(play, drawId);
}

void GetItem_DrawBombchu(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C214(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void GetItem_DrawPoes(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);

    func_8012C2DC(play->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[1]);

    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(play->state.gfxCtx, 0, play->state.frames * 0, play->state.frames * 0, 0x10, 0x20, 1,
                                play->state.frames, -(play->state.frames * 6), 0x10, 0x20));

    Matrix_Push();
    Matrix_ReplaceRotation(&play->billboardMtxF);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[3]);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[2]);

    Matrix_Pop();

    CLOSE_DISPS(play->state.gfxCtx);
}

void GetItem_DrawFairy2(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);

    func_8012C2DC(play->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[1]);
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(play->state.gfxCtx, 0, play->state.frames * 0, play->state.frames * 0, 0x20, 0x20, 1,
                                play->state.frames, -(play->state.frames * 6), 0x20, 0x20));

    Matrix_Push();
    Matrix_ReplaceRotation(&play->billboardMtxF);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[2]);

    Matrix_Pop();

    CLOSE_DISPS(play->state.gfxCtx);
}

void GetItem_DrawSkullToken(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);

    func_8012C2DC(play->state.gfxCtx);

    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(play->state.gfxCtx, 0, play->state.frames * 0, -(play->state.frames * 5), 0x20, 0x20, 1,
                                play->state.frames * 0, play->state.frames * 0, 0x20, 0x40));
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[1]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void GetItem_DrawCompass(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);

    POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 5);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[1]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void GetItem_DrawPotion(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08,
               Gfx_TwoTexScroll(play->state.gfxCtx, 0, -play->state.frames, play->state.frames, 0x20, 0x20, 1,
                                -play->state.frames, play->state.frames, 0x20, 0x20));
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[1]);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[2]);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[3]);

    func_8012C2DC(play->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[4]);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[5]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void GetItem_DrawGoronSword(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08,
               Gfx_TwoTexScroll(play->state.gfxCtx, 0, play->state.frames * 1, play->state.frames * 0, 0x20, 0x20, 1,
                                play->state.frames * 0, play->state.frames * 0, 0x20, 0x20));
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void GetItem_DrawDekuNuts(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08,
               Gfx_TwoTexScroll(play->state.gfxCtx, 0, play->state.frames * 6, play->state.frames * 6, 0x20, 0x20, 1,
                                play->state.frames * 6, play->state.frames * 6, 0x20, 0x20));
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void GetItem_DrawRecoveryHeart(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C2DC(play->state.gfxCtx);

    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(play->state.gfxCtx, 0, play->state.frames * 0, -(play->state.frames * 3), 0x20, 0x20, 1,
                                play->state.frames * 0, -(play->state.frames * 2), 0x20, 0x20));
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[0]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void GetItem_DrawFish(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C2DC(play->state.gfxCtx);

    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(play->state.gfxCtx, 0, play->state.frames * 0, play->state.frames * 1, 0x20, 0x20, 1,
                                play->state.frames * 0, play->state.frames * 1, 0x20, 0x20));
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[0]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_800EF054(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_800EF0F0(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);

    func_8012C2DC(play->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[1]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_800EF1F4(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[1]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_800EF2AC(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C2DC(play->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[0]);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[1]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void GetItem_DrawSeaHorseCaught(PlayState* play, s16 drawId) {
    s32 pad;
    MtxF sp4C;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);

    func_8012C2DC(play->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[1]);

    Matrix_MtxToMtxF(Lib_SegmentedToVirtual(sDrawItemTable[drawId].dlists[3]), &sp4C);
    Matrix_Mult(&sp4C, MTXMODE_APPLY);
    Matrix_ReplaceRotation(&play->billboardMtxF);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[2]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void GetItem_DrawFairy(PlayState* play, s16 drawId) {
    s32 pad;
    MtxF sp4C;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    AnimatedMat_Draw(play, Lib_SegmentedToVirtual(&D_06001254));

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[1]);

    Matrix_MtxToMtxF(Lib_SegmentedToVirtual(sDrawItemTable[drawId].dlists[3]), &sp4C);
    Matrix_Mult(&sp4C, MTXMODE_APPLY);
    Matrix_ReplaceRotation(&play->billboardMtxF);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[2]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void GetItem_DrawMoonsTear(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    AnimatedMat_Draw(play, Lib_SegmentedToVirtual(&D_06001C60));

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);

    Matrix_ReplaceRotation(&play->billboardMtxF);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[1]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void GetItem_DrawMagicArrow(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);

    func_8012C2DC(play->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[1]);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[2]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void GetItem_DrawUpgrades(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[1]);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[2]);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[3]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void GetItem_DrawRupee(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[1]);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);

    func_8012C2DC(play->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[3]);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[2]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void GetItem_DrawSmallRupee(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    Matrix_Scale(0.7f, 0.7f, 0.7f, MTXMODE_APPLY);
    func_8012C28C(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[1]);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);

    func_8012C2DC(play->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[3]);
    gSPDisplayList(POLY_XLU_DISP++, sDrawItemTable[drawId].dlists[2]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void GetItem_DrawWallet(PlayState* play, s16 drawId) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[1]);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[2]);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[3]);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[4]);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[5]);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[6]);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[7]);

    CLOSE_DISPS(play->state.gfxCtx);
}

void GetItem_DrawRemains(PlayState* play, s16 drawId) {
    s32 pad;
    s8 objectIdx;

    OPEN_DISPS(play->state.gfxCtx);

    objectIdx = Object_GetIndex(&play->objectCtx, OBJECT_BSMASK);

    gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.status[objectIdx].segment);

    func_8012C28C(play->state.gfxCtx);
    Matrix_Scale(0.02f, 0.02f, 0.02f, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sDrawItemTable[drawId].dlists[0]);

    POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);

    CLOSE_DISPS(play->state.gfxCtx);
}
