#ifndef Z_EN_JGAME_TSN_H
#define Z_EN_JGAME_TSN_H

#include "global.h"
#include "objects/object_tsn/object_tsn.h"

struct EnJgameTsn;

typedef void (*EnJgameTsnActionFunc)(struct EnJgameTsn*, GlobalContext*);

#define ENJGAMETSN_GET_FF(thisx) ((thisx)->params & 0xFF)

typedef struct {
    /* 0x00 */ Vec3s* points;
    /* 0x04 */ s32 count;
} EnJgameTsnStruct; // size = 0x8

typedef struct EnJgameTsn {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ SkelAnime skelAnime;
    /* 0x01D4 */ EnJgameTsnActionFunc actionFunc;
    /* 0x01D8 */ EnJgameTsnStruct unk_1D8[4];
    /* 0x01F8 */ EnJgameTsnStruct unk_1F8;
    /* 0x0200 */ EnJgameTsnStruct unk_200;
    /* 0x0208 */ u8* unk_208[4];
    /* 0x0218 */ s32 unk_218;
    /* 0x021C */ s32 unk_21C;
    /* 0x0220 */ Vec3s jointTable[OBJECT_TSN_LIMB_MAX];
    /* 0x0286 */ Vec3s morphTable[OBJECT_TSN_LIMB_MAX];
    /* 0x02EC */ Vec3s unk_2EC;
    /* 0x02F2 */ Vec3s unk_2F2;
    /* 0x02F8 */ s16 unk_2F8;
    /* 0x02FA */ s16 unk_2FA;
    /* 0x02FC */ s16 unk_2FC;
    /* 0x02FE */ s16 unk_2FE;
    /* 0x0300 */ u16 unk_300;
} EnJgameTsn; // size = 0x304

extern const ActorInit En_Jgame_Tsn_InitVars;

#endif // Z_EN_JGAME_TSN_H
