#include "z_obj_comb.h"

#define FLAGS 0x00000000

#define THIS ((ObjComb*)thisx)

void ObjComb_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjComb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjComb_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjComb_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Comb_InitVars = {
    ACTOR_OBJ_COMB,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_COMB,
    sizeof(ObjComb),
    (ActorFunc)ObjComb_Init,
    (ActorFunc)ObjComb_Destroy,
    (ActorFunc)ObjComb_Update,
    (ActorFunc)ObjComb_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Comb/func_8098CE40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Comb/func_8098CEAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Comb/func_8098D19C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Comb/func_8098D47C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Comb/func_8098D6E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Comb/func_8098D870.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Comb/func_8098D8C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Comb/func_8098D99C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Comb/func_8098DA74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Comb/ObjComb_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Comb/ObjComb_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Comb/func_8098DC44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Comb/func_8098DC60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Comb/func_8098DE58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Comb/func_8098DEA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Comb/func_8098E098.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Comb/func_8098E0B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Comb/ObjComb_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Comb/ObjComb_Draw.s")
