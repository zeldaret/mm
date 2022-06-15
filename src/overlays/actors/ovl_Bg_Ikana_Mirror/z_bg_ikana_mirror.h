#ifndef Z_BG_IKANA_MIRROR_H
#define Z_BG_IKANA_MIRROR_H

#include "global.h"

struct BgIkanaMirror;

typedef void (*BgIkanaMirrorActionFunc)(struct BgIkanaMirror*, GlobalContext*);

// typedef struct BgIkanaMirror {
//     /* 0x0000 */ Actor actor;
//     /* 0x0144 */ char unk_144[0x474];
//     /* 0x05B8 */ BgIkanaMirrorActionFunc actionFunc;
//     /* 0x05BC */ char unk_5BC[0x10];
// } BgIkanaMirror; // size = 0x5CC

typedef struct BgIkanaMirror {
    /* 0x000 */ Actor actor;
    /* 0x144 */ s32 unk144;                         /* inferred */
    /* 0x148 */ char pad148[0x14];                  /* maybe part of unk144[6]? */
    /* 0x15C */ ColliderTris unk15C;                /* inferred */
    /* 0x17C */ ColliderTrisElement unk17C;         /* inferred */
    /* 0x1D8 */ char pad1D8[0x2E0];                 /* maybe part of unk17C[9]? */
    /* 0x4B8 */ ColliderQuad unk4B8;                /* inferred */
    /* 0x538 */ char pad538[0x80];
    /* 0x5B8 */ BgIkanaMirrorActionFunc actionFunc;
    /* 0x5BC */ AnimatedMaterial *unk5BC;           /* inferred */
    /* 0x5C0 */ AnimatedMaterial *unk5C0;           /* inferred */
    /* 0x5C4 */ s16 unk5C4;                         /* inferred */
    /* 0x5C6 */ s8 unk5C6;                          /* inferred */
    /* 0x5C7 */ s8 unk5C7;                          /* inferred */
    /* 0x5C8 */ s8 unk5C8;                          /* inferred */
    /* 0x5C9 */ char pad5C9[3];                     /* maybe part of unk5C8[4]? */
} BgIkanaMirror;                                    /* size = 0x5CC */


extern const ActorInit Bg_Ikana_Mirror_InitVars;

#endif // Z_BG_IKANA_MIRROR_H
