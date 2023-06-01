#ifndef Z_EN_SYATEKI_OKUTA_H
#define Z_EN_SYATEKI_OKUTA_H

#include "global.h"
#include "objects/object_okuta/object_okuta.h"

typedef enum {
    /* 0 */ SG_OCTO_TYPE_NONE,
    /* 1 */ SG_OCTO_TYPE_RED,
    /* 2 */ SG_OCTO_TYPE_BLUE,
} ShootingGalleryOctorokType;

typedef enum {
    /* 0 */ SG_OCTO_ROW_BACK,
    /* 1 */ SG_OCTO_ROW_CENTER,
    /* 2 */ SG_OCTO_ROW_FRONT,
} ShootingGalleryOctorokRow;

typedef enum {
    /* 0 */ SG_OCTO_COL_LEFT,
    /* 1 */ SG_OCTO_COL_CENTER,
    /* 2 */ SG_OCTO_COL_RIGHT,
} ShootingGalleryOctorokColumn;

#define SG_OCTO_GET_INDEX(thisx) ((thisx)->params & 0xF)
#define SG_OCTO_GET_TYPE(octorokFlags, index) (((octorokFlags) >> ((index) * 2)) & 3)
#define SG_OCTO_INDEX_FOR_POS(row, column) (((row) * 3) + (column))
#define SG_OCTO_INDEX_DIRECTLY_IN_FRONT(index) ((index) + 3)

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
    /* 0x2A4 */ s16 deathTimer;
    /* 0x2A6 */ s16 type;
    /* 0x2A8 */ UNK_TYPE1 unk_2A8[0x2];
    /* 0x2AA */ s16 circleOrCrossAlpha;
} EnSyatekiOkuta; // size = 0x2AC

#endif // Z_EN_SYATEKI_OKUTA_H
