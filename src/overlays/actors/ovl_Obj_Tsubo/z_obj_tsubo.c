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
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_809275C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_8092762C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_80927690.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_80927714.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_8092776C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_80927818.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_80927864.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_8092788C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/ObjTsubo_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/ObjTsubo_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_80927A78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_80927D2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_80927FCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_809282F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_8092860C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_80928904.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_80928914.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_80928928.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_809289B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_809289E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_80928D6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_80928D80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_80928E74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_80928F18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_809291DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_8092926C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/ObjTsubo_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tsubo_0x809275C0/func_809294B0.asm")
