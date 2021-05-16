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
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80936CF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80936D58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80936F04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80936F24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80937130.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80937160.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80937238.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80937268.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_809372A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_809372D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80937468.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_809374F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_809375C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_809375F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/ObjBean_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/ObjBean_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80937B54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80937C10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80937C24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80937C30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80937CA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80937CE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80937D54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80937DD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80937DEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80937FB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80937FC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_809381B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_809381C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938284.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938298.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_8093833C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938358.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_809383B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_809383D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938408.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938444.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_809384E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938504.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938588.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_809385A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938670.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_8093868C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938704.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938728.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_8093876C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938780.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938804.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938834.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938874.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_809388A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_8093892C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938958.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938998.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_809389BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938A14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938A5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938AA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938AD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938C1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/ObjBean_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938E00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bean/func_80938F50.s")
