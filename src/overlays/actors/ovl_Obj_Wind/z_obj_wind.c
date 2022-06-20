/*
 * File: z_obj_wind.c
 * Overlay: ovl_Obj_Wind
 * Description: Updraft Current (STT) and Water Current (PFInterior)
 */

#include "z_obj_wind.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjWind*)thisx)

void ObjWind_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjWind_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjWind_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjWind_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Wind_InitVars = {
    ACTOR_OBJ_WIND,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjWind),
    (ActorFunc)ObjWind_Init,
    (ActorFunc)ObjWind_Destroy,
    (ActorFunc)ObjWind_Update,
    (ActorFunc)ObjWind_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B24480[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 4000, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80B24480[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Wind/ObjWind_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Wind/ObjWind_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Wind/ObjWind_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Wind/ObjWind_Draw.s")
