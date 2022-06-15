#ifndef Z_EN_GIRLA_H
#define Z_EN_GIRLA_H

#include "global.h"

struct EnGirlA;

typedef void (*EnGirlAActionFunc)(struct EnGirlA*, GlobalContext*);
typedef void (*EnGirlADrawFunc)(struct Actor*, GlobalContext*, s32);
typedef s32 (*EnGirlACanBuyFunc)(GlobalContext*, struct EnGirlA*);
typedef void (*EnGirlAShopActionFunc)(GlobalContext*, struct EnGirlA*); // Buying/Restocking

typedef struct ShopItemEntry {
    /* 0x00 */ s16 objectId;
    /* 0x02 */ s16 getItemDrawId;
    /* 0x04 */ EnGirlADrawFunc drawFunc;
    /* 0x08 */ s16 params;
    /* 0x0A */ u16 descriptionTextId;
    /* 0x0C */ u16 choiceTextId;
    /* 0x10 */ s32 getItemId;
    /* 0x14 */ EnGirlACanBuyFunc canBuyFunc;
    /* 0x18 */ EnGirlAShopActionFunc buyFunc;
    /* 0x1C */ EnGirlAShopActionFunc buyFanfareFunc;
} ShopItemEntry; // size = 0x20

typedef struct EnGirlA {
    /* 0x000 */ Actor actor;
    /* 0x144 */ UNK_TYPE1 unk144[0x44];
    /* 0x188 */ EnGirlAActionFunc actionFunc;
    /* 0x18C */ s8 objIndex;
    /* 0x190 */ EnGirlAActionFunc mainActionFunc;
    /* 0x194 */ s32 isInitialized;
    /* 0x198 */ u16 choiceTextId;
    /* 0x19C */ s32 getItemId;
    /* 0x1A0 */ s16 isOutOfStock;
    /* 0x1A4 */ EnGirlAShopActionFunc boughtFunc;
    /* 0x1A8 */ EnGirlAShopActionFunc restockFunc;
    /* 0x1AC */ s16 isSelected;
    /* 0x1AE */ s16 initialRotY;
    /* 0x1B0 */ s16 rotY;
    /* 0x1B4 */ EnGirlACanBuyFunc canBuyFunc;
    /* 0x1B8 */ EnGirlAShopActionFunc buyFunc;
    /* 0x1BC */ EnGirlAShopActionFunc buyFanfareFunc;
    /* 0x1C0 */ s16 unk1C0;
    /* 0x1C2 */ s16 itemParams;
    /* 0x1C4 */ s16 getItemDrawId;
    /* 0x1C8 */ EnGirlADrawFunc drawFunc;
} EnGirlA; // size = 0x1CC

typedef enum {
    /* 0 */ CANBUY_RESULT_SUCCESS_1,
    /* 1 */ CANBUY_RESULT_SUCCESS_2,
    /* 2 */ CANBUY_RESULT_NO_ROOM,
    /* 3 */ CANBUY_RESULT_NEED_EMPTY_BOTTLE,
    /* 4 */ CANBUY_RESULT_NEED_RUPEES,
    /* 5 */ CANBUY_RESULT_CANNOT_GET_NOW,
    /* 6 */ CANBUY_RESULT_CANNOT_GET_NOW_2,
    /* 7 */ CANBUY_RESULT_NO_ROOM_2,
    /* 8 */ CANBUY_RESULT_ALREADY_HAVE,
    /* 9 */ CANBUY_RESULT_HAVE_BETTER
} EnGirlACanBuyResult;

typedef enum {
	/* 00 */ SI_POTION_RED_1,
	/* 01 */ SI_POTION_GREEN_1,
	/* 02 */ SI_POTION_BLUE,
	/* 03 */ SI_FAIRY_1,
	/* 04 */ SI_ARROWS_LARGE_1,
	/* 05 */ SI_POTION_GREEN_2,
	/* 06 */ SI_SHIELD_HERO_1,
	/* 07 */ SI_STICK_1,
	/* 08 */ SI_ARROWS_MEDIUM_1,
	/* 09 */ SI_NUTS_1,
	/* 10 */ SI_POTION_RED_2,
	/* 11 */ SI_FAIRY_2,
	/* 12 */ SI_ARROWS_MEDIUM_2,
	/* 13 */ SI_ARROWS_LARGE_2,
	/* 14 */ SI_POTION_GREEN_3,
	/* 15 */ SI_NUTS_2,
	/* 16 */ SI_STICK_2,
	/* 17 */ SI_SHIELD_HERO_2,
	/* 18 */ SI_POTION_RED_3,
	/* 19 */ SI_MASK_ALL_NIGHT,
	/* 20 */ SI_BOMB_BAG_20_1,
	/* 21 */ SI_BOMB_BAG_30_1,
	/* 22 */ SI_BOMB_BAG_40,
	/* 23 */ SI_BOMB_BAG_20_2,
	/* 24 */ SI_BOMB_BAG_30_2,
	/* 25 */ SI_BOMBCHU,
	/* 26 */ SI_BOMB_1,
	/* 27 */ SI_SHIELD_HERO_3,
	/* 28 */ SI_ARROWS_SMALL_1,
	/* 29 */ SI_POTION_RED_4,
	/* 30 */ SI_BOMB_2,
	/* 31 */ SI_ARROWS_SMALL_2,
	/* 32 */ SI_POTION_RED_5,
	/* 33 */ SI_BOMB_3,
	/* 34 */ SI_ARROWS_SMALL_3,
	/* 35 */ SI_POTION_RED_6,
	/* 36 */ SI_BOTTLE,
	/* 37 */ SI_SWORD_GREAT_FAIRY,
	/* 38 */ SI_SWORD_KOKIRI,
	/* 39 */ SI_SWORD_RAZOR,
	/* 40 */ SI_SWORD_GILDED,
	/* 41 */ SI_SHIELD_HERO_4,
	/* 42 */ SI_SHIELD_MIRROR,
    /* 43 */ SI_MAX
} EnGirlAShopItemId;

extern const ActorInit En_GirlA_InitVars;

/* 
* Shopkeeper Common Defines 
*/
#define CURSOR_INVALID 0xFF
#define COL_CHAN_MIX(c1, c2, m) (c1 - (s32)(c2 * m)) & 0xFF

typedef struct {
    /* 0x00 */ Color_RGBAu32 stickColor;
    /* 0x10 */ f32 stickTexX;
    /* 0x14 */ f32 stickTexY;
    /* 0x18 */ Color_RGBAu32 arrowColor;
    /* 0x28 */ f32 arrowTexX;
    /* 0x2C */ f32 arrowTexY;
    /* 0x30 */ f32 texZ; // Used for both stickTexZ and arrowTexZ
    /* 0x34 */ u32 isEnabled;
} StickDirectionPrompt; // size = 0x38

typedef struct ShopItem {
    /* 0x00 */ s16 shopItemId;
    /* 0x02 */ Vec3s spawnPos;
} ShopItem; // size = 0x8;

#endif // Z_EN_GIRLA_H
