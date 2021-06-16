#ifndef Z_EN_BIGPO_H
#define Z_EN_BIGPO_H

#include <global.h>

struct EnBigpo;

typedef void (*EnBigPoActionFunc)(struct EnBigpo*, GlobalContext*);

//typedef struct EnBigpoFireParticle {
    ///* 0x00 */ LightInfo info; // size E
    ///* 0x10 */ Vec3f unk10; // struct with unkC
    ///* 0x1C */ LightNode* light;
//} EnBigpoFireParticle; // size = 0x20

typedef struct EnBigpoFireParticle {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ LightNode* light;
    /* 0x10 */ LightInfo info; // size E
} EnBigpoFireParticle; // size = 0x20

typedef struct EnBigpo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s limbDrawTbl[0xA];
    /* 0x1C4 */ Vec3s transitionDrawTbl[0xA];
    /* 0x200 */ EnBigPoActionFunc actionFunc;
    /* 0x204 */ u8 unk204;
    /* 0x206 */ s16 unk206;
    /* 0x208 */ s16 unk208;
    /* 0x20A */ s16 rotVelocity; // rot speed?
    /* 0x20C */ s16 unk20C;
    /* 0x20E */ s16 unk20E;
    /* 0x210 */ s16 switchFlags;
    /* 0x212 */ s16 unk212;
    /* 0x214 */ f32 unk214; // speed?
    /* 0x218 */ f32 unk218; // possible vec3f
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ Vec3f unk224[0x9];
    /* 0x290 */ Color_RGBA8 unk290; // color of what though? does the big poe change color?
    /* 0x294 */ Color_RGBA8 unk294;
    /* 0x298 */ char unk298[0x14];
    /* 0x2AC */ ColliderCylinder collider;
    /* 0x2F8 */ MtxF drawMtxF;
    /* 0x338 */ EnBigpoFireParticle fires[3];
} EnBigpo; // size = 0x398

extern const ActorInit En_Bigpo_InitVars;

#define FIRSTENEMY ((Actor*)globalCtx->actorCtx.actorList[ACTORCAT_ENEMY].first)

#endif // Z_EN_BIGPO_H
