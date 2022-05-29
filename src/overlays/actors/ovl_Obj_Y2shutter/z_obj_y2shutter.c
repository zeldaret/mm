/*
 * File: z_obj_y2shutter.c
 * Overlay: ovl_Obj_Y2shutter
 * Description: Pirates' Fortress sliding grate
 */

#include "z_obj_y2shutter.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjY2shutter*)thisx)

void ObjY2shutter_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjY2shutter_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjY2shutter_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjY2shutter_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Y2shutter_InitVars = {
    ACTOR_OBJ_Y2SHUTTER,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KAIZOKU_OBJ,
    sizeof(ObjY2shutter),
    (ActorFunc)ObjY2shutter_Init,
    (ActorFunc)ObjY2shutter_Destroy,
    (ActorFunc)ObjY2shutter_Update,
    (ActorFunc)ObjY2shutter_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B9AEB0[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 800, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80B9AEB0[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Y2shutter/ObjY2shutter_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Y2shutter/ObjY2shutter_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Y2shutter/func_80B9AA20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Y2shutter/ObjY2shutter_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Y2shutter/ObjY2shutter_Draw.s")
