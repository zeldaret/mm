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
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_COMB,
    sizeof(ObjComb),
    (ActorFunc)ObjComb_Init,
    (ActorFunc)ObjComb_Destroy,
    (ActorFunc)ObjComb_Update,
    (ActorFunc)ObjComb_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Comb_0x8098CE40/func_8098CE40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Comb_0x8098CE40/func_8098CEAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Comb_0x8098CE40/func_8098D19C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Comb_0x8098CE40/func_8098D47C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Comb_0x8098CE40/func_8098D6E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Comb_0x8098CE40/func_8098D870.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Comb_0x8098CE40/func_8098D8C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Comb_0x8098CE40/func_8098D99C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Comb_0x8098CE40/func_8098DA74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Comb_0x8098CE40/ObjComb_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Comb_0x8098CE40/ObjComb_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Comb_0x8098CE40/func_8098DC44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Comb_0x8098CE40/func_8098DC60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Comb_0x8098CE40/func_8098DE58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Comb_0x8098CE40/func_8098DEA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Comb_0x8098CE40/func_8098E098.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Comb_0x8098CE40/func_8098E0B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Comb_0x8098CE40/ObjComb_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Comb_0x8098CE40/ObjComb_Draw.asm")
