#ifndef Z_EN_S_GORO_H
#define Z_EN_S_GORO_H

#include "global.h"
#include "objects/object_oF1d_map/object_oF1d_map.h"

#define EN_S_GORO_GET_MAIN_TYPE(thisx) ((thisx)->params & 0xF)
#define EN_S_GORO_SCENEFLAG_INDEX(thisx) (((thisx)->params & 0x7F0) >> 4)

#define EN_S_GORO_ACTIONFLAG_ROLLEDUP (1 << 0)
#define EN_S_GORO_ACTIONFLAG_FACEPLAYER (1 << 1)
#define EN_S_GORO_ACTIONFLAG_EYESOPEN (1 << 2)
#define EN_S_GORO_ACTIONFLAG_EARSCOVERED (1 << 3)
#define EN_S_GORO_ACTIONFLAG_ENGAGED (1 << 4)
#define EN_S_GORO_ACTIONFLAG_LASTMESSAGE (1 << 5)
#define EN_S_GORO_ACTIONFLAG_GKQUIET_ACKNOWLEDGED (1 << 6)
#define EN_S_GORO_ACTIONFLAG_SNOREPHASE (1 << 7)
#define EN_S_GORO_ACTIONFLAG_UNK0100 (1 << 8)
#define EN_S_GORO_ACTIONFLAG_HANDTAP (1 << 9)
#define EN_S_GORO_ACTIONFLAG_TIRED (1 << 10)
#define EN_S_GORO_ACTIONFLAG_SUPPRESS_SNORE (1 << 11)

#define EN_S_GORO_BOMBBUYFLAG_TALKED_HUMAN (1 << 0)
#define EN_S_GORO_BOMBBUYFLAG_TALKED_GORONPK (1 << 1)
#define EN_S_GORO_BOMBBUYFLAG_TALKED_DEKU (1 << 2)
#define EN_S_GORO_BOMBBUYFLAG_TALKED_ZORA (1 << 3)
#define EN_S_GORO_BOMBBUYFLAG_TALKED_HUMAN_FINALNIGHT (1 << 4)
#define EN_S_GORO_BOMBBUYFLAG_TALKED_GOROKPK_FINALNIGHT (1 << 5)
#define EN_S_GORO_BOMBBUYFLAG_TALKED_DEKU_FINALNIGHT (1 << 6)
#define EN_S_GORO_BOMBBUYFLAG_TALKED_ZORA_FINALNIGHT (1 << 7)
#define EN_S_GORO_BOMBBUYFLAG_TALKED_GORON (1 << 8)
#define EN_S_GORO_BOMBBUYFLAG_TALKED_GORON_FINALNIGHT (1 << 9)
#define EN_S_GORO_BOMBBUYFLAG_YESBUY (1 << 10)

struct EnSGoro;

typedef void (*EnSGoroActionFunc)(struct EnSGoro*, PlayState*);

extern const ActorInit En_S_Goro_InitVars;

typedef struct EnSGoro {
    /* 0x000 */ Actor actor;
    /* 0x144 */ Actor* otherGoron;
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ EnSGoroActionFunc actionFunc;
    /* 0x190 */ ColliderCylinder collider;
    /* 0x1DC */ u16 actionFlags;
    /* 0x1DE */ u16 bombbuyFlags;
    /* 0x1E0 */ UNK_TYPE1 unk_1E0[0xC]; //No idea what this is.
    /* 0x1EC */ s16 eyeTexIndex;
    /* 0x1EE */ s16 eyeTimer;
    /* 0x1F0 */ s16 loseAttentionTimer;
    /* 0x1F4 */ s32 loadedObjIndex;
    /* 0x1F8 */ Vec3s jointTable[GORON_LIMB_MAX];
    /* 0x264 */ Vec3s morphTable[GORON_LIMB_MAX];
    /* 0x2D0 */ f32 scaleFactor;
    /* 0x2D4 */ s16 headRotZ;
    /* 0x2D6 */ s16 headRotY;
    /* 0x2D8 */ s16 bodyRotZ;
    /* 0x2DA */ s16 bodyRotY;
    /* 0x2DC */ Vec3f headTranslate;
    /* 0x2E8 */ Vec3s headRotate;
    /* 0x2F0 */ Vec3f bodyTranslate;
    /* 0x2FC */ Vec3s bodyRotate;
    /* 0x302 */ UNK_TYPE2 unk_302; //Probably padding
    /* 0x304 */ u16 textID;
    /* 0x306 */ s16 snorePhase;
    /* 0x308 */ s32 animInfoIndex;
    /* 0x30C */ s16 powderKegPrice;
} EnSGoro; // size = 0x310

typedef enum EnSGoro_Type{
	/* 0x0 */ EN_S_GORO_TYPE_SHRINE_WINTER_A,
	/* 0x1 */ EN_S_GORO_TYPE_SHRINE_WINTER_B,
	/* 0x2 */ EN_S_GORO_TYPE_SHRINE_WINTER_C,
	/* 0x3 */ EN_S_GORO_TYPE_SHRINE_SPRING_A,
	/* 0x4 */ EN_S_GORO_TYPE_SHRINE_SPRING_B,
	/* 0x5 */ EN_S_GORO_TYPE_SHRINE_SPRING_C,
	/* 0x6 */ EN_S_GORO_TYPE_SHRINE_SPRING_D,
	/* 0x7 */ EN_S_GORO_TYPE_SHRINE_SPRING_E,
	/* 0x8 */ EN_S_GORO_TYPE_SHRINE_SPRING_F,
	/* 0x9 */ EN_S_GORO_TYPE_BOMBSHOP,
} EnSGoroType;

#endif // Z_EN_S_GORO_H
