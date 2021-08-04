#include "z_obj_etcetera.h"

#define FLAGS 0x00000010

#define THIS ((ObjEtcetera*)thisx)

void ObjEtcetera_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjEtcetera_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjEtcetera_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A7BF08(ObjEtcetera* this, GlobalContext* globalCtx);
void func_80A7C168(ObjEtcetera* this, GlobalContext* globalCtx);
void func_80A7C1F0(ObjEtcetera* this, GlobalContext* globalCtx);
void func_80A7C308(ObjEtcetera* this, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Etcetera_InitVars = {
    ACTOR_OBJ_ETCETERA,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjEtcetera),
    (ActorFunc)ObjEtcetera_Init,
    (ActorFunc)ObjEtcetera_Destroy,
    (ActorFunc)ObjEtcetera_Update,
    (ActorFunc)NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A7C790 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x01000202, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 20, 14, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80A7C790;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/ObjEtcetera_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/ObjEtcetera_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7BDC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7BE8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7BF08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7C168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7C1F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7C308.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/ObjEtcetera_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7C690.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7C718.s")
