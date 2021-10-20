/*
 * File: z_en_pamera.c
 * Overlay: En_Pamera
 * Description: Pamela
 */

#include "z_en_pamera.h"
#include "../ovl_En_Bom/z_en_bom.h"
#include "../ovl_En_Door/z_en_door.h"

#define FLAGS 0x00000019

#define THIS ((EnPamera*)thisx)

void EnPamera_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPamera_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPamera_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPamera_Draw(Actor* thisx, GlobalContext* globalCtx);

s32 func_80BD84F0(EnPamera* this, GlobalContext* globalCtx);
void func_80BD8588(EnPamera* this, GlobalContext* globalCtx);
void func_80BD8658(EnPamera* this);
void func_80BD8700(EnPamera* this);
void func_80BD8758(EnPamera* this, GlobalContext* globalCtx);
void func_80BD8908(EnPamera* this);
void func_80BD8964(EnPamera* this, GlobalContext* globalCtx);
void func_80BD8A38(EnPamera* this);
void func_80BD8A7C(EnPamera* this, GlobalContext* globalCtx);
void func_80BD8B50(EnPamera* this);
void func_80BD8B70(EnPamera* this, GlobalContext* globalCtx);
void func_80BD8CCC(EnPamera* this);
void func_80BD8D1C(EnPamera* this, GlobalContext* globalCtx);
void func_80BD8D80(EnPamera* this);
void func_80BD8DB0(EnPamera* this, GlobalContext* globalCtx);
void EnPamera_LookDownWell(EnPamera* this);
void func_80BD8F60(EnPamera* this, GlobalContext* globalCtx);
void func_80BD8FF0(EnPamera* this);
void func_80BD909C(EnPamera* this, GlobalContext* globalCtx);
s32 func_80BD9234(EnPamera* this, GlobalContext* globalCtx);
void func_80BD92D0(EnPamera* this, GlobalContext* globalCtx);
void func_80BD9338(EnPamera* this, GlobalContext* globalCtx);
void func_80BD9384(EnPamera* this, GlobalContext* globalCtx);
void func_80BD93CC(EnPamera* this, s16 arg1, s16 arg2);
void func_80BD93F4(EnPamera* this, GlobalContext* globalCtx);
void func_80BD94E0(EnPamera* this, GlobalContext* globalCtx);
void func_80BD9840(EnPamera* this, GlobalContext* globalCtx);
void func_80BD9904(EnPamera* this);
void func_80BD9928(EnPamera* this, GlobalContext* globalCtx);
void func_80BD9938(EnPamera* this);
void func_80BD994C(EnPamera* this, GlobalContext* globalCtx);
void func_80BD9A9C(EnPamera* this);
void EnPamera_HandleDialogue(EnPamera* this, GlobalContext* globalCtx);
void func_80BD9B4C(EnPamera* this, GlobalContext* globalCtx);
void func_80BD9C70(EnPamera* this, GlobalContext* globalCtx);
s32 func_80BD9CB8(EnPamera* this, GlobalContext* globalCtx);
void func_80BD9E60(EnPamera* this);
void func_80BD9E78(EnPamera* this, GlobalContext* globalCtx);
void func_80BD9E88(EnPamera* this);
void func_80BD9ED0(EnPamera* this, GlobalContext* globalCtx);
void func_80BD9EE0(EnPamera* this);
void func_80BD9F3C(EnPamera* this, GlobalContext* globalCtx);
void func_80BDA038(EnPamera* this);
void func_80BDA090(EnPamera* this, GlobalContext* globalCtx);
void func_80BDA0A0(EnPamera* this);
void func_80BDA0FC(EnPamera* this, GlobalContext* globalCtx);
void func_80BDA170(EnPamera* this);
void func_80BDA1C8(EnPamera* this, GlobalContext* globalCtx);
void func_80BDA288(EnPamera* this);
void func_80BDA2E0(EnPamera* this, GlobalContext* globalCtx);
void func_80BDA344(Actor* thisx, GlobalContext* globalCtx);

extern FlexSkeletonHeader D_06008448;
extern AnimationHeader D_060005BC;
extern AnimationHeader D_06008AE0; // Pamela Walking
extern AnimationHeader D_06008E38;
extern AnimationHeader D_0600A844; // Pamela Looking down the well
extern AnimationHeader D_0600B0C4;
extern AnimationHeader D_06009870;
extern AnimationHeader D_06009F54; // HoldBack En_Hgo
extern AnimationHeader D_0600B5B0; // PushBack En_Hgo
extern AnimationHeader D_0600BCC4; // Defend En_Hgo
extern AnimationHeader D_0600D9DC;
extern AnimationHeader D_0600E16C; // Hugging En_Hg
extern AnimationHeader D_0600C9F4;
extern AnimationHeader D_0600D0F0;

extern TexturePtr D_060074E8;
extern TexturePtr D_060078E8;
extern TexturePtr D_060066E8;
extern TexturePtr D_06006AE8;
extern TexturePtr D_06006EE8;
extern TexturePtr D_060072E8;
extern TexturePtr D_060073E8;

const ActorInit En_Pamera_InitVars = {
    ACTOR_EN_PAMERA,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_PAMERA,
    sizeof(EnPamera),
    (ActorFunc)EnPamera_Init,
    (ActorFunc)EnPamera_Destroy,
    (ActorFunc)EnPamera_Update,
    (ActorFunc)EnPamera_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 12, 46, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit2 = {
    0, 0, 0, 0, MASS_IMMOVABLE,
};

static ActorAnimationEntry sAnimations[] = {
    { &D_060005BC, 1.0f, 0, 0.0f, 0, -4.0f }, { &D_06008AE0, 1.0f, 0, 0.0f, 0, -4.0f },
    { &D_06008E38, 1.0f, 0, 0.0f, 0, -4.0f }, { &D_0600A844, 1.0f, 0, 0.0f, 0, -4.0f },
    { &D_0600B0C4, 1.0f, 0, 0.0f, 0, -4.0f }, { &D_06009870, 1.0f, 0, 0.0f, 0, 0.0f },
    { &D_06009F54, 1.0f, 0, 0.0f, 0, 0.0f },  { &D_0600B5B0, 1.0f, 0, 0.0f, 0, 0.0f },
    { &D_0600BCC4, 1.0f, 0, 0.0f, 0, 0.0f },  { &D_0600D9DC, 1.0f, 0, 0.0f, 0, 0.0f },
    { &D_0600E16C, 1.0f, 0, 0.0f, 0, 0.0f },  { &D_0600C9F4, 1.0f, 0, 0.0f, 2, 0.0f },
    { &D_0600D0F0, 1.0f, 0, 0.0f, 0, 0.0f },
};

static Vec3f D_80BDA5F0 = { 1000.0f, 0.0f, 0.0f };

static TexturePtr D_80BDA5FC[] = { &D_060074E8, &D_060078E8 };

static TexturePtr D_80BDA604[] = { &D_060066E8, &D_06006AE8, &D_06006EE8 };

static TexturePtr D_80BDA610[] = { &D_060072E8, &D_060073E8 };

void EnPamera_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnPamera* this = THIS;
    Vec3f sp44;

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 15.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06008448, &D_060005BC, this->limbDrawTbl, this->transitionDrawTbl,
                     PAMERA_LIMB_MAX);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, NULL, &sColChkInfoInit2);
    this->actor.targetMode = 6;
    this->unk_312 = 0;
    this->unk_310 = 0;
    this->unk_314 = 0;
    this->unk_316 = 0;
    this->hideInisdeTimer = 0;
    this->unk_322 = 0;
    this->unk_324 = 0;
    if ((this->actor.params & 0xF000) >> 0xC) {
        func_80BD9840(this, globalCtx);
    } else {
        func_80BD8588(this, globalCtx);
        func_80BD8658(this);
        if (1) {}
        if (!(gSaveContext.weekEventReg[14] & 4) || (gSaveContext.weekEventReg[52] & 0x20) ||
            (gSaveContext.weekEventReg[75] & 0x20) || (gSaveContext.entranceIndex == 0x2090)) {
            Actor_MarkForDeath(&this->actor);
        }
        if (gSaveContext.weekEventReg[61] & 4) {
            if (!(gSaveContext.weekEventReg[59] & 1) || (gSaveContext.entranceIndex != 0x2020)) {
                if ((gSaveContext.entranceIndex != 0x2020) && (gSaveContext.weekEventReg[59] & 1)) {
                    gSaveContext.weekEventReg[59] &= (u8)~1;
                }
                func_80BD8700(this);
            } else {
                this->pathIndex = this->pathPointsCount - 1;
                Math_Vec3s_ToVec3f(&this->actor.world.pos, &this->pathPoints[this->pathIndex]);
                Math_Vec3s_ToVec3f(&sp44, &this->pathPoints[this->pathIndex - 1]);
                this->actor.world.rot.y = this->actor.shape.rot.y = Math_Vec3f_Yaw(&sp44, &this->actor.world.pos);
                func_80BD8CCC(this);
            }
        } else {
            gSaveContext.weekEventReg[59] |= 1;
            func_80BD8FF0(this);
        }
    }
}

s32 func_80BD84F0(EnPamera* this, GlobalContext* globalCtx) {
    Actor* actor = globalCtx->actorCtx.actorList[ACTORCAT_DOOR].first;

    while (actor != NULL) {
        if ((actor->id == ACTOR_EN_DOOR) && (Math_Vec3f_DistXZ(&this->actor.world.pos, &actor->world.pos) < 200.0f)) {
            this->actor.child = actor;
            return true;
        }
        actor = actor->next;
    }
    this->actor.child = NULL;
    return false;
}

void func_80BD8588(EnPamera* this, GlobalContext* globalCtx) {
    Path* path = &globalCtx->setupPathList[((this->actor.params & 0xFF0) >> 4)];
    Vec3f sp28;

    if (path == NULL) {
        Actor_MarkForDeath(&this->actor);
    }
    if (gSaveContext.weekEventReg[61] & 4) {
        path = &globalCtx->setupPathList[path->unk1];
    }
    this->pathPoints = Lib_SegmentedToVirtual(path->points);
    this->pathIndex = 0;
    this->pathPointsCount = path->count;
    this->pathId = path->unk1;
    Math_Vec3s_ToVec3f(&sp28, this->pathPoints);
    this->actor.world.rot.y = this->actor.shape.rot.y = Math_Vec3f_Yaw(&this->actor.world.pos, &sp28);
}

void func_80BD8658(EnPamera* this) {
    s32 i;
    s16 nextCutscene = this->actor.cutscene;

    for (i = 0; i < ARRAY_COUNT(this->cutscenes); i++) {
        if (nextCutscene == -1) {
            break;
        }
        this->cutscenes[i] = nextCutscene;
        nextCutscene = ActorCutscene_GetAdditionalCutscene(nextCutscene);
    }
}

void EnPamera_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnPamera* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80BD8700(EnPamera* this) {
    this->hideInisdeTimer = 0;
    this->actor.flags &= ~1;
    func_800BDC5C(&this->skelAnime, sAnimations, 0);
    this->actionFunc = func_80BD8758;
}

void func_80BD8758(EnPamera* this, GlobalContext* globalCtx) {
    if (this->hideInisdeTimer++ > 1800) {
        if (ActorCutscene_GetCanPlayNext(this->cutscenes[0]) && (this->cutscenes[0] != -1)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->cutscenes[0], &this->actor);
            func_800E02AC(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(this->cutscenes[0])), &this->actor);
            this->actor.speedXZ = 1.5f;
            func_800BDC5C(&this->skelAnime, sAnimations, 1);
            this->actor.shape.rot.y = this->actor.home.rot.y;
            this->actor.world.rot.y = this->actor.home.rot.y;
            func_80BD9338(this, globalCtx);
            func_80BD8908(this);
        } else if ((this->cutscenes[0] != -1) && (this->actor.xzDistToPlayer < 1000.0f)) {
            ActorCutscene_SetIntentToPlay(this->cutscenes[0]);
        } else {
            this->actor.speedXZ = 1.5f;
            func_800BDC5C(&this->skelAnime, sAnimations, 1);
            this->actor.shape.rot.y = this->actor.home.rot.y;
            this->actor.world.rot.y = this->actor.home.rot.y;
            func_80BD9338(this, globalCtx);
            func_80BD8908(this);
        }
    }
    if ((this->actor.draw != NULL) && (this->actionFunc != func_80BD8964)) {
        if ((this->actor.child != NULL) && (this->actor.child->id == ACTOR_EN_DOOR) &&
            (this->actor.child->world.rot.y == 0)) {
            this->actor.draw = NULL;
        }
    }
    if (func_80BD9234(this, globalCtx)) {
        // this is 1760 frames, which is ~90sec
        this->hideInisdeTimer = 88 * 20;
    }
}

void func_80BD8908(EnPamera* this) {
    this->actor.draw = EnPamera_Draw;
    this->actor.flags |= 1;
    func_800BDC5C(&this->skelAnime, sAnimations, 1);
    this->actionFunc = func_80BD8964;
}

void func_80BD8964(EnPamera* this, GlobalContext* globalCtx) {
    Vec3f vec;

    vec.x = this->pathPoints->x;
    vec.y = this->pathPoints->y;
    vec.z = this->pathPoints->z;

    if (Math_Vec3f_StepTo(&this->actor.world.pos, &vec, 1.0f) < 5.0f) {
        this->actor.speedXZ = 1.5f;
        func_800BDC5C(&this->skelAnime, sAnimations, 1);
        gSaveContext.weekEventReg[59] |= 1;
        func_80BD8B50(this);
    }
}

void func_80BD8A38(EnPamera* this) {
    func_800BDC5C(&this->skelAnime, sAnimations, 1);
    this->actionFunc = func_80BD8A7C;
}

void func_80BD8A7C(EnPamera* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &this->actor.home.pos), 0xA,
                       0x3000, 0x100);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (Math_Vec3f_StepTo(&this->actor.world.pos, &this->actor.home.pos, 1.5f) < 10.0f) {
        gSaveContext.weekEventReg[59] &= (u8)~1;
        if (!(gSaveContext.weekEventReg[61] & 4)) {
            func_80BD92D0(this, globalCtx);
            gSaveContext.weekEventReg[61] |= 4;
        }
        func_80BD8700(this);
    }
}

void func_80BD8B50(EnPamera* this) {
    this->actionFunc = func_80BD8B70;
    this->actor.gravity = -2.0f;
}

void func_80BD8B70(EnPamera* this, GlobalContext* globalCtx) {
    Vec3f vec;
    s16 sp32;

    vec.x = this->pathPoints[this->pathIndex].x;
    vec.y = this->pathPoints[this->pathIndex].y;
    vec.z = this->pathPoints[this->pathIndex].z;
    sp32 = Math_Vec3f_Yaw(&this->actor.world.pos, &vec);
    if (Math_Vec3f_StepToXZ(&this->actor.world.pos, &vec, this->actor.speedXZ) > 10.0f) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, sp32, 0xA, 0x3000, 0x100);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    } else if (this->pathIndex < (this->pathPointsCount - 1)) {
        this->pathIndex++;
    } else {
        func_80BD8CCC(this);
    }

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    this->actor.world.pos.y += this->actor.gravity;
}

void func_80BD8CCC(EnPamera* this) {
    this->hideInisdeTimer = 0;
    this->actor.speedXZ = 0.0f;
    func_800BDC5C(&this->skelAnime, sAnimations, 3);
    this->actionFunc = func_80BD8D1C;
}

void func_80BD8D1C(EnPamera* this, GlobalContext* globalCtx) {
    if (this->hideInisdeTimer++ > 200) {
        this->actor.speedXZ = 1.5f;
        func_800BDC5C(&this->skelAnime, sAnimations, 1);
        func_80BD8D80(this);
    }
}

void func_80BD8D80(EnPamera* this) {
    if (this->pathIndex > 0) {
        this->pathIndex--;
    }
    this->actor.gravity = -2.0f;
    this->actionFunc = func_80BD8DB0;
}

void func_80BD8DB0(EnPamera* this, GlobalContext* globalCtx) {
    Vec3f vec;
    s16 sp32;

    vec.x = this->pathPoints[this->pathIndex].x;
    vec.y = this->pathPoints[this->pathIndex].y;
    vec.z = this->pathPoints[this->pathIndex].z;
    sp32 = Math_Vec3f_Yaw(&this->actor.world.pos, &vec);
    if (Math_Vec3f_StepToXZ(&this->actor.world.pos, &vec, this->actor.speedXZ) > 10.0f) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, sp32, 0xA, 0x3000, 0x100);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    } else if (this->pathIndex > 0) {
        this->pathIndex--;
    } else {
        func_80BD9338(this, globalCtx);
        func_80BD8A38(this);
    }
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    this->actor.world.pos.y += this->actor.gravity;
}

void EnPamera_LookDownWell(EnPamera* this) {
    func_80BD93CC(this, 1, 1);
    func_800BDC5C(&this->skelAnime, sAnimations, 4);
    this->actionFunc = func_80BD8F60;
}

void func_80BD8F60(EnPamera* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x3000, 0x1000);
    if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) {
        func_800BDC5C(&this->skelAnime, sAnimations, 2);
        this->actor.speedXZ = 3.0f;
        func_80BD93CC(this, 0, 0);
        func_80BD8D80(this);
    }
}

void func_80BD8FF0(EnPamera* this) {
    Vec3f pameraPos;
    s16 pameraYaw;

    this->pathIndex = this->pathPointsCount - 1;
    Math_Vec3s_ToVec3f(&this->actor.world.pos, &this->pathPoints[this->pathPointsCount - 1]);
    Math_Vec3s_ToVec3f(&pameraPos, &this->pathPoints[this->pathPointsCount - 2]);
    pameraYaw = Math_Vec3f_Yaw(&pameraPos, &this->actor.world.pos);
    this->actor.shape.rot.y = pameraYaw;
    this->actor.world.rot.y = pameraYaw;
    func_800BDC5C(&this->skelAnime, sAnimations, 3);
    this->actionFunc = func_80BD909C;
}

void func_80BD909C(EnPamera* this, GlobalContext* globalCtx) {
}

void func_80BD90AC(EnPamera* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (Player_GetMask(globalCtx) != PLAYER_MASK_STONE && (this->actionFunc != func_80BD8758) &&
        (this->actionFunc != func_80BD8964) && (this->actionFunc != func_80BD8A7C) &&
        (this->actionFunc != func_80BD8F60) && ((this->actionFunc != func_80BD8B70) || (this->pathIndex != 0)) &&
        ((this->actionFunc != func_80BD8DB0) || (this->actor.speedXZ != 3.0f)) &&
        ((this->actor.xzDistToPlayer < 150.0f) ||
         ((this->actionFunc == func_80BD909C) &&
          (Math_Vec3f_DistXZ(&this->actor.home.pos, &player->actor.world.pos) < 200.0f)))) {
        if ((ActorCutscene_GetCanPlayNext(this->cutscenes[1])) && ((this->cutscenes[1] != -1))) {
            ActorCutscene_StartAndSetUnkLinkFields(this->cutscenes[1], &this->actor);
            func_800E02AC(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(this->cutscenes[1])), &this->actor);
            EnPamera_LookDownWell(this);
        } else if (this->cutscenes[1] != -1) {
            ActorCutscene_SetIntentToPlay(this->cutscenes[1]);
        } else {
            EnPamera_LookDownWell(this);
        }
    }
}

s32 func_80BD9234(EnPamera* this, GlobalContext* globalCtx) {
    Actor* actor = globalCtx->actorCtx.actorList[ACTORCAT_EXPLOSIVES].first;

    while (actor != NULL) {
        if ((actor->id == ACTOR_EN_BOM) && (Math_Vec3f_DistXZ(&this->actor.world.pos, &actor->world.pos) < 500.0f) &&
            (((EnBom*)actor)->timer == 0)) {
            return 1;
        } else {
            actor = actor->next;
        }
    }
    return 0;
}

void func_80BD92D0(EnPamera* this, GlobalContext* globalCtx) {
    Path* path;
    s32 pathId = this->pathId;

    path = &globalCtx->setupPathList[pathId];
    if (pathId >= 0) {
        this->pathPoints = Lib_SegmentedToVirtual(path->points);
        this->pathIndex = 0;
        this->pathPointsCount = path->count;
        this->pathId = path->unk1;
    }
}

void func_80BD9338(EnPamera* this, GlobalContext* globalCtx) {
    Actor* actor;

    func_80BD84F0(this, globalCtx);
    actor = this->actor.child;
    if ((actor != NULL) && (actor->id == ACTOR_EN_DOOR)) {
        ((EnDoor*)actor)->unk1A7 = -0x32;
    }
}

void func_80BD9384(EnPamera* this, GlobalContext* globalCtx) {
    if (this->unk_316 < 40) {
        this->unk_316++;
    } else {
        this->unk_312++;
        if (this->unk_312 >= 3) {
            this->unk_312 = 0;
            this->unk_316 = 0;
        }
    }
}

void func_80BD93CC(EnPamera* this, s16 arg1, s16 arg2) {
    this->unk_310 = arg1;
    this->unk_314 = arg2;
}

void func_80BD93F4(EnPamera* this, GlobalContext* globalCtx) {
    if ((this->actionFunc == func_80BD8B70) || (this->actionFunc == func_80BD8DB0) ||
        (this->actionFunc == func_80BD8964) || (this->actionFunc == func_80BD8A7C)) {
        if (this->skelAnime.animCurrentSeg == &D_06008AE0) {
            if (func_801378B8(&this->skelAnime, 9.0f) || func_801378B8(&this->skelAnime, 18.0f)) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_PAMERA_WALK);
            }
        } else if ((this->skelAnime.animCurrentSeg == &D_06008E38) &&
                   (func_801378B8(&this->skelAnime, 2.0f) || func_801378B8(&this->skelAnime, 6.0f))) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_PAMERA_WALK);
        }
    }
}

void func_80BD94E0(EnPamera* this, GlobalContext* globalCtx) {
    if ((this->actionFunc != func_80BD8B70) && (this->actionFunc != func_80BD8964) &&
        (this->actionFunc != func_80BD909C) && (this->actionFunc != func_80BD8D1C) &&
        ((this->actionFunc != func_80BD8DB0) || (this->actor.speedXZ == 3.0f))) {
        func_800E9250(globalCtx, &this->actor, &this->limb9Rot, &this->limb8Rot, this->actor.focus.pos);
    } else {
        func_800E8F08(&this->limb9Rot, &this->limb8Rot);
    }
}

void EnPamera_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnPamera* this = THIS;

    this->actionFunc(this, globalCtx);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_80BD90AC(this, globalCtx);
    func_80BD9384(this, globalCtx);
    func_80BD94E0(this, globalCtx);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    func_80BD93F4(this, globalCtx);
}

s32 EnPamera_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                              Actor* thisx) {
    EnPamera* this = THIS;

    if (limbIndex == PAMERA_LIMB_HAIR) {
        rot->x += this->limb9Rot.y;
        rot->z += this->limb9Rot.x;
    }
    return 0;
}

void EnPamera_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    if (limbIndex == PAMERA_LIMB_HAIR) {
        SysMatrix_MultiplyVector3fByState(&D_80BDA5F0, &thisx->focus.pos);
    }
}

void EnPamera_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnPamera* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(D_80BDA604[this->unk_312]));
    gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(D_80BDA610[this->unk_314]));
    gSPSegment(POLY_OPA_DISP++, 0x0A, SEGMENTED_TO_VIRTUAL(D_80BDA5FC[this->unk_310]));
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     EnPamera_OverrideLimbDraw, EnPamera_PostLimbDraw, &this->actor);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80BD9840(EnPamera* this, GlobalContext* globalCtx) {
    this->actor.update = func_80BDA344;
    this->actor.flags |= 0x2000000;
    this->actor.flags |= 0x100000;
    if ((gSaveContext.weekEventReg[75] & 0x20) || (gSaveContext.weekEventReg[52] & 0x20)) {
        func_80BD9E60(this);
        func_80BD9938(this);
    } else {
        this->actor.draw = NULL;
        func_80BD9E60(this);
        func_80BD9904(this);
    }
    if (gSaveContext.weekEventReg[14] & 4) {
        func_801A0204(0x27);
    } else {
        func_801A0204(0x1F);
    }
}

void func_80BD9904(EnPamera* this) {
    this->actor.flags &= ~1;
    this->actionFunc = &func_80BD9928;
}

void func_80BD9928(EnPamera* this, GlobalContext* globalCtx) {
}

void func_80BD9938(EnPamera* this) {
    this->actionFunc = func_80BD994C;
}

void func_80BD994C(EnPamera* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        if (Player_GetMask(globalCtx) == PLAYER_MASK_GIBDO) {
            if (1) {}
            func_80BD93CC(this, 0, 1);
            func_801518B0(globalCtx, 0x15A8, &this->actor);

            this->unk_324 = 0x15A8;
        } else if ((gSaveContext.playerForm != PLAYER_FORM_HUMAN) ||
                   ((gSaveContext.weekEventReg[52] & 0x20) && (!(gSaveContext.weekEventReg[75] & 0x20)))) {
            func_80BD93CC(this, 1, 0);
            func_801518B0(globalCtx, 0x158E, &this->actor);
            this->unk_324 = 0x158E;
        } else {
            if (!(this->unk_322 & 1)) {
                this->unk_322 |= 1;
                func_801518B0(globalCtx, 0x1587, &this->actor);
                this->unk_324 = 0x1587;
            } else {
                func_801518B0(globalCtx, 0x158C, &this->actor);
                this->unk_324 = 0x158C;
            }
        }
        func_80BD9A9C(this);
    } else {
        func_800B8614(&this->actor, globalCtx, 100.0f);
    }
}

void func_80BD9A9C(EnPamera* this) {
    this->actionFunc = EnPamera_HandleDialogue;
}

void EnPamera_HandleDialogue(EnPamera* this, GlobalContext* globalCtx) {
    switch (func_80152498(&globalCtx->msgCtx)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            break;
        case 5:
            func_80BD9B4C(this, globalCtx);
            break;
        case 6:
            if (func_80147624(globalCtx)) {
                func_80BD9938(this);
            }
            break;
        default:
            break;
    }
    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x71C, 0xB6);
    this->actor.shape.rot.y = this->actor.world.rot.y;
}

void func_80BD9B4C(EnPamera* this, GlobalContext* globalCtx) {
    if (func_80147624(globalCtx)) {
        switch (this->unk_324) {
            case 0x1587:
                func_801518B0(globalCtx, 0x1588, &this->actor);
                this->unk_324 = 0x1588;
                break;
            case 0x1588:
                func_801518B0(globalCtx, 0x1589, &this->actor);
                this->unk_324 = 0x1589;
                break;
            case 0x1589:
                func_801518B0(globalCtx, 0x158A, &this->actor);
                this->unk_324 = 0x158A;
                break;
            case 0x158A:
                func_801518B0(globalCtx, 0x158B, &this->actor);
                this->unk_324 = 0x158B;
                break;
            case 0x158C:
                func_801518B0(globalCtx, 0x158D, &this->actor);
                this->unk_324 = 0x158D;
                break;
            case 0x158E:
            case 0x15A8:
                func_801477B4(globalCtx);
                func_80BD9C70(this, globalCtx);
                break;
        }
    }
}

void func_80BD9C70(EnPamera* this, GlobalContext* globalCtx) {
    globalCtx->nextEntranceIndex = 0x2020;
    globalCtx->sceneLoadFlag = 0x14;
    globalCtx->unk_1887F = 0x46;
    gSaveContext.nextTransition = 2;
}

s32 func_80BD9CB8(EnPamera* this, GlobalContext* globalCtx) {
    u32 actionIndex;

    if (func_800EE29C(globalCtx, 0x1E5)) {
        actionIndex = func_800EE200(globalCtx, 0x1E5);
        if (this->unk_326 != globalCtx->csCtx.npcActions[actionIndex]->unk0) {
            this->unk_326 = globalCtx->csCtx.npcActions[actionIndex]->unk0;

            switch (globalCtx->csCtx.npcActions[actionIndex]->unk0) {
                case 1:
                    func_80BD9E88(this);
                    break;
                case 2:
                    if (this->actor.draw == NULL) {
                        this->actor.draw = EnPamera_Draw;
                        this->actor.flags |= 1;
                    }
                    func_80BD9EE0(this);
                    break;
                case 3:
                    func_80BDA038(this);
                    break;
                case 4:
                    func_80BDA0A0(this);
                    break;
                case 5:
                    func_80BDA170(this);
                    break;
                case 6:
                    func_80BDA288(this);
                    break;
            }
        }
        func_800EDF24(&this->actor, globalCtx, actionIndex);
        this->setupFunc(this, globalCtx);
        return 1;
    }
    if ((globalCtx->csCtx.state == 0) && (gSaveContext.weekEventReg[75] & 0x20)) {
        if ((this->actionFunc != func_80BD994C) && (this->actionFunc != EnPamera_HandleDialogue)) {
            this->actor.shape.rot.y = this->actor.world.rot.y;
            func_80BD9904(this);
            func_80BD9E60(this);
        }
    }
    this->unk_326 = 0x63;
    return 0;
}

void func_80BD9E60(EnPamera* this) {
    this->unk_31E = 0;
    this->setupFunc = func_80BD9E78;
}

void func_80BD9E78(EnPamera* this, GlobalContext* globalCtx) {
}

void func_80BD9E88(EnPamera* this) {
    func_800BDC5C(&this->skelAnime, sAnimations, 0);
    this->unk_31E = 0;
    this->setupFunc = func_80BD9ED0;
}

void func_80BD9ED0(EnPamera* this, GlobalContext* globalCtx) {
}

void func_80BD9EE0(EnPamera* this) {
    func_800BDC5C(&this->skelAnime, sAnimations, 5);
    func_80BD93CC(this, 1, 0);
    this->unk_31E = 1;
    this->setupFunc = func_80BD9F3C;
}

void func_80BD9F3C(EnPamera* this, GlobalContext* globalCtx) {
    if (this->unk_31E == 1) {
        if (func_801378B8(&this->skelAnime, 2.0f) || func_801378B8(&this->skelAnime, 6.0f) ||
            func_801378B8(&this->skelAnime, 10.0f) || func_801378B8(&this->skelAnime, 14.0f) ||
            func_801378B8(&this->skelAnime, 18.0f) || func_801378B8(&this->skelAnime, 22.0f) ||
            func_801378B8(&this->skelAnime, 25.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_PAMERA_WALK);
        }
        if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) {
            this->unk_31E = 0;
            func_80BD93CC(this, 0, 0);
            func_800BDC5C(&this->skelAnime, sAnimations, 6);
        }
    }
}

void func_80BDA038(EnPamera* this) {
    func_80BD93CC(this, 0, 1);
    func_800BDC5C(&this->skelAnime, sAnimations, 7);
    this->unk_31E = 0;
    this->setupFunc = func_80BDA090;
}

void func_80BDA090(EnPamera* this, GlobalContext* globalCtx) {
}

void func_80BDA0A0(EnPamera* this) {
    func_80BD93CC(this, 0, 1);
    func_800BDC5C(&this->skelAnime, sAnimations, 8);
    this->unk_31E = 1;
    this->setupFunc = func_80BDA0FC;
}

void func_80BDA0FC(EnPamera* this, GlobalContext* globalCtx) {
    if (this->unk_31E == 1) {
        if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) {
            this->unk_31E = 0;
            func_80BD93CC(this, 0, 0);
            func_800BDC5C(&this->skelAnime, sAnimations, 6);
        }
    }
}

void func_80BDA170(EnPamera* this) {
    this->unk_31E = 1;
    func_80BD93CC(this, 0, 1);
    func_800BDC5C(&this->skelAnime, sAnimations, 9);
    this->setupFunc = func_80BDA1C8;
}

void func_80BDA1C8(EnPamera* this, GlobalContext* globalCtx) {
    if (this->unk_31E == 1) {
        if (func_801378B8(&this->skelAnime, 2.0f) || func_801378B8(&this->skelAnime, 6.0f) ||
            func_801378B8(&this->skelAnime, 10.0f) || func_801378B8(&this->skelAnime, 14.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_PAMERA_WALK);
        }
        if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) {
            this->unk_31E = 0;
            func_80BD93CC(this, 0, 0);
            func_800BDC5C(&this->skelAnime, sAnimations, 10);
        }
    }
}

void func_80BDA288(EnPamera* this) {
    this->unk_31E = 1;
    func_80BD93CC(this, 0, 0);
    func_800BDC5C(&this->skelAnime, sAnimations, 11);
    this->setupFunc = func_80BDA2E0;
}

void func_80BDA2E0(EnPamera* this, GlobalContext* globalCtx) {
    if (this->unk_31E == 1) {
        if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) {
            this->unk_31E = 0;
            func_800BDC5C(&this->skelAnime, sAnimations, 12);
        }
    }
}

void func_80BDA344(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnPamera* this = THIS;

    this->actionFunc(this, globalCtx);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_80BD9384(this, globalCtx);
    if (func_80BD9CB8(this, globalCtx)) {
        // Pamela is outside
        if (gSaveContext.weekEventReg[59] & 1) {
            gSaveContext.weekEventReg[59] &= (u8)~1;
        }
        if (!(gSaveContext.weekEventReg[61] & 4)) {
            gSaveContext.weekEventReg[61] |= 4;
        }
        func_800E8F08(&this->limb9Rot, &this->limb8Rot);
    } else {
        func_80BD94E0(this, globalCtx);
        if (this->actionFunc == func_80BD994C) {
            Collider_UpdateCylinder(&this->actor, &this->collider);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
        if (gSaveContext.weekEventReg[14] & 4) {
            globalCtx->roomCtx.unk7A[0]++;
        }
    }
}
