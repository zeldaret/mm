/*
 * File: z_obj_toudai.c
 * Overlay: ovl_Obj_Toudai
 * Description: Unused early Clock Tower Spotlight
 */

#include "z_obj_toudai.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjToudai*)thisx)

void ObjToudai_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjToudai_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjToudai_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjToudai_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
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

#endif

extern UNK_TYPE D_060023B0;
extern UNK_TYPE D_060024E8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toudai/func_80A33B00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toudai/func_80A33BB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toudai/func_80A342F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toudai/ObjToudai_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toudai/ObjToudai_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toudai/ObjToudai_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toudai/ObjToudai_Draw.s")
