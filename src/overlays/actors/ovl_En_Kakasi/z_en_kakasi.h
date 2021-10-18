#ifndef Z_EN_KAKASI_H
#define Z_EN_KAKASI_H

#include "global.h"

struct EnKakasi;

typedef void (*EnKakasiActionFunc)(struct EnKakasi*, GlobalContext*);
typedef void (*EnKakasiUnkFunc)(GlobalContext*, struct EnKakasi*);

typedef struct EnKakasi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnKakasiUnkFunc unkFunc; // used for one z_snap calling function?
    /* 0x148 */ EnKakasiActionFunc actionFunc;
    /* 0x14C */ SkelAnime skelanime;
    /* 0x190 */ s16 unk190; // camera index for song teaching angles?
    /* 0x192 */ s16 postTeachTimer;
    /* 0x194 */ s16 aboveGroundStatus; // from params, changed to 2 in init
    /* 0x196 */ s16 unkState196;
    /* 0x19A */ UNK_TYPE1 pad198[0x8];
    /* 0x1A0 */ s32 animIndex;
    /* 0x1A4 */ s32 unkCounter1A4; // counter, counts up to F while he digs away, reused elsewhere
    /* 0x1A8 */ s32 unkState1A8;
    /* 0x1AC */ s16 unkMsgState1AC; // might be dialog state, compared against func(msgCtx)
    /* 0x1AE */ s16 actorCutscenes[3];
    /* 0x1B4 */ f32 animeFrameCount;
    /* 0x1B8 */ f32 unkHeight;
    /* 0x1BC */ Vec3f unk1BC; // set by post limbdraw func for one limb
    /* 0x1C8 */ UNK_TYPE1 pad1C8[0x3C];
    /* 0x204 */ s16 unk204; // set to A, F, 0x14, 0x28 frequently
    /* 0x208 */ UNK_TYPE1 pad206[2];
    /* 0x208 */ s16 cutsceneCamId;
    /* 0x20A */ UNK_TYPE1 pad20A[2];
    /* 0x20C */ f32 unk20C; // passed to unknown function
    /* 0x210 */ f32 unk210; // used as a target for 20C to approach
    /* 0x214 */ Vec3f unk214; // copied from unk238 regularly
    /* 0x220 */ Vec3f unk220; //EnKakasi_TeachingSong
    /* 0x22C */ Vec3f unk22C; //actor home copied to here
    /* 0x238 */ Vec3f unk238; //copied from D_80971E38[unk190]
    /* 0x244 */ Vec3f unk244;
    /* 0x250 */ f32 songSummonDist;
    /* 0x254 */ ColliderCylinder collider;
} EnKakasi; // size = 0x2A0

extern const ActorInit En_Kakasi_InitVars;

#define ENKAKASI_ABOVE_GROUND_TYPE 2

#define GET_KAKASI_SUMMON_DISTANCE(this) ((this->actor.params >> 0x8) & 0xFF) 
#define GET_KAKASI_ABOVE_GROUND(this) (this->actor.params & 0x1) 

#endif // Z_EN_KAKASI_H
