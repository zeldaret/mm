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
    (ActorFunc)ObjIcePoly_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ice_Poly_0x80931560/ObjIcePoly_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ice_Poly_0x80931560/ObjIcePoly_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ice_Poly_0x80931560/func_80931828.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ice_Poly_0x80931560/func_80931A38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ice_Poly_0x80931560/func_80931E58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ice_Poly_0x80931560/func_80931EEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ice_Poly_0x80931560/ObjIcePoly_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ice_Poly_0x80931560/ObjIcePoly_Draw.asm")
