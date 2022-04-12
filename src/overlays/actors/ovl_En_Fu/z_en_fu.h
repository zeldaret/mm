#ifndef Z_EN_FU_H
#define Z_EN_FU_H

#include "global.h"
#include "overlays/actors/ovl_Bg_Fu_Mizu/z_bg_fu_mizu.h"

struct EnFu;

typedef void (*EnFuActionFunc)(struct EnFu*, GlobalContext*);

#define ENFU_GET_FF00(thisx) (((thisx)->params >> 8) & 0xFF)

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ char unk_04[0x4];
    /* 0x08 */ Vec3f unk_08;
    /* 0x14 */ Vec3f unk_14;
    /* 0x20 */ Vec3f unk_20;
    /* 0x2C */ s16 unk_2C;
    /* 0x2E */ char unk_2E[0x8];
    /* 0x36 */ u8 unk_36;
    /* 0x37 */ u8 unk_37;
} EnFuUnkStruct; // size = 0x38

typedef struct EnFu {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ SkelAnime skelAnime;
    /* 0x01D4 */ EnFuActionFunc actionFunc;
    /* 0x01D8 */ Vec3s jointTable[21];
    /* 0x0256 */ Vec3s morphTable[21];
    /* 0x02D4 */ BgFuMizu* unk_2D4;
    /* 0x02D8 */ EnFuUnkStruct unk_2D8[10];
    /* 0x0508 */ Vec3f unk_508;
    /* 0x0514 */ Vec3f unk_514;
    /* 0x0520 */ s32 unk_520;
    /* 0x0524 */ s16 unk_524[3];
    /* 0x052A */ s16 unk_52A[3];
    /* 0x0530 */ char unk530[0x8];
    /* 0x0538 */ Vec3s* unk_538;
    /* 0x053C */ s16 unk_53C;
    /* 0x053E */ s16 unk_53E;
    /* 0x0540 */ s16 unk_540;
    /* 0x0542 */ s16 unk_542;
    /* 0x0544 */ s16 unk_544;
    /* 0x0546 */ s16 unk_546;
    /* 0x0548 */ s16 unk_548;
    /* 0x054A */ s16 unk_54A;
    /* 0x054C */ s16 unk_54C;
    /* 0x054E */ s16 unk_54E;
    /* 0x0550 */ s16 unk_550;
    /* 0x0552 */ u16 unk_552;
} EnFu; // size = 0x554

extern const ActorInit En_Fu_InitVars;

#endif // Z_EN_FU_H
