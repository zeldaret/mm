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
    ACTORTYPE_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjFireshield),
    (ActorFunc)ObjFireshield_Init,
    (ActorFunc)ObjFireshield_Destroy,
    (ActorFunc)ObjFireshield_Update,
    (ActorFunc)ObjFireshield_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Fireshield_0x80A4CA90/func_80A4CA90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Fireshield_0x80A4CA90/func_80A4CABC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Fireshield_0x80A4CA90/func_80A4CB7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Fireshield_0x80A4CA90/func_80A4CC54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Fireshield_0x80A4CA90/func_80A4CCBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Fireshield_0x80A4CA90/func_80A4CD28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Fireshield_0x80A4CA90/func_80A4CD34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Fireshield_0x80A4CA90/func_80A4CE28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Fireshield_0x80A4CA90/func_80A4D174.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Fireshield_0x80A4CA90/func_80A4D1CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Fireshield_0x80A4CA90/ObjFireshield_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Fireshield_0x80A4CA90/ObjFireshield_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Fireshield_0x80A4CA90/ObjFireshield_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Fireshield_0x80A4CA90/ObjFireshield_Draw.asm")
