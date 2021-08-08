#include "z_obj_hariko.h"

#define FLAGS 0x02000020

#define THIS ((ObjHariko*)thisx)

void ObjHariko_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHariko_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHariko_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHariko_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B66A90(ObjHariko* this, GlobalContext* globalCtx);
void func_80B66AC4(ObjHariko* this, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Hariko_InitVars = {
    ACTOR_OBJ_HARIKO,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_HARIKO,
    sizeof(ObjHariko),
    (ActorFunc)ObjHariko_Init,
    (ActorFunc)ObjHariko_Destroy,
    (ActorFunc)ObjHariko_Update,
    (ActorFunc)ObjHariko_Draw,
};

#endif

extern UNK_TYPE D_06000080;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hariko/ObjHariko_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hariko/ObjHariko_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hariko/func_80B66A7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hariko/func_80B66A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hariko/func_80B66AA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hariko/func_80B66AC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hariko/func_80B66B78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hariko/ObjHariko_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hariko/ObjHariko_Draw.s")
