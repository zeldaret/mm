#include "z_obj_etcetera.h"

#define FLAGS 0x00000010

#define THIS ((ObjEtcetera*)thisx)

void ObjEtcetera_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjEtcetera_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjEtcetera_Update(Actor* thisx, GlobalContext* globalCtx);

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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/ObjEtcetera_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/ObjEtcetera_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/func_80A7BDC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/func_80A7BE8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/func_80A7BF08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/func_80A7C168.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/func_80A7C1F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/func_80A7C308.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/ObjEtcetera_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/func_80A7C690.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/func_80A7C718.asm")
