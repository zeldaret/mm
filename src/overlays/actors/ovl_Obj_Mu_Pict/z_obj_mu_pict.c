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
    (ActorFunc)ObjMuPict_Draw
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/ObjMuPict_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/ObjMuPict_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/func_80C06B5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/func_80C06B70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/func_80C06C54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/func_80C06C68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/func_80C06CC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/func_80C06CD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/func_80C06D90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/func_80C06DC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/func_80C06E88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/ObjMuPict_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mu_Pict_0x80C06AA0/ObjMuPict_Draw.asm")
