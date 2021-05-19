#include "z_obj_bean.h"

#define FLAGS 0x00400000

#define THIS ((ObjBean*)thisx)

void ObjBean_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBean_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjBean_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Bean_InitVars = {
    ACTOR_OBJ_BEAN,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_MAMENOKI,
    sizeof(ObjBean),
    (ActorFunc)ObjBean_Init,
    (ActorFunc)ObjBean_Destroy,
    (ActorFunc)ObjBean_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80936CF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80936D58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80936F04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80936F24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80937130.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80937160.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80937238.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80937268.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_809372A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_809372D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80937468.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_809374F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_809375C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_809375F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/ObjBean_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/ObjBean_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80937B54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80937C10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80937C24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80937C30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80937CA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80937CE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80937D54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80937DD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80937DEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80937FB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80937FC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_809381B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_809381C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938284.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938298.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_8093833C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938358.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_809383B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_809383D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938408.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938444.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_809384E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938504.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938588.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_809385A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938670.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_8093868C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938704.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938728.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_8093876C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938780.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938804.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938834.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938874.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_809388A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_8093892C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938958.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938998.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_809389BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938A14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938A5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938AA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938AD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938C1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/ObjBean_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938E00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bean_0x80936CF0/func_80938F50.asm")
