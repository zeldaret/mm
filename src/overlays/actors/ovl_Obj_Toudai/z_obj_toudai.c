#include "z_obj_toudai.h"

#define FLAGS 0x00000030

#define THIS ((ObjToudai*)thisx)

void ObjToudai_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjToudai_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjToudai_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjToudai_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Toudai_InitVars = {
    ACTOR_OBJ_TOUDAI,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_F53_OBJ,
    sizeof(ObjToudai),
    (ActorFunc)ObjToudai_Init,
    (ActorFunc)ObjToudai_Destroy,
    (ActorFunc)ObjToudai_Update,
    (ActorFunc)ObjToudai_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Toudai_0x80A33B00/func_80A33B00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Toudai_0x80A33B00/func_80A33BB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Toudai_0x80A33B00/func_80A342F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Toudai_0x80A33B00/ObjToudai_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Toudai_0x80A33B00/ObjToudai_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Toudai_0x80A33B00/ObjToudai_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Toudai_0x80A33B00/ObjToudai_Draw.asm")
