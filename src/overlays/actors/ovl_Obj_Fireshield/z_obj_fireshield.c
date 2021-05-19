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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Fireshield_0x80A4CA90/func_80A4CA90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Fireshield_0x80A4CA90/func_80A4CABC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Fireshield_0x80A4CA90/func_80A4CB7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Fireshield_0x80A4CA90/func_80A4CC54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Fireshield_0x80A4CA90/func_80A4CCBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Fireshield_0x80A4CA90/func_80A4CD28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Fireshield_0x80A4CA90/func_80A4CD34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Fireshield_0x80A4CA90/func_80A4CE28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Fireshield_0x80A4CA90/func_80A4D174.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Fireshield_0x80A4CA90/func_80A4D1CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Fireshield_0x80A4CA90/ObjFireshield_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Fireshield_0x80A4CA90/ObjFireshield_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Fireshield_0x80A4CA90/ObjFireshield_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Fireshield_0x80A4CA90/ObjFireshield_Draw.asm")
