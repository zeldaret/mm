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
    /* 0x01D8 */ Vec3f unk_1D8;
    /* 0x01E4 */ Vec3f unk_1E4;
    /* 0x01F0 */ Vec3f unk_1F0;
    /* 0x01FC */ char unk_1FC[0xA8];
    /* 0x02A4 */ Vec3s jointTable[26];
    /* 0x0340 */ Vec3s morphTable[26];
    /* 0x03DC */ char unk_3DC[0x4];
    /* 0x03E0 */ s16 unk_3E0;
    /* 0x03E2 */ char unk_3E2[0x4];
    /* 0x03E6 */ s16 unk_3E6;
    /* 0x03E8 */ char unk_3E8[0x2];
    /* 0x03EA */ s16 unk_3EA;
    /* 0x03EC */ s16 unk_3EC;
    /* 0x03EE */ char unk_3EE[0xA];
} EnTalkGibud; // size = 0x3F8

extern const ActorInit En_Talk_Gibud_InitVars;

#endif // Z_EN_TALK_GIBUD_H
