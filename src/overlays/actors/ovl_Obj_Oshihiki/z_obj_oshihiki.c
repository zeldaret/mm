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
    ACTORTYPE_PROP,
    FLAGS,
    GAMEPLAY_DANGEON_KEEP,
    sizeof(ObjOshihiki),
    (ActorFunc)ObjOshihiki_Init,
    (ActorFunc)ObjOshihiki_Destroy,
    (ActorFunc)ObjOshihiki_Update,
    (ActorFunc)ObjOshihiki_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_80917290.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_809172E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_8091734C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_80917378.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_80917408.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_80917538.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_80917604.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_8091763C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_8091768C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/ObjOshihiki_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/ObjOshihiki_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_80917840.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_809179A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_80917AEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_80917B44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_80917B9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_80917C14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_80917E8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_80917F88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_80917FC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_809180C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_80918108.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_80918314.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_8091834C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_8091851C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/func_80918574.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/ObjOshihiki_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Oshihiki_0x80917290/ObjOshihiki_Draw.asm")
