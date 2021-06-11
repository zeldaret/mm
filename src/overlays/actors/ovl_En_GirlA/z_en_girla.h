#ifndef Z_EN_GIRLA_H
#define Z_EN_GIRLA_H

#include <global.h>

struct EnGirlA;

typedef void (*EnGirlAActionFunc)(struct EnGirlA*, GlobalContext*);
typedef void (*EnGirlADrawFunc)(struct Actor*, GlobalContext*, s32);
typedef s32 (*EnGirlAUnkFunc)(GlobalContext*, struct EnGirlA*);
typedef void (*EnGirlAUnkFunc2)(GlobalContext*, struct EnGirlA*);

typedef struct ShopItemEntry {
    /* 0x00 */ s16 objectId;
    /* 0x02 */ s16 getItemDrawId;
    /* 0x04 */ EnGirlADrawFunc drawFunc;
    /* 0x08 */ s16 params;
    /* 0x0A */ u16 descriptionTextId;
    /* 0x0C */ u16 choiceTextId;
    /* 0x10 */ s32 getItemId;
    /* 0x14 */ EnGirlAUnkFunc unk14Func;
    /* 0x18 */ EnGirlAUnkFunc2 unk18Func;
    /* 0x1C */ EnGirlAUnkFunc2 unk1CFunc;
} ShopItemEntry; // size = 0x20

typedef struct EnGirlA {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk144[0x44];
    /* 0x188 */ EnGirlAActionFunc actionFunc;
    /* 0x18C */ s8 objIndex;
    /* 0x190 */ EnGirlAActionFunc mainActionFunc;
    /* 0x194 */ s32 unk194;
    /* 0x198 */ u16 choiceTextId;
    /* 0x19C */ s32 getItemId;
    /* 0x1A0 */ s16 unk1A0;
    /* 0x1A4 */ EnGirlAUnkFunc2 unk1A4Func;
    /* 0x1A8 */ EnGirlAUnkFunc2 unk1A8Func;
    /* 0x1AC */ s16 unk1AC;
    /* 0x1AE */ s16 unk1AE;
    /* 0x1B0 */ s16 rotY;
    /* 0x1B4 */ EnGirlAUnkFunc unk1B4Func;
    /* 0x1B8 */ EnGirlAUnkFunc2 unk1B8Func;
    /* 0x1BC */ EnGirlAUnkFunc2 unk1BCFunc;
    /* 0x1C0 */ s16 unk1C0;
    /* 0x1C2 */ s16 itemParams;
    /* 0x1C4 */ s16 getItemDrawId;
    /* 0x1C8 */ EnGirlADrawFunc drawFunc;
} EnGirlA; // size = 0x1CC

extern const ActorInit En_GirlA_InitVars;

#endif // Z_EN_GIRLA_H
