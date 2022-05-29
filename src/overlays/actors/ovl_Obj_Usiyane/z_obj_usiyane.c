/*
 * File: z_obj_usiyane.c
 * Overlay: ovl_Obj_Usiyane
 * Description: Roof of Cow Barn
 */

#include "z_obj_usiyane.h"

#define FLAGS (ACTOR_FLAG_20)

#define THIS ((ObjUsiyane*)thisx)

void ObjUsiyane_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjUsiyane_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjUsiyane_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjUsiyane_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Usiyane_InitVars = {
    ACTOR_OBJ_USIYANE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_OBJ_USIYANE,
    sizeof(ObjUsiyane),
    (ActorFunc)ObjUsiyane_Init,
    (ActorFunc)ObjUsiyane_Destroy,
    (ActorFunc)ObjUsiyane_Update,
    (ActorFunc)ObjUsiyane_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80C086B0[] = {
    ICHAIN_F32(uncullZoneScale, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 3000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 900, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80C086B0[];

extern UNK_TYPE D_06000838;
extern UNK_TYPE D_060022AC;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Usiyane/func_80C07C80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Usiyane/func_80C07CD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Usiyane/func_80C07DC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Usiyane/func_80C07DFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Usiyane/func_80C07F30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Usiyane/func_80C081C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Usiyane/func_80C082CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Usiyane/func_80C082E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Usiyane/ObjUsiyane_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Usiyane/ObjUsiyane_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Usiyane/ObjUsiyane_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Usiyane/ObjUsiyane_Draw.s")
