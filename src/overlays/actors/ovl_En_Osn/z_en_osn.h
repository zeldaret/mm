#ifndef Z_EN_OSN_H
#define Z_EN_OSN_H

#include "global.h"

struct EnOsn;

typedef void (*EnOsnActionFunc)(struct EnOsn*, GlobalContext*);

typedef struct EnOsn {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0X0190 */ SkelAnime anime;
    /* 0x01D4 */ EnOsnActionFunc actionFunc;
    /* 0x01D8 */ char unk_1D8[0x12];
    /* 0x01EA */ u16  unk_1EA;
    /* 0x01EC */ u8 unk_1EC;
    /* 0x01ED */ u8 unk_1ED;
    /* 0x01EE */ s16 cutscene;
    /* 0x01F0 */ char unk_1F0[0x10];
} EnOsn; // size = 0x200

extern const ActorInit En_Osn_InitVars;

#endif // Z_EN_OSN_H
