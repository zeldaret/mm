#include "z_obj_aqua.h"

#define FLAGS 0x00000010

#define THIS ((ObjAqua*)thisx)

void ObjAqua_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjAqua_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjAqua_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjAqua_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Aqua_InitVars = {
    ACTOR_OBJ_AQUA,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjAqua),
    (ActorFunc)ObjAqua_Init,
    (ActorFunc)ObjAqua_Destroy,
    (ActorFunc)ObjAqua_Update,
    (ActorFunc)ObjAqua_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACB6A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACB7F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACB940.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBA10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBA60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/ObjAqua_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/ObjAqua_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBC70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBC8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBD34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBD48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBDCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/func_80ACBDFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/ObjAqua_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Aqua/ObjAqua_Draw.s")
