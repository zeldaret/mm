#ifndef Z_EN_BOMBERS2_H
#define Z_EN_BOMBERS2_H

#include "global.h"

#include "objects/object_cs/object_cs.h"

struct EnBombers2;

typedef void (*EnBombers2ActionFunc)(struct EnBombers2*, GlobalContext*);

typedef struct EnBombers2 {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s morphTable[OBJECT_CS_LIMB_MAX];
    /* 0x0206 */ Vec3s jointTable[OBJECT_CS_LIMB_MAX];
    /* 0x0284 */ EnBombers2ActionFunc actionFunc;
    /* 0x0288 */ s16 unk_288;
    /* 0x028A */ s16 unk_28A;
    /* 0x028C */ UNK_TYPE1 pad_28C[2];
    /* 0x028E */ s16 unk_28E;
    /* 0x0290 */ s16 unk_290;
    /* 0x0292 */ UNK_TYPE1 pad_292[4];
    /* 0x0296 */ s16 unk_296;
    /* 0x0298 */ UNK_TYPE1 pad_298[4];
    /* 0x029C */ Vec3f unk_29C;
    /* 0x02A8 */ s32 unk_2A8;
    /* 0x02AC */ u8 unk_2AC;
    /* 0x02AE */ s16 animIndex;
    /* 0x02B0 */ s16 cutscene;
    /* 0x02B2 */ s16 unk_2B2;
    /* 0x02B4 */ s16 unk_2B4;
    /* 0x02B6 */ s16 unk_2B6;
    /* 0x02B8 */ f32 lastAnimFrame;
    /* 0x02BC */ s16 eyeIndex;
    /* 0x02BE */ s16 unk_2BE;
    /* 0x02C0 */ s16 unk_2C0;
    /* 0x02C2 */ s16 textIdIndex;
    /* 0x02C4 */ s16 correctDigitSlots[5];
    /* 0x02CE */ s16 unk_2CE;  
    /* 0x02D0 */ ColliderCylinder collider;
} EnBombers2; // size = 0x31C

extern const ActorInit En_Bombers2_InitVars;

#endif // Z_EN_BOMBERS2_H
