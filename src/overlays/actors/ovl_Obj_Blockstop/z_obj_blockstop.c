/*
 * File: z_obj_blockstop.c
 * Overlay: ovl_Obj_Blockstop
 * Description: Push Block Trigger - Blockstop switch triggered by pushblock (Snowhead)
 */

#include "z_obj_blockstop.h"
#include "overlays/actors/ovl_Obj_Oshihiki/z_obj_oshihiki.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjBlockstop*)thisx)

void ObjBlockstop_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBlockstop_Update(Actor* thisx, GlobalContext* globalCtx);

void ObjBlockstop_CheckCollision(ObjBlockstop* this, GlobalContext* globalCtx);
void ObjBlockstop_TryPlayCutscene(ObjBlockstop* arg0, GlobalContext* arg1);

const ActorInit Obj_Blockstop_InitVars = {
    ACTOR_OBJ_BLOCKSTOP,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjBlockstop),
    (ActorFunc)ObjBlockstop_Init,
    (ActorFunc)Actor_Noop,
    (ActorFunc)ObjBlockstop_Update,
    (ActorFunc)NULL,
};

void ObjBlockstop_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjBlockstop* this = THIS;
    if (Flags_GetSwitch(globalCtx, (s32)this->actor.params)) {
        Actor_MarkForDeath(&this->actor);
    }
    this->actionFunc = ObjBlockstop_CheckCollision;
}

void ObjBlockstop_CheckCollision(ObjBlockstop* this, GlobalContext* globalCtx) {
    Actor* tempActor;
    tempActor = globalCtx->actorCtx.actorLists[6].first;
    while (tempActor) {
        if ((tempActor->id == 0x7A) && // check if oshihiki (push block)
            (fabsf(tempActor->world.pos.x - this->actor.world.pos.x) < 20.0f) &&
            (fabsf(tempActor->world.pos.z - this->actor.world.pos.z) < 20.0f) &&
            (fabsf(tempActor->world.pos.y - this->actor.world.pos.y) < 20.0f)) {

            s32 params = OBJOSHIHIKI_GET_F(tempActor);
            if (params < 3) {
                ActorCutscene_SetIntentToPlay((s16)this->actor.cutscene);
                this->actionFunc = ObjBlockstop_TryPlayCutscene;
            }
        }
        tempActor = tempActor->next;
    }
}

void ObjBlockstop_TryPlayCutscene(ObjBlockstop* arg0, GlobalContext* arg1) {
    if (ActorCutscene_GetCanPlayNext((s16)arg0->actor.cutscene) != 0) {
        Flags_SetSwitch(arg1, (s32)arg0->actor.params);
        if (ActorCutscene_GetLength((s16)arg0->actor.cutscene) != -1) {
            ActorCutscene_StartAndSetUnkLinkFields((s16)arg0->actor.cutscene, &arg0->actor);
        }
        Actor_MarkForDeath(&arg0->actor);
        return;
    }
    ActorCutscene_SetIntentToPlay((s16)arg0->actor.cutscene);
}

void ObjBlockstop_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjBlockstop* this = (ObjBlockstop*)thisx;
    this->actionFunc(this, globalCtx);
}
