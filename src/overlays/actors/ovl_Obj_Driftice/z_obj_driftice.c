#include "z_obj_driftice.h"

#define FLAGS 0x00000000

#define THIS ((ObjDriftice*)thisx)

void ObjDriftice_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjDriftice_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjDriftice_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjDriftice_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Driftice_InitVars = {
    ACTOR_OBJ_DRIFTICE,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_DRIFTICE,
    sizeof(ObjDriftice),
    (ActorFunc)ObjDriftice_Init,
    (ActorFunc)ObjDriftice_Destroy,
    (ActorFunc)ObjDriftice_Update,
    (ActorFunc)ObjDriftice_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A676F4[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80A676F4[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Driftice/func_80A66570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Driftice/func_80A665AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Driftice/func_80A665EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Driftice/func_80A667F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Driftice/func_80A66930.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Driftice/func_80A66C4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Driftice/func_80A66E30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Driftice/ObjDriftice_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Driftice/ObjDriftice_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Driftice/func_80A671A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Driftice/func_80A671BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Driftice/func_80A671CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Driftice/func_80A671E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Driftice/func_80A6743C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Driftice/func_80A67450.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Driftice/func_80A674A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Driftice/func_80A674C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Driftice/ObjDriftice_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Driftice/ObjDriftice_Draw.s")
