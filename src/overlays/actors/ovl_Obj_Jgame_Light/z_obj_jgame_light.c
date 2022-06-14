/*
 * File: z_obj_jgame_light.c
 * Overlay: ovl_Obj_Jgame_Light
 * Description: Fisherman's Jumping Game - Torch
 */

#include "z_obj_jgame_light.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjJgameLight*)thisx)

void ObjJgameLight_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjJgameLight_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjJgameLight_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjJgameLight_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Jgame_Light_InitVars = {
    ACTOR_OBJ_JGAME_LIGHT,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_SYOKUDAI,
    sizeof(ObjJgameLight),
    (ActorFunc)ObjJgameLight_Init,
    (ActorFunc)ObjJgameLight_Destroy,
    (ActorFunc)ObjJgameLight_Update,
    (ActorFunc)ObjJgameLight_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80C15BC0 = {
    { COLTYPE_METAL, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0x00100000, 0x00, 0x00 }, { 0xF6CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 12, 45, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80C15BC0;

extern UNK_TYPE D_060003A0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Jgame_Light/ObjJgameLight_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Jgame_Light/ObjJgameLight_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Jgame_Light/func_80C15474.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Jgame_Light/func_80C156C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Jgame_Light/func_80C15718.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Jgame_Light/ObjJgameLight_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Jgame_Light/ObjJgameLight_Draw.s")
