#ifndef Z_BG_HAKUGIN_SWITCH_H
#define Z_BG_HAKUGIN_SWITCH_H

#include "global.h"

struct BgHakuginSwitch;

typedef void (*BgHakuginSwitchActionFunc)(struct BgHakuginSwitch*, GlobalContext*);
typedef void (*BgHakuginSwitchUnkFunc)(struct BgHakuginSwitch*, GlobalContext*);

#define BGHAKUGINSWITCH_GET_7(thisx) ((thisx)->params & 7)
#define BGHAKUGINSWITCH_GET_10(thisx) (((thisx)->params >> 4) & 1)
#define BGHAKUGINSWITCH_GET_SWITCHFLAG(thisx) (((thisx)->params >> 8) & 0x7F)

#define BGHAKUGINSWITCH_GET_7_1 1

typedef struct BgHakuginSwitch {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ ColliderCylinder collider;
    /* 0x01A8 */ Gfx* unk_1A8;
    /* 0x01AC */ BgHakuginSwitchActionFunc actionFunc;
    /* 0x01B0 */ s16 unk_1B0;
    /* 0x01B2 */ s8 unk_1B2;
    /* 0x01B4 */ BgHakuginSwitchUnkFunc unk_1B4;
    /* 0x01B8 */ s16 unk_1B8;
    /* 0x01BA */ s16 unk_1BA;
    /* 0x01BC */ s16 unk_1BC;
    /* 0x01BE */ s8 unk_1BE;
    /* 0x01BF */ s8 unk_1BF;
    /* 0x01C0 */ s8 unk_1C0;
    /* 0x01C4 */ f32 unk_1C4;
    /* 0x01C8 */ f32 unk_1C8;
} BgHakuginSwitch; // size = 0x1CC

extern const ActorInit Bg_Hakugin_Switch_InitVars;

#endif // Z_BG_HAKUGIN_SWITCH_H
