#include "global.h"
#include "interface/parameter_static/parameter_static.h"
#include "archives/icon_item_static/icon_item_static_yar.h"
#include "archives/icon_item_24_static/icon_item_24_static_yar.h"

// Bit Flag array in which gBitFlags[n] is (1 << n)
u32 gBitFlags[] = {
    (1 << 0),  (1 << 1),  (1 << 2),  (1 << 3),  (1 << 4),  (1 << 5),  (1 << 6),  (1 << 7),
    (1 << 8),  (1 << 9),  (1 << 10), (1 << 11), (1 << 12), (1 << 13), (1 << 14), (1 << 15),
    (1 << 16), (1 << 17), (1 << 18), (1 << 19), (1 << 20), (1 << 21), (1 << 22), (1 << 23),
    (1 << 24), (1 << 25), (1 << 26), (1 << 27), (1 << 28), (1 << 29), (1 << 30), (1 << 31),
};

// four-bit masks
u16 gEquipMasks[] = {
    0xF << 0,  // Sword
    0xF << 4,  // Shield
    0xF << 8,  // Unused (Tunic)
    0xF << 12, // Unused (Boots)
};

// four-bit masks
u16 gEquipNegMasks[] = {
    ~(0xF << 0),        // Sword
    ~(0xF << 4),        // Shield
    ~(0xF << 8),        // Unused (Tunic)
    (u16) ~(0xF << 12), // Unused (Boots)
};

// 3 = two bit masks
// 7 = three bit masks
u32 gUpgradeMasks[] = {
    7 << 0,  // Quivers
    7 << 3,  // Bomb Bags
    7 << 6,  // Unused (Strength)
    7 << 9,  // Unused (Scale)
    3 << 12, // Wallets
    7 << 14, // Unused (Deku Seed Bullet Bags)
    7 << 17, // Unused (Deku Stick)
    7 << 20, // Unused (Deku Nut)
};

// 3 = two-bit masks
// 7 = three-bit masks
u32 gUpgradeNegMasks[] = {
    ~(7 << 0),  // UPG_QUIVER
    ~(7 << 3),  // UPG_BOMB_BAG
    ~(7 << 6),  // UPG_STRENGTH
    ~(7 << 9),  // UPG_SCALE
    ~(3 << 12), // UPG_WALLET
    ~(7 << 14), // UPG_BULLET_BAG
    ~(7 << 17), // UPG_STICKS
    ~(7 << 20), // UPG_NUTS
};

u8 gEquipShifts[] = {
    0,  // Sword
    4,  // Shield
    8,  // Unused (Tunic)
    12, // Unused (Boots)
};

u8 gUpgradeShifts[] = {
    0,  // UPG_QUIVER
    3,  // UPG_BOMB_BAG
    6,  // UPG_STRENGTH
    9,  // UPG_SCALE
    12, // UPG_WALLET
    14, // UPG_BULLET_BAG
    17, // UPG_STICKS
    20, // UPG_NUTS
};

u16 gUpgradeCapacities[][4] = {
    { 0, 30, 40, 50 },     // UPG_QUIVER
    { 0, 20, 30, 40 },     // UPG_BOMB_BAG
    { 0, 0, 0, 0 },        // UPG_STRENGTH
    { 0, 0, 0, 0 },        // UPG_SCALE
    { 99, 200, 500, 500 }, // UPG_WALLET
    { 0, 30, 40, 50 },     // UPG_BULLET_BAG
    { 0, 10, 20, 30 },     // UPG_STICKS
    { 0, 20, 30, 40 },     // UPG_NUTS
};

// eight-bit masks
u32 gGsFlagsMask[] = {
    0xFF << 0,
    0xFF << 8,
    0xFF << 16,
    0xFF << 24,
};

u32 gGsFlagsShift[] = {
    0,
    8,
    16,
    24,
};

TexturePtr gItemIcons[] = {
    icon_item_static_yar_Blob_000000,    // ITEM_OCARINA
    icon_item_static_yar_Blob_001000,    // ITEM_BOW
    icon_item_static_yar_Blob_002000,    // ITEM_ARROW_FIRE
    icon_item_static_yar_Blob_003000,    // ITEM_ARROW_ICE
    icon_item_static_yar_Blob_004000,    // ITEM_ARROW_LIGHT
    icon_item_static_yar_Blob_005000,    // ITEM_OCARINA_FAIRY
    icon_item_static_yar_Blob_006000,    // ITEM_BOMB
    icon_item_static_yar_Blob_007000,    // ITEM_BOMBCHU
    icon_item_static_yar_Blob_008000,    // ITEM_STICK
    icon_item_static_yar_Blob_009000,    // ITEM_NUT
    icon_item_static_yar_Blob_00A000,    // ITEM_MAGIC_BEANS
    icon_item_static_yar_Blob_00B000,    // ITEM_SLINGSHOT
    icon_item_static_yar_Blob_00C000,    // ITEM_POWDER_KEG
    icon_item_static_yar_Blob_00D000,    // ITEM_PICTO_BOX
    icon_item_static_yar_Blob_00E000,    // ITEM_LENS
    icon_item_static_yar_Blob_00F000,    // ITEM_HOOKSHOT
    icon_item_static_yar_Blob_010000,    // ITEM_SWORD_GREAT_FAIRY
    icon_item_static_yar_Blob_011000,    // ITEM_LONGSHOT
    icon_item_static_yar_Blob_012000,    // ITEM_BOTTLE
    icon_item_static_yar_Blob_013000,    // ITEM_POTION_RED
    icon_item_static_yar_Blob_014000,    // ITEM_POTION_GREEN
    icon_item_static_yar_Blob_015000,    // ITEM_POTION_BLUE
    icon_item_static_yar_Blob_016000,    // ITEM_FAIRY
    icon_item_static_yar_Blob_017000,    // ITEM_DEKU_PRINCESS
    icon_item_static_yar_Blob_018000,    // ITEM_MILK_BOTTLE
    icon_item_static_yar_Blob_019000,    // ITEM_MILK_HALF
    icon_item_static_yar_Blob_01A000,    // ITEM_FISH
    icon_item_static_yar_Blob_01B000,    // ITEM_BUG
    icon_item_static_yar_Blob_01C000,    // ITEM_BLUE_FIRE
    icon_item_static_yar_Blob_01D000,    // ITEM_POE
    icon_item_static_yar_Blob_01E000,    // ITEM_BIG_POE
    icon_item_static_yar_Blob_01F000,    // ITEM_SPRING_WATER
    icon_item_static_yar_Blob_020000,    // ITEM_HOT_SPRING_WATER
    icon_item_static_yar_Blob_021000,    // ITEM_ZORA_EGG
    icon_item_static_yar_Blob_022000,    // ITEM_GOLD_DUST
    icon_item_static_yar_Blob_023000,    // ITEM_MUSHROOM
    icon_item_static_yar_Blob_024000,    // ITEM_SEAHORSE
    icon_item_static_yar_Blob_025000,    // ITEM_CHATEAU
    icon_item_static_yar_Blob_026000,    // ITEM_HYLIAN_LOACH
    icon_item_static_yar_Blob_027000,    // ITEM_OBABA_DRINK
    icon_item_static_yar_Blob_028000,    // ITEM_MOON_TEAR
    icon_item_static_yar_Blob_029000,    // ITEM_DEED_LAND
    icon_item_static_yar_Blob_02A000,    // ITEM_DEED_SWAMP
    icon_item_static_yar_Blob_02B000,    // ITEM_DEED_MOUNTAIN
    icon_item_static_yar_Blob_02C000,    // ITEM_DEED_OCEAN
    icon_item_static_yar_Blob_02D000,    // ITEM_ROOM_KEY
    icon_item_static_yar_Blob_02E000,    // ITEM_LETTER_MAMA
    icon_item_static_yar_Blob_02F000,    // ITEM_LETTER_TO_KAFEI
    icon_item_static_yar_Blob_030000,    // ITEM_PENDANT_OF_MEMORIES
    icon_item_static_yar_Blob_031000,    // ITEM_TINGLE_MAP
    icon_item_static_yar_Blob_032000,    // ITEM_MASK_DEKU
    icon_item_static_yar_Blob_033000,    // ITEM_MASK_GORON
    icon_item_static_yar_Blob_034000,    // ITEM_MASK_ZORA
    icon_item_static_yar_Blob_035000,    // ITEM_MASK_FIERCE_DEITY
    icon_item_static_yar_Blob_036000,    // ITEM_MASK_TRUTH
    icon_item_static_yar_Blob_037000,    // ITEM_MASK_KAFEIS_MASK
    icon_item_static_yar_Blob_038000,    // ITEM_MASK_ALL_NIGHT
    icon_item_static_yar_Blob_039000,    // ITEM_MASK_BUNNY
    icon_item_static_yar_Blob_03A000,    // ITEM_MASK_KEATON
    icon_item_static_yar_Blob_03B000,    // ITEM_MASK_GARO
    icon_item_static_yar_Blob_03C000,    // ITEM_MASK_ROMANI
    icon_item_static_yar_Blob_03D000,    // ITEM_MASK_CIRCUS_LEADER
    icon_item_static_yar_Blob_03E000,    // ITEM_MASK_POSTMAN
    icon_item_static_yar_Blob_03F000,    // ITEM_MASK_COUPLE
    icon_item_static_yar_Blob_040000,    // ITEM_MASK_GREAT_FAIRY
    icon_item_static_yar_Blob_041000,    // ITEM_MASK_GIBDO
    icon_item_static_yar_Blob_042000,    // ITEM_MASK_DON_GERO
    icon_item_static_yar_Blob_043000,    // ITEM_MASK_KAMARO
    icon_item_static_yar_Blob_044000,    // ITEM_MASK_CAPTAIN
    icon_item_static_yar_Blob_045000,    // ITEM_MASK_STONE
    icon_item_static_yar_Blob_046000,    // ITEM_MASK_BREMEN
    icon_item_static_yar_Blob_047000,    // ITEM_MASK_BLAST
    icon_item_static_yar_Blob_048000,    // ITEM_MASK_SCENTS
    icon_item_static_yar_Blob_049000,    // ITEM_MASK_GIANT
    icon_item_static_yar_Blob_04A000,    // ITEM_BOW_ARROW_FIRE
    icon_item_static_yar_Blob_04B000,    // ITEM_BOW_ARROW_ICE
    icon_item_static_yar_Blob_04C000,    // ITEM_BOW_ARROW_LIGHT
    icon_item_static_yar_Blob_04D000,    // ITEM_SWORD_KOKIRI
    icon_item_static_yar_Blob_04E000,    // ITEM_SWORD_RAZOR
    icon_item_static_yar_Blob_04F000,    // ITEM_SWORD_GILDED
    icon_item_static_yar_Blob_050000,    // ITEM_SWORD_DEITY
    icon_item_static_yar_Blob_051000,    // ITEM_SHIELD_HERO
    icon_item_static_yar_Blob_052000,    // ITEM_SHIELD_MIRROR
    icon_item_static_yar_Blob_053000,    // ITEM_QUIVER_30
    icon_item_static_yar_Blob_054000,    // ITEM_QUIVER_40
    icon_item_static_yar_Blob_055000,    // ITEM_QUIVER_50
    icon_item_static_yar_Blob_056000,    // ITEM_BOMB_BAG_20
    icon_item_static_yar_Blob_057000,    // ITEM_BOMB_BAG_30
    icon_item_static_yar_Blob_058000,    // ITEM_BOMB_BAG_40
    icon_item_static_yar_Blob_059000,    // ITEM_WALLET_DEFAULT
    icon_item_static_yar_Blob_05A000,    // ITEM_WALLET_ADULT
    icon_item_static_yar_Blob_05B000,    // ITEM_WALLET_GIANT
    icon_item_static_yar_Blob_05C000,    // ITEM_FISHING_ROD
    icon_item_static_yar_Blob_05D000,    // ITEM_REMAINS_ODOLWA
    icon_item_static_yar_Blob_05E000,    // ITEM_REMAINS_GOHT
    icon_item_static_yar_Blob_05F000,    // ITEM_REMAINS_GYORG
    icon_item_static_yar_Blob_060000,    // ITEM_REMAINS_TWINMOLD
    icon_item_static_yar_Blob_062000,    // ITEM_SONG_SONATA
    icon_item_static_yar_Blob_062000,    // ITEM_SONG_LULLABY
    icon_item_static_yar_Blob_062000,    // ITEM_SONG_NOVA
    icon_item_static_yar_Blob_062000,    // ITEM_SONG_ELEGY
    icon_item_static_yar_Blob_062000,    // ITEM_SONG_OATH
    icon_item_static_yar_Blob_062000,    // ITEM_SONG_SARIA
    icon_item_static_yar_Blob_062000,    // ITEM_SONG_TIME
    icon_item_static_yar_Blob_062000,    // ITEM_SONG_HEALING
    icon_item_static_yar_Blob_062000,    // ITEM_SONG_EPONA
    icon_item_static_yar_Blob_062000,    // ITEM_SONG_SOARING
    icon_item_static_yar_Blob_062000,    // ITEM_SONG_STORMS
    icon_item_static_yar_Blob_062000,    // ITEM_SONG_SUN
    icon_item_static_yar_Blob_061000,    // ITEM_BOMBERS_NOTEBOOK
    icon_item_24_static_yar_Blob_000000, // ITEM_SKULL_TOKEN
    icon_item_24_static_yar_Blob_000900, // ITEM_HEART_CONTAINER
    icon_item_24_static_yar_Blob_001200, // ITEM_HEART_PIECE
    icon_item_static_yar_Blob_062000,    //
    icon_item_static_yar_Blob_062000,    //
    icon_item_static_yar_Blob_062000,    // ITEM_SONG_LULLABY_INTRO
    icon_item_24_static_yar_Blob_003600, // ITEM_KEY_BOSS
    icon_item_24_static_yar_Blob_004800, // ITEM_COMPASS
    icon_item_24_static_yar_Blob_003F00, // ITEM_DUNGEON_MAP
    icon_item_24_static_yar_Blob_005100, // ITEM_STRAY_FAIRIES
    icon_item_24_static_yar_Blob_005A00, // ITEM_KEY_SMALL
    icon_item_24_static_yar_Blob_006300, // ITEM_MAGIC_SMALL
    icon_item_24_static_yar_Blob_006C00, // ITEM_MAGIC_LARGE
    icon_item_static_yar_Blob_062180,    // ITEM_HEART_PIECE_2
    icon_item_static_yar_Blob_062A80,    // ITEM_INVALID_1
    icon_item_static_yar_Blob_063380,    // ITEM_INVALID_2
    gOcarinaCUpTex,                      // ITEM_INVALID_3
    gOcarinaCDownTex,                    // ITEM_INVALID_4
    gOcarinaCLeftTex,                    // ITEM_INVALID_5
    gOcarinaCRightTex,                   // ITEM_INVALID_6
    gOcarinaATex,                        // ITEM_INVALID_7
};

// Used to map item IDs to inventory slots
u8 gItemSlots[] = {
    SLOT_OCARINA,            // ITEM_OCARINA
    SLOT_BOW,                // ITEM_BOW
    SLOT_ARROW_FIRE,         // ITEM_ARROW_FIRE
    SLOT_ARROW_ICE,          // ITEM_ARROW_ICE
    SLOT_ARROW_LIGHT,        // ITEM_ARROW_LIGHT
    SLOT_TRADE_DEED,         // ITEM_OCARINA_FAIRY
    SLOT_BOMB,               // ITEM_BOMB
    SLOT_BOMBCHU,            // ITEM_BOMBCHU
    SLOT_STICK,              // ITEM_STICK
    SLOT_NUT,                // ITEM_NUT
    SLOT_MAGIC_BEANS,        // ITEM_MAGIC_BEANS
    SLOT_TRADE_KEY_MAMA,     // ITEM_SLINGSHOT
    SLOT_POWDER_KEG,         // ITEM_POWDER_KEG
    SLOT_PICTO_BOX,          // ITEM_PICTO_BOX
    SLOT_LENS,               // ITEM_LENS
    SLOT_HOOKSHOT,           // ITEM_HOOKSHOT
    SLOT_SWORD_GREAT_FAIRY,  // ITEM_SWORD_GREAT_FAIRY
    SLOT_BOTTLE_1,           // ITEM_LONGSHOT
    SLOT_BOTTLE_1,           // ITEM_BOTTLE
    SLOT_BOTTLE_1,           // ITEM_POTION_RED
    SLOT_BOTTLE_1,           // ITEM_POTION_GREEN
    SLOT_BOTTLE_1,           // ITEM_POTION_BLUE
    SLOT_BOTTLE_1,           // ITEM_FAIRY
    SLOT_BOTTLE_1,           // ITEM_DEKU_PRINCESS
    SLOT_BOTTLE_1,           // ITEM_MILK_BOTTLE
    SLOT_BOTTLE_1,           // ITEM_MILK_HALF
    SLOT_BOTTLE_1,           // ITEM_FISH
    SLOT_BOTTLE_1,           // ITEM_BUG
    SLOT_BOTTLE_1,           // ITEM_BLUE_FIRE
    SLOT_BOTTLE_1,           // ITEM_POE
    SLOT_BOTTLE_1,           // ITEM_BIG_POE
    SLOT_BOTTLE_1,           // ITEM_SPRING_WATER
    SLOT_BOTTLE_1,           // ITEM_HOT_SPRING_WATER
    SLOT_BOTTLE_1,           // ITEM_ZORA_EGG
    SLOT_BOTTLE_1,           // ITEM_GOLD_DUST
    SLOT_BOTTLE_1,           // ITEM_MUSHROOM
    SLOT_BOTTLE_1,           // ITEM_SEAHORSE
    SLOT_BOTTLE_1,           // ITEM_CHATEAU
    SLOT_BOTTLE_1,           // ITEM_HYLIAN_LOACH
    SLOT_BOTTLE_1,           // ITEM_OBABA_DRINK
    SLOT_TRADE_DEED,         // ITEM_MOON_TEAR
    SLOT_TRADE_DEED,         // ITEM_DEED_LAND
    SLOT_TRADE_DEED,         // ITEM_DEED_SWAMP
    SLOT_TRADE_DEED,         // ITEM_DEED_MOUNTAIN
    SLOT_TRADE_DEED,         // ITEM_DEED_OCEAN
    SLOT_TRADE_KEY_MAMA,     // ITEM_ROOM_KEY
    SLOT_TRADE_KEY_MAMA,     // ITEM_LETTER_MAMA
    SLOT_TRADE_COUPLE,       // ITEM_LETTER_TO_KAFEI
    SLOT_TRADE_COUPLE,       // ITEM_PENDANT_OF_MEMORIES
    SLOT_TRADE_COUPLE,       // ITEM_TINGLE_MAP
    SLOT_MASK_DEKU,          // ITEM_MASK_DEKU
    SLOT_MASK_GORON,         // ITEM_MASK_GORON
    SLOT_MASK_ZORA,          // ITEM_MASK_ZORA
    SLOT_MASK_FIERCE_DEITY,  // ITEM_MASK_FIERCE_DEITY
    SLOT_MASK_TRUTH,         // ITEM_MASK_TRUTH
    SLOT_MASK_KAFEIS_MASK,   // ITEM_MASK_KAFEIS_MASK
    SLOT_MASK_ALL_NIGHT,     // ITEM_MASK_ALL_NIGHT
    SLOT_MASK_BUNNY,         // ITEM_MASK_BUNNY
    SLOT_MASK_KEATON,        // ITEM_MASK_KEATON
    SLOT_MASK_GARO,          // ITEM_MASK_GARO
    SLOT_MASK_ROMANI,        // ITEM_MASK_ROMANI
    SLOT_MASK_CIRCUS_LEADER, // ITEM_MASK_CIRCUS_LEADER
    SLOT_MASK_POSTMAN,       // ITEM_MASK_POSTMAN
    SLOT_MASK_COUPLE,        // ITEM_MASK_COUPLE
    SLOT_MASK_GREAT_FAIRY,   // ITEM_MASK_GREAT_FAIRY
    SLOT_MASK_GIBDO,         // ITEM_MASK_GIBDO
    SLOT_MASK_DON_GERO,      // ITEM_MASK_DON_GERO
    SLOT_MASK_KAMARO,        // ITEM_MASK_KAMARO
    SLOT_MASK_CAPTAIN,       // ITEM_MASK_CAPTAIN
    SLOT_MASK_STONE,         // ITEM_MASK_STONE
    SLOT_MASK_BREMEN,        // ITEM_MASK_BREMEN
    SLOT_MASK_BLAST,         // ITEM_MASK_BLAST
    SLOT_MASK_SCENTS,        // ITEM_MASK_SCENTS
    SLOT_MASK_GIANT,         // ITEM_MASK_GIANT
    SLOT_BOW,                // ITEM_BOW_ARROW_FIRE
    SLOT_BOW,                // ITEM_BOW_ARROW_ICE
    SLOT_BOW,                // ITEM_BOW_ARROW_LIGHT
};

s16 gItemPrices[] = {
    0,   // ITEM_OCARINA
    0,   // ITEM_BOW
    0,   // ITEM_ARROW_FIRE
    0,   // ITEM_ARROW_ICE
    0,   // ITEM_ARROW_LIGHT
    0,   // ITEM_OCARINA_FAIRY
    0,   // ITEM_BOMB
    0,   // ITEM_BOMBCHU
    0,   // ITEM_STICK
    0,   // ITEM_NUT
    0,   // ITEM_MAGIC_BEANS
    0,   // ITEM_SLINGSHOT
    0,   // ITEM_POWDER_KEG
    0,   // ITEM_PICTO_BOX
    0,   // ITEM_LENS
    0,   // ITEM_HOOKSHOT
    0,   // ITEM_SWORD_GREAT_FAIRY
    0,   // ITEM_LONGSHOT
    0,   // ITEM_BOTTLE
    20,  // ITEM_POTION_RED
    20,  // ITEM_POTION_GREEN
    20,  // ITEM_POTION_BLUE
    20,  // ITEM_FAIRY
    0,   // ITEM_DEKU_PRINCESS
    20,  // ITEM_MILK_BOTTLE
    5,   // ITEM_MILK_HALF
    20,  // ITEM_FISH
    20,  // ITEM_BUG
    50,  // ITEM_BLUE_FIRE
    50,  // ITEM_POE
    200, // ITEM_BIG_POE
    20,  // ITEM_SPRING_WATER
    20,  // ITEM_HOT_SPRING_WATER
    20,  // ITEM_ZORA_EGG
    200, // ITEM_GOLD_DUST
    5,   // ITEM_MUSHROOM
    0,   // ITEM_SEAHORSE
    200, // ITEM_CHATEAU
    20,  // ITEM_HYLIAN_LOACH
    0,   // ITEM_OBABA_DRINK
    0,   // ITEM_MOON_TEAR
    0,   // ITEM_DEED_LAND
    0,   // ITEM_DEED_SWAMP
    0,   // ITEM_DEED_MOUNTAIN
    0,   // ITEM_DEED_OCEAN
    0,   // ITEM_ROOM_KEY
    0,   // ITEM_LETTER_MAMA
    0,   // ITEM_LETTER_KAFEI
    0,   // ITEM_PENDANT_OF_MEMORIES
    0,   // ITEM_TINGLE_MAP
};

// Used to map scene indexes to their region in Termina
u16 gSceneIdsPerRegion[REGION_MAX][27] = {
    // REGION_GREAT_BAY
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
        0xFFFF,
    },
    // REGION_ZORA_HALL
    {
        SCENE_33ZORACITY,
        SCENE_BANDROOM,
        0xFFFF,
    },
    // REGION_ROMANI_RANCH
    {
        SCENE_F01,
        SCENE_ROMANYMAE,
        SCENE_OMOYA,
        SCENE_F01C,
        SCENE_F01_B,
        SCENE_KOEPONARACE,
        0xFFFF,
    },
    // REGION_DEKU_PALACE
    {
        SCENE_22DEKUCITY,
        SCENE_DEKU_KING,
        SCENE_26SARUNOMORI,
        SCENE_DANPEI,
        0xFFFF,
    },
    // REGION_WOODFALL
    {
        SCENE_20SICHITAI,
        SCENE_20SICHITAI2,
        SCENE_MAP_SHOP,
        SCENE_WITCH_SHOP,
        SCENE_21MITURINMAE,
        SCENE_KINSTA1,
        0xFFFF,
    },
    // REGION_CLOCK_TOWN
    {
        SCENE_00KEIKOKU,   SCENE_TENMON_DAI, SCENE_13HUBUKINOMITI, SCENE_24KEMONOMITI, SCENE_SYATEKI_MORI,
        SCENE_IKANAMAE,    SCENE_TOWN,       SCENE_SYATEKI_MIZU,   SCENE_BOWLING,      SCENE_TAKARAYA,
        SCENE_YADOYA,      SCENE_SONCHONOIE, SCENE_MILK_BAR,       SCENE_ICHIBA,       SCENE_BOMYA,
        SCENE_AYASHIISHOP, SCENE_8ITEMSHOP,  SCENE_DOUJOU,         SCENE_POSTHOUSE,    SCENE_TAKARAKUJI,
        SCENE_BACKTOWN,    SCENE_CLOCKTOWER, SCENE_INSIDETOWER,    SCENE_OKUJOU,       SCENE_ALLEY,
        SCENE_DEKUTES,     0xFFFF,
    },
    // REGION_SNOWHEAD
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
        0xFFFF,
    },
    // REGION_IKANA_GRAVEYARD
    {
        SCENE_BOTI,
        SCENE_DANPEI2TEST,
        0xFFFF,
    },
    // REGION_IKANA_CANYON
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
        0xFFFF,
    },
    // REGION_GORON_VILLAGE
    {
        SCENE_11GORONNOSATO,
        SCENE_11GORONNOSATO2,
        SCENE_16GORON_HOUSE,
        SCENE_GORONSHOP,
        0xFFFF,
    },
    // REGION_STONE_TOWER
    {
        SCENE_F40,
        SCENE_F41,
        0xFFFF,
    },
};

s32 Inventory_GetBtnBItem(PlayState* play) {
    if (gSaveContext.buttonStatus[EQUIP_SLOT_B] == BTN_DISABLED) {
        return ITEM_NONE;
    } else if (gSaveContext.bButtonStatus == BTN_DISABLED) {
        return ITEM_NONE;
    } else if (CUR_FORM_EQUIP(EQUIP_SLOT_B) == ITEM_NONE) {
        if (play->interfaceCtx.unk_21C != 0) {
            if (play->interfaceCtx.bButtonDoAction != 0) {
                return play->interfaceCtx.bButtonDoAction;
            }
        }
        return ITEM_NONE;
    } else {
        return CUR_FORM_EQUIP(EQUIP_SLOT_B);
    }
}

/**
 * Only changes shield
 */
void Inventory_ChangeEquipment(s16 value) {
    SET_EQUIP_VALUE(EQUIP_TYPE_SHIELD, value);
}

/**
 * Only deletes shield, equipment argument unused and is a remnant of OoT
 */
u8 Inventory_DeleteEquipment(PlayState* play, s16 equipment) {
    Player* player = GET_PLAYER(play);

    if (GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SHIELD) != EQUIP_VALUE_SHIELD_NONE) {
        SET_EQUIP_VALUE(EQUIP_TYPE_SHIELD, EQUIP_VALUE_SHIELD_NONE);
        Player_SetEquipmentData(play, player);
        return true;
    }

    return false;
}

void Inventory_ChangeUpgrade(s16 upgrade, u32 value) {
    u32 upgrades = GET_SAVE_INVENTORY_UPGRADES;

    upgrades &= gUpgradeNegMasks[upgrade];
    upgrades |= value << gUpgradeShifts[upgrade];

    gSaveContext.save.saveInfo.inventory.upgrades = upgrades;
}

s32 Inventory_IsMapVisible(s16 sceneId) {
    s16 index = 0;

    /**
     * a single index of scenesVisible can only hold 32 bits. So for every 32 scenes in the scene enum,
     * increment to the next index of scenesVisible so that every scene gets a unique flag in scenesVisible,
     * 224 bits were allocated to this although there are only 112 scenes
     */
    if (sceneId >= 0x20) {
        if (sceneId < 0x40) {
            index = 1;
        } else if (sceneId < 0x60) {
            index = 2;
        } else if (sceneId < 0x80) {
            index = 3;
        } else if (sceneId < 0xA0) {
            index = 4;
        } else if (sceneId < 0xC0) {
            index = 5;
        } else if (sceneId < 0xE0) {
            index = 6;
        }
    }

    if (gSaveContext.save.saveInfo.scenesVisible[index] & gBitFlags[sceneId - (index << 5)]) {
        return true;
    }

    return false;
}

static u16 sSceneIdsPerTingleMap[TINGLE_MAP_MAX][12] = {
    {
        // TINGLE_MAP_CLOCK_TOWN
        SCENE_00KEIKOKU,
        SCENE_BOTI,
        SCENE_13HUBUKINOMITI,
        SCENE_24KEMONOMITI,
        SCENE_IKANAMAE,
        SCENE_TOWN,
        SCENE_ICHIBA,
        SCENE_BACKTOWN,
        SCENE_CLOCKTOWER,
        SCENE_ALLEY,
        0xFFFF,
    },
    {
        // TINGLE_MAP_WOODFALL
        SCENE_20SICHITAI,
        SCENE_20SICHITAI2,
        SCENE_21MITURINMAE,
        SCENE_22DEKUCITY,
        SCENE_DEKU_KING,
        SCENE_KINSTA1,
        0xFFFF,
    },
    {
        // TINGLE_MAP_SNOWHEAD
        SCENE_10YUKIYAMANOMURA,
        SCENE_10YUKIYAMANOMURA2,
        SCENE_11GORONNOSATO,
        SCENE_11GORONNOSATO2,
        SCENE_16GORON_HOUSE,
        SCENE_12HAKUGINMAE,
        SCENE_14YUKIDAMANOMITI,
        SCENE_GORONRACE,
        SCENE_17SETUGEN,
        SCENE_17SETUGEN2,
        0xFFFF,
    },
    {
        // TINGLE_MAP_ROMANI_RANCH
        SCENE_F01,
        SCENE_ROMANYMAE,
        SCENE_OMOYA,
        SCENE_F01C,
        SCENE_F01_B,
        SCENE_KOEPONARACE,
        0xFFFF,
    },
    {
        // TINGLE_MAP_GREAT_BAY
        SCENE_30GYOSON,
        SCENE_SINKAI,
        SCENE_31MISAKI,
        SCENE_TORIDE,
        SCENE_KAIZOKU,
        SCENE_33ZORACITY,
        SCENE_35TAKI,
        0xFFFF,
    },
    {
        // TINGLE_MAP_STONE_TOWER
        SCENE_F40,
        SCENE_F41,
        SCENE_CASTLE,
        SCENE_IKANA,
        SCENE_REDEAD,
        0xFFFF,
    },
};

/**
 * Removing clouds from the World Map is achieved by purchasing a tingle map
 */
void Inventory_SetWorldMapCloudVisibility(s16 tingleIndex) {
    s16 i = 0;
    s16 index = 0;
    u16(*tingleMapSceneIds)[] = &sSceneIdsPerTingleMap[tingleIndex];

    if ((tingleIndex >= 0) && (tingleIndex < TINGLE_MAP_MAX)) {
        while (true) {
            if ((*tingleMapSceneIds)[i] == 0xFFFF) {
                break;
            }

            /**
             * a single index of scenesVisible can only hold 32 bits. So for every 32 scenes in the scene enum,
             * increment to the next index of scenesVisible so that every scene gets a unique flag in scenesVisible,
             * 224 bits were allocated to this although there are only 112 scenes
             */
            if (((s16)(*tingleMapSceneIds)[i]) < 0x20) {
                index = 0;
            } else if (((s16)(*tingleMapSceneIds)[i]) < 0x40) {
                index = 1;
            } else if (((s16)(*tingleMapSceneIds)[i]) < 0x60) {
                index = 2;
            } else if (((s16)(*tingleMapSceneIds)[i]) < 0x80) {
                index = 3;
            } else if (((s16)(*tingleMapSceneIds)[i]) < 0xA0) {
                index = 4;
            } else if (((s16)(*tingleMapSceneIds)[i]) < 0xC0) {
                index = 5;
            } else if (((s16)(*tingleMapSceneIds)[i]) < 0xE0) {
                index = 6;
            }

            gSaveContext.save.saveInfo.scenesVisible[index] = gSaveContext.save.saveInfo.scenesVisible[index] |
                                                              gBitFlags[(s16)(*tingleMapSceneIds)[i] - (index << 5)];
            i++;
        }

        if (*tingleMapSceneIds == sSceneIdsPerTingleMap[TINGLE_MAP_CLOCK_TOWN]) {
            gSaveContext.save.saveInfo.worldMapCloudVisibility |= 3;
        } else if (*tingleMapSceneIds == sSceneIdsPerTingleMap[TINGLE_MAP_WOODFALL]) {
            gSaveContext.save.saveInfo.worldMapCloudVisibility |= 0x1C;
        } else if (*tingleMapSceneIds == sSceneIdsPerTingleMap[TINGLE_MAP_SNOWHEAD]) {
            gSaveContext.save.saveInfo.worldMapCloudVisibility |= 0xE0;
        } else if (*tingleMapSceneIds == sSceneIdsPerTingleMap[TINGLE_MAP_ROMANI_RANCH]) {
            gSaveContext.save.saveInfo.worldMapCloudVisibility |= 0x100;
        } else if (*tingleMapSceneIds == sSceneIdsPerTingleMap[TINGLE_MAP_GREAT_BAY]) {
            gSaveContext.save.saveInfo.worldMapCloudVisibility |= 0x1E00;
        } else if (*tingleMapSceneIds == sSceneIdsPerTingleMap[TINGLE_MAP_STONE_TOWER]) {
            gSaveContext.save.saveInfo.worldMapCloudVisibility |= 0x6000;
        }
    }

    R_MINIMAP_DISABLED = false;
}

/**
 * Also stores the players filename into dekuPlaygroundPlayerName
 */
void Inventory_SaveDekuPlaygroundHighScore(s16 timerId) {
    s16 i;

    gSaveContext.save.saveInfo.dekuPlaygroundHighScores[CURRENT_DAY - 1] = gSaveContext.timerCurTimes[timerId];

    for (i = 0; i < 8; i++) {
        gSaveContext.save.saveInfo.inventory.dekuPlaygroundPlayerName[CURRENT_DAY - 1][i] =
            gSaveContext.save.saveInfo.playerData.playerName[i];
    }
}

void Inventory_IncrementSkullTokenCount(s16 sceneIndex) {
    if (sceneIndex == SCENE_KINSTA1) {
        // Swamp Spider House (increment high bits of skullTokenCount)
        gSaveContext.save.saveInfo.skullTokenCount =
            ((u16)(((gSaveContext.save.saveInfo.skullTokenCount & 0xFFFF0000) >> 0x10) + 1) << 0x10) |
            (gSaveContext.save.saveInfo.skullTokenCount & 0xFFFF);
    } else {
        // Ocean Spider House (increment low bits of skullTokenCount)
        gSaveContext.save.saveInfo.skullTokenCount = (((u16)gSaveContext.save.saveInfo.skullTokenCount + 1) & 0xFFFF) |
                                                     (gSaveContext.save.saveInfo.skullTokenCount & 0xFFFF0000);
    }
}

s16 Inventory_GetSkullTokenCount(s16 sceneIndex) {
    if (sceneIndex == SCENE_KINSTA1) {
        // Swamp Spider House
        return (gSaveContext.save.saveInfo.skullTokenCount & 0xFFFF0000) >> 0x10;
    } else {
        // Ocean Spider House
        return gSaveContext.save.saveInfo.skullTokenCount & 0xFFFF;
    }
}

void Inventory_SaveLotteryCodeGuess(PlayState* play) {
    u16 lotteryCodeGuess;

    lotteryCodeGuess = ((play->msgCtx.unk12054[0] & 0xF) << 8);  // First Digit
    lotteryCodeGuess |= ((play->msgCtx.unk12054[1] & 0xF) << 4); // Second Digit
    lotteryCodeGuess |= (play->msgCtx.unk12054[2] & 0xF);        // Third Digit
    gSaveContext.save.saveInfo.lotteryCodeGuess =
        (gSaveContext.save.saveInfo.lotteryCodeGuess & 0xFFFF0000) | (lotteryCodeGuess & 0xFFFF);
}
