#ifndef _Z64ITEM_H_
#define _Z64ITEM_H_

#define DROP_TABLE_SIZE 16
#define DROP_TABLE_NUMBER 17

// TODO fill out these enums

typedef enum {
    /* 0x1 */ EQUIP_SHIELD = 0x1
} EquipmentType;

typedef enum {
    /* 0x0 */ UPG_QUIVER,
    /* 0x1 */ UPG_BOMB_BAG,
    /* 0x4 */ UPG_WALLET = 0x4,
    /* 0x6 */ UPG_STICK = 0x6,
    /* 0x7 */ UPG_NUTS
} UpgradeType;

typedef enum {
    /* 0x01 */ ITEM_BOW = 0x01,
    /* 0x06 */ ITEM_BOMB = 0x06,
    /* 0x07 */ ITEM_BOMBCHU,
    /* 0x08 */ ITEM_STICK,
    /* 0x09 */ ITEM_NUT,
    /* 0x10 */ ITEM_SWORD_GREAT_FAIRY = 0x10,
    /* 0x12 */ ITEM_BOTTLE = 0x12,
    /* 0x13 */ ITEM_POTION_RED,
    /* 0x14 */ ITEM_POTION_GREEN,
    /* 0x15 */ ITEM_POTION_BLUE,
    /* 0x16 */ ITEM_FAIRY,
    /* 0x38 */ ITEM_MASK_ALL_NIGHT = 0x38,
    /* 0x3B */ ITEM_MASK_GARO = 0x3B,
    /* 0x4D */ ITEM_SWORD_KOKIRI = 0x4D,
    /* 0x4E */ ITEM_SWORD_RAZOR,
    /* 0x4F */ ITEM_SWORD_GILDED,
    /* 0x51 */ ITEM_SHIELD_HERO = 0x51,
    /* 0x52 */ ITEM_SHIELD_MIRROR,
    /* 0x56 */ ITEM_BOMB_BAG_20 = 0x56,
    /* 0x57 */ ITEM_BOMB_BAG_30,
    /* 0x58 */ ITEM_BOMB_BAG_40,
    /* 0x78 */ ITEM_KEY_SMALL = 0x78,
    /* 0x79 */ ITEM_MAGIC_SMALL,
    /* 0x7A */ ITEM_MAGIC_LARGE,
    /* 0x83 */ ITEM_HEART = 0x83,
    /* 0x84 */ ITEM_RUPEE_GREEN,
    /* 0x85 */ ITEM_RUPEE_BLUE,
    /* 0x86 */ ITEM_RUPEE_10,
    /* 0x87 */ ITEM_RUPEE_RED,
    /* 0x88 */ ITEM_RUPEE_PURPLE,
    /* 0x89 */ ITEM_RUPEE_100,
    /* 0x8A */ ITEM_RUPEE_ORANGE,
    /* 0x8D */ ITEM_NUTS_5 = 0x8D,
    /* 0x8E */ ITEM_NUTS_10,
    /* 0x8F */ ITEM_BOMBS_5,
    /* 0x90 */ ITEM_BOMBS_10,
    /* 0x91 */ ITEM_BOMBS_20,
    /* 0x92 */ ITEM_BOMBS_30,
    /* 0x93 */ ITEM_ARROWS_10,
    /* 0x94 */ ITEM_ARROWS_30,
    /* 0x95 */ ITEM_ARROWS_40,
    /* 0x96 */ ITEM_ARROWS_50,
    /* 0x98 */ ITEM_BOMBCHUS_10 = 0x98,
    /* 0xFF */ ITEM_NONE = 0xFF
} ItemID;

typedef enum {
    /* 0x00 */ GI_NONE,
    /* 0x0C */ GI_HEART_PIECE = 0x0C,
    /* 0x0D */ GI_HEART_CONTAINER,
    /* 0x16 */ GI_BOMBS_10 = 0x16,
    /* 0x19 */ GI_STICKS_1 = 0x19,
    /* 0x1A */ GI_BOMBCHUS_10,
    /* 0x1B */ GI_BOMB_BAG_20,
    /* 0x1C */ GI_BOMB_BAG_30,
    /* 0x1D */ GI_BOMB_BAG_40,
    /* 0x1E */ GI_ARROWS_SMALL,
    /* 0x1F */ GI_ARROWS_MEDIUM,
    /* 0x20 */ GI_ARROWS_LARGE,
    /* 0x28 */ GI_NUTS_1 = 0x28,
    /* 0x2A */ GI_NUTS_10 = 0x2A,
    /* 0x32 */ GI_SHIELD_HERO = 0x32,
    /* 0x33 */ GI_SHIELD_MIRROR,
    /* 0x3C */ GI_KEY_SMALL = 0x3C,
    /* 0x3E */ GI_MAP = 0x3E,
    /* 0x3F */ GI_COMPASS,
    /* 0x5B */ GI_POTION_RED = 0x5B,
    /* 0x5C */ GI_POTION_GREEN,
    /* 0x5D */ GI_POTION_BLUE,
    /* 0x5E */ GI_FAIRY,
    /* 0x7E */ GI_MASK_ALL_NIGHT = 0x7E,
    /* 0x9B */ GI_SWORD_GREAT_FAIRY = 0x9B,
    /* 0x9C */ GI_SWORD_KOKIRI,
    /* 0x9D */ GI_SWORD_RAZOR,
    /* 0x9E */ GI_SWORD_GILDED,
    /* 0x9F */ GI_SHIELD_HERO_2, // Code that treats this as hero's shield is unused, so take with a grain of salt
    /* 0xA9 */ GI_BOTTLE = 0xA9
} GetItemID;

typedef enum {
    /* 0x00 */ GID_BOTTLE,
    /* 0x0A */ GID_COMPASS = 0x0A,
    /* 0x10 */ GID_MASK_ALL_NIGHT = 0x10,
    /* 0x11 */ GID_NUTS,
    /* 0x17 */ GID_BOMB_BAG_20 = 0x17,
    /* 0x18 */ GID_BOMB_BAG_30,
    /* 0x19 */ GID_BOMB_BAG_40,
    /* 0x1A */ GID_STICK = 0x1A,
    /* 0x1B */ GID_DUNGEON_MAP,
    /* 0x1E */ GID_BOMB = 0x1E,
    /* 0x23 */ GID_ARROWS_SMALL = 0x23,
    /* 0x24 */ GID_ARROWS_MEDIUM,
    /* 0x25 */ GID_ARROWS_LARGE,
    /* 0x26 */ GID_BOMBCHU,
    /* 0x27 */ GID_SHIELD_HERO,
    /* 0x30 */ GID_POTION_GREEN = 0x30,
    /* 0x31 */ GID_POTION_RED,
    /* 0x32 */ GID_POTION_BLUE,
    /* 0x33 */ GID_SHIELD_MIRROR,
    /* 0x3B */ GID_FAIRY = 0x3B,
    /* 0x55 */ GID_SWORD_KOKIRI = 0x55,
    /* 0x66 */ GID_SWORD_RAZOR = 0x66,
    /* 0x67 */ GID_SWORD_GILDED,
    /* 0x68 */ GID_SWORD_GREAT_FAIRY
} GetItemDrawID;

#endif
