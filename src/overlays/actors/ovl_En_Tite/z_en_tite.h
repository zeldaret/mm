#ifndef Z_EN_TITE_H
#define Z_EN_TITE_H

#include "global.h"

struct EnTite;

typedef void (*EnTiteActionFunc)(struct EnTite*, PlayState*);

enum {
    /* -4 */ ENTITE_MINUS_4 = -4,
    /* -3 */ ENTITE_MINUS_3,
    /* -2 */ ENTITE_MINUS_2,
    /* -1 */ ENTITE_MINUS_1,
    /*  0 */ ENTITE_MINUS_0,
};

typedef struct EnTite {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[25];
    /* 0x21E */ Vec3s morphTable[25];
    /* 0x2B4 */ EnTiteActionFunc actionFunc;
    /* 0x2B8 */ u8 unk_2B8;
    /* 0x2B9 */ u8 unk_2B9;
    /* 0x2BA */ s8 unk_2BA;
    /* 0x2BB */ u8 drawDmgEffType;
    /* 0x2BC */ s16 unk_2BC;
    /* 0x2BE */ s16 unk_2BE;
    /* 0x2C0 */ s32 unk_2C0;
    /* 0x2C4 */ f32 drawDmgEffAlpha;
    /* 0x2C8 */ f32 drawDmgEffScale;
    /* 0x2CC */ f32 drawDmgEffFrozenSteamScale;
    /* 0x2D0 */ Vec3f limbPos[9];
    /* 0x33C */ Vec3f unk_33C[9];
    /* 0x3A8 */ Gfx* unk_3A8;
    /* 0x3AC */ ColliderSphere collider;
} EnTite; // size = 0x404

extern const ActorInit En_Tite_InitVars;

#endif // Z_EN_TITE_H
