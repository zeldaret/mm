/*
 * File: z_obj_blockstop.c
 * Overlay: ovl_Obj_Blockstop
 * Description: Push Block Trigger - Blockstop switch triggered by pushblock (Snowhead)
 */

#include "z_obj_blockstop.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjBlockstop*)thisx)

void ObjBlockstop_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBlockstop_Update(Actor* thisx, GlobalContext* globalCtx);

void func_809466F0(ObjBlockstop* this, GlobalContext* globalCtx);
void func_809467E8(ObjBlockstop *arg0, GlobalContext *arg1);


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



void ObjBlockstop_Init(Actor *thisx, GlobalContext *globalCtx) {
    ObjBlockstop *this = THIS;
    if (Flags_GetSwitch(globalCtx, (s32) this->actor.params)) {
        Actor_MarkForDeath(&this->actor);
    }
    this->actionFunc = func_809466F0;
}





//checks that the position of the push block is within 20 units and activates, since the block falls and stops on the blockstop
void func_809466F0(ObjBlockstop *this, GlobalContext *globalCtx) {
    Actor *tempActor;
    tempActor = globalCtx->actorCtx.actorLists[6].first;
        while (tempActor){
            if ((tempActor->id == 0x7A) && //check if oshihiki (push block)
            (fabsf(tempActor->world.pos.x - this->actor.world.pos.x) < 20.0f) && //check coords for collision
            (fabsf(tempActor->world.pos.z - this->actor.world.pos.z) < 20.0f) && 
            (fabsf(tempActor->world.pos.y - this->actor.world.pos.y) < 20.0f)) {
                 
                s32 params = (tempActor->params & 0xF);
                if(params < 3){
                    ActorCutscene_SetIntentToPlay((s16) this->actor.cutscene);
                    this->actionFunc = func_809467E8;
                }
            }
            tempActor = tempActor->next;
        }
    
}



void func_809467E8(ObjBlockstop *arg0, GlobalContext *arg1) {
    if (ActorCutscene_GetCanPlayNext((s16) arg0->actor.cutscene) != 0) {
        Flags_SetSwitch(arg1, (s32) arg0->actor.params);
        if (ActorCutscene_GetLength((s16) arg0->actor.cutscene) != -1) {
            ActorCutscene_StartAndSetUnkLinkFields((s16) arg0->actor.cutscene, &arg0->actor);
        }
        Actor_MarkForDeath(&arg0->actor);
        return;
    }
    ActorCutscene_SetIntentToPlay((s16) arg0->actor.cutscene);
}

void ObjBlockstop_Update(Actor *thisx, GlobalContext *globalCtx) {
    ObjBlockstop *this = (ObjBlockstop *) thisx;
    this->actionFunc(this, globalCtx);
}
