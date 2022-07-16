#ifndef Z_BG_DY_YOSEIZO_H
#define Z_BG_DY_YOSEIZO_H

#include "global.h"
#include "overlays/actors/ovl_En_Dy_Extra/z_en_dy_extra.h"


struct BgDyYoseizo;

typedef void (*BgDyYoseizoActionFunc)(struct BgDyYoseizo*, PlayState*);

#define GREAT_FAIRY_GET_SWITCHFLAG(thisx) (((thisx)->params & 0xFE00) >> 9)
#define GREAT_FAIRY_GET_TYPE(thisx) ((thisx)->params & 0xF)

typedef enum {
    /* 0 */ GREAT_FAIRY_TYPE_0,
    /* 1 */ GREAT_FAIRY_TYPE_1,
    /* 2 */ GREAT_FAIRY_TYPE_2,
    /* 3 */ GREAT_FAIRY_TYPE_3,
    /* 4 */ GREAT_FAIRY_TYPE_4
} 

#define BG_DY_YOSEIZO_EFFECT_COUNT 200

typedef struct {
    /* 0x00 */ u8 alive; // drawn if 1, respawn if 0
    /* 0x04 */ Vec3f pos;
    /* 0x10 */ Vec3f velocity;
    /* 0x1C */ Vec3f accel;
    /* 0x28 */ Color_RGB8 primColor;
    /* 0x2B */ Color_RGB8 envColor;
    /* 0x2E */ s16 alpha;
    /* 0x30 */ f32 scale;
    /* 0x34 */ s16 timer; // lifetime
    /* 0x36 */ s16 type; // 0 is general radiance, else is directed towards Player
    /* 0x38 */ s16 pitch;
    /* 0x3A */ s16 yaw;
    /* 0x3C */ s16 roll; // all three are f32 in OoT
} BgDyYoseizoEffect; // size = 0x40

typedef struct BgDyYoseizo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ BgDyYoseizoActionFunc actionFunc;
    /* 0x0148 */ SkelAnime skelAnime;
    /* 0x018C */ Vec3s jointTable[28];
    /* 0x0234 */ Vec3s morphTable[28];
    /* 0x02DC */ Vec3s unk2DC;
    /* 0x02DC */ Vec3s unk2E2;
    /* 0x02E8 */ EnDyExtra* unk2E8;
    /* 0x02EC */ f32 unk2EC;
    /* 0x02F0 */ f32 unk2F0;
    /* 0x02F4 */ f32 unk2F4;
    /* 0x02F8 */ s16 unk2F8;
    /* 0x02FA */ s16 eyeIndex;
    /* 0x02FC */ s16 mouthIndex;
    /* 0x02FE */ s16 blinkTimer;
    /* 0x0300 */ s16 timer;
    /* 0x0302 */ u16 unk302;
    /* 0x0304 */ BgDyYoseizoEffect effects[200];
} BgDyYoseizo; // size = 0x3504

extern const ActorInit Bg_Dy_Yoseizo_InitVars;

#endif // Z_BG_DY_YOSEIZO_H
