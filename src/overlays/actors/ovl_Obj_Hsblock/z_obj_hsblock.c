#include "z_obj_hsblock.h"

#define FLAGS 0x00000000

#define THIS ((ObjHsblock*)thisx)

void ObjHsblock_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHsblock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHsblock_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHsblock_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Hsblock_InitVars = {
    ACTOR_OBJ_HSBLOCK,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_D_HSBLOCK,
    sizeof(ObjHsblock),
    (ActorFunc)ObjHsblock_Init,
    (ActorFunc)ObjHsblock_Destroy,
    (ActorFunc)ObjHsblock_Update,
    (ActorFunc)ObjHsblock_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hsblock/func_8093DEA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hsblock/func_8093DEAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hsblock/ObjHsblock_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hsblock/ObjHsblock_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hsblock/func_8093E03C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hsblock/func_8093E05C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hsblock/func_8093E0A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hsblock/func_8093E0E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hsblock/func_8093E10C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hsblock/ObjHsblock_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hsblock/ObjHsblock_Draw.s")
