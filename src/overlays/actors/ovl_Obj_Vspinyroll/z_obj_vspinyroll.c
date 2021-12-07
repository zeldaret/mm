/*
 * File: z_obj_vspinyroll.c
 * Overlay: ovl_Obj_Vspinyroll
 * Description: Vertical Spiked rollers
 */

#include "z_obj_vspinyroll.h"

#define FLAGS 0x00000010

#define THIS ((ObjVspinyroll*)thisx)

void ObjVspinyroll_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjVspinyroll_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjVspinyroll_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjVspinyroll_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A3CEE0(ObjVspinyroll* this, GlobalContext* globalCtx);
void func_80A3CF4C(ObjVspinyroll* this, GlobalContext* globalCtx);
void func_80A3CFE0(ObjVspinyroll* this, GlobalContext* globalCtx);
void func_80A3D038(ObjVspinyroll* this, GlobalContext* globalCtx);
void func_80A3D0FC(ObjVspinyroll* this, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Vspinyroll_InitVars = {
    ACTOR_OBJ_VSPINYROLL,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_SPINYROLL,
    sizeof(ObjVspinyroll),
    (ActorFunc)ObjVspinyroll_Init,
    (ActorFunc)ObjVspinyroll_Destroy,
    (ActorFunc)ObjVspinyroll_Update,
    (ActorFunc)ObjVspinyroll_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A3D488 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x20000000, 0x00, 0x04 }, { 0x01C37BB6, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 30, 120, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A3D4D4[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 500, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80A3D488;
extern InitChainEntry D_80A3D4D4[];

extern UNK_TYPE D_06000460;
extern UNK_TYPE D_06000F80;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3C4E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3C560.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3C658.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3C6A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3C6CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3C700.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3C7E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3C8D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CB94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CBF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CC30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CC84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/ObjVspinyroll_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/ObjVspinyroll_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CEC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CEE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CF10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CF4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CFAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CFE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3D024.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3D038.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3D0E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3D0FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/ObjVspinyroll_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/ObjVspinyroll_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3D2C0.s")
