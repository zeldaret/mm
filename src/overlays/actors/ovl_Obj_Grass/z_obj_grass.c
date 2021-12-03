/*
 * File: z_obj_grass.c
 * Overlay: ovl_Obj_Grass
 * Description:
 */

#include "z_obj_grass.h"

#define FLAGS 0x00000030

#define THIS ((ObjGrass*)thisx)

void ObjGrass_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjGrass_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjGrass_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjGrass_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
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

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809AAB20 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER | OC1_TYPE_2, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x0580C71C, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 6, 44, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_809AAB20;

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
