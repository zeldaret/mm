#ifndef Z_EN_GOROIWA_H
#define Z_EN_GOROIWA_H

#include "global.h"

struct EnGoroiwa;

typedef void (*EnGoroiwaActionFunc)(struct EnGoroiwa*, GlobalContext*);
typedef s32 (*EnGoroiwaUnkFunc)(struct EnGoroiwa*);

#define ENGOROIWA_GET_C000(thisx) (((thisx)->params >> 0xE) & 3)
#define ENGOROIWA_GET_3000(thisx) (((thisx)->params >> 0xC) & 3)
#define ENGOROIWA_GET_400(thisx) (((thisx)->params >> 0xA) & 1)
#define ENGOROIWA_GET_300(thisx) (((thisx)->params >> 0x8) & 3)
#define ENGOROIWA_GET_FF(thisx) ((thisx)->params & 0xFF)

enum {
    /* 0 */ ENGOROIWA_300_0,
    /* 1 */ ENGOROIWA_300_1,
    /* 3 */ ENGOROIWA_300_3 = 3,
};

enum {
    /* 0 */ ENGOROIWA_400_0,
    /* 1 */ ENGOROIWA_400_1,
};

enum {
    /* 0 */ ENGOROIWA_3000_0,
    /* 1 */ ENGOROIWA_3000_1,
    /* 2 */ ENGOROIWA_3000_2,
};

enum {
    /* 1 */ ENGOROIWA_C000_1 = 1,
    /* 2 */ ENGOROIWA_C000_2,
};

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ CollisionPoly* unk_28;
    /* 0x2C */ u8 unk_2C;
    /* 0x2D */ u8 unk_2D;
} EnGoroiwaStruct; // size = 0x30

typedef struct EnGoroiwa {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderJntSph collider;
    /* 0x0164 */ ColliderJntSphElement colliderElements[1];
    /* 0x01A4 */ EnGoroiwaActionFunc actionFunc;
    /* 0x01A8 */ Vec3f unk_1A8;
    /* 0x01B4 */ Vec3f unk_1B4;
    /* 0x01C0 */ f32 unk_1C0;
    /* 0x01C4 */ f32 unk_1C4;
    /* 0x01C8 */ s16 unk_1C8;
    /* 0x01CA */ s16 unk_1CA;
    /* 0x01CC */ s16 unk_1CC;
    /* 0x01CE */ s16 unk_1CE;
    /* 0x01D0 */ Vec3s* unk_1D0;
    /* 0x01D4 */ s16 unk_1D4;
    /* 0x01D6 */ s16 unk_1D6;
    /* 0x01D8 */ s16 unk_1D8;
    /* 0x01DA */ s16 unk_1DA;
    /* 0x01DC */ f32 unk_1DC;
    /* 0x01E0 */ f32 unk_1E0;
    /* 0x01E4 */ s8 unk_1E4;
    /* 0x01E5 */ u8 unk_1E5;
    /* 0x01E6 */ s8 unk_1E6;
    /* 0x01E7 */ s8 unk_1E7;
    /* 0x01E8 */ EnGoroiwaStruct unk_1E8[2];
    /* 0x0248 */ s32 unk_248;
} EnGoroiwa; // size = 0x24C

extern const ActorInit En_Goroiwa_InitVars;

#endif // Z_EN_GOROIWA_H
