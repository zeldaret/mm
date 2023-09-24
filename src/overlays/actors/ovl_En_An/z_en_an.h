#ifndef Z_EN_AN_H
#define Z_EN_AN_H

#include "global.h"
#include "assets/objects/object_an1/object_an1.h"

struct EnAn;

typedef void (*EnAnActionFunc)(struct EnAn*, PlayState*);
typedef void (*EnAnUnkFunc)(struct EnAn*, PlayState*);
typedef s32 (*MsgEventFunc)(Actor*, PlayState*);

// path index : 0xFF

#define ENAN_GET_8000(thisx) (((thisx)->params & 0x8000) >> 0xF)

typedef enum EnAnAnimation {
    /* -1 */ ENAN_ANIM_NONE = -1,
    /*  0 */ ENAN_ANIM_0,
    /*  1 */ ENAN_ANIM_1,
    /*  2 */ ENAN_ANIM_2,
    /*  3 */ ENAN_ANIM_3,
    /*  4 */ ENAN_ANIM_4,
    /*  5 */ ENAN_ANIM_5,
    /*  6 */ ENAN_ANIM_6,
    /*  7 */ ENAN_ANIM_7,
    /*  8 */ ENAN_ANIM_8,
    /*  9 */ ENAN_ANIM_9,
    /* 10 */ ENAN_ANIM_10,
    /* 11 */ ENAN_ANIM_11,
    /* 12 */ ENAN_ANIM_12,
    /* 13 */ ENAN_ANIM_13,
    /* 14 */ ENAN_ANIM_14,
    /* 15 */ ENAN_ANIM_15,
    /* 16 */ ENAN_ANIM_16,

    /* 17 */ ENAN_ANIM_17,
    /* 18 */ ENAN_ANIM_18,
    /* 19 */ ENAN_ANIM_19,
    /* 20 */ ENAN_ANIM_20,

    /* 21 */ ENAN_ANIM_21,
    /* 22 */ ENAN_ANIM_22,
    /* 23 */ ENAN_ANIM_23,
    /* 24 */ ENAN_ANIM_24,

    /* 25 */ ENAN_ANIM_25,
    /* 26 */ ENAN_ANIM_26,
    /* 27 */ ENAN_ANIM_27,
    /* 28 */ ENAN_ANIM_28,
    /* 29 */ ENAN_ANIM_29,
    /* 30 */ ENAN_ANIM_30,
    /* 31 */ ENAN_ANIM_31,
    /* 32 */ ENAN_ANIM_32,
    /* 33 */ ENAN_ANIM_33,
    /* 34 */ ENAN_ANIM_34,
    /* 35 */ ENAN_ANIM_35,
    /* 36 */ ENAN_ANIM_MAX
} EnAnAnimation;

typedef struct EnAn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnAnActionFunc actionFunc;
    /* 0x18C */ EnAnUnkFunc unk_18C;
    /* 0x190 */ ColliderCylinder unk_190;
    /* 0x1DC */ Path* unk_1DC;
    /* 0x1E0 */ Vec3f unk_1E0;                 /* maybe part of unk_1DC[5]? */
    /* 0x1EC */ f32 unk_1EC;
    /* 0x1F0 */ s32 unk_1F0;                        /* inferred */
    /* 0x1F4 */ s32 unk_1F4;                        /* inferred */
    /* 0x1F8 */ s32 unk_1F8;                        /* inferred */
    /* 0x1FC */ s32 unk_1FC;                        /* inferred */
    /* 0x200 */ u8 unk_200; // enum? // schedule result
    /* 0x201 */ char unk_201[3];                    /* maybe part of unk_200[4]? */
    /* 0x204 */ s32* msgEventScript;
    /* 0x208 */ s8 an2ObjIndex;
    /* 0x209 */ s8 an3ObjIndex;
    /* 0x20A */ s8 maskKerfayObjIndex;
    /* 0x20B */ s8 an4ObjIndex;
    /* 0x20C */ s8 msmoObjIndex;
    /* 0x20D */ char unk_20D[3];                    /* maybe part of unk_20C[4]? */
    /* 0x210 */ s32 msgScriptResumePos;
    /* 0x214 */ s8 unk_214; // curRoom.num
    /* 0x215 */ s8 unk_215;
    /* 0x216 */ UNK_TYPE1 unk_216[0x2];
    /* 0x218 */ Actor* unk_218;                     /* inferred */
    /* 0x21C */ UNK_TYPE1 unk_21C[0xC];                 /* maybe part of unk_218[0x13]? */
    /* 0x228 */ Vec3f unk_228;
    /* 0x234 */ Vec3f unk_234;
    /* 0x240 */ Vec3f unk_240;
    /* 0x24C */ UNK_TYPE1 unk_24C[0xC];
    /* 0x258 */ Vec3s unk_258;
    /* 0x25E */ UNK_TYPE1 unk_25E[0x2];
    /* 0x260 */ UNK_TYPE1 unk_260[0x4];
    /* 0x264 */ Vec3s unk_264[0x15];
    /* 0x2E2 */ Vec3s unk_2E2[0x15];
    /* 0x360 */ u16 unk_360; // flags?
    /* 0x362 */ u16 unk_362;                        /* inferred */
    /* 0x364 */ u8 unk_364;
    /* 0x365 */ char unk_365[3];                    /* maybe part of unk_364[4]? */
    /* 0x368 */ f32 unk_368;                        /* inferred */
    /* 0x36C */ char unk_36C[8];                    /* maybe part of unk_368[3]? */
    /* 0x374 */ f32 unk_374;                        /* inferred */
    /* 0x378 */ s16 unk_378; // schedule time diff
    /* 0x37A */ s16 unk_37A;
    /* 0x37C */ s16 unk_37C;                        /* inferred */
    /* 0x37E */ s16 unk_37E;                        /* inferred */
    /* 0x380 */ char unk_380[4];                    /* maybe part of unk_37E[3]? */
    /* 0x384 */ s16 unk_384;                        /* inferred */
    /* 0x386 */ s16 unk_386;
    /* 0x388 */ s16 unk_388;                        /* inferred */
    /* 0x38A */ s16 unk_38A;                        /* inferred */
    /* 0x38C */ s16 unk_38C;                        /* inferred */
    /* 0x38E */ s16 unk_38E;                        /* inferred */
    /* 0x390 */ s16 eyeTexIndex;
    /* 0x392 */ s16 mouthTexIndex;                        /* inferred */
    /* 0x394 */ s16 unk_394;
    /* 0x396 */ s16 unk_396;
    /* 0x398 */ MsgEventFunc msgEventFunc;
    /* 0x39C */ EnAnAnimation animIndex;
    /* 0x3A0 */ UNK_TYPE1 unk_3A0[8];
    /* 0x3A8 */ u32 unk_3A8;                        /* inferred */
    /* 0x3AC */ u32 unk_3AC;                        /* inferred */
    /* 0x3B0 */ s32 unk_3B0;                        /* inferred */
    /* 0x3B4 */ s32 unk_3B4;                        /* inferred */
    /* 0x3B8 */ s32 unk_3B8;
    /* 0x3BC */ s32 unk_3BC;
    /* 0x3C0 */ s32 unk_3C0;                        /* inferred */
    /* 0x3C4 */ s32 unk_3C4;
} EnAn; // size = 0x3C8

#endif // Z_EN_AN_H
