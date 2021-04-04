#ifndef Z_EN_ENCOUNT2_H
#define Z_EN_ENCOUNT2_H

#include <global.h>

typedef void (*EnEncount2ActionFunc)(struct EnEncount2*, GlobalContext*);

struct EnEncount2;

typedef struct EnEncount2 {
    /* 0x0000 */ Actor actor;
    ///* 0x0144 */ char unk_0144[0x292C];
    /* 0x0144 */ s32 unk144; // index for destroy jnt sph?
    /* 0x0148 */ UNK_TYPE1 unk_0148[0x1C];
    /* 0x0164 */ s16 unk164; //init from params, ""flag"
    /* 0x0166 */ s16 unk166; //pad
    /* 0x0168 */ f32 unk168; //from rodata?
    /* 0x016C */ UNK_TYPE1 unk16C[0x4];
    /* 0x0170 */ ColliderJntSph collider;
    /* 0x0190 */ ColliderJntSphElement colElement;
      
    ///* 0x0148 */ UNK_TYPE1 unk_0148[0x28];
} EnEncount2; // size = 0x2A70

ColliderJntSphInit D_808E1F14;

extern const ActorInit En_Encount2_InitVars;

extern BgMeshHeader D_06002420;

#endif // Z_EN_ENCOUNT2_H
