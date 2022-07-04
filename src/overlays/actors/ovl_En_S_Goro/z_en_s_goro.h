#ifndef Z_EN_S_GORO_H
#define Z_EN_S_GORO_H

#include "global.h"

#define EN_S_GORO_GET_PARAM_F(thisx) ((thisx)->params & 0xF)

#define EN_S_GORO_COLLIDER_RADIUS 24.0f
#define EN_S_GORO_COLLIDER_HEIGHT 62.0f
#define EN_S_GORO_ROLLEDUP_YOFFSET 14.0f
#define EN_S_GORO_LIMBCOUNT 18

struct EnSGoro;

typedef void (*EnSGoroActionFunc)(struct EnSGoro*, PlayState*);

extern const ActorInit En_S_Goro_InitVars;

typedef struct EnSGoro {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ Actor* otherGoron;
    /* 0x0148 */ SkelAnime skelAnime;
    /* 0x018C */ EnSGoroActionFunc actionFunc;
    /* 0x0190 */ ColliderCylinder collider;
    /* 0x01dc */ u16 actionFlags;
    /* 0x01de */ u16 bombbuyFlags;
    /* 0x01e0 */ char unk_1e0[0xc]; //No idea what this is.
    /* 0x01ec */ s16 eyeTexIndex;
    /* 0x01ee */ s16 eyeTimer;
    /* 0x01f0 */ s16 frameTimer; //Counter?. Used in transformLimbDraw to determine first bool to pass to F298
    /* 0x01f2 */ char unk_1f2[0x2]; //Probably padding
    /* 0x01f4 */ s32 loadedObjIndex;
    /* 0x01f8 */ Vec3s jointTable[EN_S_GORO_LIMBCOUNT];
    /* 0x0264 */ Vec3s morphTable[EN_S_GORO_LIMBCOUNT];
    /* 0x02d0 */ f32 scaleFactor;
    /* 0x02d4 */ s16 headRotZ; //transformLimbDraw, head
    /* 0x02d6 */ s16 headRotY; //transformLimbDraw, head
    /* 0x02d8 */ s16 bodyRotZ; //transformLimbDraw, head, body
    /* 0x02da */ s16 bodyRotY; //transformLimbDraw, body
    /* 0x02dc */ Vec3f headTranslate; //transformLimbDraw, head
    /* 0x02e8 */ Vec3s headRotate; //transformLimbDraw, head
    /* 0x02ee */ char unk_2ee[0x2]; //Probably padding
    /* 0x02f0 */ Vec3f bodyTranslate; //transformLimbDraw, body
    /* 0x02fc */ Vec3s bodyRotate; //transformLimbDraw, body
    /* 0x0302 */ char unk_302[0x2]; //Probably padding
    /* 0x0304 */ u16 textID;
    /* 0x0306 */ s16 snorePhase;
    /* 0x0308 */ s32 animInfoIndex;
    /* 0x030c */ s16 powderKegPrice;
    /* 0x030e */ u16 unk_30e; //Probably padding
} EnSGoro; // size = 0x310

typedef enum EnSGoro_MessageId{
    EnSGoro_Msg_None = 0,
    EnSGoro_Msg_Asleep = 0x23A,
    EnSGoro_Msg_Shop_NonGoron_00 = 0x664,
    EnSGoro_Msg_Shop_NonGoron_01,
    EnSGoro_Msg_Shop_NonGoron_02,
    EnSGoro_Msg_Shop_NonGoron_03,
    EnSGoro_Msg_Shop_NonGoron_LastNight_00,
    EnSGoro_Msg_Shop_NonGoron_LastNight_01,
    EnSGoro_Msg_Shop_NonGoron_LastNight_02,
    EnSGoro_Msg_Shop_NonGoron_LastNight_03,
    EnSGoro_Msg_Shop_TalkAgain_NonGoron,
    EnSGoro_Msg_Shop_TalkAgain_NonGoron_LastNight,
    EnSGoro_Msg_Shop_Intro_GoronPK_00,
    EnSGoro_Msg_Shop_Intro_GoronPK_01,
    EnSGoro_Msg_Shop_GoronPK_Common,
    EnSGoro_Msg_Shop_GoronPK_NoBuy,
    EnSGoro_Msg_Shop_GoronPK_NoBuy_LastNight,
    EnSGoro_Msg_Shop_GoronPK_NoSpace,
    EnSGoro_Msg_Shop_GoronPK_TooPoor,
    EnSGoro_Msg_Shop_GoronPK_YesBuy,
    EnSGoro_Msg_Shop_GoronPK_YesBuy_LastNight,
    EnSGoro_Msg_Shop_Intro_GoronPK_LastNight_00,
    EnSGoro_Msg_Shop_Intro_GoronPK_LastNight_01,
    EnSGoro_Msg_Shop_TalkAgain_GoronPK,
    EnSGoro_Msg_Shop_TalkAgain_GoronPK_LastNight,
    EnSGoro_Msg_Shop_GoronNoPK_00,
    EnSGoro_Msg_Shop_GoronNoPK_01,
    EnSGoro_Msg_Shop_GoronNoPK_02,
    EnSGoro_Msg_Shop_GoronNoPK_LastNight_00,
    EnSGoro_Msg_Shop_GoronNoPK_LastNight_01,
    EnSGoro_Msg_Shop_GoronNoPK_LastNight_02,
    EnSGoro_Msg_Shop_TalkAgain_GoronNoPK_00,
    EnSGoro_Msg_Shop_TalkAgain_GoronNoPK_01,
    EnSGoro_Msg_Shop_TalkAgain_GoronNoPK_LastNight_00,
    EnSGoro_Msg_Shop_TalkAgain_GoronNoPK_LastNight_01,
    EnSGoro_Msg_WShrineA_NonGoron_GKLoud = 0xcf9,
    EnSGoro_Msg_WShrineA_TalkAgain_NonGoron_GKLoud,
    EnSGoro_Msg_WShrineA_Goron_GKLoud_00,
    EnSGoro_Msg_WShrineA_Goron_GKLoud_01,
    EnSGoro_Msg_WShrineA_Goron_GKLoud_02,
    EnSGoro_Msg_WShrineA_Goron_GKLoud_03, //Also TalkAgain
    EnSGoro_Msg_WShrineA_NonGoron_GKQuiet_00,
    EnSGoro_Msg_WShrineA_NonGoron_GKQuiet_01,
    EnSGoro_Msg_WShrineA_TalkAgain_NonGoron_GKQuiet,
    EnSGoro_Msg_WShrineA_Goron_GKQuiet_00,
    EnSGoro_Msg_WShrineA_Goron_GKQuiet_01,
    EnSGoro_Msg_WShrineA_TalkAgain_Goron_GKQuiet,
    EnSGoro_Msg_WShrineA_TorchOkay_00,
    EnSGoro_Msg_WShrineA_TorchOkay_01,
    EnSGoro_Msg_WShrineA_TalkAgain_TorchOkay,
    EnSGoro_Msg_WShrineC_NonGoron_GKLoud,
    EnSGoro_Msg_WShrineC_Goron_GKLoud_00,
    EnSGoro_Msg_WShrineC_Goron_GKLoud_01,
    EnSGoro_Msg_WShrineC_Goron_GKLoud_02,
    EnSGoro_Msg_WShrineC_Goron_GKLoud_03,
    EnSGoro_Msg_WShrineC_TalkAgain_Goron_GKLoud,
    EnSGoro_Msg_WShrineC_Goron_GKQuiet_00,
    EnSGoro_Msg_WShrineC_Goron_GKQuiet_01,
    EnSGoro_Msg_WShrineC_Goron_GKQuiet_02,
    EnSGoro_Msg_WShrineC_TalkAgain_Goron_GKQuiet,
    EnSGoro_Msg_WShrineC_NonGoron_GKQuiet,
    EnSGoro_Msg_WShrineB_NonGoron_GKLoud,
    EnSGoro_Msg_WShrineB_TalkAgain_NonGoron_GKLoud,
    EnSGoro_Msg_WShrineB_Goron_GKLoud_00,
    EnSGoro_Msg_WShrineB_Goron_GKLoud_01,
    EnSGoro_Msg_WShrineB_Goron_GKLoud_02, //Also talkagain
    EnSGoro_Msg_WShrineB_NonGoron_GKQuiet_00,
    EnSGoro_Msg_WShrineB_NonGoron_GKQuiet_01,
    EnSGoro_Msg_WShrineB_NonGoron_GKQuiet_02,
    EnSGoro_Msg_WShrineB_NonGoron_GKQuiet_03,
    EnSGoro_Msg_WShrineB_NonGoron_GKQuiet_04,
    EnSGoro_Msg_WShrineB_TalkAgain_NonGoron_GKQuiet,
    EnSGoro_Msg_WShrineB_Goron_GKQuiet_00,
    EnSGoro_Msg_WShrineB_Goron_GKQuiet_01,
    EnSGoro_Msg_WShrineB_Goron_GKQuiet_02,
	EnSGoro_Msg_WShrineB_TalkAgain_Goron_GKQuiet,
    EnSGoro_Msg_SShrineA_NonGoron = 0xde1,
    EnSGoro_Msg_SShrineA_Goron_JGWaiting,
    EnSGoro_Msg_SShrineA_Goron_JGTalked_00,
    EnSGoro_Msg_SShrineA_Goron_JGTalked_01,
    EnSGoro_Msg_SShrineB_NonGoron,
    EnSGoro_Msg_SShrineB_Goron_JGWaiting,
    EnSGoro_Msg_SShrineB_Goron_JGTalked_00,
    EnSGoro_Msg_SShrineB_Goron_JGTalked_01,
    EnSGoro_Msg_SShrineC_NonGoron,
    EnSGoro_Msg_SShrineC_Goron_JGWaiting,
    EnSGoro_Msg_SShrineC_Goron_JGTalked_00,
    EnSGoro_Msg_SShrineC_Goron_JGTalked_01,
    EnSGoro_Msg_SShrineD_NonGoron_00,
    EnSGoro_Msg_SShrineD_NonGoron_01,
    EnSGoro_Msg_SShrineD_NonGoron_02,
    EnSGoro_Msg_SShrineD_Goron_JGWaiting,
    EnSGoro_Msg_SShrineD_Goron_JGTalked_00,
    EnSGoro_Msg_SShrineD_Goron_JGTalked_01,
    EnSGoro_Msg_SShrineE_NonGoron_00,
    EnSGoro_Msg_SShrineE_NonGoron_01,
    EnSGoro_Msg_SShrineE_Goron_JGWaiting,
    EnSGoro_Msg_SShrineE_Goron_JGTalked_00,
    EnSGoro_Msg_SShrineE_Goron_JGTalked_01,
    EnSGoro_Msg_SShrineF_NonGoron_00,
    EnSGoro_Msg_SShrineF_NonGoron_01,
    EnSGoro_Msg_SShrineF_Goron_JGWaiting,
    EnSGoro_Msg_SShrineF_Goron_JGTalked_00,
    EnSGoro_Msg_SShrineF_Goron_JGTalked_01,
    EnSGoro_Msg_SShrineF_Goron_JGTalked_02
} EnSGoro_MessageId;

#endif // Z_EN_S_GORO_H
