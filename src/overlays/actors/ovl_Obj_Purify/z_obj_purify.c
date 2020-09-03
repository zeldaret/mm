#include "z_obj_purify.h"

#define FLAGS 0x00000030

#define THIS ((ObjPurify*)thisx)

void ObjPurify_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjPurify_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjPurify_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Purify_InitVars = {
    ACTOR_OBJ_PURIFY,
    ACTORTYPE_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjPurify),
    (ActorFunc)ObjPurify_Init,
    (ActorFunc)ObjPurify_Destroy,
    (ActorFunc)ObjPurify_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Purify_0x80A84CD0/func_80A84CD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Purify_0x80A84CD0/func_80A84CF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Purify_0x80A84CD0/ObjPurify_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Purify_0x80A84CD0/ObjPurify_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Purify_0x80A84CD0/func_80A84EAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Purify_0x80A84CD0/func_80A84EC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Purify_0x80A84CD0/func_80A84FA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Purify_0x80A84CD0/func_80A84FB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Purify_0x80A84CD0/func_80A84FEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Purify_0x80A84CD0/func_80A85010.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Purify_0x80A84CD0/func_80A85048.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Purify_0x80A84CD0/func_80A85074.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Purify_0x80A84CD0/func_80A850B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Purify_0x80A84CD0/func_80A850E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Purify_0x80A84CD0/func_80A8515C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Purify_0x80A84CD0/func_80A85194.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Purify_0x80A84CD0/ObjPurify_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Purify_0x80A84CD0/func_80A851C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Purify_0x80A84CD0/func_80A85304.asm")
