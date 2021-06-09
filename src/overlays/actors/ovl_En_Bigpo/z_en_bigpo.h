#ifndef Z_EN_BIGPO_H
#define Z_EN_BIGPO_H

#include <global.h>

struct EnBigpo;

typedef void (*EnBigPoActionFunc)(struct EnBigPo*, GlobalContext*);

typedef struct EnBigpo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ char unk188[0x78]; //nothing here? is there a skelanime extension?
    /* 0x200 */ EnBigPoActionFunc actionFunc;
    /* 0x204 */ u8 unk204;
    /* 0x208 */ s16 unk208; // pad?
    /* 0x20A */ s16 unk20A;
    /* 0x210 */ s16 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x220 */ f32 unk220; // possible vec3f
    // weirdly nothing here? might be a fluke
    /* 0x224 */ char unk224[0x6C];
    /* 0x290 */ u8 unk290[4];
    /* 0x2AC */ ColliderCylinder collider;
    /* 0x2F8 */ char unk2F8[0x4C]; // sus
    /* 0x344 */ UNK_TYPE unk344;
    /* 0x348 */ char un348[0x50];
} EnBigpo; // size = 0x398

extern const ActorInit En_Bigpo_InitVars;

#endif // Z_EN_BIGPO_H
