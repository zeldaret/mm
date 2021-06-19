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
    (ActorFunc)ObjOshihiki_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_80917290.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_809172E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_8091734C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_80917378.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_80917408.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_80917538.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_80917604.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_8091763C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_8091768C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/ObjOshihiki_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/ObjOshihiki_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_80917840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_809179A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_80917AEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_80917B44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_80917B9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_80917C14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_80917E8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_80917F88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_80917FC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_809180C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_80918108.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_80918314.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_8091834C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_8091851C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/func_80918574.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/ObjOshihiki_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Oshihiki_0x80917290/ObjOshihiki_Draw.asm")
