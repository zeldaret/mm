#ifndef Z_EN_OSN_H
#define Z_EN_OSN_H

#include "global.h"

struct EnOsn;

typedef void (*EnOsnActionFunc)(struct EnOsn*, GlobalContext*);

typedef struct EnOsn {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0X0190 */ SkelAnime skelAnime;
    /* 0x01D4 */ EnOsnActionFunc actionFunc;
    /* 0x01D8 */ char unk_1D8[0x2];
    /* 0x01DA */ s16 unk_1DA;
    /* 0x01DC */ char unk_1DC[0xE];
    /* 0x01EA */ u16  unk_1EA;
    /* 0x01EC */ u8 unk_1EC;
    /* 0x01ED */ u8 unk_1ED;
    /* 0x01EE */ s16 cutscene;
    /* 0x01F0 */ u8 unk_1F0;
    /* 0x01F1 */ char unk_1F1[0x3];
    /* 0x01F4 */ u16 unk_1F4;
    /* 0x01F6 */ char unk_1F6[0x2];
    /* 0x01F8 */ s32 unk_1F8;
    /* 0x01FC */ u8 unk_1FC;
    /* 0x01FD */ char unk_1FD[0x3];
} EnOsn; // size = 0x200

extern const ActorInit En_Osn_InitVars;

#endif // Z_EN_OSN_H
