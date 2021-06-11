#include "z_obj_kzsaku.h"

#define FLAGS 0x00000030

#define THIS ((ObjKzsaku*)thisx)

void ObjKzsaku_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjKzsaku_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjKzsaku_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjKzsaku_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Kzsaku_InitVars = {
    ACTOR_OBJ_KZSAKU,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_KZSAKU,
    sizeof(ObjKzsaku),
    (ActorFunc)ObjKzsaku_Init,
    (ActorFunc)ObjKzsaku_Destroy,
    (ActorFunc)ObjKzsaku_Update,
    (ActorFunc)ObjKzsaku_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kzsaku/ObjKzsaku_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kzsaku/ObjKzsaku_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kzsaku/func_80C08B60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kzsaku/func_80C08B7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kzsaku/func_80C08BBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kzsaku/func_80C08BD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kzsaku/func_80C08C84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kzsaku/func_80C08CB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kzsaku/ObjKzsaku_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kzsaku/ObjKzsaku_Draw.s")
