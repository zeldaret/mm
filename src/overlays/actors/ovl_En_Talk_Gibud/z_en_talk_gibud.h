#ifndef Z_EN_TALK_GIBUD_H
#define Z_EN_TALK_GIBUD_H

#include "global.h"

struct EnTalkGibud;

typedef void (*EnTalkGibudActionFunc)(struct EnTalkGibud*, GlobalContext*);

typedef struct EnTalkGibud {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ SkelAnime skelAnime;
    /* 0x01D4 */ EnTalkGibudActionFunc actionFunc;
    /* 0x01D8 */ Vec3f unk_1D8[15];
    /* 0x028C */ s32 unk_28C;
    /* 0x0290 */ s32 unk_290;
    /* 0x0294 */ s32 unk_294;
    /* 0x0298 */ s32 unk_298;
    /* 0x029C */ f32 unk_29C;
    /* 0x02A0 */ f32 unk_2A0;
    /* 0x02A4 */ Vec3s jointTable[26];
    /* 0x0340 */ Vec3s morphTable[26];
    /* 0x03DC */ s16 unk_3DC;
    /* 0x03DE */ Vec3s unk_3DE;
    /* 0x03E4 */ Vec3s unk_3E4;
    /* 0x03EA */ s16 unk_3EA;
    /* 0x03EC */ s16 unk_3EC;
    /* 0x03EE */ s16 unk_3EE;
    /* 0x03F0 */ s16 unk_3F0;
    /* 0x03F2 */ s16 unk_3F2;
    /* 0x03F4 */ s16 unk_3F4;
    /* 0x03F6 */ u8 unk_3F6;
    /* 0x03F7 */ s8 unk_3F7;
} EnTalkGibud; // size = 0x3F8

extern const ActorInit En_Talk_Gibud_InitVars;

#endif // Z_EN_TALK_GIBUD_H
