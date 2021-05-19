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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Taru_0x80B9B6E0/func_80B9B6E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Taru_0x80B9B6E0/func_80B9B74C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Taru_0x80B9B6E0/func_80B9B9C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Taru_0x80B9B6E0/func_80B9BC64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Taru_0x80B9B6E0/func_80B9BCBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Taru_0x80B9B6E0/func_80B9BD84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Taru_0x80B9B6E0/ObjTaru_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Taru_0x80B9B6E0/ObjTaru_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Taru_0x80B9B6E0/func_80B9BF7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Taru_0x80B9B6E0/func_80B9C07C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Taru_0x80B9B6E0/func_80B9C174.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Taru_0x80B9B6E0/func_80B9C1A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Taru_0x80B9B6E0/ObjTaru_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Taru_0x80B9B6E0/ObjTaru_Draw.asm")
