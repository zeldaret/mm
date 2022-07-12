#ifndef Z_EN_OSN_H
#define Z_EN_OSN_H

#include "global.h"

struct EnOsn;

typedef void (*EnOsnActionFunc)(struct EnOsn*, PlayState*);

typedef struct EnOsn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ SkelAnime skelAnime;
    /* 0x1D4 */ EnOsnActionFunc actionFunc;
    /* 0x1D8 */ Vec3s unk_1D8;
    /* 0x1DE */ Vec3s unk_1DE;
    /* 0x1E4 */ UNK_TYPE1 unk_1E4[0x6];
    /* 0x1EA */ u16  unk_1EA;
    /* 0x1EC */ u8 unk_1EC;
    /* 0x1ED */ u8 unk_1ED;
    /* 0x1EE */ s16 cutscene;
    /* 0x1F0 */ u8 unk_1F0;
    /* 0x1F1 */ UNK_TYPE1 unk_1F1[0x3];
    /* 0x1F4 */ u16 unk_1F4;
    /* 0x1F6 */ s32 unk_1F6;
    /* 0x1FA */ u8 unk_1FA;
} EnOsn; // size = 0x1FB

extern const ActorInit En_Osn_InitVars;

#define ENOSN_GET_3(this) ((thisx)->params & 3) 

#endif // Z_EN_OSN_H
