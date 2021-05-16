#include "z_obj_ice_poly.h"

#define FLAGS 0x00000010

#define THIS ((ObjIcePoly*)thisx)

void ObjIcePoly_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjIcePoly_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjIcePoly_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjIcePoly_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Ice_Poly_InitVars = {
    ACTOR_OBJ_ICE_POLY,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjIcePoly),
    (ActorFunc)ObjIcePoly_Init,
    (ActorFunc)ObjIcePoly_Destroy,
    (ActorFunc)ObjIcePoly_Update,
    (ActorFunc)ObjIcePoly_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ice_Poly/ObjIcePoly_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ice_Poly/ObjIcePoly_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ice_Poly/func_80931828.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ice_Poly/func_80931A38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ice_Poly/func_80931E58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ice_Poly/func_80931EEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ice_Poly/ObjIcePoly_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ice_Poly/ObjIcePoly_Draw.s")
