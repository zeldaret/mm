#ifndef Z_EN_BOX_H
#define Z_EN_BOX_H

#include "global.h"

struct EnBox;
struct func_80867BDC_a0;

typedef void (*EnBoxActionFunc)(struct EnBox*, GlobalContext*);
typedef void (*EnBoxUnkFunc)(struct func_80867BDC_a0* arg0, GlobalContext* globalCtx);

typedef struct func_80867BDC_a0 {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ EnBoxUnkFunc unk_0C;
    /* 0x10 */ EnBoxUnkFunc unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
} func_80867BDC_a0; //size 0x24

typedef struct {
    f32 test[5];
} T_80869B54; // 0x14

typedef struct EnBox {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ SkelAnime skelAnime;
    /* 0x01A0 */ s32 unk_1A0;
    /* 0x01A4 */ char unk_1A4[0x04];
    /* 0x01A8 */ f32 unk_1A8;
    /* 0x01AC */ EnBoxActionFunc actionFunc;
    /* 0x01B0 */ Vec3s jointTable[5];
    /* 0x01CE */ Vec3s morphTable[5];
    /* 0x01EC */ s16 unk_1EC;
    /* 0x01EE */ u8 unk_1EE;
    /* 0x01EF */ u8 unk_1EF;
    /* 0x01F0 */ u8 unk_1F0;
    /* 0x01F1 */ u8 unk_1F1;
    /* 0x01F2 */ u8 unk_1F2;
    /* 0x01F3 */ s8 unk_1F3;
    /* 0x01F4 */ func_80867BDC_a0 unk_1F4;
    /* 0x0218 */ s16 unk_218;
    /* 0x021A */ s16 unk_21A;
    /* 0x021C */ s32 getItem;
    /* 0x0220 */ s32 unk_220;
} EnBox; // size = 0x224

extern const ActorInit En_Box_InitVars;

#endif // Z_EN_BOX_H
