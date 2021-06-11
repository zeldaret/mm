#include "z_obj_lightblock.h"

#define FLAGS 0x00000000

#define THIS ((ObjLightblock*)thisx)

void ObjLightblock_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjLightblock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjLightblock_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjLightblock_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Lightblock_InitVars = {
    ACTOR_OBJ_LIGHTBLOCK,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_LIGHTBLOCK,
    sizeof(ObjLightblock),
    (ActorFunc)ObjLightblock_Init,
    (ActorFunc)ObjLightblock_Destroy,
    (ActorFunc)ObjLightblock_Update,
    (ActorFunc)ObjLightblock_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/func_80AF3910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/ObjLightblock_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/ObjLightblock_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/func_80AF3AC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/func_80AF3ADC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/func_80AF3B8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/func_80AF3BA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/func_80AF3C18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/func_80AF3C34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/ObjLightblock_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/ObjLightblock_Draw.s")
