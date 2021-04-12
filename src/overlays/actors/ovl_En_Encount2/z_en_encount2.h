#ifndef Z_EN_ENCOUNT2_H
#define Z_EN_ENCOUNT2_H

#include <global.h>

typedef void (*EnEncount2ActionFunc)(struct EnEncount2*, GlobalContext*);

typedef struct unkEnE2Struct {
   /* 0x00 */ u8 unk0;
   /* 0x01 */ UNK_TYPE1 unk1[3];
  
   
   /* 0x04 */ Vec3f unk4; //sw, but reading from floats? might be vec3f
   ///* 0x08 */ f32 unk8;
   ///* 0x0C */ f32 unkC;

   /* 0x10 */ s8  unk10[0x4];
   /* 0x14 */ s16 unk14;
   /* 0x16 */ s16 unk16;

   /* 0x18 */ Vec3f unk18; //vec3f?
   ///* 0x1C */ f32 unk1C;
   ///* 0x20 */ f32 unk20;

   /* 0x24 */ Vec3f unk24; //vec3f?
   ///* 0x28 */ f32 unk28;
   ///* 0x2C */ f32 unk2C;

   /* 0x30 */ f32 unk30;

} unkEnE2Struct; // size 0x34

struct EnEncount2;

typedef struct EnEncount2 {
    /* 0x0000 */ Actor actor;
    ///* 0x0144 */ char unk_0144[0x292C];
    /* 0x0144 */ s32 unk144; // index for destroy jnt sph?
    /* 0x0148 */ UNK_TYPE1 unk_0148[0x14];
    /* 0x015C */ EnEncount2ActionFunc actionFunc; // index for destroy jnt sph?
    /* 0x0160 */ s16 unk160;
    /* 0x0162 */ s16 unk162; //func_808E16FC
    /* 0x0164 */ s16 unk164; //init from params, ""flag"
    /* 0x0166 */ s16 unk166; //pad
    /* 0x0168 */ f32 unk168; //gets used for scale in update
    /* 0x016C */ f32 unk16C;
    /* 0x0170 */ ColliderJntSph collider;
    /* 0x0190 */ ColliderJntSphElement colElement;
                // wild guess, there are only like 2 structs defined anywhere by anyone at this size
    ///* 0x01D0 */ EffectSsBlastInitParams unkStructs[3]; //size unk
    /* 0x01D0 */ unkEnE2Struct unkStructs[200]; //size unk

    // where the heck is the rest of the data? is element that big?
      
    ///* 0x0148 */ UNK_TYPE1 unk_0148[0x28];
} EnEncount2; // size = 0x2A70

extern ColliderJntSphInit D_808E1F14;


extern const ActorInit En_Encount2_InitVars;

extern BgMeshHeader D_06002420;

extern s32 D_06000A00;
extern s32 D_06000D78;

extern f32 D_808E1F54; // not found in rodata

extern f32 D_808E1F58; // not found in rodata

#endif // Z_EN_ENCOUNT2_H
