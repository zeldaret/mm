#include "z_obj_lightblock.h"

#define FLAGS 0x00000000

#define THIS ((ObjLightblock*)thisx)

void ObjLightblock_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjLightblock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjLightblock_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjLightblock_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Lightblock_InitVars = {
    ACTOR_OBJ_LIGHTBLOCK,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_LIGHTBLOCK,
    sizeof(ObjLightblock),
    (ActorFunc)ObjLightblock_Init,
    (ActorFunc)ObjLightblock_Destroy,
    (ActorFunc)ObjLightblock_Update,
    (ActorFunc)ObjLightblock_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AF3EA0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER | AC_TYPE_OTHER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00202000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 84, 120, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AF3EEC[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 500, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80AF3EA0;
extern InitChainEntry D_80AF3EEC[];

extern UNK_TYPE D_06000178;
extern UNK_TYPE D_06000B80;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/func_80AF3910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/ObjLightblock_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/ObjLightblock_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/func_80AF3AC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/func_80AF3ADC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/func_80AF3B8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/func_80AF3BA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/func_80AF3C18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/func_80AF3C34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/ObjLightblock_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lightblock/ObjLightblock_Draw.s")
