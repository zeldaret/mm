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

#define ENAN_STATE_8    (1 << 3)
#define ENAN_STATE_10   (1 << 4)
#define ENAN_STATE_20   (1 << 5)
#define ENAN_STATE_40   (1 << 6)
#define ENAN_STATE_80   (1 << 7)
#define ENAN_STATE_100  (1 << 8)
#define ENAN_STATE_200  (1 << 9)
#define ENAN_STATE_400  (1 << 10)
#define ENAN_STATE_800  (1 << 11)
#define ENAN_STATE_1000 (1 << 12)
#define ENAN_STATE_2000 (1 << 13)
#define ENAN_STATE_4000 (1 << 14)
#define ENAN_STATE_8000 (1 << 15)

typedef struct EnAn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnAnActionFunc actionFunc;
    /* 0x18C */ EnAnUnkFunc unk_18C;
    /* 0x190 */ ColliderCylinder collider;
    /* 0x1DC */ Path* timePath;
    /* 0x1E0 */ Vec3f timePathTargetPos;
    /* 0x1EC */ f32 timePathProgress;
    /* 0x1F0 */ s32 timePathTotalTime;
    /* 0x1F4 */ s32 timePathWaypointTime;
    /* 0x1F8 */ s32 timePathWaypoint;
    /* 0x1FC */ s32 timePathElapsedTime;
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
    /* 0x258 */ Vec3s unk_258; // some limb rot
    /* 0x25E */ UNK_TYPE1 unk_25E[0x6];
    /* 0x264 */ Vec3s jointTable[OBJECT_AN1_LIMB_MAX];
    /* 0x2E2 */ Vec3s morphTable[OBJECT_AN1_LIMB_MAX];
    /* 0x360 */ u16 stateFlags;
    /* 0x362 */ u16 prevTextId;
    /* 0x364 */ u8 cueId;
    /* 0x368 */ f32 unk_368;
    /* 0x36C */ UNK_TYPE1 unk_36C[0x8];
    /* 0x374 */ f32 unk_374;
    /* 0x378 */ s16 unk_378; // schedule time diff
    /* 0x37A */ s16 unk_37A; // schedule time diff
    /* 0x37C */ s16 unk_37C; // some limb z rot
    /* 0x37E */ s16 unk_37E; // some limb y rot
    /* 0x380 */ UNK_TYPE1 unk_380[0x4];
    /* 0x384 */ s16 timePathTimeSpeed;
    /* 0x386 */ s16 unk_386; // timer
    /* 0x388 */ s16 unk_388; // timer
    /* 0x38A */ s16 unk_38A; // face enum
    /* 0x38C */ s16 faceIndex; // face enum
    /* 0x38E */ s16 unk_38E; // timer
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
    /* 0x3C4 */ s32 unk_3C4; // set but not read
} EnAn; // size = 0x3C8

#endif // Z_EN_AN_H
