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
static BgIcefloe* D_80AC4F30[] = { NULL, NULL, NULL };

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 0, ICHAIN_STOP),
};

static s32 D_80AC5060;

void BgIcefloe_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    BgIcefloe* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 0);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_icefloe_Colheader_000C90);
    if (D_80AC5060 >= 3) {
        s32 i;

        if ((D_80AC4F30[0] != NULL) && (D_80AC4F30[0]->dyna.actor.update != NULL) &&
            (D_80AC4F30[0]->actionFunc != func_80AC4D2C)) {
            func_80AC4CF0(D_80AC4F30[0]);
        }
        for (i = 0; i < 2; i++) {
            D_80AC4F30[i] = D_80AC4F30[i + 1];
        }
        D_80AC4F30[2] = this;
    } else {
        D_80AC4F30[D_80AC5060] = this;
    }
    D_80AC5060++;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 10.0f;
    func_80AC4A80(this, globalCtx);
}

void BgIcefloe_Destroy(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    BgIcefloe* this = THIS;
    s32 i;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    D_80AC5060--;

    for (i = 0; i < 3; i++) {
        if (D_80AC4F30[i] == this) {
            D_80AC4F30[i] = NULL;
            break;
        }
    }
}

void func_80AC4A80(BgIcefloe* this, GlobalContext* globalCtx) {
    this->unk_160 = 20;
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
    this->dyna.actor.scale.x += 0.0064999997f;
    this->dyna.actor.scale.z += 0.0064999997f;
    this->dyna.actor.scale.y += 0.0064999997f;
    position.x = this->dyna.actor.world.pos.x + (velocity.x * this->dyna.actor.scale.x * 75.0f);
    position.z = this->dyna.actor.world.pos.z + (velocity.z * this->dyna.actor.scale.z * 75.0f);
    position.y = this->dyna.actor.world.pos.y + (300.0f * this->dyna.actor.scale.y);
    EffectSsIceBlock_Spawn(globalCtx, &position, &velocity, &sIceBlockAccel, Rand_S16Offset(10, 10));
    this->unk_160--;
    if (this->unk_160 == 0) {
        func_80AC4C18(this);
    }
}

void func_80AC4C18(BgIcefloe* this) {
    this->unk_160 = this->dyna.actor.params;
    this->actionFunc = func_80AC4C34;
}

void func_80AC4C34(BgIcefloe* this, GlobalContext* globalCtx) {
    WaterBox* water;

    this->unk_160--;
    if ((this->unk_160 == 0) ||
        (WaterBox_GetSurface1_2(globalCtx, &globalCtx->colCtx, this->dyna.actor.world.pos.x,
                                this->dyna.actor.world.pos.z, &this->dyna.actor.home.pos.y, &water) == 0)) {
        func_80AC4CF0(this);
    } else {
        this->dyna.actor.world.pos.y =
            (sin_rad(this->unk_160 * 0.10471976f) * 3.0f) + (this->dyna.actor.home.pos.y + 10.0f);
    }
}

void func_80AC4CF0(BgIcefloe* this) {
    this->unk_160 = 50;
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_ICE_MELT_LEVEL);
    this->actionFunc = func_80AC4D2C;
}

void func_80AC4D2C(BgIcefloe* this, GlobalContext* globalCtx) {
    this->unk_160--;
    if ((this->unk_160 >= 38) && !((this->unk_160 % 2))) {
        Vec3f velocity;
        Vec3f position;

        velocity.y = (this->unk_160 - 38) * 0.083333336f;
        velocity.x = randPlusMinusPoint5Scaled(1.5f) * velocity.y;
        velocity.z = randPlusMinusPoint5Scaled(1.5f) * velocity.y;
        velocity.y += 0.8f;
        position.x = this->dyna.actor.world.pos.x + (2.0f * velocity.x);
        position.z = this->dyna.actor.world.pos.z + (2.0f * velocity.z);
        position.y = this->dyna.actor.world.pos.y + 3.0f;
        EffectSsIceSmoke_Spawn(globalCtx, &position, &velocity, &gZeroVec3f, 200);
    }
    if (this->unk_160 < 25) {
        this->dyna.actor.scale.x -= 0.0052f;
        this->dyna.actor.scale.z -= 0.0052f;
    }
    this->dyna.actor.scale.y -= 0.0026f;
    if (this->dyna.actor.scale.y <= 0.0f) {
        Actor_MarkForDeath(&this->dyna.actor);
    }
}

void BgIcefloe_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    BgIcefloe* this = THIS;

    if (Play_InCsMode(globalCtx) == 0) {
        this->actionFunc(this, globalCtx);
    }
}

void BgIcefloe_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    BgIcefloe* this = THIS;

    Gfx_DrawDListOpa(globalCtx, object_icefloe_DL_0001E0);
}
