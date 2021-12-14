/*
 * File: z_obj_jg_gakki.c
 * Overlay: ovl_Obj_Jg_Gakki
 * Description: Goron Elder's Drum
 */

#include "z_obj_jg_gakki.h"

#define FLAGS 0x00000020

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

extern AnimationHeader D_0601B1E8;
extern SkeletonHeader D_0601B210;

void ObjJgGakki_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    ObjJgGakki* this = THIS;
    f32 frameCount = Animation_GetLastFrame(&D_0601B1E8);

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 24.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_0601B210, NULL, NULL, NULL, 0);

    if (((globalCtx->sceneNum == SCENE_SPOT00) && (gSaveContext.sceneSetupIndex == 7)) &&
        (globalCtx->csCtx.unk_12 == 0)) {
        Animation_Change(&this->skelAnime, &D_0601B1E8, 1.0f, frameCount, frameCount, 2, 0.0f);
    } else if ((globalCtx->sceneNum == SCENE_17SETUGEN) || (globalCtx->sceneNum == SCENE_10YUKIYAMANOMURA)) {
        Animation_Change(&this->skelAnime, &D_0601B1E8, 1.0f, 0.0f, frameCount, 2, 0.0f);
    } else {
        Actor_MarkForDeath(&this->actor);
    }
    Actor_SetScale(&this->actor, 0.01f);
}

void ObjJgGakki_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjJgGakki* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->colliderCylinder);
}

void ObjJgGakki_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjJgGakki* this = THIS;

    SkelAnime_Update(&this->skelAnime);
}

void ObjJgGakki_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjJgGakki* this = THIS;

    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, NULL, NULL, &this->actor);
}
