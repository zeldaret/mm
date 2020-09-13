#include "z_obj_mure.h"

#define FLAGS 0x00000000

#define THIS ((ObjMure*)thisx)

void ObjMure_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMure_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMure_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Mure_InitVars = {
    ACTOR_OBJ_MURE,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjMure),
    (ActorFunc)ObjMure_Init,
    (ActorFunc)ObjMure_Destroy,
    (ActorFunc)ObjMure_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/func_808D78D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/func_808D7928.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/ObjMure_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/ObjMure_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/func_808D7A14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/func_808D7A40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/func_808D7A68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/func_808D7C64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/func_808D7DC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/func_808D7E14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/func_808D7F0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/func_808D7F2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/func_808D7FFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/func_808D8014.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/func_808D8074.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/func_808D814C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/func_808D82CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/func_808D84F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/func_808D8678.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mure_0x808D78D0/ObjMure_Update.asm")
