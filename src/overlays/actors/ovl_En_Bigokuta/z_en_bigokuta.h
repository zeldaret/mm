#ifndef Z_EN_BIGOKUTA_H
#define Z_EN_BIGOKUTA_H

#include "global.h"

struct EnBigokuta;

typedef void (*EnBigokutaActionFunc)(struct EnBigokuta*, GlobalContext*);
typedef void (*SomeFunc)(GlobalContext* globalCtx, Actor* this);

typedef struct EnBigokuta {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SomeFunc unk_144;
    /* 0x0148 */ SkelAnime skelAnime;
    /* 0x018C */ EnBigokutaActionFunc actionFunc;
    /* 0x0190 */ u8 unk_190;
    /* 0x0191 */ u8 unk_191;
    /* 0x0192 */ s16 unk_192; // transparent or not,scale?
    /* 0x0194 */ s16 unk_194; // camera id
    /* 0x0196 */ s16 cutscene;
    /* 0x0198 */ Vec3s jointTable[20];
    /* 0x0210 */ Vec3s morphTable[20];
    /* 0x0288 */ Vec3f unk_288;
    /* 0x0294 */ Vec3f unk_294; // pos player is sent to
    /* 0x02A0 */ Vec3f unk_2A0; // pos to return player to?
    /* 0x02AC */ Vec3f unk_2AC; // camera at
    /* 0x02B8 */ Vec3f unk_2B8; // camera eye
    /* 0x02C4 */ Vec3f limbPos[13];
    /* 0x0360 */ ColliderCylinder collider1;
    /* 0x03AC */ ColliderCylinder collider2;
} EnBigokuta; // size = 0x3F8

extern const ActorInit En_Bigokuta_InitVars;

#endif // Z_EN_BIGOKUTA_H
