#ifndef Z_EN_WARP_TAG_H
#define Z_EN_WARP_TAG_H

#include "global.h"

struct EnWarptag;

typedef void (*EnWarptagActionFunc)(struct EnWarptag*, GlobalContext*);

typedef struct EnWarptag {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ s8 dangeonKeepObject;
    /* 0x15E */ union {
                    s16 reusedValue;      // default name
                    s16 unkValue15E;      // passed to unk play func, mods player rotation, stepped to 0x2710
                    s16 grottoExitDelay;  // 10 frame delay before player can leave the grotto
                };
    /* 0x160 */ EnWarptagActionFunc actionFunc;
} EnWarptag; // size = 0x164

extern const ActorInit En_Warp_tag_InitVars;

// Only two known Variants:
//  Goron Trial (MOON):    0x03C1
//  Deku Playground:       0x83C0

#define GET_WARPTAG_3C0_MAX(thisx) ((thisx)->params & 0x3C0)
#define GET_WARPTAG_3C0(thisx) (((thisx)->params >> 6) & 0xF)
#define GET_WARPTAG_EXIT_INDEX(thisx) ((thisx)->params & 0x3F)
#define GET_WARPTAG_INVISIBLE(thisx) ((thisx)->params < 0) // 0x8000 flag

#define WARPTAG_3C0_MAX 0x3C0

#endif // Z_EN_WARP_TAG_H
