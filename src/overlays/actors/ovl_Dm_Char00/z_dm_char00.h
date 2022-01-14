#ifndef Z_DM_CHAR00_H
#define Z_DM_CHAR00_H

#include "global.h"

struct DmChar00;

typedef void (*DmChar00ActionFunc)(struct DmChar00*, GlobalContext*);

#define DMCHAR00_GET(thisx) ((thisx)->params)
#define DMCHAR00_GET_F800(thisx) ((thisx)->params << 0xB)

#define DMCHAR00_0 0
#define DMCHAR00_1 1

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
} DmChar00Struct; // size = 0x10

typedef struct DmChar00 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[7];
    /* 0x01B2 */ UNK_TYPE1 unk_1B2[0x30];
    /* 0x01E2 */ Vec3s morphTable[7];
    /* 0x020C */ UNK_TYPE1 unk_20C[0x30];
    /* 0x023C */ DmChar00ActionFunc actionFunc;
    /* 0x0240 */ DmChar00Struct unk_240;
    /* 0x0250 */ DmChar00Struct unk_250;
    /* 0x0260 */ u8 unk_260;
    /* 0x0261 */ u8 unk_261;
    /* 0x0262 */ u16 unk_262;
} DmChar00; // size = 0x264

extern const ActorInit Dm_Char00_InitVars;

#endif // Z_DM_CHAR00_H
