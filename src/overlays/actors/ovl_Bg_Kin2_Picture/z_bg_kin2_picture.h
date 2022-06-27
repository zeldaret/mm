#ifndef Z_BG_KIN2_PICTURE_H
#define Z_BG_KIN2_PICTURE_H

#include "global.h"

struct BgKin2Picture;

typedef void (*BgKin2PictureActionFunc)(struct BgKin2Picture*, PlayState*);

typedef struct BgKin2Picture {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ColliderTris colliderTris;                /* inferred */
    /* 0x17C */ ColliderTrisElement unk17C;         /* inferred */
    /* 0x1D8 */ char pad1D8[0x5C];
    /* 0x234 */ BgKin2PictureActionFunc actionFunc;
    /* 0x238 */ s16 unk238;                         /* inferred */
    /* 0x23A */ s8 unk23A;                          /* inferred */
    /* 0x23B */ s8 unk23B;                          /* inferred */
    /* 0x23C */ s16 unk23C;                         /* inferred */
    /* 0x23E */ s16 unk23E;                         /* inferred */
    /* 0x240 */ s8 unk240;                          /* inferred */
    /* 0x241 */ s8 unk241;                          /* inferred */
    /* 0x242 */ s8 unk242;                          /* inferred */
    /* 0x243 */ char pad243[1];
} BgKin2Picture;                                    /* size = 0x244 */

// typedef struct BgKin2Picture {
//     /* 0x0000 */ Actor actor;
//     /* 0x0144 */ char unk_144[0xF0];
//     /* 0x0234 */ BgKin2PictureActionFunc actionFunc;
//     /* 0x0238 */ char unk_238[0xC];
// } BgKin2Picture; // size = 0x244

// extern const ActorInit Bg_Kin2_Picture_InitVars;

#endif // Z_BG_KIN2_PICTURE_H
