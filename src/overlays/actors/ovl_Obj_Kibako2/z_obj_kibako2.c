#include "z_obj_kibako2.h"

#define FLAGS 0x00000000

#define THIS ((ObjKibako2*)thisx)

void ObjKibako2_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjKibako2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjKibako2_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjKibako2_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Kibako2_InitVars = {
    ACTOR_OBJ_KIBAKO2,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KIBAKO2,
    sizeof(ObjKibako2),
    (ActorFunc)ObjKibako2_Init,
    (ActorFunc)ObjKibako2_Destroy,
    (ActorFunc)ObjKibako2_Update,
    (ActorFunc)ObjKibako2_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_8098EE60 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x80000508, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 31, 48, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8098EE8C[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_8098EE60;
extern InitChainEntry D_8098EE8C[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako2/func_8098E5C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako2/func_8098E62C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako2/func_8098E8A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako2/func_8098E900.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako2/func_8098E9C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako2/ObjKibako2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako2/ObjKibako2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako2/func_8098EB78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako2/func_8098EC68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako2/func_8098ED20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako2/ObjKibako2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako2/ObjKibako2_Draw.s")
