/*
 * File: z_obj_makekinsuta.c
 * Overlay: ovl_Obj_Makekinsuta
 * Description: Swamp Spider House - Soft soil with Skulltula hiding in it
 */

#include "z_obj_makekinsuta.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjMakekinsuta*)thisx)

void ObjMakekinsuta_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMakekinsuta_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMakekinsuta_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Makekinsuta_InitVars = {
    ACTOR_OBJ_MAKEKINSUTA,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjMakekinsuta),
    (ActorFunc)ObjMakekinsuta_Init,
    (ActorFunc)ObjMakekinsuta_Destroy,
    (ActorFunc)ObjMakekinsuta_Update,
    (ActorFunc)NULL,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8099FE30[] = {
    ICHAIN_F32(uncullZoneForward, 1, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 1, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_8099FE30[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Makekinsuta/func_8099FA40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Makekinsuta/ObjMakekinsuta_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Makekinsuta/ObjMakekinsuta_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Makekinsuta/func_8099FB64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Makekinsuta/ObjMakekinsuta_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Makekinsuta/func_8099FD7C.s")
