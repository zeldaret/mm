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
    ACTORTYPE_SWITCH,
    FLAGS,
    OBJECT_LIGHTSWITCH,
    sizeof(ObjLightswitch),
    (ActorFunc)ObjLightswitch_Init,
    (ActorFunc)ObjLightswitch_Destroy,
    (ActorFunc)ObjLightswitch_Update,
    (ActorFunc)ObjLightswitch_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_8095FBF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_8095FC94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_8095FCEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/ObjLightswitch_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/ObjLightswitch_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_8095FFF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_80960014.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_80960088.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_809600BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_8096012C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_80960148.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_80960224.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_80960260.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_8096034C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_80960370.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_80960424.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_80960440.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/ObjLightswitch_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_809605F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/func_80960880.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lightswitch_0x8095FBF0/ObjLightswitch_Draw.asm")
