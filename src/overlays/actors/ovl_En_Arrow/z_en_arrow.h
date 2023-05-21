#ifndef Z_EN_ARROW_H
#define Z_EN_ARROW_H

#include "global.h"

struct EnArrow;

typedef void (*EnArrowActionFunc)(struct EnArrow*, PlayState*);

enum {
    /* 0 */ ENARROW_0, // Lit arrow
    /* 1 */ ENARROW_1, // Horse arrow
    /* 2 */ ENARROW_2, // Normal arrow
    /* 3 */ ENARROW_3, // Fire arrow
    /* 4 */ ENARROW_4, // Ice arrow
    /* 5 */ ENARROW_5, // Light arrow
    /* 6 */ ENARROW_6, // ?
    /* 7 */ ENARROW_7, // Deku bubble
    /* 8 */ ENARROW_8, // Deku Nut
};

typedef struct {
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[5];
} EnArrowArrow; // size = 0x1A8

typedef struct {
    /* 0x144 */ f32 unk_144;
    /* 0x148 */ u8 unk_148;
    /* 0x149 */ s8 unk_149;
    /* 0x14A */ s16 unk_14A;
    /* 0x14C */ s16 unk_14C;
} EnArrowBubble; // size = 0x150

typedef struct EnArrow {
    /* 0x000 */ Actor actor;
    union {
        EnArrowArrow arrow;
        EnArrowBubble bubble;
    };
    /* 0x1A8 */ ColliderQuad collider;
    /* 0x228 */ Vec3f unk_228;
    /* 0x234 */ Vec3f unk_234;
    /* 0x240 */ s32 unk_240;
    /* 0x244 */ WeaponInfo unk_244;
    /* 0x260 */ u8 unk_260; // timer in OoT
    /* 0x261 */ u8 unk_261; // hitFlags in OoT
    /* 0x262 */ u8 unk_262;
    /* 0x263 */ u8 unk_263;
    /* 0x264 */ Actor* unk_264;
    /* 0x268 */ Vec3f unk_268;
    /* 0x274 */ EnArrowActionFunc actionFunc;
} EnArrow; // size = 0x278

#endif // Z_EN_ARROW_H
