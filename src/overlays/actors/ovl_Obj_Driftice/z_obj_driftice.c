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
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_DRIFTICE,
    sizeof(ObjDriftice),
    (ActorFunc)ObjDriftice_Init,
    (ActorFunc)ObjDriftice_Destroy,
    (ActorFunc)ObjDriftice_Update,
    (ActorFunc)ObjDriftice_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Driftice_0x80A66570/func_80A66570.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Driftice_0x80A66570/func_80A665AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Driftice_0x80A66570/func_80A665EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Driftice_0x80A66570/func_80A667F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Driftice_0x80A66570/func_80A66930.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Driftice_0x80A66570/func_80A66C4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Driftice_0x80A66570/func_80A66E30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Driftice_0x80A66570/ObjDriftice_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Driftice_0x80A66570/ObjDriftice_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Driftice_0x80A66570/func_80A671A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Driftice_0x80A66570/func_80A671BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Driftice_0x80A66570/func_80A671CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Driftice_0x80A66570/func_80A671E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Driftice_0x80A66570/func_80A6743C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Driftice_0x80A66570/func_80A67450.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Driftice_0x80A66570/func_80A674A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Driftice_0x80A66570/func_80A674C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Driftice_0x80A66570/ObjDriftice_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Driftice_0x80A66570/ObjDriftice_Draw.asm")
