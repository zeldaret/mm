#ifndef Z_EN_BJI_01_H
#define Z_EN_BJI_01_H

#include <global.h>
#include "../ovl_Obj_Moon_Stone/z_obj_moon_stone.h"

struct EnBji01;

typedef void (*EnBji01ActionFunc)(struct EnBji01*, GlobalContext*);

typedef struct EnBji01 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnBji01ActionFunc actionFunc;
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ Vec3s jointTable[0x10]; 
    /* 0x238 */ Vec3s morphTable[0x10];
    /* 0x298 */ s32 unk_298; /* assumed s32 */
    /* 0x29C */ s16 unk_29C;
    /* 0x29E */ s16 unk_29E;
    /* 0x2A0 */ s16 unk_2A0;
    /* 0x2A2 */ char unk_2A2[0xA];
    /* 0x2AC */ s32 unk_2AC; /* assumed s32 */
    /* 0x2B0 */ ObjMoonStone* moonsTear;

} EnBji01; // size = 0x2B4

extern const ActorInit En_Bji_01_InitVars;

#endif // Z_EN_BJI_01_H
