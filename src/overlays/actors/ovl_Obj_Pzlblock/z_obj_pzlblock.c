#include "z_obj_pzlblock.h"

#define FLAGS 0x04000010

#define THIS ((ObjPzlblock*)thisx)

void ObjPzlblock_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjPzlblock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjPzlblock_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Pzlblock_InitVars = {
    ACTOR_OBJ_PZLBLOCK,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjPzlblock),
    (ActorFunc)ObjPzlblock_Init,
    (ActorFunc)ObjPzlblock_Destroy,
    (ActorFunc)ObjPzlblock_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Pzlblock_0x809A33E0/func_809A33E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Pzlblock_0x809A33E0/func_809A3448.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Pzlblock_0x809A33E0/func_809A34E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Pzlblock_0x809A33E0/func_809A35EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Pzlblock_0x809A33E0/func_809A376C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Pzlblock_0x809A33E0/ObjPzlblock_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Pzlblock_0x809A33E0/ObjPzlblock_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Pzlblock_0x809A33E0/func_809A3A48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Pzlblock_0x809A33E0/func_809A3A74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Pzlblock_0x809A33E0/func_809A3BA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Pzlblock_0x809A33E0/func_809A3BC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Pzlblock_0x809A33E0/func_809A3D1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Pzlblock_0x809A33E0/func_809A3D38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Pzlblock_0x809A33E0/ObjPzlblock_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Pzlblock_0x809A33E0/func_809A3E58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Pzlblock_0x809A33E0/func_809A3F0C.asm")
