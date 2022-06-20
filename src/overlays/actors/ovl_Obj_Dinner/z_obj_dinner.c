/*
 * File: z_obj_dinner.c
 * Overlay: ovl_Obj_Dinner
 * Description: Cremia and Romani's dinner
 */

#include "z_obj_dinner.h"
#include "objects/object_obj_dinner/object_obj_dinner.h"

#define FLAGS (ACTOR_FLAG_20)

#define THIS ((ObjDinner*)thisx)

void ObjDinner_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjDinner_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjDinner_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjDinner_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Dinner_InitVars = {
    ACTOR_OBJ_DINNER,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_OBJ_DINNER,
    sizeof(ObjDinner),
    (ActorFunc)ObjDinner_Init,
    (ActorFunc)ObjDinner_Destroy,
    (ActorFunc)ObjDinner_Update,
    (ActorFunc)ObjDinner_Draw,
};

void ObjDinner_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjDinner* this = THIS;

    if (gSaveContext.save.isNight != true || (CURRENT_DAY == 3 && gSaveContext.save.weekEventReg[22] & 1)) {
        Actor_MarkForDeath(&this->actor);
    }
    Actor_SetScale(&this->actor, 0.1f);
}

void ObjDinner_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void ObjDinner_Update(Actor* thisx, GlobalContext* globalCtx) {
}

void ObjDinner_Draw(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_obj_dinner_DL_0011E0);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
