#include "z_obj_mure3.h"

#define FLAGS 0x00000000

#define THIS ((ObjMure3*)thisx)

void ObjMure3_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMure3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMure3_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Mure3_InitVars = {
    ACTOR_OBJ_MURE3,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjMure3),
    (ActorFunc)ObjMure3_Init,
    (ActorFunc)ObjMure3_Destroy,
    (ActorFunc)ObjMure3_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mure3_0x8098F040/func_8098F040.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mure3_0x8098F040/func_8098F110.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mure3_0x8098F040/func_8098F220.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mure3_0x8098F040/func_8098F364.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mure3_0x8098F040/func_8098F438.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mure3_0x8098F040/ObjMure3_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mure3_0x8098F040/ObjMure3_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mure3_0x8098F040/func_8098F598.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mure3_0x8098F040/func_8098F5AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mure3_0x8098F040/func_8098F5D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mure3_0x8098F040/func_8098F5E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mure3_0x8098F040/func_8098F66C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mure3_0x8098F040/func_8098F680.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mure3_0x8098F040/ObjMure3_Update.asm")
