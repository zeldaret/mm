#ifndef Z_ITEM_B_HEART_H
#define Z_ITEM_B_HEART_H

#include <global.h>

struct ItemBHeart;

typedef struct ItemBHeart {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x20];
    /* 0x164 */ f32 unk_164;
    /* 0x168 */ f32 unk_168;
} ItemBHeart; // size = 0x16C

extern const ActorInit Item_B_Heart_InitVars;

#endif // Z_ITEM_B_HEART_H
