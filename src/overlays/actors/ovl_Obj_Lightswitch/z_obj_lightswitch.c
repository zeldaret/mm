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

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_8095FBF0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_8095FC94.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_8095FCEC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/ObjLightswitch_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/ObjLightswitch_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_8095FFF8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_80960014.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_80960088.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_809600BC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_8096012C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_80960148.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_80960224.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_80960260.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_8096034C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_80960370.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_80960424.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_80960440.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/ObjLightswitch_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_809605F4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_80960880.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/ObjLightswitch_Draw.asm")
