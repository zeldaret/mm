#include "z_obj_driftice.h"

#define FLAGS 0x00000000

#define THIS ((ObjDriftice*)thisx)

void ObjDriftice_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjDriftice_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjDriftice_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjDriftice_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Driftice_InitVars = {
    ACTOR_OBJ_DRIFTICE,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_DRIFTICE,
    sizeof(ObjDriftice),
    (ActorFunc)ObjDriftice_Init,
    (ActorFunc)ObjDriftice_Destroy,
    (ActorFunc)ObjDriftice_Update,
    (ActorFunc)ObjDriftice_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Driftice_0x80A66570/func_80A66570.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Driftice_0x80A66570/func_80A665AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Driftice_0x80A66570/func_80A665EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Driftice_0x80A66570/func_80A667F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Driftice_0x80A66570/func_80A66930.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Driftice_0x80A66570/func_80A66C4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Driftice_0x80A66570/func_80A66E30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Driftice_0x80A66570/ObjDriftice_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Driftice_0x80A66570/ObjDriftice_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Driftice_0x80A66570/func_80A671A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Driftice_0x80A66570/func_80A671BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Driftice_0x80A66570/func_80A671CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Driftice_0x80A66570/func_80A671E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Driftice_0x80A66570/func_80A6743C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Driftice_0x80A66570/func_80A67450.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Driftice_0x80A66570/func_80A674A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Driftice_0x80A66570/func_80A674C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Driftice_0x80A66570/ObjDriftice_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Driftice_0x80A66570/ObjDriftice_Draw.asm")
