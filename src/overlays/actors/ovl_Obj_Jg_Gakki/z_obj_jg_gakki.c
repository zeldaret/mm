/*
 * File: z_obj_jg_gakki.c
 * Overlay: ovl_Obj_Jg_Gakki
 * Description: Goron Elder's Drum
 */

#include "z_obj_jg_gakki.h"
#include "objects/object_jg/object_jg.h"

#define FLAGS (ACTOR_FLAG_20)

#define THIS ((ObjJgGakki*)thisx)

void ObjJgGakki_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjJgGakki_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjJgGakki_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjJgGakki_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Jg_Gakki_InitVars = {
    ACTOR_OBJ_JG_GAKKI,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_JG,
    sizeof(ObjJgGakki),
    (ActorFunc)ObjJgGakki_Init,
    (ActorFunc)ObjJgGakki_Destroy,
    (ActorFunc)ObjJgGakki_Update,
    (ActorFunc)ObjJgGakki_Draw,
};

void ObjJgGakki_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    ObjJgGakki* this = THIS;
    f32 frameCount = Animation_GetLastFrame(&gGoronElderDrumTakeOutAnim);

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &gGoronElderDrumSkel, NULL, NULL, NULL, 0);

    if (((globalCtx->sceneNum == SCENE_SPOT00) && (gSaveContext.sceneSetupIndex == 7)) &&
        (globalCtx->csCtx.currentCsIndex == 0)) {
        Animation_Change(&this->skelAnime, &gGoronElderDrumTakeOutAnim, 1.0f, frameCount, frameCount, 2, 0.0f);
    } else if ((globalCtx->sceneNum == SCENE_17SETUGEN) || (globalCtx->sceneNum == SCENE_10YUKIYAMANOMURA)) {
        Animation_Change(&this->skelAnime, &gGoronElderDrumTakeOutAnim, 1.0f, 0.0f, frameCount, 2, 0.0f);
    } else {
        Actor_MarkForDeath(&this->actor);
    }
    Actor_SetScale(&this->actor, 0.01f);
}

void ObjJgGakki_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjJgGakki* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void ObjJgGakki_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjJgGakki* this = THIS;

    SkelAnime_Update(&this->skelAnime);
}

void ObjJgGakki_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjJgGakki* this = THIS;

    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, NULL, NULL, &this->actor);
}
