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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lightblock_0x80AF3910/func_80AF3910.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lightblock_0x80AF3910/ObjLightblock_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lightblock_0x80AF3910/ObjLightblock_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lightblock_0x80AF3910/func_80AF3AC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lightblock_0x80AF3910/func_80AF3ADC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lightblock_0x80AF3910/func_80AF3B8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lightblock_0x80AF3910/func_80AF3BA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lightblock_0x80AF3910/func_80AF3C18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lightblock_0x80AF3910/func_80AF3C34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lightblock_0x80AF3910/ObjLightblock_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lightblock_0x80AF3910/ObjLightblock_Draw.asm")
