#include "z_obj_lightswitch.h"

#define FLAGS 0x00000010

#define THIS ((ObjLightswitch*)thisx)

void ObjLightswitch_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjLightswitch_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjLightswitch_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjLightswitch_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Lightswitch_InitVars = {
    ACTOR_OBJ_LIGHTSWITCH,
    ACTORCAT_SWITCH,
    FLAGS,
    OBJECT_LIGHTSWITCH,
    sizeof(ObjLightswitch),
    (ActorFunc)ObjLightswitch_Init,
    (ActorFunc)ObjLightswitch_Destroy,
    (ActorFunc)ObjLightswitch_Update,
    (ActorFunc)ObjLightswitch_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/func_8095FBF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/func_8095FC94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/func_8095FCEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/ObjLightswitch_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/ObjLightswitch_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/func_8095FFF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/func_80960014.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/func_80960088.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/func_809600BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/func_8096012C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/func_80960148.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/func_80960224.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/func_80960260.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/func_8096034C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/func_80960370.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/func_80960424.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/func_80960440.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/ObjLightswitch_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/func_809605F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/func_80960880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightswitch/ObjLightswitch_Draw.s")
