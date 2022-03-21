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

#if 0
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

#endif

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Blockstop/ObjBlockstop_Init.s")
void ObjBlockstop_Init(Actor *thisx, GlobalContext *globalCtx) {
    ObjBlockstop *this = THIS;
    if (Flags_GetSwitch(globalCtx, (s32) this->actor.params)) {
        Actor_MarkForDeath(&this->actor);
    }
    this->actionFunc = func_809466F0;
}


//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Blockstop/func_809466F0.s")

void func_809467E8(ObjBlockstop *, GlobalContext *); /* extern */

//most likely checks that the position of the push block is within 20 units and activates, since the block falls and stops on the blockstop
void func_809466F0(ObjBlockstop *this, GlobalContext *globalCtx) {
    Actor *phi_s0;
    phi_s0 = globalCtx->actorCtx.actorLists[6].first;
        while (phi_s0){
            if ((phi_s0->id == 0x7A) && //check if oshihiki (push block)
            (fabsf(phi_s0->world.pos.x - this->actor.world.pos.x) < 20.0f) && //check coords for collision
            (fabsf(phi_s0->world.pos.z - this->actor.world.pos.z) < 20.0f) && 
            (fabsf(phi_s0->world.pos.y - this->actor.world.pos.y) < 20.0f)) {
                 
                s32 params = (phi_s0->params & 0xF);
                if(params < 3){
                    ActorCutscene_SetIntentToPlay((s16) this->actor.cutscene);
                    this->actionFunc = func_809467E8;
                }
            }
            phi_s0 = phi_s0->next;
        }
    
}



#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Blockstop/func_809467E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Blockstop/ObjBlockstop_Update.s")
