#ifndef Z_OBJ_BOYO_H
#define Z_OBJ_BOYO_H

#include "global.h"

typedef struct ObjBoyo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder unk144;            /* inferred */
    /* 0x190 */ AnimatedMaterial *unk190;           /* inferred */
    /* 0x194 */ s16 unk194;                         /* inferred */
    /* 0x196 */ s16 unk196;                         /* inferred */
    /* 0x198 */ f32 unk198;                         /* inferred */
    /* 0x19C */ f32 unk19C;                         /* inferred */
    /* 0x1A0 */ f32 unk1A0;                         /* inferred */
    /* 0x1A4 */ s16 unk1A4;                         /* inferred */
    /* 0x1A6 */ s16 unk1A6;                         /* inferred */
    /* 0x1A8 */ s16 unk1A8;                         /* inferred */
    /* 0x1AA */ s16 unk1AA;                         /* inferred */
    /* 0x1AC */ s16 unk1AC;                         /* inferred */
    /* 0x1AE */ char pad1AE[2];
} ObjBoyo;

#endif // Z_OBJ_BOYO_H
