#include "z_obj_tsubo.h"

#define FLAGS 0x04800010

#define THIS ((ObjTsubo*)thisx)

void ObjTsubo_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTsubo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTsubo_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Tsubo_InitVars = {
    ACTOR_OBJ_TSUBO,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjTsubo),
    (ActorFunc)ObjTsubo_Init,
    (ActorFunc)ObjTsubo_Destroy,
    (ActorFunc)ObjTsubo_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_809275C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_8092762C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80927690.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80927714.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_8092776C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80927818.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80927864.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_8092788C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/ObjTsubo_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/ObjTsubo_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80927A78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80927D2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80927FCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_809282F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_8092860C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80928904.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80928914.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80928928.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_809289B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_809289E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80928D6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80928D80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80928E74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_80928F18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_809291DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_8092926C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/ObjTsubo_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tsubo/func_809294B0.s")
