#ifndef Z_EN_TITE_H
#define Z_EN_TITE_H

#include "global.h"

struct EnTite;

typedef void (*EnTiteActionFunc)(struct EnTite*, GlobalContext*);

enum {
    /* -4 */ ENTITE_MINUS_4 = -4,
    /* -3 */ ENTITE_MINUS_3,
    /* -2 */ ENTITE_MINUS_2,
    /* -1 */ ENTITE_MINUS_1,
    /*  0 */ ENTITE_MINUS_0,
};

typedef struct EnTite {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[25];
    /* 0x021E */ Vec3s morphTable[25];
    /* 0x02B4 */ EnTiteActionFunc actionFunc;
    /* 0x02B8 */ u8 unk_2B8;
    /* 0x02B9 */ u8 unk_2B9;
    /* 0x02BA */ s8 unk_2BA;
    /* 0x02BB */ u8 drawDmgEffType;
    /* 0x02BC */ s16 unk_2BC;
    /* 0x02BE */ s16 unk_2BE;
    /* 0x02C0 */ s32 unk_2C0;
    /* 0x02C4 */ f32 drawDmgEffAlpha;
    /* 0x02C8 */ f32 drawDmgEffScale;
    /* 0x02CC */ f32 drawDmgEffFrozenSteamScale;
    /* 0x02D0 */ Vec3f limbPos[9];
    /* 0x033C */ Vec3f unk_33C[9];
    /* 0x03A8 */ Gfx* unk_3A8;
    /* 0x03AC */ ColliderSphere collider;
} EnTite; // size = 0x404

extern const ActorInit En_Tite_InitVars;

#endif // Z_EN_TITE_H
