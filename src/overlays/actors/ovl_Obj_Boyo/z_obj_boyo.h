#ifndef Z_OBJ_BOYO_H
#define Z_OBJ_BOYO_H

#include "global.h"
#include "../ovl_En_Torch2/z_en_torch2.h"

typedef struct ObjBoyo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;          /* inferred */
    /* 0x190 */ AnimatedMaterial* animatedMaterial; /* inferred */
    /* 0x194 */ u16 unk194;
    /* 0x196 */ u16 unk196;
    /* 0x198 */ f32 unk198;        /* inferred */
    /* 0x19C */ f32 unk19C;        /* inferred */
    /* 0x1A0 */ f32 unk1A0;        /* inferred */
    /* 0x1A4 */ s16 unk1A4;        /* inferred */
    /* 0x1A6 */ s16 unk1A6;        /* inferred */
    /* 0x1A8 */ s16 unk1A8;        /* inferred */
    /* 0x1AA */ s16 unk1AA;        /* inferred */
    /* 0x1AC */ s16 unk1AC;        /* inferred */
    /* 0x1AE */ char pad1AE[0x42]; /* maybe part of unk1AC[0x22]? */
    /* 0x1F0 */ s16 unk1F0;
    /* 0x1F4 */ s16 unk1F4;
    /* 0x1F6 */ s16 unk1F6;
    /* 0x1F8 */ f32 unk1F8;
    /* 0x1FC */ f32 unk1FC;
    /* 0x200 */ f32 unk200;
    /* 0x204 */ s16 unk204;
    /* 0x206 */ s16 unk206;
    /* 0x208 */ s16 unk208;
    /* 0x20A */ s16 unk20A;
    /* 0x20C */ s16 unk20C;
    /* 0x20E */ char pad20E[225];
    /* 0x2F0 */ f32 pushedSpeed;
    /* 0x2F0 */ s16 yawTowardsActor;
} ObjBoyo; /* size = 0x20F */

#endif // Z_OBJ_BOYO_H
