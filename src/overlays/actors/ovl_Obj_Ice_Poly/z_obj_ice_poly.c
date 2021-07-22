#include "z_obj_ice_poly.h"

#define FLAGS 0x00000010

#define THIS ((ObjIcePoly*)thisx)

void ObjIcePoly_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjIcePoly_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjIcePoly_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjIcePoly_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
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


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80932320 = {
    { COLTYPE_HARD, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x02, 0x00 }, { 0xF7CFF7FF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
    { 50, 105, 0, { 0, 0, 0 } },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_8093234C = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER | AC_TYPE_OTHER, OC1_NONE, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK5, { 0xF7CFFFFF, 0x00, 0x00 }, { 0x00000800, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 65, 105, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_80932320;
extern ColliderCylinderInit D_8093234C;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ice_Poly_0x80931560/ObjIcePoly_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ice_Poly_0x80931560/ObjIcePoly_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ice_Poly_0x80931560/func_80931828.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ice_Poly_0x80931560/func_80931A38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ice_Poly_0x80931560/func_80931E58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ice_Poly_0x80931560/func_80931EEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ice_Poly_0x80931560/ObjIcePoly_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ice_Poly_0x80931560/ObjIcePoly_Draw.asm")
