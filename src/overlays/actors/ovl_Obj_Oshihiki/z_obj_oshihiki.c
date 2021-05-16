#include "z_obj_oshihiki.h"

#define FLAGS 0x00000010

#define THIS ((ObjOshihiki*)thisx)

void ObjOshihiki_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjOshihiki_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjOshihiki_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjOshihiki_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Oshihiki_InitVars = {
    ACTOR_OBJ_OSHIHIKI,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_DANGEON_KEEP,
    sizeof(ObjOshihiki),
    (ActorFunc)ObjOshihiki_Init,
    (ActorFunc)ObjOshihiki_Destroy,
    (ActorFunc)ObjOshihiki_Update,
    (ActorFunc)ObjOshihiki_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_80917290.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_809172E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_8091734C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_80917378.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_80917408.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_80917538.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_80917604.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_8091763C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_8091768C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/ObjOshihiki_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/ObjOshihiki_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_80917840.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_809179A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_80917AEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_80917B44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_80917B9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_80917C14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_80917E8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_80917F88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_80917FC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_809180C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_80918108.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_80918314.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_8091834C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_8091851C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/func_80918574.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/ObjOshihiki_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Oshihiki/ObjOshihiki_Draw.s")
