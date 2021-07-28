#include "z_obj_armos.h"

#define FLAGS 0x04000010

#define THIS ((ObjArmos*)thisx)

void ObjArmos_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjArmos_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjArmos_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjArmos_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Armos_InitVars = {
    ACTOR_OBJ_ARMOS,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_AM,
    sizeof(ObjArmos),
    (ActorFunc)ObjArmos_Init,
    (ActorFunc)ObjArmos_Destroy,
    (ActorFunc)ObjArmos_Update,
    (ActorFunc)ObjArmos_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_809A5BC0[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 120, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 250, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -4000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_809A5BC0[];

extern UNK_TYPE D_0600033C;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Armos/func_809A4E00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Armos/func_809A4E68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Armos/func_809A4F00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Armos/func_809A500C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Armos/func_809A518C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Armos/ObjArmos_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Armos/ObjArmos_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Armos/func_809A54B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Armos/func_809A54E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Armos/func_809A5610.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Armos/func_809A562C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Armos/func_809A57D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Armos/func_809A57F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Armos/ObjArmos_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Armos/func_809A5960.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Armos/func_809A5A3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Armos/ObjArmos_Draw.s")
