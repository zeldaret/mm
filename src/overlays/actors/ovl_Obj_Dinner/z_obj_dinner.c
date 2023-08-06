/*
 * File: z_obj_dinner.c
 * Overlay: ovl_Obj_Dinner
 * Description: Cremia and Romani's dinner
 */

#include "z_obj_dinner.h"
#include "objects/object_obj_dinner/object_obj_dinner.h"

#define FLAGS (ACTOR_FLAG_20)

#define THIS ((ObjDinner*)thisx)

void ObjDinner_Init(Actor* thisx, PlayState* play);
void ObjDinner_Destroy(Actor* thisx, PlayState* play);
void ObjDinner_Update(Actor* thisx, PlayState* play);
void ObjDinner_Draw(Actor* thisx, PlayState* play);

ActorInit Obj_Dinner_InitVars = {
    /**/ ACTOR_OBJ_DINNER,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ OBJECT_OBJ_DINNER,
    /**/ sizeof(ObjDinner),
    /**/ ObjDinner_Init,
    /**/ ObjDinner_Destroy,
    /**/ ObjDinner_Update,
    /**/ ObjDinner_Draw,
};

void ObjDinner_Init(Actor* thisx, PlayState* play) {
    ObjDinner* this = THIS;

    if ((gSaveContext.save.isNight != true) ||
        ((CURRENT_DAY == 3) && CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM))) {
        Actor_Kill(&this->actor);
    }
    Actor_SetScale(&this->actor, 0.1f);
}

void ObjDinner_Destroy(Actor* thisx, PlayState* play) {
}

void ObjDinner_Update(Actor* thisx, PlayState* play) {
}

void ObjDinner_Draw(Actor* thisx, PlayState* play) {
    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_obj_dinner_DL_0011E0);

    CLOSE_DISPS(play->state.gfxCtx);
}
