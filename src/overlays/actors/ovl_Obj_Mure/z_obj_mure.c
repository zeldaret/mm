#include "z_obj_mure.h"

#define FLAGS 0x00000000

#define THIS ((ObjMure*)thisx)

void ObjMure_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMure_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMure_Update(Actor* thisx, GlobalContext* globalCtx);

void func_808D7FFC(ObjMure* this, GlobalContext* globalCtx);
void func_808D8014(ObjMure* this, GlobalContext* globalCtx);
void func_808D8678(ObjMure* this, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Mure_InitVars = {
    ACTOR_OBJ_MURE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjMure),
    (ActorFunc)ObjMure_Init,
    (ActorFunc)ObjMure_Destroy,
    (ActorFunc)ObjMure_Update,
    (ActorFunc)NULL,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808D87BC[] = {
    ICHAIN_F32(uncullZoneForward, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1200, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_808D87BC[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D78D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D7928.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/ObjMure_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/ObjMure_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D7A14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D7A40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D7A68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D7C64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D7DC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D7E14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D7F0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D7F2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D7FFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D8014.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D8074.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D814C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D82CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D84F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D8678.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/ObjMure_Update.s")
