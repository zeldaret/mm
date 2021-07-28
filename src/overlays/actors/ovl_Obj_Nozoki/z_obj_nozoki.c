#include "z_obj_nozoki.h"

#define FLAGS 0x00000010

#define THIS ((ObjNozoki*)thisx)

void ObjNozoki_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjNozoki_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjNozoki_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Nozoki_InitVars = {
    ACTOR_OBJ_NOZOKI,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjNozoki),
    (ActorFunc)ObjNozoki_Init,
    (ActorFunc)ObjNozoki_Destroy,
    (ActorFunc)ObjNozoki_Update,
    (ActorFunc)NULL,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80BA34B0[] = {
    ICHAIN_VEC3F(scale, 1, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 0, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80BA34B0[];

extern UNK_TYPE D_060001C0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/func_80BA2420.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/ObjNozoki_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/ObjNozoki_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/func_80BA2514.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/func_80BA26A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/func_80BA2708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/func_80BA2790.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/func_80BA27C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/func_80BA28DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/func_80BA2AB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/func_80BA2B64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/func_80BA2BA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/func_80BA2C28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/func_80BA2C94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/func_80BA3044.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/func_80BA311C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/func_80BA3230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/func_80BA3344.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/ObjNozoki_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Nozoki/func_80BA3434.s")
