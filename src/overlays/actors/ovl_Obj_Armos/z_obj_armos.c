#include "z_obj_armos.h"

#define FLAGS 0x04000010

#define THIS ((ObjArmos*)thisx)

void ObjArmos_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjArmos_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjArmos_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjArmos_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

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
