#include "z_obj_bean.h"

#define FLAGS 0x00400000

#define THIS ((ObjBean*)thisx)

void ObjBean_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBean_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjBean_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Bean_InitVars = {
    ACTOR_OBJ_BEAN,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_MAMENOKI,
    sizeof(ObjBean),
    (ActorFunc)ObjBean_Init,
    (ActorFunc)ObjBean_Destroy,
    (ActorFunc)ObjBean_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80936CF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80936D58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80936F04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80936F24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80937130.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80937160.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80937238.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80937268.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_809372A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_809372D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80937468.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_809374F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_809375C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_809375F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/ObjBean_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/ObjBean_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80937B54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80937C10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80937C24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80937C30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80937CA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80937CE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80937D54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80937DD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80937DEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80937FB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80937FC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_809381B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_809381C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938284.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938298.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_8093833C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938358.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_809383B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_809383D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938408.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938444.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_809384E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938504.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938588.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_809385A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938670.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_8093868C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938704.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938728.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_8093876C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938780.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938804.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938834.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938874.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_809388A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_8093892C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938958.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938998.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_809389BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938A14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938A5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938AA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938AD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938C1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/ObjBean_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938E00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bean_0x80936CF0/func_80938F50.asm")
