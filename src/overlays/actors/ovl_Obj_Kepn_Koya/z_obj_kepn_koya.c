/*
 * File: z_obj_kepn_koya.c
 * Overlay: ovl_Obj_Kepn_Koya
 * Description: Gorman Bros. Buildings
 */

#include "z_obj_kepn_koya.h"
#include "objects/object_kepn_koya/object_kepn_koya.h"

#define FLAGS 0x00000000

#define THIS ((ObjKepnKoya*)thisx)

void ObjKepnKoya_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjKepnKoya_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjKepnKoya_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjKepnKoya_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Kepn_Koya_InitVars = {
    ACTOR_OBJ_KEPN_KOYA,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_KEPN_KOYA,
    sizeof(ObjKepnKoya),
    (ActorFunc)ObjKepnKoya_Init,
    (ActorFunc)ObjKepnKoya_Destroy,
    (ActorFunc)ObjKepnKoya_Update,
    (ActorFunc)ObjKepnKoya_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 900, ICHAIN_STOP),
};

void ObjKepnKoya_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjKepnKoya* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    Actor_SetScale(&this->dyna.actor, 0.1f);
    DynaPolyActor_Init(&this->dyna, 0);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_kepn_koya_Colheader_00805C);
    if (this->dyna.bgId == BG_ACTOR_MAX) {
        Actor_MarkForDeath(&this->dyna.actor);
    }
}

void ObjKepnKoya_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjKepnKoya* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void ObjKepnKoya_Update(Actor* thisx, GlobalContext* globalCtx) {
}

void ObjKepnKoya_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, object_kepn_koya_DL_003478);
}
