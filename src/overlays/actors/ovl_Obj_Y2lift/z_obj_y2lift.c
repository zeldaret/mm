#include "z_obj_y2lift.h"

#define FLAGS 0x00000010

#define THIS ((ObjY2lift*)thisx)

void ObjY2lift_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjY2lift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjY2lift_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjY2lift_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit Obj_Y2lift_InitVars = {
    ACTOR_OBJ_Y2LIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KAIZOKU_OBJ,
    sizeof(ObjY2lift),
    (ActorFunc)ObjY2lift_Init,
    (ActorFunc)ObjY2lift_Destroy,
    (ActorFunc)ObjY2lift_Update,
    (ActorFunc)ObjY2lift_Draw,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B9A940[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 800, ICHAIN_STOP),
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Y2lift_0x80B9A650/ObjY2lift_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Y2lift_0x80B9A650/ObjY2lift_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Y2lift_0x80B9A650/ObjY2lift_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Y2lift_0x80B9A650/ObjY2lift_Draw.asm")
