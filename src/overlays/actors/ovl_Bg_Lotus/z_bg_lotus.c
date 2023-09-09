#include "z_bg_lotus.h"
#include "objects/object_lotus/object_lotus.h"

#define FLAGS 0x00000000

#define THIS ((BgLotus*)thisx)

void BgLotus_Init(Actor* thisx, PlayState* play);
void BgLotus_Destroy(Actor* thisx, PlayState* play);
void BgLotus_Update(Actor* thisx, PlayState* play);
void BgLotus_Draw(Actor* thisx, PlayState* play);
void func_80AD68DC(BgLotus* thisx, PlayState* play);
void func_80AD6A88(Actor* thisx, PlayState* play);
void func_80AD6B68(Actor* thisx, PlayState* play);

ActorInit Bg_Lotus_InitVars = {
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

s32 D_80AD6D10[] = { 0x48580064 };

void BgLotus_Init(Actor* thisx, PlayState* play) {
    BgLotus* this = THIS;

    s32 pad;
    s32 sp2C;

    Actor_ProcessInitChain(&this->dyna.actor, (InitChainEntry*)D_80AD6D10);
    DynaPolyActor_Init((DynaPolyActor*)this, 1);
    DynaPolyActor_LoadMesh(play, (DynaPolyActor*)this, &gLilyPadCol);
    this->dyna.actor.floorHeight = BgCheck_EntityRaycastFloor5(&play->colCtx, &this->dyna.actor.floorPoly, &sp2C,
                                                               &this->dyna.actor, &this->dyna.actor.world.pos);
    this->unk168 = 0x60;
    this->dyna.actor.world.rot.y = ((s32)Rand_Next() >> 0x10);
    this->unk15C = &func_80AD68DC;
}

void BgLotus_Destroy(Actor* thisx, PlayState* play) {
    BgLotus* this = THIS;
    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void func_80AD6830(Actor* thisx) {
    BgLotus* this = THIS;

    f32 temp_fv1;

    if (thisx->params == 0) {
        temp_fv1 = Math_SinF(this->unk166 * (M_PI / 4)) * ((0.014f * (this->unk166 / (80.0f * 0.1f))) + 0.01f);
        thisx->scale.x = ((1.0f + temp_fv1) * 0.1f);
        thisx->scale.z = ((1.0f - temp_fv1) * 0.1f);
    }
}

void func_80AD68DC(BgLotus* thisx, PlayState* play) {
    f32 sp34;

    thisx->unk168 = (thisx->unk168 - 1);
    sp34 = Math_SinF(thisx->unk168 * 0.06544985f) * 6.0f;
    if (thisx->dyna.actor.params == 0) {
        thisx->dyna.actor.world.pos.x =
            (Math_SinS(thisx->dyna.actor.world.rot.y) * sp34) + thisx->dyna.actor.home.pos.x;
        thisx->dyna.actor.world.pos.z =
            (Math_CosS(thisx->dyna.actor.world.rot.y) * sp34) + thisx->dyna.actor.home.pos.z;
        if (thisx->unk168 == 0) {
            thisx->unk168 = 0x60;
            thisx->dyna.actor.world.rot.y += (s16)((s32)Rand_Next() >> 0x12);
        }
    }
    if (thisx->unk160 < thisx->dyna.actor.floorHeight) {
        thisx->dyna.actor.world.pos.y = thisx->dyna.actor.floorHeight;
        goto block_12;
    }
    thisx->dyna.actor.world.pos.y = thisx->unk160;
    if (DynaPolyActor_IsPlayerOnTop((DynaPolyActor*)thisx) != 0) {
        if (thisx->unk164 == 0) {
            EffectSsGRipple_Spawn(play, &thisx->dyna.actor.world.pos, 0x3E8, 0x578, 0);
            EffectSsGRipple_Spawn(play, &thisx->dyna.actor.world.pos, 0x3E8, 0x578, 8);
            thisx->unk166 = 0x28;
        }
        if (gSaveContext.save.playerForm != 3) {
            thisx->unk166 = 0x28;
            thisx->dyna.actor.flags |= 0x10;
            thisx->unk15C = func_80AD6A88;
            return;
        }
        thisx->unk164 = 1U;
        goto block_12;
    }
    thisx->unk164 = 0U;
block_12:
    if (thisx->unk166 > 0) {
        thisx->unk166 = (thisx->unk166 - 1);
    }
    func_80AD6830(&thisx->dyna.actor);
}

void func_80AD6A88(Actor* thisx, PlayState* play) {
    BgLotus* this = THIS;

    if (this->unk160 < thisx->world.pos.y) {
        thisx->world.pos.y = this->unk160;
    }
    thisx->world.pos.y -= 1.0f;
    if (thisx->world.pos.y <= thisx->floorHeight) {
        thisx->world.pos.y = thisx->floorHeight;
        this->unk166 = 0;
    }
    if (this->unk166 > 0) {
        this->unk166 = (this->unk166 - 1);
        func_80AD6830(thisx);
        return;
    }
    if (Math_StepToF(&thisx->scale.x, 0.0f, 0.0050000004f) != 0) {
        thisx->draw = (void*)0;
        this->unk166 = 0x64;
        DynaPoly_DisableCollision(play, &play->colCtx.dyna, this->dyna.bgId);
        this->unk15C = func_80AD6B68;
    }
    thisx->scale.z = thisx->scale.x;
}

void func_80AD6B68(Actor* thisx, PlayState* play) {
    BgLotus* this = THIS;

    f32 temp_fv0;
    f32 temp_fv1;

    if (this->unk166 > 0) {
        this->unk166--;
        return;
    }
    if ((thisx->xzDistToPlayer > 100.0f) && (thisx->projectedPos.z < 0.0f)) {
        thisx->draw = BgLotus_Draw;
        DynaPoly_EnableCollision(play, &play->colCtx.dyna, this->dyna.bgId);
        Actor_SetScale(thisx, 0.1f);
        temp_fv0 = this->unk160;
        temp_fv1 = thisx->floorHeight;
        if (temp_fv0 < temp_fv1) {
            thisx->world.pos.y = temp_fv1;
        } else {
            thisx->world.pos.y = temp_fv0;
        }
        thisx->flags &= ~ACTOR_FLAG_10;
        this->unk168 = 0x60;
        this->unk15C = &func_80AD68DC;
        thisx->world.pos.x = thisx->home.pos.x;
        thisx->world.pos.z = thisx->home.pos.z;
    }
}

void BgLotus_Update(Actor* thisx, PlayState* play) {
    BgLotus* this = THIS;

    s32 pad;
    WaterBox* sp2C;

    WaterBox_GetSurface1_2(play, &play->colCtx, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.z,
                           &this->unk160, &sp2C);
    ((UNK_TYPE(*)(BgLotus*, PlayState*))(this->unk15C))(this, play);
}

void BgLotus_Draw(Actor* thisx, PlayState* play) {

    BgLotus* this = THIS;
    Gfx_DrawDListOpa(play, gLilyPadDL);
}
