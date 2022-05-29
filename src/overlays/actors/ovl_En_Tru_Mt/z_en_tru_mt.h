#ifndef Z_EN_TRU_MT_H
#define Z_EN_TRU_MT_H

#include "global.h"
#include "objects/object_tru/object_tru.h"

struct EnTruMt;

typedef void (*EnTruMtActionFunc)(struct EnTruMt*, GlobalContext*);

#define ENTRUMT_GET_FF(thisx) ((thisx)->params & 0xFF)
#define ENTRUMT_GET_FC00(thisx) (((thisx)->params & 0xFC00) >> 0xA)

typedef struct EnTruMt {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnTruMtActionFunc actionFunc;
    /* 0x0148 */ SkelAnime skelAnime;
    /* 0x018C */ ColliderSphere collider;
    /* 0x01E4 */ Vec3s jointTable[OBJECT_TRU_LIMB_MAX];
    /* 0x0286 */ Vec3s morphTable[OBJECT_TRU_LIMB_MAX];
    /* 0x0328 */ u16 unk_328;
    /* 0x032A */ UNK_TYPE1 unk32A[0xC];
    /* 0x0336 */ Vec3s unk_336;
    /* 0x033C */ Vec3f unk_33C;
    /* 0x0348 */ s16 unk_348;
    /* 0x034A */ s16 unk_34A;
    /* 0x034C */ s16 unk_34C;
    /* 0x034E */ s16 unk_34E;
    /* 0x0350 */ Vec3f unk_350;
    /* 0x035C */ Vec3f unk_35C;
    /* 0x0368 */ Path* path;
    /* 0x036C */ s32 unk_36C;
    /* 0x0370 */ Vec3f unk_370;
    /* 0x037C */ UNK_TYPE1 unk37C[0xC];
    /* 0x0388 */ s16 unk_388;
    /* 0x038A */ s16 unk_38A;
    /* 0x038C */ s16 unk_38C;
    /* 0x038E */ Vec3s unk_38E;
    /* 0x0394 */ s16 unk_394;
    /* 0x0398 */ Vec3f unk_398;
    /* 0x03A4 */ u8 unk_3A4;
} EnTruMt; // size = 0x3A8

extern const ActorInit En_Tru_Mt_InitVars;

#endif // Z_EN_TRU_MT_H
