#include "z_obj_hariko.h"

#define FLAGS 0x02000020

#define THIS ((ObjHariko*)thisx)

void ObjHariko_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHariko_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHariko_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHariko_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Hariko_InitVars = {
    ACTOR_OBJ_HARIKO,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_HARIKO,
    sizeof(ObjHariko),
    (ActorFunc)ObjHariko_Init,
    (ActorFunc)ObjHariko_Destroy,
    (ActorFunc)ObjHariko_Update,
    (ActorFunc)ObjHariko_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hariko_0x80B66A20/ObjHariko_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hariko_0x80B66A20/ObjHariko_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hariko_0x80B66A20/func_80B66A7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hariko_0x80B66A20/func_80B66A90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hariko_0x80B66A20/func_80B66AA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hariko_0x80B66A20/func_80B66AC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hariko_0x80B66A20/func_80B66B78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hariko_0x80B66A20/ObjHariko_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hariko_0x80B66A20/ObjHariko_Draw.asm")
