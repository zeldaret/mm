#ifndef Z_EN_THIEFBIRD_H
#define Z_EN_THIEFBIRD_H

#include "global.h"

struct EnThiefbird;

typedef void (*EnThiefbirdActionFunc)(struct EnThiefbird*, GlobalContext*);

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
} EnThiefbirdUnkStruct; // size = 0x24

typedef struct EnThiefbird {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnThiefbirdActionFunc actionFunc;
    /* 0x018C */ u8 drawDmgEffType;
    /* 0x018E */ s16 unk_18E;
    /* 0x0190 */ s16 unk_190;
    /* 0x0192 */ s16 unk_192;
    /* 0x0194 */ s16 unk_194;
    /* 0x0196 */ s16 unk_196[6];
    /* 0x01A2 */ Vec3s jointTable[17];
    /* 0x0208 */ Vec3s morphTable[17];
    /* 0x0270 */ ColliderJntSph collider;
    /* 0x0290 */ ColliderJntSphElement colliderElements[3];
    /* 0x0350 */ Vec3f limbPos[11];
    /* 0x03D4 */ f32 drawDmgEffAlpha;
    /* 0x03D8 */ f32 drawDmgEffScale;
    /* 0x03DC */ f32 drawDmgEffFrozenSteamScale;
    /* 0x03E0 */ f32 unk_3E0;
    /* 0x03E4 */ Gfx* unk_3E4;
    /* 0x03E8 */ Gfx* unk_3E8;
    /* 0x03EC */ EnItem00* unk_3EC;
    /* 0x03F0 */ EnThiefbirdUnkStruct unk_3F0[40];
} EnThiefbird; // size = 0x990

extern const ActorInit En_Thiefbird_InitVars;

#endif // Z_EN_THIEFBIRD_H
