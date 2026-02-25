#ifndef Z_EN_INSECT_H
#define Z_EN_INSECT_H

#include "global.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

struct EnInsect;

typedef void (*EnInsectActionFunc)(struct EnInsect*, PlayState*);

#define INSECT_FLAG_0 (1 << 0)
#define INSECT_FLAG_1 (1 << 1)
#define INSECT_FLAG_IS_SHORT_LIVED (1 << 2)
#define INSECT_FLAG_UNCATCHABLE (1 << 3) // Set when the bug is about to disappear and can no longer be caught.
#define INSECT_FLAG_FOUND_SOIL (1 << 4)
#define INSECT_FLAG_SOIL_CLOSE (1 << 5)
#define INSECT_FLAG_DROPPED_HAS_LANDED (1 << 6) // Set when the landing sound has been played.
#define INSECT_FLAG_7 (1 << 7)
#define INSECT_FLAG_CRAWLING (1 << 8)

#define ENINSECT_GET_1(thisx) ((thisx)->params & 1)

#define ENINSECT_PARAMS(param) (param)

typedef struct EnInsect {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderJntSph collider;
    /* 0x164 */ ColliderJntSphElement colliderElements[1];
    /* 0x1A4 */ SkelAnime skelAnime;
    /* 0x1E8 */ Vec3s jointTable[BUG_LIMB_MAX];
    /* 0x278 */ Vec3s morphTable[BUG_LIMB_MAX];
    /* 0x308 */ EnInsectActionFunc actionFunc;
    /* 0x30C */ u16 insectFlags;
    /* 0x30E */ s16 unk_30E;
    /* 0x310 */ s16 unk_310;
    /* 0x312 */ s16 actionTimer;
    /* 0x314 */ s16 lifeTimer;
    /* 0x316 */ s16 crawlSoundDelay;
} EnInsect; // size = 0x318

#endif // Z_EN_INSECT_H
