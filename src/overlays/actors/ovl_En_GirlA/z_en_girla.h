#ifndef Z_EN_GIRLA_H
#define Z_EN_GIRLA_H

#include <global.h>

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
    /* 0x144 */ char unk144[0x44];
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
    /* 0 */ CANBUY_RESULT_SUCCESS_FANFARE,
    /* 1 */ CANBUY_RESULT_SUCCESS,
    /* 2 */ CANBUY_RESULT_NO_ROOM,
    /* 3 */ CANBUY_RESULT_NEED_EMPTY_BOTTLE,
    /* 4 */ CANBUY_RESULT_NEED_RUPEES,
    /* 5 */ CANBUY_RESULT_CANT_GET_NOW,
    /* 6 */ CANBUY_RESULT_NO_ROOM_2,
    /* 7 */ CANBUY_RESULT_NO_ROOM_3,
    /* 8 */ CANBUY_RESULT_ALREADY_HAVE,
    /* 9 */ CANBUY_RESULT_HAVE_BETTER
} EnGirlACanBuyResult;

extern const ActorInit En_GirlA_InitVars;

#endif // Z_EN_GIRLA_H
