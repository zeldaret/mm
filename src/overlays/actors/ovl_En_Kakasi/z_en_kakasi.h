#ifndef Z_EN_KAKASI_H
#define Z_EN_KAKASI_H

#include <global.h>

struct EnKakasi;

typedef void (*EnKakasiActionFunc)(struct EnKakasi*, GlobalContext*);
typedef void (*EnKakasiUnkFunc)(GlobalContext*, struct EnKakasi*);

typedef struct EnKakasi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnKakasiUnkFunc unkFunc; // used for one z_snap calling function?
    /* 0x148 */ EnKakasiActionFunc actionFunc;
    /* 0x14C */ SkelAnime skelanime;
    /* 0x190 */ s16 unk190; // max:8, incremented in multiple places, used as index
    /* 0x192 */ s16 unk192; // 30 written to here
    /* 0x194 */ s16 unk194; // set by params, after params set to 2?
    /* 0x196 */ s16 unk196; // some sort of state? 0 if just standing around
    /* 0x198 */ s16 unk198;
    /* 0x19A */ UNK_TYPE1 pad19A[0x6];
    /* 0x1A0 */ s32 animeIndex;
    /* 0x1A4 */ s32 unkCounter1A4; // counter, counts up to F while he digs away, reused elsewhere
    /* 0x1A8 */ s32 unk1A8; // state? set to 0,1,2
    /* 0x1AC */ s16 unk1AC; // might be dialog state, compared against func(msgCtx)
    /* 0x1AE */ s16 actorCutscenes[3];
    /* 0x1B4 */ f32 animeFrameCount; // todo need better name 
    /* 0x1B8 */ f32 unkHeight;
    /* 0x1BC */ Vec3f unk1BC; // set by post limbdraw func for one limb
    /* 0x1C8 */ UNK_TYPE1 pad1C8[0x3C];
    /* 0x204 */ s16 unk204; //set to A, F, 0x14, 0x28 frequently
    /* 0x208 */ UNK_TYPE1 pad206[2];
    /* 0x208 */ s16 cutsceneCamera;
    /* 0x20A */ UNK_TYPE1 pad20A[2];//padd
    /* 0x20C */ f32 unk20C; // set to 0 or 60 in some setups
    /* 0x210 */ f32 unk210; // gets set to 60 multiple places
    /* 0x214 */ Vec3f unk214; // copied from unk238 regularly
    /* 0x220 */ Vec3f unk220; //func_80970740
    /* 0x22C */ Vec3f unk22C; //actor home copied to here
    /* 0x238 */ Vec3f unk238; //copied from D_80971E38[unk190]
    /* 0x244 */ Vec3f unk244;
    /* 0x250 */ f32 unk250; // set by params, later set to 40f or 80f
    /* 0x254 */ ColliderCylinder collider;

} EnKakasi; // size = 0x2A0

extern const ActorInit En_Kakasi_InitVars;

extern Gfx D_06000214[];
extern Gfx D_060065B0[];

#endif // Z_EN_KAKASI_H
