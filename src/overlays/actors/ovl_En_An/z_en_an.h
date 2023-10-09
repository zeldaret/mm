#ifndef Z_EN_AN_H
#define Z_EN_AN_H

#include "global.h"
#include "assets/objects/object_an1/object_an1.h"

struct EnAn;

typedef void (*EnAnActionFunc)(struct EnAn*, PlayState*);
typedef void (*EnAnUnkFunc)(struct EnAn*, PlayState*);
typedef s32 (*MsgEventFunc)(Actor*, PlayState*);

#define ENAN_GET_PATH_INDEX(thisx) ((thisx)->params & 0xFF)
#define ENAN_8000 0x8000
//#define ENAN_GET_8000(thisx) (((thisx)->params & 0x8000) >> 0xF)

typedef struct EnAn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnAnActionFunc actionFunc;
    /* 0x18C */ EnAnUnkFunc unk_18C;
    /* 0x190 */ ColliderCylinder unk_190;
    /* 0x1DC */ Path* unk_1DC; // timePath
    /* 0x1E0 */ Vec3f unk_1E0;
    /* 0x1EC */ f32 unk_1EC;
    /* 0x1F0 */ s32 unk_1F0;
    /* 0x1F4 */ s32 unk_1F4;
    /* 0x1F8 */ s32 unk_1F8;
    /* 0x1FC */ s32 unk_1FC;
    /* 0x200 */ u8 scheduleResult;
    /* 0x204 */ s32* msgEventScript;
    /* 0x208 */ s8 an2ObjectSlot;
    /* 0x209 */ s8 an3ObjectSlot;
    /* 0x20A */ s8 maskKerfayObjectSlot;
    /* 0x20B */ s8 an4ObjectSlot;
    /* 0x20C */ s8 msmoObjectSlot;
    /* 0x210 */ s32 msgScriptResumePos;
    /* 0x214 */ s8 unk_214; // curRoom.num
    /* 0x215 */ s8 unk_215;
    /* 0x218 */ Actor* unk_218;
    /* 0x21C */ UNK_TYPE1 unk_21C[0xC];
    /* 0x228 */ Vec3f unk_228;
    /* 0x234 */ Vec3f unk_234;
    /* 0x240 */ Vec3f unk_240;
    /* 0x24C */ UNK_TYPE1 unk_24C[0xC];
    /* 0x258 */ Vec3s unk_258;
    /* 0x25E */ UNK_TYPE1 unk_25E[0x6];
    /* 0x264 */ Vec3s jointTable[OBJECT_AN1_LIMB_MAX];
    /* 0x2E2 */ Vec3s morphTable[OBJECT_AN1_LIMB_MAX];
    /* 0x360 */ u16 unk_360; // flags?
    /* 0x362 */ u16 unk_362;
    /* 0x364 */ u8 unk_364;
    /* 0x368 */ f32 unk_368;
    /* 0x36C */ UNK_TYPE1 unk_36C[0x8];
    /* 0x374 */ f32 unk_374;
    /* 0x378 */ s16 unk_378; // schedule time diff
    /* 0x37A */ s16 unk_37A;
    /* 0x37C */ s16 unk_37C;
    /* 0x37E */ s16 unk_37E;
    /* 0x380 */ UNK_TYPE1 unk_380[0x4];
    /* 0x384 */ s16 unk_384;
    /* 0x386 */ s16 unk_386;
    /* 0x388 */ s16 unk_388;
    /* 0x38A */ s16 unk_38A; // face enum
    /* 0x38C */ s16 faceIndex; // face enum
    /* 0x38E */ s16 unk_38E;
    /* 0x390 */ s16 eyeTexIndex;
    /* 0x392 */ s16 mouthTexIndex;
    /* 0x394 */ s16 unk_394;
    /* 0x396 */ s16 unk_396;
    /* 0x398 */ MsgEventFunc msgEventFunc;
    /* 0x39C */ s32 animIndex;
    /* 0x3A0 */ UNK_TYPE1 unk_3A0[0x8];
    /* 0x3A8 */ u32 unk_3A8;
    /* 0x3AC */ u32 unk_3AC;
    /* 0x3B0 */ s32 unk_3B0;
    /* 0x3B4 */ s32 unk_3B4;
    /* 0x3B8 */ s32 unk_3B8;
    /* 0x3BC */ s32 unk_3BC;
    /* 0x3C0 */ s32 unk_3C0;
    /* 0x3C4 */ s32 unk_3C4;
} EnAn; // size = 0x3C8

#endif // Z_EN_AN_H
