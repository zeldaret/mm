#include "z_obj_dinner.h"

#define FLAGS 0x00000020

#define THIS ((ObjDinner*)thisx)

void ObjDinner_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjDinner_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjDinner_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjDinner_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Dinner_InitVars = {
    ACTOR_OBJ_DINNER,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_OBJECT_UNSET_DINNER,
    sizeof(ObjDinner),
    (ActorFunc)ObjDinner_Init,
    (ActorFunc)ObjDinner_Destroy,
    (ActorFunc)ObjDinner_Update,
    (ActorFunc)ObjDinner_Draw,
};

extern Gfx D_060011E0[];

void ObjDinner_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjDinner* this = THIS;

    if (gSaveContext.isNight != true || (CURRENT_DAY == 3 && gSaveContext.weekEventReg[0x16] & 1)) {
        Actor_MarkForDeath(&this->actor);
    }
    Actor_SetScale(&this->actor, 0.1f);
}

void ObjDinner_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void ObjDinner_Update(Actor* thisx, GlobalContext* globalCtx) {
}

void ObjDinner_Draw(Actor* thisx, GlobalContext* globalCtx) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad;

    func_8012C28C(gfxCtx);
    gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxCtx->polyOpa.p++, D_060011E0);
}
