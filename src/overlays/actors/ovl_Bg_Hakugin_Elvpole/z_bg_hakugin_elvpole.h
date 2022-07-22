#ifndef Z_BG_HAKUGIN_ELVPOLE_H
#define Z_BG_HAKUGIN_ELVPOLE_H

#include "global.h"

struct BgHakuginElvpole;

typedef void (*BgHakuginElvpoleActionFunc)(struct BgHakuginElvpole*, PlayState*);

typedef struct BgHakuginElvpole {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ s16 unk_15C;                         /* inferred */
    /* 0x15E */ s16 unk_15E;                         /* inferred */
    /* 0x160 */ u16 unk_160;                         /* inferred */
    /* 0x162 */ UNK_TYPE1 pad_162[2];
    /* 0x164 */ BgHakuginElvpoleActionFunc actionFunc;
} BgHakuginElvpole; // size = 0x168

extern const ActorInit Bg_Hakugin_Elvpole_InitVars;

#define BGHAKUGINELVPOLE_GET_SWITCHFLAG(thisx) ((thisx)->params & 0x7F)

#endif // Z_BG_HAKUGIN_ELVPOLE_H
