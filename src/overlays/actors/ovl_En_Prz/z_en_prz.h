#ifndef Z_EN_PRZ_H
#define Z_EN_PRZ_H

#include "global.h"

struct EnPrz;

typedef void (*EnPrzActionFunc)(struct EnPrz*, GlobalContext*);

#define ENPRZ_GET(thisx) ((thisx)->params & 0xFF)

typedef struct EnPrz {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[5];
    /* 0x01A6 */ Vec3s morphTable[5];
    /* 0x01C4 */ EnPrzActionFunc actionFunc;
    /* 0x01C8 */ u8 unk_1C8;
    /* 0x01CC */ Vec3f unk_1CC;
    /* 0x01D8 */ Vec3f unk_1D8;
    /* 0x01E4 */ s16 unk_1E4;
    /* 0x01E6 */ s16 unk_1E6;
    /* 0x01E8 */ s16 unk_1E8;
    /* 0x01EA */ s16 unk_1EA;
    /* 0x01EC */ s16 unk_1EC;
    /* 0x01EE */ s16 unk_1EE;
    /* 0x01F0 */ UNK_TYPE1 unk1F0[2];
    /* 0x01F2 */ s16 unk_1F2;
    /* 0x01F4 */ UNK_TYPE1 unk1F4[8];
    /* 0x01FC */ s16 unk_1FC;
    /* 0x01FE */ s16 unk_1FE;
    /* 0x0200 */ UNK_TYPE1 unk200[2];
    /* 0x0202 */ s16 unk_202;
    /* 0x0204 */ s32 unk_204;
    /* 0x0208 */ f32 unk_208;
    /* 0x020C */ f32 unk_20C;
    /* 0x0210 */ f32 unk_210;
    /* 0x0214 */ f32 unk_214;
    /* 0x0218 */ f32 unk_218;
    /* 0x021C */ UNK_TYPE1 unk21C[4];
    /* 0x0220 */ Actor* unk_220;
    /* 0x0224 */ ColliderCylinder collider;
} EnPrz; // size = 0x270

extern const ActorInit En_Prz_InitVars;

#endif // Z_EN_PRZ_H
