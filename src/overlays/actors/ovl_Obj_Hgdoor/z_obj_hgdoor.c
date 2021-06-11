#include "z_obj_hgdoor.h"

#define FLAGS 0x00100000

#define THIS ((ObjHgdoor*)thisx)

void ObjHgdoor_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHgdoor_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHgdoor_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHgdoor_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Hgdoor_InitVars = {
    ACTOR_OBJ_HGDOOR,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_HGDOOR,
    sizeof(ObjHgdoor),
    (ActorFunc)ObjHgdoor_Init,
    (ActorFunc)ObjHgdoor_Destroy,
    (ActorFunc)ObjHgdoor_Update,
    (ActorFunc)ObjHgdoor_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hgdoor/func_80BD4090.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hgdoor/func_80BD40D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hgdoor/ObjHgdoor_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hgdoor/ObjHgdoor_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hgdoor/func_80BD41E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hgdoor/func_80BD41FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hgdoor/func_80BD42AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hgdoor/func_80BD42C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hgdoor/func_80BD433C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hgdoor/func_80BD4358.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hgdoor/func_80BD4460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hgdoor/func_80BD4478.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hgdoor/func_80BD44D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hgdoor/func_80BD4500.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hgdoor/ObjHgdoor_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hgdoor/ObjHgdoor_Draw.s")
