/*
 * File: z_bg_icefloe.c
 * Overlay: ovl_Bg_Icefloe
 * Description: Ice Platform Created by Ice Arrow
 */

#include "z_bg_icefloe.h"
#include "objects/object_icefloe/object_icefloe.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgIcefloe*)thisx)

void BgIcefloe_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIcefloe_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIcefloe_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIcefloe_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AC4A80(BgIcefloe* this, GlobalContext* globalCtx);
void func_80AC4AE8(BgIcefloe* this, GlobalContext* globalCtx);
void func_80AC4C18(BgIcefloe* this);
void func_80AC4D2C(BgIcefloe* this, GlobalContext* globalCtx);
void func_80AC4C34(BgIcefloe* this, GlobalContext* globalCtx);
void func_80AC4CF0(BgIcefloe* this);

const ActorInit Bg_Icefloe_InitVars = {
    ACTOR_BG_ICEFLOE,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_ICEFLOE,
    sizeof(BgIcefloe),
    (ActorFunc)BgIcefloe_Init,
    (ActorFunc)BgIcefloe_Destroy,
    (ActorFunc)BgIcefloe_Update,
    (ActorFunc)BgIcefloe_Draw,
};
static BgIcefloe* sSpawnedInstances[] = { NULL, NULL, NULL };

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 0, ICHAIN_STOP),
};

static s32 numberSpawned;

void BgIcefloe_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    BgIcefloe* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 0);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &gIcefloePlatformCol);
    if (numberSpawned >= 3) {
        s32 i;

        if ((sSpawnedInstances[0] != NULL) && (sSpawnedInstances[0]->dyna.actor.update != NULL) &&
            (sSpawnedInstances[0]->actionFunc != func_80AC4D2C)) {
            func_80AC4CF0(sSpawnedInstances[0]);
        }
        for (i = 0; i < 2; i++) {
            sSpawnedInstances[i] = sSpawnedInstances[i + 1];
        }
        sSpawnedInstances[2] = this;
    } else {
        sSpawnedInstances[numberSpawned] = this;
    }
    numberSpawned++;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 10.0f;
    func_80AC4A80(this, globalCtx);
}

void BgIcefloe_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgIcefloe* this = THIS;
    s32 i;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    numberSpawned--;

    for (i = 0; i < 3; i++) {
        if (sSpawnedInstances[i] == this) {
            sSpawnedInstances[i] = NULL;
            break;
        }
    }
}

void func_80AC4A80(BgIcefloe* this, GlobalContext* globalCtx) {
    this->timer = 20;
    SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->viewProjectionMtxF, &this->dyna.actor.world.pos,
                                 &this->dyna.actor.projectedPos, &this->dyna.actor.projectedW);
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_ICE_STAND_APPEAR);
    this->actionFunc = func_80AC4AE8;
}

static Vec3f sIceBlockAccel = { 0.0f, -0.5f, 0.0f };

void func_80AC4AE8(BgIcefloe* this, GlobalContext* globalCtx) {
    Vec3f velocity;
    Vec3f position;

    velocity.x = randPlusMinusPoint5Scaled(6.0f);
    velocity.z = randPlusMinusPoint5Scaled(6.0f);
    velocity.y = Rand_ZeroFloat(4.0f) + 4.0f;
    this->dyna.actor.scale.x += (0.65f * 0.01f);
    this->dyna.actor.scale.z += (0.65f * 0.01f);
    this->dyna.actor.scale.y += (0.65f * 0.01f);
    position.x = this->dyna.actor.world.pos.x + (velocity.x * this->dyna.actor.scale.x * 75.0f);
    position.z = this->dyna.actor.world.pos.z + (velocity.z * this->dyna.actor.scale.z * 75.0f);
    position.y = this->dyna.actor.world.pos.y + (300.0f * this->dyna.actor.scale.y);
    EffectSsIceBlock_Spawn(globalCtx, &position, &velocity, &sIceBlockAccel, Rand_S16Offset(10, 10));
    this->timer--;
    if (this->timer == 0) {
        func_80AC4C18(this);
    }
}

void func_80AC4C18(BgIcefloe* this) {
    this->timer = this->dyna.actor.params;
    this->actionFunc = func_80AC4C34;
}

void func_80AC4C34(BgIcefloe* this, GlobalContext* globalCtx) {
    WaterBox* water;

    this->timer--;
    if (this->timer == 0 ||
        !WaterBox_GetSurface1_2(globalCtx, &globalCtx->colCtx, this->dyna.actor.world.pos.x,
                                this->dyna.actor.world.pos.z, &this->dyna.actor.home.pos.y, &water)) {
        func_80AC4CF0(this);
    } else {
        this->dyna.actor.world.pos.y =
            (sin_rad(this->timer * (M_PI / 30.0f)) * 3.0f) + (this->dyna.actor.home.pos.y + 10.0f);
    }
}

void func_80AC4CF0(BgIcefloe* this) {
    this->timer = 50;
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_ICE_MELT_LEVEL);
    this->actionFunc = func_80AC4D2C;
}

void func_80AC4D2C(BgIcefloe* this, GlobalContext* globalCtx) {
    this->timer--;
    if ((this->timer >= 38) && !(this->timer % 2)) {
        Vec3f velocity;
        Vec3f position;

        velocity.y = (this->timer - 38) * (1 / 12.0f);
        velocity.x = randPlusMinusPoint5Scaled(1.5f) * velocity.y;
        velocity.z = randPlusMinusPoint5Scaled(1.5f) * velocity.y;
        velocity.y += 0.8f;
        position.x = this->dyna.actor.world.pos.x + (2.0f * velocity.x);
        position.z = this->dyna.actor.world.pos.z + (2.0f * velocity.z);
        position.y = this->dyna.actor.world.pos.y + 3.0f;
        EffectSsIceSmoke_Spawn(globalCtx, &position, &velocity, &gZeroVec3f, 200);
    }
    if (this->timer < 25) {
        this->dyna.actor.scale.x -= 0.0052f;
        this->dyna.actor.scale.z -= 0.0052f;
    }
    this->dyna.actor.scale.y -= 0.0026f;
    if (this->dyna.actor.scale.y <= 0.0f) {
        Actor_MarkForDeath(&this->dyna.actor);
    }
}

void BgIcefloe_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgIcefloe* this = THIS;

    if (!Play_InCsMode(globalCtx)) {
        this->actionFunc(this, globalCtx);
    }
}

void BgIcefloe_Draw(Actor* thisx, GlobalContext* globalCtx) {
    BgIcefloe* this = THIS;

    Gfx_DrawDListOpa(globalCtx, gIcefloeIcePlatformDL);
}
