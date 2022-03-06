/*
 * File: z_obj_lupygamelift.c
 * Overlay: ovl_Obj_Lupygamelift
 * Description: Deku Scrub Playground - Rupee Elevator
 */

#include "z_obj_lupygamelift.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjLupygamelift*)thisx)

void ObjLupygamelift_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjLupygamelift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjLupygamelift_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjLupygamelift_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Lupygamelift_InitVars = {
    ACTOR_OBJ_LUPYGAMELIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_RAILLIFT,
    sizeof(ObjLupygamelift),
    (ActorFunc)ObjLupygamelift_Init,
    (ActorFunc)ObjLupygamelift_Destroy,
    (ActorFunc)ObjLupygamelift_Update,
    (ActorFunc)ObjLupygamelift_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AF0740[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 400, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80AF0740[];

extern UNK_TYPE D_060048D0;
extern UNK_TYPE D_060071B8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lupygamelift/ObjLupygamelift_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lupygamelift/ObjLupygamelift_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lupygamelift/func_80AF0394.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lupygamelift/func_80AF04BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lupygamelift/func_80AF04D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lupygamelift/func_80AF0514.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lupygamelift/func_80AF0530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lupygamelift/ObjLupygamelift_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lupygamelift/ObjLupygamelift_Draw.s")
