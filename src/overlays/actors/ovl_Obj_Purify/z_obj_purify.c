/*
 * File: z_obj_purify.c
 * Overlay: ovl_Obj_Purify
 * Description: Poisoned/Purified Water Elements
 */

#include "z_obj_purify.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjPurify*)thisx)

void ObjPurify_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjPurify_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjPurify_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Purify_InitVars = {
    ACTOR_OBJ_PURIFY,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjPurify),
    (ActorFunc)ObjPurify_Init,
    (ActorFunc)ObjPurify_Destroy,
    (ActorFunc)ObjPurify_Update,
    (ActorFunc)NULL,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A84CD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A84CF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/ObjPurify_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/ObjPurify_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A84EAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A84EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A84FA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A84FB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A84FEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A85010.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A85048.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A85074.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A850B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A850E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A8515C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A85194.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/ObjPurify_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A851C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A85304.s")
