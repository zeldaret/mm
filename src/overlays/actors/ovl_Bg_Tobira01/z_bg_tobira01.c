/*
 * File: z_Bg_Tobira01.c
 * Overlay: ovl_Bg_Tobira01
 * Description: Door to Goron Shrine
 */

#include "z_bg_tobira01.h"
#include "objects/object_spot11_obj/object_spot11_obj.h"

#define FLAGS 0x00000030

#define THIS ((BgTobira01*)thisx)

void BgTobira01_Init(Actor* thisx, PlayState* play2);
void BgTobira01_Destroy(Actor* thisx, PlayState* play2);
void BgTobira01_Update(Actor* thisx, PlayState* play2);
void BgTobira01_Draw(Actor* thisx, PlayState* play);

ActorInit Bg_Tobira01_InitVars = {
    ACTOR_BG_TOBIRA01,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_SPOT11_OBJ,
    sizeof(BgTobira01),
    (ActorFunc)BgTobira01_Init,
    (ActorFunc)BgTobira01_Destroy,
    (ActorFunc)BgTobira01_Update,
    (ActorFunc)BgTobira01_Draw,
};

void func_80B12430(BgTobira01* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 sp1A = this->dyna.actor.cutscene;
    s16 temp_v0;

    if (this->unk_168) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        } else if (ActorCutscene_GetCanPlayNext(sp1A)) {
            ActorCutscene_StartAndSetUnkLinkFields(sp1A, &this->dyna.actor);
            gSaveContext.save.weekEventReg[88] |= 0x40;
            this->unk_168 = false;
        } else {
            ActorCutscene_SetIntentToPlay(sp1A);
        }

    } else if (!(gSaveContext.save.weekEventReg[88] & 0x40) && (this->unk_160 == 0) && (play->actorCtx.unk1F5 != 0) &&
               (play->actorCtx.unk1F4 == 0) &&
               (SurfaceType_GetSceneExitIndex(&play->colCtx, player->actor.floorPoly, player->actor.floorBgId) == 6)) {
        this->unk_168 = true;
        this->unk_16C = 0;
    }
    temp_v0 = this->unk_160;
    if (gSaveContext.save.weekEventReg[88] & 0x40) {
        this->unk_160++;
    } else {
        this->unk_160--;
    }
    this->unk_160 = CLAMP(this->unk_160, 0, 60);
    if (temp_v0 != this->unk_160) {
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_STONEDOOR_OPEN_S - SFX_FLAG);
        this->dyna.actor.world.pos.y = this->unk_164 = (this->unk_160 * (5.0f / 3.0f)) + this->dyna.actor.home.pos.y;
        this->unk_162 = 180;
    }
    if (!(player->stateFlags1 & PLAYER_STATE1_40) && (gSaveContext.save.weekEventReg[88] & 0x40) &&
        (DECR(this->unk_162) == 0)) {
        gSaveContext.save.weekEventReg[88] &= (u8)~0x40;
    }
}

void BgTobira01_Init(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    BgTobira01* this = (BgTobira01*)thisx;

    DynaPolyActor_Init(&this->dyna, 1);
    DynaPolyActor_LoadMesh(play, &this->dyna, &object_spot11_obj_Colheader_0011C0);
    gSaveContext.save.weekEventReg[88] &= (u8)~0x40;
    Actor_SetScale(&this->dyna.actor, 1.0f);
    this->unk_162 = gSaveContext.save.isNight;
    this->unk_160 = 0;
    this->actionFunc = func_80B12430;
}

void BgTobira01_Destroy(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    BgTobira01* this = (BgTobira01*)thisx;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void BgTobira01_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    BgTobira01* this = (BgTobira01*)thisx;

    this->actionFunc(this, play);
}

void BgTobira01_Draw(Actor* thisx, PlayState* play) {
    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_spot11_obj_DL_000088);

    CLOSE_DISPS(play->state.gfxCtx);
}
