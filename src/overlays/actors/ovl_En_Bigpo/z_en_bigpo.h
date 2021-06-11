#ifndef Z_EN_BIGPO_H
#define Z_EN_BIGPO_H

#include <global.h>

struct EnBigpo;

typedef void (*EnBigPoActionFunc)(struct EnBigpo*, GlobalContext*);

typedef struct EnBigpoFireParticle {
    ///* 0x00 */ Vec3f pos;
    /* 0x00 */ LightInfo info; // size E
    /* 0x10 */ UNK_PTR unk10; // struct with unkC
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18; // pad?
    /* 0x1C */ LightNode* light;
} EnBigpoFireParticle; // size = 0x20

typedef struct EnBigpo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s limbDrawTbl[0xA];
    /* 0x1C4 */ Vec3s transitionDrawTbl[0xA];
    /* 0x200 */ EnBigPoActionFunc actionFunc;
    /* 0x204 */ u8 unk204;
    /* 0x206 */ s16 unk206;
    /* 0x208 */ s16 unk208; // pad?
    /* 0x20A */ s16 unk20A;
    /* 0x20C */ char unk20C[2];
    /* 0x20E */ u16 unk20E;
    /* 0x210 */ s16 switchFlags;
    /* 0x212 */ s16 unk212;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ f32 unk21C; //pad?
    /* 0x220 */ f32 unk220; // possible vec3f
    // weirdly nothing here? might be a fluke
    /* 0x224 */ char unk224[0x6C];
    /* 0x290 */ u8 unk290[4]; // color?
    /* 0x294 */ char unk294[0x18];
    /* 0x2AC */ ColliderCylinder collider;
    /* 0x2F8 */ char unk2F8[0x30];
    // somewhere here is an array of 3 0x20 items, trying to find the start because weird
    
    ///* 0x328 */ Vec3f unkPos;
    ///* 0x33C */ f32 height;
    ///* 0x33C */ f32 unk33c;
    ///* 0x344 */ LightNode* lights; // this is loc light 1 in array of structs
    /* 0x328 */ EnBigpoFireParticle fires[3];
    /* 0x388 */ char un388[0x10];
} EnBigpo; // size = 0x398

extern const ActorInit En_Bigpo_InitVars;

#endif // Z_EN_BIGPO_H
