#include "z_bg_kin2_fence.h"

#define FLAGS 0x00000010

#define THIS ((BgKin2Fence*)thisx)

void BgKin2Fence_Init(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Fence_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Fence_Update(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Fence_Draw(Actor* thisx, GlobalContext* globalCtx);

void BgKin2Fence_SetupHandleMaskCode(BgKin2Fence* this);
void BgKin2Fence_HandleMaskCode(BgKin2Fence* this, GlobalContext* globalCtx);
void BgKin2Fence_SetupPlayOpenCutscene(BgKin2Fence* this);
void BgKin2Fence_PlayOpenCutscene(BgKin2Fence* this, GlobalContext* globalCtx);
void BgKin2Fence_SetupWaitBeforeOpen(BgKin2Fence* this);
void BgKin2Fence_WaitBeforeOpen(BgKin2Fence* this, GlobalContext* globalCtx);
void BgKin2Fence_SetupRaiseFence(BgKin2Fence* this);
void BgKin2Fence_RaiseFence(BgKin2Fence* this, GlobalContext* globalCtx);
void BgKin2Fence_SetupDoNothing(BgKin2Fence* this);
void BgKin2Fence_DoNothing(BgKin2Fence* this, GlobalContext* globalCtx);

const ActorInit Bg_Kin2_Fence_InitVars = {
    ACTOR_BG_KIN2_FENCE,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KIN2_OBJ,
    sizeof(BgKin2Fence),
    (ActorFunc)BgKin2Fence_Init,
    (ActorFunc)BgKin2Fence_Destroy,
    (ActorFunc)BgKin2Fence_Update,
    (ActorFunc)BgKin2Fence_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[4] = {
    {
        {
            ELEMTYPE_UNK4,
            { 0x00000000, 0x00, 0x00 },
            { 0x00003820, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 0, { { -2040, 1400, 350 }, 28 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK4,
            { 0x00000000, 0x00, 0x00 },
            { 0x00003820, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 0, { { -1140, 1400, 350 }, 28 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK4,
            { 0x00000000, 0x00, 0x00 },
            { 0x00003820, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 0, { { 1140, 1400, 350 }, 28 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK4,
            { 0x00000000, 0x00, 0x00 },
            { 0x00003820, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 0, { { 2040, 1400, 350 }, 28 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_2,
        COLSHAPE_JNTSPH,
    },
    4,
    sJntSphElementsInit,
};

Vec3f eyeSparkleSpawnPositions[][2] = { { { -215.0f, 139.0f, 50.0f }, { -193.0f, 139.0f, 50.0f } },

                                        { { -125.0f, 139.0f, 50.0f }, { -103.0f, 139.0f, 50.0f } },

                                        { { 103.0f, 139.0f, 50.0f }, { 125.0f, 139.0f, 50.0f } },

                                        { { 193.0f, 139.0f, 50.0f }, { 215.0f, 139.0f, 50.0f } } };

Color_RGBA8 primColor = { 0xFF, 0xFF, 0xFF, 0x00 };
Color_RGBA8 envColor = { 0x00, 128, 128, 0x00 };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

extern Gfx D_06000828[];
extern CollisionHeader D_06000908;

s32 BgKin2Fence_CheckHitMask(BgKin2Fence* this) {
    ColliderJntSphElement* elements = this->collider.elements;

    if (elements[0].info.bumperFlags & 2) {
        return 0;
    }
    if (elements[1].info.bumperFlags & 2) {
        return 1;
    }
    if (elements[2].info.bumperFlags & 2) {
        return 2;
    }
    if (elements[3].info.bumperFlags & 2) {
        return 3;
    }
    return -1;
}

void BgKin2Fence_SpawnEyeSparkles(BgKin2Fence* this, GlobalContext* globalCtx, s32 mask) {
    s32 i;
    Vec3f sp58;
    s32 pad[2];

    SysMatrix_SetStateRotationAndTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                                             this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);

    for (i = 0; i < 2; i++) {
        SysMatrix_MultiplyVector3fByState(&eyeSparkleSpawnPositions[mask][i], &sp58);
        EffectSsKiraKira_SpawnDispersed(globalCtx, &sp58, &D_801D15B0, &D_801D15B0, &primColor, &envColor, 6000, -10);
    }
}

void BgKin2Fence_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgKin2Fence* this = THIS;
    s32 i = 0;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    BcCheck3_BgActorInit(&this->dyna, 0);
    BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06000908);
    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_SetJntSph(globalCtx, &this->collider, &this->dyna.actor, &sJntSphInit, this->colliderElements);
    SysMatrix_SetStateRotationAndTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                                             this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);
    Matrix_Scale(this->dyna.actor.scale.x, this->dyna.actor.scale.y, this->dyna.actor.scale.z, 1);

    for (i = 0; i < 4; i++) {
        Collider_UpdateSpheres(i, &this->collider);
    }

    if (Flags_GetSwitch(globalCtx, this->dyna.actor.params & 0x7F)) {
        BgKin2Fence_SetupDoNothing(this);
        return;
    }
    BgKin2Fence_SetupHandleMaskCode(this);
}

void BgKin2Fence_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgKin2Fence* this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void BgKin2Fence_SetupHandleMaskCode(BgKin2Fence* this) {
    this->masksHit = 0;
    this->actionFunc = BgKin2Fence_HandleMaskCode;
}

void BgKin2Fence_HandleMaskCode(BgKin2Fence* this, GlobalContext* globalCtx) {
    s32 hitMask;
    s32 nextMask;

    if (this->collider.base.acFlags & AC_HIT) {
        hitMask = BgKin2Fence_CheckHitMask(this);
        if (hitMask >= 0) {
            nextMask = (s8)gSaveContext.spiderHouseMaskOrder[this->masksHit];
            if (hitMask == nextMask) {
                play_sound(NA_SE_SY_TRE_BOX_APPEAR);
                this->masksHit += 1;
                BgKin2Fence_SpawnEyeSparkles(this, globalCtx, nextMask);
            } else {
                play_sound(NA_SE_SY_ERROR);
                this->masksHit = 0;
            }
        }
        this->collider.base.acFlags &= ~AC_HIT;
        this->cooldownTimer = 5;
        if (this->masksHit > 5) {
            BgKin2Fence_SetupPlayOpenCutscene(this);
            return;
        }
    } else {
        if (this->cooldownTimer > 0) {
            this->cooldownTimer -= 1;
            return;
        }
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void BgKin2Fence_SetupPlayOpenCutscene(BgKin2Fence* this) {
    this->actionFunc = BgKin2Fence_PlayOpenCutscene;
}

void BgKin2Fence_PlayOpenCutscene(BgKin2Fence* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        Actor_SetSwitchFlag(globalCtx, this->dyna.actor.params & 0x7F);
        BgKin2Fence_SetupWaitBeforeOpen(this);
        return;
    }
    ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
}

void BgKin2Fence_SetupWaitBeforeOpen(BgKin2Fence* this) {
    this->waitBeforeOpenTimer = 14;
    this->actionFunc = BgKin2Fence_WaitBeforeOpen;
}

void BgKin2Fence_WaitBeforeOpen(BgKin2Fence* this, GlobalContext* globalCtx) {
    if (this->waitBeforeOpenTimer > 0) {
        this->waitBeforeOpenTimer -= 1;
    } else {
        BgKin2Fence_SetupRaiseFence(this);
    }
}

void BgKin2Fence_SetupRaiseFence(BgKin2Fence* this) {
    this->actionFunc = BgKin2Fence_RaiseFence;
}

void BgKin2Fence_RaiseFence(BgKin2Fence* this, GlobalContext* globalCtx) {
    if (Math_StepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y + 58.0f, 5.0f)) {
        BgKin2Fence_SetupDoNothing(this);
    }
}
void BgKin2Fence_SetupDoNothing(BgKin2Fence* this) {
    this->actionFunc = BgKin2Fence_DoNothing;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 58.0f;
}

void BgKin2Fence_DoNothing(BgKin2Fence* this, GlobalContext* globalCtx) {
}

void BgKin2Fence_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgKin2Fence* this = THIS;

    this->actionFunc(this, globalCtx);
}

void BgKin2Fence_Draw(Actor* thisx, GlobalContext* globalCtx) {
    func_800BDFC0(globalCtx, D_06000828);
}
