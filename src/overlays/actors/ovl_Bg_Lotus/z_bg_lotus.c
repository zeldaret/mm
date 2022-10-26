/*
 * File: z_bg_lotus.c
 * Overlay: ovl_Bg_Lotus
 * Description: Lily pad
 */

#include "z_bg_lotus.h"
#include "objects/object_lotus/object_lotus.h"

#define FLAGS 0x00000000

#define THIS ((BgLotus*)thisx)

void BgLotus_Init(Actor* thisx, PlayState* play2);
void BgLotus_Destroy(Actor* thisx, PlayState* play2);
void BgLotus_Update(Actor* thisx, PlayState* play2);
void BgLotus_Draw(Actor* thisx, PlayState* play);

void func_80AD68DC(BgLotus* this, PlayState* play);
void func_80AD6A88(BgLotus* this, PlayState* play);
void func_80AD6B68(BgLotus* this, PlayState* play);

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

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void BgLotus_Init(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    BgLotus* this = (BgLotus*)thisx;
    s32 sp2C;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 1);
    DynaPolyActor_LoadMesh(play, &this->dyna, &gLilyPadCol);
    this->dyna.actor.floorHeight = BgCheck_EntityRaycastFloor5(&play->colCtx, &this->dyna.actor.floorPoly, &sp2C,
                                                               &this->dyna.actor, &this->dyna.actor.world.pos);
    this->unk_168 = 96;
    this->dyna.actor.world.rot.y = (s32)Rand_Next() >> 0x10;
    this->actionFunc = func_80AD68DC;
}

void BgLotus_Destroy(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    BgLotus* this = (BgLotus*)thisx;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void func_80AD6830(BgLotus* this) {
    if (this->dyna.actor.params == 0) {
        f32 temp_fv1 = sin_rad(this->unk_166 * (M_PI / 4.0f)) * ((0.014f * ((f32)this->unk_166 / 8)) + 0.01f);

        this->dyna.actor.scale.x = (1.0f + temp_fv1) * 0.1f;
        this->dyna.actor.scale.z = (1.0f - temp_fv1) * 0.1f;
    }
}

void func_80AD68DC(BgLotus* this, PlayState* play) {
    f32 sp34;

    this->unk_168--;
    sp34 = sin_rad(this->unk_168 * (M_PI / 48.0f)) * 6.0f;
    if (this->dyna.actor.params == 0) {
        this->dyna.actor.world.pos.x = (Math_SinS(this->dyna.actor.world.rot.y) * sp34) + this->dyna.actor.home.pos.x;
        this->dyna.actor.world.pos.z = (Math_CosS(this->dyna.actor.world.rot.y) * sp34) + this->dyna.actor.home.pos.z;
        if (this->unk_168 == 0) {
            this->unk_168 = 96;
            this->dyna.actor.world.rot.y += (s16)((s32)Rand_Next() >> 0x12);
        }
    }
    if (this->unk_160 < this->dyna.actor.floorHeight) {
        this->dyna.actor.world.pos.y = this->dyna.actor.floorHeight;
    } else {
        this->dyna.actor.world.pos.y = this->unk_160;
        if (DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
            if (!this->unk_164) {
                EffectSsGRipple_Spawn(play, &this->dyna.actor.world.pos, 1000, 1400, 0);
                EffectSsGRipple_Spawn(play, &this->dyna.actor.world.pos, 1000, 1400, 8);
                this->unk_166 = 40;
            }
            if (gSaveContext.save.playerForm != PLAYER_FORM_DEKU) {
                this->unk_166 = 40;
                this->dyna.actor.flags |= ACTOR_FLAG_10;
                this->actionFunc = func_80AD6A88;
                return;
            }
            this->unk_164 = true;
        } else {
            this->unk_164 = false;
        }
    }
    if (this->unk_166 > 0) {
        this->unk_166--;
    }
    func_80AD6830(this);
}

void func_80AD6A88(BgLotus* this, PlayState* play) {
    if (this->unk_160 < this->dyna.actor.world.pos.y) {
        this->dyna.actor.world.pos.y = this->unk_160;
    }
    this->dyna.actor.world.pos.y -= 1.0f;
    if (this->dyna.actor.world.pos.y <= this->dyna.actor.floorHeight) {
        this->dyna.actor.world.pos.y = this->dyna.actor.floorHeight;
        this->unk_166 = 0;
    }
    if (this->unk_166 > 0) {
        this->unk_166--;
        func_80AD6830(this);
    } else {
        if (Math_StepToF(&this->dyna.actor.scale.x, 0.0f, 0.1f * 0.05f)) {
            this->dyna.actor.draw = NULL;
            this->unk_166 = 100;
            func_800C62BC(play, &play->colCtx.dyna, this->dyna.bgId);
            this->actionFunc = func_80AD6B68;
        }
        this->dyna.actor.scale.z = this->dyna.actor.scale.x;
    }
}

void func_80AD6B68(BgLotus* this, PlayState* play) {
    if (this->unk_166 > 0) {
        this->unk_166--;
    } else if ((this->dyna.actor.xzDistToPlayer > 100.0f) && (this->dyna.actor.projectedPos.z < 0.0f)) {
        this->dyna.actor.draw = BgLotus_Draw;
        func_800C6314(play, &play->colCtx.dyna, this->dyna.bgId);
        Actor_SetScale(&this->dyna.actor, 0.1f);
        this->dyna.actor.world.pos.y = MAX(this->dyna.actor.floorHeight, this->unk_160);
        this->dyna.actor.flags &= ~ACTOR_FLAG_10;
        this->unk_168 = 96;
        this->actionFunc = func_80AD68DC;
        this->dyna.actor.world.pos.x = this->dyna.actor.home.pos.x;
        this->dyna.actor.world.pos.z = this->dyna.actor.home.pos.z;
    }
}

void BgLotus_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    BgLotus* this = (BgLotus*)thisx;
    WaterBox* sp2C;

    WaterBox_GetSurface1_2(play, &play->colCtx, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.z,
                           &this->unk_160, &sp2C);
    this->actionFunc(this, play);
}

void BgLotus_Draw(Actor* thisx, PlayState* play) {
    Gfx_DrawDListOpa(play, gLilyPadDL);
}
