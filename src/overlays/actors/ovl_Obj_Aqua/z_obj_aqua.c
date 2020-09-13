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
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjAqua),
    (ActorFunc)ObjAqua_Init,
    (ActorFunc)ObjAqua_Destroy,
    (ActorFunc)ObjAqua_Update,
    (ActorFunc)ObjAqua_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Aqua_0x80ACB6A0/func_80ACB6A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Aqua_0x80ACB6A0/func_80ACB7F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Aqua_0x80ACB6A0/func_80ACB940.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Aqua_0x80ACB6A0/func_80ACBA10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Aqua_0x80ACB6A0/func_80ACBA60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Aqua_0x80ACB6A0/ObjAqua_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Aqua_0x80ACB6A0/ObjAqua_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Aqua_0x80ACB6A0/func_80ACBC70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Aqua_0x80ACB6A0/func_80ACBC8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Aqua_0x80ACB6A0/func_80ACBD34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Aqua_0x80ACB6A0/func_80ACBD48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Aqua_0x80ACB6A0/func_80ACBDCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Aqua_0x80ACB6A0/func_80ACBDFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Aqua_0x80ACB6A0/ObjAqua_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Aqua_0x80ACB6A0/ObjAqua_Draw.asm")
