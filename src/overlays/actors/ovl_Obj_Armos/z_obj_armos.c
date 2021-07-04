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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A4E00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A4E68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A4F00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A500C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A518C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/ObjArmos_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/ObjArmos_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A54B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A54E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A5610.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A562C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A57D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A57F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/ObjArmos_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A5960.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A5A3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/ObjArmos_Draw.asm")
