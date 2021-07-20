#include "z_obj_makekinsuta.h"

#define FLAGS 0x00000010

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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Makekinsuta_0x8099FA40/func_8099FA40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Makekinsuta_0x8099FA40/ObjMakekinsuta_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Makekinsuta_0x8099FA40/ObjMakekinsuta_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Makekinsuta_0x8099FA40/func_8099FB64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Makekinsuta_0x8099FA40/ObjMakekinsuta_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Makekinsuta_0x8099FA40/func_8099FD7C.asm")
