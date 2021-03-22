#ifndef _Z64ITEM_H_
#define _Z64ITEM_H_

// TODO fill out these enums

typedef enum {
    /* 0x78 */ ITEM_KEY_SMALL = 0x78,
    /* 0x79 */ ITEM_MAGIC_SMALL = 0x79,
    /* 0x7A */ ITEM_MAGIC_LARGE = 0x7A,
    /* 0x83 */ ITEM_HEART = 0x83,
    /* 0x84 */ ITEM_RUPEE_GREEN = 0x84,
    /* 0x85 */ ITEM_RUPEE_BLUE = 0x85,
    /* 0x86 */ ITEM_RUPEE_10 = 0x86,
    /* 0x87 */ ITEM_RUPEE_RED = 0x87,
    /* 0x88 */ ITEM_RUPEE_PURPLE = 0x88,
    /* 0x89 */ ITEM_RUPEE_100 = 0x89,
    /* 0x8A */ ITEM_RUPEE_ORANGE = 0x8A,
    /* 0x8F */ ITEM_BOMBS_5 = 0x8F,
    /* 0x90 */ ITEM_BOMBS_10 = 0x90,
    /* 0x91 */ ITEM_BOMBS_20 = 0x91,
    /* 0x92 */ ITEM_BOMBS_30 = 0x92,
    /* 0x93 */ ITEM_ARROWS_10 = 0x93,
    /* 0x94 */ ITEM_ARROWS_30 = 0x94,
    /* 0x95 */ ITEM_ARROWS_40 = 0x95,
    /* 0x96 */ ITEM_ARROWS_50 = 0x96
} ItemID;

typedef enum {
    /* 0x00 */ GI_NONE,
    /* 0x0C */ GI_HEART_PIECE = 0x0C,
    /* 0x0D */ GI_HEART_CONTAINER = 0x0D,
    /* 0x19 */ GI_STICKS_1 = 0x19,
    /* 0x28 */ GI_NUTS_1 = 0x28,
    /* 0x2A */ GI_NUTS_10 = 0x2A,
    /* 0x32 */ GI_SHIELD_HERO = 0x32,
    /* 0x3C */ GI_KEY_SMALL = 0x3C,
    /* 0x3E */ GI_MAP = 0x3E,
    /* 0x3F */ GI_COMPASS = 0x3F
} GetItemID;

typedef enum {
    /* 0x0A */ GID_COMPASS = 0x0A,
    /* 0x1B */ GID_DUNGEON_MAP = 0x1B,
    /* 0x27 */ GID_SHIELD_HERO = 0x27
} GetItemDrawID;

#endif
