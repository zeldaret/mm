#include "z_obj_hsblock.h"

#define FLAGS 0x00000000

#define THIS ((ObjHsblock*)thisx)

void ObjHsblock_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHsblock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHsblock_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHsblock_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Hsblock_InitVars = {
    ACTOR_OBJ_HSBLOCK,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_D_HSBLOCK,
    sizeof(ObjHsblock),
    (ActorFunc)ObjHsblock_Init,
    (ActorFunc)ObjHsblock_Destroy,
    (ActorFunc)ObjHsblock_Update,
    (ActorFunc)ObjHsblock_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hsblock_0x8093DEA0/func_8093DEA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hsblock_0x8093DEA0/func_8093DEAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hsblock_0x8093DEA0/ObjHsblock_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hsblock_0x8093DEA0/ObjHsblock_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hsblock_0x8093DEA0/func_8093E03C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hsblock_0x8093DEA0/func_8093E05C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hsblock_0x8093DEA0/func_8093E0A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hsblock_0x8093DEA0/func_8093E0E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hsblock_0x8093DEA0/func_8093E10C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hsblock_0x8093DEA0/ObjHsblock_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hsblock_0x8093DEA0/ObjHsblock_Draw.asm")
