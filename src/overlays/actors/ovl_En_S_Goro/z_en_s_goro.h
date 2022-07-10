#ifndef Z_EN_S_GORO_H
#define Z_EN_S_GORO_H

#include "global.h"
#include "objects/object_oF1d_map/object_oF1d_map.h"

#define EN_S_GORO_GET_MAIN_TYPE(thisx) ((thisx)->params & 0xF)
#define EN_S_GORO_SCENEFLAG_INDEX(thisx) (((thisx)->params & 0x7F0) >> 4)

#define EN_S_GORO_ROLLEDUP_YOFFSET 14.0f

#define ENSGORO_ACTIONFLAG_ROLLEDUP (1 << 0)
#define ENSGORO_ACTIONFLAG_FACEPLAYER (1 << 1)
#define ENSGORO_ACTIONFLAG_EYESOPEN (1 << 2)
#define ENSGORO_ACTIONFLAG_EARSCOVERED (1 << 3)
#define ENSGORO_ACTIONFLAG_ENGAGED (1 << 4)
#define ENSGORO_ACTIONFLAG_LASTMESSAGE (1 << 5)
#define ENSGORO_ACTIONFLAG_GKQUIET_ACKNOWLEDGED (1 << 6)
#define ENSGORO_ACTIONFLAG_SNOREPHASE (1 << 7)
#define ENSGORO_ACTIONFLAG_UNK0100 (1 << 8)
#define ENSGORO_ACTIONFLAG_HANDTAP (1 << 9)
#define ENSGORO_ACTIONFLAG_TIRED (1 << 10)
#define ENSGORO_ACTIONFLAG_SUPPRESS_SNORE (1 << 11)

#define ENSGORO_BOMBBUYFLAG_TALKED_HUMAN (1 << 0)
#define ENSGORO_BOMBBUYFLAG_TALKED_GORONPK (1 << 1)
#define ENSGORO_BOMBBUYFLAG_TALKED_DEKU (1 << 2)
#define ENSGORO_BOMBBUYFLAG_TALKED_ZORA (1 << 3)
#define ENSGORO_BOMBBUYFLAG_TALKED_HUMAN_FINALNIGHT (1 << 4)
#define ENSGORO_BOMBBUYFLAG_TALKED_GOROKPK_FINALNIGHT (1 << 5)
#define ENSGORO_BOMBBUYFLAG_TALKED_DEKU_FINALNIGHT (1 << 6)
#define ENSGORO_BOMBBUYFLAG_TALKED_ZORA_FINALNIGHT (1 << 7)
#define ENSGORO_BOMBBUYFLAG_TALKED_GORON (1 << 8)
#define ENSGORO_BOMBBUYFLAG_TALKED_GORON_FINALNIGHT (1 << 9)
#define ENSGORO_BOMBBUYFLAG_YESBUY (1 << 10)

struct EnSGoro;

typedef void (*EnSGoroActionFunc)(struct EnSGoro*, PlayState*);

extern const ActorInit En_S_Goro_InitVars;

typedef struct EnSGoro {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ Actor* otherGoron;
    /* 0x0148 */ SkelAnime skelAnime;
    /* 0x018C */ EnSGoroActionFunc actionFunc;
    /* 0x0190 */ ColliderCylinder collider;
    /* 0x01DC */ u16 actionFlags;
    /* 0x01DE */ u16 bombbuyFlags;
    /* 0x01E0 */ UNK_TYPE1 unk_1E0[0xC]; //No idea what this is.
    /* 0x01EC */ s16 eyeTexIndex;
    /* 0x01EE */ s16 eyeTimer;
    /* 0x01F0 */ s16 frameTimer; //Counter?. Used in transformLimbDraw to determine first bool to pass to F298
    /* 0x01F4 */ s32 loadedObjIndex;
    /* 0x01F8 */ Vec3s jointTable[GORON_LIMB_MAX];
    /* 0x0264 */ Vec3s morphTable[GORON_LIMB_MAX];
    /* 0x02D0 */ f32 scaleFactor;
    /* 0x02D4 */ s16 headRotZ; //transformLimbDraw, head
    /* 0x02D6 */ s16 headRotY; //transformLimbDraw, head
    /* 0x02D8 */ s16 bodyRotZ; //transformLimbDraw, head, body
    /* 0x02DA */ s16 bodyRotY; //transformLimbDraw, body
    /* 0x02DC */ Vec3f headTranslate; //transformLimbDraw, head
    /* 0x02E8 */ Vec3s headRotate; //transformLimbDraw, head
    /* 0x02F0 */ Vec3f bodyTranslate; //transformLimbDraw, body
    /* 0x02FC */ Vec3s bodyRotate; //transformLimbDraw, body
	/* 0x0302 */ UNK_TYPE2 unk_302; //Probably padding
    /* 0x0304 */ u16 textID;
    /* 0x0306 */ s16 snorePhase;
    /* 0x0308 */ s32 animInfoIndex;
    /* 0x030C */ s16 powderKegPrice;
} EnSGoro; // size = 0x310

typedef enum EnSGoro_Type{
	ENSGORO_TYPE_SHRINE_WINTER_A,
	ENSGORO_TYPE_SHRINE_WINTER_B,
	ENSGORO_TYPE_SHRINE_WINTER_C,
	ENSGORO_TYPE_SHRINE_SPRING_A,
	ENSGORO_TYPE_SHRINE_SPRING_B,
	ENSGORO_TYPE_SHRINE_SPRING_C,
	ENSGORO_TYPE_SHRINE_SPRING_D,
	ENSGORO_TYPE_SHRINE_SPRING_E,
	ENSGORO_TYPE_SHRINE_SPRING_F,
	ENSGORO_TYPE_BOMBSHOP,
} EnSGoro_Type;

typedef enum EnSGoro_EyeTexture{
	ENSGORO_EYETEX_OPEN,
	ENSGORO_EYETEX_HALF,
	ENSGORO_EYETEX_CLOSED,
	ENSGORO_EYETEX_CLOSED2,
} EnSGoro_EyeTexture;

typedef enum EnSGoro_Animation{
	ENSGORO_ANIM_IDLE_LIEDOWN_A,
	ENSGORO_ANIM_IDLE_LIEDOWN_B,
	ENSGORO_ANIM_UNROLL_A,
	ENSGORO_ANIM_UNROLL_B,
	ENSGORO_ANIM_ROLLUP,
	ENSGORO_ANIM_SHIVER_A,
	ENSGORO_ANIM_SHIVER_B,
	ENSGORO_ANIM_COVEREARS = 11,
	ENSGORO_ANIM_TAISOU_CHEER,
	ENSGORO_ANIM_STAND_HANDTAP,
	ENSGORO_ANIM_SLEEPY,
	ENSGORO_ANIM_IDLE_STAND,
} EnSGoro_Animation;

#endif // Z_EN_S_GORO_H
