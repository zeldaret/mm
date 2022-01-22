/*
 * File: z_bg_icicle.c
 * Overlay: ovl_Bg_Icicle
 * Description: Icicles
 */

#include "z_bg_icicle.h"
#include "objects/object_icicle/object_icicle.h"

#define FLAGS 0x00000000

#define THIS ((BgIcicle*)thisx)

void BgIcicle_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIcicle_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIcicle_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIcicle_Draw(Actor* thisx, GlobalContext* globalCtx);

void BgIcicle_DoNothing(BgIcicle* this, GlobalContext* globalCtx);
void BgIcicle_Wait(BgIcicle* this, GlobalContext* globalCtx);
void BgIcicle_Shiver(BgIcicle* this, GlobalContext* globalCtx);
void BgIcicle_Fall(BgIcicle* this, GlobalContext* globalCtx);
void BgIcicle_Regrow(BgIcicle* this, GlobalContext* globalCtx);

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x04 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 13, 120, 0, { 0, 0, 0 } },
};

const ActorInit Bg_Icicle_InitVars = {
    ACTOR_BG_ICICLE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_ICICLE,
    sizeof(BgIcicle),
    (ActorFunc)BgIcicle_Init,
    (ActorFunc)BgIcicle_Destroy,
    (ActorFunc)BgIcicle_Update,
    (ActorFunc)BgIcicle_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 1500, ICHAIN_CONTINUE),
    ICHAIN_F32(gravity, -3, ICHAIN_CONTINUE),
    ICHAIN_F32(terminalVelocity, -30, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void BgIcicle_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgIcicle* this = THIS;
    s32 paramsHigh;
    s32 paramsMid;

    Actor_ProcessInitChain(thisx, sInitChain);
    DynaPolyActor_Init(&this->dyna, 0);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_icicle_Colheader_000294);

    Collider_InitAndSetCylinder(globalCtx, &this->collider, thisx, &sCylinderInit);
    Collider_UpdateCylinder(thisx, &this->collider);

    paramsHigh = (thisx->params >> 8) & 0xFF;
    paramsMid = (thisx->params >> 2) & 0x3F;
    this->unk_161 = (thisx->params >> 8) & 0xFF;
    thisx->params = thisx->params & 3;

    if (thisx->params == ICICLE_STALAGMITE_RANDOM_DROP || thisx->params == ICICLE_STALAGMITE_FIXED_DROP) {
        this->unk_160 = ((thisx->params == ICICLE_STALAGMITE_RANDOM_DROP) ? paramsHigh : paramsMid);
        this->actionFunc = BgIcicle_DoNothing;
    } else {
        this->dyna.actor.shape.rot.x = -0x8000;
        this->dyna.actor.shape.yOffset = 1200.0f;
        this->actionFunc = BgIcicle_Wait;
    }
}

void BgIcicle_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgIcicle* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void BgIcicle_Break(BgIcicle* this, GlobalContext* globalCtx, f32 arg2) {
    static Vec3f accel = { 0.0f, -1.0f, 0.0f };
    static Color_RGBA8 primColor = { 170, 255, 255, 255 };
    static Color_RGBA8 envColor = { 0, 50, 100, 255 };
    Vec3f velocity;
    Vec3f pos;
    s32 j;
    s32 i;

    SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->dyna.actor.world.pos, 30, NA_SE_EV_ICE_BROKEN);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 10; j++) {
            pos.x = this->dyna.actor.world.pos.x + randPlusMinusPoint5Scaled(8.0f);
            pos.y = this->dyna.actor.world.pos.y + (Rand_ZeroOne() * arg2) + (i * arg2);
            pos.z = this->dyna.actor.world.pos.z + randPlusMinusPoint5Scaled(8.0f);

            velocity.x = randPlusMinusPoint5Scaled(7.0f);
            velocity.z = randPlusMinusPoint5Scaled(7.0f);
            velocity.y = (Rand_ZeroOne() * 4.0f) + 8.0f;

            EffectSsEnIce_Spawn(globalCtx, &pos, (Rand_ZeroOne() * 0.2f) + 0.1f, &velocity, &accel, &primColor,
                                &envColor, 30);
        }
    }
}

void BgIcicle_DoNothing(BgIcicle* this, GlobalContext* globalCtx) {
}

void BgIcicle_Wait(BgIcicle* this, GlobalContext* globalCtx) {
    if (this->dyna.actor.xzDistToPlayer < 60.0f) {
        this->shiverTimer = 10;
        this->actionFunc = BgIcicle_Shiver;
    }
}

void BgIcicle_Shiver(BgIcicle* this, GlobalContext* globalCtx) {
    s32 randSign;
    f32 rand;

    if (this->shiverTimer != 0) {
        this->shiverTimer--;
    }

    if (!(this->shiverTimer % 4)) {
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_ICE_SWING);
    }

    if (this->shiverTimer == 0) {
        this->dyna.actor.world.pos.x = this->dyna.actor.home.pos.x;
        this->dyna.actor.world.pos.z = this->dyna.actor.home.pos.z;

        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        this->actionFunc = BgIcicle_Fall;
    } else {
        rand = Rand_ZeroOne();
        randSign = (Rand_ZeroOne() < 0.5f ? -1 : 1);
        this->dyna.actor.world.pos.x = (randSign * ((0.5f * rand) + 0.5f)) + this->dyna.actor.home.pos.x;
        rand = Rand_ZeroOne();
        randSign = (Rand_ZeroOne() < 0.5f ? -1 : 1);
        this->dyna.actor.world.pos.z = (randSign * ((0.5f * rand) + 0.5f)) + this->dyna.actor.home.pos.z;
    }
}

void BgIcicle_Fall(BgIcicle* this, GlobalContext* globalCtx) {
    if ((this->collider.base.atFlags & AT_HIT) || (this->dyna.actor.bgCheckFlags & 1)) {
        this->collider.base.atFlags &= ~AT_HIT;
        this->dyna.actor.bgCheckFlags &= ~1;

        if (this->dyna.actor.world.pos.y < this->dyna.actor.floorHeight) {
            this->dyna.actor.world.pos.y = this->dyna.actor.floorHeight;
        }

        BgIcicle_Break(this, globalCtx, 40.0f);

        if (this->dyna.actor.params == ICICLE_STALACTITE_REGROW) {
            this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 120.0f;
            func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
            this->actionFunc = BgIcicle_Regrow;
        } else {
            Actor_MarkForDeath(&this->dyna.actor);
            return;
        }
    } else {
        Actor_MoveWithGravity(&this->dyna.actor);
        this->dyna.actor.world.pos.y += 40.0f;
        Actor_UpdateBgCheckInfo(globalCtx, &this->dyna.actor, 0.0f, 0.0f, 0.0f, 4);
        this->dyna.actor.world.pos.y -= 40.0f;
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void BgIcicle_Regrow(BgIcicle* this, GlobalContext* globalCtx) {
    if (Math_StepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y, 1.0f)) {
        this->actionFunc = BgIcicle_Wait;
        this->dyna.actor.velocity.y = 0.0f;
    }
}

void BgIcicle_UpdateAttacked(BgIcicle* this, GlobalContext* globalCtx) {
    s32 dropItem00Id;

    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;

        if (this->dyna.actor.params == ICICLE_STALAGMITE_RANDOM_DROP) {
            BgIcicle_Break(this, globalCtx, 50.0f);

            if (this->unk_160 != 0xFF) {
                Item_DropCollectibleRandom(globalCtx, NULL, &this->dyna.actor.world.pos, this->unk_160 << 4);
            }
        } else if (this->dyna.actor.params == ICICLE_STALAGMITE_FIXED_DROP) {
            dropItem00Id = func_800A8150(this->unk_160);
            BgIcicle_Break(this, globalCtx, 50.0f);
            Item_DropCollectible(globalCtx, &this->dyna.actor.world.pos, (this->unk_161 << 8) | dropItem00Id);
        } else {
            if (this->dyna.actor.params == ICICLE_STALACTITE_REGROW) {
                BgIcicle_Break(this, globalCtx, 40.0f);
                this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 120.0f;
                func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
                this->actionFunc = BgIcicle_Regrow;
                return;
            }

            BgIcicle_Break(this, globalCtx, 40.0f);
        }

        Actor_MarkForDeath(&this->dyna.actor);
    }
}

void BgIcicle_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgIcicle* this = THIS;

    BgIcicle_UpdateAttacked(this, globalCtx);
    this->actionFunc(this, globalCtx);

    if (this->actionFunc != BgIcicle_Regrow) {
        Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void BgIcicle_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, object_icicle_DL_0000D0);
}
