#ifndef Z_DM_HINA_H
#define Z_DM_HINA_H

#include "global.h"

struct DmHina;

typedef void (*DmHinaActionFunc)(struct DmHina*, PlayState*);

typedef struct DmHina {
    /* 0x000 */ Actor actor;
    /* 0x144 */ DmHinaActionFunc actionFunc;
    /* 0x148 */ f32 unk148;
    /* 0x14C */ f32 unk14C;
    /* 0x150 */ f32 unk150;
    /* 0x154 */ f32 unk154;
    /* 0x158 */ f32 unk_158;
    /* 0x15C */ f32 unk_15C;
    /* 0x160 */ f32 unk160;
    /* 0x164 */ f32 unk164;
    /* 0x168 */ f32 unk168;
    /* 0x16C */ f32 unk16C;
    /* 0x170 */ f32 unk170;
    /* 0x174 */ f32 unk174;
    /* 0x178 */ char pad178[2];
    /* 0x17A */ s16 unk17A;
    /* 0x17C */ s16 unk17C;
    /* 0x17E */ u8 unk17E;
    /* 0x17F */ u8 unk17F;
    /* 0x180 */ s8 unk180;
} DmHina; // size = 0x184

#endif // Z_DM_HINA_H
