#ifndef Z_EN_PR_H
#define Z_EN_PR_H

#include "global.h"

struct EnPr;

typedef void (*EnPrActionFunc)(struct EnPr*, GlobalContext*);

#define ENPR_GET_FF00(thisx) (((thisx)->params >> 8) & 0xFF)

#define ENPR_FF00_MAX 20
#define ENPR_FF00_MIN 0

typedef struct EnPr {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[10];
    /* 0x01C4 */ Vec3s morphTable[10];
    /* 0x0200 */ EnPrActionFunc actionFunc;
    /* 0x0204 */ u8 unk_204;
    /* 0x0206 */ s16 unk_206;
    /* 0x0208 */ s16 unk_208;
    /* 0x020A */ s16 unk_20A;
    /* 0x020C */ s16 unk_20C;
    /* 0x020E */ s16 unk_20E;
    /* 0x0210 */ s16 unk_210;
    /* 0x0212 */ s16 unk_212;
    /* 0x0214 */ s16 unk_214;
    /* 0x0216 */ s16 unk_216;
    /* 0x0218 */ UNK_TYPE1 unk218[4];
    /* 0x021C */ s32 unk_21C;
    /* 0x0220 */ UNK_TYPE1 unk220[0x8];
    /* 0x0228 */ s32 unk_228;
    /* 0x022C */ s16 unk_22C;
    /* 0x022E */ s16 drawDmgEffAlpha;
    /* 0x0230 */ s16 drawDmgEffType;
    /* 0x0234 */ f32 unk_234;
    /* 0x0238 */ f32 unk_238;
    /* 0x023C */ Vec3f limbPos[10];
    /* 0x02B4 */ f32 unk_2B4;
    /* 0x02B8 */ f32 unk_2B8;
    /* 0x02BC */ f32 unk_2BC;
    /* 0x02C0 */ f32 unk_2C0;
    /* 0x02C4 */ f32 unk_2C4;
    /* 0x02C8 */ f32 unk_2C8;
    /* 0x02CC */ f32 unk_2CC;
    /* 0x02D0 */ s16 unk_2D0;
    /* 0x02D2 */ s16 unk_2D2;
    /* 0x02D4 */ Vec3f unk_2D4;
    /* 0x02E0 */ Vec3f unk_2E0;
    /* 0x02EC */ UNK_TYPE1 unk2EC[0xC];
    /* 0x02F8 */ Actor* unk_2F8;
    /* 0x02FC */ ColliderCylinder collider;
} EnPr; // size = 0x348

extern const ActorInit En_Pr_InitVars;

#endif // Z_EN_PR_H
