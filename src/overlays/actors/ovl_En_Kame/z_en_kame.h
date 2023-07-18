#ifndef Z_EN_KAME_H
#define Z_EN_KAME_H

#include "global.h"

struct EnKame;

typedef void (*EnKameActionFunc)(struct EnKame*, PlayState*);

typedef enum Tl2BodyPart {
    /*  0 */ TL_2_BODYPART_0,
    /*  1 */ TL_2_BODYPART_1,
    /*  2 */ TL_2_BODYPART_2,
    /*  3 */ TL_2_BODYPART_3,
    /*  4 */ TL_2_BODYPART_4,
    /*  5 */ TL_2_BODYPART_5,
    /*  6 */ TL_2_BODYPART_6,
    /*  7 */ TL_2_BODYPART_7,
    /*  8 */ TL_2_BODYPART_8,
    /*  9 */ TL_2_BODYPART_9,
    /* 10 */ TL_2_BODYPART_MAX
} Tl2BodyPart;

typedef struct EnKame {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime1;
    /* 0x188 */ Vec3s jointTable1[13];
    /* 0x1D6 */ Vec3s morphTable1[13];
    /* 0x224 */ SkelAnime skelAnime2;
    /* 0x268 */ Vec3s jointTable2[4];
    /* 0x280 */ Vec3s morphTable2[4];
    /* 0x298 */ EnKameActionFunc actionFunc;
    /* 0x29C */ u8 unk_29C;
    /* 0x29D */ u8 drawDmgEffType;
    /* 0x29E */ s16 unk_29E;
    /* 0x2A0 */ s16 unk_2A0;
    /* 0x2A2 */ s16 unk_2A2;
    /* 0x2A4 */ s16 unk_2A4;
    /* 0x2A6 */ s16 unk_2A6;
    /* 0x2A8 */ f32 unk_2A8;
    /* 0x2AC */ f32 unk_2AC;
    /* 0x2B0 */ f32 drawDmgEffAlpha;
    /* 0x2B4 */ f32 drawDmgEffScale;
    /* 0x2B8 */ f32 drawDmgEffFrozenSteamScale;
    /* 0x2BC */ Vec3f unk_2BC;
    /* 0x2C8 */ Vec3f bodyPartsPos[TL_2_BODYPART_MAX];
    /* 0x340 */ ColliderCylinder collider;
} EnKame; // size = 0x38C

#endif // Z_EN_KAME_H
