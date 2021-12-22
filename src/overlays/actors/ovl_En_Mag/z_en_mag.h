#ifndef Z_EN_MAG_H
#define Z_EN_MAG_H

#include "global.h"

struct EnMag;

// typedef struct EnMag {
//     /* 0x00000 */ Actor actor;
//     /* 0x00144 */ char unk_00144[0x11E34];
// } EnMag; // size = 0x11F78

typedef struct EnMag {
    /* 0x00000 */ Actor actor;
    /* 0x00144 */ char pad144[0x2C];
    /* 0x00170 */ Font font;
    /* 0x11EFC */ char pad11EFC[4];
    /* 0x11F00 */ s16 unk11F00;
    /* 0x11F02 */ s16 unk11F02;
    /* 0x11F04 */ s16 unk11F04;
    /* 0x11F06 */ s16 unk11F06; // effectPrimLodFrac in OoT
    /* 0x11F08 */ s16 unk11F08[3]; // This may be two arrays of 3: it is prim/env for effects
    /* 0x11F08 */ s16 unk11F0E[3]; // This may be two arrays of 3: it is prim/env for effects
    /* 0x11F14 */ s16 unk11F14; // effectAlpha in OoT
    /* 0x11F16 */ s16 unk11F16;
    /* 0x11F18 */ s16 unk11F18[3]; // Might be 2 arrays of 3: anothre prim/env
    /* 0x11F18 */ s16 unk11F1E[3]; // Might be 2 arrays of 3: anothre prim/env
    /* 0x11F24 */ s16 unk11F24;
    /* 0x11F26 */ s16 unk11F26; // mainAlpha in OoT?
    /* 0x11F28 */ s16 unk11F28[3]; // mmAlpha
    // /* 0x11F2A */ s16 unk11F2A;
    // /* 0x11F2C */ s16 unk11F2C;
    /* 0x11F2E */ s16 unk11F2E; // mainAlpha in OoT?
    /* 0x11F30 */ s16 unk11F30; // Alpha of flame effect mask
    /* 0x11F32 */ s16 unk11F32;
    /* 0x11F34 */ s16 unk11F34; // Copyright alpha etc.
    /* 0x11F36 */ s16 unk11F36[6];
    /* 0x11F42 */ char pad11F42[2];
    /* 0x11F44 */ s16 unk11F44[6];
    /* 0x11F50 */ char pad11F50[4];
    /* 0x11F54 */ s16 unk11F54;
    /* 0x11F56 */ s16 unk11F56;
    /* 0x11F58 */ s16 unk11F58;
    /* 0x11F5A */ s16 unk11F5A;
    /* 0x11F5C */ s32 unk11F5C;
    /* 0x11F60 */ s32 unk11F60;
    /* 0x11F64 */ s16 unk11F64;
    /* 0x11F66 */ s16 unk11F66;
    /* 0x11F68 */ s16 unk11F68;
    /* 0x11F6A */ s16 unk11F6A;
    /* 0x11F6C */ s16 unk11F6C;
    /* 0x11F6E */ s16 unk11F6E;
    /* 0x11F70 */ s16 unk11F70;
    /* 0x11F72 */ s16 unk11F72;
    /* 0x11F74 */ char pad11F74[4];
} EnMag;                                            /* size = 0x11F78 */

extern const ActorInit En_Mag_InitVars;

#endif // Z_EN_MAG_H
