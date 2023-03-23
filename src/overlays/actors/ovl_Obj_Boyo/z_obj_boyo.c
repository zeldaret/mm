#include "z_obj_boyo.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjBoyo*)thisx)

void ObjBoyo_Init(Actor* thisx, PlayState* play);
void ObjBoyo_Destroy(Actor* thisx, PlayState* play2);
void ObjBoyo_Update(Actor* thisx, PlayState* play2);
void ObjBoyo_Draw(Actor* thisx, PlayState* play);

/*
const ActorInit Obj_Boyo_InitVars = {
    ACTOR_OBJ_BOYO,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BOYO,
    sizeof(ObjBoyo),
    (ActorFunc)ObjBoyo_Init,
    (ActorFunc)ObjBoyo_Destroy,
    (ActorFunc)ObjBoyo_Update,
    (ActorFunc)ObjBoyo_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/ObjBoyo_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/ObjBoyo_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/func_809A5DC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/func_809A5DE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/func_809A5E14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/func_809A5E24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/ObjBoyo_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boyo/ObjBoyo_Draw.s")
