#include "z_obj_nozoki.h"

#define FLAGS 0x00000010

#define THIS ((ObjNozoki*)thisx)

void ObjNozoki_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjNozoki_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjNozoki_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Nozoki_InitVars = {
    ACTOR_OBJ_NOZOKI,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjNozoki),
    (ActorFunc)ObjNozoki_Init,
    (ActorFunc)ObjNozoki_Destroy,
    (ActorFunc)ObjNozoki_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/func_80BA2420.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/ObjNozoki_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/ObjNozoki_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/func_80BA2514.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/func_80BA26A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/func_80BA2708.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/func_80BA2790.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/func_80BA27C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/func_80BA28DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/func_80BA2AB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/func_80BA2B64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/func_80BA2BA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/func_80BA2C28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/func_80BA2C94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/func_80BA3044.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/func_80BA311C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/func_80BA3230.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/func_80BA3344.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/ObjNozoki_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Nozoki_0x80BA2420/func_80BA3434.asm")
