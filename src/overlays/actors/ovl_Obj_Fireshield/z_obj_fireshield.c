#include "z_obj_fireshield.h"

#define FLAGS 0x00000010

#define THIS ((ObjFireshield*)thisx)

void ObjFireshield_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjFireshield_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjFireshield_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjFireshield_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Fireshield_InitVars = {
    ACTOR_OBJ_FIRESHIELD,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjFireshield),
    (ActorFunc)ObjFireshield_Init,
    (ActorFunc)ObjFireshield_Destroy,
    (ActorFunc)ObjFireshield_Update,
    (ActorFunc)ObjFireshield_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Fireshield/func_80A4CA90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Fireshield/func_80A4CABC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Fireshield/func_80A4CB7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Fireshield/func_80A4CC54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Fireshield/func_80A4CCBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Fireshield/func_80A4CD28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Fireshield/func_80A4CD34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Fireshield/func_80A4CE28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Fireshield/func_80A4D174.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Fireshield/func_80A4D1CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Fireshield/ObjFireshield_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Fireshield/ObjFireshield_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Fireshield/ObjFireshield_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Fireshield/ObjFireshield_Draw.s")
