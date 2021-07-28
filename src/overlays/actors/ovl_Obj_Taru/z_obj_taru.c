#include "z_obj_taru.h"

#define FLAGS 0x00000000

#define THIS ((ObjTaru*)thisx)

void ObjTaru_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTaru_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTaru_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTaru_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
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

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B9C340 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x80000508, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 30, 50, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B9C36C[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 3300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80B9C340;
extern InitChainEntry D_80B9C36C[];

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
