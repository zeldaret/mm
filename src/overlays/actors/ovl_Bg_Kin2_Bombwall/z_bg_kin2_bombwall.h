#ifndef Z_BG_KIN2_BOMBWALL_H
#define Z_BG_KIN2_BOMBWALL_H

#include "global.h"

struct BgKin2Bombwall;

typedef void (*BgKin2BombwallActionFunc)(struct BgKin2Bombwall*, GlobalContext*);

typedef struct BgKin2Bombwall {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ s32 unk_144[0x18];
    /* 0x15C */ ColliderCylinder unk15C;  
    /* 0x01A8 */ BgKin2BombwallActionFunc actionFunc;
    /* 0x01AC */ char unk_1AC[0x4];
} BgKin2Bombwall; // size = 0x1B0

//typedef struct BgKin2Bombwall {
//    /* 0x000 */ Actor actor;
//    /* 0x144 */ char pad144[0x18];
//    /* 0x15C */ ColliderCylinder unk15C;            /* inferred */
//    /* 0x1A8 */ void (*actionFunc)(BgKin2Bombwall *, GlobalContext *);
//    /* 0x1AC */ char pad1AC[4];
//} BgKin2Bombwall;   

//from mips2c-ing destroy
//typedef struct BgKin2Bombwall {
//    /* 0x000 */ Actor actor;
//    /* 0x144 */ s32 unk144;                         /* inferred */
//    /* 0x148 */ char pad148[0x14];                  /* maybe part of unk144[6]? */
//    /* 0x15C */ ColliderCylinder unk15C;
//    /* 0x1A8 */ void (*actionFunc)(BgKin2Bombwall *, GlobalContext *);
//    /* 0x1AC */ char pad1AC[4];
//} BgKin2Bombwall;                                   /* size = 0x1B0 */

extern const ActorInit Bg_Kin2_Bombwall_InitVars;

#endif // Z_BG_KIN2_BOMBWALL_H
