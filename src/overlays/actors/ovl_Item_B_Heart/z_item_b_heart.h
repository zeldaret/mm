#ifndef Z_ITEM_B_HEART_H
#define Z_ITEM_B_HEART_H

#include "global.h"

struct ItemBHeart;

typedef struct ItemBHeart {
    /* 0x000 */ Actor actor;
    /* 0x144 */ UNK_TYPE1 unk_144[0x24];
    /* 0x168 */ f32 unk_168;
} ItemBHeart; // size = 0x16C

#endif // Z_ITEM_B_HEART_H
