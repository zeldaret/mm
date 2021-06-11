#include "z_obj_grass.h"

#define FLAGS 0x00000030

#define THIS ((ObjGrass*)thisx)

void ObjGrass_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjGrass_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjGrass_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjGrass_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Grass_InitVars = {
    ACTOR_OBJ_GRASS,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_FIELD_KEEP,
    sizeof(ObjGrass),
    (ActorFunc)ObjGrass_Init,
    (ActorFunc)ObjGrass_Destroy,
    (ActorFunc)ObjGrass_Update,
    (ActorFunc)ObjGrass_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass/func_809A9110.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass/func_809A91FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass/func_809A92D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass/func_809A9314.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass/ObjGrass_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass/ObjGrass_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass/func_809A9790.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass/func_809A983C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass/func_809A9DB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass/ObjGrass_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass/func_809AA278.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass/func_809AA54C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass/func_809AA798.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass/ObjGrass_Draw.s")
