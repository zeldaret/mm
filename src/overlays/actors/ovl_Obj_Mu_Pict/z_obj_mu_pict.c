#include "z_obj_mu_pict.h"

#define FLAGS 0x00000009

#define THIS ((ObjMuPict*)thisx)

void ObjMuPict_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMuPict_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMuPict_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjMuPict_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Mu_Pict_InitVars = {
    ACTOR_OBJ_MU_PICT,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjMuPict),
    (ActorFunc)ObjMuPict_Init,
    (ActorFunc)ObjMuPict_Destroy,
    (ActorFunc)ObjMuPict_Update,
    (ActorFunc)ObjMuPict_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mu_Pict/ObjMuPict_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mu_Pict/ObjMuPict_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mu_Pict/func_80C06B5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mu_Pict/func_80C06B70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mu_Pict/func_80C06C54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mu_Pict/func_80C06C68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mu_Pict/func_80C06CC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mu_Pict/func_80C06CD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mu_Pict/func_80C06D90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mu_Pict/func_80C06DC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mu_Pict/func_80C06E88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mu_Pict/ObjMuPict_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mu_Pict/ObjMuPict_Draw.s")
