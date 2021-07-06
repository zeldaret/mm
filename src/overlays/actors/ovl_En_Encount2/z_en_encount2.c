#include "z_en_encount2.h"

#define FLAGS 0x00000010

#define THIS ((EnEncount2*)thisx)

void EnEncount2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEncount2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEncount2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEncount2_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnEncount2_Idle(EnEncount2* this, GlobalContext* globalCtx);
void EnEncount2_Popped(EnEncount2* this, GlobalContext* globalCtx);
void EnEncount2_Die(EnEncount2* this, GlobalContext* globalCtx);
void EnEncount2_SetIdle(EnEncount2* this);
void EnEncount2_InitParticles(EnEncount2* this, Vec3f* vec, s16 fadeDelay);
void EnEncount2_UpdateParticles(EnEncount2* this, GlobalContext* globalCtx);
void EnEncount2_DrawParticles(EnEncount2* this, GlobalContext* globalCtx);

const ActorInit En_Encount2_InitVars = {
    ACTOR_EN_ENCOUNT2,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_FUSEN,
    sizeof(EnEncount2),
    (ActorFunc)EnEncount2_Init,
    (ActorFunc)EnEncount2_Destroy,
    (ActorFunc)EnEncount2_Update,
    (ActorFunc)EnEncount2_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 0 }, 1 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HARD,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit,
};

static DamageTable sDamageTable = {
    0xF0, 0xF0, 0x00, 0xF0, 0xE1, 0xE1, 0x00, 0xE1, 0xF0, 0xF0, 0xF0, 0xE1, 0xE1, 0xE1, 0xF0, 0xF0,
    0xE1, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0xE1, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0,
};

void EnEncount2_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnEncount2* this = THIS;
    s32 pad;
    CollisionHeader* colHeader = NULL;

    BcCheck3_BgActorInit(&this->dyna, 0);
    BgCheck_RelocateMeshHeader(&D_06002420, &colHeader);
    this->dyna.bgId = BgCheck_AddActorMesh(globalCtx, &globalCtx->colCtx.dyna, &this->dyna, colHeader);
    ActorShape_Init(&this->dyna.actor.shape, 0.0f, func_800B3FC0, 25.0f);
    this->dyna.actor.colChkInfo.mass = 0xFF;
    Collider_InitAndSetJntSph(globalCtx, &this->collider, &this->dyna.actor, &sJntSphInit, &this->colElement);

    this->dyna.actor.targetMode = 6;
    this->dyna.actor.colChkInfo.health = 1;
    this->scale = 0.1;
    this->switchFlag = GET_ENCOUNT2_SWITCH_FLAG(this);

    if (this->switchFlag == 0x7F) {
        this->switchFlag = -1;
    }

    if ((this->switchFlag >= 0) && (Flags_GetSwitch(globalCtx, this->switchFlag))) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }

    this->collider.elements->dim.modelSphere.radius = 0x39;
    this->collider.elements->dim.scale = 1.0f;
    this->collider.elements->dim.modelSphere.center.x = 0;
    this->collider.elements->dim.modelSphere.center.y = -4;
    this->collider.elements->dim.modelSphere.center.z = 0;

    this->dyna.actor.colChkInfo.damageTable = &sDamageTable;
    EnEncount2_SetIdle(this);
}

void EnEncount2_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnEncount2* this = THIS;
    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void EnEncount2_SetIdle(EnEncount2* this) {
    this->isPopped = 0;
    this->actionFunc = EnEncount2_Idle;
}

void EnEncount2_Idle(EnEncount2* this, GlobalContext* globalCtx) {
    this->oscillationAngle += 1500.0f;
    this->dyna.actor.velocity.y = Math_SinS(this->oscillationAngle);
    Math_ApproachF(&this->scale, 0.1f, 0.3f, 0.01f);
    if ((this->collider.base.acFlags & AC_HIT) && (this->dyna.actor.colChkInfo.damageEffect == 0xE)) {
        this->dyna.actor.colChkInfo.health = 0;
        this->isPopped = 1;
        this->actionFunc = EnEncount2_Popped;
    }
}

void EnEncount2_Popped(EnEncount2* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f curPos;

    Math_Vec3f_Copy(&curPos, &this->dyna.actor.world.pos);
    curPos.y += 60.0f;
    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, curPos.x, curPos.y, curPos.z, 0xFF, 0xFF, 0xC8,
                0x0001);

    for (i = 0; i != 100; ++i) {
        EnEncount2_InitParticles(this, &curPos, 10);
    }

    Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_MUJURA_BALLOON_BROKEN);
    this->deathTimer = 30;
    this->actionFunc = EnEncount2_Die;
}

void EnEncount2_Die(EnEncount2* this, GlobalContext* globalCtx) {
    if (this->deathTimer == 0) {
        if (this->switchFlag >= 0) {
            Actor_SetSwitchFlag(globalCtx, this->switchFlag);
        }
        Actor_MarkForDeath(&this->dyna.actor);
    }
}

void EnEncount2_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnEncount2* this = THIS;
    s32 pad;

    DECR(this->deathTimer);

    this->dyna.actor.shape.rot.y = this->dyna.actor.world.rot.y;
    Actor_SetHeight(&this->dyna.actor, 30.0f);
    Actor_SetScale(&this->dyna.actor, this->scale);
    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->dyna.actor);
    EnEncount2_UpdateParticles(this, globalCtx);

    if (!this->isPopped) {
        Collider_UpdateSpheresElement(&this->collider, 0, &this->dyna.actor);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void EnEncount2_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnEncount2* this = THIS;
    if (this->isPopped != 1) {
        func_800BDFC0(globalCtx, D_06000A00);
        func_800BDFC0(globalCtx, D_06000D78);
    }
    EnEncount2_DrawParticles(this, globalCtx);
}

void EnEncount2_InitParticles(EnEncount2* this, Vec3f* vec, s16 fadeDelay) {
    s16 i;
    EnEncount2Particle* sPtr = this->particles;

    for (i = 0; i < 200; ++i) {
        if (!sPtr->enabled) {
            sPtr->enabled = 1;
            sPtr->pos = *vec;
            sPtr->alphaFadeDelay = fadeDelay;
            sPtr->alpha = 0xFF;

            sPtr->accel.x = (Rand_ZeroOne() - 0.5f) * 10.0f;
            sPtr->accel.y = (Rand_ZeroOne() - 0.5f) * 10.0f;
            sPtr->accel.z = (Rand_ZeroOne() - 0.5f) * 10.0f;

            sPtr->vel.x = Rand_ZeroOne() - 0.5f;
            sPtr->vel.y = Rand_ZeroOne() - 0.5f;
            sPtr->vel.z = Rand_ZeroOne() - 0.5f;

            sPtr->scale = (Rand_ZeroFloat(1.0f) * 0.5f) + 2.0f;
            return;
        }
        sPtr++;
    }
}

void EnEncount2_UpdateParticles(EnEncount2* this, GlobalContext* globalCtx) {
    s32 i;
    EnEncount2Particle* sPtr = this->particles;

    for (i = 0; i < 200; i += 2) {
        if (sPtr->enabled) {
            sPtr->pos.x += sPtr->vel.x;
            sPtr->pos.y += sPtr->vel.y;
            sPtr->pos.z += sPtr->vel.z;
            sPtr->vel.x += sPtr->accel.x;
            sPtr->vel.y += sPtr->accel.y;
            sPtr->vel.z += sPtr->accel.z;
            if (sPtr->alphaFadeDelay != 0) {
                sPtr->alphaFadeDelay--;
            } else {
                sPtr->alpha -= 10;
                if (sPtr->alpha < 10) {
                    sPtr->enabled = 0;
                }
            }
        }
        sPtr++;

        if (sPtr->enabled) {
            sPtr->pos.x += sPtr->vel.x;
            sPtr->pos.y += sPtr->vel.y;
            sPtr->pos.z += sPtr->vel.z;
            sPtr->vel.x += sPtr->accel.x;
            sPtr->vel.y += sPtr->accel.y;
            sPtr->vel.z += sPtr->accel.z;
            if (sPtr->alphaFadeDelay != 0) {
                sPtr->alphaFadeDelay--;
            } else {
                sPtr->alpha -= 10;
                if (sPtr->alpha < 10) {
                    sPtr->enabled = 0;
                }
            }
        }
        sPtr++;
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount2_0x808E1560/EnEncount2_DrawParticles.asm")
