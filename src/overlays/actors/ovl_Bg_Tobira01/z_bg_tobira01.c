/*
 * File: z_bg_tobira01.c
 * Overlay: ovl_Bg_Tobira01
 * Description: Gate to Goron Shrine
 */

#include "z_bg_tobira01.h"
#include "objects/object_spot11_obj/object_spot11_obj.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((BgTobira01*)thisx)

void BgTobira01_Init(Actor* thisx, PlayState* play);
void BgTobira01_Destroy(Actor* thisx, PlayState* play);
void BgTobira01_Update(Actor* thisx, PlayState* play);
void BgTobira01_Draw(Actor* thisx, PlayState* play);
void func_80B12430(BgTobira01 *this, PlayState *play);

const ActorInit Bg_Tobira01_InitVars = {
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

const f32 D_80B12820 = 1.6666666f;

void func_80B12430(BgTobira01 *this, PlayState *play) {
    Player* sp1C = GET_PLAYER(play);
    s16 temp_a2 = this->dyna.actor.csId;
    s16 temp;
    if (this->unk168 != 0) {
        if (CutsceneManager_GetCurrentCsId() == 0x7C) {
            CutsceneManager_Stop(0x7C);
        } else if (CutsceneManager_IsNext(temp_a2) != 0) {
            CutsceneManager_StartWithPlayerCs(temp_a2, &this->dyna.actor);
            gSaveContext.save.saveInfo.weekEventReg[88] |= 0x40;
            this->unk168 = 0;
        } else {
            CutsceneManager_Queue(temp_a2);
        }
    } else if (!(gSaveContext.save.saveInfo.weekEventReg[88] & 0x40) &&
     (this->unk160 == 0) && (play->actorCtx.playerImpact.timer != 0) &&
      (play->actorCtx.playerImpact.type == 0) &&
       (SurfaceType_GetSceneExitIndex(&play->colCtx, sp1C->actor.floorPoly, sp1C->actor.floorBgId) == 6)) {
        this->unk168 = 1;
        this->unk16C = 0;
    }

    temp = this->unk160;
    if (gSaveContext.save.saveInfo.weekEventReg[88] & 0x40){
        this->unk160 += 1;
    }else{
        this->unk160 -= 1;
    }

    this->unk160 = CLAMP(this->unk160, 0, 0x3C);
    if(temp != this->unk160){
        Actor_PlaySfx(&this->dyna.actor, 0x2143U);
        this->dyna.actor.world.pos.y = (this->unk164 = (this->unk160 * D_80B12820) + this->dyna.actor.home.pos.y);
        this->unk162 = 0xB4;
    }

    if (!(sp1C->stateFlags1 & 0x40) && (gSaveContext.save.saveInfo.weekEventReg[88] & 0x40) && DECR(this->unk162) == 0) {
        gSaveContext.save.saveInfo.weekEventReg[88] &= 0xBF;
    }
}

void BgTobira01_Init(Actor *thisx, PlayState *play) {
    BgTobira01 *this = THIS;
    DynaPolyActor_Init((DynaPolyActor *) this, 1);
    DynaPolyActor_LoadMesh(play, (DynaPolyActor *) this, &object_spot11_obj_Colheader_0011C0);
    gSaveContext.save.saveInfo.weekEventReg[88] &= 0xBF;
    Actor_SetScale(&this->dyna.actor, 1.0f);
    this->unk162 = gSaveContext.save.isNight;
    this->unk160 = 0;
    this->unk15C = func_80B12430;
}

void BgTobira01_Destroy(Actor *thisx, PlayState *play) {
    BgTobira01 *this = THIS;
    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void BgTobira01_Update(Actor *thisx, PlayState *play) {
    BgTobira01 *this = THIS;
    this->unk15C(this, play);
}

void BgTobira01_Draw(Actor *thisx, PlayState *play) {
    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_spot11_obj_DL_000088);
    CLOSE_DISPS(play->state.gfxCtx);
}

