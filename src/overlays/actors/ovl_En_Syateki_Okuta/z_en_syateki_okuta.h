#ifndef Z_EN_SYATEKI_OKUTA_H
#define Z_EN_SYATEKI_OKUTA_H

#include "global.h"
#include "objects/object_okuta/object_okuta.h"

#define EN_SYATEKI_OKUTA_GET_F(thisx) ((thisx)->params & 0xF)

struct EnSyatekiOkuta;

typedef void (*EnSyatekiOkutaActionFunc)(struct EnSyatekiOkuta*, PlayState*);

typedef struct EnSyatekiOkuta {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnSyatekiOkutaActionFunc actionFunc;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1DC */ Vec3f headScale;
    /* 0x1E4 */ Vec3s jointTable[OCTOROK_LIMB_MAX];
    /* 0x244 */ Vec3s morphTable[OCTOROK_LIMB_MAX];
    /* 0x2A4 */ s16 unk_2A4; // timer?
    /* 0x2A6 */ s16 unk_2A6; // color?
    /* 0x2A8 */ UNK_TYPE1 unk_2A8[0x2];
    /* 0x2AA */ s16 unk_2AA; // alpha (for circle or cross)
} EnSyatekiOkuta; // size = 0x2AC

#endif // Z_EN_SYATEKI_OKUTA_H
