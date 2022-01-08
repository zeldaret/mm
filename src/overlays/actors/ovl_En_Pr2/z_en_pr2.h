#ifndef Z_EN_PR2_H
#define Z_EN_PR2_H

#include "global.h"

struct EnPr2;

typedef void (*EnPr2ActionFunc)(struct EnPr2*, GlobalContext*);

#define ENPR2_GET_F(thisx) ((thisx)->params & 0xF)
#define ENPR2_GET_FF0(thisx) (((thisx)->params >> 4) & 0xFF)

typedef struct EnPr2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[5];
    /* 0x01A6 */ Vec3s morphtable[5];
    /* 0x01C4 */ EnPr2ActionFunc actionFunc;
    /* 0x01C8 */ s16 unk_1C8;
    /* 0x01CC */ Path* path;
    /* 0x01D0 */ s32 unk_1D0;
    /* 0x01D4 */ s16 unk_1D4;
    /* 0x01D6 */ s16 unk_1D6;
    /* 0x01D8 */ s16 unk_1D8;
    /* 0x01DA */ s16 unk_1DA;
    /* 0x01DC */ s16 unk_1DC;
    /* 0x01DE */ s16 unk_1DE;
    /* 0x01E0 */ s16 unk_1E0;
    /* 0x01E2 */ UNK_TYPE1 unk1E2[2];
    /* 0x01E4 */ s16 unk_1E4;
    /* 0x01E6 */ s16 unk_1E6;
    /* 0x01E8 */ UNK_TYPE1 unk1E8[4];
    /* 0x01EC */ s16 unk_1EC;
    /* 0x01EE */ s16 unk_1EE;
    /* 0x01F0 */ s16 unk_1F0;
    /* 0x01F2 */ s16 unk_1F2;
    /* 0x01F4 */ s16 unk_1F4;
    /* 0x01F8 */ f32 unk_1F8;
    /* 0x01FC */ f32 unk_1FC;
    /* 0x0200 */ f32 unk_200;
    /* 0x0204 */ f32 unk_204;
    /* 0x0208 */ f32 unk_208;
    /* 0x020C */ f32 unk_20C;
    /* 0x0210 */ s32 unk_210;
    /* 0x0214 */ UNK_TYPE1 unk214[4];
    /* 0x0218 */ s32 unk_218;
    /* 0x021C */ Vec3f unk_21C;
    /* 0x0228 */ Vec3f unk_228;
    /* 0x0234 */ Vec3f unk_234[5];
    /* 0x0270 */ Vec3f unk_270;
    /* 0x027C */ ColliderCylinder collider;
} EnPr2; // size = 0x2C8

extern const ActorInit En_Pr2_InitVars;

#endif // Z_EN_PR2_H
