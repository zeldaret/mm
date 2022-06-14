#ifndef Z_BOSS_03_H
#define Z_BOSS_03_H

#include "global.h"
#include "objects/object_boss03/object_boss03.h"

struct Boss03;

typedef void (*Boss03ActionFunc)(struct Boss03*, GlobalContext*);

#define GYORG_WORK_TIMER_MAX 3

typedef struct {
    /* 0x00 */ u8 type;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Vec3f pos;
    /* 0x10 */ Vec3f velocity;
    /* 0x1C */ Vec3f accel;
    /* 0x28 */ UNK_TYPE1 unk_28[0x4];
    /* 0x2C */ s16 alpha;
    /* 0x2E */ s16 alphaDelta;
    /* 0x30 */ UNK_TYPE1 unk_30[0x4];
    /* 0x34 */ Vec3f unk_34; // it may not be a Vec3f
    /* 0x40 */ f32 unk_40; // colorIntensity?
} GyorgEffect; // size = 0x44

#define GYORG_EFFECT_COUNT 150

typedef enum {
    /* 0 */ GYORG_EFFECT_NONE,
    /* 1 */ GYORG_EFFECT_BUBBLE,
    /* 2 */ GYORG_EFFECT_DROPLET,
    /* 3 */ GYORG_EFFECT_SPLASH,
    /* 4 */ GYORG_EFFECT_WET_SPOT,
} GyorgEffectType;

typedef struct Boss03 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ UNK_TYPE1 unk_144[0x04];
    /* 0x0148 */ SkelAnime skelAnime;
    /* 0x018C */ Vec3s jointTable[GYORG_LIMB_MAX];
    /* 0x01E6 */ Vec3s morphTable[GYORG_LIMB_MAX];
    /* 0x0240 */ s16 unk_240; // generic timer? used by Gyorg and seaweed
    /* 0x0242 */ u8 unk_242;
    /* 0x0243 */ UNK_TYPE1 unk_243[0x09];
    /* 0x024C */ s16 workTimer[GYORG_WORK_TIMER_MAX];
    /* 0x0252 */ s8 numSpawnedSmallFish; // number of Tanron3 fish that are currently alive, -1 indexed
    /* 0x0253 */ u8 hasSpwanedSmallFishes; // Tanron
    /* 0x0254 */ s16 bubbleEffectSpawnCount; // Amount of bubble effect which will be spawned by Update
    /* 0x0258 */ f32 waterHeight; // always 430.0f
    /* 0x025C */ s16 unk_25C; // Timer related to collision?
    /* 0x025E */ s16 unk_25E;
    /* 0x0260 */ f32 unk_260; // rotY
    /* 0x0264 */ UNK_TYPE1 unk_264[0x04];
    /* 0x0268 */ Vec3f unk_268; // set to player.world.pos or random values
    /* 0x0274 */ s16 unk_274;
    /* 0x0276 */ s16 unk_276;
    /* 0x0278 */ f32 unk_278;
    /* 0x027C */ f32 unk_27C;
    /* 0x0280 */ s16 unk_280;
    /* 0x0284 */ f32 unk_284; // Maybe a Vec3f
    /* 0x0288 */ f32 unk_288; // Set but not used
    /* 0x028C */ f32 unk_28C;
    /* 0x0290 */ u8 unk_290;
    /* 0x0294 */ f32 unk_294;
    /* 0x0298 */ f32 unk_298;
    /* 0x029C */ s16 leftFinYRot;
    /* 0x029E */ s16 rightFinYRot;
    /* 0x02A0 */ s16 bodyYRot;
    /* 0x02A2 */ Vec3s unk_2A2;
    /* 0x02A8 */ s16 jawZRot;
    /* 0x02AC */ Vec3f insideJawPos; // used to grab player
    /* 0x02B8 */ f32 unk_2B8;
    /* 0x02BC */ u8 unk_2BC; // set but not used
    /* 0x02BD */ u8 unk_2BD; // playerUnderwater?
    /* 0x02BE */ s16 unk_2BE;
    /* 0x02C0 */ UNK_TYPE1 unk_2C0[0x04];
    /* 0x02C0 */ f32 unk_2C4;
    /* 0x02C8 */ Vec3f prevPlayerPos;
    /* 0x02D4 */ u8 wetSpotEffectSpawnCount;
    /* 0x02D5 */ u8 unk_2D5; // flag
    /* 0x02D6 */ s16 shapeRotTargetX;
    /* 0x02D8 */ s16 shapeRotTargetY;
    /* 0x02DA */ s16 shapeRotTargetZ;
    /* 0x02DC */ Vec3f seaweedSegmentPositions[6];
    /* 0x0324 */ s16 unk_324; // timer? set by Tanron3
    /* 0x0328 */ Boss03ActionFunc actionFunc;
    /* 0x032C */ ColliderJntSph headCollider;
    /* 0x034C */ ColliderJntSphElement headColliderElements[2];
    /* 0x03CC */ ColliderJntSph bodyCollider;
    /* 0x03EC */ ColliderJntSphElement bodyColliderElements[5];
    /* 0x052C */ f32 floppingAnimLastFrame;
    /* 0x0530 */ u32 csTimer;
    /* 0x0534 */ s16 csState;
    /* 0x0536 */ s16 csCamId;
    /* 0x0538 */ Vec3f csCamEye;
    /* 0x0544 */ Vec3f csCamAt;
    /* 0x0550 */ Vec3f csCamTargetEye;
    /* 0x055C */ Vec3f csCamTargetAt;
    /* 0x0568 */ f32 unk_568;
    /* 0x056C */ f32 unk_56C;
    /* 0x0570 */ f32 unk_570; // set but not used
    /* 0x0574 */ UNK_TYPE1 unk_574[0x04];
    /* 0x0578 */ f32 cameraFov;
} Boss03; // size = 0x57C
 
#define GYORG_PARAM_DEFAULT (0)
#define GYORG_PARAM_SEAWEED (0x23)

#endif // Z_BOSS_03_H
