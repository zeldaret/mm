#include "z_obj_taru.h"

#define FLAGS 0x00000000

#define THIS ((ObjTaru*)thisx)

void ObjTaru_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTaru_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTaru_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTaru_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Taru_InitVars = {
    ACTOR_OBJ_TARU,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_TARU,
    sizeof(ObjTaru),
    (ActorFunc)ObjTaru_Init,
    (ActorFunc)ObjTaru_Destroy,
    (ActorFunc)ObjTaru_Update,
    (ActorFunc)ObjTaru_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9B6E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9B74C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9B9C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9BC64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9BCBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9BD84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/ObjTaru_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/ObjTaru_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9BF7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9C07C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9C174.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9C1A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/ObjTaru_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/ObjTaru_Draw.s")
