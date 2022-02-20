#ifndef Z_DM_CHAR01_H
#define Z_DM_CHAR01_H

#include "global.h"

struct DmChar01;

typedef void (*DmChar01ActionFunc)(struct DmChar01*, GlobalContext*);

#define DMCHAR01_GET(thisx) ((thisx)->params)

enum {
    /* 0 */ DMCHAR01_0,
    /* 1 */ DMCHAR01_1,
    /* 2 */ DMCHAR01_2,
    /* 3 */ DMCHAR01_3,
};

typedef struct DmChar01 {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ UNK_TYPE1 unk15C[0x44];
    /* 0x01A0 */ DmChar01ActionFunc actionFunc;
    /* 0x01A4 */ UNK_TYPE1 unk1A4[0x8];
    /* 0x01AC */ s16 unk_1AC[205];
    /* 0x0346 */ s16 unk_346;
    /* 0x0348 */ f32 unk_348;
    /* 0x034C */ u8 unk_34C;
    /* 0x034D */ u8 unk_34D;
} DmChar01; // size = 0x350

extern const ActorInit Dm_Char01_InitVars;

#endif // Z_DM_CHAR01_H
