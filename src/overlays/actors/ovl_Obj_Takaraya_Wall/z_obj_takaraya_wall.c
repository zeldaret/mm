/*
 * File: z_obj_takaraya_wall.c
 * Overlay: ovl_Obj_Takaraya_Wall
 * Description: Treasure Chest Shop rising wall
 */

#include "z_obj_takaraya_wall.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjTakarayaWall*)thisx)

void ObjTakarayaWall_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTakarayaWall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTakarayaWall_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTakarayaWall_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AD9B04(ObjTakarayaWall* this, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Takaraya_Wall_InitVars = {
    ACTOR_OBJ_TAKARAYA_WALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_TAKARAYA_OBJECTS,
    sizeof(ObjTakarayaWall),
    (ActorFunc)ObjTakarayaWall_Init,
    (ActorFunc)ObjTakarayaWall_Destroy,
    (ActorFunc)ObjTakarayaWall_Update,
    (ActorFunc)ObjTakarayaWall_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80ADA2A0 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 40, 120, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80ADA2CC[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80ADA2A0;
extern InitChainEntry D_80ADA2CC[];

extern UNK_TYPE D_06000D60;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Takaraya_Wall/func_80AD9240.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Takaraya_Wall/func_80AD92FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Takaraya_Wall/func_80AD9358.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Takaraya_Wall/func_80AD9488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Takaraya_Wall/ObjTakarayaWall_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Takaraya_Wall/ObjTakarayaWall_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Takaraya_Wall/func_80AD9B04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Takaraya_Wall/ObjTakarayaWall_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Takaraya_Wall/ObjTakarayaWall_Draw.s")
