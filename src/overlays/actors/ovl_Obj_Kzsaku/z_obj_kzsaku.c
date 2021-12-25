/*
 * File: z_obj_kzsaku.c
 * Overlay: ovl_Obj_Kzsaku
 * Description: Underwater grate
 */

#include "z_obj_kzsaku.h"

#define FLAGS 0x00000030

#define THIS ((ObjKzsaku*)thisx)

void ObjKzsaku_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjKzsaku_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjKzsaku_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjKzsaku_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C08B60(ObjKzsaku* this);
void func_80C08BBC(ObjKzsaku* this);
void func_80C08C84(ObjKzsaku* this);
void func_80C08B7C(ObjKzsaku* this, GlobalContext* globalCtx);
void func_80C08BD0(ObjKzsaku* this, GlobalContext* globalCtx);
void func_80C08CB0(ObjKzsaku* this, GlobalContext* globalCtx);

const ActorInit Obj_Kzsaku_InitVars = {
    ACTOR_OBJ_KZSAKU,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_KZSAKU,
    sizeof(ObjKzsaku),
    (ActorFunc)ObjKzsaku_Init,
    (ActorFunc)ObjKzsaku_Destroy,
    (ActorFunc)ObjKzsaku_Update,
    (ActorFunc)ObjKzsaku_Draw,
};

extern Gfx D_06000040[];
extern CollisionHeader D_06001118;

void ObjKzsaku_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjKzsaku* this = THIS;
    s32 pad;
    CollisionHeader* col = NULL;

    Actor_SetScale(&this->dyna.actor, 1.0f);
    DynaPolyActor_Init(&this->dyna, 1);
    CollisionHeader_GetVirtual(&D_06001118, &col);

    this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, thisx, col);

    this->switchFlag = KZSAKU_GET_SWITCHFLAG(thisx);
    this->raisedAmount = 0.0f;

    if (Flags_GetSwitch(globalCtx, this->switchFlag)) {
        func_80C08C84(this);
    } else {
        func_80C08B60(this);
    }
}

void ObjKzsaku_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjKzsaku* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void func_80C08B60(ObjKzsaku* this) {
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y;
    this->actionFunc = func_80C08B7C;
}

void func_80C08B7C(ObjKzsaku* this, GlobalContext* globalCtx) {
    if (Flags_GetSwitch(globalCtx, this->switchFlag)) {
        func_80C08BBC(this);
    }
}

void func_80C08BBC(ObjKzsaku* this) {
    this->actionFunc = func_80C08BD0;
}

void func_80C08BD0(ObjKzsaku* this, GlobalContext* globalCtx) {
    if (this->dyna.actor.cutscene != -1) {
        if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        } else {
            ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
        }
    }
    if (this->raisedAmount < 450.0f) {
        func_800B9010(&this->dyna.actor, NA_SE_EV_METALDOOR_SLIDE - SFX_FLAG);
        this->raisedAmount += 15.0f;
    } else {
        func_80C08C84(this);
    }
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + this->raisedAmount;
}

void func_80C08C84(ObjKzsaku* this) {
    this->timer = 0;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 450.0f;
    this->actionFunc = func_80C08CB0;
}

void func_80C08CB0(ObjKzsaku* this, GlobalContext* globalCtx) {
    if (this->timer <= 20) {
        if (this->timer == 20) {
            if (ActorCutscene_GetCurrentIndex() == this->dyna.actor.cutscene) {
                ActorCutscene_Stop(this->dyna.actor.cutscene);
            }
            this->timer = 21;
        } else {
            this->timer++;
        }
    }
}

void ObjKzsaku_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjKzsaku* this = THIS;

    this->actionFunc(this, globalCtx);
}

void ObjKzsaku_Draw(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_06000040);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
