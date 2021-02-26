#include "z_obj_hsstump.h"

#define FLAGS 0x00000010

#define THIS ((ObjHsStump*)thisx)

void ObjHsStump_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHsStump_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHsStump_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHsStump_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_HsStump_InitVars = {
    ACTOR_OBJ_HSSTUMP,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_HSSTUMP,
    sizeof(ObjHsStump),
    (ActorFunc)ObjHsStump_Init,
    (ActorFunc)ObjHsStump_Destroy,
    (ActorFunc)ObjHsStump_Update,
    (ActorFunc)ObjHsStump_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_HsStump_0x80BDAA30/ObjHsStump_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_HsStump_0x80BDAA30/func_80BDAB00.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_HsStump_0x80BDAA30/func_80BDAB18.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_HsStump_0x80BDAA30/func_80BDAB6C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_HsStump_0x80BDAA30/func_80BDABCC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_HsStump_0x80BDAA30/ObjHsStump_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_HsStump_0x80BDAA30/ObjHsStump_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_HsStump_0x80BDAA30/ObjHsStump_Draw.asm")
