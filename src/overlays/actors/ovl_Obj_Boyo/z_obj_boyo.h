#ifndef Z_OBJ_BOYO_H
#define Z_OBJ_BOYO_H

#include "global.h"
#include "../ovl_En_Torch2/z_en_torch2.h"

struct ObjBoyo;

typedef struct ObjBoyo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider; /* inferred */
    /* 0x150 */ s16* unk150;               /* inferred */
    /* 0x154 */ char pad154[2];
    /* 0x156 */ u8 unk156;                           /* inferred */
    /* 0x157 */ u8 unk157;                           /* inferred */
    /* 0x158 */ char pad158[0x58];                   /* maybe part of unk157[0x59]? */
    /* 0x190 */ AnimatedMaterial* animated_material; /* inferred */
    /* 0x194 */ s16 unk194;                          /* inferred */
    /* 0x196 */ s16 unk196;                          /* inferred */
    /* 0x198 */ f32 unk198;                          /* inferred */
    /* 0x19C */ f32 unk19C;                          /* inferred */
    /* 0x1A0 */ f32 unk1A0;                          /* inferred */
    /* 0x1A4 */ s16 unk1A4;                          /* inferred */
    /* 0x1A6 */ s16 unk1A6;                          /* inferred */
    /* 0x1A8 */ s16 unk1A8;                          /* inferred */
    /* 0x1AA */ s16 unk1AA;                          /* inferred */
    /* 0x1AC */ s16 unk1AC;                          /* inferred */
    /* 0x1AE */ char pad1AE[2];
} ObjBoyo; /* size = 0x1B0 */

#endif // Z_OBJ_BOYO_H
