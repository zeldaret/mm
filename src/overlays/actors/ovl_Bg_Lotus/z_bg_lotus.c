/*
 * File: z_bg_lotus.c
 * Overlay: ovl_Bg_Lotus
 * Description: Southern Swamp Lilypads
 */

#include "z_bg_lotus.h"
#include "objects/object_lotus/object_lotus.h"

#define FLAGS 0x00000000

#define THIS ((BgLotus*)thisx)

void BgLotus_Init(Actor* thisx, GlobalContext* globalCtx);
void BgLotus_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgLotus_Update(Actor* thisx, GlobalContext* globalCtx);
void BgLotus_Draw(Actor* thisx, GlobalContext* globalCtx);

void BgLotus_Wait(BgLotus* this, GlobalContext* globalCtx);
void BgLotus_Sink(BgLotus* this, GlobalContext* globalCtx);
void BgLotus_WaitToAppear(BgLotus* this, GlobalContext* globalCtx);

const ActorInit Bg_Lotus_InitVars = {
    ACTOR_BG_LOTUS,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_LOTUS,
    sizeof(BgLotus),
    (ActorFunc)BgLotus_Init,
    (ActorFunc)BgLotus_Destroy,
    (ActorFunc)BgLotus_Update,
    (ActorFunc)BgLotus_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void BgLotus_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgLotus* this = THIS;
    s32 pad;
    s32 bgId;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 1);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_lotus_Colheader_000A20);
    this->dyna.actor.floorHeight = BgCheck_EntityRaycastFloor5(&globalCtx->colCtx, &thisx->floorPoly, &bgId,
                                                               &this->dyna.actor, &this->dyna.actor.world.pos);
    this->timer2 = 96;
    this->dyna.actor.world.rot.y = Rand_Next() >> 0x10;
    this->actionFunc = BgLotus_Wait;
}

void BgLotus_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgLotus* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void BgLotus_SetScaleXZ(BgLotus* this) {
    f32 scale;

    if (this->dyna.actor.params == 0) {
        scale = sin_rad(this->timer * 0.7853982f) * ((0.014f * ((f32)this->timer / 8)) + 0.01f);
        this->dyna.actor.scale.x = (1.0f + scale) * 0.1f;
        this->dyna.actor.scale.z = (1.0f - scale) * 0.1f;
    }
}

void BgLotus_Wait(BgLotus* this, GlobalContext* globalCtx) {
    f32 moveDist; // distance for the xz position of the lilypad to move

    this->timer2--;

    moveDist = sin_rad(this->timer2 * 0.06544985f) * 6.0f;

    if (this->dyna.actor.params == 0) {
        this->dyna.actor.world.pos.x =
            (Math_SinS(this->dyna.actor.world.rot.y) * moveDist) + this->dyna.actor.home.pos.x;
        this->dyna.actor.world.pos.z =
            (Math_CosS(this->dyna.actor.world.rot.y) * moveDist) + this->dyna.actor.home.pos.z;

        if (this->timer2 == 0) {
            this->timer2 = 96;
            this->dyna.actor.world.rot.y += (s16)(Rand_Next() >> 0x12);
        }
    }

    if (this->height < this->dyna.actor.floorHeight) {
        this->dyna.actor.world.pos.y = this->dyna.actor.floorHeight;
    } else {
        this->dyna.actor.world.pos.y = this->height;

        if (DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
            if (this->hasSpawnedRipples == 0) {
                EffectSsGRipple_Spawn(globalCtx, &this->dyna.actor.world.pos, 1000, 1400, 0);
                EffectSsGRipple_Spawn(globalCtx, &this->dyna.actor.world.pos, 1000, 1400, 8);
                this->timer = 40;
            }
            if (gSaveContext.save.playerForm != PLAYER_FORM_DEKU) {
                this->timer = 40;
                this->dyna.actor.flags |= ACTOR_FLAG_10;
                this->actionFunc = BgLotus_Sink;
                return;
            }

            this->hasSpawnedRipples = 1;
        } else {
            this->hasSpawnedRipples = 0;
        }
    }

    if (this->timer > 0) {
        this->timer--;
    }

    BgLotus_SetScaleXZ(this);
}

void BgLotus_Sink(BgLotus* this, GlobalContext* globalCtx) {
    if (this->height < this->dyna.actor.world.pos.y) {
        this->dyna.actor.world.pos.y = this->height;
    }

    this->dyna.actor.world.pos.y -= 1.0f;

    if (this->dyna.actor.world.pos.y <= this->dyna.actor.floorHeight) {
        this->dyna.actor.world.pos.y = this->dyna.actor.floorHeight;
        this->timer = 0;
    }

    if (this->timer > 0) {
        this->timer--;
        BgLotus_SetScaleXZ(this);
    } else {
        if (Math_StepToF(&this->dyna.actor.scale.x, 0, 0.0050000003539f)) {
            this->dyna.actor.draw = NULL;
            this->timer = 100;
            func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
            this->actionFunc = BgLotus_WaitToAppear;
        }

        this->dyna.actor.scale.z = this->dyna.actor.scale.x;
    }
}

void BgLotus_WaitToAppear(BgLotus* this, GlobalContext* globalCtx) {
    if (this->timer > 0) {
        this->timer--;
    } else if ((this->dyna.actor.xzDistToPlayer > 100.0f) && (this->dyna.actor.projectedPos.z < 0.0f)) {
        this->dyna.actor.draw = BgLotus_Draw;
        func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        Actor_SetScale(&this->dyna.actor, 0.1f);
        this->dyna.actor.world.pos.y = CLAMP_MIN(this->height, this->dyna.actor.floorHeight);
        this->dyna.actor.flags &= ~ACTOR_FLAG_10;
        this->timer2 = 96;
        this->actionFunc = BgLotus_Wait;
        this->dyna.actor.world.pos.x = this->dyna.actor.home.pos.x;
        this->dyna.actor.world.pos.z = this->dyna.actor.home.pos.z;
    }
}

void BgLotus_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgLotus* this = THIS;
    s32 pad;
    WaterBox* waterBox;

    WaterBox_GetSurface1_2(globalCtx, &globalCtx->colCtx, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.z,
                           &this->height, &waterBox);
    this->actionFunc(this, globalCtx);
}

void BgLotus_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, object_lotus_DL_000040);
}
